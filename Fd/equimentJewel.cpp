#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"

#define EQUIMENT_AVATAR 0
#define EQUIMENT_ONLY   1
#define TYPE            EQUIMENT_AVATAR

cmdRecvProc Cmd209RecvProc = (cmdRecvProc)0x7157A0;
thisCall1Args2 addSlotInfo_7946D0 = (thisCall1Args2)0x7946D0;

static int* selectBanner;
int __fastcall hookFindItemIndexInBothBanner_7B9F40(int* thisP, int, int a2) {
    int ret = Banner__findItemIndex_7B9F40(thisP, a2);
    if (ret != -1) goto exit;
    thisP = *(int**)0x1A6F754;
    ret = Banner__findItemIndex_7B9F40(thisP, a2);
    if (ret != -1) goto exit;
    return -1;
exit:
    selectBanner = thisP;
    return ret;
}


char __fastcall hookInventoryItemSubWin__Proc_6C07D0(int* thisP, int) {
    int* obj;
    if (!thisP[0xB]) {
        obj = (int*)getRClickGridObj(thisP, 0, 6);
        if (obj &&
            isOpenSlot_785010(obj, 0) &&
            getRClickDownGridPos(*(int**)((int)thisP + 4), 0, 6) != 0xFFFFFFFF &&
            IsKeyDown_11CBC60((int*)(*(DWORD*)0x1B56D78), 7, 0)) {
            if (showWindows((int*)(*(DWORD*)0x1A6F750), 0xB6, (int)obj, 0)) {
                int* win = (int*)showWin_E77470(*(int**)0x1A6F750, 0x40, 1, 0);
                TagLayout__setCurrentTag_11C19C0((int*)win[0x91], 1);
                //ItemInventoryWin__switchSubWinTag_6BD9D0(win, 1);
                ItemInventoryWin__switchBanner_6C1710(win, 1, 1);
                sub_6BDB00(thisP, 1, 6);
                sub_6BDA40(thisP, 0, 6);//清除右键事件
                sub_6BDA80(thisP, 0, 6);
                sub_6BDA60(thisP, 0xFFFFFFFF, 6);
            }
        }
    }
    return InventoryItemSubWin__Proc_6C07D0(thisP, 0);

}

char __fastcall hookDrawSkillLimitInfoText_F467C0(int thisP, int, int a1) {
    char ret = drawSkillLimitInfoText_F467C0((int*)thisP, 0, a1);
    if (*(BYTE*)(thisP + 0x18D) == 0) {
        drawInfoWinSlotInfo_F5A370((int*)thisP, 0, a1);
    }
    return ret;
}


int __cdecl hookCmd204RecvProc_71B7F0(int a1, int ret, int errCode, int a4) {
    int result = Cmd204RecvProc(a1, ret, errCode, a4);
#if TYPE == EQUIMENT_AVATAR
    if (result && selectBanner == *(int**)0x1A6F754) {
#elif EQUIMENT_ONLY
    if (result) {
#endif // BOTH
        int* win = (int*)showWin_E77470(*(int**)0x1A6F750, 0x40, 0, 0);
        ItemInventoryWin__switchBanner_6C1710(win, 0, 0);
    }
    return result;
    }

static int* procBanner;
int __cdecl hookCmd209RecvProc_7157A0(int a1, int ret, int errCode, int a4) {
    UINT8** p = (UINT8**)0x01B56370;
    BYTE v = 0;
    if (**p == 0xff) {
        procBanner = *((int**)0x1A6F754);
        PacketBuf_get_byte((int)&v);
    }
    else {
        procBanner = *((int**)0x1A6F768);
    }
    return Cmd209RecvProc(a1, ret, errCode, a4);
}


int __fastcall hookRandomOption__get_packet_random_option_7C7EB0(int* thisP) {
    UINT8** p = (UINT8**)0x01B56370;
    if (**p == 0xef) {
        BYTE myData[25] = { 0 };
        PacketBuf_get_byte((int)&myData);
        int size = PacketBuf_get_binary((int)&myData);
        memcpy((char*)thisP + 0xA0, myData, 18);
    }
    else {
        memset((char*)thisP + 0xA0, 0, 30);
    }
exit:
    return RandomOption__get_packet_random_option_7C7EB0(thisP);
}

thisCall1Args2 RandomOptionAttr__getAuctionItemRandOption_7C8690 = (thisCall1Args2)0x7C8690;
int __fastcall hookRandomOptionAttr__getAuctionItemRandOption_7C8690(int* thisP, int, BYTE * a2) {
    //printf("read randOption slot:0x%08x\n", (int)_ReturnAddress());
    //printf("slotInfo:");  for (int i = 0; i < 10; ++i) printf("%02x", (a2 - 10)[i]); printf("\n");
    memset((char*)thisP + 0xA0, 0, 30);
    BYTE* SlotInfo = a2 - 10;
    BYTE slotType = SlotInfo[0];
    if (slotType) {
        BYTE* p = (BYTE*)thisP + 0xA0;
        WORD slot1 = 0, slot2 = 0;
        switch (slotType) {
        case 1:slot1 = 0x01; slot2 = 0x01; break;
        case 2:slot1 = 0x02; slot2 = 0x02; break;
        case 3:slot1 = 0x04; slot2 = 0x04; break;
        case 4:slot1 = 0x08; slot2 = 0x08; break;
        case 5:slot1 = 0x10; slot2 = 0x00; break;
        }
        *(WORD*)p = slot1;
        *(DWORD*)(p + 2) = *(DWORD*)(SlotInfo + 1);
        *(BYTE*)(p + 5) = 0;
        *(WORD*)(p + 6) = slot2;
        *(DWORD*)(p + 8) = *(DWORD*)(SlotInfo + 3);
        *(BYTE*)(p + 11) = 0;
        *(WORD*)(p + 12) = 0;
        *(DWORD*)(p + 14) = 0;
        *(BYTE*)(p + 17) = 0;
    }

    return RandomOptionAttr__getAuctionItemRandOption_7C8690(thisP, (int)a2);
}
thisCall2 isAvatorEquim_788960 = (thisCall2)0x788960;
thisCall1Args2 RandomOptionAttr__setAttr_7C8630 = (thisCall1Args2)0x7C8630;
void __fastcall hookRandomOptionAttr__setAttr_7C8630(int* attr, int, int* equim) {
    if (equim && *equim && (*(UINT32*)(*equim + 0xF0) == 0x784570) && !isAvatorEquim_788960(equim)) {
        //printf("add slot:0x%08x\n", (int)_ReturnAddress());
        addSlotInfo_7946D0(equim, (int)((char*)attr + 0xA0));
    }
    //memset((char *)attr + 0xA0, 0, 30);
    RandomOptionAttr__setAttr_7C8630(attr, (int)equim);
}

bool isEmptySlot(BYTE * jewelData) {
    int v = 0;
    for (int i = 0; i < 30; ++i) v += jewelData[i];
    return v == 0;
}


int __fastcall hookAddSlotInfo(int* thisP, int, UINT8 * jewelData) {
    if (isEmptySlot(jewelData) && !isAvatorEquim_788960(thisP)) return 0;
    return addSlotInfo_7946D0(thisP, (int)jewelData);
}

//thisCall2Args2 showAddSlotWin_E782C0;
//int __fastcall hookShowAddSlotWin_E782C0(int* thisP, int, int a2, int a3) {
//    VMPV("hookShowAddSlotWin_E782C0");
//    return showAddSlotWin_E782C0(thisP, a2, a3);
//    VMPE();
//}

//使用开孔器打开物品栏
int __fastcall hookShowItemBanner(int* thisP, int, int a2, int a3, int a4) {
    int* win = (int*)showWin_E77470(thisP, a2, a3, a4);
    ItemInventoryWin__switchBanner_6C1710(win, 0, 0);
    return (int)win;
}

void equimentJewelInit(void) {
    //使用开孔器打开物品栏
    *(BYTE*)0x006EFFDB = 0;
    writeCallCode((void*)0x006EFFDF, hookShowItemBanner);

    *(BYTE*)0x007A1E98 = 21;//装备镶嵌属性支持
    *(BYTE*)0x0078BCE3 = 21;//装备类型为22一下显示镶嵌边框

#if TYPE == EQUIMENT_AVATAR
    writeCallCode((void*)0x00F1A1AF, hookFindItemIndexInBothBanner_7B9F40);
    writeCallCode((void*)0x00FDE2B0, hookFindItemIndexInBothBanner_7B9F40);
    *(DWORD*)0x00F1A3DC = (UINT32)&selectBanner;
    *(DWORD*)0x00F1A431 = (UINT32)&selectBanner;
    *(DWORD*)0x00F1A451 = (UINT32)&selectBanner;
    *(DWORD*)0x00FDDF0F = (UINT32)&selectBanner;
#elif EQUIMENT_ONLY
    * (DWORD*)0x00FDE2AB = 0x1A6F754;
    *(DWORD*)0x00F1A1AA = 0x1A6F754;
    *(DWORD*)0x00F1A3DC = 0x1A6F754;
    *(DWORD*)0x00F1A431 = 0x1A6F754;
    *(DWORD*)0x00F1A451 = 0x1A6F754;
    *(DWORD*)0x00FDDF0F = 0x1A6F754;
#endif // BOTH
    * (DWORD*)0x00715858 = (UINT32)&procBanner;
    *(DWORD*)0x007158D2 = (UINT32)&procBanner;
    *(DWORD*)0x00F1A81F = (UINT32)&procBanner;


    //*(BYTE*)0x0078BCE3 = 21;//装备类型为22一下显示镶嵌边框
    //*(BYTE*)0x00794711 = 21;
    //writeJmpCode((void*)0x00F1A1B4, hookDrawAddSlotWin);
    //// writeJmpCode((void*)0x00F1A829, hookDrawAddSlotFinishWin);
    //writeJmpCode((void*)0x00FDE2B5, hookDrawImbeding2SlotWin);
    //*(DWORD*)0x00F1A3DC = (UINT32)&selectBanner;
    //*(DWORD*)0x00F1A431 = (UINT32)&selectBanner;
    //*(DWORD*)0x00F1A451 = (UINT32)&selectBanner;
    //*(DWORD*)0x00FDDF0F = (UINT32)&selectBanner;
    //*(DWORD*)0x00E78342 = 0x0000E990;
    //*(DWORD*)0x00E7838E = 0x00008DE9;
    //*(BYTE*)0x00E784AB = 0xEB;
    //*(WORD*)0x00FDF017 = 0x9090;

    GumInterceptor* v = gum_interceptor_obtain();

    gum_interceptor_replace_fast(v, (gpointer)0x6C07D0, (gpointer)hookInventoryItemSubWin__Proc_6C07D0, (gpointer*)&InventoryItemSubWin__Proc_6C07D0);
    gum_interceptor_replace_fast(v, (gpointer)0xF467C0, (gpointer)hookDrawSkillLimitInfoText_F467C0, (gpointer*)&drawSkillLimitInfoText_F467C0);


    gum_interceptor_replace_fast(v, (gpointer)0x71B7F0, (gpointer)hookCmd204RecvProc_71B7F0, (gpointer*)&Cmd204RecvProc);
    gum_interceptor_replace_fast(v, (gpointer)0x7157A0, (gpointer)hookCmd209RecvProc_7157A0, (gpointer*)&Cmd209RecvProc);



    *(DWORD*)0x007CD94D += 30;//增加RandomOptionAttr镶嵌内存空间
    gum_interceptor_replace_fast(v, (gpointer)0x7C7EB0, (gpointer)hookRandomOption__get_packet_random_option_7C7EB0, (gpointer*)&RandomOption__get_packet_random_option_7C7EB0);
    gum_interceptor_replace_fast(v, (gpointer)0x7C8690, (gpointer)hookRandomOptionAttr__getAuctionItemRandOption_7C8690, (gpointer*)&RandomOptionAttr__getAuctionItemRandOption_7C8690);
    gum_interceptor_replace_fast(v, (gpointer)0x7C8630, (gpointer)hookRandomOptionAttr__setAttr_7C8630, (gpointer*)&RandomOptionAttr__setAttr_7C8630);


    *(BYTE*)0x00794711 = 21;

    gum_interceptor_replace_fast(v, (gpointer)0x7946D0, (gpointer)hookAddSlotInfo, (gpointer*)&addSlotInfo_7946D0);


    *(WORD*)0x00FDF017 = 0x9090;


    *(DWORD*)0x00E78342 = 0x0000E990;
    *(DWORD*)0x00E7838E = 0x00008DE9;
    *(BYTE*)0x00E784AB = 0xEB;

}
/*
void equimentJewelInit(void) {}
*/