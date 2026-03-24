#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"

#define RIDING_EN
#ifdef RIDING_EN

thisCall2 CNRDUdpModule__getModuleStage_76F3A0 = (thisCall2)0x76F3A0;
thisCall6Args2 sengGameNoticeMsg_95D130 = (thisCall6Args2)0x95D130;

#define RidingKeyMap		66
#define CoolTime0		    180000
#define CoolTime1		    360000
static int *ridableBtn;
static int* myCNRidableObjectTypeInfo;
static int* ridableImg;
static int* ridableIconImg;
static struct{
    int* spinner;
    int* btn[6];
    int ridableId[5];
    BYTE btnShortCut[6];
    BYTE questSta[5];
    BYTE state;
    int cooltime[5][4];
    int ridingFlag[4];
    int timer[7];
    int startT;

}ridableSpinner = { NULL,{0},{61735, 63009, 63008, 62132, 62133},{55,73,58,60,61,62}};

int __fastcall getSummonAni(int monsterId, int, int size) {
    int *ani = (int*)newUiComponent_11B0380(size);
    switch (monsterId) {
    case 61735:
    case 63009:
    case 63008:
    case 62132:
    case 62133:
        return loadAniObjByPath_109A4E0(ani, (int)L"ui/fd/ridableevent/summonriding.ani", 1, 0);
    default:
        return loadAniObjByPath_109A4E0(ani, (int)L"Monster/Spirit/FireAnimation/Summon.ani", 1, 0);
    }
}

void Naked 新增召唤坐骑动画(void) {
    //00B37D48
    __asm {
        mov  ecx, dword ptr[esi + 0x0DCD]
        call getSummonAni
        mov edx, 0xB37D7D
        jmp edx
    }
}

#define HEX_100         0x42C80000
#define DurationTime    (60 + 2)

static int timer[7];
static int blinkStartT[4];
static int blinkAlpha;
cdeclCall8 CNObject__drawBlinkEffect_7FE820 = (cdeclCall8)0x7FE820;
thisCall2 CNRidableObject__sendStopState_B4E210 = (thisCall2)0xB4E210;
thisCall2 myCNRidableObject__procAppend_B55C10;
void stopRiding(int* ridableObj);
void __fastcall myCNRidableObject__procAppend(int* thisP) {
    myCNRidableObject__procAppend_B55C10(thisP);
    DWORD monsterId = thisP[0x95];
    switch (monsterId) {
    case 61735:
    case 63009:
    case 63008:
    case 62132:
    case 62133:break;
    default:return;
    }
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP) || !CNTimer__IsStart_11BA4E0(timer)) return;
    int now = CNTimer__Get_11BA640(timer);
    if (now > (DurationTime) * 1000) {
        stopRiding(thisP);
    }
    else if (now > (DurationTime - 10) * 1000) {
        int start;
        int mode = 0;
        decrypt_11A0DE0(blinkStartT, (int)(blinkStartT + 2), (int)&start);
        int passT = now - start;
        if (passT >= 2000) {
            encrypt_11A0930(blinkStartT, (int)&now, (int)(blinkStartT + 2));
            blinkAlpha += 30;
        }
        else {
            CNObject__drawBlinkEffect_7FE820(0, (int)thisP, 0xFFFFFFFF, passT + 1000, 2000, blinkAlpha, HEX_100, 1);
        }
    }
}

thisCall2Args2 CNRidableObject__Constructor_D26460 = (thisCall2Args2)0xD26460;
int __fastcall hookCNRidableObject__Constructor_D26460(int* thisP, int, int id, int lv) {
    int ret = CNRidableObject__Constructor_D26460(thisP, id, lv);
    *(int*)ret = (int) & myCNRidableObjectTypeInfo[1];
    return ret;
}

#define STATE_HIDED		0
#define STATE_SHOWED	1
#define STATE_HIDING	2
#define STATE_SHOWING	3
#define START           614
#define END             420
#define SCROLL_TIME     300

void ridableSpinner_setState(int newState) {
    if (newState == STATE_HIDED) {
        setUiComponentVisable_11BE610(ridableSpinner.spinner, 0);
    }
    else if (newState == STATE_SHOWED) {
        setUiComponentVisable_11BE610(ridableSpinner.spinner, 1);
    }
    else if (ridableSpinner.state != newState) {
        ridableSpinner.startT = CNTimer__Get_11BA640(ridableSpinner.timer);
        if (newState == STATE_SHOWING) {
            setUiComponentVisable_11BE610(ridableSpinner.spinner, 1);
            setUiComponentPos_11BEAD0(ridableSpinner.spinner, START, 356, 1);
        }
        else
            setUiComponentPos_11BEAD0(ridableSpinner.spinner, END, 356, 1);
    }
    ridableSpinner.state = newState;
}

forceinline void  ridableSpinner_ProcState(void) {
    //printf("ridableSpinner_ProcState");
    int currentT = CNTimer__Get_11BA640(ridableSpinner.timer);
    int xPos;
    switch (ridableSpinner.state) {
    case STATE_HIDING:
        xPos = getLinearValue_11B98C0(END, START, currentT - ridableSpinner.startT, SCROLL_TIME);
        if (xPos == START)ridableSpinner_setState(STATE_HIDED);
        else setUiComponentPos_11BEAD0(ridableSpinner.spinner, xPos, 356, 1);
        break;
    case STATE_SHOWING:
        xPos = getLinearValue_11B98C0(START, END, currentT - ridableSpinner.startT, SCROLL_TIME);
        if (xPos == END)ridableSpinner_setState(STATE_SHOWED);
        else setUiComponentPos_11BEAD0(ridableSpinner.spinner, xPos, 356, 1);
        break;
    }
}

void __fastcall ridableSpinner_Proc(int* thisP) {
    ridableSpinner_ProcState();
    int x = thisP[5];
    int y = thisP[6];
    int v = getImageByPos_11B4BD0(ridableImg, 2);
    drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, v); 
}

bool isOverRidableSpinner(void) {
    int mouseX = MousePosX;
    int mouseY = MousePosY;
    int x = ridableSpinner.spinner[5];
    int y = ridableSpinner.spinner[6];
    if (mouseX >= x - 1 && mouseX <= x + 201 && mouseY >= y - 1 && mouseY <= y + 37) {
        return true;
    }
    return false;
}

void setRidableSpinnerBtnEnByIdx(int idx, bool en) {
    int flag = 0, start, now = TimeGetTime();
    decrypt_11A0DE0(ridableSpinner.ridingFlag, (int)(ridableSpinner.ridingFlag + 2), (int)&flag);
    decrypt_11A0DE0(ridableSpinner.cooltime[idx], (int)(ridableSpinner.cooltime[idx] + 2), (int)&start);
    start = now - start;
    if (flag || !ridableSpinner.questSta[idx] || start < (idx > 2 ? CoolTime1 : CoolTime0)) {
        setUiComponentEnable_11BE350(ridableSpinner.btn[idx], 0);
    }
    else {
        setUiComponentEnable_11BE350(ridableSpinner.btn[idx], en);
    }
}

void setRidableSpinnerBtnEn(bool en) {
    int flag = 0, start, now = TimeGetTime();
    decrypt_11A0DE0(ridableSpinner.ridingFlag, (int)(ridableSpinner.ridingFlag + 2), (int)&flag);
    for (int i = 0; i < 5; ++i) {
        decrypt_11A0DE0(ridableSpinner.cooltime[i], (int)(ridableSpinner.cooltime[i] + 2), (int)&start);
        start = now - start;
        if (flag || !ridableSpinner.questSta[i] || start < (i > 2 ? CoolTime1 : CoolTime0)) {
            setUiComponentEnable_11BE350(ridableSpinner.btn[i], 0);
        }
        else {
            setUiComponentEnable_11BE350(ridableSpinner.btn[i], en);
        }
    }
    setUiComponentEnable_11BE350(ridableSpinner.btn[5], !en);
}

