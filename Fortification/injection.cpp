/*_____          _   _  __ _           _   _             
 |  ___|__  _ __| |_(_)/ _(_) ___ __ _| |_(_) ___  _ __  
 | |_ / _ \| '__| __| | |_| |/ __/ _` | __| |/ _ \| '_ \ 
 |  _| (_) | |  | |_| |  _| | (_| (_| | |_| | (_) | | | |
 |_|  \___/|_|   \__|_|_| |_|\___\__,_|\__|_|\___/|_| |_|

For Project Diablo 2

Software Created By Divin (April 2023)
*/

#define _VARS
#include "injection.h"
char szModulePath[MAX_PATH];//={0};
WNDPROC oldWNDPROC;
HANDLE TESTHANDLE;

BOOL RemovePEHeader(HMODULE DLL)
{
	PIMAGE_DOS_HEADER DOSHD = (PIMAGE_DOS_HEADER)(DLL);
	PIMAGE_NT_HEADERS NTHD;	

	if (DOSHD->e_magic == IMAGE_DOS_SIGNATURE)
	{
		NTHD = (PIMAGE_NT_HEADERS)((DWORD)DOSHD + DOSHD->e_lfanew);

		if (NTHD->Signature == IMAGE_NT_SIGNATURE)
		{
			DWORD OldProtect;
			VirtualProtect((LPVOID)NTHD, sizeof(IMAGE_NT_HEADERS), PAGE_READWRITE, &OldProtect);
			::memset(NTHD, NULL, sizeof(IMAGE_NT_HEADERS));

			VirtualProtect((LPVOID)NTHD, sizeof(IMAGE_NT_HEADERS), OldProtect, &OldProtect);
			VirtualProtect((LPVOID)DOSHD, sizeof(IMAGE_DOS_HEADER), PAGE_READWRITE, &OldProtect);

			::memset(DOSHD, NULL, sizeof(IMAGE_DOS_HEADER));
			VirtualProtect((LPVOID)DOSHD, sizeof(IMAGE_DOS_HEADER), OldProtect, &OldProtect);
			return TRUE;
		}
	}
	
	return FALSE;
}

const int X = 0;
const int Y = 1;

void click(const int* pos)
{
	HWND d2 = FindWindow(NULL, "Diablo II"); //D2GFX_GetHwnd(); 

	SendMessage(d2, WM_MOUSEMOVE, 0, MAKELPARAM(pos[X], pos[Y]));
	SendMessage(d2, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos[X], pos[Y]));
	SendMessage(d2, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pos[X], pos[Y]));
}

void specialclick(const int* pos)
{
	HWND d2 = FindWindow(NULL, "Diablo II"); //D2GFX_GetHwnd(); 

	SendMessage(d2, WM_MOUSEMOVE, 0, MAKELPARAM(pos[X], pos[Y]));
	SendMessage(d2, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos[X], pos[Y]));
	SendMessage(d2, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pos[X], pos[Y]));
}

int InLine = 0;

DWORD WINAPI TestThread(LPVOID P) 
{
	while (true)
	{
		SleepEx(1500, true);

		if (!GameReady())
		{
			SleepEx(5000, true);
		
			HWND d2 = FindWindow(NULL, "Diablo II"); 

			if (d2 && v_Bot && !GameReady())
			{

			 if (v_GameAmount >= v_MaxGameAmount)
			 {
				  char Buffer[1024];
				  sprintf(Buffer,"You Ran %d Games: The Bot Is Now Stopped For Security Reason (Wait 24 Hours)", v_MaxGameAmount);
				  MessageBox(NULL,Buffer,"Fortification", MB_SYSTEMMODAL);
				  
				  v_Bot = false;

				  v_GameAmount = 0;
			 }

			 if (v_Bot)
			 {
			 InLine++;

             RECT rect = {0};
             GetWindowRect(d2, &rect);

             SetForegroundWindow(d2);
             SetActiveWindow(d2);
             SetFocus(d2);

			 Sleep(300);
			 SetCursorPos(rect.right - 100, rect.bottom - 145);
		     click(JOIN);

             Sleep(300);
             SetCursorPos(rect.right - 200, rect.bottom - 145);
			 click(CREATE);

			 Sleep(1000);
			 SetCursorPos(rect.right - 200, rect.bottom - 180);
			 click(CREATE_GAME);

			 if (InLine >= 3)
			 {
			 Sleep(1000);
			 SetCursorPos(rect.right - 310, rect.bottom - 180);
			 click(CANCEL);
			 InLine = 0;
			 }
			 }
			}
		}
		else
		{
			if (InLine >= 1)
				InLine = 0;
		}
	}

	return true;
}

