#define waittime config->scrollspeed

float debugVec3[1][3];
float Matrix44_[4][4];
float Matrix43_[4][3];

struct cellPadButtonData
{
	int btnData;
	int btnDigital;
};

struct needformods
{
	cellPadButtonData pdPadBtn[15];
	CellPadData pad_data;
	sys_ppu_thread_t id;
	sys_mutex_t mymtx;
	Hooks hook[10];
	uint32_t fadetime;
	element_t* my_text;
	element_t* my_shader;
	element_t* checkmark;
	element_t* TESTSHADE;
	element_t* white;
	EngineLogic_t* engine;
	element_t* shaderelements[20];
	short scrollformenus[24];
	int shadersnum;
	bool thread;
	bool isopen;
	bool init;
	bool crossdown;
	bool circledown;
	bool leftdown;
	bool rightdown;
	bool updown;
	bool downdown;
	bool movemenu;
	bool pad;
	bool lockscroll;
	int wait;
	float x;
	float y;
	short scroll;
	short optionsNum;
	short textscroll;
	short menu_id;
	short menu_return;
	float enginetorque;
};

needformods* vars = (needformods*)0x008DD3BC;

enum hooknames
{
#ifdef CellPad_HOOK
	CellPad,
#endif
#ifdef Handle_All_Drawing_HOOK
	Handle_All_Drawing,
#endif
#ifdef EngineRacer_GetEngineTorque_HOOK
	EngineRacer_GetEngineTorque,
#endif
#ifdef stringhash32_HOOK
	stringhash32,
#endif
#ifdef UI_SearchStringForHash_HOOK
	UI_SearchStringForHash,
#endif
#ifdef DALManager_GetInt_HOOK
	DALManager_GetInt,
#endif
#ifdef FEHashUpper_HOOK
	FEHashUpper,
#endif
#ifdef EngineRacer_OnTaskSimulate_HOOK
	EngineRacer_OnTaskSimulate,
#endif
#ifdef UI_PassAssetArray_HOOK
	UI_PassAssetArray,
#endif
#ifdef Huds_SetupElement_HOOK
	Huds_SetupElement,
#endif
#ifdef FEColor_CopyColor_HOOK
	FEColor_CopyColor,
#endif
#ifdef FE_Object_GetObjectColor_HOOK
	FE_Object_GetObjectColor,
#endif
#ifdef StringToKey_HOOK
	StringToKey,
#endif
#ifdef Hasher_Function_HOOK
	Hasher_Function,
#endif
#ifdef CarRenderInfo_Render_HOOK
	CarRenderInfo_Render,
#endif
#ifdef PVehicle_PVehicle_HOOK
	PVehicle_PVehicle,
#endif
#ifdef AIVehicleHuman_FetchInput_HOOK
	AIVehicleHuman_FetchInput,
#endif
};

struct color
{
	int red;
	int green;
	int blue;
	int alpha;
};
color fade = { 0, 0, 0, 255};
color background = { 0, 0, 0, 200 };
color white = { 255, 255, 255, 255 };
color gray = { 127, 127, 127, 127 };
color black = { 0, 0, 0, 255 };

color BackgroundColor = { 0.0f, 0.0f, 0.0f, 0.6f };
color BackgroundColor2 = { 0.325f, 0.325f, 0.325f, 1.0f };

/////////////////////////////////////////////////////////////
color Colors[] = {
{ 0.0f, 0.0f, 0.0f, 1.0f},//fade - 0
{ 0.0f, 0.0f, 0.0f, 1.0f},//fade2 - 1
{ 1.0f, 1.0f, 0.0f, 1.0f},//Yellow - 2
{ 1.0f, 0.27f, 0.0f,1.0f},//Red Orange - 3
{ 0.5f, 0.0f, 1.0f, 1.0f},//Purple - 4
{ 0.0f, 0.0f, 1.0f, 1.0f},//Blue - 5
{ 1.0f, 0.0f, 0.0f, 1.0f},//Red - 6
{ 0.0f, 0.55f, 0.0f,1.0f},//Green - 7
{ 1.0f, 0.0f, 0.5f, 1.0f},//Pink - 8
{ 0.0f, 1.0f, 0.0f, 1.0f},//Lime Green - 9
{ 1.0f, 0.7f, 0.0f, 1.0f},//Orange - 10
{ 0.0f, 1.0f, 1.0f, 1.0f},//Cyan - 11
{ 0.0f, 0.0f, 0.0f, 1.0f},//Black - 12
{ 0.5f, 0.5f, 0.5f, 1.0f},//Grey - 13
{ 1.0f, 1.0f, 1.0f, 1.0f},//White - 14
{ 0.0f, 0.0f, 0.6f, 1.0f},//Dark Blue - 15
{ 1.0f, 0.8f, 0.7f, 1.0f}, //Cream - 16
{ 0.5f, 0.5f, 0.5f, 1.0f} //custom - 17
};

