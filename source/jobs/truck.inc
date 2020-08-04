new TruckTimer[MAX_PLAYERS];
new TruckGetGruzTimer[MAX_PLAYERS];
new TruckPutGruzTimer[MAX_PLAYERS];

new shlak_truck;
new bool: shlak_truck_status = false; 

new arend_truck = 0;

public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerInfo[playerid][pJob] == Job_Truck && player_job_vehicle_created[playerid] > 0) EndJobTrucker(playerid);
    #if defined truck__OnPlayerDisconnect
        return truck__OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect truck__OnPlayerDisconnect
#if defined truck__OnPlayerDisconnect
    forward truck__OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1754.8612,2251.7861,15.8602))
        {
			if(PlayerInfo[playerid][pJob] != Job_Truck) return SCM(playerid, red, "Вы не работаете Дальнобойщиком!");
			if(player_job_vehicle_created[playerid] != -1) return SCM(playerid, red, "Вы уже арендуете транспорт!");
			if(arend_truck == 1) return SCM(playerid, red, "Парковка занята! Подождите немного пожалуйста.");

			SPD(playerid, D_AREND_TRUCK, DIALOG_STYLE_LIST, "{"cblue"}Аренда фуры", "\
			{"cblue"}1. {FFFFFF}ЗИЛ\t\t{"cblue"}(0 уровень и 800 рублей)\n\
			{"cblue"}2. {FFFFFF}КАМАЗ\t{"cblue"}(5 уровень и 2000 рублей)\n\
			{"cblue"}3. {FFFFFF}КАЗ\t\t{"cblue"}(10 уровень и 4500 рублей)", "Арендовать", "Закрыть");
        }
    }
	if(newkeys == 2)
	{
		if(IsPlayerInRangeOfPoint(playerid, 20.0, 1774.48, 2243.77, 15.60))
		{
			if(PlayerInfo[playerid][bAdmin] > 0 || PlayerInfo[playerid][pJob] == Job_Truck)
			{
				switch(shlak_truck_status)
				{
					case false:
					{
						MoveObject(shlak_truck, 1774.48, 2243.77, 15.60, 5000.2,  0.00, 0.00, 0.00);
						shlak_truck_status = true;
					}
					case true:
					{
						MoveObject(shlak_truck, 1774.48, 2243.77, 15.60,  5000.2,  0.00, -90.00, 0.00);
						shlak_truck_status = false;						
					}
				}
			}
		}
	}
	#if	defined	truck__OnPlayerKeyStateChange
		return truck__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange truck__OnPlayerKeyStateChange
#if	defined	truck__OnPlayerKeyStateChange
	forward truck__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_AREND_TRUCK:
		{
		    if(!response) return 1;
		    else
		    {
				switch(listitem)
				{
				    case 0:
				    {
						if(arend_truck == 1) return SCM(playerid, red, "Парковка занята! Подождите немного пожалуйста.");
				        if(PlayerInfo[playerid][pTruckLVL] < 0) return SCM(playerid, red, "Ваш навык дальнобойщика мал!");
				        if(PlayerInfo[playerid][pCash] < 800) return SCM(playerid, red, "У вас не достаточно денег!");
				        
						SCM(playerid, green, "Вы успешно арендовали фуру!");
						SCM(playerid, green, "У вас есть 45 секунд, что б сесть в транспорт!");
						SetPlayerRaceCheckpoint(playerid, 0, 1782.5551,2298.8601,16.4054, 1782.5551,2298.8601,16.4054, 10.0);
						pCheckpoint[playerid] = CP_SIT_IN_TRUCK;
						TruckTimer[playerid] = 45;
						
						player_job_vehicle_created[playerid] = CreateVehicle(403,1782.5551,2298.8601,16.4054,90.0887,7,0, -1);
						player_job_vehicle_created_2[playerid] = CreateVehicle(450,1793.3622,2298.8503,16.3607,89.6443,1,1, -1);
						arend_truck = 1;
						GiveMoney(playerid, -800, "Аренда фуры");
						SetTimer("Arend_Truck", 45000, false);
				    }
				    case 1:
				    {
						if(arend_truck == 1) return SCM(playerid, red, "Парковка занята! Подождите немного пожалуйста.");
        				if(PlayerInfo[playerid][pTruckLVL] < 5) return SCM(playerid, red, "Ваш навык дальнобойщика мал!");
				        if(PlayerInfo[playerid][pCash] < 2000) return SCM(playerid, red, "У вас не достаточно денег!");
				        
						SCM(playerid, green, "Вы успешно арендовали фуру!");
						SCM(playerid, green, "У вас есть 45 секунд, что б сесть в транспорт!");
						TruckTimer[playerid] = 45;
						SetPlayerRaceCheckpoint(playerid, 0, 1782.5551,2298.8601,16.4054, 1782.5551,2298.8601,16.4054, 10.0);
						pCheckpoint[playerid] = CP_SIT_IN_TRUCK;
						player_job_vehicle_created[playerid] = CreateVehicle(514,1782.5551,2298.8601,16.4054,90.0887,79,0, -1);
						player_job_vehicle_created_2[playerid] = CreateVehicle(450,1793.3622,2298.8503,16.3607,89.6443,1,1, -1);
						arend_truck = 1;
						GiveMoney(playerid, -2000, "Аренда фуры");
						SetTimer("Arend_Truck", 45000, false);
				    }
				    case 2:
				    {
						if(arend_truck == 1) return SCM(playerid, red, "Парковка занята! Подождите немного пожалуйста.");
        				if(PlayerInfo[playerid][pTruckLVL] < 10) return SCM(playerid, red, "Ваш навык дальнобойщика мал!");
				        if(PlayerInfo[playerid][pCash] < 4500) return SCM(playerid, red, "У вас не достаточно денег!");
				        
						SCM(playerid, green, "Вы успешно арендовали фуру!");
						SCM(playerid, green, "У вас есть 45 секунд, что б сесть в транспорт!");
						TruckTimer[playerid] = 45;
						SetPlayerRaceCheckpoint(playerid, 0, 1782.5551,2298.8601,16.4054, 1782.5551,2298.8601,16.4054, 10.0);
						pCheckpoint[playerid] = CP_SIT_IN_TRUCK;
						player_job_vehicle_created[playerid] = CreateVehicle(515,1782.5551,2298.8601,16.4054,90.0887,1,0, -1);
						player_job_vehicle_created_2[playerid] = CreateVehicle(450,1793.3622,2298.8503,16.3607,89.6443,1,1, -1);
						arend_truck = 1;
						GiveMoney(playerid, -4500, "Аренда фуры");
						SetTimer("Arend_Truck", 45000, false);
				    }
				}
		    }
		}
    }
	#if	defined	truck__OnDialogResponse
		return truck__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse truck__OnDialogResponse
#if	defined	truck__OnDialogResponse
	forward truck__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(GetPVarInt(playerid, "GoToPricep") == 1)
	{
	    if(!IsTrailerAttachedToVehicle(player_job_vehicle_created[playerid])) return GoToPricep(playerid);
	    
		if(pCheckpoint[playerid] == CP_TRUCK_GET_GRUZ)
		{
		    SCM(playerid, green, "Вы подобрали прицеп, езжайте на загрузку!");
		    SetPlayerRaceCheckpoint(playerid, 0, 2738.9680,-2271.9436,17.9269, 2738.9680,-2271.9436,17.9269, 5.0);
		}
		else if(pCheckpoint[playerid] == CP_TRUCK_PUT_GRUZ)
		{
		    SCM(playerid, green, "Вы подобрали прицеп, езжайте на разгрузку!");
		    SetPlayerRaceCheckpoint(playerid, 0, 2973.5332,2214.6572,6.8247, 2973.5332,2214.6572,6.8247, 5.0);
		}
		DeletePVar(playerid, "GoToPricep");
		return 1;
	}
    switch(pCheckpoint[playerid])
    {
		case CP_SIT_IN_TRUCK:
		{
			return 1;
		}
		case CP_TRUCK_GET_GRUZ:
		{
		    if(!IsTrailerAttachedToVehicle(player_job_vehicle_created[playerid])) return GoToPricep(playerid);
		    DisablePlayerRaceCheckpoint(playerid);
		    TruckGetGruzTimer[playerid] = 10;
		}
		case CP_TRUCK_PUT_GRUZ:
		{
		    if(!IsTrailerAttachedToVehicle(player_job_vehicle_created[playerid])) return GoToPricep(playerid);
		    DisablePlayerRaceCheckpoint(playerid);
		    TruckPutGruzTimer[playerid] = 100;
		}	
    }
    #if defined trucker_OPERC
        return trucker_OPERC(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterRaceCheckpoin || defined _ALS_OnPlayerEnterRaceCP
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnterRaceCheckpoin
	#define _ALS_OnPlayerEnterRaceCP
#endif

#define OnPlayerEnterRaceCheckpoint trucker_OPERC
#if defined trucker_OPERC
    forward trucker_OPERC(playerid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
		foreach(new i : Player)
		{
			if(GetPlayerVehicleID(playerid) == player_job_vehicle_created[i] && GetPlayerVehicleID(playerid) != player_job_vehicle_created[playerid])
			{
				RemovePlayerFromVehicle(playerid);
				return SCM(playerid, red, "У вас нет ключей от этого транспорта!");
			}
		}
		if(GetPlayerVehicleID(playerid) == player_job_vehicle_created[playerid])
		{
		    if(pCheckpoint[playerid] == CP_SIT_IN_TRUCK)
		    {
			    TruckTimer[playerid] = 0;
			    SCM(playerid, green, "Вы сели в фуру, берите прицеп и отправляйтесь на загрузку!");
			    SetPlayerRaceCheckpoint(playerid, 0, 2738.9680,-2271.9436,17.9269, 2738.9680,-2271.9436,17.9269, 5.0);
			    pCheckpoint[playerid] = CP_TRUCK_GET_GRUZ;
		    }
		    if(GetPVarInt(playerid, "EndJobTrucker") == 1)
		    {
		        SCM(playerid, green, "Вы вернулись в транспорт! Продолжайте работу!");
				KillTimer(player_end_job_timer[playerid]);
				DeletePVar(playerid, "EndJobTrucker");
			}
		}
    }
    if(oldstate == PLAYER_STATE_DRIVER)
    {
		if(player_job_vehicle_created[playerid] != -1 && PlayerInfo[playerid][pJob] == Job_Truck)
		{
		    if(GetPVarInt(playerid, "EndJobTrucker") == 1) return 1;
			player_end_job_timer[playerid] = SetTimerEx("EndJobTrucker", 15000, false, "i", playerid);
			SetPVarInt(playerid, "EndJobTrucker", 1);

			SCM(playerid, 0xFF6600FF, "У Вас есть 15 секунд чтобы вернуться в транспорт");
		}
    }
    #if defined truck__OnPlayerStateChange
        return truck__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange truck__OnPlayerStateChange
#if	defined	truck__OnPlayerStateChange
	forward truck__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

publics PlayerSecondTimer(playerid)
{

	if(TruckTimer[playerid] > 0)
	{
		TruckTimer[playerid]--;
		new string[64];
		format(string, sizeof(string), "~w~Time: ~r~%d ~w~sek", TruckTimer[playerid]);
		GameTextForPlayer(playerid, string, 1000, 4);
		
		if(TruckTimer[playerid] == 0)
		{
			EndJobTrucker(playerid);
		}
	}
	if(TruckGetGruzTimer[playerid] >= 10 && TruckGetGruzTimer[playerid] < 100)
	{
		if(!IsTrailerAttachedToVehicle(player_job_vehicle_created[playerid])) return GoToPricep(playerid);
		if(!IsPlayerInRangeOfPoint(playerid, 20.0, 2738.9680,-2271.9436,17.9269)) return 1;
		TruckGetGruzTimer[playerid] += 10;
		
		new string[64];
		format(string, sizeof(string), "~w~LOAD: ~g~%d", TruckGetGruzTimer[playerid]);
		GameTextForPlayer(playerid, string, 1000, 4);
		
		if(TruckGetGruzTimer[playerid] == 100)
		{
			SCM(playerid, green, "Вы загрузились! Езжайте на разгрузку!");
			SetPlayerRaceCheckpoint(playerid, 0, 2973.5332,2214.6572,6.8247, 2973.5332,2214.6572,6.8247, 5.0);
			pCheckpoint[playerid] = CP_TRUCK_PUT_GRUZ;
		}
	}
	if(TruckPutGruzTimer[playerid] > 0)
	{
		if(!IsTrailerAttachedToVehicle(player_job_vehicle_created[playerid])) return GoToPricep(playerid);
		if(!IsPlayerInRangeOfPoint(playerid, 15.0, 2973.5332,2214.6572,6.8247)) return 1;
		TruckPutGruzTimer[playerid] -= 10;

		new string[128];
		format(string, sizeof(string), "~w~LOAD: ~g~%d", TruckPutGruzTimer[playerid]);
		GameTextForPlayer(playerid, string, 1000, 4);

		if(TruckPutGruzTimer[playerid] == 0)
		{
			new pay = (1000*XDay)+(200*PlayerInfo[playerid][pTruckLVL]);
			SCM(playerid, green, "Вы разгрузились! Езжайте на загрузку!");
			format(string, sizeof(string), "Вы доставили груз и получили %d рублей", pay);
			SCM(playerid, green, string);
			GiveMoney(playerid, pay, "Зарплата дальнобойщика!");
			PlayerInfo[playerid][pTruckEXP]++;
			if(PlayerInfo[playerid][pTruckEXP] >= 30)
			{
				PlayerInfo[playerid][pTruckLVL]++;
				PlayerInfo[playerid][pTruckEXP] = 0;
				SCM(playerid, green, "Поздравляем! Ваш уровень дальнобойщика повышен!");
			}
			SaveAccounts(playerid);
			SetPlayerRaceCheckpoint(playerid, 0, 2738.9680,-2271.9436,17.9269, 2738.9680,-2271.9436,17.9269, 5.0);
			pCheckpoint[playerid] = CP_TRUCK_GET_GRUZ;
		}
	}

    #if defined truck__PlayerSecondTimer
        return truck__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer truck__PlayerSecondTimer
#if	defined	truck__PlayerSecondTimer
	forward truck__PlayerSecondTimer(playerid); 
#endif



publics EndJobTrucker(playerid)
{
	SCM(playerid, red, "К сожалению, вы не успели сесть в грузовикк!");
	
	DestroyVehicle(player_job_vehicle_created[playerid]);
	DestroyVehicle(player_job_vehicle_created_2[playerid]);
	DisablePlayerRaceCheckpoint(playerid);
	player_job_vehicle_created[playerid] = -1;
	player_job_vehicle_created_2[playerid] = -1;
	DeletePVar(playerid, "GoToPricep");
	DeletePVar(playerid, "EndJobTrucker");
	KillTimer(player_end_job_timer[playerid]);
	return 1;
}
publics GoToPricep(playerid)
{
	SCM(playerid, red, "Вы приехали без прицепа, поетому отправляйтесь за ним обратно!");
	new Float:x, Float:y, Float:z;
	GetVehiclePos(player_job_vehicle_created_2[playerid], x, y, z);
	SetPlayerRaceCheckpoint(playerid, 0, x, y, z, x, y, z, 5.0);
	SetPVarInt(playerid, "GoToPricep", 1);
	return 1;
}
publics Arend_Truck()
{
	arend_truck = 0;
}

CMD:jskill(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Дальнобойщики:\n\nУровень: {"cblue"}%d\n{FFFFFF}Рейсов: {"cblue"}%d/30", PlayerInfo[playerid][pTruckLVL], PlayerInfo[playerid][pTruckEXP]);
	SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Рабочие навыки", string, "Закрыть", "");
	return 1;
}