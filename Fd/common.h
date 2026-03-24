#pragma once
#include "pch.h"
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <intrin.h>
#include <unordered_set>
#include <unordered_map>

#define GameIP							L"192.168.200.131"
//#define GameIP						L"192.168.66.200"

#define MAX_LV	70
#define forceinline static __forceinline

#define EN_GM
//#define DEBUG_INFO
//#define EN_ICON_ANIM
#define EN_MULTI_PROC
#define WeaponIllusionEN

#ifdef DEBUG_INFO
#define DPRINTF(...) printf(__VA_ARGS__)  //宏打印函数定义
#define WDPRINTF(...) wprintf(__VA_ARGS__)  //宏打印函数定义
#else
#define DPRINTF(...)
#define WDPRINTF(...) 
#endif


#pragma intrinsic(_ReturnAddress)

#define Vtable(obj, pos) (*(DWORD*)(*(DWORD*)obj + pos))
#define MouseSelectUiObj                (*(DWORD *)0x01B5716C)
#define MouseSelectUiObjId              (*(DWORD *)0x01A424F0)
#define MouseClickUiObjId               (*(DWORD *)0x01A424E4)
#define MouseDoubleClickUiObjId         (*(DWORD *)0x01A424E8)


#define MouseLeftDownUiObjId            (*(DWORD *)0x01A42520)
#define MouseLastClickUiObjId           (*(DWORD *)0x01A42524)
#define ChampionMonsterKillCount        (*(DWORD *)0x01A49C50)

#define MouseSelectNWinUiObj            (*(DWORD *)0x01AF2060)
#define MouseSelectWinUiObj             (*(DWORD *)0x01AF2064)

#define MousePosX						(*(DWORD *)0x01B56504)
#define MousePosY						(*(DWORD *)0x01B56508)

#define IsTraining						(*(BYTE *)0x0215E94C)


#define CurrentUiW			640
#define CurrentUiH			480

#define GetUiWPos(cw, ow, ov)   (cw - (ow - ov))
#define GetUiHPos(ch, oh, ov)   (ch - (oh - ov))

#define TEXT_ALIGN_LEFT     0x0000
#define TEXT_ALIGN_CENTER   0x0001
#define TEXT_ALIGN_RIGHT    0x0002

#define InfoWinAlpha		130

enum GameModule{
	MODULE_NONE = -1,
	MODULE_ENTRANCE = 0,
	MODULE_ROOM_LIST = 1,
	MODULE_SELECT_DUNGEON = 2,
	MODULE_MAIN_GAME = 3,
	MODULE_PVP = 4,
	MODULE_FAIR_PVP = 5,
	MODULE_SELECT_CHANNEL = 6,
	MODULE_WARROOM = 7,
	MODULE_LOGIN = 8,
	MODULE_ASSAULT = 9,
	MODULE_DEAD_TOWER = 0x0A,
	MODULE_BLOOD_SYSTEM = 0x0B,
	MODULE_DESPAIR_TOWER = 0x0C,
	MODULE_BOSS_TOWER = 0x0D,
	MODULE_ADVANCE_ALTAR = 0x0E,
	MODULE_LOAD = 0x0F,
	MODULE_TOURNAMENT = 0x10,
	MODULE_MAX = 0x11,
	MODULE_PVP_TYPE = 0x12,
	MODULE_DUNGEON_TYPE = 0x13,
	MODULE_ALL = 0x14,
};

#define CGameModule						((*(GameModule ***)0x1A6F77C)[0x05][0xA])
#define RBYTE(ptr, pos)			(*(BYTE*)((int)ptr + pos))
#define RWORD(ptr, pos)			(*(WORD*)((int)ptr + pos))
#define RDWORD(ptr, pos)		(*(DWORD*)((int)ptr + pos))

#define WBYTE(ptr, pos, v)		(*(BYTE*)((int)ptr + pos) = v)
#define WWORD(ptr, pos, v)		(*(WORD*)((int)ptr + pos) = v)
#define WDWORD(ptr, pos, v)		(*(DWORD*)((int)ptr + pos) = v)


#define FuncBk static BYTE alignas(16)
#define ROUND_UP(x, align) (((int) (x) + (align - 1)) & ~(align - 1))
#define Naked __declspec(naked)

#define KEYVALUE_MASK   0x07


#define OBJECTTYPE_OBJECT 0x0
	#define OBJECTTYPE_COLLISION 0x1
		#define OBJECTTYPE_ACTIVE 0x11
			#define OBJECTTYPE_CHARACTER 0x111
			#define OBJECTTYPE_MONSTER 0x211
				#define OBJECTTYPE_RIDABLEOBJECT 0x1211
		#define OBJECTTYPE_PASSIVE 0x21
			#define OBJECTTYPE_ITEM 0x121
			#define OBJECTTYPE_TRAP 0x221
			#define OBJECTTYPE_BREAKABLE 0x421
		#define OBJECTTYPE_PET 0x41
		#define OBJECTTYPE_CREATURE 0x81
	#define OBJECTTYPE_DRAWONLY 0x2
		#define OBJECTTYPE_VIRTUALCHARACTER 0x12
		#define OBJECTTYPE_NPC 0x22
		#define OBJECTTYPE_DONKEY 0x42
		#define OBJECTTYPE_VIRTUALCREATURE 0x82
		#define OBJECTTYPE_DISJOINTSHOP 0x102
		#define OBJECTTYPE_VIRTUALMONSTER 0x202
		#define OBJECTTYPE_NONE_DELETE 0x402
#define OBJECTTYPE_DEFINE_END 0xF000
	




typedef int(__fastcall* thisCall)(int* thisp, int edx);
typedef int(__fastcall* thisCall1Args)(int* thisp, int edx, int a1);
typedef int(__fastcall* thisCall2Args)(int* thisp, int edx, int a1, int a2);
typedef int(__fastcall* thisCall3Args)(int* thisp, int edx, int a1, int a2, int a3);
typedef int(__fastcall* thisCall4Args)(int* thisp, int edx, int a1, int a2, int a3, int a4);
typedef int(__fastcall* thisCall5Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5);
typedef int(__fastcall* thisCall6Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5, int a6);
typedef int(__fastcall* thisCall7Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
typedef int(__fastcall* thisCall8Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
typedef int(__fastcall* thisCall9Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
typedef int(__fastcall* thisCall10Args)(int* thisp, int edx, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

typedef int(__thiscall* thisCall2)(int* thisp);
typedef float(__thiscall* thisFCall2)(int* thisp);
typedef bool(__thiscall* thisBCall2)(int* thisp);
typedef double(__thiscall* thisDCall2)(int* thisp);
typedef int(__thiscall* thisCall1Args2)(int* thisp, int a1);
typedef bool(__thiscall* thisBCall1Args2)(int* thisp, int a1);
typedef int(__thiscall* thisCall1B2)(int* thisp, BYTE a1);
typedef int(__thiscall* thisCall1W2)(int* thisp, WORD a1);
typedef int(__thiscall* thisCall1F2)(int* thisp, float a1);
typedef int(__thiscall* thisCall2Args2)(int* thisp, int a1, int a2);
typedef int(__thiscall* thisCall2ArgsF2)(int* thisp, float a1, float a2);
typedef bool(__thiscall* thisBCall2Args2)(int* thisp, int a1, int a2);
typedef float(__thiscall* thisFCall2Args2)(int* thisp, int a1, int a2);
typedef int(__thiscall* thisCall3Args2)(int* thisp, int a1, int a2, int a3);
typedef float(__thiscall* thisFCall3Args2)(int* thisp, int a1, int a2, int a3);
typedef int(__thiscall* thisCall4Args2)(int* thisp, int a1, int a2, int a3, int a4);
typedef int(__thiscall* thisCall5Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5);
typedef int(__thiscall* thisCall6Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6);
typedef int(__thiscall* thisCall7Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
typedef int(__thiscall* thisCall8Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
typedef float(__thiscall* thisFCall8Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
typedef int(__thiscall* thisCall9Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
typedef int(__thiscall* thisCall10Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
typedef int(__thiscall* thisCall11Args2)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
typedef int(__thiscall* thisCall14Args2)(int*, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
typedef int(__thiscall* thisCall15Args2)(int*, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
typedef int(__stdcall* stdCall)(void);
typedef int(__stdcall* stdCall1)(int);
typedef int(__stdcall* stdCall2)(int, int);
typedef int(__stdcall* stdCall3)(int, int, int);
typedef int(__stdcall* stdCall4)(int, int, int, int);
typedef int(__stdcall* stdCall5)(int, int, int, int, int);
typedef bool(__cdecl* cdeclCallB)(void);
typedef int(__cdecl* cdeclCall)(void);
typedef int(__cdecl* cdeclCall1)(int);
typedef int(__cdecl* cdeclCall2)(int, int);
typedef bool(__cdecl* cdeclCallB2)(int, int);
typedef double(__cdecl* cdeclDCall2)(int, int);
typedef int(__cdecl* cdeclCall3)(int, int, int);
typedef int(__cdecl* cdeclCall4)(int, int, int, int);
typedef int(__cdecl* cdeclCall5)(int, int, int, int, int);
typedef int(__cdecl* cdeclCall6)(int, int, int, int, int, int);
typedef int(__cdecl* cdeclCall8)(int, int, int, int, int, int, int, int);
typedef int(__cdecl* cdeclCall11)(int, int, int, int, int, int, int, int, int, int, int);
typedef int(__thiscall* thisCall12Type1)(int*, int, int, int*, int, int, int, int, int, int, int, int, int);

typedef int(__cdecl* cmdRecvProc)(int, int, int, int);
typedef int(*notiRecvProc)(int, int, int);

typedef int(__thiscall* thisCallType1)(int* thisp, int a1, int a2, int a3, float, float, float, int, float, float);
typedef int(__thiscall* thisCallType2)(int* thisp, double a1);
typedef int(__thiscall* thisCallType3)(int* thisp, int x, int y, int img, int, int, int, int);
typedef int(__thiscall* initPopupWinBaseCall)(int* thisp, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

typedef struct {
	int StrInfo[8];
	int color1;
	int color2;
	int color3;
	int color4;
}GameTextInfo;
typedef int(__thiscall* thisCallType4)(int* thisp, GameTextInfo info);



#define TimeGetTime						(*(stdCall*)0x155A588)

extern cdeclCall4 setGameCanvasSize_6FD880;
extern cdeclCall resetGameCanvasSize_6FD8D0;

extern thisCall5Args2 drawIcon_7B6D30 ;
extern thisCall3Args2 drawImgByXY_11B3950 ;
extern thisCall2Args2 drawIconSlot_78BCD0 ;
extern thisCall2Args2 drawIconImg_7B5AA0 ;
extern thisCall2Args2 drawIconBoard_7B5E90 ;
extern thisCall2Args2 drawIconLock_7B5DE0 ;
extern thisCall2Args2 drawIconRandomOption_789F40 ;
extern thisCall1Args2 getImageByPos_11B4BD0 ;
extern cdeclCall1 newUiComponent_11B0380 ;
extern cdeclCall1 delUiComponent_11B03C0 ;
extern thisCall3Args2 setUiComponentPos_11BEAD0 ;
extern thisCall1Args2 setUiComponentVisable_11BE610 ;
extern thisCall1Args2 setUiComponentEnable_11BE350 ;
extern thisCall2Args2 setUiComponentSize_11BE370 ;
extern thisCall1Args2 addUiComponentChild_11BF330 ;
extern thisCall1Args2 delUiComponentChild_11BF7F0;
extern thisCall1Args2 setUiComponentParent_11BE4A0;
extern thisCall2 getUiComponentParent_9405E0;
extern thisCall2 initUiComponent_11BEF80 ;
extern thisCall3Args2 loadAniObjByPath_109A4E0 ;
extern thisCall2 CNRDAnimation__Proc_109C4C0 ;
extern thisCall5Args2 CNRDAnimation__Draw_1096580 ;
extern thisCall1Args2 CNRDAnimation__Reset_109B330 ;
extern thisCall1Args2 CNRDAnimation__setEnd_403A30 ;
extern thisCall1Args2 CNRDAnimation__setLoop_44E6E0 ;
extern thisCall4Args2 CNRDAnimation__setRGBA_108EF70;
extern thisCall2 CNRDAnimation__GetCurrentFrame_43F3F0 ;
extern thisCall2 CNRDAnimation__getRealImageSize_44E720 ;
extern thisCall2 CNRDAnimation__getRangeLoopCount_5AB9E0 ;
extern thisBCall2 CNRDAnimation__isLoop_5AB9D0;

extern thisCall2 delAnim_1098D30 ;
extern thisCall isOpenSlot_785010 ;
extern thisCall refreshFacade_8094D0 ;
extern thisCall1Args getEquimObjById_1135B50 ;
extern thisCall7Args setAvatorById_811D90 ;
extern thisCall9Args setFacade_80A220 ;
extern thisCall2Args drawCopyAvatorIcon_978200 ;
extern thisCall2Args drawCopyAvatorIconImg_978230 ;
extern thisCall1Args2 loadImgFile_11BD5D0 ;
extern thisCall1Args drawAvatorCopyName_F4B3B0 ;
extern thisCall1Args setClearAvatorCopyId_9787C0 ;
extern thisCall cleanClearAvatorCopyId_978770 ;
extern thisCall1Args sub_7999A0 ;
extern thisCall1Args sub_9783A0 ;
extern thisCall1Args refreshCopyFacadeMotion_82FEF0 ;
extern thisCall1Args refreshCopyFacadeStand_857240 ;
extern thisCall isClearAvator_7841F0 ;

extern thisCall2Args2 sub_410030;
extern thisCall5Args2 DrawText_F5F080;
extern thisCallType1 drawImgByXY2_11B41E0;
extern thisCall1Args sub_684E90;
extern cdeclCall1 getEquimGradeColor_7B4F80;
extern thisCall1Args drawWeightInfoText_F44A30;
extern cdeclCall1 PacketBuf_get_short;
extern cdeclCall1 PacketBuf_get_byte;
extern cdeclCall1 PacketBuf_get_int;
extern cdeclCall1 PacketBuf_get_binary;

extern thisCall1Args2 Banner__getItemBySlot_7B9CE0;
extern thisCall1Args2 Banner__findItemIndex_7B9F40;
extern thisCall2 RandomOption__get_packet_random_option_7C7EB0;
extern cdeclCall1 getBannerObjByIndex_766200;
extern cdeclCall3 makeEquimObj_97B8F0;
extern thisCall procTownAvatorExpandAni_809FC0;
extern thisCall getEType_784570;
extern thisCall1Args getPvfObjById_1135B50;
extern thisCall1Args getExpandAni_1262260;
extern thisCall getPvfEqiumObj_7889C0;
extern cdeclCall1 new_013D6B1A;
extern cdeclCall1 delete_013D5B27;
extern thisCall2Args sub_4440C0;
extern thisCall1Args setWeaponSound_4440F0;
extern thisCall2Args2 decrypt_11A0DE0;
extern thisCall getSpectrumDuration_7844D0;
extern thisCall ItemInventoryWin__Proc_6C2050;
extern thisCall InventoryItemSubWin__Proc_6C07D0;
extern thisCall1Args getRClickDownGridPos;
extern thisCall1Args getRClickGridObj;
extern thisBCall2Args2 IsKeyDown_11CBC60;
extern thisCall3Args2 showWindows;
extern thisCall2Args2 ItemInventoryWin__switchBanner_6C1710;
extern thisCall1Args2 ItemInventoryWin__switchSubWinTag_6BD9D0;
extern thisCall2Args2 sub_6BDB00;
extern thisCall2Args2 sub_6BDA40;
extern thisCall2Args2 sub_6BDA80;
extern thisCall2Args2 sub_6BDA60;
extern thisCall2Args2 ItemInventoryWin__OnOpen_6C12F0;
extern cmdRecvProc Cmd204RecvProc;
extern thisCall1Args drawInfoWinSlotInfo_F5A370;
extern thisCall1Args drawAvatorBaseInfoText_F5DE80;
extern thisCall1Args drawSkillLimitInfoText_F467C0;
extern thisCall2Args LoadFile_11CAFB0;
extern cdeclCall1 checkGmCmd_95B0A0;
extern thisCall2Args sub_8162C0;
extern thisCall2 listInit_440820;
extern thisCall1Args2 listPush_6FE170;
extern thisCall2 getWeaponSubType_8524C0;
extern thisCall1Args2 getCameraPosX_7D6990;
extern thisCall1Args2 getCameraPosY_7D69F0;
extern thisCall2 getMapMaxWight_7D74C0;
extern thisCall2 getMapMaxHeight_7D7510;
extern thisCall2 CNRDStage_proc_8F10A0;
extern cdeclCall getCNModule_706410;
extern thisCall2Args isGateMap_1113A10;
extern thisCall1Args drawSelectCharac_11039F0;
extern thisCall1Args drawSelectDungeon_11250F0;
extern thisCall3Args sub_8D0AF0;
extern thisCall1Args getFramePos_6FD350;
extern thisCall7Args sub_1093580;
extern thisCall2Args drawMapBgAni_7D7F90;
extern thisCall2Args getZoomMapXPosByWinXPos_8A7A40;
extern thisCall2Args getWinCoordXByMapCoordX_8A79A0;
extern thisCall4Args getWinCoordYByMapCoordY_8A79E0;
extern thisCall1Args2 BasePopupWin__ProcDraw_EF7E20;
extern thisCall1Args BasePopupWin__Destructor_EF0FF0;
extern thisCall BasePopupWin__Proc_EFA900;
extern thisCall BasePopupWin__Proc_1068130;
extern thisCall2Args BasePopupWin__OnOpen_1069070;
extern thisCall2 BasePopupWin__setCenterPos_EF63A0;
extern thisCall3Args2 BasePopupWin__setPos_EF63E0;
extern thisCall1Args2 drawTextStart_12115B0;
extern thisCall4Args2 drawText_1211C30 ;
extern thisCall2 drawTextEnd_12115D0 ;

extern thisCall2Args sub_545A10;
extern thisCall1Args sub_411F20;
extern initPopupWinBaseCall initPopupWinBase_1069120;
extern cdeclCall2 makeWin_F139A0;

extern thisCall3Args2 showNavigationWin_E7AC30;
extern thisCall2Args2 closeNavigationWin_E706E0;
extern thisCall2Args2 findWinById_E72160;
extern thisBCall1Args2 isWinShowing_E71770;
extern thisCall3Args2 showWin_E77470;
extern thisCall3Args2 closeWin_E745B0;
extern thisCall1Args2 closeWinObj_E742C0;
extern thisBCall2 IControl__IsClick_11BDFC0;
extern thisBCall2 IControl__IsOver_11BE020;
extern thisBCall2 IControl__IsOverOrClick_11BE040;
extern thisBCall2 IControl__IsLBDown_11BE0F0;
extern thisBCall2 IControl__IsEnable_E6E6C0;
extern thisBCall2 IControl__IsVisible_92CFE0;

extern thisCall7Args initBtn_11C54C0;
extern thisCall1Args addBtnToNavigationWin_11E1810;

extern cdeclCall getConfigMgr_4E2630;
extern thisCall1Args2 getKeyMapValue_4DCDD0;
extern thisCall1Args2 GameStrDup_411F20;

extern cdeclCall4 playSound_766160;
extern thisCall9Args2 BasePopupWin__setTitle_EFA040;
extern thisCall1Args2 BasePopupWin__setWinType_EF5F60;
extern thisCall2Args2 BasePopupWin__setWinSize_EF95A0;
extern thisCall2 BasePopupWin__getPosX_EF65C0;
extern thisCall2 BasePopupWin__getPosY_EF65D0;
extern thisCall2 BasePopupWin__getWinWidth_EF5E60;
extern thisCall2 BasePopupWin__getWinHeight_EF5E90;
extern thisCall2Args2 BaseWin__Constructor_545A10;
extern thisCall2 BaseWin__Destructor_545CB0;
extern thisCall2Args2 setQuestDetailData_ECCBF0;
extern thisCall1Args2 setEventQuestDetailData_EC58F0;
extern cdeclCall4 getLinearValue_11B98C0;
extern thisCall3Args2 innerDrawImg_11DB180;
extern thisCall12Type1 innerDrawImg2_11DB510;

extern thisCall2 UiMgr__init_E84540;

extern thisCall1Args2 getPreloadImg_11BB1B0;
extern thisCall2 getDungeonObj_75C610;
extern thisCall2 getMapMaxX_220EAE1;
extern thisCall2 getMapMaxY_21F7021;
extern thisCall2Args2 getMapType_217DD2A;

extern cdeclCall1 ScanInt_1223660;
extern thisCall1Args2 TagLayout__getTagItemObjByIdx_11C0830;
extern thisCall1Args2 TagLayout__setCurrentTag_11C19C0;
extern thisCall2 TextFormat__init_11C9510;

#define TextView_AlignLeft		0
#define TextView_AlignCenter	1
#define TextView_AlignRight		2
extern thisCall2Args2 ScrollTextView__Constructor_11CCF60;
extern thisCall1Args2 ScrollTextView__setTextColor_11CCD30;
extern thisCall1Args2 ScrollTextView__setTextFont_11CCDF0;
extern thisCall1Args2 ScrollTextView__setMaxShowLine_11CCCB0;
extern thisCall1Args2 ScrollTextView__setEndLineNum_11CCD10;
extern thisCall1Args2 ScrollTextView_setTextAlign_296E83A;
extern thisCall1Args2 ScrollTextView__delete_11CCB90;
extern thisCall1Args2 ScrollTextView__setParent_11CCCF0;
extern thisCall2Args2 ScrollTextView__setText_11CCBB0;
extern thisCall2 ScrollTextView__initScrollCtrler_11CD030;
extern thisCall2 TextView__getTextLineNum_11FA750;
extern thisCall2 TextView__getMaxShowLine_541070;
extern thisCall1Args2 TextViewCtrl__setStartPos_11FBC80;
extern thisCall2 TextViewCtrl__getMainControl_11FBCD0;

extern thisCall1Args2 GameVectorP__push_back_138A200;

extern thisCall2 GameVector1__Constructor_458350;
extern thisCall2 GameVector1__Destructor_76D310;
extern thisCall1Args2 GameVector1__PushBack_493770;
extern thisCall1Args2 GameVector1__PopBack_C34BF0;
extern thisCall1Args2 GameVector__end_7C4340;
extern thisCall1Args2 GameVector__begin_1176170;
extern thisCall1Args2 OldTagLayout__setCurrentIdx_11D4C70;
extern thisCall2 OldTagLayout__getCurrentIdx_11DD050;

extern thisCall2 GetXPos_42FF60;
extern thisCall2 GetYPos_11BE300;
extern cdeclCallB2 sq_IsKeyDown_5AFB50;
extern cdeclCall1 getNpcObjByIdx_90C950;

extern thisCall2 CNRDObject__isMyControlObject_7F9EB0;
extern thisCall1Args2 CNRDObject__isGrowType_848D10;
extern thisCall1Args2 CNRDObject__getSkillObj_84B100;
extern thisCall2Args2 CNRDObject__setSkillEnableCancelById_847400;
extern thisCall1Args2 CNRDSkill__setCommandEnable_910D90;
extern thisCall2Args2 CNRDSkill__getMaxLv_90DC40;
extern thisCall1Args2 IRDSQRCharacter__setEnableCancelSkill_688810;

typedef int(__thiscall* addParameterFn)(int* thisp, int a1, int a2, float a3);
extern addParameterFn CNAppendage__addParameter_989AE0;
extern thisCall2Args2 CNChangeStatusAppendage__Constructor_43DC00;
extern thisCall8Args2 CNChangeStatusAppendage__AppendAppendage_9879B0;
extern thisCall4Args2 IRDAppendage__setAppendCauseSkill_9321A0;
extern thisCall2Args2 CNRDSkill__getStaticData_911930;
extern thisFCall8Args2 CNRDSkill__getLevelInfo_911B90;
extern thisFCall2Args2 CNRDSkill__getSkillCurLevelInfo_9129D0;
extern thisCall2Args2 CNRDSkill__getDataCurrentBonusRateByIdx_9138C0;
extern thisCall1Args2 CNObject__getSkillLevel_84EE40;
extern thisCall2Args2 IRDSQRCharacter__procPassiveSkill_6885D0;
extern thisCall1Args2 GetSquirrelAppendage_827F80;
extern thisCall1Args2 sq_getChangeStatus_9D5F30;
extern thisCall7Args2 sq_AddChangeStatusAppendageID_9D6CE0;
extern thisCall7Args2 sq_AddChangeStatus_9D6340;
extern cdeclCall6 sq_AppendAppendage_9DB8A0;
extern thisCall2 getCharacPhysicalDefense_4C1A60;
extern thisCall2 getCharacMagicalDefense_4C1B20;
extern cdeclDCall2 getAbilityConvertRate_766340;
#define CharacInfoTypeBase	1
#define CharacInfoTypeTotal	3
extern thisCall1Args2 getCharacInfoBase_D10040;
extern thisCall1Args2 CNRDObject__getCustomAni_84CE20;
extern cdeclCall CNVideoSystem__getInstance_11D4460;
extern thisCall5Args2 CNVideoSystem__procDraw_11D4490;
extern thisCall2 CNVideoSystem__isPlaying_11D4160;
extern thisCall2 CNVideoSystem__isPrepared_11D4120;
extern thisCallType2 CNVideoSystem__seek_11D4230;
extern thisCall2 CNVideoSystem__stop_11D4200;
extern thisCall1Args2 CNVideoSystem__prepare_11D4650;


extern thisCall2Args2 encrypt_11A0930;
extern thisCall1Args2 cryptSetValue_406860;
extern thisCall1Args2 getLevelDataKey_90DEC0;

extern thisCall2 CNTimer__Init_11BA940;
extern thisCall2 CNTimer__Reset_11BA3F0;
extern thisCall2 CNTimer__Get_11BA640;
extern thisCall2 CNTimer__Suspend_11BAB70;
extern thisCall1Args CNTimer__SetEnable_11BA430;
extern thisCall2Args2 CNTimer__Start_11BAA10;
extern thisBCall2 CNTimer__IsTime_11BA760;
extern thisCall2 CNTimer__IsSuspend_11BA510;
extern thisCall2 CNTimer__IsStart_11BA4E0;
extern thisCall2 CNTimer__IsEnable_11BA4B0;

extern thisBCall1Args2 QuestMgr__isFinishQuest_4FDC00;

extern thisCall1Args2 sq_SetCurrentAttackPower_BB28E0 ;
extern thisCall1Args2 sq_SetCurrentAttackBonusRate_B70940 ;

extern thisCall2 CNRDPassiveObject__getCurrentAttackInfo_442C60 ;
extern thisCall1Args2 CNRDPassiveObject__setCurrentAttackInfo_805030 ;
extern thisCall2 CNRDPassiveObject__getTopCharacter_5B70E0 ;
extern thisCall2 CNRDPassiveObject__getParent_5B6E10 ;
extern thisCall2 CNRDPassiveObject__getDefaultAttackInfo_5B6F50 ;
extern thisCall2 CNRDPassiveObject__getObjectIndex_5B6D20 ;
extern thisCall2 CNRDPassiveObject__getPassiveObjectIndex_5ABA70 ;

extern thisCall2 sq_StartWrite_BB16F0 ;
extern thisCall1B2 sq_WriteBool_67E850 ;
extern thisCall1F2 sq_WriteFloat_BB2B20 ;
extern thisCall1W2 sq_WriteWord_BB2B50 ;
extern thisCall1Args2 sq_WriteDword_67E870 ;
extern thisCall5Args2 sq_sendCreatePassiveObjectPacket_B6A990;
extern cdeclCall6 sq_SendCreatePassiveObjectPacketPos_5AF750;
extern thisCall14Args2 CNRDObject__createPassiveObj_878470;
extern thisCall15Args2 CNRDObject__createPassiveObjPos_879320;

extern thisCall2 BaseSubWin__GetPosX_E86310;
extern thisCall2 BaseSubWin__GetPosY_E86350;
extern thisCallType3 BaseSubWin__DrawIcon_E86390;
extern thisCall2 BaseBtn__Proc_11C35D0;
extern cdeclCall2 drawMouseOverGridImg_7B5000;

extern thisCall1Args2 makePkg_1132930;
extern thisCall2Args2 PkgPushBinary_1132A20;
extern thisCall2Args2 PkgPushBinary_11331B0;
extern thisCall1B2 PkgPushByte_1133120;
extern thisCall1W2 PkgPushShort_1133150;
extern thisCall1Args2 PkgPushStr_1133220;
extern thisCall1Args2 PkgPushWStr_11332B0;
extern thisCall1Args2 PkgPushInt_1133180;
extern stdCall sendPkg_1132A90;


extern cdeclCall1 PacketBuf__get_binary_1134620;
extern cdeclCall3 PacketBuf__get_str_11346F0;
extern cdeclCall1 PacketBuf__get_byte_11B9470;
extern cdeclCall1 PacketBuf__get_short_11B94A0;
extern cdeclCall1 PacketBuf__get_int_11B94D0;

extern cdeclCall1 GetGameText_122B260;
extern stdCall1 showSettingWinByIdx_4F2220;

extern thisCall2Args2 BaseBtn__setTextEnable_11C2B70;
extern thisCallType4 BaseBtn__setText_11C49F0;


extern cdeclCall1 getObjGradeById_7B4F40;
extern cdeclCall1 getObjIconImgById_7B4DE0;
extern cdeclCall1 getObjNameById_7B4D60;

extern thisCall2 getCharacInfo_925000;
extern cdeclCall5 RTDynamicCast_13D76DF;

extern thisCall2 CNModule__getGameModule_75C470;
extern thisCall2 listInit1_1389550;
extern thisCall2 initEncryptKey_11A2470;

extern thisCall2 getNpcId_7F8CA0;

extern FILE* logDumpFd;


enum CONVERT_TABLE_TYPE {
	CONVERT_TABLE_TYPE_DAMAGE = 0x0,
	CONVERT_TABLE_TYPE_DEFENSE = 0x1,
	CONVERT_TABLE_TYPE_HP = 0x2,
	CONVERT_TABLE_TYPE_PHYSICAL_ATTACK = 0x3,
	CONVERT_TABLE_TYPE_PHYSICAL_DEFENSE = 0x4,
	CONVERT_TABLE_TYPE_MAGICAL_ATTACK = 0x5,
	CONVERT_TABLE_TYPE_MAGICAL_DEFENSE = 0x6,
	CONVERT_TABLE_TYPE_PHYSICAL_ABSOLUTE_DAMAGE = 0x7,
	CONVERT_TABLE_TYPE_PHYSICAL_DAMAGE_REDUCE = 0x8,
	CONVERT_TABLE_TYPE_MAGICAL_ABSOLUTE_DAMAGE = 0x9,
	CONVERT_TABLE_TYPE_MAGICAL_DAMAGE_REDUCE = 0x0A,
	CONVERT_TABLE_TYPE_ACTIVESTATUS_DAMAGE_REDUCE = 0x0B,
	CONVERT_TABLE_TYPE_MP = 0x0C,
	CONVERT_TABLE_TYPE_SKILL_POWER = 0x0D,
	CONVERT_TABLE_TYPE_MAX = 0x0E,
};


enum CHANGE_STATUS_TYPE {
	CHANGE_STATUS_TYPE_PHYSICAL_ATTACK = 0x0,
	CHANGE_STATUS_TYPE_MAGICAL_ATTACK = 0x1,
	CHANGE_STATUS_TYPE_MAGICAL_DEFENSE = 0x2,
	CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE = 0x3,
	CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK = 0x4,
	CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE = 0x5,
	CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS = 0x6,
	CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS = 0x7,
	CHANGE_STATUS_TYPE_JUMP_POWER = 0x8,
	CHANGE_STATUS_TYPE_JUMP_SPEED_RATE = 0x9,
	CHANGE_STATUS_TYPE_ATTACK_SPEED = 0x0A,
	CHANGE_STATUS_TYPE_MOVE_SPEED = 0x0B,
	CHANGE_STATUS_TYPE_CAST_SPEED = 0x0C,
	CHANGE_STATUS_TYPE_HP_MAX = 0x0D,
	CHANGE_STATUS_TYPE_HP_REGEN_RATE = 0x0E,
	CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE = 0x0F,
	CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE = 0x10,
	CHANGE_STATUS_TYPE_PHYSICAL_BACK_ATTACK_CRITICAL = 0x11,
	CHANGE_STATUS_TYPE_MAGICAL_BACK_ATTACK_CRITICAL = 0x12,
	CHANGE_STATUS_TYPE_CRITICAL_TOLERANCE_RATE = 0x13,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_FIRE = 0x14,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_WATER = 0x15,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_DARK = 0x16,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_LIGHT = 0x17,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_ALL = 0x18,
	CHANGE_STATUS_TYPE_ELEMENT_TOLERANCE_ZERO = 0x19,
	CHANGE_STATUS_TYPE_ACTIVESTATUS_TOLERANCE_ALL = 0x1A,
	CHANGE_STATUS_TYPE_ACTIVEPROPERTY_STUCK = 0x1B,
	CHANGE_STATUS_TYPE_BACK_ATTACK_STUCK_TOLERANCE = 0x1C,
	CHANGE_STATUS_TYPE_MP_REGEN_RATE = 0x1D,
	CHANGE_STATUS_TYPE_EXTRA_SPEED_RATE = 0x1E,
	CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK = 0x1F,
	CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE = 0x20,
	CHANGE_STATUS_TYPE_STUCK = 0x21,
	CHANGE_STATUS_TYPE_HIT_RECOVERY = 0x22,
	CHANGE_STATUS_TYPE_MELEE_HIT_DELAY = 0x23,
	CAHNGE_STATUS_TYPE_EQUIPMENT_ALL_STAT = 0x24,
	CHANGE_STATUS_TYPE_CUSTOM = 0x25,
	CHANGE_STATUS_TYPE_EXP_DOUBLE = 0x26,
	CHANGE_STATUS_TYPE_EVIL_UP = 0x27,
	CHANGE_STATUS_TYPE_EVIL_DOWN = 0x28,
	CHANGE_STATUS_TYPE_RIGIDITY = 0x29,
	CHANGE_STATUS_TYPE_ELEMENT_ATTACK_FIRE = 0x2A,
	CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER = 0x2B,
	CHANGE_STATUS_TYPE_ELEMENT_ATTACK_DARK = 0x2C,
	CHANGE_STATUS_TYPE_ELEMENT_ATTACK_LIGHT = 0x2D,
	CHANGE_STATUS_TYPE_ELEMENT_ATTACK_ALL = 0x2E,
	CHANGE_STATUS_TYPE_DISEASE = 0x2F,
	CHANGE_STATUS_TYPE_MP_MAX = 0x30,
	CHANGE_STATUS_TYPE_COOLTIME_DECLINE = 0x31,
	CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE = 0x32,
	CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE = 0x33,
	CHANGE_STATUS_TYPE_BLOODWAR_GROW_ABILITY = 0x34,
	CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK = 0x35,
	CHANGE_STATUS_TYPE_ADDITIONAL_MAGICAL_GENUINE_ATTACK = 0x36,
	CHANGE_STATUS_TYPE_SUMMON_SKILL_POWER_BONUS_RATE = 0x37,
	CHANGE_STATUS_TYPE_ANTIEVIL = 0x38,
	CHANGE_STATUS_TYPE_PHYSICAL_ABSOLUTE_DAMAGE = 0x39,
	CHANGE_STATUS_GHOST_TRAIN_NO_BREATH_TIME = 0x3A,
	CHANGE_STATUS_CHARACTER_LINK = 0x3B,
	CHANGE_STATUS_GOLD_INCREASE = 0x3C,
	CHANGE_STATUS_TYPE_MAX = 0x3D,
	CHANGE_STATUS_TYPE_NULL = 0x4D,
};


int* newBtn(int* parent, int x, int y, int img, int sNormal, int sSelect, int sClick, int sDisable);
int* newUiComponent(int* parent, int x, int y);

int addCloseBtn(int* win, int x, int y);
void setRandView(int xPos, int yPos);

void initOld70Hub(int mapX, int mapY);
void initOld70Hub_delay(int* thisP, int mapX, int x, int y);
int* getMiniMapBtn(void);
int* getHellWinCtlbtn(void);

void common_CNTownModule_onEnterModuleCb(int* thisP, int a2);
void common_CNTownModule__onExitModuleCb(int* thisP, int a2);
void common_CNMainGameModule_onEnterModuleCb(int* thisP, int a2);
void common_CNMainGameModule_onExitModuleCb(int* thisP, int a2);
void common_OnReqHumanCertify(void);

void drawTagLine(int* WindowCommonImg, int x, int y, int w);

int my_inet_aton(const char* cp, DWORD* inp);