CMD:pass(playerid, params[])
{
    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /pass [ID игрока]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);

	new fmt_msg[128];

	format(fmt_msg, sizeof fmt_msg, "Вы показали свой паспорт %s [%d]", PlayerInfo[to_player][pName], to_player);
	SCM(playerid, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "__________[ ПАСПОРТ №%d ]__________", PlayerInfo[playerid][pID]);
	SCM(to_player, -1, fmt_msg);
	SCM(to_player, -1, "");
	
	format(fmt_msg, sizeof fmt_msg, "Имя Фамилия: %s | Годы проживания: %d", PlayerInfo[playerid][pName], PlayerInfo[playerid][pLVL]);
	SCM(to_player, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "Телефонный номер: %d | Уровень розыска: %d", PlayerInfo[playerid][pPhoneNumber], PlayerInfo[playerid][pWANTED]);
	SCM(to_player, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "Организация: %s | Должность: %s", (PlayerInfo[playerid][pMember] == 0) ? ("Нет") : (GetMember[PlayerInfo[playerid][pMember]]), (PlayerInfo[playerid][pJob] >= 1) ? (jobs_name[PlayerInfo[playerid][pJob]]) : (PlayerRank[PlayerInfo[playerid][pMember]][PlayerInfo[playerid][pRang]]));
	SCM(to_player, -1, fmt_msg);
	
	format(fmt_msg, sizeof fmt_msg, "Военный билет: %s", PlayerInfo[playerid][pVoen] == 1 ? ("Есть") : ("Нет"));
	SCM(to_player, -1, fmt_msg);

	format(fmt_msg, sizeof fmt_msg, "Законопослушность: %d", PlayerInfo[playerid][pZakon]);
	SCM(to_player, -1, fmt_msg);
	SCM(to_player, -1, "_______________________________________");
    return 1;
}