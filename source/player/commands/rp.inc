CMD:me(playerid, params[])
{
    if(sscanf(params, "s[100]", params[0])) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: ����������� /me [�����]");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"� ������ ������ � ��� ���. ����� �� ����� ����: /time");
    new string[128];
	format(string, sizeof(string), "%s %s", PlayerInfo[playerid][pName], params[0]);
	ProxDetector(30.0, playerid, string, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF);
	return 1;
}
CMD:do(playerid, params[])
{
    if(sscanf(params, "s[100]", params[0])) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: ����������� /do [�����]");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"� ������ ������ � ��� ���. ����� �� ����� ����: /time");
    new string[128];
	format(string, sizeof(string), "%s (( %s ))", params[0], PlayerInfo[playerid][pName]);
	ProxDetector(30.0, playerid, string, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF);
	return 1;
}
CMD:todo(playerid,params[])
{
	new Text_[60], Deistvie_[60];
	if(sscanf(params, "p<*>s[60]s[60]", Text_,Deistvie_)) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: /todo [�����]*[��������]");
	if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"� ������ ������ � ��� ���. ����� �� ����� ����: /time");
	stringer[0] = EOS;
	format(stringer, 240, "\"{FFFFFF}%s{DD90FF}\", - ������ %s, %s",Text_,PlayerInfo[playerid][pName],Deistvie_);
	ProxDetector(30.0, playerid, stringer, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF);
	return 1;
}
CMD:try(playerid, params[])
{
    if(sscanf(params, "s[82]", params[0])) return SCM(playerid, white, "{"cblue"}� [���������]{"cwhite"}: ����������� /try [�����]");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, green, !"� ������ ������ � ��� ���. ����� �� ����� ����: /time");
    new string[128];
    switch(random(2))
    {
        case 0: format(string, sizeof(string), "%s %s | {FF6600}��������", PlayerInfo[playerid][pName], params[0]);
        case 1: format(string, sizeof(string), "%s %s | {66CC00}������", PlayerInfo[playerid][pName], params[0]);
    }
	ProxDetector(30.0, playerid, string, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF, 0xDD90FFFF);
	return 1;
}