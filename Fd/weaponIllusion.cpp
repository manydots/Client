#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"

#ifdef WeaponIllusionEN
UINT32 WeaponIllusionId;
int WeaponSoundType;

void drawWeaponIllusionIcon(int* thisp, int x, int y) {
    if (WeaponIllusionId) {
        int charaObj = *(int*)0x01AC790C;
        charaObj = (charaObj ? ((UINT32*)charaObj)[0xC0E] : 0xffffffff);
        if (charaObj == (int)thisp) {
            const wchar_t* imgName = L"item/IconMark.img";
            int* img = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)imgName);
            int imgObj = getImageByPos_11B4BD0(img, 333);
            drawImgByXY_11B3950((int*)*(int*)0x1B5582C, x, y, imgObj);
        }
    }
}




//addDrawEnchantLayer_78FE50 Ç¿»¯ºìÓ°ÊµÏÖ
void __fastcall hookSetFacade_80A220(int* thisp, int edx, int eType, int objId, int enchant, int clearAvatorId, int blinkInterval, int a6, int a7, int a8, int a9) {
    if (WeaponIllusionId) {
        if (eType == 0x0a) objId = WeaponIllusionId;
        else if (eType == 0x02) objId = 0xffffffff;
    }
    setFacade_80A220(thisp, 0, eType, objId, enchant, clearAvatorId, blinkInterval, a6, a7, a8, a9);
    return;
}


void Naked hookFixTownSpectrum(void) {
    //0080ED2C
    __asm {
        cmp esi, 0x0a
        jnz goPass
        mov eax, dword ptr ds : 0x01AC790C
        cmp  eax, 0
        je  goPass
        mov eax, dword ptr[eax + 0x3038]
        cmp  eax, 0
        je  goPass
        mov edx, dword ptr[eax + 0x1c]
        jmp goExit
        goPass :
        mov edx, [edi + esi * 8 + 0x2D0]
            goExit :
            mov eax, 0x0080ED33
            jmp eax
    }
}

void Naked hookExpandAniCompatibility(void) {
    //0081209E
    __asm {
        cmp byte ptr[ebx + 0x6ED], 0
        jz goExit
        mov ecx, WeaponIllusionId
        cmp ecx, 0
        jnz goExit
        mov ecx, 0x8120A7
        jmp ecx
        goExit :
        mov ecx, 0x8120D4
            jmp ecx
    }
}

void Naked hookExpandAniCompatibility1(void) {
    //00811F69
    __asm {
        test eax, eax
        jz goExit
        mov ecx, WeaponIllusionId
        cmp ecx, 0
        jnz goExit
        mov edx, [eax + 34h]
        mov ecx, 0x811F70
        jmp ecx
        goExit :
        mov ecx, 0x811F81
            jmp ecx
    }
}

void Naked hookWeaponIllusion(void) {
    //00752927
    __asm {
        cmp eax, 0xFFFFFFFF
        jz goCheck
        cmp eax, 0
        jz goCheck
        test    eax, eax
        jz goCheck
        mov eax, [ebp - 0x88]
        jmp goCall
        goCheck :
        mov eax, dword ptr[esi + 0x438]
            cmp eax, 0x0A
            jne goExit
            mov eax, WeaponIllusionId
            cmp eax, 0
            jnz goCall
            mov eax, dword ptr[esi + 0x1c]
            jmp goCall
            goCall :
        push eax
            mov ecx, esi
            mov eax, 0x9787C0
            call eax
            goExit :
        mov eax, 0x752959
            jmp eax
    }
}
void Naked hookWeaponSwitch1(void) {
    //00831004
    __asm {
        cmp eax, 0xFFFFFFFF
        jz goCheck
        cmp eax, 0
        jz goCheck
        jmp goCall
        goCheck :
        mov eax, dword ptr[esi + 0x438]
            cmp eax, 0x0A
            jne goExit
            mov eax, WeaponIllusionId
            cmp eax, 0
            jnz goCall
            mov eax, dword ptr[esi + 0x1c]
            //jmp goExit
            goCall :
        push eax
            mov eax, 0x9787C0
            call eax
            goExit :
        mov eax, 0x831047
            jmp eax
    }
}
void Naked hookWeaponSwitch2(void) {
    //00831011
    __asm {
        mov eax, dword ptr[ebx + 0x438]
        cmp eax, 0x0A
        jne goExit
        mov eax, WeaponIllusionId
        cmp eax, 0
        jnz goCall
        mov eax, dword ptr[esi + 0x1c]
        mov ecx, esi
        //jmp goPass
        goCall :
        push eax
            mov eax, 0x9787C0
            call eax
            jmp goPass
            goExit :
        mov edx, dword ptr[ebx]
            mov eax, 0x00831017
            jmp eax
            goPass :
        mov eax, 0x00831047
            jmp eax
    }
}

int __fastcall hookGetExpandAni_1262260(int* thisP, int, int a2) {
    UINT32 retAddr = (UINT32)_ReturnAddress();
    if ((0x00799D89 == retAddr) && WeaponIllusionId) {
        int* obj = NULL;
        __asm mov obj, ebx
        if (obj) {
            int type = getEType_784570(obj, 0);
            type = type ? *(char*)type : 0;
            if (type == 0x02 || type == 0x0a) {
                return 0;
            }
        }
    }
    return getExpandAni_1262260(thisP, 0, a2);
}


class WeaponSound {
public:
    int* list;
    int v1;
    int v2;
    int v3;

    WeaponSound() {
        list = NULL;
        v1 = 0;
        v2 = 0;
        v3 = 0;
    }
    void init(void) {
        if (list) return;
        list = (int*)new int[2];
        list[0] = (int)&list;
        list[1] = 0;
    }
    ~WeaponSound() {
        if (list) {
            delete list;
        }
    }
};

WeaponSound weaponSound[6];
//equimObjÒôÐ§Æ«ÒÆ A00 4A4 + 55C  460
//PvfEquimObjÒôÐ§Æ«ÒÆ 794 238 + 55C

int __fastcall hookSub_9783A0(int* thisP, int, int a2) {
    int typeAddr = getEType_784570(thisP, 0);
    int type = typeAddr ? *(char*)typeAddr : 0;
    if (WeaponIllusionId) {
        if (type == 0x02 && (isClearAvator_7841F0(thisP, 0) & 0x01) && thisP[0x4F8]) {
            thisP[0x479] = 0;
            thisP[0x47A] = 0;
            thisP[0x477] = 0xFFFFFFFF;
            thisP[0x478] = 1;
            return sub_7999A0(thisP, 0, a2);
        }
        else if (type == 0x0a) {
            int ret = sub_9783A0(thisP, 0, a2);
            if (WeaponSoundType != -1) {
                setWeaponSound_4440F0(thisP + 0x118, 0, (int)&weaponSound[WeaponSoundType]);
                return ret;
            }
            int subType = -1;
            decrypt_11A0DE0((int*)(typeAddr + 4), (typeAddr + 0xC), (int)&subType);
            int* pvfObj = (int*)getPvfObjById_1135B50(*(int**)0x1A6F6B8, 0, WeaponIllusionId);
            int pvfSubType = pvfObj ? pvfObj[0x8a] : -1;
            DPRINTF("subType:%d %d\n", subType, pvfSubType);
            if (pvfSubType == subType) goto caneclSound;
            else if (pvfSubType >= 0) subType = pvfSubType;
            else if (subType < 0) return ret;
            setWeaponSound_4440F0(thisP + 0x118, 0, (int)&weaponSound[subType]);
            return ret;
        }
    }
    else if (type == 0x0a) {
    caneclSound:
        setWeaponSound_4440F0(thisP + 0x118, 0, (int)&weaponSound[4]);
    }
    return sub_9783A0(thisP, 0, a2);
}

int __fastcall hookSub_7999A0(int* thisP, int, int a2) {
    int type, retAddr = (int)_ReturnAddress();
    if (retAddr == 0x00978438/*|| retAddr == 0x0082FF58*/) goto exit;
    else if (!WeaponIllusionId) {
        setWeaponSound_4440F0(thisP + 0x118, 0, (int)&weaponSound[4]);
        goto exit;
    }
    type = getEType_784570(thisP, 0);
    type = type ? *(char*)type : 0;
    if (type == 0x0a/* || type == 0x02*/) {
        int bk = thisP[0x4F8];
        thisP[0x4F8] = WeaponIllusionId;
        int ret = hookSub_9783A0(thisP, 0, a2);
        thisP[0x4F8] = bk;
        return ret;
    }
    else if (type == 0x02) {
        thisP[0x479] = 0;
        thisP[0x47A] = 0;
        thisP[0x477] = 0xFFFFFFFF;
        thisP[0x478] = 1;
    }
exit:
    return sub_7999A0(thisP, 0, a2);
}

