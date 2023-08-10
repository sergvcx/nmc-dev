#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "../../../include/triangulation.h"
#include "../../../include/primitive.h"
#include "../../../include/nmtype.h"
#include "nmpp.h"
//#include "VShell.h"

const int size = 4;
const int maximumDestinationSize = 128;
const int maximumHeight = 40;
const int maximumWidth  = 40;
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

	printf("\nGiven Triangles:");
	for(int i = 0; i < size; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testTrianglesArray.v0.x[i], testTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testTrianglesArray.v1.x[i], testTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testTrianglesArray.v2.x[i], testTrianglesArray.v2.y[i]);
	}
	

	triangulation( &testTrianglesArray, size, maximumWidth, maximumHeight, maximumDestinationSize, &testResultTrianglesArray, &treatedCounter );


	int resultCount = 0;
	if( size + treatedCounter > maximumDestinationSize )
		resultCount = maximumDestinationSize;
	else
		resultCount = size + treatedCounter;
	printf("\n\n%d Result Triangles:", resultCount);
	/*
	for(int i = 0; i < resultCount; ++i)
	{
		printf("\nTriangle %d point a: ( %f; %f )", i + 1, testResultTrianglesArray.v0.x[i], testResultTrianglesArray.v0.y[i]);
		printf("\nTriangle %d point b: ( %f; %f )", i + 1, testResultTrianglesArray.v1.x[i], testResultTrianglesArray.v1.y[i]);
		printf("\nTriangle %d point c: ( %f; %f )\n", i + 1, testResultTrianglesArray.v2.x[i], testResultTrianglesArray.v2.y[i]);
	}
	*/
	printf("\n\n");
	/*
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
	*/
	/*
	float * a = (float*)malloc(100 * sizeof(float));
	float * b = (float*)malloc(100 * sizeof(float));
	float * c = (float*)malloc(100 * sizeof(float));
	for(int i = 0; i < 100; ++i)
	{
		a[i] = 100;
		b[i] = i;
	}
	//float constanta[2] = {0.5, 0.5};
	float * constanta = (float*)malloc(2 * sizeof(float));
	constanta[0] = 0.5;
	constanta[1] = 0.5;
	nmppsAverage(a, b, c, constanta, 100);
	for(int i = 0; i < 100; ++i)
		printf("\n%f", c[i]);
	printf("\n\n\n");

	printf("\n");
	for(int i = 0; i < 100; ++i)
		printf("\nA[%d]: %f; B[%d]: %f; NewP: %f\n", i, a[i], i, b[i], c[i]);
	printf("\n");	
	*/
	return 0;
}

