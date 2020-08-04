CMD:templeader(playerid, params[])
{ 
    if(PlayerInfo[playerid][bAdmin] < 5) return ShowCommandNotFound(playerid);

    new string[64], fmt_dialog[300];
    for(new i = 0; i < sizeof(GetMember); i++)
    {
        format(string, sizeof(string), "{"cblue"}%d. {FFFFFF}%s\n", i, GetMember[i]);
        strcat(fmt_dialog, string);
    }

    return SPD(playerid, D_TEMP_LEADER, DIALOG_STYLE_LIST, "{"cblue"}Временная лидерка", fmt_dialog, "Далее", "Отмена");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_TEMP_LEADER:
        {
            if(!response) return 1;
            else
            {
                new string[144];
                if(listitem == 0)
                {
                    format(string, sizeof(string), "[A] %s[%d] снял с себя временную лидерку %s", PlayerInfo[playerid][pName], playerid, GetMember[ PlayerInfo[playerid][pMember] ]);
                    SCMA(grey, string);
                    PlayerInfo[playerid][pMember] = 0;
                    PlayerInfo[playerid][pWarnF] = 0;
                    PlayerInfo[playerid][pRang] = 0;
                    PlayerInfo[playerid][pFSkin] = -1;
                    SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
                    return SaveAccounts(playerid);                    
                }

                PlayerInfo[playerid][pMember] = listitem;
                PlayerInfo[playerid][pRang] = 10;
                PlayerInfo[playerid][pJob] = 0;
                PlayerInfo[playerid][pFSkin] = 122;
                SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
                SaveAccounts(playerid);
                format(string, sizeof(string), "[A] %s[%d] назначил себя временным лидером организации %s", PlayerInfo[playerid][pName], playerid, GetMember[listitem]);
                return SCMA(grey, string);               
            }
        }
    }
	#if	defined	templeader__OnDialogResponse
		return templeader__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse templeader__OnDialogResponse
#if	defined	templeader__OnDialogResponse
	forward templeader__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif