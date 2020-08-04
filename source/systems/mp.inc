new mp = 0;
new teleport = 0;
new Float: mpX, Float: mpY, Float: mpZ, mpVW, mpINT;
new GO_TO_MP[MAX_PLAYERS] = 0;

CMD:mp(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

    if(mp == 0) return SCM(playerid, red, "Мероприятие не создано.");
    new string[120];
    if(teleport == 0)
    {
        format(string, sizeof(string), "[A] %s[%d] открыл телепорт на мероприятие", PlayerInfo[playerid][pName], playerid);
        SCMA(grey, string);        
        teleport = 1;

        GetPlayerPos(playerid, mpX, mpY, mpZ);
        mpVW = GetPlayerVirtualWorld(playerid);
        mpINT = GetPlayerInterior(playerid);
    }
    else
    {
        format(string, sizeof(string), "[A] %s[%d] закрыл телепорт на мероприятие", PlayerInfo[playerid][pName], playerid);
        SCMA(grey, string);  
        teleport = 0;
    }
    return 1;
}

CMD:mpstart(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

    new string[128];
    if(mp == 1) return SCM(playerid, red, " Мероприятие уже создано!");
   
    format(string, sizeof(string), "[A] %s[%d] создал мероприятие", PlayerInfo[playerid][pName], playerid);
    SCMA(grey, string);
    mp = 1;
    
    return 1;
}
CMD:mpstop(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

    new string[128];
    if(mp == 0) return SCM(playerid, red, " Мероприятие не создано!");

    format(string, sizeof(string), "[A] %s[%d] завершил мероприятие", PlayerInfo[playerid][pName], playerid);
    SCMA(grey, string);
    mp = 0;
    teleport = 0;
    foreach(new i : Player) if(GO_TO_MP[i] != 0) GO_TO_MP[i] = 0;

    return 1;
}

CMD:mpgun(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num, gun, patr; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mpgun [номер команды] [номер оружия] [кол-во пт]");
  	if(gun > 47 || gun < 1) return SCM(playerid, red,"Такого оружия не существует!");
    if(patr > 1000 || patr < 1) return SCM(playerid, red,"Неверное количество патрон!");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i] != 0)
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    GivePlayerWeaponAC(i,gun,patr);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    GivePlayerWeaponAC(i,gun,patr);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    GivePlayerWeaponAC(i,gun,patr);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mpgun [номер команды] [номер оружия] [кол-во пт]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPGUN]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
    format(string, sizeof(string), "[MPGUN]: WEAPONID: %d | PATRONS: %d", gun, patr);
    SCM(playerid, blue, string);
	
	return 1;
}

CMD:mpskin(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num, skin; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mpskin [номер команды] [номер скина]");
  	if(skin > 299 || skin < 1) return SCM(playerid, red,"Такого скина не существует!");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i])
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    SetPlayerSkin(i,skin);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    SetPlayerSkin(i,skin);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    SetPlayerSkin(i,skin);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mpskin [номер команды] [номер cкина]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPSKIN]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
    format(string, sizeof(string), "[MPSKIN]: SKIN: %d", skin);
    SCM(playerid, blue, string);
	
	return 1;
}

CMD:mphere(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mphere [номер команды]");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i])
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    SetPlayerPos(i, x, y, z);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    SetPlayerPos(i, x, y, z);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    SetPlayerPos(i, x, y, z);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mphere [номер команды]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPHERE]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
	
	return 1;
}


CMD:mpfreeze(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mpfreeze [номер команды]");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i])
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    TogglePlayerControllable(i,0);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    TogglePlayerControllable(i,0);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    TogglePlayerControllable(i, 0);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mpfreeze [номер команды]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPFREEZE]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
	
	return 1;
}
CMD:mpunfreeze(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mpunfreeze [номер команды]");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i])
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    TogglePlayerControllable(i,1);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    TogglePlayerControllable(i,1);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    TogglePlayerControllable(i, 1);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mpunfreeze [номер команды]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPUNFREEZE]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
	
	return 1;
}
CMD:mphp(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);
	extract params -> new temp_num, hp; else return SCM(playerid, yellow, "[Информация]: {ffffff}/mphp [номер команды] [количество HP]");

	new team_1[250],team_2[250], all, team1, team2;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid, x,y,z);

	foreach(new i: Player)
	{
        if(GO_TO_MP[i])
        {
            if(i == playerid) continue;
            if(!IsPlayerConnected(i)) continue;
            if(IsPlayerInRangeOfPoint(i, 100.0, x, y, z))
            {
                all++;
                if(temp_num == 0)
                {
                    SetPlayerHealth(i, hp);
                    continue;
                }
                if(temp_num == 2 && all%2 == 0)
                {
                    team2++;
                    team_2[team2] = i;
                    SetPlayerHealth(i, hp);
                    continue;
                }
                if(temp_num == 1 && all%2 == 1)
                {
                    team1++;
                    team_1[team1] = i;
                    SetPlayerHealth(i, hp);
                    continue;
                }
                if(temp_num < 0 || temp_num > 2)
                {
                    SendClientMessage(playerid, yellow, "[Информация]: {ffffff}/mphp [номер команды] [количество HP]");
                    break;
                }
            }
        }
   	}
    new string[144];
    format(string, sizeof(string), "[MPHP]: ALL: %d, TEAM 1: %d, TEAM_2: %d", all, team1, team2);
    SCM(playerid, blue, string);
    format(string, sizeof(string), "[MPHP]: HP: %d", hp);
    SCM(playerid, blue, string);
	
	return 1;
}

CMD:mpsay(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 3) return ShowCommandNotFound(playerid);

    extract params -> new string: text[144]; else return SCM(playerid, yellow, "[Оповещение]: {FFFFFF}Используйте /mpsay [Текст]");

    new all;
    foreach(new i : Player)
    {
        if(GO_TO_MP[i] > 0)
        {
            all++;
            new string[128];
            format(string, sizeof(string), "[MP]: %s[%d]: %s", PlayerInfo[playerid][pName], playerid, text);
            SCM(i, blue, string);
        }
    }
    new string[144];
    format(string, sizeof(string), "[MPSAY]: %s", text);
    SCM(playerid, blue, string);
    format(string, sizeof(string), "[MPSAY]: %d игроков увидело ваше сообщение!", all);
    SCM(playerid, blue, string);
    return 1;
}

CMD:gotomp(playerid)
{
    if(teleport == 0) return SCM(playerid, red, "Телепорт на мероприятие закрыт");
    if(PlayerInfo[playerid][pJail] > 0 || PlayerInfo[playerid][pKPZ] > 0) return SCM(playerid, red, "Вы не можете телепортироваться на мероприятие!");
    
    GetPlayerPos(playerid, PlayerInfo[playerid][pLastX], PlayerInfo[playerid][pLastY], PlayerInfo[playerid][pLastZ]);

    GO_TO_MP[playerid] = 1;
    SetPlayerPos(playerid, mpX, mpY, mpZ);
    SetPlayerInterior(playerid, mpINT);
    SetPlayerVirtualWorld(playerid, mpVW);
    return 1;
}

