CMD:takelic(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3 && !IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, id; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /takelic [ID игрока] [категория 1 - A, 2 - B, 3 - C, 4 - D]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][bAdmin] >= 3 || IsAPolice(to_player)) return SCM(playerid, red, "Вы не можете отобрать лицензии у данного игрока!");
    if(id < 1 || id > 4) return SCM(playerid, red, "2-ое значение должно быть не менее 1-го и не более 4-ех.");

    new string[144];
    switch(id)
    {
        case 1:
        {
            if(PlayerInfo[to_player][pLicA] < 1) return SCM(playerid, red, "У игрока отсутсвует лицензия данной категории!");

            PlayerInfo[to_player][pLicA] = 0;
            format(string, sizeof(string), "Вы отобрали права категории A у %s", PlayerInfo[to_player][pName]);
            SCM(playerid, blue, string);

            format(string, sizeof(string), "%s %s отобрал у вас права категории A", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName]);
            SCM(to_player, blue, string);

            SaveAccounts(to_player);
        }
        case 2:
        {
            if(PlayerInfo[to_player][pLicB] < 1) return SCM(playerid, red, "У игрока отсутсвует лицензия данной категории!");

            PlayerInfo[to_player][pLicB] = 0;
            format(string, sizeof(string), "Вы отобрали права категории B у %s", PlayerInfo[to_player][pName]);
            SCM(playerid, blue, string);

            format(string, sizeof(string), "%s %s отобрал у вас права категории B", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName]);
            SCM(to_player, blue, string);

            SaveAccounts(to_player);
        }
        case 3:
        {
            if(PlayerInfo[to_player][pLicC] < 1) return SCM(playerid, red, "У игрока отсутсвует лицензия данной категории!");

            PlayerInfo[to_player][pLicC] = 0;
            format(string, sizeof(string), "Вы отобрали права категории C у %s", PlayerInfo[to_player][pName]);
            SCM(playerid, blue, string);

            format(string, sizeof(string), "%s %s отобрал у вас права категории C", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName]);
            SCM(to_player, blue, string);

            SaveAccounts(to_player);
        }
        case 4:
        {
            if(PlayerInfo[to_player][pLicD] < 1) return SCM(playerid, red, "У игрока отсутсвует лицензия данной категории!");

            PlayerInfo[to_player][pLicD] = 0;
            format(string, sizeof(string), "Вы отобрали права категории D у %s", PlayerInfo[to_player][pName]);
            SCM(playerid, blue, string);

            format(string, sizeof(string), "%s %s отобрал у вас права категории D", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName]);
            SCM(to_player, blue, string);

            SaveAccounts(to_player);
        }
    }
    return 1;
}