DWORD random (int low, int high) {
    if (low > high) return high;
    return low + (rand() % (high - low + 1));
}

VOID SetVars()
{     
	    //Get Max Game
	    srand(time(0));
		v_MaxGameAmount = random(60,80);

	    //Hardcoded

	    v_GUI = TRUE;
		v_Maphack = TRUE;
	    v_FullLightRadius = TRUE;
		v_ConsoleDelayB = 20000;
		v_LastFC = 5000;
		v_LastMana = 5000;
		v_LastJuv = 5000;
		v_LastLife = 5000;
		v_LastPrecast = 5000;
		v_LastTP = 5000;
		v_LastPick = 5000;
		v_LastSet = 5000;
		v_BotCounter = 0;
		v_GameAmount = 0;

		//Config

		K_ToggleGUI = 46;

		v_PrevButton = 100;
		v_NextButton = 97;
		v_WaypointButton = 99;
		v_OtherButton = 98;

		v_TownLife = 30;
		v_ExitLife = 0;
		K_DefineTownKey = 69;

		K_QuickLeft1 = 53;
		K_QuickLeft2 = 54;

		v_AutoManaPercent = 30;
		v_AutoLifePercent = 90;
		v_AutoRejuvPercent = 50;

		v_PickIt = 1;
		v_PickDelay = 200;
		K_PickItToggle = 80;
		v_PickItDist = 20;
		v_NoTownPick = 1;
		v_Gold = 0;
		v_FullJuv = 1;
		v_SmallJuv = 1;
		v_LowRunes = 1;
		v_MiddleRunes = 1;
		v_HighRunes = 1;
		v_Keys = 1;
		v_LifePot = 1;
		v_ManaPot = 1;
		v_Misc = 1;
		v_Unique = 1;
		v_Set = 1;
		v_Rare = 0;
		v_Flawless = 1;
		v_Perfect = 1;
		v_ManaPotCounter = 10;
		v_LifePotCounter = 10;
		v_RejuvPotCounter = 10;
}

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved) 
{
	if(dwReason==DLL_PROCESS_ATTACH) 
	{
		RemovePEHeader(hDll); //Stealth
		SetVars();

		DefineOffsets();

		oldWNDPROC = NULL;
		if(D2GFX_GetHwnd())//only set windowhook when we can find d2's hwnd
			oldWNDPROC = (WNDPROC)SetWindowLongPtr(D2GFX_GetHwnd(), GWL_WNDPROC, (LONG)GameEventHandler);//set hook (for detecting keypresses)

		Authentication(); /*HWID Check*/

		InstallPatchs();

		if (GameReady() && v_Authed) /*Authentication Check*/
		{
			v_Reveal = new Reveal;

			PrintText(8, "Thanks For Using Fortification! Got Any Questions? Contact Divin On Discord: blakadiv"); 
			
		    PrintConsoleString("ÿc4Welcome To Fortification Unleashed Created By Divin For Project Diablo 2");

			TESTHANDLE = CreateThread(0,0,TestThread,0,0,0);
            if (TESTHANDLE)
			{
			}
		}

	    if (!v_Authed)
		{
			PrintText(1, "Your Hardware ID: %d (Send This Code To Divin On Discord: blakadiv)", v_Serial);
		}
	}

	if(dwReason==DLL_PROCESS_DETACH) {
		SetWindowLongPtr(D2GFX_GetHwnd(),GWL_WNDPROC,(LONG)oldWNDPROC); //remove the hook we set at the start of the program

		if(TESTHANDLE && TESTHANDLE != INVALID_HANDLE_VALUE)
		{
			TerminateThread(TESTHANDLE, 0);
		    CloseHandle(TESTHANDLE);
		}

        RemovePatchs();
	}

	return true;
}

/*Keep Tracks Of Authed Users

Name: Divin, HWID: 330393, Date: 4/18/2023
Name: Althorzin, HWID: 151923, Date: 4/18/2023
Name: Vitoxin, HWID: 148705, Date: 4/20/2023
Name: Schorni, HWID: 423367, Date: 4/24/2023
Name: Fear, HWID: 343794, Date: 4/24/2023
Name: Primension, HWID: 1264, Date: 4/25/2023
Name: Sali, HWID: 47028, Date: 4/25/2023
Name: Leafzer, HWID: 20630, Date: 4/26/2023
Name: Harley, HWID: 90837, Date: 4/26/2023
Name: Erich, HWID: 216278, Date: 4/27/2023
Name: Minotaur, HWID: 305389, Date: 4/27/2023
Name: Karamelov, HWID: 211807, Date: 4/28/2023
Name: Taubut, HWID: 322313, Date: 4/28/2023
Name: Corea, HWID: 188612, Date: 4/28/2023
Name: Patrick, HWID: 108033, Date: 4/28/2023
Name: Lanxes, HWID: 51857, Date: 4/28/2023
Name: Jimmy, HWID: 52681, Date: 4/28/2023
Name: Jazzy, HWID: 286773, Date: 4/28/2023
Name: Ziptie, HWID: 145761, Date: 4/28/2023
Name: Kev, HWID: 136800, Date: 4/28/2023
Name: Chinese, HWID: 299702, Date: 4/29/2023
Name: Jec, HWID: 394037, Date: 4/29/2023
Name: Thy, HWID: 243084, Date: 4/29/2023
Name: Lord, HWID: 259553, Date: 4/29/2023
Name: Abwhorent, HWID: 141350, Date: 4/29/2023
Name: Crai, HWID: 323208, Date: 4/29/2023
Name: Doom, HWID: 88452, Date: 4/29/2023
Name: Jarred, HWID: 81612, Date: 4/29/2023
Name: Heatox, HWID: 125536, Date: 4/30/2023
Name: Tomtom, HWID: 325989, Date: 4/30/2023
Name: Demodius, HWID: 70790, Date: 4/30/2023
Name: Iso, HWID: 7940, Date: 4/30/2023
Name: Haggis, HWID: 4551, Date: 5/1/2023
Name: Gmack, HWID: 366158, Date: 5/2/2023
Name: Patrick2, HWID: 380099, Date: 5/6/2023
Name: Matti, HWID: 265676, Date: 5/8/2023
Name: Tim, HWID: 279301, Date: 5/14/2023
Name: Tigrarius, HWID: 379615, Date: 5/16/2023
Name: Quicie, HWID: 74534, Date: 5/17/2023
Name: Neddles, HWID: 268465, Date: 5/21/2023
Name: Hippo, HWID: 262751, Date: 5/29/2023
Name: Lfcsie, HWID: 134865, Date: 5/29/2023
Name: Xexon, HWID: 272354, Date: 5/30/2023
Name: Raveal, HWID: 218517, Date: 5/31/2023
Name: Many, HWID: 4564, Date: 6/1/2023
Name: Mauka, HWID: 78318, Date: 6/1/2023
Name: DivinNew, HWID: 365991, Date: 7/22/2023
Name: Zefir, HWID: 347064, Date: 7/25/2023
*/

DWORD DivinHWID = 330393;
DWORD AlthorzinHWID = 151923;
DWORD VitoxinHWID = 148705;
DWORD SchorniHWID = 423367;
DWORD FearHWID = 343794;
DWORD PrimensionHWID = 1264;
DWORD SaliHWID = 47028;
DWORD LeafzerHWID = 20630;
DWORD HarleyHWID = 90837;
DWORD ErichHWID = 216278;
DWORD MinotorHWID = 305389;
DWORD KaramelovHWID = 211807;
DWORD TaubutHWID = 322313;
DWORD CoreaHWID = 188612;
DWORD PatrickHWID = 108033;
DWORD LanxesHWID = 51857;
DWORD JimmyHWID = 52681;
DWORD JazzyHWID = 286773;
DWORD ZiptieHWID = 145761;
DWORD KevHWID = 136800;
DWORD ChineseHWID = 299702;
DWORD JecHWID = 394037;
DWORD ThyHWID = 243084;
DWORD LordHWID = 259553;
DWORD AbwhorentHWID = 141350;
DWORD CraiHWID = 323208;
DWORD DoomHWID = 88452;
DWORD JarredHWID = 81612;
DWORD HeatoxHWID = 125536;
DWORD TomtomHWID = 325989;
DWORD DemodiusHWID = 70790;
DWORD IsoHWID = 7940;
DWORD HaggisHWID = 4551;
DWORD GmackHWID = 366158;
DWORD Patrick2HWID = 380099;
DWORD MattiHWID = 265676;
DWORD TimHWID = 279301;
DWORD TigrariusHWID = 379615;
DWORD QuicieHWID = 74534;
DWORD NeddlesHWID = 268465;
DWORD Neddles2HWID = 312317;
DWORD Schorni2HWID = 174718;
DWORD HippoHWID = 262751;
DWORD LfcsieHWID = 134865;
DWORD XexonHWID = 272354;
DWORD RavealHWID = 218517;
DWORD ManyHWID = 4564;
DWORD MaukaHWID = 78318;
DWORD DivinNewHWID = 365991;
DWORD ZefirHWID = 347064;

bool Authentication()
{
	v_Authed = true;
	
	/*GetVolumeInformation API Used To Grab Specific Hardware ID*/
	UCHAR szFileSys[255], szVolNameBuff[255]; DWORD dwMFL, dwSysFlags, dwErrorCode;
    GetVolumeInformation("C:\\", (LPTSTR)szVolNameBuff, 255, &dwErrorCode, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

	/*ByPass Negative HWID Values And Reduce Size*/
	v_Serial = dwErrorCode / 10002;

	/*Adds User Here*/

	if (DivinHWID == v_Serial)
		v_Authed = true;

	if (AlthorzinHWID == v_Serial)
		v_Authed = true;

	if (VitoxinHWID == v_Serial)
		v_Authed = true;

	if (SchorniHWID == v_Serial)
		v_Authed = true;

	if (FearHWID == v_Serial)
		v_Authed = true;

	if (PrimensionHWID == v_Serial)
		v_Authed = true;

	if (SaliHWID == v_Serial)
		v_Authed = true;

	if (LeafzerHWID == v_Serial)
		v_Authed = true;

	if (HarleyHWID == v_Serial)
		v_Authed = true;
	
	if (ErichHWID == v_Serial)
		v_Authed = true;

	if (MinotorHWID == v_Serial)
		v_Authed = true;

	if (KaramelovHWID == v_Serial)
		v_Authed = true;

	if (TaubutHWID == v_Serial)
		v_Authed = true;

	if (CoreaHWID == v_Serial)
		v_Authed = true;

	if (PatrickHWID == v_Serial)
		v_Authed = true;

	if (LanxesHWID == v_Serial)
		v_Authed = true;

	if (JimmyHWID == v_Serial)
		v_Authed = true;

	if (JazzyHWID == v_Serial)
		v_Authed = true;

	if (ZiptieHWID == v_Serial)
		v_Authed = true;

	if (KevHWID == v_Serial)
		v_Authed = true;
	
	if (ChineseHWID == v_Serial)
		v_Authed = true;

	if (JecHWID == v_Serial)
		v_Authed = true;

	if (ThyHWID == v_Serial)
		v_Authed = true;

	if (LordHWID == v_Serial)
		v_Authed = true;

	if (AbwhorentHWID == v_Serial)
		v_Authed = true;

	if (CraiHWID == v_Serial)
		v_Authed = true;

	if (DoomHWID == v_Serial)
		v_Authed = true;

	if (JarredHWID == v_Serial)
		v_Authed = true;

	if (HeatoxHWID == v_Serial)
		v_Authed = true;

	if (TomtomHWID == v_Serial)
		v_Authed = true;

	if (DemodiusHWID == v_Serial)
		v_Authed = true;

	if (IsoHWID == v_Serial)
		v_Authed = true;

	if (HaggisHWID == v_Serial)
		v_Authed = true;

	if (GmackHWID == v_Serial)
		v_Authed = true;

	if (Patrick2HWID == v_Serial)
		v_Authed = true;

	if (MattiHWID == v_Serial)
		v_Authed = true;

	if (TimHWID == v_Serial)
		v_Authed = true;

	if (TigrariusHWID == v_Serial)
		v_Authed = true;

	if (QuicieHWID == v_Serial)
		v_Authed = true;

	if (NeddlesHWID == v_Serial)
		v_Authed = true;

	if (Neddles2HWID == v_Serial)
		v_Authed = true;

	if (Schorni2HWID == v_Serial)
		v_Authed = true;

	if (HippoHWID == v_Serial)
		v_Authed = true;

	if (LfcsieHWID == v_Serial)
		v_Authed = true;

	if (XexonHWID == v_Serial)
		v_Authed = true;

	if (RavealHWID == v_Serial)
		v_Authed = true;

	if (ManyHWID == v_Serial)
		v_Authed = true;

	if (MaukaHWID == v_Serial)
		v_Authed = true;
	
	if (DivinNewHWID == v_Serial)
		v_Authed = true;

	if (ZefirHWID == v_Serial)
		v_Authed = true;

	return false;
}
