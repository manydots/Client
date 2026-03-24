#include "pch.h"
#include "common.h"
#include "oldSkillWin.h"
#include "frida-gum.h"
#include "tools.h"
#define YPos        22
#define YPos2       -10
static int* npc;
static int mode;

void loadSkillData(int* thisP);

void showOldSkillWin(int* npcObj, int tpMode) {
    if ((*(int**)0x1A6F750)[0x2B] == 6) {//窗口已打开
        int* win = (*(int***)0x1A6F750)[0x1C];
        if (win[0x84] != tpMode) {//模式不一样
            closeNavigationWin_E706E0(*(int**)0x1A6F750, 0, 0x15);
        }
        else if(npcObj != npc){
            npc = npcObj;
            loadSkillData(win);
            return;
        }
        else {
            return;
        }
    }
    npc = npcObj;
    mode = tpMode;
    showNavigationWin_E7AC30(*(int**)0x1A6F750, 6, 0, 0);
    if ((*(int**)0x1A6F750)[0x2C] != 5) {
        showNavigationWin_E7AC30(*(int**)0x1A6F750, 5, 0, 1);
    }
}

//thisCall2Args2 SkillBuyWindow__OnOpen_ED9A90 = (thisCall2Args2)0xED9A90;
//char __fastcall hookSkillBuyWindow__OnOpen_ED9A90(int* thisP, int, int* npc, int a3) {
//    int ret = SkillBuyWindow__OnOpen_ED9A90(thisP, (int)npc, a3);
//    std::vector<int>* p = (std::vector<int> *)(*(int*)npc[5 + 0x51]);
//    int v = 99999;
//    GameVectorP__push_back_138A200((int*)p, (int)&v);
//    for (auto i : *p) {
//        printf("npcSkill:%x\n", i);
//    }
//    p->pop_back();
//    return ret;
//}

thisCall7Args2 OldTagItem__Constructor_11CD8E0 = (thisCall7Args2)0x11CD8E0;
thisCall2 CNRDSkillInventoryWindow__init_EDD110 = (thisCall2)0xEDD110;
int __fastcall hookCNRDSkillInventoryWindow__init_EDD110(int* thisP) {
    std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
    auto b = hook->begin();
    //CNRDSkillInventoryWindow::init_EDD110 00EDDCBA
    b++->setValue(H_DWORD, 0x00EDD258, -6);
    b++->setValue(H_BYTE, 0x00EDD2DD, *(BYTE*)0x00EDD2DD + 3);
    //this[0x40] 和 this[0x4B] 交换位置
    b++->setValue(H_DWORD, 0x00EDD370, 5); //this[0x40] 新tag
    b++->setValue(H_DWORD, 0x00EDD44D, *(DWORD*)0x00EDD44D + (YPos2 - 7));
    b++->setValue(H_DWORD, 0x00EDD4C5, *(DWORD*)0x00EDD4C5 + (YPos2 - 7));
    b++->setValue(H_DWORD, 0x00EDD5FC, *(DWORD*)0x00EDD5FC + (YPos2 - 7));
    b++->setValue(H_DWORD, 0x00EDD869, *(DWORD*)0x00EDD869 + (YPos2 - 7));
    b++->setValue(H_DWORD, 0x00EDD732, *(DWORD*)0x00EDD732 + (YPos2 - 14));
    b++->setValue(H_DWORD, 0x00EDDBB8, *(DWORD*)0x00EDDBB8 + (YPos2 - 14));
    b++->setValue(H_DWORD, 0x00EDDBDF, *(DWORD*)0x00EDDBDF + (YPos2 - 14));
    b++->setValue(H_BYTE, 0x00EDDC00, 27);//窗口高度
    b++->setValue(H_DWORD, 0x00EDD85C, 0x12C);
    b++->setValue(H_DWORD, 0x00EDD875, 0x12C);
    b++->setValue(H_DWORD, 0x00EDD889, 0x12C);
    b++->setValue(H_DWORD, 0x00EDD91B, 0x12C);
    b++->setValue(H_DWORD, 0x00EDD931, 0x12C);
    b++->setValue(H_DWORD, 0x00EDD940, 0x12C);

    thisCall2 func = (thisCall2)tools_relocation_hook(0xEDD110, 0xEDDCBA, hook);
    int ret = func(thisP);
    tools_release_func_memory((int)func);
    delete hook;
    //int ret = CNRDSkillInventoryWindow__init_EDD110(thisP);
    return ret;
}


thisCall7Args2 CNRDStackNumberSet__open_1013A40 = (thisCall7Args2)0x1013A40;
int __fastcall hookCNRDStackNumberSet__open_1013A40(int* thisP, int, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    if (0x00F131AB == (int)_ReturnAddress() && a2 == 0x0A && a3 == 0x1C) {
        showWin_E77470(*(int**)0x1A6F750, 0x124, a7, 1);
        return 0;
    }
    return CNRDStackNumberSet__open_1013A40(thisP, a2, a3, a4, a5, a6, a7, a8);
}


thisCall2Args2 CNRDSkillBuyConfirmWindow__onOpen_F2CD10 = (thisCall2Args2)0xF2CD10;
thisCall1Args2 SkillBuyWindow__getCanLearnLv_ED6910 = (thisCall1Args2)0xED6910;
char __fastcall hookCNRDSkillBuyConfirmWindow__onOpen_F2CD10(int* thisP, int, int* a2, int a3) {
    int vector[5], v;
    if (a3 > 0 && (int)a2 < 256) {//老窗口Shift学习满级技能
        int* skillObj = (int*)CNRDObject__getSkillObj_84B100(*(int**)0x1AC790C, (int)a2);
        if (!skillObj) goto exit;
        GameVector1__Constructor_458350(vector);
        GameVector1__PushBack_493770(vector, (int)&skillObj);
        v = 0;
        decrypt_11A0DE0((int*)((int)skillObj + 0x38), (int)skillObj + 0x40, (int)&v);
        v = SkillBuyWindow__getCanLearnLv_ED6910(thisP, v);
        GameVector1__PushBack_493770(vector, (int)&v);
        v = 1;
        GameVector1__PushBack_493770(vector, (int)&v);
        goto exit;
    }else if(a2 && *a2 == 0x015D5228) {//老窗口传递的参数
        GameVector1__Constructor_458350(vector);
        GameVector1__PushBack_493770(vector, (int)&a2);
        v = 0;
        decrypt_11A0DE0((int*)((int)a2 + 0x38), (int)a2 + 0x40, (int)&v);
        v = SkillBuyWindow__getCanLearnLv_ED6910(thisP, v);
        GameVector1__PushBack_493770(vector, (int)&v);
        v = 0;
        GameVector1__PushBack_493770(vector, (int)&v);
        goto exit;
    }
    return CNRDSkillBuyConfirmWindow__onOpen_F2CD10(thisP, (int)a2, a3);
exit:
    v = CNRDSkillBuyConfirmWindow__onOpen_F2CD10(thisP, (int)vector, a3);
    GameVector1__Destructor_76D310(vector);
    return v;
}

const wchar_t* __cdecl getCharacJobName_1223C10(int job, unsigned int class_1) {
    if (class_1 >= 4) return  L"通用";
    switch (job) {
    case 0:
        switch (class_1) {
        case 0:return L"波动";
        case 1:return L"剑术";
        case 2:return L"血气";
        case 3:return L"鬼神";
        }
    case 1:
    case 7:
        switch (class_1) {
        case 0:return L"体术";
        case 1:return L"念气";
        case 2:return L"狂暴";
        case 3:return L"武术";
        }
    case 2:
    case 5:
        switch (class_1) {
        case 0:return L"射术";
        case 1:return L"机械";
        case 2:return L"战术";
        case 3:return L"重火器";
        }
    case 3:
        switch (class_1) {
        case 0:return L"元素";
        case 1:return L"召唤";
        case 2:return L"战斗魔法";
        case 3:return L"魔道";
        }
    case 4:
        switch (class_1) {
        case 0:return L"启示";
        case 1:return L"神击";
        case 2:return L"驱魔";
        case 3:return L"恶魔";
        }
    case 6:
        switch (class_1) {
        case 0:return L"迅捷";
        case 1:return L"忍术";
        case 2:return L"死灵";
        case 3:return L"暗杀";
        }
    case 8:
        switch (class_1) {
        case 0:return L"元素";
        case 1:return L"冰结";
        case 2:return L"战斗";
        case 3:return L"魔道";
        }
    case 9:
    case 10:return L"外传";

    }
}


int __cdecl hookGetCharacClassName(int a1) {
    int* charcObj = *(int**)0x1AC790C;
    int job = (charcObj + 0xF02)[0];
    return (int)getCharacJobName_1223C10(job, a1 - 15019);
}

thisCall2 CNRDSkillInventoryWindow__MyOnOpen;
char __fastcall hookCNRDSkillInventoryWindow__OnOpen_EDDCC0(int* thisP) {
   int ret = CNRDSkillInventoryWindow__MyOnOpen(thisP);
    return ret;
}


thisCall1Args2 CNRDSkillInventoryWindow__MyDrawProc;
char __fastcall hookCNRDSkillInventoryWindow__DrawProc_EDC630(int* thisP, int, int a2) {
    return CNRDSkillInventoryWindow__MyDrawProc(thisP, a2);
}


thisCall2 CNRDSkillInventoryWindow__MyProc;
char __fastcall hookCNRDSkillInventoryWindow__Proc_EDC040(int* thisP) {
    return CNRDSkillInventoryWindow__MyProc(thisP);
}

thisCall2 CNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0 = (thisCall2)0xEDBCA0;
int __fastcall hookCNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0(int* thisP) {
    int currentIdx = OldTagLayout__getCurrentIdx_11DD050((int*)thisP[0x3B]);
    return 8 + currentIdx * 38;
}

cdeclCall1 CNRDSkillInventoryWindow__getSkillBelongTagIdx_EDCD80 = (cdeclCall1)0xEDCD80;
int __cdecl hookCNRDSkillInventoryWindow__getSkillBelongTagIdx_EDCD80(int* skillObj){
    if (!skillObj) return 0;
    int id;
    decrypt_11A0DE0(skillObj + 0xE, (int)(skillObj + 0x10), (int)&id);
    if (id == 197) return 4;
    int skill_class;
    decrypt_11A0DE0(skillObj + 0x38, (int)(skillObj + 0x3A), (int)&skill_class);
    return skill_class;
}

cdeclCall1 CNRDSkillInventoryWindow__getTagSkillOffset_EDBBD0 = (cdeclCall1)0xEDBBD0;
int __cdecl hookCNRDSkillInventoryWindow__getTagSkillOffset_EDBBD0(int tagIdx) {
    return 8 + tagIdx * 38;
}

thisCall1Args2 CNRDSkillInventoryWindow__getSelectGridIdx_EDBCE0 = (thisCall1Args2)0xEDBCE0;
int __fastcall hookCNRDSkillInventoryWindow__getSelectGridIdx_EDBCE0(int* thisP, int, char a2) {
    int slotOffset = hookCNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0(thisP);
    int mouseX = MousePosX, mouseY = MousePosY;
    int winX = ((int**)thisP)[1][5];
    int winY = ((int**)thisP)[1][6];
    int idx = 0;
    int x, y, w;
    while (1) {
        if (a2) {
            x = winX + 33 * (idx % 6) + 16;
            y = winY + 31 * (idx / 6) + 46 + YPos;
        }
        else {
            x = winX + 33 * (idx % 6) + 12;
            y = winY + 31 * (idx / 6) + 42 + YPos;
        }
        if (mouseX >= x) {
            w = a2 != 0 ? 28 : 37;
            if (mouseX < w + x && mouseY >= y && mouseY < y + w)
                break;
        }
        ++slotOffset;
        if (++idx >= 38) return -1;
    }
    return slotOffset;
}


BYTE isGrowTypeSkill(int* skillObj, BYTE growType, int* v) {
    for (int i = 0, grow = 0, skill_fitness_growtype_size = (skillObj[0x108] - skillObj[0x107]) / 12; i < skill_fitness_growtype_size; ++i) {
        decrypt_11A0DE0((int*)(skillObj[0x107] + 12 * i), skillObj[0x107] + 12 * i + 8, (int)&grow);
        if (grow == growType) {
            decrypt_11A0DE0(&skillObj[3 * growType + 0x4D], (int)&skillObj[3 * growType + 0x4F], (int)v);
            return 1;
        }
    }
    return 0;
}

BYTE isSecondGrowTypeSkill(int* skillObj, BYTE awakenType, BYTE growType, int* v) {
    for (int i = 0, grow = 0, skill_fitness_second_growtype_size = (skillObj[0xA9] - skillObj[0xA8]) / 12; i < skill_fitness_second_growtype_size; ++i) {
        decrypt_11A0DE0((int*)(skillObj[0xA8] + 12 * i), skillObj[0xA8] + 12 * i + 8, (int)&grow);
        if (grow == awakenType) {
            decrypt_11A0DE0(&skillObj[6 * growType + 0x80 + 3 * awakenType], (int)&skillObj[6 * growType + 0x82 + 3 * awakenType], (int)v);
            return 1;
        }
    }
    return 0;
}

void addSKill(int *thisP, int *skillObj, int skill_class, int growType, int job) {
    if (thisP[0x84] == 1) {//TP模式
        if (!*((BYTE*)skillObj + 0x54C)) return;////TP技能
        int type = -1;
        decrypt_11A0DE0(skillObj + 0x35, (int)(skillObj + 0x37), (int)&type);
        if (!type) {//主动
            GameVectorP__push_back_138A200(thisP + 0x4A, (int)&skillObj);
        }
        else if (skill_class == 4) {
            GameVectorP__push_back_138A200(thisP + 0x4A + 2 * 5, (int)&skillObj);
        }
        else {
            GameVectorP__push_back_138A200(thisP + 0x4A + 5, (int)&skillObj);
        }
    }
    else {//常规技能模式
        if (*((BYTE*)skillObj + 0x54C)) return;
        GameVectorP__push_back_138A200(thisP + 0x4A + skill_class * 5, (int)&skillObj);
    }
}

thisCall2 getCharacInfo_925000 = (thisCall2)0x925000;
thisCall2 getCharacGrowTypeBase_D12230 = (thisCall2)0xD12230;
thisCall2 OldStudySkillWin__OnOpen_ED71F0 = (thisCall2)0xED71F0;
thisCall2 GameVectorInt__Constructor_1389550 = (thisCall2)0x1389550;

void checkAndAddSkill(int* thisP, GameVector* npcSkillData, BYTE isSteel) {
    int growtype_maximum_level = 0;
    int* charcObj = *(int**)0x1AC790C;
    int job = (charcObj + 0xF02)[0];
    int growType = (charcObj + 0xF02)[3];
    int awakenType = (charcObj + 0xF02)[4];
    int skillSlot, maxLevel, currentLevel;

    if (!charcObj) return;
    skillSlot = charcObj[0x1303];
    int* skillObj;
    int size = npcSkillData->getSize();
    for (int i = 0; i < size; ++i) {
        skillObj = (int*)CNRDObject__getSkillObj_84B100(*(int**)0x1AC790C, npcSkillData->getValue(i));
        //printf("getSkill:0x%p, %d\n", skillObj, i);
        if (!skillObj) continue;

        if (!isGrowTypeSkill(skillObj, growType, &growtype_maximum_level) &&
            !isSecondGrowTypeSkill(skillObj, awakenType, growType, &growtype_maximum_level)) {
            if(!isSteel) continue;
            decrypt_11A0DE0(&skillObj[3 * growType + 0x4D], (int)&skillObj[3 * growType + 0x4F], (int)&growtype_maximum_level);
        }
            
        if (!growtype_maximum_level) continue;;
        GameVectorInt__Constructor_1389550(thisP + 0x85 + skillSlot * 5);
        int skill_class = -1;
        decrypt_11A0DE0(skillObj + 0xE, (int)(skillObj + 0x10), (int)&skill_class);
        if (skill_class != 197) decrypt_11A0DE0(skillObj + 0x38, (int)(skillObj + 0x3A), (int)&skill_class);
        else continue;
        if (skill_class < 0) continue;
        maxLevel = CNRDSkill__getMaxLv_90DC40(skillObj, growType, awakenType);//max level
        decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&currentLevel);//current level
        if (currentLevel >= maxLevel) continue;
        addSKill(thisP, skillObj, skill_class, growType, job);
    }
    
}

void loadSkillData(int *thisP) {
    BYTE isSteel = 0;
    int* info;
    if (!npc) return;
    info = (int*)getCharacInfo_925000(*(int**)0x1A6F718);
    if (!info) return;
    for (int i = 0; i < 5; ++i) {//清空常规技能列表
        GameVectorInt__Constructor_1389550(thisP + 0x4A + i * 5);
    }
    for (int i = 0; i < 2; ++i) {//清空1/2技能槽列表
        GameVectorInt__Constructor_1389550(thisP + 0x85 + i * 5);
    }
    if (*npc == 27) {
        if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 355)) 
            return ;
        isSteel = 1;
    }
    checkAndAddSkill(thisP, (GameVector*)(*(int*)npc[5 * info[5] + 0x51]), isSteel);
}

