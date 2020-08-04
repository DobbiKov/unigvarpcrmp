enum
	E_DONATE_DATE
{
	donate_name[70]
};

new const
	donate_list[9][E_DONATE_DATE] =
{
	{"Перевести кредиты в рубли (1 кр. = 500 рублей)"},
	{"Сменить имя (50. кр.)"},
	{"Снять все предупреждения (100. кр.)"},
	{"Снять розыск (50 кр.)"},
	{"Военный билет (100. кр.)"},
	{"+1 EXP (10 кр.)"},
	{"+1 LvL (100 кр.)"},
	{"Навыки оружия (50 кр. = 1 шт. | 200 кр. = все)"},
	{"VIP аккаунт"}
};

CMD:donate(playerid)
{
	new string[1024], str[128];
	strcat(string, "{"cblue"}Донат {ffffff}- это Ваше пожертвование нашему проекту реальными деньгами\nна развитие и поддержание серверов и обновлений. За это вы получаете кредиты.\n\n");
	strcat(string, "{"cblue"}1 российский рубль = 1 кредиту\n\n");
	strcat(string, "{FFFFFF}За кредиты можно приобретать на игровых серверах различные услуги, ценности, возможности,\n");
	strcat(string, "а также переводить в игровые деньги {"cblue"}(1 кредит = 500 игровых рублей)\n\n\n");

	strcat(string, "{"cred"}Что бы получить кредиты нужно:\n\n");
	strcat(string, "{"cblue"}1) {FFFFFF}Зайти на сайт {"cblue"}unigva-rp.ru/donate\n");
	strcat(string, "{"cblue"}2) {FFFFFF}Выбрать сервер, на котором Вы играете\n");
	strcat(string, "{"cblue"}3) {FFFFFF}Указать свой никнэйм и желаемую сумму поплнения\n");
	strcat(string, "{"cblue"}4) {FFFFFF}Выбрать способ оплаты (QIWI, WebMoney, Яндекс.Деньги, SMS, банковскую карту любого банка)\n");
	strcat(string, "{"cblue"}5) {FFFFFF}После этого написать команду {"cblue"}/donate\n\n");
	format(str, sizeof(str), "{ffffff}Ваш никнэйм:\t\t\t\t{"cblue"}%s\n", PlayerInfo[playerid][pName]);
	strcat(string, str);
	format(str, sizeof(str), "{ffffff}Номер вашего аккаунта:\t\t{"cblue"}%d\n", PlayerInfo[playerid][pID]);
	strcat(string, str);
	format(str, sizeof(str), "{ffffff}Количество ваших кредитов:\t{"cblue"}%d", PlayerInfo[playerid][pDonate]);
	strcat(string, str);
	SPD(playerid, D_DONATE, DIALOG_STYLE_MSGBOX, "{"cblue"}Дополнительные средства", string, "Далее", "Отмена");
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
				SPD(playerid, D_DONATE_LIST, DIALOG_STYLE_LIST, "{"cblue"}Дополнительные услуги", fmt_dialog, "Далее", "Отмена");
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