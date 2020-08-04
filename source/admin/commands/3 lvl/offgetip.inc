CMD:offgetip(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new string: to_player[24]; else return SCM(playerid, yellow, "[Подсказка] {FFFFFF}Используйте: /offgetip [NICK игрока]");

	foreach(new i : Player)
	{
	    if(!strcmp(PlayerInfo[i][pName], to_player, true)) return SCM(playerid, blue, "Игрок онлайн, используйте /getip");
	}

	new string[256];
	format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pName` = '%s'", to_player);
	mysql_tquery(connects, string, "off_getip", "is", playerid, to_player);
	return 1;
}
publics off_getip(playerid, to_player[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new lastip[16], regip[16], admin;
		cache_get_field_content(0, "pLastIP", lastip, connects, 16);
		cache_get_field_content(0, "pRegIP", regip, connects, 16);
		admin = cache_get_field_content_int(0, "bAdmin");

		if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы не моежете посмотреть IP у Администратора!");
		
		new string[256];
		format(string, sizeof(string), "[Player - %s] [IP: %s] [REG IP: %s]", to_player, lastip, regip);
		SCM(playerid, blue, string);
	}
	else
	{
	    return SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}