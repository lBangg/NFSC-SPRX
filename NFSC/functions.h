void PadInit()
{
	vars->pdPadBtn[0].btnData = 0;
	vars->pdPadBtn[1].btnData = CELL_PAD_CTRL_CROSS;
	vars->pdPadBtn[2].btnData = CELL_PAD_CTRL_CIRCLE;
	vars->pdPadBtn[3].btnData = CELL_PAD_CTRL_SQUARE;
	vars->pdPadBtn[4].btnData = CELL_PAD_CTRL_TRIANGLE;
	vars->pdPadBtn[5].btnData = CELL_PAD_CTRL_L1;
	vars->pdPadBtn[6].btnData = CELL_PAD_CTRL_R1;
	vars->pdPadBtn[7].btnData = CELL_PAD_CTRL_L3;
	vars->pdPadBtn[8].btnData = CELL_PAD_CTRL_R3;
	vars->pdPadBtn[9].btnData = CELL_PAD_CTRL_L2;
	vars->pdPadBtn[10].btnData = CELL_PAD_CTRL_R2;
	vars->pdPadBtn[11].btnData = CELL_PAD_CTRL_UP;
	vars->pdPadBtn[12].btnData = CELL_PAD_CTRL_DOWN;
	vars->pdPadBtn[13].btnData = CELL_PAD_CTRL_LEFT;
	vars->pdPadBtn[14].btnData = CELL_PAD_CTRL_RIGHT;
	vars->pdPadBtn[0].btnDigital = 0;
	vars->pdPadBtn[1].btnDigital = 1;
	vars->pdPadBtn[2].btnDigital = 1;
	vars->pdPadBtn[3].btnDigital = 1;
	vars->pdPadBtn[4].btnDigital = 1;
	vars->pdPadBtn[5].btnDigital = 1;
	vars->pdPadBtn[6].btnDigital = 1;
	vars->pdPadBtn[7].btnDigital = 0;
	vars->pdPadBtn[8].btnDigital = 0;
	vars->pdPadBtn[9].btnDigital = 1;
	vars->pdPadBtn[10].btnDigital = 1;
	vars->pdPadBtn[11].btnDigital = 0;
	vars->pdPadBtn[12].btnDigital = 0;
	vars->pdPadBtn[13].btnDigital = 0;
	vars->pdPadBtn[14].btnDigital = 0;
}

