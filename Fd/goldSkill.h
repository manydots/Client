#pragma once
void goldSkillInit(void);
void goldSkillInitDelay(int *thisP);
void goldSkill_OnNotiClearQuest(void);
void goldSkill_OnFinshQuest(void);
void goldSkill_CNTownModule__onExitModuleCb(int* thisP, int a2);
void goldSkill_CNMainGameModule_onEnterModuleCb(int* thisP, int a2);
void goldSkill_CNMainGameModule_onExitModuleCb(int* thisP, int a2);
void goldSkill_CNRDBaseInterface__procCb(int* thisP);
void goldSkill_AddLevel(void);