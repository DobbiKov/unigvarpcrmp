public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP) || (newkeys & KEY_FIRE))
    {
        if(GetPVarInt(playerid, "vdv_tonn_load") > 0)
        {
            SCM(playerid, red, "Вы уронили ящик!");
            DeletePVar(playerid, "vdv_too_load");
            ClearAnimations(playerid);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
                RemovePlayerAttachedObject(playerid, 1);
        }
    }
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1400.6801,1755.8474,4.1479))
        {
            SetPlayerPos(playerid, 1400.6577,1758.0184,-5.7436);
        }
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1400.6577,1758.0184,-5.7436))
        {
            SetPlayerPos(playerid, 1400.6801,1755.8474,4.1479);
        }
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1490.5315,1668.2097,-5.3244))
        {
            SPD(playerid, D_GUN_VDV, DIALOG_STYLE_LIST, "{"cblue"}АРМИЯ | Оружие", "{"cblue"}1. {FFFFFF}Пистолет (9-mm)\n{"cblue"}2. {FFFFFF}Автомат Калашникова\n{"cblue"}3. {FFFFFF}Дубинка", "Далее", "Закрыть");
        }
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1453.0112,1761.9174,-7.5053))
        {
            if(PlayerInfo[playerid][pMember] != TEAM_VDV) return 1;
            ApplyAnimation(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
			SetPlayerAttachedObject(playerid, 1 ,3052, 1,0.11,0.36,0.0,0.0,90.0);
			SetPVarInt(playerid, "vdv_tonn_load", 1);
			SCM(playerid, blue, "Вы подняли ящик! Теперь отнесите его на склад!");
        }

        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1480.5662,1693.4558,15.8295))
        {
            SetPlayerPos(playerid, 1481.4395,1693.5308,25.5009);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1481.4395,1693.5308,25.5009))
        {
            SetPlayerPos(playerid, 1480.5662,1693.4558,15.8295);
        }

        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1649.0653,1726.3934,15.6129))
        {
            SetPlayerPos(playerid, 1649.9226,1726.4796,25.0509);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1649.9226,1726.4796,25.0509))
        {
            SetPlayerPos(playerid, 1649.0653,1726.3934,15.6129);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1886.1226,1742.4620,15.3215))
        {
            SetPlayerPos(playerid, 1886.6741,1742.4590,25.5009);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1886.6741,1742.4590,25.5009))
        {
            SetPlayerPos(playerid, 1886.1226,1742.4620,15.3215);
        }

        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1887.1824,1713.4810,15.5164))
        {
            SetPlayerPos(playerid, 1888.0596,1713.3903,25.5009);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1888.0596,1713.3903,25.5009))
        {
            SetPlayerPos(playerid, 1887.1824,1713.4810,15.5164);
        }
    }
    if(newkeys == KEY_CROUCH)
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            new vehicleid = GetPlayerVehicleID(playerid);

            if(job_car[TEAM_VDV_METALL_CAR][0] <= vehicleid <= job_car[TEAM_VDV_METALL_CAR][1])
            {
                if(IsPlayerInRangeOfPoint(playerid, 10.0, 2371.0042,2006.6135,15.9900))
                {
                    if(vehicle[vehicleid][veh_metall] >= 500) return SCM(playerid, red, "Вы не можете загрузить более 500 кг. металла");
                    SPD(playerid, D_VDV_METALL_BUY, DIALOG_STYLE_MSGBOX, "{"cblue"}Покупка металла", "{FFFFFF}Стоимость {"cblue"}500 кг {FFFFFF}стоит {"cblue"}4000 рублей{FFFFFF}. Вы уверенны, что хотите купить металл?", "Да", "Нет");
                }
                if(IsPlayerInRangeOfPoint(playerid, 10.0, 1425.2693,1672.7239,15.4692))
                {
                    if(vehicle[vehicleid][veh_metall] < 1) return SCM(playerid, red, "У вас нет металла в грузовике!");

                    DestroyDynamic3DTextLabel(vehicle[vehicleid][veh_label]);
                    SCM(playerid, green, "Вы разгрузили 500 кг. металла на склад Армии");

                    new string[128];
                    format(string, sizeof(string), "[R] %s %s[%d] разгрузил 500 кг. металла на склад", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid);
                    SCMR(TEAM_VDV, green, string);
                    
                    REPOSITORY_ARMY_METALL += vehicle[vehicleid][veh_metall];
                    SaveRepository();
                    vehicle[vehicleid][veh_metall] = 0;
                }
            }
            if(IsPlayerInRangeOfPoint(playerid, 10.0, 1653.39, 1686.51, 15.03))
            {
                if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB) return 1;
                switch(shlak_vdv_status)
                {
                    case false:
                    {
                        SCM(playerid, green, "Вы открыли шлакбаум!");
                        MoveObject(shlak_vdv, 1653.388427, 1686.505615, 15.026650, 30.0, 0.000000, 0.000000, 90.000000); //Открытый шлагбаум
                        shlak_vdv_status = true;
                    }
                    case true:
                    {
                        SCM(playerid, red, "Вы закрыли шлакбаум!");
                        MoveObject(shlak_vdv, 1653.39, 1686.51, 15.03, 30.0, 0.00, -90.00, 90.00); //Открытый шлагбаум
                        shlak_vdv_status = false;
                    }
                }
            }
        }
    }
	#if	defined	vdv__OnPlayerKeyStateChange
		return vdv__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange vdv__OnPlayerKeyStateChange
