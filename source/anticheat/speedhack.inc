public OnPlayerUpdate(playerid)
{
	if(!IsAPlane(GetPlayerVehicleID(playerid)) && SpeedVehicle(playerid) > 185)
	{
	    if(AntiCheatInfo[SpeedHack_AC][acStatus] == 1) return ResultCheat(playerid, 4);
	    else return ResultMessageCheat(playerid, 4);
	}
    #if defined sh_ac__OnPlayerUpdate
        return sh_ac__OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate sh_ac__OnPlayerUpdate
#if defined sh_ac__OnPlayerUpdate
    forward sh_ac__OnPlayerUpdate(playerid);
#endif