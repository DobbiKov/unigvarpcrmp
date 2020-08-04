public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 817.4346,806.6161,-72.9914))
        {
			if(PlayerInfo[playerid][pMember] > 0) return SCM(playerid, red, "Вы состоите в организации!");

			SPD(playerid, D_SET_JOB, DIALOG_STYLE_LIST, "{"cblue"}Устройство на работу", "\
			{"cblue"}1. {FFFFFF}Водитель автобуса\t\t\t{"cblue"}(2 уровень)\n\
			{"cblue"}2. {FFFFFF}Водитель такси\t\t\t{"cblue"}(3 уровень)\n\
			{"cblue"}3. {FFFFFF}Автомеханик\t\t\t\t{"cblue"}(4 уровень)\n\
			{"cblue"}4. {FFFFFF}Дальнобойщик\t\t\t{"cblue"}(6 уровень)", "Ок", "Закрыть");
        }
    }
	#if	defined	jobs__OnPlayerKeyStateChange
		return jobs__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange jobs__OnPlayerKeyStateChange
#if	defined	jobs__OnPlayerKeyStateChange
	forward jobs__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_SET_JOB:
		{
		    if(!response) return 1;
		    else
		    {
		        switch(listitem)
		        {
		            case 0:
		            {
		                if(PlayerInfo[playerid][pLVL] < 2) return SCM(playerid, red, "Что б работать Водителем Автобуса, нужен минимум 2 игровой уровень!");
		                
		                PlayerInfo[playerid][pJob] = Job_Bus;
						SaveAccounts(playerid);
		                SCM(playerid, blue, "Вы успешно устроились Водителем автобуса!");
		                SCM(playerid, blue, "Узнать дополнительную информацию вы сможете введя команды: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 1:
		            {
		                if(PlayerInfo[playerid][pLVL] < 3) return SCM(playerid, red, "Что б работать Водителем Такси, нужен минимум 3 игровой уровень!");
		                
		                PlayerInfo[playerid][pJob] = Job_Taxi;
		                SaveAccounts(playerid);
		                SCM(playerid, blue, "Вы успешно устроились Водителем такси!");
		                SCM(playerid, blue, "Узнать дополнительную информацию вы сможете введя команды: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 2:
		            {
		                if(PlayerInfo[playerid][pLVL] < 4) return SCM(playerid, red, "Что б работать Автомехаником, нужен минимум 4 игровой уровень!");
		                
		                PlayerInfo[playerid][pJob] = Job_Car;
              			SaveAccounts(playerid);
		                SCM(playerid, blue, "Вы успешно устроились Автомехаником!");
		                SCM(playerid, blue, "Узнать дополнительную информацию вы сможете введя команды: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 3:
		            {
		                if(PlayerInfo[playerid][pLVL] < 6) return SCM(playerid, red, "Что б работать Дальнобойщиком, нужен минимум 6 игровой уровень!");
		                
		                PlayerInfo[playerid][pJob] = Job_Truck;
	                	SaveAccounts(playerid);
		                SCM(playerid, blue, "Вы успешно устроились Дальнобойщиком!");
		                SCM(playerid, blue, "Узнать дополнительную информацию вы сможете введя команды: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
          			}
		        }
		    }
		}
    }
	#if	defined	jobs__OnDialogResponse
		return jobs__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse jobs__OnDialogResponse
#if	defined	jobs__OnDialogResponse
	forward jobs__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif