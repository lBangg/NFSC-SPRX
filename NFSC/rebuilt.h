
//uint* FUN_002fa7c8(undefined8 ui_main, longlong param_2, uint param_3)
//{
//    uint uVar1 = *(uint*)(param_2 + 4);
//    uint* puVar3 = (uint*)(param_2 + 8);
//    uint uVar2 = *puVar3;
//    if ((uVar2 >> 8 & 0xff00 | uVar2 >> 0x18 | uVar2 << 0x18 | (uVar2 & 0xff00) << 8) == param_3) {
//        return puVar3;
//    }
//    do {
//        if ((uint*)((ulonglong)(uVar1 >> 0x18 | uVar1 << 0x18 | (uVar1 & 0xff00) << 8 | uVar1 >> 8 & 0xff00) + param_2 + 8 & 0xffffffff) == puVar3) {
//            return NULL;
//        }
//        uVar2 = puVar3[1];
//        puVar3 = (uint*)((longlong)puVar3 + (ulonglong)(uVar2 >> 0x18 | uVar2 << 0x18 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00) + 8 & 0xffffffff);
//        uVar2 = *puVar3;
//    } while ((uVar2 >> 8 & 0xff00 | (uVar2 & 0xff00) << 8 | uVar2 >> 0x18 | uVar2 << 0x18) != param_3);
//    return puVar3;
//}
//
//int* FUN_002f39b4(longlong param_1, int param_2)
//
//{
//    int iVar1;
//    int* piVar2;
//    longlong lVar3;
//    int* piVar4;
//    int* piVar5;
//
//    if (*(uint*)(param_1 + 0x84) != 0) {
//        piVar2 = (int*)(ulonglong) * (uint*)(param_1 + 0x88);
//        piVar4 = (int*)((ulonglong)(piVar2 + 3) & 0xffffffff);
//        lVar3 = ((ulonglong) * (uint*)(param_1 + 0x84) - 1 & 0xffffffff) + 1;
//        piVar5 = piVar4;
//        if (*piVar2 == param_2) {
//            return piVar2;
//        }
//        while (true) {
//            piVar2 = piVar5;
//            lVar3 += -1;
//            if (lVar3 == 0) break;
//            iVar1 = *piVar4;
//            piVar5 = (int*)((ulonglong)(piVar5 + 3) & 0xffffffff);
//            piVar4 = (int*)((ulonglong)(piVar4 + 3) & 0xffffffff);
//            if (param_2 == iVar1) {
//                return piVar2;
//            }
//        }
//    }
//    return (int*)0;
//}
//
//ulonglong FUN_003017c8(undefined8 param_1, undefined4 param_2)
//{
//    dword local_30;
//    undefined4 local_2c;
//    uint local_28;
//
//    local_30 = DWORD_0093bbdc;
//    local_28 = 0;
//    local_2c = param_2;
//    FUN_002f5cc4(param_1, (dword*)((ulonglong)&local_30 & 0xffffffff));
//    *(dword*)((ulonglong)&local_30 & 0xffffffff) = DWORD_0093bad0;
//    return (ulonglong)local_28;
//}
//
//longlong FUN_0030181c(ui_main_t* ui_main, undefined8 elementNum, uint* param_3, undefined4* param_4)
//{
//    *param_3 = 0;
//    *param_4 = 0;
//    int* lVar1 = FUN_002f39b4((ulonglong)*(uint*)ui_main, elementNum);
//    if (lVar1 != 0) {
//        longlong lVar2 = FUN_002f93f4((ulonglong)ui_main->field_0x3c, (ulonglong)*(uint*)(lVar1 + 4));
//        *param_4 = (int)lVar2;
//        if (lVar2 != 0) {
//            uint uVar3 = FUN_003017c8(lVar2, (ulonglong)*(uint*)(lVar1 + 8));
//            *param_3 = uVar3;
//            return (longlong)(int)(((int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f ^ uVar3) >> 0x1f);
//        }
//    }
//    return 0;
//}
//
//void FUN_0030f7bc(element_t* elem, longlong param_2, longlong param_3, undefined8 param_4)
//{
//
//}
//
//bool Huds_SetupElement(ui_main_t* ui_main, ui_struct2* ui_params, longlong size)
//{
//    uint uVar2, uVar5;
//    element_t* peVar6;
//    ulonglong uVar8;
//    longlong lVar9;
//    element_t* new_element;
//
//    ui_struct2* ui_type = ui_params;
//    ui_main->field_0x18 = 0;
//    ui_struct2* puVar3 = ui_params;
//    do {
//        if ((ui_struct2*)((int)ui_type + size) <= puVar3)
//            return true;
//
//        uVar5 = ((uint)ui_params->ui_type & 0xff) << 8 | (uint)(ui_params->ui_type >> 8);
//        if (uVar5 == 0x504f) {
//            uint* puVar4 = (uint*)((ulonglong)&ui_params->elem_type & 0xffffffff);
//            uVar5 = *puVar4;
//            ui_main->elem->elementNum = uVar5 >> 24 | uVar5 << 24 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00;
//            uVar5 = puVar4[1];
//            ui_main->elem->hash = uVar5 >> 24 | uVar5 << 24 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00;
//            uVar5 = puVar4[2];
//            ui_main->elem->render_flags = uVar5 >> 24 | uVar5 << 24 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00;
//            ui_main->elem->field_22 = (short)(puVar4[3] >> 24) | (short)(puVar4[3] >> 8) & 0xff00;
//            peVar6 = ui_main->elem;
//            if ((peVar6->render_flags & 0x100000) != 0)
//            {
//                lVar9 = FUN_0030181c(ui_main, peVar6->elementNum, &ui_main->field_0x1c, &ui_main->field_0x20);
//                if (lVar9 == 0)
//                {
//                    if (ui_main->elem != NULL)
//                    {
//                        //(void)((int)ui_main->elem->funcs + 4)();
//                    }
//                    ui_main->elem = (element_t*)0x0;
//                    return 0;
//                }
//                *(undefined*)&ui_main->field_0x18 = 1;
//                ui_main->elem->render_flags = ui_main->elem->render_flags | *(uint*)((ulonglong)ui_main->field_0x1c + 0x1c);
//                if (ui_main->elem->field_22 == -1)
//                {
//                    ui_main->elem->font_hash = *(undefined4*)((ulonglong)ui_main->field_0x1c + 0x24);
//                    ui_main->elem->field_28 = *(undefined4*)((ulonglong)ui_main->field_0x1c + 0x28);
//                }
//                puVar4 = (uint*)(ulonglong)ui_main->field_0x1c;
//                if (puVar4[6] == 5) {
//                    new_element = (element_t*)malloc(0x6c);
//                    FUN_0030f7bc(new_element, ui_main->field_0x1c, 0, 1);
//                }
//                else {
//                    new_element = (element_t*)(*(int*)(ulonglong) * (uint*)(ulonglong) * (uint*)((ulonglong)*puVar4 + 8))(puVar4, 1);
//                }
//                new_element->elementNum = ui_main->elem->elementNum;
//                new_element->hash = ui_main->elem->hash;
//                new_element->render_flags = ui_main->elem->render_flags;
//                new_element->field_22 = ui_main->elem->field_22;
//                new_element->font_hash = ui_main->elem->font_hash;
//                new_element->field_28 = ui_main->elem->field_28;
//                if (ui_main->elem != NULL) {
//                    //(void)((int)ui_main->elem->funcs + 4)();
//                }
//                ui_main->elem = (element_t*)new_element;
//                uVar5 = *(uint*)&new_element->pad02[0x4];
//                while (uVar5 != 0) {
//                    uVar8 = (ulonglong)uVar5;
//                    if (*(uint*)(uVar8 + 0x18) != 0) {
//                        *(undefined4*)(uVar8 + 0x18) = *(undefined4*)((ulonglong) * (uint*)(uVar8 + 0x18) + 0x30);
//                    }
//                    uVar5 = *(uint*)(uVar8 + 4);
//                }
//                peVar6 = ui_main->elem;
//            }
//            if ((peVar6->render_flags & 0x10000000) == 0) goto override_jmp_0030fa18_case_0;
//            *(element_t**)((ulonglong)(ui_main->field_0x4c << 2) + (ulonglong) * (uint*)((ulonglong) * (uint*)ui_main + 0x90) & 0xffffffff) = peVar6;
//            ui_main->field_0x4c = ui_main->field_0x4c + 1;
//            uVar5 = (uint)ui_params->field_0x2;
//        }
//        else {
//            if (uVar5 < 0x5050)
//            {
//                if (uVar5 == 0x4150)
//                {
//                    uVar5 = ui_main->field_0x10;
//                    if (uVar5 == 0) {
//                        uVar2 = ui_params->elem_type & 0xffffffff;
//                    LAB_0030fc2c:
//                        uVar5 = FUN_003017c8((ulonglong) * (uint*)ui_main, (ulonglong)(uVar2 >> 24 | uVar2 << 24 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00));
//                        ui_main->field_0x10 = uVar5;
//                    }
//                    else {
//                        uVar2 = *(uint*)((ulonglong)&ui_params->elem_type & 0xffffffff);
//                        if (*(uint*)((ulonglong)uVar5 + 0xc) != (uVar2 >> 24 | uVar2 << 24 | (uVar2 & 0xff00) << 8 | uVar2 >> 8 & 0xff00))
//                            goto LAB_0030fc2c;
//                    }
//                    ui_main->field_0x14 = uVar5;
//                    uVar5 = (uint)ui_params->field_0x2;
//                }
//                else {
//                    if (uVar5 == 0x4153) {
//                        short uVar1 = ui_params->field_0x2;
//                        uVar5 = (uint)uVar1;
//                        uVar2 = (((uint)uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8)) >> 2;
//                        if (uVar2 == 0) goto LAB_0030fa60;
//                        lVar9 = (ulonglong)(uVar2 - 1) + 1;
//                        int iVar7 = 0;
//                        uVar8 = 0;
//                        if ((uVar2 == 0) || (uVar2 == 0)) {
//                            lVar9 = 1;
//                        }
//                        do {
//                            ulonglong uVar10 = ((ulonglong)&ui_params->elem_type & 0xffffffff) + uVar8;
//                            uVar2 = iVar7 << 2;
//                            iVar7 += 1;
//                            uVar8 = uVar8 + 4 & 0xffffffff;
//                            uVar5 = *(uint*)(uVar10 & 0xffffffff);
//                            (*(int*)((int*)ui_main->elem->color + uVar2)) = uVar5 >> 24 | uVar5 << 24 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00;
//                            lVar9 += -1;
//                        } while (lVar9 != 0);
//                    }
//                    else {
//                    LAB_0030f9e8:
//                        if ((ui_main->elem != NULL) && (uVar5 = ui_main->elem->type, uVar5 < 13)) {
//                            switch (uVar5) {
//                            case 0x30fa5c:
//                                goto override_jmp_0030fa18_case_0;
//                            case 0x30fea8:// case 12
//                                //FUN_002f96fc(ui_main, ui_params);
//                                //FUN_002f9740(ui_main, ui_params);
//                                uVar5 = (uint)ui_params->field_0x2;
//                                break;
//                            case 0x30fec8:// cases 1,9,10
//                                //FUN_002f96fc(ui_main, ui_params);
//                                uVar5 = (uint)ui_params->field_0x2;
//                                break;
//                            case 0x30fedc:// case 6
//                                //FUN_003030b8(ui_main, ui_params);
//                                uVar5 = (uint)ui_params->field_0x2;
//                                break;
//                            case 0x30fef0: // case 4
//                                //FUN_002fd5a4(ui_main, ui_params);
//                                uVar5 = (uint)ui_params->field_0x2;
//                                break;
//                            case 0x30ff04: // case 2
//                                //FUN_002f94e8(ui_main, ui_params);
//                                uVar5 = (uint)ui_params->field_0x2;
//                            }
//                            goto LAB_0030fa60;
//                        }
//                    }
//                override_jmp_0030fa18_case_0:
//                    uVar5 = (uint)ui_params->field_0x2;
//                }
//            }
//            else {
//                if (uVar5 == 0x6e4f) {
//                    if (ui_main->field_0x9 == '\0') goto override_jmp_0030fa18_case_0;
//                    //FUN_002f8610(ui_main->elem, &ui_params->elem_type);
//                    uVar5 = (uint)ui_params->field_0x2;
//                }
//                else {
//                    if (uVar5 == 0x744f) {
//                        uVar5 = ui_params->elem_type;
//                        //peVar6 = Huds_AllocElement(ui_main, uVar5 >> 24 | uVar5 << 24 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00);
//                        ui_main->elem = peVar6;
//                        uVar5 = (uint)ui_params->field_0x2;
//                    }
//                    else {
//                        if (uVar5 != 0x684f) goto LAB_0030f9e8;
//                        uVar5 = ui_params->elem_type;
//                        ui_main->elem->hash = uVar5 >> 0x18 | uVar5 << 0x18 | (uVar5 & 0xff00) << 8 | uVar5 >> 8 & 0xff00;
//                        uVar5 = (uint)ui_params->field_0x2;
//                    }
//                }
//            }
//        }
//    LAB_0030fa60:
//        ui_params = (ui_struct2*)((longlong)&ui_params->elem_type + (ulonglong)((uVar5 & 0xff) << 8 | uVar5 >> 8) & 0xffffffff);
//        puVar3 = ui_params;
//    } while (true);
//}
//
//bool UI_PassAssetArray_r(undefined8 param_1, undefined8 param_2, int assetNum, asset_t* asset_array)
//{
//    for (int i = 0; i < assetNum; i++)
//    {
//        char* pcVar4, charFromStr;
//        ulonglong uVar3, uVar5, lVar6;
//        char buffer[256];
//        int it2 = 0, it3 = 0;
//        do
//        {
//            uVar5 = asset_array[i].name[it2];
//            charFromStr = (char)uVar5;
//            while (true)
//            {
//                if (charFromStr == '\0')
//                {
//                    uVar3 = it2;
//                    if (it2 == 0)
//                        goto exitloops;
//                    charFromStr = (char)uVar5;
//                    pcVar4 = (char*)(asset_array[i].name[it2]);
//                    lVar6 = it2;
//                    uVar5 = it2;
//                    goto joined_r0x0025b808;
//                }
//
//                it2++;
//
//                if (charFromStr != '\\' && charFromStr != '/')
//                    break;
//
//                uVar5 = asset_array[i].name[it2];
//                charFromStr = (char)uVar5;
//                it3 = it2;
//            }
//        } while (true);
//    joined_r0x0025b808:
//        while (true)
//        {
//            uVar3 = uVar5;
//            if (charFromStr == '.')
//                break;
//            pcVar4 = (char*)((ulonglong)(pcVar4 + -1) & 0xffffffff);
//            uVar5--;
//            lVar6--;
//            uVar3 = it2;
//            if (lVar6 == 0)
//                break;
//            charFromStr = *pcVar4;
//        }
//    exitloops:
//        it2 = 0;
//        if (it3 < uVar3) {
//            lVar6 = (uVar3 - it3);
//            do {
//                buffer[it2] = asset_array[i].name[it2 + it3];
//                it2++;
//                lVar6--;
//            } while (lVar6 != 0);
//        }
//        buffer[it2] = 0;
//        str_toupper(buffer);
//        if (asset_array[i].type == 2 || asset_array[i].type != 4) {
//            asset_array[i].field_0x14 = 0;
//            asset_array[i].hash_upper = Hasher_Function(buffer);
//        }
//        else {
//            int uVar1 = malloc(0x100, 0);
//            FUN_000ba6b8((char*)uVar1, buffer, 0x100);
//            asset_array[i].field_0x14 = 0;
//            asset_array[i].hash_upper = uVar1;
//        }
//    }
//    return true;
//}

