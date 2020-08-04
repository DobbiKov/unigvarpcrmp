CMD:setfuel(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "Вы должны находится в автомобиле!");

    extract params -> new fuel; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /setfuel [кол-во бензина]");
    if(fuel > 100 || fuel < 0) return SCM(playerid, red, "Не больше 100 и не меньше 0!");

    stringer[0] = EOS;
	format(stringer, 128, "[A] %s [%d] заправил автомобиль на %d л. [vehicleid: %d]", PlayerInfo[playerid][pName], playerid, fuel, GetPlayerVehicleID(playerid));
	SCMA(grey, stringer);

	format(stringer, sizeof(stringer), "Вы заправили автомобиль на %d л. (vehicledid: %d)", fuel, GetPlayerVehicleID(playerid));
	SCM(playerid, white, stringer);
    vehicle[ GetPlayerVehicleID(playerid) ][veh_fuel] = float(fuel);
	return 1;
}