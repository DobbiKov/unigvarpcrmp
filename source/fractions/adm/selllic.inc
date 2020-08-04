CMD:selllic(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] != TEAM_ADM) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, type; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /selllic [ID игрока] [тип лицензии]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(type > 3 || type < 1) return SCM(playerid, red, "Не больше 3 и не менее 1!");
    if(PlayerInfo[to_player][pCash] < lic_price[type]) return SCM(playerid, red, "У игрока недостаточно денег!");
    if(playerid == to_player) return SCM(playerid, red, "Вы указали свой ID!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_SELLLIC, type);
}