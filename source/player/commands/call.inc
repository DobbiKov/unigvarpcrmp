#define MAX_CALLING_SERVICE 5
#define MAX_CALLINGS        20

#define calling_mech        1
#define calling_taxi        2
#define calling_heal        3
#define calling_pps         4

new prop_called[MAX_PLAYERS];
new call_called[MAX_PLAYERS];


enum e_CALLING
{
    cID,
    cPlayerID,
    cText[144],
    Float: cX,
    Float: cY,
    Float: cZ,
};
new calling[MAX_CALLING_SERVICE][MAX_CALLINGS][e_CALLING];

publics PlayerSecondTimer(playerid)
{
    new hours,minutes,seconds;
    gettime(hours, minutes, seconds);

    if(call_called[playerid] != -1)
    {
        if(seconds % 5 == 0)
        {
            PlayerInfo[playerid][pPhoneCash] -= 5;
            if(PlayerInfo[playerid][pPhoneCash] <= 0)
            {
                PlayerInfo[playerid][pPhoneCash] = 0;
                SCM(playerid, red, "На мобильном счету закончились средства.");
                SCM(call_called[playerid], orange, "У собеседника на счету закончились средства.");

                new i;
                if(prop_called[playerid] != -1) i = prop_called[playerid];
                else if(call_called[playerid] != -1) i = call_called[playerid];

                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                if(call_called[i] != -1) SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);

                if(prop_called[playerid] != -1) prop_called[playerid] = -1;
                if(prop_called[i] != -1) prop_called[i] = -1;
                if(call_called[playerid] != -1) call_called[playerid] = -1;
                if(call_called[i] != -1) call_called[i] = -1;
                DeletePVar(playerid, "me_called");
                DeletePVar(i, "me_called");
            }
        }
    }

    #if defined call__PlayerSecondTimer
        return call__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer call__PlayerSecondTimer
#if	defined	call__PlayerSecondTimer
	forward call__PlayerSecondTimer(playerid); 
#endif


CMD:call(playerid, params[])
{
    if(PlayerInfo[playerid][pPhoneNumber] < 1) return SCM(playerid, red, "У вас нет телефона, или сим-карты.");
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "У вас стоит блокировка чата!");
    if(!strlen(params)) return Call(playerid);
    else
    {
        extract params -> new number; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /call [номер абонента]");
        if(PlayerInfo[playerid][pPhoneNumber] < 1) return SCM(playerid, red, "У вас нет телефона, или сим-карты.");
        if(PlayerInfo[playerid][pPhoneCash] < 10) return SCM(playerid, red, "На балансе телефона недостаточно средств.");
        if(PlayerInfo[playerid][pPhoneStatus] == 1) return SCM(playerid, red, "Ваш телефон выключен.");
        if(number == PlayerInfo[playerid][pPhoneNumber]) return SCM(playerid, red, "Вы ввели свой номер телефона.");

        foreach(new i : Player)
        {
            if(IsPlayerConnected(i) && PlayerInfo[i][pLogin] != false)
            {
                if(number == PlayerInfo[i][pPhoneNumber] && PlayerInfo[i][pPhone] >= 1 && PlayerInfo[i][pPhoneNumber] > 0)
                {
                    if(PlayerInfo[i][pPhoneStatus] == 1) return SCM(playerid, red, "Телефон вне зоны действия.");
                    if(PlayerInfo[i][pPhoneCash] < 10) return SCM(playerid, red, "У абонента на счету недостаточно средств.");
                    if(prop_called[playerid] != -1 || call_called[playerid] != -1) return SCM(playerid, red, "Вы уже кому-то звоните.");
                    if(prop_called[i] != -1 || call_called[i] != -1) return SCM(playerid, red, "Линия занята.");

                    prop_called[playerid] = i;
                    prop_called[i] = playerid;
                    new string[144];
                    format(string, sizeof(string), "Исходящий звонок | Номер: {FFFFFF}%d {"cblue"}| Вызываемый: {FFFFFF}%s", PlayerInfo[i][pPhoneNumber], PlayerInfo[i][pName]);
                    SCM(playerid, blue, string);
                    SCM(playerid, white, "Используйте {"corange"}/h {FFFFFF}чтобы отменить вызов.");

                    format(string, sizeof(string), "Входящий звонок | Номер: {FFFFFF}%d {"cblue"}| Вызывает: {FFFFFF}%s", PlayerInfo[playerid][pPhoneNumber], PlayerInfo[playerid][pName]);
                    SCM(i, blue, string);
                    SCM(i, white, "Используйте {"cgreen"}/p {FFFFFF}чтобы ответить или {"corange"}/h {FFFFFF}чтобы отклонить вызов.");
                    SetPVarInt(playerid, "me_called", 1);
                    return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
                }
            }
        }
        SCM(playerid, red, "Телефон вне зоны действия.");

    }

    return 1;
}
CMD:togphone(playerid)
{
    if(PlayerInfo[playerid][pVIP] == 0) return SCM(playerid, red, "Данная функция доступна только VIP игрокам.");
    switch(PlayerInfo[playerid][pPhoneStatus])
    {
        case 0:
        {
            SCM(playerid, orange, "Вы выключичили телефон.");
            PlayerInfo[playerid][pPhoneStatus] = 1;
        }
        case 1:
        {
            SCM(playerid, orange, "Вы включили телефон.");
            PlayerInfo[playerid][pPhoneStatus] = 0;
        }
    }
    return 1;
}
CMD:p(playerid)
{
    if(GetPVarInt(playerid, "me_called") == 1) return SCM(playerid, red, "Вы уже звоните кому-то.");
    if(prop_called[playerid] == -1) return SCM(playerid, red, "Вам никто не звонит.");

    new i = prop_called[playerid];
    prop_called[playerid] = -1;
    prop_called[i] = -1;
    call_called[i] = playerid;
    call_called[playerid] = i;
    SCM(playerid, 0x99CC00FF, "Вы подняли трубку.");
    SCM(i, 0x99CC00FF, "Собеседник поднял трубку.");
    DeletePVar(playerid, "me_called");
    DeletePVar(i, "me_called");
    return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
}
CMD:h(playerid)
{
    if(prop_called[playerid] == -1 && call_called[playerid] == -1) return SCM(playerid, red, "Вам никто не звонит.");

    new i;
    if(prop_called[playerid] != -1) i = prop_called[playerid];
    else if(call_called[playerid] != -1) i = call_called[playerid];

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    if(call_called[i] != -1) SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);

    if(prop_called[playerid] != -1) prop_called[playerid] = -1;
    if(prop_called[i] != -1) prop_called[i] = -1;
    if(call_called[playerid] != -1) call_called[playerid] = -1;
    if(call_called[i] != -1) call_called[i] = -1;

    SCM(playerid, orange, "Вы положили трубку.");
    SCM(i, orange, "Собеседник положил трубку.");
    DeletePVar(playerid, "me_called");
    DeletePVar(i, "me_called");
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(prop_called[playerid] != -1)
    {
        new i = prop_called[playerid];
        prop_called[playerid] = -1;
        prop_called[i] = -1;
        DeletePVar(playerid, "me_called");
        DeletePVar(i, "me_called");
        SCM(i, orange, "Обрыв связи. (( игрок опкинул игру ))");
    }
    if(call_called[playerid] != -1)
    {
        new i = call_called[playerid];
        call_called[playerid] = -1;
        call_called[i] = -1;
        DeletePVar(playerid, "me_called");
        DeletePVar(i, "me_called");
        SCM(i, orange, "Обрыв связи. (( игрок опкинул игру ))");
    }
	#if	defined	call__OnPlayerDisconnect
		return call__OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerDisconnect
	#undef	OnPlayerDisconnect
#else
	#define	_ALS_OnPlayerDisconnect
#endif

#define	OnPlayerDisconnect call__OnPlayerDisconnect
#if	defined	call__OnPlayerDisconnect
	forward call__OnPlayerDisconnect(playerid, reason);
#endif

