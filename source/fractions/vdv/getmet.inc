CMD:getmet(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] != TEAM_VDV) return YouCannotUseThisFunc(playerid);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1494.8928,1660.9591,-5.3171)) return SCM(playerid, red, "Вы не на складе!");
    if(PlayerInfo[playerid][pRang] < 8) return YouCannotUseThisFunc(playerid);

    extract params -> new metall; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}/getmet [к-во патронов]");

    if(REPOSITORY_ARMY_METALL < metall) return SCM(playerid, red, "На складе недостаточно металла!");
    if((PlayerInfo[playerid][pMetall] + metall) > 100) return SCM(playerid, red, "Вы не можете унести так много металла!");

    new string[144];
    format(string, sizeof(string), "[R] %s %s[%d] взял со склада армии %d кг. металла", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, metall);
    SCMR(TEAM_VDV, green, string);
    SCMA(grey, string);

    PlayerInfo[playerid][pMetall] += metall;
    REPOSITORY_ARMY_METALL -= metall;
    SaveRepository();
    return 1;
}