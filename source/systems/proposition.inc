// proposition Y / N
new send_proposition[MAX_PLAYERS] = {-1, ...}; // кому я предложил
new incoming_proposition[MAX_PLAYERS] = {-1, ...}; // кто мне предложил
new incoming_proposition_type[MAX_PLAYERS] = {-1, ...}; // тип входящего предложения
new incoming_proposition_value[MAX_PLAYERS][2]; // значение входящего предложения

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_YES)
	{
        cmd::yes(playerid);
	}
	if(newkeys == KEY_NO)
	{
        cmd::no(playerid);
	}
	#if	defined	prop__OnPlayerKeyStateChange
		return prop__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange prop__OnPlayerKeyStateChange
#if	defined	prop__OnPlayerKeyStateChange
	forward prop__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock SendProposition(playerid, to_player, type, value_1 = 0, value_2 = 0)
{
	if(incoming_proposition[to_player] != -1) return SCM(playerid, red, "У игрока есть активные предложения.");
	if(send_proposition[playerid] != -1) return SCM(playerid, -1, "Используйте {FF9900}/cancel {FFFFFF}чтобы отозвать предыдущее предложение");
	
	send_proposition[playerid] = to_player;
	incoming_proposition[to_player] = playerid;
	incoming_proposition_type[to_player] = type;
	incoming_proposition_value[to_player][0] = value_1;
    incoming_proposition_value[to_player][1] = value_2;

	new fmt_msg[144];
	switch(type)
	{
		case PROPOSITION_TYPE_REPAIR_CAR:
		{
			format(fmt_msg, sizeof fmt_msg, "%s предлагает починить Ваш транспорт за %d руб", PlayerInfo[incoming_proposition[to_player]][pName], value_1);
			SCM(to_player, 0x3399FFFF, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы согласиться или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof fmt_msg, "Вы предложили %s сделать ремонт транспорта за %d руб", PlayerInfo[incoming_proposition[to_player]][pName], value_1);
			SCM(playerid, 0x3399FFFF, fmt_msg);
		}
		case PROPOSITION_TYPE_INVITE:
		{
			format(fmt_msg, sizeof fmt_msg, "%s %s предлагает Вам вступить в \"%s\"", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], GetMember[ PlayerInfo[playerid][pMember] ]);
			SCM(to_player, 0x3399FFFF, fmt_msg);
			
			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");
		
			format(fmt_msg, sizeof fmt_msg, "Вы предложили %s вступить в \"%s\"", PlayerInfo[to_player][pName], GetMember[ PlayerInfo[playerid][pMember] ]);
			SCM(playerid, 0x3399FFFF, fmt_msg);
		}
		case PROPOSITION_TYPE_FINVITE:
		{
			new f;
			foreach(new i : AllFamilys) if(PlayerInfo[playerid][pFamID] == FamilyInfo[i][fID]) f = i;
			
			format(fmt_msg, sizeof fmt_msg, "%s предлагает Вам вступить в семью \"%s\"", PlayerInfo[playerid][pName], FamilyInfo[f][fName]);
			SCM(to_player, 0x3399FFFF, fmt_msg);
			
			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");
		
			format(fmt_msg, sizeof fmt_msg, "Вы предложили %s вступить в вашу семью", PlayerInfo[to_player][pName]);
			SCM(playerid, 0x3399FFFF, fmt_msg);
		}
		case PROPOSITION_TYPE_FREE:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам выйти из КПЗ за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s выйти из КПЗ за %d рублей", PlayerInfo[send_proposition[playerid]][pName], value_1);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_HEAL:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам пройти платный курс лечения за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s пройти платный курс лечения за %d рублей", PlayerInfo[send_proposition[playerid]][pName], value_1);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_SELLLIC:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам приобрести лицензию на %s %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], lic_names[value_1], lic_price[value_1]);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s приобрести лицензию на %s за %d рублей", PlayerInfo[send_proposition[playerid]][pName], lic_names[value_1], lic_price[value_1]);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_SELLGUN:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам купить %s с %d пт. за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], gun_name[GetPVarInt(incoming_proposition[to_player], "weapon_id")], value_1, value_2);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s купить %s с %d пт. за %d рублей", PlayerInfo[send_proposition[playerid]][pName], gun_name[GetPVarInt(incoming_proposition[to_player], "weapon_id")], value_1, value_2);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_SELLDRUGS:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам купить %d гр. за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], value_1, value_2);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s купить %d гр. наркотиков за %d рублей", PlayerInfo[send_proposition[playerid]][pName], value_1, value_2);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_SELLBIZ:
		{
			new i = GetPVarInt(playerid, "my_biz_id");
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам купить его бизнес %s за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], business_params[ BusinessInfo[i][bType] ][bname], value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s купить ваш бизнес %s за %d рублей", PlayerInfo[send_proposition[playerid]][pName], business_params[ BusinessInfo[i][bType] ][bname], value_1);
			SCM(playerid, blue, fmt_msg);
		}

		case PROPOSITION_TYPE_SELLCAR:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам купить его транспорт %s за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], GetCarName(GetVehicleModel(player_ownable_car[ incoming_proposition[to_player] ])), value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s купить ваш транспорт %s за %d рублей", PlayerInfo[send_proposition[playerid]][pName], GetCarName(GetVehicleModel(player_ownable_car[playerid])), value_1);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_SELLHOUSE:
		{
			new h = value_2;
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам купить его дом № %d за %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], HouseInfo[h][hID], value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s купить ваш дом № %d за %d рублей", PlayerInfo[send_proposition[playerid]][pName], HouseInfo[h][hID], value_1);
			SCM(playerid, blue, fmt_msg);
		}
		case PROPOSITION_TYPE_DICE:
		{
			format(fmt_msg, sizeof(fmt_msg), "%s предлгает вам кинуть кости на %d рублей", PlayerInfo[incoming_proposition[to_player]][pName], value_1);
			SCM(to_player, blue, fmt_msg);

			SCM(to_player, -1, "Нажмите {00CC00}Y {FFFFFF}чтобы принять предложение или {FF6600}N {FFFFFF}для отказа");

			format(fmt_msg, sizeof(fmt_msg), "Вы предложили %s кинуть кости на %d рублей", PlayerInfo[send_proposition[playerid]][pName], value_1);
			SCM(playerid, blue, fmt_msg);
		}
	}
	return 1;
}
stock ClearProposition(playerid)
{
	send_proposition[playerid] = -1;
	incoming_proposition[playerid] = -1;
	incoming_proposition_type[playerid] = -1;
	incoming_proposition_value[playerid][0] = -1;
	incoming_proposition_value[playerid][1] = -1;

	return 1;
}

