#define WIN32_LEAN_AND_MEAN
//#define _WIN32_WINNT 0x0500

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))
#define _CRT_SECURE_NO_DEPRECATE
extern char szModulePath[260];

#define VALIDPTR(x) ( (x) && (!IsBadReadPtr(x,sizeof(x))) )

#pragma warning(disable : 4996)
#pragma warning(disable : 4244)
#pragma warning(disable : 4154)
#pragma warning(disable : 4018)

#include <windows.h>
#include <shlwapi.h>
#include <math.h>
#include <WinUser.h>
#include <time.h>

// header files
#include "D2Intercepts.h"
#include "SendPacket.h"
#include "CMapIncludes.h"
#include "D2Helpers.h"
#include "Offset.h"
#include "D2Ptrs.h"
#include "Constants.h"
#include "Matrix.h"
#include "AutoTele.h"
#include "PickIt.h"
#include "Reveal.h"
#include "ArrayEx.h"
#include "D2Structs.h"
#include "Vars.h"

/*ShellAPI Library*/
#pragma comment (lib, "shlwapi.lib")

#define EXPORT __declspec(dllexport)
#define FASTCALL __fastcall
#define FUNCCALL __cdecl
#define IMPORT __declspec(dllimport)
#define NAKED __declspec(naked)
#define STDCALL __stdcall

extern WNDPROC oldWNDPROC;
#define CToW(szString, wString)				(MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szString, (int)strlen(szString), wString, (int)strlen(szString)+1));
#define	WToC(wString, szString)				(WideCharToMultiByte(CP_ACP, 0, wString, -1, szString, (int)sizeof(szString), 0, 0));

#define FONTCOLOR_WHITE		0
#define FONTCOLOR_RED		1
#define FONTCOLOR_GREEN		2
#define FONTCOLOR_BLUE		3
#define FONTCOLOR_GOLD		4
#define FONTCOLOR_GREY		5
#define FONTCOLOR_BLACK		6
#define FONTCOLOR_BROWN		7
#define FONTCOLOR_ORANGE	8
#define FONTCOLOR_YELLOW	9
#define FONTCOLOR_PURPLE	10

#define NEXT 1
#define OTHER 2
#define WAYPOINT 3
#define PREV 4

const int CREATE[2]           = {590, 465};
const int CREATE_GAME[2]      = {680, 420};
const int JOIN[2]             = {700, 465};
const int CANCEL[2]           = {480, 420};

void click(const int* pos);
void specialclick(const int* pos);
bool Authentication();