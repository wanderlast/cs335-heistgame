//lianneL.cpp
//author: Lianne Louie
//CS335 game file

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "lianneL.h"

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3

using namespace std;

void movement(int n)
{
	if(n == 0){
		player.direction = DIRECTION_DOWN;
		player.pos[0][1] += 1;
		if(!checkCollision()){
			player.pos[0][1] -= 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		 player.pos[0][1] << ")" << endl;
	} else if (n == 1) {
		player.direction = DIRECTION_LEFT;
		player.pos[0][0] -= 1;
		if(!checkCollision()){
			player.pos[0][0] += 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
	} else if (n == 2) {
		player.direction = DIRECTION_UP;
		player.pos[0][1] -= 1;
		if(!checkCollision()){
			player.pos[0][1] += 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
	} else {
		player.direction = DIRECTION_RIGHT;
		player.pos[0][0] += 1;
		if(!checkCollision()){
			player.pos[0][0] -= 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
	}
	
	return;
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
