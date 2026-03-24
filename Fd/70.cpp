#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"
#include "itemInfoWin.h"
#include "goldSkill.h"
#include "riding.h"
#include "CNSelectCharacterModule.h"

int __fastcall imgFixPosDraw(int* thisP, int edx, int x, int y, int* imgAddr) {
	return innerDrawImg_11DB180(imgAddr, x - 160, y - 120, (int)thisP);
}

thisCall5Args2 sub_11BCE70 = (thisCall5Args2)0x11BCE70;
int __fastcall imgFixPosDraw2(int* thisP, int edx, int x, int y, int a4, int a5, int a6) {
	return sub_11BCE70(thisP, x - 160, y - 120, a4, a5, a6);
}


#define HUD_BASE_X 0
#define HUD_BASE_Y 391
#define HUD_BASE_W 640
void init70_UiMgr__initCb(int* thisP) {
	int* p = (*(int***)0x1AEDCEC)[0x49];
	int x = HUD_BASE_X + 366;
	int y = HUD_BASE_Y + 51;

	p[0x05] = x;//技能Ⅰ栏切换按钮x
	p[0x06] = y;//技能Ⅰ栏切换按钮y
	p = (*(int***)0x1AEDCEC)[0x4A];
	p[0x05] = x;//技能Ⅱ栏切换按钮x
	p[0x06] = y;//技能Ⅱ栏切换按钮y
	p = (*(int***)0x1AEDCEC)[0x1F2];
	p[0x05] = HUD_BASE_X + 60;//等级小三角x
	p[0x06] = HUD_BASE_Y + 77;//等级小三角y

	x = HUD_BASE_X + 277;
	y = HUD_BASE_Y + 53;
	int len = 18;
	p = (*(int***)0x1AEDCEC)[0x21];
	p[0x05] = x;//个人信息按钮x
	p[0x06] = y;//个人信息按钮y
	p = (*(int***)0x1AEDCEC)[0x22];
	p[0x05] = x + len;//物品栏按钮x
	p[0x06] = y;//物品栏按钮y
	p = (*(int***)0x1AEDCEC)[0x23];
	p[0x05] = x + 2 * len;//任务手册按钮x
	p[0x06] = y;//任务手册按钮y
	p = (*(int***)0x1AEDCEC)[0x24];
	p[0x05] = x + 3 * len;//技能栏按钮x
	p[0x06] = y;//技能栏按钮y
	p = (*(int***)0x1AEDCEC)[0x25];
	p[0x05] = x + 4 * len;//拍卖行按钮x
	p[0x06] = y;//拍卖行按钮y
	p = (int*)((*(int**)0x1AEDCEC)[0x49] - 2028);
	p[0] = 802;//菜单按钮x
	p[1] = 1000;//菜单按钮y
	p = (int*)((*(int**)0x1AEDCEC)[0x49] - 1004);
	p[0] = 740;//商城按钮x
	p[1] = 1000;//商城按钮y

	//setUiComponentPos_11BEAD0(((int***)thisP)[0x10AD][0x45], 0, 133, 0, 1);//商城
	//writeCallCode((LPVOID*)0x0040B655, (PVOID)drawCenterImg2);
	//writeCallCode((LPVOID*)0x0040B6A6, (PVOID)drawCenterImg2);
	//writeCallCode((LPVOID*)0x0040B7C5, (PVOID)drawCenterImg2);

	//writeCallCode((LPVOID*)0x0040BBA1, (PVOID)drawCenterImg2);
	//writeCallCode((LPVOID*)0x0040BB4A, (PVOID)hookDrawItemSlot_100A320);
	//*(BYTE*)0x004101A0 = 0xa1; *(DWORD*)0x004101A1 = (int) &drawCenterImg;
	//*(BYTE*)0x0041020D = 0xa1; *(DWORD*)0x0041020E = (int)&drawCenterImg;

	initOld70Hub_delay(thisP, 605, 265, 430);
	//extern void FixSingleFashion2(void);
	//*(DWORD*)0x0042133C = (int)FixSingleFashion;
	//*(DWORD*)0x0042133C = (int)FixSingleFashion2;
	extern void FixFashionTagBottomLine(void);
	*(DWORD*)0x0040B9CC = (int)FixFashionTagBottomLine;
	goldSkillInitDelay(thisP);
	ridingInitDelay(thisP);
}



cdeclCall1 getCreatureIdByEqumId_978E00 = (cdeclCall1)0x978E00;
thisCall2Args2 getCharacWearSlot_852640 = (thisCall2Args2)0x852640;
thisCall1Args2 drawExpHpMpView_4C0D60 = (thisCall1Args2)0x4C0D60;
cdeclCall1 sub_8C4D50 = (cdeclCall1)0x8C4D50;
thisDCall2 getCreatureExpPrecen_8C4750 = (thisDCall2)0x8C4750;
void __fastcall hookDrawExpHpMpView(int* thisP, int, int a2) {
	drawExpHpMpView_4C0D60(thisP, a2);
	int* charac = *(int**)0x1AC790C;
	if (!charac) return;
	int* creature = (int*)getCharacWearSlot_852640(charac, 22, 0);
	if (!creature) return;
	int v = getImageByPos_11B4BD0((int*)thisP[0x2A5], 115);drawImgByXY_11B3950(*(int**)0x1B5582C, HUD_BASE_X + (HUD_BASE_W - 89), HUD_BASE_Y - 4, v);
	decrypt_11A0DE0(creature + 0x412, (int)(creature + 0x414), (int)&v);
	v = getCreatureExpPrecen_8C4750((int*)sub_8C4D50(v));
	if (v) {
		int w = getLinearValue_11B98C0(0, 65, v, 100);
		//int h = getLinearValue_11B98C0(42, 0, v, 100);
		//printf("v:%d w:%d\n", v, w);
		int x = HUD_BASE_X + (HUD_BASE_W - 89) + 5;
		int y = HUD_BASE_Y + 1;
		setGameCanvasSize_6FD880(x, y, x + w, y + 42);
		v = getImageByPos_11B4BD0((int*)thisP[0x2A5], 116);
		if (v) drawImgByXY_11B3950(*(int**)0x1B5582C, x, y, v);
		resetGameCanvasSize_6FD8D0();
	}
	static int* headerImg = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/creatureheadicon.img");
	if (!headerImg) return;
	v = getImageByPos_11B4BD0(headerImg, getCreatureIdByEqumId_978E00(creature[7]) - 1);
	drawImgByXY_11B3950(*(int**)0x1B5582C, HUD_BASE_X + (HUD_BASE_W - 20), HUD_BASE_Y + 3, v);
}


void __cdecl favorBtnCb(void) {
	showWin_E77470(*(int**)0x1A6F750, 0x4C, 2, 0);
}
void __cdecl moodBtnCb(void) {
	showSettingWinByIdx_4F2220(6);
}

thisCall4Args2 HudInfoBtnMgr__addIconDrawFn_4E9960 = (thisCall4Args2)0x4E9960;
thisCall2Args2 HudInfoBtnMgr__setClickCb_4D87E0 = (thisCall2Args2)0x4D87E0;
thisCall2 HudInfoBtnMgr__init_4EBD70 = (thisCall2)0x4EBD70;
int __fastcall hookHudInfoBtnMgr__init_4EBD70(int* thisP) {
	int ret = HudInfoBtnMgr__init_4EBD70(thisP);
	int v3[4];
	int v4[2];
	v4[0] = 0x11;//好感度按钮callback
	v4[1] = (int)favorBtnCb;
	HudInfoBtnMgr__setClickCb_4D87E0(thisP, (int)v3, (int)v4);
	v4[0] = 0x17;//心情按钮callback
	v4[1] = (int)moodBtnCb;
	HudInfoBtnMgr__setClickCb_4D87E0(thisP, (int)v3, (int)v4);
	return ret;
}

thisCall1Args2 HudInfoBtnMgr__getBtn_4E7F20 = (thisCall1Args2)0x4E7F20;
thisCall1Args2 HudInfoBtnMgr__addBtn_4E9770 = (thisCall1Args2)0x4E9770;

int * addHudInfoBtn(int* thisP, int idx) {
	int* infoBtn = (int*)HudInfoBtnMgr__getBtn_4E7F20(thisP, idx);
	if (!infoBtn || !RBYTE(infoBtn, 8)) {
		infoBtn = (int*)HudInfoBtnMgr__addBtn_4E9770(thisP, idx);
	}
	return infoBtn;
}

GameAnim* moodAnim = new GameAnim(L"ui/fd/chn_emotion_expression_information_button.ani", false);
thisCall2 HudInfoBtn__Proc_FD50A0 = (thisCall2)0xFD50A0;
int __fastcall myHudInfoBtn__Proc(int* thisP) {
	int ret = HudInfoBtn__Proc_FD50A0(thisP);
	int x = thisP[5];
	int y = thisP[6];
	moodAnim->draw(x, y);
	return ret;
}

int* HudInfoBtnTypeInfo = NULL;
thisCall1Args2 HudInfoBtnMgr__newBtn_4E9520 = (thisCall1Args2)0x4E9520;
int* __fastcall hookHudInfoBtnMgr__newBtn_4E9520(int* thisP, int, int id) {
	int *ret = (int *)HudInfoBtnMgr__newBtn_4E9520(thisP, id);
	if (ret && id == 0x17) {
		if (!HudInfoBtnTypeInfo) {
			int typeInfoLen = 0x0185A8E0 - 0x0185A818;
			HudInfoBtnTypeInfo = (int*)malloc(typeInfoLen);
			if (HudInfoBtnTypeInfo == NULL) {
				printf("malloc vtable memory error!\n");
				return ret;
			}
			memcpy(HudInfoBtnTypeInfo, (void*)0x0185A818, typeInfoLen);
			HudInfoBtnTypeInfo[10] = (int)myHudInfoBtn__Proc;
		}
		if (*(int*)(ret[0]) != (int) & HudInfoBtnTypeInfo[1]) {
			*(int*)(ret[0]) = (int)&HudInfoBtnTypeInfo[1];
		}
	}
	return ret;
}

thisCall2 HudInfoBtnMgr__makeBtn_4E9A80 = (thisCall2)0x4E9A80;
int __fastcall hookHudInfoBtnMgr__makeBtn_4E9A80(int* thisP) {
	int ret = HudInfoBtnMgr__makeBtn_4E9A80(thisP);
	//addHudInfoBtn(thisP, 0x8);//遗忘契约 技能
	addHudInfoBtn(thisP, 0x11);//NPC好感度
	//addHudInfoBtn(thisP, 0x12);//商城
	addHudInfoBtn(thisP, 0x17);//设置心情按钮
	//HudInfoBtnMgr__addIconDrawFn_4E9960((int *)0x1A49718, 0x17, (int)drawMoodAnim, 0, 2);
	//addHudInfoBtn(thisP, 0x20);//元气加值活动
	return ret;
}



#define Width   640
#define Height  480
forceinline void init70_hud() {
	//怪物攻城战斗失败惩罚ui
	*(DWORD*)0x004CDDB8 -= 80;
	*(DWORD*)0x004CDDB3 -= 60;

	//伤害字体相关
	*(DWORD*)0x007E00C9 -= 160; *(DWORD*)0x007E00A0 -= 120;
	//*(DWORD*)0x007E01E1 -= 80; *(DWORD*)0x007E01DC -= 60;//title
	*(DWORD*)0x007DF7D9 -= 80; *(DWORD*)0x007DF7D4 -= 60;
	*(DWORD*)0x007DF84E -= 80; *(DWORD*)0x007DF849 -= 60;

	//异界抗魔值提示窗口
	*(DWORD*)0x004BD5F6 -= 160;//x
	*(DWORD*)0x004BD5F1 -= 60;
	*(DWORD*)0x004BD513 -= 160;//x
	*(DWORD*)0x004BD50E -= 60;
	*(DWORD*)0x004BD593 -= 160;//x
	*(DWORD*)0x004BD58E -= 60;
	*(DWORD*)0x004BD5C2 = 612;//x 612
	*(DWORD*)0x004BD5BD -= 60;

	//幽灵列车读条
	*(DWORD*)0x00A38BE3 -= 80;//x
	*(DWORD*)0x00A38BDE -= 120;
	*(DWORD*)0x00A38C9D -= 80;
	*(DWORD*)0x00A38C98 -= 120;
	*(DWORD*)0x00A38C43 -= 80;
	*(DWORD*)0x00A38C3E -= 120;
	*(DWORD*)0x00A38CF9 -= 80;
	*(DWORD*)0x00A38CF4 -= 120;
	*(DWORD*)0x00A38D0C -= 80;
	*(DWORD*)0x00A38D06 -= 120;
	*(DWORD*)0x00A38D14 -= 80;
	*(DWORD*)0x00A38DE9 -= 80;
	*(DWORD*)0x00A38DE4 -= 120;
	*(DWORD*)0x00A38E45 -= 120;
	*(DWORD*)0x00A38EB4 -= 80;
	*(DWORD*)0x00A38EAF -= 120;

	//异界虚无之境boss 读条
	*(DWORD*)0x0087275C -= 80;//x
	*(DWORD*)0x0087277F -= 80;
	*(DWORD*)0x00872757 -= 120;
	*(DWORD*)0x00872777 -= 120;
	*(DWORD*)0x008727DB -= 80;
	*(DWORD*)0x008727D6 -= 120;
	*(DWORD*)0x00872767 -= 80;
	*(DWORD*)0x00872837 -= 120;

	*(DWORD*)0x007F91BA = 999999;
	*(DWORD*)0x007F91E7 = 999999;
	*(BYTE*)0x00E632D5 = 30;//y

	//伤害字体显示上限
	*(DWORD*)0x007F91BA = 999999;
	*(DWORD*)0x007F91E7 = 999999;
	*(BYTE*)0x00E632D5 = 30;//y
	
	//取消获得新称号弹窗
	*(BYTE*)0x00E772B4 = 0x90;//y
	*(DWORD*)0x00E772B5 = 0x90909090;//y
	
	//任务事件完成动画
	*(DWORD*)0x00E71B14 -= 80;//x
	*(DWORD*)0x00E71B0F -= 60;//y
	*(DWORD*)0x00E71BC6 -= 80;//x
	*(DWORD*)0x00E71BC1 -= 60;//y
	
	//死灵暴君技能坐标
	*(DWORD*)0x00CE61F6 -= 120;//y
	*(DWORD*)0x00CE620C -= 120;//y
	*(DWORD*)0x00CE621C -= 120;//y
	*(DWORD*)0x00CE6251 -= 160;//x
	*(DWORD*)0x00CE62A7 -= 160;//x

	//刺客豆子
	*(DWORD*)0x00CE4492 -= 100;//y
	*(DWORD*)0x00CE44F8 -= 100;//y

	//战斗法师觉醒技能坐标
	*(DWORD*)0x00C32480 -= 120;//y
	*(DWORD*)0x00C32496 -= 120;//y
	*(DWORD*)0x00C324A6 -= 120;//y
	*(DWORD*)0x00C324B9 -= 160;//x
	*(DWORD*)0x00C324DD -= 160;//x

	//无尽祭坛
	*(DWORD*)0x00FF8481 -= 160;//x
	*(DWORD*)0x00FF84A6 -= 160;//x
	*(DWORD*)0x00FF67E1 -= 160;//x
	*(DWORD*)0x00FF67E8 -= 160;//x
	*(DWORD*)0x00FF67F0 -= 160;//x
	*(DWORD*)0x00FF67F7 -= 160;//x
	*(DWORD*)0x00FF680D -= 160;//x
	*(DWORD*)0x00FF6814 -= 160;//x
	*(DWORD*)0x00FF681C -= 160;//x
	*(DWORD*)0x00FF6823 -= 160;//x
	//*(BYTE*)0x00FF8489 -= 80;//y
	*(BYTE*)0x00FF849F -= 120;//y
	//*(DWORD*)0x00FF84C8 -= 108;//
	*(DWORD*)0x00FF84BF -= 120;//y
	
	*(DWORD*)0x00FF6A82 -= 160;//x
	*(DWORD*)0x00FF6A7A -= 120;//y
	*(DWORD*)0x00FF7D8B -= 160;//x
	*(DWORD*)0x00FF7D86 -= 60;//y

	*(DWORD*)0x00FF5F18 -= 160;//x
	*(DWORD*)0x00FF5F47 -= 160;//x
	*(DWORD*)0x00FF5F52 -= 160;//x
	*(DWORD*)0x00FF5F7F -= 160;//x
	*(DWORD*)0x00FF5FAC -= 160;//x
	*(DWORD*)0x00FF5FB5 -= 160;//x

	*(DWORD*)0x00FF60EA -= 160;//x
	*(DWORD*)0x00FF60E5 -= 120;//y

	//绝望祭坛
	*(DWORD*)0x0108BC71 -= 160;//x
	*(DWORD*)0x0108BCB4 -= 160;//x
	*(DWORD*)0x0108BDB3 -= 160;//x
	*(DWORD*)0x0108BDD5 -= 160;//x
	*(DWORD*)0x0108BE28 -= 160;//x
	*(DWORD*)0x0108BF9C -= 160;//x
	*(DWORD*)0x0108BF24 -= 160;//x
	*(DWORD*)0x0054DFF6 -= 160;//x
	*(DWORD*)0x0108BAE4 -= 160;//x
	*(DWORD*)0x00FF8971 -= 160;//x
	*(DWORD*)0x00FF8BA5 -= 160;//x

	//复活币倒数
	*(DWORD*)0x004E38ED -= 80;//x
	*(DWORD*)0x004E38E8 -= 60;//y

	//幽灵状态标签
	*(DWORD*)0x008E8EFE = Height;//x
	*(DWORD*)0x008E8F27 = Width;//y
	*(DWORD*)0x008E8F90 -= 80;//x
	*(DWORD*)0x008E8F8B -= 60;//y
	*(DWORD*)0x008E8FBC -= 80;//x
	*(DWORD*)0x008E8FB7 -= 60;//y

	//DungeonMiniMapWin::ProcDraw_1038690
	*(DWORD*)0x01038735 = Width - 7;
	*(DWORD*)0x0103CEBF = Width;
	*(DWORD*)0x0103CECE = Width - 3;
	*(DWORD*)0x0103CF40 = Width - 90;
	*(DWORD*)0x0103CF5B = Width;
	*(DWORD*)0x0103CFA1 = Width;
	*(DWORD*)0x0103CFB7 = Width;
	*(DWORD*)0x0103CFEC = Width - 7;
	*(DWORD*)0x0103D584 = Width - 7;
	//DungeonMiniMapWin::OnOpen_10384E0
	*(DWORD*)0x01038614 = Width;
	*(DWORD*)0x01038623 = Width;
	*(DWORD*)0x01038637 = Height;
	*(DWORD*)0x01038646 = Height;
	//WorldMinimap::OnOpen_103D290
	*(DWORD*)0x0103D40D = Width;
	*(DWORD*)0x0103D41C = Width;
	*(DWORD*)0x0103D430 = Height;
	*(DWORD*)0x0103D43F = Height;
	//sub_10681E0
	*(DWORD*)0x010681FC = Width;
	*(DWORD*)0x0106821a = Width;
	*(DWORD*)0x01068233 = Height;
	*(DWORD*)0x01068251 = Height;

	//右上角地图按钮
	//*(DWORD*)0x004D757D -= 160;
	//*(DWORD*)0x004CEFD1 -= 160;

	//右上角深渊指示
	*(DWORD*)0x00E76B60 -= 133;
	*(DWORD*)0x00E76B95 -= 133;
	*(DWORD*)0x00E76C73 -= 133;
	*(DWORD*)0x00E76CFE -= 133 - 6;
	//*(DWORD*)0x00E76D36 -= 133;
	//*(DWORD*)0x00E76D3E -= 133;
	//*(DWORD*)0x00E76D7C -= 133;

	//右上角频道，副本提示文本
	*(DWORD*)0x004C40B8 -= 160;
	*(DWORD*)0x004C414D -= 130;
	*(DWORD*)0x004C41C2 -= 130;
	*(DWORD*)0x004C41A0 -= 130;
	*(DWORD*)0x004D2BF3 -= 160;
	*(DWORD*)0x004D2DBC -= 130;


	//npc 点击菜单坐标
	*(DWORD*)0x0100B3A6 = Width;
	*(DWORD*)0x0100B3AD = Width - 100;
	*(DWORD*)0x0100B3C9 = Height;
	*(DWORD*)0x0100B3D0 = Height;

	*(BYTE*)0x004D2B8F = HUD_BASE_X;
	*(DWORD*)0x004D2B8A = HUD_BASE_Y;
	*(DWORD*)0x004D676F = HUD_BASE_W;
	*(DWORD*)0x004D678A = HUD_BASE_Y - 3;
	//血球
	int x = HUD_BASE_X + 12;
	int y = HUD_BASE_Y + 16;
	*(BYTE*)0x0043B255 = x;//扣血血球X
	*(DWORD*)0x0043B250 = y;//扣血血球Y
	*(BYTE*)0x0043B2D8 = x;//扣血白罩子血球X
	*(DWORD*)0x0043B2D3 = y;//扣血白罩子血球Y
	*(BYTE*)0x0043B202 = x;//血球X
	*(DWORD*)0x0043B1FD = y;//血球Y
	*(DWORD*)0x0043B1D6 = y + 56;//血球遮罩开始Y
	*(DWORD*)0x0043B1CE = y + 56;//血球遮罩结束Y
	//血球信息弹窗
	*(BYTE*)0x004CF10A = x + 36;//HP文字标识 X轴
	*(DWORD*)0x004CF105 = y - 5;//HP文字标识 Y轴  
	*(BYTE*)0x004CF058 = -(x - 2);//HP识别区域 X轴 EB → lea edx,[edi-15]
	*(DWORD*)0x004CF064 = -(y - 1);//HP识别区域 Y轴 FFFFFDF3 → lea eax,[esi-0000020D]

	//蓝球
	x = HUD_BASE_X + (HUD_BASE_W - 12 - 56);
	y = HUD_BASE_Y + 16;
	*(DWORD*)0x0043B3E3 = x;//乘骑蓝球X
	*(DWORD*)0x0043B3DE = y;//乘骑蓝球Y
	*(DWORD*)0x0043B46D = x;//异常蓝球X
	*(DWORD*)0x0043B468 = y;//异常蓝球Y
	*(DWORD*)0x0043B38D = x;//蓝球X
	*(DWORD*)0x0043B388 = y;//蓝球Y
	*(DWORD*)0x0043B361 = y + 56;//蓝球遮罩开始Y
	*(DWORD*)0x0043B359 = y + 56;//蓝球遮罩结束Y
	//蓝球信息弹窗
	*(BYTE*)0x004CF1DA = x + 20;//HP文字标识 X轴
	*(DWORD*)0x004CF1D5 = y - 5;//HP文字标识 Y轴  
	*(DWORD*)0x004CF122 = -(x - 2);//HP识别区域 X轴 EB → lea edx,[edi-15]
	*(DWORD*)0x004CF131 = -(y - 1);//HP识别区域 Y轴 FFFFFDF3 → lea eax,[esi-0000020D]

	//buff
	x = HUD_BASE_X + 86;
	y = HUD_BASE_Y + 20;
	*(BYTE*)0x004D1776 = x;//图标X
	*(DWORD*)0x004D1755 = y;//图标Y
	*(BYTE*)0x004C7F62 = x;//提示文字坐标X
	*(DWORD*)0x004C7F5A = y - 2;//提示文字坐标Y
	*(BYTE*)0x00BFCD83 = 0xEB;
	*(BYTE*)0x0093288B = 0xEB;//技能不显示buf图标
	

	//活动图标
	*(BYTE*)0x004E783F = 68;//图标X
	*(DWORD*)0x004E782F = y;//图标Y
	*(DWORD*)0x004E7813 = 0x66666667; *(BYTE*)0x004E7827 = 0x80; *(WORD*)0x004E7828 = 0x9090; *(WORD*)0x004E7835 = 0xC289; *(BYTE*)0x004E7837 = 0x90;// 图标Y
	*(WORD*)0x004E9AD5 = 0x5DEB;//不显示TP
	*(WORD*)0x004E9B3F = 0x46EB;//不显示黑砖
	//*(BYTE*)0x004E9B35 = 0x2A;//修复黑砖
	writeCallCode((LPVOID*)0x014EB185, (LPVOID)hookHudInfoBtnMgr__init_4EBD70);
	writeCallCode((LPVOID*)0x004EBA51, (LPVOID)hookHudInfoBtnMgr__makeBtn_4E9A80);
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x4E9520, (gpointer)hookHudInfoBtnMgr__newBtn_4E9520, (gpointer*)&HudInfoBtnMgr__newBtn_4E9520);


	//疲劳
	x = HUD_BASE_X + 277;
	y = HUD_BASE_Y + 45;
	*(DWORD*)0x004C42A5 = 86;//疲劳宽度
	*(DWORD*)0x004C42C6 = x;//疲劳 X轴
	*(DWORD*)0x004C4320 = x;//疲劳 X轴
	*(DWORD*)0x004C42BB = x;//疲劳 X轴
	*(DWORD*)0x004C4266 = x;//疲劳 X轴
	*(DWORD*)0x004C431B = y;//疲劳 Y轴
	*(DWORD*)0x004C42C1 = y;//疲劳 Y轴
	*(DWORD*)0x004C4261 = y;//疲劳 Y轴
	*(DWORD*)0x004C4355 = x + 28;//疲劳图标x
	*(DWORD*)0x004C4350 = y - 6;//疲劳图标y
	*(DWORD*)0x004C43E0 = x + 28;//疲劳图标闪烁x
	*(DWORD*)0x004C43DB = y - 6;//疲劳图标闪烁y
	*(DWORD*)0x004C44CA = x - 9;//疲劳图标指示闪烁x
	*(DWORD*)0x004C44C5 = y - 9;//疲劳图标指示闪烁y

	*(DWORD*)0x004CF765 = x + 43;//疲劳值文字标识 X轴   
	*(DWORD*)0x004CF760 = y - 5;//疲劳值文字标识 Y轴   
	*(DWORD*)0x004CF8C7 = x + 60;//疯狂阶段文字标识① X轴
	*(DWORD*)0x004CF8C2 = y - 5;//疯狂阶段文字标识① Y轴
	*(DWORD*)0x004CF944 = x + 60;//疯狂阶段文字标识② X轴
	*(DWORD*)0x004CF93F = y - 5;//疯狂阶段文字标识② Y轴

	*(BYTE*)0x004CF5FB = 85;//疲劳条识别区域宽度
	*(BYTE*)0x004CF60D = 7;//疲劳条识别区域高度
	*(DWORD*)0x004CF5F5 = -x;//疲劳条识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
	*(DWORD*)0x004CF607 = -(y - 3);//疲劳条识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

	//等级LV
	x = HUD_BASE_X + 26;
	y = HUD_BASE_Y + 77;
	*(DWORD*)0x004C2067 = x;//X
	*(DWORD*)0x004C208B = y;//lv Y
	*(DWORD*)0x004C209B = y;//数值 Y

	x = HUD_BASE_X + 54;
	y = HUD_BASE_Y + 74;
	*(DWORD*)0x004C20FE = x;//pk X
	*(DWORD*)0x004C20E6 = y;//pk Y
	*(DWORD*)0x004C214D = x ;//pk X
	*(DWORD*)0x004C212F = y;//pk Y

	//sp
	x = HUD_BASE_X + 604;
	y = HUD_BASE_Y + 77;
	*(DWORD*)0x004D2E9B = x;//X
	*(DWORD*)0x004D2E96 = y;//Y
	*(BYTE*)0x004CF99B = 40;//sp识别区域宽度
	*(BYTE*)0x004CF9A6 = 14;//sp识别区域高度
	*(DWORD*)0x004CF995 = -x;//sp识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
	*(DWORD*)0x004CF9A0 = -y;//sp识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

	//经验条
	x = HUD_BASE_X + 72;
	y = HUD_BASE_Y + 83;
	*(BYTE*)0x004C0F24 = x;//X
	*(DWORD*)0x004C0F1F = y;//Y
	*(BYTE*)0x004C0FAD = x;//X
	*(DWORD*)0x004C0FA8 = y;//Y
	*(BYTE*)0x004C0F6E = x;//X
	*(DWORD*)0x004C0F69 = y;//Y

	*(float*)0x01575354 = 497.0f;
	*(DWORD*)0x004C0E99 = 497;
	*(DWORD*)0x004C0ED3 = 497;
	*(DWORD*)0x004C0E80 = 497;
	*(DWORD*)0x004C0E71 = 497;

	*(BYTE*)0x004C0EE8 = x;
	*(DWORD*)0x004C0F44 = 497 + x;
	//*(DWORD*)0x004C0EE2 = 300;//y
	//*(DWORD*)0x004C0F3F = 300;//Y

	*(DWORD*)0x004CF1F8 = 497;//经验条识别区域宽度
	*(BYTE*)0x004CF20A = 8;//经验条识别区域高度
	*(BYTE*)0x004CF1F5 = -x;//经验条识别区域 X轴 FFFFFEAF → lea edx,[edi-00000151]
	*(DWORD*)0x004CF204 = -(y - 3);//经验条识别区域 Y轴 FFFFFDDD → lea eax,[esi-00000223]

	////技能栏
   //seal 按钮
	//*(DWORD*)0x004D6BBC = HUD_BASE_X + 365;//X
	//*(DWORD*)0x004D6BB7 = HUD_BASE_Y + 15;//Y

	*(BYTE*)0x004BBB59 = 0xEB;//nut技能坐标函数跳过
	x = HUD_BASE_X + 379;
	y = HUD_BASE_Y + 50;
	*(DWORD*)0x004D68A9 = x;//X
	*(DWORD*)0x004D68EF = y;//Y
	*(DWORD*)0x004D690C = x + 6 * 30;

	//扩展技能栏
	*(DWORD*)0x004D694E = x;//X
	*(DWORD*)0x004D6994 = y - 35;//Y
	*(DWORD*)0x004D69BE = x + 6 * 30;//X

	//物品栏
	*(DWORD*)0x004D683F = HUD_BASE_X + 84;//X
	*(DWORD*)0x004D6885 = y;//Y
	*(DWORD*)0x004D68A2 = *(DWORD*)0x004D683F + 6 * 30;//最大宽度
	//GumInterceptor* v = gum_interceptor_obtain();
	//gum_interceptor_replace_fast(v, (gpointer)0xE84540, (gpointer)drawHub70Btn, (gpointer*)&UiMgr__init_E84540);

	//技能冷却提示
	*(DWORD*)0x004D2E37 = 377;//x
	*(DWORD*)0x004D2E2B = 380;//两行技能栏 Y
	*(DWORD*)0x004D2E15 = 414;//单行技能栏 Y


	//耐久度图标
	*(DWORD*)0x004BD3BB = GetUiWPos(CurrentUiW, 800, *(DWORD*)0x004BD3BB);//X
	*(DWORD*)0x004BD3B6 = GetUiHPos(CurrentUiH/2, 600 / 2, *(DWORD*)0x004BD3B6);//Y
	*(DWORD*)0x004BD2E1 = GetUiWPos(CurrentUiW, 800, *(DWORD*)0x004BD2E1);//X
	*(DWORD*)0x004BD2DC = GetUiHPos(CurrentUiH/2, 600 / 2, *(DWORD*)0x004BD2DC);//Y

	writeCallCode((LPVOID*)0x004D2DEF, (LPVOID)hookDrawExpHpMpView);
}

