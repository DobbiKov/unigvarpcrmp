CMD:info(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);
    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /info [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);

    new Float:arm;
    GetPlayerHealth(to_player, PlayerInfo[to_player][pHP]);
    GetPlayerArmour(to_player, arm);

    new string[256];
    format(string, sizeof(string), "{FFFFFF}Ник: {"cblue"}%s[%d]\n{FFFFFF}Количество HP: {"cblue"}%f\n{FFFFFF}Количество брони: {"cblue"}%f", PlayerInfo[to_player][pName], to_player, PlayerInfo[to_player][pHP], arm);
    SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Инвормация о игроке", string, "Закрыть", "");
    return 1;
}