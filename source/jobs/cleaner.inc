new CleanTimer[MAX_PLAYERS];
static
	Float: coord_cleaner[][3] =
	{
		{1814.4929,2229.3308,15.8327}, //72 max
		{1768.5228,2204.1753,15.9954},
		{1768.2610,2084.8130,16.0256},
		{1827.8455,2051.9268,15.8850},
		{1935.2908,2052.6299,15.8694},
		{1961.7323,1932.6927,15.5340},
		{1961.7268,1781.3667,15.5124},
		{1979.2296,1663.7827,15.9823},
		{2000.5469,1548.5870,15.9905},
		{1923.5277,1513.2518,12.0824},
		{1876.7654,1400.5887,10.0278},
		{1929.8447,1322.1844,18.2463},
		{2058.7075,1322.4106,26.3949},
		{2219.7786,1350.5300,11.6523},
		{2437.7668,1352.0859,11.8632},
		{2576.9890,1315.9762,17.7950},
		{2731.0308,976.3642,24.1210},
		{2900.5352,631.0906,33.3205},
		{2903.5920,275.4397,14.4459},
		{2904.1638,-71.6717,25.3711},
		{2818.5552,-369.6259,26.7940},
		{2744.7151,-658.3857,23.9490},
		{2744.8467,-961.9894,23.9518},
		{2744.2183,-1125.7578,23.5559},
		{2743.3689,-1321.8080,23.5559},
		{2715.6072,-1488.3127,23.8370},
		{2632.7786,-1518.6539,23.8387},
		{2502.9983,-1513.9548,24.0984},
		{2365.8008,-1515.2732,23.6153},
		{2277.0811,-1664.0930,22.1962},
		{2277.5203,-1745.5063,21.8135},
		{2333.1975,-1761.6920,21.8141},
		{2508.5017,-1756.6156,35.6969},
		{2627.7483,-1783.4146,35.6910},
		{2707.1978,-1945.7384,35.7032},
		{2711.8547,-2106.4375,21.8247},
		{2758.3855,-2162.6082,20.0568},
		{2790.4614,-2284.7295,18.8098},
		{2791.0913,-2490.4753,21.6734},
		{2712.1177,-2628.9536,23.6630},
		{2621.1272,-2681.9590,25.2876},
		{2499.5718,-2682.5952,25.3432},
		{2469.4705,-2593.1987,22.5097},
		{2467.8811,-2357.0767,21.7679},
		{2468.2834,-2189.6814,21.8026},
		{2569.6099,-2158.7476,21.8287},
		{2607.5300,-2030.6445,21.8233},
		{2608.2517,-1762.6980,21.8156},
		{2606.9912,-1559.2693,23.6454},
		{2711.5979,-1500.7036,23.8404},
		{2750.8296,-1392.8380,23.8212},
		{2750.7878,-1123.6948,23.5559},
		{2751.1089,-897.6359,23.9272},
		{2750.5364,-587.7357,23.9396},
		{2835.4478,-352.5851,26.9802},
		{2909.7183,-95.0067,25.6604},
		{2909.0779,208.9780,13.1583},
		{2908.7437,567.9823,29.7807},
		{2780.3101,869.2909,29.7172},
		{2706.7424,1095.3995,18.6926},
		{2555.9592,1392.1802,13.2086},
		{2697.4680,1635.1068,17.0444},
		{2747.5046,1870.1857,16.2027},
		{2687.4751,1899.9716,15.9766},
		{2452.4451,1898.8759,16.2666},
		{2297.8779,1910.1825,15.8976},
		{2104.3589,1911.9784,15.8884},
		{1968.8822,1931.9821,15.4747},
		{1952.8608,2052.5862,15.8694},
		{1892.1692,2088.8875,15.9302},
		{1892.1222,2195.3472,15.9275},
		{1849.4521,2229.4067,15.8197},
		{1830.4540,2229.5522,15.8354}
	};
public OnPlayerDisconnect(playerid, reason)
{
    if(GetPVarInt(playerid, "cleaner_job") == 1) EndJobCleaner(playerid);
    #if defined clean__OnPlayerDisconnect
        return clean__OnPlayerDisconnect(playerid, reason);
    #else 
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else   
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect clean__OnPlayerDisconnect
#if defined clean__OnPlayerDisconnect
    forward clean__OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1809.6216,2253.1555,15.2729))
        {
			SPD(playerid, D_AREND_CLEAN, DIALOG_STYLE_MSGBOX, "{"cblue"}Аренда уборочной машины", "{FFFFFF}Стоимость аренды уборочной машины - {"cblue"}200 рублей{FFFFFF}.\nВы уверенны, что хотите арендовать уборочную машину?", "Арендовать", "Закрыть");
        }
    }
	#if	defined	clean__OnPlayerKeyStateChange
		return clean__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange clean__OnPlayerKeyStateChange
#if	defined	clean__OnPlayerKeyStateChange
	forward clean__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_AREND_CLEAN:
		{
			if(!response) return 1;
			else
			{
			    if(PlayerInfo[playerid][pCash] < 200) return SCM(playerid, red, "У вас не достаточно денег!");
			    
			    GiveMoney(playerid, -200, "Аренда уборочной машины!");
				SCM(playerid, blue, "Вы успешно арендовали уборочную машину!");
				SCM(playerid, blue, "У вас есть {"cyellow"}45 секунд{"cblue"}, что б сесть в транспорт!");
			    player_job_vehicle_created[playerid] = CreateVehicle(574,1821.0057,2257.3115,14.9980,180.1769,1,0, -1);
				SetPlayerCheckpoint(playerid, 1821.0057,2257.3115,14.9980, 3.0);
				pCheckpoint[playerid] = CP_CLEANER_AREND;
				CleanTimer[playerid] = 45;
				SetPVarInt(playerid, "cleaner_job", 1);
			}
		}
		case D_CMD_END_CLEANER:
		{
		    if(!response) return 1;
		    else EndJobCleaner(playerid);
		}
    }
	#if	defined	clean__OnDialogResponse
		return clean__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse clean__OnDialogResponse
#if	defined	clean__OnDialogResponse
	forward clean__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterRaceCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
		case CP_CLEANER_CP:
		{
			if(GetPlayerVehicleID(playerid) == player_job_vehicle_created[playerid])
			{
				pPressed[playerid]++;

				if(pPressed[playerid] != 72)
				{
					new i = pPressed[playerid];

					SetPlayerRaceCheckpoint(playerid, 0, coord_cleaner[i][0], coord_cleaner[i][1], coord_cleaner[i][2], coord_cleaner[i+1][0], coord_cleaner[i+1][1], coord_cleaner[i+1][2], 2.0);
					pCheckpoint[playerid] = CP_CLEANER_CP;

					new rand = random(10) + 10;

					PayJob[playerid] += rand;
				}
				else if(pPressed[playerid] == 72)
				{
					pPressed[playerid] = 0;

					new i = pPressed[playerid];

					SetPlayerRaceCheckpoint(playerid, 0, coord_cleaner[i][0], coord_cleaner[i][1], coord_cleaner[i][2], coord_cleaner[i+1][0], coord_cleaner[i+1][1], coord_cleaner[i+1][2], 2.0);
					pCheckpoint[playerid] = CP_CLEANER_CP;

					new rand = random(10) + 10;

					PayJob[playerid] += rand;
				}
			}
		}	
    }
    #if defined cleaner_OPERC
        return cleaner_OPERC(playerid);
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

#define OnPlayerEnterRaceCheckpoint cleaner_OPERC
#if defined cleaner_OPERC
    forward cleaner_OPERC(playerid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
		if(GetPlayerVehicleID(playerid) == player_job_vehicle_created[playerid])
		{
			if(pCheckpoint[playerid] == CP_CLEANER_AREND)
			{
			    CleanTimer[playerid] = 0;
				pPressed[playerid] = 0;
				new i = pPressed[playerid];
			    SCM(playerid, green, "Вы сели в уборочную машину, отправляйтесь на маршрут!");

			    SetPlayerRaceCheckpoint(playerid, 0, coord_cleaner[i][0], coord_cleaner[i][1], coord_cleaner[i][2], coord_cleaner[i+1][0], coord_cleaner[i+1][1], coord_cleaner[i+1][2], 2.0);
			    pCheckpoint[playerid] = CP_CLEANER_CP;
			}
			if(GetPVarInt(playerid, "EndJobCleaner") == 1)
			{
			    SCM(playerid, green, "Вы вернулись в транспорт! Продолжайте работу!");
				KillTimer(player_end_job_timer[playerid]);
				DeletePVar(playerid, "EndJobCleaner");
			}
		}
    }
    if(oldstate == PLAYER_STATE_DRIVER)
    {
		if(player_job_vehicle_created[playerid] != -1 && GetPVarInt(playerid, "cleaner_job") == 1)
		{
		    if(GetPVarInt(playerid, "EndJobCleaner") == 1) return 1;
			player_end_job_timer[playerid] = SetTimerEx("EndJobCleaner", 15000, false, "i", playerid);
			SetPVarInt(playerid, "EndJobCleaner", 1);

			SCM(playerid, 0xFF6600FF, "У Вас есть 15 секунд чтобы вернуться в транспорт");
		}
    }
    #if defined clean__OnPlayerStateChange
        return clean__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange clean__OnPlayerStateChange
#if	defined	clean__OnPlayerStateChange
	forward clean__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

publics PlayerSecondTimer(playerid)
{

	if(CleanTimer[playerid] > 0)
	{
		CleanTimer[playerid]--;
		new string[64];
		format(string, sizeof(string), "~w~Time: ~r~%d ~w~sek", CleanTimer[playerid]);
		GameTextForPlayer(playerid, string, 1000, 4);

		if(CleanTimer[playerid] == 0)
		{
			EndJobCleaner(playerid);
		}
	}

    #if defined clean__PlayerSecondTimer
        return clean__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer clean__PlayerSecondTimer
#if	defined	clean__PlayerSecondTimer
	forward clean__PlayerSecondTimer(playerid); 
#endif


public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
        case CP_CLEANER_AREND: DisablePlayerCheckpoint(playerid);
    }
    #if defined clean__OnPlayerEnterCheckpoint
        return clean__OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerEnterCheckpoint
	#undef	OnPlayerEnterCheckpoint
#else
	#define	_ALS_OnPlayerEnterCheckpoint
#endif

#define	OnPlayerEnterCheckpoint clean__OnPlayerEnterCheckpoint
#if	defined	clean__OnPlayerEnterCheckpoint
	forward clean__OnPlayerEnterCheckpoint(playerid);
#endif

publics EndJobCleaner(playerid)
{
	if(GetPVarInt(playerid, "EndJobCleaner") == 1) SCM(playerid, red, "К сожалению, вы не успели сесть в грузовикк!");
	new string[128];
	
	SCM(playerid, blue, "Вы успешно завершили рабочий день!");
	format(string, sizeof(string), "Ваша зар. плата в размере {"cyellow"}%d рублей{"cblue"}, была переведенна на ваш банковский счет!", PayJob[playerid]*XDay);
	SCM(playerid, blue, string);
	
	PlayerInfo[playerid][pBCash] += PayJob[playerid]*XDay;

	PayJob[playerid] = 0;
	DestroyVehicle(player_job_vehicle_created[playerid]);
	DisablePlayerRaceCheckpoint(playerid);
	player_job_vehicle_created[playerid] = -1;
	DeletePVar(playerid, "EndJobCleanr");
	DeletePVar(playerid, "cleaner_job");
	KillTimer(player_end_job_timer[playerid]);
	return 1;
}