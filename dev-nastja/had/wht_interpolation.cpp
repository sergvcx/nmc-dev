#include "string.h"
#include <iostream>
#include <fstream>

#include "./image64.cpp"

const int iDim = 128;
int interpolated_image[iDim*iDim];

int main(int argc, char const *argv[]) {
	
	memset(interpolated_image, 0, iDim*iDim);

	for (int i = 0; i < iDim/2; i++) {
		for (int j = 0; j < iDim/2; j++) {
		interpolated_image[(i*iDim+j)*2] = image64[i*iDim/2+j];
		}
	}

	std::ofstream myfile;
	myfile.open ("interpolated_image.txt");
	// myfile << "[";
	for (int i = 0; i < iDim; i++) {
		// myfile << "[";
		for (int j = 0; j < iDim; j++) {
			myfile << interpolated_image[i*iDim+j];
			// if (j==iDim-1) myfile << "],";
			// else myfile << ",";
			if (j!=iDim-1) myfile << " ";
		}
		if (i!=iDim-1) myfile << "\n";
	}
	// myfile << "]";
	myfile.close();

	return 0;
}
