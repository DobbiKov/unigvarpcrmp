#define MAX_PODEZDS 100

new player_in_podezd[MAX_PLAYERS] = -1;

enum podezd_params_info
{
	pint,
	Float:exit_x,
	Float:exit_y,
	Float:exit_z,
	Float:exit_angle,
    Float:pod_menu_x,
    Float:pod_menu_y,
    Float:pod_menu_z,
}
new podezd_params[1][podezd_params_info] =
{
	{0, 2452.1016,-2086.6279,-4.6100,182.4024, 2449.6877,-2086.0449,-4.6100}
};

enum E_PODEZD_DATA
{
    pod_id,
	Float: pod_x,
	Float: pod_y,
	Float: pod_z,

	Float: a_car_pos_x,
	Float: a_car_pos_y,
	Float: a_car_pos_z,
	Float: a_car_pos_a,
    pod_pickup,
    pod_icon,
    pod_exit_pickup,
    pod_menu_pickup,
    Text3D: pod_text,
}
new PodezdInfo[MAX_HOUSES][E_PODEZD_DATA];






new Iterator: Allpodezd<MAX_PODEZDS>;
new Iterator: Allkvart<MAX_KVARTS>;

new 
    totalpodezd, last_pod_id; 


publics LoadPodezd()
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            PodezdInfo[i][pod_id] = cache_get_field_content_int(i, "pod_id");

            PodezdInfo[i][pod_x] = cache_get_field_content_float(i, "pod_x");
            PodezdInfo[i][pod_y] = cache_get_field_content_float(i, "pod_y");
            PodezdInfo[i][pod_z] = cache_get_field_content_float(i, "pod_z");

            PodezdInfo[i][a_car_pos_x] = cache_get_field_content_float(i, "a_car_pos_x");
            PodezdInfo[i][a_car_pos_y] = cache_get_field_content_float(i, "a_car_pos_y");
            PodezdInfo[i][a_car_pos_z] = cache_get_field_content_float(i, "a_car_pos_z");
            PodezdInfo[i][a_car_pos_a] = cache_get_field_content_float(i, "a_car_pos_a");

            new string[144];
            format(string, sizeof(string), "Подъезд: №%d", PodezdInfo[i][pod_id]);
            PodezdInfo[i][pod_text] = CreateDynamic3DTextLabel(string, 0xFFFFFFFF, PodezdInfo[i][pod_x], PodezdInfo[i][pod_y], PodezdInfo[i][pod_z]+1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);

            PodezdInfo[i][pod_icon] = CreateDynamicMapIcon(PodezdInfo[i][pod_x], PodezdInfo[i][pod_y], PodezdInfo[i][pod_z], 31, 0, -1, -1, -1, 180);
            PodezdInfo[i][pod_pickup] = CreateDynamicPickup(1318, 23, PodezdInfo[i][pod_x], PodezdInfo[i][pod_y], PodezdInfo[i][pod_z], -1);
            PodezdInfo[i][pod_exit_pickup] = CreateDynamicPickup(1318, 23, podezd_params[0][exit_x], podezd_params[0][exit_y], podezd_params[0][exit_z], PodezdInfo[i][pod_id]);
            PodezdInfo[i][pod_menu_pickup] = CreateDynamicPickup(1314, 23, podezd_params[0][pod_menu_x], podezd_params[0][pod_menu_y], podezd_params[0][pod_menu_z], PodezdInfo[i][pod_id]);
            
            totalpodezd++;
            last_pod_id = PodezdInfo[i][pod_id];

            Iter_Add(Allpodezd, i);

        }
    }
    printf("[UNIGVA]: Всего загружено подъездов: %d", totalpodezd);
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(player_in_podezd[playerid] != -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, podezd_params[0][exit_x], podezd_params[0][exit_y], podezd_params[0][exit_z]))
            {
                foreach(new i : Allpodezd) if(player_in_podezd[playerid] == PodezdInfo[i][pod_id])
                {
                    SetPlayerPos(playerid, PodezdInfo[i][pod_x], PodezdInfo[i][pod_y], PodezdInfo[i][pod_z]);
                    SetPlayerVirtualWorld(playerid, 0);
                    FreezePlayer(playerid, 2000);
                    return player_in_podezd[playerid] = -1;
                }
            }
            else if(IsPlayerInRangeOfPoint(playerid, 1.0, podezd_params[0][pod_menu_x], podezd_params[0][pod_menu_y], podezd_params[0][pod_menu_z]))
            {
                SPD
                (
                    playerid, D_MENU_POD, DIALOG_STYLE_LIST,
                    "{"cblue"}Меню подъезда",
                    "{"cblue"}1. {FFFFFF}Список квартир\n\
                    {"cblue"}2. {FFFFFF}Регистрация\n\
                    {"cblue"}3. {FFFFFF}Меню жильца",
                    "Далее", "Отмена"
                );
            }
        }
        else
        {
            foreach(new i : Allpodezd)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, PodezdInfo[i][pod_x], PodezdInfo[i][pod_y], PodezdInfo[i][pod_z]))
                {
                    SetPlayerPos(playerid, podezd_params[0][exit_x], podezd_params[0][exit_y], podezd_params[0][exit_z]);
                    SetPlayerVirtualWorld(playerid, PodezdInfo[i][pod_id]);
                    FreezePlayer(playerid, 2000);
                    return player_in_podezd[playerid] = PodezdInfo[i][pod_id];
                }
            }
        }
    }
	#if	defined	podezd__OnPlayerKeyStateChange
		return podezd__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange podezd__OnPlayerKeyStateChange
