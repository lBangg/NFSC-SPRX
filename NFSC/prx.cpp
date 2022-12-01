#define CellPad_HOOK
#define Handle_All_Drawing_HOOK
#define EngineRacer_GetEngineTorque_HOOK
//#define stringhash32_HOOK
//#define UI_SearchStringForHash_HOOK
//#define DALManager_GetInt_HOOK
//#define FEHashUpper_HOOK
//#define EngineRacer_OnTaskSimulate_HOOK
//#define UI_PassAssetArray_HOOK
//#define Huds_SetupElement_HOOK
//#define FEColor_CopyColor_HOOK
//#define FE_Object_GetObjectColor_HOOK
//#define StringToKey_HOOK
//#define Hasher_Function_HOOK
#define CarRenderInfo_Render_HOOK
#define PVehicle_PVehicle_HOOK
#define AIVehicleHuman_FetchInput_HOOK

////////////////// SCREEN RECORDING //////////////////////

#define recording_util

//////////////////////////////////////////////////////////

#include "PS3_Functions.h"
#include "structs.h"
#include "Hooking.h"

#ifdef recording_util
#include "recorder.h"
#endif

#include "vars.h"
#include "functions.h"
#include "menu.h"
//#define hen_compatibility

SYS_MODULE_INFO( NFSC, 0, 1, 1);
SYS_MODULE_START( _NFSC_prx_entry );
SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _NFSC_export_function, LIBNAME );
SYS_MODULE_STOP(RestoreHooks);

extern "C" int _NFSC_export_function(void) { return CELL_OK; }
#ifdef CellPad_HOOK
int CellPad_Hook(uint32_t port_no, CellPadData* data)
{
	CellPadData pad;
	memset(&pad, 0, sizeof(CellPadData));
	pad.len = data->len;
	vars->hook[CellPad].Stub<int>(port_no, &pad);
	memcpy(data, &pad, sizeof(CellPadData));
	if (data->len != 0)
	{
		if (data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] != 0 || data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] != 0)
			memcpy(&vars->pad_data, &pad, sizeof(CellPadData));

		if (vars->isopen)
		{
			data->button[CELL_PAD_BTN_OFFSET_PRESS_LEFT] = 0;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_RIGHT] = 0;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_UP] = 0;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_DOWN] = 0;
			data->button[CELL_PAD_BTN_OFFSET_PRESS_CROSS] = 0;
		}
	}
	return 0;
}
#endif

#ifdef Handle_All_Drawing_HOOK
void Handle_All_Drawing_hook(drawparams* r3, huds_list* r4, int count)
{
	vars->hook[Handle_All_Drawing].Stub<void>(r3, r4, count);
	if (count)
	{
		if (vars->init == false)
		{
			vars->init = true;
			vars->my_text = TextElement(FONT_NFS_BODY);
			vars->my_shader = ShaderElement(BasePoly);
			vars->checkmark = ShaderElement(_Cross);
			vars->white = ShaderElement(BasePoly);

			//vars->TESTSHADE = TextElement(FONT_NFS_BODY);
		}

		//DrawText(vars->TESTSHADE, L"TEST",Matrix43_[0][0] , Matrix43_[0][1], Matrix43_[0][2], Matrix43_[1][0], &white);

		tempoptions = vars->optionsNum;
		sys_mutex_lock(vars->mymtx, 0xFFFFFF);
		vars->optionsNum = 0;
		sys_mutex_unlock(vars->mymtx);

		/*
		for (int i = 0; i < vars->shadersnum; i++)
		{
			if (vars->shaderelements[i] && (int)vars->shaderelements[i]->shader.settings != 0xEEEEEEEE)
			{
				vars->shaderelements[i]->shader.render_flags = 0x43800002;
				vars->shaderelements[i]->shader.settings->col.r = fade.red;
				vars->shaderelements[i]->shader.settings->col.r = fade.red;
				vars->shaderelements[i]->shader.settings->col.g = fade.green;
				vars->shaderelements[i]->shader.settings->col.b = fade.blue;
			}
		}
		*/

		DrawInfo(r3);

		if (vars->isopen)
		{
			drawmenu();
		}
	}
}
#endif

//00324770
int DoGearChange_4A8948_hook(EngineLogic_t* engine, int nextgear) {
	if((uint32_t)__builtin_return_address() == 0x24CC8)
		vars->engine = engine;

	//return vars->hook[sub_4A8948].Stub<int>(engine, nextgear);
}

#ifdef EngineRacer_GetEngineTorque_HOOK
float EngineRacer_GetEngineTorque_hook(EngineLogic_t* engine, float rpm)
{
	float torque = vars->hook[EngineRacer_GetEngineTorque].Stub<float>(engine, rpm);
	if (vars->engine == engine)
	{
		//float hp = ((vars->enginetorque * vars->engine->rpm) / 9550.0f) * 1.34;
		//cout("%.0fNm@%.0fRPM %.2f HP\n", torque,engine->rpm,hp);
		if (config->customtorque)
			torque *= config->torquevalue;

		vars->enginetorque = torque;
	}
	return torque;
}
#endif

unsigned int hashes_t[20000];
int hash_c = 0;

#ifdef stringhash32_HOOK
unsigned int stringhash32_hook(const char* string)
{
	unsigned int hash = vars->hook[stringhash32].Stub<unsigned int>(string);

	bool f = false;
	for (int i = 0; i < hash_c; i++)
		if (hashes_t[i] == hash)
			f = true;

	if (!f) {
		_sys_printf("%d) %s 0x%X\n", hash_c, string, hash);
		hashes_t[hash_c++] = hash;
	}

	return hash;
}
#endif

#ifdef UI_SearchStringForHash_HOOK
char* UI_SearchStringForHash_hook(unsigned int hash)
{
	char* string = vars->hook[UI_SearchStringForHash].Stub<char*>(hash);

	bool f = false;
	for (int i = 0; i < hash_c; i++)
		if (hashes_t[i] == hash)
			f = true;
	 
	if (!f) {
		_sys_printf("%d) %s 0x%X\n", hash_c, string, hash);
		hashes_t[hash_c++] = hash;
	}

	return string;
}
#endif

#ifdef DALManager_GetInt_HOOK
//0x1B6B car class 0 - special 1 - exotic 2 - muscle 3 - tuner
int DALManager_GetInt_hook(int dalmanager, int offset, int* r5, int r6, int r7, int r8)
{
	int ret = vars->hook[DALManager_GetInt].Stub<int>(dalmanager, offset, r5, r6, r7, r8);

	if (offset != 0x13BF && offset != 0x13C1 && offset != 0xBC7 && offset != 0x1B6B) {
		_sys_printf("GetInt offset 0x%X r5 %d, r6 %d,r7 %d,r8 %d\n", offset, *r5, r6, r7, r8); }

	return ret;
}
#endif

#ifdef FEHashUpper_HOOK
unsigned int FEHashUpper_hook(const char* string)
{
	unsigned int hash = vars->hook[FEHashUpper].Stub<unsigned int>(string);

	bool f = false;
	for (int i = 0; i < hash_c; i++)
		if (hashes_t[i] == hash)
			f = true;

	if (!f) {
		unsigned int hashLO = 0xff;
		//if (string != NULL) hashLO = Hasher_Function_r((char*)string);
		_sys_printf("%s 0x%X -> 0x%x\n", string, hash, hashLO);
		hashes_t[hash_c++] = hash;
	}

	return hash;
}
#endif

#ifdef EngineRacer_OnTaskSimulate_HOOK
void EngineRacer_OnTaskSimulate_hook(EngineLogic_t* engine, float f1)
{
	//if (engine == vars->engine) cout("%f	%f	%f\n", engine->SomeDelta, engine->EngineRPS, engine->ClutchRPS);

	vars->hook[EngineRacer_OnTaskSimulate].Stub<void>(engine, f1);
}
#endif

#ifdef UI_PassAssetArray_HOOK
bool refresh_elements = false;
int UI_PassAssetArray_Hook(int r3, MenuInfo* r4, int count, asset_t* assets)
{
	int ret = vars->hook[UI_PassAssetArray].Stub<int>(r3, r4, count, assets);
	refresh_elements = false;
	//for (int i = 0; i < count; i++) _sys_printf("%d %s	0x%X\n", assets[i].type, assets[i].name, assets[i].hash_upper);
	return ret;
}
#endif

