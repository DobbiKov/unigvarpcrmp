CMD:settime(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 5) return ShowCommandNotFound(playerid);
    if(sscanf(params, "d", params[0])) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: ����������� /settime [���]");
    SetWorldTime(params[0]);
    stringer[0] = EOS;
	format(stringer, 156, "[A] %s[%d] ������� ����� �� %d:00", PlayerInfo[playerid][pName], playerid, params[0]);
	SCMA(grey, stringer);
	return 1;
}