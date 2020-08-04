ALTX:spawnplayer("/spa");
CMD:spawnplayer(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте: /spawnplayer [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);

    new string[144];
    format(string, sizeof(string), "[A] %s[%d] предложил заспавниться %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
    SCMA(grey, string);

    format(string, sizeof(string), "Администратор %s предложил вам заспавниться", PlayerInfo[playerid][pName]);
    SCM(to_player, white, string);

    return SpawnList(to_player);
}
