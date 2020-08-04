public OnPlayerConnect(playerid)
{
	SendClientMessage(playerid,0x01010101, "$cmd get_custom_hash");
	#if	defined	modpack__OnPlayerConnect
		return modpack__OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerConnect
	#undef	OnPlayerConnect
#else
	#define	_ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect modpack__OnPlayerConnect
#if	defined	modpack__OnPlayerConnect
	forward modpack__OnPlayerConnect(playerid);
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(strfind(cmdtext, "$response get_custom_hash", true) != -1) 
	{
	    new packhash[64]; 
		strmid(packhash, cmdtext, 26, strlen(cmdtext));
	    if(!strcmp(packhash, "747cf2873dc83966", true))
	    {
	        ModPack[playerid] = true;
	        SCM(playerid, blue, "Пакет модификаций загружен!");
	    }
	    else
	    {
	        ModPack[playerid] = false;
	        SCM(playerid, red, "У вас не установлен пакет модификаций!");
	    }
    	return true;
	}
	#if	defined	modpack__OnPlayerCommandText
		return modpack__OnPlayerCommandText(playerid, cmdtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerCommandText
	#undef	OnPlayerCommandText
#else
	#define	_ALS_OnPlayerCommandText
#endif

#define	OnPlayerConnect modpack__OnPlayerCommandText
#if	defined	modpack__OnPlayerCommandText
	forward modpack__OnPlayerCommandText(playerid, cmdtext[]);
#endif