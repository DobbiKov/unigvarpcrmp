public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 1.0, 2051.3542,1903.5139,-77.2241))
        {
            ShowBankMenu(playerid);
        }
    }
	#if	defined	bank__OnPlayerKeyStateChange
		return bank__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange bank__OnPlayerKeyStateChange
#if	defined	bank__OnPlayerKeyStateChange
	forward bank__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_BANK:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        new string[256];
                        format(string, sizeof(string), "{FFFFFF}�� ����� ���������� �����: {"cblue"}%d ������.\n\n{FFFFFF}����� ����� �� ������� �����?", PlayerInfo[playerid][pBCash]);
                        SPD
                        (
                            playerid, D_BANK_GET_MONEY, DIALOG_STYLE_INPUT,
                            "{"cblue"}����",
                            string,
                            "�����", "������"
                        );
                    }
                    case 1:
                    {
                        new string[256];
                        format(string, sizeof(string), "{FFFFFF}� ��� �� ����� � ������ ������: {"cblue"}%d ������.\n\n{FFFFFF}����� ����� �� ������� ��������?", PlayerInfo[playerid][pCash]);
                        SPD
                        (
                            playerid, D_BANK_PUT_MONEY, DIALOG_STYLE_INPUT,
                            "{"cblue"}����",
                            string,
                            "�����", "������"
                        );
                    }
                    case 2:
                    {
                        new string[256];
                        format(string, sizeof(string), "{FFFFFF}�� ����� ���������� �����: {"cblue"}%d ������.", PlayerInfo[playerid][pBCash]);
                        SPD
                        (
                            playerid, D_BANK_MONEY, DIALOG_STYLE_INPUT,
                            "{"cblue"}����",
                            string,
                            "�����", ""
                        );
                    }
                    case 3:
                    {
                        if(PlayerInfo[playerid][pHomeID] == -1) return SCM(playerid, red, !"� ��� ��� ����.");
                        ShowPayHouse(playerid);
                    }
                    case 4:
                    {
                        if(PlayerInfo[playerid][pBizID] == -1) return SCM(playerid, red, !"� ��� ��� �������.");
                        ShowPayBiz(playerid);
                    }
                    case 5:
                    {
                        if(PlayerInfo[playerid][pBizID] == -1) return SCM(playerid, red, !"� ��� ��� �������.");
                        ShowTakeBizMoney(playerid);
                    }
                }
            }
        }
        case D_BANK_GET_MONEY:
        {
            if(!response) return ShowBankMenu(playerid);
            else
            {
                if(!IsNumeric(inputtext) || PlayerInfo[playerid][pBCash] < strval(inputtext) || strval(inputtext) < 0 || !strlen(inputtext))
                {
                    new string[256];
                    format(string, sizeof(string), "{FFFFFF}�� ����� ���������� �����: {"cblue"}%d ������.\n\n{FFFFFF}����� ����� �� ������� �����?", PlayerInfo[playerid][pBCash]);
                    SPD
                    (
                        playerid, D_BANK_GET_MONEY, DIALOG_STYLE_INPUT,
                        "{"cblue"}����",
                        string,
                        "�����", "������"
                    );
                    return 1;
                }
                GiveBankMoney(playerid, -strval(inputtext), "������ ����� � ����������� �����");
                GiveMoney(playerid, strval(inputtext), "������ ����� � ����������� �����");

                new string[144];
                format(string, sizeof(string), "�� ����� {"cyellow"}%d ������ {"cblue"}� ������ ����������� �����.", strval(inputtext));
                return SCM(playerid, blue, string);
            }
        }

        case D_BANK_PUT_MONEY:
        {
            if(!response) return ShowBankMenu(playerid);
            else
            {
                if(!IsNumeric(inputtext) || PlayerInfo[playerid][pCash] < strval(inputtext) || strval(inputtext) < 0 || !strlen(inputtext))
                {
                    new string[256];
                    format(string, sizeof(string), "{FFFFFF}� ��� �� ����� � ������ ������: {"cblue"}%d ������.\n\n{FFFFFF}����� ����� �� ������� ��������?", PlayerInfo[playerid][pCash]);
                    SPD
                    (
                        playerid, D_BANK_PUT_MONEY, DIALOG_STYLE_INPUT,
                        "{"cblue"}����",
                        string,
                        "�����", "������"
                    );
                    return 1;
                }
                GiveBankMoney(playerid, strval(inputtext), "�������(-�) ������ �� ���������� ����");
                GiveMoney(playerid, -strval(inputtext), "�������(-�) ������ �� ���������� ����");

                new string[144];
                format(string, sizeof(string), "�� �������� {"cyellow"}%d ������ {"cblue"}�� ��� ���������� ����.", strval(inputtext));
                return SCM(playerid, blue, string);
            }
        }
        case D_BANK_MONEY:
        {
            if(!response) return ShowBankMenu(playerid);
            else return ShowBankMenu(playerid);
        }
        case D_BANK_PAY_BIZ:
        {
            if(!response) return ShowBankMenu(playerid), DeletePVar(playerid, "bank_my_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "bank_my_biz_id");
                if(!IsNumeric(inputtext) || strval(inputtext) < 0 || !strlen(inputtext) || PlayerInfo[playerid][pCash] < business_params[ BusinessInfo[b][bType] ][b_rent_price]*strval(inputtext) || BusinessInfo[b][bDays]+strval(inputtext) > 30)
                {
                    return ShowPayBiz(playerid);
                }

                GiveMoney(playerid, -business_params[ BusinessInfo[b][bType] ][b_rent_price]*strval(inputtext), "������ �������");
                BusinessInfo[b][bDays] += strval(inputtext);

                UpdateBusiness(b);

                new string[144];
                format(string, sizeof(string), "�� �������� ���� ������ �� {"cyellow"}%d ����", strval(inputtext));
                return SCM(playerid, blue, string);               
            }
        }
        case D_BANK_TAKE_BIZ_MONEY:
        {
            if(!response) return ShowBankMenu(playerid), DeletePVar(playerid, "bank_my_biz_id");
            else
            {
                new b = GetPVarInt(playerid, "bank_my_biz_id");
                if(!IsNumeric(inputtext) || strval(inputtext) < 0 || !strlen(inputtext) || BusinessInfo[b][bCash] < strval(inputtext))
                {
                    return ShowTakeBizMoney(playerid);
                }

                GiveMoney(playerid, strval(inputtext), "���� ������ � ������� �������");
                BusinessInfo[b][bCash] -= strval(inputtext);

                UpdateBusiness(b);

                new string[144];
                format(string, sizeof(string), "����� � ������� ������� {"cyellow"}%d ���.", strval(inputtext));
                return SCM(playerid, blue, string);               
            }
        }
        case D_BANK_PAY_HOME:
        {
            if(!response) return ShowBankMenu(playerid), DeletePVar(playerid, "bank_my_house_id");
            else
            {
                new h = GetPVarInt(playerid, "bank_my_house_id");
                if(!IsNumeric(inputtext) || strval(inputtext) < 0 || !strlen(inputtext) || PlayerInfo[playerid][pCash] < house_params[ HouseInfo[h][hType] ][hrent]*strval(inputtext) || HouseInfo[h][hDays]+strval(inputtext) > 30)
                {
                    return ShowPayHouse(playerid);
                }

                GiveMoney(playerid, -house_params[ HouseInfo[h][hType] ][hrent]*strval(inputtext), "������ ����");
                HouseInfo[h][hDays] += strval(inputtext);

                SaveHouse(h);

                new string[144];
                format(string, sizeof(string), "�� �������� ���� ��� �� {"cyellow"}%d ����", strval(inputtext));
                return SCM(playerid, blue, string);               
            }
        }
    }
	#if	defined	bank__OnDialogResponse
		return bank__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse bank__OnDialogResponse
#if	defined	bank__OnDialogResponse
	forward bank__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

stock ShowBankMenu(playerid)
{
    SPD
    (
        playerid, D_BANK, DIALOG_STYLE_LIST,
        "{"cblue"}����",
        "\
        {"cblue"}1. {FFFFFF}����� ������\n\
        {"cblue"}2. {FFFFFF}�������� ������\n\
        {"cblue"}3. {FFFFFF}������ �����\n\
        {"cblue"}4. {FFFFFF}�������� ���\n\
        {"cblue"}5. {FFFFFF}�������� ������\n\
        {"cblue"}6. {FFFFFF}������ �������\
        ",
        "�����", "������"
    );
    return 1;
}

stock ShowPayBiz(playerid)
{
    new b;
    foreach(new i : Allbusiness) if(BusinessInfo[i][bID] == PlayerInfo[playerid][pBizID])
    { 
        b = i; 
        break;
    }

    new string[256];
    format
    (
        string, sizeof(string), 
        "{FFFFFF}\
        ���������� ����:  %d/30\n\
        ���������� �����: %d ������\n\n\
        �� ������� ���� �� ������ �������� ������?\
        ",
        BusinessInfo[b][bDays],
        business_params[ BusinessInfo[b][bType] ][b_rent_price]
    );
    SPD
    (
        playerid, D_BANK_PAY_BIZ, DIALOG_STYLE_INPUT,
        "{"cblue"}����",
        string,
        "�����", "�����"
    );
    return SetPVarInt(playerid, "bank_my_biz_id", b);
}

stock ShowPayHouse(playerid)
{
    new h;
    foreach(new i : Allhouses) if(HouseInfo[i][hID] == PlayerInfo[playerid][pHomeID]) 
    {
        h = i;
        break;
    }

    new string[256];
    format
    (
        string, sizeof(string), 
        "{FFFFFF}\
        ���������� ����:  %d/30\n\
        ���������� �����: %d ������\n\n\
        �� ������� ���� �� ������ �������� ���?\
        ",
        HouseInfo[h][hDays],
        house_params[ HouseInfo[h][hType] ][hrent]
    );
    SPD
    (
        playerid, D_BANK_PAY_HOME, DIALOG_STYLE_INPUT,
        "{"cblue"}����",
        string,
        "�����", "�����"
    );
    return SetPVarInt(playerid, "bank_my_house_id", h);
}

stock ShowTakeBizMoney(playerid)
{
    new b;
    foreach(new i : Allbusiness) if(BusinessInfo[i][bID] == PlayerInfo[playerid][pBizID])
    { 
        b = i; 
        break;
    }

    new string[256];
    format
    (
        string, sizeof(string),
        "{FFFFFF}�� ������� ������ �������: {"cblue"}%d ������{FFFFFF}.\n\n\
        ����� ����� �� ������� �����?", BusinessInfo[b][bCash]
    );

    SPD
    (
        playerid, D_BANK_TAKE_BIZ_MONEY, DIALOG_STYLE_INPUT,
        "{"cblue"}����",
        string,
        "�����", "�����"
    );

    return SetPVarInt(playerid, "bank_my_biz_id", b);
}