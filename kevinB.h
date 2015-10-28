typedef struct t_button {
//	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	float color[3];
	float dcolor[3];
	unsigned int text_color;
} Button;
extern Button button;
extern int bq;
extern void map(int bq);
