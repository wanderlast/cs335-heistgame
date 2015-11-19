//lianneL.cpp
//author: Lianne Louie
//CS335 game file
//This file deals with initializing player and treasure states, handles the
//movement and collision of players with treasure and boundaries, and generates
//treasure.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "log.h"
#include "sergioA.h"
#include "lianneL.h"
#include "kevinB.h"
#include "ryanS.h"

enum gameModes { scoreAttackEasy, timeAttackEasy, scoreAttack,
                 timeAttack, scoreAttackHard, timeAttackHard
               };

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3

#define MAX_TREASURE 15

using namespace std;

int soundNum;

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

//treasure collision and points
int findTreasureValue(int i)
{
    int value = treasure[i].type;

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

void gameTypeSelector(int select)
{
    //set player, set treasure spawn, set timer
    cout << "the selected game mode is: " << select << endl;
    gameMode = select;
    
    switch(select) {
    
    //75 seconds, spawn in set position
    //treasure spawns all at once and is replenished upon
    //grabbing it
    case scoreAttackEasy:
        initPlayer();
        initTreasure();
        clock_physics(select);
        break;
    
    //player starts in set position, 20 treasure
    //75 seconds
    case timeAttackEasy:
        initPlayer(0);
        initTreasure();
        clock_physics(select);
        break;
    
    //player starts in set position, cont. treasure
    //max 15
    //50 seconds
    case scoreAttack:
        initPlayer();
        initTreasure(12);
        clock_physics(select);
        break;
    
    //player starts in set position, 20 treasure
    //50 seconds
    case timeAttack:
        initPlayer(0);
        initTreasure(12);
        clock_physics(select);
        break;
    
    //player starts in random position, treasure spawns in increasing
    //waves capping at 10 on the map, 30 seconds
    case scoreAttackHard:
        initPlayer(3);
        initTreasure2();
        clock_physics(select);
        break;
    
    //player starts in random position, 20 treasure, 30 seconds
    case timeAttackHard:
        initPlayer(0);
        initTreasure();
        clock_physics(select);
        break;
    
    //default is scoreAttackEasy
    default:
        initPlayer(0);
        initTreasure(1);
        clock_physics(select);
        break;
    }
}

//default initplayer
//spawns the player at (2,2)
//treasure continously respawns
void initPlayer()
{
    //re-roll RNG
    srand(time(NULL));

    //spawns player in an initial position
    player.status = 1;
    player.type = 1;
    player.pos[0][0] = 2;
    player.pos[0][1] = 2;

    //just for fun, spawn them in a random direction
    int dir = rand()%4;
    switch (dir) {
    case 0:
        player.direction = DIRECTION_DOWN;
        break;

    case 1:
        player.direction = DIRECTION_LEFT;
        break;

    case 2:
        player.direction = DIRECTION_UP;
        break;

    case 3:
        player.direction = DIRECTION_RIGHT;
        break;

    default:
        //in the case of an error, just default to right
        player.direction = DIRECTION_RIGHT;
        break;
    }
}


void initPlayer(int type)
{
    //re-roll RNG
    srand(time(NULL));

    //spawns player in an initial position but with a certain game mode
    player.status = 1;
    player.type = type;
    player.pos[0][0] = 2;
    player.pos[0][1] = 2;

    //just for fun, spawn them in a random direction
    int dir = rand()%4;
    switch (dir) {
    case 0:
        player.direction = DIRECTION_DOWN;
        break;

    case 1:
        player.direction = DIRECTION_LEFT;
        break;

    case 2:
        player.direction = DIRECTION_UP;
        break;

    case 3:
        player.direction = DIRECTION_RIGHT;
        break;

    default:
        //in the case of an error, just default to right
        player.direction = DIRECTION_RIGHT;
        break;
    }
}

void initPlayer(int type, int x, int y)
{
    //re-roll RNG
    srand(time(NULL));

    //spawns player in an provided user position
    player.status = 1;
    player.type = type;
    player.pos[0][0] = x;
    player.pos[0][1] = y;

    //just for fun, spawn them in a random direction
    int dir = rand()%4;
    switch (dir) {
    case 0:
        player.direction = DIRECTION_DOWN;
        break;

    case 1:
        player.direction = DIRECTION_LEFT;
        break;

    case 2:
        player.direction = DIRECTION_UP;
        break;

    case 3:
        player.direction = DIRECTION_RIGHT;
        break;

    default:
        //in the case of an error, just default to right
        player.direction = DIRECTION_RIGHT;
        break;
    }
}

//generates treasure at the start of the game
//default version generates 15 random treasures
void initTreasure()
{
    //re-roll RNG
    srand(time(NULL));

    //generate treasure
    for ( int i = 0; i < MAX_TREASURE; i++) {
        if(player.type == 0){
		    treasureGeneration(i, 1);
	    } else {
			treasureGeneration(i);
		}
    }

    treasure[0].count = MAX_TREASURE;
}

//generates n treasures within the game
void initTreasure(int n)
{
    //re-roll RNG
    srand(time(NULL));

    //generate n treasure one at a time
    for ( int i = 0; i < n; i++) {
        if(player.type == 0){
		    treasureGeneration(i, 1);
	    } else {
			treasureGeneration(i);
		}
    }
    treasure[0].count = n;
}

//generates "n" treasure to start
//sends a value to treasure that will cause
//treasure generation to increase more than by 1
void initTreasure(int n, int generate)
{
    //re-roll RNG
    srand(time(NULL));

    //generate n treasure one at a time
    for ( int i = 0; i < n; i++) {
        if(player.type == 0){
		    treasureGeneration(i, 1);
	    } else {
			treasureGeneration(i);
		}
    }

    for (int i = 0; i < n; i++) {
        treasure[i].maxRate = generate;
    }
    treasure[0].count = n;
}

//normal initTreasure spawns all treasure at once
//this will set a max rate and a max # of treasure to spawn
//then as the game plays through, the game will spawn treasure based
//on the rate up until the max count given
void initTreasure2()
{
    //re-roll RNG
    srand(time(NULL));

    for (int i = 0; i < MAX_TREASURE; i++) {
        treasure[i].maxRate = 5;
        treasure[i].maxCount = MAX_TREASURE;
        treasure[i].increase = 2;
    }

    treasureGeneration(0); //spawns the first treasure
    treasure[0].count = 1;
}

//controls user movement, checking for collision with boundaries & treasure
//wall collision is handled within the wall itself?
void movement(int n)
{
    if (n == 0) {

        player.direction = DIRECTION_DOWN;
        player.pos[0][1] += 1;
        if (!checkBorderCollision()) {
            player.pos[0][1] -= 1;
        }
        cout << "(" << player.pos[0][0] << "," <<
             player.pos[0][1] << ")" << endl;
        treasureCollision();

    } else if (n == 1) {

        player.direction = DIRECTION_LEFT;
        player.pos[0][0] -= 1;
        if (!checkBorderCollision()) {
            player.pos[0][0] += 1;
        }
        cout << "(" << player.pos[0][0] << "," <<
             player.pos[0][1] << ")" << endl;
        treasureCollision();

    } else if (n == 2) {

        player.direction = DIRECTION_UP;
        player.pos[0][1] -= 1;
        if (!checkBorderCollision()) {
            player.pos[0][1] += 1;
        }
        cout << "(" << player.pos[0][0] << "," <<
             player.pos[0][1] << ")" << endl;
        treasureCollision();

    } else {

        player.direction = DIRECTION_RIGHT;
        player.pos[0][0] += 1;
        if (!checkBorderCollision()) {
            player.pos[0][0] -= 1;
        }
        cout << "(" << player.pos[0][0] << "," <<
             player.pos[0][1] << ")" << endl;
        treasureCollision();

    }

    return;
}

//checks if player touched the treasure
void treasureCollision()
{
    //did the player get the treasure
    for (int i = 0; i < MAX_TREASURE; i++) {
        if (player.pos[0][0] == treasure[i].pos[0] &&
                player.pos[0][1] == treasure[i].pos[1] &&
                treasure[i].status == 1) {
            //we got treasure!
            cout << player.pos[0][0] << "," << player.pos [0][1];
            cout << endl;
            cout << treasure[i].pos[0] << "," << treasure[i].pos[1];
            cout << endl;
            //add it to our score
            treasureScore += findTreasureValue(i);
            cout << "+" << findTreasureValue(i) << "!" << endl;
            cout << "score is: " << treasureScore << endl;

            //delete the physical presence of the treasure
            treasure[i].status = 0;

            //player type 1 asks for respawning treasure
            if(player.type == 1) {
                //so generate new treasure
                treasureGeneration(i);
                cout << "New position for treasure is : " <<
                     treasure[i].pos[0]	 << ", " << treasure[i].pos[1];
                cout << endl;
            } else if (player.type == 3){
              treasure[0].count++;
              for (int i = 0; i < treasure[0].increase; i++){
                treasureGeneration(i);
                treasure[0].count++;
                if (i == treasure[0].increase - 1 && treasure[0].count < treasure[0].maxCount){
                  if(treasure[0].increase < treasure[0].maxRate){
                    treasure[0].increase += 2;
                  }
                }
              }
            } else {
				treasure[0].count--;
				cout << treasure[0].count << "# left" << endl;
				if(treasure[0].count == 0){
					level = 2;
				}
			}

            if(soundFlag == 1 && level == 1 ) {
				soundNum = 2;
				createSound(soundNum);
			}
            
            //soundNum = 2;
            //createSound(soundNum);
            Log("new treasure: %i %i\n",treasure[i].pos[0],treasure[i].pos[1]);
            cout << "treasure collected" << endl;
        }
    }
    return;

}

//generates a single treasure, checking for collision
void treasureGeneration(int i)
{
    int test = 0;
    //while the treasure hasn't been "generated"
    while (treasure[i].status == 0) {
        //generate a random position
        treasure[i].pos[0] = rand() % gridDim;
        treasure[i].pos[1] = rand() % gridDim;
        cout << "new treasure loc : ";
        cout << treasure[i].pos[0] << "," << treasure[i].pos[1];
        cout << endl;

        //check to see if it's overlapping with the player
        if (treasure[i].pos[0] == player.pos[0][0] &&
                treasure[i].pos[1] == player.pos[0][1]) {
            treasure[i].status = 0;
            cout << "treasure spawned on top of player, rerolling pos";
            cout << endl;
            test = -1;
        } else {
            //not overlapping, check next
            cout << "treasure not on top of player" << endl;
            test = 1;
        }

        //check to see if it's overlapping with other treasure
        if (test == 1) {
            cout << "checking if on top of other treasure"  << endl;
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];
            for (int j = 0; j < MAX_TREASURE; j++) {
                if (i == j) {
                    break;
                }   else if (x == treasure[j].pos[0] &&
                             y == treasure[j].pos[1]) {

                    //collision occurred
                    treasure[i].status = 0;
                    cout << "treasure spawned on another treasure";
                    cout << endl;
                    test = -1; //return to the first test
                    break;
                }
            }
            //so if it passed through all values without changing to -1
            if (test == 1) {
                cout << "treasure not on other treasure" << endl;
                test = 2;
            }
        }

        if (test == 2) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];

            cout << "checking if on a wall" << endl;
            for (int j = 4; j < 26; j+=2) {
                if (x == wall.here[j] && y == wall.here[j+1]) {
                    //collision occurred
                    treasure[i].status = 0;
                    cout << "treasure spawned on wall, rerolling" << endl;
                    test = -1;
                }
            }

            //so if it was never changed, there was no collisions
            if (test == 2) {
                cout << "treasure not on a wall" << endl;
                test = 3;
            }
        }

        //this is i only if it passed all of the other tests
        if (test == 3) {
            cout << "treasure location valid" << endl;
            //generate the treasure, no collisions occurred
            treasure[i].status = 1;
            cout << i << ": (" << treasure[i].pos[0] << ", " <<
                 treasure[i].pos[1] << ")" << endl;

        }
    }

    treasure[i].type = rand()%3 + 1; //assigns it a type from 1-3
    cout << "treasure type is now: " << treasure[i].type << endl;

    if(soundFlag == 1 && level == 1 && test == 3) {
        soundNum = 2;
        createSound(soundNum);
    }
    return;
}

//generates a single treasure, but this time assigns a type as well
void treasureGeneration(int i, int type)
{
    int test = 0;
    //while the treasure hasn't been "generated"
    while (treasure[i].status == 0) {
        //generate a random position
        treasure[i].pos[0] = rand() % gridDim;
        treasure[i].pos[1] = rand() % gridDim;
        cout << "new treasure loc : ";
        cout << treasure[i].pos[0] << "," << treasure[i].pos[1];
        cout << endl;

        //check to see if it's overlapping with the player
        if (treasure[i].pos[0] == player.pos[0][0] &&
                treasure[i].pos[1] == player.pos[0][1]) {
            treasure[i].status = 0;
            cout << "treasure spawned on top of player, rerolling pos";
            cout << endl;
            test = -1;
        } else {
            //not overlapping, check next
            cout << "treasure not on top of player" << endl;
            test = 1;
        }

        //check to see if it's overlapping with other treasure
        if (test == 1) {
            cout << "checking if on top of other treasure"  << endl;
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];
            for (int j = 0; j < MAX_TREASURE; j++) {
                if (i == j) {
                    break;
                }   else if (x == treasure[j].pos[0] &&
                             y == treasure[j].pos[1]) {

                    //collision occurred
                    treasure[i].status = 0;
                    cout << "treasure spawned on another treasure";
                    cout << endl;
                    test = -1; //return to the first test
                    break;
                }
            }
            //so if it passed through all values without changing to -1
            if (test == 1) {
                cout << "treasure not on other treasure" << endl;
                test = 2;
            }
        }

        if (test == 2) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];

            cout << "checking if on a wall" << endl;
            for (int j = 4; j < 26; j+=2) {
                if (x == wall.here[j] && y == wall.here[j+1]) {
                    //collision occurred
                    treasure[i].status = 0;
                    cout << "treasure spawned on wall, rerolling" << endl;
                    test = -1;
                }
            }

            //so if it was never changed, there was no collisions
            if (test == 2) {
                cout << "treasure not on a wall" << endl;
                test = 3;
            }
        }

        //this is i only if it passed all of the other tests
        if (test == 3) {
            cout << "treasure location valid" << endl;
            //generate the treasure, no collisions occurred
            treasure[i].status = 1;
            cout << i << ": (" << treasure[i].pos[0] << ", " <<
                 treasure[i].pos[1] << ")" << endl;
        }
    }

    treasure[i].type = type; //assigns it a specific type
    cout << "treasure type is now: " << treasure[i].type << endl;

    if(soundFlag == 1 && level == 1 && test == 3) {
        soundNum = 2;
        createSound(soundNum);
    }

    return;
}
