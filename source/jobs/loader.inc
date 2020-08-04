public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP) || (newkeys & KEY_FIRE))
    {
        if(GetPVarInt(playerid, "loader_job") == 1)
        {
            if(GetPVarInt(playerid, "gruz_load") == 1)
            {
				SCM(playerid, red, "Вы уронили ящик! Пойдите и возьмите его заново!");
				SetPVarInt(playerid, "gruz_load", 0);
				ClearAnimations(playerid);

				if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
		    		RemovePlayerAttachedObject(playerid, 1);

				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2350.7695, -258.4551, 2.7890, 2.0);
				pCheckpoint[playerid] = CP_GET_MESH;
			}
		}
		//если игрок это нажал, то мешон падает
    }
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 2355.0168, -261.2938, 2.7890))
        {
            if(GetPVarInt(playerid, "loader_job") == 1)
            {
                SPD(playerid, D_LOADER_JOB, DIALOG_STYLE_MSGBOX, "{"cblue"}Прораб | Грузчик", "{FFFFFF}Ты уверен что хочешь уволиться с работы грузчика?", "Да", "Нет");
            }
            else
            {
                new string[256];
                format(string, sizeof(string), "{FFFFFF}Привет! Не хочешь поработать?\n\nТебе нужно будет носить мешки.\nЗа 1 ящик ты будешь получать %d рублей!", (loader_zp));
                SPD(playerid, D_LOADER_JOB, DIALOG_STYLE_MSGBOX, "{"cblue"} Прораб | Грузчик", string, "Да", "Нет");
            }
        }
    }
	#if	defined	loader__OnPlayerKeyStateChange
		return loader__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange loader__OnPlayerKeyStateChange
#if	defined	loader__OnPlayerKeyStateChange
	forward loader__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_LOADER_JOB:
		{
		    if(GetPVarInt(playerid, "loader_job") == 1)
		    {
		        if(!response) return SCM(playerid, green, "Вы продолжили работать грузчиком!");
		        else
		        {
		            PayJob[playerid] = (kolvo_job[playerid]*loader_zp*XDay);
		            GiveMoney(playerid, PayJob[playerid], "Зарплата грузчика");
		            SaveAccounts(playerid);
		            DeletePVar(playerid, "loader_job");
		            
					DeletePVar(playerid, "gruz_load");

					if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
			    		RemovePlayerAttachedObject(playerid, 1);

					DisablePlayerCheckpoint(playerid);
					
					new string[256];
					format(string, sizeof(string), "Вы завершили работу! Вы получили {"cyellow"}%d {"cblue"}рублей за {"cyellow"}%d {"cblue"}перенесенных ящиков!", PayJob[playerid], kolvo_job[playerid]);
					SCM(playerid, blue, string);
					
     				PayJob[playerid] = 0;
		            kolvo_job[playerid] = 0;
		            ClearAnimations(playerid);
		            if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
		            else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
		        }
		    }
		    else
		    {
		        if(!response) return SCM(playerid, blue, "Вы отказались от работы грузчика!");
		        else
				{
				    SetPVarInt(playerid, "loader_job", 1);
				    PayJob[playerid] = 0;
				    kolvo_job[playerid] = 0;
				    
				    SetPlayerSkin(playerid, 254);
				    
					SCM(playerid, blue, "Вы начали работу грузчика!");
					SCM(playerid, yellow, "Направляйтесь к красному чекпоинту!");
					SCM(playerid, yellow, "После того, как закончите работу, встаньте на синий пикап одежды.");
					SCM(playerid, yellow, "Если Вы уйдёте далеко от места работы, то Ваша зарплата анулируется.");
					
					SetPlayerCheckpoint(playerid, 2350.7695,-258.4551,2.7890, 2.0);
					pCheckpoint[playerid] = CP_GET_MESH;
				}
		    }
		}
    }
	#if	defined	loader__OnDialogResponse
		return loader__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse loader__OnDialogResponse
