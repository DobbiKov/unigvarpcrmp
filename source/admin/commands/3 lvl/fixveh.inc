CMD:fixveh(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
	if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "¬ы должны находитс€ в автомобиле!");

    stringer[0] = EOS;
	format(stringer, 128, "[A] %s [%d] отремонтировал автомобиль [vehicleid: %d]", PlayerInfo[playerid][pName],playerid, GetPlayerVehicleID(playerid));
	SCMA(grey, stringer);

	format(stringer, sizeof(stringer), "¬ы отремонтировали автомобиль (vehicleid: %d)", GetPlayerVehicleID(playerid));
	SCM(playerid, white, stringer);
	return RepairVehicle(GetPlayerVehicleID(playerid));
}