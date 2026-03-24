// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "common.h"
#include <winuser.h>
#include <tchar.h>

#include <vector>
#include <utility>

#include <fstream>
#include <thread>
#include <string>
#include "hellPartyInfoWin.h"
#include "questDetailWin.h"
#include "epicQuestListSubWin.h"
#include "currentQuestListWin.h"
#include "frida-gum.h"
#include "tools.h"
#include "70.h"
#include "oldSkillWin.h"
#include "oldQuestWin.h"
#include "cancel.h"
#include "highLevelEvil.h"
#include "goldSkill.h"
#include "riding.h"
#include "npcFavor.h"
#include "oldCharacInfoWin.h"
#include "itemInventoryWin.h"
#include "equimentJewel.h"
#include "soundOptimize.h"
#include <winsock2.h>

#include "priest.h"

VOID __declspec(dllexport) dllLoader()
{

}


int currentDungeonId;

#ifdef EN_ICON_ANIM
const static wchar_t* AnimMythologyPath = L"ui/equimiconanim/mythology.ani";
const static wchar_t* AnimArtifactPurplePath = L"ui/equimiconanim/artifact_purple.ani";
const static wchar_t* AnimArtifactRedPath = L"ui/equimiconanim/artifact_red.ani";
const static wchar_t* AnimBakalPath = L"ui/equimiconanim/bakal.ani";
const static wchar_t* AnimBakalraidPath = L"ui/equimiconanim/bakalraid.ani";
const static wchar_t* AnimBakalraidHonorPath = L"ui/equimiconanim/bakalraid_honor.ani";
const static wchar_t* AnimDimensioncloisterPath = L"ui/equimiconanim/dimensioncloister.ani";
const static wchar_t* AnimEmblemPath = L"ui/equimiconanim/emblem.ani";
const static wchar_t* AnimFiendwarPath = L"ui/equimiconanim/fiendwar.ani";
const static wchar_t* AnimIspinsPath = L"ui/equimiconanim/ispins.ani";
const static wchar_t* AnimPreyWeaponPath = L"ui/equimiconanim/prey_weapon.ani";
const static wchar_t* AnimDuskyisland1Path = L"ui/equimiconanim/duskyisland1.ani";
const static wchar_t* AnimDuskyisland2Path = L"ui/equimiconanim/duskyisland2.ani";
const static wchar_t* AnimOption2Path = L"ui/equimiconanim/option2.ani";
const static wchar_t* AnimOption3Path = L"ui/equimiconanim/option3.ani";
const static wchar_t* AnimOption3HonorPath = L"ui/equimiconanim/option3_honor.ani";
const static wchar_t* AnimOption4Path = L"ui/equimiconanim/option4.ani";
const static wchar_t* AnimOption4HonorPath = L"ui/equimiconanim/option4_honor.ani";

GameAnimCombo G_IconAnim[] = {
    GameAnimCombo(new GameAnim(AnimMythologyPath)),
    GameAnimCombo(new GameAnim(AnimArtifactPurplePath)),
    GameAnimCombo(new GameAnim(AnimArtifactRedPath)),
    GameAnimCombo(new GameAnim(AnimBakalPath)),
    GameAnimCombo(new GameAnim(AnimBakalraidPath)),
    GameAnimCombo(GameAnimCombo::PlaySerial, {new GameAnim(AnimBakalraidPath), new GameAnim(AnimBakalraidHonorPath)}),
    GameAnimCombo(new GameAnim(AnimDimensioncloisterPath)),
    GameAnimCombo(new GameAnim(AnimEmblemPath)),
    GameAnimCombo(new GameAnim(AnimFiendwarPath)),
    GameAnimCombo(new GameAnim(AnimIspinsPath)),
    GameAnimCombo(new GameAnim(AnimPreyWeaponPath)),
    GameAnimCombo(new GameAnim(AnimDuskyisland1Path)),
    GameAnimCombo(new GameAnim(AnimDuskyisland2Path)),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimOption2Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimOption3Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimOption3HonorPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimOption4Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimOption4HonorPath)}),

    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimOption2Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimOption3Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimOption3HonorPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimOption4Path)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimOption4HonorPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimBakalraidPath), new GameAnim(AnimOption4HonorPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDimensioncloisterPath), new GameAnim(AnimOption2Path)}),

    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimBakalPath), new GameAnim(AnimPreyWeaponPath)}),

    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDimensioncloisterPath), new GameAnim(AnimMythologyPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimIspinsPath), new GameAnim(AnimMythologyPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimBakalraidPath), new GameAnim(AnimMythologyPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland1Path), new GameAnim(AnimMythologyPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimDuskyisland2Path), new GameAnim(AnimMythologyPath)}),
    GameAnimCombo(GameAnimCombo::PlayParallel, {new GameAnim(AnimBakalPath), new GameAnim(AnimMythologyPath)}),
};

void initIconAnim() {
    IconMap.emplace(27147, &G_IconAnim[Mythology]);
    IconMap.emplace(27598, &G_IconAnim[Mythology]);
    IconMap.emplace(28313, &G_IconAnim[ArtifactPurple]);
    IconMap.emplace(28040, &G_IconAnim[ArtifactRed]);
    IconMap.emplace(28314, &G_IconAnim[Bakal]);
    IconMap.emplace(27747, &G_IconAnim[Bakalraid]);
    IconMap.emplace(28041, &G_IconAnim[BakalraidHonor]);
    IconMap.emplace(27599, &G_IconAnim[Dimensioncloister]);
    IconMap.emplace(27748, &G_IconAnim[Emblem]);
    IconMap.emplace(27148, &G_IconAnim[Fiendwar]);
    IconMap.emplace(27347, &G_IconAnim[Ispins]);
    IconMap.emplace(27750, &G_IconAnim[PreyWeapon]);
    IconMap.emplace(27098, &G_IconAnim[PreyWeapon]);
    IconMap.emplace(27712, &G_IconAnim[Mythology]);
    IconMap.emplace(28268, &G_IconAnim[BakalPreyWeapon]);


    IconMap.emplace(100270014, &G_IconAnim[Duskyisland1Option3]);
    IconMap.emplace(100220014, &G_IconAnim[Duskyisland1Option3]);
    IconMap.emplace(100170015, &G_IconAnim[Duskyisland1Option3]);
    IconMap.emplace(100070017, &G_IconAnim[Duskyisland1Option3]);
    IconMap.emplace(100120015, &G_IconAnim[Duskyisland1Option3]);

    IconMap.emplace(100070004, &G_IconAnim[Duskyisland1Option3Honor]);
    IconMap.emplace(100170004, &G_IconAnim[Duskyisland1Option3Honor]);
    IconMap.emplace(100120004, &G_IconAnim[Duskyisland1Option3Honor]);
    IconMap.emplace(100270004, &G_IconAnim[Duskyisland1Option3Honor]);
    IconMap.emplace(100220004, &G_IconAnim[Duskyisland1Option3Honor]);

    IconMap.emplace(100300002, &G_IconAnim[Duskyisland2Option4Honor]);
    IconMap.emplace(100310002, &G_IconAnim[Duskyisland2Option4Honor]);
    IconMap.emplace(100320004, &G_IconAnim[Duskyisland2Option4Honor]);

    IconMap.emplace(22180, &G_IconAnim[BakalraidOption4Honor]);
    IconMap.emplace(20188, &G_IconAnim[BakalraidOption4Honor]);
    IconMap.emplace(24209, &G_IconAnim[BakalraidOption4Honor]);

    IconMap.emplace(22109, &G_IconAnim[DimensioncloisterOption2]);
    IconMap.emplace(24115, &G_IconAnim[DimensioncloisterOption2]);
    IconMap.emplace(20114, &G_IconAnim[DimensioncloisterOption2]);

    IconMap.emplace(0xffffffff, &G_IconAnim[Emblem]);

    IconMap.emplace(609590021, &G_IconAnim[BakalraidMythology]);
    IconMap.emplace(609590022, &G_IconAnim[DimensioncloisterMythology]);
    IconMap.emplace(609590023, &G_IconAnim[IspinsMythology]);
    IconMap.emplace(609590024, &G_IconAnim[BakalMythology]);
    IconMap.emplace(609590025, &G_IconAnim[Duskyisland1Mythology]);
    IconMap.emplace(609590026, &G_IconAnim[Duskyisland2Mythology]);

}

enum GameAnimComboType {
    Mythology,
    ArtifactPurple,
    ArtifactRed,
    Bakal,
    Bakalraid,
    BakalraidHonor,
    Dimensioncloister,
    Emblem,
    Fiendwar,
    Ispins,
    PreyWeapon,
    Duskyisland1,
    Duskyisland2,
    Duskyisland1Option2,
    Duskyisland1Option3,
    Duskyisland1Option3Honor,
    Duskyisland1Option4,
    Duskyisland1Option4Honor,
    Duskyisland2Option2,
    Duskyisland2Option3,
    Duskyisland2Option3Honor,
    Duskyisland2Option4,
    Duskyisland2Option4Honor,
    BakalraidOption4Honor,
    DimensioncloisterOption2,
    BakalPreyWeapon,
    DimensioncloisterMythology,
    IspinsMythology,
    BakalraidMythology,
    Duskyisland1Mythology,
    Duskyisland2Mythology,
    BakalMythology,
    GameAnimComboEnd
};
std::unordered_map<int, GameAnimCombo*> IconMap;
void showIconAnim(int* thisP, int x, int y) {
    if (thisP && !*(BYTE*)(thisP + 0x8F) && !*((UINT8*)thisP + 0x1B0) && !*((UINT8*)thisP + 0x23E)) {
        int id = thisP[7];
        if (IconMap.count(id)) {
            IconMap[id]->draw(x, y);
        }
        thisCall isOpenSlot = (thisCall)Vtable(thisP, 0x124);
        if ((UINT32)isOpenSlot == 0x785010 && isOpenSlot(thisP, 0)) {
            IconMap[0xffffffff]->draw(x, y);
        }
    }
}
#else
void showIconAnim(int* thisP, int x, int y) {}
#endif

//UINT32 vobj = 0;
//BOOL frist = true;
//WCHAR shrBuff[64];
//const WCHAR cjStr[] = L"      超界·晶体";
//thisCall5Args DrawText_F5F080 = (thisCall5Args)0xF5F080;
//void __fastcall hookDrawText_F5F080(int *thisP, int, int line, int wstr, int align, int color, int a5) {
//    UINT32 retAddr = (UINT32)_ReturnAddress();
//    if (retAddr == 0x00F5E6EB) {
//        if (wstr != NULL) {
//            if (line == 1 && NULL == wcsstr((WCHAR*)wstr, L"      ")) {
//                wsprintfW(shrBuff, L"      %s", (WCHAR*)wstr);
//                wstr = (int)shrBuff;
//            }
//            if (line < 3 && NULL != wcsstr((WCHAR*)wstr, L"       [")) {
//                wstr += 2;
//            }
//        }
//        
//        if (frist) {
//            frist = false;
//            if (vobj == thisP[94]) goto exit;
//            vobj = thisP[94];
//            switch (((UINT32*)vobj)[7]){
//            case 3037:DrawText_F5F080(thisP, 0, wstr, (int)cjStr, align, 0xff0000ff, a5); break;
//            default:goto exit;
//            } 
//            __asm inc[ebx];
//            ++line;
//            goto exit;
//        }
//        else {
//            frist = true;
//        }
//        goto exit;
//    }
//    else {
//        vobj = 0;
//        frist = true;
//    exit:
//        //AlignCenter_1AF4340 AlignRight_1AF4324 AlignLeft_1AF4308
//        DrawText_F5F080(thisP, 0, line, wstr, align, color, a5);
//    }
//}

//char __cdecl hookCheckGmCmd_95B0A0(wchar_t* str) {
//    if (str && wcsstr(str, L"//weapon") == str) {
//        int id = -1, soundType = -1;
//        if (swscanf(str, L"//weapon %d %d", &id, &soundType) && id != -1) {
//            setWeaponIllusion(id, soundType);
//            return 0;
//        }
//    }
//    return checkGmCmd_95B0A0((int)str);
//}



int __fastcall hookDecrypt_11A0DE0(int* thisP, int edx, int a2, int a3) {
    int ret = decrypt_11A0DE0(thisP, a2, a3);
    int retAddr = (int)_ReturnAddress();
    if (0x28A3E18 == retAddr && *(int*)a3 > MAX_LV) {
        *(int*)a3 = MAX_LV;
    }

    //if (*(int*)a3 == 63 || *(int*)a3 == 72) {
    //    DPRINTF("0x%08x Decrypt:[0x%08x, 0x%08x, %d] \n", retAddr, *thisP, *(int*)a2, *(int*)a3);
    //}
    return ret;
}

