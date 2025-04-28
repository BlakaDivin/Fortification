#ifdef _VARS

#define ARRAY(Type, Name)		CArrayEx<Type, Type> v_##Name;
#define KEY(Name)				INT K_##Name;
#define TOGGLE(Name)			BOOL v_##Name; INT K_##Name;
#define VAR(Type, Name)			Type v##_##Name;

#else

#define ARRAY(Type, Name)		extern CArrayEx<Type, Type> v_##Name;
#define KEY(Name)				extern INT K_##Name;
#define TOGGLE(Name)			extern BOOL v_##Name; extern INT K_##Name;
#define VAR(Type, Name)			extern Type v_##Name;

#endif

VAR(bool, Register)
VAR(bool, Message)
VAR(char, ConsoleMessage[2048])
VAR(int, ConsoleDelayA)
VAR(int, ConsoleDelayB)
VAR(BOOL, FullLightRadius)
VAR(BOOL, TP)
VAR(DWORD, TownLife)
VAR(BOOL, LastTP)
VAR(DWORD, ExitLife)
VAR(DWORD, LastFC)
KEY(DefineTownKey)
VAR(BOOL, Authed)
VAR(DWORD, Serial)
VAR(DWORD, LastMana)
VAR(DWORD, AutoManaPercent)
VAR(DWORD, LastJuv)
VAR(DWORD, AutoRejuvPercent)
VAR(DWORD, LastLife)
VAR(DWORD, AutoLifePercent)
VAR(BOOL, ConfigBox)
KEY(ShowConfigBox)
VAR(DWORD, LastBox)
KEY(QuickLeft1)
KEY(QuickLeft2)
VAR(BOOL, PickIt)
VAR(BOOL, Gold)
VAR(BOOL, FullJuv)
VAR(BOOL, SmallJuv)
VAR(BOOL, Keys)
VAR(BOOL, LowRunes)
VAR(BOOL, MiddleRunes)
VAR(BOOL, HighRunes)
KEY(PickItToggle)
VAR(DWORD, PickDelay)
VAR(BOOL, LifePot)
VAR(BOOL, ManaPot)
VAR(BOOL, Misc)
VAR(BOOL, Unique)
VAR(BOOL, Set)
VAR(BOOL, Rare)
VAR(BOOL, NoTownPick)
VAR(BOOL, Flawless)
VAR(BOOL, Perfect)
VAR(DWORD, LastPick)
VAR(BOOL, GUI)
KEY(ToggleGUI)
VAR(DWORD, PickItDist)
VAR(int, NextButton)
VAR(int, PrevButton)
VAR(int, OtherButton)
VAR(int, WaypointButton)
VAR(BOOL, PickItConfig)
VAR(DWORD, LastSet)
VAR(DWORD, LastPrecast)
VAR(MYAUTOMAPLAYERMAN, MyAutoMapLayer[100])
VAR(Reveal *, Reveal)
VAR(INT, LifePotCounter)
VAR(INT, ManaPotCounter)
VAR(INT, RejuvPotCounter)
VAR(BOOL, Maphack)
VAR(BOOL, Bot)
VAR(DWORD, BotCounter)
VAR(BOOL, DelayedChicken)
VAR(BOOL, Precast)
VAR(DWORD, GameAmount)
VAR(DWORD, MaxGameAmount)