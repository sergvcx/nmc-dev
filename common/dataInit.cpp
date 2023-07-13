#include "stdio.h"
#include "stdlib.h"

void makeShortArray(int* a, int first, int last)
{
	int j = 0;
	for(int i = first; i < last; i += 2)
	{
		if(i < 0)
			*(a + j) = ((i + 2) << 16) + i;
		else
			*(a + j) = ((i + 1) << 16) + i;
		j++;
	}
}

void fillArray(int* a, int start, int end)
{
	int cnt = 0;
	for(int i = start; i < end; i++)
	{
		*(a + cnt) = i;
		cnt++;
	}
}

void randArray(int* a, int size)
{
	for(int i = 0; i < size; i++)
	{
		*(a + i) = rand() ^ (rand() << 31);
	}
}

void printIntegerLikeTwoShort(int a)
{
	printf("%d, %d\n", a >> 16, (a << 16) >> 16);
}

void initMatrices(int* initMatrix, int* nullResultMatrix, int* nullResultMatrix_C, int height, int width)
{
	for(int i = 0; i < width * height; i++)
	{
		initMatrix[i] = rand();
		nullResultMatrix[i] = 0;
		nullResultMatrix_C[i] = 0;
	}
}