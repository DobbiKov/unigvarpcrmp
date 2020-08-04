public OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID)
    {
        if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember])
        {
            if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[killerid][pMember] > 0)
            {
                new string[144];
                format(string, sizeof(string), "{"cgrey"}[{"cred"}TeamKill{"cgrey"}] %s %s[%d] убил %s %s[%d] (%s | %s)", PlayerRank[ PlayerInfo[killerid][pMember] ][ PlayerInfo[killerid][pRang] ], PlayerInfo[killerid][pName], killerid, PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, GetMember[ PlayerInfo[killerid][pMember] ], gun_name[reason]);
                SCMA(grey, string);
            }
        }
    }
    #if defined teamkill__OnPlayerDeath
        return teamkill__OnPlayerDeath(playerid, killerid, reason);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerDeath
	#undef	OnPlayerDeath
#else
	#define	_ALS_OnPlayerDeath
#endif

#define	OnPlayerDeath teamkill__OnPlayerDeath
#if	defined	teamkill__OnPlayerDeath
	forward teamkill__OnPlayerDeath(playerid, killerid, reason); 
#endif