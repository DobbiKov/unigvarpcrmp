CMD:lwarn(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new to_player, string: reason[128]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /lwarn [ID ������] [�������]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pRang] < 10) return SCM(playerid, red, "����� �� �������� ������� �����������!");

    PlayerInfo[to_player][pWarnF]++;

    new string[128];
    format(string, sizeof(string), "�� ����� ��������� ������� %s [%d|3]. �������: %s", PlayerInfo[to_player][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "������������ %s ����� ��� ��������� ������� [%d|3]. �������: %s", PlayerInfo[playerid][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(to_player, white, string);

    format(string, sizeof(string), "[A] %s[%d] ����� ��������� ������� %s[%d] [%d|3]. �������: %s", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, PlayerInfo[to_player][pWarnF], reason);
    SCMA(grey, string);

    format(string, sizeof(string), "%d", to_player);

    if(PlayerInfo[to_player][pWarnF] >= 3) 
    {
        format(string, sizeof(string), "%s ��� ������ �� �����������. �������: 3 ��������", PlayerInfo[to_player][pName]);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "�� ���� ������� �� ����������� \"%s\". �������: 3 ��������", GetMember[ PlayerInfo[to_player][pMember] ]);
        SCM(to_player, white, string);

        PlayerInfo[to_player][pMember] = 0;
        PlayerInfo[to_player][pWarnF] = 0;
        PlayerInfo[to_player][pRang] = 0;
        PlayerInfo[to_player][pFSkin] = -1;
        SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
    }
    SaveAccounts(to_player);
    return 1;
}