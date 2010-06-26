/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

#ifndef __BATTLEGROUNDMGR_H
#define __BATTLEGROUNDMGR_H

class CBattleground;
class MapMgr;
class Player;
class Map;
class Group;
class Corpse;

enum BattleGroundTypes
{
	BATTLEGROUND_ALTERAC_VALLEY = 1,
	BATTLEGROUND_WARSONG_GULCH,
	BATTLEGROUND_ARATHI_BASIN,
	BATTLEGROUND_ARENA_2V2,
	BATTLEGROUND_ARENA_3V3,
	BATTLEGROUND_ARENA_5V5,
	BATTLEGROUND_EYE_OF_THE_STORM,
	BATTLEGROUND_ARENA,
	BATTLEGROUND_STRAND_OF_THE_ANCIENTS,
	BATTLEGROUND_NUM_TYPES,
};

struct BGScore
{
	uint32 KillingBlows;
	uint32 HonorableKills;
	uint32 Deaths;
	uint32 BonusHonor;
	uint32 DamageDone;
	uint32 HealingDone;

	// the max one for this is , for AV
	uint32 MiscData[5];
};

// bg score declarations
#define BG_SCORE_WSG_FLAG_CAPTURES			0
#define BG_SCORE_WSG_FLAG_RETURNS			1
#define BG_SCORE_AB_BASE_ASSAULTED			0
#define BG_SCORE_AB_BASE_DEFENDED			1
#define BG_SCORE_AV_GRAVEYARDS_ASSAULTED	0
#define BG_SCORE_AV_GRAVEYARDS_DEFENDED		1
#define BG_SCORE_AV_TOWERS_ASSAULTED		2
#define BG_SCORE_AV_TOWERS_DEFENDED			3
#define BG_SCORE_AV_MINES_CAPTURES			4
#define BG_SCORE_EOTS_FLAG_CAPTURES			0

#define SOUND_BATTLEGROUND_BEGIN			0xD6F
#define SOUND_HORDE_SCORES					8213
#define SOUND_ALLIANCE_SCORES				8173
#define SOUND_ALLIANCE_CAPTURE				8174
#define SOUND_HORDE_CAPTURE					8212
#define SOUND_ALLIANCE_RETURNED				8192
#define SOUND_HORDE_RETURNED				8192	// huh?
#define SOUND_HORDEWINS						8454
#define SOUND_ALLIANCEWINS					8455
#define SOUND_HORDE_BGALMOSTEND				0x2108
#define SOUND_ALLIANCE_BGALMOSTEND			0x2109

#define RESURRECT_SPELL						21074   // Spirit Healer Res
#define BG_DESERTER							26013
#define BG_RECENTLY_DROPPED_FLAG			42792
#define BG_PREPARATION						44521
#define BG_REVIVE_PREPARATION				44535

// AV define's
#define AV_UNCONTROLED_SNOWFALL_GRAVE				0x7AE // 1 -> show uncontrolled

#define AV_CONTROLED_ICEBLOOD_TOWER_HORDE			0x569 // 1 -> horde controled
#define AV_CONTROLED_TOWER_POINT_HORDE				0x568 // 1 -> horde controled
#define AV_CONTROLED_FROSTWOLF_RELIFHUNT_HORDE		0x532 // 1 -> horde controled
#define AV_CONTROLED_EAST_FROSTWOLF_TOWER_HORDE		0x567 // 1 -> horde controled
#define AV_CONTROLED_WEST_FROSTWOLF_TOWER_HORDE		0x566 // 1 -> horde controled
#define AV_CONTROLED_ICEBLOOD_GRAVE_HORDE			0x543 // 1 -> horde controled
#define AV_CONTROLED_FROSTWOLF_GRAVE_HORDE			0x53A // 1 -> horde controled

#define AV_CONTROLED_IRONDEEP_MINE_TROGG			0x550 // 1 -> trogg controled
#define AV_CONTROLED_COLDTHOOT_MINE_KOBOLT			0x54D // 1 -> kobolt controled

