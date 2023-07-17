#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size = 1024;
__attribute__((section(".data.imu0"))) long long arr1[size];
__attribute__((section(".data.imu2"))) long long arr2[size];
__attribute__((section(".data.imu1"))) long long res_min[size];
__attribute__((section(".data.imu3"))) long long res_max[size];

int main() {
	// srand((unsigned) 36);
	// for (int i = 0; i < size; i++) {
	// 	arr1[i] = ((long long)rand()<<32) | (rand());
	// 	arr2[i] = ((long long)rand()<<32) | (rand());
	// }

	arr1[0] = 0x7483ab3b99990c0c;
	arr2[0] = 0x9988776655443322;
	for (int i = 1; i < size; i++) {
		arr1[i] = (arr1[i-1]<<4) + i;
		arr2[i] = (arr2[i-1]<<2) - i;
	}
	memset(res_min,0,size*2);
	memset(res_max,0,size*2);

	int hash = 0;

	for (int i = 8; i <= size*8; i+=8) {
		nmppsMinMax_8s((nm8s*) arr1, (nm8s*) arr2, (nm8s*) res_min, (nm8s*) res_max, i);
		hash ^= nmppsHash64u((long long *) res_min, i/8);
		hash ^= nmppsHash64u((long long *) res_max, i/8);
	}

	for (int i = 4; i <= size*4; i+=4) {
		nmppsMinMax_16s((nm16s*) arr1, (nm16s*) arr2, (nm16s*) res_min, (nm16s*) res_max, i);
		hash ^= nmppsHash64u((long long *) res_min, i/4);
		hash ^= nmppsHash64u((long long *) res_max, i/4);
	}

	for (int i = 2; i <= size*2; i+=2) {
		nmppsMinMax_32s((nm32s*) arr1, (nm32s*) arr2, (nm32s*) res_min, (nm32s*) res_max, i);
		hash ^= nmppsHash64u((long long *) res_min, i/2);
		hash ^= nmppsHash64u((long long *) res_max, i/2);
	}

	for (int i = 1; i <= size; i++) {
		nmppsMinMax_64s((nm64s*) arr1, (nm64s*) arr2, (nm64s*) res_min, (nm64s*) res_max, i);
		hash ^= nmppsHash64u((long long *) res_min, i);
		hash ^= nmppsHash64u((long long *) res_max, i);
	}

	int return_code = hash^0xe051e8a1;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
} 