int __fastcall fixLoadingGame(int* thisP, int edx, int x, int y, int a4, float a5, float a6, float a7, int a8, float a9, float a10) {
	return drawImgByXY2_11B41E0(thisP, 0, 0, a4, 1.0f, 1.0f, a7, a8, a9, a10);
}

thisCall4Args2 sub_F987C0 = (thisCall4Args2)0xF987C0;
int __fastcall hookSub_F987C0(int* thisP, int, int a2, int a3, int a4, int a5) {
	//printf("pos:[%d, %d, %d, %d]\n", a2, a3, a4, a5);
	int ret = sub_F987C0(thisP, a2, a3, a4, a5);
	int x = BasePopupWin__getPosX_EF65C0(thisP);
	int y = BasePopupWin__getPosY_EF65D0(thisP);
	int w = BasePopupWin__getWinWidth_EF5E60(thisP);
	//int h = BasePopupWin__getWinHeight_EF5E90(thisP);
	//printf("win:[%d, %d, %d, %d]\n", x, y, w, h);
	if (x < 0) x = 0;
	else if(x + w > 640) x = 640 - w;
	setUiComponentPos_11BEAD0((int *)thisP[3], x, y, 1);
	return ret;
}

thisCall1Args2 procDungeonQuestIcon_10776E0 = (thisCall1Args2)0x10776E0;
int __fastcall hookProcDungeonQuestIcon_10776E0(int* thisP, int, int a2) {
	return procDungeonQuestIcon_10776E0(thisP, 0);
}


void __fastcall drawQuestIconAnim(int* thisP, int, int alpha, int x, int y, int mirror, int zoom) {
	if (alpha == 0xFFFFFFFF) {//有任务
		CNRDAnimation__Proc_109C4C0(thisP);
		CNRDAnimation__Draw_1096580(thisP, *(int*)0x1B5582C, x - 2, y - 5, mirror, zoom);
	}
	return;
}

forceinline void init70_selectDungeon(void) {
	//按钮
	*(DWORD*)0x011179BB -= 150;//X
	*(DWORD*)0x011179FC -= 120;//Y
	*(BYTE*)0x01117A08 = 0x50;//Y
	////练习模式按钮
	//*(DWORD*)0x011179C0 = 3;//X
	//*(DWORD*)0x0111E49E -= 150;//X
	//*(DWORD*)0x0111E499 -= 120;//Y

	//ui/party/quickpartyselectdungeon.ui
	*(DWORD*)0x006AC767 -= 160;//困难度图标 X

	writeCallCode((LPVOID*)0x0111A78E, (LPVOID)fixLoadingGame);

	*(DWORD*)0x011252F8 = 413;//深渊火焰Y

	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0xF987C0, (gpointer)hookSub_F987C0, (gpointer*)&sub_F987C0);

	//隐藏领主粉掉落提示窗口
	writeNopCode((void*)0x0111D542, 13);

	//领主粉掉落/人物窗口偏移
	*(DWORD*)0x01076C7F = 640;//X

	//去掉播放 selectdungeon_notice_quest_default.ani
	//*(BYTE*)0x010778F5 = 0xE9; *(DWORD*)0x010778F6 = 0x000000D1;
	//*(BYTE*)0x010778F7 = 0xFC;
	*(BYTE*)0x010778F5 = 0x8B; *(DWORD*)0x010778F6 = 0x0BEBE845;
	*(BYTE*)0x010779C2 = 0xFC;
	writeCallCode((LPVOID*)0x010779C6, (LPVOID)drawQuestIconAnim);
	*(WORD*)0x010779A2 = 0x27EB;
	*(WORD*)0x010779E2 = 0x27EB;
	*(BYTE*)0x0107794C = 61;
	*(BYTE*)0x0107789F = 61;

	

	//未选择任务图标位置
	*(BYTE*)0x0107778E += 8;
	*(BYTE*)0x01077794 += 8;
	*(BYTE*)0x0107779E += 5;
	//选择任务图标位置
	*(BYTE*)0x01077763 += 8;
	*(BYTE*)0x01077770 += 5;
	*(BYTE*)0x01077753 += 8;
	*(BYTE*)0x0107775D += 5;

	//未选择任务图标动画位置
	*(BYTE*)0x0107742D += 8;
	*(BYTE*)0x0107741B += 8;
	*(BYTE*)0x01077442 += 5;
	//选择任务图标动画位置
	*(BYTE*)0x010773F9 += 8;
	*(BYTE*)0x010773D2 += 8;
	*(BYTE*)0x010773E7 += 5;
}

void init70_delay(void) {
	setRandView(-160, -125);
	initOld70Hub(538, 25);
	//drawHitCombo_8EE7F0
	writeCallCode((LPVOID*)0x8EEB07, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EEDBC, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EEDF2, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EEE41, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EEF89, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EF006, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8EEB2B, (LPVOID)imgFixPosDraw2);

	//drawDamageValue_8E7B70
	writeCallCode((LPVOID*)0x8E7C13, (LPVOID)imgFixPosDraw);
	writeCallCode((LPVOID*)0x8E7C99, (LPVOID)imgFixPosDraw2);
}

forceinline void init70_loadingDungeonUi(void) {
	//加载背景图
	*(DWORD*)0x0111A731 = 640;//800
	*(DWORD*)0x0111A778 = 480;//800

	int yPos = 110;
	*(DWORD*)0x01117DD0 -= 80;//X
	*(DWORD*)0x01117DD7 -= yPos;//X

	*(BYTE*)0x01117FAB -= 80;//x
	*(DWORD*)0x01118018 -= yPos;//y
	*(DWORD*)0x011180B0 -= yPos;//y
	*(DWORD*)0x011180ED -= yPos;//y
	*(DWORD*)0x0111812D -= yPos;//y
	*(DWORD*)0x01118192 -= yPos;//y
	*(DWORD*)0x011181F9 -= yPos;//y
	*(DWORD*)0x01118274 -= yPos;//y
	*(DWORD*)0x01118311 -= yPos;//y
	*(DWORD*)0x01118484 -= yPos;//y

	*(DWORD*)0x011182E5 -= 160;//X
	*(DWORD*)0x011182E0 -= yPos;//y

	*(DWORD*)0x01118345 -= 160;//X
	*(DWORD*)0x01118340 -= yPos;//y
}


forceinline void npcDialog(GumInterceptor* v) {



	//*(BYTE*)0x00FB4B20 = 1;
	//*(BYTE*)0x00FB4B2F = 1;
	//gum_interceptor_replace_fast(v, (gpointer)0xFB4AB0, (gpointer)hookNpcDialogWin__setNpcGifEnable_FB4AB0, (gpointer*)&NpcDialogWin__setNpcGifEnable_FB4AB0);
	/*
	this[0xE9] type
	this[0xBA] = getPreloadImg_11BB1B0((_DWORD *)ImgPreloadMgrBase_1A6A870, 55u);// Sprite/interface2/npc_dialogue_UI.img
	this[0xBB] = getPreloadImg_11BB1B0((_DWORD *)ImgPreloadMgrBase_1A6A870, 56u);// Sprite/interface/NPC_Dialog_Face.img
	this[0xBC] = getPreloadImg_11BB1B0((_DWORD *)ImgPreloadMgrBase_1A6A870, 58u);// Sprite/interface/Tutorial02/TutorialImage.img
	*/

	//NpcDialogWin::Proc_FB76F0
	*(DWORD*)0x00FB77E9 = 8;//x
	*(DWORD*)0x00FB77D1 = 8;//x
	*(DWORD*)0x00FB77E4 -= 120;//y

	//initNpcDialog_FBBD50
	*(DWORD*)0x00FBBEAD = 564;//w
	*(DWORD*)0x00FBC5E3 *= 0.8f;//文本框w
	*(DWORD*)0x00FBC692 *= 0.8f;//未知框w
	//*(DWORD*)0x00FBCD92 *= 0.8f;//未知框w 

	//NpcDialogWin::drawFaceAndTitle_FB51D0
	*(DWORD*)0x00FB5213 -= 80;//回车按钮x
	*(DWORD*)0x00FB5228 -= 80;//回车按钮x
	*(DWORD*)0x00FBACBE *= 0.8f;//奖励区域下横线x

	//接受按钮x this[0x77]
	*(DWORD*)0x00FBB42B *= 0.8f;
	*(DWORD*)0x00FBB2B9 *= 0.8f;

	int pos = *(DWORD*)0x00FBB42B + 55;
	//放弃按钮x this[0x79]
	*(DWORD*)0x00FBB445 = pos;
	*(DWORD*)0x00FBB2D3 = pos;
	//完成按钮x this[0x76]
	*(DWORD*)0x00FBB467 = pos;
	*(DWORD*)0x00FBB2F5 = pos;
	//完成按钮x this[0x76]
	*(DWORD*)0x00FBB47F = pos;
	*(DWORD*)0x00FBB30D = pos;
	//接受祝福按钮x this[0x15C]
	*(DWORD*)0x00FBC018 -= 60;
	*(DWORD*)0x00FBB47F = pos;
	*(DWORD*)0x00FBB30D = pos;
	//*(BYTE*)0x00FBC014 -= 120;//接受祝福按钮y

	*(DWORD*)0x00FBC018 -= 100;//选手等级按钮x this[0x78]
	*(DWORD*)0x00FBC30D -= 100;//赠送按钮x this[0x96]
	*(DWORD*)0x00FBC3BE -= 100;//关闭按钮x this[0x97]
	*(DWORD*)0x00FBC47A -= 100;//继续赠送按钮x this[0x98]

	//*(DWORD*)0x00FBBF5B -= 80;//接受按钮x this[0x77]
	//*(DWORD*)0x00FBC018 -= 80;//选手等级按钮x this[0x78]
	//*(DWORD*)0x00FBC19C -= 80;//放弃按钮x this[0x79]
	//*(DWORD*)0x00FBC258 -= 80;//完成按钮x this[0x76]
	//*(DWORD*)0x00FBC30D -= 80;//赠送按钮x this[0x96]
	//*(DWORD*)0x00FBC3BE -= 80;//关闭按钮x this[0x97]
	//*(DWORD*)0x00FBC47A -= 80;//继续赠送按钮x this[0x98]
	////*(BYTE*)0x00FBBF55 -= 120;//总按钮y

	//*(DWORD*)0x00FBC57F -= 100;//跳过图标按钮x
	////*(BYTE*)0x00FBC57B -= 120;//跳过图标按钮y
}

thisCall6Args2 drawMonsterHp_43ABC0;
int __fastcall hookDrawMonsterHp_43ABC0(int* thisP, int, int x, int y, int a4, int a5, int a6, int a7) {

	return drawMonsterHp_43ABC0(thisP, x, y - 60, a4, a5, a6, a7);

}

void fault(void) {
	while (1);
}


thisCall1Args2 setMonsterHpLength_4BC4F0 = (thisCall1Args2)0x4BC4F0;

forceinline void monsterHp() {
	//长度
	*(DWORD*)0x00E7C121 = 475;//保护
	*(BYTE*)0x0043D8FF -= 60;
	*(BYTE*)0x0043D8F2 -= 60;
	*(BYTE*)0x0043D8E5 -= 60;

	*(DWORD*)0x0043AB77 -= 65;//数量x
	*(DWORD*)0x0043AB7C -= 60;//数量y
	*(DWORD*)0x0043AB8B -= 60;//数量y
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x43ABC0, (gpointer)hookDrawMonsterHp_43ABC0, (gpointer*)&drawMonsterHp_43ABC0);
	//gum_interceptor_replace_fast(v, (gpointer)0x760E70, (gpointer)hookCNGameCore__onChangeModule_760E70, (gpointer*)&CNGameCore__onChangeModule_760E70);
}
#define NEW
#ifdef NEW
thisCall1Args2 myDungeonResultView__ProcDraw_10304B0;
int __fastcall hookDungeonResultView__ProcDraw_10304B0(int* thisP, int, int a2) {
	return myDungeonResultView__ProcDraw_10304B0(thisP, a2);
}

forceinline void dungeonResult(GumInterceptor* v) {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();
	int ResultPosX = 150;
	int ResultPosY = 40;

	//hook->resize(4);
	//b = hook->begin();
	//b++->setValue(H_DWORD, 0x0102B97E, *(DWORD*)0x0102B97E - ResultPosX);
	//b++->setValue(H_DWORD, 0x0102B979, *(DWORD*)0x0102B979 - ResultPosY);
	//b++->setValue(H_DWORD, 0x0102B998, *(DWORD*)0x0102B998 - ResultPosX);
	//b++->setValue(H_DWORD, 0x0102B993, *(DWORD*)0x0102B993 - ResultPosY);
	//thisCall2 playNewRecordAnimal_102B950 = (thisCall2)tools_relocation_hook(0x102B950, 0x0102B9F0, hook);

	hook->resize(55 - 4);
	b = hook->begin();
	b++->setValue(H_DWORD, 0x0102CB07, 640 - 372);
	b++->setValue(H_DWORD, 0x0102CB29, 640);
	b++->setValue(H_DWORD, 0x0102CB24, 640 - 372);
	b++->setValue(H_DWORD, 0x0102CD85, *(DWORD*)0x0102CD85 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102CE1E, *(DWORD*)0x0102CE1E - ResultPosX);
	b++->setValue(H_BYTE, 0x0102CE1C, *(BYTE*)0x0102CE1C - 20);
	b++->setValue(H_DWORD, 0x0102CE5F, *(DWORD*)0x0102CE5F - ResultPosX);
	b++->setValue(H_DWORD, 0x0102CE87, *(DWORD*)0x0102CE87 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102CE82, *(DWORD*)0x0102CE82 - ResultPosX);
	b++->setValue(H_BYTE, 0x0102CF14, *(BYTE*)0x0102CF14 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D096, *(DWORD*)0x0102D096 - (ResultPosX - 18));
	b++->setValue(H_DWORD, 0x0102D091, *(DWORD*)0x0102D091 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D0D3, *(DWORD*)0x0102D0D3 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D0F2, *(DWORD*)0x0102D0F2 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D17F, *(DWORD*)0x0102D17F - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D27B, *(DWORD*)0x0102D27B - ResultPosX);
	b++->setValue(H_BYTE, 0x0102D279, *(BYTE*)0x0102D279 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D301, *(DWORD*)0x0102D301 - ResultPosX);
	b++->setValue(H_BYTE, 0x0102D2FF, *(BYTE*)0x0102D2FF - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D45E, *(DWORD*)0x0102D45E - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D459, *(DWORD*)0x0102D459 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D4E7, *(DWORD*)0x0102D4E7 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D4E2, *(DWORD*)0x0102D4E2 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D5D8, *(DWORD*)0x0102D5D8 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D5D3, *(DWORD*)0x0102D5D3 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D6F3, *(DWORD*)0x0102D6F3 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D6EE, *(DWORD*)0x0102D6EE - ResultPosY);

	//b++->setValue(H_DWORD, 0x0102D87A, *(DWORD*)0x0102D87A - ResultPosX);
	//b++->setValue(H_DWORD, 0x0102D875, *(DWORD*)0x0102D875 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102D87A, -10000);//屏蔽最佳记录x
	b++->setValue(H_DWORD, 0x0102D875, -10000);//屏蔽最佳记录y

	b++->setValue(H_DWORD, 0x0102D919, *(DWORD*)0x0102D919 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D983, *(DWORD*)0x0102D983 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102D93D, *(DWORD*)0x0102D93D - (ResultPosY + 18));
	b++->setValue(H_DWORD, 0x0102D938, *(DWORD*)0x0102D938 - (ResultPosY + 18));
	b++->setValue(H_DWORD, 0x0102DB3E, *(DWORD*)0x0102DB3E - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DB39, *(DWORD*)0x0102DB39 - (ResultPosY + 18));
	b++->setValue(H_DWORD, 0x0102DBA7, *(DWORD*)0x0102DBA7 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DBA2, *(DWORD*)0x0102DBA2 - (ResultPosY + 18));
	b++->setValue(H_DWORD, 0x0102DC27, *(DWORD*)0x0102DC27 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DC22, *(DWORD*)0x0102DC22 - (ResultPosY + 18));
	b++->setValue(H_DWORD, 0x0102DD24, *(DWORD*)0x0102DD24 - ResultPosX);
	b++->setValue(H_BYTE, 0x0102DD22, *(BYTE*)0x0102DD22 - 20);
	ResultPosY -= 20;
	b++->setValue(H_DWORD, 0x0102DDB9, *(DWORD*)0x0102DDB9 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DDB4, *(DWORD*)0x0102DDB4 - (ResultPosY + 60));
	b++->setValue(H_DWORD, 0x0102DDDB, *(DWORD*)0x0102DDDB - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DDD6, *(DWORD*)0x0102DDD6 - (ResultPosY + 60));
	b++->setValue(H_DWORD, 0x0102DE5A, *(DWORD*)0x0102DE5A - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DE55, *(DWORD*)0x0102DE55 - ResultPosY);
	//加百利
	b++->setValue(H_DWORD, 0x0102CC39, *(DWORD*)0x0102CC39 - 80);
	b++->setValue(H_DWORD, 0x0102CC62, *(DWORD*)0x0102CC62 - 80);
	b++->setValue(H_DWORD, 0x0102CCC5, *(DWORD*)0x0102CCC5 - 80);
	//b++->setValue(H_CALL, 0x0102D897, (int)playNewRecordAnimal_102B950);
	b++->setValue(H_NOP, 0x0102D897, 5);//屏蔽新最佳记录动画
	thisCall2 sub_102CAF0 = (thisCall2)tools_relocation_hook(0x102CAF0, 0x0102DEBB, hook);
	//加百利
	*(DWORD*)0x0102C2CC -= 80;
	*(DWORD*)0x0102C32D -= 80;

	//102DEC0
	hook->resize(110);
	b = hook->begin();
	b++->setValue(H_DWORD, 0x0102DEFC, *(DWORD*)0x0102DEFC - ResultPosX);
	b++->setValue(H_DWORD, 0x0102DEE0, *(DWORD*)0x0102DEE0 - ResultPosX);
	b++->setValue(H_BYTE, 0x0102DF89, *(BYTE*)0x0102DF89 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E085, *(DWORD*)0x0102E085 - ResultPosX);
	b++->setValue(H_BYTE, 0x0102E083, *(BYTE*)0x0102E083 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E119, *(DWORD*)0x0102E119 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E114, *(DWORD*)0x0102E114 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E22C, *(DWORD*)0x0102E22C - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E227, *(DWORD*)0x0102E227 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E2AD, *(DWORD*)0x0102E2AD - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E2B5, *(DWORD*)0x0102E2B5 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E362, *(DWORD*)0x0102E362 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E346, *(DWORD*)0x0102E346 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E3EF, *(DWORD*)0x0102E3EF - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E4A8, *(DWORD*)0x0102E4A8 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E4A3, *(DWORD*)0x0102E4A3 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E54D, *(DWORD*)0x0102E54D - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E4EE, *(DWORD*)0x0102E4EE - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E4E9, *(DWORD*)0x0102E4E9 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E565, *(DWORD*)0x0102E565 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E61C, *(DWORD*)0x0102E61C - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E617, *(DWORD*)0x0102E617 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E6C2, *(DWORD*)0x0102E6C2 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E662, *(DWORD*)0x0102E662 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E65D, *(DWORD*)0x0102E65D - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E6DA, *(DWORD*)0x0102E6DA - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E792, *(DWORD*)0x0102E792 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E78D, *(DWORD*)0x0102E78D - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E838, *(DWORD*)0x0102E838 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E7D8, *(DWORD*)0x0102E7D8 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E7D3, *(DWORD*)0x0102E7D3 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E850, *(DWORD*)0x0102E850 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E908, *(DWORD*)0x0102E908 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E903, *(DWORD*)0x0102E903 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E9AD, *(DWORD*)0x0102E9AD - ResultPosX);
	b++->setValue(H_DWORD, 0x0102E94E, *(DWORD*)0x0102E94E - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E949, *(DWORD*)0x0102E949 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102E9C5, *(DWORD*)0x0102E9C5 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EA7C, *(DWORD*)0x0102EA7C - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EA77, *(DWORD*)0x0102EA77 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EB22, *(DWORD*)0x0102EB22 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EAC2, *(DWORD*)0x0102EAC2 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EABD, *(DWORD*)0x0102EABD - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EB3A, *(DWORD*)0x0102EB3A - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EBF2, *(DWORD*)0x0102EBF2 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EBED, *(DWORD*)0x0102EBED - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EC98, *(DWORD*)0x0102EC98 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EC38, *(DWORD*)0x0102EC38 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EC33, *(DWORD*)0x0102EC33 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102ECB0, *(DWORD*)0x0102ECB0 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EDF0, *(DWORD*)0x0102EDF0 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EDEB, *(DWORD*)0x0102EDEB - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EE71, *(DWORD*)0x0102EE71 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EE79, *(DWORD*)0x0102EE79 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102EF96, *(DWORD*)0x0102EF96 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102EF7A, *(DWORD*)0x0102EF7A - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F020, *(DWORD*)0x0102F020 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F0B3, *(DWORD*)0x0102F0B3 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F19E, *(DWORD*)0x0102F19E - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F198, *(DWORD*)0x0102F198 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F20D, *(DWORD*)0x0102F20D - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F208, *(DWORD*)0x0102F208 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F354, *(DWORD*)0x0102F354 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F338, *(DWORD*)0x0102F338 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F3D1, *(DWORD*)0x0102F3D1 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F44E, *(DWORD*)0x0102F44E - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F569, *(DWORD*)0x0102F569 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F563, *(DWORD*)0x0102F563 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F5D9, *(DWORD*)0x0102F5D9 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F5D4, *(DWORD*)0x0102F5D4 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F71A, *(DWORD*)0x0102F71A - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F6FE, *(DWORD*)0x0102F6FE - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F79D, *(DWORD*)0x0102F79D - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F819, *(DWORD*)0x0102F819 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F8FF, *(DWORD*)0x0102F8FF - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F8F9, *(DWORD*)0x0102F8F9 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102F96F, *(DWORD*)0x0102F96F - ResultPosX);
	b++->setValue(H_DWORD, 0x0102F96A, *(DWORD*)0x0102F96A - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FAB1, *(DWORD*)0x0102FAB1 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FA95, *(DWORD*)0x0102FA95 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FB32, *(DWORD*)0x0102FB32 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FBAE, *(DWORD*)0x0102FBAE - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FCC4, *(DWORD*)0x0102FCC4 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FCBE, *(DWORD*)0x0102FCBE - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FD34, *(DWORD*)0x0102FD34 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FD2F, *(DWORD*)0x0102FD2F - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FE76, *(DWORD*)0x0102FE76 - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FE5A, *(DWORD*)0x0102FE5A - ResultPosX);
	b++->setValue(H_DWORD, 0x0102FEF7, *(DWORD*)0x0102FEF7 - ResultPosY);
	b++->setValue(H_DWORD, 0x0102FF73, *(DWORD*)0x0102FF73 - ResultPosY);
	b++->setValue(H_DWORD, 0x01030059, *(DWORD*)0x01030059 - ResultPosX);
	b++->setValue(H_DWORD, 0x01030053, *(DWORD*)0x01030053 - ResultPosY);
	b++->setValue(H_DWORD, 0x010300C9, *(DWORD*)0x010300C9 - ResultPosX);
	b++->setValue(H_DWORD, 0x010300C4, *(DWORD*)0x010300C4 - ResultPosY);
	b++->setValue(H_DWORD, 0x0103020A, *(DWORD*)0x0103020A - ResultPosX);
	b++->setValue(H_DWORD, 0x01030205, *(DWORD*)0x01030205 - ResultPosX);
	b++->setValue(H_DWORD, 0x0103028D, *(DWORD*)0x0103028D - ResultPosY);
	b++->setValue(H_DWORD, 0x0103031A, *(DWORD*)0x0103031A - ResultPosY);
	b++->setValue(H_DWORD, 0x01030431, *(DWORD*)0x01030431 - ResultPosX);
	b++->setValue(H_DWORD, 0x0103042C, *(DWORD*)0x0103042C - (ResultPosY + 60));
	thisCall2 sub_102DEC0 = (thisCall2)tools_relocation_hook(0x102DEC0, 0x010304A4, hook);

	hook->resize(2);
	b = hook->begin();
	b++->setValue(H_CALL, 0x010304C5, (int)sub_102CAF0);
	b++->setValue(H_CALL, 0x010304D0, (int)sub_102DEC0);
	myDungeonResultView__ProcDraw_10304B0 = (thisCall1Args2)tools_relocation_hook(0x10304B0, 0x010304DA, hook);
	*(DWORD*)0x01813314 = (int)hookDungeonResultView__ProcDraw_10304B0;
	delete hook;

}
#else
forceinline void dungeonResult(GumInterceptor* v) {
	int ResultPosX = 150;
	int ResultPosY = 40;
	//sub_102CAF0 0102DEBB
	//背景滑动出现 imgPos 0
	*(DWORD*)0x0102CB07 = 640 - 372;//背景x
	*(DWORD*)0x0102CB29 = 640;//开始x
	*(DWORD*)0x0102CB24 = 640 - 372;//结束x
	//*(BYTE*)0x0102CBA8 -= ResultPosY;//y

	//大魔法阵背景 imgPos 8
	*(DWORD*)0x0102CD85 -= ResultPosX;//背景x
	//*(BYTE*)0x0102CD83 -= ResultPosY;//y

	//评分 imgPos 1
	*(DWORD*)0x0102CE1E -= ResultPosX;//背景x
	*(BYTE*)0x0102CE1C -= 20;//y

	//连击杀伤率框滑动出现 imgPos 2
	*(DWORD*)0x0102CE5F -= ResultPosX;//背景x
	*(DWORD*)0x0102CE87 -= ResultPosX;//开始x
	*(DWORD*)0x0102CE82 -= ResultPosX;//结束x
	*(BYTE*)0x0102CF14 -= ResultPosY;//y

	//小魔法阵背景 imgPos 4
	*(DWORD*)0x0102D096 -= ResultPosX - 18;//x
	*(DWORD*)0x0102D091 -= ResultPosY;//y

	//通关时间最佳纪录滑动出现 imgPos 3
	*(DWORD*)0x0102D0D3 -= ResultPosX;//结束x
	*(DWORD*)0x0102D0F2 -= ResultPosX;//开始x
	*(DWORD*)0x0102D17F -= ResultPosY;//y

	//活动加成 imgPos 11
	*(DWORD*)0x0102D27B -= ResultPosX;//x
	*(BYTE*)0x0102D279 -= ResultPosY;//y
	*(DWORD*)0x0102D301 -= ResultPosX;//x
	*(BYTE*)0x0102D2FF -= ResultPosY;//y

	//组队加成 imgPos 12
	*(DWORD*)0x0102D45E -= ResultPosX;//x
	*(DWORD*)0x0102D459 -= ResultPosY;//y
	*(DWORD*)0x0102D4E7 -= ResultPosX;//x
	*(DWORD*)0x0102D4E2 -= ResultPosY;//y

	//评分小图标 imgPos 18-26
	*(DWORD*)0x0102D5D8 -= ResultPosX;//x
	*(DWORD*)0x0102D5D3 -= ResultPosY;//y

	//数值记录
	*(DWORD*)0x0102D6F3 -= ResultPosX;//x
	*(DWORD*)0x0102D6EE -= ResultPosY;//y

	////数值记录2
	//*(DWORD*)0x0102D87A -= ResultPosX;//x
	//*(DWORD*)0x0102D875 -= ResultPosY;//y
	////新记录动画
	//*(DWORD*)0x0102B97E -= ResultPosX;//x
	//*(DWORD*)0x0102B979 -= ResultPosY;//y
	//*(DWORD*)0x0102B998 -= ResultPosX;//x
	//*(DWORD*)0x0102B993 -= ResultPosY;//y

	//数值记录2
	*(DWORD*)0x0102D87A = -10000;//x
	*(DWORD*)0x0102D875 = -10000;//y
	//新记录动画
	*(DWORD*)0x0102B97E = -10000;//x
	*(DWORD*)0x0102B979 = -10000;//y
	*(DWORD*)0x0102B998 = -10000;//x
	*(DWORD*)0x0102B993 = -10000;//y

	//评分大图标特效 Sprite/Interface2/Result_Ver2.0/Rank_Effect/Rank_Effect.img 
	*(DWORD*)0x0102D919 -= ResultPosX;//x
	*(DWORD*)0x0102D983 -= ResultPosX;//x
	*(DWORD*)0x0102D93D -= ResultPosY + 18; //start y
	*(DWORD*)0x0102D938 -= ResultPosY + 18; //end y

	//评分大图标字母 
	//Sprite/Interface2/Result_Ver2.0/Rank_Letter/Rank_Letter.img
	*(DWORD*)0x0102DB3E -= ResultPosX;//x
	*(DWORD*)0x0102DB39 -= ResultPosY + 18;//y
	//imgPos 5 
	*(DWORD*)0x0102DBA7 -= ResultPosX;//x
	*(DWORD*)0x0102DBA2 -= ResultPosY + 18;//y
	//Sprite/Interface2/Result_Ver2.0/Rank_Effect/Rank_Effect.img
	*(DWORD*)0x0102DC27 -= ResultPosX;//x
	*(DWORD*)0x0102DC22 -= ResultPosY + 18;//y

	//成绩 imgPos 6
	*(DWORD*)0x0102DD24 -= ResultPosX;//x
	*(DWORD*)0x0102DD22 -= 20;//y

	ResultPosY -= 20;
	//经验值框 imgPos 7
	*(DWORD*)0x0102DDB9 -= ResultPosX;//x
	*(DWORD*)0x0102DDB4 -= ResultPosY + 60;//y
	//经验值数值
	*(DWORD*)0x0102DDDB -= ResultPosX;//x
	*(DWORD*)0x0102DDD6 -= ResultPosY + 60;//y

	//幽灵状态图标 imgPos 28
	*(DWORD*)0x0102DE5A -= ResultPosX;//x
	*(DWORD*)0x0102DE55 -= ResultPosY;//y




	//102DEC0
	//评分框 imgPos 9
	*(DWORD*)0x0102DEFC -= ResultPosX;//开始x
	*(DWORD*)0x0102DEE0 -= ResultPosX;//结束x
	*(BYTE*)0x0102DF89 -= ResultPosY;//y

	//Sprite/Interface2/Result_Ver2.0/Rank_Letter/Rank_Letter.img
	*(DWORD*)0x0102E085 -= ResultPosX;//x
	*(BYTE*)0x0102E083 -= ResultPosY;//y
	//imgPos 5
	*(DWORD*)0x0102E119 -= ResultPosX;//x
	*(DWORD*)0x0102E114 -= ResultPosY;//y

	*(DWORD*)0x0102E22C -= ResultPosX;//x
	*(DWORD*)0x0102E227 -= ResultPosY;//y

	//活动值 imgPos 11
	*(DWORD*)0x0102E2AD -= ResultPosX;//x
	*(DWORD*)0x0102E2B5 -= ResultPosY;//y

	//其他加成框 imgPos 10
	*(DWORD*)0x0102E362 -= ResultPosX;//开始x
	*(DWORD*)0x0102E346 -= ResultPosX;//结束x
	*(DWORD*)0x0102E3EF -= ResultPosY;//y
	//组队加成 imgPos 12
	*(DWORD*)0x0102E4A8 -= ResultPosX;//x
	*(DWORD*)0x0102E4A3 -= ResultPosY;//y
	//组队加成 值
	*(DWORD*)0x0102E54D -= ResultPosX;//x
	*(DWORD*)0x0102E4EE -= ResultPosY;//开始y
	*(DWORD*)0x0102E4E9 -= ResultPosY;//结束y
	*(DWORD*)0x0102E565 -= ResultPosX;//x
	//师徒加成 imgPos 13
	*(DWORD*)0x0102E61C -= ResultPosX;//x
	*(DWORD*)0x0102E617 -= ResultPosY;//y
	//师徒加成 值
	*(DWORD*)0x0102E6C2 -= ResultPosX;//x
	*(DWORD*)0x0102E662 -= ResultPosY;//开始y
	*(DWORD*)0x0102E65D -= ResultPosY;//结束y
	*(DWORD*)0x0102E6DA -= ResultPosX;//x
	//装扮加成 imgPos 14
	*(DWORD*)0x0102E792 -= ResultPosX;//x
	*(DWORD*)0x0102E78D -= ResultPosY;//y
	//装扮加成 值
	*(DWORD*)0x0102E838 -= ResultPosX;//x
	*(DWORD*)0x0102E7D8 -= ResultPosY;//开始y
	*(DWORD*)0x0102E7D3 -= ResultPosY;//结束y
	*(DWORD*)0x0102E850 -= ResultPosX;//x
	//宠物加成 imgPos 15
	*(DWORD*)0x0102E908 -= ResultPosX;//x
	*(DWORD*)0x0102E903 -= ResultPosY;//y
	//宠物加成 值
	*(DWORD*)0x0102E9AD -= ResultPosX;//x
	*(DWORD*)0x0102E94E -= ResultPosY;//开始y
	*(DWORD*)0x0102E949 -= ResultPosY;//结束y
	*(DWORD*)0x0102E9C5 -= ResultPosX;//x
	//黑钻加成 imgPos 16
	*(DWORD*)0x0102EA7C -= ResultPosX;//x
	*(DWORD*)0x0102EA77 -= ResultPosY;//y
	//黑钻加成 值
	*(DWORD*)0x0102EB22 -= ResultPosX;//x
	*(DWORD*)0x0102EAC2 -= ResultPosY;//开始y
	*(DWORD*)0x0102EABD -= ResultPosY;//结束y
	*(DWORD*)0x0102EB3A -= ResultPosX;//x
	//对应频道加成 imgPos 17
	*(DWORD*)0x0102EBF2 -= ResultPosX;//x
	*(DWORD*)0x0102EBED -= ResultPosY;//y
	//对应频道加成 值
	*(DWORD*)0x0102EC98 -= ResultPosX;//x
	*(DWORD*)0x0102EC38 -= ResultPosY;//开始y
	*(DWORD*)0x0102EC33 -= ResultPosY;//结束y
	*(DWORD*)0x0102ECB0 -= ResultPosX;//x

	*(DWORD*)0x0102EDF0 -= ResultPosX;//x
	*(DWORD*)0x0102EDEB -= ResultPosY;//y

	*(DWORD*)0x0102EE71 -= ResultPosX;//x
	*(DWORD*)0x0102EE79 -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0102EF96 -= ResultPosX;//开始x
	*(DWORD*)0x0102EF7A -= ResultPosX;//结束x
	*(DWORD*)0x0102F020 -= ResultPosY;//y

	//Sprite/Interface2/Result_Ver2.0/Result_EventTag/Result_EventTag_tw.img
	//*(BYTE*)0x0102F0BA *= 0.8f;//x
	*(DWORD*)0x0102F0B3 -= ResultPosY;//y

	//Sprite/Interface/NewResult/result2_numset_small.img 11
	*(DWORD*)0x0102F19E -= ResultPosX;//x
	*(DWORD*)0x0102F198 -= ResultPosY;//y
	*(DWORD*)0x0102F20D -= ResultPosX;//x
	*(DWORD*)0x0102F208 -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0102F354 -= ResultPosX;//开始x
	*(DWORD*)0x0102F338 -= ResultPosX;//结束x
	*(DWORD*)0x0102F3D1 -= ResultPosY;//y
	//*(BYTE*)0x0102F45B *= 0.8f;//x
	*(DWORD*)0x0102F44E -= ResultPosY;//y

	//Sprite/Interface/NewResult/result2_numset_small.img 11
	*(DWORD*)0x0102F569 -= ResultPosX;//x
	*(DWORD*)0x0102F563 -= ResultPosY;//y
	*(DWORD*)0x0102F5D9 -= ResultPosX;//x
	*(DWORD*)0x0102F5D4 -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0102F71A -= ResultPosX;//开始x
	*(DWORD*)0x0102F6FE -= ResultPosX;//结束x
	*(DWORD*)0x0102F79D -= ResultPosY;//y
	//*(BYTE*)0x0102F820 *= 0.8f;//x
	*(DWORD*)0x0102F819 -= ResultPosY;//y

	//Sprite/Interface/NewResult/result2_numset_small.img 11
	*(DWORD*)0x0102F8FF -= ResultPosX;//x
	*(DWORD*)0x0102F8F9 -= ResultPosY;//y
	*(DWORD*)0x0102F96F -= ResultPosX;//x
	*(DWORD*)0x0102F96A -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0102FAB1 -= ResultPosX;//开始x
	*(DWORD*)0x0102FA95 -= ResultPosX;//结束x
	*(DWORD*)0x0102FB32 -= ResultPosY;//y
	//*(BYTE*)0x0102FBB5 *= 0.8f;//x
	*(DWORD*)0x0102FBAE -= ResultPosY;//y

	//Sprite/Interface/NewResult/result2_numset_small.img 11
	*(DWORD*)0x0102FCC4 -= ResultPosX;//x
	*(DWORD*)0x0102FCBE -= ResultPosY;//y
	*(DWORD*)0x0102FD34 -= ResultPosX;//x
	*(DWORD*)0x0102FD2F -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0102FE76 -= ResultPosX;//开始x
	*(DWORD*)0x0102FE5A -= ResultPosX;//结束x
	*(DWORD*)0x0102FEF7 -= ResultPosY;//y
	//*(BYTE*)0x0102FF7A *= 0.8f;//x
	*(DWORD*)0x0102FF73 -= ResultPosY;//y

	//Sprite/Interface/NewResult/result2_numset_small.img 11
	*(DWORD*)0x01030059 -= ResultPosX;//x
	*(DWORD*)0x01030053 -= ResultPosY;//y
	*(DWORD*)0x010300C9 -= ResultPosX;//x
	*(DWORD*)0x010300C4 -= ResultPosY;//y

	//特别/活动加成 imgPos 29/11
	*(DWORD*)0x0103020A -= ResultPosX;//开始x
	*(DWORD*)0x01030205 -= ResultPosX;//结束x
	*(DWORD*)0x0103028D -= ResultPosY;//y
	//*(BYTE*)0x01030321 *= 0.8f;//x
	*(DWORD*)0x0103031A -= ResultPosY;//y

	//经验值变化动画最终值
	*(DWORD*)0x01030431 -= ResultPosX;//x
	*(DWORD*)0x0103042C -= ResultPosY + 60;//y
}
#endif
#define RewardPosY   30
#define RewardPosX2  84
#define RewardPosYU  40
#define RewardPosYD  70
thisCallType1 myDrawImgByXY2_11B41E0;
int __fastcall DrawTreasureAnimation(int* thisP, int edx, int x, int y, int a4, float a5, float a6, float a7, int a8, float a9, float a10) {
	//setBalanceStage 3 by 0x01037e2d start
	//setBalanceStage 4 by 0x01037f1e end
	if (0x028DD3E2 == (int)_ReturnAddress()) {
		x -= 80;
		y -= RewardPosY;
		//printf("[%d,%d]\n", x, y);
	}
	
	return myDrawImgByXY2_11B41E0(thisP, x, y, a4, a5, a6, a7, a8, a9, a10);
}

thisCall3Args2 mySetUiComponentPos;
int __fastcall FixCardFlipPosition(int* thisP, int edx, int x, int y, char a4) {
	int retAddr = (int)_ReturnAddress();
	if (0x028A907B == retAddr) {
		//x -= 80;
		y -= RewardPosYU;
		//printf("[%d,%d]\n", x, y);
	}
	else if (retAddr == 0x00F78509) {
		y -= RewardPosYD;
	}
	
	return mySetUiComponentPos(thisP, x, y, a4);
}

void init70_setDungeonClearStateCb(int* thisP, int a2) {
	static GumInterceptor* v = gum_interceptor_obtain();
	if (a2 == 3) gum_interceptor_replace_fast(v, (gpointer)0x11B41E0, (gpointer)DrawTreasureAnimation, (gpointer*)&myDrawImgByXY2_11B41E0);
	else if (a2 == 6) gum_interceptor_replace_fast(v, (gpointer)0x11BEAD0, (gpointer)FixCardFlipPosition, (gpointer*)&mySetUiComponentPos);
	else {
		gum_interceptor_revert(v, (gpointer)0x11B41E0);
		gum_interceptor_revert(v, (gpointer)0x11BEAD0);
	}
}

void init70_CNTownModule_onEnterModuleCb(int* thisP, int a2) {
	if (isWinShowing_E71770(*(int**)0x1A6F750, 0xB2))
		closeWin_E745B0(*(int**)0x1A6F750, 0xB2, 0xFFFFFFFF, 0);
}


int __cdecl hookGetLinearValue_11B98C0(int start, int end, int currentT, int endT) {
	printf("[%d, %d, %d, %d]\n", start, end, currentT, endT);
	return getLinearValue_11B98C0(start, end, currentT, endT);
}
forceinline void dungeonRewardAndEPLP(GumInterceptor* v) {
	//return;
	//47 Sprite/Interface/EPLPNew.img
	*(DWORD*)0x01032EF2 -= 160; //titleX imgPos 0
	*(DWORD*)0x01032F35 -= 160; //背景x imgPos 1
	*(DWORD*)0x01032F65 -= 160; //底部边框x imgPos 2
	*(DWORD*)0x010330F2 -= 160; //选中高亮x imgPos 3
	*(DWORD*)0x01033125 -= 160; //选中高亮x imgPos 3
	*(DWORD*)0x01033227 -= 160; //选中高亮x imgPos 3
	*(DWORD*)0x010334EA -= 160; //选中高亮x imgPos 3
	*(DWORD*)0x01037150 -= 160; //按钮x

	//reward图标
	*(DWORD*)0x01037DEC -= 80; //x 84
	*(DWORD*)0x01037DEA -= 30; //y

	//精英怪加成背景 sub_1032D50
	*(DWORD*)0x01032DC8 -= 80; //x 35
	*(DWORD*)0x01032DC3 -= RewardPosY; //y
	*(DWORD*)0x01032326 -= 80; //x
	*(DWORD*)0x01032321 -= RewardPosY; //y
	*(DWORD*)0x0103238D -= 80; //x
	*(DWORD*)0x01032388 -= RewardPosY; //y

	*(DWORD*)0x0103246B -= 80; //x
	*(DWORD*)0x010324D2 -= 80; //x
	*(DWORD*)0x010323F0 -= RewardPosY; //y start
	*(DWORD*)0x01032415 -= RewardPosY; //y end

	//reward图标
	*(DWORD*)0x01037EB9 -= 80; //x 84
	*(DWORD*)0x01037EB7 -= 30; //y

	//精英怪加成宝箱图标 sub_1030640
	*(DWORD*)0x0103069C -= 80; //x 53
	*(DWORD*)0x01030697 -= RewardPosY; //y

	//sub_1036760
	*(DWORD*)0x010369B2 -= 80; //x
	*(DWORD*)0x01036A27 -= 80; //x
	*(DWORD*)0x01036875 -= RewardPosY; //y 
	*(BYTE*)0x01036AB2 -= 80; //x 50-53
	*(BYTE*)0x01036AB0 -= RewardPosY; //y 

	//精英怪加成宝箱魔法阵 sub_1030CD0
	*(DWORD*)0x01030D62 -= 80; //x 56
	*(DWORD*)0x01030D5D -= RewardPosY; //y
	*(DWORD*)0x01030DE1 -= 80; //x 57
	*(DWORD*)0x01030DDC -= RewardPosY; //y
	*(DWORD*)0x01030E80 -= 80; //x 56
	*(DWORD*)0x01030E7B -= RewardPosY; //y

	//sub_1030A00 0-32 
	*(DWORD*)0x01030AC7 -= 80; //x
	*(DWORD*)0x01030AC2 -= RewardPosY; //y
	*(DWORD*)0x01030B4E -= 80; //x
	*(DWORD*)0x01030B49 -= RewardPosY; //y
	*(DWORD*)0x01030C92 -= 80; //x
	*(DWORD*)0x01030C8D -= RewardPosY; //y
	*(DWORD*)0x01030C15 -= 80; //x
	*(DWORD*)0x01030C10 -= RewardPosY; //y

	//sub_1030780 
	*(DWORD*)0x0103080C -= 80; //x 53
	*(DWORD*)0x01030807 -= RewardPosY; //y
	*(DWORD*)0x01030891 -= 80; //x 54
	*(DWORD*)0x0103088C -= RewardPosY; //y 
	*(DWORD*)0x01030910 -= 80; //x 55
	*(DWORD*)0x0103090B -= RewardPosY; //y 
	*(DWORD*)0x010309AB -= 80; //x 54
	*(DWORD*)0x010309A6 -= RewardPosY; //y 

	//sub_1031170
	*(BYTE*)0x010311F7 = 0; //x 103 下排牌子运动时背景
	*(DWORD*)0x010311F2 -= RewardPosYD; //y 
	((DWORD*)0x182C590)[0] -= RewardPosX2; //x 卡牌1 end
	((DWORD*)0x182C590)[1] -= RewardPosX2; //x 卡牌2 end
	((DWORD*)0x182C590)[2] -= RewardPosX2; //x 卡牌3 end
	((DWORD*)0x182C590)[3] -= RewardPosX2; //x 卡牌4 end
	((DWORD*)0x182C590)[4] -= RewardPosX2; //x 卡牌5 end
	((DWORD*)0x182C590)[5] -= RewardPosX2; //x 卡牌6 end
	((DWORD*)0x182C590)[6] -= RewardPosX2; //x 卡牌7 end
	((DWORD*)0x182C590)[7] -= RewardPosX2; //x 卡牌8 end
	*(DWORD*)0x01031233 -= 80; //x start
	*(DWORD*)0x01A3EA9C -= RewardPosYU; //y start 45 上排运动y轴
	*(DWORD*)0x01031258 -= RewardPosYU; //y end 40  上排运动y轴
	*(DWORD*)0x01031438 -= 80; //x start
	*(DWORD*)0x01031576 -= RewardPosYD; //y 124 下排运动y轴
	*(DWORD*)0x010315FB -= RewardPosYD; //y 40  下排运动y轴

	//过度到翻牌 58
	*(DWORD*)0x01031BE1 -= 80; //x
	//*(BYTE*)0x01031BDF -= 60; //y


	//上排y		142
	//黑钻奖励	253
	//下排y		425
	//翻牌 sub_1034ED0
	*(BYTE*)0x01035199 = 0; //x 34 上排牌子背景
	*(DWORD*)0x01035194 -= RewardPosYU; //y
	*(BYTE*)0x0103521E = 0; //x 103 下排牌子背景
	*(DWORD*)0x01035219 -= RewardPosYD; //y

	//黑钻奖励下滑出现
	*(DWORD*)0x01035586 -= RewardPosYU; //x 0x182C590 y 100
	*(DWORD*)0x01A3EAA0 -= RewardPosYU; //x 0x182C590 y start 1 interface/newResult/pcroompremiumreward.img
	*(DWORD*)0x01035533 -= RewardPosYU; //x 0x182C590 y end 
	//writeCallCode((void*)0x010352B4, hookGetLinearValue_11B98C0);//01035538
	//上排 翻牌
	*(DWORD*)0x01035BF5 -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01035CCD -= RewardPosYU; //x 0x182C590 y 43/44 140/141
	*(DWORD*)0x01035992 -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01035A3B -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01035A1C -= RewardPosYU; //x 0x182C590 y 42/139
	*(DWORD*)0x01035718 -= RewardPosYU; //x 0x182C590 y 100
	*(DWORD*)0x01035793 -= RewardPosYU; //x 0x182C590 y 1 interface/newResult/pcroompremiumreward.img
	*(DWORD*)0x01035817 -= RewardPosYU; //x 0x182C590 y 137
	//黑钻 翻牌
	*(DWORD*)0x01035D4A -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01035E19 -= RewardPosYU; //x 0x182C590 y 43/44 140/141
	*(DWORD*)0x01035AC5 -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01035B45 -= RewardPosYU; //x 0x182C590 y 42/139
	*(DWORD*)0x010358E0 -= RewardPosYU; //x 0x182C590 y 1 interface/newResult/pcroompremiumreward.img

	//平滑由中心散开 取消y轴得变化
	*(DWORD*)0x010352AC -= RewardPosYU; //x 0x182C590 y end 137/100 1 interface/newResult/pcroompremiumreward.img
	//*(DWORD*)0x01A3EA9C = *(DWORD*)0x010352AC; //x 0x182C590 y start 

	*(DWORD*)0x0103615E -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x01036226 -= RewardPosYU; //x 0x182C590 y 43/44 140/141
	*(DWORD*)0x0103605F -= RewardPosYU; //x 0x182C590 y 41
	*(DWORD*)0x010360EF -= RewardPosYU; //x 0x182C590 y 42/139
	*(DWORD*)0x01035FAF -= RewardPosYU; //x 0x182C590 y 85
	*(DWORD*)0x01035F7B -= RewardPosYU; //x 0x182C590 y 4 interface/newResult/pcroompremiumreward.img

	*(DWORD*)0x010366A4 -= RewardPosYD; //x 0x182C590 y 124/142/143
	*(DWORD*)0x010364E0 -= RewardPosYD; //x 0x182C590 y 41
	*(DWORD*)0x0103658F -= RewardPosYD; //x 0x182C590 y 43/44
	*(DWORD*)0x01036570 -= RewardPosYD; //x 0x182C590 y 43/44
	*(DWORD*)0x010363F8 -= RewardPosYD; //x 0x182C590 y 41
	*(DWORD*)0x0103646D -= RewardPosYD; //x 0x182C590 y 42
	*(DWORD*)0x0103634C -= RewardPosYD; //x 0x182C590 y 85

	//*(DWORD*)0x01033ED6 -= RewardPosYU; //x 0x182C590 y
	//*(DWORD*)0x01034ABB -= RewardPosYD; //x 0x182C590 y
	//*(DWORD*)0x01034ABB -= RewardPosYD; //x 0x182C590 y

	//drawOpenRewardU_1033D80
	*(DWORD*)0x01033F96 -= RewardPosYU; //x 0x182C590 y 
	*(DWORD*)0x0103402F -= RewardPosYU; //x 0x182C590 y 
	*(DWORD*)0x010340BA -= RewardPosYU; //x 0x182C590 y 
	*(DWORD*)0x01034158 -= RewardPosYU; //x 0x182C590 y 装备图标
	*(DWORD*)0x010342BC -= RewardPosYU; //x 0x182C590 y +%d金币
	*(DWORD*)0x010343CC -= RewardPosYU + 3; //x 0x182C590 y +%d金币
	*(DWORD*)0x01034460 -= RewardPosYU; //x 0x182C590 y +%d金币
	*(BYTE*)0x01034519 -= RewardPosYU; //x 0x182C590 y 60/61 人物头像框
	*(BYTE*)0x01034566 -= RewardPosYU; //x 0x182C590 y 人物头像
	*(BYTE*)0x010345B4 -= RewardPosYU; //x 0x182C590 y 人物名字
	*(BYTE*)0x01034637 -= RewardPosYU; //x 0x182C590 y 退出队伍的角色
	*(BYTE*)0x01034758 -= RewardPosYU; //x 0x182C590 y 87/93

	//drawOpenRewardD_1034790 翻牌操作
	*(DWORD*)0x01034926 -= RewardPosYD; //x 0x182C590 y 144
	*(DWORD*)0x01034999 -= RewardPosYD; //x 0x182C590 y
	*(DWORD*)0x01034ABB -= RewardPosYD; //x 0x182C590 y 装备图标
	*(DWORD*)0x01034BA0 -= RewardPosYD; //x 0x182C590 y +% d金币
	*(DWORD*)0x01034C45 -= RewardPosYD; //x 0x182C590 y 60/61 人物头像框
	*(DWORD*)0x01034C90 -= RewardPosYD; //x 0x182C590 y 人物头像
	*(DWORD*)0x01034CEA -= RewardPosYD; //x 0x182C590 y 人物名字
	*(DWORD*)0x01034D6F -= RewardPosYD; //x 0x182C590 y 退出队伍的角色
	*(DWORD*)0x01034E94 -= RewardPosYD; //x 0x182C590 y 87/93

	//sub_1032530 翻牌提示语
	*(BYTE*)0x01032619 -= 80; //x 83
	*(BYTE*)0x01032617 -= RewardPosYU; //y 
	*(BYTE*)0x01032633 -= 80; //x 82
	*(BYTE*)0x01032631 -= RewardPosYU; //y 
	*(BYTE*)0x010326BA -= 80; //x 102 下排
	*(DWORD*)0x010326B5 -= RewardPosYD; //y 
	*(BYTE*)0x01032690 -= 80; //x 146 下排
	*(DWORD*)0x0103268B -= RewardPosYD; //y 
	*(BYTE*)0x010326D7 -= 80; //x 101/145 下排
	*(DWORD*)0x010326D2 -= RewardPosYD; //y 
	*(DWORD*)0x01032732 -= 160; //x
	*(DWORD*)0x01032746 -= 160; //x

	//sub_1031630
	*(DWORD*)0x01031735 -= RewardPosYU; //x 0x182C590 y 86
	*(DWORD*)0x01031705 -= RewardPosYU; //x 0x182C590 y 
	*(DWORD*)0x010317CD -= RewardPosYU; //x 0x182C590 y 40
	//*(DWORD*)0x01031833 -= 60; //x 0x182C590 x
	*(DWORD*)0x0103182D -= RewardPosYU; //x 0x182C590 y
	*(DWORD*)0x010318E4 -= RewardPosYD; //x 0x182C590 y 124/142/143
	//*(BYTE*)0x0103194D -= 60; //x 0x182C590 x
	*(DWORD*)0x01031947 -= RewardPosYD; //x 0x182C590 y
	*(DWORD*)0x01031926 -= RewardPosYD; //x 0x182C590 y 135
	*(DWORD*)0x010319DD -= RewardPosYD; //x 0x182C590 y 40
	//*(DWORD*)0x01031A40 -= 60; //x 0x182C590 x
	*(DWORD*)0x01031A3A -= RewardPosYD; //x 0x182C590 y
}

