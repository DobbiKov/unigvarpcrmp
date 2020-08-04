CMD:eject(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerVehicleSeat(playerid) != 0) return SCM(playerid, red, "Вы не сидите за рулём!");

    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /eject [ID игрока]");
    
    if(GetPlayerVehicleID(playerid) != GetPlayerVehicleID(to_player) || !IsPlayerInAnyVehicle(to_player)) return SCM(playerid, red, "Человек не находится в вашем авто!");

    new string[144];
    format(string, sizeof(string), "выкинул-(а) из транспорта %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);
    RemovePlayerFromVehicle(to_player);
    return TogglePlayerControllable(playerid, 1);
}