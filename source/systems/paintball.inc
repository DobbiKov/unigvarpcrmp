enum E_PAINT_COORD
{
    Float:paintX,
    Float:paintY,
    Float:paintZ,
    Float:paintA,
}

new PaintCoord[6][E_PAINT_COORD] =
{
    {2233.5603,1392.1866,11.5700,2.7487},
    {2214.6763,1391.8629,11.5600,270.9411},
    {2245.5691,1389.4352,11.5700,303.2147},
    {2228.7747,1410.4242,11.5700,78.5760},
    {2243.3755,1421.0742,11.5700,5.2554},
    {2219.9854,1431.9543,11.5600,35.3357}
};

new bool: PaintActive[2];

publics minuteupdate()
{
    new hour, minute, second;
    gettime(hour, minute, second);
    if(hour % 2 == 0 && minute == 25)
    {
        PaintActive[0] = true;
        SCMTA(0xf71694FF, "Внимание! Через 5 минут пройдет мероприятие пейнт-бол!");
        foreach(new i : Player)
        {
            if(PlayerInfo[i][pPaintKills] != 0) PlayerInfo[i][pPaintKills] = 0;
        }
    }
    if(hour % 2 == 0 && minute == 28)
    {
        SCMTA(0xf71694FF, "Внимание! Через 2 минут пройдет мероприятие пейнт-бол!");
    }
    if(hour % 2 == 0 && minute == 30)
    {
        new all = 0;
        foreach(new i : Player) if(PlayerInfo[i][pInvitePaintBall] == true) all++;
        if(all < 2) return SCMTA(0xf71694FF, "Внимание! Мероприятие пейнт-бол отменено из-за недостаточного количества участников!");

        PaintActive[0] = false;
        PaintActive[1] = true;
        SCMTA(0xf71694FF, "Внимание! Мероприятие пейнт-бол началось!");
        foreach(new i : Player)
        {
            if(PlayerInfo[i][pInvitePaintBall] == true)
            {
                PlayerInfo[i][pInvitePaintBall] = false;
                PlayerInfo[i][pPaintBall] = true;
                new index = random(6);
                SetPlayerPos(i, PaintCoord[index][paintX], PaintCoord[index][paintY], PaintCoord[index][paintZ]);
                SetPlayerFacingAngle(i, PaintCoord[index][paintA]);
                SetCameraBehindPlayer(i);
                ResetPlayerWeaponsAC(i);
                GivePaintBallWeapon(i);
                SetPlayerHealth(i, 100.0);
                PlayerInfo[i][pHP] = 100.0;
            }
        }
    }

    if(hour % 2 == 0 && minute == 40)
    {
        if(PaintActive[1] == true)
        {
            PaintActive[1] = false;
            SCMTA(0xf71694FF, "Внимание! Мероприятие пейнт-бол завершено! Список участников: /paintlist");
            foreach(new i : Player)
            {
                if(PlayerInfo[i][pPaintBall] == true)
                {
                    PlayerInfo[i][pInvitePaintBall] = false;
                    PlayerInfo[i][pPaintBall] = false;
                    SetPlayerPos(i, 2234.1284,1373.6930,11.5700);
                    SetPlayerFacingAngle(i, 180.3870);
                    SetCameraBehindPlayer(i);
                    ResetPlayerWeaponsAC(i);
                }
            }
        }
    }
	#if	defined	paintball__minuteupdate
		return paintball__minuteupdate();
	#else
		return 1;
	#endif
}
#if	defined	_ALS_minuteupdate
	#undef	minuteupdate
#else
	#define	_ALS_minuteupdate
#endif

#define	minuteupdate paintball__minuteupdate
#if	defined	paintball__minuteupdate
	forward paintball__minuteupdate();
#endif

stock GivePaintBallWeapon(playerid)
{
    GivePlayerWeapon(playerid, 24, 500);
    GivePlayerWeapon(playerid, 30, 500);
    GivePlayerWeapon(playerid, 27, 500);
    return 1;
}