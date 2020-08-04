CMD:uncuff(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);
    
    extract params -> new to_player; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /uncuff [ID игрока]");
    
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(!IsPlayerInRangeOfPoint(to_player, 5.0, x, y, z)) return SCM(playerid, red, "Человек далеко от вас!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(GetPVarInt(to_player, "cuffed") != 1) return SCM(playerid, red, "Человек не в наручниках!");
    if(IsAPolice(to_player)) return SCM(playerid, red, "Данный игрок состоит в полиции!");

    SetPlayerSpecialAction(to_player, SPECIAL_ACTION_NONE);
    DeletePVar(to_player, "cuffed");

    new string[128];
    format(string, sizeof(string), "Вы сняли наручники с %s", PlayerInfo[to_player][pName]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s снял с вас наручники", PlayerInfo[playerid][pName]);
    SCM(to_player, blue, string);
    
    format(string, sizeof(string), "снимает наручники с %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);
    return 1;
}