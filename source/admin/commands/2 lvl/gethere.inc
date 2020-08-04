ALTX:gethere("/gh");
CMD:gethere(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: Введите /gethere [id игрока]");

    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

    new Float:px, Float:py, Float:pz, string[120+MAX_PLAYER_NAME*2], vw, int;
    GetPlayerPos(playerid, px, py, pz);
    vw = GetPlayerVirtualWorld(playerid);
    int = GetPlayerInterior(playerid);
    SetPlayerPos(to_player, px, py, pz);
    SetPlayerVirtualWorld(to_player, vw);
    SetPlayerInterior(to_player, int);

    format(string, sizeof(string), "{"cgrey"}[A] %s[%d] телепортировал к себе игрока %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
    SCMA(grey, string);

    format(string, sizeof(string), "{FFFFFF}Администратор %s телепортировал вас к себе", PlayerInfo[playerid][pName]);
	SCM(to_player, grey, string);
	return 1;
}