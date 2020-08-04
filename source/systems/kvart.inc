publics LoadKvart()
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            KvartInfo[i][kvart_id] = cache_get_field_content_int(i, "kvart_id");
            KvartInfo[i][kvart_days] = cache_get_field_content_int(i, "kvart_days");
            KvartInfo[i][kvart_type] = cache_get_field_content_int(i, "kvart_type");
            KvartInfo[i][kvart_pod_id] = cache_get_field_content_int(i, "kvart_pod_id");
            KvartInfo[i][kvart_Owned] = cache_get_field_content_int(i, "kvart_Owned");
            cache_get_field_content(i, "kvart_Owner", KvartInfo[i][kvart_Owner], connects, 64);
            
            if(KvartInfo[i][kvart_Owned] == 0) TotalFreeKvart++;
            totalkvart++;

            Iter_Add(Allkvart, i);
            BuyKvart(i);
        }
    }
    printf("[UNIGVA]: Всего загружено квартир: %d", totalkvart);
    return 1;
}

stock BuyKvart(i)
{
	if(KvartInfo[i][kvart_Owned] == 0)
    {
	    DestroyDynamicPickup(KvartInfo[i][kvart_pick]);
	    KvartInfo[i][kvart_pick] = CreateDynamicPickup(1273, 23, KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_x], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_y], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_z], KvartInfo[i][kvart_pod_id]);
	    return 1;
	}
	if(KvartInfo[i][kvart_Owned] == 1)
	{
	    DestroyDynamicPickup(KvartInfo[i][kvart_pick]);
	    KvartInfo[i][kvart_pick] = CreateDynamicPickup(1272, 23, KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_x], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_y], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_z], KvartInfo[i][kvart_pod_id]);
	    return 1;
	}    
    return 1;
}

stock SaveKvart(i)
{
    new sql[1024];
    format
    (
        sql, sizeof(sql), 
        "UPDATE `kvart` SET `kvart_id` = '%d', `kvart_days` = '%d', `kvart_type` = '%d', `kvart_pod_id` = '%d', `kvart_Owned` = '%d', `kvart_Owner` = '%s' WHERE `kvart_id` = '%d'",
        KvartInfo[i][kvart_id],
        KvartInfo[i][kvart_days],
        KvartInfo[i][kvart_type],
        KvartInfo[i][kvart_pod_id],
        KvartInfo[i][kvart_Owned],
        KvartInfo[i][kvart_Owner],
        KvartInfo[i][kvart_id]
    );
    mysql_tquery(connects, sql, "", "");
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(player_in_kvart[playerid] != -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.0, kvart_params[0][kvart_exit_x], kvart_params[0][kvart_exit_y], kvart_params[0][kvart_exit_z]))
            {
                foreach(new i : Allkvart) if(player_in_kvart[playerid] == KvartInfo[i][kvart_id])
                {
                    SetPlayerPos(playerid, KvartPos[ KvartInfo[i][kvart_type] ][kvart_enter_pos_x], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_y], KvartPos[KvartInfo[i][kvart_type]][kvart_enter_pos_z]);
                    SetPlayerVirtualWorld(playerid, KvartInfo[i][kvart_pod_id]);
                    player_in_podezd[playerid] = KvartInfo[i][kvart_pod_id];
                    FreezePlayer(playerid, 2000);
                    return player_in_kvart[playerid] = -1;
                }
            }
        }
        else
        {
            for(new i = 0; i != 8; i++)
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.0, KvartPos[i][kvart_enter_pos_x], KvartPos[i][kvart_enter_pos_y], KvartPos[i][kvart_enter_pos_z]))
                {
                    foreach(new j : Allkvart) if(KvartInfo[j][kvart_pod_id] == player_in_podezd[playerid] && KvartInfo[j][kvart_type] == i)
                    {
                        new owner[MAX_PLAYER_NAME] = "Государство";
                        if(KvartInfo[i][kvart_Owned] == 1) format(owner, sizeof(owner), "%s", KvartInfo[i][kvart_Owner]);
                        new fmt_dialog[256];
                        format
                        (
                            fmt_dialog, sizeof(fmt_dialog),
                            "{FFFFFF}\
                            Квартира: \t\t{"cblue"}№%d{FFFFFF}\n\
                            Владелец: \t\t{"cblue"}%s{FFFFFF}\n\
                            Стоимость: \t\t{"cblue"}%d рублей{FFFFFF}\n\
                            Арендная плата: \t{"cblue"}%d рублей{FFFFFF}\n\n\
                            Вы уверенны, что хотите войти в квартиру?",
                            KvartInfo[i][kvart_type]+1,
                            owner,
                            2000,
                            2000
                        );
                        SPD
                        (
                            playerid, D_ENTER_KVART, DIALOG_STYLE_MSGBOX,
                            "{"cblue"}Квартира",
                            fmt_dialog,
                            "Войти", "Отмена"
                        );
                        return SetPVarInt(playerid, "enter_kvart", j);
                    }
                }
            }
        }
    }
	#if	defined	kvart__OnPlayerKeyStateChange
		return kvart__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange kvart__OnPlayerKeyStateChange
