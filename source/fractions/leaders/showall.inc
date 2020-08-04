CMD:showall(playerid)
{
    if(PlayerInfo[playerid][pMember] < 1 || PlayerInfo[playerid][pRang] < 10) return YouCannotUseThisFunc(playerid);

    SPD(playerid, D_SHOWALL, DIALOG_STYLE_LIST, "{"cblue"}Сортирование", "\
        {"cblue"}1. {FFFFFF}По возростанию ранга\n\
        {"cblue"}2. {FFFFFF}По убыванию ранга\n\
        {"cblue"}3. {FFFFFF}По возростанию даты входа\n\
        {"cblue"}4. {FFFFFF}По убыванию даты входа\n\
        {"cblue"}5. {FFFFFF}По возростанию уровня\n\
        {"cblue"}6. {FFFFFF}По убыванию уровня\n\
        {"cblue"}7. {FFFFFF}По алфавиту", "Далее", "Закрыть");
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_SHOWALL:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pRang` ASC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 1:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pRang` DESC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 2:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pLastConnect` ASC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 3:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pLastConnect` DESC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 4:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pLVL` ASC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 5:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pLVL` DESC", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
					case 6:
					{
					    new string[128];
					    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pMember` = '%i' ORDER BY `pName`", PlayerInfo[playerid][pMember]);
						mysql_tquery(connects, string, "all_members_for_fraction", "i", playerid);
					}
				}
			}
		}
    }
	#if	defined	showall__OnDialogResponse
		return showall__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse showall__OnDialogResponse
#if	defined	showall__OnDialogResponse
	forward showall__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics all_members_for_fraction(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	new fmt_str[1500], string[1500], player_name[MAX_PLAYER_NAME], rank, level, status[32];
	new last_connect[32];
	string = "{"cblue"}Ранг\tУровень\tСтатус\t\tПоследний вход\tИмя Фамилия\n\n{FFFFFF}";
	if(rows)
	{
        for(new i = 0; i < rows; i++)
		{
	        rank = cache_get_field_content_int(i, "pRang");
	        level = cache_get_field_content_int(i, "pLVL");
            cache_get_field_content(i, "pName", player_name, connects, MAX_PLAYER_NAME);
            cache_get_field_content(i, "pLastConnect", last_connect, connects, 32);

			if(GetPlayerID(player_name) == INVALID_PLAYER_ID) format(status,sizeof(status), "{C62821}OFF{FFFFFF}");
			else format(status,sizeof(status),"{99CC00}ON{FFFFFF}");
			format
			(
				fmt_str, sizeof(fmt_str),
				"%d\t\t%d\t\t%s\t\t%s\t%s\n",
				rank, level, status, last_connect, player_name
			);
	    	strcat(string, fmt_str);
    	}
	}
	ShowPlayerDialog
	(
		playerid, D_NULL, DIALOG_STYLE_MSGBOX,
		"{"cblue"}Состав организации",
		string,
		"Закрыть", ""
	);
	return true;
}