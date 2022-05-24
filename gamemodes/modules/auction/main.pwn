#define MAX_BUREAU 				3
#define MAX_AUCTION_CARS		6
#define MAX_VEHICLES_IN_PAGE	3
#define MAX_VEHICLE_ANGLES		4		
#define MAX_PAGES				"2"

#define MAX_AUCTION_GLOBAL_TEXT_DRAWS 	47
#define MAX_AUCTION_PLAYER_TEXT_DRAWS 	21
#define AUCTION_MENU_TEXT_DRAW_GLOBAL	14 		  
#define AUCTION_MENU_TEXT_DRAW_PLAYER	4	  

enum _:E_BUREAU_INFO_
{
	bool: bActive,
	bCarModel,
	bColor1,
	bColor2,
	bSalonPrice,
	bAuctionPrice,
	bStrengthPercentage,
	bMaxSpeed,
	bMileage,
	bool:bTuning,
	bool:bPTuning,
	bCurrentRate,
	bRateInitiator[MAX_PLAYER_NAME - 3],
	bRaterID,
	bTime,
	bDeliveryTime
}
new bureauInfo[MAX_BUREAU][MAX_AUCTION_CARS][E_BUREAU_INFO_];
new portInfo[MAX_BUREAU * MAX_AUCTION_CARS][E_BUREAU_INFO_];

static const E_BUREAU_INFO__EOS_[E_BUREAU_INFO_] =
{
	false,
	0,
	0,
	0,
	0,
	0,	
	0, 
	0,
	0,
	false,
	false,
	0,
	EOS,
	-1,
	0,
	0
};

/************************* variables *************************/
new Text:AuctionGlobalTextDraws[MAX_AUCTION_GLOBAL_TEXT_DRAWS];
new PlayerText:AuctionPlayerTextDraws[MAX_PLAYERS][MAX_AUCTION_PLAYER_TEXT_DRAWS];

new Float:PortCarSpawns[][] = 
{
	{-1737.3162,70.1695,3.2847},
	{-1737.4431,67.0080,3.2847},
	{-1737.6472,63.7208,3.2847},
	{-1737.6412,60.4336,3.2847},
	{-1737.4703,57.3733,3.2847},
	{-1737.5516,54.0708,3.2847},
	{-1737.7354,50.9582,3.2847},
	{-1737.3367,47.7742,3.2847},
	{-1737.5211,44.5083,3.2847},
	{-1737.5002,20.9534,3.2847},
	{-1737.5527,17.7538,3.2847},
	{-1737.4506,14.5410,3.2847},
	{-1737.6881,11.3842,3.2847},
	{-1737.6052,8.1429,3.2847},
	{-1737.7052,4.9223,3.2818},
	{-1737.4720,1.7255,3.2818},
	{-1737.9193,-1.4781,3.2818},
	{-1737.6820,-4.6473,3.2833}
};

new AuctionVehiclesList[] = { 411, 424, 426, 429, 451, 477, 480, 494, 495, 506, 533, 534, 535, 536, 541, 545, 555, 558, 559, 560 };
new VehicleComponents[] = { 0, 1008, 1009, 1010, 1018, 1019, 1020, 1021, 1022, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081,
							1082, 1083, 1084, 1085, 1086, 1087};

new runningAuctionsCount = 0, unactiveCars = 0;
new bureauSfEnterPick, bureauExitPick; //bureauLsEnterPick, bureauLvEnterPick;
new selectedCar[MAX_PLAYERS] = {-1, ...};

#include "C:\Users\grish\OneDrive\Desktop\gamemodes\gamemodes\modules\auction\load_modules.hxx"

public OnGameModeInit()
{
	CreateAuctionGlobalTextDraws();

	for(new bureau = 0; bureau < MAX_BUREAU; bureau++)
	{
		for(new vehicleid = 0; vehicleid < MAX_AUCTION_CARS; vehicleid++)
		{
			bureauInfo[bureau][vehicleid] = E_BUREAU_INFO__EOS_;
		}
	}

	CreateDynamic3DTextLabelEx("Участвовать в аукционе\n{FFFFFF}[Нажмите LALT]", COLOR_GOLD, 1396.0505,-15.1006,1000.9233, 3.0, .worlds = {0, 1, 2}, .interiors = { 3 });
	CreateDynamic3DTextLabelEx("Участвовать в аукционе\n{FFFFFF}[Нажмите LALT]", COLOR_GOLD, 1391.9778,-15.0176,1000.9233, 3.0, .worlds = {0, 1, 2}, .interiors = { 3 });
	CreateDynamic3DTextLabelEx("Участвовать в аукционе\n{FFFFFF}[Нажмите LALT]", COLOR_GOLD, 1393.3925,-12.5843,1000.9233, 3.0, .worlds = {0, 1, 2}, .interiors = { 3 });
	CreateDynamic3DTextLabelEx("Участвовать в аукционе\n{FFFFFF}[Нажмите LALT]", COLOR_GOLD, 1397.2654,-12.5508,1000.9233, 3.0, .worlds = {0, 1, 2}, .interiors = { 3 });
	CreateDynamic3DTextLabelEx("Получить автомобиль\n{FFFFFF}[Нажмите LALT]", COLOR_GOLD, -1734.1409,37.3734,3.5547, 3.0);

	bureauExitPick = CreateDynamicPickupEx(19130, 23, 1399.0337,-13.8485,1000.9233, .worlds = {0, 1, 2}, .interiors = { 3 });
	bureauSfEnterPick = CreateDynamicPickup(19130, 23, -2332.4890,-152.5884,35.3203);

	CreateDynamicPickup(19134, 23, -1734.1409,37.3734,3.5547);

	#if defined auction_OnGameModeInit
		return auction_OnGameModeInit();
	#endif
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(pickupid == bureauSfEnterPick)
	{
		SetPlayerPos(playerid, 1397.5748,-13.5947,1000.9233);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 180.0);
		return 1;
	}
	else if(pickupid == bureauExitPick)
	{
		SetPlayerPos(playerid, -2332.2312,-154.8795,35.3203);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 180.0);

		return 1;
	}

	#if defined auction_OPPDP
		return auction_OPPDP();
	#endif
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_WALK)
	{                                        
		if(IsPlayerInRangeOfPoint(playerid, 10.0, 1395.5830,-13.9561,1000.9233) && (0 <= GetPlayerVirtualWorld(playerid) < 3))
		{
			p_info[playerid][pBureau] = GetPlayerVirtualWorld(playerid);

			ShowAuctionTextDrawsForPlayer(playerid, p_info[playerid][pBureau]);
			SelectTextDraw(playerid, 0x00FF00FF);

			return 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1734.1409,37.3734,3.5547))
		{
			Dialog_Show(playerid, "CarTakeDialog");
		}
	}

	#if defined auction_OPKSC
		return auction_OPKSC();
	#endif
}

	GetPlayerName(playerid, p_info[playerid][pName], MAX_PLAYER_NAME - 3);
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	for(new i = 0; i < MAX_VEHICLES_IN_PAGE; i++)
	{
		if(clickedid == AuctionGlobalTextDraws[i + 8])
		{
			p_info[playerid][pCurrentTake] = i + p_info[playerid][pCurrentPage] * MAX_VEHICLES_IN_PAGE;
			ShowVehicleInformation(playerid, p_info[playerid][pCurrentTake]);
			p_info[playerid][pIsOpenAuctionMenu] = true;

			return 1;
		}
	}

	if(clickedid == AuctionGlobalTextDraws[12])
	{
		if(p_info[playerid][pCurrentPage] == 0) return 1;

		new bureau = p_info[playerid][pBureau], string[4];
		p_info[playerid][pCurrentPage]--;

		for(new i = 0, veh = p_info[playerid][pCurrentPage] * MAX_VEHICLES_IN_PAGE; i < MAX_VEHICLES_IN_PAGE; i++, veh++)
		{
			PlayerTextDrawSetPreviewModel(playerid, AuctionPlayerTextDraws[playerid][i], bureauInfo[bureau][veh][bCarModel]); 
			PlayerTextDrawSetPreviewVehCol(playerid, AuctionPlayerTextDraws[playerid][i], bureauInfo[bureau][veh][bColor1], bureauInfo[bureau][veh][bColor2]);

			PlayerTextDrawShow(playerid, AuctionPlayerTextDraws[playerid][i]);

			valstr(string, veh + 1);
			PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][i + 16], string);
		}

		format(string, sizeof string, "%d/"MAX_PAGES"", p_info[playerid][pCurrentPage] + 1);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][3], string);

		return 1;
	}

	if(clickedid == AuctionGlobalTextDraws[13])
	{
		if(p_info[playerid][pCurrentPage] == 1) return true;
		
		new bureau = p_info[playerid][pBureau], string[4];
		p_info[playerid][pCurrentPage]++;

		for(new i = 0, veh = p_info[playerid][pCurrentPage] * MAX_VEHICLES_IN_PAGE; i < MAX_VEHICLES_IN_PAGE; i++, veh++)
		{
			PlayerTextDrawSetPreviewModel(playerid, AuctionPlayerTextDraws[playerid][i], bureauInfo[bureau][veh][bCarModel]); 
			PlayerTextDrawSetPreviewVehCol(playerid, AuctionPlayerTextDraws[playerid][i], bureauInfo[bureau][veh][bColor1], bureauInfo[bureau][veh][bColor2]);

			PlayerTextDrawShow(playerid, AuctionPlayerTextDraws[playerid][i]);

			valstr(string, veh + 1);
			PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][i + 16], string);
		}
		format(string, sizeof string, "%d/"MAX_PAGES"", p_info[playerid][pCurrentPage] + 1);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][3], string);

		return 1;
	}

	else if(clickedid == AuctionGlobalTextDraws[41])
	{
		ShowVehicleInformation(playerid, p_info[playerid][pCurrentTake] + p_info[playerid][pCurrentPage] * MAX_VEHICLES_IN_PAGE);
		return 1;
	}

	else if(clickedid == AuctionGlobalTextDraws[42])
	{
		HideAuctionTextDrawsForPlayer(playerid);
		CancelSelectTextDraw(playerid);
		return 1;
	}

	else if(clickedid == AuctionGlobalTextDraws[43])
	{
		if(!bureauInfo[p_info[playerid][pBureau]][p_info[playerid][pCurrentTake]][bActive]) 
			return SendClientMessage(playerid, COLOR_GREY, "[Ошибка] Данный аукцион уже закончен");

		Dialog_Show(playerid, "ToDoRateDialog");
		return 1;
	}

	#if defined auction_OPCTD
		return auction_OPCTD();
	#endif
}

stock ClearVehInfo(veh) portInfo[veh] = E_BUREAU_INFO__EOS_;

#if defined _ALS_OnPlayerClickTextDraw
    #undef    OnPlayerClickTextDraw
#else

    #define    auction_OPCTD
#endif
#define    OnPlayerClickTextDraw     auction_OPCTD
#if defined  auction_OPCTD
forward auction_OPCTD();
#endif 

#if defined _ALS_OnPlayerKeyStateChange
    #undef    OnPlayerKeyStateChange
#else

    #define    _ALS_OPPDP
#endif
#define    OnPlayerKeyStateChange     auction_OPKSC
#if defined  auction_OPKSC
forward auction_OPKSC();
#endif 


#if defined _ALS_OnPlayerPickUpDynamicPickup
    #undef    OnPlayerPickUpDynamicPickup
#else

    #define    _ALS_OPPDP
#endif
#define    OnPlayerPickUpDynamicPickup     auction_OPPDP
#if defined  auction_OPPDP
forward auction_OPPDP();
#endif 

#if defined _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else

    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit     auction_OnGameModeInit
#if defined  auction_OnGameModeInit
forward auction_OnGameModeInit();
#endif 