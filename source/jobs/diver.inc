




public OnPlayerDisconnect(playerid, reason)
{
    if(GetPVarInt(playerid, "diver_job") == 1)
    {
		PayJob[playerid] = (kolvo_job[playerid]*diver_zp*XDay);
		GiveMoney(playerid, PayJob[playerid], "Зарплата водолаза");

		PayJob[playerid] = 0;
		kolvo_job[playerid] = 0;

		DeletePVar(playerid, "diver_job");
		DeletePVar(playerid, "gruz_diver_1");
		DeletePVar(playerid, "gruz_diver_2");

		RemovePlayerAttachedObject(playerid,0);
		RemovePlayerAttachedObject(playerid,1);
		RemovePlayerAttachedObject(playerid,2);
		RemovePlayerAttachedObject(playerid,8);
		RemovePlayerAttachedObject(playerid,5);
    }
    #if defined diver__OnPlayerDisconnect
        return diver__OnPlayerDisconnect(playerid, reason);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else   
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect diver__OnPlayerDisconnect
#if defined diver__OnPlayerDisconnect
    forward diver__OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 2813.1321,-1356.1815,4.0903))
        {
			if(PlayerInfo[playerid][pLVL] < 2) return SCM(playerid, red, "На данной работе можно работать только со 2-го уровня!");
            if(GetPVarInt(playerid, "diver_job") == 1)
            {
                SPD(playerid, D_DIVER_JOB, DIALOG_STYLE_MSGBOX, "{"cblue"}Прораб | Водолаз", "{FFFFFF}Ты уверен что хочешь уволиться с работы водолаза?", "Да", "Нет");
            }
            else
            {
                new string[256];
                format(string, sizeof(string), "{FFFFFF}Привет! Не хочешь поработать?\n\nТебе нужно будет достать 2 ящика из затонувшего здания.\nЗа 1 ящик ты будешь получать %d рублей!", (diver_zp));
                SPD(playerid, D_DIVER_JOB, DIALOG_STYLE_MSGBOX, "{"cblue"} Прораб | Водолаз", string, "Да", "Нет");
            }
        }
    }
	#if	defined	diver__OnPlayerKeyStateChange
		return diver__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange diver__OnPlayerKeyStateChange
#if	defined	diver__OnPlayerKeyStateChange
	forward diver__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_DIVER_JOB:
		{
		    if(GetPVarInt(playerid, "diver_job") == 1)
		    {
		        if(!response) SCM(playerid, green, "Вы продолжили работу водолаза!");
				else
				{
					PayJob[playerid] = (kolvo_job[playerid]*diver_zp*XDay);
					GiveMoney(playerid, PayJob[playerid], "Зарплата водолаза");
					
					new string[128];
					format(string, sizeof(string), "Всего заработано: {"cyellow"}%d {"cblue"}рублей.", PayJob[playerid]);
					SCM(playerid, blue, string);
					
					format(string, sizeof(string), "Всего ящиков перенесено: {"cyellow"}%d", kolvo_job[playerid]);
					SCM(playerid, blue, string);
					
					PayJob[playerid] = 0;
					kolvo_job[playerid] = 0;
					
					DeletePVar(playerid, "diver_job");
					DeletePVar(playerid, "gruz_diver_1");
					DeletePVar(playerid, "gruz_diver_2");
					
					RemovePlayerAttachedObject(playerid,0);
					RemovePlayerAttachedObject(playerid,1);
					RemovePlayerAttachedObject(playerid,2);
					RemovePlayerAttachedObject(playerid,8);
					RemovePlayerAttachedObject(playerid,5);
					SetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);
					
					if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
					else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
				}
			}
			else
			{
			    if(!response) return SCM(playerid, blue, "Вы отказались от работы водолаза!");
			    else
			    {
			        GetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);
					if(PlayerInfo[playerid][pSex]) SetPlayerSkin(playerid, 154);
					else SetPlayerSkin(playerid, 140);

					SetPlayerHealth(playerid, 100000.0);

					SCM(playerid, blue, "Вы начали работу водолаза!");
					SCM(playerid, yellow, "Товар находится в затонувшем здании возле берега.");
					SCM(playerid, yellow, "Поднятый товар вынесите на берег.");
					SCM(playerid, yellow, "Если Вы уйдёте далеко от места работы то, Ваша зарплата анулируется.");

					SetPVarInt(playerid, "diver_job", 1);

					SetPlayerAttachedObject(playerid, 0, 18843, 2, 0.05, 0.0, 0.0, 0.0, 0.0, 0.004, 0.004, 0.004, 0.004);

					SetPlayerAttachedObject(playerid, 5, 1010, 1, -0.023000,-0.071999,-0.020999,-84.700012,176.299942,1.700001,1.000000,1.000000,1.000000);
			    }
			}
		}
    }
	#if	defined	diver__OnDialogResponse
		return diver__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse diver__OnDialogResponse
#if	defined	diver__OnDialogResponse
	forward diver__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif


public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
		case CP_PUT_DIVE:
		{
		    if(GetPVarInt(playerid, "diver_job") != 1) return 1;
		    
		    SetPVarInt(playerid, "gruz_diver_1", 0);
		    SetPVarInt(playerid, "gruz_diver_2", 0);
		    DisablePlayerCheckpoint(playerid);
		    
			RemovePlayerAttachedObject(playerid,1);
			RemovePlayerAttachedObject(playerid,2);
			RemovePlayerAttachedObject(playerid,8);
			
			kolvo_job[playerid] += 2;
			
			SCM(playerid, yellow, "Вы подняли груз из затонувшего здания.");
			SCM(playerid, yellow, "Теперь вы можете поднять еще груз, либо завершить работу.");
			new string[128];
			format(string, sizeof(string), "Всего ящиков перенесено: {"cyellow"}%d", kolvo_job[playerid]);
			SCM(playerid, blue, string);
		}
    }
    #if defined diver__OnPlayerEnterCheckpoint
        return diver__OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerEnterCheckpoint
	#undef	OnPlayerEnterCheckpoint
#else
	#define	_ALS_OnPlayerEnterCheckpoint
#endif

#define	OnPlayerEnterCheckpoint diver__OnPlayerEnterCheckpoint
#if	defined	diver__OnPlayerEnterCheckpoint
	forward diver__OnPlayerEnterCheckpoint(playerid);
#endif

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(pickupid == DIVER_PICK_1)
	{
	    if(GetPVarInt(playerid, "diver_job") != 1) return SCM(playerid, red, "Вы не работаете водолазом!");
		if(GetPVarInt(playerid, "gruz_diver_1") == 1) return SCM(playerid, red, "Вы уже подобрали этот ящик!");

		SetPVarInt(playerid, "gruz_diver_1", 1);

		SetPlayerAttachedObject(playerid,1, 1279, 5,0.273000,0.039999,-0.011000,61.400001,6.000006,10.100000,1.000000,1.000000,1.000000);

		SCM(playerid, yellow, "Вы подняли затонувший ящик");
		if(GetPVarInt(playerid, "gruz_diver_1") == 1 && GetPVarInt(playerid, "gruz_diver_2") == 1)
		{
		    SCM(playerid, yellow, "Вы подняли оба ящика, теперь отнесите их на берег!");
		}
	}
	if(pickupid == DIVER_PICK_2)
	{
	    if(GetPVarInt(playerid, "diver_job") != 1) return SCM(playerid, red, "Вы не работаете водолазом!");
		if(GetPVarInt(playerid, "gruz_diver_1") != 1) return SCM(playerid, red, "Вы еще не подобрали ящик на первом этаже здания!");
		if(GetPVarInt(playerid, "gruz_diver_2") == 1) return SCM(playerid, red, "Вы уже подобрали этот ящик!");

		SetPVarInt(playerid, "gruz_diver_2", 1);

		SetPlayerAttachedObject(playerid,2, 1279, 6,0.330999,0.065999,0.072999,94.600006,-3.500000,11.500000,1.000000,1.000000,1.000000);

        SetPlayerCheckpoint(playerid, 2815.9971, -1380.4711, 2.9151, 3.0);
		pCheckpoint[playerid] = CP_PUT_DIVE;

		SCM(playerid, yellow, "Вы подняли затонувший ящик");
		if(GetPVarInt(playerid, "gruz_diver_1") == 1 && GetPVarInt(playerid, "gruz_diver_2") == 1)
		{
		    SCM(playerid, yellow, "Вы подняли оба ящика, теперь отнесите их на берег!");
		}
	}
    #if defined diver__OnPlayerPickUpPickup
        return diver__OnPlayerPickUpPickup(playerid, pickupid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerPickUpPickup
    #undef OnPlayerPickUpPickup
#else 
    #define _ALS_OnPlayerPickUpPickup
#endif

#define OnPlayerPickUpPickup diver__OnPlayerPickUpPickup
#if defined diver__OnPlayerPickUpPickup
    forward diver__OnPlayerPickUpPickup(playerid, pickupid);
#endif

public OnPlayerUpdate(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 300.0, 2815.9971,-1380.4711,2.9151))
	{
	    if(GetPVarInt(playerid, "diver_job") == 1)
	    {
			PayJob[playerid] = (kolvo_job[playerid]*diver_zp*XDay);
			GiveMoney(playerid, PayJob[playerid], "Зарплата водолаза");

			SCM(playerid, red, "Вы ушли слишком далеко от своего места работы и были уволены за это!");

			PayJob[playerid] = 0;
			kolvo_job[playerid] = 0;

			DeletePVar(playerid, "diver_job");
			DeletePVar(playerid, "gruz_diver_1");
			DeletePVar(playerid, "gruz_diver_2");

			RemovePlayerAttachedObject(playerid,0);
			RemovePlayerAttachedObject(playerid,1);
			RemovePlayerAttachedObject(playerid,2);
			RemovePlayerAttachedObject(playerid,8);
			RemovePlayerAttachedObject(playerid,5);
			
			SetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);

			if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
			else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	    }
	}
	#if defined diver__OnPlayerUpdate
		return diver__OnPlayerUpdate(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate diver__OnPlayerUpdate
#if defined diver__OnPlayerUpdate
	forward diver__OnPlayerUpdate(playerid);
#endif