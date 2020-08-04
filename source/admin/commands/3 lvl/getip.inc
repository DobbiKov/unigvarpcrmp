CMD:getip(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка] {FFFFFF}Используйте: /getip [ID игрока]");
	if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
	if(PlayerInfo[to_player][bAdmin] > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы не моежете посмотреть IP у Администратора!");
	new string[256];
	format(string, sizeof(string), "[Player - %s[%d]] [IP: %s] [REG IP: %s]", PlayerInfo[to_player][pName], to_player, PlayerInfo[to_player][pNewIp], PlayerInfo[to_player][pRegIP]);
	SCM(playerid, blue, string);
	return 1;
}