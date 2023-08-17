#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "general_header.h"
#include "triangulation.h"
#include "nmtype.h"

const int dim = 512;
int maxEdgeArray[dim] __attribute__ ((section (".data.imu0")));
int maxEdgeArrayVerif[dim] __attribute__ ((section (".data.imu1")));
float edge1[dim] __attribute__ ((section (".data.imu2")));
float edge2[dim] __attribute__ ((section (".data.imu3")));
float edge3[dim] __attribute__ ((section (".data.imu4")));

void verifivationFunc( int * maxEdgeArray, float * edge1, float * edge2, float * edge3, int edgeCount )
{
	for(int i = 0; i < edgeCount; ++i)
	{
		if( edge1[i] > edge2[i] )
			if( edge1[i] > edge3[i] )
				maxEdgeArray[i] = 1;
			else
				maxEdgeArray[i] = 3;
		else
			if( edge2[i] > edge3[i] )
				maxEdgeArray[i] = 2;
			else
				maxEdgeArray[i] = 3;
	}
}

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

	triangulationInit();

	for(int i = 2; i < dim - 1; i += 2)
	{
		randFloatArray(edge1, i);
		randFloatArray(edge2, i);
		randFloatArray(edge3, i);

		t1 = clock();
		maxEdge( maxEdgeArray, edge1, edge2, edge3, i );
		t2 = clock();
		
		verifivationFunc( maxEdgeArrayVerif, edge1, edge2, edge3, i );

		// if(i == 40)
		// 	for(int j = 0; j < i; ++j)
		// 		printf("\nmaxEdge[%d] = %d; edge1[%d] = %f; edge2[%d] = %f; edge3[%d] = %f", j, maxEdgeArray[j], j, edge1[j], j, edge2[j], j, edge3[j]);
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif	
		
		if( !vecCompare(maxEdgeArray, maxEdgeArrayVerif, i) )
		{
			printf("\n*****************************************************************************************************");
			printf("\nmaxEdge on some sizes working incorrectly\n\n");
			printf("\nVec Size = %d", i);
			return -1;
		}
	}
	triangulationFree();
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nmaxEdge test passed\n\n");

	return 0;
}

