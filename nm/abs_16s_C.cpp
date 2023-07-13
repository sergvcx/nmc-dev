#include "../include/general_header.h"
#include "stdio.h"

void abs_16s_C(int* sourceArray16s, int* resultArray32s, int dim)
{
	int j = 0;
	for(int i = 0; i < dim; i += 2)
	{
		*(resultArray32s + i) = (((*(sourceArray16s + j)) << 16) >> 16) * (((((*(sourceArray16s + j)) << 16) >> 16) >> 15) | 1);
		*(resultArray32s + i + 1) = ((*(sourceArray16s + j)) >> 16) * ((((*(sourceArray16s + j)) >> 16) >> 15) | 1);
		j++;
	}
}

void compareAbs(int* A, int* B, int* C, long* D)
{
	int hashAsm;
	int hashCxx;
	int dim = 4096;
	for(int i = -32768; i < 32767; i += dim)
	{
		makeShortArray(A, i, i + dim);
		abs_16s(A, B, dim);
		abs_16s_C(A, C, dim);
		//---------------------------------break---hash----
		/*
		if( ((i > -10000) && (i < -6000)) || ((i > 17000) && (i < 21000)) )
		{
		int temp = B[4090];
		B[4090] = B[4080];
		B[4080] = temp;
		temp = B[5];
		B[5] = B[40];
		B[40] = temp;
		temp = B[456];
		B[456] = B[3271];
		B[3271] = temp;
		}
		*/
		//longFromTwoInt(B, D, dim);
		hashCxx = hashMimic((long*)B, dim);
		hashAsm = hashRep32(C, dim);
		if(hashAsm == hashCxx)
			if(i > 0)
				printf("\nCorrect from %6d to %6d\n", i, i + dim - 1);
			else
				printf("\nCorrect from %6d to %6d\n", i, i + dim);
		else
			if(i > 0)
				printf("\nWrong from %6d to %6d\n", i, i + dim - 1);
			else
				printf("\nWrong from %6d to %6d\n", i, i + dim);
		printf("Hash by asm: %d\nHash by C:   %d\n", hashAsm, hashCxx);
	}
}

bool testAbsSizes(int* sourceArray16s, int* resultArray32s, int* resultArray32s_C, int dim)
{
	randArray(sourceArray16s, (1 << 12));
	for(int i = 0; i < (1 << 13); i += 4)
	{
		for(int j = 0; j < dim; j++)
		{
			resultArray32s[j] = 0;
			resultArray32s_C[j] = 0;
		}
		abs_16s(sourceArray16s, resultArray32s, i);
		abs_16s_C(sourceArray16s, resultArray32s_C, i);
		if(hashRep32(resultArray32s, i) != hashRep32(resultArray32s_C, i))
			return false;
	}
	return true;
}
