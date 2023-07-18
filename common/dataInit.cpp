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

extern "C" void randArray(int* arrayPointer, int size)
{
	for(int i = 0; i < size; i++)
	{
		*(arrayPointer + i) = rand() ^ (rand() << 31);
	}
}