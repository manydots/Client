#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall2 CNModule__getGameModule_75C470 = (thisCall2)0x75C470;
int __fastcall hookCNModule__getGameModule_75C470(int* thisP) {
	if (thisP[0x3E4]) return -1;
	//int chn;
	//decrypt_11A0DE0((int *)0x1A6A9C4, (int)0x1A6A9CC, (int) & chn);
	//if (chn >= 52 && chn <= 56) return -1;
	return CNModule__getGameModule_75C470(thisP);
}

int __fastcall pvpFixDraw(int* thisP, int , int x, int y, int* imgAddr) {
	return innerDrawImg_11DB180(imgAddr, 0, 0, (int)thisP);
}

void pvpResult(void) {
	//sub_1029FC0
	*(BYTE*)0x0102A059 -= 80;//x
	*(DWORD*)0x0102A054 -= 60;//y
	*(BYTE*)0x0102A308 -= 80;//x
	*(DWORD*)0x0102A303 -= 60;//y
	*(DWORD*)0x0102A4BC -= 80;//x
	*(DWORD*)0x0102A4B7 -= 60;//y
	*(DWORD*)0x0102A4C6 -= 80;//x
	*(DWORD*)0x0102A695 -= 60;//y
	*(DWORD*)0x0102A77A -= 80;//x
	*(DWORD*)0x0102A775 -= 60;//y
	*(DWORD*)0x0102A475 -= 80;//x
	*(DWORD*)0x0102A470 -= 60;//y

	//sub_1025C80
	*(BYTE*)0x01025D3D -= 80;//x
	*(DWORD*)0x01025D38 -= 60;//y
	*(DWORD*)0x01025D51 -= 80;//x
	*(DWORD*)0x01025D4c -= 80;//x
	*(DWORD*)0x01025DB6 -= 60;//y
	*(DWORD*)0x01025DC2 -= 60;//x
	*(DWORD*)0x01025E1B -= 60;//y
	
	
	*(DWORD*)0x01025E36 -= 160;//x
	*(DWORD*)0x01025E31 -= 80;//x
	*(DWORD*)0x01025E89 -= 60;//y

	*(DWORD*)0x01025E95 -= 80;//x
	*(DWORD*)0x01025EE9 -= 60;//y
	*(DWORD*)0x01025F40 -= 80;//x
	*(DWORD*)0x01025F3B -= 60;//y
	*(DWORD*)0x01025F5F -= 80;//x
	*(DWORD*)0x01025F5A -= 60;//y
	*(DWORD*)0x01025F7B -= 80;//x
	*(DWORD*)0x01025F76 -= 60;//y

	*(BYTE*)0x01026541 -= 80;//x
	*(DWORD*)0x0102653C -= 60;//y

	*(BYTE*)0x0102679F -= 80;//x
	*(BYTE*)0x0102679C -= 60;//y
	*(DWORD*)0x010267FE -= 80;//x
	*(BYTE*)0x010267FC -= 60;//y

	*(DWORD*)0x0102657E -= 160;//x
	*(DWORD*)0x01026579 -= 80;//x
	*(DWORD*)0x010265DE -= 60;//y

	*(DWORD*)0x010265EA -= 80;//x
	*(DWORD*)0x01026646 -= 60;//y
	*(DWORD*)0x010266B2 -= 80;//x
	*(DWORD*)0x010266AD -= 60;//y
	*(DWORD*)0x0102671F -= 80;//x
	*(DWORD*)0x0102671A -= 60;//y

	*(DWORD*)0x0102616A -= 80;//x
	*(DWORD*)0x01026168 -= 60;//y
	*(DWORD*)0x01025CD2 -= 80;//x
	*(DWORD*)0x010260E9 -= 60;//y
	*(DWORD*)0x010261ED -= 80;//x
	*(DWORD*)0x010261EB -= 60;//y
	*(DWORD*)0x010262D4 -= 80;//x
	*(DWORD*)0x010262D2 -= 60;//y
	*(DWORD*)0x01026357 -= 80;//x
	*(DWORD*)0x01026355 -= 60;//y
	*(DWORD*)0x01026447 -= 80;//x
	*(DWORD*)0x01026442 -= 60;//y
	*(DWORD*)0x0102649D -= 80;//x
	*(DWORD*)0x01026498 -= 60;//y

	//sub_1026810
	*(DWORD*)0x01026939 -= 80;//x
	*(BYTE*)0x01026937 -= 60;//y

	//sub_1028180
	*(DWORD*)0x0102820B -= 80;//x
	*(DWORD*)0x01028206 -= 60;//y
	*(DWORD*)0x01028280 -= 80;//x
	*(DWORD*)0x0102827B -= 60;//y
	*(DWORD*)0x010282F5 -= 80;//x
	*(DWORD*)0x010282F0 -= 60;//y
	*(DWORD*)0x0102837A -= 80;//x
	*(DWORD*)0x01028375 -= 60;//y
	*(DWORD*)0x010283EF -= 80;//x
	*(DWORD*)0x010283EA -= 60;//y
	*(DWORD*)0x0102845C -= 80;//x
	*(DWORD*)0x01028457 -= 60;//y
	*(DWORD*)0x010284B2 -= 80;//x
	*(DWORD*)0x010284AD -= 60;//y

	*(DWORD*)0x0102857E -= 80;//x
	*(DWORD*)0x01028579 -= 60;//y
	*(DWORD*)0x010285DA -= 80;//x
	*(DWORD*)0x010285D5 -= 60;//y
	*(DWORD*)0x01028660 -= 80;//x
	*(DWORD*)0x0102865B -= 60;//y
	*(DWORD*)0x010286B6 -= 80;//x
	*(DWORD*)0x010286B1 -= 60;//y
	*(DWORD*)0x01028712 -= 80;//x
	*(DWORD*)0x0102870D -= 60;//y
	*(DWORD*)0x01028780 -= 80;//x
	*(DWORD*)0x0102877B -= 60;//y
	*(DWORD*)0x010287D6 -= 80;//x
	*(DWORD*)0x010287D1 -= 60;//y
	*(DWORD*)0x01028841 -= 80;//x
	*(DWORD*)0x0102883C -= 60;//y
	*(DWORD*)0x0102885C -= 80;//x
	*(DWORD*)0x01028857 -= 60;//y

	*(DWORD*)0x01028892 -= 80;//x
	*(DWORD*)0x01028897 -= 60;//y
	*(DWORD*)0x01028604 -= 80;//x
	*(DWORD*)0x0102888C -= 60;//y

	*(DWORD*)0x010288FD -= 80;//x
	*(DWORD*)0x010288F8 -= 60;//y
	*(DWORD*)0x01028964 -= 80;//x
	*(DWORD*)0x0102895F -= 60;//y
	*(DWORD*)0x01028A62 -= 80;//x
	*(DWORD*)0x01028A5D -= 60;//y
	*(DWORD*)0x01028AB4 -= 80;//x
	*(DWORD*)0x01028AAF -= 60;//y

	*(DWORD*)0x01028AD2 -= 80;//x
	*(DWORD*)0x01028ACD -= 60;//y
	*(DWORD*)0x01028B1F -= 80;//x
	*(DWORD*)0x01028B1A -= 60;//y
	*(DWORD*)0x01028B37 -= 80;//x
	*(DWORD*)0x01028B2B -= 60;//y

	*(DWORD*)0x01028B92 -= 80;//x
	*(DWORD*)0x01028B8D -= 60;//y
	*(DWORD*)0x01028C12 -= 80;//x
	*(DWORD*)0x01028C0D -= 60;//y
	*(DWORD*)0x01028C7E -= 80;//x
	*(DWORD*)0x01028C7C -= 60;//y
	*(DWORD*)0x01028CD7 -= 80;//x
	*(DWORD*)0x01028CD5 -= 60;//y

	//sub_1025740
	*(DWORD*)0x010257AD -= 80;//x
	*(DWORD*)0x010257A8 -= 60;//y
	*(DWORD*)0x0102582C -= 80;//x
	*(DWORD*)0x01025827 -= 60;//y
	*(DWORD*)0x010255F0 -= 80;//x
	*(DWORD*)0x010255EB -= 60;//y
	*(DWORD*)0x01025657 -= 80;//x
	*(DWORD*)0x01025652 -= 60;//y

	//sub_10259E0
	*(BYTE*)0x01025A5E -= 80;//x
	*(BYTE*)0x01025A5C -= 60;//y
	*(DWORD*)0x01025AA8 -= 80;//x
	*(DWORD*)0x01025AA3 -= 60;//y

	//sub_1025850
	*(BYTE*)0x010258EF -= 80;//x
	*(DWORD*)0x010258EA -= 60;//y
	*(BYTE*)0x01025977 -= 80;//x
	*(DWORD*)0x01025972 -= 60;//y
	*(BYTE*)0x010259A3 -= 80;//x
	*(DWORD*)0x0102599E -= 60;//y

	*(DWORD*)0x0102AC33 -= 80;//x
	*(DWORD*)0x0102AC2E -= 60;//y

	//sub_1026950
	*(DWORD*)0x010269EF -= 80;//x
	*(BYTE*)0x010269DD -= 60;//y
	*(BYTE*)0x01026B6E -= 60;//y
	*(DWORD*)0x01026A60 -= 80;//x
	*(DWORD*)0x01026B43 -= 80;//x
	*(DWORD*)0x01026C4A -= 80;//x
	*(DWORD*)0x01026CA4 -= 80;//x
	*(DWORD*)0x01026DF0 -= 80;//x
	*(DWORD*)0x01026DD0 -= 80;//x
	*(DWORD*)0x01026E41 -= 80;//x
	*(DWORD*)0x01026E93 -= 80;//x
	*(DWORD*)0x01026EC5 -= 80;//x
	*(DWORD*)0x01026F09 -= 80;//x
	*(DWORD*)0x01027056 -= 80;//x
	*(DWORD*)0x010270A5 -= 80;//x
	*(DWORD*)0x01026F58 -= 80;//x
	*(DWORD*)0x01026FAD -= 80;//x
	*(DWORD*)0x01026FDF -= 80;//x
	*(DWORD*)0x0102702E -= 80;//x
	*(DWORD*)0x01027134 -= 80;//x
	*(DWORD*)0x010271B2 -= 80;//x
	*(DWORD*)0x01027211 -= 80;//x
	*(DWORD*)0x01027652 -= 80;//x
	*(DWORD*)0x010276A1 -= 80;//x
	*(DWORD*)0x0102754D -= 80;//x
	*(DWORD*)0x010275A2 -= 80;//x
	*(DWORD*)0x010275D9 -= 80;//x
	*(DWORD*)0x01027628 -= 80;//x
	*(DWORD*)0x01027732 -= 80;//x
	*(DWORD*)0x010272F5 -= 80;//x
	*(DWORD*)0x010273E3 -= 80;//x
	*(DWORD*)0x01027434 -= 80;//x
	*(DWORD*)0x01027486 -= 80;//x
	*(DWORD*)0x010274B5 -= 80;//x
	*(DWORD*)0x010274F9 -= 80;//x
	*(DWORD*)0x010273BD -= 80;//x
	*(DWORD*)0x010277B7 -= 160;//x
	*(DWORD*)0x01027814 -= 80;//x

	//sub_1027850
	*(BYTE*)0x010278C2 -= 60;//y
	*(BYTE*)0x010278C8 -= 60;//y
	*(BYTE*)0x010278CB -= 60;//y
	*(BYTE*)0x010278CE -= 60;//y
	*(DWORD*)0x01027B27 -= 80;//x
	*(DWORD*)0x01027B97 -= 80;//x
	*(DWORD*)0x010279D0 -= 80;//x
	*(DWORD*)0x01027A3D -= 80;//x

	//sub_1027BD0
	*(DWORD*)0x01027D2A -= 80;//x
	*(BYTE*)0x01027C0D -= 60;//y
	*(DWORD*)0x01027C9E -= 80;//x
	*(BYTE*)0x01027C10 -= 60;//y
}

