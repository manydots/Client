#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall1Args2 InventoryItemSubWin__init_6BFC10 = (thisCall1Args2)0x6BFC10;
int __fastcall hookInventoryItemSubWin__init_6BFC10(int* thisP, int, int a2) {
    int ret = InventoryItemSubWin__init_6BFC10(thisP, a2);
    setUiComponentVisable_11BE610((int*)thisP[52], 0);
    return ret;
}

BOOL __cdecl isNewTitle_FFA5E0() {
    return false;
}

void itemInventoryWinInit(void) {
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x6BFC10, (gpointer)hookInventoryItemSubWin__init_6BFC10, (gpointer*)&InventoryItemSubWin__init_6BFC10);
    *(BYTE*)0x006C134E = 0x1D;
    writeNopCode((void*)0x006C00FB, 6);

    //³ÆºÅ²¾Ïà¹Ø
    *(BYTE*)0x006C0ADD = 0xEB;
    gum_interceptor_replace_fast(v, (gpointer)0xFFA5E0, (gpointer)isNewTitle_FFA5E0, NULL);
}