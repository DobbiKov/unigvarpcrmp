CMD:tempjob(playerid, params[])
{ 
    if(PlayerInfo[playerid][bAdmin] < 5) return ShowCommandNotFound(playerid);
    if(PlayerInfo[playerid][pMember] > 0) return SCM(playerid, red, "Вы состоите в организации.");

    new string[64], fmt_dialog[256];
    for(new i = 0; i < sizeof(jobs_name); i++)
    {
        format(string, sizeof(string), "{"cblue"}%d. {FFFFFF}%s\n", i, jobs_name[i]);
        strcat(fmt_dialog, string);
    }

    return SPD(playerid, D_TEMP_JOB, DIALOG_STYLE_LIST, "{"cblue"}Временная работа", fmt_dialog, "Далее", "Отмена");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_TEMP_JOB:
        {
            if(!response) return 1;
            else
            {
                new string[144];
                if(listitem == 0)
                {
                    format(string, sizeof(string), "[A] %s[%d] уволил себя с временной работы: %s", PlayerInfo[playerid][pName], playerid, jobs_name[ PlayerInfo[playerid][pJob] ]);
                    SCMA(grey, string);
                    PlayerInfo[playerid][pJob] = 0;
                    return SaveAccounts(playerid);                    
                }

                PlayerInfo[playerid][pJob] = listitem;
                SaveAccounts(playerid);
                format(string, sizeof(string), "[A] %s[%d] назначил себя на временную работу: %s", PlayerInfo[playerid][pName], playerid, jobs_name[ PlayerInfo[playerid][pJob] ]);
                return SCMA(grey, string);               
            }
        }
    }
	#if	defined	tempjob__OnDialogResponse
		return tempjob__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse tempjob__OnDialogResponse
#if	defined	tempjob__OnDialogResponse
	forward tempjob__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif