#include <X11/Xlib.h>

extern int createSound(int);
extern void cleanupSound();
extern void startMenu();
extern void infoMenu();
extern void gamestateMenu();
extern void checkgamestateMouse(XEvent *e);
extern int soundNum;