#if	defined	loader__OnDialogResponse
	forward loader__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
		if(GetPVarInt(playerid, "loader_job") == 1)
		{
		    if(GetPVarInt(playerid, "gruz_load") == 1)
		    {
				SCM(playerid, red, "Вы уронили ящик! Пойдите и возьмите его заново!");
				SetPVarInt(playerid, "gruz_load", 0);
				ClearAnimations(playerid);

				if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
		    		RemovePlayerAttachedObject(playerid, 1);

				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2350.7695, -258.4551, 2.7890, 2.0);
				pCheckpoint[playerid] = CP_GET_MESH;
			}
		}
    }
    if(newstate == PLAYER_STATE_PASSENGER)
    {
		if(GetPVarInt(playerid, "loader_job") == 1)
		{
		    if(GetPVarInt(playerid, "gruz_load") == 1)
		    {
				SCM(playerid, red, "Вы уронили ящик! Пойдите и возьмите его заново!");
				SetPVarInt(playerid, "gruz_load", 0);
				ClearAnimations(playerid);

				if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
		    		RemovePlayerAttachedObject(playerid, 1);

				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2350.7695, -258.4551, 2.7890, 2.0);
				pCheckpoint[playerid] = CP_GET_MESH;
			}
		}
    }
    #if defined loader__OnPlayerStateChange
        return loader__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange loader__OnPlayerStateChange
#if	defined	loader__OnPlayerStateChange
	forward loader__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif


public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
	    case CP_GET_MESH:
	    {
  			ApplyAnimation(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
			SetPlayerAttachedObject(playerid, 1 ,3052, 1,0.11,0.36,0.0,0.0,90.0);
			SetPVarInt(playerid, "gruz_load", 1);
			
	        DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, 2322.2651,-264.3137,1.5114, 2.0);
			pCheckpoint[playerid] = CP_PUT_MESH;
			SCM(playerid, blue, "Вы подняли ящик! Теперь отнесите его на склад!");
	    }
	    case CP_PUT_MESH:
	    {
  			kolvo_job[playerid]++;
  			new string[128];
  			SCM(playerid, blue, "Вы доставили один ящик на склад!");
  			format(string, sizeof(string), "Всего ящиков перенесено: {"cyellow"}%d{"cblue"}!", kolvo_job[playerid]);
  			SCM(playerid, blue, string);
			SetPVarInt(playerid, "gruz_load", 0);
			ClearAnimations(playerid);
			
			if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
	    		RemovePlayerAttachedObject(playerid, 1);
			
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, 2350.7695, -258.4551, 2.7890, 2.0);
			pCheckpoint[playerid] = CP_GET_MESH;
	    }
    }
    #if defined loader__OnPlayerEnterCheckpoint
        return loader__OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerEnterCheckpoint
	#undef	OnPlayerEnterCheckpoint
#else
	#define	_ALS_OnPlayerEnterCheckpoint
#endif

#define	OnPlayerEnterCheckpoint loader__OnPlayerEnterCheckpoint
#if	defined	loader__OnPlayerEnterCheckpoint
	forward loader__OnPlayerEnterCheckpoint(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    if(GetPVarInt(playerid, "loader_job") == 1)
    {
        PayJob[playerid] = (kolvo_job[playerid]*loader_zp*XDay);
        GiveMoney(playerid, PayJob[playerid], "Зарплата грузчика");
		PayJob[playerid] = 0;
		kolvo_job[playerid] = 0;
		DeletePVar(playerid, "gruz_load");

		if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
    		RemovePlayerAttachedObject(playerid, 1);

		DisablePlayerCheckpoint(playerid);
    }
	#if defined loader__OnPlayerDisconnect
		return loader__OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else 
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect loader__OnPlayerDisconnect
#if defined loader__OnPlayerDisconnect
	forward loader__OnPlayerDisconnect(playerid, reason);
#endif


public OnPlayerUpdate(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 100.0, 2355.0168,-261.2938,2.7890))
	{
    	if(GetPVarInt(playerid, "loader_job") == 1)
	    {
	        PayJob[playerid] = (kolvo_job[playerid]*loader_zp*XDay);
	        GiveMoney(playerid, PayJob[playerid], "Зарплата грузчика");
			PayJob[playerid] = 0;
			kolvo_job[playerid] = 0;
			DeletePVar(playerid, "gruz_load");
			DeletePVar(playerid, "loader_job");
			if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
			else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);

			if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
	    		RemovePlayerAttachedObject(playerid, 1);

			DisablePlayerCheckpoint(playerid);
			SCM(playerid, red, "Вы ушли слишком далеко от места работы, поэтому вы были уволены!");
	    }
	}
	#if defined loader__OnPlayerUpdate
		return loader__OnPlayerUpdate(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate loader__OnPlayerUpdate
#if defined loader__OnPlayerUpdate
	forward loader__OnPlayerUpdate(playerid);
#endif