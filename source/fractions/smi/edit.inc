CMD:edit(playerid)
{
    if(PlayerInfo[playerid][pMember] != TEAM_SMI) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "У вас стоит блокировка чата!");

    new sttr[20*MAX_PLAYER_NAME+100], string[MAX_PLAYER_NAME+5+30], count, status[40];
    foreach(new i : ads)
    {
        if(AD[i][ad_ID] == -1) continue;
        dialog_listitem_values[playerid][count] = i;
        count++;

        switch(AD[i][ad_status])
        {
            case 0: status = "";
            case 1: status = "{"cyellow"}(Проверяется)";
            case 2: status = "{"cgreen"}(Проверено)";
        }

        format(string, sizeof(string), "%s %s\n", PlayerInfo[ AD[i][ad_playerid] ][pName], status);
        strcat(sttr, string);
    } 
    if(count == 0) return SCM(playerid, red, "Объявлений пока нет!");
    return SPD(playerid, D_EDIT, DIALOG_STYLE_LIST, "{"cblue"}Объявления", sttr, "Далее", "Закрыть"); 
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_EDIT:
        {
  			if(response)
			{
				new i = dialog_listitem_values[playerid][listitem];
                if(AD[i][ad_status] == 1) return SCM(playerid, red, "Объявление уже проверяеться кем-то!");
                if(AD[i][ad_status] == 2) return SCM(playerid, red, "Объявление уже проверено!");
                SetPVarInt(playerid, "d_edits", i);
				
                new string[100];
                format(string, sizeof(string), "{"cblue"}%s", AD[i][ad_text]);
                AD[GetPVarInt(playerid, "d_edits")][ad_status] = 1;
                SPD(playerid, D_EDITS, DIALOG_STYLE_LIST, string, "{"cblue"}1. {FFFFFF}Редактировать\n{"cblue"}2. {FFFFFF}Отправить\n{"cblue"}3. {FFFFFF}Удалить\n{"cblue"}2. {FFFFFF}Удалить и отправить администрации\n", "Далее", "Назад");
			}          
        }
        case D_EDITS:
        {
            if(!response)
            {
                AD[GetPVarInt(playerid, "d_edits")][ad_status] = 0;
                DeletePVar(playerid, "d_edits");
                new sttr[20*MAX_PLAYER_NAME+100], string[MAX_PLAYER_NAME+5+30], count, status[40];
                foreach(new i : ads)
                {
                    if(AD[i][ad_ID] == -1) continue;
                    dialog_listitem_values[playerid][count] = i;
                    count++;

                    switch(AD[i][ad_status])
                    {
                        case 0: status = "";
                        case 1: status = "{"cyellow"}(Проверяется)";
                        case 2: status = "{"cgreen"}(Проверено)";
                    }

                    format(string, sizeof(string), "%s %s\n", PlayerInfo[ AD[i][ad_playerid] ][pName], status);
                    strcat(sttr, string);
                } 
                return SPD(playerid, D_EDIT, DIALOG_STYLE_LIST, "{"cblue"}Объявления", sttr, "Далее", "Закрыть");                
            }
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        new string[MAX_PLAYER_NAME+20], string_2[100+10];
                        format(string, sizeof(string), "{"cblue"}Объявление: %s", PlayerInfo[AD[GetPVarInt(playerid, "d_edits")][ad_playerid]][pName]);
                        format(string_2, sizeof(string_2), "{FFFFFF}%s", AD[GetPVarInt(playerid, "d_edits")][ad_text]);
                        return SPD(playerid, D_EDIT_EDIT, DIALOG_STYLE_INPUT, string, string_2, "Oк", "Назад");
                    }
                    case 1:
                    {
                        GiveMoney(playerid, 10, "Редактирование сообщения(/edit)");
                        AD[GetPVarInt(playerid, "d_edits")][ad_status] = 2;
                        AD[GetPVarInt(playerid, "d_edits")][ad_edit_id] = playerid;
                        DeletePVar(playerid, "d_edits");                        
                    }
                    case 2:
                    {
                        new string[144];
                        format(string, sizeof(string), "%s %s[%d] удалил ваше объявление", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                        SCM(AD[GetPVarInt(playerid, "d_edits")][ad_playerid], red, string);

                        SCM(playerid, blue, "Вы удалили объявление!");

                        AD[GetPVarInt(playerid, "d_edits")][ad_ID] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_playerid] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_status] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_edit_id] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_text] = EOS;
                        Iter_Remove(ads, GetPVarInt(playerid, "d_edits"));
                        DeletePVar(playerid, "d_edits");  
                    }
                    case 3:
                    {
                        new string[144];
                        format(string, sizeof(string), "%s %s[%d] удалил ваше объявление!", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid);
                        SCM(AD[GetPVarInt(playerid, "d_edits")][ad_playerid], red, string);

                        SCM(playerid, blue, "Вы удалили объявление и отправили его Администрации!");

                        format(string, sizeof(string), "{"cgrey"}[{"cred"}AD{"cgrey"}] %s %s[%d] жалуеться на объявление %s[%d]: %s", GetPlayerRank(playerid), PlayerInfo[playerid][pName], playerid, PlayerInfo[AD[GetPVarInt(playerid, "d_edits")][ad_playerid]], AD[GetPVarInt(playerid, "d_edits")][ad_playerid], AD[GetPVarInt(playerid, "d_edits")][ad_text]);
                        SCMA(grey, string);

                        AD[GetPVarInt(playerid, "d_edits")][ad_ID] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_playerid] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_status] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_edit_id] = -1;
                        AD[GetPVarInt(playerid, "d_edits")][ad_text] = EOS;
                        Iter_Remove(ads, GetPVarInt(playerid, "d_edits"));
                        DeletePVar(playerid, "d_edits");  
                    }
                }
            }
        }
        case D_EDIT_EDIT:
        {
            if(!response)
            { 
                new string[MAX_PLAYER_NAME];
                format(string, sizeof(string), "%s", PlayerInfo[AD[GetPVarInt(playerid, "d_edits")][ad_playerid]][pName]);
                return SPD(playerid, D_EDITS, DIALOG_STYLE_LIST, string, "{"cblue"}1. {FFFFFF}Редактировать\n{"cblue"}2. {FFFFFF}Отправить\n{"cblue"}3. {FFFFFF}Удалить\n{"cblue"}2. {FFFFFF}Удалить и отправить администрации\n", "Далее", "Назад");
            }
            else
            {
                if(!strlen(inputtext) || strlen(inputtext) > 100)
                {
                    new string[MAX_PLAYER_NAME+20], string_2[100+10];
                    format(string, sizeof(string), "{"cblue"}Объявление: %s", PlayerInfo[AD[GetPVarInt(playerid, "d_edits")][ad_playerid]][pName]);
                    format(string_2, sizeof(string_2), "{FFFFFF}%s", AD[GetPVarInt(playerid, "d_edits")][ad_text]);
                    return SPD(playerid, D_EDIT_EDIT, DIALOG_STYLE_INPUT, string, string_2, "Oк", "Назад");                 
                }

                GiveMoney(playerid, 10, "Редактирование сообщения(/edit)");
                AD[GetPVarInt(playerid, "d_edits")][ad_status] = 2;
                AD[GetPVarInt(playerid, "d_edits")][ad_edit_id] = playerid;
                AD[GetPVarInt(playerid, "d_edits")][ad_text] = EOS;
                strcat(AD[GetPVarInt(playerid, "d_edits")][ad_text], inputtext);
                DeletePVar(playerid, "d_edits"); 
            }
        }
    }
	#if	defined	edit__OnDialogResponse
		return edit__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse edit__OnDialogResponse