#ifdef Huds_SetupElement_HOOK
int Huds_SetupElement_Hook(ui_main_t* ui_main, ui_struct2* ui_params, int size)
{
	int ret = vars->hook[Huds_SetupElement].Stub<int>(ui_main, ui_params, size);

	if (size == 0x6C)
	{
		if (!refresh_elements)
		{
			memset(&vars->shaderelements, 0, 20 * 4);
			vars->shadersnum = 0;
			_sys_printf("refresh_elements : \n");
			refresh_elements = true;
		}
		vars->shaderelements[vars->shadersnum++] = ui_main->elem;
		_sys_printf("elem 0x%X base 0x%X next 0x%X\n", ui_main->elem, ui_main->base, ui_main->next);
	}

	return ret;
}
#endif

#ifdef FEColor_CopyColor_HOOK
void FEColor_CopyColor_Hook(FEColor* dst, FEColor* src)
{
	//_sys_printf("Caller 0x%X\n", __builtin_return_address());
	vars->hook[FEColor_CopyColor].Stub<void>(dst, src);

	dst->r = fade.red;
	dst->g = fade.green;
	dst->b = fade.blue;
}
#endif

#ifdef FE_Object_GetObjectColor_HOOK
int FE_Object_GetObjectColor_Hook(FEColor* dst, int* r4)
{
	//_sys_printf("Caller 0x%X\n", __builtin_return_address());

	int ret = vars->hook[FE_Object_GetObjectColor].Stub<int>(dst, r4);

	dst->r = fade.red;
	dst->g = fade.green;
	dst->b = fade.blue;

	return ret;
}
#endif

#ifdef StringToKey_HOOK
unsigned int StringToKey_hook(const char* string)
{
	unsigned int hash = vars->hook[StringToKey].Stub<unsigned int>(string);

	bool f = false;
	for (int i = 0; i < hash_c; i++)
		if (hashes_t[i] == hash)
			f = true;

	if (!f) {
		_sys_printf("0x%X	%s 0x%X\n", __builtin_return_address(),string, hash);
		hashes_t[hash_c++] = hash;
	}

	return hash;
}
#endif

#ifdef Hasher_Function_HOOK
unsigned int Hasher_Function_hook(const char* string)
{
	unsigned int hash = vars->hook[Hasher_Function].Stub<unsigned int>(string);

	bool f = false;
	for (int i = 0; i < hash_c; i++)
		if (hashes_t[i] == hash)
			f = true;

	if (!f) {
		_sys_printf("0x%X	%s 0x%X\n", __builtin_return_address(), string, hash);
		hashes_t[hash_c++] = hash;
	}

	return hash;
}
#endif

#ifdef CarRenderInfo_Render_HOOK
int flagsrendervar = 0x400;
int CarRenderInfo_Render_hook(int CarRenderInfo, int eView, Vector3* pos, Matrix44* shape, Matrix44* wheels, Matrix44* r8, Matrix44* r9, int flags, int CARPART_LOD_1, int CARPART_LOD_2, float f1)
{
	//cout("Pos %f %f %f\n", pos->x, pos->y, pos->z);

	pos->x += debugVec3[0][0];
	pos->y += debugVec3[0][1];
	pos->z += debugVec3[0][2];

	*(float*)0x101C9D20 = Matrix43_[0][0];
	*(float*)0x101C9D24 = Matrix43_[0][1];
	*(float*)0x101C9D28 = Matrix43_[0][2];

	return vars->hook[CarRenderInfo_Render].Stub<int>(CarRenderInfo, eView, pos, shape, wheels, r8, r9, flags, CARPART_LOD_1, CARPART_LOD_2, f1);
}
#endif

bool foundengine = false;
#ifdef PVehicle_PVehicle_HOOK
void PVehicle_PVehicle_hook(PVehicle* self, int DriverClass, int* AttribGenpvehicle, Vector3* v1, Vector3* v2, int* Bounds, int* VehicleCustomizations, int* PVehicle_Resource, int* Physics_Info_Performance, char const* Manager)
{
	foundengine = false;
	_sys_printf("PVehicle 0x%X, Class %d ", self, DriverClass);
	cout("[%.2f][%.2f][%.2f] [%.2f][%.2f][%.2f] %s\n", v1->x, v1->y, v1->z, v2->x, v2->y, v2->z, Manager);

	vars->hook[PVehicle_PVehicle].Stub<void>(self, DriverClass, AttribGenpvehicle, v1, v2, Bounds, VehicleCustomizations, PVehicle_Resource, Physics_Info_Performance, Manager);
}
#endif

