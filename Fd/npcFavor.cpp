#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"

void npcFavor_OnNotiClearQuest(void) {

}

void npcFavor_OnFinshQuest(void) {

}

void npcFavor_CNTownModule_onEnterModuleCb(int* thisP, int a2) {

}

void npcFavor_CNTownModule__onExitModuleCb(int* thisP, int a2) {

}

thisCall1Args2 myMakePkg_1132930;
stdCall mySendPkg_1132A90;

void npcFavor_CNMainGameModule_onEnterModuleCb(int* thisP, int a2) {
	DPRINTF("npcFavor_CNMainGameModule_onEnterModuleCb:%d\n", a2);

	BYTE push = *(BYTE*)0x1132930;
	DWORD cmd = *(DWORD*)0x1132931;
	if (cmd != 0xec83ec8b) {
		DWORD v;
		VirtualProtect((LPVOID)0x1132930, 5, PAGE_EXECUTE_READWRITE, &v);
		*(BYTE*)0x1132930 = 0x55;
		*(DWORD*)0x1132931 = 0xec83ec8b;
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)0x1132930, 5);
		makePkg_1132930(*(int**)0x1AFB37C, 276);
		*(BYTE*)0x1132930 = push;
		*(DWORD*)0x1132931 = cmd;
		FlushInstructionCache(GetCurrentProcess(), (LPVOID)0x1132930, 5);
		VirtualProtect((LPVOID)0x1132930, 5, v, &v);
	}
	else {
		makePkg_1132930(*(int**)0x1AFB37C, 276);
	}
	mySendPkg_1132A90();

}

thisCall3Args2 NpcDialogWin__setNpcGifEnable_FB4AB0 = (thisCall3Args2)0xFB4AB0;
int __fastcall fixNpcFavorBtnImp(int* thisP) {
	int* villageAttackedReward = ((int***)getCNModule_706410())[0x2B][0x53];
	if (RBYTE(villageAttackedReward, 0xB4)) return 0; //攻城失败

	if (((BYTE*)0x1A83540)[thisP[0xE6]]) {
		if (thisP[0xEA] >= 3 && thisP[0xEA] <= 5) {
			return 0;
		}
		if (*(DWORD*)0x1A3E38C != 8) NpcDialogWin__setNpcGifEnable_FB4AB0(thisP, 0, 1, 1);
		else NpcDialogWin__setNpcGifEnable_FB4AB0(thisP, 1, 1, 0);
		return 1;
	}
	return 0;
	// NpcDialogWin__setNpcGifEnable_FB4AB0(thisP, 0, 1, 1);
}

void Naked fixNpcFavorBtn(void) {
	//00FC180A
	__asm {
		cmp edi, 3
		jz goPass
		cmp edi, 0
		jnz goExit
		mov ecx, esi
		call fixNpcFavorBtnImp
		cmp eax, 1
		jnz goExit
		mov ecx, 0xFC190E
		jmp ecx
		goPass :
		mov eax, 0xFC180F
		jmp eax
		goExit :
		mov eax, 0xFC1832
		jmp eax
	}
}

cdeclCall1 getNpcCurrentFavorExp_7F2120 = (cdeclCall1)0x7F2120;
void __fastcall fixNpcFavorFaceImgImp(int* thisP, int pos) {
	if (thisP[0xE9] == 0xA) {
		//赛利亚的祝福活动face
		thisP[0x11A] = thisP[0x150];
		thisP[0xE7] = 4;
		return;
	}
	else if (pos == -1) return;
	int* villageAttackedReward = ((int***)getCNModule_706410())[0x2B][0x53];
	if (RBYTE(villageAttackedReward, 0xB4)) {//攻城失败
		thisP[0x11A] = thisP[0x150];
		thisP[0xE7] = pos * 3 + 0;
		return; 
	}
	int npcId = thisP[0xE6];
	int exp = getNpcCurrentFavorExp_7F2120(npcId);
	WORD* lvExp = (WORD*)(thisP + 0x7B);
	int lv = 0;
	if (exp >= lvExp[2]) lv = 2;
	else if (exp >= lvExp[1]) lv = 1;
	else if (exp >= lvExp[0]) lv = 0;
	else return;
	thisP[0x11A] = thisP[0x150];
	thisP[0xE7] = pos * 3 + lv;
}

void Naked fixNpcFavorFaceImg(void) {
	//00FBD6A3
	__asm {
		mov ecx, esi
		mov edx, eax
		call fixNpcFavorFaceImgImp
		mov ecx, 0xFBD6E8
		jmp ecx
	}
}

thisCall1Args2 NpcDialogWin__ProcDraw_FBB730 = (thisCall1Args2)0xFBB730;
void __fastcall hookNpcDialogWin__ProcDraw_FBB730(int* thisP, int,  int a2) {
	 NpcDialogWin__ProcDraw_FBB730(thisP, a2);
	 if (thisP[0xE9] != 0) return ;
	 int npcId = thisP[0xE6];
	 if (!((BYTE*)0x1A83540)[npcId]) return ;//支持好感度npc
	 int exp = getNpcCurrentFavorExp_7F2120(npcId);
	 WORD* lvExp = (WORD*)(thisP + 0x7B);
	 int lv = 0;
	 if (exp >= lvExp[2]) lv = 3;
	 else if (exp >= lvExp[1]) lv = 2;
	 else if (exp >= lvExp[0]) lv = 1;
	 //this[0x9B] mood
	 int x = 0x160;
	 int y = 0x146;
	 if (thisP[0xEA] >= 3 && thisP[0xEA] <= 5) {
		 x = 0xA0;
		 y = 0x4B;
	 }
	 static int* profileImg = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface2/profile/profile.img");
	 if (!profileImg) return ;
	 int v = getImageByPos_11B4BD0(profileImg, 18);//bg
	 drawImgByXY_11B3950(*(int**)0x1B5582C, x + 27, y + 2, v);

	 float precent = (float)exp / lvExp[lv];
	 //printf("[%d, %d, %d, %d %f]\n", lv, exp, lvExp[lv], thisP[0x9B], precent);
	 setGameCanvasSize_6FD880(0, 0, x + 27 + precent * 57 , 480);
	 v = getImageByPos_11B4BD0(profileImg, 17);
	 if (v) drawImgByXY_11B3950(*(int**)0x1B5582C, x + 27, y + 2, v);
	 resetGameCanvasSize_6FD8D0();

	 WORD format[16];
	 TextFormat__init_11C9510((int*)format);
	 ((int*)format)[2] = *(DWORD*)0x01B56564;
	 format[1] = 12;
	 format[3] = TEXT_ALIGN_CENTER;//左对齐
	 drawTextStart_12115B0(*(int**)0x1B5582C,  (int)format);
	 switch (lv){
	 case 0:
		 drawText_1211C30(*(int**)0x1B5582C,  x, y, 0xFFEDD568, (int)L"冷淡");
		 break;
	 case 1:
		 drawText_1211C30(*(int**)0x1B5582C,  x, y, 0xFF1EFF96, (int)L"普通");
		 break;
	 case 2:
		 drawText_1211C30(*(int**)0x1B5582C,  x, y, 0xFF0092FF, (int)L"好感");
		 break;
	 case 3:
		 drawText_1211C30(*(int**)0x1B5582C,  x, y, 0xFF00F2FF, (int)L"信赖");
		 break;

	 }
	 drawTextEnd_12115D0(*(int**)0x1B5582C);
}

void __cdecl procNoti194NpcFavor_7382B0(int a1, int a2) {
	BYTE buf[320];
	WORD size = PacketBuf_get_binary((int)buf);

	//printf("procNoti194NpcFavor_7382B0 %d\n", size);
	if (!size) return;
	int* ServerFavorExpTable = (int*)0x1A801B0;
	int* ServerFavorMoodTable = (int*)0x1A812E0;
	WORD npcId, favor;
	BYTE mood;
	for (int i = 0; i < size; i += 5) {
		npcId = *(WORD*)(buf + i);
		favor = *(WORD*)(buf + i + 2);
		mood = *(BYTE*)(buf + i + 4);
		if(favor)
			ServerFavorExpTable[npcId] = favor;
		ServerFavorMoodTable[npcId] = mood;
		//printf("setFavor %d %d %d\n",npcId, favor, mood);
	}
}

void __cdecl procNoti195NpcMood_7382B0(int a1, int a2) {
	WORD size = PacketBuf_get_short((int)&size);
	DPRINTF("procNoti195NpcMood_7382B0 %d\n", size);
	if (!size) return;
	int* ServerFavorMoodTable = (int*)0x1A812E0;
	WORD npcId;
	BYTE mood;
	for (int i = 0; i < size; ++i) {
		npcId = 0;
		PacketBuf_get_short((int)&npcId);
		mood = 0;
		PacketBuf_get_byte((int)&mood);
		ServerFavorMoodTable[npcId] = mood;
		DPRINTF("setMood %d %d\n", npcId, mood);
	}
}

void __fastcall procCmd225GiveGiftToNpc_getDataImp(int* ebp) {
	struct {
		DWORD key;
		BYTE isFavorEvent;
		BYTE favorType;
		BYTE favorExcp;
		BYTE favorValueSta;
		BYTE favorM;
		BYTE bannerType;
		BYTE favorLevelSta;
		BYTE eventFavorDialogPos;
		DWORD v36;
		DWORD npcId;
		DWORD itemSlot;
		DWORD favorV;
		DWORD itemCount;
		DWORD npcRetGiftItemId;
		DWORD npcRetGiftItemCount;
		DWORD itemId;
	}binaryData;

	int size = PacketBuf_get_binary((int)&binaryData);

	WBYTE(ebp, 0x0C + 3, binaryData.isFavorEvent);//isFavorEvent
	WBYTE(ebp, -0x01, binaryData.favorType);//favorType
	WBYTE(ebp, -0x02, binaryData.favorExcp);//favorExcp
	WBYTE(ebp, -0x03, binaryData.favorValueSta);//favorValueSta
	WBYTE(ebp, -0x04, binaryData.favorM);//favorM
	WBYTE(ebp, -0x05, binaryData.bannerType);//bannerType
	WBYTE(ebp, -0x06, binaryData.favorLevelSta);//favorLevelSta
	WBYTE(ebp, -0x07, binaryData.eventFavorDialogPos);//eventFavorDialogPos
	WDWORD(ebp, -0x08, binaryData.v36);//v36
	WDWORD(ebp, -0x0C, binaryData.npcId);//npcId
	WDWORD(ebp, -0x10, binaryData.itemSlot);//itemSlot
	WDWORD(ebp, -0x14, binaryData.favorV);//favorV
	WDWORD(ebp, -0x18, binaryData.itemCount);//itemCount
	WDWORD(ebp, -0x1C, binaryData.npcRetGiftItemCount);//npcRetGiftItemCount
	WDWORD(ebp, -0x20, binaryData.npcRetGiftItemId );//npcRetGiftItemId
	WDWORD(ebp, -0x24, binaryData.itemId);//itemId
}

void Naked procCmd225GiveGiftToNpc_getData(void) {
	//0x00715391
	__asm {
		push esi
		push edi
		mov ecx, ebp
		call procCmd225GiveGiftToNpc_getDataImp
		pop edi
		pop esi
		xor ebx, ebx
		mov eax, 0x00715469
		jmp eax
	}
}

//1A83540

