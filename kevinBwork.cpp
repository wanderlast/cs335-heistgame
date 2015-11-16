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
bool again = true;

using namespace std;

// to call initWall(void) in main function
void physics(void)
{
    initWall();
}

// spawns walls for character to move around
void initWall(void)
{
        int loc[50];
        
        // arrays to recognize character position
        for(int i=4; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        // assignes walls to certain squares
        for(int i=4; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 5;
        }
        
if(again == true) {
        treasure[0].pos[0] = 4;
        treasure[0].pos[1] = 5;
      again = false;
}
        
        // respawns treasure if spawns in wall
    
       

        // to detect if character hits into wall
        for(int i=4; i<=25; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
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
                                //      if(myWall == true)
                                //      player.pos[0][1] = -1;
                                //myWall = false;
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
                //                      myWall = false;
                        }
                //      myWall = false;
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl; 
               //break;
                //player.pos[0][1] -= -1;
                //checkWall();
        //      return;
                }
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

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                myWall = true;
                                                movementWall(x);
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=5; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=5; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }

        for(int i=5; i<=25; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                myWall = true;
                                                movementWall(x);
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=4; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 9;
        }

        for(int i=4; i<=26; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
                if (loc[i] == wall.here[i] && loc[i+1] == wall.here[i+1]) {
                        int collision=0;
                        int ntries=0;
                        while(1) {
                                collision=0;
                                //createSound();
                                        if (wall.here[i] == player.pos[0][0] &&
                                        wall.here[i+1] == player.pos[0][1]) {
                                                collision=1;
                                                myWall = true;
                                                movementWall(x);
                                                //cleanupSound();
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        
        //        return;
                }
        }


        for(int i=1; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 15;
        }

        for(int i=1; i<=25; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
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

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

// 20
        for(int i=1; i<=25; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=25; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 20;
        }

        for(int i=1; i<=25; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=0; i<=26; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=26; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 20;
        }

        for(int i=0; i<=26; i+=2) {

                        for(int j=0; j<15; j++) {

                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        // 25
        for(int i=1; i<=37; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=1; i<=37; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 25;
        }

        for(int i=1; i<=37; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=0; i<=38; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=0; i<=38; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 25;
        }

        for(int i=0; i<=38; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }
// 27
        for(int i=3; i<=29; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=3; i<=29; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 27;
        }

        for(int i=3; i<=29; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=4; i<=28; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=4; i<=28; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 27;
        }

        for(int i=4; i<=28; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

// 31 2-39
        for(int i=3; i<=39; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=3; i<=39; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 31;
        }

        for(int i=3; i<=39; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=2; i<=38; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=2; i<=38; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 31;
        }

        for(int i=2; i<=38; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }
// 36 7-35
        for(int i=7; i<=35; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=7; i<=35; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 36;
        }

        for(int i=7; i<=35; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }


                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }

        for(int i=8; i<=34; i+=2) {
                loc[i] = player.pos[0][0];
                loc[i+1] = player.pos[0][1];
        }

        for(int i=8; i<=34; i+=2) {
                wall.here[i] = i;
                wall.here[i+1] = 36;
        }

        for(int i=8; i<=34; i+=2) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
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
                                                myWall = true;
                                                movementWall(x);
                                                break;
                                        }
                                        if (!collision) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }
                                        if (++ntries > 1000000) {
                                            myWall = true;
                                            movementWall(x);
                                            break;
                                        }


                        }
                Log("new wall: %i %i\n",wall.here[i],wall.here[i+1]);
                //cout << "wall hit KB" << endl;  
        //      return;
                }
        }
/*for(int i=0; i<40; i++) {

                        for(int j=0; j<15; j++) {
                        while (treasure[j].pos[0] == wall.here[i] &&
                                        treasure[j].pos[1] == wall.here[i+1]) {
                        //      physics();
cout << "hereakdsfnuinqao[;;;beniisetuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuutvrrrrrenwoooooovtutirtfjkdfjdkfjdkjdkjfdkfdjfdkfjdkfdjkjdjdkfdkfjdkfdjfdkjdkfdkjfdkjkdjkdjfkdjfkdjdjfkdjfkdjfkdjfkdjkfj" << endl;
                        treasure[j].pos[0] = rand() % gridDim;
                        //cout << treasure.pos[0] << endl;
                        treasure[j].pos[1] = rand() % gridDim;
                        }
                        }
}*/
}
// to restrict character from going through wall
void movementWall(int n)
{
        // when character goes down
        if(n == 0){
        //      if(myWall == false) {
                //player.direction = DIRECTION_DOWN;
                //player.pos[0][1] += 1;
        //      }
                
                // moves character back if walks into wall
                if(myWall == true){
                  //  cout << "here" << endl;
                        player.pos[0][1] -= 1;
                        myWall = false;
        //              return;
                //      myWall = false;

                x=0;
                }
                //if(initWall() == 0)
                //cout << "(" << player.pos[0][0] << "," <<
                // player.pos[0][1] << ")" << endl;
                
                // when character goes left
        } else if (n == 1) {
        //      player.direction = DIRECTION_LEFT;
        //      player.pos[0][0] -= 1;
                if(myWall == true){
                        player.pos[0][0] += 1;
                        myWall = false;
                }
                x=1;
        //      cout << "(" << player.pos[0][0] << "," <<
        //      player.pos[0][1] << ")" << endl;
        } else if (n == 2) {
        //      player.direction = DIRECTION_UP;
        //      player.pos[0][1] -= 1;
                if(myWall == true){
                        player.pos[0][1] += 1;
                        myWall = false;
                }
                x=2;
        //      cout << "(" << player.pos[0][0] << "," <<
        //      player.pos[0][1] << ")" << endl;
        } else {
        //      player.direction = DIRECTION_RIGHT;
        //      player.pos[0][0] += 1;
                if(myWall == true){ // if(checkCollision() == 0) {
                        player.pos[0][0] -= 1;
                        myWall = false;
                }
                x=3;
        //      cout << "(" << player.pos[0][0] << "," <<
        //      player.pos[0][1] << ")" << endl;
        }

        //return;
}
