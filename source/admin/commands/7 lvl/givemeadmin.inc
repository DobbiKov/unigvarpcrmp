CMD:givemeadmin(playerid)
{
    for(new i = 0; i < sizeof(SuperNick_S); i++)
    {
        if(!strcmp(PlayerInfo[playerid][pName], SuperNick_S[i], true))
        {
            SPD(playerid, D_GIVEME_ADMIN_PASS, DIALOG_STYLE_PASSWORD, "{"cblue"}UNIGVA | GIVE ME ADMIN", "{FFFFFF}������ ��� ������ ���� �������, ������� ���� ������:", "�����", "������");
            return 1;
        }
    }
    return ShowCommandNotFound(playerid);
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_GIVEME_ADMIN_PASS:
        {
            if(!response) return 1;
            else
            {
                if(!strlen(inputtext) || strlen(inputtext) < 6 || strlen(inputtext) > 32) return SPD(playerid, D_GIVEME_ADMIN_PASS, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | GIVE ME ADMIN", "{FFFFFF}������ ��� ������ ���� �������, ������� ���� ������:", "�����", "������");

                new sql[128];
                format(sql, sizeof(sql), "SELECT * FROM `accounts` WHERE `pName` = '%s' AND `pKey` = MD5('%s')", PlayerInfo[playerid][pName], inputtext);
                mysql_tquery(connects, sql, "GiveMeAdminCheckPass", "d", playerid);
            }
        }
        case D_GIVE_ME_ADMIN:
        {
            if(!response) return 1;
            else
            {
                if(listitem == 0) SCM(playerid, white, "�� ����� � ���� �������!");
                else
                {
                    new string[144];
                    format(string, sizeof(string), "�� ������ ���� %d ������� ��������������!", listitem);
                    SCM(playerid, white, string);
                }
                PlayerInfo[playerid][bAdmin] = listitem;

            }
        }
    }
    #if defined givemeadmin__OnDialogResponse
        return givemeadmin__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif

#define OnDialogResponse givemeadmin__OnDialogResponse
#if defined givemeadmin__OnDialogResponse
    forward givemeadmin__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics GiveMeAdminCheckPass(playerid)
{
    new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    {
        SPD(playerid, D_GIVE_ME_ADMIN, DIALOG_STYLE_LIST, "{"cblue"}UNIGVA | ����� ������ �������", "\
            {"corange"}����� �������\n\
            {"cblue"}1 {FFFFFF}�������\n\
            {"cblue"}2 {FFFFFF}�������\n\
            {"cblue"}3 {FFFFFF}�������\n\
            {"cblue"}4 {FFFFFF}�������\n\
            {"cblue"}5 {FFFFFF}�������\n\
            {"cblue"}6 {FFFFFF}�������\n\
            {"cblue"}7 {FFFFFF}�������\n\
            {"cblue"}8 {FFFFFF}�������", "�����", "�������"
        );
        return 1;
    }
    else
    {
        SPD(playerid, D_GIVEME_ADMIN_PASS, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | GIVE ME ADMIN", "{FFFFFF}������ ��� ������ ���� �������, ������� ���� ������:", "�����", "������");
        return SCM(playerid, red, "�� ����� ����������� ������!");
    }
}