#define MAX_BUSINESS 100

#define b_type_24_7     1
#define b_type_APTEKA   2
#define b_type_EAT      3
#define b_type_CASINO   4
#define b_type_REPAIR   5
#define b_type_FILL     6

new player_in_business[MAX_PLAYERS] = -1;

enum business_params_info
{
	bname[32],
	btype,
	b_rent_price,
	Float: exit_x,
	Float: exit_y,
	Float: exit_z,
	Float: exit_angle,
	Float: coord_menu_x,
	Float: coord_menu_y,
	Float: coord_menu_z,
	b_type_pred[32],
	icon,
    pickup,
    menu_pick,
}

new business_params[7][business_params_info] =
{
	{"INVALID BUSINESS ID!", 	0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "INVALID BUSINESS ID", 0, 19132, 1},
	{"Магазин 24/7", 			1, 4000, 528.7020,1716.8123,2003.1100,175.9414, 538.3618,1727.5958,2003.1100, "24/7", 17, 19132, 2941},
	{"Аптека", 					2, 3000, -250.8096,1296.8456,1013.0979,176.2207,-250.7598,1300.6337,1013.0979, "Аптека", 22, 19132, 1239},
	{"Столовая", 				3, 2000, 377.0810,-192.9939,1000.6423,1.2533, 379.1561,-184.9244,1000.6350, "Столовая", 10, 19132, 1239},
	{"Казино", 					4, 6000, 1692.1874,2068.0063,-7.8350,267.6344,0.0, 0.0,0.0, "Казино", 25, 19132, 1239},
	{"СТО", 					5, 7000, 2516.1006,-2138.0664,1127.4161, 272.0187, 2516.1006,-2138.0664,1127.4161, "СТО", 27, 1073, 1},
	{"АЗС",		            	6, 9000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "АЗС", 48, 1650, 1}
};

new Iterator: Allbusiness<MAX_BUSINESS>;
enum E_BIZ_INFO
{
    bID,
    bOwned,
    bOwner[MAX_PLAYER_NAME],
    bType,
    bPrice,
    bCash,
    bProfit,
    Float:bExitX,
    Float:bExitY,
    Float:bExitZ,
    Text3D: bLabel,
    bEnterPickup,
    bExitPickup,
    bMenuPick,
    bControl,
    bEnterPrice,
    bFillPrice,
    bRepairPrice,
    bDays,
}
new BusinessInfo[MAX_BUSINESS][E_BIZ_INFO];
new totalbusiness;

publics LoadBusiness()
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            BusinessInfo[i][bID] = cache_get_field_content_int(i, "bID");
            BusinessInfo[i][bOwned] = cache_get_field_content_int(i, "bOwned");
            BusinessInfo[i][bCash] = cache_get_field_content_int(i, "bCash");
            BusinessInfo[i][bProfit] = cache_get_field_content_int(i, "bProfit");
            BusinessInfo[i][bPrice] = cache_get_field_content_int(i, "bPrice");
            BusinessInfo[i][bType] = cache_get_field_content_int(i, "bType");

            BusinessInfo[i][bFillPrice] = cache_get_field_content_int(i, "bFillPrice");
            BusinessInfo[i][bRepairPrice] = cache_get_field_content_int(i, "bRepairPrice");
            BusinessInfo[i][bControl] = cache_get_field_content_int(i, "bControl");
            BusinessInfo[i][bEnterPrice] = cache_get_field_content_int(i, "bEnterPrice");
            BusinessInfo[i][bDays] = cache_get_field_content_int(i, "bDays");

            BusinessInfo[i][bExitX] = cache_get_field_content_float(i, "bExitX");
            BusinessInfo[i][bExitY] = cache_get_field_content_float(i, "bExitY");
            BusinessInfo[i][bExitZ] = cache_get_field_content_float(i, "bExitZ");
            cache_get_field_content(i, "bOwner", BusinessInfo[i][bOwner], connects, MAX_PLAYER_NAME);

            CreateDynamicMapIcon(BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ], business_params[ BusinessInfo[i][bType] ][icon], -1, -1, -1, -1, 200.0);

            BusinessInfo[i][bLabel] = CreateDynamic3DTextLabel("__", 0xFFFFFFFF, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
            BusinessInfo[i][bEnterPickup] = CreateDynamicPickup(business_params[ BusinessInfo[i][bType] ][pickup], 23, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]);
            BusinessInfo[i][bExitPickup] = CreateDynamicPickup(business_params[ BusinessInfo[i][bType] ][pickup], 23, business_params[ BusinessInfo[i][bType] ][ exit_x ], business_params[ BusinessInfo[i][bType] ][ exit_y ], business_params[ BusinessInfo[i][bType] ][ exit_z ], BusinessInfo[i][bID]);

            BusinessInfo[i][bExitPickup] = CreateDynamicPickup(business_params[ BusinessInfo[i][bType] ][pickup], 23, business_params[ BusinessInfo[i][bType] ][ exit_x ], business_params[ BusinessInfo[i][bType] ][ exit_y ], business_params[ BusinessInfo[i][bType] ][ exit_z ], BusinessInfo[i][bID]);
            
            if(BusinessInfo[i][bType] > 0 && BusinessInfo[i][bType] < 6) BusinessInfo[i][bMenuPick] = CreateDynamicPickup(business_params[ BusinessInfo[i][bType] ][menu_pick], 23, business_params[BusinessInfo[i][bType]][coord_menu_x], business_params[BusinessInfo[i][bType]][coord_menu_y], business_params[BusinessInfo[i][bType]][coord_menu_z], BusinessInfo[i][bID]);
            totalbusiness++;

            Iter_Add(Allbusiness, i);


            UpdateBusiness(i);
            //Buybusiness(i);
        }
    }
    printf("[UNIGVA]: Всего загружено бизнессов: %d", totalbusiness);
    return 1;
}

