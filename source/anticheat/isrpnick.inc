stock bool:IsRPNick(const name[])
{ // http://pro-pawn.ru/showthread.php?7528
    static i, __;
    if ('A' <= name[0] <= 'Z' && 'a' <= name[1] <= 'z')
    {
        for (i = 1, __ = 0;;)
        {
            switch (name[++i])
            {
                case 'a'..'z':
                    continue;
                case '_':
                    if (__++, 'A' <= name[++i] <= 'Z' && 'a' <= name[++i] <= 'z')
                        continue;
                    else
                        break;
                case '\0':
                    return (i >= 4 && __ == 1);
                default:
                    return false;
            }
        }
    }
    return false;
}