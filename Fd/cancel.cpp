#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"
#include "cancel.h"

thisCall1Args2 CNRDSkill__setCommonSkillCommandEnable_846D30 = (thisCall1Args2)0x846D30;
void __fastcall hookCNRDSkill__setCommonSkillCommandEnable_846D30(int* thisP, int, int a2) {
    if (CNRDObject__isMyControlObject_7F9EB0(thisP)) {
        if (!*((BYTE*)thisP + 0x4F73))
            a2 = 0;
        int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 170);
        int level;
        if (skillObj) {
            decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&level);
            if (level) {
                skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 169);
                CNRDSkill__setCommandEnable_910D90(skillObj, a2);
            }
        }
        *((BYTE*)thisP + 0x4FF8) = a2;
    }
	return;
}

thisCall2 IsEnableThrow_84A6B0 = (thisCall2)0x84A6B0;
int __fastcall hookIsEnableThrow_84A6B0(int* thisP) {
    int ret = IsEnableThrow_84A6B0(thisP);
    if (!ret && CNRDObject__isMyControlObject_7F9EB0(thisP)) {
        int *skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 171);
        if (skillObj) decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&ret);
    }
    return ret;
}

static short SwordmanSkill[][3] = {
    //{3,20,10},//µØÁÑ¡¤²¨¶¯½£
    //{3,21,10},//±ùÈÐ¡¤²¨¶¯½£
    //{3,22,10},//±¬Ñ×¡¤²¨¶¯½£
    {0,8,26},//Èý¶ÎÕ¶
    {0,5,28},//¹íÕ¶
    {0,46,48},//ÉÏÌô
    {0,58,59},//ÁÑ²¨Õ¶
    {0,1,45}, //¸ñµ²
    {1,68,69}, //ÆÆ¾ü
    {3,24,70}, //Å­Æø±¬·¢
    {4,2,71}, //¹íÓ¡Öé
    //{3,103,104}, //ÑªÆøÖ®ÈÐ
    {1,105,106}, //Á÷ÐÄ
    //{2,111,-1}, //¹íÓ°±Þ£¬ 70ÎÞ´Ë¼¼ÄÜ
    //{2,112,-1}, //¹íÓ°Èý»÷½££¬ 70ÎÞ´Ë¼¼ÄÜ
    {2,77,83}, //ÔÂ¹âÕ¶
    {3,64,78}, //Ê®×ÖÕ¶
    {3,65,66}, //±ÀÉ½
    {3,31,54}, //ÊÈ»êÖ®ÊÖ

    { 1,97,-1 }, // ÆÆ¿Õ°Îµ¶Õ¶
    { 1,98,-1 }, // ÆÆ¾üÕ¶Áú»÷
    { 2,95,-1}, // Ä¹±®Èý¾øÕó
    { 2,96, -1}, // ±ùËªÖ®ÈøÑÇ
    { 3,101,-1 }, //ÑªÆø±¬·¢
    { 3,102,-1 }, //Ãð»êÖ®ÊÖ
    { 4,99,-1 },// ¼«Ñ×*ÁÑ²¨½£
    { 4,100,-1 }, //¼«±ù*ÁÑ²¨½£

};


void __inline setCancelSKillEnable(int* thisP, int skillId, int cancelSkillId, int isEnable) {
    int* skillObj, skillLevel;
    if (cancelSkillId >= 0) {
        skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, cancelSkillId);
        if (!skillObj) return;
        decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&skillLevel);
        if (!skillLevel) return;
    }
    skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, skillId);
    CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
}


void __fastcall hookCNSwordman__setEnableCancelSkill_CA6CA0(int* thisP, int, int isEnable) {

    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    int growtype = thisP[0xF05];
    int skillLevel;
    int* skillObj;
    if (growtype == 4) {
        skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 10);
        if (skillObj) {
            decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&skillLevel);
            if (skillLevel) {
                skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 20);
                CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
                skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 21);
                CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
                skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 22);
                CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            }
        }
    }
    int* ap = (int*)thisP[0x1A0F];
    if (ap && ((thisBCall2*)*ap)[0x1C](ap)) {// Ë«µ¶Ap 42D810 ±êÖ¾
        setCancelSKillEnable(thisP, 103, 104, isEnable);// ÑªÆøÖ®ÈÐ
    }
    for (short i = 0, *p; i < sizeof(SwordmanSkill) / (3 * sizeof(short)); ++i) {
        p = SwordmanSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }
}

static short CNATFighterSkill[][3] = {
    {0,12,21},//ÄîÆø²¨
    {0,5,23},//ºóÌß
    {0,6,24},//ÏÂ¶ÎÌß
    {0,13,25},//Å×É³
    {0,19,26},//³åÏ¥
    {0,9,27},//Ï¥»÷
    {0,18,28}, //¸¡¿ÕÁèÔÆÌß
    {0,46,47}, //Ç°Ìß
    {0,3,48}, //ÇÜÔÂÑ×
    {0,49,53}, //Å×Í¶
    {0,58,59}, //Ðý·çÍÈ
    //{4,52,61}, //Ç¿ÖÆ - Í¶ÖÀ 52 60 75 38
    {0,86,92}, //½ð¸ÕËé
    {0,80,93}, //Öâ»÷
    {0,1,94}, //ÌúÉ½¿¿
    {0,81,95}, //ÕÛ¾±
    {0,89,96}, //µØÓü·ç»ðÂÖ
    {0,42,98}, //ÄîÆøÕÖ
    {0,15,99}, //Ê¨×Óºð
    {0,16,100}, //ÂÝÐýÄîÆø³¡
    {0,76,102}, //¶¾À×Òý±¬
    {0,82,103}, //Ë²Ó°Á¬»·Ìß
    {0,106,107}, //ÂÝÐý»¬²ù
    //{0,111,113}, //ÄîÆø»·ÈÆ£ºÏ®

    {1,117, -1},// ÄîÖ®Õ½Ã¬
    {1,118, -1},// åçÐÇ³å»÷

    {2,119, -1},// ±¬ÆÆð¤Çò
    {2,120, -1},// ³åÔÆÄîÆø³¡

    {3,121, -1},// ÎäÁ«»ª
    {3,122, -1},// Ðý·çËéÐÄÌß

    {4,123, -1},// Ç§Ë¿ÂÒÎè
    {4,124, -1},// Åùö¨ÈýÖØÌß
};

bool checkSkillList(int* list, int listSize, int skillId) {
    for (int i = 0; i < listSize; ++i) if (list[i] == skillId) return true;
    return false;
}

void __fastcall hookCNATFighter__setEnableCancelSkill_B77610(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    if ((((thisBCall2*)*thisP)[0x288])(thisP)) {
        setCancelSKillEnable(thisP, 111, 113, isEnable);
    }
    int skillLevel;
    int *skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 61);
    if (skillObj) {
        decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&skillLevel);
        if (skillLevel) {//52 60 75 38
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 52);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 60);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 75);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 38);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
        }
    }
    
    for (short i = 0, *p; i < sizeof(CNATFighterSkill) / (3 * sizeof(short)); ++i) {
        p = CNATFighterSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }

    int* ap = (int*)thisP[0x1BED];
    if (ap && ((thisBCall2*)*ap)[0x1C](ap)) {//´óÕÐap
        int begin = ((int*)0x1AD29F4)[1];
        int end = ((int*)0x1AD29F4)[2];
        int size = (end - begin) / 4;
        for (int *i = (int *)0x16CEB30; i < (int*)0x16CEC10; i += 2) {
            setCancelSKillEnable(thisP, *i, -1, checkSkillList((int *)begin, size, *i));
        }
    }

}

static short CNFighterSkill[][3] = {
    {0,12,21},//ÄîÆø²¨
    {0,5,23},//ÉÏ¹´È­
    {0,6,24},//ÏÂ¶ÎÌß
    {0,13,25},//Å×É³
    {0,19,26},//´çÈ­
    {0,9,27}, //±³Ë¤
    {0,18,28}, //ÂÝÐýåçÐÇÂä
    {0,46,47}, //Ç°Ìß
    {0,3,48}, //ÇÜÔÂÑ×
    {0,49,53}, //Å×Í¶
    {0,58,59}, //Ðý·çÍÈ
    {0,60,61}, //×©Ï®
    {0,86,92}, //½ð¸ÕËé
    {0,80,93}, //±ÀÈ­
    {0,1,94}, //ÌúÉ½¿¿
    {0,81,95}, //ÕÛ¾±
    {0,75,96}, //¶¾Ó°Õë

    {1,98, -1},//¾¿¼«ÄîÆøÕÖ
    {1,100, -1},//¿ñÊ¨Å­ºð
    {2,102, -1},//ÆÆËéÈ­
    {2,103, -1},//ÉýÁú°Ô
    {3,99, -1},//ÃÍ¶¾ÇÜÔÂÑ×
    {3,104, -1},//±¬Ëé×©ÁÑ
    {4,101, -1},//¿Õ½ÊÁ¬´¸
    {4,105, -1},//ËÀÍöÒ¡Àº
};


void __fastcall hookCNFighter__setEnableCancelSkill_BBD2B0(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    for (short i = 0, *p; i < sizeof(CNFighterSkill) / (3 * sizeof(short)); ++i) {
        p = CNFighterSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }
}

static short CNGunnerSkill[][3] = {
    {0,12,16},//¸ñÁÖ»úÇ¹
    {0,13,17},//M-3Åç»ðÆ÷
    {0,7,18},//Ë³Ìß/´ÌÌß
    {0,6,19},//Ì¤Éä/¶¤´ÌÉä
    //{0,5,24},//±¬Í·Ò»»÷
    {0,14,25}, //BBQ
    {0,73,74}, //¼ÓÅ©ÅÚ
    {0,4,84}, //Ï¥×²/ºóÁÃÌß
    {0,47,85}, //¸¡¿Õµ¯
    {0,3,86}, //»ØÐýÌß/ÉÏÐýÌß
    //{0,46,87}, //ÊÖÀ× 56 57 58
    {0,40,88}, //·´Ì¹¿ËÅÚ
    {0,41,89}, //¼¤¹âÅÚ
    {0,48,90}, //½»²æÉä»÷
    {1,101, -1},//»ØÐý½Ø»÷/ÏÊÑªÂÓ¶á
    {1,104, -1},//¼«ÏÞ¶àÖØ±¬Í·
    {2,107, -1},//º®±ùÅçÉäÆ÷
    {2,108, -1},//SW´Ìµ¯ÅÚ
    {3,105, -1},//·´»÷Õß
    {3,106, -1},//¶¾ÉßÅÚ
    {4,102, -1},//C4·ÉËÙÕ¨µ¯
    {4,103, -1},//M-61µØÀ×
};

void __fastcall hookCNGunner__setEnableCancelSkill_BF44F0(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    int skillLevel;
    int* skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 87);
    if (skillObj) {
        decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&skillLevel);
        if (skillLevel) {//ÊÖÀ× 56 57 58
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 56);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 57);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 58);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
        }
    }

    skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 24);
    if (skillObj) {
        decrypt_11A0DE0(skillObj + 0x164, (int)(skillObj + 0x166), (int)&skillLevel);
        if (skillLevel) {//ÊÖÀ× 56 57 58
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 5);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
            skillObj = (int*)CNRDObject__getSkillObj_84B100(thisP, 20);
            CNRDSkill__setCommandEnable_910D90(skillObj, isEnable);
        }
    }

    for (short i = 0, *p; i < sizeof(CNGunnerSkill) / (3 * sizeof(short)); ++i) {
        p = CNGunnerSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }
}

static short CNMageSkill[][3] = {
    {0,11,32},//Ä§·¨ÐÇµ¯
    {0,14,33},//Âä»¨ÕÆ
    {0,12,34},//Ìì»÷
    {0,65,70},//Ô²Îè¹÷
    {0,4,71},//ÁúÑÀ
    {0,13,72}, //Ëé°Ô
    {0,92,94}, //°µÓ°¶·Åñ
    {0,95,96}, //±äÒì²ÔÓ¬ÅÄ
    {0,123,124}, //ìÅÎÆÈÚºÏ
    {0,125,126}, //Ë«ÖØ´¸»÷

    {1,111, -1},//¹âµç±ùÇ½
    {1,113, -1},//ÐéÎÞ»ðÉ½

    {2,118, -1},//SW´Ìµ¯ÅÚ
    {2,119, -1},//º®±ùÅçÉäÆ÷
    {2,120, -1},//SW´Ìµ¯ÅÚ
    {2,121, -1},//º®±ùÅçÉäÆ÷
    {2,122, -1},//SW´Ìµ¯ÅÚ

    {3,112, -1},//Á÷ÐÇÀ×Á¬»÷
    {3,117, -1},//ìÅÎÆËé°Ô

    {4,114, -1},//µ¯ÌøÐý×ªÉ¨°Ñ
    {4,115, -1},//³¬¼¶²ÔÓ¬ÅÄ
};

void __fastcall hookCNMage__setEnableCancelSkill_C30950(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    int* ap = (int*)thisP[0x185C];
    if (ap && ((thisBCall2*)*ap)[0x1C](ap)) {//ap
        isEnable = 0;
    }

    for (short i = 0, *p; i < sizeof(CNMageSkill) / (3 * sizeof(short)); ++i) {
        p = CNMageSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }

    if (ap && ((thisBCall2*)*ap)[0x1C](ap)) {//ap
        ((BYTE*)ap)[0x10C] = 1;
        ((BYTE*)ap)[0x140] = 1;
        ((BYTE*)ap)[0x174] = 1;
    }
}

static short CNPriestSkill[][3] = {
    //{0,1,6},//¿ÕÕ¶´ò
    {0,8,9},//»¢Ï®
    {0,11,12},//Âä·ï´¸
    {0,31,32},//Ê¥È­Á¬»÷
    {0,43,44},//´¿°×Ö®ÈÐ
    {0,4,46}, //¼«ËÙì«·çÈ­
    //{0,2,59}, //¸©³å
    //{0,3,60}, //°Ú¶¯
    {0,61,62}, //Ö±È­³å»÷
    {0,64,65}, //¶ñÄ§Ö®ÊÖ
    {0,49,71}, //¿ñÂÒ´·´ò
    {0,41,72}, //ÐÇÂä´ò
    {0,77,79}, //Ë²È­
    {0,78,80}, //´ÌÈ­³å»÷
    {0,38,04}, //ÆÆÄ§·û
    {0,85,95}, //¼²·ç´ò
    {0,99,102}, //ÉýÌìÕó
    {0,111,112}, //¶Ï¿Õ´¸»÷

    {1,108, -1},//Ê¥¹âÁðÁ§Ëé
    {1,109, -1},//Ë«×ÓÇß¶Ü
    {2,103, -1},//´ÌÈ­¿ñ»÷
    {2,104, -1},//ÆÆ»ê×éºÏÈ­
    {3,105, -1},//¿ñ±©´¸»÷
    {3,110, -1},//Ê½ÉñÕæÐþÎä
};

void __fastcall hookCNPriest__setEnableCancelSkill_C71E00(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!*((BYTE*)thisP + 0x4F73))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);

    if (CNRDObject__isGrowType_848D10(thisP, 2)) {
        if (!RBYTE(thisP, 0x3C04)) {
            setCancelSKillEnable(thisP, 2, 59, isEnable);
            setCancelSKillEnable(thisP, 3, 60, isEnable);
        }
        else {
            goto check;
        }
    }
    else {
        check:
        setCancelSKillEnable(thisP, 1, 6, isEnable);
    }

    for (short i = 0, *p; i < sizeof(CNPriestSkill) / (3 * sizeof(short)); ++i) {
        p = CNPriestSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }
}


static short CNThiefSkill[][3] = {
    {0,1,10},//Ïè»÷
    {0,3,11},//»¡¹âÉÁ
    {0,4,12},//¼²¿ÕÌ¤
    {0,5,13},//ÑæÈÐ
    {0,7,14},//Ó°Ï®
    {0,8,15}, //ÌìÖï
    {0,16,17}, //¾øÉ±Õ¶
    {0,19,20}, //¼²³Û

    {0,27,28}, //Ë«ÈÐ´©´Ì
    {0,31,32}, //½£ÈÐ·ç±©
    {0,41,42}, //ÐýÈÐ
    {0,45,46}, //À×¹âÈÐÓ°
    {0,47,48}, //¾øÃüË²ÓüÉ±

    {0,44,65}, //²à²½
    {0,24,66}, //ÊÖÀï½£
    {0,33,67}, //ÂÝÐý´©´Ì
    {0,34,68}, //¼²·çÂÒÎè
    {0,23,69}, //×æÖäÖ®¼ô
    {0,49,70}, //ËÀÁéÖ®Ô¹
    {0,21,71}, //°µ»ê²¨
    {0,35,72}, //ËÀÍöÖ®×¦
    {0,36,73}, //°Ù¹íÒ¹ÐÐ

    {1,75,-1}, //ÔÉÂäÂÝÐý´Ì
    {1,76,-1}, //ÐýÈÐ³å»÷
    {2,74,-1}, //ËÀÁéÖ®¸¿
    {2,77,-1}, //ÊÍ»ê°µ¾¢²¨
};

void __fastcall hookCNThief__setEnableCancelSkill_CE3530(int* thisP, int, int isEnable) {
    if (!CNRDObject__isMyControlObject_7F9EB0(thisP)) return;
    if (!((thisBCall2*)*thisP)[0x212](thisP))
        isEnable = 0;
    int growtype = thisP[0xF05];
    IRDSQRCharacter__setEnableCancelSkill_688810(thisP, isEnable);
    for (short i = 0, *p; i < sizeof(CNThiefSkill) / (3 * sizeof(short)); ++i) {
        p = CNThiefSkill[i];
        if (p[0] && p[0] != growtype) continue;
        setCancelSKillEnable(thisP, p[1], p[2], isEnable);
    }
}

void cancelSKillInit(void) {
    *(DWORD*)0x017088B0 = (int)hookCNATFighter__setEnableCancelSkill_B77610;
    *(DWORD*)0x017073B8 = (int)hookCNSwordman__setEnableCancelSkill_CA6CA0;
    *(DWORD*)0x01707E30 = (int)hookCNFighter__setEnableCancelSkill_BBD2B0;
    *(DWORD*)0x01709330 = (int)hookCNGunner__setEnableCancelSkill_BF44F0;
    *(DWORD*)0x01709DA8 = (int)hookCNMage__setEnableCancelSkill_C30950;
    *(DWORD*)0x0170B2F8 = (int)hookCNThief__setEnableCancelSkill_CE3530;
    
    //*(DWORD*)0x01709DA8 = (int)hookCNMage__setEnableCancelSkill_C30950;
    GumInterceptor* v = gum_interceptor_obtain();
    gum_interceptor_replace_fast(v, (gpointer)0x846D30, (gpointer)hookCNRDSkill__setCommonSkillCommandEnable_846D30, NULL);
    gum_interceptor_replace_fast(v, (gpointer)0xC71E00, (gpointer)hookCNPriest__setEnableCancelSkill_C71E00, NULL);
    //gum_interceptor_replace_fast(v, (gpointer)0x84A6B0, (gpointer)hookIsEnableThrow_84A6B0, (gpointer *)&IsEnableThrow_84A6B0);
    //gum_interceptor_replace_fast(v, (gpointer)0xCA6CA0, (gpointer)hookCNSwordman__setEnableCancelSkill_CA6CA0, NULL);
}