cdeclCall1 sq_getJob_5AEE70 = (cdeclCall1)0x5AEE70;
thisCall2Args2 showCommandWin_1011770 = (thisCall2Args2)0x1011770;
thisCall2 getNpcId_7F8CA0 = (thisCall2)0x007F8CA0;
void __fastcall addOldSkillCommandImp(int* thisP, int* npcObj) {
    int npcIdAddr = *(int*)getNpcId_7F8CA0(npcObj);
    int* charcObj = *(int**)0x1AC790C;
    int job = (charcObj + 0xF02)[0];
    DPRINTF("npcId:%d job:%d\n", npcIdAddr, job);
    int v2, v3;
    switch (npcIdAddr) {
    case 27: if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 355)) return;
    case 1:
    case 2: 
    case 6: 
    case 7: 
    case 12:
    case 17:
    case 45:
    case 64:
        v3 = 0x27;
        v2 = 0x15 * (((thisP[0x68] - thisP[0x67]) >> 2) + 1);
        setUiComponentPos_11BEAD0((int*)thisP[0x42], GetXPos_42FF60((int*)thisP[0x1A]), v2 + GetYPos_11BE300((int*)thisP[0x1A]), 1);
        setUiComponentVisable_11BE610((int*)thisP[0x42], 1);
        GameVector1__PushBack_493770(thisP + 0x66, (int)&v3);
    }
    //int* villageAttackedReward = ((int***)getCNModule_706410())[0x2B][0x53];
    //if (RBYTE(villageAttackedReward, 0xB4)) {//攻城失败
    //    setUiComponentEnable_11BE350((int*)thisP[0x41], 0);// 物品店
    //    //setUiComponentEnable_11BE350((int*)thisP[0x42], 0);// 物品店
    //    //setUiComponentEnable_11BE350((int*)thisP[0x44], 0);// 解除虚弱
    //    setUiComponentEnable_11BE350((int*)thisP[0x46], 0);// 创建公会
    //    setUiComponentEnable_11BE350((int*)thisP[0x47], 0);// 申请公会升级
    //    setUiComponentEnable_11BE350((int*)thisP[0x48], 0);// 强化装备
    //    setUiComponentEnable_11BE350((int*)thisP[0x49], 0);// 强化装备
    //    setUiComponentEnable_11BE350((int*)thisP[0x4A], 0);// 分解装备
    //    setUiComponentEnable_11BE350((int*)thisP[0x4B], 0);// 生产
    //    setUiComponentEnable_11BE350((int*)thisP[0x53], 0);// 重铸徽章
    //    setUiComponentEnable_11BE350((int*)thisP[0x54], 0);// 徽章合成
    //    setUiComponentEnable_11BE350((int*)thisP[0x55], 0);// 装备增幅
    //    //setUiComponentEnable_11BE350((int*)thisP[0x56], 0);// 修理分解机
    //    //setUiComponentEnable_11BE350((int*)thisP[0x57], 0);// 升级分解机
    //    setUiComponentEnable_11BE350((int*)thisP[0x63], 0);// 重铸徽章
    //    setUiComponentEnable_11BE350((int*)thisP[0x64], 0);// 徽章合成
    //}
    //else {

    //}
    
    return;
}

void Naked hookAddOldSkillCommand(void) {
    //01011BF9
    __asm {
        pushad
        mov ecx, esi
        mov edx, [ebp + 8]
        call addOldSkillCommandImp
        popad
        mov     ebx, [ebp - 8]
        mov     ecx, [ebx]
        push    1
        push    1
        push    0
        push    ecx
        mov ecx, 0x01011C05
        jmp ecx
    }
}

//004F2320
//004D4628

thisCall showOldSkillWin_511EE0 = (thisCall)0x511EE0;
cdeclCall1 GetGameDataString_119FEF0 = (cdeclCall1)0x119FEF0;
int __fastcall hookshowSkillWin(int* thisP, int edx, int a2, int a3, int a4) {
    //for (int *start = (int*)0x00401000; (int)start != 0x02000000; start += 4) {
    //    if ((*start & 0xFF00FFFF) != 0x2A005400) continue;
        //GetGameDataString_119FEF0(0x1826848);
    //}
    if (sq_getJob_5AEE70(*(int*)0x01AC790C) > 8) {
        return showWin_E77470(thisP, a2, a3, a4);
    }
    if ((*(int**)0x1A6F750)[0x2C] == 5) {
        closeNavigationWin_E706E0(*(int**)0x1A6F750, 1, 0x15);
    }
    else {
        showNavigationWin_E7AC30(*(int**)0x1A6F750, 5, 0, 1);
    }

    return 1;
    //return showWin_E77470(thisP, edx, 0x112, 0xFFFFFFFF, 0);
    //return showOldSkillWin_511EE0((int*)0x01AF1F64, 0);
}


int __fastcall hookshowStudySkillWin(int* thisP, int edx, int a2, int a3, int a4) {
    if (a2 == 0xB2) return 0;//不显示城镇小地图
    else if (a2 == 0x112) {
        showOldSkillWin((int*)a3, a4);
        //showWin_E77470(thisP, a2, a3, a4);
        return 0;
    }
    else if (a2 == 0xf5) {
        if ((*(int**)0x1A6F750)[0x2C] != 5) {
            showNavigationWin_E7AC30(*(int**)0x1A6F750, 5, 0, 1);
        }
        return 0;
    }
    return showWin_E77470(thisP, a2, a3, a4);
}

DWORD isOpenning = 0;
Naked void FixInputMethod1(void) {
    __asm {
        mov edx, isOpenning
        test edx, edx
        jne goNot
        mov isOpenning, 1
        mov byte ptr ds : [0x1BDA4B0] , 0
        jmp goExit
        goNot:
        mov byte ptr ds : [0x1BDA4B0] , 1
        goExit:
        mov edx, 0x011E54D5
        jmp edx
    }
}
Naked void FixInputMethod2(void) {
    __asm {
        mov isOpenning, 0
        mov byte ptr[esi + 0x2b9], 0
        mov edx, 0x011D01FE
        jmp edx
    }
}

