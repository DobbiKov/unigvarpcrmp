CMD:tpcoord(playerid,params[])
{
    if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);
    new Float:px,Float:py,Float:pz,string[128];
    if(sscanf(params,"p<,>fff",px,py,pz)) return SCM(playerid, white, "�������: /tpcoord <x,y,z>");
    SetPlayerPos(playerid,px,py,pz);
    format(string, sizeof(string), "�� ���� ���������������� �� ��������� ���� ����������: %f, %f, %f",px,py,pz);
    SendClientMessage(playerid, 0xFFFFFFAA, string);
    return 1;
}