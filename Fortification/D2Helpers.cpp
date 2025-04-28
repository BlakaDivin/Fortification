#include "injection.h"

void PrintText(DWORD Color, char *szText, ...)
{
		if(GameReady())
		{
			char szBuffer[152] = {0};
			va_list Args;
			va_start(Args, szText);
			vsprintf_s(szBuffer,152, szText, Args);
			va_end(Args); 
			wchar_t Buffer[0x130];
			MultiByteToWideChar(0, 1, szBuffer, 152, Buffer, 304);
			D2CLIENT_PrintGameString(Buffer, Color);
		}
}

BOOL GameReady(VOID)
{
	if (!pMe)
		return FALSE;

	if(VALIDPTR(D2CLIENT_GetPlayerUnit()) && !*p_D2WIN_FirstControl)
		if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pInventory))
			if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath))
				if(D2CLIENT_GetPlayerUnit()->pPath->xPos)
					if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1))
						if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2))
							if(VALIDPTR(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel))
								if(D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo)
									if (VALIDPTR(D2CLIENT_GetPlayerUnit()->pAct))
										if(GetPlayerArea() != NULL)
											return TRUE;
	return FALSE;
}

DWORD GetPlayerArea(VOID)
{
	return D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;
	//return *p_D2CLIENT_PlayerArea;
}

Level* GetLevel(DWORD dwLevelNo)
{
	for(Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if(pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}

bool IsTownLevel(int nLevel)
{
	if(nLevel == MAP_A1_ROGUE_ENCAMPMENT ||
		nLevel == MAP_A2_LUT_GHOLEIN || 
		nLevel == MAP_A3_KURAST_DOCKS ||
		nLevel == MAP_A4_THE_PANDEMONIUM_FORTRESS ||
		nLevel == MAP_A5_HARROGATH)
		return TRUE;
	return FALSE;
}

// Getting Distance from units.
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
	return (DWORD)sqrt((double)(( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))))); }

DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
 	return (DWORD)sqrt((double)( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))); }

DWORD GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo)
{
	for(RoomTile* pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
	{
		if(*(pRoomTile->nNum) == dwTileNo)
			return pRoomTile->pRoom2->pLevel->dwLevelNo;
	}

	return NULL;
}

LONG WINAPI GameEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN)
	{
		if(GameReady() && v_Authed) /*Authentication Check*/
		{
			if(!OnKey(false, wParam, lParam))
					return false;

			if (wParam == 187 && ((lParam &0x4000) == 0)) //Auto Juv Percent
			{
				if (InTown(pMe) && IsBotSafe())
				{
				v_Bot = !v_Bot;

				ResetBot();

				if (v_Bot)
				PrintConsoleString("ÿc4Launched Avatar Plugin: You Are Now Botting...");
				else
				PrintConsoleString("ÿc4Stopped Avatar Plugin: Bot Stopped.");
				}
				else
				{
					PrintText(0, "ÿc1WARNING! You Must Be In Harrogath Above The Stairs To Launch Avatar.");
				}
			}

			if (wParam == 104 && ((lParam &0x4000) == 0)) //Auto Juv Percent
			{
				v_AutoRejuvPercent += 10;

				if (v_AutoRejuvPercent >= 100)
					v_AutoRejuvPercent = 0;

				PrintConsoleString("ÿc4Changed Auto Rejuv To %d", v_AutoRejuvPercent);
			}

			if (wParam == 102 && ((lParam &0x4000) == 0)) //Maphack Toggle
			{
				v_Maphack = !v_Maphack;

				if (v_Maphack)
					PrintConsoleString("ÿc4Maphack Enabled, Fortification Will Automatically Reveal Map");
				else
					PrintConsoleString("ÿc4Maphack Disabled, Fortification Will Not Reveal Map");
			}

			if (wParam == 101 && ((lParam &0x4000) == 0)) //PickIt Config
			{
				if (!GetUIVar(UI_CHAT))
			    {
					v_PickItConfig = !v_PickItConfig;

					if (v_PickItConfig)
						PrintConsoleString("ÿc4Opened PickIt Config, Pass Your Mouse On Features To Enable Or Disable");
					else
						PrintConsoleString("ÿc4Closed PickIt Config");
				}
			}

			if (wParam == K_QuickLeft1 && ((lParam &0x4000) == 0)) //Left 1
			{
				if (!GetUIVar(UI_CHAT))
			    {
				v_TownLife += 10;

				if (v_TownLife >= 100)
					v_TownLife = 0;

				PrintConsoleString("ÿc4Changed Town Life To %d", v_TownLife);
				}
			}

			if (wParam == K_QuickLeft2 && ((lParam &0x4000) == 0)) //Left 2
			{
				if (!GetUIVar(UI_CHAT))
			    {
			     v_ExitLife += 10;

				if (v_ExitLife >= 100)
					v_ExitLife = 0;

				PrintConsoleString("ÿc4Changed Exit Life To %d", v_ExitLife);
				}
			}

			if (wParam == K_PickItToggle && ((lParam &0x4000) == 0)) //PickIt Toggle
			{
				if (!GetUIVar(UI_CHAT))
			    {
				v_PickIt = !v_PickIt; 

				if (v_PickIt)
					PrintConsoleString("ÿc4Divin's PickIt: Set To Enabled");
				else
					PrintConsoleString("ÿc4Divin's PickIt: Set To Disabled");
				}
			}

			if (wParam == K_ToggleGUI && ((lParam &0x4000) == 0)) //Toggle GUI
			{
				if (!GetUIVar(UI_CHAT))
			    {
				v_GUI = !v_GUI;

				if (v_GUI)
					PrintText(0,"ÿc9Fortification: ÿc0Normal GUI Mode");
				else
					PrintText(0,"ÿc9Fortification: ÿc0Stealth GUI Mode");
				}
			}

			if (wParam == K_DefineTownKey && ((lParam &0x4000) == 0)) //Town
			{
			  if (!GetUIVar(UI_CHAT))
			  {
		      if (GameReady())
		       {
		     	if (GetTickCount() - v_LastTP >= 500)
	            {
			    if (Portal())
		        {
				v_TP = true;
				v_LastTP = GetTickCount();
			    }
		        }
			  }
			  }
			}

		}
	}
	return (LONG)CallWindowProcA(oldWNDPROC, hWnd, uMsg, wParam, lParam);
}

