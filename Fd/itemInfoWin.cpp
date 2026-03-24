#include "pch.h"
#include "common.h"
#include "oldSkillWin.h"
#include "frida-gum.h"
#include "tools.h"

extern void drawWeaponIllusionIcon(int* thisp, int x, int y);
extern void showIconAnim(int* thisP, int x, int y);

typedef struct {
    UINT32 name;
    UINT32 begin;
    UINT32 end;
    UINT32 color;
}GradeInfo;

GradeInfo gradeInfo[] = {
    {(UINT32)L"普通", 0, 0, 0xffffffff},
    {(UINT32)L"高级", 0, 0, 0xffedd568},
    {(UINT32)L"稀有", 0, 0, 0xffff6bb3},
    {(UINT32)L"神器", 0, 0, 0xfff000ff},
    {(UINT32)L"史诗", 0, 0, 0xff00b1ff},
    {(UINT32)L"勇者", 0, 0, 0xff6666ff},
    {(UINT32)L"传说", 0, 0, 0x81000000},
    {(UINT32)L"极上", 0, 0, 0x81010000},
    {(UINT32)L"无上", 0, 0, 0x81020000},
    {(UINT32)L"神话", 0, 0, 0x81030000},
    {(UINT32)L"天仙", 0, 0, 0x81040000},
    {(UINT32)L"玄天", 0, 0, 0x81050000},
};

typedef struct {
    UINT32 startColor;
    UINT32 endColor;
}LinearGradientColor;

const LinearGradientColor linearGradientColors[] = {
    {0xFFC7D5ED,0xFFFFC000},
    {0xFFC7D5ED,0xFFED7D31},
    {0xFFFFE699,0xFFFF1B1B},
    {0xFFFFE699,0xFF7030A0},
    {0xFFF5C929,0xFFCE68E8},
    {0xFFFF4747,0xFF7030A0},
};

WCHAR name2Buff[256];
WCHAR shrBuff[64];
int compareObj;

BOOL name2Enable = true;
BOOL iconEnable = false;
BOOL showGrade = false;

void __fastcall drawName2Imp(int* thisP, int* stringList, wchar_t* name) {
    int namePos = 0;
    if (iconEnable) {
        namePos = 6;
        *(int*)name2Buff = 0x00200020;
        *((int*)name2Buff + 1) = 0x00200020;
        if (thisP == *(int**)0x1AF424C) {
            *((int*)name2Buff + 2) = 0x30003000;
        }
        else {
            compareObj = (int)thisP;
            *((int*)name2Buff + 2) = 0x00200020;
        }
    }
    lstrcpyW(name2Buff + namePos, name);
    namePos += lstrlenW(name);
    if (name2Enable && thisP[9] && lstrlenW((wchar_t*)(thisP[9]))) {
        name2Buff[namePos++] = 0x000A;
        if (iconEnable) {
            int* bufP = (int*)(name2Buff + namePos);
            bufP[0] = 0x00200020;
            bufP[1] = 0x00200020;
            bufP[2] = 0x00200020;
            namePos += 6;
        }
        lstrcpyW(name2Buff + namePos, (wchar_t*)(thisP[9]));
    }
    else if (iconEnable) {
        name2Buff[namePos++] = 0x000A;
        int* bufP = (int*)(name2Buff + namePos);
        bufP[0] = 0x00200020;
        bufP[1] = 0x00200020;
        namePos += 4;
        name2Buff[namePos++] = 0x0020;
        name2Buff[namePos] = L'\0';
    }
    sub_410030(stringList, (int)name2Buff, lstrlenW(name2Buff));
}

void Naked drawName2(void) {
    __asm {
        pushad
        mov ecx, dword ptr[esi + 0x178]
        lea edx, dword ptr[ebp - 0xB0]
        push eax
        call drawName2Imp
        popad
        mov eax, 0xF5E3E2
        jmp eax
    }
}


int __fastcall hookDrawIcon_7B6D30(int* thisp, int edx, int x, int y, int a3, int a4, int a5) {
    int ret = drawIcon_7B6D30(thisp, x, y, a3, a4, a5);
    //showIconAnim(thisp, x, y);
    drawWeaponIllusionIcon(thisp, x, y);
    return ret;
}

int __fastcall hookDrawIconSlot_78BCD0(int* thisp, int edx, int x, int y) {
    showIconAnim(thisp, x, y);
    return drawIconSlot_78BCD0(thisp, x, y);
}

void __fastcall hookDrawHeaderText(int* thisP, int, int line, int wstr, int align, int color, int a5) {
    if (iconEnable && line == 1 && ((int*)wstr)[0] != 0x00200020) {
        wsprintfW(shrBuff, L"      %s", (WCHAR*)wstr);
        wstr = (int)shrBuff;
    }
    DrawText_F5F080(thisP, line, wstr, align, color, a5);
}

void __fastcall drawIconImp(wchar_t* text, int winId, int x, int y, int line) {
    if (line != 1 || winId || !iconEnable || ((int*)text)[0] != 0x00200020) return;
    float f1 = *(float*)0x15620FC;
    float f2 = *(float*)0x1562250;
    int obj = text[4] == 0x3000 ? *(int*)0x1AF424C : compareObj;
    if (!obj) return;
    y -= 2;
    x -= 2;
    //thisCall2Args drawIconImg = (thisCall2Args)Vtable(obj, 0xD4);
    thisCall2Args2 drawIconBoard = (thisCall2Args2)Vtable(obj, 0xAC);
    thisCall2Args2 drawIconRandomOption = (thisCall2Args2)Vtable(obj, 0x14);
    thisCall2Args2 drawIconSlot = (thisCall2Args2)Vtable(obj, 0x10);

    drawImgByXY_11B3950((int*)*(int*)0x1B5582C, x, y, ((DWORD*)obj)[0x36]);
    drawIconBoard((int*)obj, x, y);
    if (!sub_684E90((int*)*(int*)0x1AC790C, 0, obj)) {
        drawImgByXY2_11B41E0((int*)*(int*)0x1B5582C, x, y, *(int*)0x1A7FDB4, f1, f1, 0.0f, 0x4DFFFFFF, 0.0f, f2);
    }
    drawIconRandomOption((int*)obj, x, y);
    drawIconLock_7B5DE0((int*)obj, x, y);
    //showIconAnim((int*)obj, x, y);
    drawIconSlot((int*)obj, x, y);
    drawWeaponIllusionIcon((int*)obj, x, y);
    //WDPRINTF(L"[%d,%d,%d]:%s\n", winId, x, y, text);
}

void Naked drawIconV2(void) {
    //00F40006
    __asm {
        push eax
        pushad
        push dword ptr[ebp - 0x4]
        push esi
        push dword ptr[ebp - 0x8]
        mov ecx, eax
        mov edx, dword ptr[ebp - 0xc]
        call drawIconImp
        popad
        mov edx, dword ptr ds : 0x1B5582C
        mov edx, dword ptr[edx]
        mov eax, 0x00F4000F
        jmp eax
    }
}

int __cdecl hookGetEquimGradeColor_7B4F80(int grade) {
    if (grade > 5) {
        return gradeInfo[grade].color;
    }
    return getEquimGradeColor_7B4F80(grade);
}


void __fastcall hookDrawWeightInfoText_F44A30(int* thisP, int, int a1) {
    int grade = ((int**)thisP)[0x5E][0x3D];
    DrawText_F5F080(thisP, (*(int*)a1)++, gradeInfo[grade].name, 0x1AF4324, gradeInfo[grade].color, 0);
    drawWeightInfoText_F44A30(thisP, 0, a1);
}

void Naked hookGradeDecrypt(void) {
    //007888DB
    __asm {
        mov eax, dword ptr[esi + 0xF4]
        cmp eax, 6
        jl goPass;
        mov eax, 4
            goPass:
        mov ecx, 0x007888E1
            jmp ecx
    }
}



void Naked hookColor1(void) {
    //011F2B9A  011F2A8E
    __asm {
        mov edx, dword ptr ds : 0x1C1B188
        mov eax, esi
        and eax, 0xffffff00
        cmp eax, 0x81000000
        mov eax, esi
        jne goPass
        and eax, 0xFF
        imul eax, eax, TYPE LinearGradientColor
        mov esi, linearGradientColors[eax].startColor
        mov eax, linearGradientColors[eax].endColor
        goPass :
        mov dword ptr[edx + 0x10], eax//左下角
        mov dword ptr[edx + 0x2c], esi//左上角
        mov dword ptr[edx + 0x48], eax//右下角
        mov dword ptr[edx + 0x64], esi//右上角
        mov edx, 0x011F2BA3
        jmp edx
    }
}

//void itemInfoWinOptimize() {
//    //装备-消耗品 无法使用颜色
//    //writeDWordCode((void*)0x00F46B54, 0xff808080);
//    //writeDWordCode((void*)0x00F49337, 0xff808080);
//    //writeByteCode((void*)0x0069EAE3, 0x5f);
//    //writeByteCode((void*)0x00E919F7, 0x5f);
//    //writeByteCode((void*)0x00E919FB, 0x5f);
//
//    DetourAttach((LPVOID*)&drawIcon_7B6D30, (PVOID)hookDrawIcon_7B6D30);
//    DetourAttach((LPVOID*)&drawIconSlot_78BCD0, (PVOID)hookDrawIconSlot_78BCD0);
//    DetourAttach((LPVOID*)&getEquimGradeColor_7B4F80, (PVOID)hookGetEquimGradeColor_7B4F80);
//    DetourAttach((LPVOID*)&drawWeightInfoText_F44A30, (PVOID)hookDrawWeightInfoText_F44A30);
//
//    *(WORD*)0x00F5E6DA = 0xB890;
//    *(DWORD*)0x00F5E6DC = (DWORD)&hookDrawHeaderText;
//    writeJmpCode((void*)0x00F5E3B7, drawName2);
//    writeJmpCode((void*)0x00F40006, drawIconV2);
//    writeJmpCode((void*)0x007888DB, hookGradeDecrypt);
//    writeJmpCode((void*)0x011F2B9A, hookColor1);
//    //writeJmpCode((void*)0x011F2E78, hookColor2);
//    //writeJmpCode((void*)0x011F28E0, hookColor3);
//    *(BYTE*)0x011D25AE = 0xFF;
//    *(WORD*)0x011D25AF = 0xCA89;
//    //DetourAttach((LPVOID*)&DrawText_F5F080, (PVOID)hookDrawText_F5F080);//超界
//}

#define MaxItemInfoLine         35
#define MaxItemInfoLineValue    0x3A83A83B
//#define MaxItemInfoLine         36
//#define MaxItemInfoLineValue    0x38E38E39
#define MaxItemInfoLineValueP   3
int MaxLine = MaxItemInfoLine;
cdeclCall6 my_F6B330;
int __cdecl hookSub_F6B330(int a1, int a2, int a3, int a4, int a5, int a6) {
    return my_F6B330(a1, a2, a3, a4, a5, a6);
}

cdeclCall my_F6E9A0;
int __cdecl hook_F6E9A0() {
    return my_F6E9A0();
}

thisCall1Args2 my_F45CA0;
int __fastcall hook_F45CA0(int* thisP, int, int a2) {
    return my_F45CA0(thisP, a2);
}

thisCall1Args2 myShowInfoWin_F60330;
int __fastcall hookShowInfoWin_F60330(int* thisP, int, int a2) {
    return myShowInfoWin_F60330(thisP, a2);
}

void __fastcall showSeparateAttackImp(int* item, int* line, int* drawCtx, int color) {
    int v1;
    float v2;
    wchar_t buf[32];
    decrypt_11A0DE0(item + 0x252, (int)(item + 0x254), (int)&v1);
    decrypt_11A0DE0(item + 0x258, (int)(item + 0x25A), (int)&v2);
    int v3 = v1 * v2;
    if (v3) {
        //_snwprintf(buf, 32, L"物理独立攻击力 %+d", v3);
        wsprintf(buf, L"物理独立攻击力 +%d", v3);//00F5F080
        DrawText_F5F080(drawCtx, *line, (int)buf, 0x1AF4308, color, 0);
        *line += 1;
        //_snwprintf(buf, 32, L"魔法独立攻击力 %+d", v3);
        wsprintf(buf, L"魔法独立攻击力 +%d", v3);
        DrawText_F5F080(drawCtx, *line, (int)buf, 0x1AF4308, color, 0);
        *line += 1;
    }
}
//0x00F4FB0F
void Naked hookShowSeparateAttack(void) {
    //00F55775
    __asm {
        push ebx
        mov ecx, dword ptr[ebp - 0x85C]
        mov edx, ebx
        push dword ptr[ebp + 0x10]
        push esi
        call showSeparateAttackImp
        pop ebx
        mov eax, dword ptr[ebp - 0x8A8]
        test eax, eax
        jz goExit
        mov ecx, 0xF5577F
        jmp ecx
    goExit:
        mov ecx, 0xF55788 
        jmp ecx
    }
}

thisCall2Args2 itemInfoWin__OnOpen_F405C0 = (thisCall2Args2)0xF405C0;
char __fastcall hookItemInfoWin__OnOpen_F405C0(int* thisP, int, int a2, int a3) {
    int ret = itemInfoWin__OnOpen_F405C0(thisP, a2, a3);
    if(!a3) thisP[0xA] = InfoWinAlpha;
    else BasePopupWin__setCenterPos_EF63A0(thisP);
    return ret;
}

thisCall1Args2 getBoolConfig_4E12C0 = (thisCall1Args2)0x4E12C0;
int __fastcall hookGetBoolConfig_4E12C0(int* thisP, int, int a2) {
    if (a2 == 0x18) return 0;
    return getBoolConfig_4E12C0(thisP, a2);
}

//void itemInfoWinInit() {
//    GumInterceptor* v = gum_interceptor_obtain();
//    //gum_interceptor_replace_fast(v, (gpointer)0x7B6D30, (gpointer)hookDrawIcon_7B6D30, (gpointer*)&drawIcon_7B6D30);
//    //gum_interceptor_replace_fast(v, (gpointer)0x78BCD0, (gpointer)hookDrawIconSlot_78BCD0, (gpointer*)&drawIconSlot_78BCD0);
//    gum_interceptor_replace_fast(v, (gpointer)0x7B4F80, (gpointer)hookGetEquimGradeColor_7B4F80, (gpointer*)&getEquimGradeColor_7B4F80);
//    if(showGrade)
//        gum_interceptor_replace_fast(v, (gpointer)0xF44A30, (gpointer)hookDrawWeightInfoText_F44A30, (gpointer*)&drawWeightInfoText_F44A30);
//
//    //writeJmpCode((void*)0x00F40006, drawIconV2);
//    writeJmpCode((void*)0x007888DB, hookGradeDecrypt);
//    writeJmpCode((void*)0x011F2B9A, hookColor1);
//    *(BYTE*)0x011D25AE = 0xFF;
//    *(WORD*)0x011D25AF = 0xCA89;
//
//    std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
//    auto b = hook->begin();
//
//    hook->resize(2);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F6B6F8, 32);
//    b++->setValue(H_DWORD, 0x00F6B6FF, (int)&MaxLine);
//    cdeclCall my_F6B610 = (cdeclCall)tools_relocation_hook(0xF6B610, 0xF6B72F, hook);
//    //sub_F6B610
//    //*(BYTE*)0x00F6B6F8 = 32;
//    //*(DWORD*)0x018253FC = 32;
//
//    hook->resize(2);
//    b = hook->begin();
//    b++->setValue(H_DWORD, 0x00F6B5CA, 0x40000000); b++->setValue(H_BYTE, 0x00F6B5D2, 3);
//    cdeclCall1 my_F6B4C0 = (cdeclCall1)tools_relocation_hook(0xF6B4C0, 0xF6B601, hook);
//    //sub_F6B4C0
//    //*(DWORD*)0x00F6B5CA = 0x40000000; *(BYTE*)0x00F6B5D2 = 3;
//
//    //sub_F6E9A0 -> sub_F6DBF0 -> sub_F6B730 00F6BB13
//    hook->resize(9);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F6B783, 3);
//    b++->setValue(H_BYTE, 0x00F6B787, 3);
//    //b++->setValue(H_DWORD, 0x00F6B7B0, 480 - 28);
//    //b++->setValue(H_DWORD, 0x00F6B7D5, -640);
//    //b++->setValue(H_DWORD, 0x00F6B7F4, 480 - 26);
//    //b++->setValue(H_DWORD, 0x00F6B918, 640);
//    //b++->setValue(H_DWORD, 0x00F6B928, 480 - 33);
//    b++->setValue(H_DWORD, 0x00F6B7B0, 480 - 50);
//    b++->setValue(H_DWORD, 0x00F6B7D5, -640);
//    b++->setValue(H_DWORD, 0x00F6B7F4, 480 - 48);
//    b++->setValue(H_DWORD, 0x00F6B918, 640);
//    b++->setValue(H_DWORD, 0x00F6B928, 480 - 55);
//    b++->setValue(H_CALL, 0x00F6B797, (int)my_F6B610);
//    b++->setValue(H_CALL, 0x00F6B779, (int)my_F6B4C0);
//    cdeclCall my_F6B730 = (cdeclCall)tools_relocation_hook(0xF6B730, 0xF6BB13, hook);
//    //*(BYTE*)0x00F6B783 = 3;//最多显示3个信息窗
//    //*(BYTE*)0x00F6B787 = 3;
//    //*(DWORD*)0x00F6B7B0 = 480 - 28;
//    //*(DWORD*)0x00F6B7D5 = -640;
//    //*(DWORD*)0x00F6B7F4 = 480 - 26;
//    //*(DWORD*)0x00F6B918 = 640;
//    //*(DWORD*)0x00F6B928 = 480 - 33;
//
//    hook->resize(3);
//    b = hook->begin();
//    b++->setValue(H_DWORD, 0x00F6CC69, 0x40000000); b++->setValue(H_BYTE, 0x00F6CC71, 3);
//    b++->setValue(H_BYTE, 0x00F6CB1B, 3);
//    cdeclCall1 my_F6CAF0 = (cdeclCall1)tools_relocation_hook(0xF6CAF0, 0xF6CCC2, hook);
//    //sub_F6DBF0 -> sub_F6CAF0 00F6CCC2
//    //*(DWORD*)0x00F6CC69 = 0x40000000; *(BYTE*)0x00F6CC71 = 3;
//    //*(BYTE*)0x00F6CB1B = 32;
//
//    hook->resize(1);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F6D615, 29);
//    cdeclCall1 my_F6D2A0 = (cdeclCall1)tools_relocation_hook(0xF6D2A0, 0x00F6D807, hook);
//
//    hook->resize(1);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F6D132, 29);
//    cdeclCall my_F6CDE0 = (cdeclCall)tools_relocation_hook(0xF6CDE0, 0x00F6D296, hook);
//
//    hook->resize(5);
//    b = hook->begin();
//    b++->setValue(H_CALL, 0x00F6DCE7, (int)my_F6B730);
//    b++->setValue(H_CALL, 0x00F6DC3C, (int)my_F6CAF0);
//    b++->setValue(H_CALL, 0x00F6DC42, (int)my_F6B4C0);
//    b++->setValue(H_CALL, 0x00F6DCD6, (int)my_F6D2A0);
//    b++->setValue(H_CALL, 0x00F6DCA6, (int)my_F6CDE0);
//    cdeclCall my_F6DBF0 = (cdeclCall)tools_relocation_hook(0xF6DBF0, 0xF6DD49, hook);
//
//    hook->resize(1);
//    b = hook->begin();
//    b++->setValue(H_CALL, 0x00F6EA45, (int)my_F6DBF0);
//    my_F6E9A0 = (cdeclCall)tools_relocation_hook(0xF6E9A0, 0xF6EA9D, hook);
//    gum_interceptor_replace_fast(v, (gpointer)0xF6E9A0, (gpointer)hook_F6E9A0, NULL);
//
//    hook->resize(9);
//    b = hook->begin();
//    b++->setValue(H_DWORD, 0x00F5E6F3, 0x40000000); b++->setValue(H_BYTE, 0x00F5E6FB, 3);
//    b++->setValue(H_BYTE, 0x00F5E722, 32);
//    b++->setValue(H_DWORD, 0x00F5E934, 0x40000000); b++->setValue(H_BYTE, 0x00F5E958, 3);
//    b++->setValue(H_BYTE, 0x00F5E95C, 32);
//    b++->setValue(H_JUMP, 0x00F5E3B7, (int)drawName2);
//    b++->setValue(H_WORD, 0x00F5E6DA, 0xB890);
//    b++->setValue(H_WORD, 0x00F5E6DC, (int)hookDrawHeaderText);
//    thisCall2Args2 drawItemInfoWinHeader_F5E200 = (thisCall2Args2)tools_relocation_hook(0xF5E200, 0xF5EDC1, hook);
//    //drawItemInfoWinHeader_F5E200 00F5EDC1 信息栏最大显示30行 原来38
//    //*(DWORD*)0x00F5E6F3 = 0x40000000; *(BYTE*)0x00F5E6FB = 3;
//    //*(BYTE*)0x00F5E722 = 32;
//    //*(DWORD*)0x00F5E934 = 0x40000000; *(BYTE*)0x00F5E958 = 3;
//    //*(BYTE*)0x00F5E95C = 32;
//
//    hook->resize(3);
//    b = hook->begin();
//    b++->setValue(H_DWORD, 0x00F60310, 0x40000000); b++->setValue(H_BYTE, 0x00F60318, 3);
//    b++->setValue(H_CALL, 0x00F60205, (int)drawItemInfoWinHeader_F5E200);
//    thisCall1Args2 myDrawItemInfoWin_F601F0 = (thisCall1Args2)tools_relocation_hook(0x00F601F0, 0x00F6032E, hook);
//    //drawItemInfoWin_F601F0
//    //*(DWORD*)0x00F60310 = 0x40000000; *(BYTE*)0x00F60318 = 3;
//
//    b = hook->begin();
//    b++->setValue(H_DWORD, 0x00F601C2, 0x40000000); b++->setValue(H_BYTE, 0x00F601CA, 3);
//    b++->setValue(H_CALL, 0x00F5FF1E, (int)drawItemInfoWinHeader_F5E200);
//    thisCall1Args2 myDrawEquimInfoWin_F5FEE0 = (thisCall1Args2)tools_relocation_hook(0xF5FEE0, 0x00F601E2, hook);
//    //drawEquimInfoWin_F5FEE0
//    //*(DWORD*)0x00F601C2 = 0x40000000; *(BYTE*)0x00F601CA = 3;
//
//    hook->resize(3);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F603F0, 32);
//    b++->setValue(H_CALL, 0x00F60397, (int)myDrawItemInfoWin_F601F0);
//    b++->setValue(H_CALL, 0x00F6037D, (int)myDrawEquimInfoWin_F5FEE0);
//    myShowInfoWin_F60330 = (thisCall1Args2)tools_relocation_hook(0xF60330, 0xF60495, hook);
//    //ShowInfoWin_F60330
//    //*(BYTE*)0x00F603F0 = 32;
//    gum_interceptor_replace_fast(v, (gpointer)0xF60330, (gpointer)hookShowInfoWin_F60330, NULL);
//
//    hook->resize(1);
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F45DBB, 32);
//    my_F45CA0 = (thisCall1Args2)tools_relocation_hook(0xF45CA0, 0xF45F40, hook);
//    //sub_F45CA0
//    //*(BYTE*)0x00F45DBB = 32;
//    gum_interceptor_replace_fast(v, (gpointer)0xF45CA0, (gpointer)hook_F45CA0, NULL);
//
//
//    b = hook->begin();
//    b++->setValue(H_BYTE, 0x00F6B36B, 32);
//    my_F6B330 = (cdeclCall6)tools_relocation_hook(0xF6B330, 0xF6B445, hook);
//    //sub_F6B330
//    //*(BYTE*)0x00F6B36B = 32;
//    gum_interceptor_replace_fast(v, (gpointer)0xF6B330, (gpointer)hookSub_F6B330, NULL);
//    delete hook;
//
//
//
//    //独立攻击力拆分显示位物理和魔法
//    * (BYTE*)0x00F4FB0F = 0xE9; *(DWORD*)0x00F4FB10 = 0xB9; // 跳过原有显示
//    writeJmpCode((void*)0x00F55775, hookShowSeparateAttack);
//
//
//    //兼容掉落金币G 424文本 信息栏显示金币
//    *(DWORD*)0x00F5F63A = 23069;
//    
//    //信息窗口透明
//    *(DWORD*)0x01822CD8 = (int)hookItemInfoWin__OnOpen_F405C0;
//    
//    //*(BYTE*)0x00F6B783 = 3;//最多显示3个信息窗
//    //*(BYTE*)0x00F6B787 = 3;
//    //*(BYTE*)0x00F6B6F8 = 32;
//    //*(DWORD*)0x018253FC = 32;
//    //*(DWORD*)0x00F6B5CA = 0x40000000; *(BYTE*)0x00F6B5D2 = 3;
//    //*(DWORD*)0x00F6B7B0 = 480 - 28;
//    //*(DWORD*)0x00F6B7D5 = -640;
//    //*(DWORD*)0x00F6B7F4 = 480 - 26;
//    //*(DWORD*)0x00F6B918 = 640;
//    //*(DWORD*)0x00F6B928 = 480 - 33;
//    //*(DWORD*)0x00F6CC69 = 0x40000000; *(BYTE*)0x00F6CC71 = 3;
//    //*(BYTE*)0x00F6CB1B = 32;
//    ////drawItemInfoWinHeader_F5E200 00F5EDC1 信息栏最大显示30行 原来38
//    //*(BYTE*)0x00F45DBB = 32;
//    //*(DWORD*)0x00F5E6F3 = 0x40000000; *(BYTE*)0x00F5E6FB = 3;
//    //*(BYTE*)0x00F5E722 = 32;
//    //*(DWORD*)0x00F5E934 = 0x40000000; *(BYTE*)0x00F5E958 = 3;
//    //*(BYTE*)0x00F5E95C = 32;
//    //*(DWORD*)0x00F60310 = 0x40000000; *(BYTE*)0x00F60318 = 3;
//    //*(DWORD*)0x00F601C2 = 0x40000000; *(BYTE*)0x00F601CA = 3;
//    //*(BYTE*)0x00F603F0 = 32;
//    //*(BYTE*)0x00F6B36B = 32;
//    //*(BYTE*)0x00F6D615 = 29;
//}


