CMD:last(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][pVIP] < 1) return ShowCommandNotFound(playerid);
    
	new hour, minute, second, year, month, day, data[64];
	gettime(hour, minute, second);
	getdate(year, month, day);
	format(data, sizeof(data), "%0d.%02d.%d -- %d:%02d:%02d", day, month, year, hour, minute, second);
	strdel(PlayerInfo[playerid][pLastConnect], 0, 50);
	strmid(PlayerInfo[playerid][pLastConnect], data, 0, 50);

	strdel(PlayerInfo[playerid][pLastIP], 0, 16);
	strmid(PlayerInfo[playerid][pLastIP], PlayerInfo[playerid][pNewIp], 0, 16);
	
	new string[128];
	format(string, sizeof(string), "%s | %s", PlayerInfo[playerid][pLastIP], PlayerInfo[playerid][pLastConnect]);
	return SCM(playerid, grey, string);
}