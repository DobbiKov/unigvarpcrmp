CMD:cc(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
    for(new i; i < 100; i++) SCMTA(white, "");
    new string[128];
    format(string, sizeof(string), "�������������  %s[%d] ������� ���", PlayerInfo[playerid][pName], playerid);
    return SCMTA(white, string);
}