#if	defined	podezd__OnPlayerKeyStateChange
	forward podezd__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_MENU_POD:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        new fmt_str[128];
                        new text[sizeof(fmt_str)*14+53] = "Квартира\t\tСтоимость\tОплачено\tВладелец\n\n{FFFFFF}";
                        new owner[MAX_PLAYER_NAME];
                        foreach(new i : Allkvart)
                        {
                            if(KvartInfo[i][kvart_pod_id] == player_in_podezd[playerid])
                            {
                                format(owner, sizeof(owner), "{"cgreen"}Государство");
                                if(KvartInfo[i][kvart_Owned] == 1) format(owner, sizeof(owner), "{FFFFFF}%s", KvartInfo[i][kvart_Owner]);

                                format(fmt_str, sizeof(fmt_str), "{FFFFFF}№%d\t\t\t2000 рублей\t%d дн.\t\t%s\n",  KvartInfo[i][kvart_type]+1, KvartInfo[i][kvart_days], owner);
                                strcat(text, fmt_str);
                            }
                        }
                        SPD
                        (
                            playerid, D_NULL, DIALOG_STYLE_MSGBOX,
                            "{"cblue"}Список квартир",
                            text,
                            "Закрыть", ""
                        );
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][pHomeID] != -1 || PlayerInfo[playerid][pKvartID] != -1 || PlayerInfo[playerid][pPodID] != -1) return SCM(playerid, red, "У вас уже имеется жилье.");
                        foreach(new i : Allkvart)
                        {
                            if(KvartInfo[i][kvart_pod_id] == player_in_podezd[playerid])
                            {
                                if(KvartInfo[i][kvart_Owned] == 0)
                                {
                                    new string[256];
                                    new floor = 1;
                                    if(KvartInfo[i][kvart_type] >= 0 && KvartInfo[i][kvart_type] <= 2) floor = 1;
                                    else if(KvartInfo[i][kvart_type] >= 3 && KvartInfo[i][kvart_type] <= 4) floor = 2;
                                    else if(KvartInfo[i][kvart_type] >= 5 && KvartInfo[i][kvart_type] <= 7) floor = 3;

                                    format(string, sizeof(string), "{FFFFFF}Мы вам предлагаем арендовать квартиру №%d на %d этаже.\nСтоимоть аренды 2000 рублей.", KvartInfo[i][kvart_type]+1, floor);
                                    SPD
                                    (
                                        playerid, D_BUY_KVART, DIALOG_STYLE_MSGBOX,
                                        "{"cblue"}Аренда квартиры",
                                        string,
                                        "Арендовать", "Отмена"
                                    );
                                    return SetPVarInt(playerid, "buy_kvart_id", i);
                                }
                            }
                        }
                        return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Подъезд", "{FFFFFF}В данном подъезде нет свободных квартир.", "Закрыть", "");
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][pPodID] != player_in_podezd[playerid]) return SCM(playerid, red, "Вы не проживаете в данном подъезде.");
                        SPD
                        (
                            playerid, D_PODEZD_MENU, DIALOG_STYLE_LIST,
                            "{"cblue"}Меню жыльца",
                            "\
                            {"cblue"}1. {FFFFFF}Оплатить проживание\n\
                            {"cblue"}2. {FFFFFF}Забрать транспорт\n\
                            {"cblue"}3. {FFFFFF}Высилиться из квартиры",
                            "Далее", "Отмена"
                        );
                    }
                }
            }
        }
        case D_PAY_KVART:
        {
            if(!response)
            {
                DeletePVar(playerid, "my_kvart_id");
                SPD
                (
                    playerid, D_PODEZD_MENU, DIALOG_STYLE_LIST,
                    "{"cblue"}Меню жыльца",
                    "\
                    {"cblue"}1. {FFFFFF}Оплатить проживание\n\
                    {"cblue"}2. {FFFFFF}Забрать транспорт\n\
                    {"cblue"}3. {FFFFFF}Высeлиться из квартиры",
                    "Далее", "Отмена"
                );
            }
            else
            {
                new h = GetPVarInt(playerid, "my_kvart_id");
                if(!IsNumeric(inputtext) || strval(inputtext) < 0 || !strlen(inputtext) || PlayerInfo[playerid][pCash] < kvart_params[0][rent]*strval(inputtext) || KvartInfo[h][kvart_days]+strval(inputtext) > 30)
                {

                    new string[256];
                    format(string, sizeof(string), "{FFFFFF}Ваша квартира оплачена на: %d/30 дней.\n\nНа какое количество дней вы хотите оплатить квартиру?", KvartInfo[h][kvart_days]);
                    SPD
                    (
                        playerid, D_PAY_KVART, DIALOG_STYLE_INPUT,
                        "{"cblue"}Оплата квартиры",
                        string,
                        "Оплатить", "Назад"
                    );
                    return SetPVarInt(playerid, "my_kvart_id", h);
                }

                GiveMoney(playerid, -kvart_params[0][rent]*strval(inputtext), "Оплата квартиры");
                KvartInfo[h][kvart_days] += strval(inputtext);

                SaveKvart(h);

                DeletePVar(playerid, "my_kvart_id");
                new string[144];
                format(string, sizeof(string), "Вы оплатили свою квартиру на {"cyellow"}%d дней", strval(inputtext));
                return SCM(playerid, blue, string);        
            }
        }
        case D_PODEZD_MENU:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        new i;
                        foreach(new h : Allkvart) if(KvartInfo[h][kvart_id] == PlayerInfo[playerid][pKvartID]) i = h;

                        new string[256];
                        format(string, sizeof(string), "{FFFFFF}Ваша квартира оплачена на: %d/30 дней.\n\nНа какое количество дней вы хотите оплатить квартиру?", KvartInfo[i][kvart_days]);
                        SPD
                        (
                            playerid, D_PAY_KVART, DIALOG_STYLE_INPUT,
                            "{"cblue"}Оплата квартиры",
                            string,
                            "Оплатить", "Назад"
                        );
                        return SetPVarInt(playerid, "my_kvart_id", i);
                    }
                    case 1: 
                    {
                        new query[60];
                        format(query, sizeof(query), "SELECT * FROM `ownable_cars` WHERE `owner_id` = '%d'", PlayerInfo[playerid][pID]);
                        mysql_tquery(connects, query, "LoadMyCar", "i", playerid);
                    }
                    case 2:
                    {
                        new i;
                        foreach(new h : Allkvart) if(KvartInfo[h][kvart_id] == PlayerInfo[playerid][pKvartID]) i = h;

                        PlayerInfo[playerid][pKvartID] = -1;
                        PlayerInfo[playerid][pPodID] = -1;

                        TotalFreeKvart++;

                        KvartInfo[i][kvart_Owned] = 0;  
                        KvartInfo[i][kvart_Owner] = EOS;
                        format(KvartInfo[i][kvart_Owner], MAX_PLAYER_NAME, "None");
                        SaveKvart(i);  
                        BuyKvart(i);  

                        SPD
                        (
                            playerid, D_NULL, DIALOG_STYLE_MSGBOX,
                            "{"cblue"}Продажа квартиры",
                            "{FFFFFF}Вы успешно выселились из квартиры.",
                            "Закрыть", ""
                        );

                        DestroyOwnableCar(playerid);
                        SaveAccounts(playerid);
                        return 1;
                    }
                }
            }
        }
        case D_BUY_KVART:
        {
            if(!response) return DeletePVar(playerid, "buy_kvart_id");
            else
            {
                new i = GetPVarInt(playerid, "buy_kvart_id");
                DeletePVar(playerid, "buy_kvart_id");
                if(PlayerInfo[playerid][pCash] < 2000) return SCM(playerid, red, "У вас недостаточно денег.");
                if(KvartInfo[i][kvart_Owned] == 1) return SCM(playerid, red, !"Данной квартирой уже кто-то владеет.");

                GiveMoney(playerid, -2000, "Аренда квартиры");

                PlayerInfo[playerid][pKvartID] = KvartInfo[i][kvart_id];
                PlayerInfo[playerid][pPodID] = player_in_podezd[playerid];

                SetPlayerVirtualWorld(playerid, KvartInfo[i][kvart_id]);
                FreezePlayer(playerid, 2000);
                SetPlayerPos(playerid, kvart_params[0][kvart_exit_x], kvart_params[0][kvart_exit_y], kvart_params[0][kvart_exit_z]);

                player_in_podezd[playerid] = -1;
                player_in_kvart[playerid] = KvartInfo[i][kvart_id];

                TotalFreeKvart--;

                KvartInfo[i][kvart_days] = 3;  
                KvartInfo[i][kvart_Owned] = 1;  
                KvartInfo[i][kvart_Owner] = EOS;
                format(KvartInfo[i][kvart_Owner], MAX_PLAYER_NAME, "%s", PlayerInfo[playerid][pName]);
                SaveKvart(i);  
                BuyKvart(i);  

                SPD
                (
                    playerid, D_NULL, DIALOG_STYLE_MSGBOX,
                    "{"cblue"}Покупка квартиры",
                    "{FFFFFF}Поздравляем вас с успешной покупкой квартиры. Оплатить квартиру вы можете в подъезде у выхода.",
                    "Закрыть", ""
                );

                SaveAccounts(playerid);
                return DeletePVar(playerid, "buy_kvart_id");
            }
        }
    }
	#if	defined	podezd__OnDialogResponse
		return podezd__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse podezd__OnDialogResponse
#if	defined	podezd__OnDialogResponse
	forward podezd__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif