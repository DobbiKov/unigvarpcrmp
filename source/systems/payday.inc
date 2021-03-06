publics PayDay()
{
	new hour, minute;
	gettime(hour, minute);
	SetWorldTime(hour);

	foreach(new i: Player)
	{
	    PayDayForPlayer(i);
	}
	return 1;
}

publics minuteupdate()
{
	new hour, minute, second;
	gettime(hour, minute, second);

	if(minute == 0)
	{
	    if(be_pay_day == false)
	    {
		    PayDay();
			be_pay_day = true;
 		}
	}
	if(minute == 1)
	{
	    if(be_pay_day == true)
	    {
			be_pay_day = false;
		}
	}
    #if defined payday__minuteupdate
        return payday__minuteupdate();
    #else
        return 1;
    #endif
}
#if defined _ALS_minuteupdate
    #undef minuteupdate
#else
    #define _ALS_minuteupdate
#endif

#define minuteupdate payday__minuteupdate
#if defined payday__minuteupdate
    forward payday__minuteupdate();
#endif

CMD:payday(playerid)
{
 	if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);
	return PayDay();
}

stock PayDayForPlayer(i)
{
	new hour, minute, second;
	gettime(hour, minute, second);

	new fmt_text[128];

	format(fmt_text, sizeof fmt_text, "������� �����: {3399FF}%02d:00", hour);
	SCM(i, -1, fmt_text);

	if(IsPlayerAfk(i)) return 1;
	
	if(PlayerInfo[i][pLogin] != true || !IsPlayerConnected(i)) return 1;
	PlayerInfo[i][pExp] += (1*XDay);

	SCM(i, -1, "   ���������� ���");
	SCM(i, -1, "______________________");
	SCM(i, -1, " ");

	new wage;
	if(PlayerInfo[i][pMember] > 0 && PlayerInfo[i][pRang] > 0) wage = pay_orgs[ PlayerInfo[i][pMember] ][ PlayerInfo[i][pRang] ];
	else wage = 0;

	format(fmt_text, sizeof fmt_text, "��������: {66CC00}%d ���", (wage*XDay));
	SCM(i, -1, fmt_text);

	GiveBankMoney(i, wage*XDay, "�������� (PayDay)");
	
	if(PlayerInfo[i][pZakon] < 100) PlayerInfo[i][pZakon]++;
	if(PlayerInfo[i][pZakon] >= 100) PlayerInfo[i][pZakon] = 100;

	if(PlayerInfo[i][bAdmin] > 0)
	{
		new adm_zp = AdminPays[PlayerInfo[i][bAdmin]];
		GiveBankMoney(i, adm_zp, "����� �������� (PayDay)");
		format(fmt_text, sizeof fmt_text, "����� ��������: {66CC00}%d ���", adm_zp);
		SCM(i, -1, fmt_text);
	}

	format(fmt_text, sizeof fmt_text, "������� ������ �����: {%s}%d ���", PlayerInfo[i][pBCash] > 0 ? ("00CC00") : ("FF3300"),  PlayerInfo[i][pBCash]);
	SCM(i, -1, fmt_text);

	if(PlayerInfo[i][pMember] == TEAM_VDV && PlayerInfo[i][pVoen] < 1 && PlayerInfo[i][pRang] < 5)
	{
		PlayerInfo[i][pVoenEXP]++;
		if(PlayerInfo[i][pVoenEXP] >= 6) 
		{
			PlayerInfo[i][pRang]++;
			PlayerInfo[i][pVoenEXP] = 0;
			SCM(i, green, "�����������! ��� ���� � ����������� �������.");
			if(PlayerInfo[i][pRang] >= 5)
			{
				PlayerInfo[i][pVoen] = 1;
				SCM(i, green, "�����������! �� �������� ������� �����.");
			}
		}

	}

	if(PlayerInfo[i][pExp] >= (PlayerInfo[i][pLVL] * 4))
	{
		PlayerInfo[i][pLVL]++;
		PlayerInfo[i][pExp] = 0;
		SetPlayerScore(i, PlayerInfo[i][pLVL]);
		SCM(i, green, !"�����������! ��� ������� �������.");
	}
	if(PlayerInfo[i][pLVL] == 5 && PlayerInfo[i][pExp] == 0)
	{
		if(strlen(PlayerInfo[i][pReferal]) > 5)
		{
			static const fmt_query[] = "INSERT INTO `referals` (`login`, `login_invited`) VALUES ('%s', '%s')";
			new query[sizeof(fmt_query)+(-2+MAX_PLAYER_NAME)];
			format(query, sizeof(query), fmt_query, PlayerInfo[i][pReferal], PlayerInfo[i][pName]);
			mysql_tquery(connects, query, "", "");

			PlayerInfo[i][pBCash] += 50000;
			SCM(i, blue, !"�����������! �� �������� 5 ������, ������� �� � ��� ������� �������� �� 50.000!");

			if(IsPlayerConnected(GetPlayerID(PlayerInfo[i][pReferal])))
			{
				PlayerInfo[GetPlayerID(PlayerInfo[i][pReferal])][pBCash] += 50000;
				stringer[0] = EOS;
				format(stringer,512, "UPDATE `accounts` SET `pBCash` = '%d' WHERE `pName` = '%s'", PlayerInfo[GetPlayerID(PlayerInfo[i][pReferal])][pBCash], PlayerInfo[GetPlayerID(PlayerInfo[i][pReferal])][pName]);
				mysql_tquery(connects, stringer, "", "");

				SCM(GetPlayerID(PlayerInfo[i][pReferal]), blue, !"�����������! ��� ������� ������ 5 ������ � �� � �� �������� �� 50000!");
			}
			else
			{
				new mysqlstr[144];
				mysql_format(connects,mysqlstr, sizeof(mysqlstr),"SELECT * FROM `accounts` WHERE `pName` = '%s'", PlayerInfo[i][pReferal]);
				mysql_function_query(connects, mysqlstr, true, "PayDayReferal","ds", PlayerInfo[i][pReferal]);
			}
		}
	}

	SCM(i, -1, "______________________");


	SaveAccounts(i);
	PlayerPlaySound(i, 17803, 0.0, 0.0, 0.0);

	return 1;
}