enum colornames
{
	FADE,
	FADE2,
	YELLOW,
	RED_ORANGE,
	PURPLE,
	BLUE,
	RED,
	GREEN,
	PINK,
	LIME_GREEN,
	ORANGE,
	CYAN,
	BLACK,
	GREY,
	WHITE,
	DARK_BLUE,
	CREAM,
	CUSTOM
};

element_params_size elem_setup;
ui_main_t uimain;

struct VideoConfiguration
{
	char pad00[0x24];	//0x00
	int width;			//0x24
	int height;			//0x28
	char pad01[0x04];	//0x2C
};

#define videoconfig (*(VideoConfiguration**)(0x10160B04))

#define FONT_NFS_BODY 0x94AF4029
#define FONT_NFS_TITLE 0x2BD9F6BD

struct config_t	//0x94C0C4 - size 0x3F3C
{
	bool debugoptions;
	bool disablesmoke;
	bool driftmode;
	bool customtorque;
	bool disabletraffic;
	bool infiniteNOS;
	bool infiniteSBR;
	float torquevalue;
	float scrollspeed;
};
config_t* config = (config_t*)0x94C0C4;

enum menu_ids
{
	MENU_MAIN,
	MENU_CARSETTINGS,
	MENU_WORLD,
	MENU_MISC,
	MENU_C_Transmission,
	MENU_C_Torque,
	MENU_C_Nitrous,
	MENU_C_Intake
};
//#define Multi-Textured Image 0xDFCFFB00	//7
#define XcamoTile1 0x3D32FC96
#define XcamoTile2 0x3D32FC97

#define FX_HIGHLIGHT_GLOW 0xC7134E8C

#define BasePoly 0xC6AFDD7E

#define End_Of_Scroller 0x43B6310F
#define ARROW_PRIMARY 0xA650AD4D
#define ANGLED_GLINT 0x778B0387
#define Text_Glow 0x235E6F9C
#define Dotted_Line 0x9E51AF8A
#define TEXT_ENDPIECE 0x2D777900
#define Gradient_32x32 0xBE6EF52E
#define White16x16 0xE2A5C626

#define Rounded_Startpiece 0x477E12C3
#define Rounded_Connector 0xEBE0953A
#define Rounded_Endpiece 0x9A89D76C

#define _R2 0x683
#define _R3 0x684
#define _L2 0x5BD
#define _R1 0x682
#define _L1 0x5BC
#define _Circle 0x54A68051
#define _Cross 0x2959349
#define _Triangle 0x6851AAF5
#define _Square 0x7A8B6BD0
#define _Start 0x3B7F86D

#define PC_key_esc 0x1BB3C514
#define PC_key_Q 0x68A29AAA
#define PC_key_enter 0xD7B6EDB7
#define PC_key_1 0x68A29A8A
#define PC_key_2 0x68A29A8B
#define PC_HELP_FRAME 0x7C87C4A4
#define PC_CLICKDRAG_ICON 0xB35ECC7D
#define PC_key_9 0x68A29A92
#define PC_key_0 0x68A29A89
#define PC_key_3 0x68A29A8C
#define PC_key_spc 0x1BB4003F
#define PC_arrow_keys 0x7637A5D7
#define _45Corner 0x1ABEDEB1

#define SHAPE_OPTIONS_OUTLINE 0xF34630DA
#define SHAPE_STATISTICS_OUTLINE 0xA54010B9
#define SHAPE_INGAME_OUTLINE 0x31AC9C7F
#define SHAPE_CAREER_OUTLINE 0xC03CD360
#define SHAPE_CUSTOMIZATION_OUTLINE 0xFB35CBE7
#define SHAPE_QR_OUTLINE 0xA7B59EF1
#define SHAPE_CS_OUTLINE 0xE39E2024
#define SHAPE_INGAME 0x6DBC6800

#define HUD_Wii_STEERING_WHEEL 0x3A27B33C
#define HUD_COOLDOWN_METER_MASK 0x40F0AB0B
#define HUD_COOLDOWN_METER_COLOR 0x5E58A7BE
#define HUD_GEAR 0x329B9A1E
#define HUD_RPM_10000.tga 0x71B35C3E
#define HUD_MAIN_SPEED_BACKING 0x7DF71B22
#define HUD_REDLINE_COLOR 0xDBF29080
#define HUD_RPM_METER_COLOR 0x80A5708
#define HUD_RPM_METER_BACKING 0xC5B49978
#define HUD_SHIFT_ICON_NORMAL 0xCB764F2D
#define HUD_DRIFT_METER_COLOR 0xFE830B92
#define HUD_DRIFT_METER_BACKING 0x3D2C9882
#define HUD_GENERIC_METER_COLOR 0xE5F6BCF6

