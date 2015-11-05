#define MAX_GRID 80

typedef struct t_grid {
	int status;
	float color[4];
} Grid;

typedef struct t_treasure {
	int status;
	int pos[2];
	int type; // coin = 1, jewel = 2
} Treasure;

extern int xres;
extern int yres;
extern Grid grid[MAX_GRID][MAX_GRID];
extern Treasure treasure;
extern int done;
extern int gridDim;
extern int boardDim;
extern int gameover;
extern int winner;
extern int score;

//extern void checkResize(XEvent *e);
//extern void checkMouse(XEvent *e);
//extern void checkKeys(XEvent *e);
//extern int done;
