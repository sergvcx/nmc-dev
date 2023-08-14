#include "stdio.h"
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
	float nVal[2] = {0.5, 0.5};

	for(int i = 2; i < dim; i += 2)
	{
		randFloatArray( srcVec1, i );
		randFloatArray( srcVec2, i );
		
		nmppsAdd_MulC_32f(srcVec1, srcVec2, dstVec, nVal, i);
		verifivationFunc(srcVec1, srcVec2, dstStandardVec, nVal, i);
		
		if(i == 2)
			for(int j = 0; j < i; ++j)
				printf("\n%f; %f", dstVec[j], dstStandardVec[j]);

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

