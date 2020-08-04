new TMask[MAX_PLAYERS];

CMD:mask(playerid)
{
    if(PlayerInfo[playerid][pMask] <= 0) return SCM(playerid, red, "У вас нет маски!");
    if(GetPVarInt(playerid, "pMask") == 1) return SCM(playerid, red, "На вас уже надета маска!");

    PlayerInfo[playerid][pMask]--;
    SetPlayerColor(playerid, 0xFFFFFF00);
    ApplyAnimation(playerid, "SHOP","ROB_Shifty", 4.0, false, 0, 0, 0, 0);
    cmd::me(playerid, "надел маску");
    SetPVarInt(playerid, "pMask", 1);
    SCM(playerid, blue, "Вы надели одели маску! Ваше местоположение скрыто на 10 минут!");
    TMask[playerid] = SetTimerEx("PlayerMask", 1000*60*10, false, "i", playerid);
    return 1;
}

publics PlayerMask(playerid)
{
    SetPlayerColor(playerid, 0xFFFFFFFF);
    SCM(playerid, blue, "10 минут прошло, с вас была снята маска.");
    DeletePVar(playerid, "pMask");
    return 1;
}