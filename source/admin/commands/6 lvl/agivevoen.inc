CMD:agivevoen(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /agivevoen [ID игрока]");
    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

    new string[144];
    format(string, sizeof(string), "[A] %s[%d] выдал военный билет %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
    SCMA(grey, string);

    format(string, sizeof(string), "Вы выдали военный билет игроку %s", PlayerInfo[to_player][pName]);
    SCM(playerid, white, string);

    format(string, sizeof(string), "Администратор %s выдал вам военный билет.", PlayerInfo[playerid][pName]);
    SCM(to_player, white, string);

    return PlayerInfo[to_player][pVoen] = 1;
}