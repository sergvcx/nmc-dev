#include "../include/general_header.h"
#include "stdio.h"
#include "stdlib.h"

void transpose_C(int* matrica, int* result, int height, int width)
{
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			result[i * height + j] = matrica[j * width + i];
		}
	}
}

bool testTransposeCorrect(int* givenMatrix, int* resultMatrix, int* resultMatrix_C, int height, int width)
{
	for(int i = 0; i < width*height; i++)
	{
		givenMatrix[i] = i; // / width + 1;
		resultMatrix[i] = 0;
		resultMatrix_C[i] = 0;
	}

	transposeEvenSizes_32s(givenMatrix, resultMatrix, height, width);

	transpose_C(givenMatrix, resultMatrix_C, height, width);
	
	return hashRep32(resultMatrix, width*height) == hashRep32(resultMatrix_C, width*height);
}

bool testTransposeSizes(int* givenMatrix, int* resultMatrix, int* resultMatrix_C, int height, int width)
{
	for(int i = 2; i <= height; i += 2)
	{
		for(int j = 2; j <= width; j += 2)
		{
			if(!testTransposeCorrect(givenMatrix, resultMatrix, resultMatrix_C, i, j))
			{
				printf("\nHeight = %d, Width = %d", i, j);
				return false;
			}
		}
	}
	return true;
}
