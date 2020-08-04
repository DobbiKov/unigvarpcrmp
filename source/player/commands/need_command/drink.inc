CMD:drink(playerid)
{
    if(PlayerInfo[playerid][pBeer] <= 0) return SCM(playerid, red, "У вас нет пива!");
    if(PlayerInfo[playerid][pNeedDrink] + 10 > 100) return SCM(playerid, red, "Вы не хотите пить!");

    PlayerInfo[playerid][pBeer]--;
    PlayerInfo[playerid][pNeedToilet] -= 8;
    if(PlayerInfo[playerid][pNeedToilet] < 0) PlayerInfo[playerid][pNeedToilet] = 0;
    PlayerInfo[playerid][pNeedDrink] += 10;
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
    return SCM(playerid, blue, "Вы выпили пиво, тем самым уталили жажду!");
}