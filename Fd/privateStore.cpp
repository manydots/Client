#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"
extern stdCall mySendPkg_1132A90;

thisCall2 InputView__getInputText_11CE3C0 = (thisCall2)0x11CE3C0;
thisCall2 InputView__getText_11CE470 = (thisCall2)0x11CE470;
thisCall2Args2 sub_C37D70 = (thisCall2Args2)0xC37D70;
thisBCall2 isAvatorEquim_788960 = (thisBCall2)0x788960;
thisCall1Args2 sub_7B4D20 = (thisCall1Args2)0x7B4D20;
thisCall2 sub_521AB0 = (thisCall2)0x521AB0;
int* dollObj;
int __fastcall PrivateStoreNWin__sendCompleteDisplayPkg(int* thisP) {
	int* inputView = (int *)InputView__getInputText_11CE3C0((int*)thisP[0x45]);
	if (inputView[3] <= 0) return 0;
	BYTE count = 0;
	for (int i = 0; i < 14; ++i){
		if (Banner__getItemBySlot_7B9CE0(*(int **)0x1AF277C, i))
			++count;
	}
	if (count <= 0) return 0;
	BYTE push = *(BYTE*)0x1132930;
	DWORD cmd = *(DWORD*)0x1132931;
	if (cmd != 0xec83ec8b) {
		DWORD v;
		VirtualProtect((LPVOID)0x1132930, 5, PAGE_EXECUTE_READWRITE, &v);
		*(BYTE*)0x1132930 = 0x55;
		*(DWORD*)0x1132931 = 0xec83ec8b;
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)0x1132930, 5);
		makePkg_1132930(*(int**)0x1AFB37C, 90);
		*(BYTE*)0x1132930 = push;
		*(DWORD*)0x1132931 = cmd;
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)0x1132930, 5);
		VirtualProtect((LPVOID)0x1132930, 5, v, &v);
	}
	else {
		makePkg_1132930(*(int**)0x1AFB37C, 90);
	}
	PkgPushWStr_11332B0(*(int**)0x1AFB37C, inputView[2]);
	PkgPushByte_1133120(*(int**)0x1AFB37C, count);
	int data[4] = { 0 };
	for (int i = 0, *obj, **p; i < 14; ++i) {
		obj = (int*)Banner__getItemBySlot_7B9CE0(*(int**)0x1AF277C, i);
		if (!obj) continue;
		PkgPushShort_1133150(*(int**)0x1AFB37C, i);
		p = (int **)sub_C37D70((int*)thisP[0x3C], (int)data, (int)&obj);
		PkgPushInt_1133180(*(int**)0x1AFB37C, p[2][4]);
		PkgPushByte_1133120(*(int**)0x1AFB37C, sub_7B4D20(obj, 2) && isAvatorEquim_788960(obj));
		p = (int**)sub_C37D70(*(int**)0x1AF2784, (int)data, (int)&obj);
		PkgPushShort_1133150(*(int**)0x1AFB37C, p[2][4]);
		if (sub_7B4D20(obj, 2)) {//装备
			if(isAvatorEquim_788960(obj))
				PkgPushInt_1133180(*(int**)0x1AFB37C, 0);
			else {
				int v = 0;
				decrypt_11A0DE0(obj + 0x412, (int)(obj + 0x414), (int)&v);
				PkgPushInt_1133180(*(int**)0x1AFB37C, v);
			}
		}
		else {
			PkgPushInt_1133180(*(int**)0x1AFB37C, sub_521AB0(obj));
		}
	}
	int doll = *(int*)0x1AF2788;
	if (doll) {
		PkgPushShort_1133150(*(int**)0x1AFB37C, Banner__findItemIndex_7B9F40(*(int **)0x1A6F754, (int)dollObj));
	}
	else {
		PkgPushShort_1133150(*(int**)0x1AFB37C, 0xFFFF);
	}
	mySendPkg_1132A90();
	return 1;
}

thisCall3Args2 ItemDollShop__OnUsing_6EDE60 = (thisCall3Args2)0x6EDE60;
int __fastcall hookItemDollShop__OnUsing_6EDE60(int* thisP, int, int a2, int a3, int a4) {
	dollObj = thisP;
	return ItemDollShop__OnUsing_6EDE60(thisP, a2, a3, a4);
}
void privateStoreInit(void) {
	//摆摊开启14个位置
	*(DWORD*)0x00EBF5FB = 2;
	*(WORD*)0x00EC292F = 0x79EB;//x
	*(BYTE*)0x00EC3C2F = 14;//x
	*(BYTE*)0x00EC04ED = 14;//x
	*(BYTE*)0x00EC2928 = 14;//x
	*(BYTE*)0x00EC1474 = 14;//x
	*(BYTE*)0x00EC2DD1 = 14;//x
	*(BYTE*)0x00EC41FE = 14;//x
	*(WORD*)0x00EC1912 = 0x9090;//时装摆摊
	*(BYTE*)0x00EC3EE5 = 14;//展示窗口的banner
	*(BYTE*)0x00EC1F24 = 14;//购买后检查是否为空 为空就取消商店
	*(DWORD*)0x01812DB8 = (int)PrivateStoreNWin__sendCompleteDisplayPkg;
	*(DWORD*)0x015B2724 = (int)hookItemDollShop__OnUsing_6EDE60;
	//writeNopCode((void*)0x00EC2E18, 6);
	//*(DWORD*)0x01812DB8 = 
}