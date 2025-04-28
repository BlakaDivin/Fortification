#include "injection.h"

Reveal::Reveal()
{
}

Reveal::~Reveal()
{
}

DWORD PreviousLevel = 0;

VOID Reveal::RevealAutomap()
{
	if (!v_Maphack)
		return;

	if (v_Bot) //Fix Waypoint Crash
		return;

	LPUNITANY pPlayer = *p_D2CLIENT_PlayerUnit;
	Act* pAct = pPlayer->pAct;
	DWORD dwAct = pPlayer->pAct->dwAct;

		Level* CurrentLevel = GetUnitLevel(pMe);

		if (CurrentLevel->dwLevelNo != PreviousLevel)
		{
		PreviousLevel = CurrentLevel->dwLevelNo;

		if (CurrentLevel->dwLevelNo < 137) //Don't Reveal EndGame Corrupted Maps
		{
		LPLEVEL pLevel = GetLevel(pAct->pMisc, CurrentLevel->dwLevelNo);

		if (!pLevel)
			return;

		if (!pLevel->pRoom2First)
			D2COMMON_InitLevel(pLevel);

		InitAutomapLayer(CurrentLevel->dwLevelNo);
		RevealLevel(pLevel);
		}
		}

	InitAutomapLayer(pPlayer->pPath->pRoom1->pRoom2->pLevel->dwLevelNo);
}

VOID Reveal::RevealLevel(LPLEVEL pLevel)
{
	for(LPROOM2 pRoom2 = pLevel->pRoom2First; pRoom2; pRoom2 = pRoom2->pRoom2Next)
		RevealRoom(pRoom2);
}

VOID Reveal::RevealRoom(LPROOM2 pRoom2)
{
	BOOL bAdded = FALSE;

	if(pRoom2->dwPresetType == 2)
	{
		//Removed
	}

	if(!pRoom2->pRoom1)
	{
		AddAutomapRoom(pRoom2);
		bAdded = TRUE;
	}

	RevealRoom1(pRoom2);

	if(bAdded)
		RemoveAutomapRoom(pRoom2);
}

