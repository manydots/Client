#include "pch.h"
#include "common.h"
#include "hellPartyInfoWin.h"

const __declspec(noinline) wchar_t* getHellPartyDiff(void) {
    switch (*(BYTE*)0x1A6F6A1) {
    case 1:return L"非常困难";
    case 2:return L"困难";
    case 3:return L"普通";
    default:return L"普通";
    }
}

void HellPartyInfo_MyProcDraw(int *thisP) {
    WORD format[16];
    TextFormat__init_11C9510((int*)format);
    ((int*)format)[2] = *(DWORD*)0x01B56564;
    format[1] = 16 * 12;
    format[3] = TEXT_ALIGN_CENTER;//左对齐
    int* veiw = (int*)thisP[3];
    int x = veiw[5] + 6;
    int y = veiw[6];
    drawTextStart_12115B0(*(int**)0x1B5582C, (int)format);
    drawText_1211C30(*(int**)0x1B5582C, x, y + 12, 0xFF9BC8E6, (int)L"封印之门进展情况");
    drawTextEnd_12115D0(*(int**)0x1B5582C);
    format[3] = TEXT_ALIGN_LEFT;//左对齐
    drawTextStart_12115B0(*(int**)0x1B5582C, (int)format);
    wchar_t buf[16];
    drawText_1211C30(*(int**)0x1B5582C,  x, y + 45, 0xFF9BC8E6, (int)L" - 被击数");
    drawText_1211C30(*(int**)0x1B5582C, x, y + 60, 0xFF9BC8E6, (int)L" - 深渊派对难度：");
    drawTextEnd_12115D0(*(int**)0x1B5582C);

    format[3] = TEXT_ALIGN_RIGHT;//左对齐
    drawTextStart_12115B0(*(int**)0x1B5582C, (int)format);
    float count;
    decrypt_11A0DE0((int*)(*(int*)0x1A6A874 + 0x4C0), (*(int*)0x1A6A874 + 0x4C8), (int)&count);
    wsprintf(buf, L"%d/50", (int)-count);
    drawText_1211C30(*(int**)0x1B5582C, x, y + 45, 0xFF9BC8E6, (int)buf);
    const wchar_t* diff = getHellPartyDiff();
    drawText_1211C30(*(int**)0x1B5582C, x, y + 60, 0xFF9BC8E6, (int)diff);
    drawTextEnd_12115D0(*(int**)0x1B5582C);
}

void __fastcall HellPartyInfo_ProcDraw(int* thisP, int edx, int a2) {
    if (a2 == thisP[3])
        BasePopupWin__ProcDraw_EF7E20(thisP, a2);
    HellPartyInfo_MyProcDraw(thisP);
}
void HellPartyInfo_MyProc(int* thisP){
    if (IControl__IsClick_11BDFC0((int*)thisP[0x94])) {
        closeWin_E745B0(*(int**)0x1A6F750, HellPartyInfoWinId, 0xFFFFFFFF, 0);
    }
}
int __fastcall HellPartyInfo_Proc(int* thisP) {
    int ret = BasePopupWin__Proc_EFA900(thisP, 0);
    HellPartyInfo_MyProc(thisP);
    return ret;
}

int __fastcall HellPartyInfo_OnOpen(int* thisP, int edx, int a2, int a3) {
    setUiComponentVisable_11BE610((int*)thisP[0x32], 1);
    setUiComponentVisable_11BE610((int*)thisP[0x94], 1);
    //setUiComponentVisable_11BE610((int*)thisP[0x33], 0, 1);
    BasePopupWin__setPos_EF63E0(thisP, 425, 90, 1);
    ((BYTE*)thisP)[0x158] = 0;
    return 1;
}

int __fastcall HellPartyInfo_Destructor(int* thisP, int edx, int a2) {
    int obj = thisP[0x94];
    if (obj) {
        __asm {
            mov ecx, obj
            mov edx, [ecx]
            push 1
            call edx
        }
    }
    return BasePopupWin__Destructor_EF0FF0(thisP, edx, a2);
}

int* __fastcall HellPartyInfo_Constructor(int argc) {
    int* win = (int*)newUiComponent_11B0380(0x250);
    memset(win, 0, 0x250);
    BaseWin__Constructor_545A10(win, argc, HellPartyInfoWinId);
    BasePopupWin__setWinSize_EF95A0(win, 16, 5);
    BasePopupWin__setWinType_EF5F60(win, 3);
    win[0x4A] = 15;//title accesorry type

    int* typeInfo = (int*)malloc(0xB0);
    if (typeInfo == NULL) {
        DPRINTF("malloc vtable memory error!\n");
        return NULL;
    }
    memcpy(typeInfo, (void*)0x0181C720, 0xB0);
    typeInfo[1] = (int)&HellPartyInfo_ProcDraw;
    typeInfo[3] = (int)&HellPartyInfo_Destructor;
    typeInfo[4] = (int)&HellPartyInfo_Proc;
    typeInfo[6] = (int)&HellPartyInfo_OnOpen;
    //typeInfo[7] = (int)&QuestDetailWin_OnClose;
    typeInfo[8] = 0x1038170;//配置窗口显示层，通过配置窗口的父窗口实现
    *win = (int)&typeInfo[1];

    //typeInfo[0x25] = 0xEF91F0;//重写虚函数 返回 0/Esc不退出 1/退出
    ((BYTE *)win)[0x158] = 0; // isEscExit
    //win[0xA] = 200;//透明度
    win[0x62] = 0;

    win[0x94] = addCloseBtn(win, 0, 24);

    int* view = (int*)win[0x32];
    setUiComponentSize_11BE370(view, 16 * 12, 5 * 13 + 18);
    view[5] += 18;
    view[6] += 24;
    return win;
}