INT GetItemLocation(UnitAny* pItem)
{
	if(!pItem || !pItem->pItemData)
		return -1;

	switch(pItem->pItemData->ItemLocation)
	{
	case STORAGE_INVENTORY:
		return STORAGE_INVENTORY;

	case STORAGE_CUBE:
		return STORAGE_CUBE;

	case STORAGE_STASH:
		return STORAGE_STASH;

	case STORAGE_NULL:
		switch(pItem->pItemData->NodePage)
		{
		case NODEPAGE_EQUIP:
			return STORAGE_EQUIP;

		case NODEPAGE_BELTSLOTS:
			return STORAGE_BELT;
		}
	}

	return STORAGE_NULL;
}

UnitAny* __fastcall FindItem(DWORD dwCode, INT nLoc)
{
	UnitAny* Item = pMe->pInventory->pFirstItem;

	if (!Item)
		return FALSE;

	do
	{
		if (Item->dwType == UNIT_TYPE_ITEM)
		{
			//if (GetItemLocation(Item) == STORAGE_BELT)
			//    PrintText(0,"Item Code: %d", Item->dwTxtFileNo); //Get Item Code

			if (Item->dwTxtFileNo == dwCode)
			{
				if (Item->dwTxtFileNo == 520 && GetUnitStat(Item, STAT_AMMOQUANTITY) == 0) //Fixed For PD2
					continue;

				if (GetItemLocation(Item) == nLoc)
					return Item;
			}
		}
	}	while ((Item = Item->pItemData->pNextInvItem));

	return FALSE;
}

DWORD UseItemIds(INT nLoc)
{
	if (pMe->pInventory->dwLeftItemUid)
		return pMe->pInventory->dwLeftItemUid;

	for (UnitAny* Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item->dwType == UNIT_TYPE_ITEM && Item->dwUnitId)
		{
			if (Item->pInventory)
			{
				if (GetItemLocation(Item) != nLoc)
					return Item->dwUnitId;
			}
		}
	}

	if (pMe->pInventory->pLastItem)
		return pMe->pInventory->pLastItem->dwUnitId;

	return NULL;
}

VOID UseItem(UnitAny* Unit)
{
	if (!Unit)
		return;

	INT Location = GetItemLocation(Unit);

	if (Location == STORAGE_INVENTORY || Location == STORAGE_BELT)
	{
		LPBYTE Packet = new BYTE[13];
		Packet[0] = (Location == STORAGE_INVENTORY) ? 0x20 : 0x26;
		*(LPDWORD)&Packet[1] = Unit->dwUnitId;
		*(LPDWORD)&Packet[5] = (Location == STORAGE_INVENTORY) ? pMe->pPath->xPos : NULL;
		*(LPDWORD)&Packet[9] = (Location == STORAGE_INVENTORY) ? pMe->pPath->yPos : NULL;
		D2NET_SendPacket(13, 1, Packet);
		delete [] Packet;
	}

	if (Location == STORAGE_STASH || Location == STORAGE_CUBE) //Support For PD2
	{
		LPBYTE Packet = new BYTE[13];
		Packet[0] = 0x20;
		*(LPDWORD)&Packet[1] = Unit->dwUnitId;
		*(LPDWORD)&Packet[5] = pMe->pPath->xPos;
		*(LPDWORD)&Packet[9] = pMe->pPath->yPos;
		D2NET_SendPacket(13, 1, Packet);
		delete [] Packet;
	}
}

BOOL Portal()
{
	/*
	520 = PD2 TP Tome
	531 = PD2 TP Scroll
	*/

	BOOL Book = FALSE;
	INT Quantity = 0;
	UnitAny* Item = NULL;

	if (pMe->pInventory->pCursorItem)
		return FALSE;

	Item = FindItem(520, STORAGE_STASH);

	if (!Item || GetUnitStat(Item, STAT_AMMOQUANTITY) == 0)
		Item = FindItem(520, STORAGE_INVENTORY);
	else
		Book = TRUE;

	if (!Item || GetUnitStat(Item, STAT_AMMOQUANTITY) == 0)
		Item = FindItem(520, STORAGE_CUBE);
	else
		Book = TRUE;

	if (!Item || GetUnitStat(Item, STAT_AMMOQUANTITY) == 0)
		Item = FindItem(531, STORAGE_BELT);
	else
		Book = TRUE;

	if (!Item)
		Item = FindItem(531, STORAGE_INVENTORY);

	if (!Item)
		Item = FindItem(531, STORAGE_STASH);

	if (!Item)
		Item = FindItem(531, STORAGE_CUBE);

	if (!Item)
	{
		return FALSE;
	}

	if (Item)
		UseItem(Item);

	if (Book)
	{
		Quantity = GetUnitStat(Item, STAT_AMMOQUANTITY);
	}

	return TRUE;
}

INT D2IsPotion(LPSTR lpszItemCode)
{
	if (lpszItemCode == NULL)
		return 0;

	if (!_stricmp(lpszItemCode, "rvl")
		|| !_stricmp(lpszItemCode, "rvs"))
		return 1;

	if (!_stricmp(lpszItemCode, "hp1")
		|| !_stricmp(lpszItemCode, "hp2")
		|| !_stricmp(lpszItemCode, "hp3")
		|| !_stricmp(lpszItemCode, "hp4")
		|| !_stricmp(lpszItemCode, "hp5"))
		return 2;

	if (!_stricmp(lpszItemCode, "mp1")
		|| !_stricmp(lpszItemCode, "mp2")
		|| !_stricmp(lpszItemCode, "mp3")
		|| !_stricmp(lpszItemCode, "mp4")
		|| !_stricmp(lpszItemCode, "mp5"))
		return 3;

	if (!_stricmp(lpszItemCode, "yps")
		|| !_stricmp(lpszItemCode, "vps")
		|| !_stricmp(lpszItemCode, "wms"))
		return 4;

	if (!_stricmp(lpszItemCode, "tsc"))
		return 5;

	return 0;
}

BOOL GetItemCode(UnitAny* pItem, LPSTR szBuffer, DWORD dwMax)
{
	if(!pItem)
		return FALSE;

	ItemTxt* pTxt = D2COMMON_GetItemText(pItem->dwTxtFileNo);
	::memcpy(szBuffer, pTxt->szCode, min(3, dwMax));
	return (int)strlen(szBuffer);
}

INT GetTotalBeltTPs()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (UnitAny* Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_BELT)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 5)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalCubeTPs()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (UnitAny* Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_CUBE)
		{
			GetItemCode(Item, Code, 3);

			if (!_stricmp(Code, "tsc"))
				TotalItems++;

			if (!_stricmp(Code, "tbk"))
				TotalItems = TotalItems + (INT)GetUnitStat(Item, STAT_AMMOQUANTITY);
		}
	}

	return TotalItems;
}

INT GetTotalInvTPs()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (UnitAny* Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_INVENTORY)
		{
			GetItemCode(Item, Code, 3);

			if (!_stricmp(Code, "tsc"))
				TotalItems++;

			if (!_stricmp(Code, "tbk"))
				TotalItems = TotalItems + (INT)GetUnitStat(Item, STAT_AMMOQUANTITY);
		}
	}

	return TotalItems;
}

INT GetTotalStashTPs()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (UnitAny* Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_STASH)
		{
			GetItemCode(Item, Code, 3);

			if (!_stricmp(Code, "tsc"))
				TotalItems++;

			if (!_stricmp(Code, "tbk"))
				TotalItems = TotalItems + (INT)GetUnitStat(Item, STAT_AMMOQUANTITY);
		}
	}

	return TotalItems;
}

VOID ScreenToAutoMap(LPPOINT Point)
{
	POINT Mouse = {(*p_D2CLIENT_MouseX), (*p_D2CLIENT_MouseY)};
	POINT MouseOffset = {(*p_D2CLIENT_MouseOffsetX), (*p_D2CLIENT_MouseOffsetY)};

	Mouse.x += MouseOffset.x;
	Mouse.y += MouseOffset.y;

	D2COMMON_AbsScreenToMap(&Mouse.x, &Mouse.y);

	Point->x = Mouse.x;
	Point->y = Mouse.y;
}

WORD GetCurrentSkill(BOOL Left)
{
	if (!GameReady())
		return FALSE;

	if (Left)
		return pMe->pInfo->pLeftSkill->pSkillInfo->wSkillId;
	else
		return pMe->pInfo->pRightSkill->pSkillInfo->wSkillId;
}

LPROOM1 GetRoom(UINT X, UINT Y)
{
	for (UINT i = 0; i < pMe->pPath->pRoom1->dwRoomsNear; i++)
	{
		LPROOM1 Room = pMe->pPath->pRoom1->pRoomsNear[i];

		if (Room->dwXStart <= X && Room->dwYStart <= Y && Room->dwXStart + Room->dwXSize >= X && Room->dwYStart + Room->dwYSize >= Y)
			return Room;
	}

	return NULL;
}

BOOL MiddleMouseButton()
{
	if (GetTickCount() - v_LastFC >= 300) /*Fix Double Teleport*/
	{
	if (!GameReady())
		return FALSE;

	if (InTown(pMe))
		return FALSE;

	if (GetSkill(D2S_TELEPORT))
		SetSkill(D2S_TELEPORT, FALSE);

	if (pMe->dwMode == PLAYER_MODE_CAST || pMe->dwMode == PLAYER_MODE_ATTACK1 || pMe->dwMode == PLAYER_MODE_ATTACK2 ||
		pMe->dwMode == PLAYER_MODE_KICK || pMe->dwMode == PLAYER_MODE_THROW)
		return FALSE;

		if (GetCurrentSkill(FALSE) == D2S_TELEPORT)
		{
			POINT Origin = {(pMe->pPath->xPos), (pMe->pPath->yPos)};
			POINT Mouse = {(MouseX), (MouseY)};

			ScreenToAutoMap(&Mouse);

			INT Angle = CalculateAngle(Origin, Mouse);
			INT Radius = 100;
			POINT Cast;

			while (TRUE)
			{
				if (Radius <= 0)
					break;

				Cast = CalculatePointOnTrack(Origin, Radius--, Angle);

				if (GetRoom(Cast.x, Cast.y))
				{
					if (!D2COMMON_CheckCollision(pMe->pPath->pRoom1, Cast.x, Cast.y, 2))
						if (::abs(pMe->pPath->xPos - Cast.x) <= 50)
							if (::abs(pMe->pPath->yPos - Cast.y) <= 50)
								break;
				}
			}

			AttackStruct Attack;
			Attack.dwAttackType = 0x66;

			Attack.dwTargetX = Cast.x;
			Attack.dwTargetY = Cast.y;

			Attack.lpPlayerUnit = pMe;
			Attack.lpTargetUnit = NULL;

			D2CLIENT_Attack(&Attack, FALSE);

			v_LastFC = GetTickCount();

			return TRUE;
		}
	}
	return FALSE;
}

/*
PD2 Potion Items Codes

Small Juv: 517
Big Juv: 518

Super Healing Potion: 593
Greater Healing Potion: 592
Healing Potion: 591
Light Healing Potion: 590
Minor Healing Potion: 589

Super Mana Potion: 598
Greater Mana Potin: 597
Mana Potion: 596
Light Mana Potion: 595
Minor Mana Potion: 594
*/

BOOL Mana()
{
	LPUNITANY Item = NULL;
	DWORD ItemCodes[5] = {598, 597, 596, 595, 594}; //Fixed For PD2

	if (!GameReady() || InTown(pMe) || pMe->pInventory->pCursorItem)
		return FALSE;

	for (INT i = 0; i < ArraySize(ItemCodes); i++)
	{
		Item = FindItem(ItemCodes[i], STORAGE_STASH);

		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_BELT);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_INVENTORY);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_CUBE);
		if (!Item) continue;

		UseItem(Item);
		return TRUE;
	}

	return FALSE;
}

BOOL AutoMana()
{
	if (!GameReady())
		return FALSE;

	DOUBLE ManaPercent = CalcPercent((GetUnitStat(pMe, STAT_MANA) >> 8), (GetUnitStat(pMe, STAT_MAXMANA) >> 8));

	if (GetTickCount() - v_LastMana >= 500)
	{
		if (!GetUnitState(pMe, AFFECT_MANAPOT))
		{
		if (ManaPercent <= v_AutoManaPercent)
		{
		Mana();
		}
		v_LastMana = GetTickCount();
		}
	}

	return FALSE;
}

BOOL Rejuvenation()
{
	LPUNITANY Item = NULL;
	DWORD ItemCodes[2] = {518, 517}; //Fixed For PD2

	if (!GameReady() || pMe->pInventory->pCursorItem)
		return FALSE;
	
	for (INT i = 0; i < ArraySize(ItemCodes); i++)
	{
		Item = FindItem(ItemCodes[i], STORAGE_STASH);

		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_BELT);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_INVENTORY);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_CUBE);
		if (!Item) continue;

		UseItem(Item);
		return TRUE;
	}

	return FALSE;
}

BOOL AutoJuv()
{
	if (!GameReady())
		return FALSE;

	DOUBLE LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));

	if (GetTickCount() - v_LastJuv >= 500)
	{
		if (LifePercent <= v_AutoRejuvPercent)
		{
		Rejuvenation();
		
		v_LastJuv = GetTickCount();

		if (v_Bot && !InTown(pMe)) //Bot Drank A Juv
		{
			v_DelayedChicken = true;
		}
		}
	}

	return FALSE;
}

BOOL Health()
{
	LPUNITANY Item = NULL;
	DWORD ItemCodes[5] = {593, 592, 591, 590, 589}; //Fixed For PD2

	if (!GameReady() || InTown(pMe) || pMe->pInventory->pCursorItem)
		return FALSE;

	for (INT i = 0; i < ArraySize(ItemCodes); i++)
	{
		Item = FindItem(ItemCodes[i], STORAGE_STASH);

		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_BELT);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_INVENTORY);
		if (!Item) Item = FindItem(ItemCodes[i], STORAGE_CUBE);
		if (!Item) continue;

		UseItem(Item);
		return TRUE;
	}

	return FALSE;
}

BOOL AutoLife()
{
	if (!GameReady())
		return FALSE;

	DOUBLE LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));

	if (GetTickCount() - v_LastLife >= 500)
	{
		if (!GetUnitState(pMe, AFFECT_HEALTHPOT))
		{
		if (LifePercent <= v_AutoLifePercent)
		{
		Health();
		
		v_LastLife = GetTickCount();
		}
		}
	}

	return FALSE;
}

BOOL UseSkillOnUnit(DWORD UnitID, WORD Skill, BOOL Left, BOOL Shift, BOOL Animation)
{
	if (!GameReady())
		return FALSE;

	LPBYTE Packet = new BYTE[9];
	Packet[0] = Shift ? (Left ? 0x0A : 0x11) : (Left ? 0x06 : 0x0D);
	*(LPDWORD)&Packet[1] = UNIT_TYPE_PLAYER;
	*(LPDWORD)&Packet[5] = UnitID;
	D2NET_SendPacket(9, 1, Packet);
	delete [] Packet;

	if (Animation)
	{
		LPBYTE Packet = new BYTE[16];
		Packet[0] = 0x4C;
		*(LPDWORD)&Packet[1] = pMe->dwType;
		*(LPDWORD)&Packet[2] = pMe->dwUnitId;
		*(LPWORD)&Packet[6] = Skill;
		*(LPDWORD)&Packet[9] = UNIT_TYPE_PLAYER;
		*(LPDWORD)&Packet[10] = UnitID;
		D2NET_ReceivePacket(Packet, 16);
		delete [] Packet;
	}

	return TRUE;
}

VOID SinglePlayerChicken()
{
	if (InTown(pMe))
		return;

	if (v_TP)
		return;

	if (v_TownLife == 0)
		return;

	DOUBLE LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));

	if (LifePercent <= v_TownLife)
	{
	if (GameReady())
		{
			if (GetTickCount() - v_LastTP >= 500)
	        {
			if (Portal())
		    {
				v_TP = true;
				v_LastTP = GetTickCount();
			}
			}
	    }
	}
}

VOID Exit()
{
	if (InTown(pMe))
		return;

    if (v_ExitLife == 0)
		return; 

	if (GameReady())
	{
		DOUBLE LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));

		if (LifePercent <= v_ExitLife)
		{
			D2CLIENT_ExitGame();
		}
	}
}

INT GetTotalBeltRejuvenation()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_BELT)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 1)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalCubeRejuvenation()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_CUBE)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 1)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalInvRejuvenation()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_INVENTORY)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 1)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalStashRejuvenation()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_STASH)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 1)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalBeltMana()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_BELT)
		{
			GetItemCode(Item, Code, 3);
			
			if (D2IsPotion(Code) == 3)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalCubeMana()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_CUBE)
		{
			GetItemCode(Item, Code, 3);
			
			if (D2IsPotion(Code) == 3)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalInvMana()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_INVENTORY)
		{
			GetItemCode(Item, Code, 3);
			
			if (D2IsPotion(Code) == 3)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalStashMana()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_STASH)
		{
			GetItemCode(Item, Code, 3);
			
			if (D2IsPotion(Code) == 3)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalBeltHealth()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_BELT)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 2)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalCubeHealth()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_CUBE)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 2)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalInvHealth()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_INVENTORY)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 2)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

INT GetTotalStashHealth()
{
	INT TotalItems = 0;
	CHAR Code[4] = {0};

	for (LPUNITANY Item = pMe->pInventory->pFirstItem; Item; Item = Item->pItemData->pNextInvItem)
	{
		if (Item && GetItemLocation(Item) == STORAGE_STASH)
		{
			GetItemCode(Item, Code, 3);

			if (D2IsPotion(Code) == 2)
			{
				TotalItems++;
			}
		}
	}

	return TotalItems;
}

DWORD GetUnitDist(LPUNITANY pUnit1, LPUNITANY pUnit2)
{
	DWORD dwDist[4] = {0};

	switch(pUnit1->dwType)
	{
	case UNIT_TYPE_PLAYER:
	case UNIT_TYPE_MISSILE:
	case UNIT_TYPE_NPC:
		dwDist[0] = pUnit1->pPath->xPos;
		dwDist[1] = pUnit1->pPath->yPos;
		break;

	case UNIT_TYPE_OBJECT:
		dwDist[0] = pUnit1->pObjectPath->dwPosX;
		dwDist[1] = pUnit1->pObjectPath->dwPosY;
		break;
	}

	switch(pUnit2->dwType)
	{
	case UNIT_TYPE_PLAYER:
	case UNIT_TYPE_MISSILE:
	case UNIT_TYPE_NPC:
		dwDist[2] = pUnit2->pPath->xPos;
		dwDist[3] = pUnit2->pPath->yPos;
		break;

	case UNIT_TYPE_OBJECT:
		dwDist[2] = pUnit2->pObjectPath->dwPosX;
		dwDist[3] = pUnit2->pObjectPath->dwPosY;
		break;
	}

	for(int x = 0; x < 4; x++)
		if(!dwDist[x])
			return INFINITE;

	return (DWORD)CalculateDistance(dwDist[0], dwDist[1], dwDist[2], dwDist[3]);
}

LPUNITANY FindNearestUnit()
{
	LPUNITANY Target = NULL;
	INT Distance = 40;

	for (LPROOM1 Room1 = pMe->pAct->pRoom1; Room1; Room1 = Room1->pRoomNext)
	{
		for (LPUNITANY Unit = Room1->pUnitFirst; Unit; Unit = Unit->pListNext)
		{
			if (Unit && Unit->dwType == UNIT_TYPE_NPC)
			{
				if (!IsValidMonster(Unit))
					continue;

				if ((INT)GetUnitDist(pMe, Unit) > Distance)
					continue;

					Target = Unit;
					Distance = (INT)GetUnitDist(pMe, Unit);
			}
		}
	}

	return Target;
}

BOOL UsingSkill()
{
	if (pMe->dwMode == PLAYER_MODE_CAST || pMe->dwMode == PLAYER_MODE_ATTACK1 || pMe->dwMode == PLAYER_MODE_ATTACK2 ||
		pMe->dwMode == PLAYER_MODE_KICK || pMe->dwMode == PLAYER_MODE_THROW)
		return TRUE;

	return FALSE;
}

VOID AttackRightMonster()
{
	if (!GameReady())
		return;

	if (UsingSkill())
		return;

	if (InTown(pMe))
		return;

    LPUNITANY Monster = FindNearestUnit();

	WORD Skill = GetCurrentSkill(FALSE);

	if (Monster)
	{
			AttackStruct Attack;
			Attack.dwAttackType = 0x66;

			Attack.dwTargetX = Monster->pPath->xPos;
			Attack.dwTargetY = Monster->pPath->yPos;

			Attack.lpPlayerUnit = pMe;
			Attack.lpTargetUnit = Monster;

			D2CLIENT_Attack(&Attack, FALSE);
	}
}

VOID AttackLeftMonster()
{
	if (!GameReady())
		return;

	if (UsingSkill())
		return;

	if (InTown(pMe))
		return;

    LPUNITANY Monster = FindNearestUnit();

	WORD Skill = GetCurrentSkill(TRUE);

	if (Monster)
	{
		AttackStruct Attack;
		Attack.dwAttackType = 0xE5;

		Attack.dwTargetX = Monster->pPath->xPos;
        Attack.dwTargetY = Monster->pPath->yPos;

		Attack.lpPlayerUnit = pMe;			
		Attack.lpTargetUnit = Monster;

		D2CLIENT_Attack(&Attack, FALSE);
	}
}

/*Very Basic Precast Script Made In C++ - Supports All Chars*/

BOOL Switch, SwitchBIS = false;
BOOL CheckMainA, CheckMainB = false;
DWORD TheDelay = NULL;

BOOL AutoPrecast()
{
	if (!Switch)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Switching Weapon");
	keybd_event(87, 0, 0, 0);
  	keybd_event(87, 0, KEYEVENTF_KEYUP, 0);
	TheDelay = GetTickCount();
	Switch = true;
	}

	if (!CheckMainA)
	{
	if (GetTickCount() - TheDelay >= 500)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Casting Right Skill 1");

	WORD Skill = GetCurrentSkill(FALSE);

	UseSkillOnUnit(pMe->dwUnitId,Skill,FALSE,TRUE,TRUE);
	TheDelay = NULL; 
	TheDelay = GetTickCount();
	CheckMainA = true;
	}
	}

	if (!CheckMainB)
	{
	if (GetTickCount() - TheDelay >= 500)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Casting Right Skill 2");

	WORD Skill = GetCurrentSkill(FALSE);

	UseSkillOnUnit(pMe->dwUnitId,Skill,FALSE,TRUE,TRUE);
	CheckMainB = true;
	TheDelay = NULL; 
	TheDelay = GetTickCount();
	}
	}

	if (!SwitchBIS)
	{
	if (GetTickCount() - TheDelay >= 500)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Switching Weapon Back");
	keybd_event(87, 0, 0, 0);
  	keybd_event(87, 0, KEYEVENTF_KEYUP, 0);
	
	TheDelay = NULL;
	TheDelay = GetTickCount();
	SwitchBIS = true;
	}
	}

	if (CheckMainA && CheckMainB && Switch && SwitchBIS)
	{
	v_Precast = false;

	Switch = false;
	SwitchBIS = false;
	CheckMainA = false;
	CheckMainB = false;
	TheDelay = NULL;
	}

	return FALSE;
}

void ResetPrecast()
{
	v_Precast = false;

	Switch = false;
	SwitchBIS = false;
	CheckMainA = false;
	CheckMainB = false;
	TheDelay = NULL;
}