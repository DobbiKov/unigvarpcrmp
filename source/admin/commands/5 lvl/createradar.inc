CMD:createradar(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 5) return ShowCommandNotFound(playerid);
		
	SPD
	(
	    playerid, D_CREATE_RADAR, DIALOG_STYLE_LIST,
		"{"cblue"}Выберите ограничение","\
		{"cblue"}1. {FFFFFF}20 КМ/Ч\n\
		{"cblue"}2. {FFFFFF}60 КМ/Ч\n\
		{"cblue"}3. {FFFFFF}110 КМ/Ч\n\
		{"cblue"}4. {FFFFFF}90 КМ/Ч",
		"Выбрать","Отмена"
	);
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_CREATE_RADAR:
        {
            if(response)
            {
                if(GetPVarInt(playerid, "CreateRadar")) return SCM(playerid, red, "Установка радара уже начата");
                    
                SetPVarInt(playerid, "TypeRadar", listitem);
                
                new Float: posX, Float: posY, Float: posZ;
                GetPlayerPos(playerid, posX, posY, posZ);
                
                SCM(playerid, blue, "Вы начали установку радара. Установите радар на нужную позицию.");
                new radar = CreateObject(18880, posX+1, posY, posZ-0.35, 0.0, 0.0, 0.0);
                SetPVarInt(playerid, "CreateRadar", 1);
                SetPVarInt(playerid, "RadarObject", radar);
                EditObject(playerid, radar);
            }
            else return 1;
        }
    }
	#if	defined	createradar__OnDialogResponse
		return createradar__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse createradar__OnDialogResponse
#if	defined	createradar__OnDialogResponse
	forward createradar__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	if(GetPVarInt(playerid, "CreateRadar") != 0)
	{
	    if(!playerobject)
		{
			if(!IsValidObject(objectid)) return 1;
			MoveObject(objectid, fX, fY, fZ, 10.0, fRotX, fRotY, fRotZ);
		}
		
		if(response == EDIT_RESPONSE_FINAL)
		{
			TOTALRADAR++;

			switch(GetPVarInt(playerid, "TypeRadar"))
		    {
		        case 0:
		        {
				    RadarInfo[TOTALRADAR][radar_type] = 1;
					RadarInfo[TOTALRADAR][radar_speed] = 20;
				}
		        case 1:
				{
				   RadarInfo[TOTALRADAR][radar_type] = 2;
				   RadarInfo[TOTALRADAR][radar_speed] = 60;
				}
		        case 2:
				{
				    RadarInfo[TOTALRADAR][radar_type] = 3;
				    RadarInfo[TOTALRADAR][radar_speed] = 110;
				}
		        case 3:
				{
				    RadarInfo[TOTALRADAR][radar_type] = 4;
					RadarInfo[TOTALRADAR][radar_speed] = 90;
				}
		    }
			RadarInfo[TOTALRADAR][radar_x] = fX;
			RadarInfo[TOTALRADAR][radar_y] = fY;
			RadarInfo[TOTALRADAR][radar_z] = fZ;
			RadarInfo[TOTALRADAR][radar_a] = fRotZ;
			
			DestroyObject(GetPVarInt(playerid, "RadarObject"));
			RadarInfo[TOTALRADAR][radar_object] = CreateObject(18880, fX, fY, fZ, fRotX, fRotY, fRotZ);
            Iter_Add(AllRadars, TOTALRADAR);
			
            new fmt_str[80];
        	format
			(
			    fmt_str, sizeof fmt_str,
				"Радар № %d\nУстановил: %s\nОграничение скорости: %d км/ч",
				RadarInfo[TOTALRADAR][radar_id],
				PlayerInfo[playerid][pName],
				RadarInfo[TOTALRADAR][radar_speed]
			);
            RadarInfo[TOTALRADAR][radar_label] = CreateDynamic3DTextLabel(fmt_str, white, RadarInfo[TOTALRADAR][radar_x], RadarInfo[TOTALRADAR][radar_y], RadarInfo[TOTALRADAR][radar_z]+4.0, 10.0);
			
			RadarInfo[TOTALRADAR][radar_zone] = CreateDynamicSphere(RadarInfo[TOTALRADAR][radar_x], RadarInfo[TOTALRADAR][radar_y], RadarInfo[TOTALRADAR][radar_z], 10);
			
			DeletePVar(playerid, "CreateRadar");
			DeletePVar(playerid, "TypeRadar");
			DeletePVar(playerid, "RadarObject");
			CancelEdit(playerid);

			new str[512];
			format
			(
   			    str,sizeof(str),
				"INSERT INTO `radars`\
				(\
			        `radar_set`,\
	   				`radar_type`,\
	   				`radar_speed`,\
					`radar_x`,\
					`radar_y`,\
					`radar_z`,\
					`radar_a`\
				)\
				VALUES ('%s', %i, %i, '%f', '%f', '%f', '%f')",
				PlayerInfo[playerid][pName],
				RadarInfo[TOTALRADAR][radar_type],
				RadarInfo[TOTALRADAR][radar_speed],
				RadarInfo[TOTALRADAR][radar_x],
				RadarInfo[TOTALRADAR][radar_y],
				RadarInfo[TOTALRADAR][radar_z],
				RadarInfo[TOTALRADAR][radar_a]
			);
			mysql_tquery(connects, str, "", "");
			
			SCM(playerid, blue, "Радар успешно создан.");
		}
		if(response == EDIT_RESPONSE_CANCEL)
		{
			DeletePVar(playerid, "CreateRadar");
			DeletePVar(playerid, "TypeRadar");
			DeletePVar(playerid, "RadarObject");
			
			DestroyObject(GetPVarInt(playerid, "RadarObject"));
			
			CancelEdit(playerid);
			SCM(playerid, blue, "Вы отменили установку радара");
		}
	}
	if(response == EDIT_RESPONSE_CANCEL)
	{
		DestroyObject(objectid);
		CancelEdit(playerid);
	}
	if(response == EDIT_RESPONSE_FINAL)
	{
		CancelEdit(playerid);
	}
	#if	defined	createradar__OnPlayerEditObject
		return createradar__OnPlayerEditObject(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerEditObject
	#undef	OnPlayerEditObject
#else
	#define	_ALS_OnPlayerEditObject
#endif

#define	OnPlayerEditObject createradar__OnPlayerEditObject
#if	defined	createradar__OnPlayerEditObject
	forward createradar__OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ);
#endif