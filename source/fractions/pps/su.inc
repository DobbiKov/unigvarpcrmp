CMD:su(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMember] == TEAM_PPS && PlayerInfo[playerid][pRang] < 2) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, string: reason[144]; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /su [ID игрока] [причина]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pMember] == TEAM_PPS || PlayerInfo[to_player][pMember] == TEAM_FSB) return SCM(playerid, red, "Этот гражданин являеться полицейским!");
    if(PlayerInfo[to_player][pWANTED] >= 6) return SCM(playerid, red, "У данного гражданина максимальный уровень розыска!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");

    PlayerInfo[to_player][pWANTED]++;

    new string[144];
    format(string, sizeof(string), "%s %s[%d] объявил в розыск(%d) %s[%d]. Причина: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pWANTED], PlayerInfo[to_player][pName], to_player, reason);
    SCMPolice(blue, string);

    format(string, sizeof(string), "%s %s объявил вас в розыск. Причина: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], reason);
    SCM(to_player, blue, string);

    format(string, sizeof(string), "Теперь ваш уровень розыска: %d", PlayerInfo[to_player][pWANTED]);
    SCM(to_player, blue, string);

    SaveAccounts(to_player);
    return SetPlayerWantedLevel(to_player, PlayerInfo[to_player][pWANTED]);
}