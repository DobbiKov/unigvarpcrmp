CMD:setstat(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);

    extract params -> new to_player, what, count; else
	{
	    SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /setstat [id игрока] [номер] [Значение]");
	    SCM(playerid, white, "[номер]: 1 - деньги; 2 - денег в банке; 3 - ЛВЛ дальнобойщика; 4 - ЛВЛ;");
 		return 1;
	}
	
    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
    
    switch(what)
    {
		case 1:
		{
			ResetPlayerMoney(to_player);
			PlayerInfo[to_player][pCash] = 0;
			GiveMoney(to_player, count, "/setstat");
			new string[128];
			format(string, sizeof(string), "Вы установили %d денег игроку %s[%d]", count, PlayerInfo[to_player][pName], to_player);
			SCM(playerid, white, string);
			
			format(string, sizeof(string), "Администратор %s[%d] установил вам %d рублей", PlayerInfo[playerid][pName], playerid, count);
			SCM(to_player, white, string);
		}
		case 2:
		{
			PlayerInfo[to_player][pBCash] = count;
			new string[128];
			format(string, sizeof(string), "Вы установили %d денег в банке игроку %s[%d]", count, PlayerInfo[to_player][pName], to_player);
			SCM(playerid, white, string);

			format(string, sizeof(string), "Администратор %s[%d] установил вам %d рублей в банке", PlayerInfo[playerid][pName], playerid, count);
			SCM(to_player, white, string);
		}
		case 3:
		{
			PlayerInfo[to_player][pTruckLVL] = count;
			new string[128];
			format(string, sizeof(string), "Вы установили %d LVL дальнобойщика игроку %s[%d]", count, PlayerInfo[to_player][pName], to_player);
			SCM(playerid, white, string);

			format(string, sizeof(string), "Администратор %s[%d] установил вам %d уровень дальнобойщика", PlayerInfo[playerid][pName], playerid, count);
			SCM(to_player, white, string);
		}
		case 4:
		{
			PlayerInfo[to_player][pLVL] = count;
			new string[128];
			format(string, sizeof(string), "Вы установили %d LVL игроку %s[%d]", count, PlayerInfo[to_player][pName], to_player);
			SCM(playerid, white, string);

			format(string, sizeof(string), "Администратор %s[%d] установил вам %d уровень", PlayerInfo[playerid][pName], playerid, count);
			SCM(to_player, white, string);
		}
		default:
		{
  			SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /setstat [id игрока] [номер] [Значение]");
		    SCM(playerid, blue, "[номер]: 1 - деньги; 2 - денег в банке; 3 - ЛВЛ дальнобойщика; 4 - ЛВЛ;");
	 		return 1;
		}
    }
    SaveAccounts(playerid);
    SaveAccounts(to_player);
	return 1;
}