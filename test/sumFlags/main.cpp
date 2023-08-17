#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "general_header.h"
#include "triangulation.h"
#include "nmtype.h"
#include "nmpp.h"

const int dim = 4096;
int srcVec[dim] __attribute__ ((section (".data.imu0")));
int dstVec[dim] __attribute__ ((section (".data.imu1")));

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
		for(int j = 0; j < i; ++j)
			dstVec[j] = 0;

		randArray( srcVec, i / 32 + 1 );
		
		t1 = clock();
		sumFlags(srcVec, dstVec, i);
		t2 = clock();
		// if(i == 4){
		// 	for(int j = 0; j < i; ++j)
		// 		printf("\nflags[%d] = %d; flagsCheck[%d] = %d", j, nmppsGet_1(srcVec, j), j, dstVec[j]);
		// break;}
#ifdef __NM__
		printf("\nSize =  %4d; clocks/element %lf", i, (float)(t2 - t1 - dt) / i);
#endif		

		sumHash ^= hashRep32((long long *)dstVec, i);
	}
	// printf("\n%d\n", sumHash);
#ifdef __NM__
	if( sumHash != 0 )
#else
	if( sumHash != -2104638998 )
#endif
	{
		printf("\n*****************************************************************************************************");
		printf("\nsumFlags on some sizes working incorrectly\n\n");
		return -1;
	}
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nsumFlags test passed\n\n");

	return 0;
}

