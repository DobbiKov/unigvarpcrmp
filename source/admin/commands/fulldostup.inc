stock CheckFD(to_player)
{
    for(new i = 0; i < sizeof(SuperNick_S); i++)
    {
        if(!strcmp(PlayerInfo[to_player][pName], SuperNick_S[i], false))
        {
            return true;
        }
    }
    return false;
}

stock CheckNickFD(to_player[])
{
    for(new i = 0; i < sizeof(SuperNick_S); i++)
    {
        if(!strcmp(to_player, SuperNick_S[i], false))
        {
            return true;
        }
    }
    return false;
}