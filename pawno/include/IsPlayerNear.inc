#if defined _IsPlayerNear_included
    #endinput
#endif
#define _IsPlayerNear_included
#include <a_samp>
#include <foreach>
/*============================================================================*\
================================================================================
====================|			  IsPlayerNear* v1.1		|===================
====================|			Created by: White_116		|===================
================================================================================
================================================================================
					Return INVALID_VEHICLE_ID or vehicleid;
================================================================================
native GetVehicleIfPlayerNearVehicle(playerid, Float:Range=15.0, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearBoot(playerid, Float:Range=1.5, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearBonnet(playerid, Float:Range=1.5, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearPetrolCap(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearDoor(playerid, door, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearDoor0(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearDoor1(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearDoor2(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearDoor3(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearWheel(playerid, wheel, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearWheel0(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearWheel1(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearWheel2(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
native GetVehicleIfPlayerNearWheel3(playerid, Float:Range=0.75, Float:MaxAngle=30.0);
================================================================================
================================================================================
							Return 0 or 1 & x,y,z
================================================================================
native GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehiclePetrolCapPos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleDoorPos(vehicleid, door, &Float:x, &Float:y, &Float:z);
native GetVehicleDoor0Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleDoor1Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleDoor2Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleDoor3Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleWheelPos(vehicleid, wheel, &Float:x, &Float:y, &Float:z);
native GetVehicleWheel0Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleWheel1Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleWheel2Pos(vehicleid, &Float:x, &Float:y, &Float:z);
native GetVehicleWheel3Pos(vehicleid, &Float:x, &Float:y, &Float:z);
================================================================================
================================================================================
								Return 0 or 1;
================================================================================
native IsPlayerNearVehicle(playerid, vehicleid, Float:Range=15.0, Float:MaxAngle=30.0);
native IsPlayerNearVehicleBoot(playerid, vehicleid, Float:Range=1.5, Float:MaxAngle=30.0);
native IsPlayerNearVehicleBonnet(playerid, vehicleid, Float:Range=1.5, Float:MaxAngle=30.0);
native IsPlayerNearVehiclePetrolCap(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleDoor(playerid, vehicleid, door, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleDoor0(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleDoor1(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleDoor2(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleDoor3(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleWheel(playerid, vehicleid, wheel, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleWheel0(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleWheel1(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleWheel2(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
native IsPlayerNearVehicleWheel3(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0);
================================================================================
\*============================================================================*/
stock Float:GetAngleBetwen2Angles(Float:d, Float:a)
{
	if(floatcmp(d, a) >= 0) d=floatsub(d,a); else d=floatsub(a,d);
	return (floatcmp(d, 180.0) > 0 ? floatabs(floatsub(360.0,d)) : d);
}
/*============================================================================*\
================================================================================
\*============================================================================*/
new Float:VehicleSizeY[212];
new Float:VehicleSizeYD[212];
new Float:VehicleDoorFA[212];
new Float:VehicleDoorFD[212];
new Float:VehicleDoorRA[212];
new Float:VehicleDoorRD[212];

new Float:VehicleWheelFA[212];
new Float:VehicleWheelFD[212];
new Float:VehicleWheelRA[212];
new Float:VehicleWheelRD[212];
new Float:VehiclePetrolCapA[212];
new Float:VehiclePetrolCapD[212];
new Iterator:VehicleStreamFor[MAX_PLAYERS]<MAX_VEHICLES>;
new W_MaxPassengers[212 char]={50397441, 50528257, 16974081, 16974081, 50397953,
50528513, 16777987, 50397192,65807, 17302273, 50331905, 16973825, 69377, 1, 16843523,
16843009, 16843523,16843521, 257, 65795, 16777985,3, 16843521, 50331905, 16974593,
16843009,16843011,16777217, 257, 50397440, 65793, 16843009, 16973824, 65793, 16843008,
50397441,16843523, 16843523, 16777473, 16843009, 50528513, 66307, 983296, 65537, 16843011,
50397952, 251855105, 16846607, 16843008, 50529025, 16843009, 50401039, 251858703};
new W_BootSideDoor[212 char]={0xFFFFFFFF,...};


