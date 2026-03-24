#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

#define AP_COMMON_ID	0
#define NO_IMG			0
#define NO_OVERLAP		-1
#define ExPA	245
#define ExPD	246
#define ExMA	247
#define ExMD	248
#define ExS		249
#define ExAS	250
#define ExHP	251
#define ExMP	252
#define ExEAA	253
#define ExETA	254


void __fastcall hookIRDSQRCharacter__procPassiveSkill_6885D0(int* thisP, int, int skillId, int skillLv) {
	IRDSQRCharacter__procPassiveSkill_6885D0(thisP, skillId, skillLv);
	if (skillLv < 1 || skillId < ExPA || skillId > ExETA) return;
	//printf("procPassiveSkill:%d %d\n", skillId, skillLv);
	int* p = (int*)getCharacInfoBase_D10040(thisP, CharacInfoTypeTotal);
	int* ap = (int*)GetSquirrelAppendage_827F80(thisP, (int)L"appendage/character/tp.nut");
	if (!ap) {
		ap = (int*)sq_AppendAppendage_9DB8A0((int)thisP, (int)thisP, ExETA, 0, (int)L"appendage/character/tp.nut", 1);
	}
	int* changeStatusAp = (int*)sq_getChangeStatus_9D5F30(ap, (int)L"tpCommon");
	if (!changeStatusAp) {
		changeStatusAp = (int*)sq_AddChangeStatus_9D6340(ap, (int)L"tpCommon", (int)thisP, (int)thisP, 0, CHANGE_STATUS_TYPE_HP_MAX, 0, 1);
	}
	if (!changeStatusAp) return;

	(((thisCall2*)*changeStatusAp)[0x2A])(changeStatusAp);

	int* skillObj;
	float value;
	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExPA);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExPA);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExPD);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExPD);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExMA);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExMA);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExMD);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExMD);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExS);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExS);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_STUCK, 0, -value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExAS);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExAS);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_ACTIVEPROPERTY_STUCK, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExHP);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExHP);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		float preV = value / 500;
		double rate = getAbilityConvertRate_766340((int)thisP, CONVERT_TABLE_TYPE_PHYSICAL_DEFENSE);
		int baseDp = getCharacPhysicalDefense_4C1A60(p);
		float fV = baseDp * rate * preV;
		//printf("baseDp:%d rate:%lf preV:%f  fV:%f\n", baseDp, rate, preV, fV);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_HP_REGEN_RATE, 0, fV);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExMP);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExMP);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		float preV = value / 500;
		double rate = getAbilityConvertRate_766340((int)thisP, CONVERT_TABLE_TYPE_MAGICAL_DEFENSE);
		int baseDp = getCharacMagicalDefense_4C1B20(p);
		float fV = baseDp * rate * preV;
		//printf("baseMp:%d rate:%lf preV:%f  fV:%f\n", baseDp, rate, preV, fV);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_MP_REGEN_RATE, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExEAA);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExEAA);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_ELEMENT_ATTACK_ALL, 0, value);
	}

	skillLv = CNObject__getSkillLevel_84EE40(thisP, ExETA);
	if (skillLv) {
		skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, ExETA);
		value = CNRDSkill__getLevelInfo_911B90(skillObj, 0, skillLv, (int)thisP, -1, -1, 0xE, 0, 0);
		CNAppendage__addParameter_989AE0(changeStatusAp, CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_ALL, 0, value);
	}
	//IRDAppendage__setAppendCauseSkill_9321A0(changeStatusAp, 2, thisP[0xF02], ExETA, 1);
	//CNChangeStatusAppendage__AppendAppendage_9879B0(changeStatusAp, (int)thisP, (int)thisP, ExETA, NO_IMG, AP_COMMON_ID, NO_OVERLAP, 0, 0);
}


float __fastcall hookGetLevelData(int* skillObj, int, int a1, int skillLv, int a3, int a4, int a5, int a6, int a7, int a8) {
	int id = -1;
	decrypt_11A0DE0(skillObj + 0xE, (int)(skillObj + 0x10), (int) & id);
	float v = CNRDSkill__getLevelInfo_911B90(skillObj, a1, skillLv, a3, a4, a5, a6, a7, a8);
	if (id == 11) {
		DPRINTF("lvData:0x%p[%d,%f]\n", _ReturnAddress(), skillLv, v);
	}
	return v;
}

void tpSkillInit(void) {
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x6885D0, (gpointer)hookIRDSQRCharacter__procPassiveSkill_6885D0, (gpointer *)& IRDSQRCharacter__procPassiveSkill_6885D0);
	//gum_interceptor_replace_fast(v, (gpointer)0x911B90, (gpointer)hookGetLevelData, (gpointer*)&CNRDSkill__getLevelInfo_911B90);
}