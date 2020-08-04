CMD:admins(playerid)
{
	if(PlayerInfo[playerid][bAdmin] < 1 && PlayerInfo[playerid][pVIP] < 1) return ShowCommandNotFound(playerid);
	return ShowAdminsOnline(playerid);
}




stock ShowAdminsOnline(playerid)
{
	SCM(playerid, 0x5ac310FF, "Администрация онлайн:");

	new fmt_msg[85], afk[25], spec[20];

	foreach(new i: Player)
	{
        if(PlayerInfo[i][bAdmin] == 0) continue;
        {
			if(1 <= PlayerInfo[i][bAdmin] <= 5)
			{
				format(fmt_msg, sizeof fmt_msg, "%s[%d] (%d lvl)", PlayerInfo[i][pName], i, PlayerInfo[i][bAdmin]);

				if(IsPlayerAfk(i))
					format(afk, sizeof afk, " - {FF0000}AFK [%02d:%02d]", (floatround(player_afk_time[i] / 60) % 60), player_afk_time[i] % 60), strcat(fmt_msg, afk);

				if(GetPlayerState(i) == PLAYER_STATE_SPECTATING)
		        {
		            format(spec, sizeof spec, "{148f3d} > /sp %d", SpID[i]), strcat(fmt_msg, spec);
				}
				SCM(playerid, yellow, fmt_msg);
			}
		}
	}
	return 1;
}