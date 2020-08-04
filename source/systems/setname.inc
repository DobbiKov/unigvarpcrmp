CMD:setname(playerid,params[])
{
    stringer[0] = EOS;
	if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	if(sscanf(params,"i",params[0])) return SCM(playerid,white, "{"cblue"}• [Подсказка]{"cwhite"}: /setname [ID]");
	if(!PlayerInfo[params[0]][pLogin] && !IsPlayerConnected(params[0])) return 1;
    new playerName[MAX_PLAYER_NAME+1];
    GetPVarString(params[0], "WantNickChange", playerName, MAX_PLAYER_NAME);
	if(!strlen(playerName)) return SCM(playerid,white,"Игрок не подавал завку на смену ника");
	format(stringer,128,"[A] %s сменил ник игроку %s на %s",PlayerInfo[playerid][pName],PlayerInfo[params[0]][pName],playerName);
	SCMA(0x00CC66FF,stringer);

	if(GetPVarInt(params[0],"changename_fix")) return 1;
	ChangeName(params[0]);
	return 1;
}
publics CallChangeName(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		SCM(playerid, white, "Данный никнейм занят");
		DeletePVar(playerid,"WantNickChange");
		return 1;
	}

 	new playerName[MAX_PLAYER_NAME+1];
    GetPVarString(playerid, "WantNickChange", playerName, MAX_PLAYER_NAME);

	format(stringer,512,"[A] %s[%d] подал завку на смену ника. Желаемый ник: %s",PlayerInfo[playerid][pName],playerid,playerName);
	SCMA(0x00CC66FF,stringer);
	SCMA(0x00CC66FF,"Чтобы сменить ему ник Используйте /setname");
	SCM(playerid, white, "{"cgreen"}• [Успешно]{"cwhite"}: Заявка на смену ника отправлена администрации");
	return 1;
}
stock ChangeName(playerid)
{
 	new playerName[MAX_PLAYER_NAME+1];
    GetPVarString(playerid, "WantNickChange", playerName, MAX_PLAYER_NAME);

    stringer[0] = EOS;
	format(stringer,512, "UPDATE `accounts` SET `pName` = '%s' WHERE `pName` = '%s' LIMIT 1",playerName,PlayerInfo[playerid][pName]);
	mysql_tquery(connects, stringer, "", "");

	format(stringer,100, "Игрок %s сменил имя на %s",PlayerInfo[playerid][pName],playerName);
	SCMA(orange, stringer);
	SetPVarInt(playerid,"changename_fix",true);
	SetPlayerName(playerid, playerName);
	strmid(PlayerInfo[playerid][pName], playerName, 0, strlen(playerName), 31);

 	SCM(playerid, white, "{"cgreen"}• [Успешно]{"cwhite"}: Пропишите новый ник в окне CR-MP");

 	stringer[0] = EOS;
	new year, month, day, strstre[30];
 	getdate(year, month, day);
 	format(strstre,sizeof(strstre),"%d/%d/%d",day,month,year);
	mysql_format(connects, stringer, sizeof(stringer), "INSERT INTO `name_log` (`nOldName`, `nNewName`, `nDate`) VALUES ('%s', '%s', '%s')", PlayerInfo[playerid][pName], playerName, strstre);
	mysql_tquery(connects, stringer);

	DeletePVar(playerid,"WantNickChange");
	return 1;
}