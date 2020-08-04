CMD:x2day(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);

    if(XDay == 2) XDay = 1;
    else XDay = 2;

    new string[40];
    format(string, sizeof(string), "Вы установили XDay на %d!", XDay);
    SCM(playerid, blue, string);

    new sql[128];
    format(sql, sizeof(sql), "UPDATE `other` SET `XDay` = '%d'", XDay);
    mysql_tquery(connects, sql, "", "");
    return 1;
}