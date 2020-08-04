CMD:setadmin(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], level; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /setadmin [Ник игрока] [LVL Админки]");

	if(PlayerInfo[playerid][bAdmin] == 6)
	{
		if(level < 0 || level > 5)
		    return SCM(playerid, red, "Уровень администратора не больше 5 и не меньше 0!");
	}
	if(level < 0 || level > 7) return SCM(playerid, red, "Уровень администратора не больше 7 и не меньше 0!");

 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 		{
	 		PlayerInfo[i][bAdmin] = level;

			new string[256];
			format(string, sizeof(string), "[A]: %s[%d] установил игроку %s[%d] %d уровень админки", PlayerInfo[playerid][pName], playerid, PlayerInfo[i][pName], i, level);
			SCMA(grey, string);
			SaveAccounts(playerid);
			return SaveAccounts(i);
		}
 	}
	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "off_set_admin", "isi", playerid, to_player, level);
}

publics off_set_admin(playerid, to_player[], level)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin;
	    admin = cache_get_field_content_int(0, "bAdmin");
	    if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Данный игрок уже администратор.");

	    new string[256], sql_str[128];
	    format(string, sizeof(string), "[A]: %s[%d] установил игроку %s %d уровень администратора", PlayerInfo[playerid][pName], playerid, to_player, level);
	    SCMA(grey, string);

	    format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `bAdmin` = '%d' WHERE `pName` = '%s' LIMIT 1", level, to_player);
	    mysql_tquery(connects, sql_str, "", "");
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}