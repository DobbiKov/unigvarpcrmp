CMD:drugs(playerid, params[])
{
    extract params -> new how; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /drugs (1-2)");
    if(PlayerInfo[playerid][pDrugs] < how) return SCM(playerid, red, "У вас нет столько наркотиков!");
    if(GetPVarInt(playerid, "use_drugs") == 1) return SCM(playerid, red, "Наркотики можно использовать раз в минуту!");

    switch(how)
    {
        case 1:
        {
            new Float:Health; GetPlayerHealth(playerid,Health);

            ApplyAnimation(playerid,"ped","Smoke_in_car",4.1,1,1,1,1,1);
            SCM(playerid, blue, "Вы использовали наркотики!");
            cmd::me(playerid, "использовал наркотики");
            SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid)+10000);
            SetPlayerWeather(playerid, 162);
            SetTimerEx("Walkanim",6000,0,"i",playerid);
            SetTimerEx("EffectGone",60000,0,"i",playerid);
            SetPVarInt(playerid, "use_drugs", 1);
            SetPlayerHealth(playerid, Health+30.0);
        }
        case 2:
        {
            new Float:Health; GetPlayerHealth(playerid,Health);

            ApplyAnimation(playerid,"ped","Smoke_in_car",4.1,1,1,1,1,1);
            SCM(playerid, blue, "Вы использовали наркотики!");
            cmd::me(playerid, "использовал наркотики");
            SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid)+20000);
            SetPlayerWeather(playerid, 162);
            SetTimerEx("Walkanim",6000,0,"i",playerid);
            SetTimerEx("EffectGone",60000,0,"i",playerid);
            SetPVarInt(playerid, "use_drugs", 1);
            SetPlayerHealth(playerid, Health+60.0);
        }
        default: return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /drugs (1-2)");
    }
    return PlayerInfo[playerid][pDrugs] -= how;
}

publics Walkanim(playerid)
{
    return ApplyAnimation(playerid,"ped","WALK_drunk",4.1,1,1,1,1,1);
}

publics EffectGone(playerid)
{
    SetPlayerDrunkLevel(playerid,0);
    SetPlayerWeather(playerid,0);
    DeletePVar(playerid, "use_drugs");
    return 1;
}