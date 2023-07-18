#include "stdio.h"
#include "stdlib.h"
#include "../../include/general_header.h"

const int dim = 4096;
int minArray[dim];
int maxArray[dim];
int minArray_C[dim];
int maxArray_C[dim];

void minMaxMas_C(int* minArray, int* maxArray, int dim)
{
	while(dim > 0)
	{
		dim--;
		if(*(minArray + dim) > *(maxArray + dim))
		{
			*(minArray + dim) = *(maxArray + dim) - *(minArray + dim);
			*(maxArray + dim) = *(maxArray + dim) - *(minArray + dim);
			*(minArray + dim) = *(minArray + dim) + *(maxArray + dim);
		}
	}
}

int main()
{
	for(int i = 2; i <= dim; i += 2)
	{
		for(int j = 0; j < i; j++)
		{
			minArray[j] = rand();
			maxArray[j] = rand();
		}
		for(int j = 0; j < i; j++)
		{
			minArray_C[j] = minArray[j];
			maxArray_C[j] = maxArray[j];
		}
		
		vecMinMaxRep32(minArray, maxArray, i);

		minMaxMas_C(minArray_C, maxArray_C, i);

		if( hashRep32((long long *)minArray, i) != hashRep32((long long *)minArray_C, i) || (hashRep32((long long *)maxArray, i) != hashRep32((long long *)maxArray_C, i)) )
		{
			printf("\n*****************************************************************************************************");
			printf("\nVecMinMax_32s on some sizes working incorrectly\n");
			printf("Array size: %d\n\n", i);
			return -1;
		}
	}

	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nVecMinMax_32s test passed\n\n");

	return 0;
}