CMD:calling(playerid)
{
    new index;
    if(PlayerInfo[playerid][pJob] == Job_Car) index = 1;
    else if(PlayerInfo[playerid][pJob] == Job_Taxi) index = 2;
    else if(PlayerInfo[playerid][pMember] == TEAM_HEAL) index = 3;
    else if(IsAPolice(playerid)) index = 4;
    else return YouCannotUseThisFunc(playerid);

    new bool: temp = false;
    for(new i = 0; i < MAX_CALLINGS; i++) 
    {
        if( calling[index][i][cID] != -1 )
        {
            temp = true;
            break;
        } 
    }
    if(temp == false) return SCM(playerid, red, "В данный момент никаких вызовов нет!");

    new sttr[2000], string[128], count = 0;
    for(new i = 0; i < MAX_CALLINGS; i++)
    {
        if(calling[index][i][cID] != -1)
        {
            new Float: dist = GetPlayerDistanceFromPoint(playerid, calling[index][i][cX], calling[index][i][cY], calling[index][i][cZ]);
            format(string, sizeof(string), "{FFFFFF}%s[%d] (%f м.)\n", PlayerInfo[ calling[index][i][cPlayerID] ][pName], calling[index][i][cPlayerID], floatround(dist, floatround_round));
            strcat(sttr, string);

            dialog_listitem_values[playerid][count] = i;
            count++;
        }
    }
    return SPD(playerid, D_CALLING, DIALOG_STYLE_LIST, "{"cblue"}Вызовы", sttr, "Далее", "Закрыть");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_CALL:
        {
            if(!response) return 1;
            else
            {
                switch(listitem)
                {
                    case 0:
                    {
                        if(CheckCall(1, playerid)) return SCM(playerid, red, "Вы уже вызвали автомеханика, ожидайте!");
                        CallMech(playerid);
                    }
                    case 1:
                    {
                        if(CheckCall(2, playerid)) return SCM(playerid, red, "Вы уже вызвали такси, ожидайте!");
                        CallTaxi(playerid);
                    }
                    case 2: 
                    {
                        if(CheckCall(3, playerid)) return SCM(playerid, red, "Вы уже вызвали скорую помощь, ожидайте!");
                        CallHeal(playerid);
                    }
                    case 3: 
                    {
                        if(CheckCall(4, playerid)) return SCM(playerid, red, "Вы уже вызвали полицию, ожидайте!");
                        CallPolice(playerid);
                    }
                }
            }
        }
        case D_CALLING:
        {
            if(response)
            {
                new index, string[128], ind, to_player;
                if(PlayerInfo[playerid][pJob] == Job_Car) index = 1;
                else if(PlayerInfo[playerid][pJob] == Job_Taxi) index = 2;
                else if(PlayerInfo[playerid][pMember] == TEAM_HEAL) index = 3;
                else if(IsAPolice(playerid)) index = 4;
                else return YouCannotUseThisFunc(playerid); 

                ind = dialog_listitem_values[playerid][listitem];
                to_player = calling[index][ind][cPlayerID];

                format(string, sizeof(string), "Вы приняли вызов %s. Его местоположение отмечено на карте.", PlayerInfo[to_player][pName]);
                SCM(playerid, green, string);

                format(string, sizeof(string), "%s %s принял ваш вызов, ожидайте.", (PlayerInfo[playerid][pMember] > 0) ? ( PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ] ) : ( jobs_name[ PlayerInfo[playerid][pJob] ] ), PlayerInfo[playerid][pName]);
                SCM(to_player, green, string);

                SetPlayerCheckpoint(playerid, calling[index][ind][cX], calling[index][ind][cY], calling[index][ind][cZ], 5.0);
                pCheckpoint[playerid] = CP_CALLING;

                ClearCalling(index, ind);
            }
        }


        case D_CALL_MECH:
        {
            if(!response) Call(playerid);
            else
            {
                if(strlen(inputtext) < 6 || strlen(inputtext) > 20) return CallMech(playerid);

                new calltext[21], string[144];
                format(calltext, sizeof(calltext), "%s", inputtext);
                format(string, sizeof(string), "{"cblue"}[Дисптчер] %s[%d] вызывает. Описание: %s.", PlayerInfo[playerid][pName], playerid, calltext);
                SCM(playerid, blue, "[Диспетчер] Мы оповестили всех автомехаников в вашем районе.");

                foreach(new i : Player) if(PlayerInfo[i][pJob] == Job_Car) SCM(i, blue, string), SCM(i, blue, "Принять вызов: /calling");
                static const index = 1;
                for(new i = 0; i < MAX_CALLINGS; i++)
                {
                    if( calling[index][i][cPlayerID] != -1 ) continue;

                    calling[index][i][cPlayerID] = playerid;
                    calling[index][i][cID] = i;
                    strcat(calling[index][i][cText], calltext);
                    GetPlayerPos(playerid, calling[index][i][cX], calling[index][i][cY], calling[index][i][cZ]);
                    break;
                }
            }
        }
        case D_CALL_TAXI:
        {
            if(!response) Call(playerid);
            else
            {
                if(strlen(inputtext) < 6 || strlen(inputtext) > 20) return CallTaxi(playerid);

                new calltext[21], string[144];
                format(calltext, sizeof(calltext), "%s", inputtext);
                format(string, sizeof(string), "{"cblue"}[Дисптчер] %s[%d] вызывает. Описание: %s.", PlayerInfo[playerid][pName], playerid, calltext);
                SCM(playerid, blue, "[Диспетчер] Мы оповестили всех таксистов в вашем районе.");

                foreach(new i : Player) if(PlayerInfo[i][pJob] == Job_Taxi) SCM(i, blue, string), SCM(i, blue, "Принять вызов: /calling");
                static const index = 2;
                for(new i = 0; i < MAX_CALLINGS; i++)
                {
                    if( calling[index][i][cPlayerID] != -1 ) continue;

                    calling[index][i][cPlayerID] = playerid;
                    calling[index][i][cID] = i;
                    strcat(calling[index][i][cText], calltext);
                    GetPlayerPos(playerid, calling[index][i][cX], calling[index][i][cY], calling[index][i][cZ]);
                    break;
                }
            }
        }
        case D_CALL_HEAL:
        {
            if(!response) Call(playerid);
            else
            {
                if(strlen(inputtext) < 6 || strlen(inputtext) > 20) return CallHeal(playerid);

                new calltext[21], string[144];
                format(calltext, sizeof(calltext), "%s", inputtext);
                format(string, sizeof(string), "{"cblue"}[Дисптчер] %s[%d] вызывает. Описание: %s.", PlayerInfo[playerid][pName], playerid, calltext);
                SCM(playerid, blue, "[Диспетчер] Мы оповестили все скорые помощи в вашем районе.");
                foreach(new i : Player) if(PlayerInfo[i][pMember] == TEAM_HEAL) SCM(i, blue, string), SCM(i, blue, "Принять вызов: /calling");
                static const index = 3;
                for(new i = 0; i < MAX_CALLINGS; i++)
                {
                    if( calling[index][i][cPlayerID] != -1 ) continue;

                    calling[index][i][cPlayerID] = playerid;
                    calling[index][i][cID] = i;
                    strcat(calling[index][i][cText], calltext);
                    GetPlayerPos(playerid, calling[index][i][cX], calling[index][i][cY], calling[index][i][cZ]);
                    break;
                }
            }
        }
        case D_CALL_PPS:
        {
            if(!response) Call(playerid);
            else
            {
                if(strlen(inputtext) < 6 || strlen(inputtext) > 20) return CallPolice(playerid);

                new calltext[21], string[144];
                format(calltext, sizeof(calltext), "%s", inputtext);
                format(string, sizeof(string), "{"cblue"}[Дисптчер] %s[%d] вызывает. Описание: %s.", PlayerInfo[playerid][pName], playerid, calltext);
                SCM(playerid, blue, "[Диспетчер] Мы оповестили все патрули в вашем районе.");
                foreach(new i : Player) if(IsAPolice(i)) SCM(i, blue, string), SCM(i, blue, "Принять вызов: /calling");
                static const index = 4;
                for(new i = 0; i < MAX_CALLINGS; i++)
                {
                    if( calling[index][i][cPlayerID] != -1 ) continue;

                    calling[index][i][cPlayerID] = playerid;
                    calling[index][i][cID] = i;
                    strcat(calling[index][i][cText], calltext);
                    GetPlayerPos(playerid, calling[index][i][cX], calling[index][i][cY], calling[index][i][cZ]);
                    break;
                }
            }
        }
    }
	#if	defined	call__OnDialogResponse
		return call__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse call__OnDialogResponse
