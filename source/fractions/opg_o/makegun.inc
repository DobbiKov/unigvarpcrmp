enum
    E_GUN_DATA
{
	makegun_name[32],
	gun_metal,
	gun_id
};

new const
    gunlist[][E_GUN_DATA] =
{
	{"Пистолет", 15, 22},
	{"Пистолет с глушителем", 12, 23},
	{"Desert Eagle", 15, 24},
	{"ТЕК-9", 15, 32},
	{"Узи", 17, 28},
	{"МП5", 20, 29},
	{"Дробовик", 17, 25},
	{"Обрез", 20, 26},
	{"Боевой дробовик", 25, 27},
	{"АК-47", 25, 30},
	{"М4", 30, 31},
	{"Country Rifle", 20, 34},
	{"Sniper Rifle", 30, 33}
};

CMD:makegun(playerid)
{
    if(!IsAOpg(playerid) && PlayerInfo[playerid][pVIP] < 1) return YouCannotUseThisFunc(playerid);

    ShowPlayerDialogCreateGun(playerid);
    return 1;
}

stock ShowPlayerDialogCreateGun(playerid)
{
	new old_gun;
	new count;
	new fmt_str[80];
	new text[(sizeof fmt_str) * 10];

	for(new i; i < 12; i++)
	{
		if(old_gun == gunlist[i][gun_id]) continue;

		dialog_listitem_values[playerid][count] = i;
		count ++;

		old_gun = gunlist[i][gun_id];

		format(fmt_str, sizeof fmt_str, "{"cblue"}%d. {ffffff}%s{"cblue"}(%d металла)\n", i+1, gunlist[i][makegun_name], gunlist[i][gun_metal]);
		strcat(text, fmt_str);
	}

	SPD(playerid, D_CREATE_GUN, DIALOG_STYLE_LIST, "{"cblue"}Создание оружия", text, "Создать", "Отмена");
	return 1;
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_MAKEGUN_PATRONS:
        {
            if(!response) return ShowPlayerDialogCreateGun(playerid);
            else
            {
                if(!strlen(inputtext) || !IsNumeric(inputtext)) return SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, !"{"cblue"}Создание оружия | Патроны", !"{FFFFFF}Введите количество патронов, которое хотите поместить в оружие:", !"Далее", !"Назад");
                if(PlayerInfo[playerid][pPatr] < strval(inputtext)) return SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, !"{"cblue"}Создание оружия | Патроны", !"{"cred"}У вас нет такого количество патронов!\n\n{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", !"Далее", !"Назад");
            
                new i = dialog_listitem[playerid];
                new string[144];
                format(string, sizeof(string), "{"cblue"}Вы создали {"cyellow"}%s {"cblue"}в котором находится {"cyellow"}%d {"cblue"}патрон", gunlist[i][makegun_name], strval(inputtext));
                SCM(playerid, blue, string);

                GivePlayerWeaponAC(playerid, gunlist[i][gun_id], strval(inputtext));
                PlayerInfo[playerid][pMetall] -= gunlist[i][gun_metal];
            }
        }
        case D_CREATE_GUN:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(PlayerInfo[playerid][R_9MM] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 1:
                    {
                        if(PlayerInfo[playerid][R_USP] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 2:
                    {
                        if(PlayerInfo[playerid][R_DEAGLE] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 3:
                    {
                        if(PlayerInfo[playerid][R_TEK9] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 4:
                    {
                        if(PlayerInfo[playerid][R_USI] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 5:
                    {
                        if(PlayerInfo[playerid][R_MP5] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 6:
                    {
                        if(PlayerInfo[playerid][R_SHOTGUN] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 7:
                    {
                        if(PlayerInfo[playerid][R_SAWED_OF] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 8:
                    {
                        if(PlayerInfo[playerid][R_FIGHT_SHOTGUN] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 9:
                    {
                        if(PlayerInfo[playerid][R_AK47] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 10:
                    {
                        if(PlayerInfo[playerid][R_M4] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 11:
                    {
                        if(PlayerInfo[playerid][R_COUNTRY_RIFLE] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                    case 12:
                    {
                        if(PlayerInfo[playerid][R_SNIPER_RIFLE] < 1) return SCM(playerid, red, "У вас нет рецепта на данное оружие!");
                        if(PlayerInfo[playerid][pMetall] < gunlist[listitem][gun_metal]) return SCM(playerid, red, "У вас недостаточно металла!");

                        dialog_listitem[playerid] = listitem;
                        SPD(playerid, D_MAKEGUN_PATRONS, DIALOG_STYLE_INPUT, "{"cblue"}Создание оружия | Патроны", "{FFFFFF}Введите количество патронов, которое хотите поместить в оружие!", "Далее", "Назад");
                    }
                }
            }
        }
    }
	#if	defined	makegun__OnDialogResponse
		return makegun__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse makegun__OnDialogResponse
#if	defined	makegun__OnDialogResponse
	forward makegun__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif