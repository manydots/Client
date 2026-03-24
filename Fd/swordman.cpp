#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall2 CNPassiveObject__reset_8024A0 = (thisCall2)0x8024A0;


void weaponmaster(void) {
	//拔刀
	BYTE hookCmd[] = { 0x89, 0xF1, 0xE8, 0x5C, 0x9F, 0xFD, 0xFF, 0x89, 0x85, 0x24, 0xF7, 0xFF, 0xFF, 0xEB, 0x13 };
	writeCodeArray((void*)0x00CD163D, hookCmd, sizeof(hookCmd));
	*(BYTE*)0x00CB6A87 = 0xff;
	*(WORD*)0x00CD1758 = 0x0BEB;
}

void soulbringer(void) {
	*(DWORD*)0x00CDE2DC = 0x0001BBE9;//跳过鬼影步普通攻击
	*(DWORD*)0x00CDE6F9 = 0x003166E9;//跳过鬼影步前冲攻击
	*(DWORD*)0x00CCBB1D = 0x0001FEE9;//跳过卡洛+鬼影步普攻附加火焰
	*(BYTE*)0x00CA8541 = 0xEB;
	*(BYTE*)0x00CA84BA = 0xEB;
	*(BYTE*)0x00CC7415 = 0xEB;
	*(BYTE*)0x00CA7F01 = 0xEB;
}

void berserker(void) {

}

void asura(void) {

}



void swordmanInit(void) {
	weaponmaster();
	soulbringer();
	berserker();
	asura();

}