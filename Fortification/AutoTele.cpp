#include "injection.h"

int waypoints[] = {119,157,156,323,288,402,324,237,238,398,496,511,494};
int CSID = 0;
int CS[] = {392, 394, 396, 255};

int Try;
POINT End;
DWORD _timer, _timer2, _InteractTimer;
bool SetInteract, SetTele, CastTele, TeleActive;
bool DoInteract;
DWORD InteractId;
DWORD InteractType;
Room2* InteractRoom;
DWORD LastArea;
CArrayEx <POINT, POINT> TPath;
POINT Vectors[4];

Vector vVector[] = {
	{0}, {0}, {0}, {0},										//0x0
	{0}, {0}, {0}, {0},										//0x01

	{EXIT, MAP_A1_COLD_PLAINS}, 
	{EXIT, MAP_A1_DEN_OF_EVIL}, 
	{0}, 
	{EXIT, MAP_A1_ROGUE_ENCAMPMENT},						//0x02

	{EXIT, MAP_A1_STONY_FIELD},								//0x3
	{EXIT, MAP_A1_BURIAL_GROUNDS},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_BLOOD_MOOR},

	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},
	{UNIT_OBJECT, 22},										//0x4
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_COLD_PLAINS},

	{EXIT, MAP_A1_BLACK_MARSH},								//0x5
	{UNIT_OBJECT, 30},										
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},

	{EXIT, MAP_A1_TAMOE_HIGHLAND},							//0x6
	{EXIT, MAP_A1_FORGOTTEN_TOWER},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_DARK_WOOD},

	{EXIT, MAP_A1_MONASTERY_GATE},							//0x7
	{EXIT, MAP_A1_PIT_LEVEL_1},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{0},													//0x08
	{0}, 
	{0}, 
	{EXIT, MAP_A1_BLOOD_MOOR},								

	{EXIT, MAP_A1_CAVE_LEVEL_2},							//0x9
	{UNIT_MONSTER, 736},
	{0},
	{EXIT, MAP_A1_COLD_PLAINS},

	{EXIT, MAP_A1_DARK_WOOD},								//0xa
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_2},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_STONY_FIELD},

	{EXIT, MAP_A1_HOLE_LEVEL_2},							//0xb
	{EXIT, MAP_A1_HOLE_LEVEL_2},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{EXIT, MAP_A1_PIT_LEVEL_2},								//0xc
	{EXIT, MAP_A1_PIT_LEVEL_2},
	{0},
	{EXIT, MAP_A1_TAMOE_HIGHLAND},

	{UNIT_OBJECT, 397},										//0xd
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_CAVE_LEVEL_1},

	{UNIT_OBJECT, 397},										//0xe
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},


	{UNIT_OBJECT, 397},										//0xf
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_HOLE_LEVEL_1},

	{UNIT_OBJECT, 397},										//0x10
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_PIT_LEVEL_1},

	{EXIT, MAP_A1_CRYPT}, 
	{EXIT, MAP_A1_MAUSOLEUM}, 
	{UNIT_MONSTER, 805}, 
	{EXIT, MAP_A1_COLD_PLAINS},								//0x11

	{UNIT_OBJECT, 397}, 
	{UNIT_OBJECT, 397}, 
	{0}, 
	{EXIT, MAP_A1_BURIAL_GROUNDS},							//0x12

	{UNIT_OBJECT, 397}, 
	{UNIT_OBJECT, 397}, 
	{0}, 
	{EXIT, MAP_A1_BURIAL_GROUNDS},							//0x13

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},					//0x14
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},					//0x15
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},
	{0},
	{EXIT, MAP_A1_FORGOTTEN_TOWER},


	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},					//0x16
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},


	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},					//0x17
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},


	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5},					//0x18
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},


	{UNIT_MONSTER, 740},									//0x19
	{UNIT_MONSTER, 740},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},

	{EXIT, MAP_A1_OUTER_CLOISTER},							//0x1a
	{EXIT, MAP_A1_OUTER_CLOISTER},
	{0},
	{XY, 15141, 5091, MAP_A1_TAMOE_HIGHLAND},


	{EXIT, MAP_A1_BARRACKS},								//0x1b
	{EXIT, MAP_A1_BARRACKS},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_MONASTERY_GATE},


	{EXIT, MAP_A1_JAIL_LEVEL_1},							//0x1c
	{UNIT_OBJECT, 108},
	{0},
	{EXIT, MAP_A1_OUTER_CLOISTER},


	{EXIT, MAP_A1_JAIL_LEVEL_2},							//0x1d
	{EXIT, MAP_A1_JAIL_LEVEL_2},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_BARRACKS},


	{EXIT, MAP_A1_JAIL_LEVEL_3},							//0x1e
	{EXIT, MAP_A1_JAIL_LEVEL_3},
	{0},
	{EXIT, MAP_A1_JAIL_LEVEL_1},


	{EXIT, MAP_A1_INNER_CLOISTER},							//0x1f
	{EXIT, MAP_A1_INNER_CLOISTER},
	{0},
	{EXIT, MAP_A1_JAIL_LEVEL_2},


	{EXIT, MAP_A1_CATHEDRAL},								//0x20
	{EXIT, MAP_A1_CATHEDRAL},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_JAIL_LEVEL_3},


	{EXIT, MAP_A1_CATACOMBS_LEVEL_1},						//0x21
	{EXIT, MAP_A1_CATACOMBS_LEVEL_1},
	{0},
	{EXIT, MAP_A1_INNER_CLOISTER},


	{EXIT, MAP_A1_CATACOMBS_LEVEL_2},						//0x22
	{EXIT, MAP_A1_CATACOMBS_LEVEL_2},
	{0},
	{EXIT, MAP_A1_CATHEDRAL},


	{EXIT, MAP_A1_CATACOMBS_LEVEL_3},						//0x23
	{EXIT, MAP_A1_CATACOMBS_LEVEL_3},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_1},


	{EXIT, MAP_A1_CATACOMBS_LEVEL_4},						//0x24
	{EXIT, MAP_A1_CATACOMBS_LEVEL_4},
	{0},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_2},


	{XY, 22533, 9556},										//0x25
	{XY, 22563, 9556},
	{0},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_3},

	{UNIT_OBJECT, 268}, 
	{UNIT_OBJECT, 26}, 
	{0}, 
	{XY, 25173, 5083},										//0x26 -> tristram

	{0}, {0}, {0}, {0},										//0x27 -> cow lvl


	////////////////////////////////////////////////////////////////////
	// Act 2
	////////////////////////////////////////////////////////////////////

	{0}, {0}, {0}, {0},										//0x28 -> lut gholein

	{EXIT, MAP_A2_DRY_HILLS},								//0x29
	{EXIT, MAP_A2_DRY_HILLS},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_FAR_OASIS},								//0x2a
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_ROCKY_WASTE},

	{EXIT, MAP_A2_LOST_CITY},								//0x2b
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_DRY_HILLS},

	{EXIT, MAP_A2_VALLEY_OF_SNAKES},						//0x2c
	{EXIT, MAP_A2_ANCIENT_TUNNELS},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_FAR_OASIS},

	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},				//0x2d
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},
	{0},
	{EXIT, MAP_A2_LOST_CITY},

	{0},													//0x2e -> canyon of the magi
	{0},
	{UNIT_OBJECT, 402},										
	{UNIT_OBJECT, 402},


	{EXIT, MAP_A2_SEWERS_LEVEL_2},							//0x2f
	{EXIT, MAP_A2_SEWERS_LEVEL_2},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_SEWERS_LEVEL_3},							//0x30
	{EXIT, MAP_A2_SEWERS_LEVEL_3},
	{UNIT_OBJECT, 323},
	{EXIT, MAP_A2_SEWERS_LEVEL_1},

	{UNIT_OBJECT, 355},										//0x31
	{UNIT_OBJECT, 355},
	{0},
	{EXIT, MAP_A2_SEWERS_LEVEL_2},

	{UNIT_TILE, 29},										//0x32
	{UNIT_TILE, 29},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},					//0x33
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},
	{0},
	{EXIT, MAP_A2_HAREM_LEVEL_1},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},					//0x34
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},
	{UNIT_OBJECT, 288},
	{EXIT, MAP_A2_HAREM_LEVEL_2},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3},					//0x35
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3},
	{0},
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},

	{UNIT_OBJECT, 298},										//0x36
	{UNIT_OBJECT, 298},
	{0},
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},

	{EXIT, MAP_A2_STONY_TOMB_LEVEL_2}, 
	{EXIT, MAP_A2_STONY_TOMB_LEVEL_2}, 
	{0}, 
	{EXIT, MAP_A2_ROCKY_WASTE},								//0x37 -> stony tomb

	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},				//0x38
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},
	{0},
	{EXIT, MAP_A2_DRY_HILLS},

	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3},				//0x39
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},

	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},				//0x3a
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},
	{0},
	{EXIT, MAP_A2_VALLEY_OF_SNAKES},

	{UNIT_OBJECT, 397}, 
	{UNIT_OBJECT, 397}, 
	{0}, 
	{EXIT, MAP_A2_STONY_TOMB_LEVEL_1},						//0x3b -> stony tomb lvl 2

	{UNIT_OBJECT, 354},										//0x3c
	{UNIT_OBJECT, 354},
	{0},
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},

	{UNIT_OBJECT, 149},										//0x3d
	{UNIT_OBJECT, 149},
	{0},
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},

	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},						//0x3e
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},
	{0},
	{EXIT, MAP_A2_FAR_OASIS},

	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3},						//0x3f
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3},
	{0},
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1},

	{UNIT_OBJECT, 356},										//0x40
	{UNIT_OBJECT, 356},
	{0},
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},

	{0}, {0}, {0}, {EXIT, MAP_A2_LOST_CITY},										//0x41 ancient tunnels

	{UNIT_OBJECT, 152},										//0x42
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x43
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x44
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x45
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x46
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x47
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},


	{UNIT_OBJECT, 152},										//0x48										
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{0}, {0}, {0}, {0},										//0x49 -> tal chambre

	{UNIT_OBJECT, 357},										//0x4a
	{UNIT_OBJECT, 357},
	{UNIT_OBJECT, 402},
	{UNIT_OBJECT, 298},

	////////////////////////////////////////////////////////////////////
	// Act 3
	////////////////////////////////////////////////////////////////////

	{0}, {0}, {0}, {0},										//0x4b -> kurast docks


	{EXIT, MAP_A3_GREAT_MARSH},								//0x4c
	{EXIT, MAP_A3_SPIDER_CAVERN},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_DOCKS},


	{EXIT, MAP_A3_FLAYER_JUNGLE},							//0x4d
	{EXIT, MAP_A3_FLAYER_JUNGLE},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_SPIDER_FOREST},


	{EXIT, MAP_A3_LOWER_KURAST},							//0x4e
	{UNIT_OBJECT, 252},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_GREAT_MARSH},


	{EXIT, MAP_A3_KURAST_BAZAAR},							//0x4f
	{EXIT, MAP_A3_KURAST_BAZAAR},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_FLAYER_JUNGLE},


	{EXIT, MAP_A3_UPPER_KURAST},							//0x50
	{EXIT, MAP_A3_RUINED_TEMPLE},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_LOWER_KURAST},


	{EXIT, MAP_A3_KURAST_CAUSEWAY},							//0x51
	{EXIT, MAP_A3_KURAST_CAUSEWAY},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_BAZAAR},


	{EXIT, MAP_A3_TRAVINCAL},								//0x52
	{EXIT, MAP_A3_TRAVINCAL},
	{0},
	{EXIT, MAP_A3_UPPER_KURAST},


	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},					//0x53
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_CAUSEWAY},

	{0}, {0}, {0}, {0},										//0x54 -> arachnid lair
	{0}, {0}, {0}, {0},										//0x55 -> spider cavern
	{0}, {0}, {0}, {0},										//0x56 -> swampy pit lvl 1
	{0}, {0}, {0}, {0},										//0x57 -> swampy pit lvl 2
	{0}, {0}, {0}, {0},										//0x58 -> flayer dungeon lvl 1
	{0}, {0}, {0}, {0},										//0x59 -> flayer dungeon lvl 2
	{0}, {0}, {0}, {0},										//0x5a -> swampy pit lvl 3
	{0}, {0}, {0}, {0},										//0x5b -> flayer dungeon lvl 3
	{0}, {0}, {0}, {0},										//0x5c -> sewer lvl 1
	{0}, {0}, {0}, {0},										//0x5d -> sewer lvl 2
	{0}, {0}, {0}, {0},										//0x5e -> ruined temple
	{0}, {0}, {0}, {0},										//0x5f -> disused fane
	{0}, {0}, {0}, {0},										//0x60 -> forgotten reliquary
	{0}, {0}, {0}, {0},										//0x61 -> forgotton temple
	{0}, {0}, {0}, {0},										//0x62 -> ruined fane
	{0}, {0}, {0}, {0},										//0x63 -> disused reliquary

	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},					//0x64
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},
	{0},
	{EXIT, MAP_A3_TRAVINCAL},

	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3},					//0x65
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3},
	{UNIT_OBJECT, 324},
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},

	{XY, 17591, 8069},										//0x66
	{XY, 17591, 8069},
	{0},
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},


	////////////////////////////////////////////////////////////////////
	// Act 4
	////////////////////////////////////////////////////////////////////

	{0}, {0}, {0}, {0},										//0x67 pandemonium fortress


	{EXIT, MAP_A4_PLAINS_OF_DESPAIR},						//0x68
	{EXIT, MAP_A4_PLAINS_OF_DESPAIR},
	{0},
	{EXIT, MAP_A4_THE_PANDEMONIUM_FORTRESS},


	{EXIT, MAP_A4_CITY_OF_THE_DAMNED},						//0x69
	{UNIT_MONSTER, 256},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_OUTER_STEPPES},


	{EXIT, MAP_A4_RIVER_OF_FLAME},							//0x6a
	{EXIT, MAP_A4_RIVER_OF_FLAME},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_PLAINS_OF_DESPAIR},


	{UNIT_OBJECT, 255, NULL, MAP_A4_THE_CHAOS_SANCTUARY},	//0x6b
	{UNIT_OBJECT, 376},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_CITY_OF_THE_DAMNED},


	{UNIT_OBJECT, 392, 1337},										//0x6c
	{UNIT_OBJECT, 255},
	{0},
	{EXIT, MAP_A4_RIVER_OF_FLAME},


	////////////////////////////////////////////////////////////////////
	// Act 5
	////////////////////////////////////////////////////////////////////

	{0}, {0}, {0}, {0},										//0x6d

	{EXIT, MAP_A5_FRIGID_HIGHLANDS},						//0x6e
	{UNIT_MONSTER, 776},
	{0},
	{EXIT, MAP_A5_HARROGATH},

	{EXIT, MAP_A5_ARREAT_PLATEAU},							//0x6f
	{EXIT, MAP_A5_ARREAT_PLATEAU},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_THE_BLOODY_FOOTHILLS},

	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},						//0x70
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_FRIGID_HIGHLANDS},

	{EXIT, MAP_A5_GLACIAL_TRAIL},							//0x71
	{EXIT, MAP_A5_FROZEN_RIVER},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{UNIT_OBJECT, 460},										//0x72
	{UNIT_OBJECT, 460},
	{0},
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},

	{EXIT, MAP_A5_FROZEN_TUNDRA},							//0x73
	{EXIT, MAP_A5_FROZEN_TUNDRA},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},

	{0}, {0}, {0}, {0},										//0x74 -> drifter cavern

	{EXIT, MAP_A5_THE_ANCIENTS_WAY},						//0x75
	{EXIT, MAP_A5_THE_ANCIENTS_WAY},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{EXIT, MAP_A5_ARREAT_SUMMIT},							//0x76
	{EXIT, MAP_A5_ARREAT_SUMMIT},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_FROZEN_TUNDRA},

	{0}, {0}, {0}, {0},										//0x77 -> icy cellar

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},					//0x78
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},
	{0},
	{EXIT, MAP_A5_THE_ANCIENTS_WAY},

	{EXIT, MAP_A5_HALLS_OF_ANGUISH},						//0x79
	{EXIT, MAP_A5_HALLS_OF_ANGUISH},
	{0},
	{0},

	{EXIT, MAP_A5_HALLS_OF_PAIN},							//0x7a
	{EXIT, MAP_A5_HALLS_OF_PAIN},
	{0},
	{EXIT, MAP_A5_NIHLATHAKS_TEMPLE},

	{EXIT, MAP_A5_HALLS_OF_VAUGHT},							//0x7b
	{EXIT, MAP_A5_HALLS_OF_VAUGHT},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_HALLS_OF_ANGUISH},

	{UNIT_OBJECT, 462},										//0x7c
	{UNIT_OBJECT, 462},
	{0},
	{EXIT, MAP_A5_HALLS_OF_PAIN},

	{0}, {0}, {0}, {0},										//0x7d -> abaddon
	{0}, {0}, {0}, {0},										//0x7e -> pit of acheron
	{0}, {0}, {0}, {0},										//0x7f -> infernal pit

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},					//0x80
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},
	{0},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},					//0x81
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},
	{UNIT_OBJECT, 494},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},

	{EXIT, MAP_A5_THRONE_OF_DESTRUCTION},					//0x82
	{EXIT, MAP_A5_THRONE_OF_DESTRUCTION},
	{0},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},

	{XY, 15091, 5006},										//0x83
	{XY, 15114, 5069},
	{0},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},

	{0}, {0}, {0}, {0},										//0x84 -> worldstone keep

	{UNIT_OBJECT, 397},										//0x85
	{UNIT_OBJECT, 397},
	{0},
	{0},

	{0}, {0}, {0}, {0},										//0x86 -> forgotton sands

	{UNIT_OBJECT, 397},										//0x87
	{UNIT_OBJECT, 397},
	{0},
	{0}
};

void OnAutomapDraw() 
{
	int cColorDestination = 97;
    int cColor[] = {155,109,152,132};

	POINT MyPos, Pos;
	ScreenToAutomap(&MyPos, D2CLIENT_GetUnitX(D2CLIENT_GetPlayerUnit()) *32, D2CLIENT_GetUnitY(D2CLIENT_GetPlayerUnit()) *32);
	if(TPath.GetSize()) {
		CArrayEx <POINT, POINT> DrawPath;
		DrawPath.Add(MyPos, 1);
		for(int i = 0;i<TPath.GetSize();i++) {
			ScreenToAutomap(&Pos, TPath.ElementAt(i).x *32, TPath.ElementAt(i).y *32);
			DrawPath.Add(Pos, 1);
		}
		for(int i = 0;i<(DrawPath.GetSize()-1);i++) {
			D2GFX_DrawLine(DrawPath.ElementAt(i).x,DrawPath.ElementAt(i).y,DrawPath.ElementAt(i+1).x, DrawPath.ElementAt(i+1).y, cColorDestination, -1);
			DrawCross(DrawPath.ElementAt(i+1).x, DrawPath.ElementAt(i+1).y, cColorDestination);
		}
	}
	int x = 316;

	for(int i = 0;i<4;i++) {
			if(Vectors[i].x && Vectors[i].y) {
				ScreenToAutomap(&Pos, Vectors[i].x *32, Vectors[i].y *32);
				D2GFX_DrawLine(MyPos.x, MyPos.y, Pos.x, Pos.y, cColor[i], -1);
				DrawCross(Pos.x, Pos.y, cColor[i]);

				if (v_GUI)
				{
				x += 20;
				DrawCross(910,x,cColor[i]);
	
				if (i==0)
			    SpecialTextHook(920, x+5, 0, 4, "Next: Numpad 1");

				if (i==1)
				SpecialTextHook(920, x+5, 0, 4, "Quest: Numpad 2");

				if (i==2)
				SpecialTextHook(920, x+5, 0, 4, "Waypoint: Numpad 3");

				if (i==3)
				SpecialTextHook(920, x+5, 0, 4, "Previous: Numpad 4");
				}
			}
	}
}

void OnLoop() 
{
	if(LastArea != GetPlayerArea() && pMe) {
		LastArea = GetPlayerArea();
		if(LastArea != MAP_A4_THE_CHAOS_SANCTUARY)
			CSID = 0;
		GetVectors();
	}

	if(LastArea == MAP_A4_THE_CHAOS_SANCTUARY)
		if(vVector[LastArea*4].Id2 != (1337+CSID)) {
			vVector[LastArea*4].Id2 = 1337+CSID;
			GetVectors();
		}

		if(TPath.GetSize()) {
			End = TPath.GetLast();

			if(SetTele) {
				if(!SetSkill(0x36, 0)) {	//0x36 is teleport
					TPath.RemoveAll();
					//PrintText(1, "ÿc4AutoTele:ÿc1 Failed to set teleport!");
				}
				_timer = GetTickCount();
				SetTele = 0;
			}

			if(pMe->pInfo->pRightSkill->pSkillInfo->wSkillId == 0x36) {
				TeleActive = 1;
			} else {
				if(TeleActive) {
					TeleActive = 0;
					TPath.RemoveAll();
					//PrintText(1, "ÿc4AutoTele:ÿc1 Aborting teleport, deselected teleport");
					return;
				}
				if((GetTickCount() - _timer) > 1000) {
					TPath.RemoveAll();
					//PrintText(1, "ÿc4AutoTele:ÿc1 Failed to set teleport skill. Ping: %d", *p_D2CLIENT_Ping);
					return;
				}
				return;
			}

			if(CastTele) {
				CastTele = 0;
				_timer2 = GetTickCount();
				if(!CastOnMap(static_cast<WORD>(TPath.ElementAt(0).x),static_cast<WORD>(TPath.ElementAt(0).y), false)) {
					TPath.RemoveAll();
					return;
				}
			}

			if((GetTickCount() - _timer2) > 500) {
				if(Try >= 5) {
					//PrintText(1, "ÿc4AutoTele:ÿc1 Failed to teleport after 5 tries");
					TPath.RemoveAll();
					Try = 0;
					DoInteract = 0;
					return;
				} else {
					Try++;
					CastTele = 1;
					return;
				}
			}

			if(GetDistanceSquared(D2CLIENT_GetUnitX(D2CLIENT_GetPlayerUnit()), D2CLIENT_GetUnitY(D2CLIENT_GetPlayerUnit()), TPath.ElementAt(0).x, TPath.ElementAt(0).y) <= 5) {
				TPath.RemoveAt(0, 1);
				CastTele = 1;
				Try = 0;
			}

			if(DoInteract) {
				if(GetDistanceSquared(D2CLIENT_GetUnitX(D2CLIENT_GetPlayerUnit()), D2CLIENT_GetUnitY(D2CLIENT_GetPlayerUnit()), End.x, End.y) <= 5) {
					_InteractTimer = GetTickCount();
					InteractId = GetUnitByXY(End.x, End.y, InteractRoom);
					SetInteract = 1;
					TPath.RemoveAll();
					return;
				}
			}
		} else {
			End.x = 0;
			End.y = 0;
			SetTele = 1;
			CastTele = 1;
			TeleActive = 0;
			Try = 0;
		}
		if(DoInteract && SetInteract && _InteractTimer && (GetTickCount() - _InteractTimer > 150)) {
			Interact(InteractId, InteractType);
			SetInteract = 0;
			_InteractTimer = 0;
		}
		return;
}

bool OnKey(bool up, BYTE key, LPARAM lParam) {
	if (key == v_NextButton) {
		if (up)
			return false;
		ManageTele(vVector[GetPlayerArea()*4+Next]);
		return false;
	} else if (key == v_OtherButton) {
		if (up)
			return true;
		ManageTele(vVector[GetPlayerArea()*4+Other]);
		return false;
	} else if (key == v_WaypointButton) {
		if (up)
			return false;
		ManageTele(vVector[GetPlayerArea()*4+WP]);
		return false;
	} else if (key == v_PrevButton) {
		if (up)
			return false;
		ManageTele(vVector[GetPlayerArea()*4+Prev]);
		return false;
	}
	return true;
}

void GetVectors() {

	for(int i = 0;i<4;i++) {
		DWORD MyArea = GetPlayerArea();
		Vectors[i].x = 0;
		Vectors[i].y = 0;
		Vector V = vVector[MyArea*4+i];

		if(MyArea == MAP_A2_CANYON_OF_THE_MAGI) {
			if(V.dwType == 0 && V.Id == 0) {
				V.dwType = EXIT;
				V.Id = GetLevel(D2CLIENT_GetPlayerUnit()->pAct, MyArea)->pMisc->dwStaffTombLevel;
			}
		}

		if(V.dwType == UNIT_PLAYER)
			continue;

		if(V.dwType == XY) {
			Vectors[i].x = V.Id;
			Vectors[i].y = V.Id2;
		}

		if(V.dwType == UNIT_TILE || V.dwType == UNIT_OBJECT || V.dwType == UNIT_MONSTER) {
			if(V.Area)
				Vectors[i] = FindPresetLocation(V.dwType, V.Id, V.Area);
			else
				Vectors[i] = FindPresetLocation(V.dwType, V.Id, GetPlayerArea());
		}

		if(V.dwType == EXIT) {
			CCollisionMap g_collisionMap; //init the collisionmap

			DWORD Areas[2];
			DWORD AreaCount = 1;
			Areas[0] = GetPlayerArea();

			if(V.Area) {
				Areas[1] = V.Area;
				AreaCount = 2;
			}

			if(!g_collisionMap.CreateMap(Areas, AreaCount))//create a cmap for the current area
				continue;

			LPLevelExit ExitArray[0x40];//declare an array of exits to store the exits in later

			int ExitCount = g_collisionMap.GetLevelExits(ExitArray); //getlevelexits returns the exitcount

			if(!ExitCount)//if there are 0 tele positions we can stop here :p
				continue;

			for(int j = 0;j<ExitCount;j++) {//loop over evey exit to see if it matches our target
				if(ExitArray[j]->dwTargetLevel == V.Id) {
					Vectors[i] = ExitArray[j]->ptPos;
					continue;
				}
			}
		}
	}
}

