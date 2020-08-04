CMD:nick(playerid, params[])
{
    if(PlayerInfo[playerid][bAdmin] < 2) return ShowCommandNotFound(playerid);

    extract params -> new to_player; else return SCM(playerid, yellow, "[Подсказка]: {FFFFFF}Используйте: /nick [ID игрока]");
    if(!IsPlayerConnected(to_player) || PlayerInfo[to_player][pLogin] != true) return PlayerOffLine(playerid);
    if(PlayerInfo[to_player][bAdmin] > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Нельзя кикнуть администратора.");

    new string[128];
    if(PlayerInfo[to_player][pLVL] == 1)
    {
        format(string, sizeof(string), "Администратор %s кикнул игрока %s. Причина: NonRP ник-нейм", PlayerInfo[playerid][pName], PlayerInfo[to_player][pName]);
        SCMTA(0xFF4530FF, string);
        
        format(string, sizeof(string), "{FFFFFF}Вы были кикнуты с сервера, так как у вас NonRP ник-нейм!\n{FFFFFF}Поменяйте его и снова зайдите на сервер.\n{FFFFFF}Формат NickName'a: {"cblue"}Name_Surname\n{FFFFFF}Пример: {"cblue"}Eduard_Dobbikov{FFFFFF}, {"cblue"}Tatiana_Pilipiuk\n\n{FFFFFF}Что б выйти с сервера, пропишие команду {"cblue"}/q");
        SPD(to_player, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}UNIGVA | Kick", string, "Закрыть", "");
    }
    else
    {
        format(string, sizeof(string), "[A]: %s[%d] попросил игрока %s[%d] сменить NickName", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
        SCMA(grey, string);

        format(string, sizeof(string), "Администратор %s попросил вас сменить NonRP NickName!");
        SCM(to_player, white, string);

        format(string, sizeof(string), "{FFFFFF}Вам следует сменить NonRP ник-нейм!\n{FFFFFF}Что б сменить никнейм - введите команду /menu, затем выберете пункт 'Сменить NickName'.\n{FFFFFF}Формат NickName'a: {"cblue"}Name_Surname\n{FFFFFF}Пример: {"cblue"}Eduard_Dobbikov{FFFFFF}, {"cblue"}Tatiana_Pilipiuk\n\n{FFFFFF}Что б выйти с сервера, пропишие команду {"cblue"}/q");
        SPD(to_player, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}UNIGVA | NonRP NickName", string, "Далее", "");
    }
    return 1;
}