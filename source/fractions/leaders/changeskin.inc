CMD:changeskin(playerid, params[])
{
	if(PlayerInfo[playerid][pMember] == 0) return YouCannotUseThisFunc(playerid);

	if(PlayerInfo[playerid][pRang] < 8) return YouCannotUseThisFunc(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, "•[Подсказка] {ffffff}Введите: /changeskin [ид игрока]");
	change_team_skin_playerid[playerid] = to_player;

	if(PlayerInfo[playerid][pMember] != PlayerInfo[to_player][pMember])
		return SCM(playerid, red, "Вы не можете именить скин этому игроку");

	new name[MAX_PLAYER_NAME];
	new fmt_str[18];
	new text[(sizeof fmt_str) * 10];
	new old_skin;
	new org = PlayerInfo[playerid][pMember];
	new count;

	format(name, sizeof name, "%s", PlayerInfo[to_player][pName]);

	for(new i; i < 10; i++)
	{
		if(old_skin == ChangeSkin[org][i]) continue;
		if(ChangeSkin[org][i] == EOS) continue;

		dialog_listitem_values[playerid][count] = i; 
		count++;

		old_skin = ChangeSkin[org][i];

		format(fmt_str, sizeof fmt_str, "Скин %d [%d]\n", count, old_skin);
		strcat(text, fmt_str);
	}

	ShowPlayerDialog
	(
		playerid, D_CHANGE_SKIN, DIALOG_STYLE_LIST,
		name,
		text,
		"Ок", "Отмена"
	);

	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_CHANGE_SKIN:
		{
			if(response)
			{
				new team_id = PlayerInfo[playerid][pMember];
				new to_player = change_team_skin_playerid[playerid];
				new index = dialog_listitem_values[playerid][listitem];

				PlayerInfo[to_player][pFSkin] = ChangeSkin[team_id][index];
				SetPlayerSkin(to_player, PlayerInfo[to_player][pFSkin]);
				
				new fmt_msg[128];
				
				format(fmt_msg, sizeof(fmt_msg), "%s %s сменил вашу фракционную одежду", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName]);
				SCM(to_player, blue, fmt_msg);

                format(fmt_msg, sizeof(fmt_msg), "Вы сменили одежду %s", PlayerInfo[to_player][pName]);
                SCM(playerid, blue, fmt_msg);
				
                SaveAccounts(to_player);
			}
		}
    }
	#if	defined	ch_skin__OnDialogResponse
		return ch_skin__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse ch_skin__OnDialogResponse
#if	defined	ch_skin__OnDialogResponse
	forward ch_skin__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif