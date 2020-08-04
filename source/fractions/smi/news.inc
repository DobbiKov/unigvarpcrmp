CMD:news(playerid)
{
    if(PlayerInfo[playerid][pMember] != TEAM_SMI) return YouCannotUseThisFunc(playerid);

    if(GetPVarInt(playerid, "smi_news") != 1)
    {
        if(PlayerInfo[playerid][pMute] > 0) return SCM(playerid, red, "У вас имееться блокировка чата!");
        if(!IsPlayerInAnyVehicle(playerid)) return SCM(playerid, red, "Вы не находитесь в служебном автомобиле!");
        new vehicleid = GetPlayerVehicleID(playerid);
        if(job_car[TEAM_SMI_CAR][0] <= vehicleid <= job_car[TEAM_SMI_CAR][1])
        {
            SCM(playerid, green, "Вы вошли в Эфир!");
            SetPVarInt(playerid, "smi_news", 1);
        }
        else return SCM(playerid, red, "Вы не находитесь в служебном автомобиле!");
    }
    else
    {
        SCM(playerid, green, "Вы вышли из Эфира!");
        DeletePVar(playerid, "smi_news");
    }
    return 1;
}