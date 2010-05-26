/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

#include "StdAfx.h"

initialiseSingleton( WintergraspInternal );

#ifdef WIN32
static HANDLE m_abortEvent = INVALID_HANDLE_VALUE;
#else
static pthread_cond_t abortcond;
static pthread_mutex_t abortmutex;
#endif

WintergraspInternal::WintergraspInternal() : WGMgr(*(sInstanceMgr.GetMapMgr(571)))
{
	m_threadRunning = true;
	m_dirty = false;
	WGcounter = 0;
	SetWGTimer((6*60000)*3);
}

WintergraspInternal::~WintergraspInternal()
{
}

void WintergraspInternal::terminate()
{
	m_threadRunning = false;
}

void WintergraspInternal::set_tm_pointers()
{
	dupe_tm_pointer(localtime(&last_wintergrasp_time), &local_last_wintergrasp_time);
}

void WintergraspInternal::LoadWintergraspSettings()
{
	QueryResult* result = CharacterDatabase.Query("SELECT setting_value FROM server_settings WHERE setting_id = \"last_wintergrasp_time\"");
	if(result)
	{
		last_wintergrasp_time = result->Fetch()[0].GetUInt32();
		delete result;
	}
	else
		last_wintergrasp_time = 0;
}

void WintergraspInternal::UpdateWintergraspSettings()
{
	CharacterDatabase.Execute("REPLACE INTO server_settings VALUES(\"last_wintergrasp_time\", %u)", last_wintergrasp_time);
}

void WintergraspInternal::dupe_tm_pointer(tm * returnvalue, tm * mypointer)
{
	memcpy(mypointer, returnvalue, sizeof(tm));
}

bool WintergraspInternal::has_timeout_expired(tm * now_time, tm * last_time, uint32 timeoutval)
{
	switch(timeoutval)
	{
	case MONTHLY:
		return (now_time->tm_mon != last_time->tm_mon);

	case WEEKLY:
		return ( (now_time->tm_mday / 7) != (last_time->tm_mday / 7) || (now_time->tm_mon != last_time->tm_mon) );

	case DAILY:
		return ((now_time->tm_mday != last_time->tm_mday) || (now_time->tm_mon != last_time->tm_mon));

	case HOURLY:
		return ((now_time->tm_hour != last_time->tm_hour) || (now_time->tm_mday != last_time->tm_mday) || (now_time->tm_mon != last_time->tm_mon));

	case MINUTELY:
		return ((now_time->tm_min != last_time->tm_min) || (now_time->tm_hour != last_time->tm_hour) || (now_time->tm_mday != last_time->tm_mday) || (now_time->tm_mon != last_time->tm_mon));
	}
	return false;
}

bool WintergraspInternal::run()
{
	SetThreadName("WGInternal");

	LoadWintergraspSettings();

	Log.Notice("WGInternal", "Wintergrasp Handler Initiated.");

	while(m_threadRunning)
	{
		if(has_timeout_expired(&local_currenttime, &local_last_wintergrasp_time, HOURLY))
		{
			++WGcounter;

			if(WGcounter >= 3)
			{
				Log.Notice("WGInternal", "Wintergrasp function called.");
				if(m_wintergrasp == 0)
				{
					Log.Notice("WGInternal", "Starting Wintergrasp.");
					WG = Wintergrasp::Create(this, &WGMgr);

					last_wintergrasp_time = UNIXTIME;
					dupe_tm_pointer(localtime(&last_wintergrasp_time), &local_last_wintergrasp_time);
				}
				WGcounter = 0; // Reset our timer.
				m_dirty = true;
			}
		}

		if(m_dirty)
			UpdateWintergraspSettings();
	}
	return false;
}

void WintergraspInternal::SendInitWorldStates(Player* plr)
{
	printf("Pieflavor");
	WorldPacket data(SMSG_INIT_WORLD_STATES, (4+4+4+2));
	data << uint32(571);
	data << uint32(WARCTIC_WINTERGRASP);
	data << uint32(0);
	data << uint16(4+5+(WG ? 4 : 0));

	data << uint32(3803) << uint32(defendingteam == ALLIANCE ? 1 : 0);
	data << uint32(3802) << uint32(defendingteam != ALLIANCE ? 1 : 0);
	data << uint32(3801) << uint32(WG_started ? 0 : 1);
	data << uint32(3710) << uint32(WG_started ? 1 : 0);

	for (uint32 i = 0; i < 5; ++i)
		data << ClockWorldState[i] << m_clock[i];

	if(WG_started && WG != NULL)
	{
		data << uint32(A_NUMVEH_WORLDSTATE) << uint32(WG->GetNumVehicles(ALLIANCE));
		data << uint32(A_MAXVEH_WORLDSTATE) << uint32(WG->GetNumWorkshops(ALLIANCE)*4);
		data << uint32(H_NUMVEH_WORLDSTATE) << uint32(WG->GetNumVehicles(HORDE));
		data << uint32(H_MAXVEH_WORLDSTATE) << uint32(WG->GetNumWorkshops(HORDE)*4);
	}

	if(plr)
		plr->GetSession()->SendPacket(&data);
	else
	{
		if(WG != NULL)
		{
			for(WintergraspPlayerSet::iterator itr = WG->WGPlayers.begin(); itr != WG->WGPlayers.end(); ++itr)
				(*itr)->GetSession()->SendPacket(&data);
		}
		else
		{
			for(PlayerStorageMap::iterator itr =  WGMgr.m_PlayerStorage.begin(); itr != WGMgr.m_PlayerStorage.end(); ++itr)
			{
				plr = itr->second;
				if((plr->GetAreaID() == WARCTIC_WINTERGRASP) || (plr->GetZoneId() == WARCTIC_WINTERGRASP))
					plr->GetSession()->SendPacket(&data);
			}
		}
		plr = NULL;
	}
}

void WintergraspInternal::UpdateClockDigit(uint32 timer, uint32 digit, uint32 mod)
{
    uint32 value = timer%mod;
    timer /= mod;
    if(m_clock[digit] != value)
    {
        m_clock[digit] = value;
		SendWSUpdateToAll(ClockWorldState[digit], value);
    }
	WGMgr.GetStateManager().UpdateWorldState(m_clock[digit], value);
}

void WintergraspInternal::SendWSUpdateToAll(uint32 WorldState, uint32 Value)
{
	Player* plr = NULL;
	WorldPacket data(SMSG_UPDATE_WORLD_STATE, 8);
	data << WorldState;
	data << Value;
	if(WG != NULL)
	{
		for(WintergraspPlayerSet::iterator itr = WG->WGPlayers.begin(); itr != WG->WGPlayers.end(); ++itr)
			(*itr)->GetSession()->SendPacket(&data);
	}
	else
	{
		for(PlayerStorageMap::iterator itr =  WGMgr.m_PlayerStorage.begin(); itr != WGMgr.m_PlayerStorage.end(); ++itr)
		{
			plr = itr->second;
			if((plr->GetAreaID() == WARCTIC_WINTERGRASP) || (plr->GetZoneId() == WARCTIC_WINTERGRASP))
				plr->GetSession()->SendPacket(&data);
		}
	}
}

void WintergraspInternal::UpdateClock()
{
    uint32 timer = m_timer / 1000;
    UpdateClockDigit(timer, 0, 10);
    UpdateClockDigit(timer, 1, 6);
    UpdateClockDigit(timer, 2, 10);
    UpdateClockDigit(timer, 3, 6);
    if(!WG_started)
        UpdateClockDigit(timer, 4, 10);
}
