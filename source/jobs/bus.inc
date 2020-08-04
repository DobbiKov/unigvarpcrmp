new bus_route_cost[MAX_PLAYERS];
new bus_route_step[MAX_PLAYERS];

enum
	E_ROUTE
{
	Float: route_x,
	Float: route_y,
	Float: route_z,
	bool:  route_stop
};
new
	Float: route_pos[][E_ROUTE] =
	{
		{1801.0515,2508.2700,15.6717, true},
        {1791.6050,2471.5635,15.7156, false},
        {1833.3037,2385.2188,15.9530, false},
        {1886.5216,2279.0344,15.9526, false},
        {1886.3972,2168.0564,15.8542, false},
        {1878.8579,2099.5410,15.8459, true},
        {1910.5781,2051.6101,15.8734, false},
        {1961.1786,2001.7177,15.8913, false},
        {1976.8618,1901.0223,15.5280, false},
        {2023.0764,1899.0962,15.6600, true},
        {2136.8369,1903.7219,15.8837, false},
        {2316.1770,1904.6399,15.9067, false},
        {2362.4263,1939.8374,15.9051, false},
        {2358.5034,1973.0045,15.8702, true},
        {2351.7576,2001.2878,15.9900, false},
        {2357.1213,1932.8732,15.9149, false},
        {2470.3528,1894.7855,16.2636, false},
        {2680.7742,1895.1635,15.9766, false},
        {2737.5349,1875.0729,16.0974, false},
        {2703.5750,1658.3779,16.7571, false},
        {2546.7253,1460.8881,11.6498, false},
        {2636.0845,1219.6470,22.4068, false},
        {2719.6255,1021.7820,20.4733, false},
        {2831.7625,777.6901,31.2930, false},
        {2903.5720,437.2806,22.0140, false},
        {2903.4124,152.8307,15.5441, false},
        {2889.8855,-241.2037,23.9473, false},
        {2767.9658,-455.3382,23.9377, false},
        {2744.2139,-785.6935,23.9381, false},
        {2744.0300,-1134.7936,23.5559, false},
        {2743.4590,-1318.3582,23.5559, false},
        {2739.2788,-1445.8728,23.8279, false},
        {2644.6636,-1510.3229,23.4432, true},
        {2601.5439,-1592.1255,23.6343, false},
        {2587.3894,-1714.6316,21.9417, false},
        {2582.4587,-1783.7689,21.9640, true},
        {2586.8335,-1885.1345,21.8156, false},
        {2587.1414,-2091.8450,21.8156, false},
        {2564.5798,-2146.2324,21.8184, false},
        {2521.5134,-2144.6091,21.9766, true},
        {2435.3779,-2147.3047,21.8135, false},
        {2277.9097,-2147.0125,21.8135, false},
        {2245.8232,-2111.3550,21.9619, true},
        {2273.3562,-2033.6696,21.8650, false},
        {2293.3198,-1897.7233,21.8291, false},
        {2293.4355,-1790.4225,21.8135, false},
        {2186.8650,-1744.8185,21.2441, false},
        {2097.6477,-1787.7643,18.8135, false},
        {2089.4822,-1919.8475,18.8125, false},
        {2108.5132,-2022.5669,18.8125, false},
        {2178.7024,-1996.2850,18.8125, false},
        {2207.8208,-1974.6206,18.8125, true},
        {2112.6873,-1800.8063,18.8135, false},
        {2184.9478,-1760.9661,21.0260, false},
        {2250.5879,-1761.6018,21.8108, false},
        {2291.3987,-1717.5364,21.8135, false},
        {2295.7251,-1632.9285,22.7659, false},
        {2409.6667,-1529.9893,23.5976, false},
        {2558.7561,-1529.8271,23.6076, false},
        {2645.8359,-1529.9340,23.6219, false},
        {2740.7605,-1480.8304,23.4903, true},
        {2750.8413,-1396.8623,23.8201, false},
        {2750.7507,-1264.9200,23.5559, false},
        {2752.4170,-1080.9309,23.5559, false},
        {2750.7681,-842.8021,23.9346, false},
        {2751.4639,-552.9870,23.9352, false},
        {2856.6899,-318.3055,25.9011, false},
        {2910.0488,-70.1451,25.3360, false},
        {2909.0413,181.5547,14.2389, false},
        {2908.6702,605.1785,32.1032, false},
        {2853.9673,752.7320,31.8329, false},
        {2733.1665,990.6226,23.0470, false},
        {2640.2412,1238.8510,21.8262, true},
        {2562.5679,1387.5319,13.3353, false},
        {2680.7256,1606.7900,17.0908, false},
        {2752.1926,1851.2054,15.8989, false},
        {2764.0742,2054.1577,17.7797, true},
        {2766.1252,2202.0085,17.5104, false},
        {2737.1406,2451.5222,15.5994, false},
        {2656.6418,2798.3997,19.7598, false},
        {2401.3120,2955.1396,21.7077, false},
        {2131.6875,2962.2551,11.5054, false},
        {2050.8208,2866.2129,13.7474, false},
        {1897.7421,2662.0212,15.2038, false},
        {1753.8750,2507.2649,15.9631, false},
        {1787.7440,2520.7297,15.6639, false}
	};


public OnPlayerDisconnect(playerid, reason)
{
	if(player_job_vehicle_arend[playerid] != -1 && PlayerInfo[playerid][pJob] == Job_Bus)
	{
		EndJobEndJob(playerid);
	} 
    #if defined bus__OnPlayerDisconnect
        return bus__OnPlayerDisconnect(playerid, reason);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else   
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect bus__OnPlayerDisconnect
#if defined bus__OnPlayerDisconnect
    forward bus__OnPlayerDisconnect(playerid, reason);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_AREND_BUS: 
		{
		    if(!response) return RemovePlayerFromVehicle(playerid);
		    else
		    {
		        if(PlayerInfo[playerid][pCash] < 200)
		        {
		            SCM(playerid, red, "У вас не достаточно денег!");
		            return RemovePlayerFromVehicle(playerid);
		        }
		        GiveMoney(playerid, -200, "Аренда автобуса");
				SPD(playerid, D_AREND_BUS_SET, DIALOG_STYLE_INPUT, "{"cblue"}Автобус | Цена за проезд", "{FFFFFF}Установите цену за проезд.\nЦена должна быть от {"cblue"}0, до 200 рублей{FFFFFF}!", "Далее", "");
		    }
		}
		case D_AREND_BUS_SET:
		{
		    if(response)
		    {
				new vehicleid = GetPlayerVehicleID(playerid);

				if(!(job_car[BUS_CAR][0] <= vehicleid <= job_car[BUS_CAR][1])) return 1;

				new route_cost = strval(inputtext);

				if(!(0 <= route_cost <= 200) || !IsNumeric(inputtext)) return SPD(playerid, D_AREND_BUS_SET, DIALOG_STYLE_INPUT, "{"cblue"}Автобус | Цена за проезд", "{FFFFFF}Установите цену за проезд.\nЦена должна быть от {"cblue"}0, до 200 рублей{FFFFFF}!", "Далее", "");
				
				player_job_vehicle_arend[playerid] = vehicleid;

				vehicle[vehicleid][veh_arend] = 1;
				
				bus_route_cost[playerid] = route_cost;
				bus_route_step[playerid] = 0;
				PayJob[playerid] = 0;
				
				SCM(playerid, blue, "Вы успешно арендовали автобус, отправляйтесь на маршрут!");
				SCM(playerid, blue, "Что б завешить рабочий день, введите команду: {"cyellow"}/end");

				new fmt_msg[90];

				format(fmt_msg, sizeof fmt_msg, "{"cblue"}Батырево - Южный\n{FFFFFF}Стоимость проезда: {"cblue"}%d руб", bus_route_cost[playerid]);
				vehicle[vehicleid][veh_label] = CreateDynamic3DTextLabel(fmt_msg, 0xFFFFFFFF, 0.0, 0.0, 1.5, 20.0, _, vehicleid);
				NextRouteCP(playerid);
		    }
		}
		case D_CMD_END_BUS:
		{
		    if(!response) return 1;
		    else
		    {
		        EndJobEndJob(playerid);
		    }
		}
    }
	#if	defined	bus__OnDialogResponse
		return bus__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse bus__OnDialogResponse
#if	defined	bus__OnDialogResponse
	forward bus__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterRaceCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
	    case CP_BUS_NEXT:
	    {
			new route_step = bus_route_step[playerid] - 1;
			
			if(bus_route_step[playerid] >= 85) bus_route_step[playerid] = 0;

			if(IsPlayerInRangeOfPoint(playerid, 3.5, route_pos[route_step][route_x], route_pos[route_step][route_y], route_pos[route_step][route_z]))
			{
				if(route_pos[route_step][route_stop])
				{
					DisablePlayerRaceCheckpoint(playerid);
					GameTextForPlayer(playerid, "~r~Stop", 4000, 1);
					SCM(playerid, blue, "Остановка. Ждите пассажиров");

					ProxDetector(30.0, playerid, "Маршрутка по маршруту Южный - Батырево отправляется через 10 секунд", 0x669999FF, 0x669999FF, 0x669999FF, 0x669999FF, 0x669999FF);

					SetTimerEx("NextRouteCP", 10000, false, "i", playerid);
				}
				else
				{
				    DisablePlayerRaceCheckpoint(playerid);
					PayJob[playerid] += (random(30) + 20);
					NextRouteCP(playerid);
				}
			}
	        return 1;
		}
    }
    #if defined bus_OPERC
        return bus_OPERC(playerid);
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

#define OnPlayerEnterRaceCheckpoint bus_OPERC
#if defined bus_OPERC
    forward bus_OPERC(playerid);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
		if(job_car[BUS_CAR][0] <= vehicleid <= job_car[BUS_CAR][1])
		{
			if(PlayerInfo[playerid][pJob] != Job_Bus)
			{
				ClearAnimations(playerid, true);
				return SCM(playerid, red, "Вы не водитель автобуса!");
			}

			if(vehicle[vehicleid][veh_arend] != 0 && vehicleid != player_job_vehicle_arend[playerid])
			{
				ClearAnimations(playerid, true);
				return SCM(playerid, red, "Вы не можете использовать этот транспорт в данный момент!");
			}
		}
	}
	#if	defined	bus__OnPlayerEnterVehicle
		return bus__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle bus__OnPlayerEnterVehicle
#if	defined	bus__OnPlayerEnterVehicle
	forward bus__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
		new vehicleid = GetPlayerVehicleID(playerid);
		if(job_car[BUS_CAR][0] <= vehicleid <= job_car[BUS_CAR][1])
		{
			if(vehicleid != player_job_vehicle_arend[playerid])
			{
				ShowPlayerDialog
				(
					playerid, D_AREND_BUS, DIALOG_STYLE_MSGBOX,
					"{"cblue"}Автобус | Аренда проезда",
					"{FFFFFF}Аренда Автобуса составит {"cblue"}200 рублей{FFFFFF}.\nВы готовы арендовать транспорт в данный момент времени?",
					"Да", "Нет"
				);
			}
		}
		if(GetPlayerVehicleID(playerid) == player_job_vehicle_arend[playerid])
		{
		    if(GetPVarInt(playerid, "EndJobEndJob") == 1)
		    {
		        SCM(playerid, green, "Вы вернулись в транспорт! Продолжайте работу!");
				KillTimer(player_end_job_timer[playerid]);
				DeletePVar(playerid, "EndJobEndJob");
			}
		}
    }
    if(oldstate == PLAYER_STATE_DRIVER)
    {
  		if(player_job_vehicle_arend[playerid] != -1 && PlayerInfo[playerid][pJob] == Job_Bus)
		{
		    if(GetPVarInt(playerid, "EndJobEndJob") == 1) return 1;
			player_end_job_timer[playerid] = SetTimerEx("EndJobEndJob", 15000, false, "i", playerid);
			SetPVarInt(playerid, "EndJobEndJob", 1);

			SCM(playerid, 0xFF6600FF, "У Вас есть 15 секунд чтобы вернуться в транспорт");
		}
    }
    if(newstate == PLAYER_STATE_PASSENGER)
    {
	    foreach(new i : Player)
	    {
			if(GetPlayerVehicleID(playerid) == player_job_vehicle_arend[i])
			{
			    if(PlayerInfo[playerid][pCash] < bus_route_cost[i])
			    {
			        SCM(playerid, red, "У вас не достаточно денег!");
			        return RemovePlayerFromVehicle(playerid);
			    }
			    GiveMoney(i, bus_route_cost[i], "Проезд в маршрутке");
			    GiveMoney(playerid, -bus_route_cost[i], "Проезд в маршрутке");
			}
	    }
    }
    #if defined bus__OnPlayerStateChange
        return bus__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange bus__OnPlayerStateChange
#if	defined	bus__OnPlayerStateChange
	forward bus__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

publics EndJobEndJob(playerid)
{
	vehicle[player_job_vehicle_arend[playerid]][veh_arend] = 0;
	
	PlayerInfo[playerid][pBCash] += PayJob[playerid];
	
	if(GetPVarInt(playerid, "EndJobEndJob") == 1) SCM(playerid, red, "К сожалению, вы не успели сесть транспорт!");

	new string[128];
	format(string, sizeof(string), "Ваш рабочий день завершен!");
	SCM(playerid, blue, string);
	
	format(string, sizeof(string), "Заработанные вами {"cyellow"}%d рублей {"cblue"}буду переведенны на ваш банковский счет!", PayJob[playerid]);
	SCM(playerid, blue, string);

    DisablePlayerRaceCheckpoint(playerid);
	DestroyDynamic3DTextLabel(vehicle[player_job_vehicle_arend[playerid]][veh_label]);
	SetVehicleToRespawn(player_job_vehicle_arend[playerid]);
	player_job_vehicle_arend[playerid] = -1;
	PayJob[playerid] = 0;
	DeletePVar(playerid, "EndJobEndJob");
	return 1;
}
publics NextRouteCP(playerid)
{
	if(PlayerInfo[playerid][pJob] != Job_Bus) return -1;

	new route_step = bus_route_step[playerid];
	bus_route_step[playerid] ++;
	new type_cp = 0;

	SetPlayerRaceCheckpoint
	(
		playerid,
		type_cp,
		route_pos[route_step][route_x],
		route_pos[route_step][route_y],
		route_pos[route_step][route_z],
		route_pos[route_step+1][route_x],
		route_pos[route_step+1][route_y],
		route_pos[route_step+1][route_z],
		3.0
	);
	pCheckpoint[playerid] = CP_BUS_NEXT;
	return 1;
}