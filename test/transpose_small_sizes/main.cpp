#include "stdio.h"
#include "stdlib.h"
#include <dumpx.h>
#include <maxtimer.h>
#include "../../include/general_header.h"

const int matrixHeight = 64;
const int matrixWidth = 64;
int givenMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu0")));
int resultMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu1")));
int resultMatrix_C[matrixHeight * matrixWidth];

int main()
{	
	int side = 2;
	initMatrices(givenMatrix, resultMatrix, resultMatrix_C, side, side);
	
	transpose_C(givenMatrix, resultMatrix_C, side, side);

	transpose_2x2_32s(givenMatrix, resultMatrix);
	if( !(hashRep32(resultMatrix, side * side) == hashRep32(resultMatrix_C, side * side)) )
	{
		printf("\n*****************************************************************************************************");
		printf("\nMatrix 2x2 transposed incorrectly\n\n");
		return -1;
	}
	
	side = 3;

	initMatrices(givenMatrix, resultMatrix, resultMatrix_C, side, side);
	
	transpose_C(givenMatrix, resultMatrix_C, side, side);

	transpose_3x3_32s(givenMatrix, resultMatrix);
	if( !(hashRep32(resultMatrix, side * side) == hashRep32(resultMatrix_C, side * side)) )
	{
		printf("\n*****************************************************************************************************");
		printf("\nMatrix 3x3 transposed incorrectly\n\n");
		return -1;
	}
	
	side = 4;

	initMatrices(givenMatrix, resultMatrix, resultMatrix_C, side, side);
	
	transpose_C(givenMatrix, resultMatrix_C, side, side);

	transpose_4x4_32s(givenMatrix, resultMatrix);
	if( !(hashRep32(resultMatrix, side * side) == hashRep32(resultMatrix_C, side * side)) )
	{
		printf("\n*****************************************************************************************************");
		printf("\nMatrix 4x4 transposed incorrectly\n\n");
		return -1;
	}

	initMatrices(givenMatrix, resultMatrix, resultMatrix_C, matrixHeight, matrixWidth);
	
	transpose_C(givenMatrix, resultMatrix_C, matrixHeight, matrixWidth);

	transpose_64x64_32s(givenMatrix, resultMatrix);
	if( !(hashRep32(resultMatrix, matrixHeight * matrixWidth) == hashRep32(resultMatrix_C, matrixHeight * matrixWidth)) )
	{
		printf("\n*****************************************************************************************************");
		printf("\nMatrix 64x64 transposed incorrectly\n\n");
		return -1;
	}
	
	printf("\n-----------------------------------------------------------------------------------------------------");
	printf("\nMatrix transpose test on small sizes passed\n\n");

	return 0;
}

