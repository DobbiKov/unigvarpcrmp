CMD:youtubers(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
    
	SCM(playerid, 0x5ac310FF, "ётуберы онлайн:");

	new fmt_msg[85], afk[25];

	foreach(new i: Player)
	{
        if(PlayerInfo[i][bYoutube] > 0)
        {
			if(PlayerInfo[i][bAdmin] <= 5)
			{
				format(fmt_msg, sizeof fmt_msg, "%s[%d] (%d lvl)", PlayerInfo[i][pName], i, PlayerInfo[i][pLVL]);

				if(IsPlayerAfk(i))
					format(afk, sizeof afk, " - {FF0000}AFK [%02d:%02d]", (floatround(player_afk_time[i] / 60) % 60), player_afk_time[i] % 60), strcat(fmt_msg, afk);
				SCM(playerid, yellow, fmt_msg);
			}
		}
	}
	
    return 1;
}