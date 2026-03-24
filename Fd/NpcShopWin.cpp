#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall2Args2 NpcShopWin__OnOpen_EB7200 = (thisCall2Args2)0xEB7200;
int __fastcall hookNpcShopWin__OnOpen_EB7200(int* thisP, int, int a2, int a3) {
	int ret = NpcShopWin__OnOpen_EB7200(thisP, a2, a3);
	int** tagObj = (int**)thisP[0x60];
	if (!tagObj || !tagObj[0xAF]) return ret;

	int size = (tagObj[0xAF][9] - tagObj[0xAF][8]) >> 2;
	if (size == 0) return ret;
	int* obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)tagObj, size - 1);
	//setUiComponentVisable_11BE610(obj, 0);
	if (obj) setUiComponentPos_11BEAD0(obj, -10000, -10000, 1);
	setUiComponentVisable_11BE610((int*)thisP[0xA3], 0);
	setUiComponentVisable_11BE610((int*)thisP[0xA4], 0);
	return ret;
}

thisCall2Args2 sub_EB5B30 = (thisCall2Args2)0xEB5B30;
int __fastcall hooksub_EB5B30(int* thisP, int, int npcId, unsigned int a3) {
	
	return sub_EB5B30(thisP, npcId, a3 == 2 ? 0 : a3);
}

void NpcShopWinInit(void) {
	*(DWORD*)0x018223A0 = (int)hookNpcShopWin__OnOpen_EB7200;//NpcShop 隐藏回购tag	
	*(DWORD*)0x00EB1C47 = 0x10C;
	*(BYTE*)0x00EB1C0F = 0xC0;

	//*(BYTE*)0x00EB1441 -= 3; //窗体高度
	//*(BYTE*)0x00EB144B -= 3; //窗体高度
	//*(BYTE*)0x00EB1487 -= 3; //窗体高度
	//*(BYTE*)0x00EB1491 -= 3; //窗体高度

	writeCallCode((void*)0x00EB721D, hooksub_EB5B30);
}