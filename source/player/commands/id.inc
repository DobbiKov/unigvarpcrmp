CMD:id(playerid, params[])
{
	new Name[24], ids = 0;
	if(sscanf(params, "s[24]",Name)) return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /id [NickName]");
	SCM(playerid, blue, "Игроки онлайн:");
	if(IsNumeric(Name))
	if(IsPlayerConnected(strval(Name)) && PlayerInfo[strval(Name)][bAdmin] < 6)
	{
	    stringer[0] = EOS;
	    format(stringer, 100, "%s [%d]", PlayerInfo[strval(Name)][pName], strval(Name));
		return SCM(playerid, white, stringer); 
	}
	foreach(new i : Player)
	{
		if(PlayerInfo[i][bAdmin] >= 6) continue;
		if(strfind(PlayerInfo[i][pName],Name,true) == -1) continue;
		if(ids > 8) break;
		ids++;
		stringer[0] = EOS;
		format(stringer, 100, "%s [%i]",PlayerInfo[i][pName],i);
		SCM(playerid, white, stringer);
	}
	if(!ids) return SCM(playerid, lightred, "Совпадений не найдено.");
	return 1;
}