#if	defined	call__OnDialogResponse
	forward call__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
    {
        case CP_CALLING:
        {
            SCM(playerid, green, "Вы прибыли на место вызова!");
            DisablePlayerCheckpoint(playerid);
        }
    }
    #if defined call__OnPlayerEnterCheckpoint
        return call__OnPlayerEnterCheckpoint(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_OnPlayerEnterCheckpoint
	#undef	OnPlayerEnterCheckpoint
#else
	#define	_ALS_OnPlayerEnterCheckpoint
#endif

#define	OnPlayerEnterCheckpoint call__OnPlayerEnterCheckpoint
#if	defined	call__OnPlayerEnterCheckpoint
	forward call__OnPlayerEnterCheckpoint(playerid);
#endif

stock Call(playerid)
{
    return SPD(playerid, D_CALL, DIALOG_STYLE_LIST, "{"cblue"}Сервисы", "{"cblue"}1. {FFFFFF}Вызвать механика\n{"cblue"}2. {FFFFFF}Вызвать такси\n{"cblue"}3. {FFFFFF}Вызвать скорую помощь\n{"cblue"}4. {FFFFFF}Вызвать полицию", "Далее", "Закрыть");
}
stock CallMech(playerid)
{
    return SPD(playerid, D_CALL_MECH, DIALOG_STYLE_INPUT, "{"cblue"}Вызвать Механика", "{FFFFFF}Опишите место где вы находитесь\n{AFAFAF}Сообщение должно состоять из 6 до 20 символов!", "Выызвать", "Назад");
}
stock CallTaxi(playerid)
{
    return SPD(playerid, D_CALL_TAXI, DIALOG_STYLE_INPUT, "{"cblue"}Вызвать такси", "{FFFFFF}Опишите место где вы находитесь\n{AFAFAF}Сообщение должно состоять из 6 до 20 символов!", "Выызвать", "Назад");
}
stock CallHeal(playerid)
{
    return SPD(playerid, D_CALL_HEAL, DIALOG_STYLE_INPUT, "{"cblue"}Вызвать скорую помощь", "{FFFFFF}Опишите место где вы находитесь\n{AFAFAF}Сообщение должно состоять из 6 до 20 символов!", "Выызвать", "Назад");
}
stock CallPolice(playerid)
{
    return SPD(playerid, D_CALL_PPS, DIALOG_STYLE_INPUT, "{"cblue"}Вызвать полицию", "{FFFFFF}Опишите место где вы находитесь\n{AFAFAF}Сообщение должно состоять из 6 до 20 символов!", "Выызвать", "Назад");
}
stock ClearCalling(index, ind)
{
    calling[index][ind][cID] = -1;
    calling[index][ind][cPlayerID] = -1;
    calling[index][ind][cText] = EOS;
    calling[index][ind][cX] = 0.0;
    calling[index][ind][cY] = 0.0;
    calling[index][ind][cZ] = 0.0;
    return 1;
}
stock ClearCallingsForPlayer(playerid)
{
    for(new i = 0; i < MAX_CALLING_SERVICE; i++)
    {
        for(new j = 0; j < MAX_CALLINGS; j++)
        {
            if(calling[i][j][cPlayerID] == playerid)
            {
                calling[i][j][cID] = -1;
                calling[i][j][cPlayerID] = -1;
                calling[i][j][cText] = EOS;
                calling[i][j][cX] = 0.0;
                calling[i][j][cY] = 0.0;
                calling[i][j][cZ] = 0.0;
            }
        }
    }
    return 1;
}
stock CheckCall(index, playerid)
{
    for(new i = 0; i < MAX_CALLINGS; i++)
    {
        if(calling[index][i][cPlayerID] == playerid) return true;
        break;
    }
    return false;
}
