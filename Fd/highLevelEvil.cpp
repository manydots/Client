#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"
#include "highLevelEvil.h"


//#define EN_E3
int expandMode[4];

//BYTE isExpandMode = 0;
cdeclCallB isPartyLeader_1117570 = (cdeclCallB)0x1117570;
thisCall2 getPartyLeaderCharac_9264C0 = (thisCall2)0x9264C0;
thisCall1Args2 getPvfUiBtnByName_1063B00 = (thisCall1Args2)0x1063B00;
thisCall2 getPartyAverageLv_926760 = (thisCall2)0x926760;
thisCall2Args2 sub_292B349 = (thisCall2Args2)0x292B349;
thisBCall2 isGmUser_75B450 = (thisBCall2)0x75B450;
thisCall2 getCharacLevel_D10420 = (thisCall2)0xD10420;

BYTE checkIsHighLvParty() {
    int* party = *(int**)0x1A6F728, *charac, count = 0;
    for (int i = 0; i < 4; ++i) {
        if (party[6]) {
            charac = (int *)RDWORD(party[6], 0x39C);
            if (charac && getCharacLevel_D10420(charac) < 65)
                return 0;
            count++;
        }
    }
    return count > 2;
}

int __fastcall hookSub_292B349(int* thisP, int, int a1, int a2) {
    int ret = sub_292B349(thisP, a1, a2);
    if (thisP[0xA7] == 13) {
        //isExpandMode = 0;
        int v = 0;
        encrypt_11A0930(expandMode, (int) & v, (int)(expandMode + 2));
        int *expandBtn = (int *)getPvfUiBtnByName_1063B00((int*)thisP[0xED], (int)L"IDC_WORLDMAP_EXPAND_BUTTON");
        setUiComponentVisable_11BE610((int *)thisP[0x41], 0);
        //setUiComponentPos_11BEAD0((int*)thisP[0x41], -10000, -10000, 1);
        if (isPartyLeader_1117570()){
            setUiComponentPos_11BEAD0(expandBtn, 470, 421, 1);
        }
        else {
            setUiComponentPos_11BEAD0(expandBtn, -10000, -10000, 1);
        }
        setUiComponentVisable_11BE610(expandBtn, 1);
        v = 0;
        if (isGmUser_75B450((int*)getCNModule_706410()) || checkIsHighLvParty())
            v = 1;   

        setUiComponentEnable_11BE350(expandBtn, v);
        thisP[0x43] = (int)expandBtn;
    }
    return ret;
}

thisCall2Args2 CNWorldMap__setCtrlBtnVisable_1117B90 = (thisCall2Args2)0x1117B90;
int __fastcall CNWorldMap__setCtrlHellPartyVisable_1117B90(int* thisP, int, int id, int visable) {
    return CNWorldMap__setCtrlBtnVisable_1117B90(thisP, id, thisP[0xA7] == 13?0:visable);
}


int __fastcall getDungeonEvilValue_7DD790(int* thisP, int, int diff) {
    int mode = 0;
    decrypt_11A0DE0(expandMode, (int)(expandMode + 2), (int)&mode);
    int* evil = &thisP[3 * diff + 0x112 + mode * 0xF];
    decrypt_11A0DE0(evil, (int)(evil + 2), (int) & diff);
    return diff;
}

thisCall1Args2 GameList__begin_131D710 = (thisCall1Args2)0x131D710;
thisBCall1Args2 GameList__isNotEquel_92FDF0 = (thisBCall1Args2)0x92FDF0;
thisCall2 GameList__getValueP_95D920 = (thisCall2)0x95D920;
thisCall2Args2 GameList__iteratorAdd_764750 = (thisCall2Args2)0x764750;
thisCall2 BalloonView__setup_1078880 = (thisCall2)0x1078880;
thisCall2 sub_E5FA60 = (thisCall2)0xE5FA60;

thisCall2Args2 CNSelectDungeonModule__selectMapBalloon_111ADF0 = (thisCall2Args2)0x111ADF0;
thisCall2 CNSelectDungeonModule__clearDisplayDungeon_1125E50 = (thisCall2)0x1125E50;
thisCall1Args2 CNSelectDungeonModule__addDisplayDungeon_1125F50 = (thisCall1Args2)0x1125F50;
thisCall2Args2 CNRDUdpModule__makePkg_E5B5F0 = (thisCall2Args2)0xE5B5F0;
thisCall1B2 CNRDUdpModule__pushByte_76F110 = (thisCall1B2)0x76F110;
thisCall4Args2 CNRDUdpModule__sendPkg_E5C970 = (thisCall4Args2)0xE5C970;
thisCall1Args2 CNRDUdpModule__readByte_76F280 = (thisCall1Args2)0x76F280;
void procExpandMode(int* cmodule, int* btn) {
    int mode = (wcscmp((wchar_t*)(btn + 0xC6), L"勇者模式") != 0);
    //if (mode == isExpandMode)  return;
    encrypt_11A0930(expandMode, (int)&mode, (int)(expandMode + 2));
    //isExpandMode = mode;

    CNSelectDungeonModule__clearDisplayDungeon_1125E50(cmodule);
    if (!mode) {
#ifdef EN_E3
        for (int id = 62; id <= 67; id++)
#else
        for (int id = 62; id <= 64; id++)
#endif // EN_E3
            CNSelectDungeonModule__addDisplayDungeon_1125F50(cmodule, id);
    }
    else {
        for (int id = 62; id <= 64; id++)
            CNSelectDungeonModule__addDisplayDungeon_1125F50(cmodule, id);
    }
    int* worldMap = (int*)cmodule[0xEC];
    if (worldMap) {
        int* childList = (int*)worldMap[9] + 0x19;
        int b[4], e[4], l[6], * p, dungeonId;
        GameList__begin_131D710(childList, (int)b);
        GameVector__begin_1176170(childList, (int)e);//GameList__end_131D710
        while (GameList__isNotEquel_92FDF0(b, (int)e)) {
            p = (int*)GameList__getValueP_95D920(b);
            if (RDWORD(*p, 8) == 0x0E) {
                p = (int*)RTDynamicCast_13D76DF((int)*p, 0, 0x019D9688, 0x1A39E74, 0);
                if (p) {
                    BalloonView__setup_1078880(p);
                    dungeonId = ((int**)p)[0xD3][0x03];
                    if (mode) {
                        if (dungeonId > 64)
                            setUiComponentVisable_11BE610(p, 0);
                        else
                            setUiComponentVisable_11BE610(p, 1);
                    }
                    else {
                        setUiComponentVisable_11BE610(p, 1);
                    }
                }
            }
            GameList__iteratorAdd_764750(b, (int)l, 0);
        }
    }
    if (isPartyLeader_1117570()) {
        closeWin_E745B0(*(int **)0x1A6F750, 0x83, 0xFFFFFFFF, 0);
        CNRDUdpModule__makePkg_E5B5F0(*(int**)0x1A6F748, 0x41, 2);
        CNRDUdpModule__pushByte_76F110(*(int**)0x1A6F748, mode);
        CNRDUdpModule__sendPkg_E5C970(*(int**)0x1ADD538, 1, 0xFFFFFFFF, 0, 3);
    }
}


thisCall1Args2 procMouseClickEvent_11C01E0 = (thisCall1Args2)0x11C01E0;
void handleExpandPkg(int* a2) {
    BYTE mode = 0;
    CNRDUdpModule__readByte_76F280(a2, (int)&mode);
    //printf("[%d, %d, %d]\n", a1[0], RWORD(a1, 1), mode);
    int* cmodule = (int*)getCNModule_706410();
    int* selectDungeonModule = (int*)cmodule[0x2C];
    if (!isPartyLeader_1117570()) {
        int* btn = (int*)selectDungeonModule[0x43];
        if (btn) {
            int isExpandMode = (wcscmp((wchar_t*)(btn + 0xC6), L"勇者模式") != 0);
            encrypt_11A0930(expandMode, (int)&isExpandMode, (int)(expandMode + 2));
            if (isExpandMode != mode) {
                *(DWORD*)0x1A42520 = btn[0xD];
                procMouseClickEvent_11C01E0((int*)btn[0x17], (int)btn);
                procExpandMode(selectDungeonModule, btn);
                    
            }
        }
    }
    CNSelectDungeonModule__selectMapBalloon_111ADF0(selectDungeonModule, 0, 0);
}

cdeclCall3 sub_555890 = (cdeclCall3)0x555890;
void __cdecl hookSub_555890(char* a1, int* a2, int a3) {
    if (a1[0] != 2 || RWORD(a1, 1) != 0x41) {
        sub_555890((int)a1, (int)a2, a3);
    }
    else {
        handleExpandPkg(a2);
    }
}

thisBCall2Args2 IsKey_11CBAB0 = (thisBCall2Args2)0x11CBAB0;
thisCall11Args2 drawTextToast_4CED30 = (thisCall11Args2)0x4CED30;
thisCall2 sub_1119D20 = (thisCall2)0x1119D20;
int __fastcall expandBtnProc(int* thisP) {
    int ret = sub_1119D20(thisP);
    if (thisP[0xA7] == 13 && thisP[0x43]) {
        int* btn = (int*)thisP[0x43];
        if (IControl__IsOverOrClick_11BE040(btn)) {
            int x = GetXPos_42FF60(btn);
            int y = GetYPos_11BE300(btn);
            drawTextToast_4CED30((*(int***)0x1A6F750)[0xF], x, y, -1, -1, 1, (int)L"快速键 : F11", 0, 0, 0x640, 0, 0);
        }
        if (IControl__IsClick_11BDFC0(btn)) {
            procExpandMode(thisP, btn);
        }
        if (IsKey_11CBAB0(*(int**)0x1B56D78, 0x5B, 0)) {
            //thisCall2Args2 sub_11BFD90 = (thisCall2Args2)0x11C01E0;
            //5C char __thiscall sub_11BFD90(int this, char a2, char a3)
            //sub_11BFD90(btn, 0, 0);
            *(DWORD*)0x1A42520 = btn[0xD];
            procMouseClickEvent_11C01E0((int*)btn[0x17], (int)btn);
            procExpandMode(thisP, btn);
        }
    }
    return ret;
 }

//thisCall2Args2 CNRDUdpModule__makePkg_E5B5F0 = (thisCall2Args2)0xE5B5F0;
//int __fastcall hookCNRDUdpModule__makePkg_E5B5F0(int* thisP, int, int a2, char a3) {
//    int ret = CNRDUdpModule__makePkg_E5B5F0(thisP, a2, a3);
//    int retAddr = (int)_ReturnAddress();
//    if (retAddr != 0x00814772 && retAddr != 0x008a8d4d && retAddr != 0x00e5e91c) {
//        printf("0x%08x[%d %d]\n", retAddr, a2, a3);
//    }
//    return ret;
//}

thisCall1Args2 CNSelectDungeonModule__getBalloonDungeonInfo_B25CA0 = (thisCall1Args2)0xB25CA0;
void __fastcall hookHighLevelEvilSendPkg(int* thisP, int, BYTE a2) {
    //PkgPushByte_1133120(thisP, a2);
    //int* cmodule = (int*)getCNModule_706410();
    //int* selectDungeonModule = (int*)cmodule[0x2C];
    //if (selectDungeonModule[0x91] == -1) {
    //    PkgPushByte_1133120(thisP, a2);
    //    return;
    //}
    //int dungeonId = *(int *)CNSelectDungeonModule__getBalloonDungeonInfo_B25CA0(selectDungeonModule + 0x8C, selectDungeonModule[0x91]);
    int dungeonId;
    __asm mov dungeonId, edi;
    if (dungeonId >= 62 && dungeonId <= 64) {
        int mode = 0;
        decrypt_11A0DE0(expandMode, (int)(expandMode + 2), (int)&mode);
        //printf("expandMode:%d\n", dungeonId);
        PkgPushByte_1133120(thisP, mode);
    }
    else {
        PkgPushByte_1133120(thisP, a2);
    }
}

void highLevelEvil_UiMgr__initCb(int* thisP) {
    initEncryptKey_11A2470(expandMode);
    int mode = 0;
    encrypt_11A0930(expandMode, (int)&mode, (int)(expandMode + 2));
}

//
cdeclCall1 getDungeonObj_439F00 = (cdeclCall1)0x439F00;
int __cdecl getDimensionDungeonObj_439F00(int dungeonId) {
    BYTE* ret = (BYTE*)getDungeonObj_439F00(dungeonId);
    if (dungeonId >= 62 && dungeonId <= 64) {
        int mode = 0;
        decrypt_11A0DE0(expandMode, (int)(expandMode + 2), (int)&mode);
        if (mode) {
            *(ret + 0x334) = 3;
        }
        else {
            *(ret + 0x334) = 2;
        }
    }
    return (int)ret;
}
//00F992D1
void highLevelEvilInit() {
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x7DD790, (gpointer)getDungeonEvilValue_7DD790, NULL);
    gum_interceptor_replace_fast(v, (gpointer)0x555890, (gpointer)hookSub_555890, (gpointer*)&sub_555890);
    //gum_interceptor_replace_fast(v, (gpointer)0xE5B5F0, (gpointer)hookCNRDUdpModule__makePkg_E5B5F0, (gpointer *)&CNRDUdpModule__makePkg_E5B5F0);
    writeCallCode((void*)0x00740A62, hookSub_292B349);
    writeCallCode((void*)0x01118CF4, CNWorldMap__setCtrlHellPartyVisable_1117B90);
    writeCallCode((void*)0x011274AD, expandBtnProc);
    writeCallCode((void*)0x01119C3E, hookHighLevelEvilSendPkg);

    writeCallCode((void*)0x00F98FA3, getDimensionDungeonObj_439F00);
    writeCallCode((void*)0x0070E86E, getDimensionDungeonObj_439F00);
}