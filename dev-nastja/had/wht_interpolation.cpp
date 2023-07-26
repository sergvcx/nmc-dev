#include "string.h"
#include <iostream>
#include <fstream>
#include "../../include/hadamard.h"
#include "nmpp.h"

// const int dim = 64;
// const int iDim = dim<<1;

const int dim256 = 256;
int image256[dim256*dim256];

// int image64[dim*dim];
// int interpolated_image[iDim*iDim];
// int spectrum[iDim*iDim];
// int temp[iDim*iDim];
// int Y[iDim*iDim];

// long long H[iDim*(iDim/32)];
// long long H_seq[iDim*(iDim/32)];

// int filter[iDim*iDim];

// int interpolated_image64[dim*dim];
// int spectrum64[dim*dim];
// int temp64[dim*dim];
// int Y64[dim*dim];

// long long H64[dim*(dim/32)];
// long long H_seq64[dim*(dim/32)];

// int filter64[dim*dim];

int interpolated_image256[dim256*dim256];
int spectrum256[dim256*dim256];
int temp256[dim256*dim256];
int Y256[dim256*dim256];

long long H256[dim256*(dim256/32)];
long long H_seq256[dim256*(dim256/32)];

int filter256[dim256*dim256];

void getHadamardProduct_32s(nm32s *srcA, nm32s *srcB, nm32s *dst, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst[i*width+j] = srcA[i*width+j] * srcB[i*width+j];
		}
	}
};

void convertFinishedPixels(nm32s *srcA, nm32s *dst, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst[i*width+j] = srcA[i*width+j]*2;
		}
	}
};