#if	defined	vdv__OnPlayerKeyStateChange
	forward vdv__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TEAM_VDV_CAR][0] <= vehicleid <= job_car[TEAM_VDV_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                SCM(playerid, red, "У вас нет ключей от этого транспорта!");
                RemovePlayerFromVehicle(playerid);    
                return ClearAnimations(playerid, true);
            }
        }
        if(job_car[TEAM_VDV_BTR_CAR][0] <= vehicleid <= job_car[TEAM_VDV_BTR_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                SCM(playerid, red, "У вас нет ключей от этого транспорта!");
                RemovePlayerFromVehicle(playerid);   
                return ClearAnimations(playerid, true); 
            }
        }
        if(job_car[TEAM_VDV_TANK_CAR][0] <= vehicleid <= job_car[TEAM_VDV_TANK_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                SCM(playerid, red, "У вас нет ключей от этого транспорта!");
                RemovePlayerFromVehicle(playerid);
                return ClearAnimations(playerid, true);    
            }
        }
        if(job_car[TEAM_VDV_METALL_CAR][0] <= vehicleid <= job_car[TEAM_VDV_METALL_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                SCM(playerid, red, "У вас нет ключей от этого транспорта!");
                RemovePlayerFromVehicle(playerid);   
                return ClearAnimations(playerid, true);
            }
        }
	}
	#if	defined	vdv__OnPlayerEnterVehicle
		return vdv__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle vdv__OnPlayerEnterVehicle
#if	defined	vdv__OnPlayerEnterVehicle
	forward vdv__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_PASSENGER || newstate == PLAYER_STATE_DRIVER)
    {
        if(GetPVarInt(playerid, "vdv_tonn_load") > 0)
        {
            SCM(playerid, red, "Вы уронили ящик!");
            DeletePVar(playerid, "vdv_tonn_load");
            ClearAnimations(playerid);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
                RemovePlayerAttachedObject(playerid, 1);
        }        
    }
    #if defined vdv__OnPlayerStateChange
        return vdv__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange vdv__OnPlayerStateChange
