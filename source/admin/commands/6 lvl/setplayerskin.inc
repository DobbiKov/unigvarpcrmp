CMD:setplayerskin(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 6) return ShowCommandNotFound(playerid);

    extract params -> new to_player, skin; else return SCM(playerid, blue, "•[Подсказка] {ffffff}Введите: /setskin [id игрока] [ID скина]");

    if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return PlayerOffLine(playerid);

	PlayerInfo[to_player][pChar] = skin;
    SetPlayerSkin(to_player, PlayerInfo[to_player][pChar]);

    new fmt_str[128];
    format(fmt_str, sizeof(fmt_str), "UPDATE `accounts` SET `pChar` = '%d' WHERE `pID` = '%d'", PlayerInfo[to_player][pChar], PlayerInfo[to_player][pID]);
    mysql_tquery(connects, fmt_str, "", "");

    new string[128];
    format(string, sizeof(string), "[A] %s[%d] поставил постоянныйй скин(%d) игроку %s[%d]", PlayerInfo[playerid][pName], playerid, skin, PlayerInfo[to_player][pName], to_player);
    SCMA(grey, string);

    format(string, sizeof(string), "Администратор %s поставил вам постоянный скин(%d)", PlayerInfo[playerid][pName], skin);
    SCM(to_player, white, string);
    return 1;
}