new training_timer[MAX_PLAYERS];

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
	    case 1:
	    {
	        if(response)
			{
			    stringer[0] = EOS;
			    for(new i; i < 7; i++) strcat(stringer, RulesSO[i]);
				SPD(playerid, 2, DIALOG_STYLE_MSGBOX,"{"cblue"}Правила и соглашение",stringer,"Далее","Отмена");
			}
	        else { SCM(playerid, lightred, "Вы были кикнуты с сервера! Чтобы выйти из игры, введите /q (/quit)"), NewKick(playerid); }
		}
		case 2:
		{
			if(response)
			{
			    stringer[0] = EOS;
			    for(new i; i < 7; i++) strcat(stringer, RulesST[i]);
				SPD(playerid, 3, DIALOG_STYLE_MSGBOX,"{"cblue"}Правила и соглашение",stringer,"Далее","Отмена");
			}
	        else { SCM(playerid, lightred, "Вы были кикнуты с сервера! Чтобы выйти из игры, введите /q (/quit)"), NewKick(playerid); }
		}
		case 3:
		{
		    if(response) SPD(playerid, 5, DIALOG_STYLE_MSGBOX, "{"cblue"}Пол персонажа", "{"cwhite"}Выберите пол вашего персонажа.", "Мужской", "Женский");
		    else
			{
				SCM(playerid, lightred, "Вы были кикнуты с сервера! Чтобы выйти из игры, введите /q (/quit)");
				NewKick(playerid);
			}
		}
		case 4:
		{
			if(response)
			{
				new temp[26];
			    mysql_real_escape_string(inputtext, temp);
			    if(!strcmp(inputtext, PlayerInfo[playerid][pName], true))
				{
					 SCM(playerid, white, "Нельзя указывать собственный ник. Если вы не знаете других игроков нажмите кнопку 'Пропустить'");
					 return SPD(playerid,4,DIALOG_STYLE_INPUT,"{"cblue"}Приглашение от игрока", "{"cwhite"}Введите ник игрока, пригласившего Вас на сервер\nТак-же Вы можете ввести промокод, если таковой имеется", "Далее", "Пропустить");
				}
			    new string[65];
				format(string, sizeof(string), "SELECT * FROM `accounts` WHERE `pName` = '%s'", temp);
				mysql_function_query(connects, string, true, "CheckReferal", "ds", playerid, temp);
				SetPVarString(playerid, "referal", temp);
			}
			else return RegStok(playerid);
		}
		case 5:
		{
		    new rand;
		    if(response)
		    {
		        PlayerInfo[playerid][pSex] = 1;
		        rand = random(sizeof(Player_Skin_Male));
				PlayerInfo[playerid][pChar] = Player_Skin_Male[rand];
			}
		    else
		    {
		        PlayerInfo[playerid][pSex] = 2;
		        rand = random(sizeof(Player_Skin_Female));
				PlayerInfo[playerid][pChar] = Player_Skin_Female[rand];
			}
			SPD(playerid, 6, DIALOG_STYLE_INPUT, "{"cblue"}Регистрация", "{"cwhite"}Введите пароль для вашего аккаунта.\nОн будет запрашиваться при каждом входе на сервер.\n\n{"cblue"}Примечения:\n\
			- Пароль должен быть сложным (Пример: s9cQ17)\n- Пароль должен состоять из цифр и букв\n- Максимальная длина пароля от 6 до 20 символов.", "Далее", "Выйти");
		}
		case 6:
		{
		    if(response)
		    {
				if(!strlen(inputtext)) return SPD(playerid, 6, DIALOG_STYLE_INPUT, "{"cblue"}Регистрация", "{"cwhite"}Введите пароль для вашего аккаунта.\nОн будет запрашиваться при каждом входе на сервер.\n\n{"cblue"}Примечения:\n\
				- Пароль должен быть сложным (Пример: s9cQ17)\n- Пароль должен состоять из цифр и букв\n- Максимальная длина пароля от 6 до 20 символов.", "Далее", "Выйти");
			    if(strlen(inputtext) < 6 || strlen(inputtext) > 20)
			    {
			   		SPD(playerid, 6, DIALOG_STYLE_INPUT, "{"cblue"}Регистрация", "{"cwhite"}Введите пароль для вашего аккаунта.\nОн будет запрашиваться при каждом входе на сервер.\n\n{"cblue"}Примечения:\n\
					- Пароль должен быть сложным (Пример: s9cQ17)\n- Пароль должен состоять из цифр и букв\n- Максимальная длина пароля от 6 до 20 символов.", "Далее", "Выйти");
					return SCM(playerid, white, "Пароль не может быть меньше 6 и больше 20 символов.");
				}
				for(new i = strlen(inputtext); i != 0; --i)
				switch(inputtext[i])
				{
					case 'А'..'Я', 'а'..'я', '=', ' ':
					{
						SPD(playerid, 6, DIALOG_STYLE_INPUT, "{"cblue"}Регистрация", "{"cwhite"}Введите пароль для вашего аккаунта.\nОн будет запрашиваться при каждом входе на сервер.\n\n{"cblue"}Примечения:\n\
						- Пароль должен быть сложным (Пример: s9cQ17)\n- Пароль должен состоять из цифр и букв\n- Максимальная длина пароля от 6 до 20 символов.", "Далее", "Выйти");
						return SCM(playerid, white, "В пароле не должно быть русских символов.");
					}
				}
				strmid(PlayerInfo[playerid][pKey], inputtext, 0, strlen(inputtext), 64);
				RegStock(playerid);
				if(response) return SPD(playerid,4,DIALOG_STYLE_INPUT,"{"cblue"}Приглашение от игрока", "{"cwhite"}Введите ник игрока, пригласившего Вас на сервер\nТак-же Вы можете ввести промокод, если таковой имеется", "Далее", "Пропустить");
			}
			else { SCM(playerid, lightred, "Вы были кикнуты с сервера! Чтобы выйти из игры, введите /q (/quit)"), NewKick(playerid); }

		}
		case 7:
		{
		    if(response)
		    {
			    if(!strlen(inputtext))
				{
			    	stringer[0] = EOS;
					format(stringer, 170, "{"cwhite"}Добро пожаловать на {"cblue"}"name_serv"{"cwhite"}\n\nИмя персонажа {"cblue"}%s{"cwhite"}\nВведите пароль:", PlayerInfo[playerid][pName]);
	    			SPD(playerid, 7, DIALOG_STYLE_PASSWORD, "{"cblue"}Авторизация", stringer, "Войти", "Выйти");
				}
				OnPlayerLogin(playerid,inputtext);
			}
			else { SCM(playerid, lightred, "Вы были кикнуты с сервера! Чтобы выйти из игры, введите /q (/quit)"), NewKick(playerid); }
		}
		case D_SERVER_PASS:
		{
		    if(!response)
		    {
		        SCM(playerid, blue, !"Вы были кикнуты с сервера, так как отказались вводить пароль!");
		        NewKick(playerid);
		    }
		    else
		    {
				if(!strlen(inputtext)) return ShowServerPassDialog(playerid);
		        if(strcmp(inputtext, server_pass, true))
				{
				    SCM(playerid, red, "Вы были кикнуты с сервера, так как ввели пароль неправильно.");
			 		return NewKick(playerid);
				}
				else
		        {
		            new string[256];
         			format(string, sizeof(string),"SELECT `pLVL` FROM `accounts` WHERE `pName` = '%s'", PlayerInfo[playerid][pName]);
					mysql_function_query(connects, string, true, "OnPlayerRegCheck", "d", playerid);
		        }
		    }
		}
		case D_GO_REG_TRAINING:
		{
			if(!response) return 1;
			else
			{
				for(new idx = 0; idx < 9; idx++)
					PlayerTextDrawShow(playerid, training_td[playerid][idx]);
                training_timer[playerid] = 61;
                TogglePlayerControllable(playerid, false);
			}
		}
    }
	#if	defined	reg_au__OnDialogResponse
		return reg_au__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse reg_au__OnDialogResponse
