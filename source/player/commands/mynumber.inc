CMD:mynumber(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 4.0, 2571.1816,-2417.4631,22.3738) || GetPlayerVirtualWorld(playerid) != 1) return SCM(playerid, red, "�� ������ ��������� � ������ �������.");
    if(player_ownable_car[playerid] == -1) return SCM(playerid, red, "� ��� ��� ������� ����������, ���� �� �� ������.");
    if(strcmp(ownable_car[player_ownable_car[playerid]][oc_number], "None", false)) return SCM(playerid, red, "�� ����� ���������� ��� ������� ������."); 

    new model = GetVehicleModel(player_ownable_car[playerid]);
    new number[32];
    for(new i = 0; i != 6; i++)
    {
        if(!i) number[i] = random('M' - 'A') + 'A';
        if(i >= 1 && i <= 3) number[i] = random('9' - '0') + '0';
        if(i > 3) number[i] = random('M' - 'A') + 'A';
    }
    ownable_car[player_ownable_car[playerid]][oc_number] = EOS;
    strcat(ownable_car[player_ownable_car[playerid]][oc_number], number);

    new string[144];
    format(string, sizeof(string), "�� �������� ���.������ {"cwhite"}\"%s\" {"cblue"}�� ���� ��������� {"cwhite"}%s", ownable_car[player_ownable_car[playerid]][oc_number], GetCarName(model));
    SCM(playerid, blue, string);

    format(string, sizeof(string), "UPDATE `ownable_cars` SET `number` = '%s' WHERE `id` = '%d'", ownable_car[player_ownable_car[playerid]][oc_number], ownable_car[player_ownable_car[playerid]][oc_id]);
    mysql_tquery(connects, string, "", "");

    return UpdateDynamic3DTextLabelText(ownable_car_label[player_ownable_car[playerid]], 0xFFFFFFFF, ownable_car[player_ownable_car[playerid]][oc_number]);  
}