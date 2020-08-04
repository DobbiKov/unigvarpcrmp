CMD:clear(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMember] == TEAM_PPS && PlayerInfo[playerid][pRang] < 7) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /clear [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pWANTED] <= 0) return SCM(playerid, red, "Данный игрок не в розыске!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");

    PlayerInfo[to_player][pWANTED]--;

    new string[144];
    format(string, sizeof(string), "%s %s[%d] снял 1 уровень розыска(%d) у %s[%d].", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pWANTED], PlayerInfo[to_player][pName], to_player);
    SCMPolice(blue, string);

    format(string, sizeof(string), "%s %s[%d] снял с вас 1 уровень розыска", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid);
    SCM(to_player, blue, string);

    format(string, sizeof(string), "Теперь ваш уровень розыска: %d", PlayerInfo[to_player][pWANTED]);
    SCM(to_player, blue, string);
    return SetPlayerWantedLevel(to_player, PlayerInfo[to_player][pWANTED]);
}