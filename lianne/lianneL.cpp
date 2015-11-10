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

//default player init
void initPlayer()
{
    //spawns player in an initial position
    player.status = 1;
    player.type = 1;
    player.pos[0][0] = 2;
    player.pos[0][1] = 2;
    player.direction = DIRECTION_RIGHT;
}

void initPlayer(int type)
{
    //spawns player in an initial position but with a certain game mode
    player.status = 1;
    player.type = type;
    player.pos[0][0] = 2;
    player.pos[0][1] = 2;
    player.direction = DIRECTION_RIGHT;
}

void initPlayer(int type, int x, int y)
{

    //spawns player in an provided user position
    player.status = 1;
    player.type = type;
    player.pos[0][0] = x;
    player.pos[0][1] = y;
    player.direction = DIRECTION_RIGHT;
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

//allows variable treasure generation patterns
void gameSelector(int selection)
{

    if(selection < 1 || selection > 3) {
        cout << "game selection error, value of " << selection << endl;
    } else {
        switch(selection) {
        case 1:
            initTreasure();
        case 2:
            initTreasure(25);
        case 3:
            initTreasure(1, 5);
        }
    }
}

//generates treasure at the start of the game
//default version generates 15 random treasures
void initTreasure(void)
{
    //re-roll RNG
    srand(time(NULL));

    //generate treasure
    for ( int i = 0; i < MAX_TREASURE; i++) {
        treasureGeneration(i);
    }
}

//generates n treasures within the game
void initTreasure(int n)
{
    //re-roll RNG
    srand(time(NULL));

    //generate treasure
    for ( int i = 0; i < n; i++) {
        treasureGeneration(i);
    }
}

//generates "start" treasure to start
//up to a max of end treasures at any given time
void initTreasure(int start, int end)
{
    //re-roll RNG
    srand(time(NULL));

    //generate treasure
    for ( int i = 0; i < start; i++) {
        treasureGeneration(i);
    }
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

        //check to see if it's overlapping with the player
        if (treasure[i].pos[0] == player.pos[0][0] &&
                treasure[i].pos[1] == player.pos[0][1]) {
            treasure[i].status = 0;
            cout << "treasure spawned on top of player, rerolling pos";
            test = -1;
        } else {
            //not overlapping, check next
            test = 1;
        }

        //check to see if it's overlapping with other treasure
        if (test == 1) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];
            for (int j = 0; j < MAX_TREASURE; j++) {
                if (x == treasure[j].pos[0] && y == treasure[j].pos[1]) {
                    //collision occurred
                    treasure[i].status = 0;
                    cout << "treasure spawned on another treasure, rerolling";
                    test = -1; //return to the first test
                    break;
                }
            }
            //so if it passed through all values without changing to -1
            if (test == 1) {
                test = 2;
            }
        }

        if (test == 2) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];

            for (int j = 0; j < MAX_TREASURE; j+=2) {
                if (x == wall.here[j] && y == wall.here[j+1]){
                  //collision occurred
                  treasure[i].status = 0;
                  cout << "treasure spawned on wall, rerolling";
                  test = -1;
                }
            }
            
            //so if it was never changed, there was no collisions
            if (test == 2){
              test = 3;
            }
        }

        //this is i only if it passed all of the other tests
        if ( test == 3 ) {
            //generate the treasure, no collisions occurred
            treasure[i].status = 1;
            cout << i << ": (" << treasure[i].pos[0] << ", " <<
				treasure[i].pos[1] << ")";
        }
    }

    treasure[i].type = rand()%3 + 1; //assigns it a type from 1-3
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

        //check to see if it's overlapping with the player
        if (treasure[i].pos[0] == player.pos[0][0] &&
                treasure[i].pos[1] == player.pos[0][1]) {
            treasure[i].status = 0;
            test = -1;
        } else {
            //not overlapping, check next
            test = 1;
        }

        //check to see if it's overlapping with other treasure
        if (test == 1) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];
            for (int j = 0; j < MAX_TREASURE; j++) {
                if (x == treasure[j].pos[0] && y == treasure[j].pos[1]) {
                    //collision occurred
                    treasure[i].status = 0;
                    test = -1; //return to the first test
                }
            }
            //so if it passed through all values without changing to -1
            if (test == 1) {
                test = 2;
            }
        }

        //check for overlap with walls
        if (test == 2) {
            int x = treasure[i].pos[0];
            int y = treasure[i].pos[1];

            for (int j = 0; j < MAX_TREASURE; j+=2) {
                if (x == wall.here[j] && y == wall.here[j+1]){
                  //collision occurred
                  treasure[i].status = 0;
                  test = -1;
                }
            }
            
            //so if it was never changed, there was no collisions
            if (test == 2){
              test = 3;
            }
        }

        //this is i only if it passed all of the other tests
        if ( test == 3 ) {
            //generate the treasure, no collisions occurred
            treasure[i].status = 1;
            cout << i << ": (" << treasure[i].pos[0] << ", " <<
				treasure[i].pos[1] << ")";
        }
    }

    treasure[i].type = type;

}

//checks if player touched the treasure
void treasureCollision()
{
    //did the player get the treasure
    for (int i = 0; i < MAX_TREASURE; i++) {
        if (player.pos[0][0] == treasure[i].pos[0] &&
                player.pos[0][1] == treasure[i].pos[1]) {

            treasureGeneration(i);
            cout << "New position for treasure is : " << treasure[i].pos[0]
                 << ", " << treasure[i].pos[1];
            createSound();
            cleanupSound();

            //new position for treasure...
            // int collision=0;
            // int ntries=0;
            // while(1){
            // treasure[i].pos[0] = rand() % gridDim;
            // //cout << "X " << treasure[i].pos[0] << endl;
            // treasure[i].pos[1] = rand() % gridDim;
            // //cout << "Y " << treasure[i].pos[1] << endl;
            // collision=0;
            // createSound();
            // if (treasure[i].pos[0] == player.pos[0][0] &&
            // treasure[i].pos[1] == player.pos[0][1]) {
            // collision=1;
            // cleanupSound();
            // break;
            // }
            // if (!collision) break;
            // if (++ntries > 1000000) break;}
        }
        Log("new treasure: %i %i\n",treasure[i].pos[0],treasure[i].pos[1]);
        cout << "treasure collected" << endl;
        return;
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
