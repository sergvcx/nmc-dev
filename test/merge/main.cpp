#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size = 1024;
__attribute__((section(".data.imu0"))) long long array[size];
__attribute__((section(".data.imu1"))) long long result[size];

int main() {
	array[0] = 0x8000000000000000;
	for (int i = 1; i < size; i++)
	{
		array[i] = (array[i-1]<<4) + i;
	}

	int hash = 0;

	for (int i = 8; i <= size*8; i+=8) {
		nmppsAbs2_8s((nm8s*) array, (nm8s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/8);
	}

	for (int i = 4; i <= size*4; i+=4) {
		nmppsAbs2_16s((nm16s*) array, (nm16s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/4);
	}

	for (int i = 2; i <= size*2; i+=2) {
		nmppsAbs2_32s((nm32s*) array, (nm32s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i/2);
	}

	for (int i = 1; i <= size; i++) {
		nmppsAbs2_64s((nm64s*) array, (nm64s*) result, i);
		hash ^= nmppsHash64u((long long *) result, i);
	}

	int return_code = hash^0xd4b7b27f;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
} 