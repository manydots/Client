#include "pch.h"
#include "common.h"
#include "skillCommon.h"
#include "tools.h"
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <unordered_map>
#include "oldSkillWin.h"
#include "goldSkill.h"
#include "frida-gum.h"

cdeclCall4 setGameCanvasSize_6FD880 = (cdeclCall4)0x6FD880;
cdeclCall resetGameCanvasSize_6FD8D0 = (cdeclCall)0x6FD8D0;

thisCall5Args2 drawIcon_7B6D30 = (thisCall5Args2)0x7B6D30;
thisCall3Args2 drawImgByXY_11B3950 = (thisCall3Args2)0x11B3950;
thisCall2Args2 drawIconSlot_78BCD0 = (thisCall2Args2)0x78BCD0;
thisCall2Args2 drawIconImg_7B5AA0 = (thisCall2Args2)0x7B5AA0;
thisCall2Args2 drawIconBoard_7B5E90 = (thisCall2Args2)0x7B5E90;
thisCall2Args2 drawIconLock_7B5DE0 = (thisCall2Args2)0x7B5DE0;
thisCall2Args2 drawIconRandomOption_789F40 = (thisCall2Args2)0x789F40;
thisCall1Args2 getImageByPos_11B4BD0 = (thisCall1Args2)0x11B4BD0;
thisCall3Args2 innerDrawImg_11DB180 = (thisCall3Args2)0x11DB180;
thisCall12Type1 innerDrawImg2_11DB510 = (thisCall12Type1)0x11DB510;

cdeclCall1 newUiComponent_11B0380 = (cdeclCall1)0x11B0380;
cdeclCall1 delUiComponent_11B03C0 = (cdeclCall1)0x11B03C0;
thisCall3Args2 setUiComponentPos_11BEAD0 = (thisCall3Args2)0x11BEAD0;
thisCall1Args2 setUiComponentVisable_11BE610 = (thisCall1Args2)0x11BE610;
thisCall1Args2 setUiComponentEnable_11BE350 = (thisCall1Args2)0x11BE350;
thisCall2Args2 setUiComponentSize_11BE370 = (thisCall2Args2)0x11BE370;
thisCall1Args2 addUiComponentChild_11BF330 = (thisCall1Args2)0x11BF330;
thisCall1Args2 delUiComponentChild_11BF7F0 = (thisCall1Args2)0x11BF7F0;
thisCall1Args2 setUiComponentParent_11BE4A0 = (thisCall1Args2)0x11BE4A0;//this[17]
thisCall2 getUiComponentParent_9405E0 = (thisCall2)0x9405E0;//this[17]
thisCall2 initUiComponent_11BEF80 = (thisCall2)0x11BEF80;

thisCall3Args2 loadAniObjByPath_109A4E0 = (thisCall3Args2)0x109A4E0;
thisCall2 CNRDAnimation__Proc_109C4C0 = (thisCall2)0x109C4C0;
thisCall5Args2 CNRDAnimation__Draw_1096580 = (thisCall5Args2)0x1096580;
thisCall1Args2 CNRDAnimation__Reset_109B330 = (thisCall1Args2)0x109B330;
thisCall1Args2 CNRDAnimation__setEnd_403A30 = (thisCall1Args2)0x403A30;
thisCall1Args2 CNRDAnimation__setLoop_44E6E0 = (thisCall1Args2)0x44E6E0;
thisCall4Args2 CNRDAnimation__setRGBA_108EF70 = (thisCall4Args2)0x108EF70;
thisCall2 CNRDAnimation__GetCurrentFrame_43F3F0 = (thisCall2)0x43F3F0;
thisCall2 CNRDAnimation__getRealImageSize_44E720 = (thisCall2)0x44E720;
thisCall2 CNRDAnimation__getRangeLoopCount_5AB9E0 = (thisCall2)0x5AB9E0;
thisBCall2 CNRDAnimation__isLoop_5AB9D0 = (thisBCall2)0x5AB9D0;

thisCall2 delAnim_1098D30 = (thisCall2)0x1098D30;
thisCall isOpenSlot_785010 = (thisCall)0x785010;

thisCall refreshFacade_8094D0 = (thisCall)0x8094D0;
thisCall1Args getEquimObjById_1135B50 = (thisCall1Args)0x1135B50;
thisCall7Args setAvatorById_811D90 = (thisCall7Args)0x811D90;
thisCall9Args setFacade_80A220 = (thisCall9Args)0x80A220;
thisCall2Args drawCopyAvatorIcon_978200 = (thisCall2Args)0x978200;
thisCall2Args drawCopyAvatorIconImg_978230 = (thisCall2Args)0x978230;
thisCall1Args2 loadImgFile_11BD5D0 = (thisCall1Args2)0x11BD5D0;
thisCall1Args drawAvatorCopyName_F4B3B0 = (thisCall1Args)0xF4B3B0;
thisCall1Args setClearAvatorCopyId_9787C0 = (thisCall1Args)0x9787C0;
thisCall cleanClearAvatorCopyId_978770 = (thisCall)0x978770;
thisCall1Args sub_7999A0 = (thisCall1Args)0x7999A0;
thisCall1Args sub_9783A0 = (thisCall1Args)0x9783A0;
//00857240 地下城中刷新战斗状态的武器外观
thisCall1Args refreshCopyFacadeMotion_82FEF0 = (thisCall1Args)0x82FEF0;
//00857240 地下城中刷新非战斗状态的武器外观
thisCall1Args refreshCopyFacadeStand_857240 = (thisCall1Args)0x857240;
thisCall isClearAvator_7841F0 = (thisCall)0x7841F0;


thisCall2Args2 sub_410030 = (thisCall2Args2)0x410030;
thisCall5Args2 DrawText_F5F080 = (thisCall5Args2)0xF5F080;
thisCallType1 drawImgByXY2_11B41E0 = (thisCallType1)0x11B41E0;
thisCall1Args sub_684E90 = (thisCall1Args)0x00684E90;
cdeclCall1 getEquimGradeColor_7B4F80 = (cdeclCall1)0x7B4F80;
thisCall1Args drawWeightInfoText_F44A30 = (thisCall1Args)0xF44A30;

