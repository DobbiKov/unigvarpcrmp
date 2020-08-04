#define MAX_ATMS 100

new Iterator: AllATMs<MAX_ATMS>;
enum E_ATM_INFO
{
    atmID,
    Float: atmX,
    Float: atmY,
    Float: atmZ,
    Text3D: atmLabel,
}
new AtmInfo[MAX_ATMS][E_ATM_INFO];
new totalatm;

publics LoadAtm()
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            AtmInfo[i][atmID] = cache_get_field_content_int(i, "atmID");
            AtmInfo[i][atmX] = cache_get_field_content_float(i, "atmX");
            AtmInfo[i][atmY] = cache_get_field_content_float(i, "atmY");
            AtmInfo[i][atmZ] = cache_get_field_content_float(i, "atmZ");

            AtmInfo[i][atmLabel] = CreateDynamic3DTextLabel("{"cblue"}БАНКОМАТ\n\n{"cwhite"}Нажмите: {"cblue"}L. ALT", 0xFFFFFFFF, AtmInfo[i][atmX], AtmInfo[i][atmY], AtmInfo[i][atmZ]+1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);

            totalatm++;

            Iter_Add(AllATMs, i);

        }
    }
    printf("[UNIGVA]: Всего загружено банкоматов: %d", totalatm);
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        foreach(new i : AllATMs)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, AtmInfo[i][atmX], AtmInfo[i][atmY], AtmInfo[i][atmZ]))
            {
                ShowAtmDialog(playerid);
            }
        }
    }
	#if	defined	atm__OnPlayerKeyStateChange
		return atm__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange atm__OnPlayerKeyStateChange
