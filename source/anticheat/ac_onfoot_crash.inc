new AntiOnFootCrash[MAX_PLAYERS char];

public OnPlayerConnect(playerid)
{
    AntiOnFootCrash{playerid} = 0;
    #if	defined	ac_onfoot__OnPlayerConnect
        return ac_onfoot__OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerConnect
	#undef	OnPlayerConnect
#else
	#define	_ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect	ac_onfoot__OnPlayerConnect

#if	defined	ac_onfoot__OnPlayerConnect
forward ac_onfoot__OnPlayerConnect(playerid);
#endif

public OnPlayerUpdate(playerid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerCameraFrontVector(playerid, x, y, z);
    if(floatcmp(x, -1.0) == -1 || floatcmp(x, 1.0) == 1
    || floatcmp(y, -1.0) == -1 || floatcmp(y, 1.0) == 1
    || floatcmp(z, -1.0) == -1 || floatcmp(z, 1.0) == 1)
    {
        if(AntiOnFootCrash{playerid})
            if(AntiCheatInfo[OnFootCrash_AC][acStatus] == 1) ResultCheat(playerid, 1);
            else ResultMessageCheat(playerid, 11);
        else
            AntiOnFootCrash{playerid}=1; //ложный вызов из-за старых данных.
        return 0;
    }
    #if	defined	ac_onfoot__OnPlayerUpdate
        return ac_onfoot__OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerUpdate
	#undef	OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif

#define	OnPlayerUpdate	ac_onfoot__OnPlayerUpdate

#if	defined	ac_onfoot__OnPlayerUpdate
forward ac_onfoot__OnPlayerUpdate(playerid);
#endif