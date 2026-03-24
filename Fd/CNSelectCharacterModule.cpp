#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"

#define NEW
#define OldStyleCreateCharac

thisCall1Args2 myCNSelectCharacterModule__DrawProc;
int __fastcall hookCNSelectCharacterModule__DrawProc_11039F0(int* thisP, int, int a2) {
	return myCNSelectCharacterModule__DrawProc(thisP, a2);
}

thisCall2 myCNSelectCharacterModule__Proc_1105190;
int __fastcall hookCNSelectCharacterModule__Proc_1105190(int* thisP) {
	return myCNSelectCharacterModule__Proc_1105190(thisP);
}

#ifdef NEW
#define PosX    20
#define PosY    -56
#define PosY2   -78
int __fastcall DrawSelectFrame(int* thisP, int edx, int x, int y, char a4) {
	if (y == 0x127) {
		y += PosY2;
	}
	else {
		y += PosY;
	}
	return setUiComponentPos_11BEAD0(thisP, x, y + 20, a4);
}

int __fastcall  DrawRenameFrame(int* thisP, int edx, int x, int y, char a4) {
	y -= 0x26;
	return setUiComponentPos_11BEAD0(thisP, x + 2, y + 20, a4);
}

int __fastcall DrawRenameButton(int* thisP, int edx, int x, int y, char a4) {
	//if (y == 0x127) {
	//	y += PosY2;
	//}
	//else {
	//	y += PosY;
	//}
	return setUiComponentPos_11BEAD0(thisP, x, y + 20, a4);
}

thisCall3Args2 my_10FD760;
char __fastcall hookSub_10FD760(int* thisP, int edx, int a2, int* x, int* y) {
	//printf("1[%d,%d,%d]\n", a2, *x, *y);
	if (a2 >= 4) {
		*y += PosY2;
	}
	else {
		*y += PosY;
	}
	//if ((int)_ReturnAddress() == 0x01102265)
	//    *y += 20;
	return my_10FD760(thisP, a2, (int)x, (int)y);
}
char __fastcall hookSub2_10FD760(int* thisP, int edx, int a2, int* x, int* y) {
	//printf("2[%d,%d,%d]\n", a2, *x , *y);
	if (a2 >= 4) {
		*y += PosY2;
	}
	else {
		*y += PosY;
	}
	*y += 20;
	return my_10FD760(thisP, a2, (int)x, (int)y);
}

char __cdecl getRunPosYLinearValue(int a1, int a2, int a3, int a4) {
	//printf("[%d,%d][%d,%d]\n", a1, a2, a3, a4);
	if (a2 == 0x127) {
		a2 += PosY2;
	}
	else {
		a2 += PosY;
	}

	return getLinearValue_11B98C0(a1, a2, a3, a4);
}

thisCall3Args2 GameAct__play_10A4560 = (thisCall3Args2)0x10A4560;
int __fastcall hookGameAct__play_10A4560(int* thisP, int, int x, int y, int a4) {
	if (y == 0x127) {
		y += PosY2;
	}
	else {
		y += PosY;
	}
	return GameAct__play_10A4560(thisP, x, y + 20, a4);
}

thisCall2 my_515540;
char __fastcall hookSub_515540(int* thisP) {
	return my_515540(thisP);
}

