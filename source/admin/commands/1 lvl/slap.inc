CMD:slap(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: Используйте /slap [playerid]");
	if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
	if(PlayerInfo[to_player][bAdmin] > PlayerInfo[playerid][bAdmin]) return 1;

	return Slap(playerid, to_player);
}