#define AV_CONTROLED_STORMPIKE_GRAVE_ALLIANCE		0x535 // 1 -> alliance controled
#define AV_CONTROLED_STONEHEART_BUNKER_ALLIANCE		0x554 // 1 -> alliance controled
#define AV_CONTROLED_ICEWING_BUNKER_ALLIANCE		0x553 // 1 -> alliance controled
#define AV_CONTROLED_DUBALDER_NORTH_BUNKER_ALLIANCE	0x552 // 1 -> alliance controled
#define AV_CONTROLED_DUBALDER_SOUTH_BUNKER_ALLIANCE	0x551 // 1 -> alliance controled
#define AV_CONTROLED_STORMPIKE_AID_STATION_ALLIANCE	0x52D // 1 -> alliance controled
#define AV_CONTROLED_STONEHEART_GRAVE_ALLIANCE		0x516 // 1 -> alliance controled

static inline uint32 GetLevelGrouping(uint32 level)
{
	if(level < 10)
		return 0;
	else if(level < 20)
		return 1;
	else if(level < 30)
		return 2;
	else if(level < 40)
		return 3;
	else if(level < 50)
		return 4;
	else if(level < 60)
		return 5;
	else if(level < 70)
		return 6;
	else if(level < 80)
		return 7;
	else
		return 8;
}
#define MAX_LEVEL_GROUP 9
#define LEVEL_GROUP_RATED_ARENA 8
#define BG_ANTI_CHEAT 1

class SERVER_DECL CBattlegroundManager : public Singleton<CBattlegroundManager>, public EventableObject, public std::tr1::enable_shared_from_this<CBattlegroundManager>
{
	/* Battleground Instance Map */
	map<uint32, BattlegroundPointer > m_instances[BATTLEGROUND_NUM_TYPES];
	Mutex m_instanceLock;

	/* Max Id */
	uint32 m_maxBattlegroundId;
	
	/* Queue System */
	// Instance Id -> list<Player guid> [ BattlegroundType ] (instance 0 - first available)
	list<uint32> m_queuedPlayers[BATTLEGROUND_NUM_TYPES][MAX_LEVEL_GROUP];

	// Instance Id -> list<Group id> [BattlegroundType][LevelGroup]
	list<uint32> m_queuedGroups[BATTLEGROUND_NUM_TYPES];

	// Last 10 players average wait time
	uint32 m_averageQueueTimes[BATTLEGROUND_NUM_TYPES][10];

	Mutex m_queueLock;

public:
	CBattlegroundManager();
	~CBattlegroundManager();

	//����������� � ���������� ��� ������������ ����� � ��������
	void *operator new(size_t);
	void operator delete(void*);

	void Init();

	/* Packet Handlers */
	void HandleBattlegroundListPacket(WorldSession * m_session, uint32 BattlegroundType, bool battlemaster = true);
	void HandleArenaJoin(WorldSession * m_session, uint32 BattlegroundType, uint8 as_group, uint8 rated_match);

	/* Player Logout Handler */
	void OnPlayerLogout(PlayerPointer plr);

	/* Handler On Update Event */
	void EventQueueUpdate(bool forceStart);

	/* Handle Battleground Join */
	void HandleBattlegroundJoin(WorldSession * m_session, WorldPacket & pck);

	/* Remove Player From All Queues */
	void RemovePlayerFromQueues(PlayerPointer plr);
	void RemoveGroupFromQueues(Group * grp);

	/* Create a battleground instance of type x */
	BattlegroundPointer CreateInstance(uint32 Type, uint32 LevelGroup);

	/* Can we create a new instance of type x level group y? (NO LOCK!) */
	bool CanCreateInstance(uint32 Type, uint32 LevelGroup);

	/* Deletes a battleground (called from MapMgr) */
	void DeleteBattleground(BattlegroundPointer bg);

	/* Build SMSG_BATTLEFIELD_STATUS */
	//void SendBattlefieldStatus(PlayerPointer plr, uint32 Status, uint32 Type, uint32 InstanceID, uint32 Time, uint32 MapId, uint8 RatedMatch);

	/* Gets ArenaTeam info from group */
	uint32 GetArenaGroupQInfo(Group * group, int type, uint32 *avgRating);

	/* Creates an arena with groups group1 and group2 */
	int CreateArenaType(int type, Group * group1, Group * group2);

