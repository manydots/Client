#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"

#define GoldSkillKeyMap		89

static int goldSkillPObjVtabel[] = {0x18D92D0,0x9EFE90,0x6DEC90,0x4064A0,0x4064F0,0x7FB230,0x8024A0,0x802FD0,0x7FCBB0,0x7FD750,0x7FF780,0x4068A0,0x4062D0,0x7F9D90,0x497190,0xEF91F0,0xEF91F0,0x5ABA70,0x42E3F0,0x4C2000,0x406830,0x11BADA0,0x7FA110,0x7FA1D0,0x7FE4F0,0x7FB490,0x4062E0,0xA197D0,0x4062F0,0x7FAEF0,0x406300,0x406330,0x7FAF70,0x406900,0x4067E0,0x7FAFA0,0x406360,0x7F9DB0,0x7F9E30,0x7F9DF0,0x67CD40,0x7F9E40,0x406390,0x4063A0,0x4063B0,0x4063C0,0xEF91F0,0x46FC80,0x4063E0,0x406400,0x91F3F0,0x115A430,0x9AE750,0x96DF60,0x97DDB0,0x7FB510,0x802270,0x8020E0,0x7FA3F0,0x7FA8F0,0x7FAAB0,0x7F9E50,0x7F9E70,0x7F9E90,0x406440,0x406470,0x7FA330,0x7FAC10,0x406540,0x4065A0,0x7FAD50,0x7FADB0,0x406600,0x406610,0x7FAE40,0x800C80,0x800CB0,0x7FAF30,0x7FEE50,0x7FE350,0x7FF060,0x7FC060,0x800C50,0x406620,0x406630,0x7FB130,0x7FBD90,0x7FA0B0,0x406640,0x406650,0x7FDF90,0x406660,0x406680,0x406690,0x4066B0,0x4066C0,0x115A430,0x7F9FA0,0x4066F0,0xECEF30,0x7FA000,0x406700,0x406740,0x406750,0xFA9870,0x406780,0x8019A0,0x8077A0,0x6DEC90,0x800560,0x8049A0,0x406790,0x4067A0,0x4067B0,0x800B90,0x87B170,0x1198560,0x4067C0,0x4067D0,0xF27780,0x800D70,0x800DF0,0xEF91F0,0x8006E0,0xD12380,0x8045C0,0x46FBA0,0x443330,0x442C50,0x805030,0x442C60,0x443350,0x87E9D0,0x87AD70,0x442C70,0x871E80,0x871C10,0x442C80,0x46FBB0,0x442C90,0x442CA0,0x624D80,0x442EB0,0x46FBE0,0x46FBF0,0x46FC00,0x46FC10,0x46FC20,0x46FC30,0x46FC40,0x46FC50,0x46FC60,0x874600,0x442CB0,0x442EE0,0x442F00,0x442CC0,0x442CC0,0x8020A0,0x442F20,0x442F60,0x442FA0,0x442FE0,0x8763C0,0x874FE0,0x800C40,0x800C40,0x442CF0,0x805570,0x8010A0,0x8010D0,0x8010F0,0x871F50,0x87EB50,0x879C80,0x874070,0x871500,0x8715A0,0x8003B0,0x800480,0x706020,0x803510,0x800490,0x706020,0x804360,0x8711B0,0x8714A0,0x87B4D0,0xB2C1C0,0x8029C0,0x6DEC90,0x872D90,0x6DEC90,0x6DEC90,0x6DEC90,0x443020,0x8779B0,0x442D00,0x443180,0x879DB0,0x67F290,0x443050,0x521540,0x46FC90,0x800640,0x46FCC0,0x800CE0,0x871880,0x879320,0x878470,0x878620,0x872ED0,0x8712D0,0x878750,0x875BE0,0x871430,0x871360,0x443070,0x4430A0,0x4430D0,0x443100,0x872F60,0x443130,0x443160,0x874410,0xD26320,0x442D40,0x87B870,0x442D50,0x442D80,0x442D90,0x87A960,0x87B620,0x442DA0,0x818940,0x8722C0,0x442DC0,0x87D360,0x442DD0,0x442DE0,0x872320,0x442DF0,0x872340,0x872370,0x800740,0x1198560,0x1198560,0x872430,0x872850,0x8718E0,0x871A00,0x878F80,0x871EE0,0x115A430,0x115A430,0xEF91F0,0x406430,0x8722F0,0x442E10,0x442E20,0x442E30,0x442E40,0x879910,0x87D4C0,0x879970,0x443340,0xB0AE30,0x8719B0,0x6DEC90,0x46FED0,0x46FB90,0x800C00,0x802500,0x800E70,0x46FC70,0x800D20,0x46FD00,0x46FCD0,0x800BB0,0x800760,0x8010E0,0x881210,0x803C40,0x800AB0,0x8006A0 };
static float goldSkillPObjDamage[][70] = {
	{ 0, 60, 120, 180, 240, 300, 360, 420, 480, 540, 600, 660, 720, 780, 840, 900, 960, 1020, 1080, 1140, 1200, 1296, 1392, 1488, 1584, 1680, 1776, 1872, 1968, 2064, 2160, 2304, 2448, 2712, 2736, 2880, 3024, 3168, 3312, 3456, 3480, 3756, 4032, 4308, 4584, 4860, 5136, 5412, 5688, 5964, 6000, 6264, 6528, 6792, 7056, 7320, 7584, 7848, 8112, 8376, 8400, 8820, 9240, 9660, 10080, 10500, 10920, 11340, 11760, 12000 },
	{ 0, 120, 240, 360, 480, 600, 720, 840, 960, 1080, 1200, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2592, 2784, 2976, 3168, 3360, 3552, 3744, 3936, 4128, 4320, 4608, 4896, 5424, 5472, 5760, 6048, 6336, 6624, 6912, 6960, 7512, 8064, 8616, 9168, 9720, 10272, 10824, 11376, 11928, 12000, 12528, 13056, 13584, 14112, 14640, 15168, 15696, 16224, 16752, 16800, 17640, 18480, 19320, 20160, 21000, 21840, 22680, 23520, 24000 },
	{ 0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4320, 4640, 4960, 5280, 5600, 5920, 6240, 6560, 6880, 7200, 7680, 8160, 9040, 9120, 9600, 10080, 10560, 11040, 11520, 11600, 12520, 13440, 14360, 15280, 16200, 17120, 18040, 18960, 19880, 20000, 20880, 21760, 22640, 23520, 24400, 25280, 26160, 27040, 27920, 28000, 29400, 30800, 32200, 33600, 35000, 36400, 37800, 39200, 40000 }
};

