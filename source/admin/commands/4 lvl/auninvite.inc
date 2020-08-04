CMD:auninvite(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 4) return ShowCommandNotFound(playerid);

    extract params -> new to_player, string: reason[128]; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /auninvite [ID игрока] [причина]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[playerid][bAdmin] < 6) if(PlayerInfo[to_player][pRang] >= 10) return SCM(playerid, red, "Игрок являеться лидером организации."); 

    new string[128];
    format(string, sizeof(string), "Вы уволили %s из организации. Причина: %s", PlayerInfo[to_player][pName], reason);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "Администратор %s уволил вас из организации \"%s\". Причина: %s", PlayerInfo[playerid][pName], GetMember[ PlayerInfo[to_player][pMember] ], reason);
    SCM(to_player, blue, string);

    format(string, sizeof(string), "[A] %s[%d] уволил игрока %s[%d] из организации \"%s\". Причина: %s", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, GetMember[ PlayerInfo[to_player][pMember] ], reason);

    PlayerInfo[to_player][pMember] = 0;
    PlayerInfo[to_player][pWarnF] = 0;
    PlayerInfo[to_player][pRang] = 0;
    PlayerInfo[to_player][pFSkin] = -1;
    ResetPlayerWeaponsAC(to_player);
    SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
    return SaveAccounts(to_player);
}