new W_HasC,W_HasSO,W_HasSI;
#if defined FILTERSCRIPT
public OnFilterScriptInit()
{
    W_HasC=funcidx("W_OnPlayerConnect") != -1;
    W_HasSO=funcidx("W_OnVehicleStreamOut") != -1;
    W_HasSI=funcidx("W_OnVehicleStreamIn") != -1;

	W_BootSideDoor{209}=0;
	W_BootSideDoor{182}=0;
	W_BootSideDoor{98}=0;
	W_BootSideDoor{82}=0;
	W_BootSideDoor{59}=0;
	W_BootSideDoor{40}=0;
	W_BootSideDoor{28}=0;
	W_BootSideDoor{16}=0;
	W_BootSideDoor{27}=0;
	W_BootSideDoor{13}=0;
	
	Iter_Init(VehicleStreamFor);
	for(new Float:x,Float:y,Float:z, id; id < 212; id++)
	{
	    GetVehicleModelInfo(id+400, 1, x, y, z);
	    VehicleSizeY[id]=0.25+(y/2.0);
	    VehicleSizeYD[id]=3.0+(y/2.0);

	    GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_PETROLCAP, x, y, z);
	    x+=0.25;
		VehiclePetrolCapD[id]=floatsqroot((x*x)+(y*y));
		VehiclePetrolCapA[id]=atan2(x, y);

		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_FRONTSEAT, x, y, z);
  		x+=1.0;
		VehicleDoorFD[id]=floatsqroot((x*x)+(y*y));
		VehicleDoorFA[id]=atan2(x, y);

		if(W_BootSideDoor{id})
		{
			GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_REARSEAT, x, y, z);
	  		x+=1.0;
			VehicleDoorRD[id]=floatsqroot((x*x)+(y*y));
			VehicleDoorRA[id]=atan2(x, y);
		}
		else
		{
			GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_REARSEAT, x, y, z);
	  		y=-VehicleSizeY[id];
	  		x-=0.15;
			VehicleDoorRD[id]=floatsqroot((x*x)+(y*y));
			VehicleDoorRA[id]=atan2(x, y);
		}
		
		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_WHEELSFRONT, x, y, z);
  		x+=0.25;
		VehicleWheelFD[id]=floatsqroot((x*x)+(y*y));
		VehicleWheelFA[id]=atan2(x, y);

		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_WHEELSREAR, x, y, z);
  		x+=0.25;
		VehicleWheelRD[id]=floatsqroot((x*x)+(y*y));
		VehicleWheelRA[id]=atan2(x, y);
    }
   	if(funcidx("W_OnFilterScriptInit") != -1)
    {
        return CallLocalFunction("W_OnFilterScriptInit", "");
    }
    return 1;
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit W_OnFilterScriptInit
forward W_OnFilterScriptInit();
#else /*not a filterscript*/
public OnGameModeInit()
{
    W_HasC=funcidx("W_OnPlayerConnect") != -1;
    W_HasSO=funcidx("W_OnVehicleStreamOut") != -1;
    W_HasSI=funcidx("W_OnVehicleStreamIn") != -1;
    
   	W_BootSideDoor{209}=0;
	W_BootSideDoor{182}=0;
	W_BootSideDoor{98}=0;
	W_BootSideDoor{82}=0;
	W_BootSideDoor{59}=0;
	W_BootSideDoor{40}=0;
	W_BootSideDoor{28}=0;
	W_BootSideDoor{16}=0;
	W_BootSideDoor{27}=0;
	W_BootSideDoor{13}=0;
	
	Iter_Init(VehicleStreamFor);
	for(new Float:x,Float:y,Float:z, id; id < 212; id++)
	{
	    GetVehicleModelInfo(id+400, 1, x, y, z);
	    VehicleSizeY[id]=0.25+(y/2.0);
	    VehicleSizeYD[id]=3.0+(y/2.0);

	    GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_PETROLCAP, x, y, z);
	    x+=0.25;
		VehiclePetrolCapD[id]=floatsqroot((x*x)+(y*y));
		VehiclePetrolCapA[id]=atan2(x, y);

		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_FRONTSEAT, x, y, z);
  		x+=1.0;
		VehicleDoorFD[id]=floatsqroot((x*x)+(y*y));
		VehicleDoorFA[id]=atan2(x, y);

		if(W_BootSideDoor{id})
		{
			GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_REARSEAT, x, y, z);
	  		x+=1.0;
			VehicleDoorRD[id]=floatsqroot((x*x)+(y*y));
			VehicleDoorRA[id]=atan2(x, y);
		}
		else
		{
			GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_REARSEAT, x, y, z);
	  		y=-VehicleSizeY[id];
	  		x-=0.15;
			VehicleDoorRD[id]=floatsqroot((x*x)+(y*y));
			VehicleDoorRA[id]=atan2(x, y);
		}
		
		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_WHEELSFRONT, x, y, z);
  		x+=0.25;
		VehicleWheelFD[id]=floatsqroot((x*x)+(y*y));
		VehicleWheelFA[id]=atan2(x, y);

		GetVehicleModelInfo(id+400, VEHICLE_MODEL_INFO_WHEELSREAR, x, y, z);
  		x+=0.25;
		VehicleWheelRD[id]=floatsqroot((x*x)+(y*y));
		VehicleWheelRA[id]=atan2(x, y);
    }
	if(funcidx("W_OnGameModeInit") != -1)
    {
        return CallLocalFunction("W_OnGameModeInit", "");
    }
    return 1;
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit W_OnGameModeInit
forward W_OnGameModeInit();
#endif /*if defined FILTERSCRIPT*/
//------------------------------------------------------------------------------
public OnPlayerConnect(playerid)
{
    Iter_Clear(VehicleStreamFor[playerid]);
    if(W_HasC)return CallLocalFunction("W_OnPlayerConnect", "i",playerid);
	return 1;
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect W_OnPlayerConnect
forward W_OnPlayerConnect(playerid);
//------------------------------------------------------------------------------
public OnVehicleStreamIn(vehicleid, forplayerid)
{
	if(IsPlayerNPC(forplayerid)) return 1;
	Iter_Add(VehicleStreamFor[forplayerid],vehicleid);
 	if(W_HasSI)return CallLocalFunction("W_OnVehicleStreamIn", "ii", vehicleid, forplayerid);
	return 1;
	
}
#if defined _ALS_OnVehicleStreamIn
    #undef OnVehicleStreamIn
#else
    #define _ALS_OnVehicleStreamIn
#endif
#define OnVehicleStreamIn W_OnVehicleStreamIn
forward W_OnVehicleStreamIn(vehicleid, forplayerid);
//------------------------------------------------------------------------------
public OnVehicleStreamOut(vehicleid, forplayerid)
{
    if(IsPlayerNPC(forplayerid)) return 1;
	Iter_Remove(VehicleStreamFor[forplayerid], vehicleid);
	if(W_HasSO)return CallLocalFunction("W_OnVehicleStreamOut", "ii", vehicleid, forplayerid);
	return 1;
}
#if defined _ALS_OnVehicleStreamOut
    #undef OnVehicleStreamOut
#else
    #define _ALS_OnVehicleStreamOut
#endif
#define OnVehicleStreamOut W_OnVehicleStreamOut
forward W_OnVehicleStreamOut(vehicleid, forplayerid);
//------------------------------------------------------------------------------
stock GetVehicleIfPlayerNearVehicle(playerid, Float:Range=15.0, Float:MaxAngle=30.0)
{
    new Float:x,Float:y,Float:z,Float:a,Float:d, Float:rx,Float:ry,Float:rz;
    foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if(!IsValidVehicle(vehicleid))continue;
		GetVehiclePos(vehicleid, x, y, z);
		if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
		{
		    if(MaxAngle>=180.0)return vehicleid;
			GetPlayerFacingAngle(playerid, d);
		    GetPlayerPos(playerid, rx, ry, rz);
		    if((a=atan2(x-rx,y-ry)) < 0)a*=-1;else a=360-a;
			if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
		}
	}
	return 0;
}

