public OnPlayerDisconnect(playerid, reason)
{
    if(GetPVarInt(playerid, "cuffed") > 0)
    {
        PlayerInfo[playerid][pJail] = (PlayerInfo[playerid][pWANTED]*10*60)+(30*60);
        PlayerInfo[playerid][pWANTED] = 0;
        SaveAccounts(playerid);
        new string[144];
        format(string, sizeof(string), "{ff0033}%s[%d] вышел при аресте (+30 минут)", PlayerInfo[playerid][pName], playerid);
        SCMTA(red, string);
    }
    #if defined disc_cuffed__OnPlayerDisconnect
        return disc_cuffed__OnPlayerDisconnect(playerid, reason);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else   
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect disc_cuffed__OnPlayerDisconnect
#if defined disc_cuffed__OnPlayerDisconnect
    forward disc_cuffed__OnPlayerDisconnect(playerid, reason);
#endif