int __fastcall NpcDialogWin__procNormalDialog_FB86C0(int* thisP, int , int* dialogVector){
	int *villageAttackedReward = ((int ***)getCNModule_706410())[0x2B][0x53];
	if (!RBYTE(villageAttackedReward, 0xB4)) {//攻城失败
		return ((thisCall1Args2)0xFB86C0)(thisP, (int)dialogVector);
	}
	int* begin = (int *)dialogVector[1], * end = (int*)dialogVector[2];
	int dialogVectorSize = ((int)end - (int)begin) / 0x60;
	if (!dialogVectorSize) return 0;
	int dialog[24];
	for (int i = 0; i < dialogVectorSize; ++i) {
		((thisCall1Args2)0x908FA0)(dialog, (int)&begin[0x18 * i]);
		if (RBYTE(dialog, 0x28)) {
			((thisCall2)0x7F2CC0)(dialog);
			return ((thisCall1Args2)0xFB86C0)(thisP, (int)dialogVector);
		}
		else if (!((stdCall1)0xFB58A0)((int)dialog)) {
			goto next;
		}
		else if (dialog[9] != 2) {
			goto next;
		}
		GameVector1__PushBack_493770(thisP + 0x102, (int) & i);
		next:
		((thisCall2)0x7F2CC0)(dialog);
	}
	if ((thisP[0x104] - thisP[0x103] / 4) == 0) {
		return ((thisCall1Args2)0xFB86C0)(thisP, (int)dialogVector);
	}
	return dialogVectorSize;

}

thisCall1Args2 isNpcRoleType_71EC50 = (thisCall1Args2)0x71EC50;
BYTE __fastcall hookIsNpcRoleType_71EC50(int* thisP,int, int a2) {
	int retAddr = (int)_ReturnAddress();
	if (retAddr < 0x1011770 || retAddr > 0x010130F9 || thisP[0] >= 1000) return isNpcRoleType_71EC50(thisP, a2);
	int* villageAttackedReward = ((int***)getCNModule_706410())[0x2B][0x53];
	if (RBYTE(villageAttackedReward, 0xB4)) return 0;//攻城失败
	return isNpcRoleType_71EC50(thisP, a2);
}

void npcFavorInit(void) {
	writeCallCode((void*)0x00FBEFCD, NpcDialogWin__procNormalDialog_FB86C0);//修复攻城失败npc 对话框
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x71EC50, (gpointer)hookIsNpcRoleType_71EC50, (gpointer*)&isNpcRoleType_71EC50);

	*(DWORD*)0x014FFB82 = 0;
	writeNopCode((void*)0xFB4B14, 0x00FB4B32 - 0xFB4B14);
	writeJmpCode((void*)0x00FC180A, fixNpcFavorBtn);
	writeJmpCode((void*)0x00FBD6A3, fixNpcFavorFaceImg);

	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(4);
	hook->resize(1);
	auto b = hook->begin();
	b++->setValue(H_JUMP, 0x00715391, (int)procCmd225GiveGiftToNpc_getData);
	cdeclCall4 procCmd225GiveGiftToNpc_715380 = (cdeclCall4)tools_relocation_hook(0x715380, 0x0071579D, hook);
	//*(DWORD*)0x0072C113 = (int)procCmd225GiveGiftToNpc_715380;
	*(DWORD*)0x0072C113 = (int)procCmd225GiveGiftToNpc_715380;
	//writeJmpCode((void*)0x00715391, procCmd225GiveGiftToNpc_getData);

	//修复送礼物弹窗
	
	*(DWORD*)0x00FB5390 = 0x1A5;
	*(DWORD*)0x00FB6E37 = 0;
	*(BYTE*)0x00FB6E60 = 0x89;  *(DWORD*)0x00FB6E61 = 0x32EBBC75;

	*(DWORD*)0x018233BC = (int)hookNpcDialogWin__ProcDraw_FBB730;
	
	/*GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0xFBB730, (gpointer)hookNpcDialogWin__ProcDraw_FBB730, (gpointer*)&NpcDialogWin__ProcDraw_FBB730);*/

	*(DWORD*)0x00758062 = (int)procNoti194NpcFavor_7382B0;
	*(DWORD*)0x007580C7 = (int)procNoti195NpcMood_7382B0;
	myMakePkg_1132930 = (thisCall1Args2)tools_relocation(0x1132930, 0x01132964);
	mySendPkg_1132A90 = (stdCall)tools_relocation(0x1132A90, 0x01133119);

	delete hook;
	//test_tiny_aes();
	//testaes();
	//testtea();
}