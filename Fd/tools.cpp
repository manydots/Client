#include "pch.h"
#include "tools.h"
#include "common.h"
#include "frida-gum.h"

static int funcMemory;
static int pos;


int tools_get_func_memory(int len) {
	//int p = funcMemory + pos;
	//pos += ROUND_UP(len, 16);
	//return p;
    auto* p = new char[len];
    //printf( "Memory is Allocated at address [0x%p]\n", p);
    DWORD oldProtect;
    VirtualProtect(p, len, PAGE_EXECUTE_READWRITE, &oldProtect);
    return (int)p;
}

void tools_release_func_memory(int p) {
    //pos -= ROUND_UP(len, 16);
    if(p) delete (int *)p;
}

int __declspec(noinline) tools_relocation(int b, int e) {
    guint size;
    size_t len = e - b;
    int p = tools_get_func_memory(len);
    size = gum_x86_relocator_relocate((gpointer)b, len, (gpointer)p);
    //DPRINTF("tools_relocation:0x%08x %d %x\n", p, size, size);
    return p;
}

int __declspec(noinline) tools_relocation_hook(int b, int e, std::vector<RelocatHookInfo>* hook) {
    int p = tools_relocation(b, e);
    for (size_t i = 0; i < hook->size(); ++i) {
        RelocatHookInfo& info = hook->at(i);
        if (info.type == H_NULL) continue;
        else if (info.addr < b || info.addr > e) {
            DPRINTF("t:%d a:0x%08x v:0x%08x is not func addr in [0x%08x, 0x%08x]!!!\n", info.type, info.addr, info.data, b, e);
            continue;
        }
        int addrPos = p + (info.addr - b);
        switch (info.type) {
        case H_BYTE:*(BYTE*)addrPos = (BYTE)info.data; continue;
        case H_WORD:*(WORD*)addrPos = (WORD)info.data; continue;
        case H_DWORD:*(DWORD*)addrPos = info.data; continue;
        case H_CALL:writeCallCode((void*)addrPos, (void*)info.data); continue;
        case H_JUMP:writeJmpCode((void*)addrPos, (void*)info.data); continue;
        case H_NOP:writeNopCode((void*)addrPos, info.data); continue;
        case H_CALL_SELF:writeCallCode((void*)addrPos, (void*)p); continue;
        }
    }
    return p;
}

int __declspec(noinline) tools_relocation_hook(int b, int e, std::vector<RelocatHookInfo>* hook, bool log) {
    int p = tools_relocation(b, e);
    if (log)DPRINTF("relocation 0x%08x -> 0x%08x\n",b, p);
    for (size_t i = 0; i < hook->size(); ++i) {
        RelocatHookInfo &info = hook->at(i);
        if(info.type == H_NULL) continue;
        else if (info.addr < b || info.addr > e) {
            DPRINTF("t:%d a:0x%08x v:0x%08x is not func addr in [0x%08x, 0x%08x]!!!\n", info.type, info.addr, info.data, b, e);
            continue;
        }
        int addrPos = p + (info.addr - b);
        if(log)DPRINTF("relocation_hook:%d in [0x%08x, 0x%08x][0x%08x, 0x%08x]!!!\n", info.type, p, info.addr, addrPos, info.data);
        switch (info.type){
        case H_BYTE:*(BYTE*)addrPos = (BYTE)info.data;continue;
        case H_WORD:*(WORD*)addrPos = (WORD)info.data; continue;
        case H_DWORD:*(DWORD*)addrPos = info.data; continue;
        case H_CALL:writeCallCode((void*)addrPos, (void*)info.data); continue;
        case H_JUMP:writeJmpCode((void*)addrPos, (void*)info.data); continue;
        case H_NOP:writeNopCode((void*)addrPos, info.data); continue;
        case H_CALL_SELF:writeCallCode((void*)addrPos, (void*)p); continue;
        }
    }
    return p;
}

int __declspec(noinline) tools_relocation2(int b, int e, int b2, int e2) {
    guint size;
    size_t len = (e - b) + (e2 - b2);
    int p = tools_get_func_memory(len);
    size = gum_x86_relocator_relocate((gpointer)b, (e - b), (gpointer)p);
    size = gum_x86_relocator_relocate((gpointer)b2, (e2 - b2), (gpointer)(p + (e - b)));
    //DPRINTF("tools_relocation:0x%08x %d %x\n", p, size, size);
    return p;
}

int __declspec(noinline) tools_relocation2_hook(int b, int e, int b2, int e2, std::vector<RelocatHookInfo>* hook) {
    int p = tools_relocation2(b, e, b2, e2);
    for (size_t i = 0; i < hook->size(); ++i) {
        RelocatHookInfo& info = hook->at(i);
        if (info.type == H_NULL) continue;
        if ((info.addr >= b && info.addr <= e) || (info.addr >= b2 && info.addr <= e2)) {
            int addrPos;
            if ((info.addr >= b && info.addr <= e)) {
                addrPos = p + (info.addr - b);
            }
            else {
                addrPos = p + (b - e) + (info.addr - b2);
            }
            //DPRINTF("relocation2_hook:%d in 0x%08x[0x%08x, 0x%08x]!!!\n", info.type, p, addrPos, info.data);
            switch (info.type) {
            case H_BYTE:*(BYTE*)addrPos = (BYTE)info.data; continue;
            case H_WORD:*(WORD*)addrPos = (WORD)info.data; continue;
            case H_DWORD:*(DWORD*)addrPos = info.data; continue;
            case H_CALL:writeCallCode((void*)addrPos, (void*)info.data); continue;
            case H_JUMP:writeJmpCode((void*)addrPos, (void*)info.data); continue;
            case H_NOP:writeNopCode((void*)addrPos, info.data); continue;
            case H_CALL_SELF:writeCallCode((void*)addrPos, (void*)p); continue;
            }
        }
        else {
            //DPRINTF("t:%d a:0x%08x v:0x%08x is not func addr!!!\n", info.type, info.addr, info.data);
        }
    }
    return p;
}



static void print_string_hex(const char* comment, unsigned char* str, size_t len)
{
	unsigned char* c;

	DPRINTF("%s", comment);
	for (c = str; c < str + len; c++) {
		DPRINTF("0x%02x ", *c & 0xff);
	}

	DPRINTF("\n");
}

void writeNopCode(void* p, DWORD num) {
	for (DWORD i = 0; i < num; ++i) {
		*((BYTE*)p + i) = 0x90;
	}
}

void writeCodeArray(void* p, BYTE* code, DWORD num) {
    for (DWORD i = 0; i < num; ++i) {
        *((BYTE*)p + i) = code[i];
    }
}

void writeJmpCode(void* p, void* fn) {
	//DWORD v;
	//VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &v);
	*(UCHAR*)((char*)p + 0) = 0xe9;
	*(ULONG*)((char*)p + 1) = (ULONG)fn - (ULONG)p - 5;
	//FlushInstructionCache(GetCurrentProcess(), p, 5);
	//VirtualProtect(p, 5, v, &v);
}

void writeCallCode(void* p, void* fn) {
	//DWORD v;
	//VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &v);
	*(UCHAR*)((char*)p + 0) = 0xe8;
	*(DWORD*)((char*)p + 1) = (DWORD)fn - (DWORD)p - 5;
	//FlushInstructionCache(GetCurrentProcess(), p, 5);
	//VirtualProtect(p, 5, v, &v);
}

void writeDWordCode(DWORD p, DWORD v) {
    DWORD bk;
    VirtualProtect((LPVOID)p, 4, PAGE_EXECUTE_READWRITE, &bk);
    *(DWORD*)p = v;
    FlushInstructionCache(GetCurrentProcess(), (LPVOID)p, 5);
    VirtualProtect((LPVOID)p, 4, bk, &bk);
}

GameAnim::GameAnim(const WCHAR* path) {
    animPath = path;
    animObj = NULL;
    autoReset = true;
}

GameAnim::GameAnim(const WCHAR* path, bool autoReset) {
    animPath = path;
    animObj = NULL;
    GameAnim::autoReset = autoReset;
}

GameAnim* GameAnim::init(void) {
    if (animObj) return this;
    if (animPath == NULL) return NULL;
    int obj = newUiComponent_11B0380(0x1fc);
    if (!obj) {
        printf("no memory! newUiComponent fail!\n");
        return NULL;
    }
    animObj = (int*)loadAniObjByPath_109A4E0((int*)obj, (int)animPath, 1, 0);
    return this;
}

int GameAnim::draw(int x, int y) {
    return draw(x, y, 0);
}

int GameAnim::draw(int x, int y, int flag) {
    if (!animObj) {
        if (init() == NULL) return 1;
    }
    if (!autoReset && (*(BYTE*)(animObj + 0x7B) & 8)) return 1;

    CNRDAnimation__Proc_109C4C0(animObj);
    CNRDAnimation__Draw_1096580(animObj, *(int*)0x1B5582C, x, y, 0, flag);

    if (*(BYTE*)(animObj + 0x7B) & 8) {
        if (autoReset) CNRDAnimation__Reset_109B330(animObj, 1);
        return 1;
    }
    return 0;
}

void GameAnim::reset() {
    if (!animObj) return;
    if (*(BYTE*)(animObj + 0x7B) & 8) CNRDAnimation__Reset_109B330(animObj, 1);
    return;
}

void GameAnim::end() {
    if (!animObj) return;
    CNRDAnimation__setEnd_403A30(animObj, 1);
    return;
}


GameAnim::~GameAnim() {
    if (!animObj) return;
    delAnim_1098D30(animObj);
    delUiComponent_11B03C0((int)animObj);
    animObj = NULL;
}



GameAnimCombo::GameAnimCombo(PlayType type, std::initializer_list<GameAnim*> list) {
    playIdx = type;
    for (auto i = list.begin(); i != list.end(); ++i) {
        animList.push_back((*i));
    }
}

GameAnimCombo::GameAnimCombo(GameAnim* list) {
    playIdx = PlaySigle;
    animList.push_back(list);
}

void GameAnimCombo::draw(int x, int y) {
    if (PlaySigle == playIdx) {
        animList[0]->draw(x, y);
    }
    else if (playIdx == PlayParallel) {
        for (auto i = animList.begin(); i != animList.end(); ++i) {
            (*i)->draw(x, y);
        }
    }
    else {
        playIdx = (playIdx + animList[playIdx]->draw(x, y)) % animList.size();
    }
}

GameAnimCombo::~GameAnimCombo() {
    for (auto i = animList.begin(); i != animList.end(); ++i) {
        delete (*i);
    }
    animList.clear();
}




int GameVector::getSize() {
    if (!head || !*head || *head != (int)&head) return 0;
    else if (!begin || !end || begin == end) return 0;
    return ((int)end - (int)begin) / 4;
}
int GameVector::getValue(int pos) {
    return begin[pos];
}

DWORD Naked getTime()
{
    __asm rdtsc;
    __asm ret;
}