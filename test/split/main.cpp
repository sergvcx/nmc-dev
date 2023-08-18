#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "general_header.h"
#include "triangulation.h"
#include "nmtype.h"

const int dim = 512;
float axRes[dim] __attribute__ ((section (".data.imu6")));
float ayRes[dim] __attribute__ ((section (".data.imu5")));
float bxRes[dim] __attribute__ ((section (".data.imu4")));
float byRes[dim] __attribute__ ((section (".data.imu3")));
float cxRes[dim] __attribute__ ((section (".data.imu2")));
float cyRes[dim] __attribute__ ((section (".data.imu1")));
float axToSplit[dim] __attribute__ ((section (".data.imu1")));
float ayToSplit[dim] __attribute__ ((section (".data.imu2")));
float bxToSplit[dim] __attribute__ ((section (".data.imu3")));
float byToSplit[dim] __attribute__ ((section (".data.imu4")));
float cxToSplit[dim] __attribute__ ((section (".data.imu5")));
float cyToSplit[dim] __attribute__ ((section (".data.imu6")));


bool vecCompare( TrianglePointers * srcVec, int srcCount )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		if(srcVec->v0.x[i * 2] != 70.0)
			return false;
		if(srcVec->v0.y[i * 2] != 10.0)
			return false;
		if(srcVec->v1.x[i * 2] != 20.0)
			return false;
		if(srcVec->v1.y[i * 2] != 20.0)
			return false;
		if(srcVec->v2.x[i * 2] != 40.0)
			return false;
		if(srcVec->v2.y[i * 2] != 10.0)
			return false;
		if(srcVec->v0.x[i * 2 + 1] != 10.0)
			return false;
		if(srcVec->v0.y[i * 2 + 1] != 10.0)
			return false;
		if(srcVec->v1.x[i * 2 + 1] != 20.0)
			return false;
		if(srcVec->v1.y[i * 2 + 1] != 20.0)
			return false;
		if(srcVec->v2.x[i * 2 + 1] != 40.0)
			return false;
		if(srcVec->v2.y[i * 2 + 1] != 10.0)
			return false;
	}
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

	TrianglePointers toSplitTriangles;

	toSplitTriangles.v0.x = axToSplit;
	toSplitTriangles.v0.y = ayToSplit;
	toSplitTriangles.v1.x = bxToSplit;
	toSplitTriangles.v1.y = byToSplit;
	toSplitTriangles.v2.x = cxToSplit;
	toSplitTriangles.v2.y = cyToSplit;

	TrianglePointers splittedTriangles;
	int splittedTrianglesCount = 0;

	splittedTriangles.v0.x = axRes;
	splittedTriangles.v0.y = ayRes;
	splittedTriangles.v1.x = bxRes;
	splittedTriangles.v1.y = byRes;
	splittedTriangles.v2.x = cxRes;
	splittedTriangles.v2.y = cyRes;

	for(int i = 0; i < dim; ++i)
	{
		toSplitTriangles.v0.x[i] = 70.0;
		toSplitTriangles.v1.x[i] = 20.0;
		toSplitTriangles.v2.x[i] = 10.0;
		toSplitTriangles.v0.y[i] = 10.0;
		toSplitTriangles.v1.y[i] = 20.0;
		toSplitTriangles.v2.y[i] = 10.0;
		splittedTriangles.v0.x[i] = 0.0;
		splittedTriangles.v1.x[i] = 0.0;
		splittedTriangles.v2.x[i] = 0.0;
		splittedTriangles.v0.y[i] = 0.0;
		splittedTriangles.v1.y[i] = 0.0;
		splittedTriangles.v2.y[i] = 0.0;
	}

	triangulationInit();

	for(int i = 2; i < dim / 2; i += 2)
	{
		t1 = clock();
		split( &toSplitTriangles, i, &splittedTriangles, &splittedTrianglesCount );
		t2 = clock();
		
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif	

		if( !vecCompare( &splittedTriangles, splittedTrianglesCount) )
		{
			printf("\n*****************************************************************************************************");
			printf("\nsplit on some sizes working incorrectly\n\n");
			printf("\nVec Size = %d", i);
			return -1;
		}
	}
	triangulationFree();
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nsplit test passed\n\n");

	return 0;
}