Level* GetLevel(Act* pAct, int level) {
	//Insure that the shit we are getting is good.
	if (level < 0 || !pAct)
		return NULL;

	//Loop all the levels in this act

	for(Level* pLevel = pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel) {
		//Check if we have reached a bad level.
		if (!pLevel)
			break;

		//If we have found the level, return it!
		if (pLevel->dwLevelNo == level && pLevel->dwPosX > 0)
			return pLevel;
	}
	//Default old-way of finding level.
	return D2COMMON_GetLevel(pAct->pMisc, level);
}

bool cColdToCave = 0;

void ManageTele(Vector T) {

	DWORD Areas[2];
	DWORD AreaCount = 1;

	Areas[0] = GetPlayerArea();
	if(Areas[0] == MAP_A2_CANYON_OF_THE_MAGI) {
		if(T.dwType == 0 && T.Id == 0) {
			T.dwType = EXIT;
			T.Id = GetLevel(D2CLIENT_GetPlayerUnit()->pAct, Areas[0])->pMisc->dwStaffTombLevel;
		}
	} else if(Areas[0] == MAP_A1_COLD_PLAINS) {
		if(cColdToCave)
			if(T.Id == MAP_A1_BURIAL_GROUNDS)
				T.Id = MAP_A1_CAVE_LEVEL_1;
	} else if(Areas[0] == MAP_A4_THE_CHAOS_SANCTUARY && (T.Id2 >= 1337 && T.Id2 <= 1341)) {
		CSID == 3 ? CSID = 0 : CSID++;
		vVector[Areas[0]*4].Id = CS[CSID];
	}

	if(!T.Id) {
		//PrintText(1, "ÿc4AutoTele:ÿc1 Invalid destination");
		return;
	}

	if(T.Area) {
		Areas[1] = T.Area;
		AreaCount = 2;
	}

	DoInteract = 0;

	if(T.dwType == EXIT) {
		CCollisionMap g_collisionMap;	//init the collisionmap

		if(!g_collisionMap.CreateMap(Areas, AreaCount))		//create a cmap for the current area
			return;

		LPLevelExit ExitArray[0x40];	//declare an array of exits to store the exits in later

		int ExitCount = g_collisionMap.GetLevelExits(ExitArray);	//getlevelexits returns the exitcount

		if(!ExitCount)		//if there are 0 tele positions we can stop here :p
			return;

		for(int i = 0;i<ExitCount;i++) {	//loop over evey exit to see if it matches our target
			if(ExitArray[i]->dwTargetLevel == T.Id) {
				//LevelTxt * lvltext =  D2COMMON_GetLevelText(T.Id);

				DoInteract = 0;
				if(ExitArray[i]->dwType == EXIT_TILE) {
					DoInteract = 1;
					InteractType = UNIT_TILE;
					InteractRoom = ExitArray[i]->pRoom;
				} else DoInteract = 0;

				int nodes = MakePath(ExitArray[i]->ptPos.x, ExitArray[i]->ptPos.y, Areas, AreaCount, ExitArray[i]->dwType == EXIT_LEVEL ? 1: 0);
				//PrintText(1, "ÿc4AutoTele:ÿc1 Going to %s, %d nodes.", lvltext->szName, nodes);
				break;
			}
		}
		return;			
	}

	if(T.dwType == XY) {
		DoInteract = 0;
		if(!T.Id || !T.Id2) {
			//PrintText(1, "ÿc4AutoTele:ÿc1 No X/Y value found");
			return;
		}
		int nodes = MakePath(T.Id, T.Id2, Areas, AreaCount, 0);
		//PrintText(1, "ÿc4AutoTele:ÿc1 Going to X: %d, Y: %d, %d nodes", T.Id, T.Id2, nodes);
		return;
	}

	POINT PresetUnit;
	if(AreaCount == 2)
		PresetUnit = FindPresetLocation(T.dwType, T.Id, Areas[1]);
	else
		PresetUnit = FindPresetLocation(T.dwType, T.Id, Areas[0]);

	if(PresetUnit.x != 0 && PresetUnit.y != 0) {
		if(T.dwType == UNIT_TILE || (T.dwType == UNIT_OBJECT && T.Id == 298))
			DoInteract = 1;
		if(T.dwType == UNIT_OBJECT)
			for(int i = 0;i <= 13;i++)
				if(waypoints[i] == T.Id)
					DoInteract = 1;

		int nodes;
		if(nodes = MakePath(PresetUnit.x,PresetUnit.y, Areas, AreaCount, 0)) {
			if(T.dwType == UNIT_OBJECT) {
				ObjectTxt * ObjTxt = D2COMMON_GetObjectTxt(T.Id);
				//PrintText(1, "ÿc4AutoTele:ÿc1 Going to %s, %d nodes", ObjTxt->szName, nodes);
			}
			InteractType = T.dwType;
		}
		else return;
	} else {
		//PrintText(1, "ÿc4AutoTele:ÿc1 Can't find object");
		return;
	}
}

