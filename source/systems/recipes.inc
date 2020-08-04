stock ShowDialogSelectRecipe(playerid)
{
	SPD
	(
		playerid, D_SELECT_RECIPE, DIALOG_STYLE_LIST,
		"{"cblue"}Рецепты",
		"{"cblue"}1. {FFFFFF}Пистолеты\n"\
		"{"cblue"}2. {FFFFFF}Пистолеты-пулемёты\n"\
		"{"cblue"}3. {FFFFFF}Дробовики\n"\
		"{"cblue"}4. {FFFFFF}Штурмовые винтовки\n"\
		"{"cblue"}5. {FFFFFF}Снайперские винтовки\n"\
		"{"cblue"}6. {FFFFFF}Гранаты",
		"Выбрать", "Отмена"
    );
    return 1;
}

stock ShowDialogBuyRecipeGuns(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS, DIALOG_STYLE_LIST,
		"{"cblue"}Пистолеты\n",\
		"{"cblue"}1. {FFFFFF}9mm - 20 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}SDPistol - 40 000 рублей\n"\
		"{"cblue"}3. {FFFFFF}Дигл - 100 000 рублей",
		"Выбрать", "Назад"
    );
	return 1;
}

stock ShowDialogBuyRecipeGuns_2(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS_2, DIALOG_STYLE_LIST,
		"{"cblue"}Пистолеты-пулемёты\n",\
		"{"cblue"}1. {FFFFFF}ТЕК-9 - 50 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}УЗИ - 75 000 рублей\n"\
		"{"cblue"}3. {FFFFFF}МП5 - 120 000 рублей",
		"Выбрать", "Назад"
    );
    return 1;
}

stock ShowDialogBuyRecipeGuns_3(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS_3, DIALOG_STYLE_LIST,
		"{"cblue"}Дробовики\n",\
		"{"cblue"}1. {FFFFFF}Шотган - 120 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}Обрез - 150 000 рублей\n"\
		"{"cblue"}3. {FFFFFF}Боевой дробовик - 200 000 рублей",
		"Выбрать", "Назад"
    );
    return 1;
}

stock ShowDialogBuyRecipeGuns_4(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS_4, DIALOG_STYLE_LIST,
		"{"cblue"}Штурмовые винтовки\n",\
		"{"cblue"}1. {FFFFFF}АК-47 - 200 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}М4 - 300 000 рублей",
		"Выбрать", "Назад"
    );
    return 1;
}

stock ShowDialogBuyRecipeGuns_5(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS_5, DIALOG_STYLE_LIST,
		"{"cblue"}Снайперские винтовки\n",\
		"{"cblue"}1. {FFFFFF}Contry Rifle - 150 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}Sniper Rifle - 300 000 рублей",
		"Выбрать", "Назад"
    );
    return 1;
}

