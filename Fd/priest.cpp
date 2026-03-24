#include "pch.h"
#include "skillCommon.h"
#include "frida-gum.h"
#include "tools.h"

#define Element_Fire	0
#define Element_Water	1
#define Element_Dark	2
#define Element_Light	3
#define Element_All		4

void crusader(void) {//圣骑士

}

//thisCall5Args2 sub_C761A0 = (thisCall5Args2)0xC761A0;
//thisCall2Args2 CNPriest__procPassiveSkill_C905F0 = (thisCall2Args2)0xC905F0;
//void __fastcall hookCNPriest__procPassiveSkill_C905F0(int* thisP, int, int skillId, int skillLv) {
//	CNPriest__procPassiveSkill_C905F0(thisP, skillId, skillLv);
//	if (skillId == 15) {//战环精通
//		//skillLv = CNObject__getSkillLevel_84EE40(thisP, ExEAA);
//		int *skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 15);
//		if (skillLv > CNRDSkill__getStaticData_911930(skillObj, 0, (int)thisP)) {
//			int p1 = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int p2 = CNRDSkill__getLevelInfo_911B90(skillObj, 1, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int p3 = CNRDSkill__getLevelInfo_911B90(skillObj, 2, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int p4 = CNRDSkill__getLevelInfo_911B90(skillObj, 3, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			sub_C761A0(thisP, CNRDObject__getCustomAni_84CE20(thisP, 42), p1, p2, 0, 0);
//			sub_C761A0(thisP, CNRDObject__getCustomAni_84CE20(thisP, 43), p1, p2, 0, 0);
//			sub_C761A0(thisP, CNRDObject__getCustomAni_84CE20(thisP, 44), p1, p2, p3, 0);
//			sub_C761A0(thisP, CNRDObject__getCustomAni_84CE20(thisP, 45), p1, p2, 0, p4);
//		}
//		if (skillLv > CNRDSkill__getStaticData_911930(skillObj, 1, (int)thisP)) {
//			int p1 = CNRDSkill__getLevelInfo_911B90(skillObj, 4, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int p2 = CNRDSkill__getLevelInfo_911B90(skillObj, 5, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int ani = CNRDObject__getCustomAni_84CE20(thisP, 20);
//			sub_C761A0(thisP, ani, p1, p2, 0, 0);
//			if(ani) sub_C761A0(thisP, ((int *)ani)[0x10], p1, p2, 0, 0);
//		}
//		if (skillLv > CNRDSkill__getStaticData_911930(skillObj, 2, (int)thisP)) {
//			int p1 = CNRDSkill__getLevelInfo_911B90(skillObj, 6, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int p2 = CNRDSkill__getLevelInfo_911B90(skillObj, 7, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
//			int ani = CNRDObject__getCustomAni_84CE20(thisP, 49);
//			sub_C761A0(thisP, ani, p1, p2, 0, 0);
//			if (ani) sub_C761A0(thisP, ((int*)ani)[0x10], p1, p2, 0, 0);
//			ani = CNRDObject__getCustomAni_84CE20(thisP, 50);
//			sub_C761A0(thisP, ani, p1, p2, 0, 0);
//			if (ani) sub_C761A0(thisP, ((int*)ani)[0x10], p1, p2, 0, 0);
//		}
//		thisP[0x1978] = skillLv;
//	}
//}

Naked void fixBattleAuraMastery(void) {
	__asm {
		//0x00C909F2
		cmp	ebx, 15
		je isBattleAuraMastery
		cmp	ebx, 14
		je isTechnicalMastery
		mov eax, 0x00C90ED9
		jmp eax
	isTechnicalMastery:
		mov eax, 0x00C909FB
		jmp eax
	isBattleAuraMastery:
		cmp [esi + 0x65E0], edi
		je goExit
		mov eax, 0x00C90AF1
		jmp eax
	goExit:
		mov ecx, 0x00C915D5
		jmp ecx
	}
}
int __fastcall hookCNRDObject__getSkillObj_84B100(int* thisP, int, int skillId) {
	if((int)_ReturnAddress() == 0x025075E9 && skillId == 0x10) skillId = 18;
	return CNRDObject__getSkillObj_84B100(thisP, skillId);
}
int __fastcall hookCNObject__getSkillLevel_84EE40(int* thisP, int, int skillId) {
	if ((int)_ReturnAddress() == 0x025260B6 && skillId == 0x10) skillId = 18;
	return CNObject__getSkillLevel_84EE40(thisP, skillId);
}

