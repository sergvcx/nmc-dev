#include "string.h"

#include "./image64.cpp"

const int iDim = 128;
int interpolated_image[iDim*iDim];

int main(int argc, char const *argv[]) {
	
	memset(interpolated_image, 0, iDim*iDim);

	for (int i = 0; i < 64*64; i++) {
		interpolated_image[i*2] = image64[i];
	}

	return 0;
}
