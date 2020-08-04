CMD:putmet(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] != TEAM_VDV) return YouCannotUseThisFunc(playerid);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1494.8928,1660.9591,-5.3171)) return SCM(playerid, red, "Вы не на складе!");

    extract params -> new metall; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}/putmet [к-во патронов]");

    if(PlayerInfo[playerid][pMetall] < metall) return SCM(playerid, red, "У вас нет столько металла!");

    new string[144];
    format(string, sizeof(string), "Вы положили на склад армии %d кг. металла", metall);
    SCM(playerid, green, string);

    PlayerInfo[playerid][pMetall] -= metall;
    REPOSITORY_ARMY_METALL += metall;
    SaveRepository();
    return 1;
}