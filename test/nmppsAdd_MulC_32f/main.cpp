#include "stdio.h"
#include "time.h"
#include <maxtimer.h>
#include "../../include/general_header.h"
#include "../../include/triangulation.h"

const int dim = 4096;
float srcVec1[dim];
float srcVec2[dim];
float dstVec[dim];
float dstStandardVec[dim];

void verifivationFunc( float* srcVec1, float* srcVec2, float* dstVec, float* nVal, int srcCount )
{
	for(int i = 0; i < srcCount / 2; ++i)
	{
		dstVec[i * 2] = (srcVec1[i * 2] + srcVec2[i * 2]) * nVal[0];
		dstVec[i * 2 + 1] = (srcVec1[i * 2 + 1] + srcVec2[i * 2 + 1]) * nVal[1];
	}
}

bool vecCompare( float* srcVec1, float* srcVec2, int srcCount )
{
	for(int i = 0; i < srcCount; ++i)
		if(srcVec1[i] != srcVec2[i])
			return false;
	return true;
}

int main()
{
//	DISABLE_SYS_TIMER();
//	clock_t t1 = clock();
//	clock_t t2 = clock();
//	clock_t dt = t2 - t1;
	
	float nVal[2] = {0.5, 0.5};

	for(int i = 2; i < dim - 1; i += 1)
	{
		randFloatArray( srcVec1, i );
		randFloatArray( srcVec2, i );
		
//		t1 = clock();
		nmppsAdd_MulC_32f(srcVec1, srcVec2, dstVec, nVal, i + 1);
//		t2 = clock();
		
		verifivationFunc(srcVec1, srcVec2, dstStandardVec, nVal, i + 1);
		
//		printf("Time for ASM func %lf\n\n", (float)(t2 - t1 - dt) / i);
		
		if( !vecCompare(dstVec, dstStandardVec, i) )
		{
			printf("\n*****************************************************************************************************");
			printf("\nnmppsAdd_MulC_32f on some sizes working incorrectly\n\n");
			printf("\nVec Size = %d", i);
			return -1;
		}
	}
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nnmppsAdd_MulC_32f test passed\n\n");

	return 0;
}

