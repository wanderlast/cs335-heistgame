#include"kevinB.h"
#include"main.h"
using namespace std;

void getGridCenter(const int i, const int j, int cent[2])
{
	//This function can be optimized, and made more generic.
	int b2 = boardDim/2;
	int screenCenter[2] = {xres/2, yres/2};
	int s0 = screenCenter[0];
	int s1 = screenCenter[1];
	int bq;
	//quad upper-left corner
	int quad[2];
	//bq is the width of one grid section
	
	//map();
	bq = (boardDim / gridDim);


	//-------------------------------------
	//because y dimension is bottom-to-top in OpenGL.
	int i1 = gridDim - i - 1;
	quad[0] = s0-b2;
	quad[1] = s1-b2;
	cent[0] = quad[0] + bq/2;
	cent[1] = quad[1] + bq/2;
	cent[0] += (bq * j);
	cent[1] += (bq * i1);
}
