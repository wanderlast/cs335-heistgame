#define MAX_GRID 80

typedef struct t_player {
	//I'm currently keeping in the code for direction
	//in the case we substitute a directionally facing sprite in
	
	int status; //whether it exists
	//int length;
	int pos[MAX_GRID*MAX_GRID][2];
	int direction;
	double timer;
	double delay;
} Player;

extern Player player;

extern void movement();
extern int checkCollision();
