CMD:slimit(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, red, "�� �� ������ ������������ ������ ������� � ������ ������!");
    extract params -> new count; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /slimit [0-3]");
    new vehicleid = GetPlayerVehicleID(playerid);
    new Float:veh_health;
    GetVehicleHealth(vehicleid, veh_health );

    if(veh_health <= 400) return SCM(playerid, red, "�� �� ������ ������������ ������ ������� � ������ ������!");

    switch(count)
    {
        case 0:
        {
            vehicle[vehicleid][veh_limit] = 0.0;
            SCM(playerid, 0x99CC00FF, "�� ��������� ����������� ��������.");
        }
        case 1:
        {
            vehicle[vehicleid][veh_limit] = 20.0;
            SCM(playerid, 0x99CC00FF, "�� ���������� ����������� �������� �1 20 ��/�");
        }
        case 2:
        {
            vehicle[vehicleid][veh_limit] = 60.0;
            SCM(playerid, 0x99CC00FF, "�� ���������� ����������� �������� �2 60 ��/�");
        }
        case 3:
        {
            vehicle[vehicleid][veh_limit] = 90.0;
            SCM(playerid, 0x99CC00FF, "�� ���������� ����������� �������� �3 90 ��/�");
        }
        default: return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /slimit [0-3]");
    }
    return 1;
}