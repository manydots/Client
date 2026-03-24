#include "pch.h"
#include "common.h"
#include "questDetailWin.h"
#include "frida-gum.h"
#include "tools.h"
static int* winObj;

int* getQuestDetailWin(void) {
    return winObj;
}

void QuestDetailWin_setQuestData(int quest, BYTE flag) {
    if (winObj && winObj[0x62]) {
        thisCall2 onClose;
        if (winObj[0x63]) {
            onClose = (thisCall2)Vtable(winObj[0x63], 0x10);
            onClose((int*)winObj[0x63]);
        }
        onClose = (thisCall2)Vtable(winObj[0x62], 0x10);
        onClose((int*)winObj[0x62]);
        setQuestDetailData_ECCBF0((int*)winObj[0x62], (int)quest, flag);
        thisCall2 onOpen = (thisCall2)Vtable(winObj[0x62], 0x0C);
        onOpen((int*)winObj[0x62]);
    }
}

void QuestDetailWin_setEvenQuestData(int quest) {
    if (winObj && winObj[0x63]) {
        thisCall2 onClose;
        if (winObj[0x62]) {
            onClose = (thisCall2)Vtable(winObj[0x62], 0x10);
            onClose((int*)winObj[0x62]);
        }
        onClose = (thisCall2)Vtable(winObj[0x63], 0x10);
        onClose((int*)winObj[0x63]);
        setEventQuestDetailData_EC58F0((int*)winObj[0x63], (int)quest);
        thisCall2 onOpen = (thisCall2)Vtable(winObj[0x63], 0x0C);
        onOpen((int*)winObj[0x63]);
    }
}

thisCall1Args2 sub_ECDA40 = (thisCall1Args2)0xECDA40;
void __fastcall QuestDetailWin_ProcDraw(int* thisP, int edx, int a2) {
    if (a2 == thisP[3])
        BasePopupWin__ProcDraw_EF7E20(thisP, a2);

    thisCall1Args2 procDraw;   
    if (thisP[0x63]) {
        procDraw = (thisCall1Args2)Vtable(winObj[0x63], 0x04);
        procDraw((int*)thisP[0x63], a2);
    }  
    if (thisP[0x62]) {
        procDraw = (thisCall1Args2)Vtable(winObj[0x62], 0x04);
        procDraw((int*)thisP[0x62], a2);
    }
}

thisCall sub_ECBDD0 = (thisCall)0xECBDD0;
int __fastcall QuestDetailWin_Proc(int* thisP) {
    int ret = BasePopupWin__Proc_EFA900(thisP, 0);
    BYTE needClose = 0;
    thisCall2 proc;
    if (thisP[0x63]) {
        proc = (thisCall2)Vtable(winObj[0x63], 0x08);
        proc((int*)thisP[0x63]);
       if (IControl__IsClick_11BDFC0(((int***)winObj)[0x63][8])) {
            closeWin_E745B0(*(int**)0x1A6F750, QuestDetailWinId, 0xFFFFFFFF, 0);
            if ((isWinShowing_E71770(*(int**)0x1A6F750, 0x93))) {
                closeWin_E745B0(*(int**)0x1A6F750, 0x93, 0xFFFFFFFF, 0);
            }
        }
       needClose += RBYTE(thisP[0x63], 0x10);
    }
    if (thisP[0x62]) {
        proc = (thisCall2)Vtable(winObj[0x62], 0x08);
        proc((int*)thisP[0x62]);
        if (IControl__IsClick_11BDFC0(((int***)winObj)[0x62][0x30])) {
            closeWin_E745B0(*(int**)0x1A6F750, QuestDetailWinId, 0xFFFFFFFF, 0);
            if ((isWinShowing_E71770(*(int**)0x1A6F750, 0x93))) {
                closeWin_E745B0(*(int**)0x1A6F750, 0x93, 0xFFFFFFFF, 0);
            }
        }
        needClose += RBYTE(thisP[0x62], 0x10);
    }
    if (!needClose) {
        closeWin_E745B0(*(int**)0x1A6F750, QuestDetailWinId, 0xFFFFFFFF, 0);
    }
    return ret;
}

thisCall3Args2 NormalQuestDetailSubWin__Constructor_ECEAE0 = (thisCall3Args2)0xECEAE0;
thisCall3Args2 EvenQuestDetailSubWin__Constructor_EC57B0 = (thisCall3Args2)0xEC57B0;
thisCall1Args2 sub_ECB5B0 = (thisCall1Args2)0xECB5B0;
thisCall1Args2 sub_EF6970 = (thisCall1Args2)0xEF6970;


