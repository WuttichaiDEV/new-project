#if defined _frobj_included
	#endinput
#endif
#define _frobj_included

static playerSupTimer[MAX_PLAYERS];
static playerSupObject0[MAX_PLAYERS];
static playerSupObject1[MAX_PLAYERS];

forward fr_DellObjTimer(playerid);
public fr_DellObjTimer(playerid)
{
	if(playerSupObject0[playerid]) DestroyPlayerObject(playerid, playerSupObject0[playerid]);
	playerSupTimer[playerid] = 0;
	playerSupObject0[playerid] = 0;
	return 1;
}

public OnGameModeExit()
{
	DestroyAllDynamicObjects();
	DestroyAllDynamicPickups();
	DestroyAllDynamicCPs();
	DestroyAllDynamicRaceCPs();
	DestroyAllDynamicMapIcons();
	DestroyAllDynamic3DTextLabels();
	DestroyAllDynamicAreas();
	#if defined fr_OnGameModeExit
		return fr_OnGameModeExit();
	#else
		return 1;
    #endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define	_ALS_OnGameModeExit
#endif
#define OnGameModeExit fr_OnGameModeExit
#if defined fr_OnGameModeExit
	forward fr_OnGameModeExit();
#endif

public OnPlayerConnect(playerid)
{
    playerSupTimer[playerid] =
 	playerSupObject0[playerid] =
 	playerSupObject1[playerid] = 0;
	#if defined fr_OnPlayerConnect
		return fr_OnPlayerConnect(playerid);
	#else
		return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define	_ALS_OnPlayerConnect
#endif
#define OnPlayerConnect fr_OnPlayerConnect
#if defined fr_OnPlayerConnect
	forward fr_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(playerSupTimer[playerid]) KillTimer(playerSupTimer[playerid]);
    #if defined fr_OnPlayerDisconnect
    	return fr_OnPlayerDisconnect(playerid, reason);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#if defined fr_OnPlayerDisconnect
	forward fr_OnPlayerDisconnect(playerid, reason);
#endif
#define OnPlayerDisconnect fr_OnPlayerDisconnect

stock fr_SetSpawnInfo(playerid, team, skin, Float:pos_x, Float:pos_y, Float:pos_z, Float:pos_a, weap0, ammo0, weap1, ammo1, weap2, ammo2)
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(playerSupObject1[playerid]) DestroyPlayerObject(playerid, playerSupObject1[playerid]);
    playerSupObject1[playerid] = CreatePlayerObject(playerid, 19356, pos_x, pos_y, (pos_z - 1.09), 0.0, 90.0, 0.0);
	SetPlayerObjectMaterialText(playerid, playerSupObject1[playerid], " ", .fontcolor = 0xFFFFFF00);
    return SetSpawnInfo(playerid, team, skin, pos_x, pos_y, pos_z, pos_a, weap0, ammo0, weap1, ammo1, weap2, ammo2);
}
#if defined _ALS_SetSpawnInfo
	#undef SetSpawnInfo
#else
	#define	_ALS_SetSpawnInfo
#endif
#define SetSpawnInfo fr_SetSpawnInfo

stock fr_SetPlayerPos(playerid, Float:pos_x, Float:pos_y, Float:pos_z)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(playerSupObject0[playerid])
	{
	    KillTimer(playerSupTimer[playerid]);
		DestroyPlayerObject(playerid, playerSupObject0[playerid]);
	}
	playerSupTimer[playerid] = SetTimerEx("fr_DellObjTimer", 3000, 0, "i", playerid);
	playerSupObject0[playerid] = CreatePlayerObject(playerid, 19356, pos_x, pos_y, (pos_z - 1.09), 0.0, 90.0, 0.0);
	SetPlayerObjectMaterialText(playerid, playerSupObject0[playerid], " ", .fontcolor = 0xFFFFFF00);
 	return SetPlayerPos(playerid, pos_x, pos_y, pos_z);
}
#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define	_ALS_SetPlayerPos
#endif
#define SetPlayerPos fr_SetPlayerPos

stock fr_SetPlayerPosFindZ(playerid, Float:pos_x, Float:pos_y, Float:pos_z)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(playerSupObject0[playerid])
	{
	    KillTimer(playerSupTimer[playerid]);
		DestroyPlayerObject(playerid, playerSupObject0[playerid]);
	}
	playerSupTimer[playerid] = SetTimerEx("fr_DellObjTimer", 3000, 0, "i", playerid);
	playerSupObject0[playerid] = CreatePlayerObject(playerid, 19356, pos_x, pos_y, (pos_z - 1.09), 0.0, 90.0, 0.0);
	SetPlayerObjectMaterialText(playerid, playerSupObject0[playerid], " ", .fontcolor = 0xFFFFFF00);
 	return SetPlayerPosFindZ(playerid, pos_x, pos_y, pos_z);
}
#if defined _ALS_SetPlayerPosFindZ
	#undef SetPlayerPosFindZ
#else
	#define	_ALS_SetPlayerPosFindZ
#endif
#define SetPlayerPosFindZ fr_SetPlayerPosFindZ

public OnGameModeInit()
{
    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000);
    #if defined fr_OnGameModeInit
        return fr_OnGameModeInit();
	#else
	    return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#if defined fr_OnGameModeInit
    forward fr_OnGameModeInit();
#endif
#define OnGameModeInit fr_OnGameModeInit

public OnFilterScriptInit()
{
    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000);
    #if defined fr_OnFilterScriptInit
        return fr_OnFilterScriptInit();
    #else
	    return 1;
    #endif
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#if defined fr_OnFilterScriptInit
    forward fr_OnFilterScriptInit();
#endif
#define OnFilterScriptInit fr_OnFilterScriptInit
