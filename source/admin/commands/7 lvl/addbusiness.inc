CMD:addbusiness(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(totalbusiness > MAX_BUSINESS) return SCM(playerid, red, "На сервере превышен лимит бизнесов!");

    extract params -> new type, price; else
    {
        SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /addbusiness [тип бизнеса] [цена бизнеса]");
        return SCM(playerid, blue, "[тип бизнеса]: {FFFFFF}1 - 24/7 | 2 - аптека | 3 - столовая | 4 - казино | 5 - СТО | 6 - АЗС");
    }
    if(type < 1 || type > 6)
    {
        SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /addbusiness [тип бизнеса] [цена бизнеса]");
        return SCM(playerid, blue, "[тип бизнеса]: {FFFFFF}1 - 24/7 | 2 - аптека | 3 - столовая | 4 - казино | 5 - СТО | 6 - АЗС");        
    }

    new Float:x, Float:y, Float:z;
    new sql[256];
    GetPlayerPos(playerid, x, y, z);

    format(
        sql, sizeof(sql), 
        "INSERT INTO `bussines` (`bOwned`, `bOwner`, `bPrice`, `bType`, `bExitX`, `bExitY`, `bExitZ`) VALUES ('0', 'None', '%d', '%d', '%f', '%f', '%f')",
        price, type, x, y, z
    );
    mysql_tquery(connects, sql, "", "");

    SCM(playerid, green, "Вы успешно создали бизнес! Он появится после перезагрузки сервера!");
    return 1;
}