stock GetVehicleIfPlayerNearBoot(playerid, Float:Range=1.5, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d);
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
	        x+=(VehicleSizeY[m] * floatsin(a, degrees));
	    	y-=(VehicleSizeY[m] * floatcos(a, degrees));
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearBonnet(playerid, Float:Range=1.5, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=180.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
	        x-=(VehicleSizeY[m] * floatsin(a, degrees));
	    	y+=(VehicleSizeY[m] * floatcos(a, degrees));
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearPetrolCap(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d);
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehiclePetrolCapD[m]*floatsin(VehiclePetrolCapA[m]-a,degrees);
			y+=VehiclePetrolCapD[m]*floatcos(VehiclePetrolCapA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(VehiclePetrolCapA[m] >= 0.0)x=d+270.0; else x=d+90.0;
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(x, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearDoor(playerid, door, Float:Range=0.75, Float:MaxAngle=30.0)
{
	switch(door)
	{
		case 0: return GetVehicleIfPlayerNearDoor0(playerid, Range, MaxAngle);
		case 1: return GetVehicleIfPlayerNearDoor1(playerid, Range, MaxAngle);
		case 2: return GetVehicleIfPlayerNearDoor2(playerid, Range, MaxAngle);
		case 3: return GetVehicleIfPlayerNearDoor3(playerid, Range, MaxAngle);
	}
    return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearDoor0(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=90.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleDoorFD[m]*floatsin(-VehicleDoorFA[m]-a,degrees);
			y+=VehicleDoorFD[m]*floatcos(-VehicleDoorFA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearDoor1(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=270.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
		if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
	    if(W_MaxPassengers{m} < 1)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleDoorFD[m]*floatsin(VehicleDoorFA[m]-a,degrees);
			y+=VehicleDoorFD[m]*floatcos(VehicleDoorFA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearDoor2(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); 
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
	    if(W_MaxPassengers{m} < 2)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleDoorRD[m]*floatsin(-VehicleDoorRA[m]-a,degrees);
			y+=VehicleDoorRD[m]*floatcos(-VehicleDoorRA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
			    if(W_BootSideDoor{m})x=d+90.0;
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(x, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearDoor3(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d);
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
	    if(W_MaxPassengers{m} < 3)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleDoorRD[m]*floatsin(VehicleDoorRA[m]-a,degrees);
			y+=VehicleDoorRD[m]*floatcos(VehicleDoorRA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
			    if(W_BootSideDoor{m})x=d+270.0;
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(x, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}


stock GetVehicleIfPlayerNearWheel(playerid, wheel, Float:Range=0.75, Float:MaxAngle=30.0)
{
	switch(wheel)
	{
		case 0: return GetVehicleIfPlayerNearWheel0(playerid, Range, MaxAngle);
		case 1: return GetVehicleIfPlayerNearWheel1(playerid, Range, MaxAngle);
		case 2: return GetVehicleIfPlayerNearWheel2(playerid, Range, MaxAngle);
		case 3: return GetVehicleIfPlayerNearWheel3(playerid, Range, MaxAngle);
	}
    return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearWheel0(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=90.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleWheelFD[m]*floatsin(-VehicleWheelFA[m]-a,degrees);
			y+=VehicleWheelFD[m]*floatcos(-VehicleWheelFA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearWheel1(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=270.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
		if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleWheelFD[m]*floatsin(VehicleWheelFA[m]-a,degrees);
			y+=VehicleWheelFD[m]*floatcos(VehicleWheelFA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearWheel2(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=90.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleWheelRD[m]*floatsin(-VehicleWheelRA[m]-a,degrees);
			y+=VehicleWheelRD[m]*floatcos(-VehicleWheelRA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleIfPlayerNearWheel3(playerid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    GetPlayerFacingAngle(playerid, d); d+=270.0;
	foreach(new vehicleid : VehicleStreamFor[playerid])
	{
	    if((m=GetVehicleModel(vehicleid)-400) < 0)continue;
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid,VehicleSizeYD[m],x,y,z))
        {
            GetVehicleZAngle(vehicleid, a);
			x+=VehicleWheelRD[m]*floatsin(VehicleWheelRA[m]-a,degrees);
			y+=VehicleWheelRD[m]*floatcos(VehicleWheelRA[m]-a,degrees);
			if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
			{
				if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return vehicleid;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
stock GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
    x+=(VehicleSizeY[m] * floatsin(a, degrees));
	y-=(VehicleSizeY[m] * floatcos(a, degrees));
    return 1;
}

stock GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
    x-=(VehicleSizeY[m] * floatsin(a, degrees));
	y+=(VehicleSizeY[m] * floatcos(a, degrees));
    return 1;
}

stock GetVehiclePetrolCapPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehiclePetrolCapD[m]*floatsin(VehiclePetrolCapA[m]-a,degrees);
	y+=VehiclePetrolCapD[m]*floatcos(VehiclePetrolCapA[m]-a,degrees);
    return 1;
}

stock GetVehicleDoorPos(vehicleid, door, &Float:x, &Float:y, &Float:z)
{
	switch(door)
	{
		case 0: return GetVehicleDoor0Pos(vehicleid, x, y, z);
		case 1: return GetVehicleDoor1Pos(vehicleid, x, y, z);
		case 2: return GetVehicleDoor2Pos(vehicleid, x, y, z);
		case 3: return GetVehicleDoor3Pos(vehicleid, x, y, z);
	}
    return 0;
}

stock GetVehicleDoor0Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleDoorFD[m]*floatsin(-VehicleDoorFA[m]-a,degrees);
	y+=VehicleDoorFD[m]*floatcos(-VehicleDoorFA[m]-a,degrees);
    return 1;
}

stock GetVehicleDoor1Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleDoorFD[m]*floatsin(VehicleDoorFA[m]-a,degrees);
	y+=VehicleDoorFD[m]*floatcos(VehicleDoorFA[m]-a,degrees);
    return 1;
}

stock GetVehicleDoor2Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleDoorRD[m]*floatsin(-VehicleDoorRA[m]-a,degrees);
	y+=VehicleDoorRD[m]*floatcos(-VehicleDoorRA[m]-a,degrees);
    return 1;
}

stock GetVehicleDoor3Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleDoorRD[m]*floatsin(VehicleDoorRA[m]-a,degrees);
	y+=VehicleDoorRD[m]*floatcos(VehicleDoorRA[m]-a,degrees);
    return 1;
}

stock GetVehicleWheelPos(vehicleid, wheel, &Float:x, &Float:y, &Float:z)
{
	switch(wheel)
	{
		case 0: return GetVehicleWheel0Pos(vehicleid, x, y, z);
		case 1: return GetVehicleWheel1Pos(vehicleid, x, y, z);
		case 2: return GetVehicleWheel2Pos(vehicleid, x, y, z);
		case 3: return GetVehicleWheel3Pos(vehicleid, x, y, z);
	}
    return 0;
}

stock GetVehicleWheel0Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleWheelFD[m]*floatsin(-VehicleWheelFA[m]-a,degrees);
	y+=VehicleWheelFD[m]*floatcos(-VehicleWheelFA[m]-a,degrees);
    return 1;
}

stock GetVehicleWheel1Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleWheelFD[m]*floatsin(VehicleWheelFA[m]-a,degrees);
	y+=VehicleWheelFD[m]*floatcos(VehicleWheelFA[m]-a,degrees);
    return 1;
}

stock GetVehicleWheel2Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleWheelRD[m]*floatsin(-VehicleWheelRA[m]-a,degrees);
	y+=VehicleWheelRD[m]*floatcos(-VehicleWheelRA[m]-a,degrees);
    return 1;
}

stock GetVehicleWheel3Pos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new m=GetVehicleModel(vehicleid)-400;if(m<0)return 0;
    new Float:a;
    GetVehicleZAngle(vehicleid, a);
    GetVehiclePos(vehicleid, x, y, z);
	x+=VehicleWheelRD[m]*floatsin(VehicleWheelRA[m]-a,degrees);
	y+=VehicleWheelRD[m]*floatcos(VehicleWheelRA[m]-a,degrees);
    return 1;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
stock IsPlayerNearVehicle(playerid, vehicleid, Float:Range=15.0, Float:MaxAngle=30.0)
{
    new  Float:x,Float:y,Float:z,Float:a,Float:d, Float:rx,Float:ry,Float:rz;
    if(!IsValidVehicle(vehicleid))return 0;
	GetVehiclePos(vehicleid, x, y, z);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
	    if(MaxAngle>=180.0)return vehicleid;
		GetPlayerFacingAngle(playerid, d);
	    GetPlayerPos(playerid, rx, ry, rz);
	    if((a=atan2(x-rx,y-ry)) < 0)a*=-1;else a=360-a;
     	if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleBoot(playerid, vehicleid, Float:Range=1.5, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d);
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
    x+=(VehicleSizeY[m] * floatsin(a, degrees));
	y-=(VehicleSizeY[m] * floatcos(a, degrees));
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleBonnet(playerid, vehicleid, Float:Range=1.5, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d); d+=180.0;
	GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
    x-=(VehicleSizeY[m] * floatsin(a, degrees));
	y+=(VehicleSizeY[m] * floatcos(a, degrees));
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehiclePetrolCap(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d);
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehiclePetrolCapD[m]*floatsin(VehiclePetrolCapA[m]-a,degrees);
	y+=VehiclePetrolCapD[m]*floatcos(VehiclePetrolCapA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(VehiclePetrolCapA[m] >= 0.0)d+=270.0; else d+=90.0;
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleDoor(playerid, vehicleid, door, Float:Range=0.75, Float:MaxAngle=30.0)
{
	switch(door)
	{
		case 0: return IsPlayerNearVehicleDoor0(playerid, vehicleid, Range, MaxAngle);
		case 1: return IsPlayerNearVehicleDoor1(playerid, vehicleid, Range, MaxAngle);
		case 2: return IsPlayerNearVehicleDoor2(playerid, vehicleid, Range, MaxAngle);
		case 3: return IsPlayerNearVehicleDoor3(playerid, vehicleid, Range, MaxAngle);
	}
    return 0;
}

stock IsPlayerNearVehicleDoor0(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d);d+=90.0;
    GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);
	x+=VehicleDoorFD[m]*floatsin(-VehicleDoorFA[m]-a,degrees);
	y+=VehicleDoorFD[m]*floatcos(-VehicleDoorFA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleDoor1(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
	if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    if(W_MaxPassengers{m} < 1)return 0;
    GetPlayerFacingAngle(playerid, d);d+=270.0;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleDoorFD[m]*floatsin(VehicleDoorFA[m]-a,degrees);
	y+=VehicleDoorFD[m]*floatcos(VehicleDoorFA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleDoor2(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    if(W_MaxPassengers{m} < 2)return 0;
    GetPlayerFacingAngle(playerid, d);
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleDoorRD[m]*floatsin(-VehicleDoorRA[m]-a,degrees);
	y+=VehicleDoorRD[m]*floatcos(-VehicleDoorRA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
	    if(W_BootSideDoor{m})d+=90.0;
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleDoor3(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    if(W_MaxPassengers{m} < 3)return 0;
    GetPlayerFacingAngle(playerid, d); 
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleDoorRD[m]*floatsin(VehicleDoorRA[m]-a,degrees);
	y+=VehicleDoorRD[m]*floatcos(VehicleDoorRA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
	    if(W_BootSideDoor{m})d+=270.0;
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleWheel(playerid, vehicleid, wheel, Float:Range=0.75, Float:MaxAngle=30.0)
{
	switch(wheel)
	{
		case 0: return IsPlayerNearVehicleWheel0(playerid, vehicleid, Range, MaxAngle);
		case 1: return IsPlayerNearVehicleWheel1(playerid, vehicleid, Range, MaxAngle);
		case 2: return IsPlayerNearVehicleWheel2(playerid, vehicleid, Range, MaxAngle);
		case 3: return IsPlayerNearVehicleWheel3(playerid, vehicleid, Range, MaxAngle);
	}
    return 0;
}

stock IsPlayerNearVehicleWheel0(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d); d+=90.0;
    GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);
	x+=VehicleWheelFD[m]*floatsin(-VehicleWheelFA[m]-a,degrees);
	y+=VehicleWheelFD[m]*floatcos(-VehicleWheelFA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleWheel1(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
	if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d); d+=270.0;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleWheelFD[m]*floatsin(VehicleWheelFA[m]-a,degrees);
	y+=VehicleWheelFD[m]*floatcos(VehicleWheelFA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
		if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleWheel2(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d); d+=90.0;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleWheelRD[m]*floatsin(-VehicleWheelRA[m]-a,degrees);
	y+=VehicleWheelRD[m]*floatcos(-VehicleWheelRA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
	    if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}

stock IsPlayerNearVehicleWheel3(playerid, vehicleid, Float:Range=0.75, Float:MaxAngle=30.0)
{
    new m, Float:x,Float:y,Float:z,Float:a,Float:d;
    if((m=GetVehicleModel(vehicleid)-400) < 0)return 0;
    GetPlayerFacingAngle(playerid, d); d+=270.0;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);
	x+=VehicleWheelRD[m]*floatsin(VehicleWheelRA[m]-a,degrees);
	y+=VehicleWheelRD[m]*floatcos(VehicleWheelRA[m]-a,degrees);
	if(IsPlayerInRangeOfPoint(playerid, Range, x, y, z))
	{
	    if(floatcmp(MaxAngle, GetAngleBetwen2Angles(d, a)) == 1)return 1;
	}
	return 0;
}