Naked void BlackDungeonIcon0() {
    __asm {
        mov  ebx, 0xff5ad6f7
        mov  dword ptr[edi + 8], 1
        mov  eax, dword ptr[0x1b564e4]
        push 0x810613
        ret
    }
}
Naked void BlackDungeonIcon1() {
    __asm {
        cmp  dword ptr[ebx + 8], 1
        jne  goNext
        mov  dword ptr[ebp - 0x240], 0xff5ad6f7
        jmp  goExit;
        goNext:
        mov  dword ptr[ebp - 0x240], 0xffffffff
        goExit:
        push 0x810c3d
        ret
    }
}
Naked void BlackDungeonIcon2() {
    __asm {
        cmp  dword ptr[ebx + 8], 1
        jne  goExit
        cmp  dword ptr[ebp - 0x240], 0xffb3b3b3
        jne  goExit
        mov  dword ptr[ebp - 0x240], 0xff5ad6f7
        goExit:
        mov  dword ptr[ebp - 0x258], edi
        push 0x810e4b
        ret
    }
}
//S 铂金槽 0x10
//A 红色槽 0x01
//B 黄色槽 0x02
//C 绿色槽 0x04
//D 蓝色槽 0x08
//M 彩色槽 0xef
// 
//011CB31E
void hookThread() {


    //黑钻黄名
    //writeJmpCode((void*)0x81060E, BlackDungeonIcon0);
    //writeJmpCode((void*)0x810C33, BlackDungeonIcon1);
    //writeJmpCode((void*)0x810E45, BlackDungeonIcon2);

    //修复输入法
    *(BYTE*)0x011D014B = 0xEB;
    *(WORD*)0x11E54C7 = 0x9090;
    writeJmpCode((void*)0x011E54CE, FixInputMethod1);
    writeJmpCode((void*)0x011D01F7, FixInputMethod2);

    //*(DWORD*)0x00403421 = 0x3A8; //简体CodePage

    memcpy((void*)0x011F9E95, "\xE9\x24\x02\x00\x00\x90", 6); *(BYTE*)0x011F9431 = 0xEB; //修复i字符
    memcpy((void*)0x00457D97, "\xE9\xB4\x00\x00\x00\x90", 6);//修复掉强化

    //花枝未知hook
    //writeNopCode((void*)0x74F21D, 5);
    //memcpy((void*)0x760004, "\x81\x3E\x5B\x02\x00\x00\xEB\x18", 8);

    memcpy((void*)0x113295F, "\x83\xBE\x60\xC2\x2B\x00\x00", 7);//修复makePkgVmp cmp dword ptr [esi + 0x2bc260], 0
    //memcpy((void*)0x74E930, "\x55\x89\xE5\xA1\x7C\xB3\xAF\x01", 8);//修复收包Vmp  push ebp; mov  ebp, esp; mov  eax, dword ptr [0x1afb37c];
    memcpy((void*)0x1119BDF, "\x8B\xD\x7C\xF7\xA6\x01", 6);//修复sendSelectDungeonPkg Vmp
    memcpy((void*)0x514C35, "\x68\xD9\x57\x41\x01", 5);//修复进图Vmp

    //*(BYTE*)0x114E342 = 0xBA; *(DWORD*)0x114E343 = 0x25C;
    //*(BYTE*)0x114EE06 = 0x68; *(DWORD*)0x114EE07 = 0x25D;
    //*(BYTE*)0x114E8A1 = 0xB9; *(DWORD*)0x114E8A2 = 0x230;
    //*(BYTE*)0x114EA0C = 0xB9; *(DWORD*)0x114EA0d = 0x231;
    //客户端通讯协议修复
    //*(DWORD*)0x72CCA8 = 0x2F3;
    //*(DWORD*)0x72CCB9 = 0x232;
    //*(DWORD*)0x72CDC3 = 0x232;
    //天空特效
    *(WORD*)0x80A9EF = 0x9090;
    *(WORD*)0x86F560 = 0xB5E9; *(DWORD*)0x86F562 = 0x90000000;
    *(BYTE*)0x97CC09 = 0;
    *(BYTE*)0xF3FEE1 = 0xF9;
    //修复开罐动画
    *(DWORD*)0xFAC16B = 400;
    

    


    Sleep(500);

    *(DWORD*)0x0111B375 = 0x90909090;
    writeNopCode((void*)0x01118C6A, 11);



    *(WORD*)0x011CFFA0 = 0x01B0;//开启粘贴功能
    //*(WORD*)0x008C5480 = 0x56EB;//修复波比说话
   
    GumInterceptor* v = gum_interceptor_obtain();

   


    *(BYTE*)0x011A0DE0 = 0x55;
    *(DWORD*)0x011A0DE1 = 0x018BEC8B;
    gum_interceptor_replace_fast(v, (gpointer)0x11A0DE0, (gpointer)hookDecrypt_11A0DE0, (gpointer*)&decrypt_11A0DE0);

    *(BYTE*)0x004C0F87 = MAX_LV;
    *(BYTE*)0x0084A7B7 = MAX_LV;
    *(BYTE*)0x008F6477 = MAX_LV;
    *(BYTE*)0x00923122 = MAX_LV;

    init70_delay();
    soundOptimizeInit();
   
    writeJmpCode((void*)0x01011BF9, hookAddOldSkillCommand);
    writeCallCode((void*)0x004F2320, hookshowSkillWin);
    writeCallCode((void*)0x004D4628, hookshowSkillWin);
    gum_interceptor_replace_fast(v, (gpointer)0xE77470, (gpointer)hookshowStudySkillWin, (gpointer*)&showWin_E77470);
}



typedef HANDLE(__stdcall* CreateMutexWFn)(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName);
HANDLE __stdcall hookCreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName) {
    CreateMutexWFn fn = *(CreateMutexWFn*)0x0155A1A4;
    return fn(lpMutexAttributes, bInitialOwner, NULL);
}


//EFA900 draggable

thisCall1Args2 OldCharacInfoWin__Constructor_2803DF2 = (thisCall1Args2)0x2803DF2;

int __cdecl hookMakeWin_F139A0(int id, int argc) {
    int* win = NULL;
    if (id == HellPartyInfoWinId) {
        win = HellPartyInfo_Constructor(argc);
    }
    else if (id == QuestDetailWinId) {
        win = QuestDetailWin_Constructor(argc);
    }
    else if (id == CurrentQuestListWinId) {
        win = CurrentQuestListWin_Constructor(argc);
    }
    else if (id == 0x4C) {
        win = (int*)newUiComponent_11B0380(0x2C4);
        OldCharacInfoWin__Constructor_2803DF2(win, argc);
        *win = 0x18231AC;
        win[2] = 0x4C;
        setUiComponentVisable_11BE610((int *)win[0xb0], 0); //我的信息隐藏称号簿
    }
    else if (id < 417) {
        win = (int*)makeWin_F139A0(id, argc);
        if (id == 0x89) {//地下城地图窗口
            win[0x8F] = addCloseBtn(win, 0, 0);
        }
        else if (id == 0x81) {
            //隐藏地狱级提示
            setUiComponentVisable_11BE610((int *)win[3], 0);
        }
        else if (id == 0x3B) {//其他人信息隐藏称号簿
            *(DWORD*)0x00F1AD55 = 0x0000F5E9;
            setUiComponentVisable_11BE610((int*)win[0xb0], 0);
        }
    }
    
    DPRINTF("[0x%08x][%d, %d][0x%x, 0x%x]\n", win, id, argc, id, argc);
    return (int)win;
}

int __fastcall hookCloseWin_E794CE(int* thisP, int edx, int winId, int a3, char a4) {
    if (winId == 10) return winId;
    return closeWin_E745B0(thisP, winId, a3, a4);
}

void __fastcall hookCloseWinObj_E742C0(int* thisP, int edx, int *winObj) {
    //if (winObj[2] == 10) return ;
    closeWinObj_E742C0(thisP, (int)winObj);
}


thisCall1Args2 drawDungeonMiniMapWin_1038690 = (thisCall1Args2)0x1038690;
void __fastcall hookDrawDungeonMiniMapWin_1038690(int* thisP, int edx, int a2) {
    int* p = (int*)thisP[3];
    int* btn = (int*)thisP[0x8F];

    btn[5] = p[5] + p[14] - 16;
    btn[6] = p[6] + 2;

    if (IControl__IsClick_11BDFC0(btn)) {
        closeWin_E745B0(*(int**)0x1A6F750, 0x89, 0xFFFFFFFF, 0);
    }

    drawDungeonMiniMapWin_1038690(thisP, a2);
    int* minimapImg = (int*)getPreloadImg_11BB1B0(*(int**)0x1A6A870, 23);
    innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 36), p[5] + p[14] / 2 - 11, p[6] + 3, *(int*)0x1B5582C);

    //drawTextStart_12115B0(*(int**)0x1B5582C, (int)(thisP + 0x3E));
    //drawText_1211C30(*(int**)0x1B5582C, p[5] + p[14] / 2 - 16, p[6] + 3, 0xFF9BC8E6, (int)L"地图");
    //drawTextEnd_12115D0(*(int**)0x1B5582C);
}

