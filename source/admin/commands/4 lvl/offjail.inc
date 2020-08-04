CMD:offjail(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], time, string: reason[30]; else return SCM(playerid, blue, "[Подсказка] {ffffff}Введите: /offjail [Ник игрока] [Минуты] [Причина]");

	if(!(1 <= time <= 280))
	    return SCM(playerid, red, "Время от 1 до 280 минут");

 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 			return SCM(playerid, white, !"Игрок онлайн. Используйте /jail");
 	}


	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "on_player_offjail","isis", playerid, to_player, time, reason);
}

publics on_player_offjail(playerid, to_player[], time, reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin, jail;
 	    jail = cache_get_field_content_int(0, "pJail");
		admin = cache_get_field_content_int(0, "bAdmin");
		if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы пытаетесь посадить администратора.");

    	if(jail > 0) return SCM(playerid, red, "Игрок уже сидит в деморгане.");

    	PlayerInfo[playerid][bOffJail]++;
    	SaveAccounts(playerid);

		new string[256], sql_str[256];
		format(string, sizeof(string), "[A] Администратор %s посадил игрока %s в деморган оффлайн на %d минут. Причина: %s", PlayerInfo[playerid][pName], to_player, time, reason);
		SCMA(lightblue, string);

		format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pJail` = '%d' WHERE `pName` = '%s' LIMIT 1", time*60, to_player);
		mysql_tquery(connects, sql_str, "", "");

		format(string, sizeof(string), "Администратор %s посадил вас оффлайн в деморган на %d минут. Прчина: %s", PlayerInfo[playerid][pName], time, reason);

		format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pJailOffMess` = '%s' WHERE `pName` = '%s'", string, to_player);
		mysql_tquery(connects, sql_str, "", "");


		new day, month, year, hour, minute, second;
		getdate(day, month, year);
		gettime(hour, minute, second);
		format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

		mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', '%s', 'offjail')", PlayerInfo[playerid][pName], to_player, string, time, reason);
		mysql_tquery(connects, sql_str, "", "");
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}

