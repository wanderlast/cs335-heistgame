//cs335 Fall 2015 Project Component
//author: Thomas Espinoza
//
//This is a bootstrap code file to begin working off of.
//Please remove any includes or files that are unnecessary
//for what you are working on.
//
using namespace std;
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
#include "log.h"
#include "main.h"
extern "C" {
#include "fonts.h"
}
//#define WINDOW_WIDTH  1300
//#define WINDOW_HEIGHT 800

//X Windows variables
GLXContext glc;

int xres5=1300, yres5=800;

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

Button button2[4];

void scoreSheet(int highScores[]);

void highScore(int score, int isnewHigh, int highScores[], int newScores[])
{
    unsigned int cref = 0x00ffffff; //white

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, yres5);
    glVertex2i(xres5, yres5);
    glVertex2i(xres5, 0);
    glEnd();




    //===================

    Ppmimage *startImage;
    startImage=NULL;
    GLuint startTexture;

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

    //=========
    //INITIALIZE BUTTONS
    int i;
    Rect r;
    int nbuttons=0;
    button2[nbuttons].r.width = 140;
    button2[nbuttons].r.height = 60;
    button2[nbuttons].r.left = 550;
    button2[nbuttons].r.bot = 460;
    button2[nbuttons].r.right =
        button2[nbuttons].r.left + button2[nbuttons].r.width;
    button2[nbuttons].r.top = button2[nbuttons].r.bot +
                              button2[nbuttons].r.height;
    button2[nbuttons].r.centerx = (button2[nbuttons].r.left +
                                   button2[nbuttons].r.right) / 2;
    button2[nbuttons].r.centery = (button2[nbuttons].r.bot +
                                   button2[nbuttons].r.top) / 2;
    strcpy(button2[nbuttons].text, "Play Again");
    button2[nbuttons].down = 0;
    button2[nbuttons].click = 0;
    button2[nbuttons].color[0] = 0.4f;
    button2[nbuttons].color[1] = 0.4f;
    button2[nbuttons].color[2] = 0.4f;
    button2[nbuttons].dcolor[0] = button2[nbuttons].color[0] * 0.5f;
    button2[nbuttons].dcolor[1] = button2[nbuttons].color[1] * 0.5f;
    button2[nbuttons].dcolor[2] = button2[nbuttons].color[2] * 0.5f;
    button2[nbuttons].text_color = 0x00ffffff;
    nbuttons++;
    

    button2[nbuttons].r.width = 140;
    button2[nbuttons].r.height = 60;
    button2[nbuttons].r.left = 550;
    button2[nbuttons].r.bot = 360;
    button2[nbuttons].r.right =
        button2[nbuttons].r.left + button2[nbuttons].r.width;
    button2[nbuttons].r.top = button2[nbuttons].r.bot +
                              button2[nbuttons].r.height;
    button2[nbuttons].r.centerx = (button2[nbuttons].r.left +
                                   button2[nbuttons].r.right) / 2;
    button2[nbuttons].r.centery = (button2[nbuttons].r.bot +
                                   button2[nbuttons].r.top) / 2;
    strcpy(button2[nbuttons].text, "End Game");
    button2[nbuttons].down = 0;
    button2[nbuttons].click = 0;
    button2[nbuttons].color[0] = 0.4f;
    button2[nbuttons].color[1] = 0.4f;
    button2[nbuttons].color[2] = 0.4f;
    button2[nbuttons].dcolor[0] = button2[nbuttons].color[0] * 0.5f;
    button2[nbuttons].dcolor[1] = button2[nbuttons].color[1] * 0.5f;
    button2[nbuttons].dcolor[2] = button2[nbuttons].color[2] * 0.5f;
    button2[nbuttons].text_color = 0x00ffffff;
    nbuttons++;
    
    

    //=============== END OF BUTTONS
    //draw all buttons
    for (i=0; i<3; i++) {
        if (button2[i].over) {
            int w=2;
            glColor3f(1.0f, 1.0f, 0.0f);
            //draw a highlight around button
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            glVertex2i(button2[i].r.left-w,  button2[i].r.bot-w);
            glVertex2i(button2[i].r.left-w,  button2[i].r.top+w);
            glVertex2i(button2[i].r.right+w, button2[i].r.top+w);
            glVertex2i(button2[i].r.right+w, button2[i].r.bot-w);
            glVertex2i(button2[i].r.left-w,  button2[i].r.bot-w);
            glEnd();
            glLineWidth(1);
        }
        if (button2[i].down) {
            glColor3fv(button2[i].dcolor);
        } else {
            glColor3fv(button2[i].color);
        }
        glBegin(GL_QUADS);
        glVertex2i(button2[i].r.left,  button2[i].r.bot);
        glVertex2i(button2[i].r.left,  button2[i].r.top);
        glVertex2i(button2[i].r.right, button2[i].r.top);
        glVertex2i(button2[i].r.right, button2[i].r.bot);
        glEnd();
        r.left = button2[i].r.centerx;
        r.bot  = button2[i].r.centery-8;
        r.center = 1;
        if (button2[i].down) {
            ggprint16(&r, 0, button2[i].text_color, "Pressed!");
        } else {
            ggprint16(&r, 0, button2[i].text_color, button2[i].text);
        }
    }
    //========================
    
    if(isnewHigh == 0){
		Rect yourScore;
		yourScore.bot = 500;
		yourScore.left = 175;
		yourScore.center = 150;
		ggprint16(&yourScore, 0, cref, "--YOUR SCORE--");


		Rect finalScore;
		finalScore.bot = 450;
		finalScore.left = 175;
		finalScore.center = 150;

		stringstream strs;
		strs << score;
		string temp_str = strs.str();
		char* lastScore = (char*) temp_str.c_str();
		ggprint12(&finalScore, 0, cref, lastScore);
		
		Rect yourScore2;
		yourScore2.bot = 400;
		yourScore2.left = 175;
		yourScore2.center = 150;
		ggprint16(&yourScore2, 0, cref, "No New High Score");
		
		Rect yourScore3;
		yourScore3.bot = 375;
		yourScore3.left = 175;
		yourScore3.center = 150;
		ggprint16(&yourScore3, 0, cref, "Better Luck Next Time!");

		// < - - - HIGH SCORES
		Rect noHightitleScore;
		noHightitleScore.bot = 500;
		noHightitleScore.left = 435;
		noHightitleScore.center = 150;
		ggprint16(&noHightitleScore, 0, cref, "--HIGH SCORES--");
		
		Rect noHighscoreOne;
		noHighscoreOne.bot = 450;
		noHighscoreOne.left = 435;
		noHighscoreOne.center = 150;

		Rect noHighscoreTwo;
		noHighscoreTwo.bot = 425;
		noHighscoreTwo.left = 435;
		noHighscoreTwo.center = 150;

		Rect noHighscoreThree;
		noHighscoreThree.bot = 400;
		noHighscoreThree.left = 435;
		noHighscoreThree.center = 150;

		Rect noHighscoreFour;
		noHighscoreFour.bot = 375;
		noHighscoreFour.left = 435;
		noHighscoreFour.center = 450;

		Rect noHighscoreFive;
		noHighscoreFive.bot = 350;
		noHighscoreFive.left = 435;
		noHighscoreFive.center = 150;

		stringstream noHighstrs1;
		noHighstrs1 << highScores[0];
		string tmp1 = noHighstrs1.str();
		char* noHighfirstScore = (char*) tmp1.c_str();

		stringstream noHighstrs2;
		noHighstrs2 << highScores[1];
		string tmp2 = noHighstrs2.str();
		char* noHighsecondScore = (char*) tmp2.c_str();

		stringstream noHighstrs3;
		noHighstrs3 << highScores[2];
		string tmp3 = noHighstrs3.str();
		char* noHighthirdScore = (char*) tmp3.c_str();

		stringstream noHighstrs4;
		noHighstrs4 << highScores[3];
		string tmp4 = noHighstrs4.str();
		char* noHighfourthScore = (char*) tmp4.c_str();

		stringstream noHighstrs5;
		noHighstrs5 << highScores[4];
		string tmp5 = noHighstrs5.str();
		char* noHighfifthScore = (char*) tmp5.c_str();

		ggprint12(&noHighscoreOne, 0, cref, noHighfirstScore);
		ggprint12(&noHighscoreTwo, 0, cref, noHighsecondScore);
		ggprint12(&noHighscoreThree, 0, cref, noHighthirdScore);
		ggprint12(&noHighscoreFour, 0, cref, noHighfourthScore);
		ggprint12(&noHighscoreFive, 0, cref, noHighfifthScore);
	}


	if(isnewHigh == 1){
		Rect yourScore;
		yourScore.bot = 500;
		yourScore.left = 100;
		yourScore.center = 150;
		ggprint16(&yourScore, 0, cref, "--YOUR SCORE--");


		Rect finalScore;
		finalScore.bot = 450;
		finalScore.left = 100;
		finalScore.center = 150;

		stringstream strs;
		strs << score;
		string temp_str = strs.str();
		char* lastScore = (char*) temp_str.c_str();
		ggprint12(&finalScore, 0, cref, lastScore);
		
		Rect oldyourScore2;
		oldyourScore2.bot = 400;
		oldyourScore2.left = 100;
		oldyourScore2.center = 150;
		ggprint16(&oldyourScore2, 0, cref, "New High Score!");

		// < - - - OLD SCORES
		Rect oldtitleScore;
		oldtitleScore.bot = 500;
		oldtitleScore.left = 270;
		oldtitleScore.center = 150;
		ggprint16(&oldtitleScore, 0, cref, "--OLD SCORES--");
		
		Rect oldscoreOne;
		oldscoreOne.bot = 450;
		oldscoreOne.left = 270;
		oldscoreOne.center = 150;

		Rect oldscoreTwo;
		oldscoreTwo.bot = 425;
		oldscoreTwo.left = 270;
		oldscoreTwo.center = 150;

		Rect oldscoreThree;
		oldscoreThree.bot = 400;
		oldscoreThree.left = 270;
		oldscoreThree.center = 150;

		Rect oldscoreFour;
		oldscoreFour.bot = 375;
		oldscoreFour.left = 270;
		oldscoreFour.center = 450;

		Rect oldscoreFive;
		oldscoreFive.bot = 350;
		oldscoreFive.left = 270;
		oldscoreFive.center = 150;

		stringstream oldstrs1;
		oldstrs1 << highScores[0];
		string oldtmp1 = oldstrs1.str();
		char* oldfirstScore = (char*) oldtmp1.c_str();

		stringstream oldstrs2;
		oldstrs2 << highScores[1];
		string oldtmp2 = oldstrs2.str();
		char* oldsecondScore = (char*) oldtmp2.c_str();

		stringstream oldstrs3;
		oldstrs3 << highScores[2];
		string oldtmp3 = oldstrs3.str();
		char* oldthirdScore = (char*) oldtmp3.c_str();

		stringstream oldstrs4;
		oldstrs4 << highScores[3];
		string oldtmp4 = oldstrs4.str();
		char* oldfourthScore = (char*) oldtmp4.c_str();

		stringstream oldstrs5;
		oldstrs5 << highScores[4];
		string oldtmp5 = oldstrs5.str();
		char* oldfifthScore = (char*) oldtmp5.c_str();

		ggprint12(&oldscoreOne, 0, cref, oldfirstScore);
		ggprint12(&oldscoreTwo, 0, cref, oldsecondScore);
		ggprint12(&oldscoreThree, 0, cref, oldthirdScore);
		ggprint12(&oldscoreFour, 0, cref, oldfourthScore);
		ggprint12(&oldscoreFive, 0, cref, oldfifthScore);

		// < - - - NEW SCORES
		Rect titleScore;
		titleScore.bot = 500;
		titleScore.left = 435;
		titleScore.center = 150;
		ggprint16(&titleScore, 0, cref, "--NEW SCORES--");
		
		Rect scoreOne;
		scoreOne.bot = 450;
		scoreOne.left = 435;
		scoreOne.center = 150;

		Rect scoreTwo;
		scoreTwo.bot = 425;
		scoreTwo.left = 435;
		scoreTwo.center = 150;

		Rect scoreThree;
		scoreThree.bot = 400;
		scoreThree.left = 435;
		scoreThree.center = 150;

		Rect scoreFour;
		scoreFour.bot = 375;
		scoreFour.left = 435;
		scoreFour.center = 450;

		Rect scoreFive;
		scoreFive.bot = 350;
		scoreFive.left = 435;
		scoreFive.center = 150;

		stringstream strs1;
		strs1 << newScores[0];
		string tmp1 = strs1.str();
		char* firstScore = (char*) tmp1.c_str();

		stringstream strs2;
		strs2 << newScores[1];
		string tmp2 = strs2.str();
		char* secondScore = (char*) tmp2.c_str();

		stringstream strs3;
		strs3 << newScores[2];
		string tmp3 = strs3.str();
		char* thirdScore = (char*) tmp3.c_str();

		stringstream strs4;
		strs4 << newScores[3];
		string tmp4 = strs4.str();
		char* fourthScore = (char*) tmp4.c_str();

		stringstream strs5;
		strs5 << newScores[4];
		string tmp5 = strs5.str();
		char* fifthScore = (char*) tmp5.c_str();

		ggprint12(&scoreOne, 0, cref, firstScore);
		ggprint12(&scoreTwo, 0, cref, secondScore);
		ggprint12(&scoreThree, 0, cref, thirdScore);
		ggprint12(&scoreFour, 0, cref, fourthScore);
		ggprint12(&scoreFive, 0, cref, fifthScore);
		
		scoreSheet(newScores);
	}


    return;
}

