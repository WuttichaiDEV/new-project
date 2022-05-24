stock ShowAuctionTextDrawsForPlayer(playerid, bureau)
{
	CreateAuctionPlayerTextDraws(playerid, bureau);

	for(new i = 0; i < AUCTION_MENU_TEXT_DRAW_GLOBAL; i++)
	{
		if(i < AUCTION_MENU_TEXT_DRAW_PLAYER) PlayerTextDrawShow(playerid, AuctionPlayerTextDraws[playerid][i]);
		TextDrawShowForPlayer(playerid, AuctionGlobalTextDraws[i]);
	}
	return 1;
}

stock HideAuctionTextDrawsForPlayer(playerid)
{
	for(new i = 0; i < MAX_AUCTION_GLOBAL_TEXT_DRAWS; i++)
	{
		if(i < MAX_AUCTION_PLAYER_TEXT_DRAWS) PlayerTextDrawDestroy(playerid, AuctionPlayerTextDraws[playerid][i]);
		TextDrawHideForPlayer(playerid, AuctionGlobalTextDraws[i]);
	}

	p_info[playerid][pIsOpenAuctionMenu] = false;
	p_info[playerid][pCurrentTake] = p_info[playerid][pCurrentPage] = 0; 
	return 1;
}

stock ShowVehicleInformation(playerid, vehicle)
{
	new bureau = p_info[playerid][pBureau];

	for(new i = 0; i < MAX_VEHICLE_ANGLES; i++)
		PlayerTextDrawSetPreviewModel(playerid, AuctionPlayerTextDraws[playerid][i + 4], bureauInfo[bureau][vehicle][bCarModel]),
		PlayerTextDrawSetPreviewVehCol(playerid, AuctionPlayerTextDraws[playerid][i + 4], bureauInfo[bureau][vehicle][bColor1], bureauInfo[bureau][vehicle][bColor2]);
	
	{
		new string[47], pname[MAX_PLAYER_NAME - 3];
		strcat(pname, bureauInfo[bureau][vehicle][bRateInitiator]);

		valstr(string, p_info[playerid][pCurrentTake] + 1);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][8], string);

		format(string, sizeof string, "%s, 19%d", vehicle_name[bureauInfo[bureau][vehicle][bCarModel]-400], bureauInfo[bureau][vehicle][bStrengthPercentage]);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][9], string);

		valstr(string, bureauInfo[bureau][vehicle][bSalonPrice]);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][10], string);

		valstr(string, bureauInfo[bureau][vehicle][bAuctionPrice]);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][11], string);

		valstr(string, bureauInfo[bureau][vehicle][bMaxSpeed]);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][12], string);

		valstr(string, bureauInfo[bureau][vehicle][bMileage]);
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][13], string);

		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][14], (bureauInfo[bureau][vehicle][bTuning]) ? "have" : "haven't");
		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][15], (bureauInfo[bureau][vehicle][bPTuning]) ? "have" : "haven't");

		if(bureauInfo[bureau][vehicle][bActive])
		{
			new hour, minute, second;
			ToHHMMSS(bureauInfo[bureau][vehicle][bTime], hour, minute, second);
			format(string, sizeof string, "%02d:%02d:%02d", hour, minute, second);
			PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][19], string);

			format(string, sizeof string, "CURRENT RATE (%s): %d$", isnull(pname) ? "NONE" : pname, bureauInfo[bureau][vehicle][bCurrentRate]);
		}
		else
		{
			format(string, sizeof string, "WINNER: %s ( %d$ )", isnull(pname) ? "NONE" : pname, bureauInfo[bureau][vehicle][bCurrentRate]);
			PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][19], "FINISHED");
		}
		PlayerTextDrawShow(playerid, AuctionPlayerTextDraws[playerid][19]);

		PlayerTextDrawSetString(playerid, AuctionPlayerTextDraws[playerid][20], string);
	}

	for(new i = AUCTION_MENU_TEXT_DRAW_PLAYER; i < MAX_AUCTION_GLOBAL_TEXT_DRAWS; i++)
	{
		if(i < MAX_AUCTION_PLAYER_TEXT_DRAWS) PlayerTextDrawShow(playerid, AuctionPlayerTextDraws[playerid][i]);
		if(i >= AUCTION_MENU_TEXT_DRAW_GLOBAL) TextDrawShowForPlayer(playerid, AuctionGlobalTextDraws[i]);
	}
}