void __fastcall fixDungeonMiniMapAlpha(int* thisP, int edx, int a2) {
    thisP[0xA] = 0xff;
    BasePopupWin__ProcDraw_EF7E20(thisP, a2);
}

cdeclCall2 procNotiClearQuestList_7382B0 = (cdeclCall2)0x7382B0;
int __cdecl hookProcNotiClearQuestList_7382B0(int a1, int a2) {
    int ret = procNotiClearQuestList_7382B0(a1, a2);
    goldSkill_OnNotiClearQuest();
    riding_OnNotiClearQuest();
    return ret;
}

cdeclCall2 procNotiReqHumanCertify_735840 = (cdeclCall2)0x735840;
int __cdecl hookProcNotiReqHumanCertify_735840(int a1, int a2) {
    common_OnReqHumanCertify();
    int ret = procNotiReqHumanCertify_735840(a1, a2);
    return ret;
}

cdeclCall4 procCmdRecv36FinshQuest_724460 = (cdeclCall4)0x724460;
int __cdecl hookProcCmdRecv36FinshQuest_724460(int a1, int retCode, int errCode, int a4) {
    int ret = procCmdRecv36FinshQuest_724460(a1, retCode, errCode, a4);
    goldSkill_OnFinshQuest();
    riding_OnFinshQuest();
    return ret;
}


thisCall1Args CNTownModule__onEnterModule_1113E40 = (thisCall1Args)0x1113E40;
char __fastcall hookCNTownModule__onEnterModule_1113E40(int* thisP, int edx, int a2) {
    int ret = CNTownModule__onEnterModule_1113E40(thisP, edx, a2);
    common_CNTownModule_onEnterModuleCb(thisP, a2);
    init70_CNTownModule_onEnterModuleCb(thisP, a2);
    riding_CNTownModule_onEnterModuleCb(thisP, a2);
    return ret;
}

thisCall1Args CNTownModule__onExitModule_1112C70 = (thisCall1Args)0x1112C70;
char __fastcall hookCNTownModule__onExitModule_1112C70(int* thisP, int edx, int a2) {
    int ret = CNTownModule__onExitModule_1112C70(thisP, edx, a2);
    common_CNTownModule__onExitModuleCb(thisP, a2);
    goldSkill_CNTownModule__onExitModuleCb(thisP, a2);
    riding_CNTownModule__onExitModuleCb(thisP, a2);
    return ret;
}


thisCall1Args CNMainGameModule_onEnterModule_110D6E0 = (thisCall1Args)0x110D6E0;
char __fastcall hookCNMainGameModule_onEnterModule_110D6E0(int* thisP, int edx, int a2) {
    int ret = CNMainGameModule_onEnterModule_110D6E0(thisP, edx, a2);
    DPRINTF("CNMainGameModule_onEnterModule %d %d\n", a2, *(BYTE*)0x1A6F6A1);
    
    if (*(BYTE*)0x1A6F6A1) {
        showWin_E77470(*(int**)0x1A6F750, HellPartyInfoWinId, 0, 0);
        setUiComponentVisable_11BE610(getHellWinCtlbtn(), 1);
    }
    int* dungeon = (int*)getDungeonObj_75C610((int*)getCNModule_706410());
    int* map = (int*)dungeon[0x23];
    currentDungeonId = map[0x29];
    setUiComponentVisable_11BE610(getMiniMapBtn(), map[0x29] < 40001 || map[0x29] > 40095);
    common_CNMainGameModule_onEnterModuleCb(thisP, a2);
    goldSkill_CNMainGameModule_onEnterModuleCb(thisP, a2);
    riding_CNMainGameModule_onEnterModuleCb(thisP, a2);
    npcFavor_CNMainGameModule_onEnterModuleCb(thisP, a2);
    return ret;
}

thisCall1Args CNMainGameModule_onExitModule_110DBC0 = (thisCall1Args)0x110DBC0;
char __fastcall hookCNMainGameModule_onExitModule_110DBC0(int* thisP, int edx, int a2) {
    common_CNMainGameModule_onExitModuleCb(thisP, a2);
    goldSkill_CNMainGameModule_onExitModuleCb(thisP, a2);
    riding_CNMainGameModule_onExitModuleCb(thisP, a2);
    int ret = CNMainGameModule_onExitModule_110DBC0(thisP, edx, a2);
    DPRINTF("CNMainGameModule_onExitModule %d\n", a2);
    closeWin_E745B0(*(int**)0x1A6F750, HellPartyInfoWinId, 0xFFFFFFFF, 0);
    setUiComponentVisable_11BE610(getMiniMapBtn(), 0);
    setUiComponentVisable_11BE610(getHellWinCtlbtn(), 0);
    currentDungeonId = -1;
    return ret;
}

thisCall1Args setDungeonClearState_1036E80 = (thisCall1Args)0x1036E80;
int __declspec(noinline) __fastcall  hookSetDungeonClearState_1036E80(int* thisP, int edx, int a2) {
    int ret = setDungeonClearState_1036E80(thisP, edx, a2);
    int retAddr = (int)_ReturnAddress();
    DPRINTF("setDungeonClearState %d by 0x%08x\n", a2, retAddr);
    if (retAddr == 0x0073b52c) {
        closeWin_E745B0(*(int**)0x1A6F750, HellPartyInfoWinId, 0xFFFFFFFF, 0);
    }
    else if (a2 > 7) {
        closeWin_E745B0(*(int**)0x1A6F750, HellPartyInfoWinId, 0xFFFFFFFF, 0);
        setUiComponentVisable_11BE610(getMiniMapBtn(), 0);
        setUiComponentVisable_11BE610(getHellWinCtlbtn(), 0);
    }
    init70_setDungeonClearStateCb(thisP, a2);
    return ret;
}

thisCall hudBtnCickCheck_4C6680 = (thisCall)0x4C6680;
void __fastcall hookHudBtnCickCheck_4C6680(int* thisP, int edx) {
    hudBtnCickCheck_4C6680(thisP, edx);
    int *miniMapbtn = getMiniMapBtn();
    if (miniMapbtn && ((char*)miniMapbtn)[12] && (IControl__IsClick_11BDFC0(miniMapbtn) )) {
        if (isWinShowing_E71770(*(int**)0x1A6F750, 0x89))
            closeWin_E745B0(*(int**)0x1A6F750, 0x89, 0xFFFFFFFF, 0);
        else
            showWin_E77470(*(int**)0x1A6F750, 0x89, 0, 0);
    }
    int *hellWinCtlbtn = getHellWinCtlbtn();
    if (hellWinCtlbtn && ((char*)hellWinCtlbtn)[12] && (IControl__IsClick_11BDFC0(hellWinCtlbtn))) {
        if (isWinShowing_E71770(*(int**)0x1A6F750, HellPartyInfoWinId)) {
            closeWin_E745B0(*(int**)0x1A6F750, HellPartyInfoWinId, 0xFFFFFFFF, 0);
        }
        else {
            showWin_E77470(*(int**)0x1A6F750, HellPartyInfoWinId, 0, 0);
        }
    }
}

int __fastcall hookEncrypt_11A0930(int* thisP, int edx, int a2, int a3) {
    int retAddr = (int)_ReturnAddress();  
    switch (*(int*)thisP) {
        case 0x30:
            *(int*)a2 = 1;
            DPRINTF("0x%08x Encrypt:[0x%08x, 0x%08x, %d] \n", retAddr, *thisP, *(int*)a3, *(int*)a2);
    }
    return encrypt_11A0930(thisP, a2, a3);
}


//#ifdef _DEBUG
wchar_t *ip;
thisCall2Args2 sub_1204DD0 = (thisCall2Args2)0x1204DD0;
int __fastcall hookSub_1204DD0(int *thisP, int , int a2, int a3) {
    return sub_1204DD0(thisP, (int)ip, a3);
}
//#endif // DEBUG
void fixIp() {
    //ip
    ip = wcsdup(GameIP);
    *(WORD*)0x010F5E0D = 0x6890;
    *(DWORD*)0x010F5E0F = (int)ip;
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x1204DD0, (gpointer)hookSub_1204DD0, (gpointer*)&sub_1204DD0);
}
void baseFix() {
    
//#ifdef _DEBUG
    *(BYTE*)0x01A4F30C = 0x01;//gm显示技能id
    *(WORD*)0x0114E13A = 0x9090;//反调试
    *(WORD*)0x0114E0E3 = 0x9090;//反调试
//#ifndef _HOME
    *(DWORD*)0x0086DB15 = 0x000082E9;//技能无CD
    *(BYTE*)0x0084E549 = 0xEB;//技能无色无消耗
    *(DWORD*)0x0052150E = 0xC390C031;//物品无CD
    *(WORD*)0x007C17FD = 0x9090;//物品无消耗
    *(BYTE*)0x0075B456 = 0x80;//本地GM
//#endif // _HOME

    /*
    // 所有命令都包含空格 比如 //lv 70 注意输入空格方能生效
	// GM喇叭 1120 可无限使用 且显示方式为GM
	//lv 指定玩家等级 因服务端限制 最高70 根据自己版本来 如版本60 最高输 lv 60 即可
	//item 刷物品 道具默认100 除非物品有上限 有代码即可 不适用时装
	//itemseed 补齐道具 例 //itemseed 3037 9999 补齐无色到9999个
	// 如果背包有5000个 补4999 一个没有 背包到账9999个
	//mailitem 邮件刷物品 不支持宠物
	//dropitem 图内掉落物品 仅限装备 不能发时装 宠物等
	//randitem 随机属性的物品 最下级和最上级之间
	//startevent 开启活动 ID和参数 例 //startevent 1 1 开启无限PL
	// 活动ID 在数据库 d_taiwan-dnf_event_info 表里
	// 多数活动参数1即可 参数2不填 强化活动是1-100的折扣 其他有些活动是百分比
	//endevent 关闭活动 ID 例 //endevent 1 关闭无限PL
	// 开关活动命令需要输两次才能开启或关闭
	//spd 显示当前角色一些属性在公告上 没啥用
	//avatar 只能刷时装 默认属性 自己拿时装调整箱调整
	//hide 当前城镇隐身 下个城镇失效
	//dirty 刷的装备带红字
	//pd 删除角色所有契约
	//q 完成任务 需要知道任务在PVF里面的代码 且不支持完成需要材料的
	//guild exp 工会经验 一次只能刷9999 多了无效
	//coin 扣除复活币指定数量
	//durable 指定装备耐久度 例 //durable 10 30 武器耐久度更改为30
	// 武器（10）称号（11）上衣（12）肩膀（13）下衣（14）鞋子（15）腰（16）项链（17）手镯（18）戒指（19）左槽（20）魔法石（21）
	//fatigue 扣除疲劳值
	//fatigue set 指定疲劳值 例 //fatigue set 1000 当前角色疲劳值变为1000
	//cargo delete 删除账号金库 需要小退角色 且仓库内物品 一并删除
	//dimen max 重置异界进入次数
	//ulti max 极限祭坛入场次数重置
	//guildfund 公会基金指定数量
	//ac reset 删除所有称号簿称号
	//tb reset 删除称号簿
	//ac all 完成所有称号簿称号
	//pcroom on 开启黑钻7天 off是关闭 适用于所有在线角色
	//monitor
    */



//#endif // DEBUG
}

thisCall2Args2 getDiffImg_1078DF0 = (thisCall2Args2)0x1078DF0;

#ifdef _DEBUG
int __fastcall hookGetDiffImg_1078DF0(int* thisP, int, int a2, int a3) {
    int pos1[] = { 25, 26, 27, 28, 16, 17, 18, 19, 20 };
    int pos2[] = { 72, 12 };
    int pos;
    if (a2 == a3)//当前光标
        pos = pos2[thisP[0xE3]];
    else
        pos = pos1[4 * thisP[0xE3] + a3];
    return getImageByPos_11B4BD0((int*)thisP[0xDB], pos);
}

void heroDiffV1() {
    /*
    英雄级实现方式1
    通过对地狱级的修改，把地狱级提升为英雄级常规提升为地狱级
    即3格难度变4格，4格难度变5格
    */
    *(BYTE*)0x010794C8 = 0x4;//遍历到英雄级
    *(BYTE*)0x010794D8 = 0x0E;//4格光标 draw x偏移
    *(BYTE*)0x010794DF = 0x0B;//5格光标 draw x偏移
    //修复组队难度过滤的难度文本
    *(DWORD*)0x00F357E5 = 0xBBDA;
    *(DWORD*)0x00F357EB = -0xBBD8;

    //最大支持英雄级
    *(BYTE*)0x0043898F = 3;//修复组队难度过滤的难度文本 
    *(BYTE*)0x010793C8 = 3;

    *(BYTE*)0x010793A8 = 4;
    *(BYTE*)0x010793AF = 5;
    *(BYTE*)0x010706EC = 5;

    *(DWORD*)0x19D98AC = 4;
    
    *(BYTE*)0x0076724D = 0;//修复右下角小图标 0->N/E/M/K/H	21->E/M/H/U		55->普/险/勇/王/噩
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x1078DF0, (gpointer)hookGetDiffImg_1078DF0, (gpointer*)&getDiffImg_1078DF0);
}
#endif

