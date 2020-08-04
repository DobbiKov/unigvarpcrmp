CMD:stopcar(playerid)
{
    if(PlayerInfo[playerid][pMember] != TEAM_PPS) return YouCannotUseThisFunc(playerid);
    if(GetPVarInt(playerid, "zhezl") != 1) return SCM(playerid, red, "У вас нет жезла!");

    if(GetPVarInt(playerid, "status_zhezl") != 1)
    {
        ApplyAnimation(playerid, "PED", "Driveby_R", 4.1, 0, 1, 1, 1, 1, 1);
        SetPVarInt(playerid, "status_zhezl", 1);
    }
    else if(GetPVarInt(playerid, "status_zhezl") == 1)
    {
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "status_zhezl", 0);
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
    #if defined pps_OnPlayerDisconnect
        return pps_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect pps_OnPlayerDisconnect
#if defined pps_OnPlayerDisconnect
    forward pps_OnPlayerDisconnect(playerid, reason);
#endif