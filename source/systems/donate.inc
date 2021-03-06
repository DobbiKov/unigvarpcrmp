enum
	E_DONATE_DATE
{
	donate_name[70]
};

new const
	donate_list[9][E_DONATE_DATE] =
{
	{"��������� ������� � ����� (1 ��. = 500 ������)"},
	{"������� ��� (50. ��.)"},
	{"����� ��� �������������� (100. ��.)"},
	{"����� ������ (50 ��.)"},
	{"������� ����� (100. ��.)"},
	{"+1 EXP (10 ��.)"},
	{"+1 LvL (100 ��.)"},
	{"������ ������ (50 ��. = 1 ��. | 200 ��. = ���)"},
	{"VIP �������"}
};

CMD:donate(playerid)
{
	new string[1024], str[128];
	strcat(string, "{"cblue"}����� {ffffff}- ��� ���� ������������� ������ ������� ��������� ��������\n�� �������� � ����������� �������� � ����������. �� ��� �� ��������� �������.\n\n");
	strcat(string, "{"cblue"}1 ���������� ����� = 1 �������\n\n");
	strcat(string, "{FFFFFF}�� ������� ����� ����������� �� ������� �������� ��������� ������, ��������, �����������,\n");
	strcat(string, "� ����� ���������� � ������� ������ {"cblue"}(1 ������ = 500 ������� ������)\n\n\n");

	strcat(string, "{"cred"}��� �� �������� ������� �����:\n\n");
	strcat(string, "{"cblue"}1) {FFFFFF}����� �� ���� {"cblue"}unigva-rp.ru/donate\n");
	strcat(string, "{"cblue"}2) {FFFFFF}������� ������, �� ������� �� �������\n");
	strcat(string, "{"cblue"}3) {FFFFFF}������� ���� ������� � �������� ����� ���������\n");
	strcat(string, "{"cblue"}4) {FFFFFF}������� ������ ������ (QIWI, WebMoney, ������.������, SMS, ���������� ����� ������ �����)\n");
	strcat(string, "{"cblue"}5) {FFFFFF}����� ����� �������� ������� {"cblue"}/donate\n\n");
	format(str, sizeof(str), "{ffffff}��� �������:\t\t\t\t{"cblue"}%s\n", PlayerInfo[playerid][pName]);
	strcat(string, str);
	format(str, sizeof(str), "{ffffff}����� ������ ��������:\t\t{"cblue"}%d\n", PlayerInfo[playerid][pID]);
	strcat(string, str);
	format(str, sizeof(str), "{ffffff}���������� ����� ��������:\t{"cblue"}%d", PlayerInfo[playerid][pDonate]);
	strcat(string, str);
	SPD(playerid, D_DONATE, DIALOG_STYLE_MSGBOX, "{"cblue"}�������������� ��������", string, "�����", "������");
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_DONATE:
		{
			if(!response) return 1;
			else
			{
				new fmt_dialog[528], string[128];
				for(new i = 0; i < 8; i++)
				{
					format(string, sizeof(string), "{"cblue"}%d. {ffffff}%s\n", i+1, donate_list[i][donate_name]);
					strcat(fmt_dialog, string);
				}
				SPD(playerid, D_DONATE_LIST, DIALOG_STYLE_LIST, "{"cblue"}�������������� ������", fmt_dialog, "�����", "������");
			}
		}
	}
	#if	defined	donate__OnDialogResponse
		return donate__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse donate__OnDialogResponse
#if	defined	donate__OnDialogResponse
	forward donate__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif