publics CheckWarn(playerid)
{
	new rows, fields, string[256], unwarndate;
	cache_get_data(rows, fields);
	if(rows)
	{
		unwarndate = cache_get_field_content_int(0, "UnWarnDate");

		if(gettime() > unwarndate)
		{
		    format(string, sizeof(string), "DELETE FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[playerid][pName]);
		    mysql_tquery(connects, string, "", "");

		    SCM(playerid, green, "Поздравляем! С вас было снято одно предупреждение.");

		    PlayerInfo[playerid][pWarn]--;
		    if(PlayerInfo[playerid][pWarn] > 0)
		    {
		 	    format(string, sizeof(string), "SELECT * FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[playerid][pName]);
		        mysql_function_query(connects, string, true, "CheckWarn", "d", playerid);
		    }
		}
		else
		{
			if(GetPVarInt(playerid, "cmd_unwarn") == 0) SCM(playerid, red, "К сожалению, в данный момент на вашем аккаунте имееться предупреждение.");
			else
			{
			    format(string, sizeof(string), "\
				{FFFFFF}В данный моментна вашем аккаунте имееться предупреждение!\n\n\
				Это значит, что вы не можете вступать в организации, покупать/продавать дома/бизнессы.\n\n\
				Дата снятия предупреждения: {"cblue"}%s", date("%dd/%mm/%yyyy {FFFFFF}Время: {"cblue"}%hh:%ii:%ss", unwarndate));
				SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Предупреждение", string, "Закрыть", "");
			}
		}
	}
	else
	{
		if(PlayerInfo[playerid][pVIP] > 0) unwarndate = gettime() + 3*86400;
		else unwarndate = gettime() + 7*86400;

		mysql_format(connects, stringer, sizeof(stringer), "INSERT INTO `unwarn` (`UnWarnDate`, `Nick`) VALUES ('%d', '%s')", unwarndate, PlayerInfo[playerid][pName]);
		mysql_tquery(connects, stringer);
	}
	return 1;
}
publics on_player_offwarn(playerid, to_player[], reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new admin, string[256];
		admin = cache_get_field_content_int(0, "bAdmin");
		if(admin > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Вы пытаетесь заварнить администратора.");

		format(string, sizeof(string), "SELECT * FROM `Bans` WHERE `Nick` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "on_player_offwarn_bans","iss", playerid, to_player, reason);
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}
publics on_player_offwarn_bans(playerid, to_player[], reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		return SCM(playerid, red, "У данного игрока имееться блокировка аккаунта.");
	}
	else
	{
	    new string[256], warns;
	    warns = cache_get_field_content_int(0, "pWarn");

	    warns++;
	    PlayerInfo[playerid][bOffWarn]++;

		format(string, sizeof(string), "Администратор %s выдал предупреждение игроку %s [%d|3] в Offline. Причина: %s", PlayerInfo[playerid][pName], to_player, warns, reason);
		SCMTA(red, string);

		new data[64], year, month, day, hour, minute, second;

	    gettime(hour, minute, second);
	    getdate(year, month, day);
	    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

		mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '7', '%s', 'warn')", PlayerInfo[playerid][pName], to_player, data);
		mysql_tquery(connects, string, "", "");

		if(warns == 3)
		{
		    new unbandate;

 		    unbandate = gettime() + 10*86400; // Бан на дни. Записываем нынешнюю дату + число умноженное на 86400 = дни бана.
		    format(string, sizeof(string), "INSERT INTO `Bans` (`Nick`, `UnbanDate`, `AdminNick`, `BanDate`, `Type`, `Reason`) VALUES ('%s', '%d', '%s', '%s', 'offBan', '3 Предупреждения')", to_player, unbandate, PlayerInfo[playerid][pName], data); // Форматируем запрос в бд
		    mysql_tquery(connects, string, "","");

		    format(string, sizeof(string), "DELETE FROM `unwarn` WHERE `Nick` = '%s'", to_player);
		    mysql_tquery(connects, string, "", "");

			mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '10', '3 warns', 'offban')", PlayerInfo[playerid][pName], to_player, data);
			mysql_tquery(connects, string, "", "");

			format(string, sizeof(string), "Администратор %s заблокировал игрока %s на 10 дней в Offline. Причина: 3 Предупреждения", PlayerInfo[playerid][pName], to_player);
	    	SCMTA(red, string);

	    	PlayerInfo[playerid][bOffBan]++;
		}

		SaveAccounts(playerid);

		format(string, sizeof(string), "UPDATE `accounts` SET `pWarn` = '%d' WHERE `pName` = '%s' LIMIT 1", warns, to_player);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "UPDATE `accounts` SET `pMember` = '0' WHERE `pName` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "UPDATE `accounts` SET `pRang` = '0' WHERE `pName` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "UPDATE `accounts` SET `bAdmin` = '0' WHERE `pName` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "UPDATE `accounts` SET `pFSkin` = '0', `pWarnF` = '0' WHERE `pName` = '%s' LIMIT 1", to_player);
		mysql_tquery(connects, string, "", "");
	}
	return 1;
}
publics on_player_unwarn(playerid, to_player[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    new warns;
	    warns = cache_get_field_content_int(0, "pWarn");
	    warns--;
		new string[256], data[64], year, month, day, hour, minute, second;

	    gettime(hour, minute, second);
	    getdate(year, month, day);
	    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

        format(string, sizeof(string), "DELETE FROM `unwarn` WHERE `Nick` = '%s' LIMIT 1", to_player);
        mysql_tquery(connects, string, "","");

		mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '0', 'offunwarn', 'offunwarn')", PlayerInfo[playerid][pName], to_player, data);
		mysql_tquery(connects, string, "", "");

		format(string, sizeof(string), "[A]: %s[%d] снял 1 предупреждение у игрока %s", PlayerInfo[playerid][pName], playerid, to_player);
		SCMA(red, string);

		format(string, sizeof(string), "UPDATE `accounts` SET `pWarns` = '%d' WHERE `pName` = '%s' LIMIT 1", warns, to_player);
		mysql_tquery(connects, string, "", "");

		PlayerInfo[playerid][bUnWarn]++;
		SaveAccounts(playerid);
	}
	else
	{
	    SCM(playerid, red, "Такого игрока нет.");
	}
	return 1;
}

