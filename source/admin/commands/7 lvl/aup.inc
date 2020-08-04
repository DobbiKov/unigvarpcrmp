CMD:aup(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24]; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /aup [Ник игрока]");

 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 		{
 		    if(PlayerInfo[i][bAdmin] == 0) return SCM(playerid, red, "Данный игрок не администратор.");
 		    if(PlayerInfo[playerid][bAdmin] == 6)
 		    {
 		        if(PlayerInfo[i][bAdmin] >= 5) return SCM(playerid, red, "Уровень Администратора данного игрока равен 5, или более.");
 		    }
 		    if(PlayerInfo[i][bAdmin] >= 7) return SCM(playerid, red, "Уровень Администратора данного игрока равен 7, или более.");
	 		PlayerInfo[i][bAdmin]++;

			new string[256];
			format(string, sizeof(string), "[A]: %s[%d] повысил уровень администратора игрока %s[%d] до %d", PlayerInfo[playerid][pName], playerid, PlayerInfo[i][pName], i, PlayerInfo[i][bAdmin]);
			SCMA(grey, string);
			SaveAccounts(playerid);
			return SaveAccounts(i);
		}
 	}


	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "off_aup","is", playerid, to_player);
}

publics off_aup(playerid, to_player[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin;
	    admin = cache_get_field_content_int(0, "bAdmin");
	    if(admin > PlayerInfo[playerid][bAdmin] || admin > 5) return SCM(playerid, red, "Данный игрок уже администратор.");

	    admin++;

	    new string[256], sql_str[128];
	    format(string, sizeof(string), "[A]: %s[%d] повысил игроку %s уровень администратора до %d", PlayerInfo[playerid][pName], playerid, to_player, admin);
	    SCMA(grey, string);

	    format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `bAdmin` = '%d' WHERE `pName` = '%s' LIMIT 1", admin, to_player);
	    mysql_tquery(connects, sql_str, "", "");
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}