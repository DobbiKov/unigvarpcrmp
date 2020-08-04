CMD:healme(playerid)
{
    if(PlayerInfo[playerid][pHeal] <= 0) return SCM(playerid, red, "У вас нет аптечки!");

    PlayerInfo[playerid][pHeal]--;
    new Float:health;
    GetPlayerHealth(playerid, health);
    SetPlayerHealth(playerid, (health+60.0>100.0) ? (100.0) : (health+60.0));
    PlayerInfo[playerid][pHP] = (health+60.0>100.0) ? (100.0) : (health+60.0);
    ApplyAnimation(playerid,"ped","gum_eat",4.0,0,0,0,0,0,1);
    cmd::me(playerid, "использовал аптечку");
    GameTextForPlayer(playerid, "~g~ +60 HP", 3000, 1);
    return 1;
}