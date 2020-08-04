CMD:gotocar(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new vehid; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Введите - /gotocar [ID автомобиля]");
	new Float:x, Float:y, Float:z;

	if(!IsValidVehicle(vehid)) return SCM(playerid, red, "Такого транспорта не существует.");

	GetVehiclePos(vehid, x, y, z);
	SetPlayerPos(playerid, x+3, y+3, z);
	return 1;
}