	/* Add player to bg team */
	void AddPlayerToBgTeam(BattlegroundPointer bg, deque<PlayerPointer  > *playerVec, uint32 i, uint32 j, int Team);

	/* Add player to bg */
	void AddPlayerToBg(BattlegroundPointer bg, deque<PlayerPointer  > *playerVec, uint32 i, uint32 j);

	/* Add a group to an arena */
	void AddGroupToArena(BattlegroundPointer bg, Group * group, int nteam);

	void SendBattlegroundQueueStatus(PlayerPointer plr, uint32 queueSlot);

	/* Gets the average queue time (from last 10 players) */
	uint32 GetAverageQueueTime(uint32 BgType);

	/* Adds a new queueTime for average calculation */
	void AddAverageQueueTime(uint32 BgType, uint32 queueTime);
};

class CBattleground : public EventableObject, public std::tr1::enable_shared_from_this<CBattleground>
{
protected:
	/* Groups */
	Group * m_groups[2];

	time_t m_nextPvPUpdateTime;
	MapMgrPointer m_mapMgr;
	uint32 m_id;
	uint32 m_type;
	uint32 m_levelGroup;
	int32 m_deltaRating[2];

	uint32 startTime;

public:
	// for av node usage
	friend class AVNode;

	/* Team->Player Map */
	set<PlayerPointer  > m_players[2];
	void Lock() { m_mainLock.Acquire(); }
	void Unlock() { m_mainLock.Release(); }
	ARCTIC_INLINE bool IsArena() { return (m_type >= BATTLEGROUND_ARENA_2V2 && m_type <= BATTLEGROUND_ARENA_5V5); }

protected:
	/* PvP Log Data Map */
	map<uint32, BGScore> m_pvpData;

	/* Lock for all player data */
	Mutex m_mainLock;

	/* Player count per team */
	uint32 m_playerCountPerTeam;

	/* "pending" players */
	set<uint32> m_pendPlayers[2];

	/* starting time */
	uint32 m_startTime;
	bool m_started;
	bool m_shadowsightspawned;

	/* countdown stuff */
	uint32 m_countdownStage;

	/* winner stuff */
	bool m_ended;
	uint8 m_losingteam;

	/* resurrect queue */
	map<CreaturePointer, set<uint32> > m_resurrectMap;
	uint32 m_lastResurrect;

	bool m_isWeekend;

public:

	void SendChatMessage(uint32 Type, uint64 Guid, const char * Format, ...);

	/* Hook Functions */
	virtual void HookOnPlayerDeath(PlayerPointer plr) = 0;

	/* Repopping - different battlegrounds have different ways of handling this */
	virtual bool HookHandleRepop(PlayerPointer plr) = 0;

	/* In CTF battlegrounds mounting will cause you to lose your flag. */
	virtual void HookOnMount(PlayerPointer plr) = 0;

	/* Only used in CTF (as far as I know) */
	virtual void HookFlagDrop(PlayerPointer plr, GameObjectPointer obj) = 0;
	virtual void HookFlagStand(PlayerPointer plr, GameObjectPointer obj) = 0;

	/* Used when a player kills a unit/PlayerPointer */
	virtual void HookOnPlayerKill(PlayerPointer plr, UnitPointer pVictim) = 0;
	virtual void HookOnHK(PlayerPointer plr) = 0;

	/* On Area Trigger */
	virtual void HookOnAreaTrigger(PlayerPointer plr, uint32 id) = 0;

	/* On Shadow Sight */
	virtual void HookOnShadowSight() = 0;

	/* Used to generate loot for players (AV) */
	virtual void HookGenerateLoot(PlayerPointer plr, CorpsePointer pCorpse) = 0;
	virtual bool SupportsPlayerLoot() = 0;

	/* Retreival Functions */
	ARCTIC_INLINE uint32 GetId() { return m_id; }
	ARCTIC_INLINE uint32 GetLevelGroup() { return m_levelGroup; }
	ARCTIC_INLINE MapMgrPointer GetMapMgr() { return m_mapMgr; }

	/* Creating a battleground requires a pre-existing map manager */
	CBattleground( MapMgrPointer mgr, uint32 id, uint32 levelgroup, uint32 type);
	virtual ~CBattleground();
	virtual void Init();

