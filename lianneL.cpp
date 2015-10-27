//lianneL.cpp
//author: Lianne Louie
//CS335 game file

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "lianneL.h"


using namespace std;

void movement()
{
	
}

//Checks to see if the player will collide with a boundary if moved in
//the direction the player asks for. Currently only checks against
//game grid boundaries. 
int checkCollision()
{
	if (player.pos[0][0] < 0 ||
		player.pos[0][0] > gridDim-1 ||
		player.pos[0][1] < 0 ||
		player.pos[0][1] > gridDim-1) {
			return 0;
	} else {
		return 1;
	}
}