const int heroDungeonId[] = { 52, 53, 83, 84, 85, 86, 87 };
int __fastcall hookGetDiffImgV2_1078DF0(int* thisP, int, int a2, int a3) {
    int pos1[] = { 92, 93, 94, -1, 25, 26, 27, 28, 16, 17, 18, 19, 20 };
    int pos2[] = { 95, 72, 21 };
    int pos;
    if (a2 == a3)//当前光标
        pos = pos2[thisP[0xE3]];
    else
        pos = pos1[4 * thisP[0xE3] + a3];
    return getImageByPos_11B4BD0((int*)thisP[0xDB], pos);
}

void __fastcall DrawDifficultyCursor(int* thisP, int diff) {
    int pos[] = { 18, 14, 11 };//光标xPos 3/4/5
    if (thisP[0xE3] != 2) {
        thisP[0xE3] = 1;
        int dungeonId = *(int*)thisP[0xE1];
        for (int i = 0; i < sizeof(heroDungeonId) / sizeof(int); ++i) {
            if (heroDungeonId[i] == dungeonId) thisP[0xE3] = 2;
        }
    }
    int img = hookGetDiffImgV2_1078DF0(thisP, 0, thisP[0xD5], diff);
    int x = thisP[5] + diff * pos[thisP[0xE3]] + 29;
    int y = thisP[6] + 16;
    drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, img);
}

void Naked DrawDifficultyCursorHook(void) {
    //010794CB
    __asm {
        push edi
        push esi
        mov ecx, esi
        mov edx, edi
        call DrawDifficultyCursor
        pop esi
        pop edi
        mov eax, 0x1079518
        jmp eax
    }
}

cdeclCall1 getDungeonMaxDiff_438940 = (cdeclCall1)0x438940;
int __cdecl hookGetDungeonMaxDiff_438940(int dungeonId) {
    for (int i = 0; i < sizeof(heroDungeonId) / sizeof(int); ++i) {
        if (heroDungeonId[i] == dungeonId) return 4;
    }
    return 3;
    //return getDungeonMaxDiff_438940(dungeonId);
}

thisCall1Args2 setDungeonDiffType_12019D0 = (thisCall1Args2)0x12019D0;
int __fastcall hookSetDungeonDiffType_12019D0(int* thisP, int, int a2) {
    a2 = 1;
    int dungeonId;
    __asm mov dungeonId, edi
    if (dungeonId) dungeonId = *(int*)dungeonId;
    for (int i = 0; i < sizeof(heroDungeonId) / sizeof(int); ++i) {
        if (heroDungeonId[i] == dungeonId) {
            a2 = 2;
            break;
        }
    }
    return setDungeonDiffType_12019D0(thisP, a2);
}

thisCall1Args2 setDungeonDiff_1079020 = (thisCall1Args2)0x1079020;
int __fastcall hookSetDungeonDiff_1079020(int* thisP, int, int a2) {
    if (a2 == 5) return setDungeonDiff_1079020(thisP, a2);
    a2 = 4;
    int dungeonId;
    __asm mov dungeonId, edi
    if (dungeonId) dungeonId = *(int*)dungeonId;
    for (int i = 0; i < sizeof(heroDungeonId) / sizeof(int); ++i) {
        if (heroDungeonId[i] == dungeonId) {
            a2 = 5;
            break;
        }
    }
    return setDungeonDiff_1079020(thisP, a2);
}

cdeclCall1 getdiffIconPos_767240 = (cdeclCall1)0x767240;
int __cdecl hookGetdiffIconPos_767240(int a2) {
    //sprite_interface_newstyle_windows_party.NPK
    return a2;
    //if (a2 >= 6)
    //    return 6;
    //else
    //    return a2 + 21;
}

//cdeclCall1 getDungeonDesignateDiff_438F30 = (cdeclCall1)0x438F30;
int __cdecl hookGetDungeonUnlockDiff_438F30(int dungeonId) {
    for (int i = 0; i < sizeof(heroDungeonId) / sizeof(int); ++i) {
        if (heroDungeonId[i] == dungeonId) {
            return 5;
        }
    }
    return 4;
}

int __cdecl getDungeonDesignateDiff(int defaultValue) {
    ScanInt_1223660(0);
    return 4;
}

const wchar_t* __stdcall getDungeonDiffStr_4B98B0(int diff) {
    switch (diff){
    case 0:return L"普通级";
    case 1:return L"冒险级";
    case 2:return L"勇士级";
    case 3:return L"王者级";
    case 4:return L"英雄级";
    default:return L"";
    }
}
void heroDiffV2() {
    /*
        英雄级实现方式2
        直接新增英雄级，在原有的3格，4格的难度的基础上新增5格难度
        同时支持3种难度
        需要指定5格难度的dungeonId
    */
    *(BYTE*)0x010794C8 = 0x4;//遍历到英雄级
    //修复组队难度过滤的难度文本
    *(DWORD*)0x00F357E5 = 0xBBDA;
    *(DWORD*)0x00F357EB = -0xBBD8;
    *(BYTE*)0x010706EC = 0x5;
    *(DWORD*)0x19D98AC = 4;//修复右下角图标难度可以显示到5级
    *(BYTE*)0x0076724D = 0;//修复右下角小图标 0->N/E/M/K/H	21->E/M/H/U 55->普/险/勇/王/噩
    *(BYTE*)0x0072CF31 = 3;
    *(DWORD*)0x00FC3932 = 148;//获取权限的图标地狱级改成王者级
    *(DWORD*)0x00FC393E = 147;//获取权限的图标地狱级改成王者级
    *(DWORD*)0x00FC3921 = 146;//获取权限的图标地狱级改成王者级

    writeJmpCode((LPVOID*)0x010794CB, (PVOID)DrawDifficultyCursorHook);
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x438940, (gpointer)hookGetDungeonMaxDiff_438940, (gpointer*)&getDungeonMaxDiff_438940);
    gum_interceptor_replace_fast(v, (gpointer)0x12019D0, (gpointer)hookSetDungeonDiffType_12019D0, (gpointer*)&setDungeonDiffType_12019D0);
    gum_interceptor_replace_fast(v, (gpointer)0x1079020, (gpointer)hookSetDungeonDiff_1079020, (gpointer*)&setDungeonDiff_1079020);
    //gum_interceptor_replace_fast(v, (gpointer)0x438F30, (gpointer)hookGetDungeonUnlockDiff_438F30, NULL);
    //gum_interceptor_replace_fast(v, (gpointer)0x767240, (gpointer)hookGetdiffIconPos_767240, (gpointer*)&getdiffIconPos_767240);
    //writeCallCode((LPVOID*)0x01304EE8, (PVOID)getDungeonDesignateDiff);
    gum_interceptor_replace_fast(v, (gpointer)0x1078DF0, (gpointer)hookGetDiffImgV2_1078DF0, (gpointer*)&getDiffImg_1078DF0);
    gum_interceptor_replace_fast(v, (gpointer)0x004B98B0, (gpointer)getDungeonDiffStr_4B98B0, NULL);
}

