#include "D2Ptrs.h"
#include "AutoTele.h"
#include "constants.h"
#include "injection.h"

wchar_t* AnsiToUnicode(const char* str)
{
        wchar_t* buf = NULL;
        int len = MultiByteToWideChar(CP_ACP, 0, str, -1, buf, 0);
        buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, str, -1, buf, len);
        return buf;
}

void myDrawText(const char* szwText, int x, int y, int color, int font) 
{
	wchar_t* text = AnsiToUnicode(szwText);

	DWORD dwOld = D2WIN_SetFont(font);
	D2WIN_DrawText(text, x, y, color, 0);
	D2WIN_SetFont(dwOld);

	delete[] text;
}

VOID ScreenToAutomap(POINT *pPos, INT nX, INT nY) //works
{
	pPos->x = ((nX - nY) / 2 / (*p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).x + 8;
	pPos->y = ((nX + nY) / 4 / (*p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).y - 8;

	if(D2CLIENT_GetAutomapSize())
	{
		--pPos->x;
		pPos->y += 5;
	}
}

void PrintConsoleString(char* Message, ...)
{
	CHAR szBuffer[0x400] = "";
	va_list Args;

	va_start(Args, Message);
	vsprintf(szBuffer, Message, Args);
	va_end(Args);

	sprintf(v_ConsoleMessage, szBuffer);

	v_Register = true;
	v_Message = true;
}

void eDPKConsole()
{
	if (v_Message && v_Register)
	{
		v_ConsoleDelayA = 0;
		v_ConsoleDelayA = GetTickCount();
		v_Register = false;
	}

	if (GetTickCount() - v_ConsoleDelayA >= v_ConsoleDelayB)
		v_Message = false;

	if (v_Message)
	{
		ColorBox(249, 480, 575, 20, 216, 0, 2); //Message Box
		ColorBox(249, 480, 575, 20, 216, 0, 2); //Message Box
		SpecialTextHook(255, 496, 0, 4, "%s", v_ConsoleMessage); //Console Message
	}
}

void DrawCross(int x, int y, DWORD Color)
{
	char szLines[][2] = {0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2};
	for(int i = 0; i < 12; i++)
		D2GFX_DrawLine(x + szLines[i][0], y + szLines[i][1], x + szLines[i+1][0], y + szLines[i+1][1], Color, -1);
}

void ColorBox(INT X1, INT Y1, INT X2, INT Y2, INT LineColor, DWORD Color, DWORD Transparency)
{
	POINT Start = { X1, Y1 };
	POINT End = { X2, Y2 };

    D2GFX_DrawRectangle(X1, Y1, X2 + X1, Y1 + Y2, Color, Transparency);

	D2GFX_DrawLine(X1, Y1, X2 + X1, Y1, LineColor, -1);
	D2GFX_DrawLine(X1, Y1 + Y2, X1, Y1, LineColor, -1);
	D2GFX_DrawLine(X1 + X2, Y1 + Y2, X1, Y1 + Y2, LineColor, -1);
	D2GFX_DrawLine(X1 + X2, Y1, X1 + X2, Y1 + Y2, LineColor, -1);
}

VOID DrawOut(INT X, INT Y, INT Color, INT Size, LPSTR Format, ...)
{
	WCHAR wTemp[0x400] = L"";
	CHAR szTemp[0x400] = "";
	DWORD dwOldSize;
	va_list Args;

	va_start(Args, Format);
	vsprintf_s(szTemp, Format, Args);
	va_end(Args);

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp, (INT)strlen(szTemp), wTemp, (INT)strlen(szTemp));

	dwOldSize = D2WIN_SetTextSize(Size);
	D2WIN_DrawText(wTemp, X, Y, Color, -1);
	D2WIN_SetTextSize(dwOldSize);
}

void SpecialTextHook(INT X, INT Y, DWORD Color, INT Font, LPSTR Text, ...)
{
	POINT nPos = { X, Y };
	DWORD dwOldSize;
	CHAR szBuffer[800] = "";

	va_list Args;
	va_start(Args, Text);
	vsprintf_s(szBuffer, Text, Args);
	va_end(Args);
	WCHAR wBuffer[0x130];

	MultiByteToWideChar(0, 1, szBuffer, 100, wBuffer, 100);
	dwOldSize = D2WIN_SetTextSize(Font);
	D2WIN_DrawText(wBuffer, nPos.x, nPos.y, Color, -1);
	D2WIN_SetTextSize(dwOldSize);
}

void TextHook(INT xPos, INT yPos, DWORD dwColor, BOOL Automap, INT dwFont, INT dwCenter, LPSTR Text,...)
{
	POINT nPos = {xPos, yPos};
	DWORD dwOldSize, wWidth, dwFileNo;

	CHAR szBuffer[800] = "";
	va_list Args;
	va_start(Args, Text);
	vsprintf_s(szBuffer, Text, Args);
	va_end(Args);

	wchar_t wBuffer[0x130];
	MultiByteToWideChar(0, 1, szBuffer, 100, wBuffer, 100);

	dwOldSize = D2WIN_SetTextSize(dwFont);
	if (dwCenter != -1)
	{
		D2WIN_GetTextWidthFileNo(wBuffer, &wWidth, &dwFileNo);
		nPos.x -= (wWidth >> dwCenter);
	}
	
	D2WIN_DrawText (wBuffer,nPos.x, nPos.y,dwColor,-1);
	D2WIN_SetTextSize(dwOldSize);
} 

GameStructInfo* GetGameInfo()
{
	return D2CLIENT_GetGameInfo();
}

Level* GetUnitLevel(UnitAny* pUnit)
{
	if(pUnit)
		if(pUnit->pPath)
			if(pUnit->pPath->pRoom1)
				if(pUnit->pPath->pRoom1->pRoom2)
					return pUnit->pPath->pRoom1->pRoom2->pLevel;

	return FALSE;
}

BOOL InTown(UnitAny* Unit)
{
	Level* CurrentLevel = GetUnitLevel(Unit);

	if (!CurrentLevel)
		return TRUE;

	return IsTownLevel(CurrentLevel->dwLevelNo) || CurrentLevel->dwLevelNo == 0;
}

BOOL IsBotSafe()
{
	Level* CurrentLevel = GetUnitLevel(pMe);

	if (CurrentLevel->dwLevelNo == MAP_A5_HARROGATH)
		return TRUE;

	return FALSE;
}

BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin)
{
	if (dwVal == 0 || dwMaxVal == 0)
		return NULL;

	BYTE iRes = (BYTE)((double)dwVal / (double)dwMaxVal * 100.0);

	if (iRes > 100)
		iRes = 100;

	return max(iRes, iMin);
}

POINT PickFarcastLocation(POINT Target)
{
	POINT Origin = {(pMe->pPath->xPos), (pMe->pPath->yPos)};
	ScreenToAutoMap(&Target);

	INT Angle = CalculateAngle(Origin, Target);
	INT Radius = 100;
	POINT Cast = {NULL};

	while (TRUE)
	{
		Cast = CalculatePointOnTrack(Origin, Radius--, Angle);

		if (!D2COMMON_CheckCollision(pMe->pPath->pRoom1, Cast.x, Cast.y, 2))
			if (::abs(pMe->pPath->xPos - Cast.x) <= 50 && ::abs(pMe->pPath->yPos - Cast.y) <= 50)
				break;
	}

	return Cast;
}

BOOL DrawFCVector()
{
	POINT MyMouse = {MouseX, MouseY};
	POINT Position = {0,0};
	POINT Player = {0,0};

	ScreenToAutomap(&Position, PickFarcastLocation(MyMouse).x * 32, PickFarcastLocation(MyMouse).y * 32);
	ScreenToAutomap(&Player, pMe->pPath->xPos * 32, pMe->pPath->yPos * 32);

	D2GFX_DrawLine(Player.x, Player.y, Position.x, Position.y, 98, -1);
	DrawCross(Position.x, Position.y, 32);

	return FALSE;
}

