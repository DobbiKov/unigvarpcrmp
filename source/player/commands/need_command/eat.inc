CMD:eat(playerid)
{
    if(PlayerInfo[playerid][pChips] <= 0) return SCM(playerid, red, "� ��� ��� ����!");
    if(PlayerInfo[playerid][pNeedEat] + 6 > 100) return SCM(playerid, red, "�� �� ������ ����!"); 

    PlayerInfo[playerid][pChips]--;
    PlayerInfo[playerid][pNeedEat] += 6;
    PlayerInfo[playerid][pNeedToilet] -= 2; 
    if(PlayerInfo[playerid][pNeedToilet] < 0) PlayerInfo[playerid][pNeedToilet] = 0;
    PlayerInfo[playerid][pNeedWash] -= 5;
    if(PlayerInfo[playerid][pNeedWash] < 0) PlayerInfo[playerid][pNeedWash] = 0;
    
    ClearAnimations(playerid);
    ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, false, 0, 0, 0, 0);

    return SCM(playerid, blue, "�� ����� �����, ��� ����� ������� �����!");
}