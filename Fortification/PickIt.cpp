#include "injection.h"

void TakeWp()
{
		for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_OBJECT)
			{
				if (pUnit->dwTxtFileNo == 429)
				{
						BYTE Packet[9];
	                    Packet[0] = 0x49;
	                    *(LPDWORD)&Packet[1] = pUnit->dwUnitId;
	                    *(LPDWORD)&Packet[2] = NULL;
	                    *(LPDWORD)&Packet[3] = NULL;
	                    *(LPDWORD)&Packet[4] = NULL;
	                    *(LPDWORD)&Packet[5] = 0x6F;
						*(LPDWORD)&Packet[6] = NULL;
	                    *(LPDWORD)&Packet[7] = NULL;
	                    *(LPDWORD)&Packet[8] = NULL;

	                    D2NET_SendPacket(9,0,Packet);

						break; //Fix Unhandled Exception
				}
			}
}

void RessurectMerc(DWORD NPCID)
{
	BYTE Packet[5];
	Packet[0] = 0x62;
	*(LPDWORD)&Packet[1] = NPCID;
	*(LPDWORD)&Packet[2] = NULL;
	*(LPDWORD)&Packet[3] = NULL;
	*(LPDWORD)&Packet[4] = NULL;
	*(LPDWORD)&Packet[5] = NULL;
	D2NET_SendPacket(5, 1, Packet);
}

void QualInteract()
{
	 for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_NPC)
			{
				if (pUnit->dwTxtFileNo == 515) //Qual-Khek
				{ 

					Interact(pUnit->dwUnitId, UNIT_TYPE_NPC);

					break; //Fix Unhandled Exception
				}
			}
}

void ReviveMerc()
{
   for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_NPC)
			{
				if (pUnit->dwTxtFileNo == 515) //Qual-Khek
				{ 
					RessurectMerc(pUnit->dwUnitId);

					break; //Fix Unhandled Exception
				}
			}
}

VOID CloseInteract()
{
	D2CLIENT_CloseNPCInteract();
}

BOOL IsMercClassId(DWORD dwClassID)
{
	return dwClassID == MERC_A1 || dwClassID == MERC_A2 || dwClassID == MERC_A3 || dwClassID == MERC_A4LIGHT  || dwClassID == MERC_A4DARK  || dwClassID == MERC_A5;
}

LPUNITANY FindMercUnit(LPUNITANY pOwner)
{
	for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if(IsMercClassId(pUnit->dwTxtFileNo) && D2CLIENT_GetMonsterOwner(pUnit->dwUnitId) == pOwner->dwUnitId)
			{
				return pUnit;
			}

	return NULL;
}

void InteractMalah()
{
	 for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_NPC)
			{
				if (pUnit->dwTxtFileNo == 513) //Malah
				{ 
					Interact(pUnit->dwUnitId, UNIT_TYPE_NPC);

					break; //Fix Unhandled Exception
				}
			}
}

VOID MapToScreenCoords(LPPOINT Position)
{
	D2COMMON_MapToAbsScreen(&Position->x, &Position->y);
	Position->x -= D2CLIENT_GetPlayerXOffset();
	Position->y -= D2CLIENT_GetPlayerYOffset();
}

void fakeRunXY(unsigned short x, unsigned short y)
{
	//send "run" packet
	unsigned char* buffer = new unsigned char[16];

	buffer[0] = 0x0f; //run packet ID
	buffer[1] = 0x00;
	*(unsigned int*)&buffer[2] = pMe->dwUnitId;
	buffer[6] = 0x17;
	*(unsigned short*)&buffer[7] = x;
	*(unsigned short*)&buffer[9] = y;
	buffer[11] = 0x00;
	*(unsigned int*)&buffer[12] = 0x0000;

	D2NET_ReceivePacket(buffer, 16);

	delete[] buffer; //Fix Memory Leak
}

void Walkto(short x, short y)
{
    unsigned char buffer[5];
	buffer[0] =0x03;
	*reinterpret_cast<short*>(buffer + 1) = x;
	*reinterpret_cast<short*>(buffer + 3) = y;

	D2NET_SendPacket(5,0,buffer);

	delete[] buffer; //Fix Memory Leak 

	fakeRunXY(x,y);
}

void GetReAsign(WORD xpos, WORD ypos)
{
}

void WalkToMalah()
{
	 for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_NPC)
			{
				if (pUnit->dwTxtFileNo == 513) //Malah
				{ 
					unsigned char *buffer = new unsigned char[9];
	                buffer[0]=0x04;
	                *(int*)&buffer[1] = 0x01;
	                buffer[2]=0x00;
	                buffer[3]=0x00;
	                buffer[4]=0x00;
	                *(int*)&buffer[5] = pUnit->dwUnitId;

					D2NET_SendPacket(9,0,buffer);

	                delete[] buffer; //Fix Memory Leak 

					break; //Fix Unhandled Exception
				}
			}
}

void WalkToQual()
{
	 for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_NPC)
			{
				if (pUnit->dwTxtFileNo == 515) //Qual-Khek
				{ 
	                unsigned char *buffer = new unsigned char[9];
	                buffer[0]=0x04;
	                *(int*)&buffer[1] = 0x01;
	                buffer[2]=0x00;
	                buffer[3]=0x00;
	                buffer[4]=0x00;
	                *(int*)&buffer[5] = pUnit->dwUnitId;

					D2NET_SendPacket(9,0,buffer);

	                delete[] buffer; //Fix Memory Leak 

					break; //Fix Unhandled Exception
				}
			}
}

/*Very Basic Bot Script Made In C++ - Supports All Chars*/

BOOL MalahA, MalahB, MalahC, MalahD, MalahE, MalahF, MalahG, MalahH, MalahI, MalahJ = false;
BOOL EntryA, EntryB, EntryC, EntryD, EntryE, EntryF, EntryG = false;
BOOL QualA, QualB, QualC, QualD, QualE, QualF, QualG, QualH, QualI, QualJ, QualK, QualL, QualM, QualN, QualO, QualP, QualQ,
	 QualR, QualS = false;