int __fastcall hookCNPriest__getAttackCancelStartFrameSize_C726A0(int* thisP) {
	if (thisP[0x1797] == 1) {
		int skillLv = CNObject__getSkillLevel_84EE40(thisP, 17);
		if (!skillLv) return 3;
		int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 17);
		if (!skillObj) return 3;
		if (skillLv >= CNRDSkill__getStaticData_911930(skillObj, 0, (int)thisP)) return 4;
		return 3;
	}
	return ((thisCall2)0xC726A0)(thisP);//CNPriest__getAttackCancelStartFrameSize_C726A0
}

int __fastcall fixCombinationMasterySidewindImp(int* thisP) {
	int skillLv = CNObject__getSkillLevel_84EE40(thisP, 17);
	if (!skillLv) return 0;
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 17);
	if (!skillObj) return 0;
	if (skillLv >= CNRDSkill__getStaticData_911930(skillObj, 1, (int)thisP)) return 1;
	return 0;
}

Naked void fixCombinationMasterySidewind(void) {//瞬拳 0x20
	__asm {
		//00C8E24A
		mov ecx, ebx
		push ebx
		call fixCombinationMasterySidewindImp
		pop ebx
		test eax, eax
		jz goExit
		lea ecx, [ebp - 0x914]
		mov eax, 0x00C8E250
		jmp eax
		goExit:
		mov eax, 0xC8E297
		jmp eax
	}
}
int __fastcall fixSidewindBonusRate(int* thisP, int, int a2, int a3) {
	//00C99294
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 17);
	if (!skillObj) return 0;
	return CNRDSkill__getDataCurrentBonusRateByIdx_9138C0(skillObj, 0, a3);
}

int __fastcall fixCombinationMasteryMachineGunJabImp(int* thisP) {
	int skillLv = CNObject__getSkillLevel_84EE40(thisP, 17);
	if (!skillLv) return 0;
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 17);
	if (!skillObj) return 0;
	if (skillLv >= CNRDSkill__getStaticData_911930(skillObj, 2, (int)thisP)) return 1;
	return 0;
}

Naked void fixCombinationMasteryMachineGunJab(void) {//圣拳猛击 0x2D
	__asm {
		//00C8E83C
		mov ecx, ebx
		push ebx
		call fixCombinationMasteryMachineGunJabImp
		pop ebx
		test eax, eax
		jz goExit
		lea ecx, [ebp - 0x93C]
		mov eax, 0x00C8E842
		jmp eax
		goExit:
		mov eax, 0x00C8E890
		jmp eax
	}
}

int __fastcall fixMachineGunJabBonusRate(int* thisP, int, int a2, int a3) {
	//00C99294
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 17);
	if (!skillObj) return 0;
	return CNRDSkill__getDataCurrentBonusRateByIdx_9138C0(skillObj, 1, a3);
}

thisCall5Args2 IRDSQRCharacter__addSetStatePacket_6835C0 = (thisCall5Args2)0x6835C0;
//int __fastcall hookIRDSQRCharacter__addSetStatePacket_6835C0(int* thisP, int, int state, int datas, int a4, char a5, int a6) {
//	if (state == 0x8 || state == 0x2C ||state == 0x2D)
//		printf("0x%08x addSetStatePacket:[0x%08x, %d, %d]\n", (int)_ReturnAddress(), thisP, state, ((int**)datas)[1][0]);
//	return IRDSQRCharacter__addSetStatePacket_6835C0(thisP, state, datas, a4, a5, a6);
//}

