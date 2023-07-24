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
int Y[iDim*iDim];

long long H[iDim*(iDim/32)];
long long H_seq[iDim*(iDim/32)];

int filter[iDim*iDim];

void getHadamardProduct_32s(nm32s *srcA, nm32s *srcB, nm32s *dst, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst[i*width+j] = srcA[i*width+j] * srcB[i*width+j];
		}
	}
};

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

	// Hadamard transform
	nmppsHadamardInit(H, iDim);
	nmppsHadamardInitSort(H, H_seq, iDim);
	nmppsHadamard(interpolated_image, spectrum, H_seq, temp, iDim);

	// generating filter
	memset(filter, 0, iDim*iDim*sizeof(int));
	for (int i = 0; i < iDim; i++) {
		for (int j = 0; j < iDim; j++) {
			if ((i+j<iDim-1)&&(i<=dim)) filter[i*iDim+j] = 1;
			if ((i+j<iDim)&&(i>dim)) filter[i*iDim+j] = 1;
		}
	}

	// applying filter
	getHadamardProduct_32s(spectrum, filter, Y, iDim, iDim);

	// inverse Hadamard transform
	nmppsHadamardInverse(Y, interpolated_image, H_seq, temp, iDim);

	/*
	// computing spectrum
	// X = (1/(2^k))*H*x
	nmppsHadamardInit(H, iDim);
	// dyadic sort
	nmppsMulMM_2s32s(H, iDim, iDim, interpolated_image, temp, iDim);
	int nShift = 0;
	int nDim = iDim;
	while (nDim >>= 1) nShift++;
	nmppsRShiftC_32s(temp, nShift, spectrum, iDim*iDim);

	// generating filter
	memset(filter, 0, iDim*iDim*sizeof(int));
	for (int i = 0; i < iDim; i++) {
		for (int j = 0; j < iDim; j++) {
			if (i+j<iDim) filter[i*iDim+j] = 1;
		}
	}

	// convolution Y = spectrum*filter
	nmppmMul_mm_32s32s( spectrum, iDim, iDim, filter, Y, iDim);

	// reconstructed image
	// y = 2 * (interpolated_image)^T * Y * interpolated_image
	nmppsTranspose(interpolated_image, spectrum, iDim, iDim);
	nmppmMul_mm_32s32s( spectrum, iDim, iDim, Y, temp, iDim);
	nmppmMul_mm_32s32s( temp, iDim, iDim, interpolated_image, spectrum, iDim);
	// nmppsLShiftC_32s(spectrum, 1, interpolated_image, iDim*iDim);
	*/

	// writing interpolated image data to txt
	std::ofstream result;
	result.open ("interpolated_image.txt");
	for (int i = 0; i < iDim; i++) {
		for (int j = 0; j < iDim; j++) {
			result << interpolated_image[i*iDim+j];
			// result << filter[i*iDim+j];
			// result << spectrum[i*iDim+j];
			// result << temp[i*iDim+j];
			// result << Y[i*iDim+j];
			if (j!=iDim-1) result << " ";
		}
		if (i!=iDim-1) result << "\n";
	}
	result.close();

	return 0;
}
