stock SpawnList(playerid)
{
	new fmt_dialog[528] = "{"cblue"}1. {FFFFFF}На вокзале\n{"cblue"}2. {FFFFFF}Дома\n{"cblue"}3. {FFFFFF}В квартире\n{"cblue"}4. {FFFFFF}На базе организации\n";
	if(PlayerInfo[playerid][pLogin] != true) strcat(fmt_dialog, "{"cblue"}5. {FFFFFF}Где вышел");

    SPD(playerid, D_SPAWN_LIST, DIALOG_STYLE_LIST, "{"cblue"}Выбор спавна", fmt_dialog, "Далее", "");
	return 1;
}
stock SetSpawnVokzal(playerid)
{
    SpawnPlayer(playerid);
    SetPlayerPos(playerid, 1823.5634, 2528.6885, 15.6825);
    SetPlayerFacingAngle(playerid, 130.7277);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerInterior(playerid, 0);
	SetPlayerDefaultVariables(playerid);
	return 1;
}
stock SetSpawnAtHome(playerid)
{
	if(PlayerInfo[playerid][pHomeID] == -1)
	{
		SCM(playerid, red, "У вас нет дома.");
		return SpawnList(playerid);
	}
	new h;
	foreach(new i : Allhouses) if(HouseInfo[i][hID] == PlayerInfo[playerid][pHomeID])
	{
		h = i;
		break;
	}
    SpawnPlayer(playerid);
    SetPlayerPos(playerid, house_params[ HouseInfo[h][hType] ][store_pos_x], house_params[ HouseInfo[h][hType] ][store_pos_y], house_params[ HouseInfo[h][hType] ][store_pos_z]);
    SetPlayerVirtualWorld(playerid, h);
    SetPlayerInterior(playerid, 0);
	player_in_house[playerid] = h;
	SetPlayerDefaultVariables(playerid);
	return 1;
}
stock SetSpawnAtKvartira(playerid)
{
	if(PlayerInfo[playerid][pKvartID] == -1 || PlayerInfo[playerid][pPodID] == -1)
	{
		SCM(playerid, red, "У вас нет квартиры.");
		return SpawnList(playerid);
	}
    SpawnPlayer(playerid);

    SetPlayerPos(playerid, kvart_params[0][kvart_spawn_x], kvart_params[0][kvart_spawn_y], kvart_params[0][kvart_spawn_z]);
    SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pKvartID]);
    SetPlayerInterior(playerid, 0);
	player_in_kvart[playerid] = PlayerInfo[playerid][pKvartID];
	SetPlayerDefaultVariables(playerid);
	return 1;
}
stock SetSpawnAtOrganithation(playerid)
{
	if(PlayerInfo[playerid][pMember] < 1)
	{
	    SCM(playerid, red, "Вы не состоите в организации.");
	    return SpawnList(playerid);
	}
	SpawnPlayer(playerid);

	new frac = PlayerInfo[playerid][pMember];
	SetPlayerInterior(playerid, FractionInfo[frac][fractionInt]);
	SetPlayerPos(playerid, FractionInfo[frac][fPosX],FractionInfo[frac][fPosY],FractionInfo[frac][fPosZ]);
	SetPlayerFacingAngle(playerid, FractionInfo[frac][fPosA]);
	SetPlayerVirtualWorld(playerid, FractionInfo[frac][fractionVirt]);
	SetCameraBehindPlayer(playerid);

    SetPlayerDefaultVariables(playerid);
	return 1;
}
stock SetSpawnAtLastPlace(playerid)
{
	new Float:x, Float:y, Float:z;
	x = PlayerInfo[playerid][pLastX];
	y = PlayerInfo[playerid][pLastY];
	z = PlayerInfo[playerid][pLastZ];
	
	if(x == 0.0 || y == 0.0 || z == 0.0)
	{
	    SCM(playerid, red, "Координаты были утеряны.");
	    return SpawnList(playerid);
	}

    SpawnPlayer(playerid);
	SetPlayerPos(playerid, x, y, z);
	SetPlayerDefaultVariables(playerid);
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_SPAWN_LIST:
		{
		    if(!response)
		    {
				if(PlayerInfo[playerid][pLogin] != true)
				{
					SCM(playerid, red, "Вы были кикнуты с сервера, потому что отказались от авторизации");
					NewKick(playerid);
				}
		    }
		    else
		    {
		        switch(listitem)
		        {
		            case 0: SetSpawnVokzal(playerid);
		            case 1: SetSpawnAtHome(playerid);
		            case 2: SetSpawnAtKvartira(playerid);
		            case 3: SetSpawnAtOrganithation(playerid);
		            case 4: SetSpawnAtLastPlace(playerid);
		        }
		    }
		}
    }
	#if	defined	spawn__OnDialogResponse
		return spawn__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse spawn__OnDialogResponse
#if	defined	spawn__OnDialogResponse
	forward spawn__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif