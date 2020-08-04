#define MIN_PUT_IN_VEHICLE_TIME 500

static
	p_put_time[MAX_PLAYERS];

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	p_put_time[playerid] = GetTickCount();

	#if defined ac_tpinveh__OnPlayerEnterVehicl
		return ac_tpinveh__OnPlayerEnterVehicl(playerid, vehicleid, ispassenger);
	#else
	    return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle ac_tpinveh__OnPlayerEnterVehicl
#if defined ac_tpinveh__OnPlayerEnterVehicl
forward ac_tpinveh__OnPlayerEnterVehicl(playerid, vehicleid, ispassenger);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		if(GetTickCount() - p_put_time[playerid] < MIN_PUT_IN_VEHICLE_TIME)
		{			
			if(AntiCheatInfo[TP_in_VEH_AC][acStatus] == 0) return ResultMessageCheat(playerid, 9);
            else ResultCheat(playerid, 9);
		}
	}
	#if defined ac_tpinveh__OnPlayerStateChange
		return ac_tpinveh__OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange ac_tpinveh__OnPlayerStateChange
#if defined ac_tpinveh__OnPlayerStateChange
	forward ac_tpinveh__OnPlayerStateChange(playerid, newstate, oldstate);
#endif