forceinline void setCharacAlign4() {
	GumInterceptor* v = gum_interceptor_obtain();
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(80);
	hook->resize(1);
	auto b = hook->begin();
	b++->setValue(H_BYTE, 0x010FF43A, 0x3F);
	thisCall2 my_10FF410 = (thisCall2)tools_relocation_hook(0x10FF410, 0x010FF519, hook);
	////drawSelectCharacPage_1102020
	////sub_10FF410
	//*(BYTE*)0x010FF43A = 0x3F;//lea     eax, [edi+edi]

	hook->resize(5);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x010FF022, 0);
	b++->setValue(H_BYTE, 0x010FF02D, 4);
	b++->setValue(H_BYTE, 0x010FF03F, 4);
	b++->setValue(H_BYTE, 0x010FF191, 4);
	b++->setValue(H_BYTE, 0x010FF1A7, 4);
	thisCall2Args2 my_10FF010 = (thisCall2Args2)tools_relocation_hook(0x10FF010, 0x010FF1C6, hook);
	////sub_10FF340
	////sub_10FF010
	//*(BYTE*)0x010FF022 = 0x00;
	//*(BYTE*)0x010FF02D = 4;
	//*(BYTE*)0x010FF03F = 4;
	//*(BYTE*)0x010FF191 = 4;
	//*(BYTE*)0x010FF1A7 = 4;

	hook->resize(2);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x010FF377, 4);
	b++->setValue(H_CALL, 0x010FF3D1, (int)my_10FF010);
	thisCall2 my_10FF340 = (thisCall2)tools_relocation_hook(0x10FF340, 0x010FF407, hook);
	////drawSelectCharacPage_1102020
	////sub_10FF340 lea ebx, [eax+eax+4]
	////*(BYTE*)0x010FF376 = 0x00;
	//*(BYTE*)0x010FF377 = 4;

	//b = hook->begin();
	//b++->setValue(H_BYTE, 0x010FF2FE, 8);
	//b++->setValue(H_DWORD, 0x010FF309, 0x40000000);
	//thisCall2 my_1101C60 = (thisCall2)tools_relocation2_hook(0x1101C60, 0x01101D8A, 0x010FF2F0, 0x010FF339, hook);
	////drawSelectCharacPage_1102020
	////sub_1101C60
	*(BYTE*)0x010FF2FE = 8;
	*(DWORD*)0x010FF309 = 0x40000000;

	hook->resize(6);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x010FEC5C, 4);
	b++->setValue(H_BYTE, 0x010FED6C, 8);
	b++->setValue(H_BYTE, 0x010FED87, 4);
	b++->setValue(H_BYTE, 0x010FEDB7, 4);
	b++->setValue(H_BYTE, 0x010FEE09, 4);
	b++->setValue(H_BYTE, 0x010FECE9, 7);
	thisCall2 my_10FEC00 = (thisCall2)tools_relocation_hook(0x10FEC00, 0x010FEE87, hook);
	////drawSelectCharacPage_1102020
	////sub_10FEC00
	//*(BYTE*)0x010FEC5C = 4;
	//*(BYTE*)0x010FED6C = 8;
	//*(BYTE*)0x010FED87 = 4;
	//*(BYTE*)0x010FEDB7 = 4;
	//*(BYTE*)0x010FEE09 = 4;
	//*(BYTE*)0x010FECE9 = 7;
	////0x011D55CD 

	hook->resize(7);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x010FD784, 0);
	b++->setValue(H_BYTE, 0x010FD89E, 0);
	b++->setValue(H_DWORD, 0x010FD8B0, 4);
	b++->setValue(H_BYTE, 0x010FD8CF, 0);
	b++->setValue(H_BYTE, 0x010FD8DB, 4);
	b++->setValue(H_BYTE, 0x010FD836, 4);
	b++->setValue(H_CALL, 0x010FD84F, (int)getRunPosYLinearValue);
	my_10FD760 = (thisCall3Args2)tools_relocation_hook(0x10FD760, 0x010FD8F5, hook);
	////drawSelectCharacPage_1102020
	////sub_10FD760
	//*(BYTE*)0x010FD784 = 0x00;
	//*(BYTE*)0x010FD89E = 0x00;
	//*(DWORD*)0x010FD8B0 = 4;
	//*(BYTE*)0x010FD8CF = 0x00;
	//*(BYTE*)0x010FD8DB = 4;
	//*(BYTE*)0x010FD836 = 4;
	//writeCallCode((LPVOID*)0x010FD84F, (LPVOID)getRunPosYLinearValue);

	hook->resize(70);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x011020FD, 0x00); //lea eax,dword ptr ds:[eax+eax]
	b++->setValue(H_BYTE, 0x01102137, 0x00); //lea eax,dword ptr ds:[eax+eax]
	b++->setValue(H_BYTE, 0x01102110, 4);
	b++->setValue(H_BYTE, 0x0110209A, 8);
	b++->setValue(H_BYTE, 0x011020A9, 4);
	b++->setValue(H_BYTE, 0x011021BF, 0x00);//lea ecx,dword ptr ds:[eax+eax]
	b++->setValue(H_BYTE, 0x011021EC, 0x00);//lea     eax, [eax+eax]
	b++->setValue(H_BYTE, 0x01102243, 4);
	b++->setValue(H_BYTE, 0x01102227, 0x09);//lea     edx, [ecx+ecx]
	b++->setValue(H_BYTE, 0x0110233b, 0x1B);//lea     ebx, [ebx+ebx]
	b++->setValue(H_BYTE, 0x01102340, 8);
	b++->setValue(H_DWORD, 0x01102373, 0x40000000); b++->setValue(H_BYTE, 0x01102382, 0x00);// 余4
	b++->setValue(H_BYTE, 0x01102393, 4);
	b++->setValue(H_BYTE, 0x01102456, 8);
	b++->setValue(H_BYTE, 0x011024B4, 8);
	b++->setValue(H_DWORD, 0x011024ED, 0x40000000); b++->setValue(H_BYTE, 0x011024FC, 0x00);// 余4
	b++->setValue(H_BYTE, 0x0110250D, 4);
	b++->setValue(H_BYTE, 0x011028E5, 8);
	b++->setValue(H_BYTE, 0x01102904, 8);
	b++->setValue(H_DWORD, 0x01102933, 0x40000000); b++->setValue(H_BYTE, 0x01102942, 0x00);// 余4
	b++->setValue(H_BYTE, 0x01102953, 4);
	b++->setValue(H_BYTE, 0x01102C70, 8);
	b++->setValue(H_BYTE, 0x01102CB3, 7);
	b++->setValue(H_DWORD, 0x01102CBB, 0x40000000); b++->setValue(H_BYTE, 0x01102CCA, 0x00);// 余4
	b++->setValue(H_BYTE, 0x01102CDB, 4);
	b++->setValue(H_BYTE, 0x01102DC2, 8);
	b++->setValue(H_DWORD, 0x01102DE0, 0x40000000); b++->setValue(H_BYTE, 0x01102DEF, 0x00);// 余4
	b++->setValue(H_BYTE, 0x01102E00, 4);
	b++->setValue(H_BYTE, 0x01102E32, 0x00);
	b++->setValue(H_BYTE, 0x01102EDC, 8);
	b++->setValue(H_BYTE, 0x01102F6D, 8);
	b++->setValue(H_DWORD, 0x01102F93, 0x40000000); b++->setValue(H_BYTE, 0x01102FA2, 0x00);// 余4
	b++->setValue(H_BYTE, 0x01102FB4, 4);
	b++->setValue(H_BYTE, 0x01102FDA, 8);
	b++->setValue(H_BYTE, 0x01103029, 6);
	b++->setValue(H_BYTE, 0x01103070, 2);
	b++->setValue(H_BYTE, 0x011030B7, 7);
	b++->setValue(H_CALL, 0x011030C0, (int)my_10FF410);
	b++->setValue(H_CALL, 0x01102FE1, (int)my_10FF340);
	//b++->setValue(H_CALL, 0x01102F08, (int)my_1101C60);
	b++->setValue(H_CALL, 0x01102F66, (int)my_10FEC00);
	b++->setValue(H_CALL, 0x01102260, (int)hookSub2_10FD760);
	b++->setValue(H_CALL, 0x011023B3, (int)hookSub_10FD760);
	b++->setValue(H_CALL, 0x0110252F, (int)hookSub_10FD760);
	b++->setValue(H_CALL, 0x01102975, (int)hookSub_10FD760);
	b++->setValue(H_CALL, 0x01102CFB, (int)hookSub_10FD760);
	b++->setValue(H_CALL, 0x01102E22, (int)hookSub_10FD760);
	b++->setValue(H_CALL, 0x01102FCF, (int)hookGameAct__play_10A4560);
	b++->setValue(H_CALL, 0x0110217C, (int)DrawSelectFrame);
	b++->setValue(H_BYTE, 0x01102CD8, 65);
	b++->setValue(H_BYTE, 0x01102CD3, 127);
	//b++->setValue(H_BYTE, 0x01102CD8, 65);
	//b++->setValue(H_BYTE, 0x01102CD3, 127);
	b++->setValue(H_CALL, 0x01102D26, (int)DrawRenameButton);
	b++->setValue(H_CALL, 0x01102D6B, (int)DrawRenameFrame);
	b++->setValue(H_BYTE, 0x01102FB1, 65);
	b++->setValue(H_BYTE, 0x01102FAC, 127);
	b++->setValue(H_BYTE, 0x01102390, 65);
	b++->setValue(H_BYTE, 0x0110238B, 127);
	b++->setValue(H_BYTE, 0x0110294E, 65);
	b++->setValue(H_BYTE, 0x0110294B, 127);
	b++->setValue(H_BYTE, 0x01102DFD, 65);
	b++->setValue(H_BYTE, 0x01102DF8, 127);
	b++->setValue(H_BYTE, 0x0110250A, 65);
	b++->setValue(H_BYTE, 0x01102505, 127);
	thisCall1Args2 drawSelectCharacPage_1102020 = (thisCall1Args2)tools_relocation_hook(0x1102020, 0x011032CF, hook);


#ifdef OldStyleCreateCharac
	extern int __fastcall hookdrawCreateCharacPage_10FD900(int* thisP, int, int a2);
	hook->resize(2);
	b = hook->begin();
	b++->setValue(H_CALL, 0x01103AD5, (int)drawSelectCharacPage_1102020);
	b++->setValue(H_CALL, 0x01103ADE, (int)hookdrawCreateCharacPage_10FD900);
#else
	hook->resize(1);
	b = hook->begin();
	b++->setValue(H_CALL, 0x01103AD5, (int)drawSelectCharacPage_1102020);
#endif // OldStyleCreateCharac
	myCNSelectCharacterModule__DrawProc = (thisCall1Args2)tools_relocation_hook(0x11039F0, 0x01103D0A, hook);
	*(DWORD*)0x015BE274 = (int)hookCNSelectCharacterModule__DrawProc_11039F0;
	//drawSelectCharacPage_1102020 011032CF
	//*(BYTE*)0x011020FD = 0x00; //lea eax,dword ptr ds:[eax+eax]
	//*(BYTE*)0x01102137 = 0x00; //lea eax,dword ptr ds:[eax+eax]
	//*(BYTE*)0x01102110 = 4;

	//*(BYTE*)0x0110209A = 8;
	//*(BYTE*)0x011020A9 = 4;
	//*(BYTE*)0x011021BF = 0x00;//lea ecx,dword ptr ds:[eax+eax]
	//*(BYTE*)0x011021EC = 0x00;//lea     eax, [eax+eax]
	//*(BYTE*)0x01102243 = 4;
	//*(BYTE*)0x01102227 = 0x09;//lea     edx, [ecx+ecx]
	//*(BYTE*)0x0110233b = 0x1B;//lea     ebx, [ebx+ebx]
	//*(BYTE*)0x01102340 = 8;
	//*(DWORD*)0x01102373 = 0x40000000; *(BYTE*)0x01102382 = 0x00; // 余4
	//*(BYTE*)0x01102393 = 4;
	//*(BYTE*)0x01102456 = 8;

	//*(BYTE*)0x011024B4 = 8;
	//*(DWORD*)0x011024ED = 0x40000000; *(BYTE*)0x011024FC = 0x00; // 余4
	//*(BYTE*)0x0110250D = 4;
	//*(BYTE*)0x011028E5 = 8;

	//*(BYTE*)0x01102904 = 8;
	//*(DWORD*)0x01102933 = 0x40000000; *(BYTE*)0x01102942 = 0x00; // 余4
	//*(BYTE*)0x01102953 = 4;
	//*(BYTE*)0x01102C70 = 8;

	//*(BYTE*)0x01102CB3 = 7;
	//*(DWORD*)0x01102CBB = 0x40000000; *(BYTE*)0x01102CCA = 0x00; // 余4
	//*(BYTE*)0x01102CDB = 4;

	//*(BYTE*)0x01102DC2 = 8;
	//*(DWORD*)0x01102DE0 = 0x40000000; *(BYTE*)0x01102DEF = 0x00; // 余4
	//*(BYTE*)0x01102E00 = 4;
	//*(BYTE*)0x01102E32 = 0x00;
	//*(BYTE*)0x01102EDC = 8;

	//*(BYTE*)0x01102F6D = 8;
	//*(DWORD*)0x01102F93 = 0x40000000; *(BYTE*)0x01102FA2 = 0x00; // 余4
	//*(BYTE*)0x01102FB4 = 4;
	//*(BYTE*)0x01102FDA = 8;

	//*(BYTE*)0x01103029 = 6;
	//*(BYTE*)0x01103070 = 2;
	////*(BYTE*)0x01103095 = 3;
	//*(BYTE*)0x011030B7 = 7;
	//writeCallCode((LPVOID*)0x01102FCF, (LPVOID)hookGameAct__play_10A4560);
	//writeCallCode((LPVOID*)0x0110217C, (LPVOID)DrawSelectFrame);
	//*(BYTE*)0x01102FB1 = 65;//栏位起始坐标x
	//*(BYTE*)0x01102FAC = 127;//栏位间隔
	//*(BYTE*)0x01102390 = 65;//脚底魔法阵起始坐标x
	//*(BYTE*)0x0110238B = 127;//脚底魔法阵间隔
	//*(BYTE*)0x0110294E = 65;//名称职业起始坐标x
	//*(BYTE*)0x0110294B = 127;//名称职业间隔
	//*(BYTE*)0x01102DFD = 65;//鼠标拖动起始坐标x
	//*(BYTE*)0x01102DF8 = 127;//鼠标拖动间隔
	//*(BYTE*)0x0110250A = 65;//人物形象起始坐标x
	//*(BYTE*)0x01102505 = 127;//人物形象间隔


	//sub_10FE9E0
	*(DWORD*)0x010FEA0B = 0x40000000;// 除4

	//getCharacSlotPosX_10FD500
	*(DWORD*)0x010FD507 = 0x40000000; *(BYTE*)0x010FD516 = 0x00; // 余4
	*(BYTE*)0x010FD523 = 65;//栏位起始坐标x
	*(BYTE*)0x010FD520 = 127;//栏位间隔

	// sub_10FDCD0
	*(BYTE*)0x010FDCF0 = 0x00;
	*(BYTE*)0x010FDCF5 = 8;
	*(DWORD*)0x010FDD01 = 0x40000000; *(BYTE*)0x010FDD10 = 0x00; // 余4
	*(BYTE*)0x010FDD22 = 4;
	*(BYTE*)0x010FDD1F = 65;//鼠标起始坐标x
	*(BYTE*)0x010FDD1A = 127;//鼠标间隔
	*(BYTE*)0x010FDD39 = 125;//选中框宽度
	*(BYTE*)0x010FDD47 = 180;//选中框高度
	*(DWORD*)0x010FDD2F = 237;
	*(DWORD*)0x010FDD29 = -188;


	hook->resize(8);
	b = hook->begin();
	b++->setValue(H_BYTE, 0x011049B6, 9);
	b++->setValue(H_BYTE, 0x01104A73, 9);
	b++->setValue(H_BYTE, 0x01104B38, 0);
	b++->setValue(H_BYTE, 0x01104FEB, 0);
	b++->setValue(H_BYTE, 0x01104DCC, 0);
	b++->setValue(H_BYTE, 0x01104DD3, 0x1B);
	b++->setValue(H_BYTE, 0x01104DDF, 4);
	b++->setValue(H_BYTE, 0x01104DE8, 4);
	thisCall2 my_1104750 = (thisCall2)tools_relocation_hook(0x1104750, 0x0110518F, hook);

	hook->resize(1);
	b = hook->begin();
	b++->setValue(H_CALL, 0x011052FA, (int)my_1104750);
	myCNSelectCharacterModule__Proc_1105190 = (thisCall2)tools_relocation_hook(0x1105190, 0x01105355, hook);
	*(DWORD*)0x015BE288 = (int)hookCNSelectCharacterModule__Proc_1105190;

	////CNSelectCharacterModule::Proc_1105190
	////CNSelectCharacterModule::procModeSelectCharacter_1104750
	//*(BYTE*)0x011049B6 = 0x09;
	//*(BYTE*)0x01104A73 = 0x09;//lea ecx, [ecx+ecx]
	//*(BYTE*)0x01104B38 = 0x00;
	//*(BYTE*)0x01104FEB = 0x00;
	//*(BYTE*)0x01104DCC = 0x00;
	//*(BYTE*)0x01104DD3 = 0x1B;//lea edx, [ebx+ebx]
	//*(BYTE*)0x01104DDF = 4;
	//*(BYTE*)0x01104DE8 = 4;

	//sub_10FE9E0
	*(DWORD*)0x010FEA0B = 0x40000000;

	//sub_10FE850
	*(BYTE*)0x010FE90E = 0x00;
	*(BYTE*)0x010FE917 = 4;

	////槽位锁
	//*(DWORD*)0x01102F93 = 0x40000000; *(BYTE*)0x01102FA2 = 0x00; // 余4
	//*(BYTE*)0x01102FB4 = 4;

	//*(DWORD*)0x0061DCD0 = 380;//冒险团右上角提示x 0x89
	//*(BYTE*)0x0061DCCE = 2;//冒险团右上角提示y 0x218
	*(DWORD*)0x0061DCD0 = -10000;//冒险团右上角提示x 0x89
	*(BYTE*)0x0061DCCE = 2;//冒险团右上角提示y 0x218

	//CNSelectCharacterModule::DrawProc_11039F0

	hook->resize(2);
	b = hook->begin();
	b++->setValue(H_DWORD, 0x01104497, 0x40000000);
	b++->setValue(H_BYTE, 0x011044E4, 4);
	thisCall2Args2 my_1104410 = (thisCall2Args2)tools_relocation_hook(0x1104410, 0x011044EE, hook);
	////sub_1104410
	*(DWORD*)0x015390AE = 0x40000000;//角色栏总数除以4等于列表行数
	*(DWORD*)0x010FF5A7 = 0x40000000;//角色栏总数除以4等于列表行
	//*(DWORD*)0x01104497 = 0x40000000;//角色栏总数除以4等于列表行数
	//*(BYTE*)0x011044E4 = 4;

	hook->resize(1);
	b = hook->begin();
	b++->setValue(H_CALL, 0x005158EC, (int)my_1104410);
	my_515540 = (thisCall2)tools_relocation_hook(0x00515540, 0x00515964, hook);
	writeCallCode((LPVOID*)0x00515A70, (LPVOID)hookSub_515540);
	delete hook;
}
#else


#define PosX    20
#define PosY    -56
#define PosY2   -78
int __fastcall DrawSelectFrame(int* thisP, int edx, int x, int y, char a4) {
	if (y == 0x127) {
		y += PosY2;
	}
	else {
		y += PosY;
	}
	return setUiComponentPos_11BEAD0(thisP, x, y + 20, a4);
}

thisCall3Args2 sub_10FD760 = (thisCall3Args2)0x10FD760;
char __fastcall hookSub2_10FD760(int* thisP, int edx, int a2, int* x, int* y) {
	if (a2 >= 4) {
		*y += PosY2;
	}
	else {
		*y += PosY;
	}
	if ((int)_ReturnAddress() == 0x01102265)
		*y += 20;
	return sub_10FD760(thisP, a2, (int)x, (int)y);
}
char __fastcall hookSub_10FD760(int* thisP, int edx, int a2, int* x, int* y) {
	if (a2 >= 4) {
		*y += PosY2;
	}
	else {
		*y += PosY;
	}
	return sub_10FD760(thisP, a2, (int)x, (int)y);
}
char __cdecl getRunPosYLinearValue(int a1, int a2, int a3, int a4) {
	if (a2 == 0x127) {
		a2 += PosY2;
	}
	else {
		a2 += PosY;
	}

	return getLinearValue_11B98C0(a1, a2, a3, a4);
}

thisCall3Args2 GameAct__play_10A4560 = (thisCall3Args2)0x10A4560;
int __fastcall hookGameAct__play_10A4560(int* thisP, int, int x, int y, int a4) {
	if (y == 0x127) {
		y += PosY2;
	}
	else {
		y += PosY;
	}
	return GameAct__play_10A4560(thisP, x, y + 20, a4);
}

forceinline void setCharacAlign4Pos(GumInterceptor* v) {
	*(DWORD*)0x01105C7A = 365;//滑动栏高度
	*(DWORD*)0x01105CC8 = 0x240;//滑动栏x
	*(BYTE*)0x01105CC6 = 50;//滑动栏y
	*(DWORD*)0x015390AE = 0x40000000;//角色栏总数除以4等于列表行数
	*(DWORD*)0x010FF5A7 = 0x40000000;//角色栏总数除以4等于列表行数
	*(DWORD*)0x01104497 = 0x40000000;//角色栏总数除以4等于列表行数
	*(BYTE*)0x011044E4 = 4;

	writeCallCode((LPVOID*)0x01102FCF, (LPVOID)hookGameAct__play_10A4560);


	writeCallCode((LPVOID*)0x01102260, (LPVOID)hookSub2_10FD760);
	writeCallCode((LPVOID*)0x011023B3, (LPVOID)hookSub_10FD760);
	writeCallCode((LPVOID*)0x0110252F, (LPVOID)hookSub_10FD760);
	writeCallCode((LPVOID*)0x01102975, (LPVOID)hookSub_10FD760);
	writeCallCode((LPVOID*)0x01102CFB, (LPVOID)hookSub_10FD760);
	writeCallCode((LPVOID*)0x01102E22, (LPVOID)hookSub_10FD760);
	//gum_interceptor_replace_fast(v, (gpointer)0x10FD760, (gpointer)hookSub_10FD760, (gpointer*)&sub_10FD760);
	writeCallCode((LPVOID*)0x010FD84F, (LPVOID)getRunPosYLinearValue);

	writeCallCode((LPVOID*)0x0110217C, (LPVOID)DrawSelectFrame);

	*(BYTE*)0x01102FB1 = 65;//栏位起始坐标x
	*(BYTE*)0x01102FAC = 127;//栏位间隔

	*(BYTE*)0x010FD523 = 65;//栏位起始坐标x
	*(BYTE*)0x010FD520 = 127;//栏位间隔

	*(BYTE*)0x01102390 = 65;//脚底魔法阵起始坐标x
	*(BYTE*)0x0110238B = 127;//脚底魔法阵间隔

	*(BYTE*)0x0110294E = 65;//名称职业起始坐标x
	*(BYTE*)0x0110294B = 127;//名称职业间隔

	*(BYTE*)0x01102DFD = 65;//鼠标拖动起始坐标x
	*(BYTE*)0x01102DF8 = 127;//鼠标拖动间隔

	*(BYTE*)0x0110250A = 65;//人物形象起始坐标x
	*(BYTE*)0x01102505 = 127;//人物形象间隔

	*(BYTE*)0x010FDD1F = 65;//鼠标起始坐标x
	*(BYTE*)0x010FDD1A = 127;//鼠标间隔
	*(BYTE*)0x010FDD39 = 125;//选中框宽度
	*(BYTE*)0x010FDD47 = 180;//选中框高度
	*(DWORD*)0x010FDD2F = 237;
	*(DWORD*)0x010FDD29 = -188;

	*(DWORD*)0x0061DCD0 = 380;//右上角提示x 0x89
	*(BYTE*)0x0061DCCE = 2;//右上角提示y 0x218

	*(DWORD*)0x01105E1A = 55;//创建按钮x 0x89
	*(DWORD*)0x01105E15 = 440;//创建按钮y 0x218
	*(DWORD*)0x01105F37 = 135;//删除按钮x 0xD8
	*(DWORD*)0x01105F32 = 440;//删除按钮y 0x218

	*(DWORD*)0x01105F8D = 256;//开始游戏按钮x 0x151
	*(DWORD*)0x01105F88 = 430;//开始游戏按钮y 0x20E

	*(DWORD*)0x011060BD = 430;//选择频道按钮x 0x1FC
	*(DWORD*)0x011060B8 = 440;//选择频道按钮y 0x218
	*(DWORD*)0x011061DD = 510;//结束始游戏按钮x 0x24B
	*(DWORD*)0x011061D8 = 440;//结束始游戏按钮y 0x218
}

forceinline void setCharacAlign4(GumInterceptor* v) {
	//sub_1102020
	*(BYTE*)0x011020FD = 0x00; //lea eax,dword ptr ds:[eax+eax]
	*(BYTE*)0x01102137 = 0x00; //lea eax,dword ptr ds:[eax+eax]
	*(BYTE*)0x01102110 = 4;

	*(BYTE*)0x0110209A = 8;
	*(BYTE*)0x011020A9 = 4;
	*(BYTE*)0x011021BF = 0x00;//lea ecx,dword ptr ds:[eax+eax]
	*(BYTE*)0x011021EC = 0x00;//lea     eax, [eax+eax]
	*(BYTE*)0x01102243 = 4;
	*(BYTE*)0x01102227 = 0x09;//lea     edx, [ecx+ecx]
	*(BYTE*)0x0110233b = 0x1B;//lea     ebx, [ebx+ebx]
	*(BYTE*)0x01102340 = 8;
	*(DWORD*)0x01102373 = 0x40000000; *(BYTE*)0x01102382 = 0x00; // 余4
	*(BYTE*)0x01102393 = 4;
	*(BYTE*)0x01102456 = 8;

	*(BYTE*)0x011024B4 = 8;
	*(DWORD*)0x011024ED = 0x40000000; *(BYTE*)0x011024FC = 0x00; // 余4
	*(BYTE*)0x0110250D = 4;
	*(BYTE*)0x011028E5 = 8;

	*(BYTE*)0x01102904 = 8;
	*(DWORD*)0x01102933 = 0x40000000; *(BYTE*)0x01102942 = 0x00; // 余4
	*(BYTE*)0x01102953 = 4;
	*(BYTE*)0x01102C70 = 8;

	*(BYTE*)0x01102CB3 = 7;
	*(DWORD*)0x01102CBB = 0x40000000; *(BYTE*)0x01102CCA = 0x00; // 余4
	*(BYTE*)0x01102CDB = 4;

	*(BYTE*)0x01102DC2 = 8;
	*(DWORD*)0x01102DE0 = 0x40000000; *(BYTE*)0x01102DEF = 0x00; // 余4
	*(BYTE*)0x01102E00 = 4;
	*(BYTE*)0x01102E32 = 0x00;
	*(BYTE*)0x01102EDC = 8;

	*(BYTE*)0x01102F6D = 8;
	*(DWORD*)0x01102F93 = 0x40000000; *(BYTE*)0x01102FA2 = 0x00; // 余4
	*(BYTE*)0x01102FB4 = 4;
	*(BYTE*)0x01102FDA = 8;

	*(BYTE*)0x01103029 = 6;
	*(BYTE*)0x01103070 = 2;
	//*(BYTE*)0x01103095 = 3;
	*(BYTE*)0x011030B7 = 7;


	//sub_10FE9E0
	*(DWORD*)0x010FEA0B = 0x40000000;// 除4

	//sub_10FD500
	*(DWORD*)0x010FD507 = 0x40000000; *(BYTE*)0x010FD516 = 0x00; // 余4

	// sub_10FDCD0
	*(BYTE*)0x010FDCF0 = 0x00;
	*(BYTE*)0x010FDCF5 = 8;
	*(DWORD*)0x010FDD01 = 0x40000000; *(BYTE*)0x010FDD10 = 0x00; // 余4
	*(BYTE*)0x010FDD22 = 4;


	//sub_10FF410
	*(BYTE*)0x010FF43A = 0x3F;//lea     eax, [edi+edi]

	//sub_10FF340 lea ebx, [eax+eax+4]
	//*(BYTE*)0x010FF376 = 0x00;
	*(BYTE*)0x010FF377 = 4;

	//sub_10FF010
	*(BYTE*)0x010FF022 = 0x00;
	*(BYTE*)0x010FF02D = 4;
	*(BYTE*)0x010FF03F = 4;
	*(BYTE*)0x010FF191 = 4;
	*(BYTE*)0x010FF1A7 = 4;


	//sub_1101C60
	*(BYTE*)0x010FF2FE = 8;
	*(DWORD*)0x010FF309 = 0x40000000;

	//sub_10FEC00
	*(BYTE*)0x010FEC5C = 4;
	*(BYTE*)0x010FED6C = 8;
	*(BYTE*)0x010FED87 = 4;
	*(BYTE*)0x010FEDB7 = 4;
	*(BYTE*)0x010FEE09 = 4;
	*(BYTE*)0x010FECE9 = 7;
	//0x011D55CD 

	//sub_10FD760
	*(BYTE*)0x010FD784 = 0x00;
	*(BYTE*)0x010FD89E = 0x00;
	*(DWORD*)0x010FD8B0 = 4;
	*(BYTE*)0x010FD8CF = 0x00;
	*(BYTE*)0x010FD8DB = 4;
	*(BYTE*)0x010FD836 = 4;


	//sub_1104750
	*(BYTE*)0x011049B6 = 0x09;
	*(BYTE*)0x01104A73 = 0x09;//lea ecx, [ecx+ecx]
	*(BYTE*)0x01104B38 = 0x00;
	*(BYTE*)0x01104FEB = 0x00;
	*(BYTE*)0x01104DCC = 0x00;
	*(BYTE*)0x01104DD3 = 0x1B;//lea edx, [ebx+ebx]
	*(BYTE*)0x01104DDF = 4;
	*(BYTE*)0x01104DE8 = 4;

	//sub_10FE9E0
	*(DWORD*)0x010FEA0B = 0x40000000;

	//sub_10FE850
	*(BYTE*)0x010FE90E = 0x00;
	*(BYTE*)0x010FE917 = 4;

	////槽位锁
	//*(DWORD*)0x01102F93 = 0x40000000; *(BYTE*)0x01102FA2 = 0x00; // 余4
	//*(BYTE*)0x01102FB4 = 4;
	setCharacAlign4Pos(v);
}

#endif

#define OldStyleCreateCharac
#ifdef OldStyleCreateCharac
#define BtnY 394

static int* textView;

forceinline void showCharacDesc(int i) {
	ScrollTextView__setParent_11CCCF0(textView, 0);
	ScrollTextView__delete_11CCB90(textView, -1);
	//ScrollTextView__setTextFont_11CCDF0(textView, *(DWORD*)(0x1B56564 + i%5 * 4));
	ScrollTextView__setText_11CCBB0(textView, *(int*)(0x1AF9CFC + i * 4), 0);
	TextViewCtrl__setStartPos_11FBC80((int*)textView[0xAF], 0);
}

forceinline void procCharacDescUi() {
	int lines = TextView__getTextLineNum_11FA750((int*)textView[0xAE]) - TextView__getMaxShowLine_541070((int*)textView[0xAE]);
	if (lines < 0) lines = 0;
	TextViewCtrl__setStartPos_11FBC80((int*)textView[0xAF], lines);
	setUiComponentParent_11BE4A0((int*)textView[0xAE], TextViewCtrl__getMainControl_11FBCD0((int*)textView[0xAF]));
}
cdeclCall5 getLinearValue_11B9EF0 = (cdeclCall5)0x11B9EF0;
thisCall1Args2 sub_10FDBD0 = (thisCall1Args2)0x10FDBD0;
int __fastcall CNSelectCharacterModule__procCharacBtn_10FE3E0(int* thisP) {
	int* btn, v, x, y, i;
	for (i = 0; ; ++i) {
		btn = (int *)thisP[0x3c + i];
		if (btn) {
			x = btn[5];
			y = btn[6];
			//v = getImageByPos_11B4BD0((int *)thisP[0x5E], ((DWORD*)0x1835F4C)[i]);
			if (IControl__IsEnable_E6E6C0(btn)) {
				if (y < BtnY) {
					int now = CNTimer__Get_11BA640(thisP + 5);
					y = BtnY - getLinearValue_11B9EF0(8, 0, now - thisP[0x68], 200, 1);
					setUiComponentPos_11BEAD0(btn, x, y, 1);
				}
			}
			else if (y > BtnY - 8) {
				int now = CNTimer__Get_11BA640(thisP + 5);
				y = BtnY - getLinearValue_11B9EF0(0, 8, now - thisP[0x68], 200, 1);
				setUiComponentPos_11BEAD0(btn, x, y, 1);
			}
			if (IControl__IsClick_11BDFC0(btn)) {
				showCharacDesc(i);
				break;
			}
		}
		if (i == 11) goto exit;
		//drawImgByXY_11B3950(*(int**)0x1B5582C, x + 27, y + 2, v);
	}
	if (thisP[0x30] != i) {
		sub_10FDBD0(thisP, i);
		thisP[0x68] = CNTimer__Get_11BA640(thisP + 5);
	}
	exit:
	procCharacDescUi();
	return i;
}

