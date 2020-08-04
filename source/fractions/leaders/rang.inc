CMD:rang(playerid,params[])
{
	if(PlayerInfo[playerid][pMember] == TEAM_NONE || PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);
		
    extract params -> new to_player, string: rang[2]; else return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /rang [ID игрока] [+/-]");
		
	if(playerid == to_player)
		return SCM(playerid, red, "Вы указали свой ID!");
		
 	if(PlayerInfo[playerid][pMember] != PlayerInfo[to_player][pMember]) return SCM(playerid, red, "Игрок не является членом Вашей организации!");
	if(PlayerInfo[playerid][pMember] == TEAM_VDV && PlayerInfo[to_player][pVoen] < 1) return SCM(playerid, red, "У игрока нет военного билета!");
	
    switch(rang[0])
    {
		case '+':
		{
			if(PlayerInfo[to_player][pRang] >= (PlayerInfo[playerid][pRang] - 1))
				return SCM(playerid, red, "Не меньше 1 и не больше 9!");

	        PlayerInfo[to_player][pRang]++;
	        
			new string[128];
			format(string, sizeof(string), "Вы повысили %s[%d] до %s (%d)", PlayerInfo[to_player][pName], to_player, PlayerRank[ PlayerInfo[to_player][pMember] ][ PlayerInfo[to_player][pRang] ], PlayerInfo[to_player][pRang]);
			SCM(playerid, blue, string);
	        
			format(string, sizeof(string), "Ваш ранг в организации был повышен до %s (%d)", PlayerRank[ PlayerInfo[to_player][pMember] ][ PlayerInfo[to_player][pRang] ], PlayerInfo[to_player][pRang]);
			SCM(to_player, blue, string);

            SaveAccounts(to_player);
		}
		case '-':
		{
			if(PlayerInfo[to_player][pRang] >= PlayerInfo[playerid][pRang]) return SCM(playerid, red, "Вы не можете понизить этого игрока!");
			   
			if(PlayerInfo[to_player][pRang] == 1)
				return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /uninvite [ид игрока] [причина]");
				
            PlayerInfo[to_player][pRang]--;
				
			new string[128];
			format(string, sizeof(string), "Вы понизили %s[%d] до %s (%d)", PlayerInfo[to_player][pName], to_player, PlayerRank[ PlayerInfo[to_player][pMember] ][ PlayerInfo[to_player][pRang] ], PlayerInfo[to_player][pRang]);
			SCM(playerid, blue, string);
	        
			format(string, sizeof(string), "Ваш ранг в организации был понижен до %s (%d)", PlayerRank[ PlayerInfo[to_player][pMember] ][ PlayerInfo[to_player][pRang] ], PlayerInfo[to_player][pRang]);
			SCM(to_player, blue, string);

            SaveAccounts(to_player);
		}
        default: return SCM(playerid, 0xFFCC00AA, "•[Подсказка] {ffffff}Введите: /rang [ID игрока] [+/-]"); 
	}
    
    return 1;
}