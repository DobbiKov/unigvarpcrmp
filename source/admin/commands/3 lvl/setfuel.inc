CMD:setfuel(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "�� ������ ��������� � ����������!");

    extract params -> new fuel; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /setfuel [���-�� �������]");
    if(fuel > 100 || fuel < 0) return SCM(playerid, red, "�� ������ 100 � �� ������ 0!");

    stringer[0] = EOS;
	format(stringer, 128, "[A] %s [%d] �������� ���������� �� %d �. [vehicleid: %d]", PlayerInfo[playerid][pName], playerid, fuel, GetPlayerVehicleID(playerid));
	SCMA(grey, stringer);

	format(stringer, sizeof(stringer), "�� ��������� ���������� �� %d �. (vehicledid: %d)", fuel, GetPlayerVehicleID(playerid));
	SCM(playerid, white, stringer);
    vehicle[ GetPlayerVehicleID(playerid) ][veh_fuel] = float(fuel);
	return 1;
}