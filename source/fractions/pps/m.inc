CMD:m(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);

    extract params -> new string: text[144]; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /m [текст]");
    if(!strlen(text)) return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /m [текст]");

    new string[144];
    format(string, sizeof(string), "[M] %s %s[%d]: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, text);
    ProxDetector(50.0, playerid, string, yellow, yellow, yellow, yellow,yellow);
    return 1;
}