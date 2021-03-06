enum e_dice_info
{
    Float: diceX,
    Float: diceY,
    Float: diceZ,
}
new DiceInfo[4][e_dice_info] = 
{
    {1686.4261,2074.9148,-6.9444},
    {1679.8751,2074.9407,-6.9444},
    {1679.8083,2061.9507,-6.9444},
    {1686.2913,2062.0479,-6.9444}
};

CMD:dice(playerid, params[])
{
    if(player_in_business[playerid] == -1 || BusinessInfo[player_in_business[playerid]][bType] != b_type_CASINO) return SCM(playerid, red, "�� ������ ��������� � ������.");
    for(new i = 0; i < sizeof(DiceInfo); i++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, DiceInfo[i][diceX], DiceInfo[i][diceY], DiceInfo[i][diceZ]))
        {
            extract params -> new to_player, cash; else return SCM(playerid, blue, "[���������]: {FFFFFF}����������� /dice [ID ������] [������]");
            if(to_player == playerid) return SCM(playerid, red, "�� ������� ���� ID!");
            if(cash < 500 || cash > 10000000) return SCM(playerid, red, "������ ������ ���� �� ����� 500 ������ � �� ����� 10 ��������� ������.");
            if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
            if(!IsPlayerInRangeOfPoint(to_player, 3.0, DiceInfo[i][diceX], DiceInfo[i][diceY], DiceInfo[i][diceZ])) return SCM(playerid, red, "����� ������ �� ���.");
            if(PlayerInfo[playerid][pCash] < cash) return SCM(playerid, red, "� ��� ��� ������� �����.");
            if(PlayerInfo[to_player][pCash] < cash) return SCM(playerid, red, "� ������ ��� ������� �����.");
            return SendProposition(playerid, to_player, PROPOSITION_TYPE_DICE, cash);
        }
    }
    return SCM(playerid, red, "�� �� ���������� �� ������.");
}