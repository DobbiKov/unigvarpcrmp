#define MAX_FAMILYS 500
// famcolor 33cdff

new fam_rang[4][20] = {"---", "���� �����", "�����������", "���������"};

new last_fam_id;
new totalfamily;
new Iterator: AllFamilys<MAX_FAMILYS>;

enum E_FAM_INFO
{
    fID,
    fName[32],
    fCreatorID,
    fCreatorName[MAX_PLAYER_NAME],
}
new FamilyInfo[MAX_FAMILYS][E_FAM_INFO];


publics LoadFamilys()
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            FamilyInfo[i][fID] = cache_get_field_content_int(i, "fID");
            FamilyInfo[i][fCreatorID] = cache_get_field_content_int(i, "fCreatorID");
            cache_get_field_content(i, "fName", FamilyInfo[i][fName], connects, MAX_PLAYER_NAME);
            cache_get_field_content(i, "fCreatorName", FamilyInfo[i][fCreatorName], connects, MAX_PLAYER_NAME);
            totalfamily++;

            Iter_Add(AllFamilys, i);
            last_fam_id = FamilyInfo[i][fID];
        }
    }
    printf("[UNIGVA]: ����� ��������� �����: %d", totalfamily);
    return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, 821.9419,804.5621,-72.9925))
        {
            if(PlayerInfo[playerid][pFamID] != -1 || PlayerInfo[playerid][pFamRang] > 0) return SCM(playerid, red, "�� ��� �������� � �����-�� �����.");

            SPD
            (
                playerid, D_CREATE_FAMILY, DIALOG_STYLE_INPUT,
                !"{"cblue"}�������� �����",
                !"{FFFFFF}�� ������������� ������ ������� �����?\n���������: {"cblue"}500 000 ������{FFFFFF}.\n\n\
                ������� �������� ����� � ������ ����:",
                !"�������", !"������"
            );
        }
    }
	#if	defined	family__OnPlayerKeyStateChange
		return family__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange family__OnPlayerKeyStateChange
#if	defined	family__OnPlayerKeyStateChange
	forward family__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_CREATE_FAMILY:
        {
            if(!response) return 1;
            else
            {
                if(!strlen(inputtext) || strlen(inputtext) > 32)
                {
                    SPD
                    (
                        playerid, D_CREATE_FAMILY, DIALOG_STYLE_INPUT,
                        !"{"cblue"}�������� �����",
                        !"{FFFFFF}�� ������������� ������ ������� �����?\n���������: {"cblue"}500 000 ������{FFFFFF}.\n\n\
                        ������� �������� ����� � ������ ����:",
                        !"�������", !"������"
                    );
                    return 1;
                }

                if(PlayerInfo[playerid][pCash] < 500000) return SCM(playerid, red, "��� �������� ����� ���������� ����� 500 ����� ������.");

                last_fam_id++;
                new i = totalfamily;
                PlayerInfo[playerid][pFamID] = last_fam_id;
                PlayerInfo[playerid][pFamRang] = 3;
                FamilyInfo[i][fID] = last_fam_id;
                FamilyInfo[i][fCreatorID] = PlayerInfo[playerid][pID];
                format(FamilyInfo[i][fName], 32, "%s", inputtext);
                format(FamilyInfo[i][fCreatorName], 32, "%s", PlayerInfo[playerid][pName]);
                new sql[528];
                format(sql, sizeof(sql), "INSERT INTO `familys` (`fName`, `fCreatorID`, `fCreatorName`) VALUES ('%s', '%d', '%s')", FamilyInfo[i][fName], FamilyInfo[i][fCreatorID], FamilyInfo[i][fCreatorName]);
                mysql_tquery(connects, sql, "", "");

                format(sql, 144, "�� ������� ������� �����: {"cwhite"}%s", inputtext);
                SCM(playerid, blue, sql);
                SCM(playerid, white, "[�������]: {"cblue"}/f /fb /fo /foff /finvite /funinvite /funinviteoff /frang /fleave");

                GiveMoney(playerid, -500000, "�������� �����");
                SaveAccounts(playerid);
                
                return totalfamily++;
            }
        }
    }
	#if	defined	family__OnDialogResponse
		return family__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse family__OnDialogResponse
#if	defined	family__OnDialogResponse
	forward family__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

CMD:frang(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");
    if(PlayerInfo[playerid][pFamRang] < 3) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, rang; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /frang [ID ������] [���� (1-2)]");
    if(to_player == playerid) return SCM(playerid, red, !"�� ������� ���� ID.");
    if(rang > 2 || rang < 1) return SCM(playerid, red, !"���� �� ����� 1 � �� ����� 2");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pFamID] != PlayerInfo[playerid][pFamID]) return SCM(playerid, red, !"������ ����� �� ������� � ����� �����.");

    PlayerInfo[to_player][pFamRang] = rang;
    new string[144];
    
    format(string, sizeof(string), "�� �������� %s ���� � ����� �� \"%s\"", PlayerInfo[to_player][pName], fam_rang[ PlayerInfo[to_player][pFamRang] ]);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s ������� ��� ���� � ����� �� \"%s\"", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], fam_rang[ PlayerInfo[to_player][pFamRang] ]);
    SCM(to_player, blue, string);

    SaveAccounts(playerid);
    SaveAccounts(to_player);
    return 1;
}



