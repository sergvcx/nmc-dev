#include "stdio.h"
#include "../../include/general_header.h"
#include "../../include/triangulation.h"

const int dim = 4096;
float srcVec1[dim];
float srcVec2[dim];
float dstVec[dim];

int main()
{
	float nVal[2] = {0.5, 0.5};
	int hashSum = 0;

	for(int i = 0; i < dim; i += 2)
	{
		randFloatArray( srcVec1, i );
		randFloatArray( srcVec2, i );
		nmppsAdd_MulC_32f(srcVec1, srcVec2, dstVec, nVal, i);
		hashSum ^= hashRep32((long long *)dstVec, i);
	}

	if( hashSum != -910170037 )
	{
		printf("\n*****************************************************************************************************");
		printf("\nnmppsAdd_MulC_32f on some sizes working incorrectly\n\n");
		return -1;
	}

	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nnmppsAdd_MulC_32f test passed\n\n");

	return 0;
}

