#define MAX_GRID 80

typedef struct t_player {
        //I'm currently keeping in the code for direction
        //in the case we substitute a directionally facing sprite in
        
        int status; //whether it exists
        int type; //what game mode it is
        int pos[MAX_GRID*MAX_GRID][2];
        int direction;
        //double timer;
        //double delay;
} Player;

extern Player player;

extern void initPlayer();
extern void initPlayer(int type);
extern void initTreasure();
extern void movement(int n);
extern int checkBorderCollision();
extern void gameSelector (int selection);
extern void initTreasure();
extern void initTreasure(int n);
extern void initTreasure(int start, int end);

extern void treasureGeneration(int i);
extern void treasureGeneration(int i, int type);
extern void treasureCollision();
extern int findTreasureValue(int i);
