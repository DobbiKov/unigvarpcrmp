publics PlayerSecondTimer(playerid)
{
    new Float:pos[3]; 
    GetPlayerPos(playerid,pos[0],pos[1],pos[2]); 
    if(pos[0] != 0 && pos[1] != 0 && pos[2] != 0) 
    { 
        if(gettime() > PlayerInfo[playerid][TimeFly]) 
        { 
            new dist = floatround(GetPlayerDistanceFromPoint(playerid, PlayerInfo[playerid][AntiFly][0], PlayerInfo[playerid][AntiFly][1], PlayerInfo[playerid][AntiFly][2])); 
            if(GetPlayerState(playerid) != 2 && GetPlayerState(playerid) == 3 && dist > 4) 
            { 
                if(AntiCheatInfo[AirBreak_AC][acStatus] == 1) ResultCheat(playerid, 10);
                else ResultMessageCheat(playerid, 10);
                return 1; 
            } 
            if(dist > 150) 
            { 
                if(AntiCheatInfo[AirBreak_AC][acStatus] == 1) ResultCheat(playerid, 10);
                else ResultMessageCheat(playerid, 10);
                return 1; 
            } 
            else 
            { 
                if(dist > 14 && GPspeed(playerid) <= 0 && GVspeed(GetPlayerVehicleID(playerid)) <= 0) 
                { 
                    if(AntiCheatInfo[AirBreak_AC][acStatus] == 1) ResultCheat(playerid, 10);
                    else ResultMessageCheat(playerid, 10);
                    return 1; 
                } 
                else GetPlayerPos(playerid,PlayerInfo[playerid][AntiFly][0],PlayerInfo[playerid][AntiFly][1],PlayerInfo[playerid][AntiFly][2]); 
            } 
        } 
    }


    #if defined airbreak__PlayerSecondTimer
        return airbreak__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer airbreak__PlayerSecondTimer
#if	defined	airbreak__PlayerSecondTimer
	forward airbreak__PlayerSecondTimer(playerid); 
#endif

public OnPlayerUpdate(playerid)
{
	{
        new anim = GetPlayerAnimationIndex(playerid); 
        if(PlayerInfo[playerid][pAFK] > 0 || anim == 1130) GetPlayerPos(playerid,PlayerInfo[playerid][AntiFly][0],PlayerInfo[playerid][AntiFly][1],PlayerInfo[playerid][AntiFly][2]);
	}
#if	defined	airbreak__OnPlayerUpdate
	return airbreak__OnPlayerUpdate(playerid);
#else
	return 1;
#endif
}
#if	defined	_ALS_OnPlayerUpdate
	#undef	OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif

#define	OnPlayerUpdate	airbreak__OnPlayerUpdate
#if	defined	airbreak__OnPlayerUpdate
forward airbreak__OnPlayerUpdate(playerid);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{
    GetPlayerPos(playerid, PlayerInfo[playerid][AntiFly][0], PlayerInfo[playerid][AntiFly][1], PlayerInfo[playerid][AntiFly][2]);
    #if	defined	airbreak__OnPlayerExitVehicle
        return airbreak__OnPlayerExitVehicle(playerid, vehicleid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerExitVehicle
	#undef	OnPlayerExitVehicle
#else
	#define	_ALS_OnPlayerExitVehicle
#endif

#define	OnPlayerExitVehicle	airbreak__OnPlayerExitVehicle

#if	defined	airbreak__OnPlayerExitVehicle
forward airbreak__OnPlayerExitVehicle(playerid, vehicleid);
#endif



stock SetPlayerPosEx(playerid,Float:X,Float:Y,Float:Z) 
{ 
    TIMEfly(playerid,2); 
    PlayerInfo[playerid][AntiFly][0] = X; 
    PlayerInfo[playerid][AntiFly][1] = Y; 
    PlayerInfo[playerid][AntiFly][2] = Z; 
    SetPlayerPos(playerid,X,Y,Z); 
    SetCameraBehindPlayer(playerid); 
    return 1; 
} 
#define SetPlayerPos SetPlayerPosEx 

stock TIMEfly(playerid,extra) 
{ 
    PlayerInfo[playerid][TimeFly]=gettime()+extra; 
    return 1; 
}

stock GVspeed(vehicleid) 
{ 
    new Float:ST[3]; 
    GetVehicleVelocity(vehicleid, ST[0], ST[1], ST[2]); 
    return floatround(floatsqroot(ST[0]*ST[0] + ST[1]*ST[1] + ST[2]*ST[2])*100.3); 
} 

stock GPspeed(playerid) 
{ 
    new Float:pos[4]; 
    GetPlayerVelocity(playerid,pos[0],pos[1],pos[2]); 
    pos[3] = floatsqroot(floatpower(floatabs(pos[0]), 2.0) + floatpower(floatabs(pos[1]), 2.0) + floatpower(floatabs(pos[2]), 2.0))*213.3; 
    return floatround(pos[3]); 
}

// new Float:Player_Pos[3][MAX_PLAYERS];
// new Player_Off_Protect[MAX_PLAYERS];

// public OnPlayerConnect(playerid)
// {
//     Player_Off_Protect[playerid] = 9999999;

//     #if	defined	airbreak__OnPlayerConnect
//         return airbreak__OnPlayerConnect(playerid);
//     #else
//         return 1;
//     #endif
// }
// #if	defined	_ALS_OnPlayerConnect
// 	#undef	OnPlayerConnect
// #else
// 	#define	_ALS_OnPlayerConnect
// #endif

// #define	OnPlayerConnect	airbreak__OnPlayerConnect
// #if	defined	airbreak__OnPlayerConnect
//     forward airbreak__OnPlayerConnect(playerid);
// #endif

// publics PlayerSecondTimer(playerid)
// {
//     if(!Player_Off_Protect[playerid])
//     {
//         new Float:Distance = GetPlayerDistanceFromPoint(playerid, Player_Pos[0][playerid], Player_Pos[1][playerid], Player_Pos[2][playerid]);
//         if(10.0 < Distance < 40.0)
//         {
//             if(!IsPlayerInAnyVehicle(playerid))
//             {
//                 if(AntiCheatInfo[AirBreak_AC][acStatus] == 0) ResultCheat(playerid, 10);
//                 else ResultMessageCheat(playerid, 10);
//             }
//         }
//         else if(40 < Distance)
//         {
//             if(AntiCheatInfo[AirBreak_AC][acStatus] == 0) ResultCheat(playerid, 10);
//             else ResultMessageCheat(playerid, 10);
//         }
//         GetPlayerPos(playerid, Player_Pos[0][playerid], Player_Pos[1][playerid], Player_Pos[2][playerid]);
//     }


//     #if defined airbreak__PlayerSecondTimer
//         return airbreak__PlayerSecondTimer(playerid);
//     #else
//         return 1;
//     #endif
// }
// #if	defined	_ALS_PlayerSecondTimer
// 	#undef	PlayerSecondTimer
// #else
// 	#define	_ALS_PlayerSecondTimer
// #endif

// #define	PlayerSecondTimer airbreak__PlayerSecondTimer
// #if	defined	airbreak__PlayerSecondTimer
// 	forward airbreak__PlayerSecondTimer(playerid); 
// #endif

// public OnPlayerSpawn(playerid)
// {
//     Player_Off_Protect[playerid] = 2; 
//     #if	defined	airbreak__OnPlayerSpawn
//         return airbreak__OnPlayerSpawn(playerid);
//     #else
//         return 1;
//     #endif
// }
// #if	defined	_ALS_OnPlayerSpawn
// 	#undef	OnPlayerSpawn
// #else
// 	#define	_ALS_OnPlayerSpawn
// #endif

// #define	OnPlayerSpawn	airbreak__OnPlayerSpawn
// #if	defined	airbreak__OnPlayerSpawn
// forward airbreak__OnPlayerSpawn(playerid);
// #endif

// public OnPlayerExitVehicle(playerid, vehicleid)
// {
//     GetPlayerPos(playerid, Player_Pos[0][playerid], Player_Pos[1][playerid], Player_Pos[2][playerid]); 
//     #if	defined	airbreak__OnPlayerExitVehicle
//         return airbreak__OnPlayerExitVehicle(playerid, vehicleid);
//     #else
//         return 1;
//     #endif
// }
// #if	defined	_ALS_OnPlayerExitVehicle
// 	#undef	OnPlayerExitVehicle
// #else
// 	#define	_ALS_OnPlayerExitVehicle
// #endif

// #define	OnPlayerExitVehicle	airbreak__OnPlayerExitVehicle

// #if	defined	airbreak__OnPlayerExitVehicle
// forward airbreak__OnPlayerExitVehicle(playerid, vehicleid);
// #endif



// stock WAC_SetPlayerPos(playerid, Float:x,Float:y,Float:z)
// {
//     Player_Pos[0][playerid] = x;
//     Player_Pos[1][playerid] = y;
//     Player_Pos[2][playerid] = z;

//     SetPlayerPos(playerid, x,y,z);

//     Player_Off_Protect[playerid] = 2;
//     //if(!IsPlayerInRangeOfPoint(playerid, 10.0, x,y,z)) return Kick(playerid); // NOP

//     return 1;
// } 
// #if	defined	_ALS_SetPlayerPos
// 	#undef	SetPlayerPos
// #else
// 	#define	_ALS_SetPlayerPos
// #endif

// #define SetPlayerPos WAC_SetPlayerPos