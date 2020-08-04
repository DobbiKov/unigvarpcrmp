//************* | MYSQL | *************//
#define 	sqlhost     "151.80.47.109"
#define 	sqluser     "gs37636"
#define 	sqlpass     "C2nOK6JRV6"
#define 	sqldb       "gs37636"

//*********** |  | ***********//
#define 	gamemode    "UNIGVA - Beta 0.2"
#define     hostname    "[ Unigva RolePlay | Разработка с 0 ]"
#define     mapname     "Criminal Russia"
#define     site_url    "dobbikov.gq"
#define     name_serv   "Unigva RolePlay"
#define     forum_url   "dobbikov.gq"

//************* |  | *************//
#define     red        	0xFF0000AA
#define     lightred   	0xFF0033FF
#define     grey       	0xAFAFAFAA
#define     lightgrey  	0xD3D3D3FF
#define     orange     	0xFF9900AA
#define     lightorange 0xFFA161FF
#define     green       0x33AA33AA
#define     lightgreen  0x00FF00AA
#define     yellow      0xFFFF00AA
#define     lightyellow 0xFFFF47FF
#define     blue        0x0099FFAA
#define     lightblue   0x6475BFFF
#define     purple      0xDD90FFFF
#define     white       0xFFFFFFFF
#define     need        0x87bae7FF

#define     cred        #FF0000
#define     clred       #FF0033
#define     cgrey       #AFAFAF
#define     clgrey      #D3D3D3
#define     corange     #FF9900
#define     clorange    #FFA161
#define     cgreen      #33AA33
#define     clgreen     #00FF00
#define     cyellow     #FFFF00
#define     cblue       #0099FF
#define     clblue      #6475BF
#define     cwhite      #FFFFFF
#define     cerror      #AB1313
//************* |  | *************//
#define 	SCM 		SendClientMessage
#define 	SCMTA 		SendClientMessageToAll
#define     SPD         ShowPlayerDialog

#define 	IsValidEmail(%1) regex_match(%1, "|([a-z0-9_\\.\\-]{1,20})@([a-z0-9\\.\\-]{1,20})\\.([a-z]{2,4})|is")

#define     publics%0(%1)			    forward%0(%1); public%0(%1)
#define 	FreezePlayer(%0,%1)    	    TogglePlayerControllable(%0, false), SetTimerEx("PlayerToggle", %1, false, "d", %0)
#define     ShowCommandNotFound(%0)     SCM(%0, white, !"{"cwhite"}Команда не найдена. Используйте {"cblue"}/menu {"cwhite"}для поиска команд.")
#define     YouCannotUseThisFunc(%0)    SCM(%0, red, !"Вы не можете использовать жанную функцию.")
#define     PlayerOffLine(%0)           SCM(%0, red, !"Игрок оффлайн.")
#define 	NewKick(%0) 			    SetTimerEx("DelayedKick", 1000, false, "d", (%0))
#define     GetPlayerRank(%0)           PlayerRank[PlayerInfo[%0][pMember]][PlayerInfo[%0][pRang]]

#define 	PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
native 		IsValidVehicle(vehicleid);

#if !defined SPECIAL_ACTION_PISSING
    const SPECIAL_ACTION_PISSING = 68;
#endif

new stock SuperNick_S[5][MAX_PLAYER_NAME] = {"Eduard_Dobbikov", "Dregory_Dobbikov", "Sam_Esmail", "Lewis_Clifford", "Roman_Dobbikov"};

// native GameTextForAll(const string[],time,style);
// native GameTextForPlayer(playerid,const string[],time,style);
// native Menu:CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0);
// native AddMenuItem(Menu:menuid, column, const menutext[]);
// native SetMenuColumnHeader(Menu:menuid, column, const columnheader[]);
// native Text:TextDrawCreate(Float:x, Float:y, text[]);
// native TextDrawSetString(Text:text, string[]);