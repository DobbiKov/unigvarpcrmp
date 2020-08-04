CMD:selldrugs(playerid, params[])
{
    if(!IsAOpg(playerid) && PlayerInfo[playerid][pVIP] < 1) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, patrons, price; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /selldrugs [ID игрока] [гр. наркотиков] [цена]");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
	if(PlayerInfo[playerid][pDrugs] < patrons) return SCM(playerid, red, "У вас нет столько наркотиков!");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока не достаточно денег!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_SELLDRUGS, patrons, price);
}