static int* goldSkillBtn;
static int* goldSkillHideBtn;
static int* goldSkillShowBtn;

//static GameAnim* effect01 = new GameAnim(L"passiveobject/actionobject/gold_skill/animation/effect01.ani", false);
//static GameAnim* effect02 = new GameAnim(L"passiveobject/actionobject/gold_skill/animation/effect02.ani", false);
static GameAnim* cursor0 = new GameAnim(L"ui/fd/goldskill/cursor0.ani", true);
static GameAnim* cursor1 = new GameAnim(L"ui/fd/goldskill/cursor1.ani", true);
static GameAnim* level1 = new GameAnim(L"ui/fd/goldskill/level1.ani", true);
static GameAnim* level2 = new GameAnim(L"ui/fd/goldskill/level2.ani", true);
static GameAnim* level3 = new GameAnim(L"ui/fd/goldskill/level3.ani", true);
static GameAnim* title = new GameAnim(L"ui/fd/goldskill/title.ani", true);

#define STATE_DISABLE	-1
#define STATE_HIDED		0
#define STATE_SHOWED	1
#define STATE_SHOWING	2
#define STATE_HIDING	3

static BYTE state = -1;
static int level[4];
static int maxLevel[4];
static BYTE isShowGoldSKillWin = true;
static int timer[7];
static int startT;
static BYTE en = false;

void goldSkill_AddLevel(void) {
	//printf("%d %d %d\n", level, maxLevel, IsTraining);
	int lv = 0, mLv = 0;
	decrypt_11A0DE0(level, (int)(level + 2), (int)&lv);
	decrypt_11A0DE0(maxLevel, (int)(maxLevel + 2), (int)&mLv);
	if (lv >= mLv || IsTraining) return;
	if (lv == 2) {
		setUiComponentEnable_11BE350(goldSkillBtn, 1);
		++lv;
	}
	else if (lv < 10) {
		++lv;
	}
	//if (lv < 6)
	//	CNRDAnimation__setRGBA_108EF70(cursor->animObj, 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	//else
	//	CNRDAnimation__setRGBA_108EF70(cursor->animObj, 0, 0, 0, 0xFFu);
	encrypt_11A0930(level, (int)&lv, (int)(level + 2));
}