CMD:finvite(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");
    if(PlayerInfo[playerid][pFamRang] < 2) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /finvite [ID ������]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pFamID] != -1) return SCM(playerid, red, !"������ ����� ������� � �����-�� �����.");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_FINVITE);
}
CMD:funinvite(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");
    if(PlayerInfo[playerid][pFamRang] < 3) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, string: reason[120]; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /funinvite [ID ������] [�������]");
    if(to_player == playerid) return SCM(playerid, red, !"�� ������� ���� ID.");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pFamID] != PlayerInfo[playerid][pFamID]) return SCM(playerid, red, !"������ ����� �� ������� � ����� �����.");

    new string[144];

    format(string, sizeof(string), "�� ��������� %s �� �����. �������: %s", PlayerInfo[to_player][pName], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s �������� ��� �� �����. �������: %s", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], reason);
    SCM(to_player, blue, string);

    format(string, sizeof(string), "[F] %s %s[%d] �������� %s[%d] �� �����. �������: %s", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, reason);
    SCMF(PlayerInfo[playerid][pFamID], string);

    PlayerInfo[to_player][pFamRang] = 0;
    PlayerInfo[to_player][pFamID] = -1;

    SaveAccounts(playerid);
    SaveAccounts(to_player);

    return 1;
}

CMD:f(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");

    extract params -> new string: text[124]; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /f [�����]");

    new string[144];
    format(string, sizeof(string), "[F] %s %s[%d]: %s", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], playerid, text);
    SCMF(PlayerInfo[playerid][pFamID], string);
    return 1;
}

CMD:fb(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");

    extract params -> new string: text[124]; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /fb [�����]");

    new string[144];
    format(string, sizeof(string), "(( OOC: [F] %s %s[%d]: %s ))", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], playerid, text);
    SCMF(PlayerInfo[playerid][pFamID], string);
    return 1;
}
CMD:fleave(playerid)
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");
    if(PlayerInfo[playerid][pFamRang] == 3) return SCM(playerid, red, !"�� �� ������ �������� �����, ��� ��� ��������� ������� �����.");

    new string[144];
    format(string, sizeof(string), "[F] %s %s[%d] ������� ����� (/fleave)", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], playerid);
    SCMF(PlayerInfo[playerid][pFamID], string);

    PlayerInfo[playerid][pFamID] = -1;
    PlayerInfo[playerid][pFamRang] = 0;
    SaveAccounts(playerid);
    return 1;
}

CMD:fo(playerid)
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");

    new fmt_dialog[1024] = "ID\t\t��� �������\t\t����\n\n", string[144];
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFamID] == PlayerInfo[playerid][pFamID])
        {
            format(string, sizeof(string), "{FFFFFF}%d\t\t%s\t%d\n", i, PlayerInfo[i][pName], PlayerInfo[i][pFamRang]);
            strcat(fmt_dialog, string);
        }
    }
    return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, !"{"cblue"}����� ����� ������", fmt_dialog, "�������", "");
}

CMD:foff(playerid)
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");

    new sql[256];
    format(sql, sizeof(sql), "SELECT * FROM `accounts` WHERE `pFamID` = '%d'", PlayerInfo[playerid][pFamID]);
    mysql_tquery(connects, sql, "ShowFOff", "i", playerid);

    return 1;
}

publics ShowFOff(playerid)
{
    new rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new name[MAX_PLAYER_NAME], rang, last_connect[100], fmt_dialog[1024] = "��� �������\t\t����\t\t��������� ����\n\n", string[144];
        for(new i = 0; i < rows[0]; i++)
        {
            rang = cache_get_field_content_int(i, "pFamRang");
            cache_get_field_content(i, "pName", name, connects, MAX_PLAYER_NAME);
            cache_get_field_content(i, "pLastConnect", last_connect, connects, sizeof(last_connect));

            format(string, sizeof(string), "{FFFFFF}%s\t%d\t\t%s\n", name, rang, last_connect);
            strcat(fmt_dialog, string);
        }
        SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, !"{"cblue"}����� ����� �������", fmt_dialog, !"�������", !"");
    }
    return 1;
}

stock SCMF(famID, text[])
{
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFamID] == famID)
        {
            SCM(i, 0x33cdFFFF, text);
        }
    }
    return 1;
}


CMD:funinviteoff(playerid, params[])
{
    if(PlayerInfo[playerid][pFamID] == -1 || PlayerInfo[playerid][pFamRang] == 0) return SCM(playerid, red, !"�� �� �������� �� � ����� �����.");
    if(PlayerInfo[playerid][pFamRang] < 3) return YouCannotUseThisFunc(playerid);

    extract params -> new string: to_player[32], string: reason[120]; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /funinviteoff [��� ������] [�������]");

    foreach(new i : Player)
    {
        if(!strcmp(PlayerInfo[i][pName], to_player)) return SCM(playerid, white, "����� ������. ����������� /funinvite");
    }

    new query[256];
    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `pName` = '%s' AND `pFamID` = '%d'", to_player, PlayerInfo[playerid][pFamID]);
    mysql_tquery(connects, query, "funinviteOFF", "iss", playerid, to_player, reason);
    return 1;
}

publics funinviteOFF(playerid, to_player[], reason[])
{
    new rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new string[144];

        format(string, sizeof(string), "�� ��������� %s �� ����� �������. �������: %s", to_player, reason);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "[F] %s %s[%d] �������� %s �� ����� �������. �������: %s", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], playerid, to_player, reason);
        SCMF(PlayerInfo[playerid][pFamID], string);

        format(string, sizeof(string), "%s %s �������� ��� �� ����� �������. �������: %s", fam_rang[ PlayerInfo[playerid][pFamRang] ], PlayerInfo[playerid][pName], reason);

        new query[528];
        format(query, sizeof(query), "UPDATE `accounts` SET `pFamID` = '-1', `pFamRang` = '0', `pFAMoffuninvite` = '%s' WHERE `pName` = '%s'", string, to_player);
        mysql_tquery(connects, query, "", "");
    }
    else
    {
        SCM(playerid, red, !"������ ����� �� ������� � ����� �����.");
    }
    return 1;
}

