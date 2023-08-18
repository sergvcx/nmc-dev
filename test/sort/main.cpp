#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "general_header.h"
#include "triangulation.h"
#include "nmtype.h"

const int dim = 512;
const int maximumHeight = 30;
const int maximumWidth  = 30;
int flags[dim] __attribute__ ((section (".data.imu0")));
float ax[dim] __attribute__ ((section (".data.imu1")));
float ay[dim] __attribute__ ((section (".data.imu2")));
float bx[dim] __attribute__ ((section (".data.imu3")));
float by[dim] __attribute__ ((section (".data.imu4")));
float cx[dim] __attribute__ ((section (".data.imu5")));
float cy[dim] __attribute__ ((section (".data.imu6")));
float axRes[dim] __attribute__ ((section (".data.imu6")));
float ayRes[dim] __attribute__ ((section (".data.imu5")));
float bxRes[dim] __attribute__ ((section (".data.imu4")));
float byRes[dim] __attribute__ ((section (".data.imu3")));
float cxRes[dim] __attribute__ ((section (".data.imu2")));
float cyRes[dim] __attribute__ ((section (".data.imu1")));
float axToSplit[dim] __attribute__ ((section (".data.imu6")));
float ayToSplit[dim] __attribute__ ((section (".data.imu5")));
float bxToSplit[dim] __attribute__ ((section (".data.imu4")));
float byToSplit[dim] __attribute__ ((section (".data.imu3")));
float cxToSplit[dim] __attribute__ ((section (".data.imu2")));
float cyToSplit[dim] __attribute__ ((section (".data.imu1")));


bool vecCompare( int* srcVec1, int* srcVec2, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
		if(srcVec1[i] != srcVec2[i])
			return false;
	return true;
}

int main()
{
#ifdef __NM__
	DISABLE_SYS_TIMER();
#endif	
	clock_t t1 = clock();
	clock_t t2 = clock();
	clock_t dt = t2 - t1;
	
	TrianglePointers srcTriangles;

	srcTriangles.v0.x = ax;
	srcTriangles.v0.y = ay;
	srcTriangles.v1.x = bx;
	srcTriangles.v1.y = by;
	srcTriangles.v2.x = cx;
	srcTriangles.v2.y = cy;

	TrianglePointers toSplitTriangles;
	int toSplitTrianglesCount = 0;

	toSplitTriangles.v0.x = axToSplit;
	toSplitTriangles.v0.y = ayToSplit;
	toSplitTriangles.v1.x = bxToSplit;
	toSplitTriangles.v1.y = byToSplit;
	toSplitTriangles.v2.x = cxToSplit;
	toSplitTriangles.v2.y = cyToSplit;

	TrianglePointers resultTriangles;
	int resultCount = 0;

	resultTriangles.v0.x = axRes;
	resultTriangles.v0.y = ayRes;
	resultTriangles.v1.x = bxRes;
	resultTriangles.v1.y = byRes;
	resultTriangles.v2.x = cxRes;
	resultTriangles.v2.y = cyRes;

	for(int i = 0; i < dim; ++i)
	{
		srcTriangles.v0.x[i] = 30.0;
		srcTriangles.v1.x[i] = 20.0;
		srcTriangles.v2.x[i] = 10.0;
		srcTriangles.v0.y[i] = 30.0;
		srcTriangles.v1.y[i] = 20.0;
		srcTriangles.v2.y[i] = 10.0;
		flags[i] = 0;
		toSplitTriangles.v0.x[i] = 0.0;
		toSplitTriangles.v1.x[i] = 0.0;
		toSplitTriangles.v2.x[i] = 0.0;
		toSplitTriangles.v0.y[i] = 0.0;
		toSplitTriangles.v1.y[i] = 0.0;
		toSplitTriangles.v2.y[i] = 0.0;
		resultTriangles.v0.x[i] = 0.0;
		resultTriangles.v1.x[i] = 0.0;
		resultTriangles.v2.x[i] = 0.0;
		resultTriangles.v0.y[i] = 0.0;
		resultTriangles.v1.y[i] = 0.0;
		resultTriangles.v2.y[i] = 0.0;
	}
	srcTriangles.v0.x[1] = 70.0;
	flags[1] = 1;

	triangulationInit();

	for(int i = 2; i < dim - 1; i += 2)
	{
		t1 = clock();
		sort( &srcTriangles, i, &toSplitTriangles, &toSplitTrianglesCount, &resultTriangles, &resultCount, flags );
		t2 = clock();
		
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif	
		
		if( toSplitTrianglesCount != 1 )
		{
			printf("\n*****************************************************************************************************");
			printf("\nsort on some sizes working incorrectly\n\n");
			printf("\nVec Size = %d", i);
			return -1;
		}
		toSplitTrianglesCount = 0;
		resultCount = 0;
	}
	triangulationFree();
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nsort test passed\n\n");

	return 0;
}

