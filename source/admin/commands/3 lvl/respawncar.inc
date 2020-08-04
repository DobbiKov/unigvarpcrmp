CMD:respawncar(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
    extract params -> new id; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Введите /respawncar [ID car]");

	if(!IsValidVehicle(id)) return SCM(playerid, red, "Транспорта под этим ID нет.");

	SetVehicleToRespawn(id);

	new string[128];
	format(string, sizeof(string), "[A] %s[%d] зареспавнил транспорт ID: %d", PlayerInfo[playerid][pName], playerid, id);
	SCMA(grey, string);
	return 1;
}