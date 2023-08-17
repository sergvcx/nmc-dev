#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "general_header.h"
#include "triangulation.h"
#include "nmtype.h"
#include "nmpp.h"

const int dim = 4096;
float srcVec1[dim]  __attribute__ ((section (".data.imu0")));
float srcVec2[dim]  __attribute__ ((section (".data.imu1")));
float dstVec[dim] __attribute__ ((section (".data.imu2")));

int main()
{
#ifdef __NM__
	DISABLE_SYS_TIMER();
#endif
	clock_t t1 = clock();
	clock_t t2 = clock();
	clock_t dt = t2 - t1;

	int sumHash = 0;

	for(int i = 0; i < dim - 1; i += 1)
	{
		randFloatArray(srcVec1, i);
		randFloatArray(srcVec2, i);		

		t1 = clock();
		sumOfSquares( srcVec1, srcVec2, dstVec, i );
		t2 = clock();
// 		if(i == 64)
// {			for(int j = 0; j < i; ++j)
// 			{
// 				printf("\nsrc1[%d] = %f, src2[%d] = %f, dst[%d] = %f", j, srcVec1[j], j, srcVec2[j], j, dstVec[j]);

// 						}break;			}
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif		

		sumHash ^= hashRep32((long long *)dstVec, i);
	}
	
	if( sumHash != -535621593 )
	{
		printf("\n*****************************************************************************************************");
		printf("\nsumOfSquares on some sizes working incorrectly\n\n");
		return -1;
	}
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nsumOfSquares test passed\n\n");

	return 0;
}

