ALTX:n("/b");
CMD:n(playerid, params[])
{
    if(sscanf(params, "s[100]", params[0])) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: ����������� /b [�����]");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"� ������ ������ � ��� ���. ����� �� ����� ����: /time");
	new string[128];
	format(string, sizeof(string), "(( %s[%d]: %s ))", PlayerInfo[playerid][pName], playerid, params[0]);
	ProxDetector(30.0, playerid, string, 0xCCCC99FF, 0xCCCC99FF, 0xCCCC99FF, 0xCCCC99FF, 0xCCCC99FF);
	
	format(string, sizeof(string), "(( %s ))", params[0]);
	SetPlayerChatBubble(playerid, string, 0xCCCC99FF, 30.0, 5000);
	return 1;
}