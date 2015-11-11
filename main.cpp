//cs335 Spring 2014
//program: snake.cpp
//author:  Gordon Griesel
//purpose: Simple snake game
//
//
//notes:
//This may be used as the starting point for a class project.
//Students should add the following components:
//
//These items could be used to generate your requirements phase.
//
// . Introduction page
// . Title page
// . Credits page
// . Main menu
// . Snake texture
// . Rat texture
// . Levels
// . Changes in difficulty/speed
// . Scoring
// . Save high scores
// . Board texture
// . Sound
// . Special effects
// . Mouse dragging
// . Win and lose indication
// . Additional features
//
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
extern "C"{
	#include "fonts.h"
}
#include "main.h"
#include "sergioA.h"
#include "lianneL.h"
#include "kevinB.h"
#include "ryanS.h"
#include "thomasE.h"

using namespace std;

//macros
#define rnd() (double)rand()/(double)RAND_MAX

//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void initOpengl(void);
void cleanupXWindows(void);
void checkResize(XEvent *e);
void checkMouse(XEvent *e);
void checkKeys(XEvent *e);
void init();
int checkCollision();
void physics(void);
void render(void);
void getGridCenter(const int i, const int j, int cent[2]);
void resetGame();

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3
#define MAX_GRID 80
#define MAXBUTTONS 4
#define MAX_TREASURE 15
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