char* UnicodeToAnsi(const wchar_t* str)
{
	char* buf = NULL;
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, buf, 0, "?", NULL);
	buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, str, -1, buf, len, "?", NULL);
	return buf;
}

DWORD __declspec(naked) __fastcall GetUnitNameSTUB(DWORD Unit)
{
	__asm
	{
		MOV EAX, ECX;
		JMP D2CLIENT_GetUnitName_I;
	}
}

bool IsValidMonster(UnitAny *pUnit)
{
	//Have we even been given a unit?
	if (!pUnit)
		return false;

	//Check to see if unit is dead.
	if ((pUnit->dwMode == 0) || (pUnit->dwMode == 12))
		return false;

	if ((pUnit->dwTxtFileNo == 608) && (pUnit->dwMode == 8))
		return false;
	
	if ((pUnit->dwTxtFileNo == 68) && (pUnit->dwMode == 14))// Ignore burrowing maggots
		return false;

	//Hide the water creepers
	if ((pUnit->dwTxtFileNo == 258 || (pUnit->dwTxtFileNo == 261)) && (pUnit->dwMode == 14))
		return false;

	DWORD badMonIds[] = {227, 283, 326, 327, 328, 329, 330, 410, 411, 412, 413, 414, 415, 416, 366, 406,
						 351, 352, 353, 266, 408, 516, 517, 518, 519, 522, 523, 543, 543, 545, 786, 787, 788};

	for (DWORD n = 0; n < 33; n++)
	{
		if (pUnit->dwTxtFileNo == badMonIds[n])
			return false;
	}

	if (D2COMMON_GetUnitStat(pUnit, 172, 0) == 2) 
		return false;

	wchar_t* name = GetUnitName(pUnit);
	char* tmp = UnicodeToAnsi(name);

	if ((strcmp(tmp,"an evil force") == 0) || (strcmp(tmp, "dummy") == 0) || (strcmp(tmp, "Maggot") == 0)) {
		delete[] tmp;
		return false;
	}
	delete[] tmp;

	return true;
}

VOID __declspec(naked) FullLightRadiusSTUB()
{
	__asm
	{
		CMP [v_FullLightRadius], 0;
		JE OldCode;
		
		MOV EAX, 0xFF;
		MOV BYTE PTR [ESP + 0x4], AL;
		MOV BYTE PTR [ESP + 0x5], AL;
		MOV BYTE PTR [ESP + 0x6], AL;

		ADD DWORD PTR [ESP], 0x82;
		RET;

OldCode:
		MOV BYTE PTR [ESP + 0x5], 0;
		RET;
	}
}

DWORD __declspec(naked) __fastcall GetUIVarSTUB(DWORD UI)
{
	__asm
	{
		MOV EAX, ECX;
		JMP D2CLIENT_GetUiVar_I;
	}
}

DWORD Timer = 0;

