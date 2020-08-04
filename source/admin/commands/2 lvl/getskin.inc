CMD:getskin(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);
    
    extract params -> new skinid; else return SCM(playerid, yellow, "[Подсказка] {FFFFFF}Используйте: /getskin [ID скина]");
    
    SetPlayerSkin(playerid, skinid);
    SCM(playerid, blue, "Вы выдали себе временный скин!");
	return 1;
}