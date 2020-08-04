static
	Float: coord_exam[][3] =
	{
	    {1900.8645,2246.9185,15.7139},
	    {1887.3710,2234.1155,15.9526},
	    {1812.2502,2229.4512,15.8299},
	    {1767.7695,2182.2048,16.0229},
	    {1768.1252,2099.5193,16.0256},
	    {1897.6904,2053.0505,15.8772},
	    {1962.0665,2024.2561,15.8934},
	    {1961.3899,1932.3246,15.5232},
	    {2015.4318,1902.5724,15.7642},
	    {2152.4326,1904.7816,15.9052},
	    {2311.6511,1905.1666,15.9277},
	    {2411.7380,1894.4161,15.7045},
	    {2621.6543,1894.2843,16.2632},
	    {2762.4751,2048.6665,17.8023},
	    {2764.9043,2114.3000,17.9937},
	    {2753.1733,2381.4368,15.6969},
	    {2715.2339,2599.9829,15.9807},
	    {2690.4092,2726.3848,17.4332},
	    {2509.3948,2934.0823,24.2594},
	    {2218.9395,2968.1694,12.0910},
	    {2091.2639,2962.8284,12.0685},
	    {2058.8801,2881.8621,13.4363},
	    {1917.3143,2687.9778,15.1904},
	    {1771.4794,2555.7429,15.1725},
	    {1791.0187,2447.4050,15.9530},
	    {1850.5253,2357.6616,15.9530},
	    {1885.9377,2271.0728,15.9526},
	    {1903.1064,2246.7146,15.7141},
	    {1914.1827,2246.4639,15.7139} // 29
	};


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{

    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 131.3660,1368.7767,1002.9600))
        {
			if(PlayerInfo[playerid][pFines] >= 1) return SCM(playerid, red, "У вас есть неоплаченые штрафы. Оплатите их в ближайшем банкомате.");
			SPD(playerid, D_EXAM_DRIVING, DIALOG_STYLE_LIST, "{"cblue"}Сдача экзамена", "\
			{FFFFFF}Категория A\t\t\t{"cblue"}4000 рублей\n\
			{FFFFFF}Категория B\t\t\t{"cblue"}5000 рублей\n\
			{FFFFFF}Категория C\t\t\t{"cblue"}5500 рублей\n\
			{FFFFFF}Категория D\t\t\t{"cblue"}6500 рублей", "Далее", "Закрыть");
        }
    }
	#if	defined	ah__OnPlayerKeyStateChange
		return ah__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange ah__OnPlayerKeyStateChange
#if	defined	ah__OnPlayerKeyStateChange
	forward ah__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(GetPVarInt(playerid, "lesson") == 1)
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 2)
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 3)
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 4)
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	#if	defined	ah__OnPlayerDisconnect
		return ah__OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerDisconnect
	#undef	OnPlayerDisconnect
#else
	#define	_ALS_OnPlayerDisconnect
#endif