#if	defined	vdv__OnPlayerStateChange
	forward vdv__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_GUN_VDV:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(REPOSITORY_ARMY_PATRON < 50) return SCM(playerid, red, "На складе недостаточно патронов!");
                        if(REPOSITORY_ARMY_METALL < 50) return SCM(playerid, red, "На складе недостаточно металла!");

                        GivePlayerWeaponAC(playerid, 22, 50);

                        REPOSITORY_ARMY_METALL -= 50;
                        REPOSITORY_ARMY_PATRON -= 50;
                        SaveRepository();
                    }
                    case 1: 
                    {
                        if(REPOSITORY_ARMY_PATRON < 120) return SCM(playerid, red, "На складе недостаточно патронов!");
                        if(REPOSITORY_ARMY_METALL < 60) return SCM(playerid, red, "На складе недостаточно металла!");

                        GivePlayerWeaponAC(playerid, 30, 120);

                        REPOSITORY_ARMY_METALL -= 60;
                        REPOSITORY_ARMY_PATRON -= 120;
                        SaveRepository();
                    }
                    case 2: 
                    {
                        if(REPOSITORY_ARMY_PATRON < 1) return SCM(playerid, red, "На складе недостаточно патронов!");
                        if(REPOSITORY_ARMY_METALL < 1) return SCM(playerid, red, "На складе недостаточно металла!");

                        GivePlayerWeaponAC(playerid, 3, 1);

                        REPOSITORY_ARMY_METALL -= 1;
                        REPOSITORY_ARMY_PATRON -= 1;
                        SaveRepository();
                    }
                }
            }
        }
        case D_VDV_METALL_BUY:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][pCash] < 4000) return SCM(playerid, red, "У вас недостаточно денег!");

                new vehicleid = GetPlayerVehicleID(playerid);
                vehicle[vehicleid][veh_metall] = 500;
                vehicle[vehicleid][veh_label] = CreateDynamic3DTextLabel("Металл:\n500/500 кг.", green, 0.0, 0.0, 1.5, 20.0, _, vehicleid);
                GiveMoney(playerid, -4000, "Покупка металла для армии");
                SCM(playerid, green, "Вы загрузили 500 кг металла. Теперь езжайте на базу и разгрузите металл.");
            }
        }
    }
	#if	defined	vdv__OnDialogResponse
		return vdv__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse vdv__OnDialogResponse
