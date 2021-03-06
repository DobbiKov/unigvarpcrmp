CMD:r(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] < 1 && PlayerInfo[playerid][pJob] == Job_None) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "� ������ ������ � ��� ���������� ����!");

    extract params -> new string: text[144]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /r [�����]");

    new string[144];
    format(string, sizeof(string), "[R] %s %s[%d]: %s", (PlayerInfo[playerid][pMember] > 0) ? (PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ]) : (jobs_name[ PlayerInfo[playerid][pJob] ]), PlayerInfo[playerid][pName], playerid, text);
    if(PlayerInfo[playerid][pMember] > 0) SCMR(PlayerInfo[playerid][pMember], green, string);
    else if(PlayerInfo[playerid][pJob] > 0) SCMR(PlayerInfo[playerid][pJob], green, string);

    format(string, sizeof(string), "������� � �����: \"%s\"", text);
    cmd::me(playerid, string);
    return 1;
}

CMD:rb(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] < 1 && PlayerInfo[playerid][pJob] == Job_None) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "� ������ ������ � ��� ���������� ����!");

    extract params -> new string: text[144]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /rb [�����]");

    new string[144];
    format(string, sizeof(string), "(( OOC: [R] %s %s[%d]: %s ))", (PlayerInfo[playerid][pMember] > 0) ? (PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ]) : (jobs_name[ PlayerInfo[playerid][pJob] ]), PlayerInfo[playerid][pName], playerid, text);

    if(PlayerInfo[playerid][pMember] > 0) SCMR(PlayerInfo[playerid][pMember], green, string);
    else if(PlayerInfo[playerid][pJob] > 0) SCMR(PlayerInfo[playerid][pJob], green, string);
    
    return 1;
}

CMD:d(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] < 1 || PlayerInfo[playerid][pRang] < 2) return YouCannotUseThisFunc(playerid);
    if(IsAOpg(playerid)) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "� ������ ������ � ��� ���������� ����!");

    extract params -> new string: text[144]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /d [�����]");

    new string[144];
    format(string, sizeof(string), "[D] %s %s[%d]: %s", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, text);
    SCMD(0xFF7979AA, string);

    format(string, sizeof(string), "������� � �����: \"%s\"", text);
    cmd::me(playerid, string);
    return 1;
}

CMD:db(playerid, params[])
{
    if(PlayerInfo[playerid][pMember] < 1 || PlayerInfo[playerid][pRang] < 2) return YouCannotUseThisFunc(playerid);
    if(IsAOpg(playerid)) return YouCannotUseThisFunc(playerid);
    if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "� ������ ������ � ��� ���������� ����!");

    extract params -> new string: text[144]; else return SCM(playerid, yellow, "[���������]: {FFFFFF}����������� /db [�����]");

    new string[144];
    format(string, sizeof(string), "(( OOC: [D] %s %s[%d]: %s ))", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], playerid, text);
    SCMD(0xFF7979AA, string);
    return 1;
}

stock SCMR(fraction, color, text[])
{
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pMember] > 0) 
        {
            if(PlayerInfo[i][pMember] == fraction || PlayerInfo[i][pTipster] == fraction)
            {
                SCM(i, color, text);
            }
        }
        else if(PlayerInfo[i][pJob] > 0)
        {
            if(PlayerInfo[i][pJob] == fraction || PlayerInfo[i][pJobTipster] == fraction)
            {
                SCM(i, color, text);
            }   
        }
    }
    return 1;
}

stock SCMD(color, text[])
{
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pMember] > 0 && !IsAOpg(i)) 
        {
            SCM(i, color, text);
        }
    }
    return 1;
}