#define OPTION_WIDGET_BASE 0x5A0AF875
#define OPTION_WIDGET_BAR 0xEB74B22F
#define OPTION_WIDGET_END 0xEB74C091
#define OPTION_WIDGET_END_OF_SCROLLER 0x2043CEAA

#define Minimap_Icon_Event_Owned 0x972EB7CF
#define Minimap_Icon_Event_BossRace 0x7ABF10E4
#define Minimap_Icon_Event_RaceWar 0xD0926BF7
#define Minimap_Icon_Roadblock 0x123F07E2
#define Minimap_Icon_Pursuit_Breaker 0x997A2868
#define Minimap_Icon_Spike_Strips 0xEE22A331
#define Minimap_Icon_Event 0xB9358813
#define Minimap_Icon_Speedtrap 0xA96409F9
#define Minimap_Icon_Safe_House 0x2CFD5273
#define Minimap_Icon_Car_Lot 0x12BB8395
#define Minimap_Icon_Circuit 0x25559384
#define Minimap_Icon_Hiding_Spot 0xDC3C0449
#define Minimap_Icon_Event_Rival 0x975D7590
#define Minimap_Icon_Car 0xADA85247
#define Minimap_Icon_FinishLine 0x164F557A
#define Minimap_Icon_Checkpoint 0x676E6CD9
#define MINIMAP_BACKING 0xC5DE4578
#define MINIMAP_NORTH_INTICATOR 0xC2491040

#define MAP_UNDERLAY_ARROW 0xED9260EA
#define Map_Random_Destination 0x28FF2AFE
#define Map_Overlay_Rounded_Edge_Outline 0x52406FA1
#define Map_Overlay_Rounded_Edge_Outline_EDGE 0x254A74F5
#define Map_Overlay_Rounded_Edge 0xE2883922

#define FLAME 0x2C85624
#define FLAME_EFFECT 0x9F7848F0

//#define Player_Icon.tga 0xEB3DBAD4
//#define Medal_Bronze.tga 0x568CE011
//#define Medal_Gold.tga 0x1C88D067
//#define Medal_Silver.tga 0x7D903076
//#define CARBUCKET_STOCKCARS.tga 0x3A541F7F
//#define TABLE_UNDERLAY_ARROW.tga 0xBFCF98F4
//#define Logitech_Wheel_G25Force.tga 0x7564B71E
//#define DPad.tga 0x148E38
//#define Loading_controller_xbox_c1.tga 0x1113B973
//#define R1_Loading.tga 0x5595BE5F
//#define L1_Loading.tga 0x3D565799
//#define Select.tga 0x79AD657F
//#define Right_Analog_Up.tga 0x258D432
//#define Right_Analog_Down.tga 0xFBD55D85
//#define Eatrax_Rock.tga 0xD586732
//#define REORDER_ARROW.tga 0xFF1BEE1C

