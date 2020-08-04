CMD:pay(playerid, params[])
{
    extract params -> new to_player, money; else return SCM(playerid, blue, "[Подсказка] {FFFFFF}Используйте: /pay [ID игрока] [кол-во денег]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(to_player, x, y, z);
    if(!IsPlayerInRangeOfPoint(playerid, 10.0, x, y, z)) return SCM(playerid, red, "Игрок далеко от вас!");
    if(money < 1) return SCM(playerid, blue, "[Подсказка] {FFFFFF}Используйте: /pay [ID игрока] [кол-во денег]");
    if(PlayerInfo[playerid][pCash] < money) return SCM(playerid, red, "У вас нет столько денег");
    if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][pVIP] > 0 && money > 50000) return SCM(playerid, red, "Вы не можете передать более 50.000 рублей!");
    if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][pVIP] < 1 && money > 10000) return SCM(playerid, red, "Вы не можете передать более 10.000 рублей!");
    
    new string[144];
    format(string, sizeof(string), "Вы передали %s %d рублей", PlayerInfo[to_player][pName], money);
    SCM(playerid, green, string);

    format(string, sizeof(string), "%s передал вам %d рублей", PlayerInfo[playerid][pName], money);
    SCM(to_player, green, string);

    format(string, sizeof(string), "взял деньги и передал их %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);

    GiveMoney(playerid, -money, "/pay");
    GiveMoney(to_player, money, "/pay");
    return 1;
}