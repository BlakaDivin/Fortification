void PrintText(DWORD Color, char *szText, ...);
BOOL	GameReady();
DWORD	GetPlayerArea();
Level*	GetLevel(DWORD dwLevelNo);
bool	IsTownLevel(int nLevel);

DWORD	GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
DWORD	GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
typedef bool (_stdcall *fp)(UnitAny* pUnit);
DWORD	GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo);
LONG WINAPI GameEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

UnitAny* __fastcall FindItem(DWORD dwCode, INT nLoc);
BOOL Portal();
BOOL GetItemCode(UnitAny* pItem, LPSTR szBuffer, DWORD dwMax);

INT GetTotalBeltTPs();
INT GetTotalCubeTPs();
INT GetTotalInvTPs();
INT GetTotalStashTPs();

VOID ScreenToAutoMap(LPPOINT Point);
BOOL MiddleMouseButton();

BOOL AutoMana();
BOOL AutoJuv();
BOOL AutoLife();

VOID SinglePlayerChicken();
VOID Exit();

INT GetTotalBeltMana();
INT GetTotalCubeMana();
INT GetTotalInvMana();
INT GetTotalStashMana();
INT GetTotalBeltHealth();
INT GetTotalCubeHealth();
INT GetTotalInvHealth();
INT GetTotalStashHealth();
INT GetTotalBeltRejuvenation();
INT GetTotalCubeRejuvenation();
INT GetTotalInvRejuvenation();
INT GetTotalStashRejuvenation();

LPUNITANY FindNearestUnit();
BOOL UsingSkill();
VOID AttackRightMonster();
VOID AttackLeftMonster();

BOOL AutoPrecast();
void ResetPrecast();