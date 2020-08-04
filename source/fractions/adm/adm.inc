public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 792.1604,797.8721,-68.2860))
        {
            if(PlayerInfo[playerid][pMember] != TEAM_ADM) return 1;
            GivePlayerWeaponAC(playerid, 3, 1);
            SCM(playerid, green, "Вы взяли дубинку!");
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1799.2402,2121.8689,15.8595))
        {
            SetPlayerPos(playerid, 1800.0179,2121.4419,25.3648);
        }
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1800.0179,2121.4419,25.3648))
        {
            SetPlayerPos(playerid, 1799.2402,2121.8689,15.8595);
        }
    }
	#if	defined	adm__OnPlayerKeyStateChange
		return adm__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange adm__OnPlayerKeyStateChange
#if	defined	adm__OnPlayerKeyStateChange
	forward adm__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TEAM_ADM_CAR][0] <= vehicleid <= job_car[TEAM_ADM_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_ADM && PlayerInfo[playerid][pMember] != TEAM_FSB)
            {
                SCM(playerid, red, "У вас нет ключей от этого транспорта!");
                return ClearAnimations(playerid, true);
            }
        }
	}
	#if	defined	adm__OnPlayerEnterVehicle
		return adm__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle adm__OnPlayerEnterVehicle
#if	defined	adm__OnPlayerEnterVehicle
	forward adm__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif