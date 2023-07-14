#include "time.h"
#include "stdio.h"
#include "../../include/general_header.h"
#include <maxtimer.h>

const int dim = 4096;
int minArray[dim];
int maxArray[dim];
int minArray_C[dim];
int maxArray_C[dim];

int main()
{
	for(int i = 0; i <= dim; i += 2)
	{
		randArray(minArray, i);
		randArray(maxArray, i);
		for(int j = 0; j < i; j++)
		{
			minArray_C[j] = minArray[j];
			maxArray_C[j] = maxArray[j];
		}

		minMaxMas_C(minArray_C, maxArray_C, i);

		vecMinMaxRep32(minArray, maxArray, i);

		if( hashRep32(minArray, i) != hashRep32(minArray_C, i) || (hashRep32(maxArray, i) != hashRep32(maxArray_C, i)) )
			return -1;
	}

	return 0;
}

