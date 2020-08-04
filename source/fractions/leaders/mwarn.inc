CMD:mwarn(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == TEAM_NONE) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMember] == TEAM_FSB && PlayerInfo[playerid][pRang] < 5) return YouCannotUseThisFunc(playerid);
    else if(PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, string: reason[128]; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /mwarn [ID игрока] [причина]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pMember] != PlayerInfo[playerid][pMember]) return SCM(playerid, red, "Игрок не состоит в вашей организации!");
    if(PlayerInfo[to_player][pRang] > PlayerInfo[playerid][pRang]) return SCM(playerid, red, "Игрок выше вас по рангу!");

    PlayerInfo[to_player][pWarnF]++;

    new string[128];
    format(string, sizeof(string), "Вы сделали выговор %s [%d|3]. Причина: %s", PlayerInfo[to_player][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s сделал вам выговор [%d|3]. Причина: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%d", to_player);

    if(PlayerInfo[to_player][pWarnF] >= 3) 
    {
        format(string, sizeof(string), "%s был уволен из вашей организации. Причина: 3 выговора", PlayerInfo[to_player][pName]);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "Вы были уволены из организации \"%s\". Причина: 3 выговора", GetMember[ PlayerInfo[to_player][pMember] ]);
        SCM(playerid, blue, string);

        PlayerInfo[to_player][pMember] = 0;
        PlayerInfo[to_player][pWarnF] = 0;
        PlayerInfo[to_player][pRang] = 0;
        PlayerInfo[to_player][pFSkin] = -1;
        SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
    }
    SaveAccounts(to_player);
    return 1;
}