#if	defined	edit__OnDialogResponse
	forward edit__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics secondupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);
    if(second == 20 || second  == 40 || second == 59)
    {
        foreach(new i : ads)
        {
            if(AD[i][ad_status] != 2) continue;

            new string[144];
            format(string, sizeof(string), "%s | Отправил: %s (тел. %d)", AD[i][ad_text], PlayerInfo[AD[i][ad_playerid]][pName], PlayerInfo[AD[i][ad_playerid]][pPhoneNumber]);
            SCMTA(0x66cc00AA, string);

            format(string, sizeof(string), "   Объявление проверил %s %s.", GetPlayerRank(AD[i][ad_edit_id]), PlayerInfo[AD[i][ad_edit_id]][pName]);
            SCMTA(green, string);

            AD[i][ad_ID] = -1;
            AD[i][ad_playerid] = -1;
            AD[i][ad_status] = -1;
            AD[i][ad_edit_id] = -1;
            AD[i][ad_text] = EOS;
            Iter_Remove(ads, i);
        }
    }
	#if	defined	edit__secondupdate
		return edit__secondupdate();
	#else
		return 1;
	#endif
}
#if	defined	_ALS_secondupdate
	#undef	secondupdate
#else
	#define	_ALS_secondupdate
#endif

#define	secondupdate edit__secondupdate
#if	defined	edit__secondupdate
	forward edit__secondupdate();
#endif

