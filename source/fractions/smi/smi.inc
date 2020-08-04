public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
        if(GetPVarInt(playerid, "smi_news") == 1)
        {
            DeletePVar(playerid, "smi_news");
            SCM(playerid, green, "Вы вышли из Эфира!");
        }
    }

    #if defined smi__OnPlayerStateChange
        return smi__OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerStateChange
	#undef	OnPlayerStateChange
#else
	#define	_ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange smi__OnPlayerStateChange
#if	defined	smi__OnPlayerStateChange
	forward smi__OnPlayerStateChange(playerid, newstate, oldstate); 
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TEAM_SMI_CAR][0] <= vehicleid <= job_car[TEAM_SMI_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_SMI && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет ключей от этого транспорта!");
            }
        }
	}
	#if	defined	smi__OnPlayerEnterVehicle
		return smi__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle smi__OnPlayerEnterVehicle
#if	defined	smi__OnPlayerEnterVehicle
	forward smi__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif