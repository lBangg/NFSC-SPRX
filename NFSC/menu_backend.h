#define maxW 928.0f
#define maxH 516.0f

void __attribute__((noinline)) DrawText(element_t* elem, const wchar_t* text, float x, float y, float w, float h, color* col)
{
	elem->text.text = (wchar_t*)text;
	elem->text.settings->col.r = col->red;
	elem->text.settings->col.g = col->green;
	elem->text.settings->col.b = col->blue;
	elem->text.settings->col.a = 255;
	elem->text.settings->opt.text.x_pos = x;
	elem->text.settings->opt.text.y_pos = y;
	elem->text.settings->opt.text.w = w;
	elem->text.settings->opt.text.h = h;
	Draw_Caller_Internal(*(int*)0x10180724, elem);
}

void __attribute__((noinline)) DrawShader(element_t* elem, float x, float y, float w, float h, color* col)
{
	//x = x - maxW / 2 + w / 2;

	elem->shader.settings->col.r = col->red;
	elem->shader.settings->col.g = col->green;
	elem->shader.settings->col.b = col->blue;
	elem->shader.settings->col.a = col->alpha;
	elem->shader.settings->opt.shader.x_pos = x;
	elem->shader.settings->opt.shader.y_pos = y;
	elem->shader.settings->opt.shader.w = w;
	elem->shader.settings->opt.shader.h = h;
	Draw_Caller_Internal(*(int*)0x10180724, elem);
}

void drawOption(element_t* elem, const wchar_t* Option, bool crossbug = false)
{
	if (crossbug && vars->crossdown)
		vars->crossdown = false;

	vars->optionsNum++;
	DrawText(elem, Option, vars->x - 450.0f, vars->y - 240.0f + (vars->optionsNum * 15.0f), 0.75f, 0.75f, vars->scroll == vars->optionsNum ? &fade : &white);
}

bool __attribute__((noinline)) LoadSub(element_t* elem, const wchar_t* subname, short menu_id)
{
	drawOption(elem, subname);
	if (vars->crossdown && vars->optionsNum == vars->scroll)
	{
		vars->wait = 0;
		vars->crossdown = false;
		vars->menu_return = vars->menu_id;
		vars->menu_id = menu_id;
		vars->scroll = 1;
	}
}

void __attribute__((noinline)) AddOption(element_t* elem, const wchar_t* Option, void(*functionToCall)(int), int param)
{
	drawOption(elem, Option);
	if (vars->crossdown && vars->optionsNum == vars->scroll)
	{
		vars->wait = 0;
		vars->crossdown = false;
		functionToCall(param);
	}
}

void __attribute__((noinline)) BoolOption(element_t* elem2, const wchar_t* Option, bool& toggle, void(*functionToCall)() = NULL)
{
	drawOption(elem2, Option);
	DrawShader(vars->checkmark, vars->x - 340.0f, vars->y - 232.0f + vars->optionsNum * 15.0f, 17.0f, 17.0f, toggle ? &fade : &gray);
	if (vars->crossdown && vars->optionsNum == vars->scroll)
	{
		vars->crossdown = false;

		if (functionToCall != NULL)
			functionToCall();
		else
			toggle = !toggle;

		vars->wait = 0;
	}
}

void __attribute__((noinline)) SliderOption(element_t* elem, const wchar_t* Option, float& flvar, float minV, float maxV)
{
	drawOption(elem, Option);
	float inc = (maxV - minV) / 100;
	float value2pos = (maxV - flvar) / inc;
	char floatbuffer[16];
	wchar_t txt[16];
	memset(txt, 0, 16);
	Com_Sprintf(floatbuffer, 16, "%f", flvar);
	chartowide(floatbuffer, txt);
	DrawText(elem, txt, vars->x - 360.0f, vars->y - 240.0f + vars->optionsNum * 15.0f, 0.75f, 0.75f, &white);

	if (vars->optionsNum == vars->scroll)
	{
		if (vars->leftdown)
			flvar = flvar - inc, vars->leftdown = false;
		else if (vars->rightdown)
			flvar = flvar + inc, vars->rightdown = false;
	}

	if (flvar < minV)
		flvar = minV;

	if (flvar > maxV)
		flvar = maxV;

	vars->crossdown = false;
}

void __attribute__((noinline)) SliderIntOption(element_t* elem, const wchar_t* Option, int& ivar, const int minV, const int maxV)
{
	drawOption(elem, Option);
	char floatbuffer[16];
	wchar_t txt[16];
	memset(txt, 0, 16);
	Com_Sprintf(floatbuffer, 16, "%i", ivar);
	chartowide(floatbuffer, txt);
	DrawText(elem, txt, vars->x - 360.0f, vars->y - 240.0f + vars->optionsNum * 15.0f, 0.75f, 0.75f, &white);

	if (vars->optionsNum == vars->scroll)
	{
		if (vars->leftdown)
			ivar--, vars->leftdown = false;
		else if (vars->rightdown)
			ivar++, vars->rightdown = false;
	}

	if (ivar < minV)
		ivar = minV;

	if (ivar > maxV)
		ivar = maxV;
}

void __attribute__((noinline)) TextOption(element_t* elem, const wchar_t* Option, const wchar_t* Mod[], short& index, int sizeofarray)
{
	drawOption(elem, Option);
	DrawText(elem, Mod[index], vars->x - 60.0f, (vars->optionsNum * 18 + vars->y), 0.8f, 0.8f, vars->scroll == vars->optionsNum ? &fade : &white);
	if (vars->optionsNum == vars->scroll)
	{
		if (vars->lockscroll)
		{
			float x = vars->x + 2.0f;
			float y = vars->y;
			float height = ((sizeofarray <= 8) ? sizeofarray * 16.0f : 140.0f);
			//DrawShader(vars->white, x + 1, y, 100, height, BackgroundColor, data_s->m_white);//background
			//DrawShader(vars->white, x, y - 2.0f, 98, 3.0f, Colors[config->menucolor], data_s->m_white); // Top
			//DrawShader(vars->white, x, y + height, 98, 3.0f, Colors[config->menucolor], data_s->m_white); // Bottom
			//DrawShader(vars->white, x + 98, y - 2.0f, 3.0f, height + 5.0f, Colors[config->menucolor], data_s->m_white); // Right
			for (int i = 0; i < sizeofarray; i++)
			{
				float y = -1000.0f;
				if (vars->textscroll <= 8 && i <= 8)
					y = i * 15 + vars->y + 18.0f;
				else if ((i >= (vars->textscroll - 8)) && i <= vars->textscroll)
					y = ((i - (vars->textscroll - 8)) * 15) + vars->y + 18.0f;

				//if (y != -1000.0f) DrawText(elem,Mod[i], vars->x + 4, y, 0.8f, 0.9f, vars->textscroll == i ? Colors[config->menucolor] : Colors[WHITE]);
			}

			if (vars->updown)
			{
				vars->updown = false;
				if (vars->textscroll > 0)
					vars->textscroll--;
				else
					vars->textscroll = sizeofarray - 1;
				vars->wait = 0;
			}
			if (vars->downdown)
			{
				vars->downdown = false;
				if (vars->textscroll < sizeofarray - 1)
					vars->textscroll++;
				else
					vars->textscroll = 0;
				vars->wait = 0;
			}
			if (vars->circledown)
			{
				vars->circledown = false;
				vars->lockscroll = false;
				vars->wait = 0;
			}
		}
		if (vars->crossdown)
		{
			if (!vars->lockscroll)
			{
				vars->textscroll = index;
				vars->lockscroll = true;
				vars->downdown = false;
				vars->updown = false;
			}
			else
			{
				index = vars->textscroll;
			}
			vars->wait = 0;
			vars->crossdown = false;
		}
	}
}

void __attribute__((noinline)) DebuggerOption(element_t* elem, const wchar_t* Option, float* ArVal, int x, int y, int& selector, float minV, float maxV)
{
	drawOption(elem, Option);
	float inc = (maxV - minV) / 100;
	char floatbuffer[16];
	wchar_t txt[16];
	memset(txt, 0, 16);

	int r = selector / y;
	int c = selector % y;

	Com_Sprintf(floatbuffer, 16, "[%d][%d] %f", r, c, ArVal[selector]);
	chartowide(floatbuffer, txt);
	DrawText(elem, txt, vars->x - 380.0f, vars->y - 240.0f + vars->optionsNum * 15.0f, 0.75f, 0.75f, 
		vars->lockscroll && (vars->optionsNum == vars->scroll) ? &fade : &white);

	if (vars->optionsNum == vars->scroll) {
		if (vars->lockscroll) {
			if (vars->updown)
			{
				if (selector > 0)
					selector--;
				else
					selector = 0;

				vars->updown = false;
				vars->wait = 0;
			}
			if (vars->downdown)
			{
				if (selector < (x * y) - 1)
					selector++;
				else
					selector = (x * y) - 1;

				vars->downdown = false;
				vars->wait = 0;
			}
			if (vars->circledown)
			{
				vars->circledown = false;
				vars->lockscroll = false;
				vars->wait = 0;
			}
		}
		else
		{
			if (vars->leftdown)
				ArVal[selector] = ArVal[selector] - inc, vars->leftdown = false;
			else if (vars->rightdown)
				ArVal[selector] = ArVal[selector] + inc, vars->rightdown = false;

			if (ArVal[selector] < minV)
				ArVal[selector] = minV;

			if (ArVal[selector] > maxV)
				ArVal[selector] = maxV;
		}
	}

	if (vars->crossdown)
	{
		if (!vars->lockscroll)
		{
			//vars->textscroll = selector;
			vars->lockscroll = true;
			vars->downdown = false;
			vars->updown = false;
		}
		else
		{
			//selector = vars->textscroll;
		}
		vars->wait = 0;
		vars->crossdown = false;
	}
}

void addInfo(element_t* elem, wchar_t* text, float x, float y, float size)
{
	float width = FEngFont_GetTextWidth(Draw_GetFontPointer(FONT_NFS_BODY), text, 0) * size + 10.0f;
	DrawShader(vars->white, x + width / 2, y, width, 25.0f * size, &fade);
	DrawShader(vars->white, x + width / 2, y, width - 3.0f, 21.5f * size, &black);
	DrawText(vars->my_text, text, x + 3.0f, y - 6.5f, size, size, &white);
}