int calculateScore(int currentScore, int highScores[], int newScores[])
{
    for (int k = 1; k < 5; k++) { //sort all scores before checking, in case of custom values
        for (int i = 0; i < 4 - k; i++) {
            if (highScores[i] > highScores[i +1]) {
                int sort = highScores[i];
                highScores[i] = highScores[i + 1];
                highScores[i + 1] = sort;
            }
        }
    }
    
    for (int k = 1; k < 5; k++) { //sort all scores before checking, in case of custom values
        for (int i = 0; i < 4 - k; i++) {
            if (newScores[i] > newScores[i +1]) {
                int sort = newScores[i];
                newScores[i] = newScores[i + 1];
                newScores[i + 1] = sort;
            }
        }
    }

    for (int i = 0; i < 5; i++) { //check if high score was made then sort
        if(currentScore > newScores[i]) {

            newScores[0] = currentScore;

            for (int k = 1; k < 6; k++) {
                for (int i = 0; i < 5 - k; i++) {
                    if (newScores[i] > newScores[i +1]) {
                        int sort = newScores[i];
                        newScores[i] = newScores[i + 1];
                        newScores[i + 1] = sort;
                    }
                }
            }
            return 1;
        }
    }
    
    return 0;
}

void scoreSheet(int highScores[])
{
    ofstream highscoreLog;
    highscoreLog.open ("highscores.txt");

    for (int i = 0; i < 5; i++) {
        highscoreLog << highScores[i] << endl;
    }

    highscoreLog.close();
    return;
}

void readFile(int highScores[])
{

    //--------- Take the value from the txt file and read it
    char temp[10];
    char temp2[10];
    char temp3[10];
    char temp4[10];
    char temp5[10];

    stringstream scoreOne;
    stringstream scoreTwo;
    stringstream scoreThree;
    stringstream scoreFour;
    stringstream scoreFive;


    fstream highscoreLog;
    highscoreLog.open("highscores.txt");

    highscoreLog.getline(temp, 10);
    cout << "HIGH TEST" << temp << endl;
    scoreOne << temp;

    highscoreLog.getline(temp2, 10);
    scoreTwo << temp2;

    highscoreLog.getline(temp3, 10);
    scoreThree << temp3;

    highscoreLog.getline(temp4, 10);
    scoreFour << temp4;

    highscoreLog.getline(temp5, 10);
    scoreFive << temp5;

    highscoreLog.close();


    scoreOne >> highScores[0];
    scoreTwo >> highScores[1];
    scoreThree >> highScores[2];
    scoreFour >> highScores[3];
    scoreFive >> highScores[4];

    return;
}

void checkSKeys(XEvent *e)
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

void checkSMouse(XEvent *e)
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
    for (i=0; i<3; i++) {
        button2[i].over=0;
        if (x >= button2[i].r.left &&
                x <= button2[i].r.right &&
                y >= button2[i].r.bot &&
                y <= button2[i].r.top) {
            button2[i].over=1;
            if (button2[i].over) {
                if (lbutton) {
                    switch(i) {
                    case 0:
                        level = 1;
			resetGame();
                        break;
                    case 1:
                        level = 1;
                        done = 1;
                        break;
                    }
                }
            }
        }
    }
    return;
}
