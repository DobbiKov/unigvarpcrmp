
CMD:gotome(playerid, params[])
{
    if(!IsACops(playerid)) return SCM(playerid, COLOR_GRAD1, "Вы не в гос. организации.");//Проверка на фракцию
    if(!IsPlayerConnected(playerid)) return false;//Коннект ли игрок
    if(sscanf(params, "d", params[0])) return SCM(playerid, COLOR_GRAD1, "Используйте: /gotome [ID]");
    if(!IsPlayerConnected(params[0])) return SCM(playerid, COLOR_GRAD1, "Игрок Offline.");
    if(PlayerCuffed[params[0]] == false) return SCM(playerid, COLOR_GRAD1, "Игрок не в наручниках!");//Проверка на наручники.
    new Float:PPX, Float:PPY, Float:PPZ;
    GetPlayerPos(playerid, PPX, PPY, PPZ);
    if (GetPlayerState(params[0]) == 2)
    {
        SetVehiclePos(GetPlayerVehicleID(params[0]), PPX, PPY+4, PPZ), SetPlayerPos(params[0], PPX, PPY+4, PPZ), PutPlayerInVehicle(params[0], GetPlayerVehicleID(params[0]), 0);
    }
    else
    {
        SetPlayerPos(params[0],PPX,PPY+2, PPZ);
        SetPlayerVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));
        SetPlayerInterior(params[0], GetPlayerInterior(playerid));
    }
    format(strcom, 144, "%s[%d] подвёл к себе %s[%d].", Player[playerid][pName], playerid, Player[params[0]][pName], params[0]), ABroadCast(COLOR_YELLOW,strcom,1);
return SendMes(playerid, COLOR_GRAD1, "Вы подвели к себе %s.", Player[params[0]][pName]),     SendMes(params[0], COLOR_GRAD1, "%s подвёл вас к себе.", Player[playerid][pName]);
}