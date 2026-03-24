#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall2 CNSwordman__getMomentarySlashHitRate_CAB5A0 = (thisCall2)0xCAB5A0; 
int __fastcall hookCNSwordman__getMomentarySlashHitRate_CAB5A0(int* thisP) {
	int ret = CNSwordman__getMomentarySlashHitRate_CAB5A0(thisP);
	//printf("rate:%d\n", ret);
	return ret;
}

thisCall1Args2 CNRDObject__getEtcAttackInfoByIdx_70213F = (thisCall1Args2)0x70213F;
int* __fastcall fixMomentarySlashHit(int* thisP, int, int a2) {
	int* atk = (int*)CNRDObject__getEtcAttackInfoByIdx_70213F(thisP, a2);
	int rate = CNSwordman__getMomentarySlashHitRate_CAB5A0(thisP) + 100;
	//printf("rate:%d\n", rate);
	encrypt_11A0930(atk + 9, (int)&rate, (int)(atk + 0xB));
	return atk;
}

void Naked fixMomentarySlashHit1(void) {
	//00CD1659
	__asm {
		mov ecx, esi
		call hookCNSwordman__getMomentarySlashHitRate_CAB5A0
		mov dword ptr[ebp - 0x8DC] , eax
		mov eax, 0x00CD165F
		jmp eax
	}
}

#define Element_Fire	 0
#define Element_Water	 1
#define Element_Dark	 2
#define Element_Light	 3
thisCall1Args2 AttackInfo__isValidElement_12B81D0 = (thisCall1Args2)0x12B81D0;
thisCall1Args2 sub_55FE50 = (thisCall1Args2)0x55FE50;
thisCall2Args2 sub_551D00 = (thisCall2Args2)0x551D00;
int getAttackInfoElement(int* atkInfo) {
//BYTE fire = AttackInfo__isValidElement_12B81D0((int*)atkInfo, Element_Fire);
//BYTE water = AttackInfo__isValidElement_12B81D0((int*)atkInfo, Element_Water);
//BYTE dark = AttackInfo__isValidElement_12B81D0((int*)atkInfo, Element_Dark);
//BYTE light = AttackInfo__isValidElement_12B81D0((int*)atkInfo, Element_Light);
	int v10[3], v8[3], v9[3];
	int* v3, v;
	sub_55FE50(atkInfo + 0x6A, (int)v10);
	int element = 0;
	while (1) {
		v3 = (int*)GameVector__end_7C4340(atkInfo + 0x6A, (int)v9);
		if (v10[2] == v3[2]) return element;
		v = *(DWORD*)(v10[2] + 0xC);
		if (v < 4) WBYTE(&element, v, 1);
		sub_551D00(v10, (int)v8, 0);
	}
}

thisCall1Args2 myCNRDPassiveObject__setCurrentAttackInfo_805030;
thisCall1Args2 AttackInfo__setElement_12B88C0 = (thisCall1Args2)0x12B88C0;
void setAttackInfoElement(int* atk, int element) {
	AttackInfo__setElement_12B88C0(atk, 4);
	if (RBYTE(&element, Element_Fire))AttackInfo__setElement_12B88C0(atk, Element_Fire);
	if (RBYTE(&element, Element_Water))AttackInfo__setElement_12B88C0(atk, Element_Water);
	if (RBYTE(&element, Element_Dark))AttackInfo__setElement_12B88C0(atk, Element_Dark);
	if (RBYTE(&element, Element_Light))AttackInfo__setElement_12B88C0(atk, Element_Light);
}


int __fastcall hookCNRDPassiveObject__setCurrentAttackInfo_805030(int* thisP, int, int atkInfo) {
	if (!atkInfo) return myCNRDPassiveObject__setCurrentAttackInfo_805030(thisP, atkInfo);
	int element = getAttackInfoElement((int*)atkInfo);
	int ret = myCNRDPassiveObject__setCurrentAttackInfo_805030(thisP, atkInfo);
	setAttackInfoElement((int *)CNRDPassiveObject__getCurrentAttackInfo_442C60(thisP), element);
	return ret;
}

Naked void fixCNRDTombStonePObj__setAlphaForMaster(void) {
	//00A7DA24
	__asm {
		add esp, 0x14
		test eax, eax
		je monster
		mov esi, eax
		mov eax, [esi]
		mov edx, [eax + 0x448]
		mov eax, 0x00A7DA31
		jmp eax
		monster:
		push 0x2C
		push 0x0B
		mov esi, 0
		mov eax, 0x00A7DA38
		jmp eax
	}
}

thisCall5Args2 CNRDSkill__getLevelDataPower_913D70 = (thisCall5Args2)0x913D70;
int __fastcall fixCNRDTombStonePObj__getLevelDataPower_913D70(int* thisP, int, int idx, int a3, int a4, int a5, int a6) {
	if (!a3 || !RTDynamicCast_13D76DF(a3, 0, 0x19D91E8, 0x19DC7FC, 0)) return 250;
	return CNRDSkill__getLevelDataPower_913D70(thisP, idx, 0xFFFF0001, a4, a5, a6);

}

void skillCommonInit(void) {
	GumInterceptor* v = gum_interceptor_obtain();

	*(DWORD*)0x008A8EE8 = 0xFE;
	*(BYTE*)0x008A8FEF = 0xEB;
	*(BYTE*)0x008A9005 = 0xEB;

	*(DWORD*)0x00A7DCAE = 0x182474FF; *(BYTE*)0x00A7DCB2 = 0x90;
	writeJmpCode((void*)0x00A7DA24, fixCNRDTombStonePObj__setAlphaForMaster);
	writeCallCode((void*)0x00A7DCB7, fixCNRDTombStonePObj__getLevelDataPower_913D70);

	extern void gunnerInit(void);
	gunnerInit();


	myCNRDPassiveObject__setCurrentAttackInfo_805030 = (thisCall1Args2)tools_relocation(0x805030, 0x00805569);
	gum_interceptor_replace_fast(v, (gpointer)0x805030, (gpointer)hookCNRDPassiveObject__setCurrentAttackInfo_805030, (gpointer*)&CNRDPassiveObject__setCurrentAttackInfo_805030);

	extern void swordmanInit(void);
	swordmanInit();

	extern void priestInit(void);
	priestInit();
}