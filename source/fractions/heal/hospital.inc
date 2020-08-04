new
	Float: hospital_coord[4][3] =
	{
        {-813.4970,1905.9402,702.0200},
        {-796.7776,1905.4965,702.0200},
        {-809.1417,1912.8881,702.0200},
        {-809.1417,1912.8881,702.0200}
    };
new hospital_timer[MAX_PLAYERS];

public OnPlayerSpawn(playerid)
{
    if(PlayerInfo[playerid][pHOSPITAL] == 1)
    {
        new rand = random(3);
        FreezePlayer(playerid, 2000);
        SetPlayerPos(playerid, hospital_coord[rand][0], hospital_coord[rand][1], hospital_coord[rand][2]);

        hospital_timer[playerid] = SetTimerEx("HospitalTimer", 1000, 1, "d", playerid);

        PlayerInfo[playerid][pHP] = 5.0;
        SetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);
    }
    #if defined heal__OnPlayerSpawn
        return heal__OnPlayerSpawn(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else 
    #define _ALS_OnPlayerSpawn
#endif


#define OnPlayerSpawn heal__OnPlayerSpawn
#if defined heal__OnPlayerSpawn
    forward heal__OnPlayerSpawn(playerid);
#endif

publics HospitalTimer(playerid)
{
    if(PlayerInfo[playerid][pHOSPITAL] > 0)
    {
        PlayerInfo[playerid][pHP] += 1.0;
        SetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);

        GameTextForPlayer(playerid, "~g~+1 HP", 500, 4);
        SetPlayerChatBubble(playerid, "+1 HP", 0x33AA33FF, 13.0, 300);
        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        if(PlayerInfo[playerid][pHP] >= 100.0)
        {
            PlayerInfo[playerid][pHOSPITAL] = 0;
            KillTimer(hospital_timer[playerid]);
            return SCM(playerid, green, "Поздравляем! Вы выписаны из больницы, не болейте!");
        }
    }
    else KillTimer(hospital_timer[playerid]);
    return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
        if(job_car[TEAM_HEAL_CAR][0] <= vehicleid <= job_car[TEAM_HEAL_CAR][1])
        {
            if(PlayerInfo[playerid][pMember] != TEAM_FSB && PlayerInfo[playerid][pMember] != TEAM_HEAL)
            {
                ClearAnimations(playerid, true);
                return SCM(playerid, red, "У вас нет ключей от этого транспорта!");
            }
        }
	}
	#if	defined	hospital__OnPlayerEnterVehicle
		return hospital__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEnterVehicle
	#undef	OnPlayerEnterVehicle
#else
	#define	_ALS_OnPlayerEnterVehicle
#endif

#define	OnPlayerEnterVehicle hospital__OnPlayerEnterVehicle
#if	defined	hospital__OnPlayerEnterVehicle
	forward hospital__OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif