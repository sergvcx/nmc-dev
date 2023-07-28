#include "stdio.h"
#include "../../include/general_header.h"
#include "../../include/mTranspose.h"

const int matrixHeight = 128;
const int matrixWidth = 128;
int givenMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu0")));
int resultMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu1")));
int resultMatrix_C[matrixHeight * matrixWidth];

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

	nmppsTranspose_32s(givenMatrix, resultMatrix, height, width);

	transpose_C(givenMatrix, resultMatrix_C, height, width);
	
	return hashRep32((long long *)resultMatrix, width*height) == hashRep32((long long *)resultMatrix_C, width*height);
}

int main()
{	
	for(int i = 2; i <= matrixHeight; i += 2)
	{
		for(int j = 2; j <= matrixWidth; j += 2)
		{
			if(!testTransposeCorrect(givenMatrix, resultMatrix, resultMatrix_C, i, j))
			{
				printf("\n*****************************************************************************************************");
				printf("\nTranspose NxM on some sizes working incorrectly\n\n");
				printf("\nHeight = %d, Width = %d", i, j);
				return -1;
			}
		}
	}
		
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nTranspose NxM on all reps working correctly\n\n");

	return 0;
}

