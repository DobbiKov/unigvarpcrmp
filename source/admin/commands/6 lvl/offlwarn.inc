CMD:offlwarn(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new string: to_player[32]; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /offlwarn [NickName ������]");

    foreach(new i : Player)
    {
        if(!strcmp(PlayerInfo[i][pName], to_player, true))
        {
            SCM(playerid, white, "����� �� ������. �����������: /lwarn");
            return 1;
        }
    }
    new query[144];
    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `pName` = '%s'", to_player);
    mysql_tquery(connects, query, "Off_LWarn", "ds", playerid, to_player);
    return 1;
}

publics Off_LWarn(playerid, to_player[])
{
    new rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new rang, fwarns, member;
        rang = cache_get_field_content_int(0, "pRang");
        member = cache_get_field_content_int(0, "pMember");
        fwarns = cache_get_field_content_int(0, "pWarnF");

        if(rang < 10) return SCM(playerid, red, "����� �� �������� �������!");

        fwarns++;
        new string[144];
        format(string, sizeof(string), "[A] %s[%d] ����� ��������� ������� %s � �������� [%d|3]", PlayerInfo[playerid][pName], playerid, to_player, fwarns);
        SCMA(grey, string);


        if(fwarns >= 3)
        {
            format(string, sizeof(string), "UPDATE `accounts` SET `pMember` = '0' WHERE `pName` = '%s'", to_player);
            mysql_tquery(connects, string, "", "");

            format(string, sizeof(string), "UPDATE `accounts` SET `pRang` = '0' WHERE `pName` = '%s'", to_player);
            mysql_tquery(connects, string, "", "");

            format(string, sizeof(string), "UPDATE `accounts` SET `pWarnF` = '0' WHERE `pName` = '%s'", to_player);
            mysql_tquery(connects, string, "", "");
        
            format(string, sizeof(string), "UPDATE `accounts` SET `pFSkin` = '-1' WHERE `pName` = '%s'", to_player);
            mysql_tquery(connects, string, "", "");

            new data[144];
            format(data, sizeof(data), "%s ������ ��� �� ����������� %s offline. �������: 3 ��������� ��������", PlayerInfo[playerid][pName], GetMember[ member ]);

            format(string, sizeof(string), "UPDATE `accounts` SET `pOffUninviteMess` = '%s' WHERE `pName` = '%s'", data, to_player);
            mysql_tquery(connects, string, "", "");

            format(string, sizeof(string), "[A] %s ��� ������ �� �����������. �������: 3 ��������� ��������", to_player);
            SCMA(grey, string);
        }
        else
        {
            format(string, sizeof(string), "UPDATE `accounts` SET `pWarnF` = '%d' WHERE `pName` = '%s'", fwarns, to_player);
            mysql_tquery(connects, string, "", "");
        }
    }
    else
    {
        return SCM(playerid, red, "������ ������ ���!");
    }
    return 1;
}