//int __fastcall hookCNRDObject__createPassiveObj_878470(int* thisP, int,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11,int a12,int a13,int a14,int a15) {
//	WORD* p = (WORD*)(a12 + 2);
//	printf("0x%08x data:%d[%d, %d, %d, %d, %d]\n", thisP, *(BYTE *)(a12 + 1), p[0], p[1], p[2], p[3], p[4]);
//	return CNRDObject__createPassiveObj_878470(thisP, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
//}
void __fastcall CNWillDriverPObjAure__onObjectEnter_B1CC80(int* thisP, int, int *obj) {
	//weapon
	int* ap = (int*)newUiComponent_11B0380(0x154);
	if (!ap) return;
	CNChangeStatusAppendage__Constructor_43DC00(ap, 0, 1);
	
	int type[5] = {
		CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE,
		CHANGE_STATUS_TYPE_PHYSICAL_ATTACK,
		CHANGE_STATUS_TYPE_ATTACK_SPEED,
		CHANGE_STATUS_TYPE_MOVE_SPEED,
		CHANGE_STATUS_TYPE_STUCK,
	};
	int weapon = thisP[2];
	float v = 0;
	decrypt_11A0DE0(thisP + 3 + weapon * 3, (int)(thisP + 5 + weapon * 3), (int)&v);
	if (v) {
		if (weapon == 0) v *= 0.1f;
		else if(weapon == 4) v *= -0.1f;
		CNAppendage__addParameter_989AE0(ap, type[weapon], 0, v);
	}
	CNChangeStatusAppendage__AppendAppendage_9879B0(ap, (int)obj, (int)(thisP - 0x373), 0, 0, 0x20, -1, 0, 0);
	((thisCall1Args2)0x9831B0)(ap, 4 * weapon + 0x16C4C58);
}

void infighter(void) {//蓝拳
	//*(DWORD*)0x0170A1F8 = (int)hookIRDSQRCharacter__addSetStatePacket_6835C0;

	//跳过原有技巧精通的战环精通部分
	*(DWORD*)0x00C90AEB = 0x000AE5E9;
	*(BYTE*)0x00C90B71 = 15;
	*(BYTE*)0x00C9E7A4 = 15;
	*(BYTE*)0x00C9E7BB = 15;
	writeJmpCode((void*)0x00C909F2, (void*)fixBattleAuraMastery);
	;
	//硬拳精通
	//直拳冲击
	*(BYTE*)0x00C93330 = 18;
	*(BYTE*)0x00C93340 = 18;
	//神圣组合拳
	*(BYTE*)0x00C98E42 = 18;
	*(BYTE*)0x00C98E52 = 18;
	*(BYTE*)0x00C8664A = 18;
	*(BYTE*)0x00C8665A = 18;
	*(BYTE*)0x00C86810 = 18;
	*(BYTE*)0x00C86820 = 18;
	//破碎之锤
	*(BYTE*)0x00C95FFC = 18;
	*(BYTE*)0x00C9600C = 18;
	//俯冲腹拳
	*(DWORD*)0x0170A6F0 = (int)hookCNRDObject__getSkillObj_84B100;
	*(DWORD*)0x0170A6BC = (int)hookCNObject__getSkillLevel_84EE40;
	
	//组合精通
	*(DWORD*)0x0170A6E8 = (int)hookCNPriest__getAttackCancelStartFrameSize_C726A0;
	writeJmpCode((void*)0x00C8E24A, (void*)fixCombinationMasterySidewind);
	*(WORD*)0x00C9928D = 0xF189; writeCallCode((void*)0x00C9928F, (void*)fixSidewindBonusRate);
	writeJmpCode((void*)0x00C8E83C, (void*)fixCombinationMasteryMachineGunJab);
	*(WORD*)0x00C9B04A = 0xF189; writeCallCode((void*)0x00C9B04C, (void*)fixMachineGunJabBonusRate);

	//0258E75E 意念驱动
	*(DWORD*)0x01621964 = (int)CNWillDriverPObjAure__onObjectEnter_B1CC80;
	//*(BYTE*)0x02596BB2 = 0xBF;
	//*(DWORD*)0x02596BB3 = (int)hookCNRDObject__createPassiveObj_878470;
	//*(WORD*)0x02596BB7 = 0x9090;
}


//sq_SendHitObjectPacketByAttackInfo_5B7CB0
struct AttackInfoPkg
{
	DWORD power;
	DWORD powerRate;
	DWORD useWeapon;
	DWORD sizeRate;
	DWORD changeStatusType;
	float changeStatusProb;
	float changeStatusLevel;
	DWORD changeStatusDuration;
	DWORD changeStatusdamage;
	float stuckRate;
	DWORD knockBackType;
	DWORD backForce;
	DWORD upForce;
	DWORD hitStunTimeAttackerDamager;
	DWORD element;
	DWORD eType;
};

//#define power						0x00
//#define powerRate					0x04
//#define useWeapon					0x08
//#define sizeRate					0x0C
//#define changeStatusType			0x10
//#define changeStatusProb			0x14
//#define changeStatusLevel			0x18
//#define changeStatusDuration		0x1C
//#define changeStatusdamage		0x20
//#define stuckRate					0x24
//#define knockBackType				0x28
//#define backForce					0x2C
//#define upForce						0x30
//#define hitStunTimeAttackerDamager	0x34
//#define element						0x38
//#define eType						0x3C
cdeclCall1 getRandomDword_E50E60 = (cdeclCall1)0xE50E60;
cdeclCall3 sq_SendHitObjectPacketByAttackInfo_5B7CB0 = (cdeclCall3)0x5B7CB0;

thisCall3Args2 CNRDSkill__getCurrentPowerData_9139A0 = (thisCall3Args2)0x9139A0;
void __fastcall hookCNPriest__onCriticalHit_C72810(int* thisP, int,  int attacker, int *damager, int boundingBox) {
	((thisCall3Args2)0xC72810)(thisP, attacker, (int)damager, boundingBox);//CNPriest__onCriticalHit_C72810
	if ((int)thisP != attacker || ((thisCall2)0x8524C0)(thisP) != 3 || (damager[0x24] & OBJECTTYPE_ACTIVE) != OBJECTTYPE_ACTIVE) return;//IRDCharacter::getWeaponSubType_8524C0
	//if ((int)thisP == attacker) {/*!thisP[0x1980] || !RBYTE(thisP[0x1980], 0x40)*/
		int state = 0;
		decrypt_11A0DE0(thisP + 0xC25, (int)(thisP + 0xC27), (int)&state);
		if (state == 15 || state == 25 || state == 29 || state == 30) return;	//29  25 30
	//}
	//else if (RDWORD(attacker, 0x0D64) != 24014) {
	//	return;
	//}
	
	//int subState = 0
	//decrypt_11A0DE0(thisP + 0x1518, (int)(thisP + 0x151A), (int)&subState);
	int skillLv = CNObject__getSkillLevel_84EE40(thisP, 82);
	if (!skillLv) return;
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 82);
	if (!skillObj) return;
	//int randomV = getRandomDword_E50E60(NULL) % 1000;
	int randomV = ((cdeclCall2)0x5ADBA0)(0, 1000);//sq_getRandom_5ADBA0
	int rate = CNRDSkill__getLevelInfo_911B90(skillObj, 2, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	//printf("[%d, %d]\n", randomV, rate);
	if (randomV > rate) return;
	int stunRate = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	int lv = CNRDSkill__getLevelInfo_911B90(skillObj, 3, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	int duration = CNRDSkill__getLevelInfo_911B90(skillObj, 4, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	int power = CNRDSkill__getCurrentPowerData_9139A0(skillObj, 5, 3, -1);// CNRDSkill__getLevelInfo_911B90(skillObj, 5, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	//int stunTime = 0;
	//int *stunTimeAddr = (int*)attacker + 0xB5 + 0x40;
	//decrypt_11A0DE0(stunTimeAddr, (int)(stunTimeAddr + 2), (int)&stunTime);
	//int newStunTime = stunTime * (stunRate + 100) * 0.01f;

	//float stunTimeRate = 0;
	//stunTimeAddr = (int*)attacker + 0xB5 + 0x43;
	//decrypt_11A0DE0(stunTimeAddr, (int)(stunTimeAddr + 2), (int)&stunTimeRate);
	//printf("[%d, %d][ %d, %d, %d]\n", randomV, rate,  lv, duration, power);

	//struct AttackInfoPkg pkg = { 0 };
	//pkg.sizeRate = 0x64;
	////pkg.changeStatusType = 0x12;
	//pkg.hitStunTimeAttackerDamager = newStunTime;
	//pkg.element = 4;
	//pkg.stuckRate = 0;
	//pkg.changeStatusType = 11;
	//pkg.changeStatusProb = 100.0f;
	//pkg.changeStatusLevel = lv;
	//pkg.changeStatusDuration = duration;
	//pkg.changeStatusdamage = power;
	//sq_SendHitObjectPacketByAttackInfo_5B7CB0(attacker, damager, (int)&pkg);
	
	int buffp = *(int *)0x19F2CB8;
	WDWORD(buffp, 0, ((thisCall2)0x406830)(damager));
	WWORD(buffp, 4, lv);
	WDWORD(buffp, 6, duration);
	WDWORD(buffp, 10, power);
	WDWORD(buffp, 14, stunRate);
	*(DWORD*)0x19F2CBC = 18;
	sq_SendCreatePassiveObjectPacketPos_5AF750((int)thisP, 24027, 0, 
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 0),
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 1),
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 2) + damager[0x5F] / 2);
}


void __fastcall hookCNPriest__onAttack_C7EBA0(int* thisP, int, int* damager, int boundingBox, int isStuck) {
	((thisCall3Args2)0xC7EBA0)(thisP, (int )damager, boundingBox, isStuck);
	if (isStuck || ((thisCall2)0x8524C0)(thisP) != 4 || (damager[0x24] & OBJECTTYPE_ACTIVE) != OBJECTTYPE_ACTIVE) return;//IRDCharacter::getWeaponSubType_8524C0
	int state = 0;
	decrypt_11A0DE0(thisP + 0xC25, (int)(thisP + 0xC27), (int)&state);
	if (state == 15 || state == 25 || state == 29 || state == 30) return;	//29  25 30
	int skillLv = CNObject__getSkillLevel_84EE40(thisP, 83);
	if (!skillLv) return;
	int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 83);
	if (!skillObj) return;
	//int randomV = getRandomDword_E50E60(NULL) % 1000;
	int randomV = ((cdeclCall2)0x5ADBA0)(0, 1000);//sq_getRandom_5ADBA0
	int rate = CNRDSkill__getLevelInfo_911B90(skillObj, 2, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	//printf("[%d, %d]\n", randomV, rate);
	if (randomV > rate) return;
	int stunRate = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
	//CNRDSkill::getAttackBonusRateByLevelData_9138C0
	int bonusRate = CNRDSkill__getDataCurrentBonusRateByIdx_9138C0(skillObj, 3, 0x3F800000) + 100;
	//printf("[%d, %d][ %d]\n", randomV, rate, bonusRate);

	int buffp = *(int*)0x19F2CB8;
	WDWORD(buffp, 0, ((thisCall2)0x406830)(damager));
	WDWORD(buffp, 4, bonusRate);
	WDWORD(buffp, 8, stunRate);
	*(DWORD*)0x19F2CBC = 12;
	sq_SendCreatePassiveObjectPacketPos_5AF750((int)thisP, 24028, 0,
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 0),
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 1),
		((thisCall1Args2)0x8B0670)((int*)damager[0x2A], 2) + damager[0x5F] / 2);
}

int __fastcall CNScytheMasteryHitPObj__setCurrentAttackInfo_805030(int* thisP, int,  int *atkInfo) {
	int *parentObj = (int *)((thisCall2)0x46FBA0)(thisP);//CNRDPassiveObject__getParent_46FBA0
	if (parentObj) {
		int *parentObjCurrentAtkInfo = parentObj + 0xB5;
		int v = 0;
		decrypt_11A0DE0(parentObjCurrentAtkInfo + 0x40, (int)(parentObjCurrentAtkInfo + 0x42), (int)&v);
		encrypt_11A0930(atkInfo + 0x40, (int)&v, (int)(atkInfo + 0x42));
		float rate = 0.0f;
		decrypt_11A0DE0(parentObjCurrentAtkInfo + 0x43, (int)(parentObjCurrentAtkInfo + 0x45), (int)&rate);
		int stunRate = 0;
		if (thisP[0x373] == 3) {//镰刀精通
			stunRate = RDWORD(*(int*)0x19F2CC0, 14);
		}
		else if (thisP[0x373] == 4){//战斧精通
			stunRate = RDWORD(*(int *)0x19F2CC0, 8);
		}
		float newRate = rate + stunRate * 0.01f;
		//printf("%f[%f, %d]\n", newRate, rate, stunRate);
		encrypt_11A0930(atkInfo + 0x43, (int)&newRate, (int)(atkInfo + 0x45));
	}
	return ((thisCall1Args2)0x805030)(thisP, (int)atkInfo);
}

void exorcist(void) {//驱魔
	//脉轮 : 圣光 改 脉轮 : 冰轮
	*(BYTE*)0x00C7B974 = Element_Water;
	//大招改无属性
	*(BYTE*)0x00C8F544 = 0xB8; *(DWORD*)0x00C8F545 = 4;
	*(DWORD*)0x00C9D0C9 = 0x9090046A;

	//镰刀精通
	//0099DC14  0099DC92
	*(DWORD*)0x0099DC0B = 3;//武器类型
	*(WORD*)0x0099DC14 = 0x7CEB;
	*(DWORD*)0x0099DCB0 = 0x110;
	*(DWORD*)0x0099DCBE = 0x108;
	*(DWORD*)0x0099DCAA = 0x157893C;
	*(DWORD*)0x0170A1D0 = (int)hookCNPriest__onCriticalHit_C72810;
	
	//战斧精通 0x199C
	*(DWORD*)0x0170A1BC = (int)hookCNPriest__onAttack_C7EBA0;

	*(WORD*)0x00B152B4 = 0xBA90; *(DWORD*)0x00B152B6 = (int)CNScytheMasteryHitPObj__setCurrentAttackInfo_805030;
	
}

void avenger(void) {//复仇

}

void __fastcall hookCNPriest__procPassiveSkill_C905F0(int* thisP, int, int skillId, int skillLv) {
	((thisCall2Args2)0xC905F0)(thisP, skillId, skillLv);
	if (skillId != 83) return;//战斧精通
	int* ap = (int*)thisP[0x199C];
	if (skillLv) {
		if (!ap) {
			ap = (int*)newUiComponent_11B0380(0x194);
			if (!ap) return;
			((thisCall2Args2)0xB768A0)(ap, 4, 83);
			thisP[0x199C] = (int)ap;
			WBYTE((ap + 1), 0x24, 0);//auto delete flag
		}
		int apSkillLv = 0;
		decrypt_11A0DE0(ap + 0x5F, (int)(ap + 0x61), (int)&apSkillLv);
		int apSkillModule = 0;
		decrypt_11A0DE0(ap + 0x62, (int)(ap + 0x64), (int)&apSkillModule);
		int currentMoudle = CNModule__getGameModule_75C470((int *)getCNModule_706410());
		if (skillLv != apSkillLv || apSkillModule != currentMoudle) {
			encrypt_11A0930(ap + 0x5F, (int)&skillLv, (int)(ap + 0x61));
			encrypt_11A0930(ap + 0x62, (int)&currentMoudle, (int)(ap + 0x64));
			listInit1_1389550(ap + 0x2B);
			int weaponSubType = 4;
			GameVector1__PushBack_493770(ap + 0x2B, (int) & weaponSubType);//战斧武器类型
			int *skillObj = (int*)((cdeclCall3)0x91DC10)((int)thisP, 4, 83);//getSkillObj_91DC10
			float rate = CNRDSkill__getLevelInfo_911B90(skillObj, 1, skillLv, 0, -1, -1, 0xE, 0, 0) * 0.1f;
			encrypt_11A0930(ap + 0x4E, (int)&rate, (int)(ap + 0x50));//命中率
		}
		CNChangeStatusAppendage__AppendAppendage_9879B0(ap, (int)thisP, (int)thisP, 0, 0, 0, -1, 0, 0);
	}
	else {
		if (!ap || !RBYTE(ap, 0x40)) return;//CNAppendage__getState_42D810
		((thisCall1Args2)0x933A70)((int*)thisP[0xB35], (int)ap);//CNAppendageList::remove_933A70
	}
	
}

int __fastcall hookCNPriest__clear_C74840(int* thisP) {
	thisP[0x199C] = 0;
	return ((thisCall2)0xC74840)(thisP);
}

int __fastcall hookCNPriest__clearAppend_C70C40(int* thisP) {
	int ret = ((thisCall2)0xC70C40)(thisP);
	if (thisP[0x199C]) ((thisCall1Args2)0xB76E00)((int *)thisP[0x199C], 1);
	thisP[0x199C] = 0;
	return ret;
}

void priestInit(void) {
	*(DWORD*)0x00D1B85D += 4;//增加空间
	writeCallCode((void*)0x00D1A14E, hookCNPriest__clear_C74840);
	writeCallCode((void*)0x00D1A22E, hookCNPriest__clearAppend_C70C40);
	*(DWORD*)0x0170A86C = (int)hookCNPriest__procPassiveSkill_C905F0;

	crusader();
	infighter();
	exorcist();
	avenger();
}