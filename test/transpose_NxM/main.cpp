#include "stdio.h"
#include <dumpx.h>
#include <maxtimer.h>
#include "../../include/general_header.h"

const int matrixHeight = 160;//128;
const int matrixWidth = 160;//128;
int givenMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu0")));
int resultMatrix[matrixHeight * matrixWidth] __attribute__ ((section (".data.imu1")));
int resultMatrix_C[matrixHeight * matrixWidth];

int main()
{	
	if(testTransposeSizes(givenMatrix, resultMatrix, resultMatrix_C, matrixHeight, matrixWidth))
	{
		printf("\n-----------------------------------------------------------------------------------------------------");
		printf("\nTranspose NxM on all reps working correctly\n\n");
	}
	else
	{
		printf("\n*****************************************************************************************************");
		printf("\nTranspose NxM on some sizes working incorrectly\n\n");
		return -1;
	}
	
	return 0;
}

