const MAX_OWNABLE_CARS = MAX_VEHICLES;

enum E_OWNABLE_CAR
{
    oc_id,
	oc_owner_id,
	oc_number[32],
	oc_modelid,
	oc_color_1,
	oc_color_2,
	bool: oc_lock_status,
	Float: oc_mileage,
	Float: oc_fuel,
	Float: oc_health,
	tun_weels,
	tun_nitro,
	cost_car
};

new ownable_car[MAX_OWNABLE_CARS][E_OWNABLE_CAR];
new ownable_car_id[MAX_OWNABLE_CARS] = {-1, ...};
new Text3D: ownable_car_label[MAX_OWNABLE_CARS] = {Text3D: -1, ...};
new player_ownable_car[MAX_PLAYERS] = {-1, ...};


stock SaveOwnableCar(playerid)
{
    new Float: veh_health, vehicleid = player_ownable_car[playerid];
    GetVehicleHealth(vehicleid, veh_health);
    ownable_car[vehicleid][oc_lock_status] = vehicle[vehicleid][veh_lock];
    ownable_car[vehicleid][oc_mileage] = vehicle[vehicleid][veh_mileage];
    ownable_car[vehicleid][oc_fuel] = vehicle[vehicleid][veh_fuel];
    ownable_car[vehicleid][oc_health] = veh_health;

    new number[32];
    if(strval(ownable_car[vehicleid][oc_number]) == -1) number = "-1";
    else strcat(number, ownable_car[vehicleid][oc_number]);

    new color[20];
    format(color, sizeof(color), "%d,%d", ownable_car[vehicleid][oc_color_1], ownable_car[vehicleid][oc_color_2]);

    new sql[528];
    format
    (
        sql, sizeof(sql), 
        "UPDATE `ownable_cars` SET `owner_id` = '%d', `model_id` = '%d', `lock` = '%d', `weels` = '%d', `nitro` = '%d', `cost_car` = '%d', `mileage` = '%f', `fuel` = '%f', `health` = '%f', `color` = '%s' WHERE `id` = '%d'",
        ownable_car[vehicleid][oc_owner_id],
        ownable_car[vehicleid][oc_modelid],
        ownable_car[vehicleid][oc_lock_status],
        ownable_car[vehicleid][tun_weels],
        ownable_car[vehicleid][tun_nitro],
        ownable_car[vehicleid][cost_car],
        ownable_car[vehicleid][oc_mileage],
        ownable_car[vehicleid][oc_fuel],
        ownable_car[vehicleid][oc_health],
        color,
        ownable_car[vehicleid][oc_id]
    );
    mysql_tquery(connects, sql, "", "");
    return 1;
} 
publics LoadMyCar(playerid)
{
    if(player_ownable_car[playerid] != -1) return SCM(playerid, red, "Вы уже забрали ваше авто.");

    static rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        static id, owner_id, model_id, color[10], color_1, color_2, number[32], Float:mileage, lock, Float:fuel, Float:health, weels, nitro, cost_car_;

        id = cache_get_field_content_int(0, "id");
        owner_id = cache_get_field_content_int(0, "owner_id");
        model_id = cache_get_field_content_int(0, "model_id");
        lock = cache_get_field_content_int(0, "lock");
        weels = cache_get_field_content_int(0, "weels");
        nitro = cache_get_field_content_int(0, "nitro");
        cost_car_ = cache_get_field_content_int(0, "cost_car");

        cache_get_field_content(0, "color", color, connects, 64);
        cache_get_field_content(0, "number", number, connects, 64);

        mileage = cache_get_field_content_float(0, "mileage");
        fuel = cache_get_field_content_float(0, "fuel");
        health = cache_get_field_content_float(0, "health");

        sscanf(color, "p<,>dd", color_1, color_2);


        if(PlayerInfo[playerid][pHomeID] != -1)
        {
            new h;
            foreach(new i : Allhouses) if(HouseInfo[i][hID] == PlayerInfo[playerid][pHomeID])
            {
                h = i;
                break;
            }

			CreateOwnableCar
			(
				playerid,
				owner_id,
				number,
				model_id,
				color_1,
				color_2,
                HouseInfo[h][car_pos_x],
                HouseInfo[h][car_pos_y],
                HouseInfo[h][car_pos_z],
                HouseInfo[h][car_pos_a],
				lock,
				mileage,
				fuel,	
				health,
				weels,
				nitro,
				cost_car_,
                id
			);
        }
        else if(PlayerInfo[playerid][pKvartID] != -1 && PlayerInfo[playerid][pPodID] != -1)
        {
            new h;
            foreach(new i : Allpodezd) if(PodezdInfo[i][pod_id] == PlayerInfo[playerid][pPodID])
            {
                h = i;
                break;
            }

			CreateOwnableCar
			(
				playerid,
				owner_id,
				number,
				model_id,
				color_1,
				color_2,
                PodezdInfo[h][a_car_pos_x],
                PodezdInfo[h][a_car_pos_y],
                PodezdInfo[h][a_car_pos_z],
                PodezdInfo[h][a_car_pos_a],
				lock,
				mileage,
				fuel,	
				health,
				weels,
				nitro,
				cost_car_,
                id
			);
        }
    }
    else
    {
        if(PlayerInfo[playerid][pHomeID] == -1) return SCM(playerid, red, !"У вас нет личного странспорта.");
    }
    return 1;
}