void stopRiding(int *ridableObj) {
    //if (CGameModule != MODULE_MAIN_GAME) return;
    if (CNTimer__Get_11BA640(timer) < 2000) return;
    if (!ridableObj) {
        int* charac = *(int**)0x01AC790C;
        if (!charac) return;
        ridableObj = (int*)charac[0x1534];
        if (!ridableObj) return;
    }
    DWORD monsterId = ridableObj[0x95];
    switch (monsterId) {
    case 61735:
    case 63009:
    case 63008:
    case 62132:
    case 62133:
        CNRidableObject__sendStopState_B4E210(ridableObj);
        setRidableSpinnerBtnEn(true);
        CNTimer__Reset_11BA3F0(timer);
    }
}

void startRiding(int id) {
    if (CGameModule != MODULE_MAIN_GAME) return;
    int* charac = *(int**)0x01AC790C;
    if (!charac) return;
    int* ridableObj = (int*)charac[0x1534];
    if (ridableObj) return;
    DWORD start = 0, coolTime = id > 2 ? CoolTime1 : CoolTime0;
    decrypt_11A0DE0(ridableSpinner.cooltime[id], (int)(ridableSpinner.cooltime[id] + 2), (int)&start);
    start = TimeGetTime() - start;
    if (start < coolTime) return;
    //isRidingToObject
    thisCall2 isRidingToObject = (thisCall2)Vtable(charac, 0x8B0);
    if (isRidingToObject(charac) == 2) {
        sengGameNoticeMsg_95D130((*(int***)0x1A6F750)[0x10], (int)L"该状态下无法变身！", 0xFF9BC8E6, 0x10, 0, 0, 0);
        return;
    }
    //if(isRidingToObject)
    if (!*(int**)0x1A6F748) return;
    int* stage = (int*)CNRDUdpModule__getModuleStage_76F3A0(*(int**)0x1A6F748);
    if (!stage || !stage[0x23]) return;
    int* dungeon = (int*)stage[0x23];
    if (RBYTE(dungeon, 0x330) || RBYTE(dungeon, 0x2D8)) return;//IsDimensionDungeon || IsAncientDungeon
    int characLv = 1;
    decrypt_11A0DE0(charac + 0x8C7, (int)(charac + 0x8C9), (int)&characLv);
    sq_StartWrite_BB16F0(charac);
    sq_WriteBool_67E850(charac, 1);//召唤动画
    sq_WriteDword_67E870(charac, ridableSpinner.ridableId[id]);//id
    sq_WriteWord_BB2B50(charac, 0);//阵营 0/友方 100/中立 200/对立
    sq_WriteBool_67E850(charac, characLv);//lv
    sq_sendCreatePassiveObjectPacket_B6A990(charac, 48024, 0, 0, 0, 0);
    CNTimer__Reset_11BA3F0(timer);
    CNTimer__Start_11BAA10(timer, 0, 0);
    int mode = 0;
    encrypt_11A0930(blinkStartT, (int)&mode, (int)(blinkStartT + 2));
    blinkAlpha = 25;
    id += 1;
    encrypt_11A0930(ridableSpinner.ridingFlag, (int)& id, (int)(ridableSpinner.ridingFlag + 2));
    setRidableSpinnerBtnEn(false);
}

int getRidableBtnIdx(int* thisP) {
    for (int i = 0; i < 6; ++i)if (thisP == ridableSpinner.btn[i]) return i;
    return 0;
}

void __fastcall ridableBtn_Proc(int* thisP) {
    if (thisP == ridableBtn) {
        if (CGameModule != MODULE_MAIN_GAME) return;
        bool isKey = sq_IsKeyDown_5AFB50(RidingKeyMap, KEYVALUE_MASK);
        //bool isKey = IsKeyDown_11CBC60(*(int**)0x1B56D78, 7, 0);
        if (isKey || ridableSpinner.state & 0x01) {
            for (int i = 0; i < 6; ++i) {
                if (IControl__IsEnable_E6E6C0(ridableSpinner.btn[i]) &&
                    IsKeyDown_11CBC60(*(int**)0x1B56D78, ridableSpinner.btnShortCut[i], KEYVALUE_MASK)) {
                    if (i == 5) stopRiding(NULL);
                    else startRiding(i);
                }
            }
        }
    }
    else if(IControl__IsVisible_92CFE0(thisP) && IControl__IsEnable_E6E6C0(thisP)){
        if (IControl__IsOver_11BE020(thisP))
            drawMouseOverGridImg_7B5000(thisP[5], thisP[6]);
        if (CGameModule != MODULE_MAIN_GAME) return;
        if (IControl__IsClick_11BDFC0(thisP)) {
            int idx = getRidableBtnIdx(thisP);
            if (idx == 5)stopRiding(NULL);
            else startRiding(idx);
        }
    }
}


void __fastcall ridableBtn_ProcSigle(int* thisP, int idx) {
    if (!ridableSpinner.questSta[idx]) return;
    int x = thisP[5];
    int y = thisP[6];
    DWORD start = 0, coolTime = idx > 2 ? CoolTime1 : CoolTime0;
    decrypt_11A0DE0(ridableSpinner.cooltime[idx], (int)(ridableSpinner.cooltime[idx] + 2), (int)&start);
    start = TimeGetTime() - start;
    if (start < coolTime) {
        //printf("y:%d %f\n", y, 28.0 * start / coolTime);
        setGameCanvasSize_6FD880(0, 0, 640, y + 28.0 * (1 - (float)start / coolTime));
        drawImgByXY2_11B41E0(*(int**)0x1B5582C, x, y, *(int*)0x1A7FDC4, 1.0f, 1.0f, 0, 0x80FFFFFF, *(float*)0x01562250, *(float*)0x01562250);
        resetGameCanvasSize_6FD8D0();
    }
    else {
        setRidableSpinnerBtnEnByIdx(idx, true);
    }
}

void __fastcall ridableBtn_DrawProc(int* thisP) {
	BaseBtn__Proc_11C35D0(thisP);
    int* shortCutImg = (int*)getPreloadImg_11BB1B0(*(int**)0x1A6A870, 77);
    if (thisP == ridableBtn) {
        if (IControl__IsOver_11BE020(thisP) || isOverRidableSpinner() || sq_IsKeyDown_5AFB50(RidingKeyMap, KEYVALUE_MASK)) {//IsKeyDown_11CBC60((int*)(*(DWORD*)0x1B56D78), 0, 7, 0))  sq_IsKeyDown_5AFB50(KeyMap[i], KEYVALUE_MASK);
            if (ridableSpinner.state == STATE_HIDED) ridableSpinner_setState(STATE_SHOWING);
        }
        else {
            if (ridableSpinner.state == STATE_SHOWED) ridableSpinner_setState(STATE_HIDING);
        }
        int keyMapIndex = getKeyMapValue_4DCDD0((int*)0x1A4B570, RidingKeyMap);
        if (keyMapIndex < 106) {
            int x = thisP[5] + 4;
            int y = thisP[6] + 8;
            int v = getImageByPos_11B4BD0(shortCutImg, keyMapIndex);
            drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, v);
        }
  
    }
    /*else if(IControl__IsEnable_E6E6C0(thisP)) {*/
    else if(IControl__IsVisible_92CFE0(thisP)){
        int x = thisP[5];
        int y = thisP[6];
        int idx = getRidableBtnIdx(thisP);
        if (idx <= 4 && !IControl__IsEnable_E6E6C0(thisP)) {
            ridableBtn_ProcSigle(thisP, idx);
        }
        //if (IControl__IsOver_11BE020(thisP)) 
        //    drawMouseOverGridImg_7B5000(x, y);
        //if (IControl__IsClick_11BDFC0(thisP)) {
        //    if(idx == 5)stopRiding(NULL);
        //    else startRiding(ridableSpinner.ridableId[idx]);
        //}
        int v = getImageByPos_11B4BD0(shortCutImg, ridableSpinner.btnShortCut[idx]);
        drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, v);
    }

    //if (IControl__IsClick_11BDFC0(ridableBtn)) {
    //    int* charac = *(int**)0x01AC790C;
    //    if (!charac) return;
    //    int* ridableObj = (int *)charac[0x1534];
    //    if (ridableObj) {
    //        //CNTimer__Reset_11BA3F0(ridableObj + 0x1549);
    //        //CNTimer__Start_11BAA10(ridableObj + 0x1549, 5000, 0);
    //        //CNRidableObject__sendStopState_B4E210(thisP);
    //        return;
    //    }
    //    sq_StartWrite_BB16F0(charac);
    //    sq_WriteBool_67E850(charac, 1);//召唤动画
    //    sq_WriteDword_67E870(charac, 61735);//id
    //    sq_WriteWord_BB2B50(charac, 0);//阵营 0/友方 100/中立 200/对立
    //    sq_WriteBool_67E850(charac, 70);//lv
    //    sq_sendCreatePassiveObjectPacket_B6A990(charac, 48024, 0, 0, 0, 0);
    //    CNTimer__Reset_11BA3F0(timer);
    //    CNTimer__Start_11BAA10(timer, 0, 0);
    //    blinkStartT = 0;
    //    blinkAlpha = 25;
    //}
    
}