int __fastcall QuestDetailWin_OnOpen(int* thisP, int edx, int a2, int a3) {
    if (!thisP[0x62]) {
        int* subWin = (int*)new BYTE[0xE4];
        NormalQuestDetailSubWin__Constructor_ECEAE0(subWin, (int)thisP, 0, 16);
        thisP[0x62] = (int)subWin;
    }
    if (thisP[0x62]) {
        sub_ECB5B0((int*)thisP[0x62], 0);
    }
    if (!thisP[0x63]) {
        int* subWin = (int*)new BYTE[0x24];
        EvenQuestDetailSubWin__Constructor_EC57B0(subWin, (int)thisP, 0, 16);
        thisP[0x63] = (int)subWin;
    }
    sub_EF6970(thisP, 3);
    wchar_t titleBuf[64] = { 0 };
    int v[8];
    GameStrDup_411F20((int*)v, (int)titleBuf);
    BasePopupWin__setTitle_EFA040(thisP, v[0], v[1], v[2], v[3], v[4], v[5], v[6], (int)L"", -1);
    return 1;
}

void __fastcall QuestDetailWin_OnClose(int* thisP) {
    playSound_766160((int)L"WINDOW_CLOSE", -1, 0, 0);
    thisCall2 onClose = (thisCall2)Vtable(thisP[0x62], 0x10);
    onClose((int *)thisP[0x62]);
    onClose = (thisCall2)Vtable(thisP[0x63], 0x10);
    onClose((int*)thisP[0x63]);
}
//1A6F774 + 0x64 任务列表 
int* __fastcall QuestDetailWin_Destructor(int* thisP, int edx, int a2) {
    thisCall1Args2 destructor;
    if (thisP[0x62]) {
        destructor = (thisCall1Args2)Vtable(thisP[0x62], 0);
        destructor((int*)thisP[0x62], 1);
    }
    if (thisP[0x63]) {
        destructor = (thisCall1Args2)Vtable(thisP[0x63], 0);
        destructor((int*)thisP[0x63], 1);
    }
    BaseWin__Destructor_545CB0(thisP);
    if ((a2 & 1) != 0)
        delUiComponent_11B03C0((int)thisP);
    return thisP;
}

int* __fastcall QuestDetailWin_Constructor(int argc) {
    int* win = (int*)newUiComponent_11B0380(0x1CC);
    memset(win, 0, 0x1CC);
    BaseWin__Constructor_545A10(win, argc, QuestDetailWinId);
    BasePopupWin__setWinSize_EF95A0(win, 0x14, 0x15);
    BasePopupWin__setWinType_EF5F60(win, 5);
    win[0x4A] = 11;//title accesorry type

    int* typeInfo = (int *)malloc(0xB0);
    if (typeInfo == NULL) {
        printf("malloc vtable memory error!\n");
        return NULL;
    }
    memcpy(typeInfo, (void *)0x0181C720, 0xB0);
    typeInfo[1] = (int)&QuestDetailWin_ProcDraw;
    typeInfo[3] = (int)&QuestDetailWin_Destructor;
    typeInfo[4] = (int)&QuestDetailWin_Proc;
    typeInfo[6] = (int)&QuestDetailWin_OnOpen;
    typeInfo[7] = (int)&QuestDetailWin_OnClose;
    *win = (int) & typeInfo[1];
    win[0x62] = 0;

    *(BYTE*)0x00ECDB25 = 12;//标题x
    *(BYTE*)0x00ECDB23 = -32;//标题y
    *(BYTE*)0x00ECE694 = 12;//信息框y
    *(BYTE*)0x00ECE6C1 = 21;
    *(DWORD*)0x00ECE685 = 0xAA;//信息框高度
    *(DWORD*)0x00ECCDAD = 0xAA;//信息框高度
    *(BYTE*)0x00EC5623 = 0xEB;
    *(BYTE*)0x00ECC162 = 0xEB;
    
    writeNopCode((void*)0x00ECB1D8, 5);
    writeNopCode((void*)0x00ECB840, 0x38);//标题下横线
    setUiComponentPos_11BEAD0((int*)win[3], 0x20, 0xBC, 1);
    winObj = win;
    return win;
}