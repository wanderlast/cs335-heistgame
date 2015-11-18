//Author: Ryan Shephard
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "main.h"
#include "thomasE.h"
#include "lianneL.h"

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

//X Windows variables
//GLXContext glc;

//Global variables
int xres2=200, yres2=300;
float bigHand    = 90.0;
float handIncrement = 6.0;

//physics(); //THIS IS WHERE CLOCK_PHYSICS BELONGS

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

void clock_physics(int select)
{
	
	int seconds;
	
	switch(select)
	{
		cout << "RYAN: GAME MODE SELECTED IS" << select;
		
		case scoreAttackEasy:
			//gameTypeSelector(scoreAttackEasy);
			seconds = (bigHand -= (handIncrement / 15.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
			
		case timeAttackEasy:
			//gameTypeSelector(timeAttackEasy);
			seconds = (bigHand -= (handIncrement / 10.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
			
		case scoreAttack:
			//gameTypeSelector(scoreAttack);
			seconds = (bigHand -= (handIncrement / 50.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
		case timeAttack:
			//gameTypeSelector(timeAttack);
			seconds = (bigHand -= (handIncrement / 50.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
			
		case scoreAttackHard:
			//gameTypeSelector(scoreAttackHard);
			seconds = (bigHand -= (handIncrement / 30.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
			
		case timeAttackHard:
			//gameTypeSelector(timeAttackHard);
			seconds = (bigHand -= (handIncrement / 10.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
			
		default:
			seconds = (bigHand -= (handIncrement / 75.0));
			if(seconds == -255)
			{
				level = 2;
				break;
			}
		}
}	
			
			
			
			
			
			
			
		/*	
		if(select == 1)
		{
			seconds = (bigHand -= (handIncrement / 180.0));
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
 
 //TO DO:
 //MAKE KEY
 //MAKE CHAOS LEVEL?
 //ASSIGN TIME TO OTHER LEVELS
        }
    }
    */
