CMD:caps(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, blue, !"[Подсказка]: {FFFFFF}Используйте /caps [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	if(PlayerInfo[to_player][pMute] > 0) return SCM(playerid, red, "У игрока уже имееться блокировка чата!");

	PlayerInfo[to_player][pMute] = caps*60;
	PlayerInfo[playerid][bMute]++;
	SaveAccounts(to_player);
	SaveAccounts(playerid);

	new fmt_query[256];

	format(fmt_query, sizeof fmt_query, "Администратор %s наказал игрока %s. Причина: CAPS LOCK (CAPS)", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName]);
	SCMTA(0xFF4530FF, fmt_query);

	format(fmt_query, sizeof fmt_query, "[A] %s[%d] поставил затычку %s[%d] на %d минут (caps)", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, caps);
	SCMA(grey, fmt_query);

	SCM(to_player, grey, "Вам поставили затычку за нарушение правил сервера. Посмотреть время до выхода: /time");

	new string[256], sql_str[256];
	new day, month, year, hour, minute, second;
	getdate(day, month, year);
	gettime(hour, minute, second);
	format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

	mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', 'MG', 'mute')", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], string, caps);
	mysql_tquery(connects, sql_str, "", "");

    new sttr[1024];
    for(new i; i < 4; i++) strcat(sttr, RulesCAPS[i]);
    SPD(to_player, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Блокировка чата | CAPS LOCK", sttr, "Закрыть", "");

	return 1;
}