publics CreateOwnableCar(playerid, ownerid, number[], modelid, color_1, color_2, Float: pos_x, Float: pos_y, Float: pos_z, Float: angle, lock, Float:mileage, Float:fuel, Float: health, weels, nitro, cost_car_, id)
{
	player_ownable_car[playerid] = CreateVehicle(modelid, pos_x, pos_y, pos_z, angle, color_1, color_2, -1);
	
	new vehicleid = player_ownable_car[playerid];
		
	ownable_car_id[vehicleid] = vehicleid;
	
	ownable_car[vehicleid][oc_owner_id] = ownerid;
	
	new n_text[32];
	format(n_text, sizeof n_text, "%s", number);
	
	if(!strcmp(number, "None", false))
    {
        strcat(ownable_car[vehicleid][oc_number], "None"); 
        ownable_car_label[vehicleid] = CreateDynamic3DTextLabel("[ НЕТ НОМЕРОВ ]", 0xFFFFFFFF, 0.0, 0.0, 0.0, 15.0, INVALID_PLAYER_ID, vehicleid);
    }
    else 
    {
        format(ownable_car[vehicleid][oc_number], 32, "%s", number); 
        ownable_car_label[vehicleid] = CreateDynamic3DTextLabel(ownable_car[vehicleid][oc_number], 0xFFFFFFFF, 0.0, 0.0, 0.0, 15.0, INVALID_PLAYER_ID, vehicleid);
    }

	ownable_car[vehicleid][oc_modelid] = 	modelid;
	ownable_car[vehicleid][oc_color_1] = 	color_1;
	ownable_car[vehicleid][oc_color_2] = 	color_2;

	ownable_car[vehicleid][oc_id] = 	id;
	
	ownable_car[vehicleid][oc_lock_status] =	bool: lock;
	
	ownable_car[vehicleid][oc_mileage] =		mileage;
	
	ownable_car[vehicleid][tun_weels] =		weels;
	ownable_car[vehicleid][tun_nitro] = 	nitro;
	
	ownable_car[vehicleid][cost_car] =		cost_car_;
	
	if(ownable_car[vehicleid][tun_weels] != 0) AddVehicleComponent(vehicleid, ownable_car[vehicleid][tun_weels]);
	if(ownable_car[vehicleid][tun_nitro] != 0) AddVehicleComponent(vehicleid, ownable_car[vehicleid][tun_nitro]);

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);	
	SetVehicleParamsEx(vehicleid, 0, lights, alarm, ownable_car[vehicleid][oc_lock_status], bonnet, boot, objective);

	if(fuel < 0.0)
		fuel = 0.0;
		
	if(health < 280.0)
		health = 290.0;
	
    vehicle[vehicleid][veh_mileage] = mileage;
	vehicle[vehicleid][veh_fuel] = fuel;
	SetVehicleHealth(vehicleid, health);
	
	return vehicleid;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerInfo[playerid][pLogin] == true) if(PlayerInfo[playerid][pCarID] != -1) if(player_ownable_car[playerid] != -1) 
    {
       SaveOwnableCar(playerid);
       DestroyDynamic3DTextLabel(ownable_car_label[player_ownable_car[playerid]]);
       DestroyVehicle(player_ownable_car[playerid]);
    }
    #if defined ownable_car__OnPlayerDisconnect
        return ownable_car__OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect ownable_car__OnPlayerDisconnect
