#include "stdlib.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size = 1024;
__attribute__((section(".data.imu0"))) long long array[size];
__attribute__((section(".data.imu1"))) long long result[size];

int main() {
	srand((unsigned) 95);
	for (int i = 0; i < size; i++) {
		array[i] = ((long long)rand()<<32) | (rand());
	}

	int hash = 0;

	for (int i = 8; i <= size; i+=8) {
		nmppsAbs2_8s((nm8s*) array, (nm8s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/8);
	}

	for (int i = 4; i <= size; i+=4) {
		nmppsAbs2_16s((nm16s*) array, (nm16s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/4);
	}

	for (int i = 2; i <= size; i+=2) {
		nmppsAbs2_32s((nm32s*) array, (nm32s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/2);
	}

	for (int i = 1; i <= size; i++) {
		nmppsAbs2_64s((nm64s*) array, (nm64s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i);
	}

	return hash^0xE3357C08;
} 