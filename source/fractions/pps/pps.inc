public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TEAM_PPS_CAR][0] <= vehicleid <= job_car[TEAM_PPS_CAR][1])
        {
            if(!IsAPolice(playerid))
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет ключей от этого транспорта!");
            }
        }
	}
	#if	defined	pps__OnPlayerEnterVehicle
		return pps__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle pps__OnPlayerEnterVehicle
#if	defined	pps__OnPlayerEnterVehicle
	forward pps__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_GUN_PPS:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        GivePlayerWeaponAC(playerid, 23, 60);
                    }
                    case 1:
                    {
                        GivePlayerWeaponAC(playerid, 29, 120);
                    }
                    case 2:
                    {
                        GivePlayerWeaponAC(playerid, 3, 1);
                    }
                    case 3:
                    {
                        SCM(playerid, blue, "Вы взяли жезл. Использовать: /stopcar");
                        SetPVarInt(playerid, "zhezl", 1);
                        SetPlayerAttachedObject(playerid, 1, 1214, 6, -0.040454, 0.028840, -0.012862, 2.521301, 76.277267, 70.163467, 0.300000, 0.300000, 0.500000);
                    }
                }
            }
        }
    }
	#if	defined	pps__OnDialogResponse
		return pps__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse pps__OnDialogResponse
#if	defined	pps__OnDialogResponse
	forward pps__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 2567.2139,-2416.3386,22.3545))
        {
			SPD(playerid, D_GUN_PPS, DIALOG_STYLE_LIST, "{"cblue"}ППС | Оружие", "\
			{"cblue"}1. {FFFFFF}USP-S\n\
			{"cblue"}2. {FFFFFF}MP-5\n\
			{"cblue"}3. {FFFFFF}Дубинка\n\
			{"cblue"}4. {FFFFFF}Жезл", "Далее", "Закрыть");
        }
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 2759.7024, -1385.3208, 24.1169))
		{
			if(PlayerInfo[playerid][pMember] != TEAM_PPS) return 1;

			if(post_dps_1_status == false)
			{
				SCM(playerid, red, "Вы закрыли шлакбаум");
				MoveObject(post_dps_1, 2747.48, -1382.81, 23.44, 4.0,  0.00, 90.00, 0.00);
				post_dps_1_status = true;
			}
			else if(post_dps_1_status == true)
			{
				SCM(playerid, blue, "Вы открыли шлакбаум");
				MoveObject(post_dps_1, 2747.48, -1382.81, 23.44, 4.0, 0.00, 0.00, 0.00);
				post_dps_1_status = false;
			}

		}
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 2735.4485, -1380.7979, 24.1169))
		{
			if(PlayerInfo[playerid][pMember] != TEAM_PPS) return 1;

			if(post_dps_2_status == false)
			{
				SCM(playerid, red, "Вы закрыли шлакбаум");
				MoveObject(post_dps_2, 2746.83, -1382.82, 23.37, 4.0, 0.00, -90.00, 0.00);
				post_dps_2_status = true;
			}
			else if(post_dps_2_status == true)
			{
				SCM(playerid, blue, "Вы открыли шлакбаум");
				MoveObject(post_dps_2, 2746.83, -1382.82, 23.37, 4.0, 0.00, 0.00, 0.00);//2
				post_dps_2_status = false;
			}

		}
    }
	if(newkeys == KEY_CROUCH)
	{
		cmd::open(playerid);
	}
	#if	defined	pps__OnPlayerKeyStateChange
		return pps__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange pps__OnPlayerKeyStateChange
#if	defined	pps__OnPlayerKeyStateChange
	forward pps__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif