CMD:jetpack(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /jetpack [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	return SetPlayerSpecialAction(to_player, SPECIAL_ACTION_USEJETPACK);
}