CMD:mute(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	extract params -> new to_player, time, string: reason[80]; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /mute [ID игрока] [время] [причину]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	if(!strlen(reason)) return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /mute [ID игрока] [минуты] [причину]");

	if( time < 1 ||  time > 280 ) return SCM(playerid, blue, "[A]: Время должно быть не больше 280 и не меньше 1!");

	if(PlayerInfo[to_player][pMute] > 0) return SCM(playerid, red, "У игрока уже стоит затычка.");

	PlayerInfo[to_player][pMute] = time*60;
	PlayerInfo[playerid][bMute]++;
	SaveAccounts(to_player);
	SaveAccounts(playerid);

	new fmt_query[256];

	format(fmt_query, sizeof fmt_query, "Администратор %s поставил затычку %s на %d минут. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], time, reason);
	SCMTA(0xFF4530FF, fmt_query);

	format(fmt_query, sizeof fmt_query, "[A] %s[%d] поставил затычку %s[%d] на %d минут (%s)", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, time, reason);
	SCMA(grey, fmt_query);

	SCM(to_player, grey, "Вам поставили затычку за нарушение правил сервера. Посмотреть время до выхода: /time");

	new string[256], sql_str[256];
	new day, month, year, hour, minute, second;
	getdate(day, month, year);
	gettime(hour, minute, second);
	format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

	mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', '%s', 'mute')", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], string, time, reason);
	mysql_tquery(connects, sql_str, "", "");

	return 1;
}