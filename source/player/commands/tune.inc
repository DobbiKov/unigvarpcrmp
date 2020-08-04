enum e_DISKS_INFO
{
    diskName[50],
    diskID,
};

new stock disk_tune[][e_DISKS_INFO] = 
{
    {"Shadow", 1073},
    {"Mega", 1074},
    {"Wires", 1076},
    {"Classic", 1077},
    {"Twist", 1078},
    {"Cutter", 1079},
    {"Grove", 1081},
    {"Atomic", 1085},
    {"Dollar", 1083},
    {"Switch", 1080}
};

CMD:tune(playerid)
{
    if(player_in_business[playerid] == -1) return SCM(playerid, red, "Вы не находитесь в СТО!");
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, red, "Вы должны находится за рулем автомобиля!");
    new i = player_in_business[playerid];
    if(BusinessInfo[i][bType] != b_type_REPAIR) return SCM(playerid, red, "Вы не находитесь в СТО!");
    if(IsPlayerInRangeOfPoint(playerid, 10.0, business_params[ BusinessInfo[i][bType] ][coord_menu_x], business_params[ BusinessInfo[i][bType] ][coord_menu_y], business_params[ BusinessInfo[i][bType] ][coord_menu_z]))
    {
        new fmt_dialog[528];
        format(fmt_dialog, sizeof(fmt_dialog), "\
        {"cblue"}1. {FFFFFF}Поставить азот  {"cblue"}5000 рублей\n\
        {"cblue"}2. {FFFFFF}Поставить диски  {"cblue"}4000 рублей\n\
        {"cblue"}3. {FFFFFF}Перекрасить авто  {"cblue"}1000 рублей\n\
        {"cblue"}4. {FFFFFF}Убрать тюнинг с авто {"cblue"}1500 рублей\n\
        {"cblue"}5. {FFFFFF}Отремонтировать авто  {"cblue"}%d рублей", BusinessInfo[i][bRepairPrice]);
        SPD(playerid, D_TUNE, DIALOG_STYLE_LIST, "{"cblue"}СТО", fmt_dialog, "Далее", "Закрыть");
    }
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_TUNE_DISKS:
        {
            if(!response) return cmd::tune(playerid);
            else
            {
                if(PlayerInfo[playerid][pCash] < 4000) return SCM(playerid, red, "У вас не достаточно денег.");

                ownable_car[GetPlayerVehicleID(playerid)][tun_weels] = disk_tune[listitem][diskID];
                AddVehicleComponent(GetPlayerVehicleID(playerid),ownable_car[GetPlayerVehicleID(playerid)][tun_weels]);
                SaveOwnableCar(playerid);
                GiveMoney(playerid, -4000, "Покупка услуги СТО");
                GiveBusinessMoney(player_in_business[playerid], 4000, playerid);
                return SCM(playerid, blue, "Вы приобрели {"cyellow"}Диски {"cblue"}за {"cyellow"}4000 рублей{"cblue"}.");
            }
        }
        case D_TUNE_CHANGE_COLOR:
        {
            if(!response) return cmd::tune(playerid);
            else
            {
				new color[2];
				
				if(sscanf(inputtext, "p<,>d, d", color[0], color[1]))
					return 
						ShowPlayerDialog
						(
							playerid, D_TUNE_CHANGE_COLOR, DIALOG_STYLE_INPUT,
							"{"cblue"}Перекраска авто",
							"{ffffff}Введите цвет в формате: цвет, цвет. Пример: 1, 1",
							"Перекрасить", "Отмена"
						);  
				
				new vehicleid = GetPlayerVehicleID(playerid);
				
				if(player_ownable_car[playerid] != vehicleid) return SCM(playerid, red, "Вы должны находиться в своём личном авто.");
						
				if(PlayerInfo[playerid][pCash] < 1000) return SCM(playerid, red, "У вас не достаточно денег.");
				
				
				if(!(0 <= color[0] <= 255) || !(0 <= color[1] <= 255))
				{
					SCM(playerid, red, "ID цвета от 0 до 255.");
					
					return 
						ShowPlayerDialog
						(
							playerid, D_TUNE_CHANGE_COLOR, DIALOG_STYLE_INPUT,
							"{"cblue"}Перекраска авто",
							"{ffffff}Введите цвет в формате: цвет, цвет. Пример: 1, 1",
							"Перекрасить", "Отмена"
						);  
				}

                GiveMoney(playerid, -1000, "Перекраска авто в СТО");
				GiveBusinessMoney(player_in_business[playerid], 1000, playerid);
				UpdateBusiness(player_in_business[playerid]);
				
				ownable_car[vehicleid][oc_color_1] = color[0];
				ownable_car[vehicleid][oc_color_2] = color[1];
				
				ChangeVehicleColor(vehicleid, color[0], color[1]);
				SCM(playerid, blue, "Вы успешно перекрасили своё авто за {"cyellow"}1000 рублей{"cblue"}.");
            }
        }
		case D_TUNE:
		{
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(GetPlayerVehicleID(playerid) != player_ownable_car[playerid]) return SCM(playerid, red, "Вы должны находится в личном транспорте.");
                        if(PlayerInfo[playerid][pCash] < 5000) return SCM(playerid, red, "У вас не достаточно денег.");

                        GiveMoney(playerid, -5000, "Покупка услуги СТО");
                        GiveBusinessMoney(player_in_business[playerid], 5000, playerid);

                        AddVehicleComponent(GetPlayerVehicleID(playerid),1010);
                        ownable_car[GetPlayerVehicleID(playerid)][tun_nitro] = 1010;
                        SaveOwnableCar(playerid);
                        return SCM(playerid, blue, "Вы купили {"cyellow"}Nitro {"cblue"}за {"cyellow"}5000 рублей{"cblue"}.");
                    }
                    case 1:
                    {
                        if(GetPlayerVehicleID(playerid) != player_ownable_car[playerid]) return SCM(playerid, red, "Вы должны находится в личном транспорте.");

                        new fmt_dialog[528], string[180];
                        for(new i = 0; i < sizeof(disk_tune); i++)
                        {
                            format(string, sizeof(string), "{"cblue"}%d. {FFFFFF}%s\n", i+1, disk_tune[i][diskName]);
                            strcat(fmt_dialog, string);
                        }

                        SPD
                        (
                            playerid, D_TUNE_DISKS, DIALOG_STYLE_LIST,
                            "{"cblue"}Тюнинг | Диски",
                            fmt_dialog,
                            "Далее", "Отмена"
                        );
                    }
                    case 2:
                    {
                        if(GetPlayerVehicleID(playerid) != player_ownable_car[playerid]) return SCM(playerid, red, "Вы должны находится в личном транспорте.");

						ShowPlayerDialog
						(
							playerid, D_TUNE_CHANGE_COLOR, DIALOG_STYLE_INPUT,
							"{"cblue"}Перекраска авто",
							"{ffffff}Введите цвет в формате: цвет, цвет. Пример: 1, 1",
							"Перекрасить", "Отмена"
						);                       
                    }
                    case 3: 
                    {
                        if(GetPlayerVehicleID(playerid) != player_ownable_car[playerid]) return SCM(playerid, red, "Вы должны находится в личном транспорте.");
                        if(PlayerInfo[playerid][pCash] < 1500) return SCM(playerid, red, "У вас не достаточно денег.");

                        GiveMoney(playerid, -1500, "Покупка услуги СТО");
                        GiveBusinessMoney(player_in_business[playerid], 1500, playerid);

						if(ownable_car[GetPlayerVehicleID(playerid)][tun_weels] != 0) RemoveVehicleComponent(GetPlayerVehicleID(playerid), ownable_car[GetPlayerVehicleID(playerid)][tun_weels]), ownable_car[GetPlayerVehicleID(playerid)][tun_weels] = 0;
						if(ownable_car[GetPlayerVehicleID(playerid)][tun_nitro] != 0) RemoveVehicleComponent(GetPlayerVehicleID(playerid), ownable_car[GetPlayerVehicleID(playerid)][tun_nitro]), ownable_car[GetPlayerVehicleID(playerid)][tun_nitro] = 0;

                        SaveOwnableCar(playerid);

                        return SCM(playerid, blue, "Вы убрали тюнинг с вашего транспорта за {"cyellow"}1500 рублей{"cblue"}.");
                    }
                    case 4:
                    {
                        if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "Вы должны находится в авто.");
                        if(PlayerInfo[playerid][pCash] < BusinessInfo[ player_in_business[playerid] ][bRepairPrice]) return SCM(playerid, red, "У вас не достаточно денег!");

                        GiveMoney(playerid, -BusinessInfo[ player_in_business[playerid] ][bRepairPrice], "Ремонт авто в СТО!");
                        GiveBusinessMoney(player_in_business[playerid], BusinessInfo[ player_in_business[playerid] ][bRepairPrice], playerid);
                        SCM(playerid, blue, "Вы отремонтировали свое авто.");
                        RepairVehicle(GetPlayerVehicleID(playerid));
                    }
                }
            }
		}
    }
	#if	defined	tune__OnDialogResponse
		return tune__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse tune__OnDialogResponse
#if	defined	tune__OnDialogResponse
	forward tune__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif