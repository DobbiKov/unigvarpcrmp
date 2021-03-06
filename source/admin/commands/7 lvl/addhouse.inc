CMD:addhouse(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(totalhouses >= MAX_HOUSES) return SCM(playerid, red, "�� ������� �������� ����� �����.");
    
    extract params -> new type, price; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /addhouse [��� ���� (1-3)] [���� ����]");
    if(!(1 <= type <= 3)) return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /addhouse [��� ���� (1-3)] [���� ����]");

    new Float:x, Float:y, Float:z, sql[144];
    GetPlayerPos(playerid, x, y, z);

    format(sql, sizeof(sql), "INSERT INTO `houses` (`hType`, `hPrice`, `hExitX`, `hExitY`, `hExitZ`) VALUES ('%d', '%d', '%f', '%f', '%f')", type, price, x, y, z);
    mysql_tquery(connects, sql, "", "");
    return SCM(playerid, green, "��� ������� ������. �� �������� ����� ������������.");
}


CMD:sethousecarpos(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "�� ������ ��������� � ����������.");
    
    extract params -> new house_id; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /sethousecarpos [ID ����]");
    if(house_id >= MAX_HOUSES) return SCM(playerid, red, "������ ���� ���.");


    new Float:x, Float:y, Float:z, Float:angle;
    GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
    GetVehicleZAngle( GetPlayerVehicleID(playerid), angle);

    foreach(new i : Allhouses) if(house_id == HouseInfo[i][hID])
    {
        HouseInfo[i][car_pos_x] = x;
        HouseInfo[i][car_pos_y] = y;
        HouseInfo[i][car_pos_z] = z;
        HouseInfo[i][car_pos_a] = angle;
        SCM(playerid, green, "�� ���������� ����� ������ ���� ����.");
        return SaveHouse(i);
    }


    return SCM(playerid, red, "������ ���� ���!");
}

