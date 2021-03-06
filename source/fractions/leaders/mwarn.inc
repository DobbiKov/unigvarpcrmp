CMD:mwarn(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == TEAM_NONE) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMember] == TEAM_FSB && PlayerInfo[playerid][pRang] < 5) return YouCannotUseThisFunc(playerid);
    else if(PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, string: reason[128]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /mwarn [ID ������] [�������]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pMember] != PlayerInfo[playerid][pMember]) return SCM(playerid, red, "����� �� ������� � ����� �����������!");
    if(PlayerInfo[to_player][pRang] > PlayerInfo[playerid][pRang]) return SCM(playerid, red, "����� ���� ��� �� �����!");

    PlayerInfo[to_player][pWarnF]++;

    new string[128];
    format(string, sizeof(string), "�� ������� ������� %s [%d|3]. �������: %s", PlayerInfo[to_player][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s ������ ��� ������� [%d|3]. �������: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], PlayerInfo[to_player][pWarnF], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%d", to_player);

    if(PlayerInfo[to_player][pWarnF] >= 3) 
    {
        format(string, sizeof(string), "%s ��� ������ �� ����� �����������. �������: 3 ��������", PlayerInfo[to_player][pName]);
        SCM(playerid, blue, string);

        format(string, sizeof(string), "�� ���� ������� �� ����������� \"%s\". �������: 3 ��������", GetMember[ PlayerInfo[to_player][pMember] ]);
        SCM(playerid, blue, string);

        PlayerInfo[to_player][pMember] = 0;
        PlayerInfo[to_player][pWarnF] = 0;
        PlayerInfo[to_player][pRang] = 0;
        PlayerInfo[to_player][pFSkin] = -1;
        SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
    }
    SaveAccounts(to_player);
    return 1;
}