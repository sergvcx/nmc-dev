#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "triangulation.h"
#include "primitive.h"
#include "nmtype.h"
#include "nmpp.h"
#undef NDEBUG
#include "nmassert.h"
#ifdef __NM__
#else	
#include "VShell.h"
#endif

const int size = 4;
const int maximumDestinationSize = 256;
const int maximumHeight = 30;
const int maximumWidth  = 30;
static const int WIDTH  = 512;
static const int HEIGHT = 512;

int main()
{
	TrianglePointers testResultTrianglesArray;
	int treatedCounter = 0;

	float axRes[maximumDestinationSize];
	float ayRes[maximumDestinationSize];
	float bxRes[maximumDestinationSize];
	float byRes[maximumDestinationSize];
	float cxRes[maximumDestinationSize];
	float cyRes[maximumDestinationSize];

	testResultTrianglesArray.v0.x = axRes;
	testResultTrianglesArray.v0.y = ayRes;
	testResultTrianglesArray.v1.x = bxRes;
	testResultTrianglesArray.v1.y = byRes;
	testResultTrianglesArray.v2.x = cxRes;
	testResultTrianglesArray.v2.y = cyRes;

	TrianglePointers testTrianglesArray;

	float ax[size];
	float ay[size];
	float bx[size];
	float by[size];
	float cx[size];
	float cy[size];

	testTrianglesArray.v0.x = ax;
	testTrianglesArray.v0.y = ay;
	testTrianglesArray.v1.x = bx;
	testTrianglesArray.v1.y = by;
	testTrianglesArray.v2.x = cx;
	testTrianglesArray.v2.y = cy;
	testTrianglesArray.v0.x[0] = 0;
	testTrianglesArray.v0.y[0] = 0;
	testTrianglesArray.v1.x[0] = 150;
	testTrianglesArray.v1.y[0] = 50;
	testTrianglesArray.v2.x[0] = 100;
	testTrianglesArray.v2.y[0] = 150;

	testTrianglesArray.v0.x[1] = 150;
	testTrianglesArray.v0.y[1] = 50;
	testTrianglesArray.v1.x[1] = 200;
	testTrianglesArray.v1.y[1] = 300;
	testTrianglesArray.v2.x[1] = 100;
	testTrianglesArray.v2.y[1] = 150;

	testTrianglesArray.v0.x[2] = 150;
	testTrianglesArray.v0.y[2] = 50;
	testTrianglesArray.v1.x[2] = 200;
	testTrianglesArray.v1.y[2] = 300;
	testTrianglesArray.v2.x[2] = 210;
	testTrianglesArray.v2.y[2] = 120;
	
	testTrianglesArray.v0.x[3] = 150;
	testTrianglesArray.v0.y[3] = 50;
	testTrianglesArray.v1.x[3] = 300;
	testTrianglesArray.v1.y[3] = 90;
	testTrianglesArray.v2.x[3] = 210;
	testTrianglesArray.v2.y[3] = 120;

	printf("\n%d Given Triangles:", size);
	/*
	for(int i = 0; i < size; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i]);
	}
	*/
	
	triangulationInit();

	triangulate( &testTrianglesArray, 2, maximumWidth, maximumHeight, maximumDestinationSize, &testResultTrianglesArray, &treatedCounter );
	
	triangulationFree();

	int resultCount = 0;
	if( 2 + treatedCounter > maximumDestinationSize )
		resultCount = maximumDestinationSize;
	else
		resultCount = 2 + treatedCounter;
	printf("\n\n%d Result Triangles:", resultCount);

	
	for(int i = 0; i < resultCount; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	}
	

	for(int i = 0; i < 2 + treatedCounter; ++i)
	{
		printf("\ni %d\n", i);
		NMASSERT(abs(testResultTrianglesArray.v0.x[i] - testResultTrianglesArray.v1.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v2.x[i] - testResultTrianglesArray.v1.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v0.x[i] - testResultTrianglesArray.v2.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v0.y[i] - testResultTrianglesArray.v1.y[i]) <= maximumHeight);
		NMASSERT(abs(testResultTrianglesArray.v2.y[i] - testResultTrianglesArray.v1.y[i]) <= maximumHeight);
		NMASSERT(abs(testResultTrianglesArray.v0.y[i] - testResultTrianglesArray.v2.y[i]) <= maximumHeight);	
	}

	printf("\n\n");
#ifdef __NM__
#else	
	if(!VS_Init())
    	return 0;
	VS_CreateImage("Given Triangles", 0, WIDTH, HEIGHT, VS_RGB8, NULL);
	VS_CreateImage("Result Triangles", 1, WIDTH, HEIGHT, VS_RGB8, NULL);
	while(VS_Run())
	{
		for(int i = 0; i < size; ++i)
		{
			VS_Line(0, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i], testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i], RGB(255, 255, 255));
			VS_Line(0, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i], testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i], RGB(255, 255, 255));
			VS_Line(0, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i], testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i], RGB(255, 255, 255));
		}

		for(int i = 0; i < resultCount; ++i)
		{
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(255, 255, 255));
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], RGB(255, 255, 255));
			VS_Line(1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(255, 255, 255));
		}

		VS_Rectangle(0, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(255, 255, 255), RGB(0, 0, 0));
		VS_Rectangle(1, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(255, 255, 255), RGB(0, 0, 0));

		VS_Draw(VS_DRAW_ALL);
	}
#endif
	return 0;
}

