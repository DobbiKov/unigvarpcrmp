CMD:free(playerid, params[])
{
    if(PlayerInfo[playerid][pRang] < 5) return SCM(playerid, red, "Данную функцию можно использовать с 5-го ранга!");
    if(PlayerInfo[playerid][pMember] != TEAM_ADM) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, price; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /free [ID игрока] [цена]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(price < 5000 || price > 50000) return SCM(playerid, red, "Цена не менее 5000 и не более 50000!");
    if(PlayerInfo[to_player][pKPZ] == -1) return SCM(playerid, red, "Гражданин не сидит в КПЗ!");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока нет столько денег!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_FREE, price);
}