#define	OnPlayerDisconnect ah__OnPlayerDisconnect
#if	defined	ah__OnPlayerDisconnect
	forward ah__OnPlayerDisconnect(playerid, reason);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_EXAM_DRIVING:
		{
		    if(!response) return 1;
		    else
		    {
		        switch(listitem)
		        {
		            case 0:
		            {
						if(PlayerInfo[playerid][pCash] < 4000) return SCM(playerid, red, "У вас недостаточно денег!");
						if(PlayerInfo[playerid][pLicA] == 1) return SCM(playerid, red, "У вас есть права категории А!");
						if(GetPVarInt(playerid, "lesson") != 0) return SCM(playerid, red, "В данный момент вы сдаете какой-то экзамен!");
						
						GiveMoney(playerid, -4000, "Сдача экзамена");
      					SCM(playerid, green, "Вы начали практическую часть сдачи экзамена на вождение.");
		                SCM(playerid, green, "Выйдите во двор и сядьте в Мотоцыкл.");
		                
		                SetPVarInt(playerid, "lesson", 1);
		            }
		            case 1:
		            {
                        if(PlayerInfo[playerid][pCash] < 5000) return SCM(playerid, red, "У вас недостаточно денег!");
                        if(PlayerInfo[playerid][pLicB] == 1) return SCM(playerid, red, "У вас есть права категории B!");
						if(GetPVarInt(playerid, "lesson") != 0) return SCM(playerid, red, "В данный момент вы сдаете какой-то экзамен!");

						GiveMoney(playerid, -5000, "Сдача экзамена");
                        SCM(playerid, green, "Вы начали практическую часть сдачи экзамена на вождение.");
		                SCM(playerid, green, "Выйдите во двор и сядьте в Автомобиль.");
		                
		                SetPVarInt(playerid, "lesson", 2);
		            }
		            case 2:
		            {
		                if(PlayerInfo[playerid][pCash] < 5500) return SCM(playerid, red, "У вас недостаточно денег!");
		                if(PlayerInfo[playerid][pLicC] == 1) return SCM(playerid, red, "У вас есть права категории C!");
						if(GetPVarInt(playerid, "lesson") != 0) return SCM(playerid, red, "В данный момент вы сдаете какой-то экзамен!");

						GiveMoney(playerid, -5500, "Сдача экзамена");
		                SCM(playerid, green, "Вы начали практическую часть сдачи экзамена на вождение.");
		                SCM(playerid, green, "Выйдите во двор и сядьте в Грузовик.");
		                
		                SetPVarInt(playerid, "lesson", 3);
		            }
		            case 3:
		            {
		                if(PlayerInfo[playerid][pCash] < 6500) return SCM(playerid, red, "У вас недостаточно денег!");
		                if(PlayerInfo[playerid][pLicD] == 1) return SCM(playerid, red, "У вас есть права категории D!");
						if(GetPVarInt(playerid, "lesson") != 0) return SCM(playerid, red, "В данный момент вы сдаете какой-то экзамен!");

						GiveMoney(playerid, -6500, "Сдача экзамена");
		                SCM(playerid, green, "Вы начали практическую часть сдачи экзамена на вождение.");
		                SCM(playerid, green, "Выйдите во двор и сядьте в Автобус.");
		                
		                SetPVarInt(playerid, "lesson", 4);
		            }
		        }
		    }
		}
    }
	#if	defined	ah__OnDialogResponse
		return ah__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse ah__OnDialogResponse
#if	defined	ah__OnDialogResponse
	forward ah__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
    	new newcar = vehicleid;
        if(job_car[CATEG_A_CAR][0] <= newcar <= job_car[CATEG_A_CAR][1])
        {
			if(GetPVarInt(playerid, "lesson") != 1)
			{
				ClearAnimations(playerid, true);
			    return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию A!");
			}
        }
        if(job_car[CATEG_B_CAR][0] <= newcar <= job_car[CATEG_B_CAR][1])
        {
			if(GetPVarInt(playerid, "lesson") != 2)
			{
			    ClearAnimations(playerid, true);
			    return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию B!");
			}
        }
        if(job_car[CATEG_C_CAR][0] <= newcar <= job_car[CATEG_C_CAR][1])
        {
			if(GetPVarInt(playerid, "lesson") != 3)
			{
			    ClearAnimations(playerid, true);
			    return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию C!");
			}
        }
        if(newcar == job_car[CATEG_D_CAR][0])
        {
			if(GetPVarInt(playerid, "lesson") != 4)
			{
			    ClearAnimations(playerid, true);
			    return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию D!");
			}
        }
        if(IsAMoped(newcar) && PlayerInfo[playerid][pLicA] != 1)
        {
            if(GetPVarInt(playerid, "lesson") == 1) return 1;
            else
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет прав категории A!");
            }
        }
        if(IsACar(newcar) && PlayerInfo[playerid][pLicB] != 1)
        {
            if(GetPVarInt(playerid, "lesson") == 2) return 1;
            else
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет прав категории B!");
            }
        }
        if(IsATruck(newcar) && PlayerInfo[playerid][pLicC] != 1)
        {
            if(GetPVarInt(playerid, "lesson") == 3) return 1;
            else
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет прав категории C!");
            }
        }
        if(IsABus(newcar) && PlayerInfo[playerid][pLicD] != 1)
        {
            if(GetPVarInt(playerid, "lesson") == 4) return 1;
            else
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет прав категории D!");
            }
        }
	}
	#if	defined	ah__OnPlayerEnterVehicle
		return ah__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle ah__OnPlayerEnterVehicle
#if	defined	ah__OnPlayerEnterVehicle
	forward ah__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{
	new newcar = vehicleid;

	if(GetPVarInt(playerid, "lesson") == 1 && job_car[CATEG_A_CAR][0] <= newcar <= job_car[CATEG_A_CAR][1])
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 2 && job_car[CATEG_B_CAR][0] <= newcar <= job_car[CATEG_B_CAR][1])
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 3 && job_car[CATEG_C_CAR][0] <= newcar <= job_car[CATEG_C_CAR][1])
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	if(GetPVarInt(playerid, "lesson") == 4 && newcar == job_car[CATEG_D_CAR][0])
	{
		SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		DeletePVar(playerid, "lesson");
	}
	#if	defined	ah__OnPlayerExitVehicle
		return ah__OnPlayerExitVehicle(playerid, vehicleid);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerExitVehicle
	#undef	OnPlayerExitVehicle
#else
	#define	_ALS_OnPlayerExitVehicle
#endif

#define	OnPlayerExitVehicle ah__OnPlayerExitVehicle
#if	defined	ah__OnPlayerExitVehicle
	forward ah__OnPlayerExitVehicle(playerid, vehicleid);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	new newcar = GetPlayerVehicleID(playerid);
	if(job_car[CATEG_A_CAR][0] <= newcar <= job_car[CATEG_A_CAR][1])
	{
		if(GetPVarInt(playerid, "lesson") != 1)
		{
			ClearAnimations(playerid, true);
			return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию A!");
		}
		else
		{
			SCM(playerid, blue, "Для сдачи экзамена, следуйте по маркерам соблюдая ПДД. Внимание! На экзамен вам даётся {"cyellow"}10 минут{"cblue"}!");
			pPressed[playerid] = 0;
			SetPlayerRaceCheckpoint(playerid, 0, coord_exam[pPressed[playerid]][0], coord_exam[pPressed[playerid]][1], coord_exam[pPressed[playerid]][2], coord_exam[pPressed[playerid]+1][0], coord_exam[pPressed[playerid]+1][1], coord_exam[pPressed[playerid]+1][2], 5.0);
			pCheckpoint[playerid] = CP_EXAM_DRIVING;
		}
	}
	if(job_car[CATEG_B_CAR][0] <= newcar <= job_car[CATEG_B_CAR][1])
	{
		if(GetPVarInt(playerid, "lesson") != 2)
		{
			ClearAnimations(playerid, true);
			return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию B!");
		}
		else
		{
			SCM(playerid, blue, "Для сдачи экзамена, следуйте по маркерам соблюдая ПДД. Внимание! На экзамен вам даётся {"cyellow"}10 минут{"cblue"}!");
			pPressed[playerid] = 0;
			SetPlayerRaceCheckpoint(playerid, 0, coord_exam[pPressed[playerid]][0], coord_exam[pPressed[playerid]][1], coord_exam[pPressed[playerid]][2], coord_exam[pPressed[playerid]+1][0], coord_exam[pPressed[playerid]+1][1], coord_exam[pPressed[playerid]+1][2], 5.0);
			pCheckpoint[playerid] = CP_EXAM_DRIVING;
		}
	}
	if(job_car[CATEG_C_CAR][0] <= newcar <= job_car[CATEG_C_CAR][1])
	{
		if(GetPVarInt(playerid, "lesson") != 3)
		{
			ClearAnimations(playerid, true);
			return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию C!");
		}
		else
		{
			SCM(playerid, blue, "Для сдачи экзамена, следуйте по маркерам соблюдая ПДД. Внимание! На экзамен вам даётся {"cyellow"}10 минут{"cblue"}!");
			pPressed[playerid] = 0;
			SetPlayerRaceCheckpoint(playerid, 0, coord_exam[pPressed[playerid]][0], coord_exam[pPressed[playerid]][1], coord_exam[pPressed[playerid]][2], coord_exam[pPressed[playerid]+1][0], coord_exam[pPressed[playerid]+1][1], coord_exam[pPressed[playerid]+1][2], 5.0);
			pCheckpoint[playerid] = CP_EXAM_DRIVING;
		}
	}
	if(newcar == job_car[CATEG_D_CAR][0])
	{
		if(GetPVarInt(playerid, "lesson") != 4)
		{
			ClearAnimations(playerid, true);
			return SCM(playerid, red, "Этот транспорт, предназанчен, для здачи экзамена на Категорию D!");
		}
		else
		{
			SCM(playerid, blue, "Для сдачи экзамена, следуйте по маркерам соблюдая ПДД. Внимание! На экзамен вам даётся {"cyellow"}10 минут{"cblue"}!");
			pPressed[playerid] = 0;
			SetPlayerRaceCheckpoint(playerid, 0, coord_exam[pPressed[playerid]][0], coord_exam[pPressed[playerid]][1], coord_exam[pPressed[playerid]][2], coord_exam[pPressed[playerid]+1][0], coord_exam[pPressed[playerid]+1][1], coord_exam[pPressed[playerid]+1][2], 5.0);
			pCheckpoint[playerid] = CP_EXAM_DRIVING;
		}
	}
    if(newstate == PLAYER_STATE_PASSENGER)
    {
	    if(job_car[CATEG_A_CAR][0] <= newcar <= job_car[CATEG_A_CAR][1] || job_car[CATEG_B_CAR][0] <= newcar <= job_car[CATEG_B_CAR][1] || job_car[CATEG_C_CAR][0] <= newcar <= job_car[CATEG_C_CAR][1] || job_car[CATEG_D_CAR][0] <= newcar <= job_car[CATEG_D_CAR][1])
	    {
			RemovePlayerFromVehicle(playerid);
			return SCM(playerid, red, "Этот автомобиль предназначен, для сдачи экзамена на вождение!");
	    }
    }
    if(oldstate == PLAYER_STATE_DRIVER)
    {
		if(GetPVarInt(playerid, "lesson") == 1 && job_car[CATEG_A_CAR][0] <= newcar <= job_car[CATEG_A_CAR][1])
		{
		    SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		    DisablePlayerRaceCheckpoint(playerid);
	        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			DeletePVar(playerid, "lesson");
		}
		if(GetPVarInt(playerid, "lesson") == 2 && job_car[CATEG_B_CAR][0] <= newcar <= job_car[CATEG_B_CAR][1])
		{
		    SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		    DisablePlayerRaceCheckpoint(playerid);
	        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			DeletePVar(playerid, "lesson");
		}
		if(GetPVarInt(playerid, "lesson") == 3 && job_car[CATEG_C_CAR][0] <= newcar <= job_car[CATEG_C_CAR][1])
		{
		    SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		    DisablePlayerRaceCheckpoint(playerid);
	        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			DeletePVar(playerid, "lesson");
		}
		if(GetPVarInt(playerid, "lesson") == 4 && newcar == job_car[CATEG_D_CAR][0])
		{
		    SCM(playerid, red, "К сожалению, вы провалили экзамен на вождение.");
		    DisablePlayerRaceCheckpoint(playerid);
	        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			DeletePVar(playerid, "lesson");
		}
    }
    #if defined ah__OnPlayerStateChange
        return ah__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange ah__OnPlayerStateChange
