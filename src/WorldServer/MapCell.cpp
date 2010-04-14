/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

#include "StdAfx.h"

MapCell::MapCell()
{
	_forcedActive = false;
}

MapCell::~MapCell()
{
	RemoveObjects();
}

void MapCell::Init(uint32 x, uint32 y, uint32 mapid, MapMgrPointer mapmgr)
{
	_mapmgr = mapmgr;
	_active = false;
	_loaded = false;
	_playerCount = 0;
	_x=x;
	_y=y;
	_unloadpending=false;
	_objects.clear();
}

void MapCell::AddObject(ObjectPointer obj)
{
	if(obj->IsPlayer())
		++_playerCount;

	AquireLock();
	_objects.insert(obj);
	ReleaseLock(); 
}

void MapCell::RemoveObject(ObjectPointer obj)
{
	if(obj->IsPlayer())
		--_playerCount;

	AquireLock();
	_objects.erase(obj);
	ReleaseLock();
}

void MapCell::SetActivity(bool state)
{	
	if(!_active && state)
	{
		// Move all objects to active set.
		for(ObjectSet::iterator itr = _objects.begin(); itr != _objects.end(); ++itr)
		{
			if(!(*itr)->Active && (*itr)->CanActivate())
				(*itr)->Activate(_mapmgr);
		}

		if(_unloadpending)
			CancelPendingUnload();

		if (_mapmgr->IsCollisionEnabled())
			CollideInterface.ActivateTile(_mapmgr->GetMapId(), _x/8, _y/8);
	} else if(_active && !state)
	{
		// Move all objects from active set.
		for(ObjectSet::iterator itr = _objects.begin(); itr != _objects.end(); ++itr)
		{
			if((*itr)->Active)
				(*itr)->Deactivate(_mapmgr);
		}

		if(sWorld.map_unload_time && !_unloadpending)
			QueueUnloadPending();

		if (_mapmgr->IsCollisionEnabled())
			CollideInterface.DeactivateTile(_mapmgr->GetMapId(), _x/8, _y/8);
	}

	_active = state; 

}
void MapCell::RemoveObjects()
{
	ObjectSet::iterator itr;
	//uint32 ltime = getMSTime();

	/* delete objects in pending respawn state */
	ObjectPointer pObject;
	for(itr = _respawnObjects.begin(); itr != _respawnObjects.end(); ++itr)
	{
		pObject = *itr;
		if(!pObject)
			continue;
		
		switch(pObject->GetTypeId())
		{
		case TYPEID_UNIT: {
				if( pObject->IsVehicle() )
				{
					_mapmgr->_reusable_guids_vehicle.push_back( pObject->GetUIdFromGUID() );
					TO_VEHICLE(pObject)->m_respawnCell=NULL;
					TO_VEHICLE(pObject)->Destructor();
					pObject = NULLOBJ;
				}
				else if( !pObject->IsPet() )
				{
					_mapmgr->_reusable_guids_creature.push_back( pObject->GetUIdFromGUID() );
					TO_CREATURE(pObject)->m_respawnCell=NULL;
					TO_CREATURE(pObject)->Destructor();
					pObject = NULLOBJ;
				}
			}break;

		case TYPEID_GAMEOBJECT: {
			TO_GAMEOBJECT(pObject)->m_respawnCell=NULL;
			TO_GAMEOBJECT(pObject)->Destructor();
			pObject = NULLOBJ;
			}break;
		default:
			pObject->Destructor();
			pObject = NULLOBJ;
			break;

		}
	}
	_respawnObjects.clear();

	// This time it's simpler! We just remove everything :)
	ObjectPointer obj; // do this outside the loop!
	for(itr = _objects.begin(); itr != _objects.end();)
	{
		obj = (*itr);
		itr++;

		if(!obj)
			continue;

		if( _unloadpending )
		{
			if(obj->GetTypeFromGUID() == HIGHGUID_TYPE_TRANSPORTER)
				continue;

			if(obj->GetTypeId()==TYPEID_CORPSE && obj->GetUInt32Value(CORPSE_FIELD_OWNER) != 0)
				continue;

			if(!obj->m_loadedFromDB)
				continue;
		}

		if( obj->Active )
			obj->Deactivate( _mapmgr );

		if( obj->IsInWorld())
			obj->RemoveFromWorld( true );

		obj->Destructor();
		obj = NULLOBJ;
	}

	_playerCount = 0;
	_loaded = false;
}


