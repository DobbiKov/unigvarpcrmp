CMD:loadfs(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
    if(sscanf(params,"s[64]",params[0])) return SCM(playerid,white, "{"cblue"}� [���������]{"cwhite"}: /loadfs [��� �������]");
    stringer[0] = EOS;
    format(stringer, 64,"loadfs %s",params[0]);
    SendRconCommand(stringer);
    stringer[0] = EOS;
    format(stringer, 120, "{"cgreen"}� [�������]{"cwhite"}: FilterScripts: %s �����������!",params[0]);
    SCM(playerid, grey, stringer);
    return 1;
}