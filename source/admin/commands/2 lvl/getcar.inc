CMD:getcar(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new vehid; else return SCM(playerid, blue, "[���������]: {FFFFFF}������� - /getcar [ID ����������]");
	new Float:x, Float:y, Float:z;

	if(!IsValidVehicle(vehid)) return SCM(playerid, red, "������ ���������� �� ����������.");

	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehid, x+3, y+3, z);
	return 1;
}