CMD:setarm(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new to_player, health; else return SCM(playerid, blue, "[���������] {ffffff}�������: /setarm [id ������] [arm]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	new string[120+MAX_PLAYER_NAME*2];

	if(PlayerInfo[playerid][bAdmin] < 6)
	{
	    format(string, sizeof(string), "[A] %s[%d] ��������� %d ����� ������ %s[%d]", PlayerInfo[playerid][pName], playerid, health, PlayerInfo[to_player][pName], to_player);
	    SCMA(grey, string);
	}
 	format(string, sizeof(string), "������������� %s ������� ���������� ����� �����.", PlayerInfo[playerid][pName]);
 	SCM(to_player, white, string);

	return SetPlayerArmour(to_player, health);
}