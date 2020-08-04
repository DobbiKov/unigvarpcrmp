CMD:delveh(playerid,params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
	if(GetPlayerState(playerid) != 2) return SCM(playerid,  red, "¬ы не в автомобиле.");
	if(!TotalAdminVehicles) return 1;
	new vehh = GetPlayerVehicleID(playerid);
	new slot = -1;
	for(new i = 0; i < TotalAdminVehicles; i++)
	{
	    if(vehh == AVehicle[i])
	    {
	    	slot=i;
	    	break;
	    }

	}
	if(slot == -1) return SCM(playerid,  red, "Ётот автомобиль не создавал администратор");
	stringer[0] = EOS;
	format(stringer, 128, "[A] %s удалил автомобиль [model: %d] [vehicleid: %d]", PlayerInfo[playerid][pName],GetVehicleModel(AVehicle[slot]),AVehicle[slot]);
	SCMA(grey, stringer);
	if(IsValidVehicle(AVehicle[slot]))
	{
		DestroyVehicle(AVehicle[slot]);
		vehicle[AVehicle[slot]][veh_limit] = 0.0;
	}
	AVehicle[slot] = 0;
    TotalAdminVehicles--;
	return 1;
}