thisCall1Args2 Banner__getItemBySlot_7B9CE0 = (thisCall1Args2)0x7B9CE0;
thisCall1Args2 Banner__findItemIndex_7B9F40 = (thisCall1Args2)0x7B9F40;
thisCall2 RandomOption__get_packet_random_option_7C7EB0 = (thisCall2)0x7C7EB0;
cdeclCall1 getBannerObjByIndex_766200 = (cdeclCall1)0x766200;
cdeclCall3 makeEquimObj_97B8F0 = (cdeclCall3)0x97B8F0;
thisCall procTownAvatorExpandAni_809FC0 = (thisCall)0x809FC0;
thisCall getEType_784570 = (thisCall)0x784570;
thisCall1Args getPvfObjById_1135B50 = (thisCall1Args)0x1135B50;
thisCall1Args getExpandAni_1262260 = (thisCall1Args)0x1262260;//刷新城镇的装扮
thisCall getPvfEqiumObj_7889C0 = (thisCall)0x7889C0;
cdeclCall1 new_013D6B1A = (cdeclCall1)0x013D6B1A;
cdeclCall1 delete_013D5B27 = (cdeclCall1)0x013D5B27;
thisCall2Args sub_4440C0 = (thisCall2Args)0x4440C0;
thisCall1Args setWeaponSound_4440F0 = (thisCall1Args)0x4440F0;
thisCall2Args2 decrypt_11A0DE0 = (thisCall2Args2)0x11A0DE0;
thisCall getSpectrumDuration_7844D0 = (thisCall)0x7844D0;
thisCall ItemInventoryWin__Proc_6C2050 = (thisCall)0x6C2050;
thisCall InventoryItemSubWin__Proc_6C07D0 = (thisCall)0x6C07D0;
thisCall1Args getRClickDownGridPos = (thisCall1Args)0x11DCFD0;
thisCall1Args getRClickGridObj = (thisCall1Args)0x6BDAA0;
thisBCall2Args2 IsKeyDown_11CBC60 = (thisBCall2Args2)0x11CBC60;
thisCall3Args2 showWindows = (thisCall3Args2)0xE77470;
thisCall2Args2 ItemInventoryWin__switchBanner_6C1710 = (thisCall2Args2)0x6C1710;//切换banner 0物品栏/1时装栏/2宠物栏
thisCall1Args2 ItemInventoryWin__switchSubWinTag_6BD9D0 = (thisCall1Args2)0x6BD9D0;//切换tag0/1/2/3/4/5
thisCall2Args2 sub_6BDB00 = (thisCall2Args2)0x6BDB00;
thisCall2Args2 sub_6BDA40 = (thisCall2Args2)0x6BDA40;
thisCall2Args2 sub_6BDA80 = (thisCall2Args2)0x6BDA80;
thisCall2Args2 sub_6BDA60 = (thisCall2Args2)0x6BDA60;
thisCall2Args2 ItemInventoryWin__OnOpen_6C12F0 = (thisCall2Args2)0x6C12F0;
cmdRecvProc Cmd204RecvProc = (cmdRecvProc)0x71B7F0;
thisCall1Args drawInfoWinSlotInfo_F5A370 = (thisCall1Args)0xF5A370;
thisCall1Args drawAvatorBaseInfoText_F5DE80 = (thisCall1Args)0xF5DE80;
thisCall1Args drawSkillLimitInfoText_F467C0 = (thisCall1Args)0xF467C0;
thisCall2Args LoadFile_11CAFB0 = (thisCall2Args)0x11CAFB0;
cdeclCall1 checkGmCmd_95B0A0 = (cdeclCall1)0x95B0A0;
thisCall2Args sub_8162C0 = (thisCall2Args)0x8162C0;//刷新城镇的装扮
thisCall2 listInit_440820 = (thisCall2)0x440820;
thisCall1Args2 listPush_6FE170 = (thisCall1Args2)0x6FE170;
thisCall2 getWeaponSubType_8524C0 = (thisCall2)0x8524C0;
thisCall1Args2 getCameraPosX_7D6990 = (thisCall1Args2)0x7D6990;
thisCall1Args2 getCameraPosY_7D69F0 = (thisCall1Args2)0x7D69F0;
thisCall2 getMapMaxWight_7D74C0 = (thisCall2)0x7D74C0;
thisCall2 getMapMaxHeight_7D7510 = (thisCall2)0x7D7510;
thisCall2 CNRDStage_proc_8F10A0 = (thisCall2)0x8F10A0;
cdeclCall getCNModule_706410 = (cdeclCall)0x706410;
thisCall2Args isGateMap_1113A10 = (thisCall2Args)0x1113A10;
thisCall1Args drawSelectCharac_11039F0 = (thisCall1Args)0x11039F0;
thisCall1Args drawSelectDungeon_11250F0 = (thisCall1Args)0x11250F0;
thisCall3Args sub_8D0AF0 = (thisCall3Args)0x8D0AF0;
thisCall1Args getFramePos_6FD350 = (thisCall1Args)0x6FD350;
thisCall7Args sub_1093580 = (thisCall7Args)0x1093580;
thisCall2Args drawMapBgAni_7D7F90 = (thisCall2Args)0x7D7F90;
thisCall2Args getZoomMapXPosByWinXPos_8A7A40 = (thisCall2Args)0x8A7A40;
thisCall2Args getWinCoordXByMapCoordX_8A79A0 = (thisCall2Args)0x8A79A0;
thisCall4Args getWinCoordYByMapCoordY_8A79E0 = (thisCall4Args)0x8A79E0;
thisCall1Args2 BasePopupWin__ProcDraw_EF7E20 = (thisCall1Args2)0xEF7E20;
thisCall1Args BasePopupWin__Destructor_EF0FF0 = (thisCall1Args)0xEF0FF0;
thisCall BasePopupWin__Proc_EFA900 = (thisCall)0xEFA900;
thisCall BasePopupWin__Proc_1068130 = (thisCall)0x1068130;
thisCall2Args BasePopupWin__OnOpen_1069070 = (thisCall2Args)0x1069070;
thisCall2 BasePopupWin__setCenterPos_EF63A0 = (thisCall2)0xEF63A0;
thisCall3Args2 BasePopupWin__setPos_EF63E0 = (thisCall3Args2)0xEF63E0;
thisCall1Args2 drawTextStart_12115B0 = (thisCall1Args2)0x12115B0;
thisCall4Args2 drawText_1211C30 = (thisCall4Args2)0x1211C30;
thisCall2 drawTextEnd_12115D0 = (thisCall2)0x12115D0;

thisCall2Args sub_545A10 = (thisCall2Args)0x545A10;
thisCall1Args sub_411F20 = (thisCall1Args)0x411F20;
initPopupWinBaseCall initPopupWinBase_1069120 = (initPopupWinBaseCall)0x1069120;
cdeclCall2 makeWin_F139A0 = (cdeclCall2)0xF139A0;

thisCall3Args2 showNavigationWin_E7AC30 = (thisCall3Args2)0xE7AC30;
thisCall2Args2 closeNavigationWin_E706E0 = (thisCall2Args2)0xE706E0;
thisCall2Args2 findWinById_E72160 = (thisCall2Args2)0xE72160;
thisBCall1Args2 isWinShowing_E71770 = (thisBCall1Args2)0xE71770;
thisCall3Args2 showWin_E77470 = (thisCall3Args2)0xE77470;
thisCall3Args2 closeWin_E745B0 = (thisCall3Args2)0xE745B0;
thisCall1Args2 closeWinObj_E742C0 = (thisCall1Args2)0xE742C0;
thisBCall2 IControl__IsClick_11BDFC0 = (thisBCall2)0x11BDFC0;
thisBCall2 IControl__IsOver_11BE020 = (thisBCall2)0x11BE020;
thisBCall2 IControl__IsOverOrClick_11BE040 = (thisBCall2)0x11BE040;
thisBCall2 IControl__IsLBDown_11BE0F0 = (thisBCall2)0x11BE0F0;
thisBCall2 IControl__IsEnable_E6E6C0 = (thisBCall2)0xE6E6C0;
thisBCall2 IControl__IsVisible_92CFE0 = (thisBCall2)0x92CFE0;

thisCall7Args initBtn_11C54C0 = (thisCall7Args)0x11C54C0;
thisCall1Args addBtnToNavigationWin_11E1810 = (thisCall1Args)0x11E1810;

cdeclCall getConfigMgr_4E2630 = (cdeclCall)0x4E2630;
thisCall1Args2 getKeyMapValue_4DCDD0 = (thisCall1Args2)0x4DCDD0;
thisCall1Args2 GameStrDup_411F20 = (thisCall1Args2)0x411F20;

cdeclCall4 playSound_766160 = (cdeclCall4)0x766160;

thisCall9Args2 BasePopupWin__setTitle_EFA040 = (thisCall9Args2)0xEFA040;
thisCall2Args2 BaseWin__Constructor_545A10 = (thisCall2Args2)0x545A10;
thisCall2 BaseWin__Destructor_545CB0 = (thisCall2)0x545CB0;
thisCall1Args2 BasePopupWin__setWinType_EF5F60 = (thisCall1Args2)0xEF5F60;
thisCall2Args2 BasePopupWin__setWinSize_EF95A0 = (thisCall2Args2)0xEF95A0;
thisCall2 BasePopupWin__getPosX_EF65C0 = (thisCall2)0xEF65C0;
thisCall2 BasePopupWin__getPosY_EF65D0 = (thisCall2)0xEF65D0;
thisCall2 BasePopupWin__getWinWidth_EF5E60 = (thisCall2)0xEF5E60;
thisCall2 BasePopupWin__getWinHeight_EF5E90 = (thisCall2)0xEF5E90;
thisCall2Args2 setQuestDetailData_ECCBF0 = (thisCall2Args2)0xECCBF0;
thisCall1Args2 setEventQuestDetailData_EC58F0 = (thisCall1Args2)0xEC58F0;

cdeclCall4 getLinearValue_11B98C0 = (cdeclCall4)0x11B98C0;

thisCall2 UiMgr__init_E84540 = (thisCall2)0xE84540;

thisCall1Args2 getPreloadImg_11BB1B0 = (thisCall1Args2)0x11BB1B0;
thisCall2 getDungeonObj_75C610 = (thisCall2)0x75C610;
thisCall2 getMapMaxX_220EAE1 = (thisCall2)0x220EAE1;
thisCall2 getMapMaxY_21F7021 = (thisCall2)0x21F7021;
thisCall2Args2 getMapType_217DD2A = (thisCall2Args2)0x217DD2A;

cdeclCall1 ScanInt_1223660 = (cdeclCall1)0x1223660;

thisCall1Args2 TagLayout__getTagItemObjByIdx_11C0830 = (thisCall1Args2)0x11C0830;
thisCall1Args2 TagLayout__setCurrentTag_11C19C0 = (thisCall1Args2)0x11C19C0;
thisCall2 TextFormat__init_11C9510 = (thisCall2)0x11C9510;
thisCall1Args2 GameVectorP__push_back_138A200 = (thisCall1Args2)0x138A200;