stock SaveBusiness(id)
{
    new sql[1024];
    format
    (
        sql, sizeof(sql), 
        "UPDATE `bussines` SET `bOwned` = '%d', `bOwner` = '%s', `bPrice` = '%d', `bType` = '%d', `bCash` = '%d', `bProfit` = '%d', `bExitX` = '%f', `bExitY` = '%f', `bExitZ` = '%f', `bControl` = '%d', `bEnterPrice` = '%d', `bFillPrice` = '%d', `bRepairPrice` = '%d', `bDays` = '%d' WHERE `bID` = '%d'",
        BusinessInfo[id][bOwned],
        BusinessInfo[id][bOwner],
        BusinessInfo[id][bPrice],
        BusinessInfo[id][bType],
        BusinessInfo[id][bCash],
        BusinessInfo[id][bProfit],
        BusinessInfo[id][bExitX],
        BusinessInfo[id][bExitY],
        BusinessInfo[id][bExitZ],
        BusinessInfo[id][bControl],
        BusinessInfo[id][bEnterPrice],
        BusinessInfo[id][bFillPrice],
        BusinessInfo[id][bRepairPrice],
        BusinessInfo[id][bDays],
        BusinessInfo[id][bID]
    );
    mysql_tquery(connects, sql, "", "");
    return 1;
}

stock UpdateBusiness(id)
{

    new enter_price[32];
    new owner[MAX_PLAYER_NAME] = "";
    if(BusinessInfo[id][bOwned] == 0) strcat(owner, "Государство");
    else strcat(owner, BusinessInfo[id][bOwner]);

    new fmt_msg[528];
    valstr(enter_price, BusinessInfo[id][bEnterPrice]);
    strcat(enter_price, " рублей");

    if(BusinessInfo[id][bType] == b_type_REPAIR)
    {
        format(fmt_msg, sizeof(fmt_msg), "\
            {0099FF}%s\n\
            {FFFFFF}Владелец: {99cc00}%s\n\
            {FFFFFF}Стоимость: {0099FF}%d рублей\n\
            {FFFFFF}Стоимость починки: {0099FF}%d рублей\n\
            {FFFFFF}Крыша: {0099FF}%s",
            business_params[ BusinessInfo[id][bType] ][bname],
            owner,
            BusinessInfo[id][bPrice],
            BusinessInfo[id][bRepairPrice],
            (BusinessInfo[id][bControl] == 0) ? ("Отсутствует") : ( GetMember[BusinessInfo[id][bControl]] )
        );
    }
    else if(BusinessInfo[id][bType] == b_type_FILL)
    {
        format(fmt_msg, sizeof(fmt_msg), "\
            /buyk - купить канистру\n\
            /fill - заправить авто\n\n\
            {0099FF}%s\n\n\
            {FFFFFF}Владелец: {99cc00}%s\n\
            {FFFFFF}Стоимость: {0099FF}%d рублей\n\
            {FFFFFF}Цена за 1 литр бензина: {0099FF}%d рублей\n\
            {FFFFFF}Крышует: {0099FF}%s",
            business_params[BusinessInfo[id][bType]][bname],
            owner,
            BusinessInfo[id][bPrice],
            BusinessInfo[id][bFillPrice],
            (BusinessInfo[id][bControl] == 0) ? ("Отсутствует") : ( GetMember[BusinessInfo[id][bControl]] )
        );
    }
    else
    {
        format(fmt_msg, sizeof(fmt_msg), "\
            {0099FF}%s\n\
            {FFFFFF}Владелец: {99cc00}%s\n\
            {FFFFFF}Стоимость: {0099FF}%d рублей\n\
            {FFFFFF}Крышует: {0099FF}%s\n\
            {FFFFFF}Вход: {0099FF}%s",
            business_params[BusinessInfo[id][bType]][bname],
            owner,
            BusinessInfo[id][bPrice],
            (BusinessInfo[id][bControl] == 0) ? ("Отсутствует") : ( GetMember[BusinessInfo[id][bControl]] ),
            (BusinessInfo[id][bEnterPrice] == 0) ? ("Бесплатный") : (enter_price)
        );
    }

    UpdateDynamic3DTextLabelText(BusinessInfo[id][bLabel], 0xFFCC00FF, fmt_msg);

    SaveBusiness(id);
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        foreach(new i : Allbusiness)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]))
            {
                if(BusinessInfo[i][bType] < 5)
                {
                    if(BusinessInfo[i][bEnterPrice] > 0)
                    {
                        new string[144];
                        format(string, sizeof(string), "{FFFFFF}Вход платный и составляет {"cblue"}%d рублей\n{FFFFFF}Вы уверенны, что хотите войти сюда?", BusinessInfo[i][bEnterPrice]);
                        SetPVarInt(playerid, "biz_id_enter", i);
                        SPD(playerid, D_ENTER_BIZ, DIALOG_STYLE_MSGBOX, "{"cblue"}Бизнесс | Вход", string, "Войти", "Отмена");
                    }
                    else
                    {
                        FreezePlayer(playerid, 2000);
                        SetPlayerPos(playerid, business_params[ BusinessInfo[i][bType] ][exit_x], business_params[ BusinessInfo[i][bType] ][exit_y], business_params[ BusinessInfo[i][bType] ][exit_z]);
                        SetPlayerFacingAngle(playerid, business_params[ BusinessInfo[i][bType] ][exit_angle]);
                        SetPlayerVirtualWorld(playerid, BusinessInfo[i][bID]);
                        if(BusinessInfo[i][bType] == b_type_EAT) SetPlayerInterior(playerid, 17);
                        player_in_business[playerid] = i;
                    }
                }
            }

        }
        if(player_in_business[playerid] != -1)
        {
            new i = player_in_business[playerid];
            if(IsPlayerInRangeOfPoint(playerid, 2.0, business_params[BusinessInfo[i][bType]][exit_x], business_params[BusinessInfo[i][bType]][exit_y], business_params[BusinessInfo[i][bType]][exit_z]))
            {
                if(BusinessInfo[i][bType] < 5)
                {
                    SetPlayerPos(playerid, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]);
                    SetPlayerVirtualWorld(playerid, 0);
                    SetPlayerInterior(playerid, 0);
                    player_in_business[playerid] = -1;
                }
            }

            if(BusinessInfo[i][bType] > 0 && BusinessInfo[i][bType] < 5)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, business_params[BusinessInfo[i][bType]][coord_menu_x], business_params[BusinessInfo[i][bType]][coord_menu_y], business_params[BusinessInfo[i][bType]][coord_menu_z]))
                {
                    ShowPlayerBusinessMenu(playerid, i);
                }
            }
        }
    }
    if(newkeys == 2)
    {
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            if(player_in_business[playerid] == -1)
            {
                foreach(new i : Allbusiness)
                {
                    if(BusinessInfo[i][bType] == b_type_REPAIR)
                    {
                        if(IsPlayerInRangeOfPoint(playerid, 5.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]))
                        {
                            new vehicleid = GetPlayerVehicleID(playerid);
                            SetVehicleVirtualWorld ( vehicleid, BusinessInfo[i][bID]);
                            SetPlayerVirtualWorld(playerid, BusinessInfo[i][bID]);
                            SetVehiclePos(vehicleid, business_params[ BusinessInfo[i][bType] ][ exit_x ], business_params[ BusinessInfo[i][bType] ][ exit_y ], business_params[ BusinessInfo[i][bType] ][ exit_z ]);
                            SetVehicleZAngle(vehicleid, business_params[ BusinessInfo[i][bType] ][ exit_angle ]);
                            PutPlayerInVehicle(playerid, vehicleid, 0);
                            return player_in_business[playerid] = i;
                        }
                    }
                }
            }
            else if(player_in_business[playerid] != -1 && BusinessInfo[ player_in_business[playerid] ][bType] == b_type_REPAIR)
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                new i = player_in_business[playerid];
                SetVehicleVirtualWorld ( vehicleid, 0) ;
                SetPlayerVirtualWorld(playerid, 0);
                SetVehiclePos(vehicleid, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]);
                PutPlayerInVehicle(playerid, vehicleid, 0);
                player_in_business[playerid] = -1;             
            }
        }
    }
	#if	defined	biz__OnPlayerKeyStateChange
		return biz__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange biz__OnPlayerKeyStateChange