VOID GameDrawTwo()
{   
	if (v_Bot && GameReady())
		Bot();

	if (v_Precast && GameReady())
		AutoPrecast();

	if (v_Bot && v_BotCounter != NULL)
	{
	Timer = GetTickCount() - v_BotCounter;
	}
	else
	Timer = 0;

	if (v_Bot)
	{
		if (Timer >= 180000) //Above 3 Minutes, Exit Game
			D2CLIENT_ExitGame();
	}

	//TextHook(500,70,4,0,4,0,"%d %d %d", pMe->pPath->xPos, pMe->pPath->yPos, Timer);

	if (GetAsyncKeyState(18))
	{
		if (GetTickCount() - v_LastPrecast >= 250)
		{
			AttackLeftMonster();

			v_LastPrecast = GetTickCount();
		}
	}
	else if (GetAsyncKeyState(17))
	{
		if (GetTickCount() - v_LastPrecast >= 250)
		{
		    AttackRightMonster();

		    v_LastPrecast = GetTickCount();
		}
	}

	if (!v_Bot)
	     PickIt();
	else
		 BotPickIt();

	PickItBox();

	SinglePlayerChicken();
    Exit();

	if (v_GUI)
	{
	SpecialTextHook(765,547,2,4,"Fortification Unleashed");

	LONG LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));
	LONG ManaPercent = CalcPercent((GetUnitStat(pMe, STAT_MANA) >> 8), (GetUnitStat(pMe, STAT_MAXMANA) >> 8));

	TextHook(66, *p_D2CLIENT_ScreenSizeY - 50,0,0,5,1,"ÿc0%d%%", LifePercent);
	TextHook(*p_D2CLIENT_ScreenSizeX - 72, *p_D2CLIENT_ScreenSizeY - 50,0,0,5,1, "ÿc0%d%%", ManaPercent);
	}

	if (v_GUI)
	{
	if (!GetUIVar(UI_CHAT) && !GetUIVar(UI_NPCSHOP) && !GetUIVar(UI_SKILL) && !GetUIVar(UI_INVENTORY) && !GetUIVar(UI_CHARACTER)
		&& !GetUIVar(UI_STASH) && !GetUIVar(UI_TRADE) && !GetUIVar(UI_MERC) && !GetUIVar(UI_CUBE) && !GetUIVar(UI_MSGS))
	{
	eDPKConsole();
	}
	}

	if (v_GUI)
	{
	if (!GetUIVar(UI_CHAT) && !GetUIVar(UI_NPCSHOP) && !GetUIVar(UI_SKILL) && !GetUIVar(UI_INVENTORY) && !GetUIVar(UI_CHARACTER)
		&& !GetUIVar(UI_STASH) && !GetUIVar(UI_TRADE) && !GetUIVar(UI_MERC) && !GetUIVar(UI_CUBE) && !GetUIVar(UI_MSGS))
	{
	ColorBox(249, 500, 575, 20, 216, 0, 2); //Console Box
	TextHook(530, 516, 0, 0, 4, 1, "ÿc5[ÿc1-ÿc4Attack: %d ÿc1-ÿc4 Block: %d ÿc1-ÿc4 Cast: %d ÿc1-ÿc4 Recovery: %dÿc1-ÿc5]", GetUnitStat(pMe, STAT_IAS), GetUnitStat(pMe, STAT_FASTERBLOCK), GetUnitStat(pMe, STAT_FASTERCAST), GetUnitStat(pMe, STAT_FASTERHITRECOVERY)); //BreakPoint Percent
	}

	if (!GetUIVar(UI_MSGS) && !GetUIVar(UI_CHARACTER) && !GetUIVar(UI_MERC))
	{
	SpecialTextHook(77,356,8,4,"ÿc5[ÿc1-ÿc4Configurationÿc1-ÿc5]");
	SpecialTextHook(77,372,8,4,"ÿc5[ÿc1-ÿc4Auto-TP: %dÿc1-ÿc5]", v_TownLife);
	SpecialTextHook(77,388,8,4,"ÿc5[ÿc1-ÿc4Quick-Exit: %dÿc1-ÿc5]", v_ExitLife);

	INT TP = GetTotalBeltTPs() + GetTotalCubeTPs() + GetTotalInvTPs() + GetTotalStashTPs();

	SpecialTextHook(77,404,8,4,"ÿc5[ÿc1-ÿc4TP-Amount: %iÿc1-ÿc5]", TP);
	}
	}

    OnLoop();

	AutoMana();
	AutoJuv();
	AutoLife();

	if (GetAsyncKeyState(4))
	{
		MiddleMouseButton();
	}

	if (*p_D2CLIENT_AutomapOn)
	{

	if (v_Reveal)
		v_Reveal->RevealAutomap();

	DrawFCVector();

	OnAutomapDraw();

	for (Room1* room1 = pMe->pAct->pRoom1; room1; room1 = room1->pRoomNext) {
		for (UnitAny* unit = room1->pUnitFirst; unit; unit = unit->pListNext) {

			POINT automapLoc;
			ScreenToAutomap(&automapLoc, unit->pPath->xPos * 32, unit->pPath->yPos * 32);

			// Draw monster on automap
			if (unit->dwType == 1 && IsValidMonster(unit))
			{
				int color = 0x5B;
				if (unit->pMonsterData->fBoss)
					color = 0x84;
				if (unit->pMonsterData->fChamp)
					color = 0x91;
				if (unit->pMonsterData->fMinion)
					color = 0x60;

				int Check1 = D2COMMON_GetUnitStat(unit, 36,0);
				if (Check1 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc7i");
					}
				int Check2 = D2COMMON_GetUnitStat(unit, 37,0);
				if (Check2 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc8i");
					}
	            int Check3 = D2COMMON_GetUnitStat(unit, 39,0);
				if (Check3 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc1i");
					}
	            int Check4 = D2COMMON_GetUnitStat(unit, 41,0);
				if (Check4 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc9i");
					}

				int Check5 = D2COMMON_GetUnitStat(unit, 43,0);
				if (Check5 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc3i");
					}
				int Check6 = D2COMMON_GetUnitStat(unit, 45,0);
				if (Check6 >= 100)
					{
						TextHook(automapLoc.x, automapLoc.y - 8, 0, 1, 6, 1, "ÿc2i");
					}

				DrawCross(automapLoc.x, automapLoc.y, color);
			}
		}
	}
	}
}

