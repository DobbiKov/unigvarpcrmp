CMD:openvdv(playerid)
{
	if(PlayerInfo[playerid][pMember] != TEAM_VDV && PlayerInfo[playerid][pMember] != TEAM_FSB)
		return SCM(playerid, red, "Вам недоступна данная возможность");
	
	if(PlayerInfo[playerid][pMember] == TEAM_VDV && PlayerInfo[playerid][pRang] < 3)
		return SCM(playerid, red, "Вам недоступна данная возможность");
	
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, 1892.1500, 1722.0699, 15.6500)) return 1;
	
	switch(open_vdv_status)
	{
		case 0:
		{
			MoveObject(open_vdv, 1892.1500, 1717.0699, 15.65, 3.0);
			
			open_vdv_status = 1;
			
			SCM(playerid, blue, "Вы открыли ворота");
			
			SetPlayerChatBubble(playerid,"Открывает ворота",blue,30.0,10000);
		}
		case 1:
		{
			MoveObject(open_vdv, 1892.15, 1722.07, 15.65, 3.0);
			
			open_vdv_status = 0;
			
			SCM(playerid, red, "Вы закрыли ворота");
			
			SetPlayerChatBubble(playerid,"Закрывает ворота",red,30.0,10000);
		}
	}
	return 1;
}