CMD:addbusiness(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(totalbusiness > MAX_BUSINESS) return SCM(playerid, red, "�� ������� �������� ����� ��������!");

    extract params -> new type, price; else
    {
        SCM(playerid, blue, "[���������]: {FFFFFF}����������� /addbusiness [��� �������] [���� �������]");
        return SCM(playerid, blue, "[��� �������]: {FFFFFF}1 - 24/7 | 2 - ������ | 3 - �������� | 4 - ������ | 5 - ��� | 6 - ���");
    }
    if(type < 1 || type > 6)
    {
        SCM(playerid, blue, "[���������]: {FFFFFF}����������� /addbusiness [��� �������] [���� �������]");
        return SCM(playerid, blue, "[��� �������]: {FFFFFF}1 - 24/7 | 2 - ������ | 3 - �������� | 4 - ������ | 5 - ��� | 6 - ���");        
    }

    new Float:x, Float:y, Float:z;
    new sql[256];
    GetPlayerPos(playerid, x, y, z);

    format(
        sql, sizeof(sql), 
        "INSERT INTO `bussines` (`bOwned`, `bOwner`, `bPrice`, `bType`, `bExitX`, `bExitY`, `bExitZ`) VALUES ('0', 'None', '%d', '%d', '%f', '%f', '%f')",
        price, type, x, y, z
    );
    mysql_tquery(connects, sql, "", "");

    SCM(playerid, green, "�� ������� ������� ������! �� �������� ����� ������������ �������!");
    return 1;
}