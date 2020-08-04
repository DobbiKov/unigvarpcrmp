#define MAX_KVARTS 100
new TotalFreeKvart;
new player_in_kvart[MAX_PLAYERS] = -1;
new totalkvart;

enum kvart_params_info
{
    rent, 
    Float:kvart_spawn_x,
    Float:kvart_spawn_y,
    Float:kvart_spawn_z,
    Float:kvart_spawn_a,

    Float:kvart_exit_x,
    Float:kvart_exit_y,
    Float:kvart_exit_z,
    Float:kvart_exit_a,
}
new kvart_params[1][kvart_params_info] =
{
    {2000, -2303.8125,359.5068,-86.4541,182.8116,   -2294.8171,364.9778,-86.4541,359.8232}
};

enum E_KVART_DATA
{
    kvart_id,
    kvart_days,
    kvart_type,
    kvart_pod_id,
    kvart_Owned,
    kvart_Owner[MAX_PLAYER_NAME],

    kvart_pick,
}
new KvartInfo[MAX_KVARTS][E_KVART_DATA];

enum E_KVART_POS
{
    Float:kvart_enter_pos_x,
    Float:kvart_enter_pos_y,
    Float:kvart_enter_pos_z,
    Float:kvart_enter_pos_a,
}
new KvartPos[8][E_KVART_POS] = 
{
    {2446.4678,-2083.9604,-2.5775,0.0407},
    {2445.7605,-2085.2776,-2.5775,89.0282},
    {2446.3169,-2086.6499,-2.5775,176.7623},
    {2445.7903,-2085.2192,1.5084,99.3916},
    {2446.2803,-2086.6499,1.5084,189.6324},
    {2446.4727,-2083.9602,5.6022,359.1474},
    {2445.7603,-2085.1570,5.6022,98.1617},
    {2446.2703,-2086.6394,5.6022,179.3158}
};