//Author: Sergio Alvarado
//Description: This cpp holds the sound functions, the start menu,
//the controls page, and the gamestate menu.
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
#include "main.h"
extern "C" {
#include "fonts.h"
}
using namespace std;

#define MAXBUTTONS 4

ALuint alSource;
ALuint alBuffer;

void cleanupSound();

int createSound(int soundNum)
{

    int loop;

//Get started right here.
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: alutInit()\n");
    }
//Clear error state.
    alGetError();
// Setup the listener.
// Forward and up vectors are used.
    float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

    // // Buffer holds the sound information.
//alBuffer[0] = alutCreateBufferFromFile("./cha-ching.wav");
//alBuffer[0] = alutCreateBufferFromFile("./theme.wav");

    switch(soundNum) {
    case 1 :
        loop = 1;
        alBuffer = alutCreateBufferFromFile("./theme.wav");
        alGenSources(1, &alSource);
        alSourcei(alSource, AL_BUFFER, alBuffer);
        break;

    case 2 :
        loop = 0;
        alBuffer = alutCreateBufferFromFile("./cha-ching.wav");
        alGenSources(1, &alSource);
        alSourcei(alSource, AL_BUFFER, alBuffer);
        break;

    case 3 :
        loop = 0;
        alBuffer = alutCreateBufferFromFile("./gameover.wav");
        alGenSources(1, &alSource);
        alSourcei(alSource, AL_BUFFER, alBuffer);
        break;

    case 4 :
        loop = 0;
        alBuffer = alutCreateBufferFromFile("./menu.wav");
        alGenSources(1, &alSource);
        alSourcei(alSource, AL_BUFFER, alBuffer);
        break;

    }

    // // Source refers to the sound.
    // // Generate a source, and store it in a buffer.
//alGenSources(1, &alSource);
//alSourcei(alSource, AL_BUFFER, alBuffer);

    if(!loop) {
        alSourcef(alSource, AL_GAIN, 1.0f);
        alSourcef(alSource, AL_PITCH, 1.0f);
        alSourcei(alSource, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
            printf("ERROR: setting source\n");
        }
        alSourcePlay(alSource);
        usleep(90);

    }


    if(loop == 1 && level == 1) {
        alSourcef(alSource, AL_GAIN, 1.0f);
        alSourcef(alSource, AL_PITCH, 1.0f);
        alSourcei(alSource, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
            printf("ERROR: setting source\n");
        }
        alSourcePlay(alSource);
        usleep(90000000);

    }


    /*
    	// // Set volume and pitch to normal, no looping of sound.
     alSourcef(alSource, AL_GAIN, 1.0f);
     alSourcef(alSource, AL_PITCH, 1.0f);
     alSourcei(alSource, AL_LOOPING, AL_FALSE);
     if (alGetError() != AL_NO_ERROR) {
     	printf("ERROR: setting source\n");
     }

    (
     if((loop = 1)) {
     for (int i=0; i<1; i++) {
    	 alSourcePlay(alSource);
    	 usleep(999900);
     }
     }
     */

    //alSourcePlay(alSource);
    //usleep(900000);

    return 0;
}

void cleanupSound()
{
    // First delete the source.
    alDeleteSources(1, &alSource);
    // // Delete the buffer.
    alDeleteBuffers(1, &alBuffer);
    // // Close out OpenAL itself.
    // // Get active context.
    ALCcontext *Context = alcGetCurrentContext();
    // // Get device for active context.
    ALCdevice *Device = alcGetContextsDevice(Context);
    // // Disable context.
    alcMakeContextCurrent(NULL);
    // // Release context(s).
    alcDestroyContext(Context);
    // // Close device.
    alcCloseDevice(Device);

    cout << "Sound has been cleaned " << endl;

}

