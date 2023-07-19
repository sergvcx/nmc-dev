#include "string.h"
#include <iostream>
#include <fstream>
#include "../../include/hadamard.h"
#include "nmpp.h"

const int dim = 64;
const int iDim = dim<<1;

int image64[dim*dim];
int interpolated_image[iDim*iDim];
int spectrum[iDim*iDim];
int temp[iDim*iDim];

long long H[iDim*(iDim/32)];

int filter[iDim*iDim];

int main(int argc, char const *argv[]) {

	// reading image data from txt to array
	std::ifstream src_image;
	src_image.open("./image_sources_txt/image64.txt");
	int pixel;
	for (int i = 0; src_image >> pixel; i++) {
		image64[i] = pixel;
	}
	src_image.close();
	
	// adding zeros to get interpolated image
	memset(interpolated_image, 0, iDim*iDim*sizeof(int));
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
		interpolated_image[(i*iDim+j)*2] = image64[i*dim+j];
		}
	}

	// computing spectrum
	// X = (1/(2^k))*H*x
	nmppsHadamardInit(H, iDim);
	nmppsMulMM_2s32s(H, iDim, iDim, interpolated_image, temp, iDim);
	int nShift = 0;
	int nDim = iDim;
	while (nDim >>= 1) nShift++;
	nmppsRShiftC_32s(temp, nShift, spectrum, iDim*iDim);

	// generating filter
	memset(filter, 0, iDim*iDim*sizeof(int));
	for (int i = 0; i < iDim; i++) {
		for (int j = 0; j < iDim; j++) {
			if (i<=j) filter[i*iDim+j] = 1;
		}
	}

	// writing interpolated image data to txt
	std::ofstream result;
	result.open ("interpolated_image.txt");
	for (int i = 0; i < iDim; i++) {
		for (int j = 0; j < iDim; j++) {
			result << interpolated_image[i*iDim+j];
			if (j!=iDim-1) result << " ";
		}
		if (i!=iDim-1) result << "\n";
	}
	result.close();

	return 0;
}
