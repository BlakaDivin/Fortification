#ifndef D2INTERCEPTS_H
#define D2INTERCEPTS_H

#include "D2Structs.h"

void myDrawText(const char* szwText, int x, int y, int color, int font);
void ColorBox(INT X1, INT Y1, INT X2, INT Y2, INT LineColor, DWORD Color, DWORD Transparency);
void SpecialTextHook(INT X, INT Y, DWORD Color, INT Font, LPSTR Text, ...);
void TextHook(INT xPos, INT yPos, DWORD dwColor, BOOL Automap, INT dwFont, INT dwCenter, LPSTR Text,...);
void DrawCross(int x, int y, DWORD Color);
VOID ScreenToAutomap(POINT *pPos, INT nX, INT nY);
void PrintConsoleString(char* Message, ...);

Level* GetUnitLevel(UnitAny* pUnit);
BOOL InTown(UnitAny* Unit);
BOOL IsBotSafe();
BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin = 0);
DWORD __fastcall GetUnitNameSTUB(DWORD Unit);
bool IsValidMonster(UnitAny *pUnit);

DWORD __fastcall GetUIVarSTUB(DWORD UI);
VOID FullLightRadiusSTUB();
VOID DrawManaOrbSTUB();
void GamePacketReceived_Intercept();

#endif