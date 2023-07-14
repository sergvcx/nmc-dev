#include "stdlib.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size = 1024;
__attribute__((section(".data.imu0"))) long long arr1[size];
__attribute__((section(".data.imu2"))) long long arr2[size];
__attribute__((section(".data.imu1"))) long long res_min[size];
__attribute__((section(".data.imu3"))) long long res_max[size];

int main() {
	srand((unsigned) 36);
	for (int i = 0; i < size; i++) {
		arr1[i] = ((long long)rand()<<32) | (rand());
		arr2[i] = ((long long)rand()<<32) | (rand());
	}

	int hash1 = 0;
	int hash2 = 0;

	for (int i = 8; i <= size; i+=8) {
		nmppsMinMax_8s((nm8s*) arr1, (nm8s*) arr2, (nm8s*) res_min, (nm8s*) res_max, i);
		hash1 ^= nmppsHash64u((long long *) res_min, i/8);
		hash2 ^= nmppsHash64u((long long *) res_max, i/8);
	}

	for (int i = 4; i <= size; i+=4) {
		nmppsMinMax_16s((nm16s*) arr1, (nm16s*) arr2, (nm16s*) res_min, (nm16s*) res_max, i);
		hash1 ^= nmppsHash64u((long long *) res_min, i/4);
		hash2 ^= nmppsHash64u((long long *) res_max, i/4);
	}

	for (int i = 2; i <= size; i+=2) {
		nmppsMinMax_32s((nm32s*) arr1, (nm32s*) arr2, (nm32s*) res_min, (nm32s*) res_max, i);
		hash1 ^= nmppsHash64u((long long *) res_min, i/2);
		hash2 ^= nmppsHash64u((long long *) res_max, i/2);
	}

	for (int i = 1; i <= size; i++) {
		nmppsMinMax_64s((nm64s*) arr1, (nm64s*) arr2, (nm64s*) res_min, (nm64s*) res_max, i);
		hash1 ^= nmppsHash64u((long long *) res_min, i);
		hash2 ^= nmppsHash64u((long long *) res_max, i);
	}

	return hash1^hash2^0x849E226F;
} 