void riding_OnNotiClearQuest(void) {
    for (int i = 0; i < 5; ++i) {
        ridableSpinner.questSta[i] = QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20552 + i);
    }
    setRidableSpinnerBtnEn(true);
}

void riding_OnFinshQuest(void) {
    riding_OnNotiClearQuest();
}



void riding_CNTownModule_onEnterModuleCb(int* thisP, int a2) {
    //printf("riding_CNTownModule_onEnterModuleCb %d\n", a2);
    if (a2 == 0 || a2 == 6) {
        for (int i = 0; i < 5; ++i) {
            int cooltime = TimeGetTime();
            encrypt_11A0930(ridableSpinner.cooltime[i], (int)&cooltime, (int)(ridableSpinner.cooltime[i] + 2));
        }
    }
    CNTimer__Reset_11BA3F0(timer);
    CNTimer__Start_11BAA10(timer, 0, 0);
    setUiComponentVisable_11BE610(ridableBtn, 1);
    ridableSpinner_setState(STATE_HIDED);
    setRidableSpinnerBtnEn(true);
}

void riding_CNTownModule__onExitModuleCb(int* thisP, int a2) {
    setUiComponentVisable_11BE610(ridableBtn, 0);
    ridableSpinner_setState(STATE_HIDED);
}

void riding_CNMainGameModule_onEnterModuleCb(int* thisP, int a2) {
    if (!*(int**)0x1A6F748) return;
    int* stage = (int*)CNRDUdpModule__getModuleStage_76F3A0(*(int**)0x1A6F748);
    if (!stage || !stage[0x23]) return;
    int* dungeon = (int*)stage[0x23];
    if (RBYTE(dungeon, 0x330) || RBYTE(dungeon, 0x2D8)) {//IsDimensionDungeon || IsAncientDungeon
        return;
    }
    CNTimer__Reset_11BA3F0(timer);
    CNTimer__Start_11BAA10(timer, 0, 0);
    setUiComponentVisable_11BE610(ridableBtn, 1);
    ridableSpinner_setState(STATE_HIDED);
    setRidableSpinnerBtnEn(true);
}

void riding_CNMainGameModule_onExitModuleCb(int* thisP, int a2) {
    setUiComponentVisable_11BE610(ridableBtn, 0);
    ridableSpinner_setState(STATE_HIDED);
    int flag = 0;
    decrypt_11A0DE0(ridableSpinner.ridingFlag, (int)(ridableSpinner.ridingFlag + 2), (int)&flag);
    if (flag) {
        flag -= 1;
        int cooltime = TimeGetTime();
        encrypt_11A0930(ridableSpinner.cooltime[flag], (int)&cooltime, (int)(ridableSpinner.cooltime[flag] + 2));
    }
    flag = 0;
    encrypt_11A0930(ridableSpinner.ridingFlag, (int)&flag, (int)(ridableSpinner.ridingFlag + 2));
}

