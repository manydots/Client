#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"

#ifdef ExternSkillSlotEn
#define KEY_COUNT       2
#define SKILL_MAX_IDX   (KEY_COUNT + 6)
int KeyMap[KEY_COUNT] = { 56, 57/*, 89, 90*/ };

thisCall procSkillQuickKeyEvent_91F410 = (thisCall)0x91F410;
BYTE BtnStatus[KEY_COUNT][2];
int __fastcall hookProcSkillQuickKeyEvent_91F410(int* thisp) {
    int ret = procSkillQuickKeyEvent_91F410(thisp, 0);
    bool isTrigger = false, status;
    for (int i = 0; i < KEY_COUNT; i++) {
        status = sq_IsKeyDown_5AFB50(KeyMap[i], KEYVALUE_MASK);
        if (BtnStatus[i][0] || !status || isTrigger) {
            BtnStatus[i][1] = 0;
        }
        else {
            BtnStatus[i][1] = 1;
            isTrigger = true;
        }
        BtnStatus[i][0] = status;
    }
    return ret;
}

thisCall drawHubQuickSlotHotKey_4BBC20 = (thisCall)0x4BBC20;
//thisCall1Args getKeyMapValue_4DCDD0 = (thisCall1Args)0x4DCDD0;
int __fastcall hookDrawHubQuickSlotHotKey_4BBC20(int** thisp) {
    int ret = drawHubQuickSlotHotKey_4BBC20((int*)thisp, 0);
    int* skillObj;
    int keyMapIndex;
    for (int i = 0; i < KEY_COUNT; i++) {
        skillObj = thisp[0x12 + i];
        if (*skillObj && ((BYTE*)skillObj)[0x0D]) {
            keyMapIndex = getKeyMapValue_4DCDD0((int*)0x1A4B570, KeyMap[i]);
            if (keyMapIndex < 106) {
                drawImgByXY_11B3950(*(int**)0x1B5582C, skillObj[5], skillObj[6], getImageByPos_11B4BD0(thisp[0x2A7], keyMapIndex));
            }
        }
    }
    return ret;
}

void Naked hookCastSkill(void) {
    //009212AD
    __asm {
        cmp esi, 6
        jl goNext
        cmp esi, SKILL_MAX_IDX
        jge goPass
        mov ecx, esi
        sub ecx, 6
        imul ecx, ecx, 2
        inc ecx
        cmp byte ptr ds : [ecx + BtnStatus] , 0
        je goPass
        mov ecx, 0x009212C0
        jmp ecx
        goNext :
        mov ecx, 0x009212B9
            jmp ecx
            goPass :
        mov ecx, 0x00921325
            jmp ecx
    }
}

void externSkillSlotInit() {
    //ÍØÕ¹¼¼ÄÜÀ¸ 
    //	p = ptr(0x08604780);
    //  Memory.protect(p, 1, "rwx");
    //  p.writeU8(0xEB);

    *(WORD*)0x004D690C = 0x2CE + 0x1E * KEY_COUNT;
    *(BYTE*)0x004C9508 = SKILL_MAX_IDX;

    *(BYTE*)0x004C2DC7 = SKILL_MAX_IDX;
    *(BYTE*)0x004C2B35 = SKILL_MAX_IDX;
    *(BYTE*)0x004C3FA1 = SKILL_MAX_IDX;
    *(BYTE*)0x004D5000 = SKILL_MAX_IDX;
    *(BYTE*)0x004D4ED5 = SKILL_MAX_IDX;
    *(BYTE*)0x004BBB58 = SKILL_MAX_IDX - 1;
    *(BYTE*)0x004BBB88 = SKILL_MAX_IDX - 1;
    *(BYTE*)0x004BBB38 = SKILL_MAX_IDX - 1;
    *(BYTE*)0x009212AF = SKILL_MAX_IDX;
    *(BYTE*)0x0091FD6A = SKILL_MAX_IDX;

    *(WORD*)0x009212DE = 0x9090;
    *(DWORD*)0x009212E0 = 0x90909090;
    writeJmpCode((void*)0x009212AD, hookCastSkill);
    DetourAttach((LPVOID*)&procSkillQuickKeyEvent_91F410, (PVOID)hookProcSkillQuickKeyEvent_91F410);
    DetourAttach((LPVOID*)&drawHubQuickSlotHotKey_4BBC20, (PVOID)hookDrawHubQuickSlotHotKey_4BBC20);
    //*(BYTE*)0x0091F533 = SKILL_MAX_IDX * 0x10;
    //*(BYTE*)0x004BBC7F = SKILL_MAX_IDX;
    //*(BYTE*)0x004BBCE9 = SKILL_MAX_IDX;
}
#else
void externSkillSlotInit() {}
#endif // ExternSkillSlotEn