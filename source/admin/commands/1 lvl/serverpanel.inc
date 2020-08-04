

new miner_zp, loader_zp, diver_zp, dm, db, nonrp, drive, mg, epp, caps, offtop, flood;



ALTX:serverpanel("/spanel");
CMD:serverpanel(playerid)
{
	if(PlayerInfo[playerid][bAdmin] < 1) return ShowCommandNotFound(playerid);

	return ShowApanel(playerid);
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_APANEL:
		{
		    if(response)
		    {
		        switch(listitem)
				{
			        case 0: return ShowAdminsOnline(playerid);
			        case 1: return ShowAdminsOffline(playerid);
			        case 2:
			        {
			            if(PlayerInfo[playerid][bAdmin] >= 5) return ShowAntiCheat(playerid);
			            else return ShowApanel(playerid);
			        }
			        case 3:
			        {
			            if(PlayerInfo[playerid][bAdmin] >= 7) return ShowSetZp(playerid);
			            else return ShowApanel(playerid);
			        }
			        case 4:
			        {
			            if(PlayerInfo[playerid][bAdmin] >= 6) return ShowServerSettings(playerid);
			            else return ShowApanel(playerid);
			        }
			        case 5:
					{ 
						if(PlayerInfo[playerid][bAdmin] >= 2) return ShowTeleportList(playerid);
						return ShowApanel(playerid);
					}
					case 6:
					{
						if(PlayerInfo[playerid][bAdmin] >= 7) return ShowSetNakazania(playerid);
						return ShowApanel(playerid); 
					}
					case 7:
					{
						if(PlayerInfo[playerid][bAdmin] >= 6) return ShowOrgRepositories(playerid); 
						return ShowApanel(playerid);
					}
					case 8:
					{
						if(PlayerInfo[playerid][bAdmin] < 3) return ShowApanel(playerid);
						else
						{
							SCM(playerid, blue, "Вы очистили волну объявлений!");
							ShowApanel(playerid);
							return ClearAds();
						}
					}
		        }
		    }
		}
		case D_APANEL_SETZP:
		{
			if(!response) return ShowApanel(playerid);
			else
			{
			    switch(listitem)
			    {
			        case 0:
			        {
						SPD(playerid, D_SETZP_MINER, DIALOG_STYLE_INPUT, !"{"cblue"} | Зарплата шахтёров", !"{"cwhite"}Установите зарплату шахтёрам: ", !"Далее", !"Назад");
			        }
			        case 1:
			        {
						SPD(playerid, D_SETZP_LOADER, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Зарплата грузчиков", !"{"cwhite"}Установите зарплату грузчикам: ", !"Далее", !"Назад");
			        }
			        case 2:
			        {
						SPD(playerid, D_SETZP_DIVER, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Зарплата водолазов", !"{"cwhite"}Установите зарплату водолазам: ", !"Далее", !"Назад");
			        }
			    }
			}
		}
		case D_SETZP_MINER:
		{
		    if(!response) return ShowSetZp(playerid);
		    else
		    {
		        if(!strlen(inputtext) || !IsNumeric(inputtext))
		        {
                    return SPD(playerid, D_SETZP_MINER, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Зарплата шахтёров", !"{"cwhite"}Установите зарплату шахтёрам: ", !"Далее", !"Назад");
		        }

				miner_zp = strval(inputtext);
				new sql[128];
				format(sql, sizeof(sql), "UPDATE `other` SET `miner_zp` = '%d'", miner_zp);
				mysql_tquery(connects, sql, "", "");

				new string[128];
				format(string, sizeof(string), "{"cgrey"}[A]: %s[%d] установил зарплату шахтёрам: %s!", PlayerInfo[playerid][pName], playerid, inputtext);
				SCMA(grey, string);
		    }
		}
		case D_SETZP_LOADER:
		{
		    if(!response) return ShowSetZp(playerid);
		    else
		    {
		        if(!strlen(inputtext) || !IsNumeric(inputtext))
		        {
		            return SPD(playerid, D_SETZP_LOADER, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Зарплата грузчиков", !"{"cwhite"}Установите зарплату грузчикам: ", !"Далее", !"Назад");
		        }

				loader_zp = strval(inputtext);
				new sql[128];
				format(sql, sizeof(sql), "UPDATE `other` SET `loader_zp` = '%d'", loader_zp);
				mysql_tquery(connects, sql, "", "");

				new string[128];
				format(string, sizeof(string), "{"cgrey"}[A]: %s[%d] установил зарплату грузчикам: %s!", PlayerInfo[playerid][pName], playerid, inputtext);
				SCMA(grey, string);
		    }
		}
		case D_SETZP_DIVER:
		{
		    if(!response) return ShowSetZp(playerid);
		    else
		    {
		        if(!strlen(inputtext) || !IsNumeric(inputtext))
		        {
                    return SPD(playerid, D_SETZP_DIVER, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Зарплата водолазов", !"{"cwhite"}Установите зарплату водолазам: ", !"Далее", !"Назад");
		        }

				diver_zp = strval(inputtext);
				new sql[128];
				format(sql, sizeof(sql), "UPDATE `other` SET `diver_zp` = '%d'", diver_zp);
				mysql_tquery(connects, sql, "", "");

				new string[128];
				format(string, sizeof(string), "{"cgrey"}[A]: %s[%d] установил зарплату водолазам: %s!", PlayerInfo[playerid][pName], playerid, inputtext);
				SCMA(grey, string);
		    }
		}
		case D_SET_DM:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetDM(playerid);

				dm = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `dm` = '%d'", dm);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /dm на %d минут", PlayerInfo[playerid][pName], playerid, dm);
				SCMA(grey, string);
			}
		}
		case D_SET_NONRP:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetNonRP(playerid);

				nonrp = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `nonrp` = '%d'", nonrp);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /nonrp на %d минут", PlayerInfo[playerid][pName], playerid, nonrp);
				SCMA(grey, string);
			}
		}
		case D_SET_DRIVE:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetDrive(playerid);

				drive = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `drive` = '%d'", drive);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /drive на %d минут", PlayerInfo[playerid][pName], playerid, drive);
				SCMA(grey, string);
			}
		}
		case D_SET_DB:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetDB(playerid);

				db = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `db` = '%d'", db);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /driveby на %d минут", PlayerInfo[playerid][pName], playerid, db);
				SCMA(grey, string);
			}
		}
		case D_SET_MG:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetMG(playerid);

				mg = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `mg` = '%d'", mg);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /mg на %d минут", PlayerInfo[playerid][pName], playerid, mg);
				SCMA(grey, string);
			}
		}
		case D_SET_EPP:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetEPP(playerid);

				epp = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `epp` = '%d'", epp);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /epp на %d минут", PlayerInfo[playerid][pName], playerid, epp);
				SCMA(grey, string);
			}
		}
		case D_SET_CAPS:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetCAPS(playerid);

				caps = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `caps` = '%d'", caps);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /caps на %d минут", PlayerInfo[playerid][pName], playerid, caps);
				SCMA(grey, string);
			}
		}
		case D_SET_FLOOD:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetFLOOD(playerid);

				flood = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `flood` = '%d'", flood);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /flood на %d минут", PlayerInfo[playerid][pName], playerid, flood);
				SCMA(grey, string);
			}
		}
		case D_SET_OFFTOP:
		{
			if(!response) return ShowSetNakazania(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOFFTOP(playerid);

				offtop = strval(inputtext);
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `offtop` = '%d'", offtop);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A] %s[%d] установил /offtop на %d минут", PlayerInfo[playerid][pName], playerid, offtop);
				SCMA(grey, string);
			}
		}
		case D_ORG_REPOSITORIES:
		{
			if(!response) return ShowApanel(playerid);
			else
			{
				switch(listitem)
				{
					case 0:
					{
						ShowSetArmyMet(playerid);
					}
					case 1:
					{
						ShowSetArmyPatr(playerid);
					}
					case 2:
					{
						ShowSetOpgOMet(playerid);
					}
					case 3:
					{
						ShowSetOpgOPatr(playerid);
					}
					case 4:
					{
						ShowSetOpgODrugs(playerid);
					}
					case 5:
					{
						ShowSetOpgOMoney(playerid);
					}
					case 6:
					{
						ShowSetOpgSMet(playerid);
					}
					case 7:
					{
						ShowSetOpgSPatr(playerid);
					}
					case 8:
					{
						ShowSetOpgSDrugs(playerid);
					}
					case 9:
					{
						ShowSetOpgSMoney(playerid);
					}
					case 10:
					{
						ShowSetPortDrugs(playerid);
					}
				}
			}
		}
		case D_SET_PORT_DRUGS:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetPortDrugs(playerid);

				ALL_NARKO = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил в порту %d гр. наркотиков", PlayerInfo[playerid][pName], playerid, ALL_NARKO);
				SCMA(grey, string);

				SaveRepository();
			}
		}
		case D_SET_OPG_O_MET:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgOMet(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgOMet(playerid);

				OPG_O_METALL = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-О %d кг. металла", PlayerInfo[playerid][pName], playerid, OPG_O_METALL);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_O_PATR:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgOPatr(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgOPatr(playerid);

				OPG_O_PATRON = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-О %d пт.", PlayerInfo[playerid][pName], playerid, OPG_O_PATRON);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_O_DRUGS:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgODrugs(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgODrugs(playerid);

				OPG_O_DRUGS = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-О %d гр. наркотиков", PlayerInfo[playerid][pName], playerid, OPG_O_DRUGS);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_O_MONEY:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgOMoney(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgOMoney(playerid);

				OPG_O_MONEY = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-О %d руб.", PlayerInfo[playerid][pName], playerid, OPG_O_MONEY);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_S_MET:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgSMet(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgSMet(playerid);

				OPG_S_METALL = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-С %d кг. металла", PlayerInfo[playerid][pName], playerid, OPG_S_METALL);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_S_PATR:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgSPatr(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgSPatr(playerid);

				OPG_S_PATRON = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-С %d пт.", PlayerInfo[playerid][pName], playerid, OPG_S_PATRON);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_S_DRUGS:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgSDrugs(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgSDrugs(playerid);

				OPG_S_DRUGS = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-С %d гр. наркотиков", PlayerInfo[playerid][pName], playerid, OPG_S_DRUGS);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_OPG_S_MONEY:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetOpgSMoney(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetOpgSMoney(playerid);

				OPG_S_MONEY = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу ОПГ-С %d руб.", PlayerInfo[playerid][pName], playerid, OPG_S_MONEY);
				SCMA(grey, string);

				SaveRepository();
			}			
		}
		case D_SET_ARMY_MET:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetArmyMet(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetArmyMet(playerid);

				REPOSITORY_ARMY_METALL = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу армии %d кг. металла", PlayerInfo[playerid][pName], playerid, REPOSITORY_ARMY_METALL);
				SCMA(grey, string);

				SaveRepository();
			}
		}
		case D_SET_ARMY_PATR:
		{
			if(!response) return ShowOrgRepositories(playerid);
			else
			{
				if(!strlen(inputtext) || !IsNumeric(inputtext)) return ShowSetArmyPatr(playerid);
				if(strval(inputtext) < 1 || strval(inputtext) > 10000) return ShowSetArmyPatr(playerid);

				REPOSITORY_ARMY_PATRON = strval(inputtext);
				new string[144];
				format(string, sizeof(string), "[A] %s[%d] установил складу армии %d патронов", PlayerInfo[playerid][pName], playerid, REPOSITORY_ARMY_PATRON);
				SCMA(grey, string);

				SaveRepository();
			}
		}
		case D_APANEL_ANTI_CHEAT:
		{
		    if(!response) return ShowApanel(playerid);
		    else
		    {
				AntiCheatInfo[listitem][acStatus] = (AntiCheatInfo[listitem][acStatus] == 0) ? (1) : (0);
				return ShowAntiCheat(playerid);

		        // switch(listitem)
		        // {
		        //     case 0:
		        //     {
		        //         if(AntiCheatInfo[SpeedHack_AC][acStatus] != 1)
		        //         {
		        //             AntiCheatInfo[SpeedHack_AC][acStatus] = 1;

		        //             new string[128];
		        //             format(string, sizeof(string), "{"cgrey"}[A] %s[%d] установил Кик на SpeedHack", PlayerInfo[playerid][pName], playerid);
		        //             SCMA(blue, string);
		        //             return ShowAntiCheat(playerid);
		        //         }
		        //         else
		        //         {
		        //             AntiCheatInfo[SpeedHack_AC][acStatus] = 0;

		        //             new string[128];
		        //             format(string, sizeof(string), "{"cgrey"}[A] %s[%d] установил сообщение на SpeedHack", PlayerInfo[playerid][pName], playerid);
		        //             SCMA(blue, string);
		        //             return ShowAntiCheat(playerid);
				// 		}
		        //     }
		        //     case 1:
		        //     {
		        //         if(AntiCheatInfo[TP_in_VEH_AC][acStatus] != 1)
		        //         {
		        //             AntiCheatInfo[TP_in_VEH_AC][acStatus] = 1;

		        //             new string[128];
		        //             format(string, sizeof(string), "{"cgrey"}[A] %s[%d] установил Кик на Телепорт в транспорт", PlayerInfo[playerid][pName], playerid);
		        //             SCMA(blue, string);
		        //             return ShowAntiCheat(playerid);
		        //         }
		        //         else
		        //         {
		        //             AntiCheatInfo[TP_in_VEH_AC][acStatus] = 0;

		        //             new string[128];
		        //             format(string, sizeof(string), "{"cgrey"}[A] %s[%d] установил сообщение на Телепорт в транспорт", PlayerInfo[playerid][pName], playerid);
		        //             SCMA(blue, string);
		        //             return ShowAntiCheat(playerid);
				// 		}
		        //     }
		        // }
		    }
		}
		case D_SERVER_SETTINGS:
		{
		    if(!response) return ShowApanel(playerid);
		    else
		    {
		        switch(listitem)
		        {
		            case 0: ShowSetServerPass(playerid);
		            case 1:
		            {
		                SCMTA(red, "Просисходит кик игроков всего сервера!");
		                foreach(new i : Player)
		                {
		                    if(PlayerInfo[i][bAdmin] == 0)
		                    {
		                        NewKick(i);
		                    }
		                }
		            }
		            case 2:
		            {
		                SPD(playerid, D_SET_XDAY, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | XDAY", "{FFFFFF}Здесь вы можете установить XДень! Если вы ничего не введете, то XДень станет 1!", "Далее", "Назад");
		            }
		            case 3:
		            {
		                SPD(playerid, D_ASK_RESTART, DIALOG_STYLE_MSGBOX, "{"cblue"}UNIGVA | Restart", "{FFFFFF}Вы уверенны что хотите перезагрузить сервер?", "Да", "Нет");
		            }
		            case 4:
		            {
		                SPD(playerid, D_SET_SERVER_NAME, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | Название сервера", "{FFFFFF}Здесь вы можете установить название сервера.", "Далее", "Назад");
		            }
		        }
		    }
		}
		case D_ASK_RESTART:
		{
		    if(!response) return ShowServerSettings(playerid);
		    else return Restart_Server(playerid);
		}
		case D_SET_SERVER_NAME:
		{
		    if(!response) return ShowServerSettings(playerid);
		    else
		    {
		        new string[256];
		        if(!strlen(inputtext))
		        {
		            SendRconCommand("hostname "hostname"");
		            ShowServerSettings(playerid);

		            format(string, sizeof(string), "[A]: %s[%d] установил название сервера: %s", PlayerInfo[playerid][pName], playerid, hostname);
		            SCMA(grey, string);
		        }
		        else
		        {
					new serv_name[256];
					strcat(serv_name, inputtext, 256);

					format(string, sizeof(string), "hostname %s", serv_name);
					SendRconCommand(string);

		            format(string, sizeof(string), "[A]: %s[%d] установил название сервера на: %s", PlayerInfo[playerid][pName], playerid, serv_name);
		            SCMA(grey, string);
		        }
		    }
		}
		case D_SET_XDAY:
		{
		    if(!response) return ShowServerSettings(playerid);
		    else
		    {
				if(!strlen(inputtext))
				{
					XDay = 1;
				}
				else
				{
				    XDay = strval(inputtext);
				}
				new string[128];
				format(string, sizeof(string), "UPDATE `other` SET `XDay` = '%d' LIMIT 1", XDay);
				mysql_tquery(connects, string, "", "");

				format(string, sizeof(string), "[A]: %s[%d] установил X%d Day", PlayerInfo[playerid][pName], playerid, XDay);
				SCMA(grey, string);
				ShowServerSettings(playerid);
		    }
		}
		case D_SET_SERVER_PASS:
		{
		    if(!response) return ShowServerSettings(playerid);
		    else
		    {
		        if(!strlen(inputtext))
		        {
		            server_pass_status = 0;
		            new string[128];
		            format(string, sizeof(string), "[A]: %s[%d] убрал пароль сервера", PlayerInfo[playerid][pName], playerid);
		            SCMA(grey, string);

		            format(string, sizeof(string), "UPDATE `other` SET `server_pass_status` = '%d' LIMIT 1", server_pass_status);
		            mysql_tquery(connects, string, "", "");

		            format(string, sizeof(string), "UPDATE `other` SET `server_pass` = 'None' LIMIT 1");
		            mysql_tquery(connects, string, "", "");
		        }
		        else
		        {
		            if(strlen(inputtext) > 24)
		            {
		                SCM(playerid, red, "Пароль должен быть не более 24 символов!");
		                return ShowSetServerPass(playerid);
		            }
					strdel(server_pass, 0, 24);
		            server_pass_status = 1;
		            strcat(server_pass, inputtext, 24);
		            new string[128];
		            format(string, sizeof(string), "[A]: %s[%d] установил новый пароль сервера: %s", PlayerInfo[playerid][pName], playerid, server_pass);
		            SCMA(grey, string);

		            format(string, sizeof(string), "UPDATE `other` SET `server_pass_status` = '%d' LIMIT 1", server_pass_status);
		            mysql_tquery(connects, string, "", "");

		            format(string, sizeof(string), "UPDATE `other` SET `server_pass` = '%s' LIMIT 1", server_pass);
		            mysql_tquery(connects, string, "", "");
		        }
		    }
		}
		case D_SET_NAKAZANIA:
		{
			if(!response) ShowApanel(playerid);
			else
			{
				switch(listitem)
				{
					case 0:	ShowSetDM(playerid);
					case 1:	ShowSetNonRP(playerid);
					case 2:	ShowSetDrive(playerid);
					case 3:	ShowSetDB(playerid);
					case 4: ShowSetMG(playerid);
					case 5: ShowSetEPP(playerid);
					case 6: ShowSetCAPS(playerid);
					case 7: ShowSetFLOOD(playerid);
					case 8: ShowSetOFFTOP(playerid);
				}
			}
		}
	}
	#if	defined	apanel__OnDialogResponse
		return apanel__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse apanel__OnDialogResponse
#if	defined	apanel__OnDialogResponse
	forward apanel__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

stock ShowAdminsOffline(playerid)
{
    new query[1500];
    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `bAdmin` != '0' ORDER BY `pLastConnect` ASC");
	mysql_tquery(connects, query, "all_admins", "i", playerid);
	return 1;
}
stock ShowAntiCheat(playerid)
{
	new fmt_dialog[528], string[128];
	foreach(new i : AllAntiCheats)
	{
		format
		(
			string, sizeof(string), "{"cblue"}%d. {FFFFFF}%s ({"cblue"}%s{FFFFFF})\n", i+1, AntiCheatInfo[i][acName], (AntiCheatInfo[i][acStatus] == 1) ? ("Кик") : ("Сообщение")
		);
		strcat(fmt_dialog, string);
	}
	SPD(playerid, D_APANEL_ANTI_CHEAT, DIALOG_STYLE_LIST, "{"cblue"}UNIGVA | UN-AC", fmt_dialog, "Далее", "Назад");
	return 1;
}
stock ShowSetZp(playerid)
{
	new string[240];
	format(string, sizeof(string), "\
		{"cblue"}1. {"cwhite"}Установить зарплату для Шахтеров\t\t\t(%d)\n\
		{"cblue"}2. {"cwhite"}Установить зарплату для Грузчиков\t\t\t(%d)\n\
		{"cblue"}3. {"cwhite"}Установить зарплату для Водолазов\t\t(%d)",
		miner_zp, loader_zp, diver_zp);
	SPD(playerid, D_APANEL_SETZP, DIALOG_STYLE_LIST, !"{"cblue"}UNIGVA | Установить ЗП", string, !"Далее", !"Назад");

	return 1;
}
stock ShowServerSettings(playerid)
{
	SPD(playerid, D_SERVER_SETTINGS, DIALOG_STYLE_LIST, "{"cblue"}UNIGVA | Настройки сервера", "\
	{"cblue"}1. {FFFFFF}Установить пароль на сервер\n\
	{"cblue"}2. {FFFFFF}Кикнуть всех игроков(кроме админов)\n\
	{"cblue"}3. {FFFFFF}Установить XDay\n\
	{"cblue"}4. {FFFFFF}Сделать рестарт сервера\n\
	{"cblue"}5. {FFFFFF}Установить название сервера", "Далее", "Назад");
	return 1;
}
stock ShowApanel(playerid)
{
	SPD(playerid, D_APANEL, DIALOG_STYLE_LIST, !"{"cblue"}UNIGVA | APANEL", !"\
	{"cblue"}1. {"cwhite"}Все администраторы [Онлайн]\n\
	{"cblue"}2. {"cwhite"}Все администраторы [Оффлайн]\n\
	{"cblue"}3. {"cwhite"}Античит\n\
	{"cblue"}4. {"cwhite"}Установить зарплаты\n\
	{"cblue"}5. {"cwhite"}Настройки сервера\n\
	{"cblue"}6. {"cwhite"}Телепорт\n\
	{"cblue"}7. {"cwhite"}Установить наказания\n\
	{"cblue"}8. {"cwhite"}Склады организаций\n\
	{"cblue"}9. {"cwhite"}Очистить волну объявлений", !"Далее", !"Отмена");
	return 1;
}
stock ShowLogs(playerid)
{
	return 1;
}
publics all_admins(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	new fmt_str[1500], string[1500], player_name[MAX_PLAYER_NAME], rank, level, status[32];
	new last_connect[32];
	string = "{"cblue"}ЛВЛ АДМ\tУровень\tСтатус\t\tПоследний вход\tИмя Фамилия\n\n{FFFFFF}";
	if(rows)
	{
        for(new i = 0; i < rows; i++)
		{
	        rank = cache_get_field_content_int(i, "bAdmin");
	        level = cache_get_field_content_int(i, "pLVL");
            cache_get_field_content(i, "pName", player_name, connects, MAX_PLAYER_NAME);
            cache_get_field_content(i, "pLastConnect", last_connect, connects, 32);

			if(GetPlayerID(player_name) == INVALID_PLAYER_ID) format(status,sizeof(status), "{C62821}OFF{FFFFFF}");
			else format(status,sizeof(status),"{99CC00}ON{FFFFFF}");
			format
			(
				fmt_str, sizeof(fmt_str),
				"%d\t\t%d\t\t%s\t\t%s\t%s\n",
				rank, level, status, last_connect, player_name
			);
	    	strcat(string, fmt_str);
    	}
	}
	ShowPlayerDialog
	(
		playerid, D_NULL, DIALOG_STYLE_MSGBOX,
		"{"cblue"}Вся администрация",
		string,
		"Закрыть", ""
	);
	return true;
}
stock ShowSetServerPass(playerid)
{
	return SPD(playerid, D_SET_SERVER_PASS, DIALOG_STYLE_INPUT, !"{"cblue"}UNIGVA | Установить пароль на сервер", "{FFFFFF}Здесь вы можете установить пароль на сервер,\nесли вы хотите убрать пароль сервера, то просто оствьте строку пустой!", "Далее", "Назад");
}
stock ShowSetNakazania(playerid)
{
	new string[528];
	format(string, sizeof(string), "\
		{"cblue"}1. {FFFFFF}DM (%d минут)\n\
		{"cblue"}2. {FFFFFF}NonRP (%d минут)\n\
		{"cblue"}3. {FFFFFF}NonRP езда (%d минут)\n\
		{"cblue"}4. {FFFFFF}DB (%d минут)\n\
		{"cblue"}5. {FFFFFF}MG (%d минут)\n\
		{"cblue"}6. {FFFFFF}EPP (%d минут)\n\
		{"cblue"}7. {FFFFFF}CAPS (%d минут)\n\
		{"cblue"}8. {FFFFFF}FLOOD (%d минут)\n\
		{"cblue"}9. {FFFFFF}OFFTOP (%d минут)\
		", dm, nonrp, drive, db, mg, epp, caps, flood, offtop);

	SPD(playerid, D_SET_NAKAZANIA, DIALOG_STYLE_LIST, "{"cblue"}UNIGVA | Установить время за наказания", string, "Далее", "Закрыть");
	return 1;
}
stock ShowSetDM(playerid)
{
	SPD(playerid, D_SET_DM, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | DM", "{ffffff}Установите количество времени наказания за ДМ:", "Далее", "Назад");
	return 1;
}
stock ShowSetNonRP(playerid)
{
	SPD(playerid, D_SET_NONRP, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | NonRP", "{ffffff}Установите количество времени наказания за NonRP:", "Далее", "Назад");
	return 1;
}
stock ShowSetDrive(playerid)
{
	SPD(playerid, D_SET_DRIVE, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | Drive", "{ffffff}Установите количество времени наказания за NonRP езду:", "Далее", "Назад");
	return 1;
}
stock ShowSetDB(playerid)
{
	SPD(playerid, D_SET_DB, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | DB", "{ffffff}Установите количество времени наказания за ДБ:", "Далее", "Назад");
	return 1;
}
stock ShowSetMG(playerid)
{
	SPD(playerid, D_SET_MG, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | MG", "{ffffff}Установите количество времени наказания за МГ:", "Далее", "Назад");
	return 1;
}
stock ShowSetEPP(playerid)
{
	SPD(playerid, D_SET_EPP, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | ЕПП", "{ffffff}Установите количество времени наказания за ЕПП:", "Далее", "Назад");
	return 1;
}
stock ShowSetCAPS(playerid)
{
	SPD(playerid, D_SET_CAPS, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | КАПС", "{ffffff}Установите количество времени наказания за КАПС:", "Далее", "Назад");
	return 1;
}
stock ShowSetFLOOD(playerid)
{
	SPD(playerid, D_SET_FLOOD, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | ФЛУД", "{ffffff}Установите количество времени наказания за ФЛУД:", "Далее", "Назад");
	return 1;
}
stock ShowSetOFFTOP(playerid)
{
	SPD(playerid, D_SET_OFFTOP, DIALOG_STYLE_INPUT, "{"cblue"}APANEL | ОФФТОП", "{ffffff}Установите количество времени наказания за ОФФТОП:", "Далее", "Назад");
	return 1;
}
stock ShowOrgRepositories(playerid)
{
	SPD(playerid, D_ORG_REPOSITORIES, DIALOG_STYLE_LIST, "{"cblue"}APANEL | Склады организаций", "\
	{"cblue"}1. {FFFFFF}Установить металл Армии\n\
	{"cblue"}2. {FFFFFF}Установить патроны Армиии\n\
	{"cblue"}3. {FFFFFF}Установить металл ОПГ - О\n\
	{"cblue"}4. {FFFFFF}Установить патроны ОПГ - О\n\
	{"cblue"}5. {FFFFFF}Установить наркотики ОПГ - О\n\
	{"cblue"}6. {FFFFFF}Установить деньги ОПГ - О\n\
	{"cblue"}7. {FFFFFF}Установить металл ОПГ - С\n\
	{"cblue"}8. {FFFFFF}Установить патроны ОПГ - С\n\
	{"cblue"}9. {FFFFFF}Установить наркотики ОПГ - С\n\
	{"cblue"}10. {FFFFFF}Установить деньги ОПГ - С\n\
	{"cblue"}11. {FFFFFF}Установить наркотики в порту", "Далее", "Назад");
	return 1;
}
stock ShowSetArmyMet(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество металла вы хотите установить Армии? Сейчас на складе армии %d кг. металла.", REPOSITORY_ARMY_METALL);
	return SPD(playerid, D_SET_ARMY_MET, DIALOG_STYLE_INPUT, "{"cblue"}Склад Армии | Металл", string, "Далее", "Закрыть");
}
stock ShowSetArmyPatr(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество патронов вы хотите установить Армии? Сейчас на складе армии %d патронов.", REPOSITORY_ARMY_PATRON);
	return SPD(playerid, D_SET_ARMY_PATR, DIALOG_STYLE_INPUT, "{"cblue"}Склад Армии | Патроны", string, "Далее", "Закрыть");
}


stock ShowSetOpgOMet(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество металл вы хотите установить ОПГ - О? Сейчас на складе ОПГ - О %d кг металла.", OPG_O_METALL);
	return SPD(playerid, D_SET_OPG_O_MET, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - О | Металл", string, "Далее", "Закрыть");
}
stock ShowSetOpgOPatr(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество патронов вы хотите установить ОПГ - О? Сейчас на складе ОПГ - О %d патронов.", OPG_O_PATRON);
	return SPD(playerid, D_SET_OPG_O_PATR, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - О | Патроны", string, "Далее", "Закрыть");
}
stock ShowSetOpgODrugs(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество наркотиков вы хотите установить ОПГ - О? Сейчас на складе ОПГ - О %d гр. наркотиков.", OPG_O_DRUGS);
	return SPD(playerid, D_SET_OPG_O_DRUGS, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - О | Наркотики", string, "Далее", "Закрыть");
}
stock ShowSetOpgOMoney(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество денег вы хотите установить ОПГ - О? Сейчас на складе ОПГ - О %d руб..", OPG_O_MONEY);
	return SPD(playerid, D_SET_OPG_O_MONEY, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - О | Деньги", string, "Далее", "Закрыть");
}

stock ShowSetOpgSMet(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество металл вы хотите установить ОПГ - С? Сейчас на складе ОПГ - С %d кг. металла.", OPG_S_METALL);
	return SPD(playerid, D_SET_OPG_S_MET, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - С | Металл", string, "Далее", "Закрыть");
}
stock ShowSetOpgSPatr(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество патронов вы хотите установить ОПГ - С? Сейчас на складе ОПГ - С %d патронов.", OPG_S_PATRON);
	return SPD(playerid, D_SET_OPG_S_PATR, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - С | Патроны", string, "Далее", "Закрыть");
}
stock ShowSetOpgSDrugs(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество наркотиков вы хотите установить ОПГ - С? Сейчас на складе ОПГ - С %d гр. наркотиков.", OPG_S_DRUGS);
	return SPD(playerid, D_SET_OPG_S_DRUGS, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - С | Наркотики", string, "Далее", "Закрыть");
}
stock ShowSetOpgSMoney(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество денег вы хотите установить ОПГ - С? Сейчас на складе ОПГ - С %d руб..", OPG_S_MONEY);
	return SPD(playerid, D_SET_OPG_S_MONEY, DIALOG_STYLE_INPUT, "{"cblue"}Склад ОПГ - С | Денег", string, "Далее", "Закрыть");
}
stock ShowSetPortDrugs(playerid)
{
	new string[128];
	format(string, sizeof(string), "{FFFFFF}Какое количество наркотиков вы хотите установить в порту Сейчас в порту %d гр. наркотиков.", ALL_NARKO);
	return SPD(playerid, D_SET_PORT_DRUGS, DIALOG_STYLE_INPUT, "{"cblue"}Порт | Наркотики", string, "Далее", "Закрыть");
}

