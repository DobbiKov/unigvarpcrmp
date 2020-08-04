CMD:paintlist(playerid)
{
    new all = 0, string[144], fmt_dialog[2048] = "Номер | Имя Игрока\t\tКол-во убийств\n\n";
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pPaintKills] > 0) 
        {
            all++;
            format(string, sizeof(string), "{"cblue"}%d. {FFFFFF}%s\t\t%d убийств.\n", all, PlayerInfo[i][pName], PlayerInfo[i][pPaintKills]);
            strcat(fmt_dialog, string);
        }
    }
    if(all == 0) return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Пейнт-бол", "{FFFFFF}Список участников пейнт-бола пуст", "Закрыть", "");
    return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Пейнт-бол", fmt_dialog, "Закрыть", "");
}