ALTX:bh("/bunnyhop");
CMD:bh(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /bh [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	PlayerInfo[playerid][pHP] = 0.0;
	SetPlayerHealth(to_player, 0.0);
	SaveAccounts(to_player);
	SaveAccounts(playerid);

	new fmt_query[256];

	format(fmt_query, sizeof fmt_query, "Администратор %s наказал игрока %s. Причина: BH( BunnyHop )", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName]);
	SCMTA(0xFF4530FF, fmt_query);

	format(fmt_query, sizeof fmt_query, "[A] %s[%d] наказал игрока %s[%d](BunnyHop)", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, fmt_query);

	SPD(to_player, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Наказание | BH", "{FFFFFF}Вы были наказаны за BunnyHop(частые прыжки). Постарайтесь больше не нарушать правила сервера!", "Закрыть", "");

	new string[256], sql_str[256];
	new day, month, year, hour, minute, second;
	getdate(day, month, year);
	gettime(hour, minute, second);
	format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

	mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '0', 'bh', 'sethp_0')", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], string);
	mysql_tquery(connects, sql_str, "", "");

	return 1;
}