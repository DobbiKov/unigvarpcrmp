CMD:agl(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new to_player, what, count; else
	{
	    SCM(playerid, blue, "[Подсказка] {ffffff}Введите: /agl [id игрока] [номер] [Значение]");
	    SCM(playerid, white, "[номер]: Категории: 1 - A | 2 - B | 3 - C | 4 - D | Лицензии: 5 - на бизнесс | 6 - на полеты | 7 - на оружие");
        SCM(playerid, white, "[значение]: 0 - забрать; 1 - выдать;");
 		return 1;
	}
    switch(what)
    {
        case 0:
        {
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicA] = count;
			PlayerInfo[to_player][pLicB] = count;
			PlayerInfo[to_player][pLicC] = count;
			PlayerInfo[to_player][pLicD] = count;

            PlayerInfo[to_player][pLicBiz] = count;
            PlayerInfo[to_player][pLicFly] = count;
            PlayerInfo[to_player][pLicGun] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s все лицензии", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал вам все лицензии", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s все лицензии", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас все лицензии", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}           
        }
    	case 1:
		{
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicA] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s права категории A", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал вам права категории A", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s права категории A", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас права категории A", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
		}
		case 2:
		{
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicB] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s права категории B", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал вам права категории B", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s права категории B", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас права категории B", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
		}
		case 3:
		{
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicC] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s права категории C", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал вам права категории C", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s права категории C", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас права категории C", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
		}
		case 4:
		{
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicD] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s права категории D", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал вам права категории D", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s права категории D", count, PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас права категории D", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
		}
        case 5:
        {
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicBiz] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s лицензию на бизнесс", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал лицензию на бизнесс", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s лицензию на бизнесс", count, PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас лицензию на бизнесс", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
        }
        case 6:
        {
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicFly] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s лицензию на полёты", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал лицензию на полёты", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s лицензию на полёты", count, PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас лицензию на полёты", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
        }
        case 7:
        {
		    if(count > 1 || count < 0) return SCM(playerid, red, " Не менее 0 и не более 1!");
			PlayerInfo[to_player][pLicGun] = count;
			new string[128];
			if(count == 1)
			{
				format(string, sizeof(string), "Вы выдали игроку %s лицензию на оружие", PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s выдал лицензию на оружие", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
			else
			{
				format(string, sizeof(string), "Вы забрали у игрока %s лицензию на оружие", count, PlayerInfo[to_player][pName]);
				SCM(playerid, white, string);

				format(string, sizeof(string), "Администратор %s забрал у вас лицензию на оружие", PlayerInfo[playerid][pName]);
				SCM(to_player, white, string);
			}
        }
        default:
        {
            SCM(playerid, blue, "[Подсказка] {ffffff}Введите: /agl [id игрока] [номер] [Значение]");
            SCM(playerid, white, "[номер]: Категории: 1 - A | 2 - B | 3 - C | 4 - D | Лицензии: 5 - на бизнесс | 6 - на полеты | 7 - на оружие");
            SCM(playerid, white, "[значение]: 0 - забрать; 1 - выдать;");           
        }
    }
    return 1;
}