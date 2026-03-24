#include "pch.h"
#include "common.h"
#include "currentQuestListWin.h"
#include "epicQuestListSubWin.h"
#include "questDetailWin.h"
#include "oldQuestWin.h"
#include "frida-gum.h"
#include "tools.h"

thisCall2 getQuestWin_E72230 = (thisCall2)0xE72230;

int __fastcall hookSetQuestDetailData_ECCBF0(int* thisP, int edx, int a2, unsigned int a3) {
    if (!isWinShowing_E71770(*(int**)0x1A6F750, QuestDetailWinId)) {
        showWin_E77470(*(int**)0x1A6F750, QuestDetailWinId, 0, 0);
    }
    int* focusWin = (int*)MouseSelectWinUiObj;
    int closeWin1 = 0, closeWin2 = 0, x, y;
    if (!focusWin) goto exit;

    switch (focusWin[2]) {
    case 20://任务手册窗口
        closeWin1 = 21;
        closeWin2 = CurrentQuestListWinId;
        break;
    case 21://npc委托的任务窗口
        closeWin1 = 20;
        closeWin2 = CurrentQuestListWinId;
        break;
    case CurrentQuestListWinId://进行中的任务窗口
        closeWin1 = 20;
        closeWin2 = 21;
        break;
    default: goto exit;
    }
    if (closeWin1 && isWinShowing_E71770(*(int**)0x1A6F750, closeWin1)) {
        closeWin_E745B0(*(int**)0x1A6F750, closeWin1, 0xFFFFFFFF, 0);
    }
    if (closeWin2 && isWinShowing_E71770(*(int**)0x1A6F750, closeWin2)) {
        closeWin_E745B0(*(int**)0x1A6F750, closeWin2, 0xFFFFFFFF, 0);
    }
    x = BasePopupWin__getPosX_EF65C0(focusWin);
    y = BasePopupWin__getPosY_EF65D0(focusWin);
    focusWin = getQuestDetailWin();
    if (!focusWin) goto exit;
    if (x > 270) setUiComponentPos_11BEAD0((int*)focusWin[3], x - 280, y, 0);
    else  setUiComponentPos_11BEAD0((int*)focusWin[3], x + 280, y, 0);

exit:
    QuestDetailWin_setQuestData(a2, a3);
    return 1;
}

int __fastcall hookSetEvenQuestDetailData_EC58F0(int* thisP, int edx, int a2) {
    if (!isWinShowing_E71770(*(int**)0x1A6F750, QuestDetailWinId) ) {
        showWin_E77470(*(int**)0x1A6F750, QuestDetailWinId, 0, 0);
    }
    
    int closeWin1 = 21, closeWin2 = 22, x, y;
    if (closeWin1 && isWinShowing_E71770(*(int**)0x1A6F750, closeWin1) ) {
        closeWin_E745B0(*(int**)0x1A6F750, closeWin1, 0xFFFFFFFF, 0);
    }
    if (closeWin2 && isWinShowing_E71770(*(int**)0x1A6F750, closeWin2)) {
        closeWin_E745B0(*(int**)0x1A6F750, closeWin2, 0xFFFFFFFF, 0);
    }
    
    int* focusWin = (int*)getQuestWin_E72230(*(int**)0x1A6F750);
    x = BasePopupWin__getPosX_EF65C0(focusWin);
    y = BasePopupWin__getPosY_EF65D0(focusWin);
    focusWin = getQuestDetailWin();
    if (!focusWin) goto exit;
    if (x > 270) setUiComponentPos_11BEAD0((int*)focusWin[3], x - 280, y, 0);
    else  setUiComponentPos_11BEAD0((int*)focusWin[3], x + 280, y, 0);

exit:
    QuestDetailWin_setEvenQuestData(a2);
    return 1;
}

thisCall2Args2 QuestListWin__OnOpen_ED0660 = (thisCall2Args2)0xED0660;
int __fastcall hookQuestListWin__OnOpen_ED0660(int* thisP, int edx, int a2, int a3) {
    int ret = QuestListWin__OnOpen_ED0660(thisP, a2, a3);
    setUiComponentPos_11BEAD0((int*)thisP[0x03], 70, 120, 0);
    setUiComponentVisable_11BE610((int*)thisP[0x64], 0);
    return ret;
}

thisCall2Args2 RequestQuestWin__OnOpen_EC85B0 = (thisCall2Args2)0xEC85B0;
int __fastcall hookRequestQuestWin__OnOpen_EC85B0(int* thisP, int edx, int a2, int a3) {
    int ret = RequestQuestWin__OnOpen_EC85B0(thisP, a2, a3);
    setUiComponentPos_11BEAD0((int*)thisP[0x03], 70, 120, 0);
    return ret;
}

thisCall2 getCurrentQuestSubWin_ECEF20 = (thisCall2)0xECEF20;
int __fastcall hookGetCurrentQuestSubWin_ECEF20(int* thisP) {
    //if (thisP && (*thisP == 0x15BE5EC || *thisP == 0x15BE454)) return thisP[0x6D];//pk场兼容
    return getCurrentQuestSubWin();
}

int __fastcall fixPvpGetData_ECEF20(int* thisP) {
    return thisP[0x6D];
}


thisCall1Args2 showNewQuestWin_E7C6A0 = (thisCall1Args2)0xE7C6A0;
int __fastcall hookShowNewQuestWin_E7C6A0(int* thisP, int, char a2) {
    if (a2) {
        if (!isWinShowing_E71770(*(int**)0x1A6F750, CurrentQuestListWinId) )
            showWin_E77470(*(int**)0x1A6F750, CurrentQuestListWinId, 0, 0);
    }
    else {
        if (!isWinShowing_E71770(*(int**)0x1A6F750, 20))
            showWin_E77470(*(int**)0x1A6F750, 20, 0, 0);
    }
    return 0;
}


int __fastcall hookGetQuestWin_E72230(int* thisP) {
    if (isWinShowing_E71770(*(int**)0x1A6F750, QuestDetailWinId)) {
        closeWin_E745B0(*(int**)0x1A6F750, QuestDetailWinId, 0xFFFFFFFF, 0);
    }
    return 0;
}

thisCall2Args2 sub_EC5D60 = (thisCall2Args2)0xEC5D60;
thisCall1Args2 sub_8FB130 = (thisCall1Args2)0x8FB130;
int __fastcall hookSub_8FB130(int* thisP, int, int questObj) {
    int v5;
    __asm mov v5, esi;
    int ret = sub_8FB130(thisP, questObj);
    if (ret) {
        int** questWin = (int**)getQuestWin_E72230(*(int**)0x1A6F750);
        if (questWin && !sub_EC5D60(questWin[0x6C], v5, 1))
            showWin_E77470(*(int**)0x1A6F750, 0x93, v5, 1);
    }
    return ret;
}

thisCall2 QuestListWin__init_ED0120 = (thisCall2)0xED0120;
int __fastcall hookQuestListWin__init_ED0120(int* thisP) {
    int ret = QuestListWin__init_ED0120(thisP);
    setUiComponentVisable_11BE610((int *)thisP[0x63], 0);
    return ret;
}
thisCall3Args2 TimeQuestSubWin__Constructor_4FE6B0 = (thisCall3Args2)0x4FE6B0;
int __fastcall hookTimeQuestSubWin__Constructor_4FE6B0(int* thisP, int, int a2, int a3, int a4) {
    int ret = TimeQuestSubWin__Constructor_4FE6B0(thisP, a2, a3, a4);
    thisCall2 onClose = (thisCall2)Vtable(ret, 0x10);
    onClose((int *)ret);
    return ret;
}

int __fastcall fixEventQuestSubWinEmptyDraw(int* thisP, int edx, int x, int y, int* imgAddr) {
    return innerDrawImg_11DB180(imgAddr, x - 270, y + 25, (int)thisP);
}

void oldQuestWinInit() {
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0xECCBF0, (gpointer)hookSetQuestDetailData_ECCBF0, (gpointer*)&setQuestDetailData_ECCBF0);
    gum_interceptor_replace_fast(v, (gpointer)0xEC58F0, (gpointer)hookSetEvenQuestDetailData_EC58F0, (gpointer*)&setEventQuestDetailData_EC58F0);
    gum_interceptor_replace_fast(v, (gpointer)0xED0660, (gpointer)hookQuestListWin__OnOpen_ED0660, (gpointer*)&QuestListWin__OnOpen_ED0660);
    gum_interceptor_replace_fast(v, (gpointer)0xEC85B0, (gpointer)hookRequestQuestWin__OnOpen_EC85B0, (gpointer*)&RequestQuestWin__OnOpen_EC85B0);
    gum_interceptor_replace_fast(v, (gpointer)0xECEF20, (gpointer)hookGetCurrentQuestSubWin_ECEF20, (gpointer*)&getCurrentQuestSubWin_ECEF20);
    gum_interceptor_replace_fast(v, (gpointer)0xE7C6A0, (gpointer)hookShowNewQuestWin_E7C6A0, (gpointer*)&showNewQuestWin_E7C6A0);

    //接受任务窗口
    *(BYTE*)0x00EC83EC = 20;
    writeNopCode((void*)0x00EC817E, 3);//屏蔽委托任务窗口的右边栏显示
    writeNopCode((void*)0x00EC7F0E, 9);
    //writeNopCode((void*)0x00EC812F, 2);//屏蔽委托任务窗口点击处理
    ////任务列表窗口
    *(BYTE*)0x00ED016F = 20;
    writeNopCode((void*)0x00ECF692, 3);//屏蔽任务窗口的右边栏显示
    *(BYTE*)0x00ECF5AA = 0xE9;//跳过qp信息draw
    *(DWORD*)0x00ECF5AB = 0x84;

    //打开任务手册不要打开qp技能窗口，qp技能窗口改成进行中任务窗口
    *(BYTE*)0x00ECFC71 = 0xEB;
    *(BYTE*)0x00E7C6AA = 0xEB;
    writeNopCode((void*)0x00ED08DA, 17);

    //writeNopCode((void*)0x00ECFA18, 31);
    //writeNopCode((void*)0x00ECFA66, 21);
    writeNopCode((void*)0x00ECFA2A, 13);
    writeNopCode((void*)0x00ECFA6E, 13);

    //*(BYTE*)0x00EC67E9 = 0xeb;//writeNopCode((void*)0x00ED0970, 2);//屏蔽任务手册窗口点击处理
    //*(DWORD*)0x00ECA0B3 = 0x0000F0E9;//writeNopCode((void*)0x00ED0985, 2);//屏蔽进行中的任务窗口点击处理

    *(DWORD*)0x00ECFD50 = 42390;//主线任务
    *(DWORD*)0x00ECFD33 = 42390;
    *(DWORD*)0x00ED02FC = 42325;//主线
    writeCallCode((LPVOID*)0x00ED0716, (PVOID)CEpicQuestListSubWin__Constructor);

    //点击活动叹号 弹出完成任务窗口
    *(WORD*)0x004E645B = 0x2EEB;

    //点击npc 弹出完成任务窗口
    writeNopCode((void*)0x00EC8D7B, 7);
    *(DWORD*)0x007F2B34 = 0x5608758B; *(WORD*)0x007F2B38 = 0x4EEB;
    *(BYTE*)0x00ED08F5 = 0;

    //点击npc头顶叹号 弹出完成任务窗口
    *(DWORD*)0x007F6F60 = 0x9050EB57;

    *(WORD*)0x0EC4A07 = 0x5690;
    writeCallCode((LPVOID*)0x00EC4A09, (PVOID)0xEC58F0);
    *(WORD*)0x00EC4A0E = 0x24EB;

    *(BYTE*)0x0070F59F = 0xEB;//修复放弃任务闪退
    *(BYTE*)0x004EBCD7 = 0;//修复新主线任务活动按钮点击问题

    
    writeCallCode((LPVOID*)0x00FB7D4C, (PVOID)hookGetQuestWin_E72230);//修复点击npc对话窗口完成任务时关闭任务详细窗口
    
    *(BYTE*)0x00E797AF = 1; //esc不同时关闭npc聊天窗口，任务详细窗口

    //任务提示窗口点击弹出进行中的任务窗口
    *(BYTE*)0x00FC5FCA = 1;
    *(WORD*)0x00FC5FFB = 0x0CEB;
    *(WORD*)0x00FC6025 = 0x0CEB;
    *(BYTE*)0x008F7E44 = 1;
    *(WORD*)0x008F7E57 = 0x14EB;
    

    //修复任务完成触发后续任务
    *(BYTE*)0x00FC748F = 0;
    *(BYTE*)0x00FC7357 = 0;
    *(BYTE*)0x0063EA02 = 0;
    *(BYTE*)0x0063EB3a = 0;
    //*(BYTE*)0x007F6F54 = 0;
    //*(BYTE*)0x007F2B2e = 0;
   
        
  /*  writeNopCode((void*)0x00FC737B, 5); 
    writeNopCode((void*)0x0063EA26, 5);*/

    //隐藏时间之门任务tag
    writeNopCode((void*)0x00ED051F, 6);
    writeCallCode((void*)0x00F09EA9, hookQuestListWin__init_ED0120);
    writeCallCode((void*)0x00ED0807, hookTimeQuestSubWin__Constructor_4FE6B0);

    *(WORD*)0x00ECC260 = 0x20EB;//开启任务追钟时不关闭其他任务窗口
    writeNopCode((void*)0x00EC482E, 5);//事件子窗口空条目时的绘制
    //std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(4);
    ////hook->resize(4);
    //auto b = hook->begin();
    //b++->setValue(H_CALL, 0x0108A9E5, (int)fixEventQuestSubWinEmptyDraw);
    //thisCall2 draw = (thisCall2)tools_relocation_hook(0x0108A960, 0x0108A9F7, hook);
    //writeCallCode((void*)0x00EC482E, draw);
    ////writeCallCode((void*)0x0108A9E5, fixEventQuestSubWinEmptyDraw);
    ////writeNopCode((void*)0x00EC482E, 5);//事件子窗口空条目时的绘制
    //delete hook;

    *(DWORD*)0x015BE6D0 = (int)fixPvpGetData_ECEF20;
    *(DWORD*)0x015BE538 = (int)fixPvpGetData_ECEF20;
}