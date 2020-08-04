publics Restart(playerid)
{
	new string[128];
	format(string, sizeof(string), "Внимание! Через %d минуты произойдет перезагрузка сервера!", restart_time);
	SCMTA(red, string);
	restart_time--;
	if(restart_time == 0)
	{
	    foreach(new i : Player)
	    {
	        SaveAccounts(i);
	    }
	    SCMTA(red, "Внимание! Происходит перезагрузка сервера!");
		SetTimer("Restart_", 5000, false);
	}
	return 1;
}
publics Restart_()
{
	foreach(new i: Player)
	{
	    SaveAccounts(i);
		if(GetPVarInt(i, "restart") != 1)
		{
	    	NewKick(i);
		}
	}
	return SendRconCommand("gmx");
}
stock Restart_Server(playerid)
{
	if(GetPVarInt(playerid, "restart") == 1)
	{
		return SetTimer("Restart_", 5000, false);
	}

	SCMTA(red, "Внимание! Через 5 минут произойдет перезагрузка сервера!");

	SetTimer("Restart", 60000, true);

	SetPVarInt(playerid, "restart", 1);

	return 1;
}

publics minuteupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);

	if(hour == 4 && minute == 0)
	{
	    SCMTA(red, "Внимание! Через 5 минут произойдёт техническая перезагрузка сервера!");
	}
	if(hour == 4 && minute == 1)
	{
	    SCMTA(red, "Внимание! Через 4 минут произойдёт техническая перезагрузка сервера!");
	}
	if(hour == 4 && minute == 2)
	{
	    SCMTA(red, "Внимание! Через 3 минут произойдёт техническая перезагрузка сервера!");
	}
	if(hour == 4 && minute == 3)
	{
	    SCMTA(red, "Внимание! Через 2 минут произойдёт техническая перезагрузка сервера!");
	}
	if(hour == 4 && minute == 4)
	{
	    SCMTA(red, "Внимание! Через 1 минут произойдёт техническая перезагрузка сервера!");
	}
	if(hour == 4 && minute == 5)
	{
	    SCMTA(red, "Внимание! Происходит техническая перезагрузка сервера!");
	    foreach(new i : Player)
	    {
	        SaveAccounts(i);
	        GameTextForAll("~r~SERVER IS RESTARTING", 9000, 5);
	        Kick(i);
	    }
	    SetTimer("TehRestart", 5000, false);
	}
    #if defined gmx__minuteupdate
        return gmx__minuteupdate();
    #else
        return 1;
    #endif
}
#if defined _ALS_minuteupdate
    #undef minuteupdate
#else
    #define _ALS_minuteupdate
#endif

#define minuteupdate gmx__minuteupdate
#if defined gmx__minuteupdate
    forward gmx__minuteupdate();
#endif

publics TehRestart()
{
    GameModeExit();
}

CMD:restart(playerid)
{
	if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
	return Restart_Server(playerid);
}