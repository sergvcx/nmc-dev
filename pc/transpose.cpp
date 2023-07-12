extern "C" void nmppsTranspose(int* matrica, int* result, int height, int width) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			result[i * height + j] = matrica[j * width + i];
		}
	}
}