BOOL CheckA, CheckB, CheckC, CheckD, CheckE, CheckF, CheckG, CheckH, CheckI, CheckJ, CheckK, CheckL, CheckM, CheckN, CheckO,
	 CheckP, CheckQ, CheckR, CheckS, CheckT, CheckU, CheckV, CheckW, CheckX, CheckY, CheckZ, CheckAA,
	 CheckBB, CheckCC, CheckDD, CheckEE, CheckFF, CheckGG, CheckHH, CheckINT, CheckINT2, CheckINT3,
	 CheckII, CheckJJ, CheckKK, CheckLL, CheckMM, CheckNN, CheckOO = false;
DWORD Delay = NULL;
DWORD AttackDelay = 5000;
DWORD MercDelay = 400;
DWORD QualInteractDelay = 1200;
BOOL MercPathing = false;
BOOL EldrichComplete = false;
BOOL ShenkComplete = false;
BOOL DoPrecast = false;
BOOL MalahPathing = false;
DWORD MalahPathDelay = 400;
DWORD MalahInteractDelay = 1500;

BOOL Bot()
{
	if (v_DelayedChicken)
	{
		if (GetTickCount() - Delay >= 400)
	    {
			v_DelayedChicken = false;

			if (!InTown(pMe)) D2CLIENT_ExitGame();
		}

		return false;
	}

    LPUNITANY Unit = FindNearestUnit();

	if (Unit && !v_Precast)
		{
		DWORD Distance = CalculateDistance(Unit->pPath->xPos, Unit->pPath->yPos, pMe->pPath->xPos, pMe->pPath->yPos);

		if (Unit && Distance <= 10)
		{
			if (GetTickCount() - AttackDelay >= 500)
		    {
		    AttackLeftMonster();

			AttackDelay = GetTickCount();
			Delay = GetTickCount();
			}

		return false;
		}
	    }

	if (!MalahA)
	{
	if (GetTickCount() - Delay >= 400)
	{
	v_BotCounter = GetTickCount();
	v_TownLife = 0;
	v_ExitLife = 20;

	PrintText(0,"ÿc9Avatar: ÿc0Games Left: %d", v_MaxGameAmount - v_GameAmount);

	PrintText(0,"ÿc9Avatar: ÿc0Checking Life Percentage");

	DOUBLE LifePercent = CalcPercent((GetUnitStat(pMe, STAT_HP) >> 8), (GetUnitStat(pMe, STAT_MAXHP) >> 8));

	if (LifePercent <= 80) //Path To Malah If Life Below 80
	{
		PrintText(0,"ÿc9Avatar: ÿc0Going To Malah");
		Walkto(5090, 5026);
		MalahPathing = true;
		MalahPathDelay = 400;
		MalahInteractDelay = 1500;
	}
	else
	{
		MalahPathDelay = 0;
		MalahInteractDelay = 0;
	}

	MalahA = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahB)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5086, 5030);
 
	MalahB = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahC)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5082, 5033);

	MalahC = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahD)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5079, 5033);

	MalahD = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahE)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5075, 5031);

	MalahE = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahF)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5075, 5024);

	MalahF = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahG)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5075, 5026);

	MalahG = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahH)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    WalkToMalah();

	MalahH = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahI)
	{
	if (GetTickCount() - Delay >= MalahInteractDelay)
	{
	if (MalahPathing)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Interacting With Malah");
	InteractMalah();
	}

	MalahI = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MalahInteractDelay)
	{
	if (MalahPathing)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Closing Interact");
	CloseInteract();
	}

	MalahJ = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryA && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Going To Town Entry");

	Walkto(5075, 5026);
	}

	EntryA = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryB && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5075, 5024);

	EntryB = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryC && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5075, 5031);

	EntryC = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryD && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5079, 5033);

	EntryD = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryE && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5082, 5033);

	EntryE = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryF && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
    	Walkto(5086, 5030);

	EntryF = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!EntryG && MalahI && MalahJ)
	{
	if (GetTickCount() - Delay >= MalahPathDelay)
	{
	if (MalahPathing)
	    Walkto(5090, 5026);

	EntryG = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckO && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Going To Waypoint");

	Walkto(5102, 5037);

	CheckO = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckP && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	GetReAsign(5102, 5037);
	Walkto(5103, 5041);

	CheckP = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckQ && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5103, 5041);

	CheckQ = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckR && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5104, 5045);

	CheckR = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckS && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5105, 5049);

	CheckS = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckT && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	GetReAsign(5105, 5049);
	Walkto(5106, 5053);

	CheckT = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckU && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5107, 5056);

	CheckU = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}
	
	if (!CheckV && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5109, 5061);

	CheckV = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckW && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	GetReAsign(5109, 5061);
	Walkto(5110, 5064);

	CheckW = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckX && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5112, 5068);

	CheckX = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckY && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	Walkto(5115, 5070);

	CheckY = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckZ && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	GetReAsign(5115, 5070);
	Walkto(5115, 5071);

	CheckZ = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualA && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= 400)
	{

	if (!FindMercUnit(pMe))
	{
		 PrintText(0,"ÿc9Avatar: ÿc0Mercenary Not Found");
		 MercPathing = true;
	     Walkto(5117, 5077);
	}
	else
	{
		 PrintText(0,"ÿc9Avatar: ÿc0Mercenary Found");
		 MercDelay = 0;
		 QualInteractDelay = 0;
	}

	QualA = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualB && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	{
	    Walkto(5118, 5084);
	}

	QualB = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualC && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5111, 5086);

	QualC = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualD && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
    	Walkto(5100, 5085);

	QualD = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualE && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5091, 5084);

	QualE = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualF && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5081, 5082);

	QualF = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualG && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
    	Walkto(5072, 5078);
	
	QualG = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualH && MalahJ && MalahI)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	{
     	WalkToQual();
	}
	
	QualH = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualI && MalahJ && MalahI && QualB)
	{
	if (GetTickCount() - Delay >= QualInteractDelay)
	{
	if (MercPathing)
	{
		PrintText(0,"ÿc9Avatar: ÿc0Interacting With Qual-Khek");
	    QualInteract();
	}
	
	QualI = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualJ && MalahJ && MalahI && QualI && QualB)
	{
	if (GetTickCount() - Delay >= QualInteractDelay)
	{
	if (MercPathing)
	{
		PrintText(0,"ÿc9Avatar: ÿc0Reviving Merc");
	    ReviveMerc();
	}
	
	QualJ = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualK && MalahJ && MalahI && QualI && QualJ && QualB)
	{
	if (GetTickCount() - Delay >= QualInteractDelay)
	{
	if (MercPathing)
	{
		PrintText(0,"ÿc9Avatar: ÿc0Closing Interact");
	    CloseInteract();
	}
	
	QualK = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualL && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	{
		PrintText(0,"ÿc9Avatar: ÿc0Going To Waypoint");
	    Walkto(5072, 5078);
	}

	QualL = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualM && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5081, 5082);
	
	QualM = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualN && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5091, 5084);
	
	QualN = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualO && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5100, 5085);
	
	QualO = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualP && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5111, 5086);
	
	QualP = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualQ && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5118, 5084);
	
	QualQ = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualR && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5117, 5077);
	
	QualR = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!QualS && MalahJ && MalahI && QualI && QualJ && QualK && QualB)
	{
	if (GetTickCount() - Delay >= MercDelay)
	{
	if (MercPathing)
	    Walkto(5115, 5071);
	
	QualS = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckAA && MalahJ && MalahI && QualS && QualB)
	{
	if (GetTickCount() - Delay >= 1400)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Taking Waypoint");
    
	TakeWp();
			
	CheckAA = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!DoPrecast && MalahJ && MalahI && QualS && QualB)
	{
	if (GetTickCount() - Delay >= 2400)
	{
    v_Precast = true; //Call Precast Script
			
	DoPrecast = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckBB && MalahJ && MalahI && QualS)
	{
	if (GetTickCount() - Delay >= 5400)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Going To Eldrich");

	Walkto(3766, 5098);

	CheckBB = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckCC && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	GetReAsign(3766, 5098);
	Walkto(3754, 5089);

	CheckCC = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckDD && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	GetReAsign(3754, 5089);
	Walkto(3741, 5080);

	CheckDD = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckEE && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	GetReAsign(3741, 5080);
	Walkto(3735, 5067);

	CheckEE = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckFF && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	GetReAsign(3735, 5067);
	Walkto(3739, 5064);
	
	CheckFF = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckGG && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Attacking Monsters");
	GetReAsign(3739, 5064);
	
	CheckGG = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckHH && CheckBB && CheckGG)
	{
	if (GetTickCount() - Delay >= 400)
	{

	if (GetTickCount() - AttackDelay >= 500)
		{
		LPUNITANY Unit = FindNearestUnit();

		if (Unit)
		{
		DWORD Distance = CalculateDistance(Unit->pPath->xPos, Unit->pPath->yPos, pMe->pPath->xPos, pMe->pPath->yPos);

		if (Unit && Distance <= 20)
		    AttackLeftMonster();
		else
			{
			PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 1");

			CheckHH = true;
	        Delay = NULL; 
	        Delay = GetTickCount();
	     	}
		}
		else
		{
			PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 1");

			CheckHH = true;
	        Delay = NULL; 
	        Delay = GetTickCount();
		}

		AttackDelay = GetTickCount();
		}
	}
	}

	if (!CheckINT && CheckHH && CheckBB)
	{
	if (GetTickCount() - Delay >= 5000)
	{
	Walkto(3726, 5061);

	CheckINT = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckINT2 && CheckHH && CheckINT && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	GetReAsign(3726, 5061);
	Walkto(3720, 5066);

	CheckINT2 = true;
	Delay = NULL; 
	Delay = GetTickCount();
	}
	}

	if (!CheckINT3 && CheckHH && CheckINT && CheckBB)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 2");

	GetReAsign(3720, 5066);

	CheckINT3 = true;
	Delay = NULL; 
	Delay = GetTickCount();

	EldrichComplete = true;
	}
	}

	if (!CheckA && EldrichComplete)
	{
	if (GetTickCount() - Delay >= 3000)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Going To Shenk");

	Walkto(3730, 5074);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckA = true;
	}
	}

	if (!CheckB && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 1");
	GetReAsign(3730, 5074);
	Walkto(3740, 5083);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckB = true;
	}
	}

	if (!CheckC && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 2");
	GetReAsign(3740, 5083);
	Walkto(3751, 5090);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckC = true;
	}
	}

	if (!CheckD && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 3");
	GetReAsign(3751, 5090);
	Walkto(3762, 5094);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckD = true;
	}
	}

	if (!CheckE && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 4");
	GetReAsign(3762, 5094);
	Walkto(3777, 5098);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckE = true;
	}
	}

	if (!CheckF && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 5");
	GetReAsign(3777, 5098);
	Walkto(3788, 5101);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckF = true;
	}
	}

	if (!CheckG && EldrichComplete && CheckA)
	{
	if (GetTickCount() - Delay >= 1500)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 6");
	GetReAsign(3788, 5101);
	Walkto(3803, 5105);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckG = true;
	}
	}

	if (!CheckH && EldrichComplete && CheckA && CheckG)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 7");
	GetReAsign(3803, 5105);
	Walkto(3815, 5106);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckH = true;
	}
	}

	if (!CheckI && EldrichComplete && CheckA && CheckG && CheckH)
	{
	if (GetTickCount() - Delay >= 1500)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 8");
	GetReAsign(3815, 5106);
	Walkto(3827, 5111);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckI = true;
	}
	}

	if (!CheckJ && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 9");
	GetReAsign(3827, 5111);
	Walkto(3838, 5117);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckJ = true;
	}
	}

	if (!CheckK && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 10");
	GetReAsign(3838, 5117);
	Walkto(3850, 5123);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckK = true;
	}
	}

	if (!CheckL && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 11");
	GetReAsign(3850, 5123);
	Walkto(3862, 5126);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckL = true;
	}
	}

	if (!CheckM && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 12");
	GetReAsign(3862, 5126);
	Walkto(3873, 5127);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckM = true;
	}
	}

	if (!CheckN && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 13");
	GetReAsign(3873, 5127);
	Walkto(3884, 5124);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckN = true;
	}
	}

	if (!CheckII && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	//PrintText(0,"ÿc9Avatar: ÿc0Walk 14");
	GetReAsign(3884, 5124);
	Walkto(3886, 5114);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckII = true;
	}
	}

	if (!CheckJJ && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Attacking Monsters");
	GetReAsign(3886, 5114);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckJJ = true;
	}
	}

	if (!CheckKK && EldrichComplete && CheckA && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 1000)
	{
	
	if (GetTickCount() - AttackDelay >= 500)
		{
		LPUNITANY Unit = FindNearestUnit();

		if (Unit)
		{
		DWORD Distance = CalculateDistance(Unit->pPath->xPos, Unit->pPath->yPos, pMe->pPath->xPos, pMe->pPath->yPos);

		if (Unit && Distance <= 30)
		    AttackLeftMonster();
		else
			{
			PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 1");

			CheckKK = true;
	        Delay = NULL; 
	        Delay = GetTickCount();
	     	}
		}
		else
		{
			PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 1");

			CheckKK = true;
	        Delay = NULL; 
	        Delay = GetTickCount();
		}

		AttackDelay = GetTickCount();
		}
	}
	}

	if (!CheckLL && EldrichComplete && CheckA && CheckKK && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 5000)
	{
	Walkto(3895, 5113);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckLL = true;
	}
	}

	if (!CheckMM && EldrichComplete && CheckA && CheckKK && CheckLL && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	GetReAsign(3895, 5113);
	Walkto(3902, 5114);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckMM = true;
	}
	}

	if (!CheckNN && EldrichComplete && CheckA && CheckKK && CheckLL && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 400)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Waiting To Pick Items 2");
	GetReAsign(3902, 5114);

	Delay = NULL; 
	Delay = GetTickCount();
	CheckNN = true;
	}
	}

	if (!CheckOO && EldrichComplete && CheckA && CheckKK && CheckLL && CheckG && CheckH && CheckI)
	{
	if (GetTickCount() - Delay >= 3000)
	{
	PrintText(0,"ÿc9Avatar: ÿc0Bot Sequence Terminated");
	ShenkComplete = true;

	Delay = NULL; 
	Delay = GetTickCount();
	CheckOO = true;
	}
	}

	if (MalahA && MalahB && MalahC && MalahD && MalahE && MalahF && MalahG && MalahH && MalahI && MalahJ 
		&& EntryA && EntryB && EntryC && EntryD && EntryE && EntryF && EntryG 
		&& QualA && QualB && QualC && QualD && QualE && QualF && QualG && QualH && QualI && QualJ && QualK
		&& QualL && QualM && QualN && QualO && QualP && QualQ && QualR && QualS
		&& CheckA && CheckB && CheckC && CheckD && CheckE && CheckF && CheckG && CheckH && CheckI
		&& CheckJ && CheckK && CheckL && CheckM && CheckN && CheckO && CheckP && CheckQ && CheckR && CheckS && CheckT 
		&& CheckU && CheckV && CheckW && CheckX && CheckY && CheckZ && CheckAA
		&& CheckBB && CheckCC && CheckDD && CheckEE && CheckFF && CheckGG && CheckHH && CheckINT && CheckINT2 && CheckINT3
		&& CheckII && CheckJJ && CheckKK && CheckLL && CheckMM && CheckNN && CheckOO && DoPrecast)
	{
	MalahPathing = false;
	MercPathing = false;
	EldrichComplete = false;
	ShenkComplete = false;
	MalahA = false;
	MalahB = false;
	MalahC = false;
	MalahD = false;
	MalahE = false;
	MalahF = false;
	MalahG = false;
	MalahH = false;
	MalahI = false;
	MalahJ = false;
	EntryA = false;
	EntryB = false;
	EntryC = false;
	EntryE = false;
	EntryF = false;
	EntryG = false;
	QualA = false;
	QualB = false;
	QualC = false;
	QualD = false;
	QualE = false;
	QualF = false;
	QualG = false;
	QualH = false;
	QualI = false;
	QualJ = false;
	QualK = false;
	QualL = false;
	QualM = false;
	QualN = false;
	QualO = false;
	QualP = false;
	QualQ = false;
	QualR = false;
	QualS = false;
	CheckA = false;
	CheckB = false;
	CheckC = false;
	CheckD = false;
	CheckE = false;
	CheckF = false;
	CheckG = false;
	CheckH = false;
	CheckI = false;
	CheckJ = false;
	CheckK = false;
	CheckL = false;
	CheckM = false;
	CheckN = false;
	CheckO = false;
	CheckP = false;
	CheckQ = false;
	CheckR = false;
	CheckS = false;
	CheckT = false;
	CheckU = false;
	CheckV = false;
	CheckW = false;
	CheckX = false;
	CheckY = false;
	CheckZ = false;
	CheckAA = false;
	CheckBB = false;
	CheckCC = false;
	CheckDD = false;
	CheckEE = false;
	CheckFF = false;
	CheckGG = false;
	CheckHH = false;
	CheckINT = false;
	CheckINT2 = false;
	CheckINT3 = false;
	CheckII = false;
	CheckJJ = false;
	CheckKK = false;
	CheckLL = false;
	CheckMM = false;
	CheckNN = false;
	CheckOO = false;
	DoPrecast = false;
	v_BotCounter = 0;
	Delay = NULL;
	MercDelay = 400;
	QualInteractDelay = 1200;
	MalahPathDelay = 400;
	MalahInteractDelay = 1500;

	v_GameAmount++;

	ResetPrecast();

	D2CLIENT_ExitGame();
	}

	return FALSE;
}

void ResetBot()
{
	MalahPathing = false;
	MercPathing = false;
	EldrichComplete = false;
	ShenkComplete = false;
	MalahA = false;
	MalahB = false;
	MalahC = false;
	MalahD = false;
	MalahE = false;
	MalahF = false;
	MalahG = false;
	MalahH = false;
	MalahI = false;
	MalahJ = false;
	EntryA = false;
	EntryB = false;
	EntryC = false;
	EntryE = false;
	EntryF = false;
	EntryG = false;
	QualA = false;
	QualB = false;
	QualC = false;
	QualD = false;
	QualE = false;
	QualF = false;
	QualG = false;
	QualH = false;
	QualI = false;
	QualJ = false;
	QualK = false;
	QualL = false;
	QualM = false;
	QualN = false;
	QualO = false;
	QualP = false;
	QualQ = false;
	QualR = false;
	QualS = false;
	CheckA = false;
	CheckB = false;
	CheckC = false;
	CheckD = false;
	CheckE = false;
	CheckF = false;
	CheckG = false;
	CheckH = false;
	CheckI = false;
	CheckJ = false;
	CheckK = false;
	CheckL = false;
	CheckM = false;
	CheckN = false;
	CheckO = false;
	CheckP = false;
	CheckQ = false;
	CheckR = false;
	CheckS = false;
	CheckT = false;
	CheckU = false;
	CheckV = false;
	CheckW = false;
	CheckX = false;
	CheckY = false;
	CheckZ = false;
	CheckAA = false;
	CheckBB = false;
	CheckCC = false;
	CheckDD = false;
	CheckEE = false;
	CheckFF = false;
	CheckGG = false;
	CheckHH = false;
	CheckINT = false;
	CheckINT2 = false;
	CheckINT3 = false;
	CheckII = false;
	CheckJJ = false;
	CheckKK = false;
	CheckLL = false;
	CheckMM = false;
	CheckNN = false;
	CheckOO = false;
	DoPrecast = false;
	v_BotCounter = 0;
	MercDelay = 400;
	QualInteractDelay = 1200;
	MalahPathDelay = 400;
	MalahInteractDelay = 1500;
	Delay = NULL;

	ResetPrecast();
}

void BotPickIt()
{
		if (v_Bot)
		{
		for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_ITEM)
			{
				if (v_NoTownPick && InTown(pMe))
					break;

				CHAR Code[4] = {0};

				GetItemCode(pUnit, Code, 3);

				DWORD Distance = CalculateDistance(pUnit->pItemPath->dwPosX, pUnit->pItemPath->dwPosY, pMe->pPath->xPos, pMe->pPath->yPos);

				//PrintText(0,"%s %d %d", Code, pUnit->pItemData->dwQuality, Distance); //Get Code

				if (Distance <= v_PickItDist)
				{
				if (GetTickCount() - v_LastPick >= v_PickDelay)
				{

				if (v_Flawless)
				{
				if (!_stricmp(Code, "glb")) /*Flawless Saphire*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glw")) /*Flawless Diamond*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gly")) /*Flawless Topaz*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glr")) /*Flawless Ruby*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glg")) /*Flawless Emerald*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);
				}

				if (!_stricmp(Code, "gzv")) /*Flawless Amethyst*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "skl")) /*Flawless Skull*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_Perfect)
				{
				if (!_stricmp(Code, "gpw")) /*Perfect Diamond*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpr")) /*Perfect Ruby*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpg")) /*Perfect Emerald*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpv")) /*Perfect Amethyst*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "skz")) /*Perfect Skull*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpy")) /*Perfect Topaz*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpb")) /*Perfect Saphire*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
						if (!_stricmp(Code, "jew")) /*Jewel*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Jewel");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

					if (pUnit->pItemData->dwQuality == 7)
					{
						if (!_stricmp(Code, "amu")) /*Unique Amu*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "uap")) /*Shako*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "ci3")) /*Griffon*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "uar")) /*Might Armor*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "ulc")) /*Arach*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}
						
						if (!_stricmp(Code, "urn")) /*Coa*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "usk")) /*Andariel*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "t51")) /*Unique Map 1*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "t52")) /*Unique Map 2*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}

						if (!_stricmp(Code, "rin")) /*Unique Ring*/
						{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
						}
					}

				if (v_FullJuv)
				{
				INT FRP = GetTotalBeltRejuvenation() + GetTotalInvRejuvenation(); //Belt + Inv

				if (FRP < v_RejuvPotCounter)
				{
				if (!_stricmp(Code, "rvl")) /*Full Rejuv*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Full Rejuv Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_SmallJuv)
				{
				INT SRP = GetTotalBeltRejuvenation() + GetTotalInvRejuvenation(); //Belt + Inv

				if (SRP < v_RejuvPotCounter)
				{
				if (!_stricmp(Code, "rvs")) /*Small Rejuv*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Small Rejuv Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_LowRunes) //El Eld Tir Nef Eth Ith Tal Ral Ort Thul Amn Sol
				{
				if (!_stricmp(Code, "r01")) /*El Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick El Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r02")) /*Eld Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Eld Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r03")) /*Tir Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Tir Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r04")) /*Nef Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Nef Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r05")) /*Eth Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Eth Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r06")) /*Ith Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ith Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r07")) /*Tal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Tal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r08")) /*Ral Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ral Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r09")) /*Ort Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ort Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r10")) /*Thul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Thul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r11")) /*Amn Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Amn Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r12")) /*Sol Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Sol Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_MiddleRunes) //Shael Dol Hel Io Lum Ko Fal Lem Pul Um Mal
				{
				if (!_stricmp(Code, "r13")) /*Shael Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Shael Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r14")) /*Dol Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Dol Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r15")) /*Hel Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Hel Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r16")) /*Io Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Io Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r17")) /*Lum Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lum Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r18")) /*Ko Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ko Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r19")) /*Fal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Fal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r20")) /*Lem Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lem Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r21")) /*Pul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Pul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r22")) /*Um Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Um Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r23")) /*Mal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Mal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (!_stricmp(Code, "r24")) /*Ist Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ist Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r25")) /*Gul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Gul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r26")) /*Vex Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Vex Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r27")) /*Ohm Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ohm Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r28")) /*Lo Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lo Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r29")) /*Sur Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Sur Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r30")) /*Ber Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ber Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r31")) /*Jah Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Jah Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r32")) /*Cham Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Cham Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r33")) /*Zod Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Zod Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				
				if (v_LifePot) //Pick Life Potion
				{

				INT HP = GetTotalBeltHealth() + GetTotalInvHealth(); //Belt + Inv
				
				if (HP < v_LifePotCounter)
				{
				if (!_stricmp(Code, "hp1")) /*Minor Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Minor Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp2")) /*Light Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Light Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp3")) /*Normal Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Normal Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp4")) /*Greater Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Greater Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp5")) /*Super Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Super Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_ManaPot) //Pick Mana Potion
				{

				INT MP = GetTotalBeltMana() + GetTotalInvMana(); //Belt + Inv

				if (MP < v_ManaPotCounter)
				{
				if (!_stricmp(Code, "mp1")) /*Minor Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Minor Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp2")) /*Light Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Light Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp3")) /*Normal Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Normal Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp4")) /*Greater Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Greater Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp5")) /*Super Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Super Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (!_stricmp(Code, "wss")) /*Worldstone Shard*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Worldstone Shard");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lbo")) /*Larzuk's Puzzle Box*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Larzuk's Puzzle Box");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lpp")) /*Larzuk's Puzzle Piece*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Larzuk's Puzzle Piece");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "scr")) /*Horadrim Scarab*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Horadrim Scarab");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "dcb")) /*Pure Demonic Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Pure Demonic Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "llm")) /*Lilith's Mirror*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lilith's Mirror");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lsv")) /*Vial*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Vial");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				
				if (!_stricmp(Code, "iws")) /*Catalyst Shard*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Catalyst Shard");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "rke")) /*Skeleton Key*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Skeleton Key");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
			}
			}
			}
	}
	}

void PickIt()
{
		if (v_PickIt)
		{
		for(LPROOM1 pRoom1 = pMe->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext)
		for(LPUNITANY pUnit = pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
			if (pUnit->dwType == UNIT_TYPE_ITEM)
			{
				if (v_NoTownPick && InTown(pMe))
					break;

				CHAR Code[4] = {0};

				GetItemCode(pUnit, Code, 3);

				DWORD Distance = CalculateDistance(pUnit->pItemPath->dwPosX, pUnit->pItemPath->dwPosY, pMe->pPath->xPos, pMe->pPath->yPos);

				//PrintText(0,"%s %d %d", Code, pUnit->pItemData->dwQuality, Distance); //Get Code

				if (Distance <= v_PickItDist)
				{
				if (GetTickCount() - v_LastPick >= v_PickDelay && v_PickIt)
				{

				if (v_Unique)
				{
					if (pUnit->pItemData->dwQuality == 7)
					{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Unique Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
					}
				}

				if (v_Set)
				{
					if (pUnit->pItemData->dwQuality == 5)
					{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Set Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
					}
				}

				if (v_Rare)
				{
					if (pUnit->pItemData->dwQuality == 6)
					{
						PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Rare Item");

						PickItem(pUnit->dwUnitId);

						v_LastPick = GetTickCount();
					}
				}

				if (v_Gold)
				{
				if (!_stricmp(Code, "gld")) /*Gold*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Gold");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_FullJuv)
				{
				INT FRP = GetTotalBeltRejuvenation() + GetTotalInvRejuvenation(); //Belt + Inv

				if (FRP < v_RejuvPotCounter)
				{
				if (!_stricmp(Code, "rvl")) /*Full Rejuv*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Full Rejuv Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_SmallJuv)
				{
				INT SRP = GetTotalBeltRejuvenation() + GetTotalInvRejuvenation(); //Belt + Inv

				if (SRP < v_RejuvPotCounter)
				{
				if (!_stricmp(Code, "rvs")) /*Small Rejuv*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Small Rejuv Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_LowRunes) //El Eld Tir Nef Eth Ith Tal Ral Ort Thul Amn Sol
				{
				if (!_stricmp(Code, "r01")) /*El Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick El Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r02")) /*Eld Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Eld Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r03")) /*Tir Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Tir Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r04")) /*Nef Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Nef Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r05")) /*Eth Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Eth Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r06")) /*Ith Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ith Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r07")) /*Tal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Tal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r08")) /*Ral Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ral Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r09")) /*Ort Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ort Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r10")) /*Thul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Thul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r11")) /*Amn Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Amn Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r12")) /*Sol Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Sol Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_MiddleRunes) //Shael Dol Hel Io Lum Ko Fal Lem Pul Um Mal
				{
				if (!_stricmp(Code, "r13")) /*Shael Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Shael Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r14")) /*Dol Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Dol Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r15")) /*Hel Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Hel Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r16")) /*Io Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Io Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r17")) /*Lum Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lum Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r18")) /*Ko Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ko Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r19")) /*Fal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Fal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r20")) /*Lem Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lem Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r21")) /*Pul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Pul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r22")) /*Um Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Um Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r23")) /*Mal Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Mal Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_HighRunes) //Ist Gul Vex Ohm Lo Sur Ber Jah Cham Zod
				{
				if (!_stricmp(Code, "r24")) /*Ist Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ist Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r25")) /*Gul Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Gul Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r26")) /*Vex Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Vex Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r27")) /*Ohm Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ohm Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r28")) /*Lo Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lo Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r29")) /*Sur Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Sur Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r30")) /*Ber Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Ber Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r31")) /*Jah Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Jah Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r32")) /*Cham Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Cham Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "r33")) /*Zod Rune*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Zod Rune");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_Keys) //Keys
				{
				if (!_stricmp(Code, "pk1")) /*Key Of Terror*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Key Of Terror");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "pk2")) /*Key Of Hatred*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Key Of Hatred");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "pk3")) /*Key Of Destruction*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Key Of Destruction");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				
				if (v_LifePot) //Pick Life Potion
				{

				INT HP = GetTotalBeltHealth() + GetTotalInvHealth(); //Belt + Inv
				
				if (HP < v_LifePotCounter)
				{
				if (!_stricmp(Code, "hp1")) /*Minor Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Minor Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp2")) /*Light Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Light Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp3")) /*Normal Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Normal Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp4")) /*Greater Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Greater Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "hp5")) /*Super Healing Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Super Healing Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_ManaPot) //Pick Mana Potion
				{

				INT MP = GetTotalBeltMana() + GetTotalInvMana(); //Belt + Inv

				if (MP < v_ManaPotCounter)
				{
				if (!_stricmp(Code, "mp1")) /*Minor Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Minor Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp2")) /*Light Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Light Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp3")) /*Normal Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Normal Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp4")) /*Greater Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Greater Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "mp5")) /*Super Mana Potion*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Super Mana Potion");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
				}

				if (v_Misc) //Pick Misc Items
				{

				if (!_stricmp(Code, "jew")) /*Jewel*/
				{
				PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Jewel");

				PickItem(pUnit->dwUnitId);

				v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "ceh")) /*Hatred Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Hatred Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "tes")) /*Suffering Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Suffering Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "bet")) /*Terror Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Terror Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "fed")) /*Destruction Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Destruction Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "cm1")) /*Small Charm*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Small Charm");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "cm2")) /*Large Charm*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Large Charm");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "cm3")) /*Grand Charm*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Grand Charm");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "wss")) /*Worldstone Shard*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Worldstone Shard");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lbo")) /*Larzuk's Puzzle Box*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Larzuk's Puzzle Box");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lpp")) /*Larzuk's Puzzle Piece*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Larzuk's Puzzle Piece");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "scr")) /*Horadrim Scarab*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Horadrim Scarab");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "dcb")) /*Pure Demonic Essence*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Pure Demonic Essence");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "llm")) /*Lilith's Mirror*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Lilith's Mirror");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "dcs")) /*Prime Evil Soul*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Prime Evil Soul");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "lsv")) /*Vial*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Vial");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "iws")) /*Catalyst Shard*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Catalyst Shard");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "rke")) /*Skeleton Key*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Skeleton Key");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_Flawless)
				{
				if (!_stricmp(Code, "glb")) /*Flawless Saphire*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glw")) /*Flawless Diamond*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gly")) /*Flawless Topaz*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glr")) /*Flawless Ruby*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "glg")) /*Flawless Emerald*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);
				}

				if (!_stricmp(Code, "gzv")) /*Flawless Amethyst*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "skl")) /*Flawless Skull*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Flawless Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}

				if (v_Perfect)
				{
				if (!_stricmp(Code, "gpw")) /*Perfect Diamond*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpr")) /*Perfect Ruby*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpg")) /*Perfect Emerald*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpv")) /*Perfect Amethyst*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "skz")) /*Perfect Skull*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpy")) /*Perfect Topaz*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}

				if (!_stricmp(Code, "gpb")) /*Perfect Saphire*/
				{
					PrintConsoleString("ÿc4Divin's PickIt: Trying To Pick Perfect Gem");

			        PickItem(pUnit->dwUnitId);

					v_LastPick = GetTickCount();
				}
				}
			}
			}
			}
	}
	}

