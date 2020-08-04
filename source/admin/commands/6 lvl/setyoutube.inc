CMD:setyoutube(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], level; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /setyoutube [Ник игрока] [0 - снять | 1 - поставить]");
	
	if(level != 1 && level != 0) return SCM(playerid, red, "Только 0, или 1!");

 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 		{
	 		PlayerInfo[i][bYoutube] = level;

			new string[256];
			format(string, sizeof(string), "[A]: %s[%d] установил игроку %s[%d] %d уровень ютуберки", PlayerInfo[playerid][pName], playerid, PlayerInfo[i][pName], i, level);
			SCMA(grey, string);
			SaveAccounts(playerid);
			return SaveAccounts(i);
		}
 	}
	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "off_set_youtube", "isi", playerid, to_player, level);
}

publics off_set_youtube(playerid, to_player[], level)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new string[256], sql_str[128];
	    format(string, sizeof(string), "[A]: %s[%d] установил игроку %s %d уровень ютуберки", PlayerInfo[playerid][pName], playerid, to_player, level);
	    SCMA(grey, string);

	    format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `bYoutube` = '%d' WHERE `pName` = '%s' LIMIT 1", level, to_player);
	    mysql_tquery(connects, sql_str, "", "");
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}