thisCall2 OldStudySkillWin__MyOnOpen;
char __fastcall hookOldStudySkillWin__OnOpen_ED71F0(int* thisP) {
    thisP[0x84] = mode;
    loadSkillData(thisP);
    int ret = OldStudySkillWin__MyOnOpen(thisP);
    if (mode) {
        OldTagLayout__setCurrentIdx_11D4C70((int*)thisP[0x3B], 0);
    }
    //int* v = (int*)(*(int*)0x1A6F750 + 0x164C);
    //GameVector1__PushBack_493770(v, (int)&thisP);
    return ret;
}

thisCall2 OldStudySkillWin__onClose = (thisCall2)0xED4C80;
char __fastcall hookOldStudySkillWin__OnClose_ED4C80(int* thisP) {
    //int* v = (int*)(*(int**)0x1A6F750 + 0x164C);
    //int end[3];
    //GameVector__end_7C4340(v, (int)end);
    //GameVector1__PopBack_C34BF0(v, (int)end);
    return OldStudySkillWin__onClose(thisP);
}

thisCall1Args2 OldStudySkillWin__MyProcDraw;
char __fastcall hookOldStudySkillWin__ProcDraw_ED5DB0(int* thisP, int, int a2) {
    return OldStudySkillWin__MyProcDraw(thisP, a2);
}

thisCall2 OldStudySkillWin__MyProc;
char __fastcall hookOldStudySkillWin__Proc_ED5950(int* thisP) {
    return OldStudySkillWin__MyProc(thisP);
}

stdCall1 prepareSkillVideoBySkillObj_504640 = (stdCall1)0x504640;
thisCall2Args2 SkillInfoWin__OnOpen_6526C0 = (thisCall2Args2)0x6526C0;
char __fastcall hookSkillInfoWin__OnOpen_6526C0(int* thisP, int, int skillObj, int a3) {
    *(BYTE*)0x0065274E = 0;
    CNVideoSystem__stop_11D4200((int *)CNVideoSystem__getInstance_11D4460());
    int ret = SkillInfoWin__OnOpen_6526C0(thisP, skillObj, a3);
    if (a3 == 2) {
        if (prepareSkillVideoBySkillObj_504640(skillObj)) {
            BasePopupWin__setWinSize_EF95A0(thisP, thisP[6], thisP[7] + 8);
        }
    }
    *(BYTE*)0x0065274E = 1;
    thisP[0xA] = InfoWinAlpha;//背景透明
    return ret;
}

thisCall1Args2 SkillInfoWin__ProcDraw_6529A0 = (thisCall1Args2)0x6529A0;
char __fastcall hookSkillInfoWin__ProcDraw_6529A0(int* thisP, int, int a2) {
    BYTE isSketchyBk = *((BYTE*)thisP + 0x1EC);
    int ret = SkillInfoWin__ProcDraw_6529A0(thisP, a2);
    BYTE isSketchy = *((BYTE*)thisP + 0x1EC);
    if (*(int *)0x19E0878 == 2 && isSketchy == 0) {
        if (isSketchyBk == 1 && prepareSkillVideoBySkillObj_504640(*(int*)0x1A4F310)) {
            BasePopupWin__setWinSize_EF95A0(thisP, thisP[6], thisP[7] + 8);
        }
        int *inst = (int *)CNVideoSystem__getInstance_11D4460();
        int y = ((int**)thisP)[3][6] + BasePopupWin__getWinHeight_EF5E90(thisP) - 105;
        CNVideoSystem__procDraw_11D4490(inst, ((int **)thisP)[3][5] + 15, y, 0x3F800000, 0x3F800000, 0);
        if (!CNVideoSystem__isPlaying_11D4160(inst)) {
            CNVideoSystem__seek_11D4230(inst, 0.0);
            if (!CNVideoSystem__isPrepared_11D4120(inst)) {
                prepareSkillVideoBySkillObj_504640(*(int*)0x1A4F310);
            }
        }
    }
    return ret;
}


thisCall1Args2 SkillInfoWin__loadModuleData_658870 = (thisCall1Args2)0x658870;
char __fastcall hookSkillInfoWin__loadModuleData_658870(int* thisP, int, int a2) {
    int ret = SkillInfoWin__loadModuleData_658870(thisP, a2);
    if (*(int*)0x19E0878 == 2 && *((BYTE*)thisP + 0x1EC) == 0) {
        if (CNVideoSystem__isPlaying_11D4160((int*)CNVideoSystem__getInstance_11D4460()))
            BasePopupWin__setWinSize_EF95A0(thisP, thisP[6], thisP[7] + 8);
    }
    return ret;
}

thisCall2 SkillInfoWin__OnClose_652640 = (thisCall2)0x652640;
char __fastcall hookSkillInfoWin__OnClose_652640(int* thisP) {
    CNVideoSystem__stop_11D4200((int*)CNVideoSystem__getInstance_11D4460());
    return SkillInfoWin__OnClose_652640(thisP);
}

char __fastcall hookBasePopupWin__setWinSize_EF95A0(int* thisP, int, int w, int h) {
    //printf("0x%08x setWinSize:[%d, %d]\n", _ReturnAddress(), w, h);
    return BasePopupWin__setWinSize_EF95A0(thisP, w, h);
}

char __fastcall CNRDSkillInventoryWindow__onLeftDrag_EDCB50(int* thisP) {
    int v = 2;
    v++;
    v = 0;
    return v;
}

