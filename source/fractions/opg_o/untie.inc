CMD:untie(playerid, params[])
{
    if(!IsAOpg(playerid)) return YouCannotUseThisFunc(playerid);
    
    extract params -> new to_player; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /untie [ID игрока]");
    
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(!IsPlayerInRangeOfPoint(to_player, 5.0, x, y, z)) return SCM(playerid, red, "Человек далеко от вас!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(GetPVarInt(to_player, "tied") != 1) return SCM(playerid, red, "У данного человека не связаны руки!");

    SetPlayerSpecialAction(to_player, SPECIAL_ACTION_NONE);
    DeletePVar(to_player, "tied");

    new string[128];
    format(string, sizeof(string), "Вы развязали руки %s", PlayerInfo[to_player][pName]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s развязал вам руки", PlayerInfo[playerid][pName]);
    SCM(to_player, blue, string);
    
    format(string, sizeof(string), "развязывает руки %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);
    return 1;
}