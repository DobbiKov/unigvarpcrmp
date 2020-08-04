CMD:close(playerid)
{
    if(!IsAOpg(playerid) || PlayerInfo[playerid][pRang] < 10) return YouCannotUseThisFunc(playerid);

    if(PlayerInfo[playerid][pMember] == TEAM_OREX)
    {
        switch(OPG_O_STATUS)
        {
            case 0:
            {
                new string[144];
                format(string, sizeof(string), "[R] %s %s[%d] открыл склад", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                SCMR(PlayerInfo[playerid][pMember], green, string);
                OPG_O_STATUS = 1;
            }
            case 1:
            {
                new string[144];
                format(string, sizeof(string), "[R] %s %s[%d] закрыл склад", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                SCMR(PlayerInfo[playerid][pMember], green, string);
                OPG_O_STATUS = 0;
            }
        }
    }
    else if(PlayerInfo[playerid][pMember] == TEAM_SUN)
    {
        switch(OPG_S_STATUS)
        {
            case 0:
            {
                new string[144];
                format(string, sizeof(string), "[R] %s %s[%d] открыл склад", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                SCMR(PlayerInfo[playerid][pMember], green, string);
                OPG_S_STATUS = 1;
            }
            case 1:
            {
                new string[144];
                format(string, sizeof(string), "[R] %s %s[%d] закрыл склад", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                SCMR(PlayerInfo[playerid][pMember], green, string);
                OPG_S_STATUS = 0;
            }
        }
    }
    return SaveRepository();
}