public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == 1024)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 817.4346,806.6161,-72.9914))
        {
			if(PlayerInfo[playerid][pMember] > 0) return SCM(playerid, red, "�� �������� � �����������!");

			SPD(playerid, D_SET_JOB, DIALOG_STYLE_LIST, "{"cblue"}���������� �� ������", "\
			{"cblue"}1. {FFFFFF}�������� ��������\t\t\t{"cblue"}(2 �������)\n\
			{"cblue"}2. {FFFFFF}�������� �����\t\t\t{"cblue"}(3 �������)\n\
			{"cblue"}3. {FFFFFF}�����������\t\t\t\t{"cblue"}(4 �������)\n\
			{"cblue"}4. {FFFFFF}������������\t\t\t{"cblue"}(6 �������)", "��", "�������");
        }
    }
	#if	defined	jobs__OnPlayerKeyStateChange
		return jobs__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnPlayerKeyStateChange
	#undef	OnPlayerKeyStateChange
#else
	#define	_ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange jobs__OnPlayerKeyStateChange
#if	defined	jobs__OnPlayerKeyStateChange
	forward jobs__OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
		case D_SET_JOB:
		{
		    if(!response) return 1;
		    else
		    {
		        switch(listitem)
		        {
		            case 0:
		            {
		                if(PlayerInfo[playerid][pLVL] < 2) return SCM(playerid, red, "��� � �������� ��������� ��������, ����� ������� 2 ������� �������!");
		                
		                PlayerInfo[playerid][pJob] = Job_Bus;
						SaveAccounts(playerid);
		                SCM(playerid, blue, "�� ������� ���������� ��������� ��������!");
		                SCM(playerid, blue, "������ �������������� ���������� �� ������� ����� �������: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 1:
		            {
		                if(PlayerInfo[playerid][pLVL] < 3) return SCM(playerid, red, "��� � �������� ��������� �����, ����� ������� 3 ������� �������!");
		                
		                PlayerInfo[playerid][pJob] = Job_Taxi;
		                SaveAccounts(playerid);
		                SCM(playerid, blue, "�� ������� ���������� ��������� �����!");
		                SCM(playerid, blue, "������ �������������� ���������� �� ������� ����� �������: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 2:
		            {
		                if(PlayerInfo[playerid][pLVL] < 4) return SCM(playerid, red, "��� � �������� �������������, ����� ������� 4 ������� �������!");
		                
		                PlayerInfo[playerid][pJob] = Job_Car;
              			SaveAccounts(playerid);
		                SCM(playerid, blue, "�� ������� ���������� �������������!");
		                SCM(playerid, blue, "������ �������������� ���������� �� ������� ����� �������: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
		            }
		            case 3:
		            {
		                if(PlayerInfo[playerid][pLVL] < 6) return SCM(playerid, red, "��� � �������� ��������������, ����� ������� 6 ������� �������!");
		                
		                PlayerInfo[playerid][pJob] = Job_Truck;
	                	SaveAccounts(playerid);
		                SCM(playerid, blue, "�� ������� ���������� ��������������!");
		                SCM(playerid, blue, "������ �������������� ���������� �� ������� ����� �������: {"cyellow"}/mm{"cblue"}, {"cyellow"}/help{"cblue"}");
          			}
		        }
		    }
		}
    }
	#if	defined	jobs__OnDialogResponse
		return jobs__OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 1;
	#endif
}
#if	defined	_ALS_OnDialogResponse
	#undef	OnDialogResponse
#else
	#define	_ALS_OnDialogResponse
#endif

#define	OnDialogResponse jobs__OnDialogResponse
#if	defined	jobs__OnDialogResponse
	forward jobs__OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif