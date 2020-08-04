CMD:veh(playerid,params[])
{
	if(PlayerInfo[playerid][bAdmin] < 4 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
	if(sscanf(params,"ddd",params[0],params[1],params[2])) return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: Используйте /veh [carid] [цвет1] [цвет2]");
	if(params[0] < 400 || params[0] > 611) return SCM(playerid,  red, "Номер машины не может быть меньше 400 и больше чем 611!");
	if(params[1] < 0 || params[1] > 126) return SCM(playerid,  red, "Номер цвета не может быть меньше 0 и больше 126!");
	if(params[2] < 0 || params[2] > 126) return SCM(playerid,  red, "Номер цвета не может быть меньше 0 и больше 126!");
	if(TotalAdminVehicles > 50)
	{
	   SCM(playerid,  red, "Лимит админ-машин превышен");
	   return 1;
	}
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);

	AVehicle[TotalAdminVehicles] = CreateVehicle(params[0], X+5,Y+5,Z, 0.0, params[1], params[2], -1);

	LinkVehicleToInterior(AVehicle[TotalAdminVehicles], GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(AVehicle[TotalAdminVehicles],GetPlayerVirtualWorld(playerid));
	vehicle[AVehicle[TotalAdminVehicles]][veh_fuel] = 80.0;
	vehicle[AVehicle[TotalAdminVehicles]][veh_limit] = 0.0;
    stringer[0] = EOS;
	format(stringer, 128, "[A] %s[%d] создал автомобиль [model: %d] [vehicleid: %d]", PlayerInfo[playerid][pName],playerid,params[0],AVehicle[TotalAdminVehicles]);
	SCMA(grey, stringer);
	TotalAdminVehicles ++;
	return 1;
}