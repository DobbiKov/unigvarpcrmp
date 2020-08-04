CMD:ticket(playerid, params[])
{
    if(!IsAPolice(playerid) && PlayerInfo[playerid][bAdmin] < 2) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, cash, string: reason[50]; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /ticket [ID игрока] [сумма] [причина]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID.");
    if(cash > 50000 || cash <= 0) return SCM(playerid, red, "Сумма штрафа не менее 0 и не более 50 тысяч.");
    if(!strlen(reason) || strlen(reason) > 50) return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /ticket [ID игрока] [сумма] [причина]");

    new Float:pos[3];
    GetPlayerPos(to_player, pos[0], pos[1], pos[2]);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2])) return SCM(playerid, red, "Игрок далеко от вас");
    if(PlayerInfo[to_player][pFines] >= 30) return SCM(playerid, red, "У данного игрока уже 30 штрафов.");

    new fine = cash;

    PlayerInfo[to_player][pFines]++;
    PlayerInfo[to_player][pSumFines] += fine;

    if(PlayerInfo[to_player][pFines] >= 30)
    {
        PlayerInfo[to_player][pLicA] = 0;
        PlayerInfo[to_player][pLicB] = 0;
        PlayerInfo[to_player][pLicC] = 0;
        PlayerInfo[to_player][pLicD] = 0;

        SCM(to_player, red, "Вы были лишены водительских прав за неуплату 30 штрафов.");
        SCM(to_player, blue, "Оплатить штрафы Вы можете в любом банкомате. Просмотр штрафов: /tickets");
    }
    else
    {
        new hours, minutes, sec;
        gettime(hours, minutes, sec);

        static const fmt_query[] = "INSERT INTO `fines` (`account_id`, `fined`, `fine`, `date`, `reason`) VALUES ('%d', '%s', '%d', '%s %02d:%02d:%02d', '%s')";
        new query[sizeof(fmt_query)+(-2+3)+(-2+MAX_PLAYER_NAME)+(-2+6)+(-2+30)+(-2+30)];
        format(query, sizeof(query), fmt_query, PlayerInfo[to_player][pID], PlayerInfo[playerid][pName], fine, date("%dd.%mm.%yyyy", gettime()), hours, minutes, sec, reason);
        mysql_tquery(connects, query, "", "");

        new string[144];
        format(string, sizeof(string), "%s %s выписал вам штраф на сумму %d руб. Причина: %s", GetPlayerRank(playerid), PlayerInfo[playerid][pName], fine, reason);
        SCM(to_player, blue, string);

        format(string, sizeof(string), "Вы выписали штраф %s на сумму %d руб. Причина: %s", PlayerInfo[to_player][pName], fine, reason);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "выписал(-а) штраф %s", PlayerInfo[to_player][pName]);
        cmd::me(playerid, string);

        static const fmt_msg[] = "Количество штрафов: %d/30 до изьятия водительских прав";
        format(string, sizeof(string), fmt_msg, PlayerInfo[playerid][pFines]);
        SCM(to_player, blue, string);
    }
    SaveAccounts(playerid);
    SaveAccounts(to_player);
    return 1;
}