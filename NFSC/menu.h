#include "menu_backend.h"


void DrawInfo(drawparams* r3)
{
	float yc = -245.f;
	addInfo(vars->my_text, wide_va("Ingame : %d", r3->inGame), -460.0f, yc, 0.8f);
	yc += 22.0f;
	if (cFEng_mInstance != NULL)
	{
		if ((int)cFEng_mInstance->menuinfo1->MenuName != 0xEEEEEEEE)
		{
			addInfo(vars->my_text, wide_va("%s", cFEng_mInstance->menuinfo1->MenuName), -460.0f, yc, 0.8f);
			yc += 22.0f;
			addInfo(vars->my_text, wide_va("FPS %.1f", (float)(1000 / cFEng_mInstance->menuinfo1->frametime)), -460.0f, yc, 0.8f);
			yc += 22.0f;
			addInfo(vars->my_text, wide_va("X=%.1f", vars->x), -460.0f, yc, 0.8f);
			yc += 22.0f;
			addInfo(vars->my_text, wide_va("Y=%.1f", vars->y), -460.0f, yc, 0.8f);
			yc += 22.0f;
		}
	}
	if (r3->inGame && vars->engine != NULL)
	{
		addInfo(vars->my_text, wide_va("%.1f rpm", vars->engine->rpm), -460.0f, yc, 0.8f);
		yc += 22.0f;
		addInfo(vars->my_text, wide_va("%.2f HP", ((vars->enginetorque * vars->engine->rpm) / 9550.0f) * 1.34), -460.0f, yc, 0.8f);
		yc += 22.0f;
		addInfo(vars->my_text, wide_va("torque %.1f", vars->enginetorque), -460.0f, yc, 0.8f);
	}
}

#ifdef recording_util
void toggleRec()
{
	if (isRecON == false)
	{
		cellRecStart();
		isRecON = true;
	}
	else if (isRecON == true)
	{
		cellRecStop();
		isRecON = false;
	}
}
#endif

int tempoptions = 0;
int vecd1_s = 0, vecd2_s = 0, vecd3_s = 0;
void drawmenu()
{
	float height = tempoptions * 15.0f;
	DrawShader(vars->my_shader, vars->x - 390.0f, vars->y - 225.0f + height / 2, 160.0f, height + 4.0f, &background);

	switch (vars->menu_id)
	{
	case MENU_MAIN:
		LoadSub(vars->my_text, L"Car Settings", MENU_CARSETTINGS);
		LoadSub(vars->my_text, L"World Modifications", MENU_WORLD);
		LoadSub(vars->my_text, L"Misc", MENU_MISC);
		BoolOption(vars->my_text, L"Move Menu", vars->movemenu);

		DebuggerOption(vars->my_text, L"Position", (float*)&debugVec3, 1, 3, vecd1_s, -10.0f, 10.0f);
		DebuggerOption(vars->my_text, L"Matrix [4][4]", (float*)&Matrix44_, 4, 4, vecd2_s, -2.0f, 2.0f);
		DebuggerOption(vars->my_text, L"Matrix [4][3]", (float*)&Matrix43_, 4, 3, vecd3_s, -1.0f, 1.0f);
		break;
	case MENU_CARSETTINGS:
		BoolOption(vars->my_text, L"Drift Mode", config->driftmode, ToggleDriftMode);
		BoolOption(vars->my_text, L"Torque Mod", config->customtorque);
		if (config->customtorque) SliderOption(vars->my_text, L"Torque Value", config->torquevalue, 1.0f, 100.0f);
		if (vars->engine != NULL)
		{
			//LoadSub(vars->my_text, L"Transmission", MENU_C_Transmission);
			//LoadSub(vars->my_text, L"Torque", MENU_C_Torque);
			//LoadSub(vars->my_text, L"Nitrous", MENU_C_Nitrous);
			//LoadSub(vars->my_text, L"Intake", MENU_C_Intake);

			SliderOption(vars->my_text, L"1st", vars->engine->GearRatios.table->gearratio[0], 2.0f, 6.0f);
			SliderOption(vars->my_text, L"2nd", vars->engine->GearRatios.table->gearratio[1], 1.0f, 4.0f);
			SliderOption(vars->my_text, L"3rd", vars->engine->GearRatios.table->gearratio[2], 0.8f, 3.0f);
			SliderOption(vars->my_text, L"4th", vars->engine->GearRatios.table->gearratio[3], 0.5f, 2.0f);
			SliderOption(vars->my_text, L"5th", vars->engine->GearRatios.table->gearratio[4], 0.4f, 2.0f);
			SliderOption(vars->my_text, L"6th", vars->engine->GearRatios.table->gearratio[5], 0.3f, 1.0f);
			SliderOption(vars->my_text, L"7th", vars->engine->GearRatios.table->gearratio[6], 0.2f, 0.9f);
		}
		break;
	case MENU_WORLD:
		BoolOption(vars->my_text, L"Disable Smoke", config->disablesmoke, ToggleSmoke);
		BoolOption(vars->my_text, L"Disable Traffic", config->disabletraffic, ToggleTraffic);
		break;
	case MENU_MISC:
		BoolOption(vars->my_text, L"Debug Menu", config->debugoptions, ToggleDebugMenu);
		AddOption(vars->my_text, L"Jump to Safehouse", jumptosf, 0);
#ifdef recording_util
		BoolOption(vars->my_text, L"Recording", isRecON, toggleRec);
#endif
		break;
	}
}