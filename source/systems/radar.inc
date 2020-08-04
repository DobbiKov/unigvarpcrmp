#define MAX_RADARS 100
enum r_info
{
	radar_id,
	radar_set[24],
	radar_type,
	radar_speed,
	Float:radar_x,
	Float:radar_y,
	Float:radar_z,
	Float:radar_a,
	radar_object,
	Text3D:radar_label,
	radar_zone
}

new RadarInfo[MAX_RADARS][r_info];
new TOTALRADAR;
new Iterator: AllRadars<MAX_RADARS>;

publics LoadRadar()
{
    static rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        for(new i; i < rows[0]; i++)
        {
            RadarInfo[i][radar_id] = cache_get_field_content_int(i, "radar_id");
            cache_get_field_content(i, "radar_set", RadarInfo[i][radar_set], connects, MAX_PLAYER_NAME);
            RadarInfo[i][radar_type] = cache_get_field_content_int(i, "radar_type");
            RadarInfo[i][radar_speed] = cache_get_field_content_int(i, "radar_speed");
            RadarInfo[i][radar_x] = cache_get_field_content_float(i, "radar_x");
            RadarInfo[i][radar_y] = cache_get_field_content_float(i, "radar_y");
            RadarInfo[i][radar_z] = cache_get_field_content_float(i, "radar_z");
            RadarInfo[i][radar_a] = cache_get_field_content_float(i, "radar_a");

            new fmt_str[80];
        	format
			(
			    fmt_str, sizeof fmt_str,
				"Радар № %d\nУстановил: %s\nОграничение скорости: %d км/ч",
				RadarInfo[i][radar_id],
				RadarInfo[i][radar_set],
				RadarInfo[i][radar_speed]
			);

            RadarInfo[i][radar_label] = CreateDynamic3DTextLabel(fmt_str, white, RadarInfo[i][radar_x], RadarInfo[i][radar_y], RadarInfo[i][radar_z]+4.0, 10.0);

            RadarInfo[i][radar_object] = CreateDynamicObject(18880, RadarInfo[i][radar_x], RadarInfo[i][radar_y], RadarInfo[i][radar_z], 0.0, 0.0, RadarInfo[i][radar_a]);
            RadarInfo[i][radar_zone] = CreateDynamicSphere(RadarInfo[i][radar_x], RadarInfo[i][radar_y], RadarInfo[i][radar_z], 10.0);

            Iter_Add(AllRadars, i);
            TOTALRADAR++;
        }
    }
    return printf("[UNIGVA]: Всего загружено радаров: %d", TOTALRADAR);
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	foreach(new r_id : AllRadars)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
			if(areaid == RadarInfo[r_id][radar_zone])
	        {
	            {
	                callback_radar(playerid, r_id);
				}
			}
		}
	}
	#if defined radar__OnPlayerEnterDynamicArea
        return radar__OnPlayerEnterDynamicArea(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea radar__OnPlayerEnterDynamicArea
#if defined radar__OnPlayerEnterDynamicArea
    forward radar__OnPlayerEnterDynamicArea(playerid, areaid);
#endif

publics callback_radar(playerid, r_id)
{
    new speed = SpeedVehicle(playerid);
    
    if(speed > RadarInfo[r_id][radar_speed]+10)
    {
		new speeding = (speed - RadarInfo[r_id][radar_speed]);
	    new fine = (speed - RadarInfo[r_id][radar_speed])*RadarInfo[r_id][radar_speed];

		PlayerInfo[playerid][pFines]++;
		PlayerInfo[playerid][pSumFines] += fine;

		if(PlayerInfo[playerid][pFines] >= 30)
		{
			PlayerInfo[playerid][pLicA] = 0;
			PlayerInfo[playerid][pLicB] = 0;
			PlayerInfo[playerid][pLicC] = 0;
			PlayerInfo[playerid][pLicD] = 0;

			SCM(playerid, red, "Вы были лишены водительских прав за неуплату 30 штрафов.");
			SCM(playerid, blue, "Оплатить штрафы Вы можете в любом банкомате. Просмотр штрафов: /tickets");
		}
	    else
	    {
	    	new hours, minutes, sec;
		    gettime(hours, minutes, sec);

			static const fmt_query[] = "INSERT INTO `fines` (`account_id`, `fined`, `fine`, `date`, `reason`) VALUES ('%d', '%s', '%d', '%s %02d:%02d:%02d', 'Превышение скорости на %d км/ч')";
			new query[sizeof(fmt_query)+(-2+3)+(-2+MAX_PLAYER_NAME)+(-2+6)+(-2+30)+(-2+30)];
			format(query, sizeof(query), fmt_query, PlayerInfo[playerid][pID], RadarInfo[r_id][radar_set], fine, date("%dd.%mm.%yyyy", gettime()), hours, minutes, sec, speeding);
			mysql_tquery(connects, query, "", "");

			SCM(playerid, blue, "Вам выписан штраф за превышение скорости. Подробней /tickets");

			static const fmt_msg[] = "Количество штрафов: %d/30 до изьятия водительских прав";
			new string[sizeof(fmt_msg)+(-2+2)];
			format(string, sizeof(string), fmt_msg, PlayerInfo[playerid][pFines]);
			SCM(playerid, blue, string);
		}
		SaveAccounts(playerid);
	}
	return 1;
}