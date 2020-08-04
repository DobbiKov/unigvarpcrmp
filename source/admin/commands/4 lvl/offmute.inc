CMD:offmute(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], time, string: reason[30]; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /offmute [Ник игрока] [Минуты] [Причина]");

	if(!(1 <= time <= 280))
	    return SCM(playerid, red, "Время от 1 до 280 минут");

 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 			return SCM(playerid, white, !"Игрок онлайн. Используйте /mute");
 	}


	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "on_player_offmute","isis", playerid, to_player, time, reason);
}

publics on_player_offmute(playerid, to_player[], time, reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin, mute;
 	    mute = cache_get_field_content_int(0, "pMute");
		admin = cache_get_field_content_int(0, "bAdmin");
		if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы пытаетесь замутить администратора.");

    	if(mute > 0) return SCM(playerid, red, "У данного игрока уже стоит затычка.");

    	PlayerInfo[playerid][bOffMute]++;
    	SaveAccounts(playerid);

		new string[256], sql_str[256];
		format(string, sizeof(string), "[A] Администратор %s поставил затычку игроку %s оффлайн на %d минут. Причина: %s", PlayerInfo[playerid][pName], to_player, time, reason);
		SCMA(lightblue, string);

		format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pMute` = '%d' WHERE `pName` = '%s' LIMIT 1", time*60, to_player);
		mysql_tquery(connects, sql_str, "", "");

		format(string, sizeof(string), "Администратор %s поставил вам затычку оффлайн на %d минут. Прчина: %s", PlayerInfo[playerid][pName], time, reason);

		format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pMuteOffMess` = '%s' WHERE `pName` = '%s'", string, to_player);
		mysql_tquery(connects, sql_str, "", "");


		new day, month, year, hour, minute, second;
		getdate(day, month, year);
		gettime(hour, minute, second);
		format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

		mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', '%s', 'OffMute')", PlayerInfo[playerid][pName], to_player, string, time, reason);
		mysql_tquery(connects, sql_str, "", "");
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет!");
	}
	return 1;
}