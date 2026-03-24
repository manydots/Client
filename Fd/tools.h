#pragma once
#include "pch.h"
#include <vector>
//#include <capstone/platform.h>
//#include <capstone/capstone.h>
enum HookType {
    H_NULL = -1,
    H_BYTE = 0,
    H_WORD = 1,
    H_DWORD = 2,
    H_CALL = 3,
    H_JUMP = 4,
    H_NOP = 5,
    H_CALL_SELF = 6
};

 class RelocatHookInfo {
 public:
    
    int type;
    int addr;
    int data;

    RelocatHookInfo() {
        type = H_NULL;
    }
    RelocatHookInfo(int t, int a, int d) {
        type = t;
        addr = a;
        data = d;
    }
    
    void setValue(int t, int a, int d) {
        type = t;
        addr = a;
        data = d;
    }

    ~RelocatHookInfo() {};
};

 DWORD getTime();

int tools_get_func_memory(int len);
void tools_release_func_memory(int p);
int tools_relocation(int b, int e);
int tools_relocation_hook(int b, int e, std::vector<RelocatHookInfo>* hook);
int tools_relocation_hook(int b, int e, std::vector<RelocatHookInfo>* hook, bool log);
int tools_relocation2(int b, int e, int b2, int e2);
int tools_relocation2_hook(int b, int e, int b2, int e2, std::vector<RelocatHookInfo>* hook);

void writeNopCode(void* p, DWORD num);
void writeCodeArray(void* p, BYTE* code, DWORD num);
void writeJmpCode(void* p, void* fn);
void writeCallCode(void* p, void* fn);
void writeDWordCode(DWORD p, DWORD v);


class GameAnim
{
public:
    int* animObj;
    const WCHAR* animPath;
    bool autoReset;

    GameAnim(const WCHAR* path);
    GameAnim(const WCHAR* path, bool autoReset);

    GameAnim* init(void);

    int draw(int x, int y);
    int draw(int x, int y, int flag);
    void reset();
    void end();
    ~GameAnim();
};

class GameAnimCombo
{
public:
    enum PlayType
    {
        PlaySigle = -2,
        PlayParallel = -1,
        PlaySerial = 0
    };
    std::vector<GameAnim*> animList;
    int playIdx;

    GameAnimCombo(PlayType type, std::initializer_list<GameAnim*> list);
    GameAnimCombo(GameAnim* list);
    void draw(int x, int y);
    ~GameAnimCombo();
};


class GameVector
{
public:
    int *head;
    int *begin;
    int *end;
    int *endP;

    int getSize();
    int getValue(int pos);
};