	/* Has it ended? */
	ARCTIC_INLINE bool HasEnded() { return m_ended; }
	ARCTIC_INLINE bool HasStarted() { return m_started; }

	/* Send the pvp log data of all players to this player. */
	void SendPVPData(PlayerPointer plr);

	/* Get the starting position for this team. */
	virtual LocationVector GetStartingCoords(uint32 Team) = 0;

	/* Send a packet to the entire battleground */
	void DistributePacketToAll(WorldPacket * packet);

	/* send a packet to only this team */
	void DistributePacketToTeam(WorldPacket * packet, uint32 Team);

	/* play sound to this team only */
	void PlaySoundToTeam(uint32 Team, uint32 Sound);

	/* play sound to all */
	void PlaySoundToAll(uint32 Sound);

	/* Full? */
	ARCTIC_INLINE bool IsFull() { return !(HasFreeSlots(0) || HasFreeSlots(1)); }

	/* Are we full? */
	bool HasFreeSlots(uint32 Team)
	{
		m_mainLock.Acquire();
		bool res = ((m_players[Team].size() + m_pendPlayers[Team].size()) < m_playerCountPerTeam);
		m_mainLock.Release();
		return res;
	}

	/* Add PlayerPointer */
	void AddPlayer(PlayerPointer plr, uint32 team);
	virtual void OnAddPlayer(PlayerPointer plr) = 0;

	/* Remove PlayerPointer */
	void RemovePlayer(PlayerPointer plr, bool logout);
	virtual void OnRemovePlayer(PlayerPointer plr) = 0;

	/* Port PlayerPointer */
	void PortPlayer(PlayerPointer plr, bool skip_teleport = false);
	virtual void OnCreate() = 0;

	/* Remove pending PlayerPointer */
	void RemovePendingPlayer(PlayerPointer plr);

	/* Gets the number of free slots */
	uint32 GetFreeSlots(uint32 t)
	{
		m_mainLock.Acquire();
		size_t s = m_playerCountPerTeam - m_players[t].size() - m_pendPlayers[t].size();
		m_mainLock.Release();
		return (uint32)s;
	}

	GameObjectPointer SpawnGameObject(uint32 entry,float x, float y, float z, float o, uint32 flags, uint32 faction, float scale);
	CreaturePointer SpawnCreature(uint32 entry,float x, float y, float z, float o);
	void UpdatePvPData();

	ARCTIC_INLINE uint32 GetStartTime() { return m_startTime; }
	ARCTIC_INLINE uint32 GetType() { return m_type; }

	// events should execute in the correct context
	int32 event_GetInstanceID();
	void EventCreate();

	virtual const char * GetName() = 0;
	void EventCountdown();

	virtual void Start();
	virtual void OnStart() {}
	void Close();
	virtual void OnClose() {}

	CreaturePointer SpawnSpiritGuide(float x, float y, float z, float o, uint32 horde);

	ARCTIC_INLINE uint32 GetLastResurrect() { return m_lastResurrect; }
	void AddSpiritGuide(CreaturePointer pCreature);
	void RemoveSpiritGuide(CreaturePointer pCreature);
	void QueuePlayerForResurrect(PlayerPointer plr, CreaturePointer spirit_healer);
	void RemovePlayerFromResurrect(PlayerPointer plr, CreaturePointer spirit_healer);
	void EventResurrectPlayers();
	virtual bool CanPlayerJoin(PlayerPointer plr);
	virtual bool CreateCorpse(PlayerPointer plr) { return true; }
	virtual bool HookSlowLockOpen(GameObjectPointer pGo, PlayerPointer pPlayer, SpellPointer pSpell);

	void BuildPvPUpdateDataPacket(WorldPacket * data);
	virtual uint8 Rated() { return 0; }
	void OnPlayerPushed(PlayerPointer plr);
	void QueueAtNearestSpiritGuide(PlayerPointer plr, CreaturePointer old);
	void GiveHonorToTeam(uint32 team, uint32 amt);

	virtual void SetIsWeekend(bool isweekend) {}
};

#define BattlegroundManager CBattlegroundManager::getSingleton( )

	
#endif
