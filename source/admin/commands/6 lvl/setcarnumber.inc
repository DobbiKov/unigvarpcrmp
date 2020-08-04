CMD:setcarnumber(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new string: to_player[32], string: number[32]; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /setcarnumber [NickName игрока] [номер]");
    if(strlen(number) < 0 || strlen(number) > 32) return SCM(playerid, red, "Длина номера не менее 0 и не более 32.");
    foreach(new i : Player)
    {
        if(!strcmp(PlayerInfo[i][pName], to_player, false))
        {
            if(PlayerInfo[i][pCarID] == -1) return SCM(playerid, red, "У данного игрока нет автомобиля.");
            if(player_ownable_car[i] == -1) return SCM(playerid, red, "Личное авто данного игрока не создано.");

            ownable_car[player_ownable_car[i]][oc_number] = EOS;
            strcat(ownable_car[player_ownable_car[i]][oc_number], number);
            UpdateDynamic3DTextLabelText(ownable_car_label[player_ownable_car[i]], 0xFFFFFFFF, ownable_car[player_ownable_car[i]][oc_number]);

            new sql[144];
            format(sql, sizeof(sql), "UPDATE `ownable_cars` SET `number` = '%s' WHERE `id` = '%d'", number, ownable_car[player_ownable_car[i]][oc_id]);
            mysql_tquery(connects, sql, "", "");

            format(sql, sizeof(sql), "Вы выдали игроку %s номера на личный транспорт: %s", to_player, number);
            SCM(playerid, white, sql);

            SaveOwnableCar(i);
            return 1;
        }
    }
    new sql[144];
    format(sql, sizeof(sql), "SELECT * FROM `accounts` WHERE `pName` = '%s'", to_player);
    mysql_tquery(connects, sql, "CheckPlayerForSetCarNumber", "iss", playerid, to_player, number);
    return 1;
}

publics CheckPlayerForSetCarNumber(playerid, to_player[], number[])
{
    static rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        static carid, owner_id;
        carid = cache_get_field_content_int(0, "pCarID");
        owner_id = cache_get_field_content_int(0, "pID");
        if(carid == -1) return SCM(playerid, red, "У данного игрока нет личного транспорта.");

        new sql[144];
        format(sql, sizeof(sql), "UPDATE `ownable_cars` SET `number` = '%s' WHERE `owner_id` = '%d'", number, owner_id);
        mysql_tquery(connects, sql, "", "");

        format(sql, sizeof(sql), "Вы выдали игроку %s номера на личный транспорт: %s", to_player, number);
        SCM(playerid, white, sql);
    }
    else
    {
        return SCM(playerid, red, "Такого игрока нет.");
    }
    return 1;
}