#if	defined	biz__OnPlayerKeyStateChange
	forward biz__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_ENTER_BIZ:
        {
            if(!response) DeletePVar(playerid, "biz_id_enter");
            else
            {
                new i = GetPVarInt(playerid, "biz_id_enter");

                if(PlayerInfo[playerid][pCash] < BusinessInfo[i][bEnterPrice]) return SCM(playerid, red, "У вас нет столько денег!");

                GiveMoney(playerid, -BusinessInfo[i][bEnterPrice], "Вход в бизнесс");
                GiveBusinessMoney(i, BusinessInfo[i][bEnterPrice], playerid);
                FreezePlayer(playerid, 2000);
                SetPlayerPos(playerid, business_params[ BusinessInfo[i][bType] ][exit_x], business_params[ BusinessInfo[i][bType] ][exit_y], business_params[ BusinessInfo[i][bType] ][exit_z]);
                SetPlayerFacingAngle(playerid, business_params[ BusinessInfo[i][bType] ][exit_angle]);
                SetPlayerVirtualWorld(playerid, BusinessInfo[i][bID]);
                if(BusinessInfo[i][bType] == b_type_EAT) SetPlayerInterior(playerid, 17);
                player_in_business[playerid] = i;
                DeletePVar(playerid, "biz_id_enter");
            }
        }
        case D_BUY_BIZ:
        {
            if(!response) DeletePVar(playerid, "cmd_buy_biz");
            else
            {
                new i = GetPVarInt(playerid, "cmd_buy_biz");
                if(BusinessInfo[i][bOwned] != 0) return SCM(playerid, red, "Данный бизнессом уже кто-то владеет.");
                BusinessInfo[i][bOwned] = 1;
                BusinessInfo[i][bOwner] = EOS;
                strcat(BusinessInfo[i][bOwner], PlayerInfo[playerid][pName]);
                PlayerInfo[playerid][pBizID] = BusinessInfo[i][bID];
                GiveMoney(playerid, -BusinessInfo[i][bPrice], "Покупка бизнесса!");

                new string[144];
                format(string, sizeof(string), "Вы успешно приобрели бизнесс %s", business_params[ BusinessInfo[i][bType] ][bname]);
                SCM(playerid, green, string);
                SCM(playerid, green, "Управление бизнесом: /business");

                UpdateBusiness(i);
                SaveAccounts(playerid);
                DeletePVar(playerid, "cmd_buy_biz");
            }
        }
        case D_CMD_BUSINESS:
        {
            if(!response) DeletePVar(playerid, "my_biz_id");
            else
            {
                ShowDialogBizParams(playerid);
            }
        }
        case D_SELL_BIZ:
        {
            if(!response) DeletePVar(playerid, "my_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "my_biz_id");

                BusinessInfo[b][bOwned] = 0;
                BusinessInfo[b][bOwner] = EOS;
                strcat(BusinessInfo[b][bOwner], "None");
                PlayerInfo[playerid][pBizID] = -1;
                new price = (BusinessInfo[b][bPrice]/10)*8;
                BusinessInfo[b][bEnterPrice] = 0;
                GiveMoney(playerid, price, "Продажа бизнеса"); 
                UpdateBusiness(b);
                SaveAccounts(playerid);

            }
        }
        case D_BIZ_PARAMS:
        {
            if(!response) 
            {
                cmd::business(playerid); 
                DeletePVar(playerid, "my_biz_id");
            }
            else
            {
                new b = GetPVarInt(playerid, "my_biz_id");
                switch(listitem)
                {
                    case 0:
                    {
                        if(BusinessInfo[b][bType] == b_type_FILL || BusinessInfo[b][bType] == b_type_REPAIR) return SCM(playerid, red, "Вам недоступна данная функция!"); DeletePVar(playerid, "my_biz_id");
                        SetBizEnterPrice(playerid);
                    }
                    case 1: 
                    {
                        cmd::sellbusiness(playerid); 
                        DeletePVar(playerid, "my_biz_id");
                    }
                    case 2:
                    {
                        new query[256];
                        format(query, sizeof(query), "SELECT * FROM `business_profit` WHERE `bid` = '%d' ORDER BY date DESC LIMIT 30", BusinessInfo[b][bID]);
						mysql_tquery(connects, query, "ShowBusinessProfit", "i", playerid);
                    }
                    case 3:
                    {
                        if(BusinessInfo[b][bType] == b_type_REPAIR)
                        {
                            ShowSetBizRepairPrice(playerid);
                        }
                        else if(BusinessInfo[b][bType] == b_type_FILL)
                        {
                            ShowSetBizFillPrice(playerid);
                        }
                    }
                }
            }
        }
        case D_BIZ_ENTER_PRICE:
        {
            if(!response)
            {
                ShowDialogBizParams(playerid);
                DeletePVar(playerid, "my_biz_id");
            }
            else
            {
                new b = GetPVarInt(playerid, "my_biz_id");
                if(!strlen(inputtext) || !IsNumeric(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 5000) SetBizEnterPrice(playerid);

                new string[144];
                format(string, sizeof(string), "Вы сменили стоимость входа в бизнес на %d рублей.", strval(inputtext));
                SCM(playerid, green, string);

                BusinessInfo[b][bEnterPrice] = strval(inputtext);
                UpdateBusiness(b);
            }
        }
        case D_MENU_BIZ_24_7:
        {
            if(!response) return 1;
            else
            {
                new b = player_in_business[playerid];
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][pBeer] >= 5) return SCM(playerid, red, "Вы не можете унести с собой столько пива!");
                        if(PlayerInfo[playerid][pCash] < 50) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pBeer]++;
                        GiveMoney(playerid, -50, "Покупка пива");
                        GiveBusinessMoney(b, 50, playerid);
                        SCM(playerid, green, "Вы купили банку пива! Используйте: /drink");
                        SaveAccounts(playerid);
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][pSmoke] >= 5) return SCM(playerid, red, "Вы не можете унести с собой столько пачек сигарет!");
                        if(PlayerInfo[playerid][pCash] < 30) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pSmoke]++;
                        GiveMoney(playerid, -30, "Покупка сигарет");
                        GiveBusinessMoney(b, 30, playerid);
                        SCM(playerid, green, "Вы купили пачку сигарет!");
                        SaveAccounts(playerid);
                    }

                    case 2:
                    {
                        if(PlayerInfo[playerid][pChips] >= 5) return SCM(playerid, red, "Вы не можете унести с собой столько пачек чипсов!");
                        if(PlayerInfo[playerid][pCash] < 40) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pChips]++;
                        GiveMoney(playerid, -40, "Покупка чипс");
                        GiveBusinessMoney(b, 40, playerid);
                        SCM(playerid, green, "Вы купили чипсы! Используйте: /eat");
                        SaveAccounts(playerid);
                    }
                    case 3:
                    {
                        if(PlayerInfo[playerid][pLighter] >= 5) return SCM(playerid, red, "Вы не можете унести с собой столько зажигалок!");
                        if(PlayerInfo[playerid][pCash] < 10) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pLighter]++;
                        GiveMoney(playerid, -10, "Покупка зажигалки");
                        GiveBusinessMoney(b, 10, playerid);
                        SCM(playerid, green, "Вы купили зажигалку!");
                        SaveAccounts(playerid);
                    }
                    case 4:
                    {
                        if(PlayerInfo[playerid][pCash] < 500) return SCM(playerid, red, "У вас нет столько денег!");

                        GiveMoney(playerid, -500, "Покупка дров");
                        GiveBusinessMoney(b, 500, playerid);
                        SCM(playerid, green, "Вы купили дрова!");
                        SaveAccounts(playerid);
                    }
                    case 5:
                    {
                        if(PlayerInfo[playerid][pPhone] >= 1) return SCM(playerid, red, "У вас уже есть телефон!"); 
                        if(PlayerInfo[playerid][pCash] < 2000) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pPhone] = 1;
                        GiveMoney(playerid, -2000, "Покупка телефона");
                        GiveBusinessMoney(b, 2000, playerid);
                        SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Покупка телефона", "{FFFFFF}Вы купили себе телефон\nТеперь вам необходимо купить сим-карту", "Закрыть", "");
                        SaveAccounts(playerid);
                    }
                    case 6:
                    {
                        if(PlayerInfo[playerid][pPhone] == 0) return SCM(playerid, red, "У вас нет телефона!"); 
                        if(PlayerInfo[playerid][pCash] < 100) return SCM(playerid, red, "У вас нет столько денег!");

						SPD
						(
							playerid, D_BUY_SIM, DIALOG_STYLE_INPUT,
							"{"cblue"}Изменение номера",
							"{FFFFFF}Введите новый номер в поле ниже\n\n\
							{FF6600}Примечания:\n\
							{FFCC00}- Номер должен быть шестизначным,\n\
							например: 123456\n\
						    - Номер не должен начинаться с 0",
							"Далее", "Отмена"
						);
                    }
                    case 7:
                    {
                        if(PlayerInfo[playerid][pBackPack] >= 1) return SCM(playerid, red, "У вас уже есть рюкзак!"); 
                        if(PlayerInfo[playerid][pCash] < 2000) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pBackPack] = 1;
                        GiveMoney(playerid, -2000, "Покупка рюкзака");
                        GiveBusinessMoney(b, 2000, playerid);
                        SCM(playerid, green, "Вы купили рюкзак!");
                        SaveAccounts(playerid);
                        SetPlayerAttachedObject(playerid, 1, 3026, 1, -0.176000, -0.066000, 0.0000,0.0000, 0.0000, 0.0000, 1.07600, 1.079999, 1.029000);
                    }
                    case 8:
                    {
                        if(PlayerInfo[playerid][pPepsi] >= 5) return SCM(playerid, red, "Вы не можете унести столько пепси!"); 
                        if(PlayerInfo[playerid][pCash] < 50) return SCM(playerid, red, "У вас нет столько денег!");

                        PlayerInfo[playerid][pPepsi]++;
                        GiveMoney(playerid, -50, "Покупка пепси");
                        GiveBusinessMoney(b, 50, playerid);
                        SCM(playerid, green, "Вы купили пепси! Используйте: /pepsi");
                        SaveAccounts(playerid);
                    }
                    case 9:
                    {
                        if(PlayerInfo[playerid][pCash] < 500) return SCM(playerid, red, "У вас нет столько денег!");

                        GiveMoney(playerid, -500, "Покупка фотоапарата");
                        GiveBusinessMoney(b, 500, playerid);
                        SCM(playerid, green, "Вы купили фотоаппарат!");
                        GivePlayerWeaponAC(playerid, 43, 20);
                        SaveAccounts(playerid);
                    }
                }
            }
        }
        case D_BUY_SIM:
        {
            if(!response) return 1;
            else
            {
                if(!strlen(inputtext) || !IsNumeric(inputtext) || strlen(inputtext) != 6 || inputtext[0] == 0)
                {
                    SPD
                    (
                        playerid, D_BUY_SIM, DIALOG_STYLE_INPUT,
                        "{"cblue"}Изменение номера",
                        "{FFFFFF}Введите новый номер в поле ниже\n\n\
                        {FF6600}Примечания:\n\
                        {FFCC00}- Номер должен быть шестизначным,\n\
                        например: 123456\n\
                        - Номер не должен начинаться с 0",
                        "Далее", "Отмена"
                    );
                    return 1;
                }

                new sql[144];
                format(sql, sizeof(sql), "SELECT * FROM `accounts` WHERE `pPhoneNumber` = '%d'", strval(inputtext));
                mysql_tquery(connects, sql, "buy_sim_card", "id", playerid, strval(inputtext));
            }
        }
        case D_MENU_BIZ_APTEKA:
        {
            if(!response) return 1;
            else
            {
                new b = player_in_business[playerid];
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][pHeal] >= 2) return SCM(playerid, red, "Вы не можете унести столько аптечек");
                        if(PlayerInfo[playerid][pCash] < 1000) return SCM(playerid, red, "У вас не достаточно дене!");

                        PlayerInfo[playerid][pHeal]++;
                        GiveMoney(playerid, -1000, "Покупка аптечки в аптеке");
                        GiveBusinessMoney(b, 1000, playerid);
                        SaveAccounts(playerid);
                        SCM(playerid, green, "Вы купили аптечку. Используйте: /healme");
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][pMask] >= 1) return SCM(playerid, red, "Вы не можете унести столько масок");
                        if(PlayerInfo[playerid][pCash] < 500) return SCM(playerid, red, "У вас не достаточно дене!");

                        PlayerInfo[playerid][pMask]++;
                        GiveMoney(playerid, -500, "Покупка маски в аптеке");
                        GiveBusinessMoney(b, 500, playerid);
                        SaveAccounts(playerid);
                        SCM(playerid, green, "Вы купили маску. Используйте: /mask");
                    }
                }
            }
        }
        case D_MENU_BIZ_EAT:
        {
            if(!response) return 1;
            else
            {
                new b = player_in_business[playerid];
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][pNeedEat] + 20 > 100) return SCM(playerid, red, "Вы сыты!");
                        if(PlayerInfo[playerid][pCash] < 200) return SCM(playerid, red, "У вас не достаточно денег!");

                        PlayerInfo[playerid][pNeedEat] += 20;
                        PlayerInfo[playerid][pNeedDrink] -= 2;
                        GiveMoney(playerid, -200, "Покупка куриного супа в столовой");
                        GiveBusinessMoney(b, 200, playerid);
                        SCM(playerid, green, "Вы съели куриный суп, тем самым уталили голод.");
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, false, 0, 0, 0, 0);
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][pNeedEat] + 10 > 100) return SCM(playerid, red, "Вы сыты!");
                        if(PlayerInfo[playerid][pCash] < 100) return SCM(playerid, red, "У вас не достаточно денег!");

                        PlayerInfo[playerid][pNeedEat] += 10;
                        PlayerInfo[playerid][pNeedDrink] -= 2;
                        GiveMoney(playerid, -100, "Покупка макарон с катлетами в столовой");
                        GiveBusinessMoney(b, 100, playerid);
                        SCM(playerid, green, "Вы съели макароны с катлетой, тем самым уталили голод.");
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, false, 0, 0, 0, 0);
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][pNeedDrink] + 15 > 100) return SCM(playerid, red, "Вы не хотите пить!");
                        if(PlayerInfo[playerid][pCash] < 50) return SCM(playerid, red, "У вас не достаточно денег!");

                        PlayerInfo[playerid][pNeedDrink] += 15;
                        PlayerInfo[playerid][pNeedToilet] -= 5;
                        GiveMoney(playerid, -50, "Покупка стакана компота в столовой");
                        GiveBusinessMoney(b, 50, playerid);
                        SCM(playerid, green, "Вы выпили стакан компота, тем самым уталили жажду.");
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, false, 0, 0, 0, 0);
                    }
                }
            }
        }
        case D_BIZ_SET_REPAIR_PRICE:
        {
            if(!response) return DeletePVar(playerid, "my_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "my_biz_id");
                if(!strlen(inputtext) || !IsNumeric(inputtext) || strval(inputtext) > 5000 || strval(inputtext) < 1000) return ShowSetBizRepairPrice(playerid);

                BusinessInfo[b][bRepairPrice] = strval(inputtext);
                new string[144];
                format(string, sizeof(string), "Вы установили цену за ремонт автомобиля: {"cyellow"}%d рублей{"cblue"}.", strval(inputtext));
                SCM(playerid, blue, string);
                return UpdateBusiness(b);
            }
        }
        case D_BIZ_SET_FILL_PRICE:
        {
            if(!response) return DeletePVar(playerid, "my_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "my_biz_id");
                if(!strlen(inputtext) || !IsNumeric(inputtext) || strval(inputtext) > 110 || strval(inputtext) < 10) return ShowSetBizFillPrice(playerid);

                BusinessInfo[b][bFillPrice] = strval(inputtext);
                new string[144];
                format(string, sizeof(string), "Вы установили цену за 1 литр бензина: {"cyellow"}%d рублей{"cblue"}.", strval(inputtext));
                SCM(playerid, blue, string);
                return UpdateBusiness(b);
            }
        }
    }
	#if	defined	biz__OnDialogResponse
		return biz__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse biz__OnDialogResponse
