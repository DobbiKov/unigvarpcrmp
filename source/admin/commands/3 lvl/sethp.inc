CMD:sethp(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new to_player, health; else return SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /sethp [id игрока] [health]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	new string[120+MAX_PLAYER_NAME*2];


	format(string, sizeof(string), "{"cgrey"}[A] %s[%d] установил %d хп игроку %s[%d]", PlayerInfo[playerid][pName], playerid, health, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, string);
	
 	format(string, sizeof(string), "{"cwhite"}Администратор %s изменил ваше здоровье.", PlayerInfo[playerid][pName]);
 	SCM(to_player, grey, string);

	PlayerInfo[to_player][pHP] = health;
	return SetPlayerHealth(to_player, health);
}