BOOL GetMapName(BYTE iMapID, LPSTR lpszBuffer, DWORD dwMaxChars)
{
	if(lpszBuffer == NULL)
		return FALSE;

	lpszBuffer[0] = '\0';
	::memset(lpszBuffer, 0, sizeof(TCHAR) * dwMaxChars);
	if(dwMaxChars == 0)
		return FALSE;

	switch (iMapID)
	{	
		///////////////////////////////////////////////////
		// Act 1 Maps
		///////////////////////////////////////////////////
	case MAP_A1_ROGUE_ENCAMPMENT:
		strncpy(lpszBuffer, "Rogue Encampment", dwMaxChars);
		break;

	case MAP_A1_BLOOD_MOOR:
		strncpy(lpszBuffer, "Blood Moor", dwMaxChars);
		break;

	case MAP_A1_COLD_PLAINS:
		strncpy(lpszBuffer, "Cold Plains", dwMaxChars);
		break;

	case MAP_A1_STONY_FIELD:
		strncpy(lpszBuffer, "Stony Field", dwMaxChars);
		break;

	case MAP_A1_DARK_WOOD:
		strncpy(lpszBuffer, "Dark Wood", dwMaxChars);
		break;

	case MAP_A1_BLACK_MARSH:
		strncpy(lpszBuffer, "Black Marsh", dwMaxChars);
		break;

	case MAP_A1_DEN_OF_EVIL:
		strncpy(lpszBuffer, "Den of Evil", dwMaxChars);
		break;

	case MAP_A1_CAVE_LEVEL_1:
		strncpy(lpszBuffer, "Cave Level 1", dwMaxChars);
		break;

	case MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1:
		strncpy(lpszBuffer, "Underground Passage Level 1", dwMaxChars);
		break;

	case MAP_A1_HOLE_LEVEL_1:
		strncpy(lpszBuffer, "Hole Level 1", dwMaxChars);
		break;

	case MAP_A1_PIT_LEVEL_1:
		strncpy(lpszBuffer, "Pit Level 1", dwMaxChars);
		break;

	case MAP_A1_CAVE_LEVEL_2:
		strncpy(lpszBuffer, "Cave Level 2", dwMaxChars);
		break;

	case MAP_A1_UNDERGROUND_PASSAGE_LEVEL_2:
		strncpy(lpszBuffer, "Underground Passage Level 2", dwMaxChars);
		break;

	case MAP_A1_HOLE_LEVEL_2:
		strncpy(lpszBuffer, "Hole Level 2", dwMaxChars);
		break;

	case MAP_A1_PIT_LEVEL_2:
		strncpy(lpszBuffer, "Pit Level 2", dwMaxChars);
		break;

	case MAP_A1_BURIAL_GROUNDS:
		strncpy(lpszBuffer, "Burial Grounds", dwMaxChars);
		break;

	case MAP_A1_CRYPT:
		strncpy(lpszBuffer, "Crypt", dwMaxChars);
		break;

	case MAP_A1_MAUSOLEUM:
		strncpy(lpszBuffer, "Mausoleum", dwMaxChars);
		break;

	case MAP_A1_FORGOTTEN_TOWER:
		strncpy(lpszBuffer, "Forgotten Tower", dwMaxChars);
		break;

	case MAP_A1_TOWER_CELLAR_LEVEL_1:
		strncpy(lpszBuffer, "Tower Cellar Level 1", dwMaxChars);
		break;

	case MAP_A1_TOWER_CELLAR_LEVEL_2:
		strncpy(lpszBuffer, "Tower Cellar Level 2", dwMaxChars);
		break;

	case MAP_A1_TOWER_CELLAR_LEVEL_3:
		strncpy(lpszBuffer, "Tower Cellar Level 3", dwMaxChars);
		break;

	case MAP_A1_TOWER_CELLAR_LEVEL_4:
		strncpy(lpszBuffer, "Tower Cellar Level 4", dwMaxChars);
		break;

	case MAP_A1_TOWER_CELLAR_LEVEL_5:
		strncpy(lpszBuffer, "Tower Cellar Level 5", dwMaxChars);
		break;

	case MAP_A1_TAMOE_HIGHLAND:
		strncpy(lpszBuffer, "Tamoe Highland", dwMaxChars);
		break;

	case MAP_A1_MONASTERY_GATE:
		strncpy(lpszBuffer, "Monastery Gate", dwMaxChars);
		break;

	case MAP_A1_OUTER_CLOISTER:
		strncpy(lpszBuffer, "Outer Cloister", dwMaxChars);
		break;

	case MAP_A1_BARRACKS:
		strncpy(lpszBuffer, "Barracks", dwMaxChars);
		break;

	case MAP_A1_JAIL_LEVEL_1:
		strncpy(lpszBuffer, "Jail Level 1", dwMaxChars);
		break;

	case MAP_A1_JAIL_LEVEL_2:
		strncpy(lpszBuffer, "Jail Level 2", dwMaxChars);
		break;

	case MAP_A1_JAIL_LEVEL_3:
		strncpy(lpszBuffer, "Jail Level 3", dwMaxChars);
		break;

	case MAP_A1_INNER_CLOISTER:
	case MAP_A1_INNER_CLOISTER_2:
		strncpy(lpszBuffer, "Inner Cloister", dwMaxChars);
		break;

	case MAP_A1_CATACOMBS_LEVEL_1:
		strncpy(lpszBuffer, "Catacombs Level 1", dwMaxChars);
		break;

	case MAP_A1_CATACOMBS_LEVEL_2:
		strncpy(lpszBuffer, "Catacombs Level 2", dwMaxChars);
		break;

	case MAP_A1_CATACOMBS_LEVEL_3:
		strncpy(lpszBuffer, "Catacombs Level 3", dwMaxChars);
		break;

	case MAP_A1_CATACOMBS_LEVEL_4:
		strncpy(lpszBuffer, "Catacombs Level 4", dwMaxChars);
		break;

	case MAP_A1_TRISTRAM:
		strncpy(lpszBuffer, "Tristram", dwMaxChars);
		break;

	case MAP_A1_THE_SECRET_COW_LEVEL:
		strncpy(lpszBuffer, "The Secret Cow Level", dwMaxChars);
		break;


		///////////////////////////////////////////////////
		// Act 2 Maps
		///////////////////////////////////////////////////
	case MAP_A2_LUT_GHOLEIN:
		strncpy(lpszBuffer, "Lut Gholein", dwMaxChars);
		break;

	case MAP_A2_ROCKY_WASTE:
		strncpy(lpszBuffer, "Rocky Waste", dwMaxChars);
		break;

	case MAP_A2_DRY_HILLS:
		strncpy(lpszBuffer, "Dry Hills", dwMaxChars);
		break;

	case MAP_A2_FAR_OASIS:
		strncpy(lpszBuffer, "Far Oasis", dwMaxChars);
		break;

	case MAP_A2_LOST_CITY:
		strncpy(lpszBuffer, "Lost City", dwMaxChars);
		break;

	case MAP_A2_VALLEY_OF_SNAKES:
		strncpy(lpszBuffer, "Valley of Snakes", dwMaxChars);
		break;

	case MAP_A2_CANYON_OF_THE_MAGI:
		strncpy(lpszBuffer, "Cayon of the Magi", dwMaxChars);
		break;

	case MAP_A2_SEWERS_LEVEL_1:
		strncpy(lpszBuffer, "Sewers Level 1", dwMaxChars);
		break;

	case MAP_A2_SEWERS_LEVEL_2:
		strncpy(lpszBuffer, "Sewers Level 2", dwMaxChars);
		break;

	case MAP_A2_SEWERS_LEVEL_3:
		strncpy(lpszBuffer, "Sewers Level 3", dwMaxChars);
		break;

	case MAP_A2_HAREM_LEVEL_1:
		strncpy(lpszBuffer, "Harem Level 1", dwMaxChars);
		break;

	case MAP_A2_HAREM_LEVEL_2:
		strncpy(lpszBuffer, "Harem Level 2", dwMaxChars);
		break;

	case MAP_A2_PALACE_CELLAR_LEVEL_1:
		strncpy(lpszBuffer, "Palace Cellar Level 1", dwMaxChars);
		break;

	case MAP_A2_PALACE_CELLAR_LEVEL_2:
		strncpy(lpszBuffer, "Palace Cellar Level 2", dwMaxChars);
		break;

	case MAP_A2_PALACE_CELLAR_LEVEL_3:
		strncpy(lpszBuffer, "Palace Cellar Level 3", dwMaxChars);
		break;

	case MAP_A2_STONY_TOMB_LEVEL_1:
		strncpy(lpszBuffer, "Stony Tomb Level 1", dwMaxChars);
		break;

	case MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1:
		strncpy(lpszBuffer, "Halls of the Dead Level 1", dwMaxChars);
		break;

	case MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2:
		strncpy(lpszBuffer, "Halls of the Dead Level 2", dwMaxChars);
		break;

	case MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1:
		strncpy(lpszBuffer, "Claw Viper Temple Level 1", dwMaxChars);
		break;

	case MAP_A2_STONY_TOMB_LEVEL_2:
		strncpy(lpszBuffer, "Stony Tomb Level 2", dwMaxChars);
		break;

	case MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3:
		strncpy(lpszBuffer, "Halls of the Dead Level 3", dwMaxChars);
		break;

	case MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2:
		strncpy(lpszBuffer, "Claw Viper Temple Level 2", dwMaxChars);
		break;

	case MAP_A2_MAGGOT_LAIR_LEVEL_1:
		strncpy(lpszBuffer, "Maggot Lair Level 1", dwMaxChars);
		break;

	case MAP_A2_MAGGOT_LAIR_LEVEL_2:
		strncpy(lpszBuffer, "Maggot Lair Level 2", dwMaxChars);
		break;

	case MAP_A2_MAGGOT_LAIR_LEVEL_3:
		strncpy(lpszBuffer, "Maggot Lair Level 3", dwMaxChars);
		break;

	case MAP_A2_ANCIENT_TUNNELS:
		strncpy(lpszBuffer, "Ancient Tunnels", dwMaxChars);
		break;

	case MAP_A2_TAL_RASHAS_TOMB_1:
	case MAP_A2_TAL_RASHAS_TOMB_2:
	case MAP_A2_TAL_RASHAS_TOMB_3:
	case MAP_A2_TAL_RASHAS_TOMB_4:
	case MAP_A2_TAL_RASHAS_TOMB_5:
	case MAP_A2_TAL_RASHAS_TOMB_6:
	case MAP_A2_TAL_RASHAS_TOMB_7:
		strncpy(lpszBuffer, "Tal Rasha's Tomb", dwMaxChars);
		break;

	case MAP_A2_TAL_RASHAS_CHAMBER:
		strncpy(lpszBuffer, "Tal Rasha's Chamber", dwMaxChars);
		break;

	case MAP_A2_ARCANE_SANCTUARY:
		strncpy(lpszBuffer, "Arcane Sanctuary", dwMaxChars);
		break;


		///////////////////////////////////////////////////
		// Act 3 Maps
		///////////////////////////////////////////////////
	case MAP_A3_KURAST_DOCKS:
		strncpy(lpszBuffer, "Kurast Docks", dwMaxChars);
		break;

	case MAP_A3_SPIDER_FOREST:
		strncpy(lpszBuffer, "Spider Forest", dwMaxChars);
		break;

	case MAP_A3_GREAT_MARSH:
		strncpy(lpszBuffer, "Great Marsh", dwMaxChars);
		break;

	case MAP_A3_FLAYER_JUNGLE:
		strncpy(lpszBuffer, "Flayer Jungle", dwMaxChars);
		break;

	case MAP_A3_LOWER_KURAST:
		strncpy(lpszBuffer, "Lower Kurast", dwMaxChars);
		break;

	case MAP_A3_KURAST_BAZAAR:
		strncpy(lpszBuffer, "Kurast Bazaar", dwMaxChars);
		break;

	case MAP_A3_UPPER_KURAST:
		strncpy(lpszBuffer, "Upper Kurast", dwMaxChars);
		break;

	case MAP_A3_KURAST_CAUSEWAY:
		strncpy(lpszBuffer, "Kurast Causeway", dwMaxChars);
		break;

	case MAP_A3_TRAVINCAL:
		strncpy(lpszBuffer, "Travincal", dwMaxChars);
		break;

	case MAP_A3_ARCHNID_LAIR:
		strncpy(lpszBuffer, "Arachnid Lair", dwMaxChars);
		break;

	case MAP_A3_SPIDER_CAVERN:
		strncpy(lpszBuffer, "Spider Cavern", dwMaxChars);
		break;

	case MAP_A3_SWAMPY_PIT_LEVEL_1:
		strncpy(lpszBuffer, "Swampy Pit Level 1", dwMaxChars);
		break;

	case MAP_A3_SWAMPY_PIT_LEVEL_2:
		strncpy(lpszBuffer, "Swampy Pit Level 2", dwMaxChars);
		break;

	case MAP_A3_FLAYER_DUNGEON_LEVEL_1:
		strncpy(lpszBuffer, "Flayer Dungeon Level 1", dwMaxChars);
		break;

	case MAP_A3_FLAYER_DUNGEON_LEVEL_2:
		strncpy(lpszBuffer, "Flayer Dungeon Level 2", dwMaxChars);
		break;

	case MAP_A3_SWAMPY_PIT_LEVEL_3:
		strncpy(lpszBuffer, "Swampy Pit Level 3", dwMaxChars);
		break;

	case MAP_A3_FLAYER_DUNGEON_LEVEL_3:
		strncpy(lpszBuffer, "Flayer Dungeon Level 3", dwMaxChars);
		break;

	case MAP_A3_SEWERS_LEVEL_1:
		strncpy(lpszBuffer, "Sewers Level 1", dwMaxChars);
		break;

	case MAP_A3_SEWERS_LEVEL_2:
		strncpy(lpszBuffer, "Sewers Level 2", dwMaxChars);
		break;

	case MAP_A3_RUINED_TEMPLE:
		strncpy(lpszBuffer, "Ruined Temple", dwMaxChars);
		break;

	case MAP_A3_DISUSED_FANE:
		strncpy(lpszBuffer, "Disused Fane", dwMaxChars);
		break;

	case MAP_A3_FORGOTTEN_RELIQUARY:
		strncpy(lpszBuffer, "Forgotten Reliquary", dwMaxChars);
		break;

	case MAP_A3_FORGOTTEN_TEMPLE:
		strncpy(lpszBuffer, "Forgotten Temple", dwMaxChars);
		break;

	case MAP_A3_RUINED_FANE:
		strncpy(lpszBuffer, "Ruined Fane", dwMaxChars);
		break;

	case MAP_A3_DISUSED_RELIQUARY:
		strncpy(lpszBuffer, "Disused Reliquary", dwMaxChars);
		break;

	case MAP_A3_DURANCE_OF_HATE_LEVEL_1:
		strncpy(lpszBuffer, "Durance of Hate Level 1", dwMaxChars);
		break;

	case MAP_A3_DURANCE_OF_HATE_LEVEL_2:
		strncpy(lpszBuffer, "Durance of Hate Level 2", dwMaxChars);
		break;

	case MAP_A3_DURANCE_OF_HATE_LEVEL_3:
		strncpy(lpszBuffer, "Durance of Hate Level 3", dwMaxChars);
		break;

		///////////////////////////////////////////////////
		// Act 4 Maps
		///////////////////////////////////////////////////
	case MAP_A4_THE_PANDEMONIUM_FORTRESS:
		strncpy(lpszBuffer, "The Pandemonium Fortress", dwMaxChars);
		break;

	case MAP_A4_OUTER_STEPPES:
		strncpy(lpszBuffer, "Outer Steppes", dwMaxChars);
		break;

	case MAP_A4_PLAINS_OF_DESPAIR:
		strncpy(lpszBuffer, "Plains of Despair", dwMaxChars);
		break;

	case MAP_A4_CITY_OF_THE_DAMNED:
		strncpy(lpszBuffer, "City of the Damned", dwMaxChars);
		break;

	case MAP_A4_RIVER_OF_FLAME:
		strncpy(lpszBuffer, "River of Flame", dwMaxChars);
		break;

	case MAP_A4_THE_CHAOS_SANCTUARY:
		strncpy(lpszBuffer, "The Chaos Sanctuary", dwMaxChars);
		break;

		///////////////////////////////////////////////////
		// Act 5 Maps
		///////////////////////////////////////////////////
	case MAP_A5_HARROGATH:
		strncpy(lpszBuffer, "Harrogath", dwMaxChars);
		break;

	case MAP_A5_THE_BLOODY_FOOTHILLS:
		strncpy(lpszBuffer, "The Bloody Foothills", dwMaxChars);
		break;

	case MAP_A5_FRIGID_HIGHLANDS:
		strncpy(lpszBuffer, "Frigid Highlands", dwMaxChars);
		break;

	case MAP_A5_ARREAT_PLATEAU:
		strncpy(lpszBuffer, "Arreat Plateau", dwMaxChars);
		break;

	case MAP_A5_CRYSTALLINE_PASSAGE:
		strncpy(lpszBuffer, "Crystalline Passage", dwMaxChars);
		break;

	case MAP_A5_FROZEN_RIVER:
		strncpy(lpszBuffer, "Frozen River", dwMaxChars);
		break;

	case MAP_A5_GLACIAL_TRAIL:
		strncpy(lpszBuffer, "Glacial Trail", dwMaxChars);
		break;

	case MAP_A5_DRIFTER_CAVERN:
		strncpy(lpszBuffer, "Drifter Cavern", dwMaxChars);
		break;

	case MAP_A5_FROZEN_TUNDRA:
		strncpy(lpszBuffer, "Frozen Tundra", dwMaxChars);
		break;

	case MAP_A5_THE_ANCIENTS_WAY:
		strncpy(lpszBuffer, "The Ancients' Way", dwMaxChars);
		break;

	case MAP_A5_ICY_CELLAR:
		strncpy(lpszBuffer, "Icy Cellar", dwMaxChars);
		break;

	case MAP_A5_ARREAT_SUMMIT:
		strncpy(lpszBuffer, "Arreat Summit", dwMaxChars);
		break;

	case MAP_A5_HALLS_OF_PAIN:
		strncpy(lpszBuffer, "Halls of Pain", dwMaxChars);
		break;

	case MAP_A5_ABADDON:
		strncpy(lpszBuffer, "Abaddon", dwMaxChars);
		break;

	case MAP_A5_PIT_OF_ACHERON:
		strncpy(lpszBuffer, "Pit of Acheron", dwMaxChars);
		break;

	case MAP_A5_INFERNAL_PIT:
		strncpy(lpszBuffer, "Infernal Pit", dwMaxChars);
		break;

	case MAP_A5_NIHLATHAKS_TEMPLE:
		strncpy(lpszBuffer, "Nihlathak's Temple", dwMaxChars);
		break;

	case MAP_A5_HALLS_OF_ANGUISH:
		strncpy(lpszBuffer, "Halls of Anguish", dwMaxChars);
		break;

	case MAP_A5_HALLS_OF_VAUGHT:
		strncpy(lpszBuffer, "Halls of Vaught", dwMaxChars);
		break;	

	case MAP_A5_WORLDSTONE_KEEP_LEVEL_1:
		strncpy(lpszBuffer, "Worldstone Keep Level 1", dwMaxChars);
		break;

	case MAP_A5_WORLDSTONE_KEEP_LEVEL_2:
		strncpy(lpszBuffer, "Worldstone Keep Level 2", dwMaxChars);
		break;

	case MAP_A5_WORLDSTONE_KEEP_LEVEL_3:
		strncpy(lpszBuffer, "Worldstone Keep Level 3", dwMaxChars);
		break;

	case MAP_A5_THRONE_OF_DESTRUCTION:
		strncpy(lpszBuffer, "Throne of Destruction", dwMaxChars);
		break;

	case MAP_A5_WORLDSTONE_KEEP:
		strncpy(lpszBuffer, "The Worldstone Chamber", dwMaxChars);
		break;

	default:
		strncpy(lpszBuffer, "Project Diablo 2", dwMaxChars);
		break;
	}

	return FALSE;
}