int x;
int xres;
int yres;
Grid grid[MAX_GRID][MAX_GRID];
Treasure treasure[MAX_TREASURE];
int done;
int level;
int start;
int gridDim;
int boardDim;
int gameover;
int winner;
int score;
Ppmimage *heistImage;
GLuint heistTexture;
int nbuttons;
Button button[MAXBUTTONS];
Player player;
Wall wall;
int treasureScore; // <- - - PUT TOTAL TREASURE VALUE HERE
//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
			(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------


int main(int argc, char *argv[])
{
	
	xres = 800;
	yres = 600;
	done = 0;
	start = 0;
	gridDim = 40;
	gameover = 0;
	winner = 0;
	nbuttons = 0;
	heistImage=NULL;	
	
	if (argc) {}
	if (argv[0]) {}
	logOpen();
	initXWindows();
	initOpengl();
//	initSound();
	init();
	initialize_fonts();
	srand((unsigned int)time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	
	while(!start) {  //game has not started
		while(XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			checkResize(&e);
			checkMouse(&e);
			checkKeys(&e);
		}
		startMenu();
		glXSwapBuffers(dpy, win);
	}
	
	level = 1;
	while(!done) {	
		if (level == 1){
			while(XPending(dpy)) {
				XEvent e;
				XNextEvent(dpy, &e);
				checkResize(&e);
				checkMouse(&e);
				checkKeys(&e);
			}
			//
			//Below is a process to apply physics at a consistent rate.
			//1. Get the time right now.
			clock_gettime(CLOCK_REALTIME, &timeCurrent);
			//2. How long since we were here last?
			timeSpan = timeDiff(&timeStart, &timeCurrent);
			//3. Save the current time as our new starting time.
			timeCopy(&timeStart, &timeCurrent);
			//4. Add time-span to our countdown amount.
			physicsCountdown += timeSpan;
			//5. Has countdown gone beyond our physics rate? 
			//       if yes,
			//           In a loop...
			//              Apply physics
			//              Reducing countdown by physics-rate.
			//              Break when countdown < physics-rate.
			//       if no,
			//           Apply no physics this frame.
			while(physicsCountdown >= physicsRate) {
				//6. Apply physics
				physics();
				//7. Reduce the countdown by our physics-rate
				physicsCountdown -= physicsRate;
			}
			//Always render every frame.
			render();
			glXSwapBuffers(dpy, win);
		}
	
	if(level == 2){
		done = 0;
		int randNumber = rand() % 100;
		
		int highScores[5];
		/*highScores[0] = 4;
		highScores[1] = 23;
		highScores[2] = 45;
		highScores[3] = 59;
		highScores[4] = 80; //< - - - UNIT TESTING*/
		readFile(highScores);
		calculateScore(randNumber, highScores);
		
		while(level == 2) {
			while(XPending(dpy)) {
				XEvent e;
				XNextEvent(dpy, &e);
				checkResize(&e);
				checkSKeys(&e);
			}
		
			highScore(randNumber, highScores);
			scoreSheet(highScores);
			glXSwapBuffers(dpy, win);
		}
	}
	}
	
	cleanupXWindows();
	cleanup_fonts();
	logClose();
	//exit(EXIT_SUCCESS);ls
	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void setTitle(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Press ESC to see High Score");
}

void setupScreenRes(const int w, const int h)
{
	xres = w;
	yres = h;
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;
	setupScreenRes(xres, yres);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask |
						KeyPressMask |
						KeyReleaseMask |
						ButtonPressMask |
						ButtonReleaseMask |
						PointerMotionMask |
						StructureNotifyMask |
						SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,	vi->depth,
					InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	setTitle();
}

void reshapeWindow(int width, int height)
{
	//window has been resized.
	setupScreenRes(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, xres, 0, yres, -1, 1);
	setTitle();
}

void initOpengl(void)
{
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
	heistImage = ppm6GetImage("./images/heist.ppm");
	//
	//create opengl texture elements
	glGenTextures(1, &heistTexture);
	glBindTexture(GL_TEXTURE_2D, heistTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             heistImage->width, heistImage->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, heistImage->data);
}

void checkResize(XEvent *e)
{
	//The ConfigureNotify is sent by the server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != xres || xce.height != yres) {
		//Window size did change.
		reshapeWindow(xce.width, xce.height);
	}
}

void initPlayer(void)
{
	//spawns player in an initial position
	player.status = 1;
	player.delay = .15;
	player.pos[0][0] = 2;
	player.pos[0][1] = 2;
	player.direction = DIRECTION_RIGHT;
	//snake.timer = glfwGetTime() + 0.5;
}

void initTreasure(void)
{
	treasureGeneration();
}

void init(void)
{
	boardDim = gridDim * 10;
	//
	initPlayer();
	initTreasure();
	//
	//initialize buttons...
	nbuttons=0;
	//size and position
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 320;
	button[nbuttons].r.right =
	   button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top =
	   button[nbuttons].r.bot + button[nbuttons].r.height;
	button[nbuttons].r.centerx =
	   (button[nbuttons].r.left + button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery =
	   (button[nbuttons].r.bot + button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Reset");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.4f;
	button[nbuttons].color[1] = 0.4f;
	button[nbuttons].color[2] = 0.7f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 160;
	button[nbuttons].r.right =
	   button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
	   button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
	   button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
	   button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Give Up");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.3f;
	button[nbuttons].color[1] = 0.3f;
	button[nbuttons].color[2] = 0.6f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 160;
	button[nbuttons].r.right =
	   button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
	   button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
	   button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
	   button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Play Again");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.3f;
	button[nbuttons].color[1] = 0.3f;
	button[nbuttons].color[2] = 0.6f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 20;
	button[nbuttons].r.bot = 160;
	button[nbuttons].r.right =
	   button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
	   button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
	   button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
	   button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "End Game");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.3f;
	button[nbuttons].color[1] = 0.3f;
	button[nbuttons].color[2] = 0.6f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x00ffffff;
	nbuttons++;
	
	
}

void resetGame(void)
{
	initPlayer();
	initTreasure();
	gameover  = 0;
	score = 0;
	winner    = 0;
}

void checkKeys(XEvent *e)
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
	if (shift){}

	switch(key) {
		case XK_r:
			resetGame();
			break;
		//~ case XK_equal:
			//~ g.snake.delay *= 0.9;
			//~ if (g.snake.delay < 0.001)
				//~ g.snake.delay = 0.001;
			//~ break;
		//~ case XK_minus:
			//~ g.snake.delay *= (1.0 / 0.9);
			//~ break;
		case XK_Left:
			movement(1);
			x=1;
			movementWall(x);
			break;
		case XK_Right:
			movement(3);
			x=3;
			movementWall(x);
			break;
		case XK_Up:
			movement(2);
			x=2;
			movementWall(x);
			
			break;
		case XK_Down:
			movement(0);
			x=0;
			movementWall(x);
			break;
		case XK_Escape:
			level = 2;
		case XK_space:
			start = 1;
	}
}

void checkMouse(XEvent *e)
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
			if (rbutton){}
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
		button[i].over=0;
		if (x >= button[i].r.left &&
			x <= button[i].r.right &&
			y >= button[i].r.bot &&
			y <= button[i].r.top) {
			button[i].over=1;
			if (button[i].over) {
				if (lbutton) {
					switch(i) {
						case 0:
							resetGame();
							break;
						case 1:
							level=2;
							break;
					}
				}
			}
		}
	}
	return;
}

/*void getGridCenter(const int i, const int j, int cent[2])
{
	//This function can be optimized, and made more generic.
	int b2 = boardDim/2;
	int screenCenter[2] = {xres/2, yres/2};
	int s0 = screenCenter[0];
	int s1 = screenCenter[1];
	int bq;
	//quad upper-left corner
	int quad[2];
	//bq is the width of one grid section
	bq = (boardDim / gridDim);
	//-------------------------------------
	//because y dimension is bottom-to-top in OpenGL.
	int i1 = gridDim - i - 1;
	quad[0] = s0-b2;
	quad[1] = s1-b2;
	cent[0] = quad[0] + bq/2;
	cent[1] = quad[1] + bq/2;
	cent[0] += (bq * j);
	cent[1] += (bq * i1);
}*/

/*void physics(void)
{
	//
	//
	//
	clock_physics();
	//
	//
	//Is it time to move the player?
	//move the player segments...
	int headpos[2];
	//save the head position.
	headpos[0] = player.pos[0][0];
	headpos[1] = player.pos[0][1];
	//player.direction:
	//0=down
	//1=left
	//2=up
	//3=right
	// switch(player.direction) {
		// case DIRECTION_DOWN:  player.pos[0][1] += 1; break;
		// case DIRECTION_LEFT:  player.pos[0][0] -= 1; break;
		// case DIRECTION_UP:    player.pos[0][1] -= 1; break;
		// case DIRECTION_RIGHT: player.pos[0][0] += 1; break;
	// }

	//
	//did the player get the treasure
	if (headpos[0] == treasure.pos[0] && headpos[1] == treasure.pos[1]) {
		//new position for treasure...
		int collision=0;
		int ntries=0;
		while(1) {
			treasure.pos[0] = rand() % gridDim;
			treasure.pos[1] = rand() % gridDim;
			collision=0;
			createSound();
			if (treasure.pos[0] == player.pos[0][0] &&
					treasure.pos[1] == player.pos[0][1]) {
					collision=1;
					cleanupSound();
					break;
				}
			if (!collision) break;
			if (++ntries > 1000000) break;
		}
		Log("new treasure: %i %i\n",treasure.pos[0],treasure.pos[1]);
		return;
	}
}*/

void render(void)
{
	int i,j;
	Rect r;

	//--------------------------------------------------------
	//This code is repeated several times in this program, so
	//it can be made more generic and cleaner with some work.
	int b2 = boardDim/2;
	int s0 = xres>>1;
	int s1 = yres>>1;
	//center of a grid
	int cent[2];
	//bq is the width of one grid section
	//--------------------------------------------------------
	//start the opengl stuff
	//set the viewing area on screen
	glViewport(0, 0, xres, yres);
	//clear color buffer
	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//init matrices
	glMatrixMode (GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//this sets to 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//
	//screen background
	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, heistTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	//
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
	//draw the main game board in middle of screen
	glColor3f(0.6f, 0.5f, 0.2f);
	glBegin(GL_QUADS);
		glVertex2i(s0-b2, s1-b2);
		glVertex2i(s0-b2, s1+b2);
		glVertex2i(s0+b2, s1+b2);
		glVertex2i(s0+b2, s1-b2);
	glEnd();
	//
	//grid lines...
	int x0 = s0-b2;
	int x1 = s0+b2;
	int y0 = s1-b2;
	int y1 = s1+b2;
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_LINES);
	for (i=1; i<gridDim; i++) {
		y0 += 10;
		glVertex2i(x0,y0);
		glVertex2i(x1,y0);
	}
	x0 = s0-b2;
	y0 = s1-b2;
	y1 = s1+b2;
	for (j=1; j<gridDim; j++) {
		x0 += 10;
		glVertex2i(x0,y0);
		glVertex2i(x0,y1);
	}
	glEnd();
	//
	//
	clock_animation();
	#define COLORFUL_SNAKE
	//
	//draw snake...
	#ifdef COLORFUL_SNAKE
	float c[3]={1.0f,1.0,0.5};
	float rgb[3];
	rgb[0] = -0.9;
	rgb[2] = -0.45;
	glColor3fv(c);
	//
	glBegin(GL_QUADS);
		getGridCenter(player.pos[0][1],player.pos[0][0],cent);
		glVertex2i(cent[0]-4, cent[1]-3);
		glVertex2i(cent[0]-4, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]-3);
		c[0] +=	rgb[0];
		c[2] +=	rgb[2];
		glColor3fv(c);
	glEnd();
	#else //COLORFUL_SNAKE
	glColor3f(0.1f, 0.8f, 0.1f);
	glBegin(GL_QUADS);
	for (i=0; i<player.length; i++) {
		getGridCenter(player.pos[i][1],player.pos[i][0],cent);
		glVertex2i(cent[0]-4, cent[1]-3);
		glVertex2i(cent[0]-4, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]-3);
		glColor3f(0.0f, 0.6f, 0.0f);
	}
	glEnd();
	#endif //COLORFUL_SNAKE
	//
	//
	//draw treasure...
	for (int i = 0; i < MAX_TREASURE; i++) {
		getGridCenter(treasure[i].pos[1],treasure[i].pos[0],cent);
		glColor3f(0.1, 0.1f, 0.0f);
		glBegin(GL_QUADS);
		glVertex2i(cent[0]-4, cent[1]-3);
		glVertex2i(cent[0]-4, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]-3);
		glEnd();
	}
	//
	//
	r.left   = xres/2;
	r.bot    = yres-100;
	r.center = 1;
	ggprint16(&r, 16, 0x00ffffff, "Heist Game");
	
	// draw wall
	for(int i=4; i<26; i++) {
	getGridCenter(5, i, cent);
	glColor3f(0.1, 0.1f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2i(cent[0]-5, cent[1]-4);
	glVertex2i(cent[0]-5, cent[1]+3);
	glVertex2i(cent[0]+4, cent[1]+3);
	glVertex2i(cent[0]+4, cent[1]-4);
	glEnd();
	//
	//
	r.left   = xres/2;
	r.bot    = yres-100;
	r.center = 1;
	ggprint16(&r, 16, 0x00ffffff, "Heist Game");
	}
	
	for(int i=4; i<=26; i++) {
        getGridCenter(9, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }

        for(int i=0; i<=26; i++) {
        getGridCenter(15, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }
        
        for(int i=0; i<=26; i++) {
        getGridCenter(20, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }
        
        for(int i=0; i<=38; i++) {
        getGridCenter(25, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }

        for(int i=3; i<=29; i++) {
        getGridCenter(27, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }

        for(int i=2; i<=39; i++) {
        getGridCenter(31, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }

        for(int i=7; i<=35; i++) {
        getGridCenter(36, i, cent);
        glColor3f(0.1, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-5, cent[1]-4);
        glVertex2i(cent[0]-5, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]+3);
        glVertex2i(cent[0]+4, cent[1]-4);
        glEnd();
        //
        //
        r.left   = xres/2;
        r.bot    = yres-100;
        r.center = 1;
        ggprint16(&r, 16, 0x00ffffff, "Heist Game");
        }
}
