CMD:unawarn(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка] {FFFFFF}Используйте: /unawarn [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][bAdmin] < 1) return SCM(playerid, red, "Игрок не является администратором!");
    if(PlayerInfo[to_player][pWarnA] < 1) return SCM(playerid, red, "У Администратора нет выговоров!");

    PlayerInfo[to_player][pWarnA]--;
    new string[144];
    format(string, sizeof(string), "[A] %s[%d] снял 1 админ. выговор у %s[%d] [%d|3]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, PlayerInfo[to_player][pWarnA]);
    SCMA(grey, string);
    format(string, sizeof(string), "%s %s снял у вас 1 выговор. Теперь у вас %d выговоров!", GetRangAdmin[ PlayerInfo[playerid][bAdmin] ], PlayerInfo[playerid][pName], PlayerInfo[to_player][pWarnA]);
    SCM(to_player, white, string);
    
    return SaveAccounts(to_player);
}