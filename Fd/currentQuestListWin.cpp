#include "pch.h"
#include "common.h"
#include "currentQuestListWin.h"
#include "tools.h"
#include "frida-gum.h"
static int* winObj;

int getCurrentQuestSubWin(void) {
    if (!winObj || !winObj[0x6d]) {
        if (!(isWinShowing_E71770(*(int**)0x1A6F750, CurrentQuestListWinId)))
            showWin_E77470(*(int**)0x1A6F750, CurrentQuestListWinId, 0, 0);
    }
    return winObj[0x6d];
}

void __fastcall CurrentQuestListWin_ProcDraw(int* thisP, int edx, int a2) {
    if (a2 == thisP[3])
        BasePopupWin__ProcDraw_EF7E20(thisP, a2);
    thisCall1Args2 procDraw = (thisCall1Args2)Vtable(thisP[0x6D], 0x04);
    procDraw((int *)thisP[0x6D], a2);
}

int __fastcall CurrentQuestListWin_Proc(int* thisP) {
    int ret = BasePopupWin__Proc_EFA900(thisP, 0);
    thisCall2 proc = (thisCall2)Vtable(thisP[0x6D], 0x08);
    proc((int*)thisP[0x6D]);
    return ret;
}

//thisCall2 QuestListWin__setTagTitle_ECFC90 = (thisCall2)0xECFC90;
thisCall3Args2 CurrentQuestSubWin__Constructor_ECAAE0 = (thisCall3Args2)0xECAAE0;
int __fastcall CurrentQuestListWin_OnOpen(int* thisP, int edx, int a2, int a3) {
    if (!thisP[0x6D]) {
        int *p = (int *)new BYTE[0x94u];
        if (p) {
            thisP[0x6D] = CurrentQuestSubWin__Constructor_ECAAE0(p, (int)thisP, 0, 0);
            thisCall2 onOpen = (thisCall2)Vtable(p, 0x0C);
            onOpen(p);
            setUiComponentVisable_11BE610(((int***)thisP)[0x6D][0x1F], 0);
        }   
    } else {
        thisCall2 onOpen = (thisCall2)Vtable(thisP[0x6D], 0x0C);
        onOpen((int *)thisP[0x6D]);
        setUiComponentVisable_11BE610(((int***)thisP)[0x6D][0x1F], 0);
    }
    wchar_t titleBuf[64] = {0};
    int keyValue = getKeyMapValue_4DCDD0((int *)getConfigMgr_4E2630(), 0xD);
    if (keyValue > 0x85) {
        wsprintf(titleBuf, L"正在进行中的任务(无)");
    }
    else {
        wsprintf(titleBuf, L"正在进行中的任务(%s)", (wchar_t *)((int *)0x01B56D80)[keyValue]);
    }
    int v[7];
    GameStrDup_411F20((int*)v, (int)titleBuf);
    BasePopupWin__setTitle_EFA040(thisP, v[0], v[1], v[2], v[3], v[4], v[5], v[6], (int)L"正在进行中的任务(%s)", -1);
    setUiComponentPos_11BEAD0((int*)thisP[0x03], 340, 120, 0);
    return 1;
}

thisCall2 QuestListWin__OnClose_ECFB80 = (thisCall2)0xECFB80;
void __fastcall CurrentQuestListWin_OnClose(int* thisP) {
    //QuestListWin__OnClose_ECFB80(thisP);
    playSound_766160((int)L"WINDOW_CLOSE", -1, 0, 0);
    if (thisP[0x6D]) {
        thisCall2 onClose = (thisCall2)Vtable(thisP[0x6D], 0x10);
        onClose((int *)thisP[0x6D]);
    }
}

int* __fastcall CurrentQuestListWin_Destructor(int* thisP, int edx, int a2) {
    int obj = thisP[0x6D];
    if (obj) {
        __asm {
            mov ecx, obj
            mov edx, [ecx]
            push 1
            call edx
        }
    }
    if ((a2 & 1) != 0)
        delUiComponent_11B03C0((int)thisP);
    return thisP;
}

int* __fastcall CurrentQuestListWin_Constructor(int argc) {
    int* win = (int*)newUiComponent_11B0380(0x1CC);
    memset(win, 0, 0x1CC);
    BaseWin__Constructor_545A10(win, argc, CurrentQuestListWinId);
    BasePopupWin__setWinSize_EF95A0(win, 0x14, 0x17);
    BasePopupWin__setWinType_EF5F60(win, 5);
    win[0x4A] = 15;//title accesorry type
    
   int* typeInfo = (int*)malloc(0xB0);
    if (typeInfo == NULL) {
        printf("malloc vtable memory error!\n");
        return NULL;
    }
    memcpy(typeInfo, (void*)0x0181C720, 0xB0);
    typeInfo[1] = (int)&CurrentQuestListWin_ProcDraw;
    typeInfo[3] = (int)&CurrentQuestListWin_Destructor;
    typeInfo[4] = (int)&CurrentQuestListWin_Proc;
    typeInfo[6] = (int)&CurrentQuestListWin_OnOpen;
    typeInfo[7] = (int)&CurrentQuestListWin_OnClose;
    //*win = 0x0181C724;
    *win = (int)&typeInfo[1];
    //win[0x4A] = 15;//title accesorry type
    //win[0x62] = 0;
    writeNopCode((void*)0x00EC9E64, 38);//屏蔽对父窗口的TAG操作，因为此窗口只有一个tag
    writeNopCode((void*)0x00ECA057, 38);
    //writeNopCode((void*)0x00ECA968, 5);
    writeNopCode((void*)0x00EC8E7D, 0x4B);//屏蔽按地下城查看文案

    writeNopCode((void*)0x00ECA170, 17);//屏蔽原detail窗口的onOpen调用

    *(BYTE*)0x00EC8F39 = 3;
    *(BYTE*)0x00ECAA28 = 0;
    *(BYTE*)0x00EC9793 = 11;
    *(BYTE*)0x00EC989F = 11;

    
    //setUiComponentPos_11BEAD0((int*)win[3], 32, 188, 1);
    winObj = win;
    return win;
}