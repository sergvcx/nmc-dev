#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "../../include/general_header.h"
#include <maxtimer.h>

const int dim = 4096;
int Array[dim];

int main()
{
	int hash_asm;
	int hash_cxx;
	for(int j = 0; j < 1000; j++) //j — number of rand iterations
	{
		for(int i = 0; i < dim; i++)
		{
			Array[i] = rand() ^ (rand() << 31);
		}
		hash_cxx = hash_C((long*)Array, dim);
		hash_asm = hashRep32(Array, dim);
		if(hash_asm != hash_cxx)
		{
			printf("\n*****************************************************************************************************");
			printf("\nHash on some numbers working incorrectly\n\n");
			printf("Hash by asm: %d\nHash by C:   %d\n\n", hash_asm, hash_cxx);
			return -1;
		}
	}

	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nHash test passed\n\n");

	return 0;
}

