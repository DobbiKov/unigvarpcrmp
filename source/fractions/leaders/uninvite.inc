CMD:uninvite(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] == TEAM_NONE || PlayerInfo[playerid][pRang] < 9) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, string: reason[128]; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /uninvite [ID игрока] [причина]");
    if(to_player == playerid) return SCM(playerid, red, "Вы не можете уволить себя!");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pMember] != PlayerInfo[playerid][pMember]) return SCM(playerid, red, "Игрок не состоит в вашей организации!");
    if(PlayerInfo[to_player][pRang] >= PlayerInfo[playerid][pRang]) return SCM(playerid, red, "Игрок выше вас по рангу!"); 

    new string[128];
    format(string, sizeof(string), "Вы уволили %s из организации. Причина: %s", PlayerInfo[to_player][pName], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s уволил вас из организации \"%s\". Причина: %s", PlayerInfo[playerid][pName], GetMember[ PlayerInfo[to_player][pMember] ], reason);
    SCM(to_player, blue, string);

    PlayerInfo[to_player][pMember] = 0;
    PlayerInfo[to_player][pWarnF] = 0;
    PlayerInfo[to_player][pRang] = 0;
    PlayerInfo[to_player][pFSkin] = -1;
    ResetPlayerWeaponsAC(to_player);
    SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
    return SaveAccounts(to_player);
}