void drawWin(int* thisP, int x, int y, int w, int h) {
	int xPos = x;
	int yPos = y;
	drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x5F]);
	xPos += 11;
	for (int i = 0; i < w; ++i, xPos += 12) {
		drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x60]);
	}
	drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x61]);
	yPos += 11;

	for (int i = 0; i < h; ++i, yPos += 13) {
		xPos = x;
		drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x62]);
		xPos += 11;

		for (int j = 0; j < w; ++j, xPos += 12) {
			drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x63]);
		}

		drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x64]);
	}
	
	xPos = x;
	drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x65]);
	xPos += 11;
	for (int i = 0; i < w; ++i, xPos += 12) {
		drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x66]);
	}
	drawImgByXY_11B3950(*(int**)0x1B5582C, xPos, yPos, thisP[0x67]);
	yPos += 11;
}

thisCall1Args2 drawCreateCharacPage_10FD900;
int __fastcall hookdrawCreateCharacPage_10FD900(int* thisP, int, int a2) {
	if (a2 == thisP[0x2F]) {
		int v = getImageByPos_11B4BD0((int*)thisP[0x5E], 0);//bg
		drawImgByXY_11B3950(*(int**)0x1B5582C, 0, 0, v);
		int now = CNTimer__Get_11BA640(thisP + 5);
		v = getLinearValue_11B9EF0(0, 640, now - thisP[0x68], 500, 1);
		drawImgByXY_11B3950(*(int**)0x1B5582C, v - 640, 0, thisP[0x4A]);
		drawWin(thisP, 0x120, 0x60, 0x18, 0x13);
		v = getImageByPos_11B4BD0((int*)thisP[0x5E], 93);
		drawImgByXY_11B3950(*(int**)0x1B5582C, 0x12A, 0xBA, v);
	}
	int ret = drawCreateCharacPage_10FD900(thisP, a2);
	return ret;
}

forceinline void setCreateCharac(void) {
	//*(DWORD*)0x011063EE = 48;
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(6);
	auto b = hook->begin();
	//b++->setValue(H_DWORD, 0x010FD9B7, -100000); //TitleX
	//b++->setValue(H_BYTE, 0x010FD9B5, 20); //TitleY
	//b++->setValue(H_DWORD, 0x010FDB35, -100000); //职业描述x
	//b++->setValue(H_DWORD, 0x010FDB30, 160); //职业描述y
	b++->setValue(H_DWORD, 0x010FD923, 0x98E9);//跳过背景 title 职业图像 draw
	//b++->setValue(H_WORD, 0x010FD9A0, 0x1EEB);//跳过title draw
	b++->setValue(H_DWORD, 0x010FDB12, 0xA2E9);//跳过职业描述 draw
	b++->setValue(H_DWORD, 0x010FDA38, 0x125); //logoX
	b++->setValue(H_BYTE, 0x010FDA36, -5); //logoY
	b++->setValue(H_DWORD, 0x010FDABA, 0x12E); //难度X
	b++->setValue(H_DWORD, 0x010FDAB5, 0x6D); //难度y
	drawCreateCharacPage_10FD900 = (thisCall1Args2)tools_relocation_hook(0x10FD900, 0x010FDBCB, hook);
	delete hook;

	writeCallCode((void*)0x011041FE, CNSelectCharacterModule__procCharacBtn_10FE3E0);
}


#else
void Naked 创建角色头像位置(void) {
	//011063A2
	__asm {
		mov dword ptr[ebp - 0x64], 0
		cmp eax, 8
		jl goExit
		mov dword ptr[ebp - 0x64], 1
		goExit:
		mov ebx, 0x11063BA
			jmp ebx
	}
}

void Naked 创建角色头像位置2(void) {
	//010FE3FF
	__asm {
		mov dword ptr[ebp - 0x08], 0
		cmp eax, 8
		jl goExit
		mov dword ptr[ebp - 0x08], 1
		goExit:
		mov ecx, 0x10FE417
			jmp ecx
	}
}
forceinline void setCreateCharac(void) {
	*(DWORD*)0x011063EE = 48;
	writeJmpCode((LPVOID*)0x011063A2, (LPVOID)创建角色头像位置);
	writeJmpCode((LPVOID*)0x010FE3FF, (LPVOID)创建角色头像位置2);

	*(DWORD*)0x010FD9B7 = 450;//TitleX
	*(BYTE*)0x010FD9B5 = 20;//TitleY

	*(DWORD*)0x010FDA38 = 380;//logoX
	*(BYTE*)0x010FDA36 = 70;//logoY

	*(DWORD*)0x010FDABA = 360;//难度x
	*(DWORD*)0x010FDAB5 = 290;//难度y

	*(DWORD*)0x010FDB35 = 340;//职业描述x
	*(DWORD*)0x010FDB30 = 160;//职业描述y

	*(DWORD*)0x01106533 = 256;//创建按钮x
	*(DWORD*)0x0110652E = 430;//创建按钮y

	*(DWORD*)0x011069BD = 520;//上一页按钮x
	*(DWORD*)0x011069B8 = 440;//上一页按钮y

	*(DWORD*)0x01106585 = 235;//输入栏提示x
	*(DWORD*)0x01106580 = 395;//输入栏提示y

	*(DWORD*)0x0110665E = 240;//输入栏x
	*(DWORD*)0x01106659 = 420;//输入栏y

	*(DWORD*)0x0110677D = 260;//确定按钮x
	*(DWORD*)0x01106778 = 440;//确定按钮y

	*(DWORD*)0x0110689D = 318;//取消按钮x
	*(DWORD*)0x01106898 = 440;//取消按钮y
}
#endif // OldStyleCreateCharac
thisCall1Args2 ScrollTextView__sub_294B232 = (thisCall1Args2)0x294B232;
thisCall1Args2 ScrollTextView__sub_294252B = (thisCall1Args2)0x294252B;
thisCall1Args2 ScrollTextView__sub_29511C6 = (thisCall1Args2)0x29511C6;
thisCall1Args2 ScrollTextView__sub_2927B64 = (thisCall1Args2)0x2927B64;
void __fastcall hookCNSelectCharacterModule__init_1105860(int* thisP) {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
	auto b = hook->begin();
	//select
	b++->setValue(H_BYTE, 0x01105CC6, 50);
	b++->setValue(H_DWORD, 0x01105C7A, 365);
	b++->setValue(H_DWORD, 0x01105CC8, 0x240);
	b++->setValue(H_DWORD, 0x01105E1A, 55);
	b++->setValue(H_DWORD, 0x01105E15, 440);
	b++->setValue(H_DWORD, 0x01105F37, 135);
	b++->setValue(H_DWORD, 0x01105F32, 440);
	b++->setValue(H_DWORD, 0x01105F8D, 256);
	b++->setValue(H_DWORD, 0x01105F88, 430);
	b++->setValue(H_DWORD, 0x011060BD, 430);
	b++->setValue(H_DWORD, 0x011060B8, 440);
	b++->setValue(H_DWORD, 0x011061DD, 510);
	b++->setValue(H_DWORD, 0x011061D8, 440);
	//create
	b++->setValue(H_DWORD, 0x011064F0, 0x28 * 4);
	//短按钮
	//b++->setValue(H_BYTE, 0x01106501, 0x5A);
	//b++->setValue(H_BYTE, 0x011064FF, 0x5B);
	//b++->setValue(H_BYTE, 0x011064FD, 0x5C);
	//b++->setValue(H_DWORD, 0x011064F8, 0x90905D6A);
	//长按钮
	b++->setValue(H_BYTE, 0x01106501, 0x42);
	b++->setValue(H_BYTE, 0x011064FF, 0x43);
	b++->setValue(H_BYTE, 0x011064FD, 0x44);
	b++->setValue(H_DWORD, 0x011064F8, 0x9090456A);
	b++->setValue(H_DWORD, 0x01106923, 48004);

	b++->setValue(H_DWORD, 0x01106533, 348);//创建按钮x
	b++->setValue(H_DWORD, 0x0110652E, 334);//创建按钮y
	b++->setValue(H_DWORD, 0x011069BD, 446);//上一页按钮x
	b++->setValue(H_DWORD, 0x011069B8, 334);//上一页按钮y

#define InputX 70
#define InputY 290
	b++->setValue(H_DWORD, 0x01106585, InputX);//输入栏提示x
	b++->setValue(H_DWORD, 0x01106580, InputY);//输入栏提示y
	b++->setValue(H_DWORD, 0x0110665E, InputX + 5);//输入栏x
	b++->setValue(H_DWORD, 0x01106659, InputY + 25);//输入栏y
	b++->setValue(H_DWORD, 0x0110677D, InputX + 25);//确定按钮x
	b++->setValue(H_DWORD, 0x01106778, InputY + 45);//确定按钮y
	b++->setValue(H_DWORD, 0x0110689D, InputX + 83);//取消按钮x
	b++->setValue(H_DWORD, 0x01106898, InputY + 45);//取消按钮y
	thisCall2 my_init = (thisCall2)tools_relocation_hook(0x01105860, 0x01107275, hook);
	my_init(thisP);
	tools_release_func_memory((int)my_init);
	delete hook;

	BaseBtn__setTextEnable_11C2B70((int*)thisP[0x51], *(int*)0x01B56564, 1);
	GameTextInfo info = { 0 };
	info.color4 = 4287401100;
	info.color3 = 4290314239;
	info.color2 = 0xFFB8FFFF;
	info.color1 = 0xFF93C5DD;
	GameStrDup_411F20(info.StrInfo, GetGameText_122B260(21285));
	BaseBtn__setText_11C49F0((int*)thisP[0x51], info);
		
	setUiComponentVisable_11BE610((int*)thisP[0x3C + 8], 0);
	setUiComponentVisable_11BE610((int*)thisP[0x3C + 9], 0);
	setUiComponentVisable_11BE610((int*)thisP[0x3C + 10], 0);

	textView = (int *)newUiComponent_11B0380(0x2C0); 
	ScrollTextView__Constructor_11CCF60(textView, 270, 2048);
	ScrollTextView__setTextColor_11CCD30(textView, 0xFFBEE9F9);
	//Font_1B56564
	//Font_1B56568
	//Font_1B5656C
	//Font_1B56570
	//Font_1B56574
	ScrollTextView__setTextFont_11CCDF0(textView, *(DWORD*)0x1B56564);
	ScrollTextView__setMaxShowLine_11CCCB0(textView, 11);
	//ScrollTextView__setEndLineNum_11CCD10(textView, 5);
	//ScrollTextView_setTextAlign_296E83A(textView, 3);
	//ScrollTextView__sub_294B232(textView, 1);
	//ScrollTextView__sub_294252B(textView, 0xFF000000);
	//ScrollTextView__sub_29511C6(textView, 1);
	//ScrollTextView__sub_2927B64(textView, 0xFF000000);
	
	ScrollTextView__initScrollCtrler_11CD030(textView);
	addUiComponentChild_11BF330((int*)thisP[0x2F], (int)textView);
	setUiComponentPos_11BEAD0(textView, 0x130, 0xC0, 1);

	*(int*)0x1AF9CFC = (int)L"    鬼剑士也称‘鬼手’，左手常戴着抑制鬼神的封印锁链。\n    鬼剑士拥有神秘的鬼神力量和较强的暗属性抗性，善于用刀剑和钝器同时攻击多个敌人，是近战型职业；推荐穿戴重甲。\n    当角色达到Lv18时，可以转职为以下职业 ：\n\n        <剑魂>\n    不屈服鬼神的阻碍，穷其毕生钻研武器极限威力的鬼剑士。\n    - 善于用光剑攻击敌人。\n    - 可以把各类武器精通技能提升到极限。\n\n        <狂战士>\n    被卡赞瘟疫感染的鬼剑士。\n    - 掌握暴走和血气攻击技能。\n    - 独特的死亡抗拒可以使他们远离死亡威胁。\n\n        <鬼泣>\n    被鬼神之力魅惑，解开封印锁链的鬼剑士。\n    - 拥有极高的暗属性抗性。\n    - 能利用黑暗的力量掌握到多种鬼神技能。\n\n        <阿修罗>\n    为习得波动剑的执念，愿意牺牲自己眼睛的鬼剑士。\n    - 善于利用波动剑攻击敌人。\n    - 拥有独特的板甲专精和邪光斩技能。";
	*(int*)0x1AF9D00 = (int)L"    格斗家，注重拳、脚、肩、膝等身体部位锻练并运用它们攻击敌人的战士!\n    格斗家拥有良好的体力，善长近攻和灵活的防守。他们掌握着出神入化的体技，往往一招一式就可以强行压制对手；推荐穿戴轻甲。\n    当角色达到Lv18时，可以转职为以下职业 ：\n\n        <气功师>\n    修练念气之力的格斗家。\n    - 善于利用念气感知周围物体，能回避失明等异常状态。\n    - 多数技能可以对敌人造成光属性伤害。\n\n        <街霸>\n    崇尚实用和最有效的战斗方式的实战专家。\n    - 可以攻击倒地的敌人或把毒抹在武器上袭击对手。\n    - 精通爪类带刃武器，能抵抗剧毒。\n\n        <散打>\n    强力打击敌人身体要害，追求肉体力量巅峰的正统格斗达人。\n    - 掌握暴击技能，可以增加自身暴击率和减少敌人回避率。\n    - 可以使用拳套和指定敌人的弱点。\n\n        <柔道家>\n    拥有强大腰部力量和身体韧性的近身格斗之王。\n    - 精通多种抓取技能，可以瞬间对敌人造成致命伤害。";
	*(int*)0x1AF9D04 = (int)L"    生活在天界的神枪手，是善于利用枪械击毙远距离敌人的战士! 他们拥有高大的体格和健壮的臂膀，但视力和体力却不如人类。\n    神枪手熟悉各类枪械和重型武器的使用方法，可以把火焰、寒冰等属性附加到枪弹上，且任何时候都能迅速举枪攻击敌人；推荐穿戴皮甲。\n    当角色达到Lv18时，可以转职为以下职业 ：\n\n        <漫游枪手>\n    在天界残酷的边缘地带生存下来的神枪手。\n    - 掌握了任何姿势、任何时刻都能射击敌人的独特射击技能。\n    - 可以利用腿部向敌人发出近身攻击。\n    - 左轮枪射击速度最快的职业。\n\n        <枪炮师>\n    精通重型武器的神枪手。\n    - 善用雷射炮、狙击枪等强大威力的重型武器攻击敌人，是极具威胁性的职业。\n\n        <机械师>\n    精通机器人制造和各种机械组装的神枪手。\n    - 可以召唤出辅助战斗的机器人。\n    - 可以进行强威力的空中火力支援。\n\n        <弹药专家>\n    善于强化弹药威力的神枪手。\n    - 掌握冰冻弹、 爆炎弹等独特的弹药技能。\n    - 特殊的交叉射击技能可以攻击大范围的敌人。";
	*(int*)0x1AF9D08 = (int)L"    魔法师是使用魔法力量攻击敌人的魔族! 她们拥有俏丽可爱的外形，无需学习便可以掌握初级的魔法，能远距离攻击大范围的敌人。\n    魔法师的体力和防御力较弱，但她们掌握的多种魔法技能弥补了她们的缺陷； 推荐穿戴布甲。\n    当角色达到等级18时，可以转职为以下职业 ：\n\n        <元素师>\n    把元素之力发挥到极限的正统魔法师。\n    - 掌握自然界的冰、 火、 光、 暗四种元素的强大力量，可以远距离攻击敌人并造成极大伤害。\n\n        <召唤师>\n    能召唤出具有元素属性的精灵或达成契约的怪物，并使它们协助自身战斗的魔法师。\n    - 掌握控制召唤兽的各种技能。\n    - 同时召唤出的精灵或怪物的数量随着召唤技能等级的提升而增加。\n\n        <战斗法师>\n    为了在混乱的世界生存，不断修练且努力学习各种近战技能的魔法师。\n    - 可以将自身的魔法力量转变成各种属性的炫纹攻击敌人。\n\n        <魔道学者>\n    好奇心旺盛、 对科学有着浓厚兴趣的魔法师。\n    - 她们随身带着用链金术制造的使唤生物，并善于利用魔道学制造的武器攻击对手。\n    - 她们坚信只要破解了魔界的科学秘密，就能拥有强大的破坏力。\n    - 可以使用魔道学者特有的武器--扫把。";
	*(int*)0x1AF9D0C = (int)L"    圣职者，为铲除邪魔和普度众生而接受残酷训练的虔诚信徒。\n    圣职者受过神谕和启示，善用快速的拳头和巨兵镇压邪恶，拥有治癒伤口和驱散异常状态的技能； 推荐穿戴重甲。\n    当角色达到Lv18时，可以转职为以下职业 :\n\n        <圣骑士>\n    用诸神给予的守护能力保护队友生命的圣职者。\n    - 精通治癒、 保护、 替队友承受伤害的技能。\n    - 危急时，可以瞬间引爆神圣之力对敌人造成伤害。\n\n        <蓝拳圣使>\n    善用快速的拳击和移动的格斗技能攻击敌人的圣职者。\n    - 可以召唤出巨兵隐藏的强大魔力给予周围敌人致命伤害。\n\n        <驱魔师>\n    利用巨兵和虚祖地区的传统咒术来消灭恶魔的圣职者。\n    - 精通式神和符咒技能，可以对周边大范围内的妖魔造成致命伤害。\n    - 精通虚祖特有的自我强化技能脉轮。\n\n        <复仇者> (目前未开放)\n    因对邪恶的极度仇恨和愤怒，甘愿让自身变成恶魔的圣职者。\n    - 可以变身为恶魔，增加攻击力和移动速度，但会减少防御力且不能恢复魔法值。\n    - 能吸进敌人的血气或把自己的血转变成魔法值。\n    - 拥有多种弱化敌人的技能。";
	*(int*)0x1AF9D10 = *(int*)0x1AF9D04;
	*(int*)0x1AF9D14 = (int)L"    为了黑妖精的未来而动身离开阿拉德大陆的顶尖特务。双手持短剑、利用敏捷的移动搭配强力的剑术给予对手致命的打击。\n    - 基本是双手持短剑，就敏捷性来说没有任何职业能够与之相提并论。\n    - 拥有多种滞空专用技能、容易给予敌人致命一击。\n    --能够通过死灵术驱动召唤死者之魂出来战斗。\n    - 黑妖精拥有独特的法术，称之为忍术。\n\n        <刺客>\n    以高超的剑术搭配快速的攻击、华丽的空中攻击得意的暗夜使者\n    - 拥有独门的Y轴回避与2段跳跃\n    - 保留大师级的短剑、双剑驱使技术\n    - 绝大部分的暗夜使者技能都能够取消。\n    - 使用暗夜使者特有的连携系统，能够使出比平常更快速的连击。\n\n        <死灵术士>\n    连强大的死灵都能够压制的暗夜使者，能够驱使死灵术使敌人陷入衰弱状态。\n    - 以暗属性为主\n    - 战斗风格基本上为将敌人陷入衰弱状态导致给予的伤害大幅提升\n    - 拥有各种特殊能力的死灵是战斗时的一大助力。\n    - 能能够将强力的死灵降灵附身于自身、进而使出多样化的战斗风格。\n\n        <忍者>\n    将湘南固有的咒术与黑妖精的特性融合而成的奇特魔法称之为忍术。而穷究忍术的暗夜使者又称之为忍者\n    - 忍术的特徵为驱使各式各样的元素魔法进行攻击\n    - 忍者通过忍术能够展现非常人的移动速度和战斗方式。\n    - 由于仅能装备轻甲，防御力偏低、但倚仗精湛的剑术与敏捷的移动速度弥补这个弱点。\n\n        <影武者>\n    静悄悄的接近敌人身旁并针对其要害给予致命伤，将敌人暗杀的暗夜使者，又称为刺客。\n    - 能够进行潜伏、于敌人背后发动多种暗杀术是刺客的特徵。\n    - 降低敌人能力素质，更能大幅提升暗杀术的威力，给予其致命伤。";
	*(int*)0x1AF9D18 = *(int*)0x1AF9D00;
	ScrollTextView__delete_11CCB90(textView, -1);
	ScrollTextView__setText_11CCBB0(textView, *(int*)(0x1AF9CFC), 0);
	//*(BYTE*)0x01105CC6 = 50;//滑动栏y
	//*(DWORD*)0x01105C7A = 365;//滑动栏高度
	//*(DWORD*)0x01105CC8 = 0x240;//滑动栏x
	//*(DWORD*)0x01105E1A = 55;//创建按钮x 0x89
	//*(DWORD*)0x01105E15 = 440;//创建按钮y 0x218
	//*(DWORD*)0x01105F37 = 135;//删除按钮x 0xD8
	//*(DWORD*)0x01105F32 = 440;//删除按钮y 0x218
	//*(DWORD*)0x01105F8D = 256;//开始游戏按钮x 0x151
	//*(DWORD*)0x01105F88 = 430;//开始游戏按钮y 0x20E
	//*(DWORD*)0x011060BD = 430;//选择频道按钮x 0x1FC
	//*(DWORD*)0x011060B8 = 440;//选择频道按钮y 0x218
	//*(DWORD*)0x011061DD = 510;//结束始游戏按钮x 0x24B
	//*(DWORD*)0x011061D8 = 440;//结束始游戏按钮y 0x218


#ifdef OldStyleCreateCharac
	//thisP[v256 + 0x3C]
	int x = 20;
	for (int i = 0, *btn; i < 8; ++i) {
		btn = (int*)thisP[0x3c + i];
		setUiComponentPos_11BEAD0(btn, x + i * 75, BtnY, 1);
	}
#endif


}


void CNSelectCharacterModuleInit(void) {
	setCharacAlign4();
	setCreateCharac();
	writeCallCode((LPVOID*)0x00763746, (LPVOID)hookCNSelectCharacterModule__init_1105860);

}