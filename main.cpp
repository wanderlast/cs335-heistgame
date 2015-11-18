// Kevin Boberg
// cs335
// final project

#include"kevinB.h"
//#include "lianneL.h"
#include"main.h"
#include"log.h"
#include"sergioA.h"
#include"cstdlib"
#include<iostream>
#include"lianneL.h"

// character directions
#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3

// assigned to true when character hits wall then assigned back to false after moved from wall
bool myWall = false;
//bool again = true;

using namespace std;
void evenWall(int, int);
int loc[50];

// to call initWall(void) in main function
void physics(void)
{
    initWall();
}

// spawns walls for character to move around
void initWall(void)
{
        // arrays to recognize character position
        for(int i=4; i<=25; i+=2) 
        {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        // assignes walls to certain squares
        for(int i=4; i<=25; i+=2) 
        {
                wall.here[i] = i;
                wall.here[i+1] = 5;
        }        
evenWall(4, 25);        
    
        for(int i=5; i<=26; i+=2) 
        {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=5; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 5;
        }
        // first wall 5
evenWall(5, 26);

        for(int i=5; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=5; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }
evenWall(5, 25);

        for(int i=4; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }
evenWall(4, 26);

        for(int i=1; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 15;
        }
evenWall(1, 25);

        for(int i=0; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 15;
        }
evenWall(0,26);

        for(int i=1; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 20;
        }
evenWall(1, 25);

        for(int i=0; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 20;
        }
evenWall(0,26);

        for(int i=1; i<=37; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=37; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 25;
        }
evenWall(1,38);

        for(int i=0; i<=38; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=38; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 25;
        }
evenWall(0,38);

        for(int i=3; i<=29; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=3; i<=29; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 27;
        }
evenWall(3,29);

        for(int i=4; i<=28; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=28; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 27;
        }
evenWall(4,28);

        for(int i=2; i<=38; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=2; i<=38; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 31;
        }
evenWall(2,38);

        for(int i=3; i<=39; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=3; i<=39; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 31;
        }
evenWall(3,39);

        for(int i=8; i<=34; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=8; i<=34; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 36;
        }
evenWall(8,34);


        for(int i=7; i<=35; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=7; i<=35; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 36;
        }
evenWall(7,35);

        for(int i=6; i<=9; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=6; i<=9; i+=2) {
                wall.here[i] = 9;
                wall.here[i+1] = i;
        }
evenWall(6, 9);

        for(int i=7; i<=9; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=7; i<=9; i+=2) {
                wall.here[i] = 9;
                wall.here[i+1] = i;
        }
evenWall(7, 9);

        for(int i=10; i<=14; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=10; i<=14; i+=2) {
                wall.here[i] = 15;
                wall.here[i+1] = i;
        }
evenWall(10, 14);

        for(int i=11; i<=14; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=11; i<=14; i+=2) {
                wall.here[i] = 15;
                wall.here[i+1] = i;
        }
evenWall(11, 14);

        for(int i=28; i<=30; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=28; i<=30; i+=2) {
                wall.here[i] = 15;
                wall.here[i+1] = i;
        }
evenWall(28,31);

        for(int i=27; i<=30; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=27; i<=30; i+=2) {
                wall.here[i] = 15;
                wall.here[i+1] = i;
        }
evenWall(29,31);

}
void evenWall(int a, int b) {
        for(int i=a; i<=b; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                //      myWall = false;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                //cleanupSound();
                                        myWall = true;
                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                           
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000){
                                            
                                            myWall = true;
                                            movementWall(x);
                                        break;
                                        }
                        }
                        cout << "wall collision kb" << endl;
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                }
        }
}

// to restrict character from going through wall
void movementWall(int n)
{
        // when character goes down
        if(n == 0)
        {
                // moves character back if walks into wall
                if(myWall == true)
                {
                        player.pos[0][1] -= 1;
                        myWall = false;
                }
        } 

                // when character goes left
        else if (n == 1) 
        {
                if(myWall == true)
                {
                        player.pos[0][0] += 1;
                        myWall = false;
                }

        }

        else if (n == 2) 
        {
                if(myWall == true)
                {
                        player.pos[0][1] += 1;
                        myWall = false;
                }
        } 

        else 
        {
                if(myWall == true)
                {
                        player.pos[0][0] -= 1;
                        myWall = false;
                }
        }
}
