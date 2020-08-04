CMD:unmwarn(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == TEAM_NONE || PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /unmwarn [ID игрока] [причина]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pMember] != PlayerInfo[playerid][pMember]) return SCM(playerid, red, "Игрок не состоит в вашей организации!");
    if(PlayerInfo[to_player][pRang] > PlayerInfo[playerid][pRang]) return SCM(playerid, red, "Игрок выше вас по рангу!");
    if(PlayerInfo[to_player][pWarnF] <= 0) return SCM(playerid, red, "У игрока нет выговоров!");

    PlayerInfo[to_player][pWarnF]--;

    new string[128];
    format(string, sizeof(string), "Вы сняли 1 выговор у %s [%d|3].", PlayerInfo[to_player][pName], PlayerInfo[to_player][pWarnF]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s снял у вас 1 выговор [%d|3].", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], PlayerInfo[to_player][pWarnF]);
    SCM(playerid, blue, string);
    return 1;
}