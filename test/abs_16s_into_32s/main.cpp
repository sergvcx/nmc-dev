#include "stdio.h"
#include "../../include/general_header.h"

const int dim = 8192;
int sourceArray[dim / 2];
int absResultArray[dim];

int main()
{
	int hashSum = 0;
	for(int i = -32768; i < 32767; i += dim)
	{
		makeShortArray(sourceArray, i, i + dim);
		abs_16s(sourceArray, absResultArray, dim);
		hashSum ^= hashRep32((long long *)absResultArray, dim);
	}
	
	if( hashSum != -872413269 )
	{
		printf("\n*****************************************************************************************************");
		printf("\nAbs on some values working incorrectly\n\n");
		return -1;
	}

	makeShortArray(sourceArray, 0, dim);
	for(int i = 0; i < dim; i += 4)
	{
		abs_16s(sourceArray, absResultArray, i);
		hashSum ^= hashRep32((long long *)absResultArray, i);
	}
	
	if( hashSum != 1717436773 )
	{
		printf("\n*****************************************************************************************************");
		printf("\nAbs on some sizes working incorrectly\n\n");
		return -1;
	}


	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nAbs test passed\n\n");

	return 0;
}

