CMD:slimit(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SCM(playerid, red, "Вы не можете использовать данную функцию в данный момент!");
    extract params -> new count; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /slimit [0-3]");
    new vehicleid = GetPlayerVehicleID(playerid);
    new Float:veh_health;
    GetVehicleHealth(vehicleid, veh_health );

    if(veh_health <= 400) return SCM(playerid, red, "Вы не можете использовать данную функцию в данный момент!");

    switch(count)
    {
        case 0:
        {
            vehicle[vehicleid][veh_limit] = 0.0;
            SCM(playerid, 0x99CC00FF, "Вы отключили ограничение скорости.");
        }
        case 1:
        {
            vehicle[vehicleid][veh_limit] = 20.0;
            SCM(playerid, 0x99CC00FF, "Вы установили ограничение скорости №1 20 км/ч");
        }
        case 2:
        {
            vehicle[vehicleid][veh_limit] = 60.0;
            SCM(playerid, 0x99CC00FF, "Вы установили ограничение скорости №2 60 км/ч");
        }
        case 3:
        {
            vehicle[vehicleid][veh_limit] = 90.0;
            SCM(playerid, 0x99CC00FF, "Вы установили ограничение скорости №3 90 км/ч");
        }
        default: return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /slimit [0-3]");
    }
    return 1;
}