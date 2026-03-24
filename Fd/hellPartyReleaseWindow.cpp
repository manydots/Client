#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"


static int itemId;
int __cdecl hookGetObjIconImgById_7B4DE0(int a1) {
	return getObjIconImgById_7B4DE0(itemId? itemId : a1);
}

int __cdecl hookGetObjNameById_7B4D60(int a1) {
	return getObjNameById_7B4D60(itemId ? itemId : a1);
}

int __cdecl hookGetObjGradeById_7B4F40(int a1) {
	return getObjGradeById_7B4F40(itemId ? itemId : a1);
}

thisCall2Args2 HellPartyReleaseWindow__OnOpen_63F5B0 = (thisCall2Args2)0x63F5B0;
char __fastcall hookHellPartyReleaseWindow__OnOpen_63F5B0(int* thisP, int, int questId, int a3) {
	itemId = 0;
	switch (*(int *)questId){
	case 2601:itemId = 4151; break;
	case 2603:itemId = 4152; break;
	case 2610:itemId = 4158; break;
	case 2613:itemId = 4356; break;
	case 2619:itemId = 4393; break;
	case 2622:itemId = 4394; break;
	}
	return HellPartyReleaseWindow__OnOpen_63F5B0(thisP, questId, a3);
}

void HellPartyReleaseWindowInit(void) {
	writeCallCode((void*)0x0063F66B, hookGetObjIconImgById_7B4DE0);
	writeCallCode((void*)0x0063F67B, hookGetObjNameById_7B4D60);
	writeCallCode((void*)0x0063F6B1, hookGetObjGradeById_7B4F40);
	*(DWORD*)0x015A3AF8 = (int)hookHellPartyReleaseWindow__OnOpen_63F5B0;
}
