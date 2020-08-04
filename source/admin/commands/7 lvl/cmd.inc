CMD:cmd(playerid, params[])
{ 
	if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
					
	if(sscanf(params, "ds[90]", params[0], params[1],params[2])) return SendClientMessage(playerid, blue, "[Подсказка]: {ffffff}/cmd [ид игрока] [команда] [текст]");
    if(!IsPlayerConnected(params[0]) || PlayerInfo[params[0]][pLogin] != true) return PlayerOffLine(playerid);
	new mess[100];
    format(mess, sizeof(mess), "%s", params[1]);
    CallLocalFunction("OnPlayerCommandText", "is", params[0], mess);
	return 1;
}
CMD:cmd_say(playerid, params[])
{ 
	if(PlayerInfo[playerid][bAdmin] < 7) return ShowCommandNotFound(playerid);
					
	if(sscanf(params, "ds[90]", params[0], params[1])) return SendClientMessage(playerid, blue, "[Подсказка]: {ffffff}/cmd_say [ид игрока] [текст]");
    if(!IsPlayerConnected(params[0]) || PlayerInfo[params[0]][pLogin] != true) return PlayerOffLine(playerid);

    CallLocalFunction("OnPlayerText", "is", params[0], params[1]);
	return 1;
}