void oldSkillWin_UiMgr__initCb(int* thisP) {
    thisCall2 OldStudySkillWin__init = (thisCall2)tools_relocation(0x00ED89F0, 0x00ED927D);
    std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
    hook->resize(1);
    auto b = hook->begin();
    b++->setValue(H_CALL, 0x00E73394, (int)OldStudySkillWin__init);
    thisCall1Args2  OldStudySkillWin__Constructor = (thisCall1Args2)tools_relocation_hook(0x00E732F0, 0x00E733AD, hook);

    int* win = (int *)newUiComponent_11B0380(0x240);
    OldStudySkillWin__Constructor(win, (int)thisP);
    thisP[0x1C] = (int)win;
    int* typeInfo = (int*)malloc(sizeof(void*) * 28);
    if (typeInfo == NULL) {
        printf("oldSkillWin_UiMgr__initCb malloc vtable memory error!\n");
        return ;
    }
    memcpy(typeInfo, (void*)0x01812AF0, sizeof(void*) * 28);

    OldStudySkillWin__MyProcDraw = (thisCall1Args2)tools_relocation(0x00ED5DB0, 0x00ED674D);
    typeInfo[1] = (int)hookOldStudySkillWin__ProcDraw_ED5DB0;// procDraw
    OldStudySkillWin__MyProc = (thisCall2)tools_relocation(0x00ED5950, 0x00ED5DAA);
    typeInfo[14] = (int)hookOldStudySkillWin__Proc_ED5950;// proc
    OldStudySkillWin__MyOnOpen = (thisCall2)tools_relocation(0x00ED71F0, 0x00ED7627);
    typeInfo[16] = (int)hookOldStudySkillWin__OnOpen_ED71F0;//onOpen
    //typeInfo[17] = (int)hookOldStudySkillWin__OnClose_ED4C80;//onOpen
    
    *win = (int)&typeInfo[1];
    //gum_interceptor_replace_fast(v, (gpointer)0xED71F0, (gpointer)hookOldStudySkillWin__OnOpen_ED71F0, (gpointer*)&OldStudySkillWin__OnOpen_ED71F0);
    //gum_interceptor_replace_fast(v, (gpointer)0xED5DB0, (gpointer)hookOldStudySkillWin__ProcDraw_ED5DB0, (gpointer*)&OldStudySkillWin__ProcDraw_ED5DB0);
    //gum_interceptor_replace_fast(v, (gpointer)0xED5950, (gpointer)hookOldStudySkillWin__Proc_ED5950, (gpointer*)&OldStudySkillWin__Proc_ED5950);

    tools_release_func_memory((int)OldStudySkillWin__Constructor);
    tools_release_func_memory((int)OldStudySkillWin__init);
    delete hook;

}

thisCall1Args2 setCNRDSkillSlot_851310 = (thisCall1Args2)0x851310;
int __fastcall hookSetCNRDSkillSlot_851310(int* thisP, int, int skillSlot) {
     int ret = setCNRDSkillSlot_851310(thisP, skillSlot);
     if ((*(int**)0x1A6F750)[0x2B] == 6)// 学习窗口打开中
        loadSkillData((*(int***)0x1A6F750)[0x1C]);
     return ret;
}

thisCall2 sub_851500;
int __fastcall hookSub_851500(int* thisP) {
    int ret = sub_851500(thisP);
    if ((*(int**)0x1A6F750)[0x2B] == 6)// 学习窗口打开中
        loadSkillData((*(int***)0x1A6F750)[0x1C]);
    return ret;
}

cdeclCall4 sub_11B9960 = (cdeclCall4)0x11B9960;
cdeclCall4 CNRDNpc__drawQuestIcon_7F2290 = (cdeclCall4)0x7F2290;
int __cdecl hookCNRDNpc__drawQuestIcon_7F2290(int x, int y, int type, int a4) {
    int v;
    __asm mov v, esi;
    if (type != 0x10) return CNRDNpc__drawQuestIcon_7F2290(x, y, type, a4);
    float v2 = *(float*)0x01562250;
    int npcId = ((int *)v)[0x84];
    switch (npcId) {
        case 27: if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 355)) return 1;
        case 1:
        case 2:
        case 6:
        case 7:
        case 12:
        case 17:
        case 45:
        case 64:
            if (!*(int**)0x1A83994) return 0;
            x -= 0x1E;
            y -= 0x1E;
            v = 0x00FFFFFF | (sub_11B9960(0xFF, a4?0:130, TimeGetTime(), 400) << 0x18);
            ((cdeclCall2)0x11B3460)(2, 0);
            drawImgByXY2_11B41E0(*(int**)0x1B5582C, x, y, getImageByPos_11B4BD0(*(int **)0x1A83994, 10), 1.0f, 1.0f, 0.0f, v, v2, v2);
            ((cdeclCall)0x11B3570)();
            drawImgByXY2_11B41E0(*(int**)0x1B5582C, x, y, getImageByPos_11B4BD0(*(int**)0x1A83994, 11), 1.0f, 1.0f, 0.0f, a4?v:0xFFFFFFFF, v2, v2);
            break;
    }
    return 0;
}

thisCall2 sub_1112B20 = (thisCall2)0x1112B20;
int __fastcall drawMouseCursorIconImp(int* npc, int pos) {
    if(!npc) return pos;
    else if (pos ) {//&& pos == 131
        int* user = (int*)getCNModule_706410();
        int* obj = (int *)sub_1112B20((int*)user[0x2B]);
        if (!obj || obj[0x86] != 0x10)
            return pos;
    }
    switch (npc[0]) {
    case 27: if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 355)) return 1;
    case 1:
    case 2:
    case 6:
    case 7:
    case 12:
    case 17:
    case 45:
    case 64:
        return 135;
    }
    return pos;
}

void Naked hookDrawMouseCursorIcon() {
    //01008BFB
    __asm {
        mov edx, 0x76D310
        call edx
        mov ecx, ebx
        mov edx, esi
        call drawMouseCursorIconImp
        mov esi, eax
        mov ebx, 0x01008C00
        jmp ebx
    }
}

int __fastcall clickMouseCursorIconImp(int* npcObj, int type) {
    if (type == 0x10) {
        switch (npcObj[0x84]) {
        case 27: if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 355)) return 1;
        case 1:
        case 2:
        case 6: 
        case 7:
        case 12:
        case 17:
        case 45:
        case 64:
            showOldSkillWin((int*)getNpcObjByIdx_90C950(npcObj[0x84]), 0);
            return 0;
        }
    }
    return 1;
}

void Naked hookClickMouseCursorIcon() {
    //007F7623
    __asm {
        test eax, eax
        jz goExit
        mov ecx, esi
        mov edx, eax
        call clickMouseCursorIconImp
        test eax, eax
        jz goRet
        mov ecx, 0x7F76BF
        jmp ecx
        goRet:
        mov ecx, 0x7F76D2
        jmp ecx
        goExit:
        mov eax, 0x007F762B
        jmp eax
    }
}

thisCall1Args2 CNRDSkillMgr__getCNRDSkillObj_91F7B0 = (thisCall1Args2)0x91F7B0;
int __fastcall fixGuildInfoWinSkill(int* thisP, int, int slot) {
    int idx = slot - 138;
    if (idx < 2) {
        return CNRDSkillMgr__getCNRDSkillObj_91F7B0(thisP, idx + 196);
    }
    return 0;
}

