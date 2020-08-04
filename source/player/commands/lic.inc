CMD:lic(playerid, params[])
{
    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /lic [ID игрока]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);

	new fmt_msg[128];

	format(fmt_msg, sizeof fmt_msg, "Вы показали свои лицензии %s [%d]", PlayerInfo[to_player][pName], to_player);
	SCM(playerid, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "___________[ ЛИЦЕНЗИИ ]___________");
	SCM(to_player, -1, fmt_msg);
	SCM(to_player, -1, "");
	
	format(fmt_msg, sizeof fmt_msg, "Имя Фамилия: %s", PlayerInfo[playerid][pName]);
	SCM(to_player, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "Лицензия категории A: %s | Лицензия категории B: %s", PlayerInfo[playerid][pLicA] == 1 ? ("есть") : ("нет"), PlayerInfo[playerid][pLicB] == 1 ? ("есть") : ("нет"));
	SCM(to_player, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "Лицензия категории C: %s | Лицензия категории D: %s", PlayerInfo[playerid][pLicC] == 1 ? ("есть") : ("нет"), PlayerInfo[playerid][pLicD] == 1 ? ("есть") : ("нет"));
	SCM(to_player, -1, fmt_msg);

	format(fmt_msg, sizeof fmt_msg, "Лицензия на бизнесс: %s | Лицензия полёты: %s", PlayerInfo[playerid][pLicBiz] == 1 ? ("есть") : ("нет"), PlayerInfo[playerid][pLicFly] == 1 ? ("есть") : ("нет"));
	SCM(to_player, -1, fmt_msg);

	format(fmt_msg, sizeof fmt_msg, "Лицензия на оружие: %s", PlayerInfo[playerid][pLicGun] == 1 ? ("есть") : ("нет"));
	SCM(to_player, -1, fmt_msg);
	
	SCM(to_player, -1, "_______________________________________");
    return 1;
}