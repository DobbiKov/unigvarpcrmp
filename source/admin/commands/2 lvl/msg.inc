CMD:msg(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);
    if(sscanf(params, "s[100]", params[0])) return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: Используйте /msg [текст]");
	stringer[0] = EOS;
	format(stringer, 150, "Администратор %s: %s", PlayerInfo[playerid][pName], params[0]);
	SCMTA(yellow, stringer);
	return 1;
}