int MakePath(int x, int y, DWORD Areas[], DWORD count, bool MoveThrough) {

	CCollisionMap g_collisionMap; //init the collisionmap
	DWORD dwCount;
	POINT aPath[255];

	if(!g_collisionMap.CreateMap(Areas, count))
		return false;

	POINT ptStart = {D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos};
	POINT ptEnd = {x, y};

	if(!g_collisionMap.IsValidAbsLocation(ptStart.x, ptStart.y))
		return false;

	if(!g_collisionMap.IsValidAbsLocation(ptEnd.x, ptEnd.y))
		return false;

	g_collisionMap.AbsToRelative(ptStart);
	g_collisionMap.AbsToRelative(ptEnd);

	WordMatrix matrix;

	if(!g_collisionMap.CopyMapData(matrix))
		return false;

	CTeleportPath tf(matrix.GetData(), matrix.GetCX(), matrix.GetCY());
	dwCount = tf.FindTeleportPath(ptStart, ptEnd, aPath, 255);

	if(dwCount == 0)
		return false;

	for(DWORD i = 0;i < dwCount;i++) {
		g_collisionMap.RelativeToAbs(aPath[i]);
	}

	if(MoveThrough) {
		if(aPath[dwCount-1].x > aPath[dwCount-2].x)
			aPath[dwCount].x = aPath[dwCount-1].x + 2;
		else
			aPath[dwCount].x = aPath[dwCount-1].x - 2;
		if(aPath[dwCount-1].y > aPath[dwCount-2].y)
			aPath[dwCount].y = aPath[dwCount-1].y + 2;
		else
			aPath[dwCount].y = aPath[dwCount-1].y - 2;

		dwCount++;

		if(GetDistanceSquared(aPath[dwCount-1].x, aPath[dwCount-1].y, aPath[dwCount-3].x, aPath[dwCount-3].y) <= 30) {
			aPath[dwCount-2] = aPath[dwCount-1];
			aPath[dwCount-1].x = 0;
			aPath[dwCount-1].y = 0;
			dwCount--;
		}
	}


	TPath.RemoveAll();
	for(DWORD i = 0;i<dwCount;i++)
		TPath.Add(aPath[i], 1);

	return dwCount;
}

POINT FindPresetLocation(DWORD dwType, DWORD dwTxtFileNo, DWORD Area)
{
	Level* pLevel = GetLevel(D2CLIENT_GetPlayerUnit()->pAct, Area);

	POINT loc;
	loc.x = 0;
	loc.y = 0;
	DoInteract = 0;

	if(!VALIDPTR(pLevel))
		return loc;

	bool bAddedRoom = false;
	bool stoploop = false;
	for(Room2 *pRoom = pLevel->pRoom2First; pRoom; pRoom = pRoom->pRoom2Next)
	{
		bAddedRoom = false;
		if(!VALIDPTR(pRoom->pPreset) && !VALIDPTR(pRoom->pRoomTiles) && !VALIDPTR(pRoom->pRoom1))
		{
			D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = true;
		}

		for(PresetUnit* pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
		{
			//if(pUnit->dwTxtFileNo != 40 && pUnit->dwTxtFileNo != 41 && pUnit->dwTxtFileNo != 42)
			//	PrintText(4, "X: %d, Y: %d, TxtFileNo: %d, Type: %d", pUnit->dwPosX, pUnit->dwPosY, pUnit->dwTxtFileNo, pUnit->dwType);
			if(((dwType == NULL) || (dwType == pUnit->dwType)) && (dwTxtFileNo == pUnit->dwTxtFileNo))
			{
				if(dwType == UNIT_TILE || (dwType == UNIT_OBJECT && dwTxtFileNo == 298))
				{
					InteractRoom = pRoom;
					InteractType = dwType;
					//DoInteract = 1;
				}

				if(dwType == UNIT_OBJECT)
				{
					for(int i = 0;i <= 13;i++)
					{
						if(waypoints[i] == dwTxtFileNo)
						{
							InteractRoom = pRoom;
							InteractType = dwType;
							//DoInteract = 1;
							stoploop = 1;//stop looping over the rooms
							break;
						}
					}
				}

				loc.x = (pUnit->dwPosX) + (pRoom->dwPosX * 5);
				loc.y = (pUnit->dwPosY) + (pRoom->dwPosY * 5);

				stoploop = 1;//stop looping over the rooms
				break;
			}
		}

		if(bAddedRoom)
		{
			D2COMMON_RemoveRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = false;
		}
		if(stoploop)
		{
			stoploop = 0;
			break;
		}
	}

	return loc;
}

bool SetSkill(WORD wSkillId, bool Left)
{
	if(!D2CLIENT_GetPlayerUnit())
		return 0;

	BYTE PutSkill[9] = {0x3c,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
	if(GetSkill(wSkillId))
	{
		*(WORD*)&PutSkill[1] = wSkillId;
		if(Left)
			*(BYTE*)&PutSkill[4] = 0x80;
		D2NET_SendPacket(9,0,PutSkill);
	}
	else return 0;

	return 1;
}

bool GetSkill(WORD wSkillId)
{
	if(!D2CLIENT_GetPlayerUnit()) 
		return 0;

	for(Skill* pSkill = D2CLIENT_GetPlayerUnit()->pInfo->pFirstSkill; pSkill; pSkill = pSkill->pNextSkill)
		if(pSkill->pSkillInfo->wSkillId == wSkillId)
			return 1;//D2COMMON_GetSkillLevel(D2CLIENT_GetPlayerUnit(), pSkill, TRUE);

	return 0;
}

DWORD GetUnitByXY(DWORD X, DWORD Y, Room2* pRoom) {
	UnitAny* pUnit;

	if(!VALIDPTR(pRoom))
		return 0;

	if(!VALIDPTR(pRoom->pRoom1))
		return 0;

	if(!VALIDPTR(pRoom->pRoom1->pUnitFirst))
		return 0;

	pUnit = pRoom->pRoom1->pUnitFirst;

	if(!VALIDPTR(pUnit))
		return 0;

	if(!VALIDPTR(pUnit->pObjectPath))
		return 0;

	while(pUnit) {
		if(pUnit->dwType != UNIT_PLAYER)
			if(X == pUnit->pObjectPath->dwPosX)
				if(Y == pUnit->pObjectPath->dwPosY)
					return pUnit->dwUnitId;
		pUnit=pUnit->pListNext;
	}
	return 0;
}