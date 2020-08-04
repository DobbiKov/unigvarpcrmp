CMD:find(playerid)
{
	if(PlayerInfo[playerid][pMember] == 0) return YouCannotUseThisFunc(playerid);
	new full, string[150], string_dialogue[2048], text[20];
    strcat(string_dialogue, "{"cblue"}ID\tУровень\tТелефон\tРанг\tИмя\n\n");
	foreach(new i: Player)
	{
		if(PlayerInfo[i][pLogin] == false || PlayerInfo[i][bAdmin] || !IsPlayerConnected(i)) continue;
		if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember])
		{
		    if(PlayerInfo[i][pPhoneNumber] <= 1) format(text, sizeof(text), "None\t\t");
			else format(text, sizeof(text), "%i\t\t", PlayerInfo[i][pPhoneNumber]);
		    format(string, sizeof(string),"{FFFFFF}%i\t%i\t\t%s%i\t%s\n", i, PlayerInfo[i][pLVL], text, PlayerInfo[i][pRang], PlayerInfo[i][pName]);
			strcat(string_dialogue, string);
			full++;
		}
	}
    format(string, sizeof(string), "{FFFFFF}Всего членов организации онлайн: {"cblue"}%d", full);
    strcat(string_dialogue, string);

	ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Члены организации онлайн", string_dialogue, "Закрыть", "");
	return 1;
}