#if	defined	reg_au__OnDialogResponse
	forward reg_au__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics OnPlayerRegCheck(playerid)
{
	new rows[2];
	cache_get_data(rows[0], rows[1]);
	SetPlayerCameraPos(playerid, 1920.9984,2096.5823,40.5753);
	SetPlayerCameraLookAt(playerid, 1819.1917,2095.7693,21.2062);
	SCM(playerid, blue, "Добро пожаловать на "name_serv"");
	SetPlayerVirtualWorld(playerid, playerid);
	if(rows[0]) // Авторизации
	{
		stringer[0] = EOS;
		PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
		format(stringer, 170, "{"cwhite"}Добро пожаловать на {"cblue"}"name_serv"{"cwhite"}\n\nИмя персонажа {"cblue"}%s{"cwhite"}\nВведите пароль:", PlayerInfo[playerid][pName]);
	    SPD(playerid, 7, DIALOG_STYLE_PASSWORD, "{"cblue"}Авторизация", stringer, "Войти", "Выйти");
	}
	else // Регистрации
	{
		for(new i = 0; i < 3; i++) TextDrawShowForPlayer(playerid, logotype_td[i]);
	    SPD(playerid,D_REGISTER,DIALOG_STYLE_MSGBOX,"{"cblue"}Регистрация", "{"cwhite"}Добро пожаловать на {"cblue"}Unigva RolePlay{"cwhite"}\n\nВы впервые зашли на этот сервер и для начала игры,\
		вам нужно пройти регистрацию.\nПроцесс регистрации не займет много времени.", "Далее", "Выйти");
	}
	return 1;
}
publics CheckReferal(playerid, temp)
{
	new rows[2];
	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
	    new referal[26];
	    GetPVarString(playerid, "referal", referal, 26);
	    PlayerInfo[playerid][pReferal] = referal;

	    new string[128];
	    format(string, sizeof(string), "Вы указали, как реферала игрока - %s", PlayerInfo[playerid][pReferal]);
	    SCM(playerid, blue, string);

	    new query[94];
		format(query, sizeof(query), "UPDATE `accounts` SET `pReferal` = '%s' WHERE `pName` = '%s' LIMIT 1", PlayerInfo[playerid][pReferal], PlayerInfo[playerid][pName]);
		mysql_tquery(connects, query, "", "");
		RegStok(playerid);
	}
	else
	{
	    SCM(playerid, white, "Такого игрока не существует. Если вы не знаете других игроков нажмите кнопку 'Пропустить'");
		return SPD(playerid,4,DIALOG_STYLE_INPUT,"{"cblue"}Приглашение от игрока", "{"cwhite"}Введите ник игрока, пригласившего Вас на сервер\nТак-же Вы можете ввести промокод, если таковой имеется", "Далее", "Пропустить");
	}
	return 1;
}

