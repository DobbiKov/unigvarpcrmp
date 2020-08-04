CMD:givemoney(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

	extract params -> new to_player, count; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /givemoney [ID игрока] [количество]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

 	GiveMoney(to_player, count, "/givemoney");

	SaveAccounts(playerid);
	SaveAccounts(to_player);

	new string[120+MAX_PLAYER_NAME*2];
	format(string, sizeof(string), "[A] %s[%d] выдал %s[%d] %d рублей", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, count);
	return SCMA(grey, string);
}