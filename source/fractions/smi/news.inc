CMD:news(playerid)
{
    if(PlayerInfo[playerid][pMember] != TEAM_SMI) return YouCannotUseThisFunc(playerid);

    if(GetPVarInt(playerid, "smi_news") != 1)
    {
        if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "� ��� �������� ���������� ����!");
        if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "�� �� ���������� � ��������� ����������!");
        new vehicleid = GetPlayerVehicleID(playerid);
        if(job_car[TEAM_SMI_CAR][0] <= vehicleid <= job_car[TEAM_SMI_CAR][1])
        {
            SCM(playerid, green, "�� ����� � ����!");
            SetPVarInt(playerid, "smi_news", 1);
        }
        else return SCM(playerid, red, "�� �� ���������� � ��������� ����������!");
    }
    else
    {
        SCM(playerid, green, "�� ����� �� �����!");
        DeletePVar(playerid, "smi_news");
    }
    return 1;
}