void MapCell::LoadObjects(CellSpawns * sp)
{
	_loaded = true;
	Instance * pInstance = _mapmgr->pInstance;

	if(sp->CreatureSpawns.size())//got creatures
	{
		VehiclePointer v;
		CreaturePointer c;
		for(CreatureSpawnList::iterator i=sp->CreatureSpawns.begin();i!=sp->CreatureSpawns.end();i++)
		{
			if(pInstance)
			{
				if(pInstance->m_killedNpcs.find((*i)->id) != pInstance->m_killedNpcs.end())
					continue;
			}
			if(!(*i)->eventid)
			{
				if((*i)->vehicle != 0)
				{
					v=_mapmgr->CreateVehicle((*i)->entry);

					v->SetMapId(_mapmgr->GetMapId());
					v->SetInstanceID(_mapmgr->GetInstanceID());
					v->m_loadedFromDB = true;

					if(v->Load(*i, _mapmgr->iInstanceMode, _mapmgr->GetMapInfo()))
					{
						if(!v->CanAddToWorld())
						{
							v->Destructor();
							v = NULLVEHICLE;
							continue;
						}

						v->PushToWorld(_mapmgr);
					}
					else
					{
						v->Destructor();
						v = NULLVEHICLE;
					}
				}
				else
				{
					c=_mapmgr->CreateCreature((*i)->entry);

					c->SetMapId(_mapmgr->GetMapId());
					c->SetInstanceID(_mapmgr->GetInstanceID());
					c->m_loadedFromDB = true;

					if(c->Load(*i, _mapmgr->iInstanceMode, _mapmgr->GetMapInfo()))
					{
						if(!c->CanAddToWorld())
						{
							c->Destructor();
							c = NULLCREATURE;
							continue;
						}

						c->PushToWorld(_mapmgr);
					}
					else
					{
						c->Destructor();
						c = NULLCREATURE;
					}
				}
			}
		}
	}

	if(sp->GOSpawns.size()) // got GOs
	{
		GameObjectPointer go;
		for(GOSpawnList::iterator i=sp->GOSpawns.begin();i!=sp->GOSpawns.end();i++)
		{
			if(!(*i)->eventid)
			{
				go = _mapmgr->CreateGameObject((*i)->entry);
				if(go == NULL)
					continue;
				if(go->Load(*i))
				{
					go->m_loadedFromDB = true;
					go->PushToWorld(_mapmgr);
					CALL_GO_SCRIPT_EVENT(go, OnSpawn)();
				}
				else
				{
					go->Destructor();
					go = NULLGOB;
				}
			}
		}
	}
}

void MapCell::QueueUnloadPending()
{
	if(_unloadpending)
		return;

	_unloadpending = true;
	sEventMgr.AddEvent(_mapmgr, &MapMgr::UnloadCell,(uint32)_x,(uint32)_y,MAKE_CELL_EVENT(_x,_y),sWorld.map_unload_time * 1000,1,0);
}

void MapCell::CancelPendingUnload()
{
	if(!_unloadpending)
		return;

	sEventMgr.RemoveEvents(_mapmgr,MAKE_CELL_EVENT(_x,_y));
}

void MapCell::Unload()
{
	ASSERT(_unloadpending);
	if(_active)
		return;

	RemoveObjects();
	_unloadpending=false;
}