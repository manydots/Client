#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"

/*
thisCall2Args setWinSize_11D8310 = (thisCall2Args)0x11D8310;
int __fastcall hookSetWinSize_11D8310(int* thisP, int edx, int w, int h) {
    if (w <= 800) w = 1067;
    //else w *= 1.33375f;
    return setWinSize_11D8310(thisP, edx, w, h);
}

thisCall4Args setGameWindowsSize_11B4710 = (thisCall4Args)0x11B4710;
int __fastcall hookSetGameWindowsSize_11B4710(int* thisP, int edx, int x, int y, int w, int h) {
    if (w == 800) w = 1067;
    //else w *= 1.33375f;
    return setGameWindowsSize_11B4710(thisP, edx, x, y, w, h);
}
UINT32 hookRateAddr[]{
    //0x00429CA6,
    0x0043346F,
    0x00435A33,
    0x00436B3E,

    0x00436F47,
    0x00436FD9,

    0x00437B71,

    0x00437D36,

    0x004701B6,

    0x00488F75,

    0x0049655A,
    0x0049881A,

    //0x004B9B78,

    0x004CC65C,
    0x004CD36A,
    0x004CE014,

    0x0055E079,
    0x0055E0AE,
    0x0055E15E,
    0x0055E33E,

    0x00569131,
    0x0056EAD8,

    0x00571105,
    0x005803D4,

    0x005934EE,
    0x00595476,
    0x00595690,
    0x00597C76,
    0x00598181,
    0x00598CE5,
    0x00598CF8,

    0x005B8BFE,
    0x005B8C20,

    0x00633596,

    0x00635DEA,
    0x00635DF7,
    0x00635E0B,

    0x0063623B,

    0x0063F518,
    0x00642261,
    0x006428FB,
    0x00644031,

    0x00648670,
    0x0064867C,

    0x006494A6,
    0x0065DE66,
    0x0065DE79,
    0x0065E259,

    0x006610B9,
    0x00661205,

    0x00675707,
    //0x0067570F,

    0x006757DB,
    0x006757FB,
    0x00675A11,

    0x0067C110,

    0x006AB784,

    0x006B1380,
    0x006B1E70,
    0x006B27D0,
    0x006B55BB,
    0x006B6042,
    0x006B6435,
    0x006B7A85,
    0x006B7EDC,
    0x006C5674,
    0x006F2D46,
    0x006F2E57,
    0x006F33E1,
    0x006F6A3C,

    0x00702DE9,

    0x007B528D,

    0x007D8130,
    0x007D8247,
    0x007D8298,
    0x007D82A2,
    0x007D82CE,
    0x007D84DA,
    0x007D8507,
    0x007DD369,
    0x007DD421,

    0x007E00C9,

    //0x0089FE70,

    0x008B2ACA,
    0x008B4BD4,
    0x008B4C4E,
    0x008B4E0C,

    0x008E7F80,
    0x008E852C,

    0x008E8F27,

    0x008EAD52,

    0x008EBEEB,

    0x008EED8A,
    0x008F33A9,

    0x0097CCFC,

    0x009E2A2F,
    0x009EB1BC,
    0x009EB1CE,

    0x00A362F9,

    0x00A65EA7,

    0x00A750BC,

    0x00AA4803,
    0x00AA481C,
    0x00AA4A0C,
    0x00AA4A3C,

    0x00AA4CFC,
    0x00AA4D57,

    0x00AC125C,
    0x00AC4892,
    0x00AD3A45,

    0x00ADDD16,

    0x00AFCAE8,
    0x00AFCB0B,
    0x00AFCB2E,

    0x00B09BDC,

    0x00B124AC,
    0x00B12420,
    0x00B12438,
    0x00B1AD5C,

    0x00B374AB,


};

BOOL(WINAPI* GetClientRectBk)(_In_ HWND hWnd, _Out_ LPRECT lpRect) = GetClientRect;
BOOL hookGetClientRect(HWND hWnd, LPRECT lpRect) {
    BOOL ret = GetClientRectBk(hWnd, lpRect);
    if (lpRect)
        DPRINTF("[%d,%d,%d,%d]\n", lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    return ret;
}

typedef int(__cdecl* getZoomPos)(int*, int*, float, float);
getZoomPos getZoomPos_8E7CC0 = (getZoomPos)0x8E7CC0;
int __cdecl hookGetZoomPos_8E7CC0(int* o_x, int* o_y, float a3, float a4) {
    int fixPos = *o_x % 4;
    int ret = getZoomPos_8E7CC0(o_x, o_y, a3, a4);
    if(fixPos) *o_x += fixPos - 1;
    return ret;
}

int __fastcall hookInitUiComponent_11BEF80(int* thisP, int edx) {
    DWORD id = *(DWORD*)0x1B57170;
    if (id == 0x85) {
        DPRINTF("init uiObj:%u %08x by %08x\n", id, id, (int)_ReturnAddress());
    }

    return initUiComponent_11BEF80(thisP);
}

int __fastcall hookSetUiComponentPos_11BEAD0(int* thisP, int edx, int x, int y, char a4) {
    if (x > 400) x += 133;
    return setUiComponentPos_11BEAD0(thisP, x, y, a4);
}

int __fastcall hookSetUiComponentSize_11BE370(int* thisP, int edx, int w, int h) {
    DWORD id = thisP[0x0D];
    DPRINTF("set uiObj size[%d, %d]:%u %08x by %08x\n", w, h, id, id, (int)_ReturnAddress());
    return setUiComponentSize_11BE370(thisP, w, h);
}

int __fastcall drawHubImg(int* thisP, int edx, int a2, int a3, int* imgAddr) {
    return innerDrawImg_11DB180(imgAddr, 347 + a2, a3, (int)thisP);
}

int __fastcall drawHubImg2(int* thisP, int edx, int x, int y, int a4, float a5, float a6, float a7, int a8, float a9, float a10) {
    return drawImgByXY2_11B41E0(thisP, 347 + x, y, a4, a5, a6, a7, a8, a9, a10);
}

int __fastcall drawCenterImg(int* thisP, int edx, int a2, int a3, int* imgAddr) {
    return innerDrawImg_11DB180(imgAddr, 133 + a2, a3, (int)thisP);
}


int __fastcall drawCenterImg2(int* thisP, int edx, int x, int y, int a4, float a5, float a6, float a7, int a8, float a9, float a10) {
    return drawImgByXY2_11B41E0(thisP, 133 + x, y, a4, a5, a6, a7, a8, a9, a10);
}

thisCall3Args drawItemSlot_100A320 = (thisCall3Args)0x100A320;
void __fastcall hookDrawItemSlot_100A320(int* thisP, int edx, int a2, int a3, int a4) {
    drawItemSlot_100A320(thisP, edx, a2, a3, a4);
}

int __fastcall setHudObjPos_11BEAD0(int* thisP, int edx, int x, int y, char a4) {
    return setUiComponentPos_11BEAD0(thisP, x + 133, y, a4);
}

cdeclCall11 drawToastWin_4CD120 = (cdeclCall11)0x4CD120;
void __cdecl drawHubToastWin(int x, int y, int a3, int a4, int a5, int a6, unsigned int a7, char a8, int a9, char a10, char a11) {
    drawToastWin_4CD120(x + 347, y, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

int getHubMousePosX() {
    return *(DWORD*)0x01B56504 - 347;
}

thisCall drawGatigueView_4C4230 = (thisCall)0x4C4230;
int __fastcall hookDrawGatigueView_4C4230(int* thisP, int edx) {
    int bgImg = getImageByPos_11B4BD0((int *)thisP[0x2A5], 203);
    innerDrawImg_11DB180((int *)bgImg, 790, 590, *(int *)0x1B5582C);
    return drawGatigueView_4C4230(thisP, edx);
}

thisCall1Args drawMpView_43A580 = (thisCall1Args)0x43A580;
void __fastcall hookDrawMpView_43A580(int* thisP, int edx, int a2) {
    drawMpView_43A580(thisP, edx, a2);
    int bgImg = getImageByPos_11B4BD0((int*)thisP[0x5A], 202);
    innerDrawImg_11DB180((int*)bgImg, 320, 582, *(int*)0x1B5582C);
}


int __fastcall setActIconPos_11BEAD0(int* thisP, int edx, int x, int y, char a4) {
    return setUiComponentPos_11BEAD0(thisP, x + 462, y + 8, a4);
}

cdeclCall4 sub_6FD880 = (cdeclCall4)0x6FD880;
int __cdecl hudSsub_6FD880(int x, int y, int w, int h) {
    return sub_6FD880(x, y, w + 347, h);
}

void Naked fixDrawBufIconPosX() {
    //004D1774
    __asm {
        add     esi, 150
        sub     edi, eax
        mov eax, 0x004D1779
        jmp eax
    }
}

void Naked fixShowBufIconToastPosX() {
    //004C7F5E
    __asm {
        sub     edi, eax
        add     esi, 150
        mov eax, 0x004C7F63
        jmp eax
    }
}


int __fastcall drawHub100Btn(int* thisP, int edx) {
    int ret = UiMgr__init_E84540(thisP);
    int* p = (*(int***)0x1AEDCEC)[0x49];
    p[0x05] = 441;//技能Ⅰ栏切换按钮x
    p[0x06] = 563;//技能Ⅰ栏切换按钮y
    p = (*(int***)0x1AEDCEC)[0x4A];
    p[0x05] = 441;//技能Ⅱ栏切换按钮x
    p[0x06] = 563;//技能Ⅱ栏切换按钮y
    p = (*(int***)0x1AEDCEC)[0x1F2];
    p[0x05] = 382;//等级小三角x
    p[0x06] = 590;//等级小三角y
    p = (*(int***)0x1AEDCEC)[0x21];
    p[0x05] = 828;//个人信息按钮x
    p[0x06] = 560;//个人信息按钮y
    p = (*(int***)0x1AEDCEC)[0x22];
    p[0x05] = 848;//物品栏按钮x
    p[0x06] = 560;//物品栏按钮y
    p = (*(int***)0x1AEDCEC)[0x23];
    p[0x05] = 868;//任务手册按钮x
    p[0x06] = 560;//任务手册按钮y
    p = (*(int***)0x1AEDCEC)[0x24];
    p[0x05] = 890;//技能栏按钮x
    p[0x06] = 560;//技能栏按钮y
    p = (*(int***)0x1AEDCEC)[0x25];
    p[0x05] = 908;//拍卖行按钮x
    p[0x06] = 560;//拍卖行按钮y
    p = (int*)((*(int**)0x1AEDCEC)[0x49] - 2028);
    p[0] = 802;//菜单按钮x
    p[1] = 560;//菜单按钮y
    p = (int*)((*(int**)0x1AEDCEC)[0x49] - 1004);
    p[0] = 740;//商城按钮x
    p[1] = 560;//商城按钮y

    //setUiComponentPos_11BEAD0(((int***)thisP)[0x10AD][0x45], 0, 133, 0, 1);//商城
    //writeCallCode((LPVOID*)0x0040B655, (PVOID)drawCenterImg2);
    //writeCallCode((LPVOID*)0x0040B6A6, (PVOID)drawCenterImg2);
    //writeCallCode((LPVOID*)0x0040B7C5, (PVOID)drawCenterImg2);

    //writeCallCode((LPVOID*)0x0040BBA1, (PVOID)drawCenterImg2);
    //writeCallCode((LPVOID*)0x0040BB4A, (PVOID)hookDrawItemSlot_100A320);
    //*(BYTE*)0x004101A0 = 0xa1; *(DWORD*)0x004101A1 = (int) &drawCenterImg;
    //*(BYTE*)0x0041020D = 0xa1; *(DWORD*)0x0041020E = (int)&drawCenterImg;
    return ret;
}

//hub.img 202/经验条  203/疲劳条bg 211/疲劳logo

void newRateInit() {
    for (int i = 0; i < sizeof(hookRateAddr) / sizeof(int); ++i) {
        *(DWORD*)(hookRateAddr[i]) = 1067;
    }
    *(WORD*)0x007D7E7A = 0x9090;

    *(DWORD*)0x007D7E80 = 250 / 0.75f;
    *(DWORD*)0x007D7E85 = 160 / 0.75f;

    *(DWORD*)0x007D7E8A = 450 / 0.75f;
    *(DWORD*)0x007D7E8F = 350 / 0.75f;
    *(DWORD*)0x007D74F7 = 1067;

    //*(DWORD*)0x1B2960C = 0;

    *(DWORD*)0x011B2B3F = 0;
    *(DWORD*)0x011B2FDA = 1067;

    *(DWORD*)0x004E14FE = 1067;
    *(DWORD*)0x004E150C = 1366;
    *(DWORD*)0x004E151A = 1707;

    *(DWORD*)0x0121120F = 1067;//拓展渲染画布

    *(WORD*)0x0011F336D = 1067;//拓展渲染宽度
    *(float*)0x001566D1C = 1067;//拓展地图背景渲染宽度
    *(double*)0x0015A2928 = 1067;//拓展鼠标识别宽度

    //DetourAttach((LPVOID*)&setWinSize_11D8310, (PVOID)hookSetWinSize_11D8310);
    DetourAttach((LPVOID*)&setGameWindowsSize_11B4710, (PVOID)hookSetGameWindowsSize_11B4710);
    DetourAttach((LPVOID*)&getZoomPos_8E7CC0, (PVOID)hookGetZoomPos_8E7CC0);

    //DetourAttach((LPVOID*)&setUiComponentSize_11BE370, (PVOID)hookSetUiComponentSize_11BE370);
    //DetourAttach((LPVOID*)&setUiComponentPos_11BEAD0, (PVOID)hookSetUiComponentPos_11BEAD0);
    DetourAttach((LPVOID*)&initUiComponent_11BEF80, (PVOID)hookInitUiComponent_11BEF80);

    //miniMap
    *(DWORD*)0x006FD89B = 1067;
    *(DWORD*)0x006FD8A2 = 1067;
    *(DWORD*)0x00F43917 = 1067;
    *(DWORD*)0x00F4391E = 1067;
    *(DWORD*)0x00F439AC = 1067;
    *(DWORD*)0x00F439B5 = 1067;
    *(DWORD*)0x01038735 = 1064;
    *(DWORD*)0x0103CEBF = 1067;
    *(DWORD*)0x0103CECE = 1064;
    *(DWORD*)0x0103CF40 = 977;
    *(DWORD*)0x0103CF5B = 1067;
    *(DWORD*)0x0103CFA1 = 1067;
    *(DWORD*)0x0103CFB7 = 1067;
    *(DWORD*)0x0103CFEC = 1064;
    *(DWORD*)0x0103D584 = 1064;
    *(DWORD*)0x010681FC = 1067;
    *(DWORD*)0x0106821a = 1067;
    *(DWORD*)0x01038614 = 1067;
    *(DWORD*)0x01038623 = 1067;
    *(DWORD*)0x0103D40D = 1067;
    *(DWORD*)0x0103D41C = 1067;

    //#define MouseSelectUiObjId              (*(DWORD *)0x01A424F0)
    //右上角地图按钮
    *(DWORD*)0x004D757D += 267;
    *(DWORD*)0x004CEFD1 += 267;

    //右上角深渊指示
    *(DWORD*)0x00E76B60 += 267;
    *(DWORD*)0x00E76B95 += 267;
    *(DWORD*)0x00E76C73 += 267;
    *(DWORD*)0x00E76CFE += 267;
    *(DWORD*)0x00E76D36 += 267;
    *(DWORD*)0x00E76D3E += 267;
    *(DWORD*)0x00E76D7C += 267;

    //右上角频道，副本提示文本
    *(DWORD*)0x004C40B8 += 267;
    *(DWORD*)0x004C414D += 267;
    *(DWORD*)0x004C41C2 += 267;
    *(DWORD*)0x004C41A0 += 267;
    *(DWORD*)0x004D2BF3 += 267;
    *(DWORD*)0x004D2DBC += 267;
    setRandView(267, 0);

    //活动提示窗口
    *(DWORD*)0x0045D612 += 267;
    *(DWORD*)0x0045D646 += 267;
    *(DWORD*)0x0045D664 += 267;
    *(DWORD*)0x0045D787 += 267;
    *(DWORD*)0x0045D814 += 267;
    *(DWORD*)0x004C6040 += 267;
    *(DWORD*)0x004C60C0 += 267;

    //右下角拉伸图标
    *(DWORD*)0x0100902D += 267;
    //hub
    //hub背景图片
    *(DWORD*)0x004D2B8A = 516;
    writeCallCode((LPVOID*)0x004D2B90, (PVOID)drawHubImg);
    *(DWORD*)0x004D676F = 1067;//鼠标识别宽度
    *(BYTE*)0x004D676D = 96;//鼠标识别高度
    //*(DWORD*)0x004D678A = 516;//识别开始高度
    //writeCallCode((LPVOID*)0x004D678F, (PVOID)setHudObjPos_11BEAD0);

    //支援兵
    //*(DWORD*)0x006F293A = ZoomRate;//x
    //*(DWORD*)0x006F2935 = 300;//y

    //血球
    *(BYTE*)0x0043B255 = 25;//扣血血球X
    *(DWORD*)0x0043B250 = 537;//扣血血球Y
    *(BYTE*)0x0043B2D8 = 25;//扣血白罩子血球X
    *(DWORD*)0x0043B2D3 = 537;//扣血白罩子血球Y
    *(BYTE*)0x0043B202 = 25;//血球X
    *(DWORD*)0x0043B1FD = 537;//血球Y
    writeCallCode((LPVOID*)0x0043B256, (PVOID)drawHubImg2);
    writeCallCode((LPVOID*)0x0043B2D9, (PVOID)drawHubImg2);
    writeCallCode((LPVOID*)0x0043B203, (PVOID)drawHubImg);
    *(DWORD*)0x0043B1D6 = 593;//血球遮罩开始Y
    *(DWORD*)0x0043B1CE = 593;//血球遮罩结束Y
    //血球信息弹窗
    *(BYTE*)0x004CF10A = 50;//HP文字标识 X轴
    *(DWORD*)0x004CF105 = 537;//HP文字标识 Y轴
    *(BYTE*)0x004CF05B = 60;//HP 识别区域宽度
    *(BYTE*)0x004CF06A = 50;//HP 识别区域高度
    *(BYTE*)0x004CF058 = -25;//HP识别区域 X轴 EB → lea edx,[edi-15]
    *(DWORD*)0x004CF064 = -537;//HP识别区域 Y轴 FFFFFDF3 → lea eax,[esi-0000020D]


    ////蓝球
    *(DWORD*)0x0043B3E3 = 318;//乘骑蓝球X
    *(DWORD*)0x0043B3DE = 537;//乘骑蓝球Y
    *(DWORD*)0x0043B46D = 318;//异常蓝球X
    *(DWORD*)0x0043B468 = 537;//异常蓝球Y
    *(DWORD*)0x0043B38D = 318;//蓝球X
    *(DWORD*)0x0043B388 = 537;//蓝球Y
    writeCallCode((LPVOID*)0x0043B3E7, (PVOID)drawHubImg2);
    writeCallCode((LPVOID*)0x0043B471, (PVOID)drawHubImg2);
    writeCallCode((LPVOID*)0x0043B391, (PVOID)drawHubImg);
    *(DWORD*)0x0043B361 = 593;//蓝球遮罩开始Y
    *(DWORD*)0x0043B359 = 593;//蓝球遮罩结束Y
    // //蓝球信息弹窗
    *(DWORD*)0x004CF1DA = 343;//HP文字标识 X轴
    *(DWORD*)0x004CF1D5 = 537;//HP文字标识 Y轴
    *(BYTE*)0x004CF128 = 60;//HP 识别区域宽度
    *(BYTE*)0x004CF137 = 50;//HP 识别区域高度
    *(DWORD*)0x004CF122 = -318;//HP识别区域 X轴 EB → lea edx,[edi-15]
    *(DWORD*)0x004CF131 = -537;//HP识别区域 Y轴 FFFFFDF3 → lea eax,[esi-0000020D]

    writeCallCode((LPVOID*)0x004CF588, (PVOID)drawHubToastWin);
    writeCallCode((LPVOID*)0x004CED93, (PVOID)getHubMousePosX);


    DetourAttach((LPVOID*)&UiMgr__init_E84540, (PVOID)drawHub100Btn);//菜单按钮初始化

    //202 203
    ////疲劳
    writeCallCode((LPVOID*)0x004D2EA8, (PVOID)hookDrawGatigueView_4C4230);

    *(DWORD*)0x004C42A5 = 141;//疲劳宽度
    *(DWORD*)0x004C42C6 = 790;//疲劳 X轴
    *(DWORD*)0x004C4320 = 790;//疲劳 X轴
    *(DWORD*)0x004C42BB = 790;//疲劳 X轴
    *(DWORD*)0x004C4266 = 790;//疲劳 X轴
    *(DWORD*)0x004C431B = 590;//疲劳 Y轴
    *(DWORD*)0x004C42C1 = 590;//疲劳 Y轴
    *(DWORD*)0x004C4261 = 590;//疲劳 Y轴
    *(DWORD*)0x004C4355 = 845;//疲劳图标x
    *(DWORD*)0x004C4350 = 586;//疲劳图标y
    *(DWORD*)0x004C43E0 = 845;//疲劳图标闪烁x
    *(DWORD*)0x004C43DB = 586;//疲劳图标闪烁y
    *(DWORD*)0x004C44CA = 779;//疲劳图标指示闪烁x
    *(DWORD*)0x004C44C5 = 584;//疲劳图标指示闪烁y

    *(DWORD*)0x004CF765 = 850;//疲劳值文字标识 X轴
    *(DWORD*)0x004CF760 = 580;//疲劳值文字标识 Y轴
    *(DWORD*)0x004CF8C7 = 850;//疯狂阶段文字标识① X轴
    *(DWORD*)0x004CF8C2 = 580;//疯狂阶段文字标识① Y轴
    *(DWORD*)0x004CF944 = 850;//疯狂阶段文字标识② X轴
    *(DWORD*)0x004CF93F = 580;//疯狂阶段文字标识② Y轴

    *(BYTE*)0x004CF5FB = 144;//疲劳条识别区域宽度
    *(BYTE*)0x004CF60D = 10;//疲劳条识别区域高度
    *(DWORD*)0x004CF5F5 = -443;//疲劳条识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
    *(DWORD*)0x004CF607 = -588;//疲劳条识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

    ////buff
    writeJmpCode((LPVOID*)0x004D1774, (PVOID)fixDrawBufIconPosX);
    //*(BYTE*)0x004D1776 = 150;//图标X
    *(DWORD*)0x004D1755 = 542;//图标Y
    writeJmpCode((LPVOID*)0x004C7F5E, (PVOID)fixShowBufIconToastPosX);
    //*(BYTE*)0x004C7F62 = 150;//提示文字坐标X
    *(DWORD*)0x004C7F5A = 540;//提示文字坐标Y

    ////活动图标
    writeCallCode((LPVOID*)0x004E7848, (PVOID)setActIconPos_11BEAD0);
    //*(BYTE*)0x004E783F = 127;//图标X
    //*(DWORD*)0x004E782F = 520;//图标Y

    //经验等级sp
    writeCallCode((LPVOID*)0x004C0DA5, (PVOID)hookDrawMpView_43A580);
    //等级LV
    *(DWORD*)0x004C2067 = 672;//X
    *(DWORD*)0x004C208B = 588;//lv Y
    *(DWORD*)0x004C209B = 588;//数值 Y
    *(DWORD*)0x004C20FE = 696;//pk X
    *(DWORD*)0x004C20E6 = 585;//pk Y
    *(DWORD*)0x004C214D = 696;//pk X
    *(DWORD*)0x004C212F = 585;//pk Y

    //sp
    *(DWORD*)0x004D2E9B = 716;//X
    *(DWORD*)0x004D2E96 = 588;//Y
    *(BYTE*)0x004CF99B = 40;//sp识别区域宽度
    *(BYTE*)0x004CF9A6 = 14;//sp识别区域高度
    *(DWORD*)0x004CF995 = -350;//sp识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
    *(DWORD*)0x004CF9A0 = -588;//sp识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

    //经验条
    *(BYTE*)0x004C0F24 = 47;//X
    writeCallCode((LPVOID*)0x004C0F25, (PVOID)drawHubImg);
    *(BYTE*)0x004C0FAD = 47;//X
    writeCallCode((LPVOID*)0x004C0FAE, (PVOID)drawHubImg);
    *(BYTE*)0x004C0F6E = 47;//X
    writeCallCode((LPVOID*)0x004C0F6F, (PVOID)drawHubImg);

    *(DWORD*)0x004C0F1F = 595;//Y
    *(DWORD*)0x004C0FA8 = 595;//Y
    *(DWORD*)0x004C0F69 = 595;//Y

    *(float*)0x01575354 = 300.0f;
    *(DWORD*)0x004C0E99 = 300;
    *(DWORD*)0x004C0ED3 = 300;
    *(DWORD*)0x004C0E80 = 300;
    *(DWORD*)0x004C0E71 = 300;

    *(BYTE*)0x004C0EE8 = 47;
    writeCallCode((LPVOID*)0x004C0EEE, (PVOID)hudSsub_6FD880);
    *(DWORD*)0x004C0F44 = 300 + 47;
    //*(DWORD*)0x004C0EE2 = 300;//y
    //*(DWORD*)0x004C0F3F = 300;//Y

    writeCallCode((LPVOID*)0x004CF582, (PVOID)getHubMousePosX);
    *(DWORD*)0x004CF1F8 = 300;//经验条识别区域宽度
    *(BYTE*)0x004CF20A = 6;//经验条识别区域高度
    *(BYTE*)0x004CF1F5 = -45;//经验条识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
    *(DWORD*)0x004CF204 = -594;//经验条识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

    //*(BYTE*)0x004C0EE8 = 90;//X

    ////技能栏
    //seal 按钮
    *(DWORD*)0x004D6BBC = 444;//X
    *(DWORD*)0x004D6BB7 = 533;//Y
    *(BYTE*)0x004BBB59 = 0xEB;//nut技能坐标函数跳过

    *(DWORD*)0x004D68A9 = 455;//X
    *(DWORD*)0x004D68EF = 564;//Y
    *(DWORD*)0x004D690C = 455 + 6 * 30;

    //扩展技能栏
    *(DWORD*)0x004D694E = 455;//X
    *(DWORD*)0x004D6994 = 534;//Y
    *(DWORD*)0x004D69BE = 455 + 6 * 30;//X

    //物品栏
    *(DWORD*)0x004D683F = 150;//X
    *(DWORD*)0x004D6885 = 570;//Y
    *(DWORD*)0x004D68A2 = 150 + 6 * 30;//最大宽度
}
*/