#define MAX_GRID 80

typedef struct t_grid {
	int status;
	float color[4];
} Grid;

typedef struct t_treasure {
	int status; //whether it has spawned
	int pos[2]; //position (x,y)
	int maxCount; //max # of treasures to spawn
	int maxRate; //max treasure spawn rate
	int increase; //how many treasures should spawn next
	int type; // coin = 1, jewel = 2
} Treasure;

extern int xres;
extern int yres;
extern Grid grid[MAX_GRID][MAX_GRID];
extern Treasure treasure[];
extern int done;
extern int gridDim;
extern int boardDim;
extern int gameover;
extern int winner;
extern int score;
extern void init(void);
extern void resetGame();
extern int level;
extern int treasureScore;
extern int soundFlag;
extern int start;
extern int timestart;
extern int soundNum;
extern int gamemodeSelected;

//extern void checkResize(XEvent *e);
//extern void checkMouse(XEvent *e);
//extern void checkKeys(XEvent *e);
//extern int done;

