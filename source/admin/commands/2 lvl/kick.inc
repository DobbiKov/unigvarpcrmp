CMD:kick(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

	if(sscanf(params, "ds[64]", params[0], params[1])) return SCM(playerid, white, "{"cblue"}• [Подсказка]{"cwhite"}: Используйте /kick [playerid] [текст]");

	if(!IsPlayerConnected(params[0])) return PlayerOffLine(playerid);

	if(PlayerInfo[params[0]][bAdmin] > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Администратор не может быть кикнут.");

	stringer[0] = EOS;
	format(stringer, 164, "Администратор %s кикнул игрока %s. Причина: %s", PlayerInfo[playerid][pName],PlayerInfo[params[0]][pName],params[1]);
	SCMTA(0xFF4530FF, stringer);

	NewKick(params[0]);

	return 1;
}