void itemInfoWinInit() {
    GumInterceptor* v = gum_interceptor_obtain();
    //gum_interceptor_replace_fast(v, (gpointer)0x7B6D30, (gpointer)hookDrawIcon_7B6D30, (gpointer*)&drawIcon_7B6D30);
    //gum_interceptor_replace_fast(v, (gpointer)0x78BCD0, (gpointer)hookDrawIconSlot_78BCD0, (gpointer*)&drawIconSlot_78BCD0);
    gum_interceptor_replace_fast(v, (gpointer)0x7B4F80, (gpointer)hookGetEquimGradeColor_7B4F80, (gpointer*)&getEquimGradeColor_7B4F80);
    if (showGrade)
        gum_interceptor_replace_fast(v, (gpointer)0xF44A30, (gpointer)hookDrawWeightInfoText_F44A30, (gpointer*)&drawWeightInfoText_F44A30);

    //writeJmpCode((void*)0x00F40006, drawIconV2);
    writeJmpCode((void*)0x007888DB, hookGradeDecrypt);
    writeJmpCode((void*)0x011F2B9A, hookColor1);
    *(BYTE*)0x011D25AE = 0xFF;
    *(WORD*)0x011D25AF = 0xCA89;

    std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
    auto b = hook->begin();

    hook->resize(2);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F6B6F8, MaxItemInfoLine);
    b++->setValue(H_DWORD, 0x00F6B6FF, (int)&MaxLine);
    cdeclCall my_F6B610 = (cdeclCall)tools_relocation_hook(0xF6B610, 0xF6B72F, hook);
    //sub_F6B610
    //*(BYTE*)0x00F6B6F8 = MaxItemInfoLine;
    //*(DWORD*)0x018253FC = MaxItemInfoLine;

    hook->resize(2);
    b = hook->begin();
    b++->setValue(H_DWORD, 0x00F6B5CA, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F6B5D2, MaxItemInfoLineValueP);
    cdeclCall1 my_F6B4C0 = (cdeclCall1)tools_relocation_hook(0xF6B4C0, 0xF6B601, hook);
    //sub_F6B4C0
    //*(DWORD*)0x00F6B5CA = 0x40000000; *(BYTE*)0x00F6B5D2 = 3;

    //sub_F6E9A0 -> sub_F6DBF0 -> sub_F6B730 00F6BB13
    hook->resize(13);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F6B783, 3);
    b++->setValue(H_BYTE, 0x00F6B787, 3);
    //32
    //b++->setValue(H_DWORD, 0x00F6B7B0, 480 - 28);
    //b++->setValue(H_DWORD, 0x00F6B7D5, -640);
    //b++->setValue(H_DWORD, 0x00F6B7F4, 480 - 26);
    //b++->setValue(H_DWORD, 0x00F6B918, 640);
    //b++->setValue(H_DWORD, 0x00F6B928, 480 - 33);
    //36
    //b++->setValue(H_DWORD, 0x00F6B7B0, 480 - 2);
    //b++->setValue(H_DWORD, 0x00F6B7D5, -640);
    //b++->setValue(H_DWORD, 0x00F6B7F4, 480 - 0);
    //b++->setValue(H_DWORD, 0x00F6B918, 640);
    //b++->setValue(H_DWORD, 0x00F6B928, 480 - 7);
    //35
    b++->setValue(H_DWORD, 0x00F6B7BC, 0);
    b++->setValue(H_BYTE, 0x00F6B7EA, 0);
    b++->setValue(H_BYTE, 0x00F6B81E, 0);
    b++->setValue(H_BYTE, 0x00F6B7FC, 0);
    b++->setValue(H_DWORD, 0x00F6B7B0, 480 - 12);
    b++->setValue(H_DWORD, 0x00F6B7D5, -640);
    b++->setValue(H_DWORD, 0x00F6B7F4, 480 - 10);
    b++->setValue(H_DWORD, 0x00F6B918, 640);
    b++->setValue(H_DWORD, 0x00F6B928, 480 - 17);
    b++->setValue(H_CALL, 0x00F6B797, (int)my_F6B610);
    b++->setValue(H_CALL, 0x00F6B779, (int)my_F6B4C0);
    cdeclCall my_F6B730 = (cdeclCall)tools_relocation_hook(0xF6B730, 0xF6BB13, hook);
    //*(BYTE*)0x00F6B783 = 3;//最多显示3个信息窗
    //*(BYTE*)0x00F6B787 = 3;
    //*(DWORD*)0x00F6B7B0 = 480 - 28;
    //*(DWORD*)0x00F6B7D5 = -640;
    //*(DWORD*)0x00F6B7F4 = 480 - 26;
    //*(DWORD*)0x00F6B918 = 640;
    //*(DWORD*)0x00F6B928 = 480 - 33;

    hook->resize(3);
    b = hook->begin();
    b++->setValue(H_DWORD, 0x00F6CC69, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F6CC71, MaxItemInfoLineValueP);
    b++->setValue(H_BYTE, 0x00F6CB1B, 3);
    cdeclCall1 my_F6CAF0 = (cdeclCall1)tools_relocation_hook(0xF6CAF0, 0xF6CCC2, hook);
    //sub_F6DBF0 -> sub_F6CAF0 00F6CCC2
    //*(DWORD*)0x00F6CC69 = 0x40000000; *(BYTE*)0x00F6CC71 = 3;
    //*(BYTE*)0x00F6CB1B = 32;

    hook->resize(1);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F6D615, MaxItemInfoLine - 3);
    cdeclCall1 my_F6D2A0 = (cdeclCall1)tools_relocation_hook(0xF6D2A0, 0x00F6D807, hook);

    hook->resize(1);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F6D132, MaxItemInfoLine - 3);
    cdeclCall my_F6CDE0 = (cdeclCall)tools_relocation_hook(0xF6CDE0, 0x00F6D296, hook);

    hook->resize(5);
    b = hook->begin();
    b++->setValue(H_CALL, 0x00F6DCE7, (int)my_F6B730);
    b++->setValue(H_CALL, 0x00F6DC3C, (int)my_F6CAF0);
    b++->setValue(H_CALL, 0x00F6DC42, (int)my_F6B4C0);
    b++->setValue(H_CALL, 0x00F6DCD6, (int)my_F6D2A0);
    b++->setValue(H_CALL, 0x00F6DCA6, (int)my_F6CDE0);
    cdeclCall my_F6DBF0 = (cdeclCall)tools_relocation_hook(0xF6DBF0, 0xF6DD49, hook);

    hook->resize(1);
    b = hook->begin();
    b++->setValue(H_CALL, 0x00F6EA45, (int)my_F6DBF0);
    my_F6E9A0 = (cdeclCall)tools_relocation_hook(0xF6E9A0, 0xF6EA9D, hook);
    gum_interceptor_replace_fast(v, (gpointer)0xF6E9A0, (gpointer)hook_F6E9A0, NULL);

    hook->resize(9);
    b = hook->begin();
    b++->setValue(H_DWORD, 0x00F5E6F3, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F5E6FB, MaxItemInfoLineValueP);
    b++->setValue(H_BYTE, 0x00F5E722, MaxItemInfoLine);
    b++->setValue(H_DWORD, 0x00F5E934, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F5E958, MaxItemInfoLineValueP);
    b++->setValue(H_BYTE, 0x00F5E95C, MaxItemInfoLine);
    b++->setValue(H_JUMP, 0x00F5E3B7, (int)drawName2);
    b++->setValue(H_WORD, 0x00F5E6DA, 0xB890);
    b++->setValue(H_WORD, 0x00F5E6DC, (int)hookDrawHeaderText);
    thisCall2Args2 drawItemInfoWinHeader_F5E200 = (thisCall2Args2)tools_relocation_hook(0xF5E200, 0xF5EDC1, hook);
    //drawItemInfoWinHeader_F5E200 00F5EDC1 信息栏最大显示30行 原来38
    //*(DWORD*)0x00F5E6F3 = 0x40000000; *(BYTE*)0x00F5E6FB = 3;
    //*(BYTE*)0x00F5E722 = 32;
    //*(DWORD*)0x00F5E934 = 0x40000000; *(BYTE*)0x00F5E958 = 3;
    //*(BYTE*)0x00F5E95C = 32;

    hook->resize(3);
    b = hook->begin();
    b++->setValue(H_DWORD, 0x00F60310, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F60318, MaxItemInfoLineValueP);
    b++->setValue(H_CALL, 0x00F60205, (int)drawItemInfoWinHeader_F5E200);
    thisCall1Args2 myDrawItemInfoWin_F601F0 = (thisCall1Args2)tools_relocation_hook(0x00F601F0, 0x00F6032E, hook);
    //drawItemInfoWin_F601F0
    //*(DWORD*)0x00F60310 = 0x40000000; *(BYTE*)0x00F60318 = 3;

    b = hook->begin();
    b++->setValue(H_DWORD, 0x00F601C2, MaxItemInfoLineValue); b++->setValue(H_BYTE, 0x00F601CA, MaxItemInfoLineValueP);
    b++->setValue(H_CALL, 0x00F5FF1E, (int)drawItemInfoWinHeader_F5E200);
    thisCall1Args2 myDrawEquimInfoWin_F5FEE0 = (thisCall1Args2)tools_relocation_hook(0xF5FEE0, 0x00F601E2, hook);
    //drawEquimInfoWin_F5FEE0
    //*(DWORD*)0x00F601C2 = 0x40000000; *(BYTE*)0x00F601CA = 3;

    hook->resize(3);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F603F0, MaxItemInfoLine);
    b++->setValue(H_CALL, 0x00F60397, (int)myDrawItemInfoWin_F601F0);
    b++->setValue(H_CALL, 0x00F6037D, (int)myDrawEquimInfoWin_F5FEE0);
    myShowInfoWin_F60330 = (thisCall1Args2)tools_relocation_hook(0xF60330, 0xF60495, hook);
    //ShowInfoWin_F60330
    //*(BYTE*)0x00F603F0 = MaxItemInfoLine;
    gum_interceptor_replace_fast(v, (gpointer)0xF60330, (gpointer)hookShowInfoWin_F60330, NULL);

    hook->resize(1);
    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F45DBB, MaxItemInfoLine);
    my_F45CA0 = (thisCall1Args2)tools_relocation_hook(0xF45CA0, 0xF45F40, hook);
    //sub_F45CA0
    //*(BYTE*)0x00F45DBB = MaxItemInfoLine;
    gum_interceptor_replace_fast(v, (gpointer)0xF45CA0, (gpointer)hook_F45CA0, NULL);


    b = hook->begin();
    b++->setValue(H_BYTE, 0x00F6B36B, MaxItemInfoLine);
    my_F6B330 = (cdeclCall6)tools_relocation_hook(0xF6B330, 0xF6B445, hook);
    //sub_F6B330
    //*(BYTE*)0x00F6B36B = MaxItemInfoLine;
    gum_interceptor_replace_fast(v, (gpointer)0xF6B330, (gpointer)hookSub_F6B330, NULL);
    delete hook;



    //独立攻击力拆分显示位物理和魔法
    *(BYTE*)0x00F4FB0F = 0xE9; *(DWORD*)0x00F4FB10 = 0xB9; // 跳过原有显示
    writeJmpCode((void*)0x00F55775, hookShowSeparateAttack);


    //兼容掉落金币G 424文本 信息栏显示金币
    *(DWORD*)0x00F5F63A = 23069;
    *(DWORD*)0x00F5FE7A = 23069;
    
    //信息窗口透明
    *(DWORD*)0x01822CD8 = (int)hookItemInfoWin__OnOpen_F405C0;

    //屏蔽装备对比
    gum_interceptor_replace_fast(v, (gpointer)0x4E12C0, (gpointer)hookGetBoolConfig_4E12C0 , (gpointer*)&getBoolConfig_4E12C0);

    //*(BYTE*)0x00F6B783 = 3;//最多显示3个信息窗
    //*(BYTE*)0x00F6B787 = 3;
    //*(BYTE*)0x00F6B6F8 = 32;
    //*(DWORD*)0x018253FC = 32;
    //*(DWORD*)0x00F6B5CA = 0x40000000; *(BYTE*)0x00F6B5D2 = 3;
    //*(DWORD*)0x00F6B7B0 = 480 - 28;
    //*(DWORD*)0x00F6B7D5 = -640;
    //*(DWORD*)0x00F6B7F4 = 480 - 26;
    //*(DWORD*)0x00F6B918 = 640;
    //*(DWORD*)0x00F6B928 = 480 - 33;
    //*(DWORD*)0x00F6CC69 = 0x40000000; *(BYTE*)0x00F6CC71 = 3;
    //*(BYTE*)0x00F6CB1B = 32;
    ////drawItemInfoWinHeader_F5E200 00F5EDC1 信息栏最大显示30行 原来38
    //*(BYTE*)0x00F45DBB = 32;
    //*(DWORD*)0x00F5E6F3 = 0x40000000; *(BYTE*)0x00F5E6FB = 3;
    //*(BYTE*)0x00F5E722 = 32;
    //*(DWORD*)0x00F5E934 = 0x40000000; *(BYTE*)0x00F5E958 = 3;
    //*(BYTE*)0x00F5E95C = 32;
    //*(DWORD*)0x00F60310 = 0x40000000; *(BYTE*)0x00F60318 = 3;
    //*(DWORD*)0x00F601C2 = 0x40000000; *(BYTE*)0x00F601CA = 3;
    //*(BYTE*)0x00F603F0 = 32;
    //*(BYTE*)0x00F6B36B = 32;
    //*(BYTE*)0x00F6D615 = 29;
}