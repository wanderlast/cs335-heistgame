//lianneL.cpp
//author: Lianne Louie
//CS335 game file

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "lianneL.h"
#include "log.h"
#include "sergioA.h"

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3

#define MAX_TREASURE 15

using namespace std;

//controls user movement, checking for collision with boundaries
void movement(int n)
{
	if(n == 0){
		player.direction = DIRECTION_DOWN;
		player.pos[0][1] += 1;
		if(!checkBorderCollision()){
			player.pos[0][1] -= 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		 player.pos[0][1] << ")" << endl;
		treasureCollision();
	} else if (n == 1) {
		player.direction = DIRECTION_LEFT;
		player.pos[0][0] -= 1;
		if(!checkBorderCollision()){
			player.pos[0][0] += 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
		treasureCollision();
	} else if (n == 2) {
		player.direction = DIRECTION_UP;
		player.pos[0][1] -= 1;
		if(!checkBorderCollision()){
			player.pos[0][1] += 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
		treasureCollision();
	} else {
		player.direction = DIRECTION_RIGHT;
		player.pos[0][0] += 1;
		if(!checkBorderCollision()){
			player.pos[0][0] -= 1;
		}
		cout << "(" << player.pos[0][0] << "," <<
		player.pos[0][1] << ")" << endl;
		treasureCollision();
	}
	
	return;
}

//Checks to see if the player will collide with a boundary if moved in
//the direction the player asks for. Currently only checks against
//game grid boundaries. 
int checkBorderCollision()
{
	if (player.pos[0][0] < 0 ||
		player.pos[0][0] > gridDim-1 ||
		player.pos[0][1] < 0 ||
		player.pos[0][1] > gridDim-1) {
			//collision with window boundaries occurred
			return 0;
	} else {
		return 1; //collision did not occur
	}
}

//generates treasure at the start of the game
void initTreasure(void)
{
	//re-roll RNG
	srand(time(NULL));

	//generate treasure
	for ( int i = 0; i < MAX_TREASURE; i++){ 
		treasureGeneration(i);
	}
}

//generates a single treasure, checking for collision
void treasureGeneration(int i)
{
	int test = 0;
	//while the treasure hasn't been "generated"
	while(treasure[i].status == 0){
		//generate a random position
		treasure[i].pos[0] = rand() % gridDim;
		treasure[i].pos[1] = rand() % gridDim;
		cout << i << ": (" << treasure[i].pos[0] << ", " <<
			treasure[i].pos[1] << ")";
			
		//check to see if it's overlapping with the player
		if (treasure[i].pos[0] == player.pos[0][0] &&
				treasure[i].pos[1] == player.pos[0][1]) {
			treasure[i].status = 0;
			test = 1;
		}
		
		if (test == 1) {
			//check to see if it's overlapping with other treasure
			for (int j = 0; j < i; j++){
			  
			}
			treasure[i].status = 0;
			test = 1;
		}
		
		if (test == 2) {
			//check for overlap with walls
		} 
		
		//this is i only if it passed all of the other tests
		if ( test == 0 )
		{
			treasure[i].status = 1;
		}	
	}
	treasure[i].type = rand()%3 + 1; //assigns it a type from 1-3
}

void treasureCollision()
{
	//did the player get the treasure
	for (int i = 0; i < MAX_TREASURE; i++){
		if (player.pos[0][0] == treasure[i].pos[0] &&
		  player.pos[0][1] == treasure[i].pos[1]) {
			//new position for treasure...
			int collision=0;
			int ntries=0;
			while(1) {
				treasure[i].pos[0] = rand() % gridDim;
				//cout << treasure.pos[0] << endl;
				treasure[i].pos[1] = rand() % gridDim;
				//cout << treasure.pos[0] << endl;
				collision=0;
				createSound();
				if (treasure[i].pos[0] == player.pos[0][0] &&
						treasure[i].pos[1] == player.pos[0][1]) {
						collision=1;
						cleanupSound();
						break;
					}
				if (!collision) break;
				if (++ntries > 1000000) break;
			}
			Log("new treasure: %i %i\n",treasure[i].pos[0],treasure[i].pos[1]);
			cout << "treasure collected" << endl;
			return;
		}
	}
  
}

//treasure collision and points
int findTreasureValue(Treasure* t)
{	
	int value = t-> type;
	
	switch (value) {
	  case 1:
	    //coin
	    return 100;
	    break;
	  case 2:
	    //jewel
	    return 500;
	    break;
	  default:
	    //chest
	    return 1000;
	    break;
	}
}

//spritework here