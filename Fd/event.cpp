#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

static int eventIconPosX;
int __fastcall hookDrawX(int* thisP, int edx, int x, int y, int a4, float a5, float a6, float a7, int a8, float a9, float a10) {
	return drawImgByXY2_11B41E0(thisP, x + eventIconPosX, y, a4, a5, a6, a7, a8, a9, a10);
}

thisCall2 drawProperDungeonEventIcon_1076FA0;
BYTE __fastcall hookDrawEventIcon(int* thisP) {
    int characLv = 1;
    int* charcObj = *(int**)0x1AC790C;
    if (charcObj)
        decrypt_11A0DE0(charcObj + 0x8C7, (int)(charcObj + 0x8C9), (int)&characLv);
    int* dungeonInfo = (int*)thisP[0xD3];
   
    if (characLv >= dungeonInfo[0x12]) {//minLv
        int maxLv = 0;
        decrypt_11A0DE0(dungeonInfo + 0x18, (int)(dungeonInfo + 0x1A), (int) & maxLv);
        if (characLv <= maxLv + 1 && ((thisCall2)0x42E9B0)((int*)thisP[0xFC]) != 1) {
            eventIconPosX = 68 + ((BYTE*)thisP)[0xA4] * 50;
            drawProperDungeonEventIcon_1076FA0(thisP);
        }  
    }
    return IControl__IsOverOrClick_11BE040(thisP);
}
void eventInit(void) {
    //std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(4);
    //auto b = hook->begin();
    //b++->setValue(H_BYTE, 0x010770F7, 116);
    //b++->setValue(H_BYTE, 0x01077091, 117);
    ////b++->setValue(H_BYTE, 0x01077003, 117);//y
    //b++->setValue(H_CALL, 0x010770A3, (int)hookDrawX);//x
    //b++->setValue(H_CALL, 0x01077106, (int)hookDrawX);//x
    //drawProperDungeonEventIcon_1076FA0 = (thisCall2)tools_relocation_hook(0x01076FA0, 0x01077117, hook);
    //delete hook;
    //writeCallCode((void *)0x0107803D, hookDrawEventIcon);

    //修复攻城buf消失问题
    //*(DWORD*)0x0076103B = 0x90909090;
    //*(BYTE*)0x01113E99 = 0x90; *(WORD*)0x01113E9A = 0x9090;
    //*(DWORD*)0x011159C3 = 0x90909090;
    //*(WORD*)0x0042F8AB = 0x9090;
    //*(WORD*)0x0110DCF6 = 0x9090;
    *(BYTE*)0x0042F894 = 0xEB;
    *(BYTE*)0x0110DCDF = 0xEB;
}