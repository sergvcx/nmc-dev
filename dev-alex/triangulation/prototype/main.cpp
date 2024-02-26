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

const int maximumDestinationSize = 256;
const int maximumHeight = 30;
const int maximumWidth  = 30;
static const int WIDTH  = 512;
static const int HEIGHT = 512;

int main()
{
	int size = 4;
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

	float ax[maximumDestinationSize];
	float ay[maximumDestinationSize];
	float bx[maximumDestinationSize];
	float by[maximumDestinationSize];
	float cx[maximumDestinationSize];
	float cy[maximumDestinationSize];

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
	
	TrianglePointers savedTrianglesArray;

	float axSaved[size];
	float aySaved[size];
	float bxSaved[size];
	float bySaved[size];
	float cxSaved[size];
	float cySaved[size];

	savedTrianglesArray.v0.x = axSaved;
	savedTrianglesArray.v0.y = aySaved;
	savedTrianglesArray.v1.x = bxSaved;
	savedTrianglesArray.v1.y = bySaved;
	savedTrianglesArray.v2.x = cxSaved;
	savedTrianglesArray.v2.y = cySaved;

	for(int i = 0; i < size; ++i)
	{
		savedTrianglesArray.v0.x[i] = testTrianglesArray.v0.x[i];
		savedTrianglesArray.v0.y[i] = testTrianglesArray.v0.y[i];
		savedTrianglesArray.v1.x[i] = testTrianglesArray.v1.x[i];
		savedTrianglesArray.v1.y[i] = testTrianglesArray.v1.y[i];
		savedTrianglesArray.v2.x[i] = testTrianglesArray.v2.x[i];
		savedTrianglesArray.v2.y[i] = testTrianglesArray.v2.y[i];
	}

	printf("\n%d Given Triangles:\n", size);
	// for(int i = 0; i < size; ++i)
	// {
	// 	printf("\nTriangle %d point a: ( %f; %f )", i + 1, savedTrianglesArray.v0.x[i], savedTrianglesArray.v0.y[i]);
	// 	printf("\nTriangle %d point b: ( %f; %f )", i + 1, savedTrianglesArray.v1.x[i], savedTrianglesArray.v1.y[i]);
	// 	printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, savedTrianglesArray.v2.x[i], savedTrianglesArray.v2.y[i]);
	// }
	
	printf("\n\ntriangulationInit %d\n", triangulationInit());
	
	while ( treatedCounter < maximumDestinationSize && size != 0 )
	{
		triangulate( &testTrianglesArray, &size, maximumWidth, maximumHeight, &testResultTrianglesArray, &treatedCounter );
		 printf("\nSuitable Triangles: %d\nSplitted triangles: %d\n", treatedCounter, size);
	}

	triangulationFree();

	int resultCount = 0;
	if( size + treatedCounter > maximumDestinationSize )
		resultCount = maximumDestinationSize;
	else
		resultCount = size + treatedCounter;
	printf("\n\n%d Result Triangles:\n", resultCount);
	// for(int i = 0; i < resultCount; ++i)
	// {
	// 	printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
	// 	printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
	// 	printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	// }
	
	for(int i = 0; i < size + treatedCounter; ++i)
	{
		NMASSERT(abs(testResultTrianglesArray.v0.x[i] - testResultTrianglesArray.v1.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v2.x[i] - testResultTrianglesArray.v1.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v0.x[i] - testResultTrianglesArray.v2.x[i]) <= maximumWidth);
		NMASSERT(abs(testResultTrianglesArray.v0.y[i] - testResultTrianglesArray.v1.y[i]) <= maximumHeight);
		NMASSERT(abs(testResultTrianglesArray.v2.y[i] - testResultTrianglesArray.v1.y[i]) <= maximumHeight);
		NMASSERT(abs(testResultTrianglesArray.v0.y[i] - testResultTrianglesArray.v2.y[i]) <= maximumHeight);	
		printf("\nTriangle %d checked\n", i + 1);
	}
	
	printf("\n\n");
#ifdef __NM__
#else	
	if(!VS_Init())
    	return 0;
	VS_STOP_COLOR pStopColor[2]={
		VS_MAKE_STOP_COLOR(3	,VS_WHITE),
		VS_MAKE_STOP_COLOR(26	,VS_BLACK),
	};
	S_VS_Pal palette[256];
	VS_CreateCustomPalette(palette,pStopColor, 1);

	VS_CreateImage("Given Triangles", 0, WIDTH, HEIGHT, VS_RGB8, palette);
	VS_CreateImage("Result Triangles", 1, WIDTH, HEIGHT, VS_RGB8, palette);
	while(VS_Run())
	{
		for(int i = 0; i < 4; ++i)
		{
			VS_Line(0, savedTrianglesArray.v0.x[i], savedTrianglesArray.v0.y[i], savedTrianglesArray.v1.x[i], savedTrianglesArray.v1.y[i], RGB(0, 0, 0));
			VS_Line(0, savedTrianglesArray.v0.x[i], savedTrianglesArray.v0.y[i], savedTrianglesArray.v2.x[i], savedTrianglesArray.v2.y[i], RGB(0, 0, 0));
			VS_Line(0, savedTrianglesArray.v2.x[i], savedTrianglesArray.v2.y[i], savedTrianglesArray.v1.x[i], savedTrianglesArray.v1.y[i], RGB(0, 0, 0));
		}

		for(int i = 0; i < resultCount; ++i)
		{
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(0, 0, 0));
			VS_Line(1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i], testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], RGB(0, 0, 0));
			VS_Line(1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i], testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i], RGB(0, 0, 0));
		}

		VS_Rectangle(0, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(0, 0, 0), RGB(255, 255, 255));
		VS_Rectangle(1, 10, 300, 10 + maximumWidth, 300 + maximumHeight, RGB(0, 0, 0), RGB(255, 255, 255));

		VS_Draw(VS_DRAW_ALL);
	}
#endif
	return 0;
}

