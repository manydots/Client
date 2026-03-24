#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"


int __fastcall drawCharacInfoPropertyIcon(int* thisP, int startIdx, int x, int y) {
	int idx = 2 * startIdx, idxIconPos = 0x1827104 + (8 * startIdx);
    int i = 8, v;
    do{
        if (idx == 8) {
            idx += 2;
            idxIconPos += 8;
        }
        if (idx < 32){
            v = RDWORD(idxIconPos, -4);
            if (v != -1){
                v = getImageByPos_11B4BD0((int *)thisP[0x7A], v);
                drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, v);
            }
        }
        if (idx + 1 < 32){
            v = RDWORD(idxIconPos, 0);
            if (v != -1) {
                v = getImageByPos_11B4BD0((int*)thisP[0x7A], v);
                drawImgByXY_11B3950(*(int**)0x1B5582C, x + 0x7E, y, v);
            }
        }
        idxIconPos += 8;
        idx += 2;
        y += 18;
        --i;
    } while (i);
    return 0;
}

thisCall2Args2 drawCharacInfoPropertyData = (thisCall2Args2)0xFAF100;
int __fastcall drawCharacPropertyInfo(int* thisP) {
    int x = GetXPos_42FF60((int*)thisP[3]);
    int y = GetYPos_11BE300((int*)thisP[3]) + 0x9E;
    int startIdx = ((int***)thisP)[0x82][0xB0][0xB2];
    drawCharacInfoPropertyIcon(thisP, startIdx, x + 3, y);
    startIdx *= 2;
    int line = 0;
    do{
        if (startIdx == 8) {
            startIdx += 2;
        }
        if (startIdx < 32)
            drawCharacInfoPropertyData(thisP, startIdx, line);
        if (startIdx + 1 < 32)
            drawCharacInfoPropertyData(thisP, startIdx + 1, line);
        ++line;
        startIdx += 2;
    } while (line < 8);
    return 0;
}

thisCall1Args2 getCharacPropertyInfoToastText = (thisCall1Args2)0xFAE430;
int __fastcall hookGetCharacPropertyInfoToastText(int *thisP, int, int idx){
    if (idx >= 8 && idx <= 23) {
        idx += 2;
        __asm add edx, 2;
    }
    return getCharacPropertyInfoToastText(thisP, idx);
}

thisCall2Args2 OldCharacInfoWin__OnOpen_FB4730 = (thisCall2Args2)0xFB4730;
int __fastcall hookOldCharacInfoWin__OnOpen_FB4730(int* thisP, int, int a2, int a3) {
    int ret = OldCharacInfoWin__OnOpen_FB4730(thisP, a2, a3);
    if (a2 > 0) {
        OldTagLayout__setCurrentIdx_11D4C70((int*)thisP[0x7B], a2);
    }
    return ret;
}

void oldCharacInfoWinInit() {
    writeCallCode((void*)0x00FB2A9F, drawCharacPropertyInfo);
    writeCallCode((void*)0x00FB1C1F, hookGetCharacPropertyInfoToastText);
    *(DWORD*)0x018231C0 = (int)hookOldCharacInfoWin__OnOpen_FB4730;
}