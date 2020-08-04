CMD:unfreeze(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /unfreeze [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	new string[256];
	format(string, sizeof(string), "[A] %s[%d] разморозил игрока %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, string);

	format(string, sizeof(string), "Администратор %s[%d] разморозил вас!", PlayerInfo[playerid][pName], playerid);
	SCM(to_player, white, string);
	TogglePlayerControllable(to_player, 1);
	return 1;
}