VOID __declspec(naked) DrawManaOrbSTUB()
{
	__asm
	{
		CALL D2CLIENT_DrawManaOrb;
		CALL GameDrawTwo;
		RETN;
	}
}

DWORD __fastcall GamePacketReceived(BYTE* pPacket, DWORD dwSize)
{
   if (pPacket[0] == 0x51)
	 {
		if (pPacket[6] == 0x3B)
		{
		if (pPacket[12] < 2)
	     	pPacket[12] = 2;
		}
	 }

	if (pPacket[0] == 0x82)
	{
		if (v_TP && !InTown(pMe))
		{
			if (*(LPDWORD)&pPacket[1] == pMe->dwUnitId)
			{
				 Interact(*(LPDWORD)&pPacket[21], UNIT_TYPE_OBJECT);

			     v_TP = FALSE;
			}
		}
		return TRUE;
	}

	if (pPacket[0] == 0xA7)
	{
			if (pPacket[6] == AFFECT_JUST_PORTALED)
				return FALSE;

		return TRUE;
	}

	if (pPacket[0] == 0x5B)
	{
	int PlayerId = pPacket[3];
	const char* PlayerName = (LPSTR)&pPacket[8];

	if (strcmp(PlayerName, pMe->pPlayerData->szName) == 0) /*You've Entered The Game*/
	{
		if (v_Bot)
			ResetBot();

		v_Reveal = new Reveal;

		PrintText(8, "Thanks For Using Fortification! Got Any Questions? Contact Divin On Discord: blakadiv");

		PrintConsoleString("ÿc4Welcome To Fortification Unleashed Created By Divin For Project Diablo 2");
	}
	return true;
	}

	if (pPacket[0] == 0x2C)
	{
		if (pPacket[1] == 0x00)
		{
			if (dwSize == 8 && pPacket[6] == 0x17)
			{
				PrintConsoleString("ÿc4Divin's PickIt: Your Inventory Is Full, PickIt Disabled. (Use Toggle Key To Enable It)");

				v_PickIt = false;
			}
		}
	}

	return true;
}

void __declspec(naked) GamePacketReceived_Intercept()
{
        __asm
        {
                pop ebp;
                pushad;

                call GamePacketReceived;
                test eax, eax;

                popad;
                jnz OldCode;

                mov edx, 0;

OldCode:
                call D2NET_ReceivePacket_I;

                push ebp;
                ret;
        }
}