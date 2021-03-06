new player_in_bath[MAX_PLAYERS] = -1;

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 661.4055,2323.3774,1504.3500))
        {
            if(GetPVarInt(playerid, "bath_buy") == 1) return SCM(playerid, red, "�� ��� ������ ��������� � ����.");
            SPD
            (
                playerid, D_BATH_BUY, DIALOG_STYLE_MSGBOX,
                "{"cblue"}������� ����������",
                "{FFFFFF}�� ������ ������ ��������� � ����? ��������� ���������� {"cblue"}500 ������{ffffff}.",
                "��", "���"
            );
        }
    }
	#if	defined	bath__OnPlayerKeyStateChange
		return bath__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange bath__OnPlayerKeyStateChange
#if	defined	bath__OnPlayerKeyStateChange
	forward bath__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_BATH_BUY:
        {
            if(!response) return 1;
            else
            {
                if(PlayerInfo[playerid][pCash] < 500) return SCM(playerid, red, "� ��� ������������ �����!");

                SCM(playerid, blue, "�� ������ ���������, �������� � ����.");
                SetPVarInt(playerid, "bath_buy", 1); 
                GiveMoney(playerid, -500, "������� ���������� � ����");
            }
        }
    }
	#if	defined	bath__OnDialogResponse
		return bath__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse bath__OnDialogResponse
#if	defined	bath__OnDialogResponse
	forward bath__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

publics PlayerSecondTimer(playerid)
{
    new hour, minute, second;
    gettime(hour, minute, second);
    if(second % 3 == 0)
    {
        if(player_in_bath[playerid] == 1 && PlayerInfo[playerid][pNeedWash] < 100)
        {
            PlayerInfo[playerid][pNeedWash]++;
            GameTextForPlayer(playerid, "~g~+1", 500, 4);
            SetPlayerChatBubble(playerid, "+1", 0x33AA33FF, 13.0, 300);
            if(PlayerInfo[playerid][pNeedWash] == 100)
            {
                SCM(playerid, green, "������ ��� �������� ����.");
                SaveAccounts(playerid);
            }
        }
    }

    #if defined bath__PlayerSecondTimer
        return bath__PlayerSecondTimer(playerid);
    #else
        return 1;
    #endif
}
#if	defined	_ALS_PlayerSecondTimer
	#undef	PlayerSecondTimer
#else
	#define	_ALS_PlayerSecondTimer
#endif

#define	PlayerSecondTimer bath__PlayerSecondTimer
#if	defined	bath__PlayerSecondTimer
	forward bath__PlayerSecondTimer(playerid); 
#endif