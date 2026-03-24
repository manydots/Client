#pragma once
#define QuestDetailWinId	23
int* __fastcall QuestDetailWin_Constructor(int argc);
void QuestDetailWin_setQuestData(int quest, BYTE flag);
void QuestDetailWin_setEvenQuestData(int quest);
int* getQuestDetailWin(void);