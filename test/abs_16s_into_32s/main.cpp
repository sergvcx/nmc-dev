#include "stdio.h"
#include "stdlib.h"
#include "../../include/general_header.h"

const int dim = 8192;
int sourceArray[dim / 2];
int absResultArray[dim];
int absResultArray_C[dim];

int main()
{
	int hash_asm;
	int hash_cxx;
	for(int i = -32768; i < 32767; i += dim)
	{
		makeShortArray(sourceArray, i, i + dim);
		abs_16s(sourceArray, absResultArray, dim);
		abs_16s_C(sourceArray, absResultArray_C, dim);
		hash_cxx = hashRep32(absResultArray_C, dim);
		hash_asm = hashRep32(absResultArray, dim);
		if(hash_asm != hash_cxx)
		{
			printf("\n*****************************************************************************************************");
			printf("\nAbs on some values working incorrectly\n\n");
			return -1;
		}
	}
	
	randArray(sourceArray, dim / 2);
	for(int i = 0; i < dim; i += 4)
	{
		abs_16s(sourceArray, absResultArray, i);
		abs_16s_C(sourceArray, absResultArray_C, i);
		if(hashRep32(absResultArray, i) != hashRep32(absResultArray_C, i))
		{
			printf("\n*****************************************************************************************************");
			printf("\nAbs on some sizes working incorrectly\n\n");
			return -1;
		}
	}
	
	//x86
	/*
	int Sum = 0;
	for(int i = 0; i < (1 << 13); i += 4)
	{
		for (int j = -32768; j < 32767; j += i)
		{
			if (i == 0)
				break;
			if (32768 - j < i)
				break;
			makeShortArray(sourceArray, j, j + i);
			abs_16s_C_(sourceArray, absResultArray, i);
			Sum += hash_C((long long*)absResultArray, i);
		}
	}	
	*/

	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nAbs test passed\n\n");

	return 0;
}