stock ShowDialogBuyRecipeGuns_6(playerid)
{
	SPD
	(
		playerid, D_BUY_RECIPE_GUNS_6, DIALOG_STYLE_LIST,
		"{"cblue"}Гранаты\n",\
		"{"cblue"}1. {FFFFFF}Дымовая граната - 150 000 рублей\n"\
		"{"cblue"}2. {FFFFFF}Коктейль молотова - 300 000 рублей\n"\
		"{"cblue"}3. {FFFFFF}Взрывчатая граната - 600 000 рублей",
		"Выбрать", "Назад"
    );
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_SELECT_RECIPE:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0: ShowDialogBuyRecipeGuns(playerid);
                    case 1: ShowDialogBuyRecipeGuns_2(playerid);
                    case 2: ShowDialogBuyRecipeGuns_3(playerid);
                    case 3: ShowDialogBuyRecipeGuns_4(playerid);
                    case 4: ShowDialogBuyRecipeGuns_5(playerid);
                    case 5: ShowDialogBuyRecipeGuns_6(playerid);
                }
            }

        }
        case D_BUY_RECIPE_GUNS:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_9MM] == 1)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 20000)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -20000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия 9MM!");
                        PlayerInfo[playerid][R_9MM] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_USP] == 1)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 40000)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -40000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия SDPistol!");
                        PlayerInfo[playerid][R_USP] = 1;
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][R_DEAGLE] == 1)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 100000)
                        {
                            ShowDialogBuyRecipeGuns(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -100000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Desert Eagle!");
                        PlayerInfo[playerid][R_DEAGLE] = 1;
                    }
                }

            }
        }
        case D_BUY_RECIPE_GUNS_2:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_TEK9] == 1)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 50000)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -50000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Tec9!");
                        PlayerInfo[playerid][R_TEK9] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_USI] == 1)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 75000)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -75000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия УЗИ!");
                        PlayerInfo[playerid][R_USI] = 1;
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][R_MP5] == 1)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 120000)
                        {
                            ShowDialogBuyRecipeGuns_2(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -120000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия МП5!");
                        PlayerInfo[playerid][R_MP5] = 1;
                    }
                }

            }
        }
        case D_BUY_RECIPE_GUNS_3:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_SHOTGUN] == 1)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 120000)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -120000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Шотган!");
                        PlayerInfo[playerid][R_SHOTGUN] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_SAWED_OF] == 1)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 150000)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -150000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Обрез!");
                        PlayerInfo[playerid][R_SAWED_OF] = 1;
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][R_FIGHT_SHOTGUN] == 1)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 200000)
                        {
                            ShowDialogBuyRecipeGuns_3(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -200000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Боевой Дробовик!");
                        PlayerInfo[playerid][R_FIGHT_SHOTGUN] = 1;
                    }
                }
            }
        }
        case D_BUY_RECIPE_GUNS_4:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_AK47] == 1)
                        {
                            ShowDialogBuyRecipeGuns_4(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 200000)
                        {
                            ShowDialogBuyRecipeGuns_4(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -200000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия АК-47!");
                        PlayerInfo[playerid][R_AK47] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_M4] == 1)
                        {
                            ShowDialogBuyRecipeGuns_4(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 300000)
                        {
                            ShowDialogBuyRecipeGuns_4(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -300000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия М4!");
                        PlayerInfo[playerid][R_M4] = 1;
                    }
                }
            }
        }
        case D_BUY_RECIPE_GUNS_5:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_COUNTRY_RIFLE] == 1)
                        {
                            ShowDialogBuyRecipeGuns_5(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 150000)
                        {
                            ShowDialogBuyRecipeGuns_5(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -150000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Country Rifle!");
                        PlayerInfo[playerid][R_COUNTRY_RIFLE] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_SNIPER_RIFLE] == 1)
                        {
                            ShowDialogBuyRecipeGuns_5(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 300000)
                        {
                            ShowDialogBuyRecipeGuns_5(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -300000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Снайперкскую винктовку!");
                        PlayerInfo[playerid][R_SNIPER_RIFLE] = 1;
                    }
                }
            }
        }
        case D_BUY_RECIPE_GUNS_6:
        {
            if(!response) return ShowDialogSelectRecipe(playerid);
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_SMOKE] == 1)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 150000)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -150000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Дымовая Граната!");
                        PlayerInfo[playerid][R_SMOKE] = 1;
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_MOLOTOV] == 1)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 300000)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -300000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Коктейль Молотова!");
                        PlayerInfo[playerid][R_MOLOTOV] = 1;
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][R_GRENADE] == 1)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас уже есть данный рецепт!");
                        }                       
                        if(PlayerInfo[playerid][pCash] < 600000)
                        {
                            ShowDialogBuyRecipeGuns_6(playerid);
                            return SCM(playerid, red, "У вас не достаточно денег!");
                        }

                        GiveMoney(playerid, -600000, "Покупка рецепта на оружие");
                        SCM(playerid, green, "Вы успешно купили рецепт для оружия Осколочная граната!");
                        PlayerInfo[playerid][R_GRENADE] = 1;
                    }
                    
                }
            }
        }
    }
	#if	defined	recipes__OnDialogResponse
		return recipes__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse recipes__OnDialogResponse
#if	defined	recipes__OnDialogResponse
	forward recipes__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 2003.2611,1339.8290,26.1513))
        {
            ShowDialogSelectRecipe(playerid);
        }
    }
	#if	defined	recipes__OnPlayerKeyStateChange
		return recipes__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange recipes__OnPlayerKeyStateChange
#if	defined	recipes__OnPlayerKeyStateChange
	forward recipes__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif