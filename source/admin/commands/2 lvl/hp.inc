CMD:hp(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 2 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
    
    PlayerInfo[playerid][pHP] = 100.0;
    SetPlayerHealth(playerid, 100.0);
    return SCM(playerid, white, "¬ы установили себе здоровье в количестве 100 единиц.");
}