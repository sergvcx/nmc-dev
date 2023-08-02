extern "C" void nmppmTranspose_32s(const nm32s* srcMatrix, nm32s* resultMatrix, int height, int width) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			resultMatrix[i * height + j] = srcMatrix[j * width + i];
		}
	}
}

extern "C" void nmppmTranspose_16s(const nm16s* srcMatrix, nm16s* resultMatrix, int height, int width) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			resultMatrix[i * height + j] = srcMatrix[j * width + i];
		}
	}
}