CMD:fly(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
    new mode;
    if(IsPlayerFlying(playerid))
    {
        mode = 0;
        SCM(playerid, white, "Вы вышли из режима полёта!");
        SetPVarInt(playerid, "exit_fly_mode", 1);
    }
    else if(!IsPlayerFlying(playerid))
    {
        mode = 1;
        SCM(playerid, white, "Вы вошли в режим полёта!");
    }
    return SetPlayerFlyStatus(playerid, mode);
}

public OnPlayerSpawn(playerid)
{
    if(GetPVarInt(playerid, "exit_fly_mode") == 1)
    {
        if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
        else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
    }
    #if defined cmd_fly__OnPlayerSpawn
        return cmd_fly__OnPlayerSpawn(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn cmd_fly__OnPlayerSpawn
#if defined cmd_fly__OnPlayerSpawn
    forward cmd_fly__OnPlayerSpawn(playerid);
#endif