CMD:fill(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, red, "Вы должны находится за рулем автомобиля!");

    new b;
    foreach(new i : Allbusiness) if(BusinessInfo[i][bType] == b_type_FILL) if(IsPlayerInRangeOfPoint(playerid, 3.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]))
    {
        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
        if(engine == 1) return SCM(playerid, red, "Для начала заглушите двигатель!");
        b = i;
        SetPVarInt(playerid, "fill_biz_id", b);

        new fmt_dialog[256];
        format(fmt_dialog, sizeof(fmt_dialog), "{ffffff}Введите количество литров, которым вы хотите заправить авто.\nСтоимость {"cblue"}1 л. {ffffff}бензина составляет {"cblue"}%d рублей{ffffff}.", BusinessInfo[b][bFillPrice]);

        return SPD(playerid, D_FILL, DIALOG_STYLE_INPUT, "{"cblue"}Заправка авто", fmt_dialog, "Далее", "Отмена");
    }
    return SCM(playerid, red, "Вы должны находится возле АЗС!");
}

CMD:buyk(playerid)
{
    if(IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "Вы не должны находится в автомобиле!");

    new b;
    foreach(new i : Allbusiness) if(BusinessInfo[i][bType] == b_type_FILL) if(IsPlayerInRangeOfPoint(playerid, 3.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]))
    {
        b = i;
        SetPVarInt(playerid, "fill_biz_id", b);

        if(PlayerInfo[playerid][pCash] < BusinessInfo[b][bFillPrice]*20) return SCM(playerid, red, "У вас не достаточно денег!");

        GiveMoney(playerid, -BusinessInfo[b][bFillPrice]*20, "Покупка канисты");

        SetPVarInt(playerid, "have_jerrican", 1);
        SetPlayerAttachedObject(playerid, 3, 1650, 5, 0.15, 0.0, 0.0, 0.0, -90.0, 180.0, 1.0, 1.0, 1.0, 0);
        
        SCM(playerid, blue, "Вы успешно купили канистру. Подойдите к авто и нажмите {"cyellow"}\"H\" {"cblue"}что б его заправить.");
        return GiveBusinessMoney(b, BusinessInfo[b][bFillPrice]*20, playerid);
    }
    return SCM(playerid, red, "Вы должны находится возле АЗС!");
}




public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_FILL:
		{
            if(!response) DeletePVar(playerid, "fill_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "fill_biz_id");
                new vehicleid = GetPlayerVehicleID(playerid);
                if( vehicle[vehicleid][veh_fuel] + strval(inputtext) > 100.0) return SCM(playerid, red, "В бензобак вашего автомобиля не поместится столько бензина.");

                if(PlayerInfo[playerid][pCash] < strval(inputtext)*BusinessInfo[b][bFillPrice]) return SCM(playerid, red, "У вас не достаточно денег!");

                vehicle[vehicleid][veh_fuel] = vehicle[vehicleid][veh_fuel] + strval(inputtext);
                GiveMoney(playerid, -(strval(inputtext)*BusinessInfo[b][bFillPrice]), "Покупка бензина");
                GiveBusinessMoney(b, strval(inputtext)*BusinessInfo[b][bFillPrice], playerid);
                new string[144];
                format(string, sizeof(string), "Вы успешно заправили свой автомобиль на {"cyellow"}%d л. {"cblue"}за {"cyellow"}%d руб{"cblue"}.", strval(inputtext), strval(inputtext)*BusinessInfo[b][bFillPrice]);
                SCM(playerid, blue, string);
            }
		}
        case D_FILL_CANISTRA:
        {
            if(!response) return DeletePVar(playerid, "jerrican_fill_car");
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        new vehicleid = GetPVarInt(playerid, "jerrican_fill_car");
                        if(vehicle[vehicleid][veh_fuel] + 20.0 > 100.0) return SCM(playerid, red, "В бензобак транспорта не поместится столько бензина!");

                        
                        SCM(playerid, green, "Вы успешно заправили авто с помощью канистры!");
                        vehicle[vehicleid][veh_fuel] += 20.0;
                        GameTextForPlayer(playerid, "~g~заправлено", 3000, 1);
                        RemovePlayerAttachedObject(playerid,3);
                        DeletePVar(playerid, "have_jerrican");
                        DeletePVar(playerid, "jerrican_fill_car");
                    }
                }
            }
        }
    }
	#if	defined	fill__OnDialogResponse
		return fill__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse fill__OnDialogResponse
#if	defined	fill__OnDialogResponse
	forward fill__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 262144)
    {
        if(GetPVarInt(playerid, "have_jerrican") == 1)
        {
            foreach(new v : Vehicle)
            {
                if(v == INVALID_VEHICLE_ID) continue;
                new Float:x, Float:y, Float:z;
                GetVehiclePos(v, x, y, z);
                if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
                {
                    SetPVarInt(playerid, "jerrican_fill_car", v);
                    return SPD(playerid, D_FILL_CANISTRA, DIALOG_STYLE_LIST, "{"cblue"}Канистра", "{FFFFFF}Вы хотите заправить этот транспорт с канистры?", "Да", "Нет");
                }
            }
        }
    }
	#if	defined	fill__OnPlayerKeyStateChange
		return fill__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange fill__OnPlayerKeyStateChange
#if	defined	fill__OnPlayerKeyStateChange
	forward fill__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

publics secondupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);

    if(second == 20 || second == 40 || second == 59)
    { 
        foreach(new v : Vehicle)
        {
            if(Engines{v} == true)
            {
                vehicle[v][veh_fuel] = vehicle[v][veh_fuel] - 1.0;
            }
        }
    }

    foreach(new v : Vehicle)
    {
        if(Engines{v} == true)
        {
            if(vehicle[v][veh_fuel] < 1.0)
            {
                Engines{v} = false;
                new engine, lights, alarm, doors, bonnet, boot, objective;
                GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
                SetVehicleParamsEx(v, false, lights, alarm, doors, bonnet, boot, objective);
            }
        }
    }
	#if	defined	fill__secondupdate
		return fill__secondupdate();
	#else
		return 1;
	#endif
}
#if	defined	_ALS_secondupdate
	#undef	secondupdate
#else
	#define	_ALS_secondupdate
#endif

#define	secondupdate fill__secondupdate
#if	defined	fill__secondupdate
	forward fill__secondupdate();
#endif

public OnPlayerUpdate(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        new Float:veh_health, v = GetPlayerVehicleID(playerid);
        GetVehicleHealth(v, veh_health);
        if(veh_health < 400.0 && vehicle[v][veh_limit] != 20.0)
        {
            vehicle[v][veh_limit] = 20.0;
        }
        if(veh_health < 305.0 && Engines{v} == true)
        {
            Engines{v} = false;
            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
            SetVehicleParamsEx(v, false, lights, alarm, doors, bonnet, boot, objective);   
            SetVehicleHealth(v, 300.0);            
        }
    }
    #if defined fill__OnPlayerUpdate
        return fill__OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate fill__OnPlayerUpdate
#if defined fill__OnPlayerUpdate
    forward fill__OnPlayerUpdate(playerid);
#endif