#ifdef AIVehicleHuman_FetchInput_HOOK
void AIVehicleHuman_FetchInput_hook(AIVehicleHuman* self)
{
	BehaviorList* l = self->pvehicle->behaviors.mBegin;

	if (l && foundengine == false)
	{
		for (int i = 0; i < self->pvehicle->behaviors.mSize; i++)
		{
			Behavior* behavior = l->behavior;
			if (behavior) {
				//_sys_printf("0x%X , 0x%X - 0x%X\n", behavior->hash1, behavior->hash2, behavior);
				if (behavior->hash1 == 0xA3E13328 && behavior->hash2 == 0xB2809518) {
					vars->engine = (EngineLogic_t*)behavior;
					foundengine = true;
					break;
				}
				l = l->next;
			}
		}
	}

	vars->hook[AIVehicleHuman_FetchInput].Stub<void>(self);
}
#endif

int functionhooks[][2] = {
	#ifdef CellPad_HOOK
	0x8DAFD4,(int)CellPad_Hook,
	#endif
	#ifdef Handle_All_Drawing_HOOK
	0x2C1484, (int)Handle_All_Drawing_hook,
	#endif
	#ifdef EngineRacer_GetEngineTorque_HOOK
	0x462520, (int)EngineRacer_GetEngineTorque_hook,
	#endif
	#ifdef stringhash32_HOOK
	0x3178F4, (int)stringhash32_hook,
	#endif
	#ifdef UI_SearchStringForHash_HOOK
	0x2478FC, (int)UI_SearchStringForHash_hook,
	#endif
	#ifdef DALManager_GetInt_HOOK
	0x10392C, (int)DALManager_GetInt_hook,
	#endif
	#ifdef FEHashUpper_HOOK
	0x2F1628, (int)FEHashUpper_hook,
	#endif
	#ifdef EngineRacer_OnTaskSimulate_HOOK
	0x4861AC, (int)EngineRacer_OnTaskSimulate_hook,
	#endif
	#ifdef UI_PassAssetArray_HOOK
	0x25B70C, (int)UI_PassAssetArray_Hook,
	#endif
	#ifdef Huds_SetupElement_HOOK
	0x30F97C, (int)Huds_SetupElement_Hook,
	#endif
	#ifdef FEColor_CopyColor_HOOK
	0x2F0860, (int)FEColor_CopyColor_Hook,
	#endif
	#ifdef FE_Object_GetObjectColor_HOOK
	0x251E78, (int)FE_Object_GetObjectColor_Hook,
	#endif
	#ifdef StringToKey_HOOK
	0xA3DA4, (int)StringToKey_hook,
	#endif
	#ifdef Hasher_Function_HOOK
	0xB9A80, (int)Hasher_Function_hook
	#endif
	#ifdef CarRenderInfo_Render_HOOK
	0x5A2758, (int)CarRenderInfo_Render_hook,
	#endif
	#ifdef PVehicle_PVehicle_HOOK
	0x447BE4, (int)PVehicle_PVehicle_hook,
	#endif
	#ifdef AIVehicleHuman_FetchInput_HOOK
	0x4B364, (int)AIVehicleHuman_FetchInput_hook
	#endif
};

