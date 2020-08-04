CMD:heal(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] != TEAM_HEAL) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, price; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /heal [ID игрока] [цена]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(price < 100 || price > 500) return SCM(playerid, red, "Цена не менее 100 и не более 500 рублей!");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока нет столько денег!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_HEAL, price);
}