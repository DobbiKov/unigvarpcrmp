CMD:tie(playerid, params[])
{
    if(!IsAOpg(playerid)) return YouCannotUseThisFunc(playerid);
    
    extract params -> new to_player; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /tie [ID игрока]");
    
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(!IsPlayerInRangeOfPoint(to_player, 5.0, x, y, z)) return SCM(playerid, red, "Человек далеко от вас!");
    if(IsPlayerInAnyVehicle(to_player)) return SCM(playerid, red, "Игрок находиться в автомобиле!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(GetPVarInt(to_player, "tied") == 1 || GetPVarInt(to_player, "cuffed") == 1) return SCM(playerid, red, "У данного человека уже связаны руки!");

    SetPlayerSpecialAction(to_player, SPECIAL_ACTION_NONE);    
	SetPlayerSpecialAction(to_player, SPECIAL_ACTION_CUFFED);
	//SetPlayerAttachedObject(to_player, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
    SetPVarInt(to_player, "tied", 1);

    new string[128];
    format(string, sizeof(string), "Вы связали руки %s", PlayerInfo[to_player][pName]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s связал вам руки", PlayerInfo[playerid][pName]);
    SCM(to_player, blue, string);
    
    format(string, sizeof(string), "связывает руки %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);
    return 1;
}