void PvpInit(void) {
	//计时
	writeCallCode((void*)0x004C4B13, pvpFixDraw);//背景
	*(DWORD*)0x004C4D62 -= 160;//x
	*(DWORD*)0x004C4D5D -= 99;//y
	*(DWORD*)0x004C4D98 -= 160;//x
	*(DWORD*)0x004C4D93 -= 99;//y
	*(DWORD*)0x004C4DB7 -= 160;//x
	*(DWORD*)0x004C4DB2 -= 99;//y
	*(DWORD*)0x004C4C81 -= 160;//x
	*(DWORD*)0x004C4C7C -= 99;//y
	*(DWORD*)0x004C4CB8 -= 160;//x
	*(DWORD*)0x004C4CB3 -= 99;//y
	*(DWORD*)0x004C4C30 -= 160;//x
	*(DWORD*)0x004C4C2B -= 99;//y
	*(DWORD*)0x004C4C4F -= 160;//x
	*(DWORD*)0x004C4C4A -= 99;//y
	*(DWORD*)0x004C4BFA -= 160;//x
	*(DWORD*)0x004C4BF5 -= 99;//y
	*(DWORD*)0x004C4E40 -= 80;//x
	*(DWORD*)0x004C4E3B -= 50;//y
	*(DWORD*)0x004BDFBC -= 80;//x
	*(DWORD*)0x004BDFB7 -= 60;//y

	//框框
	writeCallCode((void*)0x004CA44A, pvpFixDraw);
	writeCallCode((void*)0x004CA475, pvpFixDraw);

	//左方 CNRDBaseInterface::drawPvpLeftnMain_4BF7E0
	//背景
	writeCallCode((void*)0x004BF8A0, pvpFixDraw);
	writeCallCode((void*)0x004BF87F, pvpFixDraw);
	writeCallCode((void*)0x004BF8BD, pvpFixDraw);
	//头像
	*(BYTE*)0x004BF909 = 6;//x
	*(BYTE*)0x004BF907 = 6;//y

	*(DWORD*)0x004BF92B = 226;//血条长度
	*(DWORD*)0x004BF995 = 226;//蓝条长度
	//血条cover
	*(DWORD*)0x004BF949 -= 120; *(BYTE*)0x004BF94F = 53; writeCallCode((void*)0x004BF96E, pvpFixDraw); //*(BYTE*)0x004BF96D = 53; *(BYTE*)0x004BF96B = 0;
	//蓝条
	*(DWORD*)0x004BF9B3 -= 120; *(BYTE*)0x004BF9B9 = 53; *(BYTE*)0x004BF9D7 = 53; *(BYTE*)0x004BF9D5 = 32;
	//名字
	*(BYTE*)0x004BFA0A = 57;//x
	*(BYTE*)0x004BFA08 = 15;//y
	//死亡红叉
	*(BYTE*)0x004BFA63 = 4;//x
	*(BYTE*)0x004BFA61 = 0;//y
	//服务器
	*(BYTE*)0x004BFA94 = 60;//x
	*(BYTE*)0x004BFA91 = 15;//y
	//*(BYTE*)0x004BFA6E = 0xEB;//跳过服务器显示
	//ping
	*(BYTE*)0x004BFA23 = 35;//x
	*(BYTE*)0x004BFA21 = 14;//y

	//右方 CNRDBaseInterface::drawPvpRightMain_4BFAC0
	//背景
	writeCallCode((void*)0x004BFB86, pvpFixDraw);
	writeCallCode((void*)0x004BFB62, pvpFixDraw);
	writeCallCode((void*)0x004BFBA6, pvpFixDraw);
	//头像
	*(DWORD*)0x004BFBF2 = 592;//x
	*(BYTE*)0x004BFBF0 = 6;//y

	*(DWORD*)0x004BFC17 = 226;//血条长度
	*(DWORD*)0x004BFC8B = 226;//蓝条长度
	//血条cover
	*(DWORD*)0x004BFC3A -= 160; *(DWORD*)0x004BFC35 -= 120; *(DWORD*)0x004BFC3F = 587; writeCallCode((void*)0x004BFC64, pvpFixDraw); //*(BYTE*)0x004BF96D = 53; *(BYTE*)0x004BF96B = 0;
	//蓝条
	*(DWORD*)0x004BFCB1 -= 160; *(DWORD*)0x004BFCA9 -= 120; *(DWORD*)0x004BFCB6 = 587; *(DWORD*)0x004BFCD4 = 361; *(BYTE*)0x004BFCD2 = 32;
	//名字
	*(DWORD*)0x004BFD0D = 497;//x
	*(BYTE*)0x004BFD0B = 15;//y
	//死亡红叉
	*(DWORD*)0x004BFD6C = 591;//x
	*(BYTE*)0x004BFD6A = 0;//y
	//服务器
	*(DWORD*)0x004BFDC1 -= 160;//x
	*(BYTE*)0x004BFDCC = 15;//y
	//*(BYTE*)0x004BFD7A = 0xEB;//跳过服务器显示
	//ping
	*(DWORD*)0x004BFD26 -= 160;//x
	*(BYTE*)0x004BFD24 = 14;//y

	//左方 CNRDBaseInterface::drawPvpLeftSecond_4BFDF0
	*(BYTE*)0x004BFE74 = 6;//x pos
	writeCallCode((void*)0x004BFEA2, pvpFixDraw);
	*(BYTE*)0x004BFEF5 = 22;//x 光标
	*(BYTE*)0x004BFEF3 -= 23;//y
	writeCallCode((void*)0x004BFF2A, pvpFixDraw);
	*(BYTE*)0x004BFF7A -= 23;//y 头像
	*(BYTE*)0x004BFF9D -= 23;//y 死亡红叉
	*(BYTE*)0x004C0049 -= 23;//y 申请出战
	*(BYTE*)0x004C007E -= 23;//y 名字
	*(BYTE*)0x004C009A = 35; *(BYTE*)0x004C009A = 35;//y ping
	*(BYTE*)0x004C00AA -= 23;//y ping

	//右方 CNRDBaseInterface::drawPvpRightSecond_4C00F0
	*(BYTE*)0x004C0172 = 553;//x pos
	writeCallCode((void*)0x004C01AB, pvpFixDraw);
	*(DWORD*)0x004C01FE -= 160;//x 光标
	*(BYTE*)0x004C01FC -= 23;//y
	writeCallCode((void*)0x004C0239, pvpFixDraw);
	*(BYTE*)0x004C0289 -= 23;//y 头像
	*(BYTE*)0x004C02AC -= 23;//y 死亡红叉
	*(BYTE*)0x004C0358 -= 23;//y 申请出战
	*(BYTE*)0x004C038D -= 23;//y 名字
	*(DWORD*)0x004C03AB -= 160; *(BYTE*)0x004C03A9 = 35;//y ping
	*(DWORD*)0x004C03BE -= 160; *(BYTE*)0x004C03BC -= 23;//y ping

	writeCallCode((void*)0x004CA44A, pvpFixDraw);
	writeCallCode((void*)0x004CA44A, pvpFixDraw);
	writeCallCode((void*)0x004CA44A, pvpFixDraw);
	writeCallCode((void*)0x004CA44A, pvpFixDraw);

	writeCallCode((void*)0x004D2B9C, hookCNModule__getGameModule_75C470);
	writeCallCode((void*)0x00E76BE7, hookCNModule__getGameModule_75C470);
	writeCallCode((void*)0x00E76BF8, hookCNModule__getGameModule_75C470);
	writeCallCode((void*)0x00E76C09, hookCNModule__getGameModule_75C470);
	*(BYTE*)0x004D2BA6 = 0xE9; *(DWORD*)0x004D2BA7 = 0x0000022B;
	//PvpRoomListWin::
	*(DWORD*)0x00FE7E9F -= 160;//右边窗口x
	*(BYTE*)0x00FE7E9D -= 31;//右边窗口y
	*(DWORD*)0x00FE7F59 -= 160;//返回城镇x
	*(DWORD*)0x00FE7F54 -= 31;//返回城镇y
	*(DWORD*)0x00FE800D -= 160;//创建房间x
	*(DWORD*)0x00FE8008 -= 31;//创建房间y
	*(DWORD*)0x00FE80C1 -= 160;//立即开始x
	*(DWORD*)0x00FE80BC -= 31;//立即开始y
	*(DWORD*)0x00FE8175 -= 160;//决斗练习x
	*(DWORD*)0x00FE8170 -= 31;//决斗练习y
	*(DWORD*)0x00FE81CE -= 160;//x
	*(DWORD*)0x00FE81C9 -= 31;//y
	*(DWORD*)0x00FE8232 -= 160;//x	
	*(DWORD*)0x00FE822D -= 31;//y
	*(DWORD*)0x00FE8CFC -= 160; 
	*(DWORD*)0x00FE8C9B -= 31;//y
	*(DWORD*)0x00FE8DC0 -= 160; 
	*(DWORD*)0x00FE9084 -= 160; 
	*(DWORD*)0x00FE90B0 -= 160;
	*(DWORD*)0x00FE9112 -= 160;
	*(DWORD*)0x00FE91C7 -= 160;
	*(DWORD*)0x00FE921C -= 160;
	*(DWORD*)0x00FE8E18 -= 160;
	*(DWORD*)0x00FE8E44 -= 160;
	*(DWORD*)0x00FE8EA6 -= 160;
	*(DWORD*)0x00FE8F2B -= 160;
	*(DWORD*)0x00FE7D02 += 160;
	*(DWORD*)0x00FE7CF1 -= 31;

	//PvpCharacListView::init_4F9DD0
	//*(DWORD*)0x004FABF7 -= 160;//更换地图x
	*(DWORD*)0x004F77BE -= 160;//名字
	*(DWORD*)0x004F3DA2 += 160; *(DWORD*)0x004F3D91 -= 31;
	*(DWORD*)0x004FBCD6 -= 160; *(BYTE*)0x004FBCD4 -= 31;
	*(DWORD*)0x004FBCF6 -= 160; *(BYTE*)0x004FBCF4 -= 31;
	
	*(DWORD*)0x004FC841 -= 160; 
	*(DWORD*)0x004FC83C -= 160; *(BYTE*)0x004FC829 -= 31;
	*(DWORD*)0x004FC87F -= 160; *(BYTE*)0x004FC87D -= 31;

	*(DWORD*)0x004FC8D1 -= 160; *(BYTE*)0x004FC8B9 -= 31;
	*(DWORD*)0x004FC8CC -= 160;
	*(DWORD*)0x004FC90F -= 160; *(BYTE*)0x004FC90D -= 31;

	*(DWORD*)0x004F8312 -= 160; *(BYTE*)0x004F8310 -= 31;
	*(DWORD*)0x004F83F0 -= 160; *(BYTE*)0x004F83EE -= 31;

	*(DWORD*)0x004F7275 -= 160; *(BYTE*)0x004F7273 -= 31;
	*(DWORD*)0x004F7295 -= 160; *(BYTE*)0x004F7293 -= 31;
	*(DWORD*)0x004F72F6 -= 160; *(BYTE*)0x004F72F4 -= 31;
	*(DWORD*)0x004F7333 -= 160; *(BYTE*)0x004F7331 -= 31;
	*(DWORD*)0x004F7429 -= 160; *(DWORD*)0x004F736A -= 31;
	*(DWORD*)0x004F7470 -= 160; 

	*(DWORD*)0x004F7482 -= 160;
	*(DWORD*)0x004F74F2 -= 160;
	*(DWORD*)0x004F7579 -= 160;
	*(DWORD*)0x004F75D1 -= 160;
	*(DWORD*)0x004F7628 -= 160;
	*(DWORD*)0x004F76ED -= 160;
	*(DWORD*)0x004F7764 -= 160;

	*(DWORD*)0x004F7963 -= 160;
	*(DWORD*)0x004F73B9 -= 160;
	*(DWORD*)0x004F79EA -= 160; *(BYTE*)0x004F79E8 -= 31;
	*(DWORD*)0x004F7A7A -= 160; *(DWORD*)0x004F7A75 -= 31;

	*(DWORD*)0x004F68D8 -= 160; *(BYTE*)0x004F68D6 -= 31;
	*(DWORD*)0x004F6963 -= 160; *(DWORD*)0x004F695E -= 31;
	*(DWORD*)0x004F814B -= 160; *(DWORD*)0x004F8146 -= 31;
	*(DWORD*)0x004F8193 -= 160; *(DWORD*)0x004F818E -= 31;

	*(DWORD*)0x004F81DA -= 160; *(DWORD*)0x004F81D5 -= 31;
	*(DWORD*)0x004F8222 -= 160; *(BYTE*)0x004F8220 -= 31;

	*(DWORD*)0x004F82AC -= 160; *(DWORD*)0x004F82A7 -= 31;

	*(BYTE*)0x00E7C257 = 0xEB;//pvp不放大

	*(DWORD*)0x004CA57E -= 22;//血条
	*(DWORD*)0x004CA594 -= 22;//血条y
	pvpResult();
}