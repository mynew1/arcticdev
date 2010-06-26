/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2010 Arctic Server Team
 * See COPYING for license details.
 */

#include "RStdAfx.h"

/* Table formats converted to strings */
const char * gAchievementRewardFormat					= "uuuu";
const char * gAreaTriggerFormat							= "ucuusffffuu";
const char * gCreatureNameFormat						= "usssuuuuuuuuuuuffcc";
const char * gCreatureProtoFormat						= "uuuuuuufuuuffuffuuuuuuuuuuuffsuuuufffuuic";
const char * gCreatureStatsHeroicFormat					= "uuuuuuuuuuuuuuusu";
const char * gFishingFormat								= "uuu";
const char * gGameObjectNameFormat						= "uuusfuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
const char * gGraveyardFormat							= "uffffuuuux";
const char * gItemPageFormat							= "usu";
const char * gItemPrototypeFormat						= "uuuussssuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuffuffuffuffuffuuuuuuuuuufuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuusuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
const char * gNpcTextFormat								= "ufssuuuuuuufssuuuuuuufssuuuuuuufssuuuuuuufssuuuuuuufssuuuuuuufssuuuuuuufssuuuuuuu";
const char * gQuestFormat								= "uuuuuuuuuuuuuuuuuuuussssssssssuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuc";
const char * gTeleportCoordFormat						= "uxuffff";
const char * gWorldMapInfoFormat                        = "uuuuuufffusuuuuuuufub";
const char * gProfessionDiscoveryFormat					= "uuuf";
const char * gRandomItemCreationFormat					= "uuuu";
const char * gRandomCardCreationFormat					= "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
const char * gScrollCreationFormat						= "uu";
const char * gZoneGuardsFormat							= "uuu";

/* SQLStorage symbols */
SQLStorage<ItemPrototype, ArrayStorageContainer<ItemPrototype> >				ItemPrototypeStorage;
SQLStorage<CreatureInfo, HashMapStorageContainer<CreatureInfo> >				CreatureNameStorage;
SQLStorage<GameObjectInfo, HashMapStorageContainer<GameObjectInfo> >			GameObjectNameStorage;
//SQLStorage<CreatureProto, HashMapStorageContainer<CreatureProto> >				CreatureProtoStorage;
//SQLStorage<AreaTrigger, HashMapStorageContainer<AreaTrigger> >					AreaTriggerStorage;
SQLStorage<ItemPage, HashMapStorageContainer<ItemPage> >						ItemPageStorage;
SQLStorage<Quest, HashMapStorageContainer<Quest> >								QuestStorage;
SQLStorage<GossipText, HashMapStorageContainer<GossipText> >					NpcTextStorage;
//SQLStorage<SpellExtraInfo, HashMapStorageContainer<SpellExtraInfo> >			SpellExtraStorage;
//SQLStorage<GraveyardTeleport, HashMapStorageContainer<GraveyardTeleport> >		GraveyardStorage;
//SQLStorage<TeleportCoords, HashMapStorageContainer<TeleportCoords> >			TeleportCoordStorage;
//SQLStorage<FishingZoneEntry, HashMapStorageContainer<FishingZoneEntry> >		FishingZoneStorage;
SQLStorage<MapInfo, HashMapStorageContainer<MapInfo> >							WorldMapInfoStorage;

void Storage_Load()
{
	ItemPrototypeStorage.Load("items", gItemPrototypeFormat);
	CreatureNameStorage.Load("creature_names", gCreatureNameFormat);
	GameObjectNameStorage.Load("gameobject_names", gGameObjectNameFormat);
	ItemPageStorage.Load("itempages", gItemPageFormat);
	QuestStorage.Load("quests", gQuestFormat);
	WorldMapInfoStorage.Load("worldmap_info", gWorldMapInfoFormat);
}

void Storage_Cleanup()
{
	ItemPrototypeStorage.Cleanup();
	CreatureNameStorage.Cleanup();
	GameObjectNameStorage.Cleanup();
	//CreatureProtoStorage.Cleanup();
	//AreaTriggerStorage.Cleanup();
	ItemPageStorage.Cleanup();
	QuestStorage.Cleanup();
	//SpellExtraStorage.Cleanup();
	//GraveyardStorage.Cleanup();
	//TeleportCoordStorage.Cleanup();
	//FishingZoneStorage.Cleanup();
	NpcTextStorage.Cleanup();
	WorldMapInfoStorage.Cleanup();
}

bool Storage_ReloadTable(const char * TableName)
{
	// bur: mah god this is ugly :P
	if(!stricmp(TableName, "items"))					// Items
		ItemPrototypeStorage.Reload();
/*	else if(!stricmp(TableName, "creature_proto"))		// Creature Proto
		CreatureProtoStorage.Reload();*/
	else if(!stricmp(TableName, "creature_names"))		// Creature Names
		CreatureNameStorage.Reload();
	else if(!stricmp(TableName, "gameobject_names"))	// GO Names
		GameObjectNameStorage.Reload();
/*	else if(!stricmp(TableName, "areatriggers"))		// Areatriggers
		AreaTriggerStorage.Reload();*/
	else if(!stricmp(TableName, "itempages"))			// Item Pages
		ItemPageStorage.Reload();
/*	else if(!stricmp(TableName, "spellextra"))			// Spell Extra Info
		SpellExtraStorage.Reload();*/
	else if(!stricmp(TableName, "quests"))				// Quests
		QuestStorage.Reload();
	else if(!stricmp(TableName, "npc_text"))			// NPC Text Storage
		NpcTextStorage.Reload();
/*	else if(!stricmp(TableName, "fishing"))				// Fishing Zones
		FishingZoneStorage.Reload();
	else if(!stricmp(TableName, "teleport_coords"))		// Teleport coords
		TeleportCoordStorage.Reload();
	else if(!stricmp(TableName, "graveyards"))			// Graveyards
		TeleportCoordStorage.Reload();*/
	else if(!stricmp(TableName, "worldmap_info"))		// WorldMapInfo
		WorldMapInfoStorage.Reload();
	else
		return false;
	return true;
}
