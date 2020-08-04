CMD:search(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /search [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID.");

    new fmt_dialog[1024], string[144];
    format(string, sizeof(string), "обыскал(-а) %s", PlayerInfo[to_player][pName]);
    cmd::me(playerid, string);

    format
    (
        string, sizeof(string), 
        "\
        {"cblue"}%s[%d]\n\n\
        {FFFFFF}Наркотики: {"cblue"}%d гр.\n\
        {FFFFFF}Металл: {"cblue"}%d кг.\n\
        {FFFFFF}Патроны: {"cblue"}%d пт.\n\n\
        ",
        PlayerInfo[to_player][pName],
        to_player,
        PlayerInfo[to_player][pDrugs],
        PlayerInfo[to_player][pMetall],
        PlayerInfo[to_player][pPatr]
    );
    strcat(fmt_dialog, string);

	new weapons[13][2];
	for(new i = 0; i != 12; i ++)
	{
		GetPlayerWeaponData(to_player, i, weapons[i][0], weapons[i][1]);
		if(weapons[i][0] != 0)
		{
			format(string, 70, "\nОружие:\t\t%s (%d)\nПатроны:\t\t%d", gun_name[ weapons[i][0] ],weapons[i][0],weapons[i][1]);
			strcat(fmt_dialog, string);
		}
	}
    return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Обыск игрока", fmt_dialog, "Закрыть", "");
}