thisCall2 GameVector1__Constructor_458350 = (thisCall2)0x458350;
thisCall1Args2 GameVector1__PushBack_493770 = (thisCall1Args2)0x493770;
thisCall1Args2 GameVector1__PopBack_C34BF0 = (thisCall1Args2)0xC34BF0;

thisCall2Args2 ScrollTextView__Constructor_11CCF60 = (thisCall2Args2)0x11CCF60;
thisCall1Args2 ScrollTextView__setTextColor_11CCD30 = (thisCall1Args2)0x11CCD30;
thisCall1Args2 ScrollTextView__setTextFont_11CCDF0 = (thisCall1Args2)0x11CCDF0;
thisCall1Args2 ScrollTextView__setMaxShowLine_11CCCB0 = (thisCall1Args2)0x11CCCB0;
thisCall1Args2 ScrollTextView__setEndLineNum_11CCD10 = (thisCall1Args2)0x11CCD10;//超出滑动控件的行数
thisCall1Args2 ScrollTextView_setTextAlign_296E83A = (thisCall1Args2)0x296E83A;
thisCall1Args2 ScrollTextView__delete_11CCB90 = (thisCall1Args2)0x11CCB90;
thisCall1Args2 ScrollTextView__setParent_11CCCF0 = (thisCall1Args2)0x11CCCF0;
thisCall2 ScrollTextView__initScrollCtrler_11CD030 = (thisCall2)0x11CD030;
thisCall2Args2 ScrollTextView__setText_11CCBB0 = (thisCall2Args2)0x11CCBB0;
thisCall2 TextView__getTextLineNum_11FA750 = (thisCall2)0x11FA750;
thisCall2 TextView__getMaxShowLine_541070 = (thisCall2)0x541070;
thisCall1Args2 TextViewCtrl__setStartPos_11FBC80 = (thisCall1Args2)0x11FBC80;
thisCall2 TextViewCtrl__getMainControl_11FBCD0 = (thisCall2)0x11FBCD0;

thisCall1Args2 GameVector__end_7C4340 = (thisCall1Args2)0x7C4340;
thisCall1Args2 GameVector__begin_1176170 = (thisCall1Args2)0x1176170;
thisCall2 GameVector1__Destructor_76D310 = (thisCall2)0x76D310;

thisCall1Args2 OldTagLayout__setCurrentIdx_11D4C70 = (thisCall1Args2)0x11D4C70;
thisCall2 OldTagLayout__getCurrentIdx_11DD050 = (thisCall2)0x11DD050;

thisCall2 GetXPos_42FF60 = (thisCall2)0x42FF60;
thisCall2 GetYPos_11BE300 = (thisCall2)0x11BE300;
cdeclCallB2 sq_IsKeyDown_5AFB50 = (cdeclCallB2)0x5AFB50;
cdeclCall1 getNpcObjByIdx_90C950 = (cdeclCall1)0x90C950;

thisCall2 CNRDObject__isMyControlObject_7F9EB0 = (thisCall2)0x7F9EB0;
thisCall1Args2 CNRDObject__isGrowType_848D10 = (thisCall1Args2)0x848D10;
thisCall1Args2 CNRDObject__getSkillObj_84B100 = (thisCall1Args2)0x84B100;
thisCall2Args2 CNRDObject__setSkillEnableCancelById_847400 = (thisCall2Args2)0x847400;
thisCall1Args2 CNRDSkill__setCommandEnable_910D90 = (thisCall1Args2)0x910D90;
thisCall2Args2 CNRDSkill__getMaxLv_90DC40 = (thisCall2Args2)0x90DC40;
thisCall1Args2 IRDSQRCharacter__setEnableCancelSkill_688810 = (thisCall1Args2)0x688810;
addParameterFn CNAppendage__addParameter_989AE0 = (addParameterFn)0x989AE0;
thisCall2Args2 CNChangeStatusAppendage__Constructor_43DC00 = (thisCall2Args2)0x43DC00;
thisCall8Args2 CNChangeStatusAppendage__AppendAppendage_9879B0 = (thisCall8Args2)0x9879B0;

thisCall4Args2 IRDAppendage__setAppendCauseSkill_9321A0 = (thisCall4Args2)0x9321A0;

thisCall2Args2 CNRDSkill__getStaticData_911930 = (thisCall2Args2)0x911930;
thisFCall8Args2 CNRDSkill__getLevelInfo_911B90 = (thisFCall8Args2)0x911B90;
thisFCall2Args2 CNRDSkill__getSkillCurLevelInfo_9129D0 = (thisFCall2Args2)0x9129D0;
thisCall2Args2 CNRDSkill__getDataCurrentBonusRateByIdx_9138C0 = (thisCall2Args2)0x9138C0;
thisCall1Args2 CNObject__getSkillLevel_84EE40 = (thisCall1Args2)0x84EE40;
thisCall2Args2 IRDSQRCharacter__procPassiveSkill_6885D0 = (thisCall2Args2)0x6885D0;
thisCall1Args2 GetSquirrelAppendage_827F80 = (thisCall1Args2)0x827F80;
thisCall1Args2 sq_getChangeStatus_9D5F30 = (thisCall1Args2)0x9D5F30;
thisCall7Args2 sq_AddChangeStatusAppendageID_9D6CE0 = (thisCall7Args2)0x9D6CE0;
thisCall7Args2 sq_AddChangeStatus_9D6340 = (thisCall7Args2)0x9D6340;

cdeclCall6 sq_AppendAppendage_9DB8A0 = (cdeclCall6)0x9DB8A0;

thisCall2 getCharacPhysicalDefense_4C1A60 = (thisCall2)0x4C1A60;
thisCall2 getCharacMagicalDefense_4C1B20 = (thisCall2)0x4C1B20;
cdeclDCall2 getAbilityConvertRate_766340 = (cdeclDCall2)0x766340;

thisCall1Args2 getCharacInfoBase_D10040 = (thisCall1Args2)0xD10040;
thisCall1Args2 CNRDObject__getCustomAni_84CE20 = (thisCall1Args2)0x84CE20;
cdeclCall CNVideoSystem__getInstance_11D4460 = (cdeclCall)0x11D4460;
thisCall5Args2 CNVideoSystem__procDraw_11D4490 = (thisCall5Args2)0x11D4490;
thisCall2 CNVideoSystem__isPlaying_11D4160 = (thisCall2)0x11D4160;
thisCall2 CNVideoSystem__isPrepared_11D4120 = (thisCall2)0x11D4120;
thisCallType2 CNVideoSystem__seek_11D4230 = (thisCallType2)0x11D4230;
thisCall2 CNVideoSystem__stop_11D4200 = (thisCall2)0x11D4200;
thisCall1Args2 CNVideoSystem__prepare_11D4650 = (thisCall1Args2)0x11D4650;


thisCall2Args2 encrypt_11A0930 = (thisCall2Args2)0x11A0930;
thisCall1Args2 cryptSetValue_406860 = (thisCall1Args2)0x406860;
thisCall1Args2 getLevelDataKey_90DEC0 = (thisCall1Args2)0x90DEC0;

thisCall2 CNTimer__Init_11BA940 = (thisCall2)0x11BA940;
thisCall2 CNTimer__Reset_11BA3F0 = (thisCall2)0x11BA3F0;
thisCall2 CNTimer__Get_11BA640 = (thisCall2)0x11BA640;
thisCall2 CNTimer__Suspend_11BAB70 = (thisCall2)0x11BAB70;
thisCall1Args CNTimer__SetEnable_11BA430 = (thisCall1Args)0x11BA430;
thisCall2Args2 CNTimer__Start_11BAA10 = (thisCall2Args2)0x11BAA10;
thisBCall2 CNTimer__IsTime_11BA760 = (thisBCall2)0x11BA760;
thisCall2 CNTimer__IsSuspend_11BA510 = (thisCall2)0x11BA510;
thisCall2 CNTimer__IsStart_11BA4E0 = (thisCall2)0x11BA4E0;
thisCall2 CNTimer__IsEnable_11BA4B0 = (thisCall2)0x11BA4B0;

thisBCall1Args2 QuestMgr__isFinishQuest_4FDC00 = (thisBCall1Args2)0x4FDC00;

thisCall1Args2 sq_SetCurrentAttackPower_BB28E0 = (thisCall1Args2)0xBB28E0;
thisCall1Args2 sq_SetCurrentAttackBonusRate_B70940 = (thisCall1Args2)0xB70940;

