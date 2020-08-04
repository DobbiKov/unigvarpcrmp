CMD:yhelp(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
    SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}UNIGVA | YHELP", "\
	{"cblue"}/up, /down, /left, /right, /before, /after {FFFFFF}- телепортировать на небольшое расстояние\n\
	{"cblue"}/tp {FFFFFF}- телепорт по всей карте\n\
	{"cblue"}/hp {FFFFFF}- выдать себе 100 хп\n\
	{"cblue"}/arm {FFFFFF}- выдать себе 100 брони\n\
	{"cblue"}/getskin {FFFFFF}- выдать себе временный скин\n\
	{"cblue"}/veh {FFFFFF}- создать транспорт\n\
	{"cblue"}/delveh {FFFFFF}- удалить транспорт\n\
	{"cblue"}/fixveh {FFFFFF}- отремонтировать транспорт\n\
	{"cblue"}/y - {FFFFFF}- связь ютуберов и администраторов\n\
	{"cblue"}/youtubers {FFFFFF}- ютуберы онлайн\
	", "Закрыть", "");
	return 1;
}