stock ShowServerPassDialog(playerid)
{
	SPD(playerid, D_SERVER_PASS, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | Пароль от сервера", "{FFFFFF}Сервер запаролен.\nЕсли вы знаете пароль, то вы можете его ввести и зайти на сервер.\nВ противном случае, в данный момент на сервер вы зайти не можете!", "Далее", "Отмена");
	return 1;
}

stock RegStock(playerid)
{
	new Year, Month, Day, data[12], string[340], ip[18];
	getdate(Year, Month, Day);
	format(data,sizeof(data),"%d/%d/%d", Year, Month, Day);
	PlayerInfo[playerid][pLogin] = true;
	GetPlayerIp(playerid, ip, sizeof(ip));
    PlayerInfo[playerid][pLVL] = 1;
    PlayerInfo[playerid][pAFK] = 0;
	PlayerInfo[playerid][pCash] = 400;
	PlayerInfo[playerid][pMute] = -1;
    PlayerInfo[playerid][pJail] = -1;
	PlayerInfo[playerid][pZakon] = 0;
	PlayerInfo[playerid][pHP] = 100.0;
	PlayerInfo[playerid][pNeedToilet] = 100;
	PlayerInfo[playerid][pNeedEat] = 100; 
	PlayerInfo[playerid][pNeedDrink] = 100; 
	PlayerInfo[playerid][pNeedWash] = 100;
	SpID[playerid] = -1;

	mysql_format(connects, string, sizeof(string), "INSERT INTO `accounts`(`pName`, `pLVL`, `pKey`, `pChar`, `pSex`, `pCash`, `pDateReg`, `pRegIP`, `pEmail`, `pMute`, `pJail`) VALUES ('%s','%d',MD5('%s'),'%d','%d','%d','%s','%s','%s', '%d', '%d')", PlayerInfo[playerid][pName], PlayerInfo[playerid][pLVL], PlayerInfo[playerid][pKey], PlayerInfo[playerid][pChar],
	PlayerInfo[playerid][pSex], PlayerInfo[playerid][pCash], data, ip, PlayerInfo[playerid][pEmail], PlayerInfo[playerid][pMute], PlayerInfo[playerid][pJail]);
	mysql_tquery(connects, string, "", "");
	return 1;
}
stock RegStok(playerid)
{
    SpawnPlayer(playerid);
	SPD(playerid, D_GO_REG_TRAINING, DIALOG_STYLE_MSGBOX, "{"cblue"}Обучение", "{FFFFFF}Если вы на сервере впервые, то вы можете пройти обучение.\nВы желаете пройти обучение?", "Пройти", "Отмена");
	return SetSpawnVokzal(playerid);
}

publics PlayerSecondTimer(playerid)
{

    if(training_timer[playerid] > 0)
    {
		training_timer[playerid]--;
		switch(training_timer[playerid])
		{
			case 60: // - Шахта
			{
				SetPlayerCameraPos(playerid, 2342.2654, 1981.7173, 26.6535);
				SetPlayerCameraLookAt(playerid, 2342.9080, 1982.4899, 26.2436);
				SetPlayerPos(playerid, 2313.2966,2036.8577,11.9981);
			}
			case 50: // - Автошкола
			{
				for(new idx = 0; idx < 9; idx++)
					PlayerTextDrawHide(playerid, training_td[playerid][idx]);
					
				for(new idx = 9; idx < 18; idx++)
					PlayerTextDrawShow(playerid, training_td[playerid][idx]);
					
				SetPlayerCameraPos(playerid, 1939.1083, 2251.6011, 24.2016);
				SetPlayerCameraLookAt(playerid, 1938.4526, 2250.8381, 23.6466);
				SetPlayerPos(playerid, 1959.7449,2260.2537,12.6678);
			}
			case 40: // - Квартиры
			{
				for(new idx = 9; idx < 18; idx++)
					PlayerTextDrawHide(playerid, training_td[playerid][idx]);
				for(new idx = 18; idx < 28; idx++)
				    PlayerTextDrawShow(playerid, training_td[playerid][idx]);
				    
				SetPlayerCameraPos(playerid, 2113.0801, 1786.9546, 19.7348);
				SetPlayerCameraLookAt(playerid, 2113.5679, 1787.8352, 19.4598);
				SetPlayerPos(playerid, 2139.6240,1773.2572,12.0000);
			}
			case 30: // - Автосалон
			{
				for(new idx = 18; idx < 28; idx++)
					PlayerTextDrawHide(playerid, training_td[playerid][idx]);
				for(new idx = 28; idx < 38; idx++)
				    PlayerTextDrawShow(playerid, training_td[playerid][idx]);
				    
				SetPlayerCameraPos(playerid, 2032.1256, 1902.7820, 25.9034);
				SetPlayerCameraLookAt(playerid, 2031.6134, 1901.9167, 25.5184);
				SetPlayerPos(playerid, 2066.4194,1877.2097,12.0000);
			}
			case 20: // - Больница
			{
				for(new idx = 28; idx < 38; idx++)
					PlayerTextDrawHide(playerid, training_td[playerid][idx]);
				for(new idx = 38; idx < 47; idx++)
				    PlayerTextDrawShow(playerid, training_td[playerid][idx]);
				    
				SetPlayerCameraPos(playerid, 2002.1024, 1609.2822, 24.9018);
				SetPlayerCameraLookAt(playerid, 2001.1436, 1608.9752, 24.7218);
				SetPlayerPos(playerid, 2034.6138,1605.4178,15.3126);
			}
			case 10: // - Обучение пройдено
			{
				for(new idx = 38; idx < 47; idx++)
					PlayerTextDrawHide(playerid, training_td[playerid][idx]);
				
				KillTimer(training_timer[playerid]);
				
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, true);
				
				SetPlayerPos(playerid, 1823.5634,2528.6885,15.6825);
				SetPlayerFacingAngle(playerid, 130.7277);
				
				SCM(playerid, blue, "Поздравляем! Вы прошли обучение!");
				SCM(playerid, blue, "На остальные вопросы Вам ответит администрация или игроки на форуме.");
				SCM(playerid, blue, "Теперь отправляйтесь на шахту, чтобы заработать 5000-10000 рублей (/gps > 2. Подработки)");
			}
		}
    }
    #if defined reg_au__PlayerSecondTimer
        return reg_au__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer reg_au__PlayerSecondTimer
#if	defined	reg_au__PlayerSecondTimer
	forward reg_au__PlayerSecondTimer(playerid); 
#endif
