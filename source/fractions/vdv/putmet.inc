CMD:putmet(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] != TEAM_VDV) return YouCannotUseThisFunc(playerid);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1494.8928,1660.9591,-5.3171)) return SCM(playerid, red, "�� �� �� ������!");

    extract params -> new metall; else return SCM(playerid, yellow, "[���������]: {FFFFFF}/putmet [�-�� ��������]");

    if(PlayerInfo[playerid][pMetall] < metall) return SCM(playerid, red, "� ��� ��� ������� �������!");

    new string[144];
    format(string, sizeof(string), "�� �������� �� ����� ����� %d ��. �������", metall);
    SCM(playerid, green, string);

    PlayerInfo[playerid][pMetall] -= metall;
    REPOSITORY_ARMY_METALL += metall;
    SaveRepository();
    return 1;
}