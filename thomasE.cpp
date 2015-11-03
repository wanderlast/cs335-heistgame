//cs335 Fall 2015 Project Component
//author:
//
//This is a bootstrap code file to begin working off of.
//Please remove any includes or files that are unnecessary
//for what you are working on.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
#include "log.h"
extern "C" {
  #include "fonts.h"
}
//#define WINDOW_WIDTH  1300
//#define WINDOW_HEIGHT 800

//X Windows variables
Display *dpy;
Window win;
GLXContext glc;

int xres=1300, yres=800;

//Structures
struct Vec {
	float x, y, z;
};

struct Longwall {
  float width;
  float height;
  float radius;
  Vec center;
};

struct Squarewall {
  float width;
  float height;
  float radius;
  Vec center;
};

struct Highwall {
  float width;
  float height;
  float radius;
  Vec center;
};


struct Map {
  Longwall longw[10];
  Squarewall squarew[10];
  Highwall highw[10];
  int n;
};

Ppmimage *backgroundImage=NULL;
GLuint backgroundTexture;

//Function Prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void render(Map *maze);
int check_keys(XEvent *e);
void buildLongwall(Map *maze, int num, float centerX, float centerY);
void buildSquarewall(Map *maze, int num, float centerX, float centerY);
void buildHighwall(Map *maze, int num, float centerX, float centerY);
void setup_screen_res(const int w, const int h);

int main(void)
{

  int done=0;
  srand(time(NULL));
  initXWindows();
  init_opengl();

  //declare game object
  Map maze;
  maze.n=0;

  buildLongwall(&maze, 0, 150, -15);
  buildLongwall(&maze, 1, 450, -15);
  buildLongwall(&maze, 2, 750, -15);
  buildLongwall(&maze, 3, 1050, -15);
  buildLongwall(&maze, 4, 900, 830);
  buildLongwall(&maze, 5, 600, 830);
  buildLongwall(&maze, 6, 300, 830);
  buildLongwall(&maze, 7, 325, 480);
  
  buildHighwall(&maze, 0, -15, 150);
  buildHighwall(&maze, 1, -15, 450);
  buildHighwall(&maze, 2, -15, 750);
  buildHighwall(&maze, 3, 1300, 650);
  buildHighwall(&maze, 3, 1300, 350);
  
  buildSquarewall(&maze, 0, 225, 480);
  buildSquarewall(&maze, 1, 1150, 660);
  buildSquarewall(&maze, 2, 700, 80);

  //start animation
  while(!done) {
    while(XPending(dpy)) {
      XEvent e;
      XNextEvent(dpy, &e);
      done = check_keys(&e);
    }
    render(&maze);
    glXSwapBuffers(dpy, win);
 }

  cleanupXWindows();
  
  return 0;
}

void set_title(void)
{
  //Set the window title bar.
  XMapWindow(dpy, win);
  XStoreName(dpy, win, "335 Game Project Test");
}

void cleanupXWindows(void) {
  //do not change
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
}

void initXWindows(void) 
{

  GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
  //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
  XSetWindowAttributes swa;
  setup_screen_res(xres, yres);
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    std::cout << "\n\tcannot connect to X server\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  Window root = DefaultRootWindow(dpy);
  XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
  if (vi == NULL) {
    std::cout << "\n\tno appropriate visual found\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
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

void setup_screen_res(const int w, const int h)
{
	xres = w;
	yres = h;
}

void init_opengl(void)
{
  //OpenGL initialization
  glViewport(0, 0, xres, yres);
  //Initialize matrices
  glMatrixMode(GL_PROJECTION); glLoadIdentity();
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
  //Set 2D mode (no perspective)
  glOrtho(0, xres, 0, yres, -1, 1);
  //Set the screen background color
  glClearColor(1.0, 1.0, 1.0, 1.0);


  //Do this to allow fonts
  glEnable(GL_TEXTURE_2D);
  initialize_fonts();
  //
  //load the images file into a ppm structure.
  //
  backgroundImage = ppm6GetImage("./images/background.ppm");
  //
  //create opengl texture elements
  glGenTextures(1, &backgroundTexture);
  //-------------------------------------------------------------------------
  //
  //background
  glBindTexture(GL_TEXTURE_2D, backgroundTexture);
  //
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
  backgroundImage->width, backgroundImage->height,
  0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImage->data);
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------

}


int check_keys(XEvent *e)
{
  //Was there input from the keyboard?
  if (e->type == KeyPress) {
    int key = XLookupKeysym(&e->xkey, 0);
      if (key == XK_Escape) {
        return 1;
      }
      //You may check other keys here.
    }
  return 0;
}

void buildLongwall(Map *maze, int num, float centerX, float centerY)
{

  maze->longw[num].center.x = centerX;
  maze->longw[num].center.y = centerY;
  maze->longw[num].width = 300;
  maze->longw[num].height = 80;

  return;
}

void buildSquarewall(Map *maze, int num, float centerX, float centerY)
{

  maze->squarew[num].center.x = centerX;
  maze->squarew[num].center.y = centerY;
  maze->squarew[num].width = 160;
  maze->squarew[num].height = 160;

  return;
}

void buildHighwall(Map *maze, int num, float centerX, float centerY)
{

  maze->highw[num].center.x = centerX;
  maze->highw[num].center.y = centerY;
  maze->highw[num].width = 80;
  maze->highw[num].height = 300;

  return;
}


void render(Map *maze)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  ///Draw background
  glColor3f(1.0, 1.0, 1.0);
  glBindTexture(GL_TEXTURE_2D, backgroundTexture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
  glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
  glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
  glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
  glEnd();
  
  //Draw shapes...

  //draw box
  
  for (int j=0; j<10; j++) {
    Longwall *l;
    glColor3ub(140,140,140);
    //glColor3f(1.0, 1.0, 1.0);
    l = &maze->longw[j];
    glPushMatrix();
    glTranslatef(l->center.x, l->center.y, l->center.z);
  
    glBegin(GL_QUADS);
      glVertex2i(-l->width,-l->height);
      glVertex2i(-l->width, l->height);
      glVertex2i( l->width, l->height);
      glVertex2i( l->width,-l->height);
  
    glEnd();
    glPopMatrix();
  }

  for (int j=0; j<10; j++) {
    Squarewall *s;
    glColor3ub(140,140,140);
    //glColor3f(1.0, 1.0, 1.0);
    s = &maze->squarew[j];
    glPushMatrix();
    glTranslatef(s->center.x, s->center.y, s->center.z);
  
    glBegin(GL_QUADS);
      glVertex2i(-s->width,-s->height);
      glVertex2i(-s->width, s->height);
      glVertex2i( s->width, s->height);
      glVertex2i( s->width,-s->height);
  
    glEnd();
    glPopMatrix();
  }
  
  for (int j=0; j<10; j++) {
    Highwall *h;
    glColor3ub(140,140,140);
    //glColor3f(1.0, 1.0, 1.0);
    h = &maze->highw[j];
    glPushMatrix();
    glTranslatef(h->center.x, h->center.y, h->center.z);
  
    glBegin(GL_QUADS);
      glVertex2i(-h->width,-h->height);
      glVertex2i(-h->width, h->height);
      glVertex2i( h->width, h->height);
      glVertex2i( h->width,-h->height);
  
    glEnd();
    glPopMatrix();
  }

}

