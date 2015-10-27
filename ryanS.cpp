//CLOCK SOURCE CODE. NEEDS TO BE IMPLEMENTED TO SNAKE FRAMEWORKS AND 
//REDRAWN AS A WHOLE. THIS IS JUST THE START. :)

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


void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e);
void check_keys(XEvent *e);
void physics(void);
void render(void);


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
	len = (float)(xres / 4); //CHANGE THIS TO A SMALLER VALUE
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

void clockPhysics(void)
{
	secondHand -= handIncrement;
	if (secondHand <= -360.0) {
		nRevolutions++;
		secondHand += 360.0;
	}
	bigHand -= handIncrement / 60.0;
	littleHand -= handIncrement / 60.0 / 12.0;
}

void clockRender(void)
{
	Rect r;
	glClear(GL_COLOR_BUFFER_BIT);
	clock_animation();
	r.left=8;
	r.bot=yres-30;
	r.center=0;
}
