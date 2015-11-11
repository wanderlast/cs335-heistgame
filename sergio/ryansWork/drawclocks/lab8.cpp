//cs371 Fall 2014
//
//program: lab8.cpp
//author:  Gordon Griesel
//date:    2014
//
//This program demonstrates the use of OpenGL and XWindows
//
//
//Assignment:
//  1. Make the metronome work
//  2. Make hand shadows show on the numeral spots 
//  3. Make clock work without glRotate, glTranslate
//     Use matrix.c, matrix.h
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "log.h"
#include "fonts.h"

typedef float Flt;
#define PI 3.1415926535897932384626433832795
#define degrees_to_radians(d)  ((d) * PI / 180.0)
#define SWAP(x,y) (x)^=(y);(y)^=(x);(x)^=(y)

//X Windows variables
Display *dpy;
Window win;
GLXContext glc;

//Function prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e);
void check_keys(XEvent *e);
void physics(void);
void render(void);

//Global variables
int done=0;
int xres=200, yres=300;
float bigHand    = 90.0;
float littleHand = 90.0;
float secondHand = 90.0;
float handIncrement = 6.0;
int useUsleep=0;
int nRevolutions=0;

//Setup timers-------------------------------------------------------
struct timespec res;
struct timespec timeStart, timeCurrent;
double physicsCountdown=0.0;
double timeSpan=0.0;
int child=0;
//
struct timespec timePause;
int metronome=0;
unsigned int uPause=0;
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
			(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//-------------------------------------------------------------------


int main(int argc, char *argv[])
{
	initXWindows();
	init_opengl();
	logOpen();
	//
	//Display clock resolution...
	if (clock_getres(CLOCK_REALTIME, &res) < 0) {
		printf("clock_getres error!\n");
	}
	//printf("tv_sec: %li\n", res.tv_sec);
	//printf("tv_nsec: %li\n", res.tv_nsec);
	//
	if (argc > 0) {
		printf("argc: %i argv[0] **%s**\n", argc, argv[0]);
		if (*argv[0]=='1') {
			//This happens when a user presses X in a
			//running openglClock process.
			child = 1;
			handIncrement = 360.0 * physicsRate;
			metronome = 1;
			nRevolutions = 0;
		}
	}
	//
	//Important to init timers before starting loop!
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	//
	while(!done) {
		while(XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_resize(&e);
			check_mouse(&e);
			check_keys(&e);
		}
		//
		//Apply physics at a consistent rate
		//
		//1. Get the time right now.


		//
		//2. How long since we were here last?


		//
		//3. Save the current time as our new starting time.


		//
		//4. Add time-span to our countdown amount.


		//
		//5. Has countdown gone beyond our physics rate? 
		//       if yes,
		//           In a loop...
		//              Apply physics
		//              Reducing countdown by physics-rate.
		//              Break when countdown < physics-rate.
		//       if no,
		//           Apply no physics this frame.
		//
		if (metronome) {
			while(physicsCountdown >= physicsRate) {
				//6. Apply physics


				//7. Reduce the countdown by our physics-rate


			}
		} else {
			physics();
		}
		//
		//
		//Always render every frame.
		render();
		glXSwapBuffers(dpy, win);
		//
		if (useUsleep) {
			//-------------------------------------------------------
			//This is just for testing to mix-up the program speed
			//Sleep for an unknown amount of time...
			timeSpan = timeDiff(&timePause, &timeCurrent);
			//Log("timeSpan: %lf\n",timeSpan);
			if (timeSpan > 2.123) {
				uPause = rand()%200000;
				//Log("pause: %u\n",pause);
				timeCopy(&timePause, &timeCurrent);
			}
			usleep(uPause);
			//-------------------------------------------------------
		}
	}
	cleanupXWindows();
	cleanup_fonts();
	logClose();
	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void set_title(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "CS371 OpenGL Animation");
}

void setup_screen_res(const int w, const int h)
{
	xres = w;
	yres = h;
}

void initXWindows(void)
{
	Window root;
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;

	setup_screen_res(xres, yres);
	dpy = XOpenDisplay(NULL);
	if(dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(EXIT_FAILURE);
	}
	root = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);
	if(vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(EXIT_FAILURE);
	} 
	//else {
	//	// %p creates hexadecimal output like in glxinfo
	//	printf("\n\tvisual %p selected\n", (void *)vi->visualid);
	//}
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
						StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
							vi->depth, InputOutput, vi->visual,
							CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}

void reshape_window(int width, int height)
{
	//window has been resized.
	setup_screen_res(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, xres, 0, yres, -1, 1);
	set_title();
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, xres, yres);
	//init matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
}

void check_resize(XEvent *e)
{
	//Respond to ConfigureNotify.
	//Event sent by the server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	//Has window size changed?
	if (xce.width != xres || xce.height != yres) {
		reshape_window(xce.width, xce.height);
	}
}

void check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) { }
		if (e->xbutton.button==3) { }
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
}

void initMetronome(void)
{
	metronome = 1;
	nRevolutions=0;
	bigHand    = 90.0;
	littleHand = 90.0;
	secondHand = 90.0;
	handIncrement = 360.0 * physicsRate;
	nRevolutions=0;
	physicsCountdown=0.0;
	timeSpan=0.0;
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
}

void startAnotherClock(void)
{
	pid_t pid;
	pid = fork();
	switch (pid) {
		case -1:
			perror("fork");
			break;
		case 0:
			execl("./lab8", "1", (char *)0);
			perror("exec");
			break;
	//	default:
	//	{
	//		int status;
	//		printf("Child id: %i\n", pid);
	//		fflush(NULL);
	//		if (waitpid(pid, &status, 0) != -1) {
	//			printf("Child exited with status %i\n", status);
	//		} else {
	//			perror("waitpid");
	//		}
	//		break;
	//	}
	}
}

void check_keys(XEvent *e)
{
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyRelease) {
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return;
	}
	if (e->type == KeyPress) {
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=1;
	} else {
		return;
	}
	switch(key) {
		case XK_m:
			metronome ^= 1;
			if (metronome) {
				initMetronome();
			}
			break;
		case XK_u:
			uPause = 0;
			useUsleep ^= 1;
			break;
		case XK_x:
			if (child)
				break;
			child=1;
			startAnotherClock();
			initMetronome();
			break;
		case XK_equal:
			handIncrement += 1.0f;
			break;
		case XK_minus:
			handIncrement -= 1.0f;
			break;
		case XK_Escape:
			done=1;
			break;
	}
	if (shift){}
}



void clock_animation(void)
{
	//Draw a clock face
	//Dimensions are proportional to the width of the window.
	//
	int i;
	float ang;
	float len, wid, len2, len4;
	//x,y is clock center
	float x = xres/2.0;
	float y = yres/2.0 - 40.0;
	//
	//Draw clock hands
	//
	//second hand shadow
	len = (float)(xres / 4);
	wid = 1.0;
	len2 = len / 2.0;
	len4 = len / 4.0;
	glPushMatrix();
	glTranslatef(x+8, y-8, 0.0);
	glRotatef(secondHand, 0.0, 0.0, 1.0);
	glColor3ub(230,230,230);
	glBegin(GL_QUADS);
		glVertex2i(-len2, -wid);
		glVertex2i(-len2,  wid);
		glVertex2i( len,   wid);
		glVertex2i( len,  -wid);
		glVertex2i(-len4, -wid*4);
		glVertex2i(-len4,  wid*4);
		glVertex2i(-len2,  wid*4);
		glVertex2i(-len2, -wid*4);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*5.0);
		glVertex2i(len+24.0, 0.0);
		glVertex2i(len,      wid*5.0);
	glEnd();
	glPopMatrix();
	//
	//big hand shadow
	len = (float)(xres / 6);
	wid = 4.0;
	glPushMatrix();
	glTranslatef(x+6,y-6,0.0);
	glRotatef(bigHand, 0.0, 0.0, 1.0);
	glColor3ub(230,230,230);
	glBegin(GL_QUADS);
		glVertex2i(0,   -wid);
		glVertex2i(0,    wid);
		glVertex2i(len,  wid);
		glVertex2i(len, -wid);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*2.0);
		glVertex2i(len+20.0, 0.0);
		glVertex2i(len,      wid*2.0);
	glEnd();
	glPopMatrix();
	//
	//little hand shadow
	len = (float)(xres / 10);
	wid = 4.0;
	glPushMatrix();
	glTranslatef(x+4, y-4, 0.0);
	glRotatef(littleHand, 0.0, 0.0, 1.0);
	glColor3ub(230, 230, 230);
	glBegin(GL_QUADS);
		glVertex2i(0,   -wid);
		glVertex2i(0,    wid);
		glVertex2i(len,  wid);
		glVertex2i(len, -wid);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*2.5);
		glVertex2i(len+10.0, 0.0);
		glVertex2i(len,      wid*2.5);
	glEnd();
	glPopMatrix();
	//
	//
	//clock face
	//
	//Numeral spots
	for (i=0; i<12; i++) {
		glPushMatrix();
		glTranslatef(x, y, 0.0);
		glRotatef((360.0/12.0)*(float)i, 0.0, 0.0, 1.0);
		glTranslatef(xres/4.0+20.0, 0.0, 0.0);
		glColor3ub(250,200,200);
		glBegin(GL_QUADS);
			glVertex2i(-12, -12);
			glVertex2i(-12,  12);
			glVertex2i( 12,  12);
			glVertex2i( 12, -12);
		glEnd();
		glPopMatrix();
	}
	//
	//big hand
	glColor3ub(60,60,60);
	glPushMatrix();
	len = (float)(xres / 5);
	wid = 4.0;
	glTranslatef(x,y,0.0);
	glRotatef(bigHand, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2i(0,   -wid);
		glVertex2i(0,    wid);
		glVertex2i(len,  wid);
		glVertex2i(len, -wid);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*2.0);
		glVertex2i(len+20.0, 0.0);
		glVertex2i(len,      wid*2.0);
	glEnd();
	glPopMatrix();
	//
	//little hand
	glColor3ub(60, 60, 60);
	glPushMatrix();
	len = (float)(xres / 8);
	wid = 4.0;
	glTranslatef(x, y, 0.0);
	glRotatef(littleHand, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2i(0,   -wid);
		glVertex2i(0,    wid);
		glVertex2i(len,  wid);
		glVertex2i(len, -wid);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*2.5);
		glVertex2i(len+10.0, 0.0);
		glVertex2i(len,      wid*2.5);
	glEnd();
	glPopMatrix();
	//
	//second hand
	glColor3ub(200,60,90);
	glPushMatrix();
	len = (float)(xres / 4);
	wid = 1.0;
	glTranslatef(x, y, 0.0);
	glRotatef(secondHand, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2i(-len2, -wid);
		glVertex2i(-len2,  wid);
		glVertex2i(len,  wid);
		glVertex2i(len, -wid);
		glVertex2i(-len4, -wid*4);
		glVertex2i(-len4,  wid*4);
		glVertex2i(-len2,  wid*4);
		glVertex2i(-len2, -wid*4);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2i(len,     -wid*5.0);
		glVertex2i(len+24.0, 0.0);
		glVertex2i(len,      wid*5.0);
	glEnd();
	glPopMatrix();
	//
	//dot at center of clock
	glColor3ub(250,60,90);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (i=0; i<12; i++) {
		ang = (float)i * (PI/6.0);
		glVertex2f(cos(ang) * 10.0f, sin(ang) * 10.0f);
	}
	glEnd();
	glPopMatrix();
}

void physics(void)
{
	secondHand -= handIncrement;
	if (secondHand <= -360.0) {
		nRevolutions++;
		secondHand += 360.0;
	}
	bigHand -= handIncrement / 60.0;
	littleHand -= handIncrement / 60.0 / 12.0;
}

void render(void)
{
	Rect r;
	glClear(GL_COLOR_BUFFER_BIT);
	clock_animation();
	r.left=8;
	r.bot=yres-30;
	r.center=0;
	ggprint16(&r, 24, 0x00990000, "Metronome: %s", (metronome)?"ON":"OFF");
	ggprint16(&r, 24, 0, "Step: %3.0lf", handIncrement);
	ggprint16(&r, 24, 0, "usleep(%u)", uPause);
}



