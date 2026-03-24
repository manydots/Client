#include "pch.h"
#include "common.h"
#include "tools.h"
#include "frida-gum.h"
#include "70.h"

bool wstr_endwith(const wchar_t* str, const wchar_t* reg) {
    int l1 = wcslen(str), l2 = wcslen(reg);
    if (l1 < l2) return false;
    str += l1 - l2;
    while (*str && *reg && *str == *reg) {
        str++;
        reg++;
    }
    if (!*str && !*reg) return true;
    return false;
}

#define SOUND_WAV

thisCall6Args2 playEffectOrEnvSound_11985D0 = (thisCall6Args2)0x11985D0;
int __fastcall hookPlayEffectOrEnvSound_11985D0(int* thisP, int, int soundObj, int a3, int a4, int a5, int a6, int a7) {
    wchar_t* soundName = *(wchar_t**)(soundObj + 0x34);
    if (
#ifdef SOUND_WAV
        wstr_endwith(soundName, L"pub_hit_01.wav") ||
        wstr_endwith(soundName, L"c_lightadd.wav") 
        //wstr_endwith(soundName, L"sizzle_hit.wav") ||
        //wstr_endwith(soundName, L"icicle_hit.wav") 
#else
        wstr_endwith(soundName, L"pub_hit_01.ogg") ||
        wstr_endwith(soundName, L"c_lightadd.ogg") 
        //wstr_endwith(soundName, L"sizzle_hit.ogg") ||
        //wstr_endwith(soundName, L"icicle_hit.ogg")
#endif // SOUND_WAV
        ) {
        thisP[0xFC1] = 8;
    }
#ifdef SOUND_WAV
    else if (wstr_endwith(soundName, L"death_critical.wav"))
#else
    else if (wstr_endwith(soundName, L"death_critical.ogg"))
#endif
    {
        ((int*)soundObj)[2] = 500;
        thisP[0xFC1] = 12;
    }else if (wcsstr(soundName, L"hit")) {
        //((int*)soundObj)[2] = 400;
        thisP[0xFC1] = 4;
    }
    else {
        thisP[0xFC1] = 2;
    }
    return playEffectOrEnvSound_11985D0(thisP, soundObj, a3, a4, a5, a6, a7);
}

thisCall2 SoundChannel__getCoord_119EFF0 = (thisCall2)0x119EFF0;
int __fastcall fixMaxSoundCountImp(int **soundMgr, int* sound, int *soundChannel, int soundCount, int v58, int v64) {
    if (soundChannel) {
        float* soundCoord = (float*)SoundChannel__getCoord_119EFF0(soundChannel);
        if (soundCoord) {
            float* coord = (float*)(((thisCall2*)*soundMgr[0xFA7])[1])(soundMgr[0xFA7]);
            //printf("0x%08x[0x%08x, 0x%08x, %d, %d][%0.2f, %0.2f][%0.2f, %0.2f]\n", soundChannel, v58, v64, soundCount, RWORD(sound, 124), *coord, *soundCoord, coord[1], soundCoord[1]);
            //return 0;
            /*if (fabs(coord[0] - soundCoord[0]) > 640) {
                return soundCount >= 2;
            }
            else */if (coord[0] == soundCoord[0] && coord[1] == soundCoord[1]) {
     /*          if (sound && *sound == 0x185148C && RWORD(sound, 124) == 4)
                    return soundCount >= 2;
               else*/
                    return 0;
                //return soundCount >= 20;
            }
        }
    }
    //printf("0x%08x[0x%08x, 0x%08x, %d, %d]\n", soundChannel, v58, v64, soundCount, RWORD(sound, 124));
    if (sound && *sound == 0x185148C) {
        WORD v = RWORD(sound, 124);
        //if (v == 66) return soundCount >= 1;
        //else if (v == 16) return 0;
        return soundCount >= v;
    }
    return 0;
}

void* f;
void Naked fixMaxSoundCount(void) {
    //011987BF
    __asm {
        mov ecx, edi
        mov edx, [ebp + 0x08]//sound
        push edi
        push[ebp - 0x04]
        push[ebp - 0x1C]
        push [ebp - 0x0C]
        push [ebp + 0x0C]
        call fixMaxSoundCountImp
        pop edi
        mov edx, f
        test eax, eax
        jz goNext
        add edx, 0x208
        //mov edx, 0x11987D8
        jmp edx
        goNext:
        add edx, 0x1FA
        //mov edx, 0x011987CA
        jmp edx
    }
}

thisCall1Args2 EffectSound__parse_119E850 = (thisCall1Args2)0x119E850;
int __fastcall hookEffectSound__parse_119E850(int* thisP, int, int a2) {
    int ret = EffectSound__parse_119E850(thisP, a2);
    if (thisP && *thisP == 0x185148C) {//EffectSound
        wchar_t* str = NULL;
        if (thisP[0x12] < 8)
            str = (wchar_t*)(thisP + 0xD);
        else
            str = (wchar_t*)thisP[0xD];
        if (!str) return ret;
  /*      if (wcsstr(str, L"hk_") || wcsstr(str, L"hk1_") || wcsstr(str, L"hk2_")) {
            WWORD(thisP, 124, 66);
        }
        else */if (wcsstr(str, L"death_critical")
            ) {
            WWORD(thisP, 124, 30);
            //thisP[2] = 1000;
        }
        else if (wcsstr(str, L"pub_hit_01") 
            //|| wcsstr(str, L"c_lightadd")
           
            ) {
            WWORD(thisP, 124, 20);
            //thisP[2] = 1000;
        }
        else if (wcsstr(str, L"/dstraight_hit") 
            || wcsstr(str, L"/punch3_hit") 
   /*         || wcsstr(str, L"/upper_hit") 
            || wcsstr(str, L"/dupper") */
            //|| wcsstr(str, L"/gc_")
            //|| wcsstr(str, L"/ddash")
            || wcsstr(str, L"/beamSwdC_hit")
            || wcsstr(str, L"/atk_fire")
            
            ) {
             WWORD(thisP, 124, 12);
        }
        else if (
            wcsstr(str, L"/dwarfsilver_")
            /*|| wcsstr(str, L"/atk_fire")*/
            || wcsstr(str, L"/atk_water")
            || wcsstr(str, L"/atk_lightning")
            || wcsstr(str, L"/atk_darklightning")
            ) {
            WWORD(thisP, 124, 8);
        }
        else if (wcsstr(str, L"/punch12_hit")
            ) {
            WWORD(thisP, 124, 5);
        }
        else if (wcsstr(str, L"/hk_tech")

            ) {
             WWORD(thisP, 124, 4);
        }
        //else if (wcsstr(str, L"hit")) {
        //    WWORD(thisP, 124, 20);
        //}
        else {
            WWORD(thisP, 124, 3);
        }
    }
    return ret;
}

thisCall1Args2 EffectSoundChannel__Constructor_119F050 = (thisCall1Args2)0x119F050;
int __fastcall hookEffectSoundChannel__Constructor_119F050(int* thisP, int, wchar_t* str) {
    if (wcsstr(str, L"hk_") || wcsstr(str, L"hk1_") || wcsstr(str, L"hk2_")) {
        WBYTE(thisP, 0x238, 255);
        //WDWORD(thisP, 0x23A, 0x3F666666);//0.9f
    }
    //else if (wcsstr(str, L"dstraight_hit") || wcsstr(str, L"\\punch") || wcsstr(str, L"\\upper_hit")) {
    //    WBYTE(thisP, 0x238, 198);
    //    WDWORD(thisP, 0x23A, 0x3F800000);
    //}
    else {
        WBYTE(thisP, 0x238, 0);
    }
    return EffectSoundChannel__Constructor_119F050(thisP, (int)str);
}


stdCall2 FMOD__Channel__setPriority = (stdCall2)0x013B699E;
int __stdcall hookFMOD__Channel__setPriority(int a1, int a2) {
    int *soundChannel = 0;
    __asm mov soundChannel, ebx;
    if (soundChannel && *soundChannel == 0x18515D0 && RBYTE(soundChannel, 0x238)) {
        a2 = RBYTE(soundChannel, 0x238);
    }
    //printf("setPriority[0x%08x, %d]\n", a1, a2);
    return FMOD__Channel__setPriority(a1, a2);
}

stdCall2 FMOD__Channel__setVolume = (stdCall2)0x013B6974;
int __stdcall hookFMOD__Channel__setVolume(int a1, int a2) {
    //int* soundChannel = 0;
    //__asm mov soundChannel, ebx;
    //if (soundChannel && *soundChannel == 0x18515D0 && RBYTE(soundChannel, 0x238)) {
    //    a2 = RDWORD(soundChannel, 0x23A);
    //}
    printf("setVolume  [0x%08x, %f]\n", a1, *(float*)&a2);
    return FMOD__Channel__setVolume(a1, a2);
}

stdCall5 FMOD__System__playSound = (stdCall5)0x013B69A4;
int __stdcall hookFMOD__System__playSound(int system, int sound, int channelGroup, int paused, int channel) {
    int ret = FMOD__System__playSound(system, sound, channelGroup, paused, channel);
    printf("playSound  [0x%08x]\n", *(int *)channel);
    return ret;
}

thisCall5Args2 CNRDObject__playSound_7FBD90 = (thisCall5Args2)0x7FBD90;
void __fastcall hookCNRDObject__playSound_7FBD90(int* thisP, int, wchar_t* name, int a3, int a4, int a5, int a6) {
    if(name && wcscmp(name, L""))
        WDPRINTF(L"0x%08x play1:%s\n", (int)_ReturnAddress(), (wchar_t*)name);
    CNRDObject__playSound_7FBD90(thisP, (int)name, a3, a4, a5, a6);
}

void soundOptimizeInit() {
    static float SoundVolumeDecayRate = 3.8f;
    *(BYTE*)0x0119ABDE += 2;
    *(DWORD*)0x0119C829 += 6;
    *(DWORD*)0x0119C559 += 6;
    writeCallCode((void*)0x0119C582, hookEffectSoundChannel__Constructor_119F050);
    writeCallCode((void*)0x0119C852, hookEffectSoundChannel__Constructor_119F050);
    *(DWORD*)0x01851498 = (int)hookEffectSound__parse_119E850;

    GumInterceptor* v = gum_interceptor_obtain();

    *(BYTE*)0x01197205 = 8;
    *(DWORD*)0x01197207 = 0x1800;
    *(BYTE*)0x01197971 = 0x00; //背景音乐最高优先级
    *(BYTE*)0x01197264 = 108;//音效并发通道 默认15
    *(BYTE*)0x0119727C = 108;
    *(BYTE*)0x0119726B = 10;//背景音效并发通道 默认10
    *(BYTE*)0x01197283 = 118;//总音效并发通道
    *(BYTE*)0x0119A6F4 = 2;//相同音效最大并发数，默认3

    f = (void *)0x011985D0;
    writeJmpCode((void*)0x011987BF, fixMaxSoundCount);
    *(BYTE*)0x011989F8 = 0xC7;//a12风格 声音源最近优先级最高
    *(WORD*)0x011989FC = 0xC801;//a12风格 声音源最近优先级最高
    //*(BYTE*)0x01198A60 = 0x58;
    //*(DWORD*)0x011989E8 = 0x40000001;
    *(DWORD*)0x01198A5A = (int) & SoundVolumeDecayRate;

    writeCallCode((void*)0x01198A19, hookFMOD__Channel__setPriority);
    //writeCallCode((void*)0x01198ADE, hookFMOD__Channel__setVolume);
    //writeCallCode((void*)0x01198912, hookFMOD__System__playSound);
    gum_interceptor_replace_fast(v, (gpointer)0x7FBD90, (gpointer)hookCNRDObject__playSound_7FBD90, (gpointer*)&CNRDObject__playSound_7FBD90);
    //gum_interceptor_replace_fast(v, (gpointer)0x11985D0, (gpointer)hookPlayEffectOrEnvSound_11985D0, (gpointer*)&playEffectOrEnvSound_11985D0);
    

   
}

