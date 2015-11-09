#include"kevinB.h"
//#include"lianneL.h"
#include"main.h"
#include"log.h"
#include"sergioA.h"
#include"cstdlib"
#include<iostream>
#include"lianneL.h"

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3
bool myWall = false;
bool again = true;
int x;
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
    initWall();
        //
        //
        //Is it time to move the player?
        //move the player segments...
        int headpos[2];
        //save the head position.
        headpos[0] = player.pos[0][0];
        headpos[1] = player.pos[0][1];

        // save
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
		if(again == true) {
	treasure.pos[0] = 6;
	treasure.pos[1] = 5;
	again = false;
		}
                return;
        }
}

void initWall(void)
{
        int loc[50];
        for(int i=4; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 5;
	}
	//treasure.pos[0] = 4;
	//treasure.pos[1] = 5;
	for(int i=4; i<25; i+=2) {
                        while (treasure.pos[0] == wall.here[i] &&
                                        treasure.pos[1] == wall.here[i+1]) {
			//	physics();
cout << "here" << endl;
                        treasure.pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure.pos[1] = rand() % gridDim;
			}
	}		
        for(int i=4; i<=25; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
		//	myWall = false;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
					myWall = true;
				//	if(myWall == true)
				//	player.pos[0][1] = -1;
				//myWall = false;
				movementWall(x);	
                                                break;
                                        }
                                        if (!collision) { 
					    myWall = true;
					    break;
					}
                                        if (++ntries > 1000000){ 
					    myWall = true;
					break;
			}
		//			myWall = false;
                        }
		//	myWall = false;
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl; 
	       //break;	
		//player.pos[0][1] -= -1;
		//checkWall();
        //      return;
/*
                        if (player.pos[0][0] < 0 ||
                        player.pos[0][0] > gridDim-1 ||
                        player.pos[0][1] < 0 ||
                        player.pos[0][1] > gridDim-1)
                        {
                                return 0;
                        }

                        else
                        {
                                return 1;
                        }
              */  }
        }

        for(int i=5; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=5; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 5;
        }

        for(int i=5; i<=26; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) break;
                                        if (++ntries > 1000000) break;
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=4; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }

        for(int i=4; i<=25; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) break;
                                        if (++ntries > 1000000) break;
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=5; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=5; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }

        for(int i=5; i<=26; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) break;
                                        if (++ntries > 1000000) break;
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl;  
        
	//        return;
                }
        }


        for(int i=0; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 15;
        }

        for(int i=0; i<=25; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) break;
                                        if (++ntries > 1000000) break;
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=0; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 15;
        }

        for(int i=0; i<=26; i+=2) {
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) break;
                                        if (++ntries > 1000000) break;
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                cout << "wall hit KB" << endl;  
        //      return;
                }
        }
	
}

void movementWall(int n)
{
	if(n == 0){
	//    	if(myWall == false) {
		player.direction = DIRECTION_DOWN;
		player.pos[0][1] += 1;
	//	}
		if(myWall == true){
		    cout << "here" << endl;
		player.pos[0][1] -= 2;
			myWall = false;
	//		return;
		//	myWall = false;
		}
		x=0;
		//if(initWall() == 0)
		//cout << "(" << player.pos[0][0] << "," <<
		// player.pos[0][1] << ")" << endl;
	} else if (n == 1) {
		player.direction = DIRECTION_LEFT;
		player.pos[0][0] -= 1;
		if(myWall == true){
			player.pos[0][0] += 2;
			myWall = false;
		}
		x=1;
	//	cout << "(" << player.pos[0][0] << "," <<
	//	player.pos[0][1] << ")" << endl;
	} else if (n == 2) {
		player.direction = DIRECTION_UP;
		player.pos[0][1] -= 1;
		if(myWall == true){
			player.pos[0][1] += 2;
			myWall = false;
		}
		x=2;
	//	cout << "(" << player.pos[0][0] << "," <<
	//	player.pos[0][1] << ")" << endl;
	} else {
		player.direction = DIRECTION_RIGHT;
		player.pos[0][0] += 1;
		if(myWall == true){ // if(checkCollision() == 0) {
			player.pos[0][0] -= 2;
			myWall = false;
		}
		x=3;
	//	cout << "(" << player.pos[0][0] << "," <<
	//	player.pos[0][1] << ")" << endl;
	}
	
	//return;
}

//Checks to see if the player will collide with a boundary if moved in
//the direction the player asks for. Currently only checks against
//game grid boundaries. 
//
//
//bool checkWall()
//{
    //if(a == 0) return 1;
	//if (player.pos[0][0] < 0 ||
	//	player.pos[0][0] > gridDim-1 ||
	//	player.pos[0][1] < 0 ||
	//	player.pos[0][1] > gridDim-1) {
  //  	if(myWall==false)
//	    return 1;
//	else return 0;
	//} else {
	//	return 1;
	//}
//}
