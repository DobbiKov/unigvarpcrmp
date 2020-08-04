CMD:addtoilet(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(totaltoilets > MAX_TOILETS) return SCM(playerid, red, "На сервере превышен лимит туалетов!");

    new Float:x, Float:y, Float:z;
    new sql[256];
    GetPlayerPos(playerid, x, y, z);

    format(
        sql, sizeof(sql), 
        "INSERT INTO `toilets` (`tEnterX`, `tEnterY`, `tEnterZ`) VALUES ('%f', '%f', '%f')",
        x, y, z
    );
    mysql_tquery(connects, sql, "", "");

    new i = totaltoilets;

    ToiletInfo[i][tEnterX] = x;
    ToiletInfo[i][tEnterY] = y;
    ToiletInfo[i][tEnterZ] = z;

    ToiletInfo[i][tLabel] = CreateDynamic3DTextLabel("{"cblue"}[ ТУАЛЕТ ]\n{"cwhite"}Нажмите {"cblue"}L. Alt {"cwhite"}что б войти в туалет", 0xFFFFFFFF, ToiletInfo[i][tEnterX], ToiletInfo[i][tEnterY], ToiletInfo[i][tEnterZ]+1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);

    totaltoilets++;

    Iter_Add(AllToilets, i);

    SCM(playerid, green, "Вы успешно создали туалет!");
    return 1;
}