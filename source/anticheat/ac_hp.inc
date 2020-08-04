static Float:ac_hp__health[MAX_PLAYERS];
static ac_hp__ignore_tick[MAX_PLAYERS];

#if	!defined	AC_HP__IGNORE_TIME
	#define	AC_HP__IGNORE_TIME	1300
#endif


public OnPlayerUpdate(playerid)
{
	{
		new Float:health;
		GetPlayerHealth(playerid, health);
		if(_:ac_hp__health[playerid] != _:health)
		{
			if((ac_hp__health[playerid] > health) && (GetTickCount() > ac_hp__ignore_tick[playerid]))
			{
				ac_hp__health[playerid] = health;
			}
			else if(ac_hp__health[playerid] < health && GetTickCount() > ac_hp__ignore_tick[playerid])
			{
				SetPlayerHealth(playerid, ac_hp__health[playerid]);
				ResultMessageCheat(playerid, 8);
			}
		}
	}
#if	defined	ac_hp__OnPlayerUpdate
	return ac_hp__OnPlayerUpdate(playerid);
#else
	return 1;
#endif
}
#if	defined	_ALS_OnPlayerUpdate
	#undef	OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif
#define	OnPlayerUpdate	ac_hp__OnPlayerUpdate
#if	defined	ac_hp__OnPlayerUpdate
forward ac_hp__OnPlayerUpdate(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = 100.0;
#if	defined	ac_hp__OnPlayerSpawn
	ac_hp__OnPlayerSpawn(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerSpawn
	#undef	OnPlayerSpawn
#else
	#define	_ALS_OnPlayerSpawn
#endif
#define	OnPlayerSpawn	ac_hp__OnPlayerSpawn
#if	defined	ac_hp__OnPlayerSpawn
forward ac_hp__OnPlayerSpawn(playerid);
#endif


stock ac_hp__SetPlayerHealth(playerid, Float:health)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = health;
	return SetPlayerHealth(playerid, health);
}
#if	defined	_ALS_SetPlayerHealth
	#undef	SetPlayerHealth
#else
	#define	_ALS_SetPlayerHealth
#endif
#define SetPlayerHealth ac_hp__SetPlayerHealth

stock ac_hp__GetPlayerHealth(playerid, &Float:health)
{
	health = ac_hp__health[playerid];
	return 1;
}
#if	defined	_ALS_GetPlayerHealth
	#undef	GetPlayerHealth
#else
	#define	_ALS_GetPlayerHealth
#endif
#define GetPlayerHealth ac_hp__GetPlayerHealth