forceinline void deathTowerRewardAndEPLP() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();

	//DeathTowerRewardView::drawEPLP_105FD60
	*(DWORD*)0x0105FDAD -= 160; //titleX imgPos 0
	*(DWORD*)0x0182C630 -= 160; //背景x imgPos 1
	*(DWORD*)0x0105FE2F -= 160; //底部边框x imgPos 2
	*(DWORD*)0x0182C628 -= 160; //选中高亮x imgPos 3
	*(DWORD*)0x0106151B -= 160; //x\

	//CommonEplpWin::ProcDraw_F1F8C0
	*(DWORD*)0x00F1F90D -= 160; //x
	*(DWORD*)0x00F1F98F -= 160; //x

	//DeathTowerResultView0::drawBg_105D540
	//*(DWORD*)0x0105D65C -= 80; //x
	hook->resize(8);
	b = hook->begin();
	/*//DeathTowerResultView0::draw0_105D670
	*(BYTE*)0x0105D6E6 -= 80; //x
	*(BYTE*)0x0105D6E4 -= 60; //y
	*(DWORD*)0x0105D732 -= 80; //x
	*(DWORD*)0x0105D72D -= 60; //y
	*(DWORD*)0x0105D75D -= 80; //x
	*(DWORD*)0x0105D758 -= 60; //y
	*(BYTE*)0x0105D6EC = 0xE9;
	*(DWORD*)0x0105D6ED = 0x7F;*/
	b++->setValue(H_BYTE, 0x0105D6E6, *(BYTE*)0x0105D6E6 - 80);
	b++->setValue(H_BYTE, 0x0105D6E4, *(BYTE*)0x0105D6E4 - 60);
	b++->setValue(H_DWORD, 0x0105D732, *(DWORD*)0x0105D732 - 80);
	b++->setValue(H_DWORD, 0x0105D72D, *(DWORD*)0x0105D72D - 60);
	b++->setValue(H_DWORD, 0x0105D75D, *(DWORD*)0x0105D75D - 80);
	b++->setValue(H_DWORD, 0x0105D758, *(DWORD*)0x0105D758 - 60);
	b++->setValue(H_BYTE, 0x0105D6EC, 0xE9);
	b++->setValue(H_DWORD, 0x0105D6ED, 0x7F);
	thisCall1Args2 DeathTowerResultView0__draw0_105D670 = (thisCall1Args2)tools_relocation_hook(0x105D670, 0x0105D779, hook);
	writeCallCode((void*)0x0105F456, (void*)DeathTowerResultView0__draw0_105D670);
	writeCallCode((void*)0x0105F4F2, (void*)DeathTowerResultView0__draw0_105D670);

	hook->resize(64);
	b = hook->begin();
	/*//DeathTowerResultView0::draw1_105DD60
	*(DWORD*)0x0105DE00 -= 80; //x
	*(BYTE*)0x0105DDFE -= 60; //y
	*(DWORD*)0x0105DE56 -= 80; //x
	*(DWORD*)0x0105DE51 -= 60; //y
	*(DWORD*)0x0105DED0 -= 80; //x
	*(DWORD*)0x0105DECB -= 60; //y
	*(BYTE*)0x0105DF3C -= 80; //x
	*(DWORD*)0x0105DF37 -= 60; //y
	*(BYTE*)0x00105DF79 -= 80; //x
	*(DWORD*)0x0105DF74 -= 60; //y
	*(DWORD*)0x0105DFD6 -= 80; //x
	*(DWORD*)0x0105DFD1 -= 60; //y
	*(DWORD*)0x0105DFE9 -= 60; //y
	*(DWORD*)0x0105E067 -= 80; //x
	*(DWORD*)0x0105E090 -= 80; //x
	*(DWORD*)0x0105E0DD -= 80; //x
	*(DWORD*)0x0105E11D -= 80; //x
	*(DWORD*)0x0105E118 -= 60; //y
	*(DWORD*)0x0105E173 -= 80; //x
	*(DWORD*)0x0105E16E -= 60; //y
	*(DWORD*)0x0105E257 -= 80; //x
	*(BYTE*)0x0105E255 -= 60; //y
	*(DWORD*)0x0105E2B0 -= 80; //x
	*(BYTE*)0x0105E2AE -= 60; //y
	*(DWORD*)0x0105E197 -= 80; //x
	*(DWORD*)0x0105E192 -= 60; //y
	*(DWORD*)0x0105E1FE -= 80; //x
	*(DWORD*)0x0105E1E8 -= 60; //y
	*(DWORD*)0x0105E317 -= 80; //x
	*(DWORD*)0x0105E310 -= 60; //y
	*(DWORD*)0x0105E37C -= 80; //x
	*(DWORD*)0x0105E376 -= 60; //y
	*(DWORD*)0x0105E39A -= 80; //x
	*(DWORD*)0x0105E394 -= 60; //y
	*(DWORD*)0x0105E3FA -= 60; //y
	*(DWORD*)0x0105E415 -= 60; //y
	*(DWORD*)0x0105E46F -= 80; //x
	*(DWORD*)0x0105E46A -= 60; //y
	*(DWORD*)0x0105E488 -= 60; //y
	*(DWORD*)0x0105E52A -= 80; //x
	*(DWORD*)0x0105E5C3 -= 80; //x
	*(DWORD*)0x0105E613 -= 80; //x
	*(DWORD*)0x0105E560 -= 80; //x
	*(DWORD*)0x0105E54D -= 60; //y
	*(DWORD*)0x0105E654 -= 80; //x
	*(DWORD*)0x0105E64F -= 60; //y
	*(DWORD*)0x0105E6CE -= 80; //x
	*(DWORD*)0x0105E6C9 -= 60; //y
	*(DWORD*)0x0105E735 -= 80; //x
	*(DWORD*)0x0105E722 -= 60; //y
	*(DWORD*)0x0105E798 -= 80; //x
	*(DWORD*)0x0105E791 -= 60; //y
	*(DWORD*)0x0105E7FD -= 80; //x
	*(DWORD*)0x0105E7F7 -= 60; //y
	*(DWORD*)0x0105E81b -= 80; //x
	*(DWORD*)0x0105E815 -= 60; //y
	*(DWORD*)0x0105E87B -= 60; //y
	*(DWORD*)0x0105E896 -= 60; //y
	*(DWORD*)0x0105E9FB -= 80; //x
	*(DWORD*)0x0105E9F6 -= 60; //y
	*(DWORD*)0x0105EA63 -= 80; //x
	*(DWORD*)0x0105EA5E -= 60; //y
	*(DWORD*)0x0105EAC8 -= 80; //x
	*(DWORD*)0x0105EAC3 -= 60; //y*/
	b++->setValue(H_DWORD, 0x0105DE00, *(DWORD*)0x0105DE00 - 80);
	b++->setValue(H_BYTE, 0x0105DDFE, *(BYTE*)0x0105DDFE - 60);
	b++->setValue(H_DWORD, 0x0105DE56, *(DWORD*)0x0105DE56 - 80);
	b++->setValue(H_DWORD, 0x0105DE51, *(DWORD*)0x0105DE51 - 60);
	b++->setValue(H_DWORD, 0x0105DED0, *(DWORD*)0x0105DED0 - 80);
	b++->setValue(H_DWORD, 0x0105DECB, *(DWORD*)0x0105DECB - 60);
	b++->setValue(H_BYTE, 0x0105DF3C, *(BYTE*)0x0105DF3C - 80);
	b++->setValue(H_DWORD, 0x0105DF37, *(DWORD*)0x0105DF37 - 60);
	b++->setValue(H_BYTE, 0x00105DF79, *(BYTE*)0x00105DF79 - 80);
	b++->setValue(H_DWORD, 0x0105DF74, *(DWORD*)0x0105DF74 - 60);
	b++->setValue(H_DWORD, 0x0105DFD6, *(DWORD*)0x0105DFD6 - 80);
	b++->setValue(H_DWORD, 0x0105DFD1, *(DWORD*)0x0105DFD1 - 60);
	b++->setValue(H_DWORD, 0x0105DFE9, *(DWORD*)0x0105DFE9 - 60);
	b++->setValue(H_DWORD, 0x0105E067, *(DWORD*)0x0105E067 - 80);
	b++->setValue(H_DWORD, 0x0105E090, *(DWORD*)0x0105E090 - 80);
	b++->setValue(H_DWORD, 0x0105E0DD, *(DWORD*)0x0105E0DD - 80);
	b++->setValue(H_DWORD, 0x0105E11D, *(DWORD*)0x0105E11D - 80);
	b++->setValue(H_DWORD, 0x0105E118, *(DWORD*)0x0105E118 - 60);
	b++->setValue(H_DWORD, 0x0105E173, *(DWORD*)0x0105E173 - 80);
	b++->setValue(H_DWORD, 0x0105E16E, *(DWORD*)0x0105E16E - 60);
	b++->setValue(H_DWORD, 0x0105E257, *(DWORD*)0x0105E257 - 80);
	b++->setValue(H_BYTE, 0x0105E255, *(BYTE*)0x0105E255 - 60);
	b++->setValue(H_DWORD, 0x0105E2B0, *(DWORD*)0x0105E2B0 - 80);
	b++->setValue(H_BYTE, 0x0105E2AE, *(BYTE*)0x0105E2AE - 60);
	b++->setValue(H_DWORD, 0x0105E197, *(DWORD*)0x0105E197 - 80);
	b++->setValue(H_DWORD, 0x0105E192, *(DWORD*)0x0105E192 - 60);
	b++->setValue(H_DWORD, 0x0105E1FE, *(DWORD*)0x0105E1FE - 80);
	b++->setValue(H_DWORD, 0x0105E1E8, *(DWORD*)0x0105E1E8 - 60);
	b++->setValue(H_DWORD, 0x0105E317, *(DWORD*)0x0105E317 - 80);
	b++->setValue(H_DWORD, 0x0105E310, *(DWORD*)0x0105E310 - 60);
	b++->setValue(H_DWORD, 0x0105E37C, *(DWORD*)0x0105E37C - 80);
	b++->setValue(H_DWORD, 0x0105E376, *(DWORD*)0x0105E376 - 60);
	b++->setValue(H_DWORD, 0x0105E39A, *(DWORD*)0x0105E39A - 80);
	b++->setValue(H_DWORD, 0x0105E394, *(DWORD*)0x0105E394 - 60);
	b++->setValue(H_DWORD, 0x0105E3FA, *(DWORD*)0x0105E3FA - 60);
	b++->setValue(H_DWORD, 0x0105E415, *(DWORD*)0x0105E415 - 60);
	b++->setValue(H_DWORD, 0x0105E46F, *(DWORD*)0x0105E46F - 80);
	b++->setValue(H_DWORD, 0x0105E46A, *(DWORD*)0x0105E46A - 60);
	b++->setValue(H_DWORD, 0x0105E488, *(DWORD*)0x0105E488 - 60);
	b++->setValue(H_DWORD, 0x0105E52A, *(DWORD*)0x0105E52A - 80);
	b++->setValue(H_DWORD, 0x0105E5C3, *(DWORD*)0x0105E5C3 - 80);
	b++->setValue(H_DWORD, 0x0105E613, *(DWORD*)0x0105E613 - 80);
	b++->setValue(H_DWORD, 0x0105E560, *(DWORD*)0x0105E560 - 80);
	b++->setValue(H_DWORD, 0x0105E54D, *(DWORD*)0x0105E54D - 60);
	b++->setValue(H_DWORD, 0x0105E654, *(DWORD*)0x0105E654 - 80);
	b++->setValue(H_DWORD, 0x0105E64F, *(DWORD*)0x0105E64F - 60);
	b++->setValue(H_DWORD, 0x0105E6CE, *(DWORD*)0x0105E6CE - 80);
	b++->setValue(H_DWORD, 0x0105E6C9, *(DWORD*)0x0105E6C9 - 60);
	b++->setValue(H_DWORD, 0x0105E735, *(DWORD*)0x0105E735 - 80);
	b++->setValue(H_DWORD, 0x0105E722, *(DWORD*)0x0105E722 - 60);
	b++->setValue(H_DWORD, 0x0105E798, *(DWORD*)0x0105E798 - 80);
	b++->setValue(H_DWORD, 0x0105E791, *(DWORD*)0x0105E791 - 60);
	b++->setValue(H_DWORD, 0x0105E7FD, *(DWORD*)0x0105E7FD - 80);
	b++->setValue(H_DWORD, 0x0105E7F7, *(DWORD*)0x0105E7F7 - 60);
	b++->setValue(H_DWORD, 0x0105E81b, *(DWORD*)0x0105E81b - 80);
	b++->setValue(H_DWORD, 0x0105E815, *(DWORD*)0x0105E815 - 60);
	b++->setValue(H_DWORD, 0x0105E87B, *(DWORD*)0x0105E87B - 60);
	b++->setValue(H_DWORD, 0x0105E896, *(DWORD*)0x0105E896 - 60);
	b++->setValue(H_DWORD, 0x0105E9FB, *(DWORD*)0x0105E9FB - 80);
	b++->setValue(H_DWORD, 0x0105E9F6, *(DWORD*)0x0105E9F6 - 60);
	b++->setValue(H_DWORD, 0x0105EA63, *(DWORD*)0x0105EA63 - 80);
	b++->setValue(H_DWORD, 0x0105EA5E, *(DWORD*)0x0105EA5E - 60);
	b++->setValue(H_DWORD, 0x0105EAC8, *(DWORD*)0x0105EAC8 - 80);
	b++->setValue(H_DWORD, 0x0105EAC3, *(DWORD*)0x0105EAC3 - 60);
	thisCall1Args2 DeathTowerResultView0__draw1_105DD60 = (thisCall1Args2)tools_relocation_hook(0x0105DD60, 0x0105EADF, hook);
	writeCallCode((void*)0x0105F47B, (void*)DeathTowerResultView0__draw1_105DD60);
	writeCallCode((void*)0x0105F4FA, (void*)DeathTowerResultView0__draw1_105DD60);

	hook->resize(19);
	b = hook->begin();
	/*//DeathTowerResultView0::draw2_105D780
	*(DWORD*)0x0105D84E -= 80; //x
	*(DWORD*)0x0105D82A -= 60; //y
	*(DWORD*)0x0105D842 -= 60; //y
	*(DWORD*)0x0105D816 -= 60; //y
	*(DWORD*)0x0105D8AF -= 80; //x
	*(DWORD*)0x0105D879 -= 60; //y
	*(DWORD*)0x0105D8C7 -= 60; //y
	*(DWORD*)0x0105D92E -= 80; //x
	*(DWORD*)0x0105D929 -= 60; //y
	*(DWORD*)0x0105D945 -= 60; //y
	*(DWORD*)0x0105D963 -= 80; //x
	*(DWORD*)0x0105DA7E -= 80; //x
	*(DWORD*)0x0105DB3C -= 80; //x
	*(DWORD*)0x0105DB7A -= 80; //x
	*(DWORD*)0x0105DBCF -= 80; //x
	*(DWORD*)0x0105DC29 -= 80; //x
	*(DWORD*)0x0105DC8D -= 80; //x
	*(DWORD*)0x0105DCA7 -= 80; //x
	*(DWORD*)0x0105DD3A -= 60; //y*/
	b++->setValue(H_DWORD, 0x0105D84E, *(DWORD*)0x0105D84E - 80);
	b++->setValue(H_DWORD, 0x0105D82A, *(DWORD*)0x0105D82A - 60);
	b++->setValue(H_DWORD, 0x0105D842, *(DWORD*)0x0105D842 - 60);
	b++->setValue(H_DWORD, 0x0105D816, *(DWORD*)0x0105D816 - 60);
	b++->setValue(H_DWORD, 0x0105D8AF, *(DWORD*)0x0105D8AF - 80);
	b++->setValue(H_DWORD, 0x0105D879, *(DWORD*)0x0105D879 - 60);
	b++->setValue(H_DWORD, 0x0105D8C7, *(DWORD*)0x0105D8C7 - 60);
	b++->setValue(H_DWORD, 0x0105D92E, *(DWORD*)0x0105D92E - 80);
	b++->setValue(H_DWORD, 0x0105D929, *(DWORD*)0x0105D929 - 60);
	b++->setValue(H_DWORD, 0x0105D945, *(DWORD*)0x0105D945 - 60);
	b++->setValue(H_DWORD, 0x0105D963, *(DWORD*)0x0105D963 - 80);
	b++->setValue(H_DWORD, 0x0105DA7E, *(DWORD*)0x0105DA7E - 80);
	b++->setValue(H_DWORD, 0x0105DB3C, *(DWORD*)0x0105DB3C - 80);
	b++->setValue(H_DWORD, 0x0105DB7A, *(DWORD*)0x0105DB7A - 80);
	b++->setValue(H_DWORD, 0x0105DBCF, *(DWORD*)0x0105DBCF - 80);
	b++->setValue(H_DWORD, 0x0105DC29, *(DWORD*)0x0105DC29 - 80);
	b++->setValue(H_DWORD, 0x0105DC8D, *(DWORD*)0x0105DC8D - 80);
	b++->setValue(H_DWORD, 0x0105DCA7, *(DWORD*)0x0105DCA7 - 80);
	b++->setValue(H_DWORD, 0x0105DD3A, *(DWORD*)0x0105DD3A - 60);
	thisCall1Args2 DeathTowerResultView0__draw2_105D780 = (thisCall1Args2)tools_relocation_hook(0x0105D780, 0x0105DD58, hook);
	writeCallCode((void*)0x0105F502, (void*)DeathTowerResultView0__draw2_105D780);
	writeCallCode((void*)0x0105F4A0, (void*)DeathTowerResultView0__draw2_105D780);

	//DeathTowerRewardView::drawBg_105FAE0
	//*(DWORD*)0x0105FBFE -= 80; //x
	*(DWORD*)0x0105FC77 -= 80; //x
	*(BYTE*)0x0105FC75 -= 60; //y


	hook->resize(7);
	b = hook->begin();
	/*//DeathTowerRewardView::draw1_105F650
	*(DWORD*)0x0105F6F9 -= 80; //x
	*(DWORD*)0x0105F6F4 -= 60; //y
	*(DWORD*)0x0105F6A6 -= 80; //x
	*(DWORD*)0x0105F6A1 -= 60; //y
	*(DWORD*)0x0105F718 -= 80; //x
	*(DWORD*)0x0105F713 -= 60; //y
	*(DWORD*)0x0105F6D4 -= 60; //y*/
	b++->setValue(H_DWORD, 0x0105F6F9, *(DWORD*)0x0105F6F9 - 80);
	b++->setValue(H_DWORD, 0x0105F6F4, *(DWORD*)0x0105F6F4 - 60);
	b++->setValue(H_DWORD, 0x0105F6A6, *(DWORD*)0x0105F6A6 - 80);
	b++->setValue(H_DWORD, 0x0105F6A1, *(DWORD*)0x0105F6A1 - 60);
	b++->setValue(H_DWORD, 0x0105F718, *(DWORD*)0x0105F718 - 80);
	b++->setValue(H_DWORD, 0x0105F713, *(DWORD*)0x0105F713 - 60);
	b++->setValue(H_DWORD, 0x0105F6D4, *(DWORD*)0x0105F6D4 - 60);
	thisCall1Args2 DeathTowerRewardView__draw1_105F650 = (thisCall1Args2)tools_relocation_hook(0x105F650, 0x0105F723, hook);

	hook->resize(7);
	b = hook->begin();
	/*//DeathTowerRewardView::ProcDraw_1061840
	*(DWORD*)0x01061A3B -= 80; //x
	*(DWORD*)0x01061A36 -= 60; //y
	*(DWORD*)0x01061A96 -= 80; //x
	*(DWORD*)0x01061A91 -= 60; //y
	*(DWORD*)0x010619AB -= 80; //x
	*(DWORD*)0x010619B4 -= 60; //y*/
	b++->setValue(H_DWORD, 0x01061A3B, *(DWORD*)0x01061A3B - 80);
	b++->setValue(H_DWORD, 0x01061A36, *(DWORD*)0x01061A36 - 60);
	b++->setValue(H_DWORD, 0x01061A96, *(DWORD*)0x01061A96 - 80);
	b++->setValue(H_DWORD, 0x01061A91, *(DWORD*)0x01061A91 - 60);
	b++->setValue(H_DWORD, 0x010619AB, *(DWORD*)0x010619AB - 80);
	b++->setValue(H_DWORD, 0x010619B4, *(DWORD*)0x010619B4 - 60);
	b++->setValue(H_CALL, 0x01061B3B, (int)DeathTowerRewardView__draw1_105F650);
	thisCall1Args2 DeathTowerRewardView__ProcDraw_1061840 = (thisCall1Args2)tools_relocation_hook(0x1061840, 0x1061BCC, hook);
	*(DWORD*)0x018128BC = (int)DeathTowerRewardView__ProcDraw_1061840;

	//DeathTowerRewardView::draw0_1061110
	delete hook;
}

forceinline void despairTowerRewardAndEPLP() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();

	hook->resize(6);
	b = hook->begin();
	//BloodWarResultView::drawReward_10893D0 010894CD
	/**(DWORD*)0x0108945A -= 60; //x 奖励列表柱状图
	*(DWORD*)0x01089455 -= 94; //y 奖励列表柱状图
	*(DWORD*)0x0108942F -= 60; //x
	*(DWORD*)0x01089429 -= 94; //y
	*(DWORD*)0x01089424 -= 60; //x
	*(DWORD*)0x0108941F -= 94; //y*/
	b++->setValue(H_DWORD, 0x0108945A, *(DWORD*)0x0108945A - 60);
	b++->setValue(H_DWORD, 0x01089455, *(DWORD*)0x01089455 - 94);
	b++->setValue(H_DWORD, 0x0108942F, *(DWORD*)0x0108942F - 60);
	b++->setValue(H_DWORD, 0x01089429, *(DWORD*)0x01089429 - 94);
	b++->setValue(H_DWORD, 0x01089424, *(DWORD*)0x01089424 - 60);
	b++->setValue(H_DWORD, 0x0108941F, *(DWORD*)0x0108941F - 94);
	thisCall1Args2 BloodWarResultView__drawReward = (thisCall1Args2)tools_relocation_hook(0x10893D0, 0x010894CD, hook);

	hook->resize(2);
	b = hook->begin();
	//sub_10894D0 010895E9
	/*//*(BYTE*)0x01089E24 = -15; //x
	*(DWORD*)0x010894E7 -= 60; //x
	*(DWORD*)0x010894FF -= 60; //x*/
	b++->setValue(H_DWORD, 0x010894E7, *(DWORD*)0x010894E7 - 60);
	b++->setValue(H_DWORD, 0x010894FF, *(DWORD*)0x010894FF - 60);
	thisCall1Args2 sub_10894D0 = (thisCall1Args2)tools_relocation_hook(0x10894D0, 0x010895E9, hook);

	hook->resize(9);
	b = hook->begin();
	//BloodWarResultView::drawResult_1089650 0108974E
	/*
	*(DWORD*)0x0108969A -= 60; //x 奖励icon
	*(DWORD*)0x01089698 -= 64; //y 奖励icon
	*(DWORD*)0x010896BE -= 94; //y 奖励列表背景
	*(DWORD*)0x010896C3 -= 60; //x 奖励列表背景
	*(DWORD*)0x0108970A -= 60; //x 击败玩家幻影
	*(DWORD*)0x01089705 -= 94; //y 击败玩家幻影
	*(DWORD*)0x01089731 -= 30; //x 层数
	*(DWORD*)0x0108972C -= 94; //y 层数
	*/
	b++->setValue(H_DWORD, 0x0108969A, *(DWORD*)0x0108969A - 60);
	b++->setValue(H_DWORD, 0x01089698, *(DWORD*)0x01089698 - 64);
	b++->setValue(H_DWORD, 0x010896BE, *(DWORD*)0x010896BE - 94);
	b++->setValue(H_DWORD, 0x010896C3, *(DWORD*)0x010896C3 - 60);
	b++->setValue(H_DWORD, 0x0108970A, *(DWORD*)0x0108970A - 60);
	b++->setValue(H_DWORD, 0x01089705, *(DWORD*)0x01089705 - 94);
	b++->setValue(H_DWORD, 0x01089731, *(DWORD*)0x01089731 - 30);
	b++->setValue(H_DWORD, 0x0108972C, *(DWORD*)0x0108972C - 94);
	b++->setValue(H_CALL, 0x0108965C, (int)sub_10894D0);
	thisCall1Args2 BloodWarResultView__drawResult = (thisCall1Args2)tools_relocation_hook(0x1089650, 0x0108974E, hook);

	hook->resize(1 + 5 + 5);
	b = hook->begin();
	//BloodWarResultView::ProcDraw_1089750 01089A60
	/**(DWORD*)0x010898A1 -= 50; //x 魔法阵*/
	b++->setValue(H_DWORD, 0x010898A1, *(DWORD*)0x010898A1 - 50);
	b++->setValue(H_CALL, 0x01089914, (int)BloodWarResultView__drawReward);
	b++->setValue(H_CALL, 0x01089960, (int)BloodWarResultView__drawReward);
	b++->setValue(H_CALL, 0x010899A8, (int)BloodWarResultView__drawReward);
	b++->setValue(H_CALL, 0x010899DB, (int)BloodWarResultView__drawReward);
	b++->setValue(H_CALL, 0x01089A25, (int)BloodWarResultView__drawReward);
	b++->setValue(H_CALL, 0x0108990A, (int)BloodWarResultView__drawResult);
	b++->setValue(H_CALL, 0x01089952, (int)BloodWarResultView__drawResult);
	b++->setValue(H_CALL, 0x01089981, (int)BloodWarResultView__drawResult);
	b++->setValue(H_CALL, 0x010899CD, (int)BloodWarResultView__drawResult);
	b++->setValue(H_CALL, 0x01089A1B, (int)BloodWarResultView__drawResult);
	thisCall1Args2 BloodWarResultView__ProcDraw_1089750  = (thisCall1Args2)tools_relocation_hook(0x1089750, 0x01089A60, hook);
	*(DWORD*)0x018129F8 = (int)BloodWarResultView__ProcDraw_1089750;
	
	//BloodWarResultView::init_1089090
	*(DWORD*)0x010891E1 -= 60; //x
	*(DWORD*)0x010891DC -= 88; //y

	//*(DWORD*)0x0108DF50 -= 100; //x

	hook->resize(1);
	b = hook->begin();
	//sub_1089DB0 01089E6F
	//*(DWORD*)0x01089E38 -= 88; //y
	b++->setValue(H_DWORD, 0x01089E38, *(DWORD*)0x01089E38 - 88);
	thisCall1Args2 sub_1089DB0 = (thisCall1Args2)tools_relocation_hook(0x1089DB0, 0x01089E6F, hook);
	writeCallCode((void*)0x0042FCAA, (void*)sub_1089DB0);

	delete hook;
}

forceinline void gbossTowerRewardAndEPLP() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();

	//GBossTowerResultView::ProcDraw_436280
	//ui/gbosstower/result.ui

	//GBossTowerRewardView::drawEplp_437290
	*(DWORD*)0x004372E0 -= 160;
	*(DWORD*)0x00437362 -= 160;
	
	hook->resize(8);
	b = hook->begin();
	//sub_436580
	/**(DWORD*)0x00436629 -= 80;
	*(DWORD*)0x00436624 -= 70;
	*(DWORD*)0x004365D6 -= 80;
	*(DWORD*)0x004365D1 -= 70;
	*(DWORD*)0x00436648 -= 80;
	*(DWORD*)0x00436643 -= 70;
	*(BYTE*)0x00436609 -= 80;
	*(DWORD*)0x00436604 -= 70;*/
	b++->setValue(H_DWORD, 0x00436629, *(DWORD*)0x00436629 - 80);
	b++->setValue(H_DWORD, 0x00436624, *(DWORD*)0x00436624 - 70);
	b++->setValue(H_DWORD, 0x004365D6, *(DWORD*)0x004365D6 - 80);
	b++->setValue(H_DWORD, 0x004365D1, *(DWORD*)0x004365D1 - 70);
	b++->setValue(H_DWORD, 0x00436648, *(DWORD*)0x00436648 - 80);
	b++->setValue(H_DWORD, 0x00436643, *(DWORD*)0x00436643 - 70);
	b++->setValue(H_BYTE, 0x00436609, *(BYTE*)0x00436609 - 80);
	b++->setValue(H_DWORD, 0x00436604, *(DWORD*)0x00436604 - 70);
	thisCall1Args2 sub_436580 = (thisCall1Args2)tools_relocation_hook(0x436580, 0x00436653, hook);

	hook->resize(6 + 1);
	b = hook->begin();
	//GBossTowerRewardView::ProcDraw_437C80 0043800C
	/**(DWORD*)0x00437DEB -= 80;
	*(DWORD*)0x00437DF4 -= 60;
	*(DWORD*)0x00437E7B -= 80;
	*(DWORD*)0x00437E76 -= 60;
	*(DWORD*)0x00437ED6 -= 80;
	*(DWORD*)0x00437ED1 -= 70;*/
	b++->setValue(H_DWORD, 0x00437DEB, *(DWORD*)0x00437DEB - 80);
	b++->setValue(H_DWORD, 0x00437DF4, *(DWORD*)0x00437DF4 - 60);
	b++->setValue(H_DWORD, 0x00437E7B, *(DWORD*)0x00437E7B - 80);
	b++->setValue(H_DWORD, 0x00437E76, *(DWORD*)0x00437E76 - 60);
	b++->setValue(H_DWORD, 0x00437ED6, *(DWORD*)0x00437ED6 - 80);
	b++->setValue(H_DWORD, 0x00437ED1, *(DWORD*)0x00437ED1 - 70);
	b++->setValue(H_CALL, 0x00437F7B, (int)sub_436580);
	thisCall1Args2 GBossTowerRewardView__ProcDraw_437C80 = (thisCall1Args2)tools_relocation_hook(0x437C80, 0x0043800C, hook);
	*(DWORD*)0x018126F0 = (int)GBossTowerRewardView__ProcDraw_437C80;

	*(BYTE*)0x00436192 = 0xFF; //修复播放多次音效
	delete hook;
}

forceinline void bloodyFightTowerRewardAndEPLP() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();

	hook->resize(8);
	b = hook->begin();
	//BloodyFightTowerResultView::ProcDraw_108C5C0 0108CBAC
	/*//*(DWORD*)0x0108C707 -= 80;
	*(DWORD*)0x0108C8EE = 397;
	*(DWORD*)0x0108C8E9 = 338;
	*(DWORD*)0x0108CA67 -= 80;
	*(DWORD*)0x0108CA62 -= 60;
	*(DWORD*)0x0108CAFF -= 80;
	*(DWORD*)0x0108CAFA -= 60;
	*(DWORD*)0x0108CB95 -= 80;
	*(DWORD*)0x0108CB90 -= 60;*/
	b++->setValue(H_DWORD, 0x0108C8EE, 397);
	b++->setValue(H_DWORD, 0x0108C8E9, 338);
	b++->setValue(H_DWORD, 0x0108CA67, *(DWORD*)0x00437E7B - 80);
	b++->setValue(H_DWORD, 0x0108CA62, *(DWORD*)0x00437E76 - 60);
	b++->setValue(H_DWORD, 0x0108CAFF, *(DWORD*)0x00437ED6 - 80);
	b++->setValue(H_DWORD, 0x0108CAFA, *(DWORD*)0x00437ED1 - 60);
	b++->setValue(H_DWORD, 0x0108CB95, *(DWORD*)0x00437ED6 - 80);
	b++->setValue(H_DWORD, 0x0108CB90, *(DWORD*)0x00437ED1 - 60);
	void* BloodyFightTowerResultView__ProcDraw_108C5C0  = (void*)tools_relocation_hook(0x108C5C0, 0x0108CBAC, hook);
	*(DWORD*)0x0181258C = (int)BloodyFightTowerResultView__ProcDraw_108C5C0;


	//BloodyFightTowerResultView::ProcDraw_108E230
	//*(DWORD*)0x0108E30C -= 80;
	
	//BloodyFightTowerResultView::drawRewardItem_108D0D0
	*(DWORD*)0x0108D12C -= 80;
	*(BYTE*)0x0108D12A -= 60;

	//sub_54FDD0
	*(BYTE*)0x0054FE07 = 0xb9; 
	*(DWORD*)0x0054FE08 = 0x11B;

	//sub_108E7B0
	*(BYTE*)0x0108E838 -= 60;

	delete hook;
}

thisCall8Args2 AdvanceAltar__SummonMonster_575770 = (thisCall8Args2)0x575770;
int __fastcall hookAdvanceAltar__SummonMonster_575770(int* thisP, int, int a2, int a3, int x, int y, int z, int a7, int a8, int a9) {
	return AdvanceAltar__SummonMonster_575770(thisP, a2, a3, x + 10, y - 70, z, a7, a8, a9);
}

forceinline void advanceAltar() {
#ifdef NEW
	writeCallCode((void*)0x00739DFE, (void*)hookAdvanceAltar__SummonMonster_575770);
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();
	//防御升级
	*(DWORD*)0x0111E185 -= 160;//x
	*(DWORD*)0x0111E17D -= 120;//y
	//防御设置
	*(DWORD*)0x0111E29A -= 160;//x
	*(DWORD*)0x0111E295 -= 120;//y
	//领取奖励
	*(DWORD*)0x0111E39C -= 160;//x
	*(DWORD*)0x0111E397 -= 120;//y
	//返回城镇
	*(DWORD*)0x0111E49E -= 160;//x
	*(DWORD*)0x0111E499 -= 120;//y
	//开始
	*(DWORD*)0x0111E5A0 -= 160;//x
	//*(DWORD*)0x0111E59B -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E80D -= 160;//x
	//*(DWORD*)0x0111E808 -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E89D -= 170;//x
	//*(DWORD*)0x0111E898 -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E931 -= 160;//x
	//*(DWORD*)0x0111E92C -= 120;//y

	//无限模式
	*(DWORD*)0x0111E9C0 -= 160;//x
	*(DWORD*)0x0111E9BB -= 80;//y


	//197窗口位置
	//writeDWordCode(0x019DDB54, 90);
	//writeDWordCode(0x019DDB58, 483);
	*(DWORD*)0x019DDB54 = 90;//x
	//*(DWORD*)0x019DDB58 = 440;//y
	*(DWORD*)0x005A5151 -= 120;//y
	static int yP = 440;
	*(DWORD*)0x005A4FA1 = (int)&yP;
	*(DWORD*)0x005A4FEF = (int)&yP;
	*(DWORD*)0x005A501C -= 175;//y
	*(DWORD*)0x005A5023 -= 175;//y

	//198窗口位置
	//writeDWordCode(0x019DDAC8, 382);
	//writeDWordCode(0x019DDACC, 440);
	*(DWORD*)0x019DDAC8 = 382;//x
	//*(DWORD*)0x019DDACC = 440;//y
	*(DWORD*)0x005A2861 -= 120;//y
	static int yP2 = 440;
	*(DWORD*)0x005A26B1 = (int)&yP2;
	*(DWORD*)0x005A26FF = (int)&yP2;
	*(DWORD*)0x005A272C -= 175;//y
	*(DWORD*)0x005A2733 -= 175;//y

	////地下城信息
	//*(DWORD*)0x01AFA950 = -160;
	//*(DWORD*)0x01AFA958 = -160;

	hook->resize(15);
	b = hook->begin();
	//CNSelectDungeonModule::drawAdvanceAltar_11218E0
	/**(DWORD*)0x01122590 -= 160;//x
	*(DWORD*)0x01122627 -= 160;//x
	*(DWORD*)0x01122690 -= 160;//x
	*(DWORD*)0x011226BF -= 160;//x
	*(DWORD*)0x0112272E -= 160;//x
	*(DWORD*)0x01122788 -= 160;//x
	*(DWORD*)0x01122831 -= 160;//x
	*(DWORD*)0x01122940 -= 160;//x
	*(DWORD*)0x01122A93 -= 160;//x
	*(DWORD*)0x01122B34 -= 160;//x
	*(DWORD*)0x01122C24 -= 160;//x
	*(DWORD*)0x01122B78 -= 160;//x
	*(DWORD*)0x01123365 -= 160;//x
	*(DWORD*)0x01123386 -= 160;//x
	*(DWORD*)0x011233B0 -= 160;//x*/
	b++->setValue(H_DWORD, 0x01122590, *(DWORD*)0x01122590 - 160);//x
	b++->setValue(H_DWORD, 0x01122627, *(DWORD*)0x01122627 - 160);//x
	b++->setValue(H_DWORD, 0x01122690, *(DWORD*)0x01122690 - 160);//x
	b++->setValue(H_DWORD, 0x011226BF, *(DWORD*)0x011226BF - 160);//x
	b++->setValue(H_DWORD, 0x0112272E, *(DWORD*)0x0112272E - 160);//x
	b++->setValue(H_DWORD, 0x01122788, *(DWORD*)0x01122788 - 160);//x
	b++->setValue(H_DWORD, 0x01122831, *(DWORD*)0x01122831 - 160);//x
	b++->setValue(H_DWORD, 0x01122940, *(DWORD*)0x01122940 - 160);//x
	b++->setValue(H_DWORD, 0x01122A93, *(DWORD*)0x01122A93 - 160);//x
	b++->setValue(H_DWORD, 0x01122B34, *(DWORD*)0x01122B34 - 160);//x
	b++->setValue(H_DWORD, 0x01122C24, *(DWORD*)0x01122C24 - 160);//x
	b++->setValue(H_DWORD, 0x01122B78, *(DWORD*)0x01122B78 - 160);//x
	b++->setValue(H_DWORD, 0x01123365, *(DWORD*)0x01123365 - 160);//x
	b++->setValue(H_DWORD, 0x01123386, *(DWORD*)0x01123386 - 160);//x
	b++->setValue(H_DWORD, 0x011233B0, *(DWORD*)0x011233B0 - 160);//x
	void* CNSelectDungeonModule__drawAdvanceAltar_11218E0 = (void*)tools_relocation_hook(0x11218E0, 0x011237DA, hook);
	writeCallCode((void*)0x0112521F, CNSelectDungeonModule__drawAdvanceAltar_11218E0);

	//sub_1119340
	*(DWORD*)0x01119452 -= 160;//x

	//右上角副本信息
	*(DWORD*)0x004D31A9 -= 140;//背景
	*(DWORD*)0x004D31DC -= 130;//文本

	hook->resize(7);
	b = hook->begin();
	//CNRDBaseInterfaceHud::DrawProc_4D2AE0 -> AdvanceAltar::drawEndlessModeHud_54E090 无尽模式
	/**(DWORD*)0x0054E0DB -= 160;//阶段背景
	*(DWORD*)0x0054E11E -= 160;//频道信息背景
	*(DWORD*)0x0054E21D -= 160;//频道
	*(DWORD*)0x0054E23F -= 160;//频道
	*(DWORD*)0x0054E292 -= 160;//阶段图标
	*(DWORD*)0x0054E3FC -= 160;//阶段数值
	*(DWORD*)0x0054E384 -= 160;//阶段图标大
	//*(DWORD*)0x0054DFF6 -= 160;//血蓝条 sub_54DF10*/
	*(DWORD*)0x0054DEF4 -= 160;//阶段背景光圈 sub_54DE10
	b++->setValue(H_DWORD, 0x0054E0DB, *(DWORD*)0x0054E0DB - 160);//阶段背景
	b++->setValue(H_DWORD, 0x0054E11E, *(DWORD*)0x0054E11E - 160);//频道信息背景
	b++->setValue(H_DWORD, 0x0054E21D, *(DWORD*)0x0054E21D - 160);//频道
	b++->setValue(H_DWORD, 0x0054E23F, *(DWORD*)0x0054E23F - 160);//频道
	b++->setValue(H_DWORD, 0x0054E292, *(DWORD*)0x0054E292 - 160);//阶段图标
	b++->setValue(H_DWORD, 0x0054E3FC, *(DWORD*)0x0054E3FC - 160);//阶段数值
	b++->setValue(H_DWORD, 0x0054E384, *(DWORD*)0x0054E384 - 160);//阶段图标大
	//b++->setValue(H_DWORD, 0x0054DEF4, *(DWORD*)0x0054DEF4 - 160);//阶段背景光圈 sub_54DE10
	void* AdvanceAltar__drawEndlessModeHud_54E090 = (void*)tools_relocation_hook(0x54E090, 0x0054E426, hook);
	writeCallCode((void*)0x004D30B2, AdvanceAltar__drawEndlessModeHud_54E090);

	hook->resize(16);
	b = hook->begin();
	//AdvanceAltarUiSub0::ProcDraw_54F3B0
	/**(DWORD*)0x0054F3D9 -= 80; 
	*(BYTE*)0x0054F3D7 -= 25;
	*(DWORD*)0x0054F418 -= 80; 
	*(BYTE*)0x0054F41D -= 25; 
	*(DWORD*)0x0054F411 -= 80;  
	*(BYTE*)0x0054F40A -= 25;
	*(DWORD*)0x0054F434 -= 80; 
	*(BYTE*)0x0054F432 -= 25;
	*(DWORD*)0x0054F456 -= 80; 
	*(BYTE*)0x0054F453 -= 25;
	*(DWORD*)0x0054F535 -= 80; 
	*(BYTE*)0x0054F532 -= 25;
	*(DWORD*)0x0054F54F -= 80; 
	*(BYTE*)0x0054F54C -= 25;
	*(DWORD*)0x0054F5F7 -= 80; 
	*(DWORD*)0x0054F652 -= 80; */
	b++->setValue(H_DWORD, 0x0054F3D9, *(DWORD*)0x0054F3D9 - 80);
	b++->setValue(H_BYTE, 0x0054F3D7, *(BYTE*)0x0054F3D7 - 25);
	b++->setValue(H_DWORD, 0x0054F418, *(DWORD*)0x0054F418 - 80);
	b++->setValue(H_BYTE, 0x0054F41D, *(BYTE*)0x0054F41D - 25);
	b++->setValue(H_DWORD, 0x0054F411, *(DWORD*)0x0054F411 - 80);
	b++->setValue(H_BYTE, 0x0054F40A, *(BYTE*)0x0054F40A - 25);
	b++->setValue(H_DWORD, 0x0054F434, *(DWORD*)0x0054F434 - 80);
	b++->setValue(H_BYTE, 0x0054F432, *(BYTE*)0x0054F432 - 25);
	b++->setValue(H_DWORD, 0x0054F456, *(DWORD*)0x0054F456 - 80);
	b++->setValue(H_BYTE, 0x0054F453, *(BYTE*)0x0054F453 - 25);
	b++->setValue(H_DWORD, 0x0054F535, *(DWORD*)0x0054F535 - 80);
	b++->setValue(H_BYTE, 0x0054F532, *(BYTE*)0x0054F532 - 25);
	b++->setValue(H_DWORD, 0x0054F54F, *(DWORD*)0x0054F54F - 80);
	b++->setValue(H_BYTE, 0x0054F54C, *(BYTE*)0x0054F54C - 25);
	b++->setValue(H_DWORD, 0x0054F5F7, *(DWORD*)0x0054F5F7 - 80);
	b++->setValue(H_DWORD, 0x0054F652, *(DWORD*)0x0054F652 - 80);
	void* AdvanceAltarUiSub0__ProcDraw_54F3B0 = (void*)tools_relocation_hook(0x54F3B0, 0x0054F6CF, hook);

	hook->resize(15);
	b = hook->begin();
	//AdvanceAltarUiSub1::ProcDraw_54E880
	/**(DWORD*)0x0054EAC1 -= 120;
	*(DWORD*)0x0054EB00 -= 120;
	*(DWORD*)0x0054EB16 -= 120;
	*(DWORD*)0x0054EA3B -= 120;
	*(DWORD*)0x0054EA7B -= 120;
	*(DWORD*)0x0054EA91 -= 120;
	*(DWORD*)0x0054EB38 -= 120;
	*(DWORD*)0x0054EBA1 -= 120;
	*(DWORD*)0x0054EBE1 -= 120;
	*(DWORD*)0x0054EC49 -= 120;
	*(DWORD*)0x0054EC8B -= 120;
	*(DWORD*)0x0054ECFF -= 120;
	*(DWORD*)0x0054ED60 -= 120;
	*(DWORD*)0x0054ED57 -= 120;
	*(DWORD*)0x0054ED83 -= 120;*/
	b++->setValue(H_DWORD, 0x0054EAC1, *(DWORD*)0x0054EAC1 - 120);
	b++->setValue(H_DWORD, 0x0054EB00, *(DWORD*)0x0054EB00 - 120);
	b++->setValue(H_DWORD, 0x0054EB16, *(DWORD*)0x0054EB16 - 120);
	b++->setValue(H_DWORD, 0x0054EA3B, *(DWORD*)0x0054EA3B - 120);
	b++->setValue(H_DWORD, 0x0054EA7B, *(DWORD*)0x0054EA7B - 120);
	b++->setValue(H_DWORD, 0x0054EA91, *(DWORD*)0x0054EA91 - 120);
	b++->setValue(H_DWORD, 0x0054EB38, *(DWORD*)0x0054EB38 - 120);
	b++->setValue(H_DWORD, 0x0054EBA1, *(DWORD*)0x0054EBA1 - 120);
	b++->setValue(H_DWORD, 0x0054EBE1, *(DWORD*)0x0054EBE1 - 120);
	b++->setValue(H_DWORD, 0x0054EC49, *(DWORD*)0x0054EC49 - 120);
	b++->setValue(H_DWORD, 0x0054EC8B, *(DWORD*)0x0054EC8B - 120);
	b++->setValue(H_DWORD, 0x0054ECFF, *(DWORD*)0x0054ECFF - 120);
	b++->setValue(H_DWORD, 0x0054ED60, *(DWORD*)0x0054ED60 - 120);
	b++->setValue(H_DWORD, 0x0054ED57, *(DWORD*)0x0054ED57 - 120);
	b++->setValue(H_DWORD, 0x0054ED83, *(DWORD*)0x0054ED83 - 120);
	void* AdvanceAltarUiSub1__ProcDraw_54E880 = (void*)tools_relocation_hook(0x54E880, 0x0054F113, hook);

	hook->resize(8);
	b = hook->begin();
	//AdvanceAltarUiSub2::ProcDraw_54F120
	/**(BYTE*)0x0054F18D -= 25;
	*(BYTE*)0x0054F1F5 -= 25;
	*(BYTE*)0x0054F290 -= 25;
	*(BYTE*)0x0054F2D6 -= 25; 
	*(BYTE*)0x0054F2D0 -= 25;
	*(BYTE*)0x0054F2F3 -= 25;
	*(BYTE*)0x0054F345 -= 25;
	*(BYTE*)0x0054F36B -= 25;*/
	b++->setValue(H_BYTE, 0x0054F18D, *(BYTE*)0x0054F18D - 25);
	b++->setValue(H_BYTE, 0x0054F1F5, *(BYTE*)0x0054F1F5 - 25);
	b++->setValue(H_BYTE, 0x0054F290, *(BYTE*)0x0054F290 - 25);
	b++->setValue(H_BYTE, 0x0054F2D6, *(BYTE*)0x0054F2D6 - 25);
	b++->setValue(H_BYTE, 0x0054F2D0, *(BYTE*)0x0054F2D0 - 25);
	b++->setValue(H_BYTE, 0x0054F2F3, *(BYTE*)0x0054F2F3 - 25);
	b++->setValue(H_BYTE, 0x0054F345, *(BYTE*)0x0054F345 - 25);
	b++->setValue(H_BYTE, 0x0054F36B, *(BYTE*)0x0054F36B - 25);
	void* AdvanceAltarUiSub2__ProcDraw_54F120 = (void*)tools_relocation_hook(0x54F120, 0x0054F3A1, hook);

	//AdvanceAltar::ProcDraw_5729B0 -> AdvanceAltarUi__ProcDraw_54F6D0
	hook->resize(3);
	b = hook->begin();
	b++->setValue(H_CALL, 0x0054F6DC, (int)AdvanceAltarUiSub0__ProcDraw_54F3B0);
	b++->setValue(H_CALL, 0x0054F6E4, (int)AdvanceAltarUiSub1__ProcDraw_54E880);
	b++->setValue(H_JUMP, 0x0054F6ED, (int)AdvanceAltarUiSub2__ProcDraw_54F120);
	void* AdvanceAltarUi__ProcDraw_54F6D0 = (void*)tools_relocation_hook(0x54F6D0, 0x0054F6F4, hook);
	writeCallCode((void*)0x005729EA, AdvanceAltarUi__ProcDraw_54F6D0);

	hook->resize(20);
	b = hook->begin();
	//CNRDBaseInterfaceHud::DrawProc_4D2AE0 -> AdvanceAltar::drawTutorial_576F00
	/**(DWORD*)0x00577396 -= 80; // 请使用技能
	*(BYTE*)0x00577384 -= 60;
	*(DWORD*)0x005773D8 -= 80; 
	*(BYTE*)0x005773BD -= 60;
	*(DWORD*)0x005774A4 -= 80; 
	*(DWORD*)0x0057748F -= 60;
	*(DWORD*)0x0057761F -= 80; // 请召唤士兵
	*(BYTE*)0x0057760D -= 60;
	*(DWORD*)0x00577661 -= 80; 
	*(BYTE*)0x00577646 -= 60;
	*(DWORD*)0x00577731 -= 80; 
	*(DWORD*)0x0057771C -= 60;
	*(DWORD*)0x0057784A -= 120;// 可按Z键使用技能！
	*(DWORD*)0x00577884 -= 120;
	*(DWORD*)0x005778BD -= 80; 
	*(DWORD*)0x0057798D -= 80; 
	*(DWORD*)0x00577146 -= 80; // 请守护召唤阵！ 若角色死亡或召唤阵被破坏， 则闯关结束。
	*(BYTE*)0x00577134 -= 60;
	*(DWORD*)0x00577221 -= 80; 
	*(DWORD*)0x00577209 -= 60;*/
	b++->setValue(H_DWORD, 0x00577396, *(DWORD*)0x00577396 - 80); // 请使用技能
	b++->setValue(H_BYTE, 0x00577384, *(BYTE*)0x00577384 - 60);
	b++->setValue(H_DWORD, 0x005773D8, *(DWORD*)0x005773D8 - 80);
	b++->setValue(H_BYTE, 0x005773BD, *(BYTE*)0x005773BD - 60);
	b++->setValue(H_DWORD, 0x005774A4, *(DWORD*)0x005774A4 - 80);
	b++->setValue(H_DWORD, 0x0057748F, *(DWORD*)0x0057748F - 60);
	b++->setValue(H_DWORD, 0x0057761F, *(DWORD*)0x0057761F - 80); // 请召唤士兵
	b++->setValue(H_BYTE, 0x0057760D, *(BYTE*)0x0057760D - 60);
	b++->setValue(H_DWORD, 0x00577661, *(DWORD*)0x00577661 - 80);
	b++->setValue(H_BYTE, 0x00577646, *(BYTE*)0x00577646 - 60);
	b++->setValue(H_DWORD, 0x00577731, *(DWORD*)0x00577731 - 80);
	b++->setValue(H_DWORD, 0x0057771C, *(DWORD*)0x0057771C - 60);
	b++->setValue(H_DWORD, 0x0057784A, *(DWORD*)0x0057784A - 120);// 可按Z键使用技能！
	b++->setValue(H_DWORD, 0x00577884, *(DWORD*)0x00577884 - 120);
	b++->setValue(H_DWORD, 0x005778BD, *(DWORD*)0x005778BD - 80);
	b++->setValue(H_DWORD, 0x0057798D, *(DWORD*)0x0057798D - 80);
	b++->setValue(H_DWORD, 0x00577146, *(DWORD*)0x00577146 - 80); // 请守护召唤阵！ 若角色死亡或召唤阵被破坏， 则闯关结束。
	b++->setValue(H_BYTE, 0x00577134, *(BYTE*)0x00577134 - 60);
	b++->setValue(H_DWORD, 0x00577221, *(DWORD*)0x00577221 - 80);
	b++->setValue(H_DWORD, 0x00577209, *(DWORD*)0x00577209 - 60);
	void* AdvanceAltar__drawTutorial_576F00 = (void*)tools_relocation_hook(0x576F00, 0x00577A6E, hook);
	writeCallCode((void*)0x004D30BD, AdvanceAltar__drawTutorial_576F00);


	hook->resize(21);
	b = hook->begin();
	//AdvanceAltarRewardView::drawRewardItemWin_432290
	/**(DWORD*)0x00432367 -= 80;
	*(DWORD*)0x00432362 -= 60;
	*(DWORD*)0x00432509 -= 80;
	*(DWORD*)0x00432371 -= 60;
	*(DWORD*)0x00432517 -= 60;
	*(DWORD*)0x0043258E -= 80;
	*(DWORD*)0x00432589 -= 60;
	*(DWORD*)0x0043259A -= 60;
	*(DWORD*)0x004323FE -= 80;
	*(DWORD*)0x004323F9 -= 60;
	*(DWORD*)0x0043240B -= 80;
	*(DWORD*)0x00432480 -= 80;
	*(DWORD*)0x00432471 -= 60;
	*(DWORD*)0x00432489 -= 60;
	*(DWORD*)0x00432647 -= 80;
	*(DWORD*)0x0043274E -= 80;
	*(DWORD*)0x004327C4 -= 80;
	*(DWORD*)0x00432994 -= 80;
	*(DWORD*)0x00432893 -= 80;
	*(DWORD*)0x004328A3 -= 80;
	*(DWORD*)0x00432920 -= 80;*/
	b++->setValue(H_DWORD, 0x00432367, *(DWORD*)0x00432367 - 80);
	b++->setValue(H_DWORD, 0x00432362, *(DWORD*)0x00432362 - 60);
	b++->setValue(H_DWORD, 0x00432509, *(DWORD*)0x00432509 - 80);
	b++->setValue(H_DWORD, 0x00432371, *(DWORD*)0x00432371 - 60);
	b++->setValue(H_DWORD, 0x00432517, *(DWORD*)0x00432517 - 60);
	b++->setValue(H_DWORD, 0x0043258E, *(DWORD*)0x0043258E - 80);
	b++->setValue(H_DWORD, 0x00432589, *(DWORD*)0x00432589 - 60);
	b++->setValue(H_DWORD, 0x0043259A, *(DWORD*)0x0043259A - 60);
	b++->setValue(H_DWORD, 0x004323FE, *(DWORD*)0x004323FE - 80);
	b++->setValue(H_DWORD, 0x004323F9, *(DWORD*)0x004323F9 - 60);
	b++->setValue(H_DWORD, 0x0043240B, *(DWORD*)0x0043240B - 80);
	b++->setValue(H_DWORD, 0x00432480, *(DWORD*)0x00432480 - 80);
	b++->setValue(H_DWORD, 0x00432471, *(DWORD*)0x00432471 - 60);
	b++->setValue(H_DWORD, 0x00432489, *(DWORD*)0x00432489 - 60);
	b++->setValue(H_DWORD, 0x00432647, *(DWORD*)0x00432647 - 80);
	b++->setValue(H_DWORD, 0x0043274E, *(DWORD*)0x0043274E - 80);
	b++->setValue(H_DWORD, 0x004327C4, *(DWORD*)0x004327C4 - 80);
	b++->setValue(H_DWORD, 0x00432994, *(DWORD*)0x00432994 - 80);
	b++->setValue(H_DWORD, 0x00432893, *(DWORD*)0x00432893 - 80);
	b++->setValue(H_DWORD, 0x004328A3, *(DWORD*)0x004328A3 - 80);
	b++->setValue(H_DWORD, 0x00432920, *(DWORD*)0x00432920 - 80);
	void* AdvanceAltarRewardView__drawRewardItemWin_432290 = (void*)tools_relocation_hook(0x432290, 0x004329A6, hook);

	hook->resize(20 + 1);
	b = hook->begin();
	//AdvanceAltarRewardView::ProcDraw_433880
	/**(DWORD*)0x00433AD3 -= 80;
	*(DWORD*)0x00433B83 -= 80;
	*(DWORD*)0x00433CDF -= 80; 
	*(DWORD*)0x00433D4A -= 60; 
	*(DWORD*)0x00433DD3 -= 60; 
	*(DWORD*)0x00433E2F -= 60;
	*(DWORD*)0x00433EE7 -= 80; 
	*(DWORD*)0x00433EE1 -= 60;
	*(DWORD*)0x00433F15 -= 80; 
	*(DWORD*)0x00433F10 -= 60;
	*(DWORD*)0x00434049 -= 80;
	*(DWORD*)0x0043409C -= 80;
	*(DWORD*)0x004340E7 -= 80;
	*(DWORD*)0x0043414B -= 80;
	*(DWORD*)0x00434205 -= 80;
	*(DWORD*)0x004341B3 -= 80;
	*(DWORD*)0x004338B0 -= 60;
	*(DWORD*)0x00433E6B -= 60;
	*(DWORD*)0x00433F32 -= 60;
	*(DWORD*)0x004342C4 -= 80;*/
	b++->setValue(H_DWORD, 0x00433AD3, *(DWORD*)0x00433AD3 - 80);
	b++->setValue(H_DWORD, 0x00433B83, *(DWORD*)0x00433B83 - 80);
	b++->setValue(H_DWORD, 0x00433CDF, *(DWORD*)0x00433CDF - 80);
	b++->setValue(H_DWORD, 0x00433D4A, *(DWORD*)0x00433D4A - 60);
	b++->setValue(H_DWORD, 0x00433DD3, *(DWORD*)0x00433DD3 - 60);
	b++->setValue(H_DWORD, 0x00433E2F, *(DWORD*)0x00433E2F - 60);
	b++->setValue(H_DWORD, 0x00433EE7, *(DWORD*)0x00433EE7 - 80);
	b++->setValue(H_DWORD, 0x00433EE1, *(DWORD*)0x00433EE1 - 60);
	b++->setValue(H_DWORD, 0x00433F15, *(DWORD*)0x00433F15 - 80);
	b++->setValue(H_DWORD, 0x00433F10, *(DWORD*)0x00433F10 - 60);
	b++->setValue(H_DWORD, 0x00434049, *(DWORD*)0x00434049 - 80);
	b++->setValue(H_DWORD, 0x0043409C, *(DWORD*)0x0043409C - 80);
	b++->setValue(H_DWORD, 0x004340E7, *(DWORD*)0x004340E7 - 80);
	b++->setValue(H_DWORD, 0x0043414B, *(DWORD*)0x0043414B - 80);
	b++->setValue(H_DWORD, 0x00434205, *(DWORD*)0x00434205 - 80);
	b++->setValue(H_DWORD, 0x004341B3, *(DWORD*)0x004341B3 - 80);
	b++->setValue(H_DWORD, 0x004338B0, *(DWORD*)0x004338B0 - 60);
	b++->setValue(H_DWORD, 0x00433E6B, *(DWORD*)0x00433E6B - 60);
	b++->setValue(H_DWORD, 0x00433F32, *(DWORD*)0x00433F32 - 60);
	b++->setValue(H_DWORD, 0x004342C4, *(DWORD*)0x004342C4 - 80);
	b++->setValue(H_CALL, 0x00433C54, (int)AdvanceAltarRewardView__drawRewardItemWin_432290);
	void* AdvanceAltarRewardView__ProcDraw_433880 = (void*)tools_relocation_hook(0x433880, 0x004346D5, hook);
	*(DWORD*)0x01813558 = (int)AdvanceAltarRewardView__ProcDraw_433880;

	//AdvanceAltarRewardView::setState_433650
	*(DWORD*)0x00433761 -= 80; 
	*(BYTE*)0x0043375F -= 60;
	*(DWORD*)0x01566A50 -= 80; 
	*(DWORD*)0x01566A54 -= 60;
	*(DWORD*)0x01566A58 -= 80; 
	*(DWORD*)0x01566A5C -= 60;

	//CNAdvanceAltarDungeonModule::init_42C460
	*(DWORD*)0x0042C5AE -= 160;

	//* (DWORD*)0x0042C5A9 -= 120;//暂停按钮

	//*(BYTE*)0x0042C6A8 += 160;
	* (DWORD*)0x0042C6A3 -= 120;//升级按钮

	//开始倒数 common/etc/animation/pvpstartcount.ani
	*(DWORD*)0x004BE266 -= 80; *(DWORD*)0x004BE261 -= 60;
	delete hook;
#else
	//防御升级
	*(DWORD*)0x0111E185 -= 160;//x
	*(DWORD*)0x0111E17D -= 120;//y
	//防御设置
	*(DWORD*)0x0111E29A -= 160;//x
	*(DWORD*)0x0111E295 -= 120;//y
	//领取奖励
	*(DWORD*)0x0111E39C -= 160;//x
	*(DWORD*)0x0111E397 -= 120;//y
	//返回城镇
	*(DWORD*)0x0111E49E -= 160;//x
	*(DWORD*)0x0111E499 -= 120;//y
	//开始
	*(DWORD*)0x0111E5A0 -= 160;//x
	//*(DWORD*)0x0111E59B -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E80D -= 160;//x
	//*(DWORD*)0x0111E808 -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E89D -= 170;//x
	//*(DWORD*)0x0111E898 -= 120;//y

	//ScrollTextView
	*(DWORD*)0x0111E931 -= 160;//x
	//*(DWORD*)0x0111E92C -= 120;//y

	//无限模式
	*(DWORD*)0x0111E9C0 -= 160;//x
	*(DWORD*)0x0111E9BB -= 80;//y


	//197窗口位置
	//writeDWordCode(0x019DDB54, 90);
	//writeDWordCode(0x019DDB58, 483);
	*(DWORD*)0x019DDB54 = 90;//x
	//*(DWORD*)0x019DDB58 = 440;//y
	*(DWORD*)0x005A5151 -= 120;//y
	static int yP = 440;
	*(DWORD*)0x005A4FA1 = (int)&yP;
	*(DWORD*)0x005A4FEF = (int)&yP;
	*(DWORD*)0x005A501C -= 175;//y
	*(DWORD*)0x005A5023 -= 175;//y

	//198窗口位置
	//writeDWordCode(0x019DDAC8, 382);
	//writeDWordCode(0x019DDACC, 440);
	*(DWORD*)0x019DDAC8 = 382;//x
	//*(DWORD*)0x019DDACC = 440;//y
	*(DWORD*)0x005A2861 -= 120;//y
	static int yP2 = 440;
	*(DWORD*)0x005A26B1 = (int)&yP2;
	*(DWORD*)0x005A26FF = (int)&yP2;
	*(DWORD*)0x005A272C -= 175;//y
	*(DWORD*)0x005A2733 -= 175;//y

	////地下城信息
	//*(DWORD*)0x01AFA950 = -160;
	//*(DWORD*)0x01AFA958 = -160;

	*(DWORD*)0x01122590 -= 160;//x
	//*(DWORD*)0x0112258A -= 60;//y
	*(DWORD*)0x01122627 -= 160;//x
	//*(DWORD*)0x01122621 -= 60;//y
	*(DWORD*)0x01122690 -= 160;//x
	//*(DWORD*)0x01122683 -= 60;//y
	*(DWORD*)0x011226BF -= 160;//x
	//*(DWORD*)0x011226B2 -= 60;//y
	*(DWORD*)0x0112272E -= 160;//x
	//*(BYTE*)0x01122725 -= 60;//y
	*(DWORD*)0x01122788 -= 160;//x
	//*(DWORD*)0x01122783 -= 60;//y
	*(DWORD*)0x01122831 -= 160;//x
	//*(BYTE*)0x0112282E -= 60;//y
	*(DWORD*)0x01122940 -= 160;//x
	//*(BYTE*)0x0112293B -= 60;//y
	*(DWORD*)0x01122A93 -= 160;//x
	//*(BYTE*)0x01122A90 -= 60;//y
	*(DWORD*)0x01122B34 -= 160;//x
	//*(DWORD*)0x01122B2F -= 60;//y
	*(DWORD*)0x01122C24 -= 160;//x
	//*(DWORD*)0x01122C19 -= 60;//y
	*(DWORD*)0x01122B78 -= 160;//x
	//*(DWORD*)0x01122BF6 -= 60;//y
	*(DWORD*)0x01123365 -= 160;//x
	//*(BYTE*)0x01123362 -= 60;//y
	*(DWORD*)0x01123386 -= 160;//x
	//*(BYTE*)0x0112338B -= 60;//y
	*(DWORD*)0x011233B0 -= 160;//x
	//*(BYTE*)0x011233AE -= 60;//y

	*(DWORD*)0x01119452 -= 160;//x

	//右上角副本信息
	*(DWORD*)0x004D31A9 -= 140;//背景
	*(DWORD*)0x004D31DC -= 130;//文本

	//AdvanceAltar::drawEndlessModeHud_54E090 无尽模式
	*(DWORD*)0x0054E0DB -= 160;//阶段背景
	*(DWORD*)0x0054E11E -= 160;//频道信息背景
	*(DWORD*)0x0054E21D -= 160;//频道
	*(DWORD*)0x0054E23F -= 160;//频道
	*(DWORD*)0x0054E292 -= 160;//阶段图标
	*(DWORD*)0x0054E3FC -= 160;//阶段数值
	*(DWORD*)0x0054E384 -= 160;//阶段图标大
	//*(DWORD*)0x0054DFF6 -= 160;//血蓝条 sub_54DF10
	*(DWORD*)0x0054DEF4 -= 160;//阶段背景光圈 sub_54DE10

	//AdvanceAltarUiSub0::ProcDraw_54F3B0
	*(DWORD*)0x0054F3D9 -= 80; *(BYTE*)0x0054F3D7 -= 25;
	*(DWORD*)0x0054F418 -= 80; *(BYTE*)0x0054F41D -= 25; *(DWORD*)0x0054F411 -= 80;  *(BYTE*)0x0054F40A -= 25;
	*(DWORD*)0x0054F434 -= 80; *(BYTE*)0x0054F432 -= 25;
	*(DWORD*)0x0054F456 -= 80; *(BYTE*)0x0054F453 -= 25;
	*(DWORD*)0x0054F535 -= 80; *(BYTE*)0x0054F532 -= 25;
	*(DWORD*)0x0054F54F -= 80; *(BYTE*)0x0054F54C -= 25;
	*(DWORD*)0x0054F5F7 -= 80; /**(BYTE*)0x0054F5FE -= 60;*/
	*(DWORD*)0x0054F652 -= 80; /**(BYTE*)0x0054F65C -= 60;*/

	//AdvanceAltarUiSub1::ProcDraw_54E880
	/**(DWORD*)0x0054EAC6 -= 80; */*(DWORD*)0x0054EAC1 -= 120;
	/**(DWORD*)0x0054EB05 -= 80; */*(DWORD*)0x0054EB00 -= 120;
	/**(DWORD*)0x0054EB1B -= 80; */*(DWORD*)0x0054EB16 -= 120;
	/**(DWORD*)0x0054EA40 -= 80; */*(DWORD*)0x0054EA3B -= 120;
	/**(DWORD*)0x0054EA80 -= 80; */*(DWORD*)0x0054EA7B -= 120;
	/**(DWORD*)0x0054EA96 -= 80; */*(DWORD*)0x0054EA91 -= 120;
	/**(BYTE*)0x0054EB3D -= 80; */*(DWORD*)0x0054EB38 -= 120;
	/**(BYTE*)0x0054EBA6 -= 80; */*(DWORD*)0x0054EBA1 -= 120;
	//*(DWORD*)0x0054EBBC -= 80; *(DWORD*)0x01588FD0 -= 80; *(DWORD*)0x01588FD4 -= 80;*(DWORD*)0x01588FD8 -= 80;*(DWORD*)0x01588FDC -= 80;
	*(DWORD*)0x0054EBE1 -= 120;
	*(DWORD*)0x0054EC49 -= 120;
	*(DWORD*)0x0054EC8B -= 120;
	*(DWORD*)0x0054ECFF -= 120;
	*(DWORD*)0x0054ED60 -= 120;
	*(DWORD*)0x0054ED57 -= 120;
	/**(BYTE*)0x0054ED88 -= 80; */*(DWORD*)0x0054ED83 -= 120;

	//AdvanceAltarUiSub2::ProcDraw_54F120
	/**(BYTE*)0x0054F18F -= 20;*/ *(BYTE*)0x0054F18D -= 25;
	/**(BYTE*)0x0054F1F7 -= 20;*/ *(BYTE*)0x0054F1F5 -= 25;
	/**(BYTE*)0x0054F292 -= 20;*/ *(BYTE*)0x0054F290 -= 25;
	/**(BYTE*)0x0054F2D8 -= 20;*(BYTE*)0x0054F2D3 -= 20;*/ *(BYTE*)0x0054F2D6 -= 25; *(BYTE*)0x0054F2D0 -= 25;
	/**(BYTE*)0x0054F2F5 -= 20;*/ *(BYTE*)0x0054F2F3 -= 25;
	/**(BYTE*)0x0054F347 -= 20;*/ *(BYTE*)0x0054F345 -= 25;
	/**(BYTE*)0x0054F36D -= 20;*/ *(BYTE*)0x0054F36B -= 25;

	//AdvanceAltar::drawTutorial_576F00
	// 请使用技能
	*(DWORD*)0x00577396 -= 80; *(BYTE*)0x00577384 -= 60;
	*(DWORD*)0x005773D8 -= 80; *(BYTE*)0x005773BD -= 60;
	*(DWORD*)0x005774A4 -= 80; *(DWORD*)0x0057748F -= 60;
	// 请召唤士兵
	*(DWORD*)0x0057761F -= 80; *(BYTE*)0x0057760D -= 60;
	*(DWORD*)0x00577661 -= 80; *(BYTE*)0x00577646 -= 60;
	*(DWORD*)0x00577731 -= 80; *(DWORD*)0x0057771C -= 60;
	// 可按Z键使用技能！
	/**(BYTE*)0x0057784F -= 80; */*(DWORD*)0x0057784A -= 120;
	/**(BYTE*)0x0057788A -= 80; */*(DWORD*)0x00577884 -= 120;
	*(DWORD*)0x005778BD -= 80; /**(DWORD*)0x005778A5 -= 60;*/
	*(DWORD*)0x0057798D -= 80; /**(DWORD*)0x00577972 -= 60;*/
	// 请守护召唤阵！ 若角色死亡或召唤阵被破坏， 则闯关结束。
	*(DWORD*)0x00577146 -= 80; *(BYTE*)0x00577134 -= 60;
	*(DWORD*)0x00577221 -= 80; *(DWORD*)0x00577209 -= 60;
	//*(BYTE*)0x005772B5 -= 80; *(BYTE*)0x005772B2 -= 60;
	//*(BYTE*)0x005772D8 -= 80; *(DWORD*)0x005772D0 -= 60;
	//*(BYTE*)0x0057731C -= 80; *(DWORD*)0x0057730D -= 60;
	//*(BYTE*)0x00577338 -= 80;

	//AdvanceAltarRewardView::ProcDraw_433880
	*(DWORD*)0x00433AD3 -= 80; /**(BYTE*)0x00433AE0 -= 60;*/
	*(DWORD*)0x00433B83 -= 80; /**(BYTE*)0x00433B8A -= 60;*/
	*(DWORD*)0x00433CDF -= 80; *(DWORD*)0x00433D4A -= 60; *(DWORD*)0x00433DD3 -= 60; *(DWORD*)0x00433E2F -= 60;
	*(DWORD*)0x00433EE7 -= 80; *(DWORD*)0x00433EE1 -= 60;
	*(DWORD*)0x00433F15 -= 80; *(DWORD*)0x00433F10 -= 60;
	*(DWORD*)0x00434049 -= 80;
	*(DWORD*)0x0043409C -= 80;
	*(DWORD*)0x004340E7 -= 80;
	*(DWORD*)0x0043414B -= 80;
	*(DWORD*)0x00434205 -= 80;
	*(DWORD*)0x004341B3 -= 80;
	*(DWORD*)0x004338B0 -= 60;
	*(DWORD*)0x00433E6B -= 60;
	*(DWORD*)0x00433F32 -= 60;
	*(DWORD*)0x004342C4 -= 80;

	//AdvanceAltarRewardView::drawRewardItemWin_432290
	*(DWORD*)0x00432367 -= 80; *(DWORD*)0x00432362 -= 60;
	*(DWORD*)0x00432509 -= 80; *(DWORD*)0x00432371 -= 60; *(DWORD*)0x00432517 -= 60;
	*(DWORD*)0x0043258E -= 80; *(DWORD*)0x00432589 -= 60; *(DWORD*)0x0043259A -= 60;
	*(DWORD*)0x004323FE -= 80; *(DWORD*)0x004323F9 -= 60;
	*(DWORD*)0x0043240B -= 80; *(DWORD*)0x00432480 -= 80; *(DWORD*)0x00432471 -= 60; *(DWORD*)0x00432489 -= 60;
	*(DWORD*)0x00432647 -= 80; *(DWORD*)0x0043274E -= 80; *(DWORD*)0x004327C4 -= 80; *(DWORD*)0x00432994 -= 80; *(DWORD*)0x00432893 -= 80;
	*(DWORD*)0x004328A3 -= 80; *(DWORD*)0x00432920 -= 80;

	//AdvanceAltarRewardView::setState_433650
	*(DWORD*)0x00433761 -= 80; *(BYTE*)0x0043375F -= 60;
	*(DWORD*)0x01566A50 -= 80; *(DWORD*)0x01566A54 -= 60;
	*(DWORD*)0x01566A58 -= 80; *(DWORD*)0x01566A5C -= 60;

	//CNAdvanceAltarDungeonModule::init_42C460
	*(DWORD*)0x0042C5AE -= 160;

	//* (DWORD*)0x0042C5A9 -= 120;//暂停按钮

	//*(BYTE*)0x0042C6A8 += 160;
	* (DWORD*)0x0042C6A3 -= 120;//升级按钮

	//开始倒数 common/etc/animation/pvpstartcount.ani
	*(DWORD*)0x004BE266 -= 80; *(DWORD*)0x004BE261 -= 60;

#endif
}

