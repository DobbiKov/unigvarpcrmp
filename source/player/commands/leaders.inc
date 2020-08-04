CMD:leaders(playerid)
{
    new string[128], sttr[2000], text[20], zam, leaders;
    strcat(sttr, "{"cblue"}Организация - Должность - Имя - Телефон\n\n");
    foreach(new i : Player)
    {
        if(!IsPlayerConnected(i) || PlayerInfo[i][pLogin] != true) continue;

        if(PlayerInfo[i][pRang] >= 9)
        {
            if(PlayerInfo[i][pPhoneNumber] < 1) format(text, sizeof(text), "None");
            else format(text, sizeof(text), "%d", PlayerInfo[i][pPhoneNumber]);

            format(string, sizeof(string), "{FFFFFF}%s - %s - %s - %s\n", GetMember[ PlayerInfo[i][pMember] ], PlayerRank[ PlayerInfo[i][pMember] ][ PlayerInfo[i][pRang] ], PlayerInfo[i][pName], text);
            strcat(sttr, string);

            if(PlayerInfo[i][pRang] == 9) zam++;
            else if(PlayerInfo[i][pRang] == 10) leaders++;
        }
    }
    format(string, sizeof(string), "\n{"cblue"}Всего лидеров: {FFFFFF}%d. {"cblue"}Всего заместителей: {FFFFFF}%d.", leaders, zam);
    strcat(sttr, string);
    return SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Лидеры/Заместители онлайн", sttr, "Закрыть", "");
}