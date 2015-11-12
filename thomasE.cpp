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

void highScore(int score, int highScores[])
{ 
	unsigned int cref = 0x00ffffff; //white
	
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, yres5);
	glVertex2i(xres5, yres5);
	glVertex2i(xres5, 0);
	glEnd();

	Rect titleScore;
	titleScore.bot = 500;
	titleScore.left = 135;
	titleScore.center = 150;

	ggprint16(&titleScore, 0, cref, "--HIGH SCORE--");
	
	Rect finalScore;
	finalScore.bot = 400;
	finalScore.left = 135;
	finalScore.center = 150;
	
    stringstream strs;
    strs << score;
    string temp_str = strs.str();
    char* testCheck2 = (char*) temp_str.c_str();

	ggprint12(&finalScore, 0, cref, testCheck2);
	
	
	// < - - - HIGH SCORES
	Rect scoreOne;
	scoreOne.bot = 350;
	scoreOne.left = 135;
	scoreOne.center = 150;
	
	Rect scoreTwo;
	scoreTwo.bot = 325;
	scoreTwo.left = 135;
	scoreTwo.center = 150;
	
	Rect scoreThree;
	scoreThree.bot = 300;
	scoreThree.left = 135;
	scoreThree.center = 150;
	
	Rect scoreFour;
	scoreFour.bot = 275;
	scoreFour.left = 135;
	scoreFour.center = 150;
	
	Rect scoreFive;
	scoreFive.bot = 250;
	scoreFive.left = 135;
	scoreFive.center = 150;
	
	stringstream strs1;
    strs1 << highScores[0];
    string tmp1 = strs1.str();
    char* firstScore = (char*) tmp1.c_str();
    
    stringstream strs2;
    strs2 << highScores[1];
    string tmp2 = strs2.str();
    char* secondScore = (char*) tmp2.c_str();
    
    stringstream strs3;
    strs3 << highScores[2];
    string tmp3 = strs3.str();
    char* thirdScore = (char*) tmp3.c_str();
    
    stringstream strs4;
    strs4 << highScores[3];
    string tmp4 = strs4.str();
    char* fourthScore = (char*) tmp4.c_str();
    
    stringstream strs5;
    strs5 << highScores[4];
    string tmp5 = strs5.str();
    char* fifthScore = (char*) tmp5.c_str();
	
	ggprint12(&scoreOne, 0, cref, firstScore);
	ggprint12(&scoreTwo, 0, cref, secondScore);
	ggprint12(&scoreThree, 0, cref, thirdScore);
	ggprint12(&scoreFour, 0, cref, fourthScore);
	ggprint12(&scoreFive, 0, cref, fifthScore);
	
  
  
  return;
}

void calculateScore(int currentScore, int highScores[])
{
  for (int k = 1; k < 5; k++){ //sort all scores before checking, in case of custom values
    for (int i = 0; i < 4 - k; i++){
      if (highScores[i] > highScores[i +1]){
	  int sort = highScores[i];
	  highScores[i] = highScores[i + 1];
	  highScores[i + 1] = sort;
      }
    }
  }
  
  for (int i = 0; i < 5; i++){ //check if high score was made then sort
    if(currentScore > highScores[i]){
    
    highScores[0] = currentScore;  
      
    for (int k = 1; k < 6; k++){
      for (int i = 0; i < 5 - k; i++){
		if (highScores[i] > highScores[i +1]){
			int sort = highScores[i];
			highScores[i] = highScores[i + 1];
			highScores[i + 1] = sort;
			}
		}
	}
	break;
    }
  }
}

void scoreSheet(int highScores[])
{
	ofstream highscoreLog;
	highscoreLog.open ("highscores.txt");

	for (int i = 0; i < 5; i++){
		highscoreLog << highScores[i] << endl;
	}

	highscoreLog.close();  
	return;
}

void readFile(int highScores[])
{
	
	//--------- Take the value from the txt file and read it
	//string scoreNum[5];
	//int tmp = 0;
	//string line;
	
	ifstream highscoreLog;
	highscoreLog.open("highscore.txt");
	for(int i = 0; i < 6; i++){
		highscoreLog >> highScores[i];
	}
	highscoreLog.close();
	
	/*LOOK UP THE FIN FUNCTION INSTEAD, YOU ARE PULLING INTS FROM THE FILE
	istringstream scoreOne(scoreNum[0]);
    scoreOne >> highScores[0];
    
    istringstream scoreTwo(scoreNum[1]);
    scoreTwo >> highScores[1];
    
    istringstream scoreThree(scoreNum[2]);
	scoreThree >> highScores[2];
    
    stringstream scoreFour(scoreNum[3]);
	scoreFour >> highScores[3];
    
    stringstream scoreFive(scoreNum[4]);
    scoreFive >> highScores[4];*/
	
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
	if (shift){}

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


