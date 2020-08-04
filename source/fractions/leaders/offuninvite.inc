CMD:offuninvite(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == TEAM_NONE || PlayerInfo[playerid][pRang] < 10) return YouCannotUseThisFunc(playerid);

    extract params -> new string: to_player[32], string: reason[128]; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /offuninvite [NickName игрока] [причина]");
    if(!strcmp(to_player, PlayerInfo[playerid][pName], true)) return SCM(playerid, red, "Вы не можете уволить себя!");
    foreach(new i : Player)
    {
        if(!strcmp(PlayerInfo[i][pName], to_player, true)) return SCM(playerid, red, "Игрок онлайн, используйте: /uninvite");
    }

    new string[128];
    format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pName` = '%s'", to_player);
    mysql_tquery(connects, string, "off_uninvite", "iss", playerid, to_player, reason);
    return 1;
}

publics off_uninvite(playerid, to_player[], reason[])
{
    new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    {
        new rang, member, string[256];
        member = cache_get_field_content_int(0, "pMember");
        rang = cache_get_field_content_int(0, "pRang");

        if(PlayerInfo[playerid][pMember] != member) return SCM(playerid, red, "Игрок не состоит в вашей организации!");
        if(rang >= PlayerInfo[playerid][pRang]) return SCM(playerid, red, "Вы не можете уволить игрока выше вас по рангу!");

        format(string, sizeof(string), "Вы уволили игрока %s из организации. Причина: %s", to_player, reason);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "UPDATE `accounts` SET `pMember` = '0' WHERE `pName` = '%s'", to_player);
        mysql_tquery(connects, string, "", "");

        format(string, sizeof(string), "UPDATE `accounts` SET `pRang` = '0' WHERE `pName` = '%s'", to_player);
        mysql_tquery(connects, string, "", "");

        format(string, sizeof(string), "UPDATE `accounts` SET `pWarnF` = '0' WHERE `pName` = '%s'", to_player);
        mysql_tquery(connects, string, "", "");
    
        format(string, sizeof(string), "UPDATE `accounts` SET `pFSkin` = '-1' WHERE `pName` = '%s'", to_player);
        mysql_tquery(connects, string, "", "");

        new data[144];
        format(data, sizeof(data), "%s %s уволил вас из организации %s offline. Причина: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], GetMember[ PlayerInfo[playerid][pMember] ], reason);

        format(string, sizeof(string), "UPDATE `accounts` SET `pOffUninviteMess` = '%s' WHERE `pName` = '%s'", data, to_player);
        mysql_tquery(connects, string, "", "");
    }
    else
    {
        SCM(playerid, red, "Такого игрока нет.");
    }
    return 1;
}
