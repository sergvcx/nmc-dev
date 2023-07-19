#include "string.h"
#include <iostream>
#include <fstream>

const int dim = 64;
const int iDim = dim<<1;
int image64[dim*dim];
int interpolated_image[iDim*iDim];

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
	memset(interpolated_image, 0, iDim*iDim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
		interpolated_image[(i*iDim+j)*2] = image64[i*dim+j];
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
