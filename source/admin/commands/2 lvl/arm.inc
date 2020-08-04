CMD:arm(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 2 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);

    SetPlayerArmour(playerid, 100);
    return SCM(playerid, white, "¬ы установили себе броню в количестве 100 единиц.");
}