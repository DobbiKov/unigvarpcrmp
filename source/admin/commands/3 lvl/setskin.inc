CMD:setskin(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

    extract params -> new to_player, skin; else return SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /setskin [id игрока] [ID скина]");

    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

    SetPlayerSkin(to_player, skin);

    new string[128];
    format(string, sizeof(string), "[A] %s[%d] поставил временный скин(%d) игроку %s[%d]", PlayerInfo[playerid][pName], playerid, skin, PlayerInfo[to_player][pName], to_player);
    SCMA(grey, string);

    format(string, sizeof(string), "Администратор %s изменил ваш скин", PlayerInfo[playerid][pName]);
    SCM(to_player, white, string);
    return 1;
}