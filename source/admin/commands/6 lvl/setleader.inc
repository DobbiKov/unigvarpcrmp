CMD:setleader(playerid, params[])
{
	if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

	extract params -> new to_player, id; else
    {
        SCM(playerid, blue, "[Подсказка] {ffffff}Введите: /setleader [ID игрока] [ID]");
        return SCM(playerid, blue, "[Подсказка] {FFFFFF}: 1 - АП | 2 - СМИ | 3 - Полиция | 4 - Больница | 5 - ВДВ | 6 - ОПГ - О | 7 - ОПГ - С | 8 - ФСБ(None)");
    }
    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

    if(id > 8 || id < 1) return SCM(playerid, red, "Не более 9 и не менее 1.");

    new string[128];
    if(PlayerInfo[to_player][pMember] > 0)
    {
        format(string, sizeof(string), "[A]: %s[%d] снял %s[%d] с должности лидера организации %s", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, GetMember[ PlayerInfo[to_player][pMember] ]);
        SCMA(grey, string);
        PlayerInfo[to_player][pMember] = 0;
        PlayerInfo[to_player][pRang] = 0;
        PlayerInfo[to_player][pFSkin] = -1;
        PlayerInfo[to_player][pWarnF] = 0;
        SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);
        return SaveAccounts(to_player);
    }

    PlayerInfo[to_player][pMember] = id;
    PlayerInfo[to_player][pRang] = 10;
    PlayerInfo[to_player][pFSkin] = 1;
    PlayerInfo[to_player][pJob] = 0;

    format(string, sizeof(string), "[A]: %s[%d] назначил %s[%d] лидером организации %s", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player, GetMember[id]);
    SCMA(grey, string);

    format(string, sizeof(string), "Администратор %s назначил вас лидером организации %s", PlayerInfo[playerid][pName], GetMember[id]);
    SCM(to_player, white, string);
    SaveAccounts(to_player);
    return 1;
}