#if defined ownable_car__OnPlayerDisconnect
    forward ownable_car__OnPlayerDisconnect(playerid, reason);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_SELL_CAR:
		{
            if(!response) return 1;
            else
            {
                GiveBankMoney(playerid, (ownable_car[player_ownable_car[playerid]][cost_car] / 10) * 8, "Продажа транспорта в госс.");
                
                SCM(playerid, blue, "Вы продали транспорт.");
                new string[144];
                format(string, sizeof(string), "Налоговый сбор составляет 20 процентов от его стоимости {"cblue"}(%d рублей)", floatround((ownable_car[player_ownable_car[playerid]][cost_car] / 10) * 2, floatround_round));
                SCM(playerid, white, string);

                format(string, sizeof(string), "На основной банковский счет переведено {"cwhite"}%d рублей", floatround((ownable_car[player_ownable_car[playerid]][cost_car] / 10) * 8, floatround_round));
                SCM(playerid, blue, string);

                format(string, sizeof(string), "DELETE FROM `ownable_cars` WHERE `id` = '%d'", ownable_car[player_ownable_car[playerid]][oc_id]);
                mysql_tquery(connects, string, "", "");

                DestroyDynamic3DTextLabel(ownable_car_label[player_ownable_car[playerid]]);
                DestroyVehicle(player_ownable_car[playerid]);
                player_ownable_car[playerid] = -1;
                PlayerInfo[playerid][pCarID] = -1;
            }
		}
    }
	#if	defined	ownable_car__OnDialogResponse
		return ownable_car__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse ownable_car__OnDialogResponse
#if	defined	ownable_car__OnDialogResponse
	forward ownable_car__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

CMD:sellcar(playerid)
{
    if(PlayerInfo[playerid][pCarID] == -1) return SCM(playerid, red, "У вас нет личного транспорта.");
    if(player_ownable_car[playerid] == -1) return SCM(playerid, red, "Ваш личный транспорт не создан.");

    new fmt_dialog[528];
    format
    (
        fmt_dialog, sizeof(fmt_dialog),
        "{FFFFFF}\
        Модель:\t%s(№%d)\n\
        Стоимость:\t%d\n\n\
        Вы уверенны, что хотите продать ваш транспорт?\n\
        На ваш банковский счет будет начислено %d рублей.\n\n\
        Если вы хотите продать транспорт другому игроку,\n\
        используйте команду /sellmycar",
        GetCarName(GetVehicleModel(player_ownable_car[playerid])),
        GetVehicleModel(player_ownable_car[playerid]),
        ownable_car[player_ownable_car[playerid]][cost_car],
        floatround((ownable_car[player_ownable_car[playerid]][cost_car] / 10) * 8, floatround_round)
    );
    SPD
    (
        playerid, D_SELL_CAR, DIALOG_STYLE_MSGBOX,
        !"{"cblue"}Продажа транспорта",
        fmt_dialog,
        !"Да", !"Нет"
    );
    return 1;
}
CMD:sellmycar(playerid, params[])
{
    if(PlayerInfo[playerid][pCarID] == -1) return SCM(playerid, red, "У вас нет автомобиля!");
    if(player_ownable_car[playerid] == -1) return SCM(playerid, red, "Ваш личный транспорт не создан.");

    extract params -> new to_player, price; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /sellmycar [ID игрока] [цена]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);

    if(PlayerInfo[to_player][pCarID] != -1) return SCM(playerid, red, "У игрока уже имеется личный транспорт.");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока нет столько денег.");
    if(price < 0) return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /sellmycar [ID игрока] [цена]");

    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerVehicleID(playerid) != player_ownable_car[playerid]) return SCM(playerid, red, "Вы должны находится в личном транспорте.");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_SELLCAR, price);
}
CMD:car(playerid)
{
    if(PlayerInfo[playerid][pCarID] == -1) return SCM(playerid, red, "У вас нет личного транспорта.");
    if(player_ownable_car[playerid] == -1) return SCM(playerid, red, "Ваш личный транспорт не создан.");

    new fmt_dialog[528], number[32];
    if(!strcmp(ownable_car[player_ownable_car[playerid]][oc_number], "None", false)) number = "-----";
    else strcat(number, ownable_car[player_ownable_car[playerid]][oc_number]);
    format
    (
        fmt_dialog, sizeof(fmt_dialog),
        "\
        {FFFFFF}Номер: \t{"cblue"}%s\n\
        {FFFFFF}Модель: \t{"cblue"}%s(%d)\n\
        {FFFFFF}Стоимость: \t{"cblue"}%d",
        number,
        GetCarName(GetVehicleModel(player_ownable_car[playerid])), GetVehicleModel(player_ownable_car[playerid]),
        ownable_car[player_ownable_car[playerid]][cost_car]
    );
    SPD
    (
        playerid, D_NULL, DIALOG_STYLE_MSGBOX,
        !"{"cblue"}Личный транспорт",
        fmt_dialog,
        !"Закрыть", !""
    );
    return 1;
}

stock DestroyOwnableCar(playerid)
{
    if(PlayerInfo[playerid][pLogin] == true) if(PlayerInfo[playerid][pCarID] != -1) if(player_ownable_car[playerid] != -1) 
    {
       SaveOwnableCar(playerid);
       DestroyDynamic3DTextLabel(ownable_car_label[player_ownable_car[playerid]]);
       DestroyVehicle(player_ownable_car[playerid]);
    }
    return 1;
}