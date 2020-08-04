CMD:arrest(playerid, params[])
{
    if(!IsAPolice(playerid)) return YouCannotUseThisFunc(playerid);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1939.8840,2161.2378,15.7034)) return SCM(playerid, red, "Вы не у тюрьмы!");

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте /arrest [ID игрока]");

    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] == false) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][pWANTED] < 1) return SCM(playerid, red, "Игрок не в розыске!");
    if(GetPVarInt(to_player, "cuffed") < 1) return SCM(playerid, red, "Игрок не в наручниках!");



    PlayerInfo[to_player][pKPZ] = PlayerInfo[to_player][pWANTED]*600;
    PlayerInfo[to_player][pJP] = random(2);

    new string[144];
    format(string, sizeof(string), "Вы посадили преступника %s в тюрьму и получили премию в размере %d рублей.", PlayerInfo[to_player][pName], PlayerInfo[to_player][pWANTED]*500);
    SCM(playerid, blue, string);

    format(string, sizeof(string), "%s %s посадил %s в тюрьму. И получил премию в размере %d рублей.", PlayerRank[ PlayerInfo[playerid][pMember] ][ PlayerInfo[playerid][pRang] ], PlayerInfo[playerid][pName], PlayerInfo[to_player][pName], PlayerInfo[to_player][pWANTED]*500);
    SCMPolice(blue, string);

    format(string, sizeof(string), "%s посадил вас в тюрьму, так как вы были в розыске. Посмотреть время до выхода - /time", PlayerInfo[playerid][pName]);
    SCM(to_player, blue, string);

    GiveMoney(playerid, PlayerInfo[to_player][pWANTED]*500, "Посадил преступника");
    PlayerInfo[to_player][pWANTED] = 0;
    SetPlayerWantedLevel(to_player, 0);
    DeletePVar(to_player, "cuffed");
    SetPlayerSpecialAction(to_player, SPECIAL_ACTION_NONE); 

    ResetPlayerWeaponsAC(to_player);
    SaveAccounts(playerid);
    SaveAccounts(to_player);
    PutPlayerInKPZ(to_player);
    return 1;
}