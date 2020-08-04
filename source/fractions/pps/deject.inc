CMD:deject(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);
    
    extract params -> new to_player; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /deject [ID игрока]");
    
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(!IsPlayerInRangeOfPoint(to_player, 5.0, x, y, z)) return SCM(playerid, red, "Человек далеко от вас!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(IsAPolice(to_player)) return SCM(playerid, red, "Данный игрок состоит в полиции!");
    if(!IsPlayerInAnyVehicle(to_player)) return SCM(playerid, red, "Человек не находиться в автомобиле!");

    new string[144];
    format(string, sizeof(string), "Вы вытащили %s из авто", PlayerInfo[to_player][pName]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s вытащил вас из авто", PlayerInfo[playerid][pName]);
    SCM(to_player, blue, string);

    format(string, sizeof(string), "выломал дверь автомобиля");
    cmd::me(playerid, string);
    return RemovePlayerFromVehicle(to_player);
}