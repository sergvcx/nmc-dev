#include "stdio.h"
#include "stdlib.h"

extern "C" void makeShortArray(int* arrayPointer, int first, int last)
{
	int j = 0;
	for(int i = first; i < last; i += 2)
	{
		if(i < 0)
			*(arrayPointer + j) = ((i + 2) << 16) + i;
		else
			*(arrayPointer + j) = ((i + 1) << 16) + i;
		j++;
	}
}

void fillArray(int* arrayPointer, int start, int end)
{
	int cnt = 0;
	for(int i = start; i < end; i++)
	{
		*(arrayPointer + cnt) = i;
		cnt++;
	}
}

extern "C" void randArray(int* arrayPointer, int size)
{
	for(int i = 0; i < size; i++)
	{
		*(arrayPointer + i) = rand() ^ (rand() << 31);
	}
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