#define UNDER_OPTIONS_BAR 0xFA3F327C
//#define FULL_CIRCLE.tga 0x88E26A23
//#define RADAR_RING.tga 0x6CD0C4B8
//#define LOADING_PILLAR.tga 0xC8858660
//#define CAMO_TYPE_09.tga 0x4A651A68
//#define Tip_Autosculpt.tga 0xFAB51A7F
//#define AUTOZONElogo.tga 0x376DF1A5
//#define FULL_CIRCLE_RING.tga 0x17E87D2
//#define TIMER_ICON.tga 0x9AFDD528
//#define WRONGWAY.tga 0x3BFDC7FD	
//#define ENGAGE_ARROW.tga 0x5F146230
//#define HIGHLIGHT_BAR_ARROWHEAD.tga 0xFB0CBFC7
//#define Plus.tga 0x1B1463
//#define Mode_Icon_Drift.tga 0x119144
//#define HEAT_ICON.tga 0xC30EA0A9
//#define PIP_FRAME.tga 0xB28C4C72
//#define PIP_STATIC_TILE.tga 0x17B4801C
//#define WINGMAN_PATHFINDER.tga 0x264D1AB4
//#define IconSelection_Glow.tga 0x5FBBA846
//#define VOIP_ICON_ON.tga 0x19B9DF81
//#define LEADERBOARD_COP_INDICATOR.tga 0x37C58B31
//#define TAC_NUMBER_GHOST.tga 0x83ABFD83
//#define NOS_ICON.tga 0x11479E57
//#define COPS_DESTROYED.tga 0xC3BB7F26
//#define COPS_INVOLVED.tga 0x7DAD461A
//#define MULTIPLIER_X.tga 0x412561FD
//#define SPEEDBREAKER_ICON.tga 0x4CBD97B4
//#define MIRROR_FRAME.tga 0x7FB56F24
//#define Chyron_Music_Icon.tga 0xA8885BFA
//#define Helicopter_Line_Of_Sight.tga 0x21390E47
//#define Helicopter_Minimap_Icon.tga 0x586874A0
//#define Helicopter_Blades.tga 0x2C68F8B8
#define Radial_Spinner 0x83A2D04A
//#define WORLD_MAP_CURSOR_CIRCLE.tga 0xAC749412
//#define WORLD_MAP_CURSOR_CROSSHAIR.tga 0xA65BB16E
//#define SOFT_CIRCLE.tga 0xDD7C38AC
//#define AAA_WM_PLACEHOLDER.tga 0x9FE56E47
//#define Triangle_end.tga 0x3E9D654B
//#define Mode_Icon_Sprint.tga 0x2521E5EB
//#define CREW_ICON_01.tga 0x26FCDF78
//#define DEFAULT_TRACK.tga 0x804FBAF8
//#define CORNER_CURVE_EDGE.tga 0x1CD04D60
//#define CORNER_CURVE_MAP.tga 0xF91DB769
//#define Generic_New_Item.tga 0xCFFB7033
#define Check_Mark 0xD578AD67
//#define Locked_Icon_small.tga 0x4CF36A31
//#define Locked_Icon.tga 0xBEA19E19
//#define MyCars_Frame.tga 0xEE5E7C98
//#define CARSELECT_MANUFACTURER_PORSCHE.TGA 0x61A67474
//#define CHALLENGE_UNDERLAY.tga 0x3C4597A5
//#define Frame_highlight_1.tga 0xECC321B1
//#define Right_Analog.tga 0xFBB0B78E
//#define X_OUTER.tga 0x6D22BBC5
//#define X_Mark.tga 0x872E2B01
//#define choosergradient.tga 0x61BF27E0
//#define roundedBox.tga 0x422CAAB9
//#define HEAT_INCREMENT.tga 0x38E46545
//#define HEAT_INNER.tga 0x24E8B8DC
//#define Impound_Strike_Under.tga 0xCD699DA9
//#define Impound_Strike.tga 0x84C81E0C
#define IMPOUND_ICON 0x843698A3
#define Main_Icon_Career 0x3704F3D
#define Secondary_Logo_911turbo 0x3D47C15D
#define car_class_tuner 0x71BEE5B7
#define ADD_CAR_ICON 0xFEF3BC05
#define Mode_Icon_Canyon 0xFEBDFEF3
#define Stars_Bronze 0x72A04EFB
#define Stars_Silver 0x99A39F60
#define Stars_Gold_single 0xF00879F2

#define REWARDS_FRAME 0xA52EBCC1
#define REWARDS_UNDERLAY 0xD058BA1A
#define REWARDS_CURSOR 0x44469214
#define REWARDS_SIDE_UNDER 0x19E90ED8


/*///DAL

0x1771 GetCareerIsCurrentlyActive
0x1772 GetCar
0x1773 GetNumCareerCars
0x1774 GetCanPurchaseCareerCar
0x1775 GetNewCareerCar
0x1776 GetBin(a3);
0x1777 GetIsCasinotownUnlocked
0x1778 GetCash
0x1779 GetRep
0x177A GetCareerStarted
0x177B GetTutorialComplete
0x177C GetGameOver
0x177D GetCareerCompleted
0x1780 GetCarClass
0x1781 GetTutorial
0x1782 GetCurrentWingman
0x1783 GetNumGetOutOfJailCards
0x1784 GetCurPursuitNumInfractions
0x1785 GetCurPursuitInfractionsCost
0x1786 GetNumImpoundStrikesRemainingOnCurrentCar
0x1789 GetNumUnservedInfractionsOnCurrentCar
0x178A GetUnservedInfractionsCostOnCurrentCar
0x178C GetControllerConfigLoads
0x178D GetCareerFeLocation
0x178E GetCurrentBoss
0x178F GetIsBossFlow
0x1790 GetCrewOwnedFlag
0x1791 GetSMSMessageHandle
0x1792 GetSMSMessageIsAvailable
0x1793 GetSMSMessageWasRead
0x1794 GetSMSMessageIsVoice
0x1795 GetSMSMessageIsTip
0x1796 GetSMSMessageSortOrder
0x1797 GetSMSMessageHashSubject
0x1798 GetSMSMessageHashFrom
0x1799 GetSMSMessageHashMessage
0x179A GetHasTipBeenShown

*/