thisCall2 CNRDPassiveObject__getCurrentAttackInfo_442C60 = (thisCall2)0x442C60;
thisCall1Args2 CNRDPassiveObject__setCurrentAttackInfo_805030 = (thisCall1Args2)0x805030;

thisCall2 CNRDPassiveObject__getTopCharacter_5B70E0 = (thisCall2)0x5B70E0;
thisCall2 CNRDPassiveObject__getParent_5B6E10 = (thisCall2)0x5B6E10;
thisCall2 CNRDPassiveObject__getDefaultAttackInfo_5B6F50 = (thisCall2)0x5B6F50;
thisCall2 CNRDPassiveObject__getObjectIndex_5B6D20 = (thisCall2)0x5B6D20;
thisCall2 CNRDPassiveObject__getPassiveObjectIndex_5ABA70 = (thisCall2)0x5ABA70;

thisCall2 sq_StartWrite_BB16F0 = (thisCall2)0xBB16F0;
thisCall1B2 sq_WriteBool_67E850 = (thisCall1B2)0x67E850;
thisCall1F2 sq_WriteFloat_BB2B20 = (thisCall1F2)0xBB2B20;
thisCall1W2 sq_WriteWord_BB2B50 = (thisCall1W2)0xBB2B50;
thisCall1Args2 sq_WriteDword_67E870 = (thisCall1Args2)0x67E870;
thisCall5Args2 sq_sendCreatePassiveObjectPacket_B6A990 = (thisCall5Args2)0xB6A990;
cdeclCall6 sq_SendCreatePassiveObjectPacketPos_5AF750 = (cdeclCall6)0x5AF750;
thisCall14Args2 CNRDObject__createPassiveObj_878470 = (thisCall14Args2)0x878470;
thisCall15Args2 CNRDObject__createPassiveObjPos_879320 = (thisCall15Args2)0x879320;

thisCall2 BaseSubWin__GetPosX_E86310 = (thisCall2)0xE86310;
thisCall2 BaseSubWin__GetPosY_E86350 = (thisCall2)0xE86350;
thisCallType3 BaseSubWin__DrawIcon_E86390 = (thisCallType3)0xE86390;

thisCall2 BaseBtn__Proc_11C35D0 = (thisCall2)0x11C35D0;
cdeclCall2 drawMouseOverGridImg_7B5000 = (cdeclCall2)0x7B5000;


thisCall1Args2 makePkg_1132930 = (thisCall1Args2)0x1132930;
thisCall2Args2 PkgPushBinary_1132A20 = (thisCall2Args2)0x1132A20;
thisCall2Args2 PkgPushBinary_11331B0 = (thisCall2Args2)0x11331B0;
thisCall1B2 PkgPushByte_1133120 = (thisCall1B2)0x1133120;
thisCall1W2 PkgPushShort_1133150 = (thisCall1W2)0x1133150;
thisCall1Args2 PkgPushStr_1133220 = (thisCall1Args2)0x1133220;
thisCall1Args2 PkgPushWStr_11332B0 = (thisCall1Args2)0x11332B0;
thisCall1Args2 PkgPushInt_1133180 = (thisCall1Args2)0x1133180;
stdCall sendPkg_1132A90 = (stdCall)0x1132A90;

cdeclCall1 PacketBuf_get_short = (cdeclCall1)0x11B94A0;
cdeclCall1 PacketBuf_get_byte = (cdeclCall1)0x11B9470;
cdeclCall1 PacketBuf_get_int = (cdeclCall1)0x11B94D0;
cdeclCall1 PacketBuf_get_binary = (cdeclCall1)0x1134620;

cdeclCall1 GetGameText_122B260 = (cdeclCall1)0x122B260;
//cdeclCall1 PacketBuf__get_binary_1134620 = (cdeclCall1)0x1134620;
//cdeclCall3 PacketBuf__get_str_11346F0 = (cdeclCall3)0x11346F0;
//cdeclCall1 PacketBuf__get_byte_11B9470 = (cdeclCall1)0x11B9470;
//cdeclCall1 PacketBuf__get_short_11B94A0 = (cdeclCall1)0x11B94A0;
//cdeclCall1 PacketBuf__get_int_11B94D0 = (cdeclCall1)0x11B94D0;

thisCall2Args2 BaseBtn__setTextEnable_11C2B70 = (thisCall2Args2)0x11C2B70;
thisCallType4 BaseBtn__setText_11C49F0 = (thisCallType4)0x11C49F0;


cdeclCall1 getObjGradeById_7B4F40 = (cdeclCall1)0x7B4F40;
cdeclCall1 getObjIconImgById_7B4DE0 = (cdeclCall1)0x7B4DE0;
cdeclCall1 getObjNameById_7B4D60 = (cdeclCall1)0x7B4D60;

cdeclCall5 RTDynamicCast_13D76DF = (cdeclCall5)0x013D76DF;
thisCall2 initEncryptKey_11A2470 = (thisCall2)0x11A2470;


int addCloseBtn(int* win, int x, int y) {
	int img = loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface/commonBtn01.img");
	int* btn = (int*)newUiComponent_11B0380(0x3C4);
	initBtn_11C54C0(btn, 0, img, 65, 66, 67, 0xFFFFFFFF, 0, 0);
	addUiComponentChild_11BF330((int*)win[3], (int)btn);

	int* view = (int*)win[0x33];
	view[5] += x;
	view[6] += y;

	btn[5] = view[5];
	btn[6] = view[6];

	return (int)btn;
}

void setRandView(int xPos, int yPos) {
	//评分
	//*(DWORD*)0x004C095B = 0x00010101;//从左到右每个字节分别是 伤害点数 技巧 操作 被击数（00关/01开）
	*(DWORD*)0x004C095B = 0x00000000;

	//*(DWORD*)0x008E7C0E = 748;//被伤害 字 Y轴
	//*(DWORD*)0x008E7C94 = 748;//被伤害 数 Y轴
	//评分系统总体Y轴
	*(int*)0x008EC303 = -15;///有 志愿兵控件时
	*(int*)0x008EC329 = -15;//没 志愿兵控件时

	*(int*)0x008EC383 += xPos;//连击杀伤率 字 X轴
	*(int*)0x008EC3D9 += xPos;//连击杀伤率 次 X轴
	*(int*)0x008EC413 += xPos;//连击杀伤率 数 X轴
	*(int*)0x008EC371 += yPos;//连击杀伤率 总 Y轴

	*(int*)0x008EC6A4 += xPos;//伤害点数 字 X轴
	*(int*)0x008EC6F9 += xPos;//伤害点数 次 X轴
	*(int*)0x008EC725 += xPos;//伤害点数 数 X轴
	*(int*)0x008EC684 += yPos;//伤害点数 总 Y轴

	*(int*)0x008EC7C1 = 750 + xPos;//被击数 字 X轴
	*(int*)0x008EC816 = 730 + xPos;//被击数 次 X轴
	*(int*)0x008EC842 = 730 + xPos;//被击数 数 X轴
	*(int*)0x008EC7A1 += yPos;//被击数 总 Y轴

	*(int*)0x008EC9B3 += xPos;//操作 字 X轴
	*(int*)0x008ECA09 += xPos;//操作 次 X轴
	*(int*)0x008ECA28 += xPos;//操作 数 X轴
	*(int*)0x008EC993 += yPos;//操作 总 Y轴

	*(int*)0x008ECB83 += xPos;//技巧 字 X轴
	*(int*)0x008ECBD9 += xPos;//技巧 次 X轴
	*(int*)0x008ECBF5 += xPos;//技巧 数 X轴
	*(int*)0x008ECB71 += yPos;//技巧 总 Y轴

	*(int*)0x008EC471 = 761 + xPos;//评分 字 X轴
	*(int*)0x008EC45F += yPos;//评分 字 Y轴
	*(int*)0x008EC5DC = 760 + xPos;//评分 数 X轴
	*(int*)0x008EC603 += yPos;//评分 数 Y轴

	//特效评分系统坐标
	*(int*)0x008E7909 = 678 + xPos; //技巧 字 X轴
	*(int*)0x008E7973 = 670 + xPos; //技巧 字 X轴修正
	*(int*)0x008E79B5 = 670 + xPos; //技巧 数 X轴
	*(int*)0x008E7998 = 424 + yPos; //技巧 字 Y轴
	*(int*)0x008E7A06 = 424 + yPos; //技巧 数 Y轴

	*(int*)0x008E7A49 = 668 + xPos; //操作 字 X轴
	*(int*)0x008E7AB3 = 660 + xPos; //操作 字 X轴修正
	*(int*)0x008E7AF5 = 660 + xPos; //操作 数 X轴
	*(int*)0x008E7AD8 = 402 + yPos; //操作 字 Y轴
	*(int*)0x008E7B46 = 402 + yPos; //操作 数 Y轴
}




