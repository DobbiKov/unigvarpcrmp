CMD:addatm(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(totalatm > MAX_ATMS) return SCM(playerid, red, "�� ������� �������� ����� ����������!");

    new Float:x, Float:y, Float:z;
    new sql[256];
    GetPlayerPos(playerid, x, y, z);

    format(
        sql, sizeof(sql), 
        "INSERT INTO `atms` (`atmX`, `atmY`, `atmZ`) VALUES ('%f', '%f', '%f')",
        x, y, z
    );
    mysql_tquery(connects, sql, "", "");

    new i = totalatm;
    i += 1;

    AtmInfo[i][atmX] = x;
    AtmInfo[i][atmY] = y;
    AtmInfo[i][atmZ] = z;

    AtmInfo[i][atmLabel] = CreateDynamic3DTextLabel("{"cblue"}��������\n\n{"cwhite"}�������: {"cblue"}L. ALT", 0xFFFFFFFF, AtmInfo[i][atmX], AtmInfo[i][atmY], AtmInfo[i][atmZ]+1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);

    totalatm++;

    Iter_Add(AllATMs, i);

    SCM(playerid, green, "�� ������� ������� ��������!");
    return 1;
}