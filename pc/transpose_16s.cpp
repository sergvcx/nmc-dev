#include "stdlib.h"
#include "../include/nmtype.h"

// height must be a multiple of 4^n
// width must be a multiple of 4
int nmppmTranspose_16s(const int* srcMatrix, int* resultMatrix, int height, int width) {

	nm16s *temp;
	temp = (nm16s *)malloc(height*width*sizeof(short));

	for (int i = height; i > 1; i/=4) {
		if (i==height)
	}
	

	// // size of each array
	// int sizeOfEachArray = height/4;

	// // creating 4 arrays for merge
	// nm16s *array0, *array1, *array2, *array3;
	// array0 = (nm16s *)malloc(sizeOfEachArray*sizeof(short));
	// if (array0==NULL) return 1;
	// array1 = (nm16s *)malloc(sizeOfEachArray*sizeof(short));
	// if (array1==NULL) return 1;
	// array2 = (nm16s *)malloc(sizeOfEachArray*sizeof(short));
	// if (array2==NULL) return 1;
	// array3 = (nm16s *)malloc(sizeOfEachArray*sizeof(short));
	// if (array3==NULL) return 1;

	// // number of lines in each array
	// int numLinesEach = sizeOfEachArray/4;

	// // filling 4 arrays for merge
	// for (int i = 0; i < width; i++) {
	// 	for (int j = 0; i < sizeOfEachArray; i++) {
	// 		/* code */
	// 	}
		
	// 	array0[]
	// }

	// // merging 4 arrays (getting transposed array)

	return 0;
};