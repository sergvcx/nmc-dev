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
int flagsVerificat[dim] __attribute__ ((section (".data.imu7")));
float ax[dim] __attribute__ ((section (".data.imu1")));
float ay[dim] __attribute__ ((section (".data.imu2")));
float bx[dim] __attribute__ ((section (".data.imu3")));
float by[dim] __attribute__ ((section (".data.imu4")));
float cx[dim] __attribute__ ((section (".data.imu5")));
float cy[dim] __attribute__ ((section (".data.imu6")));

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

	for(int i = 0; i < dim; ++i)
	{
		srcTriangles.v0.x[i] = 30.0;
		srcTriangles.v1.x[i] = 20.0;
		srcTriangles.v2.x[i] = 10.0;
		srcTriangles.v0.y[i] = 30.0;
		srcTriangles.v1.y[i] = 20.0;
		srcTriangles.v2.y[i] = 10.0;
		flags[i] = 0;
		flagsVerificat[i] = 0;
	}

	srcTriangles.v0.x[3] = 70.0;
	flagsVerificat[3] = 1;

	triangulationInit();

	for(int i = 2; i < dim - 1; i += 2)
	{
		t1 = clock();
		generateMasks( &srcTriangles, i, maximumWidth, maximumHeight, flags );
		t2 = clock();
		
		// if(i == 4)
		// 	for(int j = 0; j < i; ++j)
		// 		printf("\nflags[%d] = %d; flagsCheck[%d] = %d", j, flags[j], j, flagsVerificat[j]);
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif	
		
		if( !vecCompare(flags, flagsVerificat, i) )
		{
			printf("\n*****************************************************************************************************");
			printf("\ngenerateMasks on some sizes working incorrectly\n\n");
			printf("\nVec Size = %d", i);
			return -1;
		}
		for(int j = 0; j < i; ++j)
		{
			flags[j] = 0;
		}
	}
	triangulationFree();
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\ngenerateMasks test passed\n\n");

	return 0;
}

