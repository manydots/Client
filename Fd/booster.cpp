
#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"



BYTE __cdecl CNStackable__isRandomBox_6E4FF0(int itemId, int a3) {
	if (itemId == 2681819) return 1;
	return ((cdeclCall2)0x6E4FF0)(itemId, a3);
}

int __fastcall CNBoosterItem__getType_6EF1A0(int* thisP) {
	if (thisP[7] == 2681819) return 0x1C;
	return ((thisCall2)0x6EF1A0)(thisP);
}

int __fastcall fixBoosterWinImp(int id) {
	switch (id){
		case 896:
		case 992:
		case 2660169:
		case 2660397:
		case 2660419:
		case 690000280:
		case 2681819:
			return 1;
	}
	return 0;
}

Naked void fixBoosterWin(void) {
	//00F32451
	__asm {
		test bl, bl
		jnz goPass
		mov ecx, eax
		call fixBoosterWinImp
		test eax, eax
		jz checkNext
		goPass:
		mov eax, 0xF324A6
		jmp eax
	checkNext:
		mov eax, 0xF3247F
		jmp eax
	}

}

void boosterInit(void) {
	//GumInterceptor* v = gum_interceptor_obtain();
	//gum_interceptor_replace_fast(v, (gpointer)0x94C830, (gpointer)hookShowMainWinText_94C830, (gpointer*)&showMainWinText_94C830);
	writeCallCode((void*)0x006EDBEA, CNStackable__isRandomBox_6E4FF0);
	writeCallCode((void*)0x006F153C, CNBoosterItem__getType_6EF1A0);
	writeJmpCode((void*)0x00F32451, fixBoosterWin);
}