CMD:invite(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == 0 || PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /invite [ID ������]");

    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
    if(!IsPlayerInRangeOfPlayer(playerid, to_player, 10.0)) return SCM(playerid, red, "����� ������� ������!");
    if(PlayerInfo[to_player][pFines] != 0) return SCM(playerid, red, "� ������ ���� ����������� ������!");
    if(PlayerInfo[to_player][pWarn] > 0) return SCM(playerid, red, "� ������ �������� �������������� �� ��������!");
    if(to_player == playerid) return SCM(playerid, red, "�� ������� ���� ID!");
    if(PlayerInfo[to_player][pMember] > 0) return SCM(playerid, red, "����� ������� � �����������!");
    if(IsAPolice(playerid) && PlayerInfo[to_player][pVoen] < 1) return SCM(playerid, red, "� ���������� ��� �������� ������!");
    if(PlayerInfo[to_player][pLVL] < 2) return SCM(playerid, red, "��������� ������� ���� ��������� � �������!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_INVITE, 0, 0);
}