void ridingInitDelay(int* thisP) {
    ridableImg = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/newstyle/windows/ridable_change.img");

    int typeInfoLen = 0x0185A8E0 - 0x0185A818;
    int* btnTypeInfo = (int*)malloc(typeInfoLen);
    if (btnTypeInfo == NULL) {
        printf("malloc vtable memory error!\n");
        return;
    }
    memcpy(btnTypeInfo, (void*)0x0185A818, typeInfoLen);
    btnTypeInfo[11] = (int)ridableBtn_DrawProc;
    btnTypeInfo[13] = (int)ridableBtn_Proc;

    int x = 614, y = 356;
    //ridableSpinner先初始化，显示优先级比ridableBtn低
    ridableSpinner.spinner = newUiComponent(((int***)thisP)[0x0F][2], x, y);
    typeInfoLen = 0x0185A6B0 - 0x0185A610;
    int* typeInfo = (int*)malloc(typeInfoLen);
    if (typeInfo == NULL) {
        printf("malloc vtable memory error!\n");
        return;
    }
    memcpy(typeInfo, (void*)0x0185A610, typeInfoLen);
    typeInfo[10] = (int)ridableSpinner_Proc;
    *ridableSpinner.spinner = (int)&typeInfo[1];

    ridableIconImg = (int *)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/newstyle/windows/ridableicon.img");
    for (int i = 0, pos = 0, x1; i < 6; ++i) {
        if (i == 1) pos = 4;
        else if(i == 2)pos = 2;
        else pos = i * 2;
        x1 = x + i * 30 + 4;
        ridableSpinner.btn[i] = newBtn(ridableSpinner.spinner, x1, y + 4, (int)ridableIconImg, pos, pos, pos, pos + 1);
        *ridableSpinner.btn[i] = (int)&btnTypeInfo[1];
        setUiComponentVisable_11BE610(ridableSpinner.btn[i], 1);
        if (i == 5)setUiComponentEnable_11BE350(ridableSpinner.btn[5], 0);
        else {
            initEncryptKey_11A2470(ridableSpinner.cooltime[i]);
            int cooltime = TimeGetTime();
            encrypt_11A0930(ridableSpinner.cooltime[i], (int)&cooltime, (int)(ridableSpinner.cooltime[i] + 2));
        }
    }
   

    x -= 10; y -= 2;
    ridableBtn = newBtn(((int***)thisP)[0x0F][2], x, y, (int)ridableImg, 0, 0, 0, 0);
    *ridableBtn = (int)&btnTypeInfo[1];

    //goldSkillShowBtn = newBtn(((int***)thisP)[0x0F][2], x, y, goldskillImg, 10, 10, 11, 0xffffffff);
    //goldSkillHideBtn = newBtn(((int***)thisP)[0x0F][2], x, y, goldskillImg, 12, 12, 12, 0xffffffff);
    CNTimer__Init_11BA940(ridableSpinner.timer);
    CNTimer__Reset_11BA3F0(ridableSpinner.timer);
    CNTimer__Start_11BAA10(ridableSpinner.timer, 0, 0);
    CNTimer__Init_11BA940(timer);
    initEncryptKey_11A2470(blinkStartT);
    int mode = 0;
    encrypt_11A0930(blinkStartT, (int)&mode, (int)(blinkStartT + 2));
    initEncryptKey_11A2470(ridableSpinner.ridingFlag);
    encrypt_11A0930(ridableSpinner.ridingFlag, (int)&mode, (int)(ridableSpinner.ridingFlag + 2));
}

void __fastcall fixRidableQuestLabelNpcDialogImp(int *thisP, int x, int y) {
    int* img = (int *)getPreloadImg_11BB1B0(*(int**)0x1A6A870, 20);
    int v = getImageByPos_11B4BD0(img, 60);
    drawImgByXY_11B3950(*(int**)0x1B5582C, x + 216, y + 66, v);
    v = getImageByPos_11B4BD0(ridableIconImg, ((int**)thisP)[0x5F][0xAE] * 2);
    drawImgByXY_11B3950(*(int**)0x1B5582C, x + 397, y + 71, v);
}

