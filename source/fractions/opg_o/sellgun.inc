CMD:sellgun(playerid, params[])
{
    if(!IsAOpg(playerid) && PlayerInfo[playerid][pVIP] < 1) return YouCannotUseThisFunc(playerid);

    extract params -> new to_player, patrons, price; else return SCM(playerid, blue, "[Подсказка]: {FFFFFF}Используйте /sellgun [ID игрока] [кол-во патронов] [цена]");
    if(to_player == playerid) return SCM(playerid, red, "Вы указали свой ID!");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
	if(!GetPlayerWeapon(playerid)) return SCM(playerid, red, "Возьмите в руку оружие, которое хотите продать!");
	new ammo = GetPlayerAmmo(playerid);
	if(ammo < patrons) return SCM(playerid, red, "У вас нет столько патронов!");
    if(PlayerInfo[to_player][pCash] < price) return SCM(playerid, red, "У игрока не достаточно денег!");

	SetPVarInt(playerid, "weapon_id", GetPlayerWeapon(playerid));

    return SendProposition(playerid, to_player, PROPOSITION_TYPE_SELLDRUGS, patrons, price);
}