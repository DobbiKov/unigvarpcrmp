CMD:gruz(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[���������]: {FFFFFF}����������� /gruz [ID ������]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	
	if(player_job_vehicle_created_2[to_player] == -1) return SCM(playerid, red, "� ������ ��� ����.");
	
	AttachTrailerToVehicle(player_job_vehicle_created_2[to_player], player_job_vehicle_created[to_player]);
	new string[128];
	format(string, sizeof(string), "[A] %s[%d] �������� ���� � ���� ������ %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, string);
	
	format(string, sizeof(string), "������������� %s �������� ���� � ����� ����!", PlayerInfo[playerid][pName]);
	SCM(to_player, white, string);
	return 1;
}