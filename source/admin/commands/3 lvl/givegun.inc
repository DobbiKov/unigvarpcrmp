CMD:givegun(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

	extract params -> new to_player, weaponid, ammunition; else return SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /givegun [id игрока] [weaponid] [патроны]");
	new string[120+MAX_PLAYER_NAME*2];

	if(!(1 <= weaponid <= 50)) return SCM(playerid, 0xCECECEFF, "Weaponid от 1 до 46");
	else if(!(1 <= ammunition <= 10000)) return SCM(playerid, 0xCECECEFF, "Патроны от 1 до 1000");

	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	if(PlayerInfo[playerid][bAdmin] < 6)
	{
	    format(string, sizeof(string), "{"cgrey"}[A]: {"cwhite"}%s[%d] выдал оружие %s[%d] игроку %s[%d]", PlayerInfo[playerid][pName], playerid, gun_name[weaponid], weaponid, PlayerInfo[to_player][pName], to_player);
	    SCMA(grey, string);
	}
	format(string, sizeof(string), "Вы выдали оружие %s[%d] игроку %s[%d]", gun_name[weaponid], weaponid, PlayerInfo[to_player][pName], to_player);
	SCM(playerid, white, string);
    format(string, sizeof(string), "{"cwhite"}Администратор %s выдал вам оружие %s", PlayerInfo[playerid][pName], gun_name[weaponid]);
    SCM(to_player, grey, string);

	GivePlayerWeaponAC(to_player, weaponid, ammunition);

	return 1;
}