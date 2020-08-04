CMD:wanted(playerid, params[])
{
	if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);

	new fmt_str[MAX_PLAYER_NAME+3+6+30];
	new text[(sizeof fmt_str) * 10];
	new count;

	foreach(new i : Player)
	{
		if(PlayerInfo[i][pWANTED] > 0)
		{
			if(!IsPlayerConnected(i) || PlayerInfo[i][pLogin] == false) continue;

			dialog_listitem_values[playerid][count] = i;
			count++;

			format(fmt_str, sizeof fmt_str, "%s[%d] (%d уровень рзыска)\n", PlayerInfo[i][pName], i, PlayerInfo[i][pWANTED]);
			strcat(text, fmt_str);
		}
	}

	ShowPlayerDialog
	(
		playerid, D_WANTED, DIALOG_STYLE_LIST,
		"{"cblue"}Список разыскиваемых",
		text,
		"Ок", "Отмена"
	);

	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_WANTED:
		{
			if(response)
			{
				new to_player = dialog_listitem_values[playerid][listitem];
				
				new fmt_msg[128];
				
				format(fmt_msg, sizeof(fmt_msg), "Разыскиваемый %s отмечен на карте красной меткой", PlayerInfo[to_player][pName]);
				SCM(playerid, blue, fmt_msg);

				new Float:x, Float:y, Float:z;
				GetPlayerPos(to_player, x, y, z);
				SetPlayerCheckpoint(playerid, x, y, z, 5.0);
				pCheckpoint[playerid] = CP_WANTED;
			}
		}
    }
	#if	defined	wanted__OnDialogResponse
		return wanted__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse wanted__OnDialogResponse
#if	defined	wanted__OnDialogResponse
	forward wanted__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
	{
		case CP_WANTED:
		{
			DisablePlayerCheckpoint(playerid);
			SCM(playerid, blue, "Последний раз подозреваемого видели тут!");
		}
	}
    #if defined wanted__OnPlayerEnterCheckpoint
        return wanted__OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerEnterCheckpoint
	#undef	OnPlayerEnterCheckpoint
#else
	#define	_ALS_OnPlayerEnterCheckpoint
#endif

#define	OnPlayerEnterCheckpoint wanted__OnPlayerEnterCheckpoint
#if	defined	wanted__OnPlayerEnterCheckpoint
	forward wanted__OnPlayerEnterCheckpoint(playerid);
#endif