typedef std::pair<int, const wchar_t*> NavgationBtnInfo;
typedef std::pair<int*, std::vector<std::pair<int*, NavgationBtnInfo*>>> NavgationWin;
NavgationWin HubMenuWin[5];

forceinline void addNavigationWinBtn(NavgationWin* obj, const wchar_t* imgPath, NavgationBtnInfo* info, int num) {
	int img = loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)imgPath);
	for (int* btn, pos, i = 0; i < num; ++i) {
		btn = (int*)newUiComponent_11B0380(0x3C4);
		if (!btn) {
			DPRINTF("NavigationWinBtn new fail!!!\n");
			return;
		}
		pos = i * 4;
		initBtn_11C54C0(btn, 0, img, pos, pos + 1, pos + 2, pos + 3, 0, 0);
		obj->second.push_back({ btn ,&info[i] });
		addBtnToNavigationWin_11E1810(obj->first, 0, (int)btn);
	}
}


thisCall6Args initNavigationWin_11E1960 = (thisCall6Args)0x11E1960;
forceinline void initNavigationWin(NavgationWin* win, int* parentWin, int winImg, const wchar_t* imgPath, NavgationBtnInfo* info, int num, int x, int y) {
	win->first = (int*)newUiComponent_11B0380(0x308);
	initNavigationWin_11E1960(win->first, 0, winImg, 0, 8, 1, 0, 0);
	addUiComponentChild_11BF330(parentWin, (int)win->first);
	addNavigationWinBtn(win, imgPath, info, num);
	setUiComponentVisable_11BE610(win->first, 0);
	setUiComponentPos_11BEAD0(win->first, x, y - 26 * ((win->first[0xBF] - win->first[0xBE]) >> 2), 1);
}

int* newBtn(int* parent, int x, int y, int img, int sNormal, int sSelect, int sClick, int sDisable) {
	int* btn = (int*)newUiComponent_11B0380(0x3C4);
	if (!btn) {
		DPRINTF("newBtn new fail!!!\n");
		return NULL;
	}
	initBtn_11C54C0(btn, 0, img, sNormal, sSelect, sClick, sDisable, 0, 0);
	addUiComponentChild_11BF330(parent, (int)btn);
	setUiComponentVisable_11BE610(btn, 0);
	setUiComponentPos_11BEAD0(btn, x, y, 1);
	return btn;
}

int* newUiComponent(int* parent, int x, int y) {
	int* component = (int*)newUiComponent_11B0380(0x2B8);
	if (!component) {
		DPRINTF("newUiComponent new fail!!!\n");
		return NULL;
	}
	initUiComponent_11BEF80(component);
	addUiComponentChild_11BF330(parent, (int)component);
	setUiComponentPos_11BEAD0(component, x, y, 1);
	return component;
}

NavgationBtnInfo myinfoMenuBtnInfo[] = {
	{1,L"物品栏"},
	{3,L"技能栏"},
	{0,L"个人信息"},
	{-2,L"好感度"},
	{2,L"任务列表"},
	{2,L"执行中的任务"},
	{4,L"副职业"},
	{100 + MODULE_ROOM_LIST,L"地图"},
	{3,L"特性技能"},
};

NavgationBtnInfo communityMenuBtnInfo[] = {
	{7,L"推荐伙伴"},
	{8,L"队伍信息"},
	{9,L"好友"},
	{9,L"工会"},
	{9,L"师徒"},
	{9,L"黑名单"},
	{10,L"邮箱"},
	{6,L"设置心情"},
};

NavgationBtnInfo contentsMenuBtnInfo[] = {
	{11,L"决斗场"},
	{13,L"拍卖行"},
	{14,L"金币拍卖行"},
	//{12,L"守护者祭坛"},
	{-2,L"守护者祭坛"},
};

NavgationBtnInfo serviceMenuBtnInfo[] = {
	{-2,L"商城"},
	{18,L"录制视频"},
	{-1,L"新手教程列表"},
	{-1,L"游戏指南"},
};

NavgationBtnInfo systemMenuBtnInfo[] = {
	{20,L"游戏设置"},
	{21,L"键盘设置"},
	{22,L"选择角色"},
	{23,L"选择频道"},
	{24,L"返回城镇"},
	{25,L"结束游戏"},
};




int* miniMapbtn;
int* hellWinCtlbtn;
int* getMiniMapBtn(void) {
	return miniMapbtn;
}
int* getHellWinCtlbtn(void) {
	return hellWinCtlbtn;
}
void initOld70Hub_delay(int* thisP, int mapX, int x, int y) {
	int img = loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"Interface/WindowCommon.img");
	initNavigationWin(&HubMenuWin[1], (int*)thisP[0x0E], img, L"interface/newstyle/windows/globalnavigation/community.img", communityMenuBtnInfo, 8, x, y);
	initNavigationWin(&HubMenuWin[2], (int*)thisP[0x0E], img, L"interface/globalnavigation/contentsmenu.img", contentsMenuBtnInfo, 4, x, y);
	initNavigationWin(&HubMenuWin[0], (int*)thisP[0x0E], img, L"interface/globalnavigation/myinfomenu.img", myinfoMenuBtnInfo, 9, x, y);
	initNavigationWin(&HubMenuWin[3], (int*)thisP[0x0E], img, L"interface/globalnavigation/servicemenu.img", serviceMenuBtnInfo, 4, x, y);
	initNavigationWin(&HubMenuWin[4], (int*)thisP[0x0E], img, L"interface/globalnavigation/systemmenu.img", systemMenuBtnInfo, 6, x, y);

	img = loadImgFile_11BD5D0(*(int**)0x1B564E4, (int)L"interface2/minimap/dungeon/minimap.img");
	miniMapbtn = newBtn(((int***)thisP)[0x0F][2], mapX, 26, img, 24, 24, 26, 0xffffffff);
	hellWinCtlbtn = newBtn(((int***)thisP)[0x0F][2], mapX, 90, img, 41, 41, 42, 0xffffffff);
}

stdCall1 showSettingWinByIdx_4F2220 = (stdCall1)0x4F2220;
cdeclCall1 getSettingBtnEnable_646050 = (cdeclCall1)0x646050;

void showNavigationWin(int winIdx) {
	int gmodule = CGameModule;
	if (MODULE_SELECT_DUNGEON == gmodule || MODULE_ENTRANCE == gmodule) return;
	for (int i = 0; i < 5; ++i) {
		if (winIdx == i) continue;
		setUiComponentVisable_11BE610(HubMenuWin[i].first, 0);
	}
	char isVisable = !((char*)HubMenuWin[winIdx].first)[12];
	if (isVisable) {
		int idx;
		for (auto j = HubMenuWin[winIdx].second.begin(); j != HubMenuWin[winIdx].second.end(); ++j) {
			idx = (*j).second->first;
			if (idx < 0) {
				setUiComponentEnable_11BE350((*j).first, idx == -2);
			}
			else {
				if(idx >= 100) setUiComponentEnable_11BE350((*j).first, gmodule == (idx - 100));
				else setUiComponentEnable_11BE350((*j).first, getSettingBtnEnable_646050(idx));
			}

		}
	}
	setUiComponentVisable_11BE610(HubMenuWin[winIdx].first, isVisable);
}

char __stdcall hookShowSettingWinByIdx_4F2220(int a1) {
	int retAddr = (int)_ReturnAddress();
	if (retAddr > 0x004C67BF) {
		return showSettingWinByIdx_4F2220(a1);
	}
	else if (a1 < 5) {
		showNavigationWin(a1);
		return 0;
	}
	return showSettingWinByIdx_4F2220(a1);
}


char __fastcall hookCloseNavigationWin(char* thisP) {
	for (int i = 0; i < 5; ++i) {
		if (HubMenuWin[i].first && ((char*)HubMenuWin[i].first)[12])
			setUiComponentVisable_11BE610(HubMenuWin[i].first, 0);
	}
	return thisP?thisP[12]:0;
}

int __fastcall hookShowNavigationWin(int* thisP) {
	showNavigationWin(4);
	return 1;
}


stdCall1 openSettingsWin_4F1510 = (stdCall1)0x4F1510;
int __stdcall hookOpenSettingsWin_4F1510() {
	for (int i = 0; i < 5; ++i) {
		if (((char*)HubMenuWin[i].first)[12]) {
			setUiComponentVisable_11BE610(HubMenuWin[i].first, 0);
			return 0;
		}
	}
	showNavigationWin(4);
	return 1;
}

thisCall1Args openCashShop_427810 = (thisCall1Args)0x427810;
cdeclCall1 openQuestWin_ED08A0 = (cdeclCall1)0xED08A0;
thisCall1Args switchSocialWinTag_F727C0 = (thisCall1Args)0xF727C0;
int __cdecl hookOpenQuestWin_ED08A0(int a1) {
	if (a1 == 0) openQuestWin_ED08A0(0);
	else {
		if (isWinShowing_E71770(*(int**)0x1A6F750, 22)) {
			closeWin_E745B0(*(int**)0x1A6F750, 22, 0xFFFFFFFF, 0);
		}
		else {
			showWin_E77470(*(int**)0x1A6F750, 22, 0, 0);
		}
	}

	return 0;
}

int* getCharacTutorNpcObj(void) {
	int* charcObj = *(int**)0x1AC790C;
	int job = (charcObj + 0xF02)[0];
	int npcId = -1;
	switch (job)
	{
	case 0:npcId = 7; break;
	case 1:
	case 7:npcId = 6; break;
	case 4:npcId = 45; break;
	case 6:npcId = 64; break;
	case 2:
	case 5:npcId = 17; break;
	case 3:
	case 8:npcId = 12; break;
	default:return NULL;
	}
	return (int*)getNpcObjByIdx_90C950(npcId);
}
//void test(void) {
//	int banner = getBannerObjByIndex_766200(0);
//	for (int i = 0; i < 64; ++i) {
//		printf("%d:%08x\n", i, Banner__getItemBySlot_7B9CE0((int*)banner, i));
//	}
//}
thisCall2 showGameMapWin_4BF670 = (thisCall2)0x4BF670;
void openVWin(int* thisP, int i, int idx) {
	switch (i) {
	case 0:
		switch (idx) {
		case 0: showNavigationWin_E7AC30(thisP, 0, 1, 1); break;//物品栏
		case 1: showNavigationWin_E7AC30(thisP, 5, 0, 1); break;//技能栏
		case 2: showWin_E77470(thisP, 0x4C, 0, 0); break;//个人信息
		case 3: showWin_E77470(thisP, 0x4C, 2, 0); break;//好感度
		case 4: openQuestWin_ED08A0(0); break;//任务列表ED08A0
		case 5: hookOpenQuestWin_ED08A0(1); break;//任务列表ED08A0
		case 6: showSettingWinByIdx_4F2220(4); break;//副职业
		case 7: showGameMapWin_4BF670(thisP); break;//地图
		case 8:showOldSkillWin(getCharacTutorNpcObj(), 1);break;//特性技能
		}
		break;
	case 1:
		switch (idx) {
		case 0: showSettingWinByIdx_4F2220(7); break;//推荐伙伴
		case 1: showSettingWinByIdx_4F2220(8);  break;//队伍信息
		case 2:
		case 3:
		case 4:
		case 5: showSettingWinByIdx_4F2220(9); switchSocialWinTag_F727C0(*(int**)0x1AF487C, 0, idx - 2); break; // 好友
		case 6: showSettingWinByIdx_4F2220(10); break;//邮箱
		case 7: showSettingWinByIdx_4F2220(6); break;//心情
		}
		break;
		break;
	case 2:
		switch (idx) {
		case 0: showSettingWinByIdx_4F2220(11); break;//PVP
		case 1: showSettingWinByIdx_4F2220(13); break;//拍卖行
		case 2: showSettingWinByIdx_4F2220(14); break;//金币寄售
		case 3: showSettingWinByIdx_4F2220(12); break;//守护者祭坛
		}
		break;
		break;
	case 3:
		switch (idx) {
		case 0: openCashShop_427810(*(int**)(*(int*)0x01A6F750 + 0x42B4), 0, 1); break;//商城
		case 1: showSettingWinByIdx_4F2220(18); break;//录像
		case 2: break;//新手教程列表
		case 3: break;//游戏指南
		}
		break;
	case 4: showSettingWinByIdx_4F2220(20 + idx); break;
	}
}

thisCall1Args2 CNSelectChannelModule__onEnterModule_10F7040 = (thisCall1Args2)0x10F7040;
char __fastcall hookCNSelectChannelModule__onEnterModule_10F7040(int* thisP, int, int a2) {
	int ret = CNSelectChannelModule__onEnterModule_10F7040(thisP, a2);
	setUiComponentVisable_11BE610((int*)thisP[0x0F], 0);
	//printf("CNSelectChannelModule__onEnterModule_10F7040 %d\n", a2);
	return ret;
}

thisCall1Args2 CNSelectChannelModule__onExitModule_10F4410 = (thisCall1Args2)0x10F4410;
char __fastcall hookCNSelectChannelModule__onExitModule_10F4410(int* thisP, int edx, int a2) {
	return CNSelectChannelModule__onExitModule_10F4410(thisP, a2);
}

thisCall1Args2 CNSelectChannelModule__ProcDraw_10FCF90 = (thisCall1Args2)0x10FCF90;
void __fastcall hookCNSelectChannelModule__ProcDraw_10FCF90(int* thisP, int, int a2) {
	CNSelectChannelModule__ProcDraw_10FCF90(thisP, a2);
}

void __fastcall hookProcNavigationBtnEven_4D4415(int* thisP) {
	for (int idx, i = 0; i < 5; ++i) {
		if (HubMenuWin[i].first && ((char*)HubMenuWin[i].first)[12]) {
			idx = 0;
			for (auto j = HubMenuWin[i].second.begin(); j != HubMenuWin[i].second.end(); ++j, ++idx) {
				if (IControl__IsClick_11BDFC0((*j).first)) {
					openVWin(thisP, i, idx);
					setUiComponentVisable_11BE610(HubMenuWin[i].first, 0);
				}
			}
		}
	}
	goldSkill_CNRDBaseInterface__procCb(thisP);
}
/*
*
MODULE_TYPE_NONE <- -1
MODULE_TYPE_ENTRANCE <- 0
MODULE_TYPE_ROOM_LIST <- 1	// 마을
MODULE_TYPE_SELECT_DUNGEON <- 2				// 던전 선택화면
MODULE_TYPE_MAIN_GAME <- 3					// 일반던전(이계 포함)
MODULE_TYPE_PVP <- 4						// 결장
MODULE_TYPE_FAIR_PVP <- 5					// 공결
//MODULE_TYPE_LABYRINTH <- 7				// 사라짐
MODULE_TYPE_SELECT_CHANNEL <- 6
MODULE_TYPE_WARROOM <- 7					// 전쟁지역
//MODULE_TYPE_CHAOS <- 8
MODULE_TYPE_LOGIN <- 8
MODULE_TYPE_ASSAULT <- 9					// 싸우자
MODULE_TYPE_DEAD_TOWER <- 10					// 사탑
MODULE_TYPE_BLOOD_SYSTEM <- 11				// 무한의 제단
MODULE_TYPE_DESPAIR_TOWER <- 12			//절망의탑

// 글로벌실 컨텐츠
MODULE_TYPE_BOSS_TOWER <- 13			//심연의 투기장
MODULE_TYPE_ADVANCE_ALTAR <- 14			//진격의 제단 守护者祭坛

MODULE_TYPE_LOAD <- 15
MODULE_TYPE_TOURNAMENT <- 16
MODULE_TYPE_MAX <- 17
MODULE_TYPE_PVP_TYPE <- 18			// 결투장, 싸우자, 전쟁지역을 합쳐 지칭
MODULE_TYPE_DUNGEON_TYPE <- 19		// 던전, 사탑, 무제를 합쳐 지칭
MODULE_TYPE_ALL <- 20
*/
//0/选择角色 1/城镇 2/选择地下城 3/地下城 10/亡者之塔
//int __thiscall setStageBtnEnable_4BC3D0(_DWORD** this, int stage)

GameAnim* champKeyFx = new GameAnim(L"ui/fd/champkeyfx.ani", false);
thisCall2Args2 isCanPassMap_7D6E30 = (thisCall2Args2)0x7D6E30;
thisCall2Args2 isBossMiniMap_7E2940 = (thisCall2Args2)0x7E2940;
thisCall2Args2 sub_7DE820 = (thisCall2Args2)0x7DE820;
thisCall2 sub_4C4070 = (thisCall2)0x4C4070;
stdCall4 sub_4BA760 = (stdCall4)0x4BA760;
int OldMinMapX;
int OldMinMapY;

void drawChampKeyFx(int* img) {
	static int lastCount = 0;
	int count = ChampionMonsterKillCount;
	if (count > 0) {
		if (lastCount != count) champKeyFx->reset();
		lastCount = count;
		innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(img, 4), OldMinMapX - 16, 26, *(int*)0x1B5582C);
		if (count / 10)
			innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(img, 5 + count / 10), OldMinMapX + 12, 31, *(int*)0x1B5582C);
		innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(img, 5 + count % 10), OldMinMapX + 21, 31, *(int*)0x1B5582C);
		champKeyFx->draw(410, -110);
	}
}

void drawMap(int* minimapImg) {
	int* dungeon = (int*)getDungeonObj_75C610((int*)getCNModule_706410());
	int* map = (int*)dungeon[0x23];
	int maxX = getMapMaxX_220EAE1(map);
	int maxY = getMapMaxY_21F7021(map);
	if (maxX == 1 && maxY == 1) return;
	int currenMapX = dungeon[0x24];
	int currenMapY = dungeon[0x25];
	int v = 0, t = 0;
	innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 1), OldMinMapX + 10, 33, *(int*)0x1B5582C);

	decrypt_11A0DE0((int*)(dungeon[0x22] + 0x108), dungeon[0x22] + 0x110, (int)&v);
	BYTE needDraw = (v != 1) && (!isBossMiniMap_7E2940(map, currenMapX, currenMapY));
	//DPRINTF("[%d, %d][%d, %d][%d, %d]\n", maxX, maxY, currenMapX, currenMapY, v, needDraw);
	char xB = currenMapX - 2, xE = currenMapX + 2, yB = currenMapY - 2, yE = currenMapY + 2;
	char end = 0;
	setGameCanvasSize_6FD880(OldMinMapX + 12, OldMinMapY + 13, OldMinMapX + 12 + 67, OldMinMapY + 13 + 67);
	for (int y = yB, yPos = OldMinMapY; y <= yE; ++y, yPos += 18) { 
		if (y < 0 || y >= maxY) continue;
		for (int x = xB, xPos = OldMinMapX; x <= xE; ++x, xPos += 18) {
			if (x < 0 || x >= maxX) continue;
			else if (y == yB && x == xB) continue;
			else if (y == yE && x == xB) continue;
			else if (x == xE && y == yB) continue;
			else if (x == xE && y == yE) continue;

			char isCanPass = isCanPassMap_7D6E30((int*)dungeon[0x13], x, y);
			v = getMapType_217DD2A(map, x, y);
			if (!sub_7DE820(map, x, y)) v = 0;
			
			if ((currenMapX == x && currenMapY == y) || v || needDraw && isCanPassMap_7D6E30((int*)dungeon[0x13], x, y)) {
				innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 0), xPos - 2, yPos - 2, *(int*)0x1B5582C);
			}
		}
	}

	for (int y = yB, yPos = OldMinMapY; y <= yE; ++y, yPos += 18) {
		if (y < 0 || y >= maxY) continue;
		for (int x = xB, xPos = OldMinMapX; x <= xE; ++x, xPos += 18) {
			if (x < 0 || x >= maxX) continue;
			else if (y == yB && x == xB) continue;
			else if (y == yE && x == xB) continue;
			else if (x == xE && y == yB) continue;
			else if (x == xE && y == yE) continue;

			char isCanPass = isCanPassMap_7D6E30((int*)dungeon[0x13], x, y);
			//DPRINTF("isCanPass:%d\n", isCanPass);
			char isHighLight = 0;
			t = (((*(stdCall*)0x155A588)() / 250) & 1) == 0;
			v = getMapType_217DD2A(map, x, y);
			if (!sub_7DE820(map, x, y)) {
				v = 0;
				isHighLight = t;
			}
			else if (needDraw && t && isCanPass) {
				isHighLight = 1;
			}
			if (currenMapX == x && currenMapY == y) {
				//DPRINTF("[%d, %d, %d, %d]\n", v, 8 * v - 8, x, y);
				v = 8 * v - 8;
				//innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 0), xPos - 2, yPos - 2, *(int*)0x1B5582C);
				innerDrawImg_11DB180((int*)getImageByPos_11B4BD0((int*)map[0x30], v + 4), xPos, yPos, *(int*)0x1B5582C);
				innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 3), xPos + 6, yPos + 4, *(int*)0x1B5582C);
				//drawImgByXY2_11B41E0(*(int**)0x1B5582C, 0, xPos, yPos, getImageByPos_11B4BD0(minimapImg, 0, v + 48), 1.0f, 1.0f, 0.0f, 0x00FFFFFF, *(float *)0x01562250, *(float *)0x01562250);
			}
			else if (v || needDraw && isCanPass) {
				//DPRINTF("[%d, %d, %08x]\n", v, isHighLight, map[0x30]);
				//innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 0), xPos - 2, yPos - 2, *(int*)0x1B5582C);
				innerDrawImg_11DB180((int*)sub_4BA760(v, 0, isHighLight, map[0x30]), xPos, yPos, *(int*)0x1B5582C);
				//drawImgByXY2_11B41E0(*(int**)0x1B5582C, 0, xPos, yPos, getImageByPos_11B4BD0(minimapImg, 0, v + 44), 1.0f, 1.0f, 0.0f, 0x00FFFFFF, *(float*)0x01562250, *(float*)0x01562250);
			}
		}
	}
	resetGameCanvasSize_6FD8D0();
	innerDrawImg_11DB180((int*)getImageByPos_11B4BD0(minimapImg, 2), OldMinMapX - 100, 0, *(int*)0x1B5582C);
}
int __fastcall drawOldMiniMap(int* thisP, int edx) {
	int* minimapImg = (int*)getPreloadImg_11BB1B0(*(int**)0x1A6A870, 23);
	drawMap(minimapImg);
	drawChampKeyFx(minimapImg);
	return sub_4C4070(thisP);
}

void common_CNMainGameModule_onEnterModuleCb(int* thisP, int a2) {
	champKeyFx->reset();
}

void common_CNMainGameModule_onExitModuleCb(int* thisP, int a2) {

}

void common_CNTownModule_onEnterModuleCb(int* thisP, int a2) {


}

void common_CNTownModule__onExitModuleCb(int* thisP, int a2) {
}


thisCall1Args2 GlobalNavigationMgr__init_1007730 = (thisCall1Args2)0x1007730;
int __fastcall hookGlobalNavigationMgr__init_1007730(int* thisP,int , int a2) {
	int ret = GlobalNavigationMgr__init_1007730(thisP, a2);
	thisP[6] = (int)newBtn((int*)thisP[3], 505, 30 + 28, thisP[0x2F], 5, 6, 7, 8);
	setUiComponentVisable_11BE610((int *)thisP[6], 1);
	return ret;
}

thisCall2 GlobalNavigationMgr__Proc_1007EF0 = (thisCall2)0x1007EF0;
int __fastcall hookGlobalNavigationMgr__Proc_1007EF0(int* thisP) {
	int ret = GlobalNavigationMgr__Proc_1007EF0(thisP);
	if (IControl__IsClick_11BDFC0((int *)thisP[6])) {
		openCashShop_427810(*(int**)(*(int*)0x01A6F750 + 0x42B4), 0, 1);
		playSound_766160((int)L"CLICK_BUTTON1", 0xFFFFFFFF, 0, 0);
	}
	return ret;
}


int globalBtnPosY = 0;
thisCall1Args2 cashShopBtnProcDraw;
thisCall1Args2 GlobalNavigationMgr__ProcDraw_1007AB0 = (thisCall1Args2)0x1007AB0;
int __fastcall hookGlobalNavigationMgr__ProcDraw_1007AB0(int* thisP, int, int a2) {
	int* villageAttackedReward = ((int***)getCNModule_706410())[0x2B][0x53];
	if (!RBYTE(villageAttackedReward, 4)) {//非怪物攻城中
		if (globalBtnPosY + 30 != ((int*)thisP[4])[6]) {
			setUiComponentPos_11BEAD0((int*)thisP[4], 505, globalBtnPosY + 30, 1);
			setUiComponentPos_11BEAD0((int*)thisP[6], 505, globalBtnPosY + 58, 1);
		}
	}
	else {
		if (121 != ((int*)thisP[4])[6]) {
			setUiComponentPos_11BEAD0((int*)thisP[4], 505, 121, 1);
			setUiComponentPos_11BEAD0((int*)thisP[6], 505, 121 + 28, 1);
		}
	}
	int ret = GlobalNavigationMgr__ProcDraw_1007AB0(thisP, a2);
	cashShopBtnProcDraw(thisP, a2);
	return ret;
}

int __fastcall fixGlobalBtnPosY(int* thisP, int, int a2) {
	int ret = getImageByPos_11B4BD0(thisP, a2);
	if (ret)
		globalBtnPosY = ((WORD*)ret)[0xF] + 5;
	return ret;
}

thisCall2 sub_45D490 = (thisCall2)0x45D490;
int __fastcall hookSub_45D490(int* thisP){
	globalBtnPosY = 0;
	return sub_45D490(thisP);
}

int __cdecl getHellParyItemConditionCount_125A4C0(int lv) {
	return 1;
}

void common_OnReqHumanCertify(void) {
	hookCloseNavigationWin(NULL);
}



void initOld70Hub(int mapX, int mapY) {
	writeCallCode((LPVOID*)0x00F98DCC, (PVOID)getHellParyItemConditionCount_125A4C0);//深渊门票数

	GumInterceptor* v = gum_interceptor_obtain();

	gum_interceptor_replace_fast(v, (gpointer)0x4F2220, (gpointer)hookShowSettingWinByIdx_4F2220, (gpointer*)&showSettingWinByIdx_4F2220);
	gum_interceptor_replace_fast(v, (gpointer)0x4F1510, (gpointer)hookOpenSettingsWin_4F1510, (gpointer*)&openSettingsWin_4F1510);

	//writeCallCode((LPVOID*)0x00E79553, (PVOID)hookCloseNavigationWin);//ESC 关闭窗口
	writeCallCode((LPVOID*)0x00E777CE, (PVOID)hookCloseNavigationWin);//打开其他弹窗时，关闭窗口
	writeCallCode((LPVOID*)0x00E71146, (PVOID)hookCloseNavigationWin);//跟随以前的关闭窗口逻辑
	writeCallCode((LPVOID*)0x004C6809, (PVOID)hookShowNavigationWin);//系统设置按钮
	writeCallCode((LPVOID*)0x004C6810, (PVOID)hookShowNavigationWin);//系统设置按钮
	*(BYTE*)0x004BC40E = 1;//不禁用系统设置按钮
	writeCallCode((LPVOID*)0x004D4415, (PVOID)hookProcNavigationBtnEven_4D4415);
	gum_interceptor_replace_fast(v, (gpointer)0xED08A0, (gpointer)hookOpenQuestWin_ED08A0, (gpointer*)&openQuestWin_ED08A0);

	//24 26 41 42
	writeCallCode((LPVOID*)0x004D2FD0, (PVOID)drawOldMiniMap);
	OldMinMapX = mapX;
	OldMinMapY = mapY;

	//initNavigationWin_11E1960
	//addNavigationBtn_E71000
	//procNavigationBtnEven_E7C730
	// buttomCickCheck_4C6680 -> sub_E71100 -> setUiComponentVisable_11BE610
	// showNavigationWin_E7AC30 技能4/5
	// char __stdcall sub_4F2220(int a1)
	// E7AC30
	//CNRDBaseInterface::DrawProc_4D5110 -> isMouseSelectObj_11BE040 提示文字 jmp     loc_4D551A
	//00E772E3 选中NavigationWinBtn toast

		//*(DWORD*)0x015BE208 = (int)hookCNSelectChannelModule__ProcDraw_10FCF90;
	*(DWORD*)0x015BE230 = (int)hookCNSelectChannelModule__onEnterModule_10F7040;
	*(DWORD*)0x015BE234 = (int)hookCNSelectChannelModule__onExitModule_10F4410;
	

	//*(BYTE*)0x010079B3 = 1;
	//*(DWORD*)0x01007994 = 467;
	*(DWORD*)0x0100779E = 456;
	*(BYTE*)0x01007E6E = 1;
	*(BYTE*)0x01007E65 = 1;
	*(BYTE*)0x01007F48 = 1;
	*(DWORD*)0x01007ED6 = 505;//x
	*(DWORD*)0x01007EBC = 30;//y
	writeCallCode((LPVOID*)0x00E847B6, (PVOID)hookGlobalNavigationMgr__init_1007730);//系统设置按钮
	writeCallCode((LPVOID*)0x00E7F0C1, (PVOID)hookGlobalNavigationMgr__Proc_1007EF0);//系统设置按钮

	std::vector<RelocatHookInfo>* hook = new std::vector<RelocatHookInfo>(12);
	//hook->resize(4);
	auto b = hook->begin();
	BYTE timerPtrPos = 0x28 + 2 * (7 * 4);//sizeof(timer) == 7 * 4
	BYTE objPos = 6 * 4;
	DWORD timerCountPos = 0xB4 + 2;
	b++->setValue(H_BYTE, 0x01007AD5, timerPtrPos);//thisP[6] 商城
	b++->setValue(H_BYTE, 0x01007AF1, timerPtrPos);//thisP[6] 商城
	b++->setValue(H_BYTE, 0x01007B57, timerPtrPos);//thisP[6] 商城

	b++->setValue(H_DWORD, 0x01007AF9, timerCountPos);//thisP[6] 商城
	b++->setValue(H_DWORD, 0x01007B1A, timerCountPos);//thisP[6] 商城
	b++->setValue(H_DWORD, 0x01007B5F, timerCountPos);//thisP[6] 商城
	b++->setValue(H_DWORD, 0x01007B69, timerCountPos);//thisP[6] 商城
	b++->setValue(H_DWORD, 0x01007B86, timerCountPos);//thisP[6] 商城
	b++->setValue(H_DWORD, 0x01007B8D, timerCountPos);//thisP[6] 商城

	b++->setValue(H_BYTE, 0x01007ADD, objPos);//thisP[6] 商城
	b++->setValue(H_BYTE, 0x01007BF8, objPos);//thisP[6] 商城
	b++->setValue(H_BYTE, 0x01007C01, objPos);//thisP[6] 商城
	cashShopBtnProcDraw = (thisCall1Args2)tools_relocation_hook(0x1007AB0, 0x01007C20, hook);
	*(DWORD*)0x01812574 = (int)hookGlobalNavigationMgr__ProcDraw_1007AB0;

	
	*(DWORD*)0x0094A1C8 -= 160; *(BYTE*)0x0094A1C6 -= 20;
	*(DWORD*)0x0094A1ED -= 185; *(BYTE*)0x0094A1EB -= 20;
	*(DWORD*)0x0094A20B -= 160; *(BYTE*)0x0094A209 -= 20;

	*(DWORD*)0x0094A26C -= 160; *(DWORD*)0x0094A267 -= 120;
	*(DWORD*)0x0094A28F -= 160; *(BYTE*)0x0094A28D -= 20;
	*(DWORD*)0x0094A2A5 -= 160; *(BYTE*)0x0094A2A3 -= 20;

	static float xCover = 631 - 160;
	*(DWORD*)0x0094A2B7 = (int) & xCover; *(DWORD*)0x0094A2BC -= 120;
	*(DWORD*)0x0094A2DE -= 160; *(BYTE*)0x0094A2DC -= 20;
	*(DWORD*)0x0094A306 -= 160; *(BYTE*)0x0094A304 -= 20;
	*(DWORD*)0x0094A323 -= 160; *(BYTE*)0x0094A321 -= 20;

	//计时
	*(DWORD*)0x0094A35E = 365;//x
	*(DWORD*)0x0094A359 = 6;//y

	//通关动画
	*(BYTE*)0x00949879 -= 80;//x
	*(DWORD*)0x00949874 -= 60;//y
	*(DWORD*)0x00949897 -= 80;//x
	*(DWORD*)0x00949892 -= 80;//x
	*(DWORD*)0x009498F6 -= 60;//y
	*(DWORD*)0x00949902 -= 80;//x
	*(DWORD*)0x0094995D -= 60;//y
	*(DWORD*)0x009499C9 -= 80;//x
	*(DWORD*)0x009499C4 -= 60;//y
	*(DWORD*)0x00949A2E -= 80;//x
	*(DWORD*)0x00949A29 -= 60;//y

	//中央动画
	*(BYTE*)0x00949EF1 -= 80;//x
	*(BYTE*)0x00949EEF -= 60;//y

	//writeCallCode((LPVOID*)0x0094A1B9, (PVOID)fixGlobalBtnPosY);
	//writeCallCode((LPVOID*)0x0045D603, (PVOID)fixGlobalBtnPosY);
	writeCallCode((LPVOID*)0x0045D706, (PVOID)fixGlobalBtnPosY);
	writeCallCode((LPVOID*)0x0045E54E, (PVOID)hookSub_45D490);
	
}


void drawTagLine(int* WindowCommonImg, int x, int y, int w) {
	int* img = (int*)getImageByPos_11B4BD0(WindowCommonImg, 158);
	for (int i = x; i < x + w; ++i) {
		innerDrawImg_11DB180(img, i, y, *(int*)0x1B5582C);
	}
}