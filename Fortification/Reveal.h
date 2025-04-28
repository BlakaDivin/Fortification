#pragma once
#include "Matrix.h"

#define MAP_DATA_NULL		-1
#define MAP_DATA_AVOID		11115
#define MAP_DATA_FILL		11111

#define MYCELL_CHUNK_NUM 15

typedef struct TCTallys
{
	INT groupnos[5];
	INT runeno;
} TCTALLYS, *LPTCTALLYS;

typedef struct MyAutomapCell
{
	WORD nCellNo;
	WORD xPixel;
	WORD yPixel;
} MYAUTOMAPCELL, *LPMYAUTOMAPCELL;

typedef struct MyAutomapLayer
{
	MyAutomapCell aMyCell[MYCELL_CHUNK_NUM];
	MyAutomapLayer *pNextChunk;
} MYAUTOMAPLAYER, *LPMYAUTOMAPLAYER;

typedef struct MyAutomapLayerMan
{
	MyAutomapLayer *pMyLayer;
	WORD wCellChunkNum;
	WORD wCellNodeNum;
} MYAUTOMAPLAYERMAN, *LPMYAUTOMAPLAYERMAN;

typedef struct CaveDescriptor_t
{
	CHAR szName[0x40];
	POINT ptPos;
	DWORD dwLevelNo;
	DWORD dwTargetLevelNo;
	DWORD dwAct;
} CAVEDESC, *LPCAVEDESC;

typedef struct pLevelExit_t
{
	POINT ptPos;
	DWORD dwTargetLevel;
} LEVELEXIT, *LPLEVELEXIT;

class Reveal
{
public:
	Reveal();
	virtual ~Reveal();

	VOID RevealAutomap();
	BOOL CreateCollisionMap();
	LPLEVEL GetLevel(ActMisc* misc, DWORD levelno);
	BOOL GetCaveExits(LPCAVEDESC *lpLevel, INT nMaxExits);
	BOOL GetLevelExits(LPLEVELEXIT *lpLevel, INT nMaxExits);
	VOID DestroyLevelExits();

	VOID AddMyAutomapCell(AutomapCell* cell);
	VOID DestroyMyAutomapCells();
	VOID DoRemoveMyAutomapCell(AutomapCell* cell);
	VOID NextRemoveMyAutomapCell(AutomapCell* cell);
	VOID RemoveMyAutomapCells();

	LPMYAUTOMAPCELL GetMyAutomapCell(INT Index);

	WORD GetCollisionInfo(INT nX, INT nY);
	BOOL ExportCollisionMap(CMatrix<WORD, WORD>& cMatrix);

	DWORD GetTileLevelNo(LPROOM2 lpRoom2, DWORD dwTileNo);

	CArrayEx<LPCAVEDESC, LPCAVEDESC> m_LevelExits;

	UCHAR m_ActLevels[6];
	UCHAR m_RevealedActs[5];

protected:
	VOID AddAutomapRoom(LPROOM2 pRoom2);
	VOID RemoveAutomapRoom(LPROOM2 pRoom2);

	VOID RevealLevel(LPLEVEL pLevel);
	VOID RevealRoom(LPROOM2 pRoom);
	VOID RevealRoom1(LPROOM2 pRoom);

	AutomapLayer2* InitAutomapLayer(DWORD dwLayer);

	BOOL AddCollisionData(LPROOM2 pRoom2, CArrayEx<DWORD, DWORD>& aSkip);
	BOOL AddCollisionData(CollMap* pColl);
	BOOL FillGaps();
	BOOL IsGap(INT nX, INT nY);

	INT m_LastLevel;
	INT m_SizeX;
	INT m_SizeY;
	POINT m_LevelOrigin;
	CMatrix<WORD, WORD> m_Map;
};

BOOL GetMapName(BYTE iMapID, LPSTR lpszBuffer, DWORD dwMaxChars);