void sprx_thread(uint64_t arg)
{
	//cout("%.6f %.6f\n",*(float*)0x93f8d4, *(float*)0x93f8d8);

	for (int i = 0; i < 24; i++)
	{
		vars->scrollformenus[i] = 1;
	}

	while (vars->thread)
	{
		vars->wait = vars->wait + 10.0f;
		if (!vars->isopen) {
			if (PAD_READ(R3)) {
				vars->isopen = true;
				vars->wait = 0;
			}
		}
		else {
			if (vars->scroll > tempoptions)
				vars->scroll = 1;

			if (vars->movemenu) {
				if (PAD_READ(LEFT) 
					//&& vars->x > 5.0f
					) {
					vars->x -= 4.0f;
				}
				if (PAD_READ(RIGHT) 
					//&& vars->x < 1280.0f
					) {
					vars->x += 4.0f;
				}
				if (PAD_READ(UP) 
					//&& vars->y > 25.0f
					) {
					vars->y -= 4.0f;
				}
				if (PAD_READ(DOWN) 
					//&& vars->y < 720.0f
					) {
					vars->y += 4.0f;
				}
				if (PAD_READ(CROSS) && vars->wait >= waittime) {
					vars->crossdown = true;
					vars->wait = 0;
				}
			}
			else if (!vars->lockscroll)
			{
				if (PAD_READ(LEFT)) {
					vars->leftdown = true;
				}
				if (PAD_READ(RIGHT)) {
					vars->rightdown = true;
				}
				if (vars->wait >= waittime)
				{
					if (PAD_READ(UP)) {
						vars->scroll--;
						if (vars->scroll < 1)
							vars->scroll = tempoptions;

						vars->updown = true;
						vars->scrollformenus[vars->menu_id] = vars->scroll;
						vars->wait = 0;
					}
					if (PAD_READ(DOWN)) {
						vars->scroll++;
						if (vars->scroll > tempoptions)
							vars->scroll = 1;

						vars->downdown = true;
						vars->scrollformenus[vars->menu_id] = vars->scroll;
						vars->wait = 0;
					}
					if (PAD_READ(CROSS)) {
						vars->crossdown = true;
					}
					if (PAD_READ(CIRCLE)) {
						if (vars->menu_id > MENU_MAIN) {
							vars->menu_id = vars->menu_return;
							vars->scroll = vars->scrollformenus[vars->menu_id];
							vars->wait = 0;
						}
						else {
							vars->wait = 0;
							vars->isopen = false;
						}
					}
				}
			}
			else {
				if (vars->wait >= waittime) {
					if (PAD_READ(UP)) {
						vars->updown = true;
						vars->wait = 0;
					}
					if (PAD_READ(DOWN)) {
						vars->downdown = true;
						vars->wait = 0;
					}
					if (PAD_READ(CROSS)) {
						vars->crossdown = true;
						vars->wait = 0;
					}
					if (PAD_READ(CIRCLE)) {
						vars->circledown = true;
						vars->wait = 0;
					}
				}
			}
		}
		fadecolor(fade, vars->fadetime);
		memset(&vars->pad_data, 0, sizeof(CellPadData));
		sleep(10);
	}
	sys_ppu_thread_exit(0);
}

extern "C" int _NFSC_prx_entry(void)
{
	PadInit();
	cellPadInit(1);

	sys_mutex_attribute_t attr;
	sys_mutex_attribute_initialize(attr);
	sys_mutex_create(&vars->mymtx, &attr);

	uimain.loopNum = 5;

	elem_setup.type1 = 0x05000000;
	elem_setup.sizecount1 = 0x44000000;
	elem_setup.type2 = 0x01000000;
	elem_setup.sizecount2 = 0x54000000;
	elem_setup.type3 = 0x02000000;
	elem_setup.sizecount3 = 0x44000000;
	elem_setup.type4 = 0x0c000000;
	elem_setup.sizecount4 = 0x90000000;
	elem_setup.type5 = 0x00000000;
	elem_setup.sizecount5 = 0x94000000;

	uimain.somestruct = &elem_setup;

	vars->scroll = 1;
	vars->menu_id = MENU_MAIN;
	vars->menu_return = MENU_MAIN;
	vars->x = 750.0f;

	config->scrollspeed = 150.0f;

#ifdef hen_compatibility
	sleep(20 * 1000);
#endif

	for (int i = 0; i < (sizeof(functionhooks) / 8); i++)
		vars->hook[i].Hook(functionhooks[i][0], functionhooks[i][1]);

#ifndef hen_compatibility
	printmemory();
#endif // !hen_compatibility

#ifdef recording_util
	RecordInit();
	printmemory();
#endif
	vars->thread = true;
	sys_ppu_thread_create(&vars->id,sprx_thread,0,2000,4096,0,"sprx_thread");
    return SYS_PRX_RESIDENT;
}

extern "C" int RestoreHooks(void)
{
#ifdef recording_util
	RecordingClose();
#endif
	vars->thread = false;
	sleep(150);
	for (int i = 0; i < (sizeof(functionhooks) / 8); i++)
		vars->hook[i].Restore();

	sys_mutex_destroy(vars->mymtx);

	memset(vars,0,sizeof(needformods));
	memset(config, 0, sizeof(config_t));
    return SYS_PRX_RESIDENT;
}