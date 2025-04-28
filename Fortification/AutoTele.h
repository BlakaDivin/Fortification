#pragma once

void OnLoop();
void OnAutomapDraw();
bool OnKey(bool up, BYTE key, LPARAM lParam);

enum TeleType {
	Next = 0,
	Other,
	WP,
	Prev
};

/*enum Type {
	UNIT_PLAYER  =	0,
	UNIT_MONSTER,
	UNIT_OBJECT,
	UNIT_MISSILE,
	UNIT_ITEM,
	UNIT_TILE,
	EXIT,
	XY
};*/

typedef struct Vector_t
{
	unsigned int dwType;
	unsigned int Id;
	unsigned int Id2;
	unsigned int Area;
} Vector;

extern int Try;
extern POINT End;
extern 		DWORD _timer, _timer2, _InteractTimer;
extern 		bool SetInteract, SetTele, CastTele, TeleActive;
extern 		bool DoInteract;
extern 		DWORD InteractId;
extern 		DWORD InteractType;
extern 		Room2* InteractRoom;
extern 		DWORD LastArea;
		
		

		//functions
DWORD GetPlayerArea();
void ManageTele(Vector T);
int MakePath(int x, int y, DWORD Areas[], DWORD count, bool MoveThrough);
POINT FindPresetLocation(DWORD dwType, DWORD dwTxtFileNo, DWORD Area);
bool GetSkill(WORD wSkillId);
bool SetSkill(WORD wSkillId, bool Left);
void PrintText(DWORD Color, char *szText, ...);
bool CastOnMap(WORD x, WORD y, bool Left);
bool Interact(DWORD UnitId, DWORD UnitType);
DWORD GetUnitByXY(DWORD X, DWORD Y, Room2* pRoom);
void GetVectors();

extern 		CArrayEx <POINT, POINT> TPath;
extern 		POINT Vectors[4];

Level* GetLevel(Act* pAct, int level);
DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2);