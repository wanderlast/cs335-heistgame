#include"kevinB.h"
#include"main.h"
#include"log.h"
#include"sergioA.h"
#include"cstdlib"
#include<iostream>
#include"lianneL.h"
using namespace std;

void getGridCenter(const int i, const int j, int cent[2])
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
	
	//map();
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
}




void physics(void)
{
	//
	//
	//Is it time to move the player?
	//move the player segments...
	int headpos[2];
	//save the head position.
	headpos[0] = player.pos[0][0];
	headpos[1] = player.pos[0][1];

	int loc[50];
	// save
	loc[0] = player.pos[0][0];
	loc[1] = player.pos[0][1];
	loc[2] = player.pos[0][0];
	loc[3] = player.pos[0][1];
	for(int i=4; i<=40; i++) {
	    loc[i] = player.pos[0][0];
		loc[i+1] = player.pos[0][1];
	}
	cout << "kb note: " << loc[5] << endl;
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
			//cout << treasure.pos[0] << endl;
			treasure.pos[1] = rand() % gridDim;
			//cout << treasure.pos[0] << endl;
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
		cout << "treasure collected KB" << endl;
		return;
	}

	if (loc[0] == wall.here[0] && loc[1] == wall.here[1]) {
		//new position for treasure...
		int collision=0;
		int ntries=0;
		while(1) {
			//wall.here[0] = 30;
			//wall.here[1] = 20;

			//wall.here[2] = 30;
			//wall.here[3] = 20;

			wall.here[0] = 9;
			wall.here[1] = 10;
			//wall.here[0] = 11;
			//wall.here[1] = 12;
			//wall.here[2] = 11;
		//wall.here[3] = 12;

			collision=0;
			//collision=0;
			//collision=0;
			//createSound();
			if (wall.here[0] == player.pos[0][0] &&
					wall.here[1] == player.pos[0][1]) {
					collision=1;
			//		cleanupSound();
					break;
				}
			if (!collision) break;
			if (++ntries > 1000000) break;
		}
		Log("new wall: %i %i\n",wall.here[0],wall.here[1]);
		cout << "wall hit KB" << endl;
		return;
	}

	if (loc[2] == wall.here[2] && loc[3] == wall.here[3]) {
		//new position for treasure...
		int collision=0;
		int ntries=0;
		while(1) {
			//wall.here[0] = 30;
			//wall.here[1] = 20;

			//wall.here[2] = 30;
			//wall.here[3] = 20;

			wall.here[2] = 11;
			wall.here[3] = 12;
			//wall.here[2] = 11;
		//wall.here[3] = 12;
			
			collision=0;
			//collision=0;
			//collision=0;
			//createSound();
			if (wall.here[2] == player.pos[0][0] &&
					wall.here[3] == player.pos[0][1]) {
					collision=1;
			//		cleanupSound();
					break;
				}
			if (!collision) break;
			if (++ntries > 1000000) break;
		}
		Log("new wall: %i %i\n",wall.here[2],wall.here[3]);
		cout << "wall hit KB" << endl;  
		return;
	}
for(int i=4; i<=40; i++) {
	if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
		//new position for treasure...
		int collision=0;
		int ntries=0;
		while(1) {
			//wall.here[0] = 30;
			//wall.here[1] = 20;

			//wall.here[2] = 30;
			//wall.here[3] = 20;

			wall.here[i] = 11+i;
			wall.here[i+1] = 12+i;
			//wall.here[2] = 11;
		//wall.here[3] = 12;
			
			collision=0;
			//collision=0;
			//collision=0;
			//createSound();
			if (wall.here[i] == player.pos[0][0] &&
					wall.here[i+1] == player.pos[0][1]) {
					collision=1;
			//		cleanupSound();
					break;
				}
			if (!collision) break;
			if (++ntries > 1000000) break;
		}
		Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
		cout << "wall hit KB" << endl;  
		return;
	}
	cout << "crash: " << i  << endl;
}}
