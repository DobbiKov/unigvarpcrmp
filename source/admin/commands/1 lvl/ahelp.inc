CMD:ahelp(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);
    new fmt_dialog[1024];
    for(new i = 0; i < sizeof(Command1LVL); i++) strcat(fmt_dialog, Command1LVL[i]);
	return SPD(playerid, D_AHELP_1, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 1 уровня", fmt_dialog, "Далее", "Закрыть");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_AHELP_1:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 2) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[2048];
                for(new i = 0; i < sizeof(Command2LVL); i++) strcat(fmt_dialog, Command2LVL[i]);
                return SPD(playerid, D_AHELP_2, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 2 уровня", fmt_dialog, "Далее", "Закрыть");
            }
        }
        case D_AHELP_2:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 3) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[2048];
                for(new i = 0; i < sizeof(Command3LVL); i++) strcat(fmt_dialog, Command3LVL[i]);
                return SPD(playerid, D_AHELP_3, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 3 уровня", fmt_dialog, "Далее", "Закрыть");
            }
        }
        case D_AHELP_3:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 4) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[1024];
                for(new i = 0; i < sizeof(Command4LVL); i++) strcat(fmt_dialog, Command4LVL[i]);
                return SPD(playerid, D_AHELP_4, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 4 уровня", fmt_dialog, "Далее", "Закрыть");
            }
        }
        case D_AHELP_4:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 4) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[1024];
                for(new i = 0; i < sizeof(Command5LVL); i++) strcat(fmt_dialog, Command5LVL[i]);
                return SPD(playerid, D_AHELP_5, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 5 уровня", fmt_dialog, "Далее", "Закрыть");
            }
        }
        case D_AHELP_5:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 6) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[1024];
                for(new i = 0; i < sizeof(Command6LVL); i++) strcat(fmt_dialog, Command6LVL[i]);
                return SPD(playerid, D_AHELP_6, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 6 уровня", fmt_dialog, "Далее", "Закрыть");
            }
        }
        case D_AHELP_6:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][bAdmin] < 7) return SCM(playerid, red, "Ваш уровень Администратора мал, для просмотра этих команд.");

                new fmt_dialog[1024];
                for(new i = 0; i < sizeof(Command7LVL); i++) strcat(fmt_dialog, Command7LVL[i]);
                return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Команды администратора 7 уровня", fmt_dialog, "Закрыть", "");
            }
        }
    }
	#if	defined	ahelp__OnDialogResponse
		return ahelp__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse ahelp__OnDialogResponse
#if	defined	ahelp__OnDialogResponse
	forward ahelp__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif