#include "pch.h"
#include "common.h"
#include "frida-gum.h"
#include "tools.h"

thisCall7Args2 showMainWinText_94C830 = (thisCall7Args2)0x94C830;
int __fastcall hookShowMainWinText_94C830(int* thisP, int, int text, int time, int x, int y, int w, int h, int a8) {
	return showMainWinText_94C830(thisP, text, time, x - 80, y - 60, w, h, a8);

}

void actionInit(void) {
	GumInterceptor* v = gum_interceptor_obtain();
	gum_interceptor_replace_fast(v, (gpointer)0x94C830, (gpointer)hookShowMainWinText_94C830, (gpointer*)&showMainWinText_94C830);
}