DWORD __declspec(naked) __fastcall GetUnitSTUB(DWORD dwUnitId, DWORD dwUnitType)
{
	__asm
	{
		POP EAX;
		PUSH EDX;
		PUSH EAX;
		SHL EDX, 9;
		MOV EAX, D2CLIENT_GetUnitFromId_I;
		ADD EDX, EAX;
		MOV EAX, ECX;
		AND EAX, 0x7F;
		JMP D2CLIENT_GetUnitFromId_II;
	}
}

void PickItem(DWORD ItemId)
{
	LPBYTE Packet = new BYTE[13];
	Packet[0] = 0x16;
	*(LPDWORD)&Packet[1] = 0x04;
	Packet[2] = Packet[3] = Packet[4] = 0;
	*(LPDWORD)&Packet[5] = ItemId;
	 Packet[9] = Packet[10] = Packet[11] = Packet[12] = 0;
	D2NET_SendPacket(13, 0, Packet);
	delete [] Packet;
}

VOID PickItBox()
{
	if (v_PickItConfig)
	{
	ColorBox(249, 100, 385, 190, 216, 0, 2); //Console Box

	SpecialTextHook(381, 115, 3, 4, "PickIt Config");

	SpecialTextHook(256, 135, 3, 4, "Pick Gold = %s", v_Gold ? "Yes" : "No"); SpecialTextHook(456, 135, 3, 4, "Pick Distance = %d", v_PickItDist);

	SpecialTextHook(256, 151, 3, 4, "Pick Full Juv = %s", v_FullJuv ? "Yes" : "No"); SpecialTextHook(456, 151, 3, 4, "Pick Small Juv = %s", v_SmallJuv ? "Yes" : "No");

	SpecialTextHook(256, 167, 3, 4, "Pick Low Runes = %s", v_LowRunes ? "Yes" : "No"); SpecialTextHook(456, 167, 3, 4, "Pick Middle Runes = %s", v_MiddleRunes ? "Yes" : "No");

	SpecialTextHook(256, 183, 3, 4, "Pick High Runes = %s", v_HighRunes ? "Yes" : "No"); SpecialTextHook(456, 183, 3, 4, "Pick Keys = %s", v_Keys ? "Yes" : "No");

	SpecialTextHook(256, 199, 3, 4, "Pick Life Potion = %s", v_LifePot ? "Yes" : "No"); SpecialTextHook(456, 199, 3, 4, "Pick Mana Potion = %s", v_ManaPot ? "Yes" : "No");

	SpecialTextHook(256, 215, 3, 4, "Pick Misc = %s", v_Misc ? "Yes" : "No"); SpecialTextHook(456, 215, 3, 4, "Pick Unique = %s", v_Unique ? "Yes" : "No");

	SpecialTextHook(256, 231, 3, 4, "Pick Set = %s", v_Set ? "Yes" : "No"); SpecialTextHook(456, 231, 3, 4, "Pick Rare = %s", v_Rare ? "Yes" : "No");

	SpecialTextHook(256, 247, 3, 4, "Pick Flaw Gem = %s", v_Flawless ? "Yes" : "No"); SpecialTextHook(456, 247, 3, 4, "Pick Perf Gem = %s", v_Perfect ? "Yes" : "No");

	SpecialTextHook(256, 263, 3, 4, "PickIt Delay = %d", v_PickDelay); SpecialTextHook(456, 263, 3, 4, "Rejuv Counter = %d", v_RejuvPotCounter);

	SpecialTextHook(256, 279, 3, 4, "Life Counter = %d", v_LifePotCounter); SpecialTextHook(456, 279, 3, 4, "Mana Counter = %d", v_ManaPotCounter);

	if (GetTickCount() - v_LastSet >= 500)
	        {
		            //Set 1

					if (MouseX >= 260 && MouseX <= 350)
						if (MouseY >= 121 && MouseY <= 134)
							v_Gold = !v_Gold;

					if (MouseX >= 260 && MouseX <= 366)
						if (MouseY >= 139 && MouseY <= 151)
							v_FullJuv = !v_FullJuv;

					if (MouseX >= 260 && MouseX <= 385)
						if (MouseY >= 156 && MouseY <= 167)
							v_LowRunes = !v_LowRunes;

					if (MouseX >= 260 && MouseX <= 390)
						if (MouseY >= 171 && MouseY <= 181)
							v_HighRunes = !v_HighRunes;

					if (MouseX >= 260 && MouseX <= 384)
						if (MouseY >= 187 && MouseY <= 197)
							v_LifePot = !v_LifePot;

					if (MouseX >= 260 && MouseX <= 351)
						if (MouseY >= 203 && MouseY <= 214)
							v_Misc = !v_Misc;

					if (MouseX >= 260 && MouseX <= 342)
						if (MouseY >= 220 && MouseY <= 230)
							v_Set = !v_Set;

					if (MouseX >= 260 && MouseX <= 380)
						if (MouseY >= 234 && MouseY <= 246)
							v_Flawless = !v_Flawless;

					if (MouseX >= 260 && MouseX <= 364)
						if (MouseY >= 250 && MouseY <= 263)
						{
							if (v_PickDelay == 400)
								v_PickDelay = 200;
							else
								v_PickDelay = 400;
						}
						
					if (MouseX >= 260 && MouseX <= 362)
						if (MouseY >= 267 && MouseY <= 279)
						{
							if (v_LifePotCounter == 10)
								v_LifePotCounter = 20;
							else
								v_LifePotCounter = 10;
						}

					//Set 2

					if (MouseX >= 460 && MouseX <= 567)
						if (MouseY >= 121 && MouseY <= 134)
						{
							if (v_PickItDist == 20)
								v_PickItDist = 5;
							else
								v_PickItDist = 20;
						}

					if (MouseX >= 460 && MouseX <= 573)
						if (MouseY >= 139 && MouseY <= 151)
							v_SmallJuv = !v_SmallJuv;

					if (MouseX >= 460 && MouseX <= 600)
						if (MouseY >= 156 && MouseY <= 167)
							v_MiddleRunes = !v_MiddleRunes;

					if (MouseX >= 460 && MouseX <= 551)
						if (MouseY >= 171 && MouseY <= 181)
							v_Keys = !v_Keys;

					if (MouseX >= 460 && MouseX <= 593)
						if (MouseY >= 187 && MouseY <= 197)
							v_ManaPot = !v_ManaPot;

					if (MouseX >= 460 && MouseX <= 562)
						if (MouseY >= 203 && MouseY <= 214)
							v_Unique = !v_Unique;

					if (MouseX >= 460 && MouseX <= 550)
						if (MouseY >= 220 && MouseY <= 230)
							v_Rare = !v_Rare;

					if (MouseX >= 460 && MouseX <= 578)
						if (MouseY >= 234 && MouseY <= 246)
							v_Perfect = !v_Perfect;

					if (MouseX >= 460 && MouseX <= 571)
						if (MouseY >= 250 && MouseY <= 263)
						{
							if (v_RejuvPotCounter == 10)
								v_RejuvPotCounter = 20;
							else
								v_RejuvPotCounter = 10;
						}
						
					if (MouseX >= 460 && MouseX <= 573)
						if (MouseY >= 267 && MouseY <= 279)
						{
							if (v_ManaPotCounter == 10)
								v_ManaPotCounter = 20;
							else
								v_ManaPotCounter = 10;
						}

					v_LastSet = GetTickCount();
	}
}
}