#if	defined	kvart__OnPlayerKeyStateChange
	forward kvart__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_ENTER_KVART:
        {
            if(!response) return DeletePVar(playerid, "enter_kvart");
            else
            {
                new j = GetPVarInt(playerid, "enter_kvart");
                SetPlayerVirtualWorld(playerid, KvartInfo[j][kvart_id]);
                FreezePlayer(playerid, 2000);
                SetPlayerPos(playerid, kvart_params[0][kvart_exit_x], kvart_params[0][kvart_exit_y], kvart_params[0][kvart_exit_z]);
                player_in_podezd[playerid] = -1;
                player_in_kvart[playerid] = KvartInfo[j][kvart_id];
                return DeletePVar(playerid, "enter_kvart");
            }
        }
    }
	#if	defined	kvart__OnDialogResponse
		return kvart__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse kvart__OnDialogResponse
#if	defined	kvart__OnDialogResponse
	forward kvart__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics minuteupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);
    if(hour == 00 && minute == 20)
    {
        foreach(new i : Allkvart) if(KvartInfo[i][kvart_Owned] == 1)
        {
            KvartInfo[i][kvart_days]--;
            SaveKvart(i);
            if(KvartInfo[i][kvart_days] <= 0)
            {
                foreach(new j : Player)
                {
                    if(PlayerInfo[j][pKvartID] == KvartInfo[i][kvart_id])
                    {
                        SCM(j, green, "Ваша квартира была продана государству за неуплату.");

                        PlayerInfo[j][pKvartID] = -1;

                        KvartInfo[i][kvart_Owned] = 0;
                        KvartInfo[i][kvart_days] = 3;
                        KvartInfo[i][kvart_Owner] = EOS;
                        format(KvartInfo[i][kvart_Owner], MAX_PLAYER_NAME, "None");
                        SaveAccounts(j);
                        SaveKvart(i);
                        return BuyKvart(i);
                    }
                }
                KvartInfo[i][kvart_days] = 3;
                KvartInfo[i][kvart_Owned] = 0;
                KvartInfo[i][kvart_Owner] = EOS;
                format(KvartInfo[i][kvart_Owner], MAX_PLAYER_NAME, "None");
                SaveKvart(i);
                BuyKvart(i);

                new offkvartmess[144] = "Ваша квартира была передана государству, за неуплату.";

                new sql[144];
                format(sql, sizeof(sql), "UPDATE `accounts` SET `pKvartOffMess` = '%s', `pKvartID` = '-1' WHERE `pKvartID` = '%d'", offkvartmess, KvartInfo[i][kvart_id]);
                return mysql_tquery(connects, sql, "", "");
            }
        }
    }
	#if	defined	kvart__minuteupdate
		return kvart__minuteupdate();
	#else
		return 1;
	#endif
}
#if	defined	_ALS_minuteupdate
	#undef	minuteupdate
#else
	#define	_ALS_minuteupdate
#endif

#define	minuteupdate kvart__minuteupdate
#if	defined	kvart__minuteupdate
	forward kvart__minuteupdate();
#endif