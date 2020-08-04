publics CheckBan(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new string[512], AdminName[MAX_PLAYER_NAME], reason[256], data[64], unbandate;
		unbandate = cache_get_field_content_int(0, "UnbanDate");
		cache_get_field_content(0, "Reason", reason, connects, 256);
		cache_get_field_content(0, "BanDate", data, connects, 50);
		cache_get_field_content(0, "AdminNick", AdminName, connects, 32);

        if(gettime() >= unbandate)
        {
            format(string, sizeof(string), "DELETE FROM `Bans` WHERE `Nick` = '%s' LIMIT 1", PlayerInfo[playerid][pName]);
            mysql_tquery(connects, string, "","");

       	    SpawnList(playerid);
			if(strcmp(PlayerInfo[playerid][pJailOffMess], "None", true))
			{
			    SCM(playerid, red, "Jail:");
			    SCM(playerid, red, PlayerInfo[playerid][pJailOffMess]);
			}
			if(strcmp(PlayerInfo[playerid][pMuteOffMess], "None", true))
			{
			    SCM(playerid, red, "Mute:");
			    SCM(playerid, red, PlayerInfo[playerid][pMuteOffMess]);
			}
			if(XDay != 1)
			{
				format(string, sizeof(string), "Сегодня на сервере X%d день! Это значит, что оплата на работах, зарплата во фракциях, опыт и т.д начисляються в двое больше.", XDay);
				SCM(playerid, yellow, string);
			}

            return 1;
        }
		else
		{
			format(string, sizeof(string), "\
			{FFFFFF}Вы забанены на этом сервере.\n\n\
			{FFFFFF}Ваш ник:\t\t\t{"cblue"}%s\n\
			{FFFFFF}Ник Администратора:\t\t{"cblue"}%s\n\
			{FFFFFF}Причина:\t\t\t{"cblue"}%s\n\
			{FFFFFF}Дата блокировки:\t\t{"cblue"}%s\n\
			{FFFFFF}Дата разблокировки:\t\t{"cblue"}%s\n\n\
			{FFFFFF}Если вы не согласны с наказанием,\n\
		 	вы можете написать жалобу на наш форум!\n\n\
	 		Введите {"cblue"}/q {FFFFFF}что б выйти.", PlayerInfo[playerid][pName], AdminName, reason, data, date("%dd/%mm/%yyyy Время: %hh:%ii:%ss", unbandate));
			SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Блокировка аккаунта", string, "Закрыть", "");
			NewKick(playerid);
		}
	}
	else
	{
	    SpawnList(playerid);
		if(strcmp(PlayerInfo[playerid][pJailOffMess], "None", true))
		{
		    SCM(playerid, red, "Jail:");
		    SCM(playerid, red, PlayerInfo[playerid][pJailOffMess]);
		}
		if(strcmp(PlayerInfo[playerid][pMuteOffMess], "None", true))
		{
		    SCM(playerid, red, "Mute:");
		    SCM(playerid, red, PlayerInfo[playerid][pMuteOffMess]);
		}
		if(XDay != 1)
		{
			new string[150];
			format(string, sizeof(string), "Сегодня на сервере X%d день! Это значит, что оплата на работах, зарплата во фракциях,опыт и т.д начисляються в двое больше.", XDay);
			SCM(playerid, yellow, string);
		}
	}
	return 1;
}
publics on_player_unban(playerid, to_player[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new string[256], data[64], year, month, day, hour, minute, second;

	    gettime(hour, minute, second);
	    getdate(year, month, day);
	    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

        format(string, sizeof(string), "DELETE FROM `Bans` WHERE `Nick` = '%s' LIMIT 1", to_player);
        mysql_tquery(connects, string, "","");

		mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '0', 'unban', 'unban')", PlayerInfo[playerid][pName], to_player, data);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "[A]: %s[%d] разбанил игрока %s", PlayerInfo[playerid][pName], playerid, to_player);
		SCMA(red, string);

		PlayerInfo[playerid][bUnBan]++;
		SaveAccounts(playerid);
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}
publics on_player_offban(playerid, to_player[], time, reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin, string[256];
		admin = cache_get_field_content_int(0, "bAdmin");
		if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы пытаетесь забанить администратора.");

		format(string, sizeof(string), "SELECT * FROM `Bans` WHERE `Nick` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "on_player_offbans","isis", playerid, to_player, time, reason);
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}
publics on_player_offbans(playerid, to_player[], time, reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		return SCM(playerid, red, "Игрок уже забанен.");
	}
	else
	{
		new string[256], unbandate, data[64], year, month, day, hour, minute, second;

	    gettime(hour, minute, second);
	    getdate(year, month, day);
	    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

	    unbandate = gettime() + time*86400;
	    format(string, sizeof(string), "INSERT INTO `Bans` (`Nick`, `UnbanDate`, `AdminNick`, `BanDate`, `Type`, `Reason`) VALUES ('%s', '%d', '%s', '%s', 'offBan', '%s')", to_player, unbandate, PlayerInfo[playerid][pName], data, reason); // Форматируем запрос в бд
	    mysql_tquery(connects, string, "","");

	    format(string, sizeof(string), "Администратор %s забанил игрока %s на %d дней в Offline. Причина: %s", PlayerInfo[playerid][pName], to_player, time, reason);
	    SCMTA(red, string);

		mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', '%s', 'offban')", PlayerInfo[playerid][pName], to_player, data, time, reason);
		mysql_tquery(connects, string, "", "");

		PlayerInfo[playerid][bOffBan]++;
		SaveAccounts(playerid);

	}
	return 1;
}

CMD:ban(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], time, string: reason[30]; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /ban [Ник игрока] [Дни(1-30)] [Причина]");

	if(time < 1)
	    return SCM(playerid, red, "От 1, до 30-ти дней.");
	if(time > 30 && time < 365)
		return SCM(playerid, red, "От 1, до 30-ти дней.");
	if(time > 365)
		return SCM(playerid, red, "От 1, до 30-ти дней.");

	new string[256], unbandate, data[64], year, month, day, hour, minute, second;
 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 		{
 		    if(PlayerInfo[i][bAdmin] > PlayerInfo[playerid][bAdmin])
 		    {
 		        format(string, sizeof(string), "[A]: %s[%d] попытался забанить %s[%d].");
 		        SCMA(red, string);
 		        PlayerInfo[playerid][bAdmin] = 0;
 		        return SaveAccounts(playerid);
 		    }

 		    gettime(hour, minute, second);
 		    getdate(year, month, day);
 		    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

 		    unbandate = gettime() + time*86400; // Бан на дни. Записываем нынешнюю дату + число умноженное на 86400 = дни бана.
		    format(string, sizeof(string), "INSERT INTO `Bans` (`Nick`, `UnbanDate`, `AdminNick`, `BanDate`, `Type`, `Reason`) VALUES ('%s', '%d', '%s', '%s', 'Ban', '%s')", PlayerInfo[i][pName], unbandate, PlayerInfo[playerid][pName], data, reason); // Форматируем запрос в бд
		    mysql_tquery(connects, string, "","");

		    format(string, sizeof(string), "Администратор %s забанил игрока %s на %d дней. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[i][pName], time, reason);
		    SCMTA(red, string);

			mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', '%s', 'ban')", PlayerInfo[playerid][pName], PlayerInfo[i][pName], data, time, reason);
			mysql_tquery(connects, string, "", "");

			PlayerInfo[i][bAdmin] = 0;
			PlayerInfo[playerid][bBan]++;

			SaveAccounts(i);
			SaveAccounts(playerid);

			format(string, sizeof(string), "\
			{FFFFFF}Вы забанены на этом сервере!\n\n\
			{FFFFFF}Ваш ник:\t\t{"cblue"}%s\n\
			{FFFFFF}Ник Администратора:\t{"cblue"}%s\n\
			{FFFFFF}Причина:\t\t{"cblue"}%s\n\
			{FFFFFF}Дата блокировки:\t{"cblue"}%s\n\
			{FFFFFF}Дата разблокировки:\t{"cblue"}%s\n\n\
			{FFFFFF}Если вы не согласны с наказанием,\n\
		 	вы можете написать жалобу на наш форум!\n\n\
		 	Введите {"cblue"}/q {FFFFFF}что б выйти.", PlayerInfo[i][pName], PlayerInfo[playerid][pName], reason, data, date("%dd/%mm/%yyyy Время: %hh:%ii:%ss", unbandate));
			SPD(i, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Блокировка аккаунта", string, "Закрыть", "");
            return NewKick(i);
	 	}
 	}


	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "on_player_offban", "isis", playerid, to_player, time, reason);
}

CMD:unban(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24]; else return SCM(playerid, blue, "• [Подсказка]: {FFFFFF}Используйте /unabn [NickName игрока]");

	new query[256];
	format(query, sizeof(query), "SELECT * FROM `Bans` WHERE `Nick` = '%s'", to_player);
	mysql_tquery(connects, query, "on_player_unban", "is", playerid, to_player);
	return 1;
}