publics minuteupdate()
{
	new hours,minutes,seconds;
    gettime(hours, minutes, seconds);

    foreach(new i : Player)
    if(minutes == 5 || minutes == 15 || minutes == 30 || minutes == 45)
    {
        PlayerInfo[i][pNeedToilet] -= 2;
        if(PlayerInfo[i][pNeedToilet] < 0) PlayerInfo[i][pNeedToilet] = 0;
        if(PlayerInfo[i][pNeedToilet] < 40) SCM(i, need, "�� ������ � ������!");

        PlayerInfo[i][pNeedEat] -= 4;
        if(PlayerInfo[i][pNeedEat] < 0) PlayerInfo[i][pNeedEat] = 0;
        if(PlayerInfo[i][pNeedEat] < 40) 
        {
            SCM(i, need, "�� �������������! �������� �������� ��� ������ ����� � 24/7. ������ ��������� ���������: /need");
            PlayerPlaySound(i, 40403, 0.0, 0.0, 0.0);
            new Float:health;
            GetPlayerHealth(i, health);
            PlayerInfo[i][pHP] = health - 3;
            SetPlayerHealth(i, health - 3);
        }
        PlayerInfo[i][pNeedDrink] -= 3;
        if(PlayerInfo[i][pNeedDrink] < 0) PlayerInfo[i][pNeedDrink] = 0;
        if(PlayerInfo[i][pNeedDrink] < 40)
        {
            SCM(i, need, "�� ������ ����! �������� �������� ��� ������ ����� � 24/7. ������ ��������� ���������: /need");
        }

        PlayerInfo[i][pNeedWash]--;
        if(PlayerInfo[i][pNeedWash] < 0) PlayerInfo[i][pNeedWash] = 0;
        if(PlayerInfo[i][pNeedWash] < 40)
        {
            cmd::do(i, "����� ������...");
            SCM(i, need, "�� ��������� ����� �������! �������� ���� ��� ��������� ���� � ����. ������ ��������� ���������: /need");
        }       
    }
    #if defined needs__minuteupdate
        return needs__minuteupdate();
    #else
        return 1;
    #endif
}
#if defined _ALS_minuteupdate
    #undef minuteupdate
#else
    #define _ALS_minuteupdate
#endif

#define minuteupdate needs__minuteupdate
#if defined needs__minuteupdate
    forward needs__minuteupdate();
#endif

CMD:need(playerid)
{
    new fmt_dialog[256];
    format(fmt_dialog, sizeof(fmt_dialog), "�������: \t%d%%\n�����: \t%d%%\n������: \t%d%%\n�������: \t%d%%", PlayerInfo[playerid][pNeedEat], PlayerInfo[playerid][pNeedDrink], PlayerInfo[playerid][pNeedToilet], PlayerInfo[playerid][pNeedWash]);
    SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}�����", fmt_dialog, "�������", "");
    return 1;
}