new taxi_price[MAX_PLAYERS];
new PlayerTimerTaxi[MAX_PLAYERS] = -1;



public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerInfo[playerid][pJob] == Job_Taxi && player_job_vehicle_arend[playerid] > 0) EndJobTaxi(playerid);
    #if defined taxi__OnPlayerDisconnect
        return taxi__OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect taxi__OnPlayerDisconnect
#if defined taxi__OnPlayerDisconnect
    forward taxi__OnPlayerDisconnect(playerid, reason);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_AREND_TAXI_CAR:
		{
		    if(!response) RemovePlayerFromVehicle(playerid);
		    else
		    {
		        if(PlayerInfo[playerid][pCash] < 200)
		        {
		            RemovePlayerFromVehicle(playerid);
		            return SCM(playerid, red, "У вас недостаточно денег!");
		        }

		        GiveMoney(playerid, -200, "Аренда машины таксиста");
				SPD(playerid, D_SET_TAXI_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Таксист | Стоимость проезда", "{"cblue"}Установите цену на проезд за 1 км.\nЦена должна быть не менее {"cyellow"}100 рублей {"cblue"} и не более {"cyellow"} 500 рублей{"cblue"}!", "Далее", "");
		    }
		}
		case D_SET_TAXI_PRICE:
		{
		    if(!response) SPD(playerid, D_SET_TAXI_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Таксист | Стоимость проезда", "{"cblue"}Установите цену на проезд за 1 км.\nЦена должна быть не менее {"cyellow"}100 рублей {"cblue"} и не более {"cyellow"} 500 рублей{"cblue"}!", "Далее", "");
			else
			{
			    if(!strlen(inputtext)) return SPD(playerid, D_SET_TAXI_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Таксист | Стоимость проезда", "{"cblue"}Установите цену на проезд за 1 км.\nЦена должна быть не менее {"cyellow"}100 рублей {"cblue"} и не более {"cyellow"} 500 рублей{"cblue"}!", "Далее", "");
				if(!IsNumeric(inputtext)) return SPD(playerid, D_SET_TAXI_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Таксист | Стоимость проезда", "{"cblue"}Установите цену на проезд за 1 км.\nЦена должна быть не менее {"cyellow"}100 рублей {"cblue"} и не более {"cyellow"} 500 рублей{"cblue"}!", "Далее", "");
				if(strval(inputtext) < 100 || strval(inputtext) > 500) return SPD(playerid, D_SET_TAXI_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Таксист | Стоимость проезда", "{"cblue"}Установите цену на проезд за 1 км.\nЦена должна быть не менее {"cyellow"}100 рублей {"cblue"} и не более {"cyellow"} 500 рублей{"cblue"}!", "Далее", "");

				taxi_price[playerid] = strval(inputtext);

				SCM(playerid, blue, "Вы успешно арендовали транспорт!");
				new string[128];
				format(string, sizeof(string), "Вы будете получать {"cyellow"}%d рублей{"cblue"} за 1 км проезда пассажира!", taxi_price[playerid]);
				SCM(playerid, blue, string);

				SetPVarInt(playerid, "taxi_job", 1);
				player_job_vehicle_arend[playerid] = GetPlayerVehicleID(playerid);

				format(string, sizeof(string), "{15a6f8}ООО << UNIGVA Taxi >>\n{FFFFFF}Стоимость проезда: {15a6f8}%d руб/км", taxi_price[playerid]);
				vehicle[player_job_vehicle_arend[playerid]][veh_label] = CreateDynamic3DTextLabel(string, 0xFFFFFFFF, 0.0, 0.0, 1.5, 20.0, _, player_job_vehicle_arend[playerid]);
				vehicle[player_job_vehicle_arend[playerid]][veh_arend] = 1;

			}
		}
    }
	#if	defined	taxi__OnDialogResponse
		return taxi__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse taxi__OnDialogResponse
#if	defined	taxi__OnDialogResponse
	forward taxi__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TAXI_CAR][0] <= vehicleid <= job_car[TAXI_CAR][1])
        {
            if(PlayerInfo[playerid][pJob] != Job_Taxi)
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "Вы не таксист!");
            }

            if(vehicle[vehicleid][veh_arend] != 0 && vehicleid != player_job_vehicle_arend[playerid])
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "Вы не можете использовать этот транспорт в данный момент!");
            }
        }
	}
	#if	defined	taxi__OnPlayerEnterVehicle
		return taxi__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle taxi__OnPlayerEnterVehicle
#if	defined	taxi__OnPlayerEnterVehicle
	forward taxi__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	new vehicleid = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER)
    {
        if(job_car[TAXI_CAR][0] <= vehicleid <= job_car[TAXI_CAR][1])
        {
            if(PlayerInfo[playerid][pJob] != Job_Taxi)
            {
                RemovePlayerFromVehicle(playerid);
                return SCM(playerid, red, "Вы не таксист!");
            }

            if(vehicle[vehicleid][veh_arend] != 0 && vehicleid != player_job_vehicle_arend[playerid])
            {
                RemovePlayerFromVehicle(playerid);
                return SCM(playerid, red, "Вы не можете использовать этот транспорт в данный момент!");
            }

            if(vehicleid != player_job_vehicle_arend[playerid])
            {
                ShowPlayerDialog
                (
                    playerid, D_AREND_TAXI_CAR, DIALOG_STYLE_MSGBOX,
                    "{"cblue"}Таксист | Аренда транспорта",
                    "{FFFFFF}Аренда автомобиля составит {"cblue"}200 рублей{FFFFFF}.\nВы готовы арендовать транспорт в данный момент времени?",
                    "Да", "Нет"
                );
            }
        }
		if(GetPlayerVehicleID(playerid) == player_job_vehicle_arend[playerid])
		{
		    if(GetPVarInt(playerid, "EndJobTaxi") == 1)
		    {
		        SCM(playerid, green, "Вы вернулись в транспорт! Продолжайте работу!");
				KillTimer(player_end_job_timer[playerid]);
				DeletePVar(playerid, "EndJobTaxi");
			}
		}
    }
    if(oldstate == PLAYER_STATE_DRIVER)
    {
  		if(player_job_vehicle_arend[playerid] != -1 && PlayerInfo[playerid][pJob] == Job_Taxi)
		{
		    if(GetPVarInt(playerid, "EndJobTaxi") == 1) return 1;
			player_end_job_timer[playerid] = SetTimerEx("EndJobTaxi", 15000, false, "i", playerid);
			SetPVarInt(playerid, "EndJobTaxi", 1);

			SCM(playerid, 0xFF6600FF, "У Вас есть 15 секунд чтобы вернуться в транспорт");
		}
    }
	if(newstate == PLAYER_STATE_PASSENGER)
	{
        if(job_car[TAXI_CAR][0] <= vehicleid <= job_car[TAXI_CAR][1])
        {
			if(vehicle[vehicleid][veh_arend] != 1)
			{
				RemovePlayerFromVehicle(playerid);
				return SCM(playerid, red, "В данный момент данное такси не перевозит людей!");
			}

			foreach(new i : Player)
			{
				if(vehicleid == player_job_vehicle_arend[i])
				{
					if(PlayerInfo[playerid][pCash] < taxi_price[i])
					{
						RemovePlayerFromVehicle(playerid);
						return SCM(playerid, red, "У вас недостаточно денег!");
					}
					else 
					{
						new string[128];
						format(string, sizeof(string), "Вы начали поездку на такси. Ваш водитель %s. Вы будете платить %d рублей за 1 км!", PlayerInfo[i][pName], taxi_price[i]);
						SCM(playerid, blue, string);

						format(string, sizeof(string), "Ваш новый пассажир %s", PlayerInfo[playerid][pName]);
						SCM(i, blue, string);
						PlayerTimerTaxi[playerid] = SetTimerEx("PublicTimerTaxi", 15000, true, "i", playerid);
					}
				}
			}
        }
	}
	if(oldstate == PLAYER_STATE_PASSENGER)
	{
		if(PlayerTimerTaxi[playerid] > 0)
		{
			if(vehicle[vehicleid][veh_arend] != 1) return 1;

			SCM(playerid, green, "Вы завершили поездку на такси!");
			KillTimer(PlayerTimerTaxi[playerid]);
			PlayerTimerTaxi[playerid] = -1;
			foreach(new j : Player)
			{
				if(vehicleid == player_job_vehicle_arend[j])
				{
					new string[128];
					format(string, sizeof(string), "Пассажир %s вышел из авто и завершил поездку!");
					SCM(j, green, string);
				}
			}
		}
	}
    #if defined taxi__OnPlayerStateChange
        return taxi__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange taxi__OnPlayerStateChange
#if	defined	taxi__OnPlayerStateChange
	forward taxi__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

publics EndJobTaxi(playerid)
{
	SCM(playerid, blue, "Вы не успели сесть в транспорт!");

	DeletePVar(playerid, "taxi_job");
	DeletePVar(playerid, "EndJobTaxi");
	
	DestroyDynamic3DTextLabel(vehicle[player_job_vehicle_arend[playerid]][veh_label]);
	SetVehicleToRespawn(player_job_vehicle_arend[playerid]);
	
	vehicle[player_job_vehicle_arend[playerid]][veh_arend] = 0;
	taxi_price[playerid] = -1;
	player_job_vehicle_arend[playerid] = -1;

	return 1;
}

publics PublicTimerTaxi(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
	{
		KillTimer(PlayerTimerTaxi[playerid]);
		return PlayerTimerTaxi[playerid] = -1;
	}

	foreach(new i : Player)
	{
		if(GetPlayerVehicleID(playerid) == player_job_vehicle_arend[i])
		{
			if(PlayerInfo[playerid][pCash] < taxi_price[i])
			{
				new string[128];
				format(string, sizeof(string), "У вашего клиента закончились деньги!");
				SCM(i, blue, string);

				format(string, sizeof(string), "У вас закончились деньги!");
				SCM(playerid, blue, string);
				return RemovePlayerFromVehicle(playerid);
			}
			if(SpeedVehicle(playerid) > 40)
			{
				GiveMoney(playerid, -taxi_price[i], "Проезд в такси");
				GiveMoney(i, taxi_price[i], "Работа таксиста");
			}
			else if(SpeedVehicle(playerid) < 5)
			{
				continue;
			}
			else
			{
				GiveMoney(playerid, floatround(-taxi_price[i]/2, floatround_round), "Проезд в такси");
				GiveMoney(i, floatround(taxi_price[i], floatround_round), "Работа таксиста");	
			}
		}
	}
	return 1;
}