#if	defined	biz__OnDialogResponse
	forward biz__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics minuteupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);
    if(hour == 23 && minute == 58)
    {
        foreach(new b : Allbusiness)
        {
            new year, month, day, sql[256], _date[100];
            getdate(year, month, day);

            format(_date, sizeof(_date), "%d.%d.%d", day, month, year);

            format(sql, sizeof(sql), "INSERT INTO `business_profit` (`bid`, `date`, `money`) VALUES ('%d', '%s', '%d')", BusinessInfo[b][bID], _date, BusinessInfo[b][bProfit]);
            mysql_tquery(connects, sql, "", "");

            BusinessInfo[b][bProfit] = 0;
            UpdateBusiness(b);
        }
    }
    if(hour == 00 && minute == 20)
    {
        foreach(new i : Allbusiness) if(BusinessInfo[i][bOwned] == 1)
        {
            BusinessInfo[i][bDays]--;
            UpdateBusiness(i);
            if(BusinessInfo[i][bDays] <= 0)
            {
                foreach(new j : Player)
                {
                    if(PlayerInfo[j][pBizID] == BusinessInfo[i][bID])
                    {
                        SCM(j, green, "Ваш дом был продан государству за неуплату. Вы получили 80 процентов от гос. стоимости.");

                        GiveBankMoney(j, (BusinessInfo[i][bPrice] / 10) * 8, "Неуплата бизнеса и в госс.");
                        PlayerInfo[j][pBizID] = -1;

                        BusinessInfo[i][bOwned] = 0;
                        BusinessInfo[i][bDays] = 3;
                        BusinessInfo[i][bOwner] = EOS;
                        format(BusinessInfo[i][bOwner], MAX_PLAYER_NAME, "None");
                        SaveAccounts(j);
                        UpdateBusiness(i);
                        return 1;
                    }
                }
                BusinessInfo[i][bDays] = 3;
                BusinessInfo[i][bOwned] = 0;
                BusinessInfo[i][bOwner] = EOS;
                format(BusinessInfo[i][bOwner], MAX_PLAYER_NAME, "None");
                UpdateBusiness(i);

                new sql[144];
                format(sql, sizeof(sql), "SELECT * FROM `accounts` WHERE `pBizID` = '%d'", BusinessInfo[i][bID]);
                return mysql_tquery(connects, sql, "SletBiz", "i", i);
            }
        }
    }
	#if	defined	biz__minuteupdate
		return biz__minuteupdate();
	#else
		return 1;
	#endif
}
#if	defined	_ALS_minuteupdate
	#undef	minuteupdate
