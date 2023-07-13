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

	//transposeEvenSizes_32s(givenMatrix, resultMatrix, height, width, 0);
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
/*
//counts time per elem for transpose HxW with chosen algorithm
float transposeTimeCount(int* givenMatrix, int* resultMatrix, int height, int width)//, int mode)
{
	clock_t t1 = clock();
	clock_t t2 = clock();
	clock_t dt = t2 - t1;
	
	for(int i = 0; i < width*height; i++)
	{
		givenMatrix[i] = i; // / width + 1;
		resultMatrix[i] = 0;
	}

	t1 = clock();
	//transposeEvenSizes_32s(givenMatrix, resultMatrix, height, width, mode);
	transposeEvenSizes_32s(givenMatrix, resultMatrix, height, width);
	t2 = clock();
	return (float)(t2 - t1 - dt) / height / width;
}

//fills mtr with times per elem for different sizes
void testTransposeTime(int* givenMatrix, int* resultMatrix, float* time_mtr, int height, int width)//, int mode)
{
	int k = 0;

	for(int i = 2; i <= height; i += 2)
	{
		for(int j = 2; j <= width; j += 2)
		{
			time_mtr[k] = transposeTimeCount(givenMatrix, resultMatrix, i, j);//, mode);
			k++;
		}
	}
}

//---------------------------------Transpose-algorithm-time-test-in-letters--------------------
//fills time_test_result_mtr with letters of better algorithm for certain size
void formTimeTestResult(char* resultMatrixInChar, float* matrixByColumns, float* matrixByLines, int height, int width)
{
	for(int i = 0; i < height * width / 4; i++)
	{
		if(matrixByColumns[i] < matrixByLines[i])
			resultMatrixInChar[i] = 'C';
		else
			resultMatrixInChar[i] = 'L';
	}
}

//func for printing time_test_result_mtr in good-looking way
void printTimeTestResult(char* mtr, int height, int width)
{
	printf("Height/Width");
	for(int i = 2; i <= width; i += 2)
	{
		printf("%3d", i);
	}
	printf("\n");
	for(int i = 0; i < height / 2; i++)
	{
		printf("         %3d", (i + 1) * 2);
		for(int j = 0; j < width / 2; j++)
		{
			printf("%3c", mtr[i * (height / 2) + j]);
		}
		printf("\n");
	}
}

//---------------------------------Transpose-algorithm-time-test-in-ratio----------------------
//fills time_mtr_ratio with ratio of different algorithm times for certain size
void formTimeMtrRatio(float* timeRatioMtr, float* matrixByColumns, float* matrixByLines, int height, int width)
{
	for(int i = 0; i < height * width / 4; i++)
	{
		timeRatioMtr[i] = matrixByColumns[i] / matrixByLines[i];
	}
}
*/