void oldSkillWinInit() {
    writeCallCode((void*)0x007F34AD, hookCNRDNpc__drawQuestIcon_7F2290);
    writeCallCode((void*)0x00FA2455, fixGuildInfoWinSkill);
    writeJmpCode((void*)0x01008BFB, hookDrawMouseCursorIcon);
    writeJmpCode((void*)0x007F7623, hookClickMouseCursorIcon);

    std::vector<RelocatHookInfo> *hook = new std::vector<RelocatHookInfo>(32);
#define GetCanLearnLvB 0xED6910
#define GetCanLearnLvE 0xED6ACF
    //hook->resize(4);
    auto b = hook->begin();
    b++->setValue(H_WORD, GetCanLearnLvB + 0xA3, 0x03FA);
    b++->setValue(H_DWORD, GetCanLearnLvB + 0xA5, 0x90909090);
    b++->setValue(H_WORD, GetCanLearnLvB + 0x149, 0x03F8);
    b++->setValue(H_DWORD, GetCanLearnLvB + 0x14B, 0x90909090);
    SkillBuyWindow__getCanLearnLv_ED6910 = (thisCall1Args2)tools_relocation_hook(GetCanLearnLvB, GetCanLearnLvE, hook);
    //printf("relocate SkillBuyWindow__getCanLearnLv_ED6910:0x%p\n", SkillBuyWindow__getCanLearnLv_ED6910);
    //*(WORD*)(p + 0xA3) = 0x03FA;
    //*(DWORD*)(p + 0xA5) = 0x90909090;

    //*(WORD*)(p + 0x149) = 0x03F8;
    //*(DWORD*)(p + 0x14B) = 0x90909090;

    *(DWORD*)0x01812BAC = (int)CNRDSkillInventoryWindow__onLeftDrag_EDCB50;
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x1013A40, (gpointer)hookCNRDStackNumberSet__open_1013A40, (gpointer*)&CNRDStackNumberSet__open_1013A40);
    gum_interceptor_replace_fast(v, (gpointer)0xF2CD10, (gpointer)hookCNRDSkillBuyConfirmWindow__onOpen_F2CD10, (gpointer*)&CNRDSkillBuyConfirmWindow__onOpen_F2CD10);
    //gum_interceptor_replace_fast(v, (gpointer)0xEDD110, (gpointer)hookCNRDSkillInventoryWindow__init_EDD110, (gpointer*)&CNRDSkillInventoryWindow__init_EDD110);
    writeCallCode((void*)0x00E84B63, hookCNRDSkillInventoryWindow__init_EDD110);

    //gum_interceptor_replace_fast(v, (gpointer)0xEDDCC0, (gpointer)hookCNRDSkillInventoryWindow__OnOpen_EDDCC0, (gpointer*)&CNRDSkillInventoryWindow__OnOpen_EDDCC0);
    hook->resize(6);
    b = hook->begin();
    ////CNRDSkillInventoryWindow::OnOpen_EDDCC0 00EDE02A
    
    b++->setValue(H_BYTE, 0x00EDDF99, 0xEB);
    b++->setValue(H_BYTE, 0x00EDDE61, 5);
    b++->setValue(H_DWORD, 0x00EDDE90, 5);
    b++->setValue(H_BYTE, 0x00EDDE83, *(BYTE*)0x00EDDE83 + 24);
    b++->setValue(H_CALL, 0x00EDDD4F, (int)hookGetCharacClassName);
    b++->setValue(H_CALL, 0x00EDDDD8, (int)hookGetCharacClassName);
    CNRDSkillInventoryWindow__MyOnOpen = (thisCall2)tools_relocation_hook(0xEDDCC0, 0xEDE02A, hook);
    *(DWORD*)0x01812BA0 = (int)hookCNRDSkillInventoryWindow__OnOpen_EDDCC0;

    hook->resize(10);
    b = hook->begin();
    //procDraw sub_EDB6C0 EDBBC3
    b++->setValue(H_DWORD, 0x00EDB84E, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBAA3, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBAB6, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBAC9, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBAD4, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBAEB, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBB01, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBB0C, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBB8F, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBBA7, 0x12C);
    thisCall2 my_EDB6C0 = (thisCall2)tools_relocation_hook(0xEDB6C0, 0xEDBBC3, hook);

    //*(WORD*)0x00EDC8F9 = 0xF189;
    //writeCallCode((void*)0x00EDC8FB, hookCNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0);
    //*(WORD*)0x00EDC900 = 0x35EB;

    hook->resize(15);
    b = hook->begin();
    //CNRDSkillInventoryWindow::DrawProc_EDC630 EDC9A2
    b++->setValue(H_BYTE, 0x00EDC710, 4);
    b++->setValue(H_BYTE, 0x00EDC6D9, *(BYTE*)0x00EDC6D9 + YPos);
    b++->setValue(H_BYTE, 0x00EDC736, *(BYTE*)0x00EDC736 + YPos);
    b++->setValue(H_BYTE, 0x00EDC78E, *(BYTE*)0x00EDC78E + YPos);
    b++->setValue(H_BYTE, 0x00EDC811, *(BYTE*)0x00EDC811 + YPos);
    b++->setValue(H_BYTE, 0x00EDC95E, *(BYTE*)0x00EDC95E + YPos);
    b++->setValue(H_WORD, 0x00EDC694, 0x28EB);
    b++->setValue(H_DWORD, 0x00EDC865, *(DWORD*)0x00EDC865 + YPos2);
    b++->setValue(H_DWORD, 0x00EDC893, *(DWORD*)0x00EDC893 + YPos2);
    b++->setValue(H_DWORD, 0x00EDC8BD, *(DWORD*)0x00EDC8BD + YPos2);
    b++->setValue(H_BYTE, 0x00EDC845, 38);
    b++->setValue(H_CALL, 0x00EDC995, (int)my_EDB6C0);
    b++->setValue(H_WORD, 0x00EDC8F9, (int)0xF189);
    b++->setValue(H_WORD, 0x00EDC900, (int)0x35EB);
    b++->setValue(H_CALL, 0x00EDC8FB, (int)hookCNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0);
    CNRDSkillInventoryWindow__MyDrawProc = (thisCall1Args2)tools_relocation_hook(0xEDC630, 0xEDC9A2, hook);
    *(DWORD*)0x01812B64 = (int)hookCNRDSkillInventoryWindow__DrawProc_EDC630;

    hook->resize(3);
    b = hook->begin();
    //Proc_EDC040 ->sub_EDBC20 00EDBC97
    b++->setValue(H_DWORD, 0x00EDBC88, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBC77, 0x12C);
    b++->setValue(H_DWORD, 0x00EDBC62, 0x12C);
    thisCall2 my_EDBC20 = (thisCall2)tools_relocation_hook(0xEDBC20, 0xEDBC97, hook);


    *(DWORD*)0x00E84B24 = 0x134;//拓展空间
    hook->resize(3);
    b = hook->begin();
    //Proc_EDC040 -> CNRDSkillInventoryWindow::checkCooltimeNotifyMouseTask_EDBF50
    b++->setValue(H_DWORD, 0x00EDBF80, 0x130);
    b++->setValue(H_DWORD, 0x00EDC020, 0x130);
    b++->setValue(H_DWORD, 0x00EDC02E, 0x130);
    thisCall2 CNRDSkillInventoryWindow__checkCooltimeNotifyMouseTask = (thisCall2)tools_relocation_hook(0xEDBF50, 0x00EDC03A, hook);

    hook->resize(4);
    b = hook->begin();
    //CNRDSkillInventoryWindow::Proc_EDC040 EDC629
    b++->setValue(H_BYTE, 0x00EDC181, 5);
    b++->setValue(H_DWORD, 0x00EDC2B5, 0x12C);
    b++->setValue(H_CALL, 0x00EDC26A, (int)my_EDBC20);
    b++->setValue(H_CALL, 0x00EDC1BB, (int)CNRDSkillInventoryWindow__checkCooltimeNotifyMouseTask);
    CNRDSkillInventoryWindow__MyProc = (thisCall2)tools_relocation_hook(0xEDC040, 0xEDC629, hook);
    *(DWORD*)0x01812B98 = (int)hookCNRDSkillInventoryWindow__Proc_EDC040;

    //CNRDSkillInventoryWindow::onDragEvent_EDCE00
    *(BYTE*)0x00EDD01D = 38;

    gum_interceptor_replace_fast(v, (gpointer)0xEDBCE0, (gpointer)hookCNRDSkillInventoryWindow__getSelectGridIdx_EDBCE0, (gpointer*)&CNRDSkillInventoryWindow__getSelectGridIdx_EDBCE0);
    gum_interceptor_replace_fast(v, (gpointer)0xEDBCA0, (gpointer)hookCNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0, (gpointer*)&CNRDSkillInventoryWindow__getGridIdxOffset_EDBCA0);
    gum_interceptor_replace_fast(v, (gpointer)0xEDCD80, (gpointer)hookCNRDSkillInventoryWindow__getSkillBelongTagIdx_EDCD80, (gpointer*)&CNRDSkillInventoryWindow__getSkillBelongTagIdx_EDCD80);
    gum_interceptor_replace_fast(v, (gpointer)0xEDBBD0, (gpointer)hookCNRDSkillInventoryWindow__getTagSkillOffset_EDBBD0, (gpointer*)&CNRDSkillInventoryWindow__getTagSkillOffset_EDBBD0);
    gum_interceptor_replace_fast(v, (gpointer)0x1223C10, (gpointer)getCharacJobName_1223C10, NULL);
    
    gum_interceptor_replace_fast(v, (gpointer)0x658870, (gpointer)hookSkillInfoWin__loadModuleData_658870, (gpointer*)&SkillInfoWin__loadModuleData_658870);
    gum_interceptor_replace_fast(v, (gpointer)0x6526C0, (gpointer)hookSkillInfoWin__OnOpen_6526C0, (gpointer*)&SkillInfoWin__OnOpen_6526C0);
    gum_interceptor_replace_fast(v, (gpointer)0x6529A0, (gpointer)hookSkillInfoWin__ProcDraw_6529A0, (gpointer*)&SkillInfoWin__ProcDraw_6529A0);
    gum_interceptor_replace_fast(v, (gpointer)0x652640, (gpointer)hookSkillInfoWin__OnClose_652640, (gpointer*)&SkillInfoWin__OnClose_652640);


    gum_interceptor_replace_fast(v, (gpointer)0x851310, (gpointer)hookSetCNRDSkillSlot_851310, (gpointer*)&setCNRDSkillSlot_851310);
    gum_interceptor_replace_fast(v, (gpointer)0x851500, (gpointer)hookSub_851500, (gpointer*)&sub_851500);


    //hook->resize(4);
    //b = hook->begin();
    //00EDD110 00EDDCBA
    //*(DWORD*)0x00EDD258 = -6;
    //*(BYTE*)0x00EDD2DD += 3;
  
    //this[0x40] 和 this[0x4B] 交换位置

    //*(DWORD*)0x00EDD370 = 5;//this[0x40] 新tag
    //*(BYTE*)0x00EDDE61 = 5;
    //*(DWORD*)0x00EDDE90 = 5;

    //*(BYTE*)0x00EDDE83 += 24;
    //*(DWORD*)0x00EDD44D += YPos2 - 7;
    //*(DWORD*)0x00EDD4C5 += YPos2 - 7;
    //*(DWORD*)0x00EDD5FC += YPos2 - 7;
    //*(DWORD*)0x00EDD869 += YPos2 - 7;
    //*(DWORD*)0x00EDD732 += YPos2 - 14;
    //*(DWORD*)0x00EDDBB8 += YPos2 - 14;
    //*(DWORD*)0x00EDDBDF += YPos2 - 14;

    //*(BYTE*)0x00EDDC00 = 27;//窗口高度


    //*(DWORD*)0x00EDD85C = 0x12C;
    //*(DWORD*)0x00EDD875 = 0x12C;
    //*(DWORD*)0x00EDD889 = 0x12C;
    //*(DWORD*)0x00EDD91B = 0x12C;
    //*(DWORD*)0x00EDD931 = 0x12C;
    //*(DWORD*)0x00EDD940 = 0x12C;


    //*(BYTE*)0x00EDC6D9 += YPos;
    //*(BYTE*)0x00EDC736 += YPos;
    //*(BYTE*)0x00EDC78E += YPos;
    //*(BYTE*)0x00EDC811 += YPos;
    //*(BYTE*)0x00EDC95E += YPos;


    //*(WORD*)0x00EDC694 = 0x28EB;


    //*(DWORD*)0x00EDC865 += YPos2;
    //*(DWORD*)0x00EDC893 += YPos2;
    //*(DWORD*)0x00EDC8BD += YPos2;


    //proc
    //*(BYTE*)0x00EDC181 = 5;
    //*(BYTE*)0x00EDC710 = 4;
    //*(DWORD*)0x00EDC2B5 = 0x12C;
    //*(DWORD*)0x00EDBC88 = 0x12C;
    //*(DWORD*)0x00EDBC77 = 0x12C;
    //*(DWORD*)0x00EDBC62 = 0x12C;

    //procDraw
    //*(DWORD*)0x00EDB84E = 0x12C;
    //*(DWORD*)0x00EDBAA3 = 0x12C;
    //*(DWORD*)0x00EDBAB6 = 0x12C;
    //*(DWORD*)0x00EDBAC9 = 0x12C;
    //*(DWORD*)0x00EDBAD4 = 0x12C;
    //*(DWORD*)0x00EDBAEB = 0x12C;
    //*(DWORD*)0x00EDBB01 = 0x12C;
    //*(DWORD*)0x00EDBB0C = 0x12C;
    //*(DWORD*)0x00EDBB8F = 0x12C;
    //*(DWORD*)0x00EDBBA7 = 0x12C;
   
    //*(BYTE*)0x00EDC845 = 38;
    


    //CNRDBaseInterface::onLeftButtonUp_4C2D60
    *(BYTE*)0x004C311D = 38;


    
    //sendMoveSkillPkg_920D90
    *(BYTE*)0x00920DD3 = 8;
    *(BYTE*)0x00920E19 = 8;

    *(BYTE*)0x00ED8B93 = 48; //技能学习窗口y
    
    //writeWordCode((void*)0x00920E11, 0x9090);
    //writeDWordCode((void*)0x00920E13, 0x90909090);
    //writeWordCode((void*)0x00920E62, 0x9090);
    //writeDWordCode((void*)0x00920E64, 0x90909090);
    //writeDWordCode((void*)0x006574A5, 0x0000C9E9);

    //技能信息窗口位置
    *(DWORD*)0x00598CE5 = 640;
    *(DWORD*)0x00598CF8 = 640;
    *(DWORD*)0x00598D17 = 480;

    
    //*(DWORD*)0x00653FE6 = 0x33333334;
    //*(BYTE*)0x007D75C9 = 0x89; *(BYTE*)0x007D75CC = 3;
    //*(BYTE*)0x00654021 = 0xBF; *(BYTE*)0x00654028 = 3;

    //修复工会技能
    writeCallCode((void*)0x00FA2455, fixGuildInfoWinSkill);
    *(DWORD*)0x00920E6A = -196;//sendMoveSkillPkg_920D90
    *(BYTE*)0x00920E70 = 1;//sendMoveSkillPkg_920D90
    *(DWORD*)0x0071D416 = 196;
    for (int i = 0; i < 12; ++i) {
        ((DWORD*)0x19E2BBC)[i] = i + 196;
    }
    delete hook;
}