#if	defined	atm__OnPlayerKeyStateChange
	forward atm__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock ShowAtmDialog(playerid)
{
    SPD
    (
        playerid, D_ATM, DIALOG_STYLE_LIST,
        "{"cblue"}Банкомат",
        "\
        {"cblue"}1. {FFFFFF}Снять с банковского счета\n\
        {"cblue"}2. {FFFFFF}Положить на банковский счет\n\
        {"cblue"}3. {FFFFFF}Баланс баковского счета\n\
        {"cblue"}4. {FFFFFF}Оплатить штраф\n\
        {"cblue"}5. {FFFFFF}Оплатить все штрафы\n\
        {"cblue"}6. {FFFFFF}Пополнить счет мобильного\
        ",
        "Выбрать", "Отмена"
    );
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_ATM_GET:
        {
            if(!response) return ShowAtmDialog(playerid);
            else
            {
                if(!IsNumeric(inputtext) || PlayerInfo[playerid][pBCash] < strval(inputtext))
                {
                    SPD
                    (
                        playerid, D_ATM_GET, DIALOG_STYLE_INPUT,
                        !"{"cblue"}Банкомат",
                        !"{FFFFFF}Укажите сумму, которую вы желаете снять с вашего банковского счета:",
                        !"Снять", !"Назад"
                    );                    
                    return 1;
                }

                GiveMoney(playerid, strval(inputtext), "Снятие денег в банкомате");
                GiveBankMoney(playerid, -strval(inputtext), "Снятие денег в банкомате");

                new string[144];
                format(string, sizeof(string), "Вы сняли с банковского счета %d руб.", strval(inputtext));
                return SCM(playerid, blue, string);
            }
        }
        case D_ATM_PUT:
        {
            if(!response) return ShowAtmDialog(playerid);
            else
            {
                if(!IsNumeric(inputtext) || PlayerInfo[playerid][pCash] < strval(inputtext))
                {
                    SPD
                    (
                        playerid, D_ATM_PUT, DIALOG_STYLE_INPUT,
                        !"{"cblue"}Банкомат",
                        !"{FFFFFF}Укажите сумму, которую вы желаете положить на ваш банковский счет:",
                        !"Положить", !"Назад"
                    );                  
                    return 1;
                }

                GiveMoney(playerid, -strval(inputtext), "Положил деньги в банкомате");
                GiveBankMoney(playerid, strval(inputtext), "Положил деньги в банкомате");

                new string[144];
                format(string, sizeof(string), "Вы положили на ваш банковсий счет %d руб.", strval(inputtext));
                return SCM(playerid, blue, string);
            }
        }
        case D_ATM_BALANCE:
        {
            if(!response) ShowAtmDialog(playerid);
            else ShowAtmDialog(playerid);
        }
        case D_ATM:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        SPD
                        (
                            playerid, D_ATM_GET, DIALOG_STYLE_INPUT,
                            !"{"cblue"}Банкомат",
                            !"{FFFFFF}Укажите сумму, которую вы желаете снять с вашего банковского счета:",
                            !"Снять", !"Назад"
                        );
                    }
                    case 1:
                    {
                        SPD
                        (
                            playerid, D_ATM_PUT, DIALOG_STYLE_INPUT,
                            !"{"cblue"}Банкомат",
                            !"{FFFFFF}Укажите сумму, которую вы желаете положить на ваш банковский счет:",
                            !"Положить", !"Назад"
                        );
                    }
                    case 2:
                    {
                        new string[256];
                        format(string, sizeof(string), "{FFFFFF}На вашем банковском счету %d руб.", PlayerInfo[playerid][pBCash]);
                        SPD
                        (
                            playerid, D_ATM_BALANCE, DIALOG_STYLE_MSGBOX,
                            !"{"cblue"}Банкомат",
                            string,
                            !"Назад", !""
                        );
                    }
                    case 3:
                    {
                        SPD
                        (
                            playerid, D_ATM_PAY_FINE, DIALOG_STYLE_INPUT,
                            !"{"cblue"}Оплата штрафа:",
                            !"{"cblue"}Введите номер штрафа.\n\n\
                            Что бы узнать номер штрафа, введите: /tickets",
                            !"Далее", !"Назад"
                        );
                    }
                    case 4:
                    {
                        if(PlayerInfo[playerid][pFines] < 1) return SCM(playerid, red, "У вас нет неоплаченых штрафов.");
                        new string[256];
                        format
                        (
                            string, sizeof(string), 
                            "{FFFFFF}\
                            Количество штрафов:\t{"cblue"}%d{FFFFFF}\n\
                            Общая сумма:\t\t\t{"cblue"}%d руб.{FFFFFF}\n\n\
                            Вы желаете оплатить все штрафы?",
                            PlayerInfo[playerid][pFines], PlayerInfo[playerid][pSumFines]
                        );
                        SPD
                        (
                            playerid, D_ATM_PAY_ALL_FINES, DIALOG_STYLE_MSGBOX,
                            !"{"cblue"}Оплата штрафов",
                            string,
                            !"Оплатить", !"Назад"
                        );
                    }
                    case 5:
                    {
                        if(PlayerInfo[playerid][pPhone] <= 0 || PlayerInfo[playerid][pPhoneNumber] <= 0) return SCM(playerid, red, "У вас нет телефона, либо сим-карты. Купите их в ближайшем 24/7.");
                        SPD
                        (
                            playerid, D_ATM_PAY_PHONE_CASH, DIALOG_STYLE_INPUT,
                            !"{"cblue"}Банкомат",
                            !"{FFFFFF}Укажите сумму, на коотрую вы хотите пополнить баланс телефона:",
                            !"Пополнить", !"Назад"
                        );
                    }
                }
            }
        }
        case D_ATM_PAY_FINE:
        {
            if(!response) return ShowAtmDialog(playerid);
            else
            {
                if(!IsNumeric(inputtext))
                {
                    SPD
                    (
                        playerid, D_ATM_PAY_FINE, DIALOG_STYLE_INPUT,
                        !"{"cblue"}Оплата штрафа:",
                        !"{"cblue"}Введите номер штрафа.\n\n\
                        Что бы узнать номер штрафа, введите: /tickets",
                        !"Далее", !"Назад"
                    );
                    return 1;
                }

                new sql[144];
                format(sql, sizeof(sql), "SELECT * FROM `fines` WHERE `account_id` = '%d' AND `fine_id` = '%d'", PlayerInfo[playerid][pID], strval(inputtext));
                mysql_tquery(connects, sql, "PaymentFine", "i", playerid);
            }
        }
        case D_ATM_PAY_PHONE_CASH:
        {
            if(!response) return ShowAtmDialog(playerid);
            else
            {
                if(PlayerInfo[playerid][pBCash] < strval(inputtext)) return SCM(playerid, red, !"На вашем банковском счету недостаточно средств.");

                if(!IsNumeric(inputtext))
                {
                    SPD
                    (
                        playerid, D_ATM_PAY_PHONE_CASH, DIALOG_STYLE_INPUT,
                        !"{"cblue"}Банкомат",
                        !"{FFFFFF}Укажите сумму, на коотрую вы хотите пополнить баланс телефона:",
                        !"Пополнить", !"Назад"
                    );  
                    return 1;                  
                }

                PlayerInfo[playerid][pPhoneCash] += strval(inputtext);
                GiveBankMoney(playerid, -strval(inputtext), "Пополнение баланса телефона");
                
                new string[144];
                format(string, sizeof(string), "Вы пополнили баланс телефона на %d руб.", strval(inputtext));
                SCM(playerid, blue, string);
                return SaveAccounts(playerid);
            }
        }
        case D_ATM_PAY_ALL_FINES:
        {
            if(!response) ShowAtmDialog(playerid);
            else
            {
                if(PlayerInfo[playerid][pCash] < PlayerInfo[playerid][pSumFines]) return SCM(playerid, red, !"У вас недостаточно средств.");

                GiveMoney(playerid, -PlayerInfo[playerid][pSumFines], "Оплата всех штрафов");
                PlayerInfo[playerid][pFines] = 0;
                PlayerInfo[playerid][pSumFines] = 0;

                SaveAccounts(playerid);

                new sql[144];
                format(sql, sizeof(sql), "DELETE FROM `fines` WHERE `account_id` = '%d'", PlayerInfo[playerid][pID]);
                mysql_tquery(connects, sql, "", "");

                return SCM(playerid, blue, !"Вы успешно оплатили все штрафы.");
            }
        }
        case D_PAYMENT_FINE:
        {
            if(!response)
            {
                DeletePVar(playerid, "fine_id");
                DeletePVar(playerid, "fine");

                SPD
                (
                    playerid, D_ATM_PAY_FINE, DIALOG_STYLE_INPUT,
                    !"{"cblue"}Оплата штрафа:",
                    !"{"cblue"}Введите номер штрафа.\n\n\
                    Что бы узнать номер штрафа, введите: /tickets",
                    !"Далее", !"Назад"
                );
                return 1;
            }
            else
            {
                new fine_id = GetPVarInt(playerid, "fine_id");
                new fine = GetPVarInt(playerid, "fine"); 

                if(PlayerInfo[playerid][pCash] < fine) return SCM(playerid, red, !"У вас недостаточно средств.");

                GiveMoney(playerid, -fine, "Оплата штрафа");
                PlayerInfo[playerid][pFines]--;
                PlayerInfo[playerid][pSumFines] -= fine;

                SaveAccounts(playerid);

                new sql[180];
                format(sql, sizeof(sql), "DELETE FROM `fines` WHERE `fine_id` = '%d'", fine_id);
                mysql_tquery(connects, sql, "", "");

                DeletePVar(playerid, "fine_id");
                DeletePVar(playerid, "fine");

                return SCM(playerid, blue, "Вы успешно оплатили штраф.");
            }
        }
    }
	#if	defined	atm__OnDialogResponse
		return atm__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse atm__OnDialogResponse