void Naked fixRidableQuestLabelNpcDialog() {
    //00FBB28D
    __asm {
        cmp ecx, 23
        jnz goExit
        push ebx
        push edi
        mov edx, ebx
        mov ecx, esi
        push edi
        call fixRidableQuestLabelNpcDialogImp
        pop edi
        pop ebx
        goExit:
        mov eax, dword ptr[esi + 0x3A8]
        mov ecx, 0x00FBB293
        jmp ecx
    }
}

bool __fastcall fixRidableQuestLabelDetailSubWinImp(int* thisP) {
    int type = ((int**)thisP)[0x05][0xA8];
    if (type != 23) return 1;
    int x = BaseSubWin__GetPosX_E86310(thisP) + 4;
    int y = BaseSubWin__GetPosY_E86350(thisP) + 184;
    drawTextStart_12115B0(*(int**)0x1B5582C,  (int)(thisP + 0x19));
    drawText_1211C30(*(int**)0x1B5582C, x, y, 0xFF93C5DD, (int)L"获得以下奖励。");
    drawTextEnd_12115D0(*(int**)0x1B5582C);

    int v = getImageByPos_11B4BD0((int *)thisP[0x0C], 60);
    BaseSubWin__DrawIcon_E86390(thisP, 22, 192, v, 0x3f800000, 0x3f800000, 0, -1);
    v = getImageByPos_11B4BD0(ridableIconImg, ((int**)thisP)[0x05][0xAE] * 2);
    BaseSubWin__DrawIcon_E86390(thisP, 22 + 181, 192 + 5, v, 0x3f800000, 0x3f800000, 0, -1);
    return 0;
}

void Naked fixRidableQuestLabelDetailSubWin() {
    //00ECDE4C
    __asm {
        call fixRidableQuestLabelDetailSubWinImp
        cmp al, 0
        jz goOk
        mov ecx, esi
        mov edx, 0xECD910
        call edx
        mov edx, 0x00ECDE51
        jmp edx
    goOk:
        mov ecx, 0xECDCA7
        jmp ecx
    }
}


void ridingInit(void) {
    //npc 对话窗口修复
    writeJmpCode((void*)0x00FBB28D, fixRidableQuestLabelNpcDialog);
    writeJmpCode((void*)0x00ECDE4C, fixRidableQuestLabelDetailSubWin);
    //变身额外技能框
    *(DWORD*)0x004C92BE = 634 * 0.8f + 5;//x
    *(DWORD*)0x004C92B9 = 489 * 0.8f + 5;//y
    int typeInfoLen = 0x0170FC38 - 0x0170F3C8;
    myCNRidableObjectTypeInfo = (int*)malloc(typeInfoLen);
    if (myCNRidableObjectTypeInfo == NULL) {
        printf("malloc vtable memory error!\n");
        return;
    }
    memcpy(myCNRidableObjectTypeInfo, (void*)0x0170F3C8, typeInfoLen);
    myCNRidableObjectTypeInfo[(0x0170F5BC - 0x0170F3C8)/4] = (int)myCNRidableObject__procAppend;
    writeJmpCode((void*)0x00B37D48, 新增召唤坐骑动画);
    
    //myCNRidableObject__procAppend_B55C10 = (thisCall2)tools_relocation(0xB55C10, 0x00B56D78)
    myCNRidableObject__procAppend_B55C10 = (thisCall2)0xB55C10;

    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0xD26460, (gpointer)hookCNRidableObject__Constructor_D26460, (gpointer *) & CNRidableObject__Constructor_D26460);
}
#else

void riding_OnNotiClearQuest(void) {
}

void riding_OnFinshQuest(void) {
}

void riding_CNTownModule_onEnterModuleCb(int* thisP, int a2) {
}

void riding_CNTownModule__onExitModuleCb(int* thisP, int a2) {
}

void riding_CNMainGameModule_onEnterModuleCb(int* thisP, int a2) {
}

void riding_CNMainGameModule_onExitModuleCb(int* thisP, int a2) {
}

void ridingInitDelay(int* thisP) {
}
void ridingInit(void) {
}
#endif // RIDING_EN
