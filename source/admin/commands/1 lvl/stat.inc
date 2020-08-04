CMD:stat(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /stat [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	return stats_player(playerid, to_player);
}