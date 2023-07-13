#include "stdio.h"
#include "stdlib.h"
#include "../include/general_header.h"

int sumArray(int* source, int dim)
{
	int Sum = 0;
	for(int i = 0; i < dim; i++)
	{
		Sum += *(source + i);
	}
	return Sum;
}

bool tupoCompare(int* source, int* b, int dim)
{
	for(int i = 0; i < dim; i++)
	{
		if( *(source + i) != *(b + i) )
			return false;
	}	
	return true;
}

int hash_C(int* source, int dim)
{
	unsigned int Sum = 0;
	int mask = 1 << 31;
	for(int i = 0; i < dim; i++)
	{
		//Sum = ((Sum >> 31) | (Sum << 1)) ^ (*(source + i));
		Sum = (((Sum << 31) & mask) | ((Sum >> 1) & (mask - 1))) ^ (*(source + i));
	}
	return Sum;
}

int hashMimic(long* source, int dim)
{
	long Array[32];
	for(int i = 0; i < 32; i++)
	{
		Array[i] = 0;
	}
	int Sum = 0;
	long mask = long(1) << 63;
	int long_size = dim / 2;
	int pointer = 0;
	for(int i = 0; i < long_size / 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + (*(source + pointer));
			pointer++;
		}
	}
	for(int j = 0; j < 16; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 16];
	}
	for(int j = 0; j < 8; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 8];
	}
	for(int j = 0; j < 4; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 4];
	}
	for(int j = 0; j < 2; j++)
	{
		Array[j] = (((Array[j] << 63) & mask) | ((Array[j] >> 1) & (mask - 1))) + Array[j + 2];
	}
	Array[0] = (((Array[0] << 63) & mask) | ((Array[0] >> 1) & (mask - 1))) + Array[1];
	for(int i = 0; i < long_size % 32; i++)
	{
		Array[0] = (((Array[0] << 63) & mask) | ((Array[0] >> 1) & (mask - 1))) + (*(source + pointer));
		pointer++;
	}
	mask = long(1) << 32;
	Sum = ((Array[0] >> 32) & (mask - 1)) + (Array[0] & (mask - 1));
	return Sum;
}

int sumHash(int* sourcePointer, int* resultPointer)
{
	int Sum = 0;
	for(int i = 0; i < (1 << 13); i += 4)
	{
		for(int j = -32768; j < 32767; j += i)
		{
			if (i == 0)
				break;
			if (32768 - j < i)
				break;
			makeShortArray(sourcePointer, j, j + i);
			abs_16s(sourcePointer, resultPointer, i);
			Sum += hashRep32(resultPointer, i);
		}
	}
	return Sum;
}

void testHash(int* arrayPointer, int dim)
{
	int hashAsm;
	int hashCxx;
	long* p;
	//-----------------------------------TEST-FOR-RANDOM-NUMBER-----------
	for(int j = 0; j < 100; j++) //j — number of rand iterations
	{
		for(int i = 0; i < dim; i++)
		{
			arrayPointer[i] = rand() ^ (rand() << 31);
		}
		p = (long*)arrayPointer;
		hashCxx = hashMimic(p, dim);
		hashAsm = hashRep32(arrayPointer, dim);
		printf("Iteration %3d:", j);
		if(hashAsm == hashCxx)
			printf("\nEqual result\n");
		else
			printf("\nFunctions worked wrong\n");
		printf("Hash by asm: %d\nHash by C:   %d\n\n", hashAsm, hashCxx);
	}
}