#else
	#define	_ALS_minuteupdate
#endif

#define	minuteupdate biz__minuteupdate
#if	defined	biz__minuteupdate
	forward biz__minuteupdate();
#endif

publics SletBiz(i)
{
    static rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new bmoney, player_id;
        player_id = cache_get_field_content_int(0, "pID");
        bmoney = cache_get_field_content_int(0, "pBCash");
        bmoney += (BusinessInfo[i][bPrice]/10) * 8;

        new bizoffmess[144] = "Ваш бизнес был продан государству, за неуплату. Вы получили 80 процентов от госс. стоимости дома.";

        new sql[144];
        format(sql, sizeof(sql), "UPDATE `accounts` SET `pBizID` = '-1', `pBizOffMess` = '%s', `pBCash` = '%d' WHERE `pID` = '%d'", bizoffmess, bmoney, player_id);
    }
    else
    {
        printf("Залупа (дома)");
    }
    return 1;
}

stock GiveBusinessMoney(id, money, playerid = -1)
{
    new m = (money / 10) * 3;
    if(BusinessInfo[id][bControl] == TEAM_OREX) OPG_O_MONEY += m;
    else if(BusinessInfo[id][bControl] == TEAM_SUN) OPG_S_MONEY += m;

    BusinessInfo[id][bCash] += money - m;
    BusinessInfo[id][bProfit] += money - m;
    UpdateBusiness(id);
    SetPVarInt(playerid, "playerid", playerid);
    return 1;
}
ALTX:buybusiness("/buybiz");
CMD:buybusiness(playerid)
{
    foreach(new i : Allbusiness)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ]))
        {
            if(BusinessInfo[i][bOwned] != 0) return SCM(playerid, red, "Данным бизнесом уже кто-то владеет!");
            if(PlayerInfo[playerid][pCash] < BusinessInfo[i][bPrice]) return SCM(playerid, red, "У вас не достаточно денег!");
            if(PlayerInfo[playerid][pBizID] != -1) return SCM(playerid, red, "У вас уже есть бизнесс!");

            new string[286];
            format(string, sizeof(string), "\
                {FFFFFF}Название:\t\t\t{0099FF}%s\n\
                {FFFFFF}Стоимость:\t\t\t{0099FF}%d руб\n\
                {FFFFFF}Плата за аренду:\t\t{0099FF}%d руб в день\n\n\
                {0099FF}Вы уверены что хотите купить этот бизнес?",
                business_params[ BusinessInfo[i][bType] ][bname],
                BusinessInfo[i][bPrice],
                business_params[BusinessInfo[i][bType]][b_rent_price]
            );
            SPD(playerid, D_BUY_BIZ, DIALOG_STYLE_MSGBOX, "{"cblue"}Покупка нового бизнесса", string, "Да", "Нет");
            SetPVarInt(playerid, "cmd_buy_biz", i);
        }
    }
    return 1;
}
ALTX:business("/biz");
CMD:business(playerid)
{
    if(PlayerInfo[playerid][pBizID] == -1) return SCM(playerid, red, "У вас нет бизнеса!");
    new b;
    foreach(new i : Allbusiness) 
    {
        if(BusinessInfo[i][bID] == PlayerInfo[playerid][pBizID])
        {
            b = i; 
            break;
        }
    }
	new fmt_dialog[1024], text[128];
	
	format
	(
		fmt_dialog, sizeof fmt_dialog,
		"{ffffff}Название:\t\t\t{0099FF}%s(%d)\n\
		{ffffff}Владелец:\t\t\t{0099FF}%s\n\
		{ffffff}Стоимость:\t\t\t{0099FF}%d рублей\n\
		{ffffff}Баланс:\t\t\t{0099FF}%d рублей\n\
        {ffffff}Прибыль:\t\t\t{0099FF}%d рублей\n\
		{ffffff}Оплачен на:\t\t\t{0099FF}%d из 30 дней\n\
		{ffffff}Цена за вход:\t\t\t{0099FF}%d рублей",
		business_params[BusinessInfo[b][bType]][bname], BusinessInfo[b][bID],
		BusinessInfo[b][bOwner],
		BusinessInfo[b][bPrice],
		BusinessInfo[b][bCash],
		BusinessInfo[b][bProfit],
		BusinessInfo[b][bDays],
		BusinessInfo[b][bEnterPrice]
	);
	
	if(BusinessInfo[b][bType] == b_type_REPAIR)
	{
		format(text, sizeof text, "\n{ffffff}Стоимость починки:\t\t%d рублей", BusinessInfo[b][bRepairPrice]);
		strcat(fmt_dialog, text);
	}
	if(BusinessInfo[b][bType] == b_type_FILL)
	{
		format(text, sizeof text, "\n{ffffff}Стоимость бензина за 1 литр:\t\t%d рублей", BusinessInfo[b][bFillPrice]);
		strcat(fmt_dialog, text);
	}
	
    SetPVarInt(playerid, "my_biz_id", b);

	SPD
	(
		playerid, D_CMD_BUSINESS, DIALOG_STYLE_MSGBOX,
		"{"cblue"}Информация о бизнесе",
		fmt_dialog,
		"Изменить", "Отмена"
	);

    return 1;
}
ALTX:sellbusiness("/sellbiz");
CMD:sellbusiness(playerid)
{
    if(PlayerInfo[playerid][pBizID] == -1) return SCM(playerid, red, "У вас нет бизнеса!");
    new b;
    foreach(new i : Allbusiness) if(BusinessInfo[i][bID] == PlayerInfo[playerid][pBizID]) b = i;
    new fmt_dialog[256];
    format
    (
        fmt_dialog, sizeof(fmt_dialog),
        "{FFFFFF}Вы уверенны, что хотите продать свой бизнес {"cblue"}%s{FFFFFF}? Вы получите 80 процентов {FFFFFF}от гос. стоимости бизнеса.", business_params[ BusinessInfo[b][bType] ][bname]
    );

    SPD
    (
        playerid, D_SELL_BIZ, DIALOG_STYLE_MSGBOX, "{"cblue"}Продажа бизнеса", fmt_dialog, "Да", "Нет"
    );
    SetPVarInt(playerid, "my_biz_id", b);
    return 1;
}