void setWeaponIllusion(int id, int soundType) {
    if (WeaponIllusionId == id) return;
    WeaponSoundType = soundType;
    WeaponIllusionId = id;
    int* facadeObj = *(int**)0x01AC7910;
    int* charaObj = *(int**)0x01AC790C;
    int* equimObj = NULL, * weaponAvatorObj = NULL;
    if (charaObj) {
        equimObj = (int*)charaObj[0xC0E];
        weaponAvatorObj = (int*)charaObj[0xC06];
    }

    if (facadeObj) {
        if (WeaponIllusionId) {
            hookSetFacade_80A220(facadeObj, 0, 0x0a, 0xffffffff, 0, 0, 0, 0, 0, 0, 0);
            hookSetFacade_80A220(facadeObj, 0, 0x02, 0xffffffff, 0, 0, 0, 0, 0, 0, 0);
        }
        else {
            hookSetFacade_80A220(facadeObj, 0, 0x0a, equimObj ? equimObj[7] : 0xffffffff, 0, 0, 0, 0, 0, 0, 0);
            hookSetFacade_80A220(facadeObj, 0, 0x02, weaponAvatorObj ? weaponAvatorObj[7] : 0xffffffff, 0, 0, 0, 0, 0, 0, 0);
        }
    }
    if (equimObj) {
        thisCall1Args preCall;
        thisCall1Args refreshCopyFacadeMotion = (thisCall1Args)Vtable(charaObj, 0x54C);
        thisCall1Args refreshCopyFacadeStand = (thisCall1Args)Vtable(charaObj, 0x790);
        int bk;
        if (weaponAvatorObj) {
            preCall = (thisCall1Args)Vtable(weaponAvatorObj, 0x130);
            preCall(weaponAvatorObj, 0, (int)charaObj);
            bk = weaponAvatorObj[0x4F8];
            if (WeaponIllusionId) weaponAvatorObj[0x4F8] = WeaponIllusionId;
            sub_9783A0(weaponAvatorObj, 0, 0);
            refreshCopyFacadeMotion(charaObj, 0, (int)weaponAvatorObj);
            refreshCopyFacadeStand(charaObj, 0, (int)weaponAvatorObj);
            weaponAvatorObj[0x4F8] = bk;
        }
        preCall = (thisCall1Args)Vtable(equimObj, 0x130);
        preCall(equimObj, 0, (int)charaObj);
        bk = equimObj[0x4F8];
        equimObj[0x4F8] = WeaponIllusionId;
        sub_9783A0(equimObj, 0, 0);
        refreshCopyFacadeMotion(charaObj, 0, (int)equimObj);
        refreshCopyFacadeStand(charaObj, 0, (int)equimObj);
        equimObj[0x4F8] = bk;
        if (!WeaponIllusionId) {
            setWeaponSound_4440F0(equimObj + 0x118, 0, (int)&weaponSound[4]);
        }
        if (getSpectrumDuration_7844D0(equimObj, 0))
            Sleep(500);
    }
}


wchar_t SoundName[6][4][32] = {
    //{//¶Ì½£
    //    L"R_MINERALSWDA",
    //    L"MINERALSWDB",
    //    L"R_MINERALSWDA_HIT",
    //    L"MINERAL_SWDB_HIT",
    //},
    //{//Ì«µ¶
    //    L"R_KATANAA",
    //    L"KATANAB",
    //    L"R_KATANAA_HIT",
    //    L"KATANAB_HIT",
    //},
    //{//¶ÛÆ÷
    //    L"R_STICKA",
    //    L"STICKB_01",
    //    L"R_STICKA_HIT",
    //    L"STICKB_HIT_01",
    //},
    //{//¾Þ½£
    //    L"R_SQUARESWDA",
    //    L"SQUARESWDB",
    //    L"R_SQUARESWDA_HIT",
    //    L"SQUARESWDB_HIT",
    //},
    //{//ÆúÓÃ
    //   NULL,
    //   NULL,
    //   NULL,
    //   NULL,
    //},
    //{//¹â½£
    //    L"R_BEAMSWDA",
    //    L"BEAMSWDB",
    //    L"R_BEAMSWDA_HIT",
    //    L"BEAMSWDB_HIT",
    //}
};


thisCall2 GameString__Constructor_10B2290 = (thisCall2)0x10B2290;
thisCall2Args2 GameString__dup_410030 = (thisCall2Args2)0x410030;
thisCall1Args2 GameString__getRef_11A3D20 = (thisCall1Args2)0x11A3D20;
void initSoundList() {



    WeaponSound* ps;
    for (int p, i = 0; i < 6; ++i) {
        ps = &weaponSound[i];
        ps->init();
        listInit_440820((int*)&ps->list);
        for (int j = 0; j < 4; ++j) {
            p = (int)&SoundName[i][j][3];
            listPush_6FE170((int*)&ps->list, (int)&p);
        }
    }
    WeaponIllusionId = 0;
    WeaponSoundType = -1;
}


void weaponIllusionInit() {
    initSoundList();
    //writeByteCode((void*)0x0092452D, 0x0B); 
    //writeByteCode((void*)0x00924560, 0x0B);
    //writeByteCode((void*)0x00923718, 0x0B);
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x80A220, (gpointer)hookSetFacade_80A220, (gpointer*)&setFacade_80A220);

    //////writeJmpCode((void*)0x00811F69, hookExpandAniCompatibility1);
    //writeJmpCode((void*)0x0081209E, hookExpandAniCompatibility);
    writeJmpCode((void*)0x0080ED2C, hookFixTownSpectrum);

    //writeJmpCode((void*)0x00752927, hookWeaponIllusion);
    //writeJmpCode((void*)0x00831004, hookWeaponSwitch1);
    //writeJmpCode((void*)0x00831011, hookWeaponSwitch2);
    //writeWordCode((void*)0x00830FFB, 0x9090);

    *(WORD*)0x00831075 = 0x9090;
    *(DWORD*)0x00799D77 = 0x90909090;
    *(WORD*)0x00799D7B = 0x9090;
}
#else
void weaponIllusionInit() {}
void drawWeaponIllusionIcon(int* thisp, int x, int y) {}
#endif // ExternSkillSlotEn