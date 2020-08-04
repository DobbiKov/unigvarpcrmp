CMD:y(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
	
	extract params -> new string: mess[200]; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /y [сообщение]");
	
	foreach(new i : Player)
	{
	    if(PlayerInfo[i][bAdmin] > 0 || PlayerInfo[i][bYoutube] > 0)
	    {
	        new string[256];
	        format(string, sizeof(string), "[%s] %s[%d]: %s", ((PlayerInfo[playerid][bAdmin] > 0) ? ("A") : ("Y")), PlayerInfo[playerid][pName], playerid, mess);
	        SCM(i, lightred, string);
	    }
	}
	return 1;
}