stock SetBizEnterPrice(playerid)
{
    return SPD(playerid, D_BIZ_ENTER_PRICE, DIALOG_STYLE_INPUT, "{"cblue"}Бизнес | Установить цену за вход", "{FFFFFF}Введите цену, какую хотите установить за вход. Минимальная цена {"cblue"}0 рублей{FFFFFF}, максимальная цена {"cblue"}5000 рублей{FFFFFF}.", "Далее", "Закрыть");
}

stock ShowDialogBizParams(playerid)
{
    new b = GetPVarInt(playerid, "my_biz_id");
    new fmt_dialog[286];
    format
    (
        fmt_dialog, sizeof(fmt_dialog),
        "{"cblue"}1. {FFFFFF}Изменить цену за вход\n\
        {"cblue"}2. {FFFFFF}Продать государству\n\
        {"cblue"}3. {FFFFFF}Финансовая статистика"
    );

    if(BusinessInfo[b][bType] == b_type_REPAIR)
    {
        new text[96] = "\n{"cblue"}4. {FFFFFF}Изменить стоимость починки";

        strcat(fmt_dialog, text);
    }
    if(BusinessInfo[b][bType] == b_type_FILL)
    {
        new text[96] = "\n{"cblue"}4. {FFFFFF}Изменить цену за 1 литр";

        strcat(fmt_dialog, text);
    }

    SPD(playerid, D_BIZ_PARAMS, DIALOG_STYLE_LIST, "{"cblue"}Управление бизнесом", fmt_dialog, "Далее", "Отмена");
    return 1;
}

