CMD:weap(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[�����������]: {FFFFFF}����������� /weap [ID ������]");
    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	new strings[1000],strin[70],strs[100];
	new weapons[13][2];
	format(strs, 100, "{"cblue"}�����:\t\t\t%s{FFFFFF}", PlayerInfo[to_player][pName]);
	strcat(strings, strs);
	for(new i = 0; i != 12; i ++)
	{
		GetPlayerWeaponData(to_player, i, weapons[i][0], weapons[i][1]);
		if(weapons[i][0] != 0)
		{
			format(strin,70,"\n\n������:\t\t%s (%d)\n�������:\t\t%d", gun_name[ weapons[i][0] ],weapons[i][0],weapons[i][1]);
			strcat(strings,strin);
		}
	}
	SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}������ ������", strings, "�������", "");
    return 1;
}