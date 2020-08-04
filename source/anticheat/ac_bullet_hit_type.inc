public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(hittype == BULLET_HIT_TYPE_PLAYER)
    {
        if((floatcmp(floatabs(fX), 20.0) == 1)
        || (floatcmp(floatabs(fY), 20.0) == 1)
        || (floatcmp(floatabs(fZ), 20.0) == 1))
        {
            if(AntiCheatInfo[BulletHitType_AC][acStatus] == 1) ResultCheat(playerid, 12);
            else ResultMessageCheat(playerid, 12);
            return 1;
        }
    }
#if    defined    hotfix_OnPlayerWeaponShot
    return hotfix_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
#else
    return 1;
#endif
}
#if    defined    _ALS_OnPlayerWeaponShot
    #undef    OnPlayerWeaponShot
#else
    #define    _ALS_OnPlayerWeaponShot
#endif
#define    OnPlayerWeaponShot    hotfix_OnPlayerWeaponShot
#if    defined    hotfix_OnPlayerWeaponShot
forward    hotfix_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif 