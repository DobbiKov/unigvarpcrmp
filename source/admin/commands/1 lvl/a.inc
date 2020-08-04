CMD:a(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);
    if(sscanf(params, "s[100]", params[0])) return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: Используйте /a [текст]");
	
	stringer[0] = EOS;
	format(stringer, 150, "[A] %s %s[%d]: %s", GetRangAdmin[PlayerInfo[playerid][bAdmin]], PlayerInfo[playerid][pName], playerid, params[0]);
	SCMA(0x99CC00FF, stringer);
	return 1;
}