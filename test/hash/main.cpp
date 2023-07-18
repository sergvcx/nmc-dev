#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "../../include/general_header.h"

const int dim = 4096;
int Array[dim];

int main()
{
	int hashSum1 = 0;
	int hashSum2 = 0;

	for(int j = 0; j < 10; ++j)
	{
		randArray(Array, dim);

		for(int i = 1; i < dim; ++i)
		{
			hashSum1 ^= hashRep32((long long*)Array, i);
			hashSum2 ^= hashRep32((long long*)Array, i + 1);
			if(hashSum1 == hashSum2)
			{
				printf("\n*****************************************************************************************************");
				printf("\nHash on some numbers working incorrectly\n\n");
				printf("Hash on size %d: %d\nHash on size %d: %d\n\n", i, hashSum1, i + 1, hashSum2);
				return -1;
			}
		}
	}
	
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nHash test passed\n\n");

	return 0;
}

