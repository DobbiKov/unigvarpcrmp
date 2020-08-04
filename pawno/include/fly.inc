/*
	About: system fly mode
	Author of the system: Norck
	Author of the modification:	odosenok
*/

#if defined _included_fly
	#endinput
#endif
#define _included_fly

static
	Float:fly_x[MAX_PLAYERS],
	Float:fly_y[MAX_PLAYERS],
	Float:fly_z[MAX_PLAYERS],
	Float:fly_a[MAX_PLAYERS],

	fly_world[MAX_PLAYERS],
	fly_int[MAX_PLAYERS],

	bool:fly_spawn[MAX_PLAYERS],
	fly_state[MAX_PLAYERS],
	fly_object[MAX_PLAYERS],

	fly_last_move[MAX_PLAYERS],
	fly_mode[MAX_PLAYERS],
	fly_last_ud[MAX_PLAYERS],
	fly_last_lr[MAX_PLAYERS],
	Float:fly_accelmul[MAX_PLAYERS];

enum
{
	CAMERA_MODE_NONE	= 0,
	CAMERA_MODE_FLY		= 1,
	CAMERA_MODE_REVERSE	= 2
};
enum
{
	MOVE_FORWARD = 1,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FORWARD_LEFT,
	MOVE_FORWARD_RIGHT,
	MOVE_BACK_LEFT,
	MOVE_BACK_RIGHT
};

const
	Float:MOVE_SPEED = 100.0,
	Float:ACCEL_RATE = 0.03;


public OnPlayerConnect(playerid)
{
	fly_x[playerid] = 0.0;
	fly_y[playerid] = 0.0;
	fly_z[playerid] = 0.0;
	fly_a[playerid] = 0.0;

	fly_world[playerid] = 0;
	fly_int[playerid] = 0;

	fly_state[playerid] = CAMERA_MODE_NONE;

	fly_object[playerid] = -1,

	bool:fly_spawn[playerid] = false;

	fly_last_move[playerid] = 0;
	fly_mode[playerid] = 0;
	fly_last_ud[playerid] = 0;
	fly_last_lr[playerid] = 0;
	fly_accelmul[playerid] = 0.0;

	#if defined _included_fly_OnPlayerConnect
		return _included_fly_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect _included_fly_OnPlayerConnect
#if defined _included_fly_OnPlayerConnect
	forward _included_fly_OnPlayerConnect(playerid);
#endif

stock SetPlayerFlyStatus(playerid, status = 2)
{
	if(status == CAMERA_MODE_FLY && fly_state[playerid] == CAMERA_MODE_FLY)
		return SendClientMessage(playerid, -1, "Fly system already enabled.") & 0;
	else if(status == CAMERA_MODE_NONE && fly_state[playerid] == CAMERA_MODE_NONE)
		return SendClientMessage(playerid, -1, "Fly system already disabled.") & 0;

	switch(status)
	{
		case CAMERA_MODE_NONE:
		{
			CancelEdit(playerid);
			GetPlayerCameraPos(playerid, fly_x[playerid], fly_y[playerid], fly_z[playerid]);
			TogglePlayerSpectating(playerid, false);

			fly_state[playerid] = CAMERA_MODE_NONE;
			fly_spawn[playerid] = true;

			SendClientMessage(playerid, -1, "Fly system disabled.");			
		}
		case CAMERA_MODE_FLY:
		{
			GetPlayerPos(playerid, fly_x[playerid], fly_y[playerid], fly_z[playerid]);
			fly_world[playerid] = GetPlayerVirtualWorld(playerid);
			fly_int[playerid] = GetPlayerInterior(playerid);
			GetPlayerFacingAngle(playerid, fly_a[playerid]);

			fly_object[playerid] = CreatePlayerObject(playerid, 19300, fly_x[playerid], fly_y[playerid], fly_z[playerid], 0.0, 0.0, 0.0);
			TogglePlayerSpectating(playerid, true);

			AttachCameraToPlayerObject(playerid, fly_object[playerid]);

			fly_state[playerid] = CAMERA_MODE_FLY;

			SendClientMessage(playerid, -1, "Fly system enabled.");		
		}
		case CAMERA_MODE_REVERSE:
		{
			if(fly_state[playerid] == CAMERA_MODE_NONE)
				return SetPlayerFlyStatus(playerid, CAMERA_MODE_FLY);
			else
				return SetPlayerFlyStatus(playerid, CAMERA_MODE_NONE);
		}
		default:
			return SendClientMessage(playerid, -1, "Your argument is not valid.") & 0;
	}
	return 1;
}

stock IsPlayerFlying(playerid)
	return fly_state[playerid];
	
public OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid != INVALID_PLAYER_ID)
	{
		if(IsPlayerFlying(playerid))
			SetPlayerFlyStatus(playerid, false);
	}

	#if defined _included_fly_OnPlayerDeath
		return _included_fly_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath _included_fly_OnPlayerDeath