#if	defined	ah__OnPlayerStateChange
	forward ah__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

public OnPlayerEnterRaceCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
		case CP_EXAM_DRIVING:
		{
  			pPressed[playerid]++;
  			new i = pPressed[playerid];
  			DisablePlayerRaceCheckpoint(playerid);
  			if(i != 28)
  			{
			    SetPlayerRaceCheckpoint(playerid, 0, coord_exam[i][0], coord_exam[i][1], coord_exam[i][2], coord_exam[i+1][0], coord_exam[i+1][1], coord_exam[i+1][2], 5.0);
			    pCheckpoint[playerid] = CP_EXAM_DRIVING;
			}
			else if(i == 28)
			{
				new Float: veh_health;
				GetVehicleHealth(GetPlayerVehicleID(playerid), veh_health);

				if(veh_health >= 900)
				{
					switch(GetPVarInt(playerid, "lesson"))
					{
					    case 1:
						{
						    SCM(playerid, green, "Поздравляем! Вы успешно сдали на права категории A.");
							PlayerInfo[playerid][pLicA] = 1;
						}
						case 2:
						{
						    SCM(playerid, green, "Поздравляем! Вы успешно сдали на права категории B.");
							PlayerInfo[playerid][pLicB] = 1;
						}
					    case 3:
						{
						    SCM(playerid, green, "Поздравляем! Вы успешно сдали на права категории C.");
							PlayerInfo[playerid][pLicC] = 1;
						}
					    case 4:
						{
						    SCM(playerid, green, "Поздравляем! Вы успешно сдали на права категории D.");
							PlayerInfo[playerid][pLicD] = 1;
						}
					}
				}
				else
				{
				    SCM(playerid, red, "К сожалению вы провалили экзамен на вождение!");
				}
				SaveAccounts(playerid);
                SetVehicleToRespawn(GetPlayerVehicleID(playerid));
				DeletePVar(playerid, "lesson");
			}
		}
    }
    #if defined ah_OnPlayerEnterRaceCheckpoint
        return ah_OnPlayerEnterRaceCheckpoint(playerid);
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

#define OnPlayerEnterRaceCheckpoint ah_OnPlayerEnterRaceCheckpoint
#if defined ah_OnPlayerEnterRaceCheckpoint
    forward ah_OnPlayerEnterRaceCheckpoint(playerid);
#endif