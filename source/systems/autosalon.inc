new player_buy_car[MAX_PLAYERS]     = {-1, ...};
new buy_car_select_car[MAX_PLAYERS] = {-1, ...};
new buy_car_select_color[MAX_PLAYERS];

enum E_STRUCT_CAR_MARKET
{
	car_id,
	car_cost,
	car_name[64]
};

new car_market_data[35][E_STRUCT_CAR_MARKET] =
{
	{400, 4000000,  "BMW X5"},
	{401, 150000,   "ВАЗ 2107"},
	{404, 1500000,  "Mercedes A 45 AMG"},
	{410, 5000000,  "Range Rover Supercharged Sport 2012"},
	{412, 100000,   "Москвич Комби"},
	{415, 12000000, "Mercedes AMG GT"},
	{421, 1200000,  "Mercedes E500"},
	{436, 2500000,  "Mercedes CLS63"},
	{439, 150000,   "LADA 112"},
	{451, 16000000, "Ferrari Scuderia"},
	{458, 130000,   "ГАЗ 24"},
	{466, 20000000, "Porsche Panamera GTS"},
	{467, 150000,   "ВАЗ 2103"},
	{474, 200000,   "ГАЗ 21"},
	{477, 1500000,  "Mazda RX 7"},
	{479, 800000,   "Chevrolet Captiva"},
	{489, 1300000,  "Toyota Highlander"},
	{505, 2000000,  "BMW X5"},
	{506, 6000000,  "Corvette Stingray"},
	{526, 800000,   "Renault Megane"},
	{529, 600000,   "Lada Priora"},
	{535, 500000,   "Волга Купе"},
	{546, 173000,   "ВАЗ 2106"},
	{550, 1000000,  "Volkswagen Passat"},
	{551, 3000000,  "Mercedes S600"},
	{558, 7000000,  "BMW M4"},
	{559, 10000000, "Mitsubishi Lancer Evolution MR"},
	{562, 4000000,  "Nissan Silvia S15"},
	{565, 140000,   "LADA 2108 'Спутник'"},
	{576, 120000,   "Москвич 408"},
	{579, 6000000,  "Mercedes Gelenvagen"},
	{585, 5500000,  "AUDI A6"},
	{587, 7000000,  "BMW M5"},
	{589, 5400000,  "Mini Cooper"},
	{602, 5000000,  "Volkswagen Touareg"}
};

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{

    if(playertextid == PlayerText:auto_salon_td[playerid][8])
    {
        CarMarketShowNextCar(playerid, '+');
    }
    // - back car
    if(playertextid == PlayerText:auto_salon_td[playerid][7])
    {
        CarMarketShowNextCar(playerid, '-');
    }
    // - next color
    if(playertextid == PlayerText:auto_salon_td[playerid][16])
    {
        CarMarketShowNextColor(playerid, '+');
    }
    // - back color
    if(playertextid == PlayerText:auto_salon_td[playerid][15])
    {
        CarMarketShowNextColor(playerid, '-');
    }
	if(playertextid == PlayerText:auto_salon_td[playerid][26]) // купить*/
	{

		if(PlayerInfo[playerid][pHomeID] == -1) if(PlayerInfo[playerid][pPodID] == -1) return SCM(playerid, red, "Для того чтобы купить транспорт необходимо иметь жильё. (дом, квартира)");

		if(PlayerInfo[playerid][pCarID] != -1) return SCM(playerid, red, "У Вас уже есть личный транспорт");

		if(PlayerInfo[playerid][pLicB] == 0) return SCM(playerid, red, "У Вас нет прав категории B");

		new select_car = buy_car_select_car[playerid];

		if(PlayerInfo[playerid][pCash] < car_market_data[select_car][car_cost]) return SCM(playerid, red, "У Вас недостаточно денег для покупки этого транспорта");

		GiveMoney(playerid, -car_market_data[select_car][car_cost], "Покупка автомобиля в автосалоне");

		new modelid;

		modelid = car_market_data[select_car][car_id];

		new query[120];
		format
		(
			query, sizeof query,
			"INSERT INTO `ownable_cars` (`owner_id`,`model_id`,`color`,`cost_car`) VALUES ('%d','%d','%d, %d', '%d')",
			PlayerInfo[playerid][pID],
			modelid,
			buy_car_select_color[playerid],
			0,
			car_market_data[select_car][car_cost]
		);
		mysql_query(connects, query);

		SCM(playerid, blue, "Поздравляем Вас с успешной покупкой транспорта");
		SCM(playerid, blue, "Получить номера вы можете в Полиции ({"cyellow"}/mynumber{"cblue"})");
		SCM(playerid, blue, "Если у Вас дом, то перезайдите. Если у Вас квартира то заберите транспорт в подъезде.");

		PlayerInfo[playerid][pCarID] = modelid;

        SaveAccounts(playerid);

		for(new i = 0; i < auto_salon_td_size; i++) PlayerTextDrawHide(playerid, auto_salon_td[playerid][i]);

		FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 2022.1450,1883.4620,15.6600);
		SetPlayerFacingAngle(playerid, 0.9597);
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);

		DestroyVehicle(player_buy_car[playerid]);

		buy_car_select_color[playerid] =
		player_buy_car[playerid] = -1;

		CancelSelectTextDraw(playerid);
	}    
    if(playertextid == PlayerText:auto_salon_td[playerid][28] || playertextid == PlayerText:INVALID_TEXT_DRAW) // отмена
    {
        if(GetPVarInt(playerid, "player_in_autosalon") == 1)
        {  
            DeletePVar(playerid, "player_in_autosalon");
            for(new i = 0; i < auto_salon_td_size; i++) PlayerTextDrawHide(playerid, auto_salon_td[playerid][i]);

            FreezePlayer(playerid, 2000);
            SetPlayerPos(playerid, 2022.1450,1883.4620,15.6600);
            SetPlayerFacingAngle(playerid, 0.9597);
            SetCameraBehindPlayer(playerid);
            TogglePlayerControllable(playerid, 0);
            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);

            DestroyVehicle(player_buy_car[playerid]);

            buy_car_select_color[playerid] =
            player_buy_car[playerid] = -1;

            CancelSelectTextDraw(playerid);
        }
    }
    #if defined as__OnPlayerClickPlayerTextDraw
        return as__OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerClickPlayerTextDra || defined _ALS_OnPlayerClickPlayerTD
    #undef OnPlayerClickPlayerTextDraw
#else
    #define _ALS_OnPlayerClickPlayerTextDra
    #define _ALS_OnPlayerClickPlayerTD
#endif

#define OnPlayerClickPlayerTextDraw as__OnPlayerClickPlayerTextDraw
#if defined as__OnPlayerClickPlayerTextDraw
    forward as__OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW) // отмена
    {
        if(GetPVarInt(playerid, "player_in_autosalon") == 1)
        {  
            DeletePVar(playerid, "player_in_autosalon");
            for(new i = 0; i < auto_salon_td_size; i++) PlayerTextDrawHide(playerid, auto_salon_td[playerid][i]);

            FreezePlayer(playerid, 2000);
            SetPlayerPos(playerid, 2022.1450,1883.4620,15.6600);
            SetPlayerFacingAngle(playerid, 0.9597);
            SetCameraBehindPlayer(playerid);
            TogglePlayerControllable(playerid, 0);
            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);

            DestroyVehicle(player_buy_car[playerid]);

            buy_car_select_color[playerid] =
            player_buy_car[playerid] = -1;

            CancelSelectTextDraw(playerid);
        }
    }
    #if defined as__OnPlayerClickTextDraw
        return as__OnPlayerClickTextDraw(playerid, Text:clickedid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerClickTextDraw
    #undef OnPlayerClickTextDraw
#else
    #define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw as__OnPlayerClickTextDraw
#if defined as__OnPlayerClickTextDraw
    forward as__OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, 2021.8312,1879.7206,15.6600))
        {
            SetPVarInt(playerid, "player_in_autosalon", 1);
			buy_car_select_car[playerid] = 0;
			
			buy_car_select_color[playerid] = 1;
			
			SetPlayerVirtualWorld(playerid, playerid + 1);
			SetPlayerPos(playerid, 1036.5732, -1313.1025, 930.000);
			TogglePlayerControllable(playerid, false);
			SetPlayerInterior(playerid, 1);

			player_buy_car[playerid] = AddStaticVehicle(car_market_data[0][car_id], 1043.2223, -1315.9160, 942.4186, 90.0000, buy_car_select_color[playerid], 1);

			SetVehicleVirtualWorld(player_buy_car[playerid], playerid + 1);
			LinkVehicleToInterior(player_buy_car[playerid], 1);
			
			SetPlayerCameraPos(playerid, 1036.5732, -1313.1025, 944.5166);
			SetPlayerCameraLookAt(playerid, 1037.5304, -1313.3905, 944.1879);
			
			SelectTextDraw(playerid, white);
			
			for(new i = 0; i < auto_salon_td_size; i++) PlayerTextDrawShow(playerid, auto_salon_td[playerid][i]);
			
			BuyCarTDUpdate(playerid);
        }
    }
	#if	defined	as__OnPlayerKeyStateChange
		return as__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange as__OnPlayerKeyStateChange
#if	defined	as__OnPlayerKeyStateChange
	forward as__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {

    }
	#if	defined	as__OnDialogResponse
		return as__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse as__OnDialogResponse
#if	defined	as__OnDialogResponse
	forward as__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(GetPVarInt(playerid, "player_in_autosalon") == 1)
	{  
		DeletePVar(playerid, "player_in_autosalon");
		for(new i = 0; i < auto_salon_td_size; i++) PlayerTextDrawHide(playerid, auto_salon_td[playerid][i]);

		FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 2022.1450,1883.4620,15.6600);
		SetPlayerFacingAngle(playerid, 0.9597);
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 0);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);

		DestroyVehicle(player_buy_car[playerid]);

		buy_car_select_color[playerid] =
		player_buy_car[playerid] = -1;

		CancelSelectTextDraw(playerid);
	}
	#if	defined	as__OnPlayerDisconnect
		return as__OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerDisconnect
	#undef	OnPlayerDisconnect
#else
	#define	_ALS_OnPlayerDisconnect
#endif

#define	OnPlayerDisconnect as__OnPlayerDisconnect
#if	defined	as__OnPlayerDisconnect
	forward as__OnPlayerDisconnect(playerid, reason);
#endif

stock BuyCarTDUpdate(playerid) 
{
	if(player_buy_car[playerid] == -1) return 1;
	
	new select_car = buy_car_select_car[playerid]; 
	
	new format_td[85];
	format
	(
	    format_td, sizeof format_td, "%s",
		car_market_data[select_car][car_name],
		car_market_data[select_car][car_cost]
	);
	PlayerTextDrawSetString(playerid, auto_salon_td[playerid][9], format_td);
	
	format
	(
	    format_td, sizeof format_td, "%dр.",
		car_market_data[select_car][car_cost]
	);
	PlayerTextDrawSetString(playerid, auto_salon_td[playerid][22], format_td);
	
	return 1;
}

stock CarMarketShowNextCar(playerid, next = '+')
{	
	static const max_car_index[] = {264};
	
	if(next == '+')
	{
		if(++buy_car_select_car[playerid] > max_car_index[0])
			buy_car_select_car[playerid] = 0;
	}
	else 
	{
		if(--buy_car_select_car[playerid] < 0)
			buy_car_select_car[playerid] = max_car_index[0];
	}
	
	new select_car = buy_car_select_car[playerid];
	new color = buy_car_select_color[playerid];
	
	DestroyVehicle(player_buy_car[playerid]);
	player_buy_car[playerid] = AddStaticVehicle(car_market_data[select_car][car_id], 1043.2223, -1315.9160, 942.4186, 90.0000, color, 0);
	SetPlayerVirtualWorld(playerid, playerid + 1);
	SetVehicleVirtualWorld(player_buy_car[playerid], playerid + 1); 
	LinkVehicleToInterior(player_buy_car[playerid], 1);
	
	BuyCarTDUpdate(playerid);
	
	return 1;
}

stock CarMarketShowNextColor(playerid, next = '+')
{
	if(next == '+')
	{
		buy_car_select_color[playerid] ++;
	
		ChangeVehicleColor(player_buy_car[playerid], buy_car_select_color[playerid], 0);
	}
	else
	{
		buy_car_select_color[playerid] --;
		
		if(buy_car_select_color[playerid] < 0)
			buy_car_select_color[playerid] = 0;
		
		ChangeVehicleColor(player_buy_car[playerid], buy_car_select_color[playerid], 0);
	}
	return 1;
}