#if	defined	atm__OnDialogResponse
	forward atm__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics PaymentFine(playerid)
{
    static rows[2], fine_id, fined[MAX_PLAYER_NAME], fine, reason[40];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        fine_id = cache_get_field_content_int(0, "fine_id");
        fine = cache_get_field_content_int(0, "fine");
        cache_get_field_content(0, "fined", fined, connects, sizeof(fined));
        cache_get_field_content(0, "reason", reason, connects, sizeof(reason));

		SetPVarInt(playerid, "fine_id", fine_id);
		SetPVarInt(playerid, "fine", fine);

	    new fmt_dialog[180];
		format
		(
			fmt_dialog, sizeof fmt_dialog,
			"{FFFFFF}Штраф \t\t{"cblue"}№%d\n\n\
		    {FFFFFF}Выписан: \t\t{"cblue"}%s\n\
			{FFFFFF}Сумма: \t\t{"cblue"}%d рублей\n\
			{FFFFFF}Причина: \t\t{"cblue"}%s",
			fine_id,
			fined,
			fine,
			reason

		);

		ShowPlayerDialog
		(
			playerid, D_PAYMENT_FINE, DIALOG_STYLE_MSGBOX,
			"{"cblue"}Оплата штрафа:",
			fmt_dialog,
			"Оплатить", "Назад"
		);
    }
    else SCM(playerid, red, "Штраф не найден.");
    return 1;
}