CMD:warn(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new string: to_player[24], string: reason[30]; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /warn [Ник игрока] [Причина]");

	new string[528], data[64], year, month, day, hour, minute, second;
 	foreach(new i:Player)
 	{
 		if(!strcmp(PlayerInfo[i][pName], to_player, true))
 		{
 		    if(PlayerInfo[i][bAdmin] > PlayerInfo[playerid][bAdmin])
 		    {
 		        format(string, sizeof(string), "[A]: %s[%d] попытался заварнить %s[%d].");
 		        SCMA(red, string);
 		        PlayerInfo[playerid][bAdmin] = 0;
 		        return SaveAccounts(playerid);
 		    }

 		    gettime(hour, minute, second);
 		    getdate(year, month, day);
 		    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

			mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '7', '%s', 'warn')", PlayerInfo[playerid][pName], PlayerInfo[i][pName], data, reason);
			mysql_tquery(connects, string, "", "");

			PlayerInfo[i][bAdmin] = 0;
			PlayerInfo[i][pWarn]++;
			PlayerInfo[playerid][bWarn]++;

		    format(string, sizeof(string), "Администратор %s выдал предупреждение игроку %s [%d|3]. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[i][pName], PlayerInfo[i][pWarn], reason);
		    SCMTA(red, string);

			if(PlayerInfo[i][pWarn] == 3)
			{
				PlayerInfo[i][pFSkin] = -1;
				PlayerInfo[i][pMember] = 0;
				PlayerInfo[i][pRang] = 0;
				PlayerInfo[i][pWarnF] = 0;

			    new unbandate;

	 		    unbandate = gettime() + 10*86400; // Бан на дни. Записываем нынешнюю дату + число умноженное на 86400 = дни бана.
			    format(string, sizeof(string), "INSERT INTO `Bans` (`Nick`, `UnbanDate`, `AdminNick`, `BanDate`, `Type`, `Reason`) VALUES ('%s', '%d', '%s', '%s', 'Ban', '3 Предупреждения')", PlayerInfo[i][pName], unbandate, PlayerInfo[playerid][pName], data); // Форматируем запрос в бд
			    mysql_tquery(connects, string, "","");

			    format(string, sizeof(string), "DELETE FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[i][pName]);
			    mysql_tquery(connects, string, "", "");

				mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '10', '3 warns', 'ban')", PlayerInfo[playerid][pName], PlayerInfo[i][pName], data);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "Администратор %s заблокировал игрока %s на 10 дней. Причина: 3 Предупреждения", PlayerInfo[playerid][pName], PlayerInfo[i][pName]);
		    	SCMTA(red, string);
			}

			SaveAccounts(i);
			SaveAccounts(playerid);

			format(string, sizeof(string), "\
			{FFFFFF}Вам было выдано предупреждение!\n\n\
			{FFFFFF}Ваш ник:\t\t\t{"cblue"}%s\n\
			{FFFFFF}Ник Администратора:\t\t{"cblue"}%s\n\
			{FFFFFF}Причина:\t\t\t{"cblue"}%s\n\
			{FFFFFF}Дата выдачи:\t\t\t{"cblue"}%s\n\n\
			{FFFFFF}Если вы не согласны с наказанием,\n\
		 	вы можете написать жалобу на наш форум!\n\n\
		 	Введите {"cblue"}/q {FFFFFF}что б выйти.", PlayerInfo[i][pName], PlayerInfo[playerid][pName], reason, data);
			SPD(i, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Предупреждение", string, "Закрыть", "");
            return NewKick(i);
	 	}
 	}


	static const fmt_query[] = "SELECT * FROM `accounts` WHERE `pName` = '%s' LIMIT 1";
    new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
    format(query, sizeof(query), fmt_query, to_player);
    return mysql_tquery(connects, query, "on_player_offwarn", "iss", playerid, to_player, reason);
}
CMD:unwarn(playerid, params[])
{
    new string[256];
	if(PlayerInfo[playerid][bAdmin] < 4)
	{
	    if(PlayerInfo[playerid][pWarn] == 0) return SCM(playerid, red, "У вас нет предупреждений.");

	    SetPVarInt(playerid, "cmd_unwarn", 1);
 		format(string, sizeof(string), "SELECT * FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[playerid][pName]);
        mysql_function_query(connects, string, true, "CheckWarn", "d", playerid);
	}
	else
	{
		extract params -> new string: to_player[24]; else return SCM(playerid, blue, "• [Подсказка]: {FFFFFF}Используйте /unwarn [NickName игрока]");

		foreach(new i : Player)
		{
		    if(!strcmp(PlayerInfo[i][pName], to_player, true))
		    {
		        if(PlayerInfo[i][pWarn] == 0) return SCM(playerid, red, "У данного игрока нет предупреждений.");

		        PlayerInfo[i][pWarn]--;
		        PlayerInfo[playerid][bUnWarn]++;
		        format(string, sizeof(string), "DELETE FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[i][pName]);
		        mysql_tquery(connects, string, "", "");

		        SaveAccounts(i);
		        SaveAccounts(playerid);

		        new data[64], year, month, day, hour, minute, second;

			    gettime(hour, minute, second);
			    getdate(year, month, day);
			    format(data, sizeof(data), "%d/%d/%d -- %d:%d:%d", year, month, day, hour, minute, second);

				mysql_format(connects, string, sizeof(string), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '0', 'unwarn', 'unwarn')", PlayerInfo[playerid][pName], PlayerInfo[i][pName], data);
				mysql_tquery(connects, string, "", "");

		        format(string, sizeof(string), "[A]: %s[%d] снял 1 предупреждение у игрока %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[i][pName], i);
		        return SCMA(red, string);
		    }
		}

		new query[256];
		format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `pName` = '%s'", to_player);
		mysql_tquery(connects, query, "on_player_unwarn", "is", playerid, to_player);
	}
	return 1;
}
    