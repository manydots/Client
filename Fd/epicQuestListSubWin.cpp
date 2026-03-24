#include "pch.h"
#include "common.h"
#include "epicQuestListSubWin.h"
#include "tools.h"
#include "frida-gum.h"




//1A6F774 + 0x64 任务列表
thisCall2 listInit1_1389550 = (thisCall2)0x1389550;
thisCall1Args2 listPush1_493770 = (thisCall1Args2)0x493770;
thisCall2 sub_11E0800 = (thisCall2)0x11E0800;
cdeclCall2 sub_ED0A20 = (cdeclCall2)0xED0A20;
stdCall1 isFitLevelQuest_8F6360 = (stdCall1)0x8F6360;
thisCall2 CheckBox__isCheck_11CDA40 = (thisCall2)0x11CDA40;
void checkAndAddQuest(int *thisP, int* questB, int* questE) {
	bool checkFitLevel = CheckBox__isCheck_11CDA40((int*)thisP[0x1a]);
	for (; questB != questE; ++questB) {
		int* quest = (int*)*questB;

		if (((char*)quest)[0x32A]) {//[even]活动任务
			listPush1_493770(thisP + 0x15, (int)questB);
			continue;
		}
		switch (quest[0x55])//[job change quest]特殊转换
		{
		case 1://转职
		case 2://觉醒
		case 20://副职业
			listPush1_493770(thisP + 0x15, (int)questB);
			continue;
		case 10://进化
			continue;
		}
		if (quest[0x53] == 0) {//[epic]主线任务
			if (checkFitLevel) {
				if (isFitLevelQuest_8F6360((int)quest)) {
					listPush1_493770(thisP + 0x15, (int)questB);
				}
			}
			else {
				listPush1_493770(thisP + 0x15, (int)questB);
			}
		}
	}
}

void __fastcall refreshEpicQuestData(int* thisP, int edx, char arg0) {
	listInit1_1389550(thisP + 0x15);
	int* questB = (int*)*(int*)(*(int*)0x1A6F774 + 0x68);
	int* questE = (int*)*(int*)(*(int*)0x1A6F774 + 0x6C);
	//int count = (questE - questB) / 4;
	//printf("questListCount:%d\n", count);
	checkAndAddQuest(thisP, questB, questE);
	if (arg0 && thisP[0xD]) {
		sub_11E0800((int *)thisP[0xD]);
	}
	sub_ED0A20(thisP[0xD], (int)(thisP + 0x15));
}

thisCall3Args TotalQuestSubWin__Constructor_EC7210 = (thisCall3Args)0xEC7210;
int *__fastcall CEpicQuestListSubWin__Constructor(int* thisP, int edx, int a2, int a3, int a4) {

#define DestructorB 0x00EC6870
#define DestructorE 0x00EC6891
	int destructor = tools_relocation(DestructorB, DestructorE);
	printf("relocate EpicQuestListSubWin__Destructor:0x%08x\n", destructor);

#define ProcDrawB 0x00EC5BA0
#define ProcDrawE 0x00EC5BDA
	int procDraw = tools_relocation(ProcDrawB, ProcDrawE);
	printf("relocate EpicQuestListSubWin__ProcDraw:0x%08x\n", procDraw);

#define ProcB 0x00EC71E0
#define ProcE 0x00EC7203
#define ProcB2 0x00EC67A0
#define ProcE2 0x00EC6862
	int proc = tools_relocation2(ProcB, ProcE, ProcB2, ProcE2);
	printf("relocate EpicQuestListSubWin__Proc:0x%08x\n", proc);

#define OnOpenB 0x00EC7120
#define OnOpenE 0x00EC71DC
	int onOpen = tools_relocation(OnOpenB, OnOpenE);
	printf("relocate EpicQuestListSubWin__OnOpen:0x%08x\n", onOpen);

#define OnCloseB 0x00EC5A50
#define OnCloseE 0x00EC5A87
	int onClose = tools_relocation(OnCloseB, OnCloseE);
	printf("relocate EpicQuestListSubWin__OnClose:0x%08x\n", onClose);

#define OnVisableChangeB 0x00EC59F0
#define OnVisableChangeE 0x00EC5A4F
	int onVisableChange = tools_relocation(OnVisableChangeB, OnVisableChangeE);
	printf("relocate EpicQuestListSubWin__OnVisableChange:0x%08x\n", onVisableChange);

#define SubEC6590B 0x00EC6590
#define SubEC6590E 0x00EC66D2
	int sub_EC6590 = tools_relocation(SubEC6590B, SubEC6590E);
	printf("relocate sub_EC6590B:0x%08x\n", sub_EC6590);

#define SubEC6530B 0x00EC6530
#define SubEC6530E 0x00EC6587
	int sub_EC6530 = tools_relocation(SubEC6530B, SubEC6530E);
	printf("relocate sub_EC6530:0x%08x\n", sub_EC6530);

#define DrawQuestItemWithDungeonB 0x00ED1330 
#define DrawQuestItemWithDungeonE 0x00ED1884

	int drawQuestItemWithDungeon = tools_relocation(DrawQuestItemWithDungeonB, DrawQuestItemWithDungeonE);
	printf("relocate drawQuestItemWithDungeon:0x%08x\n", drawQuestItemWithDungeon);

	int* typeInfo = (int*)malloc(sizeof(void *) * 12);
	if (typeInfo == NULL) {
		printf("malloc vtable memory error!\n");
		return NULL;
	}

	typeInfo[0] = 0x190000C;
	typeInfo[1] = (int)destructor;
	typeInfo[2] = (int)procDraw;
	typeInfo[3] = (int)proc;
	typeInfo[4] = (int)onOpen;
	typeInfo[5] = (int)onClose;
	typeInfo[6] = 0xE86310;
	typeInfo[7] = 0xE86350;
	typeInfo[8] = 0xE86390;
	typeInfo[9] = (int)onVisableChange;
	typeInfo[10] = 0xEC5C40;
	typeInfo[11] = 0x6DEC90;
	int *subWin = (int *)TotalQuestSubWin__Constructor_EC7210(thisP, edx, a2, 0, 0);
	*subWin = (int)&typeInfo[1];

	*(DWORD*)(drawQuestItemWithDungeon + (0x00ED14EF - DrawQuestItemWithDungeonB)) = 0x00009AE9;
	*(DWORD*)(drawQuestItemWithDungeon + (0x00ED172A - DrawQuestItemWithDungeonB)) = 0x0000BCE9;
	*(BYTE*)(drawQuestItemWithDungeon + (0x00ED17F8 - DrawQuestItemWithDungeonB)) = 0xB4;
	*(BYTE*)(drawQuestItemWithDungeon + (0x00ED15B3 - DrawQuestItemWithDungeonB)) = 0xB4;
	*(BYTE*)(drawQuestItemWithDungeon + (0x00ED159B - DrawQuestItemWithDungeonB)) = 0xB4;
	
	((int***)subWin)[0x0D][0xAE][0x3] = drawQuestItemWithDungeon;

#define CallAddr 0x00EC71B1
	writeCallCode((LPVOID*)(onOpen + (CallAddr - OnOpenB)), (PVOID)refreshEpicQuestData);

#define CallAddr2 0x00EC6622
	writeCallCode((LPVOID*)(sub_EC6590 + (CallAddr2 - SubEC6590B)), (PVOID)refreshEpicQuestData);
	
#define CallAddr3 0x00EC7160
	writeCallCode((LPVOID*)(onOpen + (CallAddr3 - OnOpenB)), (PVOID)sub_EC6590);

#define CallAddr4 0x00EC657D
	writeCallCode((LPVOID*)(sub_EC6530 + (CallAddr4 - SubEC6530B)), (PVOID)refreshEpicQuestData);

	writeCallCode((LPVOID*)(proc + 0xBB), (PVOID)sub_EC6530);
	writeCallCode((LPVOID*)(proc + 0xDE), (PVOID)sub_EC6590);

	*(BYTE*)0x00E76DE6 = 0xEB;
	return subWin;
}

