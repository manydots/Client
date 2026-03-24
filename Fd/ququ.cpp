#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"


typedef int(__thiscall* _pfnAllocString)(DWORD* pthis, wchar_t* str, int size);
_pfnAllocString pfnAllocString = (_pfnAllocString)0x410030;
stdCall4 getAudioTag_46E2B0 = (stdCall4)0x46E2B0;
int __stdcall hookGetAudioTag_46E2B0(wchar_t* StrSound, DWORD* pCGString, int Saber, int Type) {
    if (StrSound && Type >= 11)
        return pfnAllocString(pCGString, StrSound, wcslen(StrSound));
    else
        return getAudioTag_46E2B0((int)StrSound, (int)pCGString, Saber, Type);
}

//static const wchar_t* PatchText = L"UI/NowLoading/Intro/Intro_12.ui";
//Naked void set_AniPatch()
//{
//    _asm {
//        mov esi, PatchText
//        push 696
//        mov eax, 0x006F4205
//        jmp eax
//    }
//}


cdeclCall sub_293BDA2 = (cdeclCall)0x293BDA2;
cdeclCall4 playSound = (cdeclCall4)0x766160;
int __cdecl set_IntroSound(void){
    static BYTE flag = 1;
    if (flag) {
        playSound((int)L"INTRO_LOGO", -1, 0, 1);
        flag = 0;
    }
    
    //playSound(L"INTRO_LOGO", -1, -1, 1);
    return sub_293BDA2(); //执行原始逻辑
}

//载图提示 UI/DungeonLoading/DungeonLoading.ui
//声音 INTRO_LOGO sounds/ui/intro_logo.ogg
Naked void set_NowloadingTime(){
    _asm {
        sub eax, [ebp - 0x14]
        cmp eax, 5220 //播放时间；韩服exe默认5100
        push 0x006FD83A
        ret
    }
}

//int GameCall_LoadImageEx(const WCHAR* wszImgPath, int index) {
//    int pNPK = LoadFile_11CAFB0(*(int **)0x1B564E4, 0, 0, (int)wszImgPath);
//    return getImageByPos_11B4BD0((int *)pNPK, index);
//}

//thisCall3Args sub_11B3980 = (thisCall3Args)0x11B3980;
int __fastcall draw_NowLoading(int *pDraw, int, int x, int y, int pImageEx){
    static int* img = NULL;
    if (!img) {
        img = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"Interface2/NowLoading/cutscene_acttitle.img");
        
    }
    //if(pImageEx != -1)
    //    drawImgByXY_11B3950(pDraw, x, y, pImageEx); //执行原始逻辑
    drawImgByXY_11B3950(pDraw, 0, 0, getImageByPos_11B4BD0(img, 0));
    
    return drawImgByXY_11B3950(pDraw, 0, 0, getImageByPos_11B4BD0(img, 1));
}

Naked void fix_Cross(){
    _asm {
        mov edx, [eax + 0x1F4]
        mov ecx, esi
        call edx
        test eax, eax
        je label1
        push 0x0
        push 0x19DC7FC
        push 0x19D91E8
        push 0x0
        push eax
        mov eax, 0x013D76DF//__RTDynamicCast
        call eax
        add esp, 0x14
        test eax, eax
        je label1
        push 0xA057BA
        ret
        label1 :
        push 0xA05A48
        ret
    }
}

Naked void hide_Button(){
    _asm {
        mov eax, [edx + 0x10]
        jnz Label1
        push 0xF37C3A
        ret
        Label1 :
        mov[esi + 0x178], 1
        mov ecx, [esi + 0x198]
        mov edx, [ecx]
        mov eax, [edx + 0x10]
        push 0
        call eax
        mov ecx, [esi + 0x19C]
        mov edx, [ecx]
        mov eax, [edx + 0x10]
        push 0
        call eax
        or ecx, 0xFFFFFFFF
        mov[esi + 0x17C], cx
        mov ecx, [esi + 0x188]
        mov edx, [ecx]
        mov eax, [edx + 0x10]
        push 0xF37C3E
        ret
    }
}

Naked void make_buffIcon(){
    _asm {
        cmp eax, 153 //sub_4B2CD0 default:153 空白buff 编号
        je label1
        mov ecx, [ebp + 0xC]
        cmp eax, [ecx + 0x8]
        push 0x4D14BD
        ret
        label1 :
        mov eax, 0x4D1501
        jmp eax
    }
}


thisCall1Args2 getPvfUiObjByName_10639E0 = (thisCall1Args2)0x10639E0;
thisCall2 GamePvfAnimation__initAnimation_1076640 = (thisCall2)0x1076640;

thisCall2ArgsF2 CNRDAnimation__setImageRate_10942E0 = (thisCall2ArgsF2)0x10942E0;
thisCall2ArgsF2 CNRDAnimation__setImageRateFromOriginal_10944F0 = (thisCall2ArgsF2)0x10944F0;
thisCall2ArgsF2 CNRDAnimation__setImageRateFromOriginalOnlyChild_1094900 = (thisCall2ArgsF2)0x1094900;

int __fastcall hookSub_1067EC0(int* thisP, int,  int Src, int a3, int a4) {
    int ret = ((thisCall3Args2)0x1067EC0)(thisP, Src, a3, a4);
    int aniNameList[] = {
        (int)L"IDC_ANIMATION_INTRO_BASE",
        (int)L"IDC_ANIMATION_INTRO_SMOG",
        (int)L"IDC_ANIMATION_INTRO_LOGO",
        (int)L"IDC_ANIMATION_INTRO_LOGO02",
        (int)L"IDC_ANIMATION_INTRO_BRUSH",
        (int)L"IDC_ANIMATION_INTRO_GRADE18"
    };
    int* obj;
    for (int i = 0; i < sizeof(aniNameList) / 4; ++i) {
        obj = (int*)getPvfUiObjByName_10639E0(thisP, aniNameList[i]);
        if (!obj) continue;
        GamePvfAnimation__initAnimation_1076640(obj);
        obj = (int*)obj[0xBA];
        if (!obj) continue;
        CNRDAnimation__setImageRate_10942E0(obj, 0.8, 0.8);
    }
    return ret;
}

Naked void make_dgnNameColor(){
    _asm {
        push 0xFF3232FF //红色
        lea edx, [ebp - 0x404]
        mov eax, 0x00F98BEF
        jmp eax
    }
}

void byQuQuInit(void) {

    //修复双门票
    *(char*)0x00F98BF1 = 7;
    writeJmpCode((void*)0x00F98BE7, &make_dgnNameColor);


    //修复死亡音效1
    * (BYTE*)0x008376CA = 0x53;

    //怪物死亡音效2
    //DetourAttach((LPVOID*)&getAudioTag_46E2B0, (PVOID)hookGetAudioTag_46E2B0);

    //* (BYTE*)0x008376CA = 0x50;


    //领主之塔结算音效修复
    *(BYTE*)0x0046E3E2 = 0xFF;

    //启动动画
    *(WORD*)0x006FD796 = 0x11EB;
    memcpy((void*)0x006FD80B, "\xEB\x13\x90\x90\x90", 5); //Esc跳过
    writeCallCode((void*)0x006FD7A9, &set_IntroSound); //注册声音
    writeJmpCode((void*)0x006FD834, &set_NowloadingTime); //播放时间
    writeCallCode((void*)0x006FD76B, &hookSub_1067EC0); //设置缩放

    //共享地下城动画
    //*(BYTE*)0x011174FB = 0xEB;

    //城镇过图插画修复
    writeCallCode((void*)0x01112846, &draw_NowLoading);

    //修复十字斩反伤秒杀
    writeJmpCode((void*)0x00A057A8, &fix_Cross);

    //重火器精通buff残留修复
    //memcpy((void*)0x004D3931, "\xEB\x01\x90", 3);

    //队友切换位置按钮
    writeJmpCode((void*)0x00F37C35, &hide_Button);
    memcpy((void*)0x00F37B1D, "\xEB\x30\x90\x90\x90\x90", 6);

    //修复空白bufficon
    writeJmpCode((void*)0x004D14B7, &make_buffIcon);

    //PVP换装按钮
    //*(BYTE*)0x006C0143 = 0x01;
    //*(BYTE*)0x006C0796 = 0x01;

    //越级转职物品窗口修复视频播放
    *(BYTE*)0x00477C74 = 0xA8;
    *(DWORD*)0x1821874 = 0x477BA0;
}