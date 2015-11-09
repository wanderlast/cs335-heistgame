/*typedef struct t_button {
//	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	float color[3];
	float dcolor[3];
	unsigned int text_color;
} Button;
extern Button button;*/
//extern Player player;
typedef struct t_wall {
	int point;
	int here[50];
} Wall;
extern Wall wall;
extern void getGridCenter(const int i, const int j, int cent[2]);
extern void physics(void);