void startMenu()
{

    Ppmimage *startImage;
    startImage=NULL;
    GLuint startTexture;
    Rect r;

    //OpenGL initialization
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    //
    //choose one of these
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    glEnable(GL_TEXTURE_2D);
    //marble_texture = loadBMP("marble.bmp");
    glBindTexture(GL_TEXTURE_2D, 0);

    //load the image file into a ppm structure.
    startImage = ppm6GetImage("./images/start.ppm");

    //create opengl texture elements
    glGenTextures(1, &startTexture);
    glBindTexture(GL_TEXTURE_2D, startTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 startImage->width, startImage->height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, startImage->data);

    //start the opengl stuff
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

    /*  glColor3ub(119,119,119);
      glPushMatrix();
      glBegin(GL_QUADS);
        glVertex2i(250, 400);
        glVertex2i(250, 400);
        glVertex2i(250, 400);
        glVertex2i(400, 250);
      glEnd();
      glPopMatrix();
    */

    r.left   = xres/2;
    r.bot    = yres-100;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Heist Game");

    r.left   = xres/2;
    r.bot    = yres-300;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Press SPACE to start!");

    r.left   = xres/2;
    r.bot    = yres-400;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Press Enter to view CONTROLS");


}

void infoMenu()
{

    Ppmimage *startImage;
    startImage=NULL;
    GLuint startTexture;
    Rect r;

    //OpenGL initialization
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    //
    //choose one of these
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    glEnable(GL_TEXTURE_2D);
    //marble_texture = loadBMP("marble.bmp");
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    //load the image file into a ppm structure.
    //
    startImage = ppm6GetImage("./images/start.ppm");
    //
    //create opengl texture elements
    glGenTextures(1, &startTexture);
    glBindTexture(GL_TEXTURE_2D, startTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 startImage->width, startImage->height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, startImage->data);

    //start the opengl stuff
    //set the viewing area on screen
    glViewport(0, 0, xres, yres);
    //clear color buffer
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //this sets to 2D mode (no perspective)
    glOrtho(0, xres, 0, yres, -1, 1);
    //

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

    r.left   = xres/2;
    r.bot    = yres-100;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Important Keys");

    r.left   = 200;
    r.bot    = yres-50;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "HIT SPACE TO PLAY GAME!");

    r.left   = 200;
    r.bot    = 375;
    ggprint16(&r, 16, 0x00ffffff, "--IN MENU--");

    r.left   = 500;
    r.bot    = 375;
    ggprint16(&r, 16, 0x00ffffff, "--IN GAME--");

    r.left   = 500;
    r.bot    = 330;
    ggprint16(&r, 16, 0x00ffffff, "Arrow Up: move up");

    r.left   = 500;
    r.bot    = 300;
    ggprint16(&r, 16, 0x00ffffff, "Arrow Down: move down");

    r.left   = 500;
    r.bot    = 270;
    ggprint16(&r, 16, 0x00ffffff, "Arrow Left: move left");

    r.left   = 500;
    r.bot    = 240;
    ggprint16(&r, 16, 0x00ffffff, "Arrow Right: move right");

    r.left   = 500;
    r.bot    = 375;
    ggprint16(&r, 16, 0x00ffffff, "--IN GAME--");

    r.left   = 200;
    r.bot    = 300;
    ggprint16(&r, 16, 0x00ffffff, "SPACE: start!");

    r.left   = 200;
    r.bot    = 330;
    ggprint16(&r, 16, 0x00ffffff, "R: restart");

}