enum cellpadkeys
{
	pad,
	CROSS,
	CIRCLE,
	SQUARE,
	TRIANGLE,
	L1,
	R1,
	L3,
	R3,
	L2,
	R2,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

bool __attribute__((noinline)) PAD_READ(int button)
{
	cellPadButtonData Monitor = vars->pdPadBtn[button];
	uint16_t Digital;
	if (!Monitor.btnDigital)
	{
		Digital = vars->pad_data.button[CELL_PAD_BTN_OFFSET_DIGITAL1];
	}
	else
	{
		Digital = vars->pad_data.button[CELL_PAD_BTN_OFFSET_DIGITAL2];
	}
	return (Digital & Monitor.btnData) > 0;
}

void printmemory()
{
	uint32_t meminfo[2];
	system_call_1(352, (uint64_t)&meminfo);
	_sys_printf("Free Memory: %i KB / %i MB\n", meminfo[1] / 1024, (meminfo[0] / 1024) / 1024);
}

int sprintf_t[2] = { 0xBCF84 ,TOC };
int (*sprintf_f)(char* buffer, int size, ...) = (int(*)(char*, int, ...))sprintf_t;

ulonglong malloc(undefined8 param_1, ulonglong param_2)
{
}
void FUN_000ba6b8(char* param_1, char* param_2, int param_3)
{
}

void wchar_cpy(char* str, wchar_t* wstr)
{
	if (wstr != 0x0 && wstr[0] != 0)
	{
		int i = 0;
		do
		{
			str[i] = wstr[i];
			i++;
		} while (wstr[i] != 0);
		str[i] = 0;
	}
}

void fadecolor(color& c, uint32_t& timer)
{
	c.red = (int)(sinf(0.01f * timer) * 127 + 128);
	c.green = (int)(sinf(0.01f * timer + 2) * 127 + 128);
	c.blue = (int)(sinf(0.01f * timer + 4) * 127 + 128);
	if (timer++ >= 999999999) timer = 0;
}

void ToggleDebugMenu()
{
	config->debugoptions = !config->debugoptions;
	if(config->debugoptions)
		*(char*)0x10188AD2 = 0x1;
	else
		*(char*)0x10188AD2 = 0x0;
}

void ToggleSmoke()
{
	config->disablesmoke = !config->disablesmoke;
	if (config->disablesmoke)
		*(int*)0x4DC3A8 = 0x4E800020;
	else
		*(int*)0x4DC3A8 = 0X812238AC;
}

void ToggleTraffic()
{
	config->disabletraffic = !config->disabletraffic;
	if (config->disabletraffic)
		*(char*)0x100D3185 = 1;//Tweak_TrafficStopSpawning
	else
		*(char*)0x100D3185 = 0;
}

int UI_SearchStringForHash_t[2] = { 0x2478FC ,TOC };
char* (*UI_SearchStringForHash_f)(unsigned int hash) = (char*(*)(unsigned int))UI_SearchStringForHash_t;

int UI_WideCharLen_t[2] = { 0x2F1BE4 ,TOC };
int (*UI_WideCharLen)(wchar_t* str) = (int(*)(wchar_t*))UI_WideCharLen_t;

int Game_ActivateDriftMode_t[2] = { 0x39783C ,TOC };
void(*Game_ActivateDriftMode)() = (void(*)())Game_ActivateDriftMode_t;

int Game_DeactivateDriftMode_t[2] = { 0x389F58 ,TOC };
void(*Game_DeactivateDriftMode)() = (void(*)())Game_DeactivateDriftMode_t;

void ToggleDriftMode()
{
	config->driftmode = !config->driftmode;
	if(config->driftmode)
		Game_ActivateDriftMode();
	else
		Game_DeactivateDriftMode();
}

int Draw_Caller_Internal_t[2] = { 0x290338 ,TOC };
void (*Draw_Caller_Internal)(int r3, element_t* elem) = (void(*)(int, element_t*))Draw_Caller_Internal_t;

int Hud_ShowMessage_t[2] = { 0x39790C ,TOC };
void(*Hud_ShowMessage)(const char* str) = (void(*)(const char*))Hud_ShowMessage_t;

int Hasher_Function_t[2] = { 0xB9A80 ,TOC };
uint (*Hasher_Function_f)(const char* str) = (uint(*)(const char*))Hasher_Function_t;

int Draw_GetFontPointer_t[2] = { 0x2573C8 ,TOC };
int(*Draw_GetFontPointer)(int hash) = (int(*)(int))Draw_GetFontPointer_t;

int FEngFont_GetTextWidth_t[2] = { 0x274560 ,TOC };
float(*FEngFont_GetTextWidth)(int font_hash, wchar_t* str, int flag) = (float(*)(int,wchar_t*,int))FEngFont_GetTextWidth_t;

int Draw_SetupDrawCmdStruct_t[2] = { 0x277864 ,TOC };
DrawCmd_t*(*Draw_SetupDrawCmdStruct)(int r3, element_t* elem, int font) = (DrawCmd_t*(*)(int, element_t *, int))Draw_SetupDrawCmdStruct_t;

int drawtext_t[2] = { 0x28F050 ,TOC };
void (*drawtext_f)(int font, FEColor* r4, wchar_t* r5, element_t* r6, OptionsUnion* r7, DrawCmd_t* r8) = (void(*)(int, FEColor*, wchar_t*, element_t*, OptionsUnion*, DrawCmd_t*))drawtext_t;

int Draw_AddText_t[2] = { 0x28F544 ,TOC };
void (*Draw_AddText)(int r3, element_t* elem, DrawCmd_t* drawcmd) = (void(*)(int, element_t *, DrawCmd_t *))Draw_AddText_t;

int UI_SetupRenderParams_t[2] = { 0x30E2D0 ,TOC };
void (*UI_SetupRenderParams)(element_t* elem, int size) = (void(*)(element_t *, int))UI_SetupRenderParams_t;

int UI_SetupElementText_t[2] = { 0x30BBE8 ,TOC };
void (*UI_SetupElementText)(element_t* elem) = (void(*)(element_t * elem))UI_SetupElementText_t;

int Huds_AllocElement_t[2] = { 0x30E338 ,TOC };
element_t*(*Huds_AllocElement)(ui_main_t* elem, int type) = (element_t*(*)(ui_main_t * ,int))Huds_AllocElement_t;

int setup_parameters_t[2] = { 0x2F2B48 ,TOC };
void(*setup_parameters)(Text_Options* elem) = (void(*)(Text_Options*))setup_parameters_t;

element_t* TextElement(int font)
{
	element_t* element = Huds_AllocElement(&uimain, 2);
	if (element == NULL)
	{
		_sys_printf("element allocation NULL\n");
		__asm("trap");
	}
	else
	{
		element->text.alloc_text_len = 0x32;
		element->text.render_flags = 0x43800002;
		element->text.font_hash = font;
		setup_parameters(&element->text.settings->opt.text);
	}
	return element;
}

element_t* ShaderElement(int material)
{
	element_t* element = Huds_AllocElement(&uimain, 1);
	if (element == NULL)
	{
		_sys_printf("element allocation NULL\n");
		__asm("trap");
	}
	else
	{
		element->shader.material_hash = material;
		element->shader.render_flags = 0x43800002;
		setup_parameters((Text_Options*)&element->shader.settings->opt.shader);
		element->shader.settings->opt.shader.s0 = 0.0f;
		element->shader.settings->opt.shader.t0 = 0.0f;
		element->shader.settings->opt.shader.s1 = 1.0f;
		element->shader.settings->opt.shader.t1 = 1.0f;
		element->shader.settings->opt.shader.field0x44 = 0.0f;
		element->shader.settings->opt.shader.field0x48 = 0.0f;
		element->shader.settings->opt.shader.field0x4C = 0.0f;
		element->shader.settings->opt.shader.field0x50 = 0.0f;
	}
	return element;
}

uint Hasher_Function_r(char* str)
{
	byte bVar1 = *str;
	uint uVar2 = -1;
	uint uVar3;
	if (bVar1 != 0)
	{
		do {
			uVar3 = (ulonglong)bVar1;
			str = (char*)((ulonglong)(str + 1) & 0xffffffff);
			bVar1 = *str;
			uVar2 = (uint)((int)uVar2 << 5) + uVar2 + uVar3 & 0xffffffff;
		} while (bVar1 != 0);
	}
	return uVar2;
}

void str_toupper(char* temp) {
	char* s = temp;
	while (*s) {
		*s = toupper((unsigned char)*s);
		s++;
	}
}

struct ui_struct2 {
    short ui_type;//0x0
    short field_0x2;//0x2
    uint elem_type;//0x4
};

uint32_t swap_uint32(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

//! Byte swap int
int32_t swap_int32(int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

typedef struct _D3DMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} D3DMATRIX;

#define Width 1280
#define Height 720

D3DMATRIX* D3DXMatrixTranspose(D3DMATRIX* pout, const _D3DMATRIX* pm)
{
	const _D3DMATRIX m = *pm;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pout->m[i][j] = m.m[j][i];
		}
	}

	return pout;
}

_D3DMATRIX viewMatrix;
bool WorldToScreen(Vector3* origin, Vector2* out)
{
	_D3DMATRIX temp;


	D3DXMatrixTranspose(&temp, &viewMatrix);

	Vector3 translationVector = Vector3(temp._41, temp._42, temp._43);
	Vector3 up = Vector3(temp._21, temp._22, temp._23);
	Vector3 right = Vector3(temp._11, temp._12, temp._13);

	float w = origin->DotProduct(translationVector) + temp._44;

	if (w < 0.098f)
		return false;

	float y = origin->DotProduct(up) + temp._24;
	float x = origin->DotProduct(right) + temp._14;

	out->x = (int)(Width / 2) * (1.f + x / w);
	out->y = (int)(Height / 2) * (1.f - y / w);

	return true;
}

int Game_JumpToSafeHouse_t[2] = { 0x397CC8 ,TOC };
void(*Game_JumpToSafeHouse)() = (void(*)())Game_JumpToSafeHouse_t;

void jumptosf(int r3)
{
	Game_JumpToSafeHouse();
}

#include "rebuilt.h"