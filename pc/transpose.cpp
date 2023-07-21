extern "C" void nmppsTranspose(const int* srcMatrix, int* resultMatrix, int height, int width) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			resultMatrix[i * height + j] = srcMatrix[j * width + i];
		}
	}
}