float CalculateTorqueFtlb(EngineValueTable* map, float rpm)
{
    float idleRPM = *(float*)((ulonglong)map->table + 0x5c);
    float MaxRPM = (float)((double)*(float*)((ulonglong)map->table + 0x54) - idleRPM);
    if (rpm - idleRPM <= 0.0)
        rpm = idleRPM;

    int InGear = map->table->gears - 1;
    if (map->table->gears < 2)
        return 0.0f;

    int* torquemap = (int* )map->table;
    MaxRPM = ((float)(rpm - idleRPM) * (float)InGear) / MaxRPM;
    ulonglong  uVar2 = (longlong)MaxRPM & 0xffffffff;
    MaxRPM = (double)((float)MaxRPM - (float)uVar2);
    ulonglong uVar1 = map->table->gears;
    float flvar1 = *(float*)(ulonglong)((int)uVar2 * 4 + torquemap + 8);
    if ((uVar1 & 0xffffffff) <= uVar2) {
        flvar1 = 0.0f;
    }
    idleRPM = flvar1;
    uVar2 = uVar2 + 1 & 0xffffffff;
    if (uVar2 < InGear) {
       // torquemap = map->table;
        InGear = map->table->gears;
        flvar1 = *(float*)(ulonglong)((int)uVar2 * 4 + torquemap + 8);
        if (uVar2 < InGear) goto LAB_0043b1d0;
    }
    else {
        //torquemap = map->table;
        uVar2 = map->table->gears;
        flvar1 = *(float*)(ulonglong)((map->table->gears - 1) * 4 + torquemap + 8);
        if (InGear < uVar2) goto LAB_0043b1d0;
    }
    flvar1 = 0.0f;
LAB_0043b1d0:
    return (MaxRPM * (flvar1 - idleRPM) + idleRPM);
}