void gamestateMenu()
{
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

    Ppmimage *startImage;
    startImage=NULL;
    GLuint startTexture;
    Rect r;
    int nbuttons, i;
    Button button[MAXBUTTONS];

    //OpenGL initialization
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    //
    //choose one of these
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    glEnable(GL_TEXTURE_2D);
    //marble_texture = loadBMP("marble.bmp");
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    //load the image file into a ppm structure.
    //
    startImage = ppm6GetImage("./images/start.ppm");
    //
    //create opengl texture elements
    glGenTextures(1, &startTexture);
    glBindTexture(GL_TEXTURE_2D, startTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 startImage->width, startImage->height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, startImage->data);

    //start the opengl stuff
    //set the viewing area on screen
    glViewport(0, 0, xres, yres);
    //clear color buffer
    //init matrices
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //this sets to 2D mode (no perspective)
    glOrtho(0, xres, 0, yres, -1, 1);
    //

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

    r.left   = xres/2;
    r.bot    = yres-100;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Heist Game");

    r.left   = xres/2;
    r.bot    = yres-300;
    r.center = 1;
    ggprint16(&r, 16, 0x00ffffff, "Choose A Game Mode!");

    //initalize buttons
    nbuttons = 0;
    //score challange button setting
    button[nbuttons].r.width = 140;
    button[nbuttons].r.height = 60;
    button[nbuttons].r.left = 250;
    button[nbuttons].r.bot = 160;
    button[nbuttons].r.right =
        button[nbuttons].r.left + button[nbuttons].r.width;
    button[nbuttons].r.top = button[nbuttons].r.bot +
                             button[nbuttons].r.height;
    button[nbuttons].r.centerx = (button[nbuttons].r.left +
                                  button[nbuttons].r.right) / 2;
    button[nbuttons].r.centery = (button[nbuttons].r.bot +
                                  button[nbuttons].r.top) / 2;
    strcpy(button[nbuttons].text, "Score Challange");
    button[nbuttons].down = 0;
    button[nbuttons].click = 0;
    button[nbuttons].color[0] = 0.4f;
    button[nbuttons].color[1] = 0.4f;
    button[nbuttons].color[2] = 0.4f;
    button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
    button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
    button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
    button[nbuttons].text_color = 0x00ffffff;
    nbuttons++;

    //time trial button settings
    button[nbuttons].r.width = 140;
    button[nbuttons].r.height = 60;
    button[nbuttons].r.left = 50;
    button[nbuttons].r.bot = 160;
    button[nbuttons].r.right =
        button[nbuttons].r.left + button[nbuttons].r.width;
    button[nbuttons].r.top = button[nbuttons].r.bot +
                             button[nbuttons].r.height;
    button[nbuttons].r.centerx = (button[nbuttons].r.left +
                                  button[nbuttons].r.right) / 2;
    button[nbuttons].r.centery = (button[nbuttons].r.bot +
                                  button[nbuttons].r.top) / 2;
    strcpy(button[nbuttons].text, "Time Trial");
    button[nbuttons].down = 0;
    button[nbuttons].click = 0;
    button[nbuttons].color[0] = 0.4f;
    button[nbuttons].color[1] = 0.4f;
    button[nbuttons].color[2] = 0.4f;
    button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
    button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
    button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
    button[nbuttons].text_color = 0x00ffffff;
    nbuttons++;

    //draw all buttons
    for (i=0; i<2; i++) {
        if (button[i].over) {
            int w=2;
            glColor3f(1.0f, 1.0f, 0.0f);
            //draw a highlight around button
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            glVertex2i(button[i].r.left-w,  button[i].r.bot-w);
            glVertex2i(button[i].r.left-w,  button[i].r.top+w);
            glVertex2i(button[i].r.right+w, button[i].r.top+w);
            glVertex2i(button[i].r.right+w, button[i].r.bot-w);
            glVertex2i(button[i].r.left-w,  button[i].r.bot-w);
            glEnd();
            glLineWidth(1);
        }
        if (button[i].down) {
            glColor3fv(button[i].dcolor);
        } else {
            glColor3fv(button[i].color);
        }
        glBegin(GL_QUADS);
        glVertex2i(button[i].r.left,  button[i].r.bot);
        glVertex2i(button[i].r.left,  button[i].r.top);
        glVertex2i(button[i].r.right, button[i].r.top);
        glVertex2i(button[i].r.right, button[i].r.bot);
        glEnd();
        r.left = button[i].r.centerx;
        r.bot  = button[i].r.centery-8;
        r.center = 1;
        if (button[i].down) {
            ggprint16(&r, 0, button[i].text_color, "Pressed!");
        } else {
            ggprint16(&r, 0, button[i].text_color, button[i].text);
        }
    }


}


