//Author: Ryan Shephard
//Purpose: Create a portable clock that can be used in any OpenGL program
//         and to make a credit screen. :)
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "ppm.h"
#include "main.h"
#include "thomasE.h"
#include "lianneL.h"
extern "C" {
#include "fonts.h"
}

using namespace std;

enum gameModes { scoreAttackEasy, timeAttackEasy, scoreAttack,
                 timeAttack, scoreAttackHard, timeAttackHard
               };

typedef float Flt;
#define PI 3.1415926535897932384626433832795
#define degrees_to_radians(d)  ((d) * PI / 180.0)


//Function prototypes
void clock_physics();
void clock_animation();
void checkCreditKeys();
void checkCreditMouse();
void creditScreen();
void creditButton();

//X Windows variables
//GLXContext glc;


typedef struct t_button {
    Rect r;
    char text[32];
    int over;
    int down;
    int click;
    float color[3];
    float dcolor[3];
    unsigned int text_color;
} Button;

Button credits[0];

//Global variables
int xres2=200, yres2=300;
float bigHand    = 90.0;
float handIncrement = 6.0;


//NOTE:
//physics(); //THIS IS WHERE CLOCK_PHYSICS BELONGS




//This function draws the clock hands, face, and just the clock in general.
void clock_animation()
{
    //Draw a clock face
    //Dimensions are proportional to the width of the window.
    //
    int i;
    float ang;
    float len, wid;
    //x,y is clock center
    //float x = xres2/2.0;
    //float y = yres2/2.0 - 40.0;
    float x = 700;
    float y = 450;
    //
    //Draw clock hands
    //
    //big hand shadow
    len = (float)(xres2 / 6);
    wid = 4.0;
    glPushMatrix();
    glTranslatef(x+6,y-6,0.0);
    glRotatef(bigHand, 0.0, 0.0, 1.0);
    glColor3ub(230,230,230);
    glBegin(GL_QUADS);
    glVertex2i(0, -wid);
    glVertex2i(0, wid);
    glVertex2i(len, wid);
    glVertex2i(len, -wid);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(len, -wid*2.0);
    glVertex2i(len+20.0, 0.0);
    glVertex2i(len, wid*2.0);
    glEnd();
    glPopMatrix();
    //
    //
    //
    //clock face
    //
    //Numeral spots
    for (i=0; i<12; i++) {
        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glRotatef((360.0/12.0)*(float)i, 0.0, 0.0, 1.0);
        glTranslatef(xres2/4.0+20.0, 0.0, 0.0);
        glColor3ub(119,119,119);
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
    len = (float)(xres2 / 5);
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
    //dot at center of clock
    glColor3ub(0,0,1);
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


//This function is threaded in with Lianne's code
//It sets the time for the game mode based off the enums Lianne created.
void clock_physics(int select)
{

    int seconds;
    //cout << "RYAN: GAME MODE SELECTED IS" << select;
    switch(select) {
    case scoreAttackEasy:
        //gameTypeSelector(scoreAttackEasy);
        seconds = (bigHand -= (handIncrement / 60.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    case timeAttackEasy:
        //gameTypeSelector(timeAttackEasy);
        seconds = (bigHand -= (handIncrement / 60.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    case scoreAttack:
        //gameTypeSelector(scoreAttack);
        seconds = (bigHand -= (handIncrement / 45.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    case timeAttack:
        //gameTypeSelector(timeAttack);
        seconds = (bigHand -= (handIncrement / 45.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    case scoreAttackHard:
        //gameTypeSelector(scoreAttackHard);
        seconds = (bigHand -= (handIncrement / 30.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    case timeAttackHard:
        //gameTypeSelector(timeAttackHard);
        seconds = (bigHand -= (handIncrement / 30.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;

    default:
        seconds = (bigHand -= (handIncrement / 60.0));
        seconds = (bigHand -= (handIncrement / 60.0));
        if(seconds == -255) {
            level = 2;
            break;
        }
        break;
    }
}

//This function creates me credits button.
void creditButton()
{
    Rect r;
    int nbuttons, i;

    //initalize buttons
    nbuttons = 0;
    //score challange button setting
    credits[nbuttons].r.width = 140;
    credits[nbuttons].r.height = 60;
    credits[nbuttons].r.left = 125;
    credits[nbuttons].r.bot =  250;
    credits[nbuttons].r.right =
        credits[nbuttons].r.left + credits[nbuttons].r.width;
    credits[nbuttons].r.top = credits[nbuttons].r.bot +
                              credits[nbuttons].r.height;
    credits[nbuttons].r.centerx = (credits[nbuttons].r.left +
                                   credits[nbuttons].r.right) / 2;
    credits[nbuttons].r.centery = (credits[nbuttons].r.bot +
                                   credits[nbuttons].r.top) / 2;
    strcpy(credits[nbuttons].text, "Credits");
    credits[nbuttons].down = 0;
    credits[nbuttons].click = 0;
    credits[nbuttons].color[0] = 0.4f;
    credits[nbuttons].color[1] = 0.4f;
    credits[nbuttons].color[2] = 0.4f;
    credits[nbuttons].dcolor[0] = credits[nbuttons].color[0] * 0.5f;
    credits[nbuttons].dcolor[1] = credits[nbuttons].color[1] * 0.5f;
    credits[nbuttons].dcolor[2] = credits[nbuttons].color[2] * 0.5f;
    credits[nbuttons].text_color = 0x00ffffff;
    nbuttons++;

    //=============== END OF BUTTONS
    //draw all buttons
    for (i=0; i<2; i++) {
        if (credits[i].over) {
            int w=2;
            glColor3f(1.0f, 1.0f, 0.0f);
            //draw a highlight around button
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            glVertex2i(credits[i].r.left-w,  credits[i].r.bot-w);
            glVertex2i(credits[i].r.left-w,  credits[i].r.top+w);
            glVertex2i(credits[i].r.right+w, credits[i].r.top+w);
            glVertex2i(credits[i].r.right+w, credits[i].r.bot-w);
            glVertex2i(credits[i].r.left-w,  credits[i].r.bot-w);
            glEnd();
            glLineWidth(1);
        }
        if (credits[i].down) {
            glColor3fv(credits[i].dcolor);
        } else {
            glColor3fv(credits[i].color);
        }
        glBegin(GL_QUADS);
        glVertex2i(credits[i].r.left,  credits[i].r.bot);
        glVertex2i(credits[i].r.left,  credits[i].r.top);
        glVertex2i(credits[i].r.right, credits[i].r.top);
        glVertex2i(credits[i].r.right, credits[i].r.bot);
        glEnd();
        r.left = credits[i].r.centerx;
        r.bot  = credits[i].r.centery-8;
        r.center = 1;
        if (credits[i].down) {
            ggprint16(&r, 0, credits[i].text_color, "Schwifty");
        } else {
            ggprint16(&r, 0, credits[i].text_color, credits[i].text);
        }
    }

}

void checkCreditKeys(XEvent *e)
{
    static int shift=0;
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyRelease) {
        if (key == XK_Shift_L || key == XK_Shift_R)
            shift=0;
        return;
    }
    if (e->type == KeyPress) {
        if (key == XK_Shift_L || key == XK_Shift_R) {
            shift=1;
            return;
        }
    } else {
        return;
    }
    if (shift) {}

    switch(key) {
    case XK_r:
        treasureScore = 0;
        level = 1;
        resetGame();
        break;
    case XK_Escape:
        done = 1;
        level = 1;
    }
}

void checkCreditMouse(XEvent *e)
{
    static int savex = 0;
    static int savey = 0;
    int i,x,y;
    int lbutton=0;
    int rbutton=0;
    //
    if (e->type == ButtonRelease)
        return;
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button is down
            lbutton=1;
        }
        if (e->xbutton.button==3) {
            //Right button is down
            rbutton=1;
            if (rbutton) {}
        }
    }
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = yres - y;
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
        //Mouse moved
        savex = e->xbutton.x;
        savey = e->xbutton.y;
    }
    for (i=0; i<2; i++) {
        credits[i].over=0;
        if (x >= credits[i].r.left &&
                x <= credits[i].r.right &&
                y >= credits[i].r.bot &&
                y <= credits[i].r.top) {
            credits[i].over=1;
            if (credits[i].over) {
                if (lbutton) {
                    switch(i) {
                    case 0:
                        level = 1;
                        creditScreen();
                        break;
                    }
                }
            }
        }
    }
    return;
}

//The Credit screen function.
//This loads in the ppm once the creditButton has been pushed

void creditScreen()
{
    Ppmimage *startImage;
    startImage=NULL;
    GLuint startTexture;
    // Rect r;

    //OpenGL initialization
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    glEnable(GL_TEXTURE_2D);
    //marble_texture = loadBMP("marble.bmp");
    glBindTexture(GL_TEXTURE_2D, 0);

    //load the image file into a ppm structure.
    startImage = ppm6GetImage("./images/credits.ppm");

    //create opengl texture elements
    glGenTextures(1, &startTexture);
    glBindTexture(GL_TEXTURE_2D, startTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 startImage->width, startImage->height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, startImage->data);

    //set the viewing area on screen
    glViewport(0, 0, xres, yres);

    //clear color buffer
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //this sets to 2D mode (no perspective)
    glOrtho(0, xres, 0, yres, -1, 1);

    //screen background
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, startTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(0,      0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(0,      yres);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(xres, yres);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(xres, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}





//Working Code, but for a different use.
/*
if(select == 1)
{
	seconds = (bigHand -= (handIncrement / 180.0));  <========This is meant for the time. And it works perfectly :)
	if(seconds == -255)
	{
		level = 2;
	}
}

else(gameModes == 2)
{
	bigHand = 90;
}

else if (gameModes == 3)
{
	//clock_animation();
	seconds = (bigHand += (handIncrement / 45.0));
	if(seconds == -9000)
	{
		level = 2;
	}
}

else if (gameModes == 4)
{
	bigHand = 90;
}
*
//THIS IS WHERE REALLY OLD COLD STARTS
int seconds;
if(level != 1) {
bigHand = 90;
//seconds = 90;
} else {
seconds = (bigHand -= (handIncrement / 10.0)); //THIS CHANGES THE TIME OF THE GAME
//cout << seconds << endl;
if(seconds == -255) {
    bigHand = 90;
    level = 2;
    //highScore(score);

}
}
*/


