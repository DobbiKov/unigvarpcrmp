ALTX:time("/t");
CMD:time(playerid)
{
	new h,m,s;
	new year,month,day;
    stringer[0] = EOS;
	getdate(year, month, day);
	gettime(h,m,s);

	format(stringer,148,"~w~%02d:%02d:%02d~n~~b~%d-%s%d-%s%d~n~~b~SERVER 01",h,m,s,day, ((month < 10) ? ("0") : ("")), month, (year < 10) ? ("0") : (""), year);
	GameTextForPlayer(playerid,stringer,5000,1);

	new fmt_msg[256];
	if(PlayerInfo[playerid][pMute] > 0)
	{
		format(fmt_msg, sizeof fmt_msg, "Время до разблокировки чата: %d:%02d.", floatround(PlayerInfo[playerid][pMute] / 60) % 60, (PlayerInfo[playerid][pMute] % 60));
		SendClientMessage(playerid, 0x66CC00FF, fmt_msg);
	}
	if(PlayerInfo[playerid][pJail] > 0)
	{
		format(fmt_msg, sizeof fmt_msg, "Время до выхода из деморгана: %d:%02d.", floatround(PlayerInfo[playerid][pJail] / 60) % 60, (PlayerInfo[playerid][pJail] % 60));
		SendClientMessage(playerid, 0x66CC00FF, fmt_msg);
	}
	if(PlayerInfo[playerid][pKPZ] > 0)
	{
		format(fmt_msg, sizeof fmt_msg, "Время до выхода из КПЗ: %d:%02d.", floatround(PlayerInfo[playerid][pKPZ] / 60) % 60, (PlayerInfo[playerid][pKPZ] % 60));
		SendClientMessage(playerid, 0x66CC00FF, fmt_msg);
	}
	return 1;
}