CMD:cancel(playerid)
{
	new send_to_player = send_proposition[playerid];
	if(send_to_player == -1) return SCM(playerid, 0xCECECEFF, "У Вас нет активных предложений");

	new player_incoming_proposition = incoming_proposition[send_to_player];
	ClearProposition(playerid);

	if(player_incoming_proposition == playerid)
	{
		ClearProposition(send_to_player);

		new fmt_msg[55];
		format(fmt_msg, sizeof fmt_msg, "%s отозвал свое предложение", PlayerInfo[playerid][pName]);
		SCM(send_to_player, 0xFF6600FF, fmt_msg);

		format(fmt_msg, sizeof fmt_msg, "Вы отозвали свое предложение для %s", PlayerInfo[send_to_player][pName]);
		SCM(playerid, 0xFF6600FF, fmt_msg);
	}
	else SCM(playerid, 0xFF6600FF, "Вы отозвали свое последнее предложение");

	return 1;
}
CMD:yes(playerid)
{
	new proposition = incoming_proposition[playerid];
	new type = incoming_proposition_type[playerid];
	new value_1 = incoming_proposition_value[playerid][0];
	new value_2 = incoming_proposition_value[playerid][1];

	if(proposition != -1)
	{
		ClearProposition(playerid);
		ClearProposition(proposition);
		if(!IsPlayerConnected(proposition)) return SCM(playerid, 0x999999FF, "Игрок вышел из игры");

		new Float: x, Float: y, Float: z;
		GetPlayerPos(proposition, x, y, z);
		new Float: dist = GetPlayerDistanceFromPoint(playerid, x, y, z);

		if(dist > 10.0) return SCM(playerid, 0x999999FF, "Игрок слишком далеко");

		switch(type)
		{
			case PROPOSITION_TYPE_REPAIR_CAR:
			{
				new vehicleid = GetPlayerVehicleID(playerid);

				if(!vehicleid || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, 0xCECECEFF, "Вы должны находится в транспорте за рулем");

				if(PlayerInfo[proposition][pJob] != Job_Car || player_job_vehicle_arend[proposition] == -1) return SCM(playerid, 0xCECECEFF, "Авмеханик не в рабочем транспорте");
				

				if(PlayerInfo[playerid][pCash] < value_1)
					return SCM(playerid, red, "У Вас недостаточно денег");
				if(!IsPlayerInAnyVehicle(proposition)) return SCM(playerid, red, "Игрок не в транспорте!");
				if(GetPlayerVehicleID(proposition) != player_job_vehicle_arend[proposition]) return SCM(playerid, red, "Игрок не в транспорте!");

				GiveMoney(playerid, -value_1, "Починка транспорта");
				GiveMoney(proposition, value_1, "Починка транспорта");

				RepairVehicle(vehicleid);
				SetPlayerChatBubble(playerid, "Repair", 0x3399FFFF, 10.0, 2000);

				new fmt_msg[65];
				format(fmt_msg, sizeof fmt_msg, "Автомеханик %s починил Ваш транспорт за %d рублей", PlayerInfo[proposition][pName], value_1);
				SCM(playerid, 0x66CC00FF, fmt_msg);

				format(fmt_msg, sizeof fmt_msg, "Вы починили транспорт %s за %d рублей", PlayerInfo[playerid][pName], value_1);
				SCM(proposition, 0x66CC00FF, fmt_msg);
			}
			case PROPOSITION_TYPE_INVITE:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Поздравляем! Вы вступили в организацию \"%s\"", GetMember[ PlayerInfo[proposition][pMember] ]);
				SCM(playerid, green, string);
				SCM(playerid, 0x3399FFFF, "Используйте {FFCC00}/menu > Команды сервера{3399FF}, чтобы узнать о новых возможностях");	
				
				PlayerInfo[playerid][pMember] = PlayerInfo[proposition][pMember];
				PlayerInfo[playerid][pRang] = 1;
				PlayerInfo[playerid][pFSkin] = 1;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
				PlayerInfo[playerid][pJob] = 0;
				
				SaveAccounts(playerid);

				format(string, sizeof(string), "%d", playerid);
				cmd::changeskin(proposition, string);
			}

			case PROPOSITION_TYPE_FINVITE:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				new f;
				foreach(new i : AllFamilys) if(PlayerInfo[proposition][pFamID] == FamilyInfo[i][fID]) f = i;

				format(string, sizeof(string), "Поздравляем! Вы вступили в семью \"%s\"", FamilyInfo[f][fName]);
				SCM(playerid, green, string);
				
				PlayerInfo[playerid][pFamID] = PlayerInfo[proposition][pFamID];
				PlayerInfo[playerid][pFamRang] = 1;
				
				SaveAccounts(playerid);
			}
			case PROPOSITION_TYPE_FREE:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Вы вышли из КПЗ за %d рублей", value_1);
				SCM(playerid, blue, string);

				GiveMoney(playerid, -value_1, "Выход из КПЗ");
				GiveMoney(proposition, value_1, "Выпустил из КПЗ");

				PlayerInfo[playerid][pKPZ] = -1;
				PlayerInfo[playerid][pJP] = 0;
				
				SetSpawnVokzal(playerid);
				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_HEAL:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Вы прошли платный курс лечения за %d рублей", value_1);
				SCM(playerid, blue, string);

				GiveMoney(playerid, -value_1, "Курс лечения");
				GiveMoney(proposition, value_1, "Вылечил человека");
				
				PlayerInfo[playerid][pHP] = 100.0;
				SetPlayerHealth(playerid, 100.0);
				PlayerInfo[playerid][pHOSPITAL] = 0;

				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_DICE:
			{
				new b = player_in_business[playerid];
				if(BusinessInfo[b][bType] != b_type_CASINO || b == -1) return SCM(playerid, red, "Вы не находитесь в казино.");

				new rand_1 = random(6)+1, rand_2 = random(6)+1, string[144];
				new value_dice = value_1 / 10;

				if(rand_1 == rand_2)
				{					
					format(string, sizeof string, "Выпало %d", rand_1);

					SetPlayerChatBubble(playerid, string, blue, 10.0, 3000);
					SetPlayerChatBubble(proposition, string, blue, 10.0, 3000);
					
					format(string, sizeof string, "%s и %s бросили кости. Результат {ffcc00}%d:%d", PlayerInfo[playerid][pName], PlayerInfo[proposition][pName], rand_1, rand_2);
					
					SCM(playerid, orange, "Игра закончилась в ничью");
					SCM(proposition, orange, "Игра закончилась в ничью");
				}
				else if(rand_1 > rand_2)
				{
					GiveMoney(playerid, value_1 - value_dice, "Выигрыш в казино");
					GiveMoney(proposition, -value_1, "Проигрыш в казино");

					GiveBusinessMoney(b, value_dice, playerid);
					UpdateBusiness(b);

					format(string, sizeof string, "Выпало %d", rand_1);
					SetPlayerChatBubble(playerid, string, green, 10.0, 3000);

					format(string, sizeof string, "Выпало %d", rand_2);
					SetPlayerChatBubble(proposition, string, red, 10.0, 3000);

					format(string, sizeof string, "%s и %s бросили кости. Результат {"cblue"}%d:%d", PlayerInfo[playerid][pName], PlayerInfo[proposition][pName], rand_1, rand_2);

					SCM(proposition, red, "К сожалению, Вы проиграли");
					SCM(playerid, green, "Поздравляем! Вы выиграли");
				}

				else if(rand_2 > rand_1)
				{
					GiveMoney(playerid, -value_1, "Проигрыш в казино");
					GiveMoney(proposition, value_1 - value_dice, "Выигрыш в казино");

					GiveBusinessMoney(b, value_dice, playerid);
					UpdateBusiness(b);

					format(string, sizeof string, "Выпало %d", rand_1);
					SetPlayerChatBubble(proposition, string, green, 10.0, 3000);

					format(string, sizeof string, "Выпало %d", rand_2);
					SetPlayerChatBubble(playerid, string, red, 10.0, 3000);

					format(string, sizeof string, "%s и %s бросили кости. Результат {"cblue"}%d:%d", PlayerInfo[playerid][pName], PlayerInfo[proposition][pName], rand_1, rand_2);

					SCM(playerid, red, "К сожалению, Вы проиграли");
					SCM(proposition, green, "Поздравляем! Вы выиграли");
				}

				ProxDetector(30.0, playerid, string, 0xc2a2daFF, 0xc2a2daFF, 0xc2a2daFF, 0xc2a2daFF, 0xc2a2daFF);
				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_SELLLIC:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Вы купили лицензию на %s за %d рублей", lic_names[value_1], lic_price[value_1]);
				SCM(playerid, blue, string);

				GiveMoney(playerid, -lic_price[value_1], "Покупка лицензий");
				GiveMoney(proposition, (lic_price[value_1]/2), "Продажа лицензий");
				
				switch(value_1)
				{
					case 1: PlayerInfo[playerid][pLicBiz] = 1;
					case 2:	PlayerInfo[playerid][pLicFly] = 1;
					case 3: PlayerInfo[playerid][pLicGun] = 1;
				}

				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_SELLGUN:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Вы купили %s с %d пт. за %d рублей", gun_name[GetPVarInt(proposition, "weapon_id")], value_1, value_2);
				SCM(playerid, blue, string);

				GiveMoney(playerid, -value_2, "Покупка оружия");
				GiveMoney(proposition, value_2, "Продажа оружия");
				
				GivePlayerWeaponAC(playerid, GetPVarInt(proposition, "weapon_id"), value_1);
				SetPVarInt(playerid, "ammo_count", GetPlayerAmmo(playerid));
				RemovePlayerWeapon(proposition, GetPVarInt(proposition, "weapon_id"));
				if((GetPVarInt(proposition, "ammo_count") - value_1) > 1) GivePlayerWeaponAC(proposition, GetPVarInt(proposition, "weapon_id"), GetPVarInt(proposition, "ammo_count") - value_1);

				DeletePVar(proposition, "weapon_id");
				DeletePVar(proposition, "ammo_count");

				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_SELLDRUGS:
			{
				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);
				
				format(string, sizeof(string), "Вы купили %d гр. наркотиков за %d рублей", value_1, value_2);
				SCM(playerid, blue, string);

				GiveMoney(playerid, -value_2, "Покупка наркотиков");
				GiveMoney(proposition, value_2, "Продажа наркотиков");
				
				PlayerInfo[playerid][pDrugs] += value_1;
				PlayerInfo[proposition][pDrugs] -= value_1;

				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_SELLBIZ:
			{
				new i = GetPVarInt(playerid, "my_biz_id");

				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);

				format(string, sizeof(string), "Вы купили бизнес %s за %d рублей", business_params[ BusinessInfo[i][bType] ][bname], value_1);
				SCM(playerid, blue, string);

				PlayerInfo[playerid][pBizID] = BusinessInfo[i][bID];
				PlayerInfo[proposition][pBizID] = -1;

				BusinessInfo[i][bOwner] = EOS;
				strcat(BusinessInfo[i][bOwner], PlayerInfo[playerid][pName]);

				GiveMoney(playerid, -value_1, "Покупка бизнеса у игрока");
				GiveMoney(proposition, value_1, "Продажа бизнеса игроку");
				SaveAccounts(playerid);
				SaveAccounts(proposition);
				UpdateBusiness(i);
				DeletePVar(playerid, "my_biz_id");
			}

			case PROPOSITION_TYPE_SELLCAR:
			{

				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);

				format(string, sizeof(string), "Вы купили транспорт %s за %d рублей", GetCarName(GetVehicleModel(player_ownable_car[proposition])), value_1);
				SCM(playerid, blue, string);

				PlayerInfo[playerid][pCarID] = PlayerInfo[proposition][pCarID];
				PlayerInfo[proposition][pCarID] = -1;

				ownable_car[player_ownable_car[proposition]][oc_owner_id] = PlayerInfo[playerid][pID];
				SaveOwnableCar(proposition);

				DestroyDynamic3DTextLabel(ownable_car_label[player_ownable_car[proposition]]);
				DestroyVehicle(player_ownable_car[proposition]);
				player_ownable_car[proposition] = -1;

				GiveMoney(playerid, -value_1, "Покупка транспорта у игрока");
				GiveMoney(proposition, value_1, "Продажа транспорта игроку");
				SaveAccounts(playerid);
				SaveAccounts(proposition);
			}
			case PROPOSITION_TYPE_SELLHOUSE:
			{
				if(PlayerInfo[playerid][pCash] < value_1)
				{
					SCM(playerid, red, "У вас недостаточно денег.");
					SCM(proposition, red, "У игрока недостаточно денег.");
					return 1;
				}
				if(PlayerInfo[playerid][pHomeID] != -1)
				{
					SCM(playerid, red, "У вас уже есть дом.");
					SCM(proposition, red, "У игрока уже есть дом.");
					return 1;
				}
				new h = value_2;

				new string[128];
				format(string, sizeof(string), "%s принимает Ваше предложение", PlayerInfo[playerid][pName]);
				SCM(proposition, green, string);

				format(string, sizeof(string), "Вы купили дом № %d за %d рублей", HouseInfo[h][hID], value_1);
				SCM(playerid, blue, string);

				PlayerInfo[playerid][pHomeID] = HouseInfo[h][hID];
				PlayerInfo[proposition][pHomeID] = -1;

				HouseInfo[h][hOwner] = EOS;
				strcat(HouseInfo[h][hOwner], PlayerInfo[playerid][pName]);

				GiveMoney(playerid, -value_1, "Покупка дома у игрока");
				GiveMoney(proposition, value_1, "Продажа дома игроку");
				SaveAccounts(playerid);
				SaveAccounts(proposition);
				SaveHouse(h);
				BuyHouse(h);
				DestroyOwnableCar(proposition);
			}
		}
	}
	else return SCM(playerid, red, "Вам ничего не предлагают!");
	return 1;
}
CMD:no(playerid)
{
	new proposition = incoming_proposition[playerid];
	if(proposition == -1) return SCM(playerid, 0x999999FF, "В данный момент Вам ничего не предлагают");

	if(send_proposition[proposition] == playerid)
	{
		ClearProposition(proposition);

		new fmt_msg[60];
		format(fmt_msg, sizeof fmt_msg, "%s отказался от Вашего предложения", PlayerInfo[playerid][pName]);
		SCM(proposition, 0xFF6600FF, fmt_msg);

		format(fmt_msg, sizeof fmt_msg, "Вы отказались от предложения игрока %s", PlayerInfo[proposition][pName]);
		SCM(playerid, 0xFF6600FF, fmt_msg);

		GameTextForPlayer(proposition, "~r~no", 4000, 1);
	}
	else SCM(playerid, 0xFF6600FF, "Вы отказались от предложения игрока");

	ClearProposition(playerid);
	return 1;
}