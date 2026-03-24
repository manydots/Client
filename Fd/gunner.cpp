#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

void ranger(void) {
	//多爆群攻
	/*std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
	hook->resize(1);
	auto b = hook->begin();
	b++->setValue(H_WORD, 0x00C023EA, 0x9090);
	thisCall3Args2 multiheadshot = (thisCall3Args2)tools_relocation_hook(0x00C020A0, 0x00C02479, hook);
	writeCallCode((void*)0x0233ADB5, multiheadshot);
	delete hook;*/
}

void launcher(void) {
	//手炮精通
	*(BYTE*)0x00C08157 = 112;
	*(BYTE*)0x00C08203 = 112;
	*(BYTE*)0x00C08201 = 0;
	*(BYTE*)0x0099DF39 = 112;
	*(BYTE*)0x0099DF4E = 1;

	//卫星定位
	*(DWORD*)0x004BE4DB = 640 - 30;
	*(DWORD*)0x004BE4E8 = 480 - 1;

	*(DWORD*)0x004BE55B = -(640 - 33);
	*(DWORD*)0x004BE560 = 640 - 21;

	*(DWORD*)0x004BE5BF = -(640 - 119);
	*(DWORD*)0x004BE5C5 = 640 - 95;

	*(DWORD*)0x004BE504 = 640 + 20;
	*(DWORD*)0x004BE511 = 480 -1;
}

void mechanic(void) {

}

int __fastcall loadImproveHitDelayAni(int *thisP, int, wchar_t* Source, int a3, int a4) {
	int* charac = 0;
	__asm mov charac, edi;
	if (charac) {
		float v1 = 0;
		decrypt_11A0DE0(charac + 0x1816, (int)(charac + 0x1818), (int)&v1);
		if (v1 == 1.0f) return loadAniObjByPath_109A4E0(thisP, (int)L"ui/fd/dump/dump0.ani", a3, a4);
		//wprintf(L"load ani:%s %0.2f %d\n", Source, v1, v2);
	}
	
	return loadAniObjByPath_109A4E0(thisP, (int)Source, a3, a4);
}

int __fastcall loadImprovePiercingAni(int* thisP, int, wchar_t* Source, int a3, int a4) {
	int* charac = 0;
	__asm mov charac, edi;
	if (charac) {
		int v2 = 0;
		decrypt_11A0DE0(charac + 0x1813, (int)(charac + 0x1815), (int)&v2);
		if (!v2)  return loadAniObjByPath_109A4E0(thisP, (int)L"ui/fd/dump/dump1.ani", a3, a4);
		//wprintf(L"load ani:%s %0.2f %d\n", Source, v1, v2);
	}

	return loadAniObjByPath_109A4E0(thisP, (int)Source, a3, a4);
}

int __fastcall loadImprovePiercingLoopAni(int* thisP, int, wchar_t* Source, int a3, int a4) {
	int* charac = 0;
	__asm mov charac, esi;
	if (charac) {
		int v2 = 0;
		decrypt_11A0DE0(charac + 0x1813, (int)(charac + 0x1815), (int)&v2);
		if (!v2)  return loadAniObjByPath_109A4E0(thisP, (int)L"ui/fd/dump/dump2.ani", a3, a4);
		//wprintf(L"load ani:%s %0.2f %d\n", Source, v1, v2);
	}

	return loadAniObjByPath_109A4E0(thisP, (int)Source, a3, a4);
}

int __fastcall procImprove(int* thisP) {
	int lv31 = CNObject__getSkillLevel_84EE40(thisP, 31);
	int lv38 = CNObject__getSkillLevel_84EE40(thisP, 38);
	return !lv31 && !lv38;

}

void Naked fixImprove(void) {
	//00C08603
	__asm {
		cmp	edi, 31
		jz goProc
		cmp	edi, 38
		jz goProc
		mov eax, 0xC086FF
		jmp eax
		goProc:
		mov ecx, esi
		call procImprove
		test eax,eax
		jnz goCancel
		mov eax, 0x00C08614
		jmp eax
		goCancel:
		mov eax, 0xC086C5
		jmp eax

	}
}

void spitfire(void) {
	//*(DWORD*)0x00ACB64A = 0x016B9D10;
	//gum_init_embedded();
	//GumInterceptor* v = gum_interceptor_obtain();
	//gum_interceptor_replace_fast(v, (gpointer)0x109A4E0, (gpointer)GameAniObj__load_109A4E0, (gpointer*)&loadAniObjByPath_109A4E0);
	writeCallCode((void *)0x023929E1, loadImproveHitDelayAni);//ImproveHitDelay.ani
	writeCallCode((void *)0x02403D09, loadImprovePiercingAni);//ImprovePiercingLoop.ani 僵直ani
	writeCallCode((void*)0x00ACB659, loadImprovePiercingLoopAni);//ImprovePiercingLoop.ani 僵直ani
	*(BYTE*)0x009BB016 = 38;
	*(BYTE*)0x009BB052 = 0;
	writeJmpCode((void*)0x00C08603, fixImprove);
}

void gunnerInit(void) {
	ranger();
	launcher();
	mechanic();
	spitfire();
}

