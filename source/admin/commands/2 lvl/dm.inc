CMD:dm(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	extract params -> new to_player; else return SCM(playerid, yellow, !"[Подсказка]: {FFFFFF}Используйте /dm [ID игрока]");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
	if(PlayerInfo[to_player][pJail] > 0) return SCM(playerid, red, "Игрок уже сидит в деморгане!");

	PlayerInfo[to_player][pJail] = dm*60;
	PlayerInfo[playerid][bJail]++;
	SaveAccounts(to_player);
	SaveAccounts(playerid);

	new fmt_query[256];

	format(fmt_query, sizeof fmt_query, "Администратор %s наказал игрока %s. Причина: DM (DeathMatch)", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName]);
	SCMTA(0xFF4530FF, fmt_query);

	format(fmt_query, sizeof fmt_query, "[A] %s[%d] посадил в деморган %s[%d] на %d минут (DM)", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, dm);
	SCMA(grey, fmt_query);

	SCM(to_player, grey, "Вы были посажены в деморган за нарушение правил. Посмотреть время до выхода: /time");

	new string[256], sql_str[256];
	new day, month, year, hour, minute, second;
	getdate(day, month, year);
	gettime(hour, minute, second);
	format(string, sizeof(string), "%d/%d/%d - %d:%d:%d", day, month, year, hour, minute, second);

	mysql_format(connects, sql_str, sizeof(sql_str), "INSERT INTO `nakazania` (`AdminName`, `Name`, `Date`, `Time`, `Reason`, `Type`) VALUES ('%s', '%s', '%s', '%d', 'DM', 'jail')", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], string, dm);
	mysql_tquery(connects, sql_str, "", "");

    new sttr[512];
    for(new i; i < 5; i++) strcat(sttr, RulesDM[i]);
    SPD(to_player, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Деморган | DM", sttr, "Закрыть", "");

	return PlayerPutInDemorgan(to_player);
}