VOID Reveal::RevealRoom1(LPROOM2 pRoom)
{
	D2CLIENT_RevealAutomapRoom(pRoom->pRoom1, 1, *p_D2CLIENT_AutomapLayer);

	for(PresetUnit* pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
	{
		INT nCell = 0;

		if(pUnit->dwType == UNIT_TYPE_NPC)
		{
			if(pUnit->dwTxtFileNo == 256) nCell = 300;
			if(pUnit->dwTxtFileNo == 745) nCell = 745;
		}

		if(pUnit->dwType == UNIT_TYPE_OBJECT)
		{
			
		}

		if(pUnit->dwType == UNIT_TYPE_TILE)
		{
			DWORD dwTargetLevel = GetTileLevelNo(pRoom, pUnit->dwTxtFileNo);
			if(dwTargetLevel)
			{
				for(INT i = 0; i < m_LevelExits.GetSize(); i++)
				{
					if((m_LevelExits[i]->ptPos.x == (pRoom->dwPosX * 5) + pUnit->dwPosX) && 
						(m_LevelExits[i]->ptPos.y == (pRoom->dwPosY * 5) + pUnit->dwPosY))
						return;
				}

				LPCAVEDESC LevelDesc = new CAVEDESC;
				CHAR szLevel[0x40] = "";

				::memset(LevelDesc, 0, sizeof(CAVEDESC));
				GetMapName((INT)dwTargetLevel, szLevel, 0x40);

				sprintf_s(LevelDesc->szName, szLevel);
				LevelDesc->ptPos.x = (pRoom->dwPosX * 5) + pUnit->dwPosX - (8 << 1);
				LevelDesc->ptPos.y = (pRoom->dwPosY * 5) + pUnit->dwPosY - 10;
				LevelDesc->dwAct = pMe->pAct->dwAct;
				LevelDesc->dwLevelNo = pRoom->pLevel->dwLevelNo;
				LevelDesc->dwTargetLevelNo = dwTargetLevel;

				if(dwTargetLevel == pRoom->pLevel->pMisc->dwStaffTombLevel)
					strcat_s(LevelDesc->szName, "ÿc2*");

				m_LevelExits.Add(LevelDesc);
			}
		}
	}
}

VOID Reveal::AddMyAutomapCell(AutomapCell* cell)
{
	LPMYAUTOMAPLAYERMAN pMyLayerMan = &v_MyAutoMapLayer[AutoMapLayer->nLayerNo];
	LPMYAUTOMAPLAYER * ppMyLayer = &pMyLayerMan->pMyLayer;

	while (*ppMyLayer && (*ppMyLayer)->pNextChunk)
		ppMyLayer = &(*ppMyLayer)->pNextChunk;

	if (*ppMyLayer && pMyLayerMan->wCellNodeNum < MYCELL_CHUNK_NUM)
	{
		(*ppMyLayer)->aMyCell[pMyLayerMan->wCellNodeNum].nCellNo = cell->nCellNo;
		(*ppMyLayer)->aMyCell[pMyLayerMan->wCellNodeNum].xPixel = cell->xPixel;
		(*ppMyLayer)->aMyCell[pMyLayerMan->wCellNodeNum].yPixel = cell->yPixel;
		pMyLayerMan->wCellNodeNum++;
	}

	else
	{
		if (*ppMyLayer)
			ppMyLayer = &(*ppMyLayer)->pNextChunk;

		*ppMyLayer = new MyAutomapLayer;
		memset(*ppMyLayer, 0, sizeof(MyAutomapLayer));
		pMyLayerMan->wCellChunkNum++;
		(*ppMyLayer)->aMyCell[0].nCellNo = cell->nCellNo;
		(*ppMyLayer)->aMyCell[0].xPixel = cell->xPixel;
		(*ppMyLayer)->aMyCell[0].yPixel = cell->yPixel;
		pMyLayerMan->wCellNodeNum = 1;
	}
}

VOID Reveal::DestroyMyAutomapCells()
{
	for (INT i = 0; i < ArraySize(v_MyAutoMapLayer); i++)
	{
		LPMYAUTOMAPLAYER pMyLayer = v_MyAutoMapLayer[i].pMyLayer;

		while(pMyLayer)
		{
			MyAutomapLayer *pTemp = pMyLayer->pNextChunk;
			delete pMyLayer;
			pMyLayer = pTemp;
		}
	}

	::memset(v_MyAutoMapLayer, 0, sizeof(v_MyAutoMapLayer));
}

VOID Reveal::DoRemoveMyAutomapCell(AutomapCell* cell)
{
	if (cell->nCellNo >= CELLNO_MYSHRINES && cell->nCellNo < CELLNO_MYSHRINES+23)
		cell->nCellNo = CELLNO_SHRINE;

	else if ((SHORT)cell->nCellNo < 0)
		cell->nCellNo = 0;
}

VOID Reveal::NextRemoveMyAutomapCell(AutomapCell* cell)
{
	if (cell)
	{
		NextRemoveMyAutomapCell(cell->pLess);
		DoRemoveMyAutomapCell(cell);
		NextRemoveMyAutomapCell(cell->pMore);
	}
}

VOID Reveal::RemoveMyAutomapCells()
{
	// Removed
}

LPMYAUTOMAPCELL Reveal::GetMyAutomapCell(INT Index)
{
	LPMYAUTOMAPLAYERMAN MyLayerMan = &v_MyAutoMapLayer[AutoMapLayer->nLayerNo];

	INT Chunk = Index / MYCELL_CHUNK_NUM;
	INT ID = Index % MYCELL_CHUNK_NUM;

	LPMYAUTOMAPLAYER MyLayer = MyLayerMan->pMyLayer;
	
	for (INT j = 0; MyLayer && j < Chunk; j++)
		MyLayer = MyLayer->pNextChunk;
	
	return MyLayer ? &MyLayer->aMyCell[ID] : NULL;
}

VOID Reveal::AddAutomapRoom(LPROOM2 pRoom2)
{
	LPUNITANY pUnit = *p_D2CLIENT_PlayerUnit;
	D2COMMON_AddRoomData(pRoom2->pLevel->pMisc->pAct,
		pRoom2->pLevel->dwLevelNo,
		pRoom2->dwPosX,
		pRoom2->dwPosY,
		pUnit->pPath->pRoom1);
}

VOID Reveal::RemoveAutomapRoom(LPROOM2 pRoom2)
{
	LPUNITANY pUnit = *p_D2CLIENT_PlayerUnit;
	D2COMMON_RemoveRoomData(pRoom2->pLevel->pMisc->pAct,
		pRoom2->pLevel->dwLevelNo,
		pRoom2->dwPosX,
		pRoom2->dwPosY,
		pUnit->pPath->pRoom1);
}

BOOL Reveal::GetCaveExits(LPCAVEDESC *lpLevel, INT nMaxExits)
{
	INT nTotal = 0;

	for(INT i = 0; i < m_LevelExits.GetSize(); i++)
	{
		if(nTotal > nMaxExits)
			return FALSE;

		lpLevel[nTotal] = m_LevelExits[i];
		nTotal++;
	}

	return nTotal;
}

DWORD Reveal::GetTileLevelNo(LPROOM2 lpRoom2, DWORD dwTileNo)
{
	for(RoomTile* pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
	{
		if(*(pRoomTile->nNum) == dwTileNo)
			return pRoomTile->pRoom2->pLevel->dwLevelNo;
	}

	return NULL;
}

LPLEVEL Reveal::GetLevel(ActMisc* pMisc, DWORD dwLevelNo)
{
	for(LPLEVEL pLevel = pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if (pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(pMisc, dwLevelNo);
}

DWORD NAKED FASTCALL InitAutomapLayerSTUB(DWORD dwLayer)
{
	__asm
	{
		PUSH EAX;
		MOV EAX, ECX;
		CALL D2CLIENT_InitAutomapLayer_I;
		POP EAX;
		RET;
	}
}

AutomapLayer2* Reveal::InitAutomapLayer(DWORD levelno)
{
	AutomapLayer2* pLayer = D2COMMON_GetLayer(levelno);
	return (AutomapLayer2*)InitAutomapLayerSTUB(pLayer->nLayerNo);
}

BOOL Reveal::CreateCollisionMap()
{
	if(GetUnitLevel(pMe)->dwLevelNo == m_LastLevel)
		return TRUE;

	if(!pMe)
		return FALSE;

	if(!pMe->pPath->pRoom1)
		return FALSE;

	LPLEVEL pLevel = pMe->pPath->pRoom1->pRoom2->pLevel;
	if(!pLevel)
		return FALSE;

	if(m_Map.IsCreated())
		m_Map.Destroy();

	m_LastLevel = pLevel->dwLevelNo;
	m_LevelOrigin.x = pLevel->dwPosX * 5;
	m_LevelOrigin.y = pLevel->dwPosY * 5;
	m_SizeX = pLevel->dwSizeX * 5;
	m_SizeY = pLevel->dwSizeY * 5;

	m_Map.Lock();
	if(!m_Map.Create(pLevel->dwSizeX * 5, pLevel->dwSizeY * 5, MAP_DATA_NULL))
	{
		m_Map.Unlock();
		return FALSE;
	}

	CArrayEx<DWORD, DWORD> aSkip;
	AddCollisionData(pMe->pPath->pRoom1->pRoom2, aSkip);

	FillGaps();
	FillGaps();

	m_Map.Unlock();
	return TRUE;
}

BOOL Reveal::IsGap(INT nX, INT nY)
{
	if(m_Map[nX][nY] % 2)
		return FALSE;

	INT nSpaces = 0;
	INT i = 0;

	for(i = nX - 2; i <= nX + 2 && nSpaces < 3; i++)
	{
		if(i < 0 || i >= m_Map.GetCX() || (m_Map[i][nY] % 2))
			nSpaces = 0;
		else
			nSpaces++;
	}

	if(nSpaces < 3)
		return TRUE;

	nSpaces = 0;
	for(i = nY - 2; i <= nY + 2 && nSpaces < 3; i++)
	{
		if(i < 0 || i >= m_Map.GetCY() || (m_Map[nX][i] % 2))
			nSpaces = 0;
		else
			nSpaces++;
	}

	return nSpaces < 3;
}

BOOL Reveal::FillGaps()
{
	if(!m_Map.IsCreated())
		return FALSE;

	INT nCX = m_Map.GetCX();
	INT nCY = m_Map.GetCY();

	for(INT x = 0; x < nCX; x++)
	{
		for(INT y = 0; y < nCY; y++)
		{
			if(IsGap(x, y))
				m_Map[x][y] = MAP_DATA_FILL;
		}
	}

	return TRUE;
}

BOOL Reveal::AddCollisionData(CollMap* pColl)
{
	if(!pColl)
		return FALSE;

	INT nX = pColl->dwPosGameX - m_LevelOrigin.x;
	INT nY = pColl->dwPosGameY - m_LevelOrigin.y;
	INT nCX = pColl->dwSizeGameX;
	INT nCY = pColl->dwSizeGameY;

	if(!m_Map.IsValidIndex(nX, nY))
		return FALSE;

	INT nLimitX = nX + nCX;
	INT nLimitY = nY + nCY;

	LPWORD p = pColl->pMapStart;
	if(!p)
		return FALSE;

	for(INT y = nY; y < nLimitY; y++)
	{
		for(INT x = nX; x < nLimitX; x++)
		{
			m_Map[x][y] = *p;

			if(m_Map[x][y] == 1024)
				m_Map[x][y] = MAP_DATA_AVOID;

			p++;
		}
	}

	return TRUE;
}

BOOL Reveal::AddCollisionData(LPROOM2 pRoom2, CArrayEx<DWORD, DWORD>& aSkip)
{
	if(!pRoom2)
		return FALSE;

	if(pRoom2->pLevel->dwLevelNo != m_LastLevel)
		return FALSE;

	if(aSkip.Find((DWORD)pRoom2) != -1)
		return TRUE;

	aSkip.Add((DWORD)pRoom2);

	BOOL bAdd = FALSE;
	if(!pRoom2->pRoom1)
	{
		AddAutomapRoom(pRoom2);
		bAdd = TRUE;
	}

	if(pRoom2->pRoom1)
		AddCollisionData(pRoom2->pRoom1->Coll);

	LPROOM2 *pRoomNear = pRoom2->pRoom2Near;
	for(DWORD i = 0; i < pRoom2->dwRoomsNear; i++)
		AddCollisionData(pRoomNear[i], aSkip);

	if(bAdd)
		RemoveAutomapRoom(pRoom2);

	return TRUE;
}

BOOL Reveal::GetLevelExits(LPLEVELEXIT *lpLevel, INT nMaxExits)
{
	POINT ptExitPoints[0x40][2];
	INT nTotalPoints = 0, nCurrentExit = 0;

	for(INT i = 0; i < m_Map.GetCX(); i++)
	{
		if(!(m_Map[i][0] % 2))
		{
			ptExitPoints[nTotalPoints][0].x = i;
			ptExitPoints[nTotalPoints][0].y = 0;

			for(i++; i < m_Map.GetCX(); i++)
			{
				if(m_Map[i][0] % 2)
				{
					ptExitPoints[nTotalPoints][1].x = i - 1;
					ptExitPoints[nTotalPoints][1].y = 0;
					break;
				}
			}

			nTotalPoints++;
			break;
		}
	}

	for(INT i = 0; i < m_Map.GetCX(); i++)
	{
		if(!(m_Map[i][m_Map.GetCY() - 1] % 2))
		{
			ptExitPoints[nTotalPoints][0].x = i;
			ptExitPoints[nTotalPoints][0].y = m_Map.GetCY() - 1;

			for(i++; i < m_Map.GetCX(); i++)
			{
				if((m_Map[i][m_Map.GetCY() - 1] % 2))
				{
					ptExitPoints[nTotalPoints][1].x = i - 1;
					ptExitPoints[nTotalPoints][1].y = m_Map.GetCY() - 1;
					break;
				}
			}

			nTotalPoints++;
			break;
		}
	}

	for(INT i = 0; i < m_Map.GetCY(); i++)
	{
		if(!(m_Map[0][i] % 2))
		{
			ptExitPoints[nTotalPoints][0].x = 0;
			ptExitPoints[nTotalPoints][0].y = i;

			for(i++; i < m_Map.GetCY(); i++)
			{
				if((m_Map[0][i] % 2))
				{
					ptExitPoints[nTotalPoints][1].x = 0;
					ptExitPoints[nTotalPoints][1].y = i - 1;
					break;
				}
			}

			nTotalPoints++;
			break;
		}
	}

	for(INT i = 0; i < m_Map.GetCY(); i++)
	{
		if(!(m_Map[m_Map.GetCX() - 1][i] % 2))
		{
			ptExitPoints[nTotalPoints][0].x = m_Map.GetCX() - 1;
			ptExitPoints[nTotalPoints][0].y = i;

			for(i++; i < m_Map.GetCY(); i++)
			{
				if((m_Map[m_Map.GetCX() - 1][i] % 2))
				{
					ptExitPoints[nTotalPoints][1].x = m_Map.GetCX() - 1;
					ptExitPoints[nTotalPoints][1].y = i - 1;
					break;
				}
			}

			nTotalPoints++;
			break;
		}
	}

	LPPOINT ptCenters = new POINT[nTotalPoints];

	for(INT i = 0; i < nTotalPoints; i++)
	{
		INT nXDiff = ptExitPoints[i][1].x - ptExitPoints[i][0].x;
		INT nYDiff = ptExitPoints[i][1].y - ptExitPoints[i][0].y;
		INT nXCenter = 0, nYCenter = 0;

		if(nXDiff > 0)
		{
			if(nXDiff % 2)
				nXCenter = ptExitPoints[i][0].x + ((nXDiff - (nXDiff % 2)) / 2);
			else
				nXCenter = ptExitPoints[i][0].x + (nXDiff / 2);
		}

		if(nYDiff > 0)
		{
			if(nYDiff % 2)
				nYCenter = ptExitPoints[i][0].y + ((nYDiff - (nYDiff % 2)) / 2);
			else
				nYCenter = ptExitPoints[i][0].y + (nYDiff / 2);
		}

		ptCenters[i].x = nXCenter ? nXCenter : ptExitPoints[i][0].x;
		ptCenters[i].y = nYCenter ? nYCenter : ptExitPoints[i][0].y;
	}

	for(LPROOM2 pRoom = GetUnitLevel(pMe)->pRoom2First; pRoom; pRoom = pRoom->pRoom2Next)
	{
		LPROOM2 * pNear = pRoom->pRoom2Near;

		for(DWORD i = 0; i < pRoom->dwRoomsNear; i++)
		{
			if(pNear[i]->pLevel->dwLevelNo != GetUnitLevel(pMe)->dwLevelNo)
			{
				INT nRoomX = pRoom->dwPosX * 5;
				INT nRoomY = pRoom->dwPosY * 5;

				for(INT j = 0; j < nTotalPoints; j++)
				{
					if((ptCenters[j].x + m_LevelOrigin.x) >= (WORD)nRoomX && (ptCenters[j].x + m_LevelOrigin.x) <= (WORD)(nRoomX + (pRoom->dwSizeX * 5)))
					{
						if((ptCenters[j].y + m_LevelOrigin.y) >= (WORD)nRoomY && (ptCenters[j].y + m_LevelOrigin.y) <= (WORD)(nRoomY + (pRoom->dwSizeY * 5)))
						{
							if(nCurrentExit >= nMaxExits)
								return FALSE;

							lpLevel[nCurrentExit] = new LEVELEXIT;
							lpLevel[nCurrentExit]->dwTargetLevel = pNear[i]->pLevel->dwLevelNo;
							lpLevel[nCurrentExit]->ptPos.x = ptCenters[j].x + m_LevelOrigin.x;
							lpLevel[nCurrentExit]->ptPos.y = ptCenters[j].y + m_LevelOrigin.y;
							nCurrentExit++;
						}
					}
				}

				break;
			}
		}

		BOOL bAdded = FALSE;

		if(!pRoom->pRoom1)
		{
			D2COMMON_AddRoomData(pMe->pAct, pRoom->pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, pMe->pPath->pRoom1);
			bAdded = TRUE;
		}
			
		for(PresetUnit* pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
		{
			if(nCurrentExit >= nMaxExits)
			{
				if(bAdded)
					D2COMMON_RemoveRoomData(pMe->pAct, pRoom->pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, pMe->pPath->pRoom1);

				return FALSE;
			}

			if(pUnit->dwType == UNIT_TYPE_TILE)
			{
				DWORD dwTargetLevel = GetTileLevelNo(pRoom, pUnit->dwTxtFileNo);
				
				if(dwTargetLevel)
				{
					BOOL Exists = FALSE;

					for(INT i = 0; i < nCurrentExit; i++)
					{
						if((lpLevel[i]->ptPos.x == (pRoom->dwPosX * 5) + pUnit->dwPosX) &&
							(lpLevel[i]->ptPos.y == (pRoom->dwPosY * 5) + pUnit->dwPosY))
							Exists = TRUE;
					}

					if (!Exists)
					{
						lpLevel[nCurrentExit] = new LEVELEXIT;
						lpLevel[nCurrentExit]->dwTargetLevel = dwTargetLevel;
						lpLevel[nCurrentExit]->ptPos.x = (pRoom->dwPosX * 5) + pUnit->dwPosX;
						lpLevel[nCurrentExit]->ptPos.y = (pRoom->dwPosY * 5) + pUnit->dwPosY;
						nCurrentExit++;
					}
				}
			}
		}

		if(bAdded)
			D2COMMON_RemoveRoomData(pMe->pAct, pRoom->pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, pMe->pPath->pRoom1);
	}

	return TRUE;
}

VOID Reveal::DestroyLevelExits()
{
	if (!m_LevelExits.IsEmpty())
	{
		for (INT i = 0; i < m_LevelExits.GetSize(); i++)
		{
			if (m_LevelExits[i])
				delete m_LevelExits[i];
		}

		m_LevelExits.RemoveAll();
	}
}

WORD Reveal::GetCollisionInfo(INT nX, INT nY)
{
	nX -= m_LevelOrigin.x;
	nY -= m_LevelOrigin.y;

	if(!m_Map.IsValidIndex(nX, nY))
		return NULL;

	return m_Map[nX][nY];
}

BOOL Reveal::ExportCollisionMap(CMatrix<WORD, WORD>& cMatrix)
{
	m_Map.Lock();
	m_Map.ExportData(cMatrix);
	m_Map.Unlock();

	return TRUE;
}