int main(int argc, char const *argv[]) {

		// reading image data from txt to array
	std::ifstream src_image;
	src_image.open("./image_sources_txt/image256.txt");
	int pixel;
	for (int i = 0; src_image >> pixel; i++) {
		image256[i] = pixel;
	}
	src_image.close();

	// checkered pattern on source image
	for (int i = 0; i < dim256; i++) {
		for (int j = 0; j < dim256; j++) {
			if ((i%2+j%2)!=1) image256[i*dim256+j] = 0;
		}
	}

	// Hadamard transform
	nmppsHadamardInit(H256, dim256);
	nmppsHadamardInitSort(H256, H_seq256, dim256);
	nmppsHadamard(image256, spectrum256, H_seq256, temp256, dim256);

	// generating filter
	memset(filter256, 0, dim256*dim256*sizeof(int));
	for (int i = 0; i < dim256; i++) {
		for (int j = 0; j < dim256; j++) {
			// filter256[i*dim256+j] = 1;
			// if ((i+j<dim256-1)&&(i<=dim256/2)) filter256[i*dim256+j] = 1;
			// if ((i+j<dim256)&&(i>dim256/2)) filter256[i*dim256+j] = 1;
			if ((i+j<dim256)) filter256[i*dim256+j] = 2;
			if ((i+j==dim256)) filter256[i*dim256+j] = 1;
			// if ((i<dim256/2)||(j<dim256/2)) filter256[i*dim256+j] = 1;
		}
	}

	// applying filter
	// getHadamardProduct_32s(spectrum256, filter256, Y256, dim256, dim256);
	for (int i = 0; i < dim256; i++) {
		for (int j = 0; j < dim256; j++) {
			switch (filter256[i*dim256+j]) {
			case 0:
				Y256[i*dim256+j] = 0;
				break;
			case 1:
				Y256[i*dim256+j] = spectrum256[i*dim256+j]>>1;
				break;
			case 2:
				Y256[i*dim256+j] = spectrum256[i*dim256+j];
				break;
			default:
				break;
			}
		}
	}

	// inverse Hadamard transform
	nmppsHadamardInverse(Y256, spectrum256, H_seq256, temp256, dim256);

	// fixing colors
	convertFinishedPixels(spectrum256, interpolated_image256, dim256, dim256);

	// writing interpolated image data to txt
	std::ofstream result;
	result.open ("interpolated_image.txt");
	for (int i = 0; i < dim256; i++) {
		for (int j = 0; j < dim256; j++) {
			result << interpolated_image256[i*dim256+j];
			// result << filter256[i*dim256+j];
			// result << spectrum256[i*dim256+j];
			// result << temp256[i*dim256+j];
			// result << Y256[i*dim256+j];
			if (j!=dim256-1) result << " ";
		}
		if (i!=dim256-1) result << "\n";
	}
	result.close();


//*******************************************************************

	// // reading image data from txt to array
	// std::ifstream src_image;
	// src_image.open("./image_sources_txt/image64.txt");
	// int pixel;
	// for (int i = 0; src_image >> pixel; i++) {
	// 	image64[i] = pixel;
	// }
	// src_image.close();

	// // checkered pattern on source image
	// for (int i = 0; i < dim; i++) {
	// 	for (int j = 0; j < dim; j++) {
	// 		if ((i%2+j%2)!=1) image64[i*dim+j] = 0;
	// 	}
	// }

	// // Hadamard transform
	// nmppsHadamardInit(H64, dim);
	// nmppsHadamardInitSort(H64, H_seq64, dim);
	// nmppsHadamard(image64, spectrum64, H_seq64, temp64, dim);

	// // generating filter
	// memset(filter64, 0, dim*dim*sizeof(int));
	// for (int i = 0; i < dim; i++) {
	// 	for (int j = 0; j < dim; j++) {
	// 		// filter64[i*dim+j] = 1;
	// 		// if ((i+j<dim-1)&&(i<=dim/2)) filter64[i*dim+j] = 1;
	// 		// if ((i+j<dim)&&(i>dim/2)) filter64[i*dim+j] = 1;
	// 		if ((i<dim/2)||(j<dim/2)) filter64[i*dim+j] = 1;
	// 	}
	// }

	// // applying filter
	// getHadamardProduct_32s(spectrum64, filter64, Y64, dim, dim);

	// // inverse Hadamard transform
	// nmppsHadamardInverse(Y64, interpolated_image64, H_seq64, temp64, dim);

	// // writing interpolated image data to txt
	// std::ofstream result;
	// result.open ("interpolated_image.txt");
	// for (int i = 0; i < dim; i++) {
	// 	for (int j = 0; j < dim; j++) {
	// 		result << interpolated_image64[i*dim+j];
	// 		// result << filter64[i*dim+j];
	// 		// result << spectrum64[i*dim+j];
	// 		// result << temp64[i*dim+j];
	// 		// result << Y64[i*dim+j];
	// 		if (j!=dim-1) result << " ";
	// 	}
	// 	if (i!=dim-1) result << "\n";
	// }
	// result.close();

//*******************************************************************************************
	
	// // adding zeros to get interpolated image
	// memset(interpolated_image, 0, iDim*iDim*sizeof(int));
	// for (int i = 0; i < dim; i++) {
	// 	for (int j = 0; j < dim; j++) {
	// 		if ((i%2+j%2)==1) interpolated_image[i*iDim+j] = image64[i*dim+j];
	// 		/* checkered pattern
	// 		if (i%2==0) interpolated_image[i*iDim+j*2] = image64[i*dim+j];
	// 		else interpolated_image[i*iDim+j*2+1] = image64[i*dim+j];
	// 		*/
	// 	}
	// }

	// // Hadamard transform
	// nmppsHadamardInit(H, iDim);
	// nmppsHadamardInitSort(H, H_seq, iDim);
	// nmppsHadamard(interpolated_image, spectrum, H_seq, temp, iDim);

	// // generating filter
	// memset(filter, 0, iDim*iDim*sizeof(int));
	// for (int i = 0; i < iDim; i++) {
	// 	for (int j = 0; j < iDim; j++) {
	// 		filter[i*iDim+j] = 1;
	// 		// filter type 3
	// 		// if ((i+j<iDim-1)&&(i<=dim)) filter[i*iDim+j] = 1;
	// 		// if ((i+j<iDim)&&(i>dim)) filter[i*iDim+j] = 1;
	// 		/* my filter
	// 		if ((i+j<iDim-1)) filter[i*iDim+j] = 1;
	// 		*/
	// 		/* filter type 4
	// 		if ((i+j<iDim-1)) filter[i*iDim+j] = 2;
	// 		if ((i+j==iDim)) filter[i*iDim+j] = 1;
	// 		*/
	// 	}
	// }

	// // applying filter
	// getHadamardProduct_32s(spectrum, filter, Y, iDim, iDim);
	// /* filter type 4
	// for (int i = 0; i < iDim; i++) {
	// 	for (int j = 0; j < iDim; j++) {
	// 		switch (filter[i*iDim+j]) {
	// 		case 0:
	// 			Y[i*iDim+j] = 0;
	// 			break;
	// 		case 1:
	// 			Y[i*iDim+j] = spectrum[i*iDim+j]>>1;
	// 			break;
	// 		case 2:
	// 			Y[i*iDim+j] = spectrum[i*iDim+j];
	// 			break;
			
	// 		default:
	// 			break;
	// 		}
	// 	}
	// }
	// */

	// // inverse Hadamard transform
	// nmppsHadamardInverse(Y, interpolated_image, H_seq, temp, iDim);

	// /*
	// // computing spectrum
	// // X = (1/(2^k))*H*x
	// nmppsHadamardInit(H, iDim);
	// // dyadic sort
	// nmppsMulMM_2s32s(H, iDim, iDim, interpolated_image, temp, iDim);
	// int nShift = 0;
	// int nDim = iDim;
	// while (nDim >>= 1) nShift++;
	// nmppsRShiftC_32s(temp, nShift, spectrum, iDim*iDim);

	// // generating filter
	// memset(filter, 0, iDim*iDim*sizeof(int));
	// for (int i = 0; i < iDim; i++) {
	// 	for (int j = 0; j < iDim; j++) {
	// 		if (i+j<iDim) filter[i*iDim+j] = 1;
	// 	}
	// }

	// // convolution Y = spectrum*filter
	// nmppmMul_mm_32s32s( spectrum, iDim, iDim, filter, Y, iDim);

	// // reconstructed image
	// // y = 2 * (interpolated_image)^T * Y * interpolated_image
	// nmppsTranspose(interpolated_image, spectrum, iDim, iDim);
	// nmppmMul_mm_32s32s( spectrum, iDim, iDim, Y, temp, iDim);
	// nmppmMul_mm_32s32s( temp, iDim, iDim, interpolated_image, spectrum, iDim);
	// // nmppsLShiftC_32s(spectrum, 1, interpolated_image, iDim*iDim);
	// */

	// // writing interpolated image data to txt
	// std::ofstream result;
	// result.open ("interpolated_image.txt");
	// for (int i = 0; i < iDim; i++) {
	// 	for (int j = 0; j < iDim; j++) {
	// 		result << interpolated_image[i*iDim+j];
	// 		// result << filter[i*iDim+j];
	// 		// result << spectrum[i*iDim+j];
	// 		// result << temp[i*iDim+j];
	// 		// result << Y[i*iDim+j];
	// 		if (j!=iDim-1) result << " ";
	// 	}
	// 	if (i!=iDim-1) result << "\n";
	// }
	// result.close();

	return 0;
}