int __fastcall hookUiMgr__init_E84540(int* thisP) {
    int ret = UiMgr__init_E84540(thisP);
    init70_UiMgr__initCb(thisP);
    oldSkillWin_UiMgr__initCb(thisP);
    highLevelEvil_UiMgr__initCb(thisP);
    return ret;
}

//cdeclCall1 SetCharacTp_91FC60 = (cdeclCall1)0x91FC60;
int __cdecl fixSetCharacTp_91FC60(int tp) {
    int ret = ((cdeclCall1)0x91FC60)(tp);
    int slotBk = (*(int**)0x1AC790C)[0x1303];
    (*(int**)0x1AC790C)[0x1303] = 1 - slotBk;
    ((cdeclCall1)0x91FC60)(tp);
    (*(int**)0x1AC790C)[0x1303] = slotBk;
    return ret;
}

//7=Shift键    a=Alt键
char __fastcall hookIsKeyDown_11CBC60(int* thisp, int, int a2, int a3) {
    static char lastValue;
    char ret = IsKeyDown_11CBC60(thisp, a2, a3);
    if (a2 == 0x4E && ret) {
        if (lastValue) {
            lastValue = 0;
            return 0;
        }
        else {
            lastValue = 1;
            return 0x80;
        }
    }
    return ret;
}

void init() {
    gum_init_embedded();
    GumInterceptor* v = gum_interceptor_obtain();
    *(DWORD*)0x00758FA7 = (int)&hookProcNotiClearQuestList_7382B0;
    *(DWORD*)0x00757939 = (int)&hookProcNotiReqHumanCertify_735840;
    *(DWORD*)0x0072BA18 = (int)&hookProcCmdRecv36FinshQuest_724460;

#ifdef EN_GM
    //* (WORD*)0x0088C04D = 0x9090;//修复绝望祭坛掉线问题
    //baseFix();
    //fixIp();
    //gum_interceptor_replace_fast(v, (gpointer)0x11CBC60, (gpointer)hookIsKeyDown_11CBC60, (gpointer*)&IsKeyDown_11CBC60);//连发
#ifdef EN_MULTI_PROC
    //支持双开
    writeCallCode((LPVOID*)0x0112D97E, (PVOID)hookCreateMutexW);
    *(BYTE*)0x0112D983 = 0x90;
    writeCallCode((LPVOID*)0x00706872, (PVOID)hookCreateMutexW);
    *(BYTE*)0x00706877 = 0x90;
    *(BYTE*)0x0116D0DC = 0xEB;
#endif // EN_MULTI_PROC
#endif // EN_GM
    * (BYTE*)0x0070564A = 0xEB;//取消启动缩小其他窗口
    

    //客户定制
    * (DWORD*)0x0071F383 = 0x00010be9;//忽略升级获取的sp 提示
    writeCallCode((LPVOID*)0x0071F5A2, (PVOID)fixSetCharacTp_91FC60);//修复同步tp点数

    extern void HellPartyReleaseWindowInit(void);
    HellPartyReleaseWindowInit();

    extern void tpSkillInit(void);
    tpSkillInit();

    heroDiffV2();
    
    init70();

    writeNopCode((void*)0x00706883, 5);//修复卡进度条，返回城镇黑屏问题

    oldSkillWinInit();
    cancelSKillInit();
    oldQuestWinInit();
    npcFavorInit();
    oldCharacInfoWinInit();
    itemInventoryWinInit();
    highLevelEvilInit();
    equimentJewelInit();

    extern void privateStoreInit(void);
    privateStoreInit();

    extern void NpcShopWinInit(void);
    NpcShopWinInit();

    extern void byQuQuInit(void);
    byQuQuInit();

    extern void skillCommonInit(void);
    skillCommonInit();

    extern void PvpInit(void);
    PvpInit();

    extern void actionInit(void);
    actionInit();

    extern void boosterInit(void);
    boosterInit();

    extern void eventInit(void);
    eventInit();
    
    

    gum_interceptor_replace_fast(v, (gpointer)0xE84540, (gpointer)hookUiMgr__init_E84540, (gpointer*)&UiMgr__init_E84540); 
    
    gum_interceptor_replace_fast(v, (gpointer)0xF139A0, (gpointer)hookMakeWin_F139A0, (gpointer*)&makeWin_F139A0);
    gum_interceptor_replace_fast(v, (gpointer)0x1038690, (gpointer)hookDrawDungeonMiniMapWin_1038690, (gpointer*)&drawDungeonMiniMapWin_1038690);

    writeCallCode((LPVOID*)0x004D508D, (PVOID)hookHudBtnCickCheck_4C6680);

    gum_interceptor_replace_fast(v, (gpointer)0x1113E40, (gpointer)hookCNTownModule__onEnterModule_1113E40, (gpointer*)&CNTownModule__onEnterModule_1113E40);
    gum_interceptor_replace_fast(v, (gpointer)0x1112C70, (gpointer)hookCNTownModule__onExitModule_1112C70, (gpointer*)&CNTownModule__onExitModule_1112C70);

    gum_interceptor_replace_fast(v, (gpointer)0x110D6E0, (gpointer)hookCNMainGameModule_onEnterModule_110D6E0, (gpointer*)&CNMainGameModule_onEnterModule_110D6E0);
    gum_interceptor_replace_fast(v, (gpointer)0x110DBC0, (gpointer)hookCNMainGameModule_onExitModule_110DBC0, (gpointer*)&CNMainGameModule_onExitModule_110DBC0);
    gum_interceptor_replace_fast(v, (gpointer)0x1036E80, (gpointer)hookSetDungeonClearState_1036E80, (gpointer*)&setDungeonClearState_1036E80);

    
    //writeCallCode((LPVOID*)0x00E7741B, (PVOID)hookCloseWinObj_E742C0);
    //writeCallCode((LPVOID*)0xE794CE, (PVOID)hookCloseWin_E794CE);//esc按键 关闭窗口判断

    //地下城地图窗口添加关闭btn控件空间
    *(DWORD*)0x00F15511 += 4;
    *(DWORD*)0x00F16996 += 4;
    //*(BYTE*)0x00EF698B = 1;//窗口的右上角？按钮显示
    //*(BYTE*)0x00EF60D3 = 1;
    //*(BYTE*)0x00EF6014 = 1;

    //*(BYTE*)0x00EF621D = 1;
    //*(BYTE*)0x00EF622C = 1;
    //*(BYTE*)0x00EF623B = 1;

#ifdef EN_ICON_ANIM
    initIconAnim();
#endif
    (new std::thread(hookThread))->detach();
}

void deinit() {
    gum_deinit_embedded();
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: init(); break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:break;
    case DLL_PROCESS_DETACH: deinit(); break;
    }
    return TRUE;
}