#if defined _included_fly_OnPlayerDeath
	forward _included_fly_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerSpawn(playerid)
{
	if(fly_spawn[playerid] == true)
		SetTimerEx("@OnPlayerSpawnEx", 100, false, "i", playerid);
	
	#if defined _included_fly_OnPlayerSpawn
		return _included_fly_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn _included_fly_OnPlayerSpawn
#if defined _included_fly_OnPlayerSpawn
	forward _included_fly_OnPlayerSpawn(playerid);
#endif

@OnPlayerSpawnEx(playerid);
@OnPlayerSpawnEx(playerid)
{
	SetPlayerPos(playerid, fly_x[playerid], fly_y[playerid], fly_z[playerid]);
	SetPlayerFacingAngle(playerid, fly_a[playerid]);
	SetPlayerVirtualWorld(playerid, fly_world[playerid]);
	SetPlayerInterior(playerid, fly_int[playerid]);

	fly_spawn[playerid] = false;
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(fly_state[playerid] == CAMERA_MODE_FLY)
	{
		new keys, ud, lr;
		GetPlayerKeys(playerid, keys, ud, lr);
		
		if(fly_mode[playerid] && (GetTickCount() - fly_last_move[playerid] > 100))
			MoveCamera(playerid);

		if(fly_last_ud[playerid] != ud || fly_last_lr[playerid] != lr)
		{
			if((fly_last_ud[playerid] != 0 || fly_last_lr[playerid] != 0) && ud == 0 && lr == 0)
			{
				StopPlayerObject(playerid, fly_object[playerid]);
				fly_mode[playerid] = 0;
				fly_accelmul[playerid] = 0.0;
			}
			else
			{

				fly_mode[playerid] = GetMoveDirectionFromKeys(ud, lr);
				MoveCamera(playerid);
			}
		}
		fly_last_ud[playerid] = ud;
		fly_last_lr[playerid] = lr;
		return 0;

	}
	#if defined _included_fly_OnPlayerUpdate
		return _included_fly_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate _included_fly_OnPlayerUpdate
#if defined _included_fly_OnPlayerUpdate
	forward _included_fly_OnPlayerUpdate(playerid);
#endif

stock MoveCamera(playerid)
{
	new
		Float:cam_pos_x, Float:cam_pos_y, Float:cam_pos_z,
		Float:cam_front_x, Float:cam_front_y, Float:cam_front_z;
		
	GetPlayerCameraPos(playerid, cam_pos_x, cam_pos_y, cam_pos_z);
	GetPlayerCameraFrontVector(playerid, cam_front_x, cam_front_y, cam_front_z);

	if(fly_accelmul[playerid] <= 1)
		fly_accelmul[playerid] += ACCEL_RATE;

	new
		Float:speed = MOVE_SPEED * fly_accelmul[playerid],
		Float:x, Float:y, Float:z;
		
	GetNextCameraPosition(fly_mode[playerid], cam_pos_x, cam_pos_y, cam_pos_z, cam_front_x, cam_front_y, cam_front_z, x, y, z);
	MovePlayerObject(playerid, fly_object[playerid], x, y, z, speed);

	fly_last_move[playerid] = GetTickCount();
	return 1;
}

stock GetNextCameraPosition
	(
		move_mode,
		Float:cam_pos_x, Float:cam_pos_y, Float:cam_pos_z,
		Float:cam_front_x, Float:cam_front_y, Float:cam_front_z,
		&Float:x, &Float:y, &Float:z
	)
{
	new const
		Float:change = 6000.0,
		Float:pos_x = cam_front_x * change,
		Float:pos_y = cam_front_y * change,
		Float:pos_z = cam_front_z * change;

	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			x = cam_pos_x + pos_x;
			y = cam_pos_y + pos_y;
			z = cam_pos_z + pos_z;
		}
		case MOVE_BACK:
		{
			x = cam_pos_x - pos_x;
			y = cam_pos_y - pos_y;
			z = cam_pos_z - pos_z;
		}
		case MOVE_LEFT:
		{
			x = cam_pos_x - pos_y;
			y = cam_pos_y + pos_x;
			z = cam_pos_z;
		}
		case MOVE_RIGHT:
		{
			x = cam_pos_x + pos_y;
			y = cam_pos_y - pos_x;
			z = cam_pos_z;
		}
		case MOVE_BACK_LEFT:
		{
			x = cam_pos_x + (-pos_x - pos_y);
 			y = cam_pos_y + (-pos_y + pos_x);
		 	z = cam_pos_z - pos_z;
		}
		case MOVE_BACK_RIGHT:
		{
			x = cam_pos_x + (-pos_x + pos_y);
 			y = cam_pos_y + (-pos_y - pos_x);
		 	z = cam_pos_z - pos_z;
		}
		case MOVE_FORWARD_LEFT:
		{
			x = cam_pos_x + (pos_x  - pos_y);
			y = cam_pos_y + (pos_y  + pos_x);
			z = cam_pos_z + pos_z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			x = cam_pos_x + (pos_x  + pos_y);
			y = cam_pos_y + (pos_y  - pos_x);
			z = cam_pos_z + pos_z;
		}
	}
}
stock GetMoveDirectionFromKeys(ud, lr)
{
	new
		direction = 0;

	if(lr < 0)
	{
		if(ud < 0)
			direction = MOVE_FORWARD_LEFT;
		else if(ud > 0)
			direction = MOVE_BACK_LEFT;
		else
			direction = MOVE_LEFT;
	}
	else if(lr > 0)
	{
		if(ud < 0)
			direction = MOVE_FORWARD_RIGHT;
		else if(ud > 0)
			direction = MOVE_BACK_RIGHT;
		else
			direction = MOVE_RIGHT;
	}
	else if(ud < 0)
		direction = MOVE_FORWARD;
	else if(ud > 0)
		direction = MOVE_BACK;

	return direction;
}