stock ShowPlayerBusinessMenu(playerid, i)
{
    switch(BusinessInfo[i][bType])
    {
        case b_type_24_7:
        {
			ShowPlayerDialog
			(
				playerid, D_MENU_BIZ_24_7, DIALOG_STYLE_LIST,
				"{"cblue"}Магазин 24/7",
				"{"cblue"}1. {ffffff}Бутылка пива\t{"cblue"}50 рублей\n\
				{"cblue"}2. {ffffff}Пачка сигарет\t{"cblue"}30 рублей\n\
				{"cblue"}3. {ffffff}Чипсы\t\t{"cblue"}40 рублей\n\
				{"cblue"}4. {ffffff}Зажигалка\t\t{"cblue"}10 рублей\n\
				{"cblue"}5. {ffffff}Дрова\t\t{"cblue"}500 рублей\n\
				{"cblue"}6. {ffffff}Телефон\t\t{"cblue"}2000 рублей\n\
				{"cblue"}7. {ffffff}Сим-карта\t\t{"cblue"}100 рублей\n\
				{"cblue"}8. {FFFFFF}Рюкзак\t\t{"cblue"}2000 рублей \n\
				{"cblue"}9. {ffffff}Пепси\t\t{"cblue"}50 рублей\n\
				{"cblue"}10. {ffffff}Фотоаппарат\t{"cblue"}500 рублей",
				"Купить", "Отмена"
			);
        }
        case b_type_APTEKA:
        {
			ShowPlayerDialog
			(
				playerid, D_MENU_BIZ_APTEKA, DIALOG_STYLE_LIST,
				"{"cblue"}Аптека",
				"{"cblue"}1. {ffffff}Аптечка\t{"cblue"}1000 рублей\n\
				{"cblue"}2. {ffffff}Маска\t{"cblue"}500 рублей",
				"Купить", "Отмена"
			);
        }
        case b_type_EAT:
        {
			ShowPlayerDialog
			(
				playerid, D_MENU_BIZ_EAT, DIALOG_STYLE_LIST,
				"{"cblue"}Столовая",
				"\
                {"cblue"}1. {ffffff}Куриный суп\t\t\t{"cblue"}200 рублей\n\
				{"cblue"}2. {ffffff}Макароны с катлетами\t{"cblue"}100 рублей\n\
				{"cblue"}3. {ffffff}Стакан компота\t\t{"cblue"}50 рублей",
				"Выбрать", "Отмена"
			);
        }
    }
    return 1;
}

publics ShowBusinessProfit(playerid)
{
    static rows, fields;
    cache_get_data(rows, fields);
    
    new string[600];
    
    if(rows)
    {
        new fmt_str[144];
        new money, _date[64];
        
        string = "{FFFFFF}Дата\t\t\tПрибыль\n\n{FFFFFF}";
        
        for(new idx; idx < rows; idx++)
        {
            cache_get_field_content(idx, "date", _date, connects, 64);
            money = cache_get_field_content_int(idx, "money");
            
            format(fmt_str, sizeof fmt_str, "{"cblue"}%d. {FFFFFF}%s\t\t%d рублей\n", idx+1, _date, money);
            strcat(string, fmt_str);
        }
    }
    else string = "{FFFFFF}Финансовая статистика Вашего бизнеса еще не сформирована";
    
    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{"cblue"}Доход бизнеса за 30 дней", string, "Закрыть", "");
}

stock ShowSetBizRepairPrice(playerid)
{
    ShowPlayerDialog
    (
        playerid, D_BIZ_SET_REPAIR_PRICE, DIALOG_STYLE_INPUT,
        "{"cblue"}Бизнесс | Установить цену за ремонт",
        "{FFFFFF}Введите цену, которую будут платить клиенты за ремонт т/с.\n\n\
        \t{"cblue"}Примечания:\n\
        {FFFFFF}Цена должна быть минимум {"cblue"}1000 рублей {FFFFFF}и максимум {"cblue"}5000 рублей{FFFFFF}.",
        "Далее", "Отмена"
    );
    return 1;
}

stock ShowSetBizFillPrice(playerid)
{
    ShowPlayerDialog
    (
        playerid, D_BIZ_SET_FILL_PRICE, DIALOG_STYLE_INPUT,
        "{"cblue"}Бизнесс | Установить цену за  бензин",
        "{FFFFFF}Введите цену, которую будут платить клиенты за 1 литр бензина.\n\n\
        \t{"cblue"}Примечания:\n\
        {FFFFFF}Цена должна быть минимум {"cblue"}10 рублей {FFFFFF}и максимум {"cblue"}110 рублей{FFFFFF}.",
        "Далее", "Отмена"
    );
    return 1;
}

publics buy_sim_card(playerid, number)
{
    new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    {
        SPD
        (
            playerid, D_BUY_SIM, DIALOG_STYLE_INPUT,
            "{"cblue"}Изменение номера",
            "{FFFFFF}Введите новый номер в поле ниже\n\n\
            {FF6600}Примечания:\n\
            {FFCC00}- Номер должен быть шестизначным,\n\
            например: 123456\n\
            - Номер не должен начинаться с 0",
            "Далее", "Отмена"
        );
        return SCM(playerid, red, "Введёный Вами номер уже занят.");
    }
    else
    {
        new b = player_in_business[playerid];
        PlayerInfo[playerid][pPhoneNumber] = number;
        GiveMoney(playerid, -200, "Покупка сим-карты");
        GiveBusinessMoney(b, 200, playerid);
        SaveAccounts(playerid);

 		new fmt_msg[180];

		format
		(
			fmt_msg, sizeof fmt_msg,
			"{ffffff}Вы изменили номер телефона\n\
			Теперь с Вами можно связаться по номеру {"cblue"}%d",
			PlayerInfo[playerid][pPhoneNumber]
		);

		ShowPlayerDialog
		(
			playerid, 0, DIALOG_STYLE_MSGBOX,
			"{"cblue"}Изменение номера",
			fmt_msg,
			"Закрыть", ""
		);       
    }
    return 1;
}

CMD:sellmybusiness(playerid, params[])
{
    if(PlayerInfo[playerid][pBizID] == -1) return SCM(playerid, red, "У вас нет бизнеса!");
    extract params -> new to_player, price; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /sellmybusiness [ID игрока] [цена]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pBizID] != -1) return SCM(playerid, red, "У игрока уже имеется бизнесс.");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока нет столько денег.");
    if(price < 0) return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /sellmybusiness [ID игрока] [цена]");
    foreach(new i : Allbusiness) if(BusinessInfo[i][bID] == PlayerInfo[playerid][pBizID]) SetPVarInt(playerid, "my_biz_id", i);
    new i = GetPVarInt(playerid, "my_biz_id");
    if(!IsPlayerInRangeOfPoint(playerid, 10.0, BusinessInfo[i][bExitX], BusinessInfo[i][bExitY], BusinessInfo[i][bExitZ])) return SCM(playerid, red, "Вы должны находится возле своего бизнеса!");
    return SendProposition(playerid, to_player, PROPOSITION_TYPE_SELLBIZ, price);
}