#if	defined	vdv__OnDialogResponse
	forward vdv__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics PlayerSecondTimer(playerid)
{
    new hours,minutes,seconds;
    gettime(hours, minutes, seconds);

    if(IsPlayerInRangeOfPoint(playerid, 3.0, 1494.8928,1660.9591,-5.3171))
    {
        if(seconds % 2 == 0) if(IsAOpg(playerid) || PlayerInfo[playerid][pVIP] > 0 || PlayerInfo[playerid][pMember] == TEAM_VDV) StealPatron(playerid);

        if(GetPVarInt(playerid, "vdv_tonn_load") > 0)
        {
            SCM(playerid, green, "Вы доставили ящик на склад!");
            DeletePVar(playerid, "vdv_tonn_load");
            ClearAnimations(playerid);

            if(IsPlayerAttachedObjectSlotUsed(playerid, 1))
                RemovePlayerAttachedObject(playerid, 1);   

            REPOSITORY_ARMY_PATRON += 50;
            SaveRepository();         
        }
    }

    #if defined vdv__PlayerSecondTimer
        return vdv__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer vdv__PlayerSecondTimer
#if	defined	vdv__PlayerSecondTimer
	forward vdv__PlayerSecondTimer(playerid); 
#endif

stock UpdateRepository()
{
	new string_ammo[128];
	format(string_ammo, sizeof(string_ammo), "{ffcc00}Склад\n\n{ffffff}Патроны: {ff9900}%d\n{ffffff}Металл: {ff9900}%d\n\n{ff4f00}Команды:\n{ffcc00}/getmet\n/putmet", REPOSITORY_ARMY_PATRON, REPOSITORY_ARMY_METALL);
	UpdateDynamic3DTextLabelText(RepositoryArmyText, 0xFFFFFFFF, string_ammo);

	new opg_o_ammo[256];
	format(opg_o_ammo, sizeof(opg_o_ammo), "{ffcc00}Склад\n\n{FFFFFF}Патроны: {ff9900}%d\n{ffffff}Металл: {ff9900}%d\n{ffffff}Наркотики: {ff9900}%d\n{ffffff}Деньги: {ff9900}%d\n\n{ffffff}Статус: {ff9900}%s\n\n\n", OPG_O_PATRON, OPG_O_METALL, OPG_O_DRUGS, OPG_O_MONEY, OPG_O_STATUS == 0 ? "Закрыт" : "Открыт");
	UpdateDynamic3DTextLabelText(SkladOPGOText, 0xFFFFFFFF, opg_o_ammo);

	new opg_s_ammo[256];
	format(opg_s_ammo, sizeof(opg_s_ammo), "{ffcc00}Склад\n\n{FFFFFF}Патроны: {ff9900}%d\n{ffffff}Металл: {ff9900}%d\n{ffffff}Наркотики: {ff9900}%d\n{ffffff}Деньги: {ff9900}%d\n\n{ffffff}Статус: {ff9900}%s\n\n\n", OPG_S_PATRON, OPG_S_METALL, OPG_S_DRUGS, OPG_S_MONEY, OPG_S_STATUS == 0 ? "Закрыт" : "Открыт");
	UpdateDynamic3DTextLabelText(SkladOPGSText, 0xFFFFFFFF, opg_s_ammo);


	new port_narko[256];
	format(port_narko, sizeof(port_narko), "{"cblue"}Наркотики\n\n{FFFFFF}Количество: %d\n{"cblue"}Стоимость:\n1 {FFFFFF}гр. - {"cblue"}500 {FFFFFF}рублей\n\n\n\n\n\n{"cblue"}___", ALL_NARKO);
	UpdateDynamic3DTextLabelText(PortNarkoText, 0xFFFFFFFF, port_narko);
	return 1;
}
stock SaveRepository()
{
	new query[96];
	format(query, sizeof query, "UPDATE `repositories` SET `army_met` = '%d'", REPOSITORY_ARMY_METALL);
    mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `army_patr` = '%d'", REPOSITORY_ARMY_PATRON);
	mysql_tquery(connects, query, "", "");

	format(query, sizeof query, "UPDATE `repositories` SET `OPG_O_METALL` = '%d'", OPG_O_METALL);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_O_PATRON` = '%d'", OPG_O_PATRON);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_O_DRUGS` = '%d'", OPG_O_DRUGS);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_O_MONEY` = '%d'", OPG_O_MONEY);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_O_STATUS` = '%d'", OPG_O_STATUS);
	mysql_tquery(connects, query, "", "");

	format(query, sizeof query, "UPDATE `repositories` SET `OPG_S_METALL` = '%d'", OPG_S_METALL);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_S_PATRON` = '%d'", OPG_S_PATRON);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_S_DRUGS` = '%d'", OPG_S_DRUGS);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_S_MONEY` = '%d'", OPG_S_MONEY);
	mysql_tquery(connects, query, "", "");
	format(query, sizeof query, "UPDATE `repositories` SET `OPG_S_STATUS` = '%d'", OPG_S_STATUS);
	mysql_tquery(connects, query, "", "");

	format(query, sizeof query, "UPDATE `repositories` SET `ALL_NARKO` = '%d'", ALL_NARKO);
	mysql_tquery(connects, query, "", "");

	UpdateRepository();

	return 1;
}

stock StealPatron(playerid)
{
	new patr = random(4) + 1;

	if(REPOSITORY_ARMY_PATRON < patr) return 1;

	if(PlayerInfo[playerid][pVIP] > 0)
	{
		if(PlayerInfo[playerid][pPatr] + patr > 600)
			return GameTextForPlayer(playerid, "~r~FULL", 1500, 6);
    }
	else
	{
		if(PlayerInfo[playerid][pPatr] + patr > 400)
			return GameTextForPlayer(playerid, "~r~FULL", 1500, 6);
	}


	PlayerInfo[playerid][pPatr] += patr;
	REPOSITORY_ARMY_PATRON -= patr;
	SaveRepository();

	new fmt_msg[100];

	format(fmt_msg, sizeof fmt_msg, "~b~+%d~n~~g~total: %d", patr, PlayerInfo[playerid][pPatr]);
	GameTextForPlayer(playerid, fmt_msg, 1500, 6);

    SaveAccounts(playerid);

	return 1;
}