void goldSkill_resetLevel(void) {
	int lv = 0;
	decrypt_11A0DE0(level, (int)(level + 2), (int)&lv);
	if(lv >= 10)lv = 0;
	else if(lv >= 6) lv -= 6;
	else if (lv >= 3) lv -= 3;
	encrypt_11A0930(level, (int)&lv, (int)(level + 2));
	setUiComponentEnable_11BE350(goldSkillBtn, lv >= 3);
}

void goldSkill_setState(int newState) {
	if (newState == STATE_HIDED) {
		setUiComponentVisable_11BE610(goldSkillBtn, 0);
		setUiComponentVisable_11BE610(goldSkillHideBtn, 0);
		setUiComponentVisable_11BE610(goldSkillShowBtn, 1);
		isShowGoldSKillWin = 0;
	}
	else if (newState == STATE_SHOWED) {
		setUiComponentVisable_11BE610(goldSkillBtn, 1);
		setUiComponentVisable_11BE610(goldSkillHideBtn, 1);
		setUiComponentVisable_11BE610(goldSkillShowBtn, 0);
		isShowGoldSKillWin = 1;
	}
	else if (state != newState){
		startT = CNTimer__Get_11BA640(timer);
		if (newState == STATE_SHOWING) {
			setUiComponentVisable_11BE610(goldSkillBtn, 1);
			setUiComponentPos_11BEAD0(goldSkillBtn, -130, 68, 1);
		} else 
			setUiComponentPos_11BEAD0(goldSkillBtn, 15, 68, 1);
	}
	state = newState;
}

forceinline void goldSkillBtn_ProcState(void) {
	int currentT = CNTimer__Get_11BA640(timer);
	int xPos;
	switch (state) {
	case STATE_HIDING:
		xPos = getLinearValue_11B98C0(15, -130, currentT - startT, 200);
		if (xPos == -130)goldSkill_setState(STATE_HIDED);
		else setUiComponentPos_11BEAD0(goldSkillBtn, xPos, 68, 1);
		break;
	case STATE_SHOWING:
		xPos = getLinearValue_11B98C0(-130, 15, currentT - startT, 200);
		if (xPos == 15)goldSkill_setState(STATE_SHOWED);
		else setUiComponentPos_11BEAD0(goldSkillBtn, xPos, 68, 1);
		break;
	}
}
//thisCall2 BaseBtn__Proc_11C35D0 = (thisCall2)0x11C35D0;
void __fastcall goldSkillBtn_Proc(int* thisP) {
	static int* goldskillImg = (int*)loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/goldskill/ui.img");
	BaseBtn__Proc_11C35D0(thisP);
	int x = thisP[0xE2] + thisP[5];
	int y = thisP[0xDE] + thisP[6];
	//int x = thisP[0xE0] + thisP[5];
	//int y = thisP[0xDC] + thisP[6];
	int lv = 0;
	decrypt_11A0DE0(level, (int)(level + 2), (int)&lv);
	int w = lv * 13 + 3;
	int v;
	goldSkillBtn_ProcState();
	if (!lv) return;
#define YPos 16
	setGameCanvasSize_6FD880(x + 3, y, x + w, y + 36);
	if (lv < 6) {
		v = getImageByPos_11B4BD0(goldskillImg, 1);
		drawImgByXY_11B3950(*(int**)0x1B5582C, x + 3, y + YPos, v);
		if (lv == 3) {
			setGameCanvasSize_6FD880(x, y, x + w + 3, y + 36);
			level1->draw(x - 1, y + YPos - 4);
			setGameCanvasSize_6FD880(x + 3, y, x + w, y + 36);
		}
	}
	else if (lv < 10) {
		v = getImageByPos_11B4BD0(goldskillImg, 2);
		drawImgByXY_11B3950(*(int**)0x1B5582C, x + 3, y + YPos, v);
		if (lv == 6) {
			setGameCanvasSize_6FD880(x, y, x + w + 3, y + 36);
			level2->draw(x - 1, y + YPos - 3);
			setGameCanvasSize_6FD880(x + 3, y, x + w, y + 36);
			
		}
	}
	else if (lv == 10) {
		v = getImageByPos_11B4BD0(goldskillImg, 3);
		drawImgByXY_11B3950(*(int**)0x1B5582C, x + 3, y + YPos, v);
		setGameCanvasSize_6FD880(x, y, x + w, y + 36);
		level3->draw(x - 1, y + YPos - 3);
		setGameCanvasSize_6FD880(x + 3, y, x + w - 13, y + 36);
	}
	if (lv < 6) {
		cursor0->draw(x, y + YPos);
		cursor0->draw(x - 117, y + YPos);
	}
	else {
		cursor1->draw(x, y + YPos);
		cursor1->draw(x - 117, y + YPos);
	}

	resetGameCanvasSize_6FD8D0();

	if (lv > 2) {
		title->draw(x - 1, y - 1);
	}

//	effect02->draw(x - 10, y - 10);
//	if (effect01->draw(x - 10, y - 10)) {//²¥·ÅÍê±Ï
//		goldSkill_resetLevel();
//	}
}

void goldSkillInitDelay(int *thisP) {
	CNTimer__Init_11BA940(timer);
	int goldskillImg = loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/goldskill/ui.img");
	int x = 4, y = 75;
	goldSkillBtn = newBtn(((int***)thisP)[0x0F][2], x + 11, y - 4, goldskillImg, 0, 0, 9, 0);
	int* typeInfo = (int*)malloc(sizeof(void*) * 50);
	if (typeInfo == NULL) {
	    printf("malloc vtable memory error!\n");
	    return;
	}
	memcpy(typeInfo, (void*)0x0185A818, 0xC8);
	typeInfo[11] = (int)goldSkillBtn_Proc;
	*goldSkillBtn = (int) & typeInfo[1];

	goldSkillShowBtn = newBtn(((int***)thisP)[0x0F][2], x, y, goldskillImg, 10, 10, 11, 0xffffffff);
	goldSkillHideBtn = newBtn(((int***)thisP)[0x0F][2], x, y, goldskillImg, 12, 12, 12, 0xffffffff);

	int v = 0;
	initEncryptKey_11A2470(level);
	encrypt_11A0930(level, (int)&v, (int)(level + 2));
	initEncryptKey_11A2470(maxLevel);
	encrypt_11A0930(maxLevel, (int)&v, (int)(maxLevel + 2));
}

int __fastcall setCurrentAttackInfo(int* thisP, int, int atkInfo) {
	int pobjIdx = CNRDPassiveObject__getPassiveObjectIndex_5ABA70(thisP);
	if (pobjIdx >= 12069 && pobjIdx <= 12071) {
		float power = -1;
		decrypt_11A0DE0((int*)atkInfo, atkInfo + 8, (int)&power);
		if (power > 0) {
			int parent = CNRDPassiveObject__getParent_5B6E10(thisP);
			if (parent) {
				int characLv = 1;
				decrypt_11A0DE0((int*)(parent + 0x231C), parent + 0x231C + 8, (int)&characLv);
				if (characLv > 0 && characLv <= 70) {
					float lvDamage = goldSkillPObjDamage[pobjIdx - 12069][characLv - 1];
					//printf("[%d, 0x%08x, %d, %f, %f]\n", characLv, parent, pobjIdx, power, lvDamage);
					//power += lvDamage;
					encrypt_11A0930((int*)atkInfo, (int)&lvDamage, (atkInfo + 8));
				}
			}
		}
	}
	return CNRDPassiveObject__setCurrentAttackInfo_805030(thisP, atkInfo);
}

//int* __fastcall getCurrentAttackInfo(int* thisP) {
//	int *ret = (int *)CNRDPassiveObject__getCurrentAttackInfo_442C60(thisP);
//	float v = -1;
//	decrypt_11A0DE0(ret, (int)(ret + 2), (int)&v);
//	return ret;
//}


thisCall2Args2 CNRDPassiveObject__Constructor_9EFE60/* = (thisCall2Args2)0x9EFE60*/;
int __fastcall hookCNRDPassiveObject__Constructor_9EFE60(int* thisP, int, int id, int a3) {
	int ret = CNRDPassiveObject__Constructor_9EFE60(thisP, id, a3);
	if (id - 12069 < 3) {
		*(int*)ret = (int)&goldSkillPObjVtabel[1];
	}
	return ret;
}

void triggerGoldSkill(int level) {
	if (CGameModule != MODULE_MAIN_GAME) return;
	int* charac = *(int**)0x01AC790C;
	if (!charac) return;
	setUiComponentEnable_11BE350(goldSkillBtn, 0);
	
	//effect01->reset();
	//effect02->reset();
	sq_StartWrite_BB16F0(charac);
	int passiveId = 12069;
	if (level >= 10) passiveId += 2;
	else if (level >= 6) passiveId += 1;
	sq_sendCreatePassiveObjectPacket_B6A990(charac, passiveId, 0, 0, 0, 0);
	goldSkill_resetLevel();
}
 
void goldSkill_CNRDBaseInterface__procCb(int* thisP) {
	if (!en || CGameModule != MODULE_MAIN_GAME) return;
	if (((char*)goldSkillShowBtn)[12] && IControl__IsClick_11BDFC0(goldSkillShowBtn)) {
		goldSkill_setState(STATE_SHOWING);
	}
	else if (((char*)goldSkillHideBtn)[12] && IControl__IsClick_11BDFC0(goldSkillHideBtn)) {
		goldSkill_setState(STATE_HIDING);
	}
	int lv = 0;
	decrypt_11A0DE0(level, (int)(level + 2), (int)&lv);
	if (lv < 3) return;
	bool isKey = sq_IsKeyDown_5AFB50(GoldSkillKeyMap, KEYVALUE_MASK);
	bool isClick = ((char*)goldSkillBtn)[12] && IControl__IsClick_11BDFC0(goldSkillBtn);
	if (!isKey && !isClick) return;
	triggerGoldSkill(lv);
}

void setMaxLevel(void) {
	if (!QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20573)) {
		//printf("set null:%d\n", maxLevel);
		return;
	}
	int lv = 0;
	if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20575))lv = 10;
	else if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20574))lv = 6;
	else if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20573))lv = 3;
	encrypt_11A0930(maxLevel, (int)&lv, (int)(maxLevel + 2));
	//printf("sete:%d\n", maxLevel);
}

void goldSkill_OnNotiClearQuest(void) {
	setMaxLevel();
}

void goldSkill_OnFinshQuest(void) {
	setMaxLevel();
}


void goldSkill_CNTownModule__onExitModuleCb(int* thisP, int a2) {
	setMaxLevel();
}

void goldSkill_CNMainGameModule_onEnterModuleCb(int* thisP, int a2) {
	if (IsTraining || !QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20573)) {
		setUiComponentVisable_11BE610(goldSkillBtn, 0);
		setUiComponentVisable_11BE610(goldSkillHideBtn, 0);
		setUiComponentVisable_11BE610(goldSkillShowBtn, 0);
		en = false;
		return;
	}
	en = true;
	setMaxLevel();
	CNTimer__Reset_11BA3F0(timer);
	CNTimer__Start_11BAA10(timer, 0, 0);
	//if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20575))maxLevel = 10;
	//else if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20574))maxLevel = 6;
	//else if (QuestMgr__isFinishQuest_4FDC00(*(int**)0x1A6F774, 20573))maxLevel = 3;
	int lv = 0;
	decrypt_11A0DE0(level, (int)(level + 2), (int)&lv);
	setUiComponentEnable_11BE350(goldSkillBtn, lv >= 3);
	goldSkill_setState(isShowGoldSKillWin);
}

void goldSkill_CNMainGameModule_onExitModuleCb(int* thisP, int a2) {
	setUiComponentVisable_11BE610(goldSkillBtn, 0);
	setUiComponentVisable_11BE610(goldSkillHideBtn, 0);
	setUiComponentVisable_11BE610(goldSkillShowBtn, 0);
}

void goldSkillInit(void) {
	goldSkillPObjVtabel[129] = (int)setCurrentAttackInfo;
	//goldSkillPObjVtabel[130] = (int)getCurrentAttackInfo;
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x9EFE60, (gpointer)hookCNRDPassiveObject__Constructor_9EFE60, (gpointer*)&CNRDPassiveObject__Constructor_9EFE60);
}