CMD:invite(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == 0 || PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /invite [ID игрока]");

    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);
    if(!IsPlayerInRangeOfPlayer(playerid, to_player, 10.0)) return SCM(playerid, red, "Игрок слишком далеко!");
    if(PlayerInfo[to_player][pFines] != 0) return SCM(playerid, red, "У игрока есть неоплаченые штрафы!");
    if(PlayerInfo[to_player][pWarn] > 0) return SCM(playerid, red, "У игрока имееться предупреждение на аккаунте!");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(PlayerInfo[to_player][pMember] > 0) return SCM(playerid, red, "Игрок состоит в организации!");
    if(IsAPolice(playerid) && PlayerInfo[to_player][pVoen] < 1) return SCM(playerid, red, "У гражданина нет военного билета!");
    if(PlayerInfo[to_player][pLVL] < 2) return SCM(playerid, red, "Гражданин слишком мало проживает в области!");

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_INVITE, 0, 0);
}