forceinline void auctionInit() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();
	*(BYTE*)0x00E99B98 = 51; *(BYTE*)0x00E99B96 = 30;//w h
	*(DWORD*)0x00E99BAF -= 160; *(DWORD*)0x00E99BCA -= 120;//x y
	//物品列表
	//AuctionListView::create_E89F90
	*(BYTE*)0x00E8A5FF = 6;
	//AuctionListView::reset_E8B3F0
	*(BYTE*)0x00E8B407 = 6;
	//sub_E865E0
	*(BYTE*)0x00E865F7 = 6 - 1;
	*(BYTE*)0x00E86639 = 6;
	//sub_E87860
	*(BYTE*)0x00E878B1 = 6;
	*(BYTE*)0x00E879FC = 6;
	*(BYTE*)0x00E87B27 = 6;
	*(BYTE*)0x00E87F47 = 6;
	*(BYTE*)0x00E87F9C = 6;
	//sub_E86AC0
	*(BYTE*)0x00E86B9D = 6;
	//sub_E8CC70
	*(BYTE*)0x00E8CCCD = 6;
	*(BYTE*)0x00E8CCED = 0x40;
	*(BYTE*)0x00E8CCF1 = -6;
	*(BYTE*)0x00E8CDC9 = 6;
	*(BYTE*)0x00E8D08E = 6;
	*(BYTE*)0x00E8D355 = 6;

	hook->resize(3);
	b = hook->begin();
	//sub_E8D3F0
	//*(DWORD*)0x00E8D41E = 0x55555556;*(WORD*)0x00E8D424 = 0xEAD1;*(BYTE*)0x00E8D426 = 0x90;
	b++->setValue(H_DWORD, 0x00E8D41E, 0x55555556);
	b++->setValue(H_WORD, 0x00E8D424, 0xEAD1);
	b++->setValue(H_BYTE, 0x00E8D426, 0x90);
	void* sub_E8D3F0 = (void*)tools_relocation_hook(0xE8D3F0, 0x00E8D459, hook);
	writeCallCode((void*)0x00E8D833, sub_E8D3F0);
	writeCallCode((void*)0x00E8D9C0, sub_E8D3F0);

	hook->resize(3);
	b = hook->begin();
	// sub_E86830
	//*(DWORD*)0x00E86844 = 0x55555556; *(WORD*)0x00E8684A = 0xEAD1; *(BYTE*)0x00E8684C = 0x90;
	b++->setValue(H_DWORD, 0x00E86844, 0x55555556);
	b++->setValue(H_WORD, 0x00E8684A, 0xEAD1);
	b++->setValue(H_BYTE, 0x00E8684C, 0x90);
	void* sub_E86830 = (void*)tools_relocation_hook(0xE86830, 0x00E86860, hook);
	writeCallCode((void*)0x00E94569, sub_E86830);
	writeCallCode((void*)0x00E94646, sub_E86830);
	writeCallCode((void*)0x00E94716, sub_E86830);

	//左边搜索栏
	*(DWORD*)0x00E96308 -= 120;//高度
	*(BYTE*)0x00E96398 -= 6;

	//搜索栏控件
	int pos = 20;
	*(DWORD*)0x00E9A6AD -= pos;//请输入搜索关键字  w
	*(DWORD*)0x00E9A772 -= pos;//等级搜索0  x
	*(DWORD*)0x00E9A814 -= pos;//等级搜索1  x
	*(DWORD*)0x00E9AA97 -= pos;//强化搜索0  x
	*(DWORD*)0x00E9AB6A -= pos;//强化搜索1  x
	*(DWORD*)0x00E9AC32 -= pos;//锻造搜索0  x
	*(DWORD*)0x00E9AD05 -= pos;//锻造搜索1  x
	*(DWORD*)0x00E9AE8B -= pos;//搜索物品  x
	*(DWORD*)0x00E9AF15 -= pos;//重置  x
	*(DWORD*)0x00E9A8A2 -= pos;//稀有度  x
	//搜索栏文案
	*(WORD*)0x00E99728 = 0x35EB;
	*(DWORD*)0x00E99752 -= pos;//搜索魔法封印装备  x
	*(DWORD*)0x00E99792 -= pos;//等级  x
	*(DWORD*)0x00E997CC -= pos;//~  x
	*(DWORD*)0x00E99806 -= pos;//强化  x
	*(DWORD*)0x00E99840 -= pos;//~  x
	*(DWORD*)0x00E9987A -= pos;//锻造  x
	*(DWORD*)0x00E998B4 -= pos;//~  x

	//%d/%d 翻页 y
	//可上架的数量 %d/%d
	// 拍卖行优待券图标
	// 拍卖行优待券
	// 剩余时间 : %d天
	// 剩余时间 : %d小时
	// 搜索出%d个
	// 搜到%d个物品的列表
	*(DWORD*)0x00E8726A -= 130;


	*(DWORD*)0x00E9996B = 0x178;// 所持金币y
	*(DWORD*)0x00E9999F = 422;// 所持金币x
	*(DWORD*)0x00E99972 = 485;// 金币x
	*(DWORD*)0x00E998F9 = 470;	*(DWORD*)0x00E998F4 = 371;// 金币icon

	*(DWORD*)0x00E99DC9 -= 130;// y
	*(DWORD*)0x00E923BC -= 130;// y
	*(DWORD*)0x00E92350 -= 130;// y
	*(DWORD*)0x00E92EFF -= 130;// y
	//上架拍卖品 x y 00E99DD5
	// 竞拍 x y 00E99E94
	// 立即购买 00E99F4C
	// 关闭 00E9A006
	// 取消登录  00E9A0C4

	*(DWORD*)0x00E8A55B -= 130;// 上翻页
	*(DWORD*)0x00E8A5BB -= 130;// 下翻页

	*(BYTE*)0x00E994C3 = 0xE9; *(DWORD*)0x00E994C4 = 0x0192;
	*(WORD*)0x00E993FC = 0x75EB;
	*(DWORD*)0x00E9A424 = -10000;
	delete hook;
}

forceinline void goldAuctionInit() {
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(128);
	auto b = hook->begin();
	*(BYTE*)0x0056EAC2 = 51; *(BYTE*)0x0056EAC0 = 30;//w h
	*(DWORD*)0x0056EAD8 -= 160; *(DWORD*)0x0056EAF3 -= 120;//x y

	//物品列表
	//GoldAuctionListView::create_5658C0
	*(BYTE*)0x00565E3E = 6;
	//GoldAuctionListView::reset_567150
	*(BYTE*)0x0056715C = 6;
	//sub_563070
	*(BYTE*)0x00563087 = 6 - 1;
	*(BYTE*)0x005630C9 = 6;
	//sub_563E80
	*(BYTE*)0x00563F2C = 6;
	*(BYTE*)0x00563ED1 = 6;
	*(BYTE*)0x00563F81 = 6;
	*(BYTE*)0x00564182 = 6;
	*(BYTE*)0x005641D7 = 6;
	//sub_563420
	*(BYTE*)0x005634FD = 6;
	//sub_567FD0
	*(BYTE*)0x0056806C = 6;
	*(BYTE*)0x00568098 = -6;
	*(BYTE*)0x0056808C = 0x40;
	*(BYTE*)0x00568169 = 6;
	*(BYTE*)0x0056840D = 6;

	hook->resize(3);
	b = hook->begin();
	//sub_5684A0
	//*(DWORD*)0x005684CE = 0x55555556; *(WORD*)0x005684D4 = 0xEAD1; *(BYTE*)0x005684D6 = 0x90;
	b++->setValue(H_DWORD, 0x005684CE, 0x55555556);
	b++->setValue(H_WORD, 0x005684D4, 0xEAD1);
	b++->setValue(H_BYTE, 0x005684D6, 0x90);
	void* sub_5684A0 = (void*)tools_relocation_hook(0x5684A0, 0x00568509, hook);
	writeCallCode((void*)0x00568763, sub_5684A0);
	writeCallCode((void*)0x005688F0, sub_5684A0);

	hook->resize(3);
	b = hook->begin();
	//sub_5632C0
	//*(DWORD*)0x005632D4 = 0x55555556; *(WORD*)0x005632DA = 0xEAD1; *(BYTE*)0x005632DC = 0x90;
	b++->setValue(H_DWORD, 0x005632D4, 0x55555556);
	b++->setValue(H_WORD, 0x005632DA, 0xEAD1);
	b++->setValue(H_BYTE, 0x005632DC, 0x90);
	void* sub_5632C0 = (void*)tools_relocation_hook(0x5632C0, 0x005632F0, hook);
	writeCallCode((void*)0x0056C929, sub_5632C0);
	writeCallCode((void*)0x0056CA06, sub_5632C0);
	writeCallCode((void*)0x0056CAD6, sub_5632C0);

	// 上架拍卖品  取消登录 立即购买 关闭
	*(DWORD*)0x0056ECC9 -= 130;// y
	*(DWORD*)0x0056F1E5 -= 160; *(DWORD*)0x0056F1D4 -= 130;//刷新
	*(DWORD*)0x0056F289 -= 160; *(DWORD*)0x0056F278 -= 130;//商城
	*(DWORD*)0x0056A870 -= 130;// y
	*(DWORD*)0x0056B28D -= 130;// y

	*(DWORD*)0x0056F647 -= 30;// 搜索物品 x
	*(DWORD*)0x0056F776 -= 30;// 重置搜索条件 x

	//GoldAuctionListView::drawInfo_5638C0
	*(DWORD*)0x0056397A -= 130;// y

	//左边搜索栏 GolddAuctionWin::createSeachBar_56E600
	*(DWORD*)0x0056E668 -= 120;//高度
	*(BYTE*)0x0056E6E6 -= 6;

	*(DWORD*)0x00565D9A -= 130;// 上翻页
	*(DWORD*)0x00565DFA -= 130;// 下翻页

	//金币
	*(DWORD*)0x0056B126 = 442; *(DWORD*)0x0056B11F = 373;// 金币
	*(DWORD*)0x0056B0A1 = 480;	*(DWORD*)0x0056B09C = 368;// 金币icon


	*(WORD*)0x0056AF6D = 0x75EB;
	delete hook;
}


forceinline void hudPartyView(GumInterceptor* v) {
	////*(DWORD*)0x004D6E67 = 136;//x
	////*(DWORD*)0x004D6E70 = *(DWORD*)0x004D6E67 * 4 + 4;//x
	//*(BYTE*)0x004D6E48 = 4;//y
	////*(DWORD*)0x004D6E2F = 133;//w
	////*(BYTE*)0x004D6E2D = 29;//h
	//
	////血蓝槽长度
	//*(DWORD*)0x004C45E5 = 100 + 29;//w 29为头像宽度
	////血条长度
	//*(BYTE*)0x004C48CE = 100;
	//*(BYTE*)0x004C48EA = 100;
	////蓝条长度
	//*(DWORD*)0x004C489D = 100;
	//*(DWORD*)0x004C48EC = 0x8AD8F2FC;//0x8AD8F2FC/59 0x51EB851F/100

	*(DWORD*)0x004D6E67 = 136 - 41;//x
	*(DWORD*)0x004D6E70 = *(DWORD*)0x004D6E67 * 4 + 4;//x
	*(BYTE*)0x004D6E48 = 4;//y
	*(DWORD*)0x004D6E2F = 133 - 41;//w
	//*(BYTE*)0x004D6E2D = 29;//h

	//城镇 血蓝槽长度 drawTownHudTeamStateView_4C4560
	*(DWORD*)0x004C45E5 = 59 + 29;//w 29为头像宽度
	//血条长度
	*(BYTE*)0x004C48CE = 59;
	*(BYTE*)0x004C48EA = 59;
	//*(DWORD*)0x004C48D0 = 0x75270D05;//0x75270D05/59 0x51EB851F/100
	//蓝条长度
	*(DWORD*)0x004C489D = 59;
	//*(DWORD*)0x004C48EC = 0x75270D05;//0x75270D05/59 0x51EB851F/100

	//地下城 血蓝槽长度 drawDungeonHudTeamStateView_4BD630
	*(DWORD*)0x004BD700 = 59 + 29;//w 29为头像宽度
	*(DWORD*)0x004BD751 = 59 + 29;//w 29为头像宽度
	*(BYTE*)0x004BD9D2 = 59;
	*(BYTE*)0x004BD9FD = 59;
}
//(*(int***)0x1AEDCEC)[0x8D]0x1AEDCEC  +0x234

int mapZoomRate = 0x3F4CCCCD;//0.8
int mapZoomParam = 0;//0x7E967699 中心对齐

int __cdecl getMinimapDungeonPos(int defaultValue) {
	return ScanInt_1223660(defaultValue) * 0.8f + 3;
}

thisCall5Args2 sub_1048B80;
int* __fastcall hookSub_1048B80(int* thisP, int edx, int a2, int a3, int a4, int a5, int a6) {
	int* p = (int*)sub_1048B80(thisP, a2, a3, a4, a5, a6);
	//if ((int)_ReturnAddress() == 0x00E49EF9) {
	p[0] *= 0.8f;
	p[1] *= 0.8f;
	//}
	return p;
}

int  getMinimapMousePosX(void) {
	return MousePosX * 1.25f;
}

int  getMinimapMousePosY(void) {
	return MousePosY * 1.25f;
}

thisCall2 WorldmapView__init_10395B0;
int __fastcall hookWorldmapView__init_10395B0(int** thisP) {
	int p = WorldmapView__init_10395B0((int*)thisP);
	setUiComponentVisable_11BE610(thisP[0x24], 0);
	setUiComponentVisable_11BE610(thisP[0x23], 0);

	setUiComponentPos_11BEAD0(thisP[0x2A], 237, 8, 1); //按NPC名称搜索 下拉蓝色按钮
	setUiComponentPos_11BEAD0(thisP[0x29], 131, 7, 1); //按NPC名称搜索 黑框主体

	setUiComponentPos_11BEAD0(thisP[0xC], 426, 8, 1); //按NPC功能搜索 下拉蓝色按钮
	setUiComponentPos_11BEAD0(thisP[0xB], 320, 7, 1); //按NPC功能搜索 黑框主体

	setUiComponentPos_11BEAD0(thisP[0x22], 587, 11, 1); //查看适合等级的任务 checkbox

	setUiComponentPos_11BEAD0(thisP[0x47], 620, 12, 1); //右上角关闭按钮
	return p;
}

forceinline void wordMapView() {
	GumInterceptor* v = gum_interceptor_obtain();
	*(DWORD*)0x0103BE94 = (int)&mapZoomRate;
	*(DWORD*)0x0103BE7B = (int)&mapZoomParam;
	writeCallCode((LPVOID*)0x00E4B9A6, (LPVOID)getMinimapDungeonPos);
	writeCallCode((LPVOID*)0x00E4B9AF, (LPVOID)getMinimapDungeonPos);
	gum_interceptor_replace_fast(v, (gpointer)0x1048B80, (gpointer)hookSub_1048B80, (gpointer*)&sub_1048B80);

	writeCallCode((LPVOID*)0x01048925, (LPVOID)getMinimapMousePosX);
	writeCallCode((LPVOID*)0x0104892C, (LPVOID)getMinimapMousePosY);
	writeCallCode((LPVOID*)0x0103CC93, (LPVOID)getMinimapMousePosX);
	writeCallCode((LPVOID*)0x0103CC9E, (LPVOID)getMinimapMousePosY);

	gum_interceptor_replace_fast(v, (gpointer)0x10395B0, (gpointer)hookWorldmapView__init_10395B0, (gpointer*)&WorldmapView__init_10395B0);
	*(DWORD*)0x0103B072 = 480;//查看符合等级的任务 文案

	*(BYTE*)0x0111637B = 0xeb; //不显示城镇地图窗口
}



thisCall2Args2 GeneralPopupWin__OnOpen_FC3C70;
char __fastcall hookGeneralPopupWin__OnOpen_FC3C70(int* thisP, int, int a2, int a3) {
	int ret = GeneralPopupWin__OnOpen_FC3C70(thisP, a2, a3);
	BasePopupWin__setCenterPos_EF63A0(thisP);
	return ret;
}

int __fastcall BasePopupWin__setVCenterPos_EF63A0(int* thisP, int x) {
	int** thipp = (int **)thisP;
	int y = (240 - (thipp[3][15] >> 1));
	return setUiComponentPos_11BEAD0(thipp[3], x, y, 1);
}

int __fastcall BasePopupWin__setRBPos_EF63A0(int* thisP) {
	int** thipp = (int**)thisP;
	int h = thipp[3][15] + 20;
	int w = thipp[3][14] + 20;
	int x = 640 - w;
	int y = 480 - h;
	return setUiComponentPos_11BEAD0(thipp[3], x, y, 1);
}

extern char __fastcall hookCloseNavigationWin(char* thisP);
char __fastcall hookPopupWin__OnOpen_Cb(int* thisP, int, int a2, int a3) {
	thisCall2Args2 onOpen = (thisCall2Args2)Vtable(thisP, 0x14);
	int ret = onOpen(thisP, a2, a3);
	int id = thisP[2];
	if (id == 0x11A || id == 0x115 || id == 0x116 || id == 0x117) {
		return ret;
	}
	switch (id) {//id
	case 0x02: BasePopupWin__setPos_EF63E0(thisP, 390, 120, 0); break;//今日伙伴
	case 0x06: BasePopupWin__setPos_EF63E0(thisP, 286, 82, 0); break;//寻找队伍
	case 0x08: BasePopupWin__setPos_EF63E0(thisP, 19, 82, 0); break;//我的队伍
	case 0x18: BasePopupWin__setPos_EF63E0(thisP, 323, 50, 0); break;//社交
	case 0x2d: BasePopupWin__setPos_EF63E0(thisP, 0x40, 0x92, 0); break;//时装合成器
	case 0x2E: BasePopupWin__setPos_EF63E0(thisP, 0x40, 0x92, 0); break;//时装属性调整箱
		//case 0x15: BasePopupWin__setPos_EF63E0(thisP, 70, 115, 0); break;//npc委托任务
		//case 0x16: BasePopupWin__setPos_EF63E0(thisP, 340, 115, 0); break;//进行中的任务
	case 0x19://魔法封印
	case 0x1A://魔法封印
	case 0x1B://魔法封印
	case 0x1D:BasePopupWin__setPos_EF63E0(thisP, 85, 165, 0); break;//魔法封印
		//case 0x14://任务手册
	case 0x2A: BasePopupWin__setPos_EF63E0(thisP, 44, 145, 0); break;//魔法封印
	case 0x30: BasePopupWin__setVCenterPos_EF63A0(thisP, 0x49); break;//装备合成
	case 0x32: BasePopupWin__setPos_EF63E0(thisP, 70, 70, 0); break;//邮箱
	case 0x37: BasePopupWin__setPos_EF63E0(thisP, 0x6B, 0xD7, 0); break;//品级调整窗口
	case 0x38: 
		//npc商店  
		if(BasePopupWin__getWinHeight_EF5E90(thisP) == 130)BasePopupWin__setPos_EF63E0(thisP, 0x15, 0x124, 0); //加百利
		else BasePopupWin__setPos_EF63E0(thisP, 75, 143, 0);
		break;
	case 0x39: BasePopupWin__setPos_EF63E0(thisP, 55, 35, 0); break;//仓库
	case 0x3B: BasePopupWin__setVCenterPos_EF63A0(thisP, 340); break;//他人信息窗
	case 0x40: BasePopupWin__setVCenterPos_EF63A0(thisP, 335); break;//物品栏
	case 0x4C: BasePopupWin__setVCenterPos_EF63A0(thisP, 55); break;//个人信息
	case 0x53: BasePopupWin__setPos_EF63E0(thisP, 95, 95, 0); break;//活动
	case 0x54: BasePopupWin__setPos_EF63E0(thisP, 380, 165, 0); break;//活动信息
	case 0x64: BasePopupWin__setVCenterPos_EF63A0(thisP, 336); break;//附魔/炼金制作窗口
	case 0x71: BasePopupWin__setPos_EF63E0(thisP, 0, 0, 0); break;//附魔/
	case 0x79: BasePopupWin__setPos_EF63E0(thisP, 0x51, 0xC5, 0); break;//拍卖行上架窗口
	case 0xAA: BasePopupWin__setPos_EF63E0(thisP, 75, 300, 0); break;//附魔交易窗口
	case 0xB6: BasePopupWin__setPos_EF63E0(thisP, 0x55, 0xEA, 0); break;//镶嵌窗口
	case 0x23: BasePopupWin__setPos_EF63E0(thisP, 206, 185, 0); break;
	case 0xe4: BasePopupWin__setPos_EF63E0(thisP, 380, 310, 0); break;//勇者装备拾取确认窗
	case 0xe5: BasePopupWin__setPos_EF63E0(thisP, 380, 310, 0); break;//领主装备拾取确认窗
	case 0xEE: BasePopupWin__setPos_EF63E0(thisP, 0x179, 0x12B, 0); break;//
	case 0x61: BasePopupWin__setRBPos_EF63A0(thisP); break;//交易邀请/组队邀请
	case 0xF6: BasePopupWin__setPos_EF63E0(thisP, 0x50, 0x30, 0); break;//技能返回窗口
	case 0xF9: BasePopupWin__setPos_EF63E0(thisP, 44, 206, 0); break;//时装染色窗口
	case 0x1C:
	case 0x2C:
	case 0x33:
	case 0x5E:
	case 0x63:
	//case 0x65:
	case 0x68:
	case 0x69:
	case 0x6B:
	case 0x6E:
	case 0x6D:
	case 0x73:
	case 0x77:
	case 0x84:
	case 0x92:
	case 0x97:
	case 0xA4:
	case 0xA5:
	case 0xB4:
	case 0xB5:
	case 0xB7:
	case 0xBF:
	case 0xC0:
	case 0xC2:
	case 0xC8:
	case 0xCD:
	case 0xD3:
	case 0xDD:
	case 0xE1:
	case 0xEA:
	case 0xFB:
	case 0x104:
	case 0x110:
	case 0x12C:
	case 0x12e:
	case 0x144:
	case 0x14a:
	case 0x14C:
	case 0x14D:	
	case 0x14e:
	case 0x15B:
	case 0x164:
	case 0x178:
	case 0x19a:
	case 0x19C:BasePopupWin__setCenterPos_EF63A0(thisP); break;
	}
	if (id != 0x46)
		hookCloseNavigationWin(NULL);
	return ret;
}

thisCall2Args2 BaseNavigationPopupWin__setPos_EE5EF0 = (thisCall2Args2)0xEE5EF0;
char __fastcall hookNavigationPopupWin__OnOpen_Cb(int* thisP) {
	thisCall2 onOpen = (thisCall2)Vtable(thisP, 0x3C);
	int ret = onOpen(thisP);
	switch (thisP[0]) {
	case 0x01812B64:BaseNavigationPopupWin__setPos_EE5EF0(thisP, 352, 48); break;//技能窗
	case 0x01813464:BaseNavigationPopupWin__setPos_EE5EF0(thisP, 80, 102); break;//炼金副职业窗口
	case 0x01812BD4:
		if(GetYPos_11BE300((int *)thisP[1]) != -800)
			BaseNavigationPopupWin__setPos_EE5EF0(thisP, 84, 210); 
		break;//分解/强化/增幅，重铸徽章窗口
	case 0x018138EC:BaseNavigationPopupWin__setPos_EE5EF0(thisP, 84, 112); break;//生产
	case 0x018134DC:BaseNavigationPopupWin__setPos_EE5EF0(thisP, 80, 38); break;//附魔副职业
	case 0x018133F4:BaseNavigationPopupWin__setPos_EE5EF0(thisP, 64, 100); break;//交易窗口
	}
	//hookCloseNavigationWin(NULL);
	return ret;
}

int __fastcall zoom70Draw(int* thisP, int edx, int x, int y, int imgAddr) {
	return drawImgByXY2_11B41E0(thisP, x, y, imgAddr, 0.8f, 0.8f, 0, -1, 0, 0);
}

thisCall2Args2 sub_FA7AF0 = (thisCall2Args2)0xFA7AF0;
int __fastcall hookSub_FA7AF0(int* thisP, int edx, int x, int y) {
	return sub_FA7AF0(thisP, 508, y);
}


thisCall2 EquimCompoundWin__init_F8EC20 = (thisCall2)0xF8EC20;
char __fastcall hookEquimCompoundWin__init_F8EC20(int* thisP) {
	int ret = EquimCompoundWin__init_F8EC20(thisP);
	setUiComponentVisable_11BE610((int*)thisP[0x70], 0);
	setUiComponentVisable_11BE610((int*)thisP[0x71], 0);
	setUiComponentVisable_11BE610((int*)thisP[0x72], 0);
	thisP[0x82] = 2;//写死随机
	return ret;
}

thisCall2 VendingMachineNWin__OnOpen_EA2B10 = (thisCall2)0xEA2B10;
int __fastcall hookVendingMachineNWin__OnOpen_EA2B10(int* thisP) {
	int ret = VendingMachineNWin__OnOpen_EA2B10(thisP);
	int *charac = (int *)getCharacInfo_925000(*(int **)0x1A6F718);
	int isPcroom = 0;
	decrypt_11A0DE0(charac + 0xA1, (int)(charac + 0xA3), (int)&isPcroom);
	setUiComponentEnable_11BE350((int*)thisP[0x3A], isPcroom);
	return ret;
}

forceinline void init70_popupWin(GumInterceptor* v) {
	//黑钻机只允许黑钻用户抽奖
	*(DWORD*)0x01813A08 = (int)hookVendingMachineNWin__OnOpen_EA2B10;//x
	

	//装备合成
	writeCallCode((void*)0x00F94026, hookEquimCompoundWin__init_F8EC20);
	*(DWORD*)0x00F918BA = -10000;//x
	*(DWORD*)0x00F9151F = -10000;//x

	//品级调整箱
	*(WORD*)0x0064525A = 0x9090;//x
	*(BYTE*)0x0064501E = 0xEB;//x
	*(DWORD*)0x00644731 = 0x000118E9;//x
	writeNopCode((void*)0x006443CF, 6);
	*(BYTE*)0x00644363 = 0x00;//x
	
	//writeNopCode((void*)0x0064528C, 5);

	//遗忘之水窗口
	*(DWORD*)0x00F1BA0D -= 160;//x
	*(DWORD*)0x00F1BA28 -= 120;//y

	//时装合成窗口0x65位置
	*(DWORD*)0x00F97046 -= 160;//x
	*(DWORD*)0x00F97061 -= 120;//y


	//升级可学习技能提示
	//*(DWORD*)0x0054D992 = 640/2;//x
	//*(DWORD*)0x0054D9B0 = 480/2;//y
	//*(DWORD*)0x0054DCC1 = 640 / 2;//x
	//*(DWORD*)0x0054DCDF = 480 / 2;//y
	*(BYTE*)0x0054D9F8 = 0xEB;//隐藏
	

	//土罐竞速计时ui
	int xPos = 365, yPos = 6;
	*(DWORD*)0x008EB124 = xPos;//x
	*(DWORD*)0x008EB11F = yPos;//y
	*(DWORD*)0x008EB1E3 = xPos + 18;//x
	*(DWORD*)0x008EB20F = yPos + 3;//y
	*(DWORD*)0x008EB263 = xPos + 51;//x
	*(DWORD*)0x008EB28F = yPos + 3;//y
	*(DWORD*)0x008EB2E4 = xPos + 86;//x
	*(DWORD*)0x008EB30F = yPos + 3;//y
	*(DWORD*)0x008EB33E = xPos + 32;//x
	*(DWORD*)0x008EB339 = yPos + 3;//y
	*(DWORD*)0x008EB360 = xPos + 64;//x
	*(DWORD*)0x008EB35B = yPos + 3;//y

	//任务提示窗
	*(DWORD*)0x00FC6185 = 483;//x
	*(DWORD*)0x00FC6180 = 160;//y
	
	//新手教程
	*(WORD*)0x010E8058 = 0x4EEB;//esc 弹窗异常
	*(DWORD*)0x00FF5806 = 640;//新手药剂窗口x
	*(DWORD*)0x00FF5821 = 480;//新手药剂窗口y

	//1v1私聊窗口
	*(DWORD*)0x00FAA3CA = 0x180;
	*(DWORD*)0x00FAA3AF = 0x180;
	//*(DWORD*)0x00FA7C54 -= 160;
	writeCallCode((void*)0x00FA7CB2, hookSub_FA7AF0);//消息提示框位置

	//工会窗口位置
	*(BYTE*)0x00F72B18 = -10;//y
	*(DWORD*)0x00F72B1A = 243;//x

	//装备强化卷
	//*(BYTE*)0x006EE08C = 0xEB;
	//*(BYTE*)0x006EE0EC = 0xEB;
	//*(BYTE*)0x006EE3DC = 0xEB;
	//*(BYTE*)0x006EE43C = 0xEB;
	//*(BYTE*)0x006EE7BE = 0xEB;
	//*(BYTE*)0x006EE91D = 0xEB;

	//仓库切换tag
	*(BYTE*)0x00FD9363 = -25;
	*(BYTE*)0x00FD9358 = -25;

	//sub_FC3AC0 
	*(DWORD*)0x00FC3B77 = 640;
	*(DWORD*)0x00FC3B92 = 480;

	//信息弹窗sub_F438C0
	*(DWORD*)0x00F43917 = 640;
	*(DWORD*)0x00F4391E = 640;
	*(DWORD*)0x00F439AC = 640;
	*(DWORD*)0x00F439B5 = 640;
	*(DWORD*)0x00F43A22 = 480;
	*(DWORD*)0x00F43A49 = 480;
	*(DWORD*)0x00F43A85 = 480;
	*(DWORD*)0x00F43AC1 = 480;
	*(DWORD*)0x00F43A60 = 470;
	*(DWORD*)0x00F43A9C = 470;
	*(DWORD*)0x00F43AD8 = 470;
	//00F43B72

	//信息弹窗sub_F43B80
	*(DWORD*)0x00F43BE2 = 320;
	*(DWORD*)0x00F43C0B = 640;
	*(DWORD*)0x00F43C12 = 640;
	*(DWORD*)0x00F43C22 = 480;
	*(DWORD*)0x00F43C29 = 480;
	//00F43C8D

	itemInfoWinInit();

	//00F6E841
	*(BYTE*)0x00E77723 = 0xBA; *(DWORD*)0x00E77724 = (int)hookPopupWin__OnOpen_Cb;
	*(BYTE*)0x00E7AD25 = 0xB8; *(DWORD*)0x00E7AD26 = (int)hookNavigationPopupWin__OnOpen_Cb;
	//BasePopupWin__setCenterPos_EF63A0
	*(DWORD*)0x00EF63B0 = 480 / 2;
	*(DWORD*)0x00EF63C5 = 640 / 2;

	//任务奖励窗口
	*(DWORD*)0x00FC7753 = 640;
	*(DWORD*)0x00FC776E = 480;
	
	//gum_interceptor_replace_fast(v, (gpointer)0xFC3C70, (gpointer)hookGeneralPopupWin__OnOpen_FC3C70, (gpointer*)&GeneralPopupWin__OnOpen_FC3C70);

	//sub_F8D920 00F8DC25 0x9D新角色进图漫画窗口
	*(DWORD*)0x00F8D96D = 192;//操作按钮x
	*(DWORD*)0x00F8D9F0 = 192;//操作按钮x
	*(DWORD*)0x00F8DA36 = 192;//操作按钮x
	*(DWORD*)0x00F8D952 = 446;//操作按钮y
	*(DWORD*)0x00F8D9AF = 446;//操作按钮y
	*(DWORD*)0x00F8D9DA = 446;//操作按钮y
	*(DWORD*)0x00F8D535 = 480;//操作按钮y
	*(DWORD*)0x00F8D957 = 480;//操作按钮y
	*(DWORD*)0x00F8D9D5 = 480;//操作按钮y
	*(DWORD*)0x00F8DA2B = 480;//操作按钮y
	writeCallCode((LPVOID*)0x00F8DD49, (LPVOID)zoom70Draw);

	//0x35转职窗口
	static int changeClass[] = { 4,4,4,4,4,4,2,4,2,0,0 };
	*(DWORD*)0x00F89C93 = (int)changeClass;
	*(DWORD*)0x00F89353 = (int)changeClass;
	*(DWORD*)0x01A3DFF0 = 3;//屏蔽复仇者转职
	//*(DWORD*)0x00F89287 = (int)&mapZoomRate;//背景放大系数
	//*(DWORD*)0x00F89293 = (int)&mapZoomParam;//重播按钮y
	writeCallCode((LPVOID*)0x00F892F6, (LPVOID)zoom70Draw);//背景
	*(DWORD*)0x00F88A70 -= 160;//推出按钮x
	//*(BYTE*)0x00F88A6E = 413;//推出按钮y

	*(DWORD*)0x00F88B54 = 410;//转职按钮x
	*(DWORD*)0x00F88B4F = 355;//转职按钮y

	*(DWORD*)0x00F89F88 = 320;//职业按钮x
	*(DWORD*)0x00F89FA8 = 413;//职业按钮y
	*(DWORD*)0x00F893F5 = 413;//职业按钮y
	*(DWORD*)0x00F893F0 = 405;//职业按钮y
	*(DWORD*)0x00F8945E = 405;//职业按钮y
	*(DWORD*)0x00F894E9 = 405;//职业按钮y
	*(DWORD*)0x00F894E4 = 413;//职业按钮y
	*(DWORD*)0x00F894C4 = 413;//职业按钮y
	*(BYTE*)0x00F895B4 = -80;//职业按钮背景x
	*(DWORD*)0x00F895AF = 400;//职业按钮背景y

	writeCallCode((LPVOID*)0x00F893D1, (LPVOID)zoom70Draw);//职业贴图
	*(DWORD*)0x00F89574 = 265;//标题x
	//*(BYTE*)0x00F89572 = 413;//标题y
	*(DWORD*)0x00F896AF = 310;//职业说明x
	*(BYTE*)0x00F896AD = 30;//职业说明y
	*(DWORD*)0x00F895F0 = *(DWORD*)0x00F896AF + 40;//视频背景x
	*(DWORD*)0x00F895EB = *(BYTE*)0x00F896AD + 112;//视频背景y
	*(DWORD*)0x00F89620 = *(DWORD*)0x00F895F0 + 15;//视频x
	*(DWORD*)0x00F8961B = *(DWORD*)0x00F895EB + 11;//视频y
	*(DWORD*)0x00F88AE2 = *(DWORD*)0x00F895F0 + 103;//重播按钮x
	*(DWORD*)0x00F88ADD = *(DWORD*)0x00F895EB + 37;//重播按钮y
	writeCallCode((LPVOID*)0x00F896B3, (LPVOID)zoom70Draw);//职业说明贴图
}

thisCall4Args2 BaseWin__drawTagLine_EF6520 = (thisCall4Args2)0xEF6520;
thisCall2 CashShop__drawCharacShow_409930 = (thisCall2)0x409930;
void __fastcall CashShop__fixDrawTagLine(int* thisP) {
	CashShop__drawCharacShow_409930(thisP);
	if (thisP[0x11D])return;
	//装扮页
	drawTagLine((int*)thisP[3], 85, 73, 71);
	
}

#define UserGridBannerPosY 35
#define CharacX 475 //525
#define CharacY 200 //291
//thisCall2 CashShop__init_429AA0 = (thisCall2)0x429AA0;
void __fastcall hookCashShop__init_429AA0(int* thisP) {

	int GridBaseX = 60; //45 121
	int GridBaseY = 85;
	int GridPitch = 34;
	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(32);
	hook->resize(12);
	auto b = hook->begin();
	b++->setValue(H_DWORD, 0x004113F6, CharacX - 59);
	b++->setValue(H_DWORD, 0x004113F1, CharacY - 71);
	b++->setValue(H_DWORD, 0x0041140D, CharacX + 39);
	b++->setValue(H_DWORD, 0x00411408, CharacY - 71);
	b++->setValue(H_DWORD, 0x004114C5, CharacX - 11);
	b++->setValue(H_DWORD, 0x004114C0, CharacY + 23);
	b++->setValue(H_DWORD, 0x00411762, CharacX + GridBaseX);
	b++->setValue(H_DWORD, 0x0041175D, CharacX + GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x00411767, CharacX + GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x00411758, CharacY - GridBaseY);
	b++->setValue(H_DWORD, 0x0041176C, CharacY - GridBaseY + GridPitch);
	b++->setValue(H_DWORD, 0x0041177A, CharacY - GridBaseY + GridPitch * 2);
	thisCall2 my_411110 = (thisCall2)tools_relocation_hook(0x411110, 0x00411849, hook);

	// init sub_411110 00411849
	//*(DWORD*)0x004113F6 = CharacX - 59;//修改动作左按钮x
	//*(DWORD*)0x004113F1 = CharacY - 71;//修改动作左按钮y
	//*(DWORD*)0x0041140D = CharacX + 39;//修改动作右按钮x
	//*(DWORD*)0x00411408 = CharacY - 71;//修改动作右按钮y
	//*(DWORD*)0x004114C5 = CharacX - 11;//恢复原来时装按钮x
	//*(DWORD*)0x004114C0 = CharacY + 23;//恢复原来时装按钮y
	//*(DWORD*)0x00411762 = CharacX + GridBaseX;//时装格子x1 646 //右上角时装格子 
	//*(DWORD*)0x0041175D = CharacX + GridBaseX + GridPitch;//时装格子x2 680
	//*(DWORD*)0x00411767 = CharacX + GridBaseX + GridPitch * 2;//时装格子x3 714
	//*(DWORD*)0x00411758 = CharacY - GridBaseY;//时装格子y1 167
	//*(DWORD*)0x0041176C = CharacY - GridBaseY + GridPitch;//时装格子y2 200
	//*(DWORD*)0x0041177A = CharacY - GridBaseY + GridPitch * 2;//时装格子y3 234

	hook->resize(24);
	b = hook->begin();
	GridBaseX = 420;
	GridBaseY = 100;
	GridPitch = 30;
	b++->setValue(H_DWORD, 0x0040D222, GridBaseX);
	b++->setValue(H_DWORD, 0x0040D258, GridBaseX);
	b++->setValue(H_DWORD, 0x0040D28E, GridBaseX);
	b++->setValue(H_DWORD, 0x0040D2C4, GridBaseX);
	b++->setValue(H_DWORD, 0x0040D2F1, GridBaseX);
	b++->setValue(H_DWORD, 0x0040D22C, GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x0040D262, GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x0040D298, GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x0040D2CE, GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x0040D2FB, GridBaseX + GridPitch);
	b++->setValue(H_DWORD, 0x0040D236, GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D26C, GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D2A2, GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D2D8, GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D305, GridBaseX + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D1E1, GridBaseX + GridPitch * 3);
	b++->setValue(H_DWORD, 0x0040D1E6, GridBaseX + GridPitch * 4);
	b++->setValue(H_DWORD, 0x0040D1EB, GridBaseX + GridPitch * 5);
	b++->setValue(H_DWORD, 0x0040D1F2, GridBaseX + GridPitch * 6);
	b++->setValue(H_DWORD, 0x0040D14F, GridBaseY);
	b++->setValue(H_DWORD, 0x0040D17E, GridBaseY + GridPitch);
	b++->setValue(H_DWORD, 0x0040D1AD, GridBaseY + GridPitch * 2);
	b++->setValue(H_DWORD, 0x0040D1DC, GridBaseY + GridPitch * 3);
	b++->setValue(H_DWORD, 0x0040D218, GridBaseY + GridPitch * 4);
	thisCall2 my_40D120 = (thisCall2)tools_relocation_hook(0x40D120, 0x0040D556, hook);

	//右上角预购栏格子 sub_40D120 init
	//GridBaseX = 420;
	//GridBaseY = 100;
	//GridPitch = 30;
	//*(DWORD*)0x0040D222 = GridBaseX;                  //格子x1 493
	//*(DWORD*)0x0040D258 = GridBaseX;                  //格子x1 493
	//*(DWORD*)0x0040D28E = GridBaseX;                  //格子x1 493
	//*(DWORD*)0x0040D2C4 = GridBaseX;                  //格子x1 493
	//*(DWORD*)0x0040D2F1 = GridBaseX;                  //格子x1 493
	//*(DWORD*)0x0040D22C = GridBaseX + GridPitch;      //格子x2 523
	//*(DWORD*)0x0040D262 = GridBaseX + GridPitch;      //格子x2 523
	//*(DWORD*)0x0040D298 = GridBaseX + GridPitch;      //格子x2 523
	//*(DWORD*)0x0040D2CE = GridBaseX + GridPitch;      //格子x2 523
	//*(DWORD*)0x0040D2FB = GridBaseX + GridPitch;      //格子x2 523
	//*(DWORD*)0x0040D236 = GridBaseX + GridPitch * 2;  //格子x3 553
	//*(DWORD*)0x0040D26C = GridBaseX + GridPitch * 2;  //格子x3 553
	//*(DWORD*)0x0040D2A2 = GridBaseX + GridPitch * 2;  //格子x3 553
	//*(DWORD*)0x0040D2D8 = GridBaseX + GridPitch * 2;  //格子x3 553
	//*(DWORD*)0x0040D305 = GridBaseX + GridPitch * 2;  //格子x3 553
	//*(DWORD*)0x0040D1E1 = GridBaseX + GridPitch * 3;  //格子x4 583
	//*(DWORD*)0x0040D1E6 = GridBaseX + GridPitch * 4;  //格子x5 613
	//*(DWORD*)0x0040D1EB = GridBaseX + GridPitch * 5;  //格子x6 643
	//*(DWORD*)0x0040D1F2 = GridBaseX + GridPitch * 6;  //格子x7 673
	//*(DWORD*)0x0040D14F = GridBaseY;                  //格子y1 131
	//*(DWORD*)0x0040D17E = GridBaseY + GridPitch;      //格子y2 161
	//*(DWORD*)0x0040D1AD = GridBaseY + GridPitch * 2;  //格子y3 191
	//*(DWORD*)0x0040D1DC = GridBaseY + GridPitch * 3;  //格子y4 221
	//*(DWORD*)0x0040D218 = GridBaseY + GridPitch * 4;  //格子y5 251


	hook->resize(2);
	b = hook->begin();
	b++->setValue(H_DWORD, 0x00415243, 426);
	b++->setValue(H_DWORD, 0x00415231, 264 + UserGridBannerPosY);
	thisCall2 my_414DC0 = (thisCall2)tools_relocation_hook(0x414DC0, 0x00416339, hook);
	//init sub_414DC0 00416339
	//*(DWORD*)0x00415243 = 426;  //右下角tagLayout x
	//*(DWORD*)0x00415231 = 264 + UserGridBannerPosY;  //右下角tagLayout y 336
	////*(BYTE*)0x0040BB8A = 2;
	////*(DWORD*)0x0040BB98 = 282;


	b = hook->begin();
	b++->setValue(H_DWORD, 0x00414D19, 612);
	b++->setValue(H_DWORD, 0x00414D14, 292 + UserGridBannerPosY);
	thisCall2 my_414CB0 = (thisCall2)tools_relocation_hook(0x414CB0, 0x00414DB1, hook);
	//init sub_414CB0 00414DB1
	//*(DWORD*)0x00414D19 = 612;  //滑块控件x
	//*(DWORD*)0x00414D14 = 292 + UserGridBannerPosY;  //滑块控件y

	hook->resize(4);
	b = hook->begin();
	b++->setValue(H_CALL, 0x00429D58, (int)my_411110);
	b++->setValue(H_CALL, 0x00429D66, (int)my_40D120);
	b++->setValue(H_CALL, 0x00429D51, (int)my_414DC0);
	b++->setValue(H_CALL, 0x00429D7B, (int)my_414CB0);
	thisCall2 CashShop__init_429AA0 = (thisCall2)tools_relocation_hook(0x429AA0, 0x0042ACC3, hook);
	CashShop__init_429AA0(thisP);
	tools_release_func_memory((int)CashShop__init_429AA0);
	//writeCallCode((LPVOID*)0x00429D51,(LPVOID)my_414DC0);
	//writeCallCode((LPVOID*)0x00429D58,(LPVOID)my_411110);
	//writeCallCode((LPVOID*)0x00429D66,(LPVOID)my_40D120);
	//writeCallCode((LPVOID*)0x00429D7B,(LPVOID)my_414CB0);
	//thisCall2 CashShop__init_429AA0 = (thisCall2)0x429AA0;
	//CashShop__init_429AA0(thisP);

	tools_release_func_memory((int)my_414CB0);
	tools_release_func_memory((int)my_414DC0);
	tools_release_func_memory((int)my_40D120);
	tools_release_func_memory((int)my_411110);
	delete hook;
	//礼包右上角预购栏格子
	int pos = 31;
	int baseX = 540;
	int baseY = 100;
	setUiComponentPos_11BEAD0((int*)thisP[0xAB], baseX - 3, baseY - 36, 1);
	setUiComponentPos_11BEAD0((int*)thisP[0xAC], baseX + pos, baseY - pos, 1);
	setUiComponentPos_11BEAD0((int*)thisP[0xAD], baseX + 2 * pos, baseY - pos, 1);
	int x[3] = { baseX , baseX + pos, baseX + 2 * pos };
	int y[6] = { baseY , baseY + pos, baseY + 2 * pos, baseY + 3 * pos, baseY + 4 * pos, baseY + 5 * pos };
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 3; ++j) {
			setUiComponentPos_11BEAD0((int*)thisP[0xAE + i * 3 + j], x[j], y[i], 1);
		}
	}
	//baseX -= 15;
	//int x2[3] = { baseX - 3 * pos, baseX - 2 * pos, baseX - 1 * pos };
	//int y2 = baseY + 3 * pos;
	//for (int j = 0; j < 3; ++j) {
	//    setUiComponentPos_11BEAD0((int*)thisP[0xBD + j], x2[j], y2, 1);
	//}

	//退出按钮
	setUiComponentPos_11BEAD0((int*)thisP[0x4B], 565, 12, 1);
	//加入按钮
	setUiComponentPos_11BEAD0((int*)thisP[0xCB], 431, 256, 1);

	//全部购买按钮
	setUiComponentPos_11BEAD0((int*)thisP[0xC7], 424, 425, 1);

	//全部赠送按钮
	setUiComponentPos_11BEAD0((int*)thisP[0xC9], 540, 424, 1);

	//充值点券按钮
	setUiComponentPos_11BEAD0((int*)thisP[0xC3], 540, 451, 1);

	//刷新点券按钮
	setUiComponentPos_11BEAD0((int*)thisP[0xC5], 230, 450, 1);


	//右下角物品栏 屏蔽消耗品和材料项
	int* obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xDE], 1);
	setUiComponentVisable_11BE610(obj, 0);
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xDE], 2);
	setUiComponentVisable_11BE610(obj, 0);
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xDE], 3);
	setUiComponentPos_11BEAD0(obj, 426 + obj[0xE], 264 + UserGridBannerPosY, 1);
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xDE], 4);
	setUiComponentPos_11BEAD0(obj, 426 + obj[0xE] * 2, 264 + UserGridBannerPosY, 1);

	//隐藏轮盘 时装代笔 标签
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xD6], 0);
	setUiComponentPos_11BEAD0(obj, -10000, -10000, 1);
	//setUiComponentVisable_11BE610(obj, 0);
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xD6], 1);
	//setUiComponentPos_11BEAD0(obj, 17, 55, 1);
	setUiComponentPos_11BEAD0(obj, -10000, -10000, 1);
	obj = (int*)TagLayout__getTagItemObjByIdx_11C0830((int*)thisP[0xD6], 2);
	//setUiComponentPos_11BEAD0(obj, 17 + obj[0xE], 55, 1);
	setUiComponentPos_11BEAD0(obj, 17, 55, 1);
	TagLayout__setCurrentTag_11C19C0((int*)thisP[0xD6], 2);


	//右下角物品栏格子
	pos = 30;
	baseX = 430;
	baseY = 291 + UserGridBannerPosY;//363
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 6; ++j) {
			setUiComponentPos_11BEAD0((int*)thisP[0x67 + i * 6 + j], baseX + j * pos, baseY + i * pos, 1);
		}
	}
	for (int i = 18; i < 33; ++i) {
		setUiComponentPos_11BEAD0((int*)thisP[0x67 + i], -10000, -10000, 1);
		setUiComponentVisable_11BE610((int*)thisP[0x67 + i], 0);
	}

}

Naked void FixSingleFashion(void) {
	__asm {
		cmp ebx, 1
		jz goFix
		mov ecx, dword ptr ds : [esi + 0x3A0]
		mov eax, 0x11C6130
		call eax
		mov ecx, dword ptr ss : [ebp - 4]
		lea ecx, dword ptr ds : [ecx + ecx * 4]
		lea edx, dword ptr ds : [eax + ecx * 2]
		imul edx, edx, 64
		mov ecx, dword ptr ds : [edx + esi + 0xA19C]
		sub ecx, dword ptr ds : [edx + esi + 0xA198]
		push 0x4211EE
		ret
		goFix :
		push 0x4211E2
		ret
	}
}

Naked void FixSingleFashion2(void) {
	__asm {
		mov ecx, dword ptr ds : [esi + 0x3A0]
		mov eax, 0x11C6130
		call eax
		mov ecx, dword ptr ss : [ebp - 4]
		lea ecx, dword ptr ds : [ecx + ecx * 4]
		lea edx, dword ptr ds : [eax + ecx * 2]
		imul edx, edx, 64
		mov ecx, dword ptr ds : [edx + esi + 0xA19C]
		sub ecx, dword ptr ds : [edx + esi + 0xA198]
		push 0x4211EE
		ret
	}
}

Naked void FixSingleFashion_HZ(void) {
	__asm {
		mov  ecx, dword ptr[esi + 0x3a0]
		mov  eax, 0x11c6130
		call eax
		mov  ecx, dword ptr[ebp - 4]
		lea  ecx, [ecx + ecx * 4]
		lea  edx, [eax + ecx * 2]
		imul edx, edx, 0x64
		mov  ecx, dword ptr[edx + esi + 0xa19c]
		sub  ecx, dword ptr[edx + esi + 0xa198]
		push 0x4211ee
		ret
		/*rol  byte ptr[ebx + 0x6a04c4], 1
		push eax
		push 0x1ae4670
		push ecx
		mov  edx, dword ptr[ebx]
		push edx
		mov  ecx, esi
		mov  eax, 0xf542f0
		call eax
		mov  ecx, dword ptr[0x1ae4678]
		inc  dword ptr[ebx]
		mov  eax, 0xf53b73
		jmp  eax*/
	}
}

Naked void FixFashionTagBottomLine(void) {
	__asm {
		mov ecx, [esi + 0x1C]
		push 5
		call getImageByPos_11B4BD0
		push eax
		push 73
		push 15
		mov ecx, dword ptr ds : 0x1B5582C
		call drawImgByXY_11B3950
		pop edi
		pop esi
		pop ebx
		retn
	}
}

forceinline void cashShop(GumInterceptor* v) {
	writeCallCode((LPVOID*)0x00E823E8, (LPVOID)hookCashShop__init_429AA0);
	writeCallCode((LPVOID*)0x00429606, (LPVOID)CashShop__fixDrawTagLine);
	
	//人物时装展示
//#define CharacX 475 //525
//#define CharacY 200 //291
	int GridBaseX = 60; //45 121
	int GridBaseY = 85;
	int GridPitch = 34;

	//ProcDraw -> CashShop::drawCharacShow_409930 00409A7C
	*(DWORD*)0x00409A6B = CharacX;//人物x
	*(DWORD*)0x00409A66 = CharacY;//人物y
	*(DWORD*)0x004099E7 = CharacX - 53;//魔法阵x
	*(DWORD*)0x004099E2 = CharacY - 13;//魔法阵y
	*(DWORD*)0x00409A43 = CharacX - 54;//魔法阵光效x
	*(DWORD*)0x00409A3E = CharacY - 88;//魔法阵光效y
	*(DWORD*)0x0040998A = *(DWORD*)0x00411762 - GridPitch;//格子背景x
	*(DWORD*)0x00409985 = *(DWORD*)0x00411758 - 3;//格子背景y

	//ProcDraw -> CashShop::drawUserItemBanner_40B9F0
	*(BYTE*)0x0040BA60 = 18;
	*(BYTE*)0x0040BA98 = 18;
	*(BYTE*)0x0040BAD0 = 18;
	*(BYTE*)0x0040BB48 = 18;
	//*(DWORD*)0x0040BB9D = 419;  //tag底线x
	*(DWORD*)0x0040BB98 = 282 + UserGridBannerPosY;  //tag底线y

	//ProcDraw -> CashShop::drawUserData_410130 00410415
	*(DWORD*)0x004101B7 = 290;  //时装代币x
	*(DWORD*)0x004101B2 = 450;  //时装代币y
	*(DWORD*)0x00410224 = 25;  //代币券x
	*(DWORD*)0x0041021F = 450;  //代币券y
	*(DWORD*)0x00410311 = 152;  //点券x
	*(DWORD*)0x0041030C = 450;  //点券y
	*(DWORD*)0x004103E0 = 245;  //复活币x
	*(DWORD*)0x004103DB = 450;  //复活币y

	//CashShop::ProcDraw_429590
	*(DWORD*)0x004295DE = CharacX;//人物x
	*(DWORD*)0x004295D9 = CharacY;//人物y


	//Proc -> sub_40ED50 0040F136
	*(BYTE*)0x0040EE41 = 6;
	*(BYTE*)0x0040EE6F = 18;
	*(BYTE*)0x0040EE95 = 6;
	*(BYTE*)0x0040EEC4 = 18;
	*(BYTE*)0x0040EDF3 = -6;
	*(BYTE*)0x0040EE1B = 18;
	*(BYTE*)0x0040EF68 = 6;
	*(BYTE*)0x0040EF80 = 18;

	//右下角格子按 6 * 3 显示
	//CashShop::Proc_4285E0 004294E6
	*(BYTE*)0x004287A0 = 18;
	*(BYTE*)0x004287A9 = -18;
	*(DWORD*)0x004287AB = 0x55555556;//除6
	*(BYTE*)0x004287BC = 18;
	*(BYTE*)0x004287C1 = -18;
	*(BYTE*)0x004287C4 = 6;
	*(BYTE*)0x004286EB = 18;

	int* p = (int*)0x01564C58;
	int startX = 430;
	int startY = 291 + UserGridBannerPosY;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 6; ++j) {
			p[0] = startX + j * 30;
			p[1] = startY + i * 30;
			p += 2;
		}
	}
	for (int i = 18; i < 33; ++i) {
		p[1] = -10000;
		p += 2;
	}


	//sub_420BE0 00421323 商品页展示数12->8
	*(DWORD*)0x00421150 = 8 * 16;//proc
	//*(DWORD*)0x0041892D = 8 * 16;//draw
	//*(BYTE*)0x004209D2 = 8;//鼠标触发信息窗
	*(BYTE*)0x00420C37 = 0x00; *(DWORD*)0x00420C3B = -8;//商品按8个分页
	*(DWORD*)0x004212FE = 0x40000000;//翻页数

	//翻页数
	*(DWORD*)0x0040CC8A = 0x40000000;//sub_40CB80
	*(DWORD*)0x0040D81B = 0x40000000;//sub_40D7A0
	*(DWORD*)0x0040D905 = 0x40000000;//sub_40D8A0
	*(DWORD*)0x0040D9FA = 0x40000000;//sub_40D990
	*(DWORD*)0x0041D7EF = 0x40000000;//sub_41D4F0
	*(DWORD*)0x0041DAC6 = 0x40000000;//sub_41D9E0
	*(DWORD*)0x00422A35 = 0x40000000;//sub_4229C0
	*(DWORD*)0x00422B85 = 0x40000000;//sub_422B30
	*(DWORD*)0x00422C15 = 0x40000000;//sub_422BC0
	*(DWORD*)0x00422CB5 = 0x40000000;//sub_422C60

	//sub_424390 00424867
	*(DWORD*)0x00424527 = 0x40000000;
	*(DWORD*)0x004245DE = 0x40000000;
	*(DWORD*)0x004246BB = 0x40000000;
	*(DWORD*)0x00424825 = 0x40000000;
	*(DWORD*)0x0042474B = 0x40000000;

	//sub_41AE70 0041AF8D 购物车最大18个
	*(BYTE*)0x0041AEB4 = 17;
	*(BYTE*)0x0041AEDA = 18;
}



thisCall1Args2 PvfDungeonObj__Constructor_E44250 = (thisCall1Args2)0xE44250;
int __fastcall hookPvfDungeonObj__Constructor_E44250(int* thisP, int, int dungeonId) {
	int ret = PvfDungeonObj__Constructor_E44250(thisP, dungeonId);
	if (ret) {//[background pos]
		if (dungeonId == 61) WDWORD(ret, 0x160 * 4, -40);
		if (dungeonId == 41) WDWORD(ret, 0x160 * 4, -22);
		else WDWORD(ret, 0x160 * 4, -30);
	}
	return ret;
}

thisCall2Args2 DungeonMap__Constructor_7E8080 = (thisCall2Args2)0x7E8080;
int __fastcall hookDungeonMap__Constructor_7E8080(int* thisP, int, int mapId, int type) {
	//printf("DungeonMap:%d %d\n", mapId, type);
	int ret = DungeonMap__Constructor_7E8080(thisP, mapId, type);
	if (ret) {
		if (mapId == 9100) {
			thisP[0x1B2] = 160 * 0.8f + 50;
			thisP[0x1B3] = 240 * 0.8f + 50;
		}
		else if((mapId > 9100 && mapId <= 9108) || mapId == 60029) {
			thisP[0x1B2] = 160 * 0.8f + 10;
			thisP[0x1B3] = 240 * 0.8f + 10;
		}
		else if (mapId >= 5801 && mapId <= 5803) {
			thisP[0x1B2] = 160 * 0.8f + 50;
			thisP[0x1B3] = 240 * 0.8f + 50;
		}
		//else if ((mapId >= 30001 && mapId <= 30045) || (mapId >= 31001 && mapId <= 31025)) {
		//	thisP[0x1B2] = 160 * 0.8f + 100;
		//	thisP[0x1B3] = 240 * 0.8f + 100;
		//}
	}
	return ret;
}

thisCall2Args2 TownMap__Constructor_10EF1F0 = (thisCall2Args2)0x10EF1F0;
int __fastcall hookTownMap__Constructor_10EF1F0(int* thisP, int, int mapPath, int type) {
	int ret = TownMap__Constructor_10EF1F0(thisP, mapPath, type);
	//wprintf(L"TownMap:%s %d %d\n", (wchar_t*)mapPath, type, thisP[0x158]);
	wchar_t map[64];
	wcscpy(map, (wchar_t *)mapPath);
	for (int i = 0; i < wcslen(map); ++i) {
		map[i] = towlower(map[i]);
	}
	if (ret){
		if (wcsstr(map, L"pvp")) {
			thisP[0x158] = -35;//[background pos]
		}else if(!wcscmp(map, L"alfhlyra/alfhlyra.map")
		|| !wcscmp(map, L"hendonmyre/westcoast.map")
		|| !wcscmp(map, L"hendonmyre/hendon.map")
		//|| !wcscmp(map, L"stormpass/stormpass.map")
			) {
				thisP[0x1B2] = 208;
				thisP[0x1B3] = 252;
		}
	}
	return ret;
}


static UINT32 YPosBk = 0;
int __fastcall hookCNRDStage_proc_8F10A0(int* thisp, int) {
	//int cmodule = CGameModule;
	//if(cmodule == 4 || cmodule == 5) return CNRDStage_proc_8F10A0(thisp);
	int* mapObj = (int*)thisp[0x13];
	if (YPosBk) mapObj[0x18F] = YPosBk;
	int ret = CNRDStage_proc_8F10A0(thisp);
	YPosBk = 0;
	if (thisp[0x137]) return ret;
	int* mapInfoObj = (int*)thisp[0x15];
	if (mapObj && mapInfoObj) {
		int maxW = getMapMaxWight_7D74C0(mapObj);
		int maxH = getMapMaxHeight_7D7510(mapObj);
		//int x = getCameraPosX_7D6990(mapObj, 0, 1);
	   /* int y = getCameraPosY_7D69F0(mapObj, 0, 1);*/
		int x = 0, y = 0, z = 0;
		thisCall3Args getInfo = (thisCall3Args)Vtable(mapInfoObj, 0x124);
		getInfo(mapInfoObj, 0, (int)&x, (int)&y, (int)&z);
		if (z > 0) {
			z = z / 4;
			int y = mapObj[0x18F];// getCameraCoordY_7D69F0(mapObj, 1);
			int mapId = mapObj[0x92];
			if (!maxH && z > 30) z = 30;
			else if (maxH) {
				x = y / 4;
				if (mapId == 9105 || mapId == 9107) {
					if (x < 24) x = 16;
				}
	/*			else if (mapId >= 5801 && mapId <= 5803) {
					if (x < 24) x = 16;
				}*/
				else if (x < 30) x = 30;
				if (z > x) z = x;
			}
			//printf("%d[%d, %d, %d]\n", mapObj[0x92], maxH, z, y);
			if (y >= 0) {
				YPosBk = y;
				mapObj[0x18F] -= z;
			}
			else {
				YPosBk = 0;
				mapObj[0x18F] = -z;
			}
		}
		//printf("[%d, %d][%d, %d, %d]\n", y, maxH , a1, a2, a3);
		//printf("[%d, %d, %d][%d, %d, %d]\n", y, mapObj[0x18F], maxH , a1, a2, a3);
		//printf("[%d, %d][%d, %d][%d, %d, %d]\n", x, y, maxW, maxH, a1, a2, a3);
	}
	return ret;
}

thisCall3Args2 CNModule__changeMap_7E8510;
int __fastcall hookCNModule__changeMap_7E8510(int* thisP, int, int a2, int a3, int a4) {
	int ret = CNModule__changeMap_7E8510(thisP, a2, a3, a4); 
	YPosBk = 0;
	return ret;
}

void Naked FixDungeonCameraPosition(void) {
	//007E8D6E
	__asm {
		sar  edx, 2
		cmp  edi, edx
		jae  exitError
		test esi, esi
		jz goOut
		mov dword ptr[esi + 0x63c], 0
		//mov YPosBk, 0
		push eax
		push ecx
		call goldSkill_AddLevel
		pop ecx
		pop eax
		goOut:
		mov dword ptr[eax + edi * 4], esi
		mov ecx, 0x007E8D7D
		jmp ecx
		exitError :
		mov ecx, 0x007E8D75
		jmp ecx
	}
}

cdeclCall2 mySub_768750;
char __cdecl hookSub_768750(int a1, char a2) {
	return mySub_768750(a1, a2);
}

void __fastcall myChatWin__drawBg_4A1380(int* thisP) {
	RECT rect;
	int ret = GetClientRect((HWND)(thisP[2]), &rect);
	if (!ret) return;
	int *img = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"Interface/newstyle/windows/Chatting/chatting_ver4.img");
	int v = getImageByPos_11B4BD0(img, 114);
	drawImgByXY_11B3950(*(int**)0x1B5582C, 0, 0, v);
}

thisCall2 getWinWidth_11D84B0 = (thisCall2)0x11D84B0;
int __fastcall hookGetWinWidth_11D84B0(int* thisP) {
	int ret = getWinWidth_11D84B0(thisP);
	if (ret == 800) return 640;
	return ret;
}

thisCall2 getWinHeight_11D84E0 = (thisCall2)0x11D84E0;
int __fastcall hookGetWinHeight_11D84E0(int* thisP) {
	int ret = getWinHeight_11D84E0(thisP);
	if (ret == 600) return 480;
	return ret;
}
//[map loading image path]
thisCall2 sub_118E0C0 = (thisCall2)0x118E0C0;
thisCall2 sub_13D71D8 = (thisCall2)0x13D71D8;
void Naked fixMapLoadingImage(void) {

	//0075EC6B
	__asm {
		lea		ecx, dword ptr[ebp - 0x49C]
		call	sub_118E0C0
		mov     eax, 1
		mov     ecx, dword ptr[ebp - 0x0C]
		mov     dword ptr fs : [0] , ecx
		pop     ecx
		pop     edi
		pop     esi
		pop     ebx
		mov     ecx, dword ptr[ebp - 0x10]
		xor		ecx, ebp
		call    sub_13D71D8
		mov     esp, ebp
		pop     ebp
		retn
	}
}


int showDropGold(int) {
	return (int)L"G";
}
void init70(void) {
	writeCallCode((void*)0x004CD640, showDropGold);

	//塔过场动画
	*(BYTE*)0x006FDF38 = 0x00;
	*(BYTE*)0x006FDF3A = 0x00;
	*(BYTE*)0x006FDF53 = 0x00;
	*(BYTE*)0x006FDF55 = 0x00;
	//*(BYTE*)0x007E88CF = 0xe9; *(DWORD*)0x007E88D0 = 0x00000145;
	writeJmpCode((void*)0x0075EC6B, fixMapLoadingImage);

	//BYTE cmdFix[] = { 0x8D, 0x8D, 0x64, 0xFB, 0xFF, 0xFF, 0xE8, 0xE5, 0xDF, 0xA2, 0x00, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xF4, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x59, 0x5F, 0x5E, 0x5B, 0x8B, 0x4D, 0xF0, 0x31, 0xE9, 0xE8, 0xE0, 0x70, 0xC7, 0x00, 0x89, 0xEC, 0x5D, 0xC3 };
	//writeCodeArray((void*)0x007600D0, cmdFix, 44);
	//BYTE cmdFix[] = { 0x85, 0xFF, 0x0F, 0x85, 0x07, 0x01, 0x00, 0x00, 0x68, 0x08, 0x40, 0x00, 0x00, 0xE8, 0x4D, 0x6B, 0xC7, 0x00, 0x89, 0xC6, 0x68, 0x00, 0x40, 0x00, 0x00, 0x8D, 0x7E, 0x04, 0x6A, 0x00, 0x83, 0xCB, 0xFF, 0x57, 0x89, 0x1E, 0xE8, 0xBC, 0x6A, 0xC7, 0x00, 0x83, 0xC4, 0x10, 0x89, 0x9E, 0x04, 0x40, 0x00, 0x00, 0x8B, 0x0D, 0x7C, 0xB3, 0xAF, 0x01, 0x56, 0x68, 0x08, 0x40, 0x00, 0x00, 0x81, 0xC1, 0x38, 0xD2, 0x20, 0x00, 0xE8, 0xDC, 0xAC, 0xFF, 0xFF, 0x81, 0x3E, 0x5B, 0x02, 0x00, 0x00, 0x74, 0x18, 0x8D, 0x8D, 0x64, 0xFB, 0xFF, 0xFF, 0x89, 0x5D, 0xFC, 0xE8, 0xA6, 0xE0, 0xA2, 0x00, 0xB8, 0x00, 0x00, 0x00, 0x80, 0xE9, 0xBC, 0x00, 0x00, 0x00, 0x0F, 0xB7, 0x0E, 0x51, 0x8B, 0x0D, 0x7C, 0xB3, 0xAF, 0x01, 0xE8, 0xFD, 0x28, 0x9D, 0x00, 0x8B, 0x96, 0x04, 0x40, 0x00, 0x00, 0x8B, 0x0D, 0x7C, 0xB3, 0xAF, 0x01, 0x52, 0x57, 0xE8, 0x6A, 0x31, 0x9D, 0x00, 0xE8, 0x45, 0x2A, 0x9D, 0x00, 0x56, 0xE8, 0xD6, 0x5A, 0xC7, 0x00, 0xA1, 0xB4, 0xD0, 0xAF, 0x01, 0x83, 0xC4, 0x04, 0x80, 0x78, 0x41, 0x01, 0x75, 0x6E, 0xFF, 0x15, 0x88, 0xA5, 0x55, 0x01, 0x8B, 0x0D, 0xB4, 0xD0, 0xAF, 0x01, 0x68, 0x50, 0x07, 0x5B, 0x01, 0x89, 0x41, 0x34, 0xE8, 0x78, 0xFE, 0xA3, 0x00, 0x8B, 0x15, 0xB4, 0xD0, 0xAF, 0x01, 0x8B, 0x42, 0x34, 0x83, 0xC4, 0x04, 0x50, 0x68, 0x50, 0x07, 0x5B, 0x01, 0xE8, 0x61, 0xFE, 0xA3, 0x00, 0x83, 0xC4, 0x04, 0x50, 0x68, 0xE7, 0x07, 0x00, 0x00, 0x68, 0xBC, 0x0C, 0x5B, 0x01, 0xE8, 0x4E, 0xFE, 0xA3, 0x00, 0x83, 0xC4, 0x04, 0x50, 0x68, 0x90, 0xD3, 0x5A, 0x01, 0xE8, 0x40, 0xFE, 0xA3, 0x00, 0x83, 0xC4, 0x04, 0x50, 0x6A, 0x00, 0xE8, 0xD5, 0x74, 0xA9, 0x00, 0x8B, 0x0D, 0xB4, 0xD0, 0xAF, 0x01, 0x83, 0xC4, 0x18, 0xC6, 0x41, 0x41, 0x00, 0xEB, 0x03, 0x83, 0xCB, 0xFF, 0x89, 0x5D, 0xFC, 0x8D, 0x8D, 0x64, 0xFB, 0xFF, 0xFF, 0xE8, 0xE5, 0xDF, 0xA2, 0x00, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xF4, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x59, 0x5F, 0x5E, 0x5B, 0x8B, 0x4D, 0xF0, 0x31, 0xE9, 0xE8, 0xE0, 0x70, 0xC7, 0x00, 0x89, 0xEC, 0x5D, 0xC3 };
	//writeCodeArray((void*)0x0075FFBB, cmdFix, 321);

	*(DWORD*)0x00C01984 = 0x00009CE9;//不显示属性子弹个数图标
	*(DWORD*)0x01062B00 = 640;//觉醒动画
	*(DWORD*)0x01062B35 = 640;//觉醒动画
	*(DWORD*)0x0084D1DF = 378;//技能计数icon
	*(DWORD*)0x00AD3D47 = 560;//尼尔狙击子弹x
	*(DWORD*)0x00AD3D42 = 240;//尼尔狙击子弹y

	//右下角loading
	*(DWORD*)0x01112602 = 458;//x
	*(DWORD*)0x011125FD = 390;//y
	*(DWORD*)0x006FDF6C = 458;//x
	*(DWORD*)0x006FDF67 = 390;//y

	//右上角schedule提示窗口
	
	*(BYTE*)0x0045D610 -= 17;//y
	*(BYTE*)0x0045D662 -= 17;//y
	*(DWORD*)0x004C603B -= 17;//y
	*(DWORD*)0x004C609B -= 17;//y
	*(DWORD*)0x0045D725 -= 17;//y
	*(DWORD*)0x004C60A2 -= 17;//y
	*(DWORD*)0x0045D612 = 457;
	*(DWORD*)0x0045D646 = 457;
	*(DWORD*)0x0045D664 = 457;
	*(DWORD*)0x0045D787 = 457;
	*(DWORD*)0x0045D814 = 457;
	*(DWORD*)0x004C6040 -= 160;
	*(DWORD*)0x004C60C0 -= 160;

	//title动画
	*(DWORD*)0x01112818 = 640 / 2;
	*(DWORD*)0x01112813 = 480 / 2;
	*(DWORD*)0x007E01E1 = 640 / 2;
	*(DWORD*)0x007E01DC = 480 / 2;

	//活动title动画
	*(DWORD*)0x0061B017 = 640 / 2;
	*(DWORD*)0x0061B089 = 640 / 2;
	*(DWORD*)0x0061B177 = 640 / 2;
	*(DWORD*)0x0061B22E = 640 / 2;
	*(DWORD*)0x0061B6AD = 190;

	//*(DWORD*)0x00403B9A = 640 / 2;
	//*(DWORD*)0x00403B95 = 480 / 2;
	//*(DWORD*)0x004BDFBC = 640 / 2;
	//*(DWORD*)0x004BDFB7 = 480 / 2;
	//*(DWORD*)0x004BE266 = 640 / 2;
	//*(DWORD*)0x004BE261 = 480 / 2;
	//*(DWORD*)0x00647489 = 640 / 2;
	//*(DWORD*)0x00647484 = 480 / 2;
	//*(DWORD*)0x007DF7D9 = 640 / 2;
	//*(DWORD*)0x007DF7D4 = 480 / 2;
	//*(DWORD*)0x007DF84E = 640 / 2;
	//*(DWORD*)0x007DF849 = 480 / 2;
	//*(DWORD*)0x00E41A38 = 640 / 2;
	//*(DWORD*)0x00E41A33 = 480 / 2;
	//*(DWORD*)0x00E71B14 = 640 / 2;
	//*(DWORD*)0x00E71B0F = 480 / 2;
	//*(DWORD*)0x00E71BC6 = 640 / 2;
	//*(DWORD*)0x00E71BC1 = 480 / 2;
	//游戏分辨率还原640*480
	*(DWORD*)0x007DBABE = 350 * 0.8f;
	*(DWORD*)0x007DBAC8 = 450 * 0.8f;
	*(DWORD*)0x007DBAD2 = 160 * 0.8f + 30;
	*(DWORD*)0x007DBADC = 240 * 0.8f + 30;
	*(DWORD*)0x007D74F7 = 640;

	GumInterceptor* v = gum_interceptor_obtain();
#define Debug 1
#if Debug
	*(DWORD*)0x008B4BD4 = Width;
	*(DWORD*)0x008B4BB4 = Height;
	*(DWORD*)0x008B4C4E = Width;
	*(DWORD*)0x008B4C64 = Height;
	*(DWORD*)0x008B4E0C = Width;
	*(DWORD*)0x008B4E1D = Height;
	*(DWORD*)0x00436F47 = Width;
	*(DWORD*)0x00436F2B = Height;
	*(DWORD*)0x00436FD9 = Width;
	*(DWORD*)0x00436FF0 = Height;
	*(DWORD*)0x00432CC7 = Width;
	*(DWORD*)0x00432CAB = Height;
	*(DWORD*)0x00432D59 = Width;
	*(DWORD*)0x00432D70 = Height;
	*(DWORD*)0x00F1F5B7 = Width;
	*(DWORD*)0x00F1F59B = Height;
	*(DWORD*)0x00F1F649 = Width;
	*(DWORD*)0x00F1F660 = Height;
	*(DWORD*)0x01032A77 = Width;
	*(DWORD*)0x01032A5B = Height;
	*(DWORD*)0x01032B09 = Width;
	*(DWORD*)0x01032B20 = Height;

	*(DWORD*)0x004A168D = Height;//chatWin H
	writeCallCode((void*)0x004A53A1, myChatWin__drawBg_4A1380);
	*(DWORD*)0x0095CC2D -= 80;//冰心
	*(DWORD*)0x0095CCBD -= 80;//冰心
	//setGameCanvasSize_6FD880
	*(DWORD*)0x006FD89B= Width;
	*(DWORD*)0x006FD8A2= Width;
	*(DWORD*)0x006FD8AA = Height;
	*(DWORD*)0x006FD8B1 = Height;
	//resetGameCanvasSize_6FD8D0
	*(DWORD*)0x006FD8DC = Width;
	*(DWORD*)0x006FD8D7 = Height;

	*(DWORD*)0x1B2960C = 0;
	*(DWORD*)0x011B2B3F = 0;
	*(DWORD*)0x011B2FDA = Width;
	*(DWORD*)0x011B2FE1 = Height;
	*(DWORD*)0x0121120F = Width;//拓展渲染画布
	*(DWORD*)0x0121120A = Height;//拓展渲染画布
	*(DWORD*)0x0011F336D = Width;//拓展渲染宽度
	*(DWORD*)0x0011F3377 = Height;//拓展渲染高度
	*(float*)0x001566D1C = Width;//拓展地图背景渲染宽度
	*(float*)0x001566D20 = Height;//拓展地图背景渲染高度
	*(double*)0x0015A2928 = Width;//拓展鼠标识别宽度
	*(double*)0x0015A2920 = Height;//拓展鼠标识别高度度

	*(DWORD*)0x0040ABC6 = Width/2;//商城赠送窗口居中计算宽度
	*(DWORD*)0x0040ABE4 = Height/2;//商城赠送窗口居中计算高度
	*(DWORD*)0x00F1BE0D = Width;//商城弹出窗口居中计算宽度
	*(DWORD*)0x00F1BE28 = Height;//商城弹出窗口居中计算高度
	*(double*)0x00185AA38 = (double)1.0 / (double)Width;//IMouse::SetXPos_11C7E40
	*(double*)0x00185AA30 = (double)1.0 / (double)Height;//IMouse::SetYPos_11C7EC0
	writeCallCode((void*)0x006360C6, hookGetWinWidth_11D84B0);
	writeCallCode((void*)0x006360D4, hookGetWinHeight_11D84E0);
	//*(BYTE*)0x006360DB = 0xEB;
	

	*(DWORD*)0x004E14FE = 640;//800
	*(DWORD*)0x004E1505 = 480;//600
	*(DWORD*)0x004E150C = 1280;//1024
	*(DWORD*)0x004E1513 = 960;//768
	*(DWORD*)0x004E151A = 1280;
	*(DWORD*)0x004E1521 = 960;

	*(DWORD*)0x004E0D8C = 640;
	*(DWORD*)0x004E0D91 = 640;
	*(DWORD*)0x004E0DAB = 480;
	*(DWORD*)0x004E0DB0 = 480;

	////*(DWORD*)0x01205832 = 640;
	////*(DWORD*)0x0120582D = 480;
	//*(DWORD*)0x011B2AD7 = 640;
	//*(DWORD*)0x011B2AFC = 640;
	//*(DWORD*)0x011B2B0D = 480;
	//*(DWORD*)0x011B2B14 = 480;

	*(DWORD*)0x011D831A = 640;
	*(DWORD*)0x011D8321 = 640;
	*(DWORD*)0x011D832A = 480;
	*(DWORD*)0x011D8331 = 480;

	*(DWORD*)0x011B2402 = 640;
	*(DWORD*)0x011B2409 = 640;
	*(DWORD*)0x011B2411 = 480;
	*(DWORD*)0x011B2418 = 480;

	*(DWORD*)0x00635DEA = 640;
	*(DWORD*)0x00635DF7 = 640;
	*(DWORD*)0x00635E0B = 640;
	*(DWORD*)0x00635DF1 = 480;
	*(DWORD*)0x00635DFF = 480;
	*(DWORD*)0x00635E06 = 480;
	
	*(DWORD*)0x011B2AD7 = 640;
	*(DWORD*)0x011B2AFC = 640;
	*(DWORD*)0x011B2B0D = 480;
	*(DWORD*)0x011B2B14 = 480;

	*(DWORD*)0x010E0386 = 640;
	*(DWORD*)0x010E03B0 = 480;
	*(DWORD*)0x010E0343 = 640;
	*(DWORD*)0x010E0301 = 480;
	*(DWORD*)0x010E06F8 = 640;
	*(DWORD*)0x010E075A = 480 - 20;
	*(DWORD*)0x010E029B = 640;
	*(DWORD*)0x010E02D5 = 480;
	*(DWORD*)0x010E2048 = 640;
	*(DWORD*)0x010E200C = 480;
	//std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(16);
	//hook->resize(4);
	//auto b = hook->begin();
	//b++->setValue(H_DWORD, 0x011B2AD7, 640);
	//b++->setValue(H_DWORD, 0x011B2AFC, 640);
	//b++->setValue(H_DWORD, 0x011B2B0D, 480);
	//b++->setValue(H_DWORD, 0x011B2B14, 480);
	//thisCall4Args2 sub_11B2A80 = (thisCall4Args2)tools_relocation_hook(0x011B2A80, 0x011B2C8B, hook);
	//hook->resize(1);
	//b = hook->begin();
	//b++->setValue(H_CALL, 0x007687D5, (int)sub_11B2A80);
	//mySub_768750 = (cdeclCall2)tools_relocation_hook(0x768750, 0x00768875, hook);
	//gum_interceptor_replace_fast(v, (gpointer)0x768750, (gpointer)hookSub_768750, NULL);
	//delete hook;

#endif // 
	//ui适配640*480
	* (BYTE*)0x004E0E5A = 2;//大区默认选择希罗克
	*(BYTE*)0x010FC08A = 0xEB;//进游戏禁止弹出大区选择窗口

	init70_hud();

	gum_interceptor_replace_fast(v, (gpointer)0xE44250, (gpointer)hookPvfDungeonObj__Constructor_E44250, (gpointer*)&PvfDungeonObj__Constructor_E44250);
	gum_interceptor_replace_fast(v, (gpointer)0x7E8080, (gpointer)hookDungeonMap__Constructor_7E8080, (gpointer*)&DungeonMap__Constructor_7E8080);
	gum_interceptor_replace_fast(v, (gpointer)0x10EF1F0, (gpointer)hookTownMap__Constructor_10EF1F0, (gpointer*)&TownMap__Constructor_10EF1F0);
	gum_interceptor_replace_fast(v, (gpointer)0x8F10A0, (gpointer)hookCNRDStage_proc_8F10A0, (gpointer*)&CNRDStage_proc_8F10A0);
	//gum_interceptor_replace_fast(v, (gpointer)0x10F7040, (gpointer)hookCNSelectChannelModule__onEnterModule_10F7040, (gpointer*)&CNSelectChannelModule__onEnterModule_10F7040);

	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(1);
	auto b = hook->begin();
	b++->setValue(H_JUMP, 0x007E8D6E, (int)FixDungeonCameraPosition);
	//writeJmpCode((LPVOID*)0x007E8D6E, (PVOID)FixDungeonCameraPosition);
	CNModule__changeMap_7E8510 = (thisCall3Args2)tools_relocation_hook(0x7E8510, 0x007E9800, hook);
	delete hook;
	gum_interceptor_replace_fast(v, (gpointer)0x7E8510, (gpointer)hookCNModule__changeMap_7E8510, NULL);
	
	*(DWORD*)0x006FDB06 *= 0.8f;
	*(DWORD*)0x006FDB0B *= 0.8f;
	*(DWORD*)0x010FC28F *= 0.8f;
	*(DWORD*)0x010FC294 *= 0.8f;

	*(DWORD*)0x010FC444 *= 0.8f;
	*(DWORD*)0x010FC449 *= 0.8f;

	*(BYTE*)0x010FC4DA = 42;
	*(DWORD*)0x010FC4CF = 145;

	//*(DWORD*)0x010FC62C *= 0.8f;
	//*(DWORD*)0x010FC635 *= 0.8f;
	//*(DWORD*)0x010FC667 *= 0.8f;

	//*(DWORD*)0x010FC6EF *= 0.8f;
	//*(DWORD*)0x010FC6F4 *= 0.8f;


	*(DWORD*)0x010FC78F = 550;//刷新按钮x
	*(DWORD*)0x010FC78A = 395;//刷新按钮y

	*(DWORD*)0x010FC817 = 256;//开始游戏按钮x
	*(DWORD*)0x010FC812 = 430;//开始游戏按钮y

	*(DWORD*)0x010FC951 = 520;//结束始游戏按钮x
	*(DWORD*)0x010FC94C = 440;//结束始游戏按钮y

	init70_popupWin(v);
	cashShop(v);
	//writeNopCode((void*)0x0111283D, 14);//过图动画去掉框框
	init70_loadingDungeonUi();
	npcDialog(v);
	monsterHp();
	dungeonResult(v);
	dungeonRewardAndEPLP(v);
	deathTowerRewardAndEPLP();
	despairTowerRewardAndEPLP();
	gbossTowerRewardAndEPLP();
	bloodyFightTowerRewardAndEPLP();
	advanceAltar();
	auctionInit();
	goldAuctionInit();
	hudPartyView(v);
	wordMapView();
	////writeNopCode((void*)0x011D24F4, 6);//地下城内显示公告
	CNSelectCharacterModuleInit();
	init70_selectDungeon();
	goldSkillInit();
	ridingInit();

	writeNopCode((void *)0x00730954, 6);//兼容233弹窗命令
	*(WORD*)0x00E77D0E = 0x9090;//时装分解解除限制

	//*(BYTE*)0x00733CF5 = 0x90;//修复南部溪谷门票进入时公告数量错误
	
}
