CMD:unloadfs(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(sscanf(params,"s[64]",params[0])) return SCM(playerid,white, "{"cblue"}Х [ѕодсказка]{"cwhite"}: /unloadfs [»м€ скрипта]");
    stringer[0] = EOS;
    format(stringer, 64,"loadfs %s",params[0]);
    SendRconCommand(stringer);
    stringer[0] = EOS;
    format(stringer, 120, "{"cgreen"}Х [”спешно]{"cwhite"}: FilterScripts: %s деактивирован!",params[0]);
    SCM(playerid, grey, stringer);
    return 1;
}