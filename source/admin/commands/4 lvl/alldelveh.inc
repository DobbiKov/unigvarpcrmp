CMD:alldelveh(playerid,params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);
    stringer[0] = EOS;
	format(stringer, 128, "[A] %s[%d] удалил все автомобили созданные администраторами", PlayerInfo[playerid][pName], playerid);
	SCMA(grey, stringer);
	for(new i = 0; i < TotalAdminVehicles; i++)
	{
	    if(IsValidVehicle(AVehicle[i]))
	    {
			DestroyVehicle(AVehicle[i]);
			vehicle[AVehicle[i]][veh_limit] = 0.0;
		}
		AVehicle[i] = 0;
	}
	TotalAdminVehicles=0;
	return 1;
}