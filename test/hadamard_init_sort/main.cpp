#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size_had = 512;
__attribute__((section(".data.imu2"))) long long H2[size_had*(size_had/32)];
__attribute__((section(".data.imu3"))) long long H2_sort[size_had*(size_had/32)];

int main() {
	int hash = 0;
	int return_code;

	for (int i = 32; i <= size_had; i<<=1) {
		nmppsHadamardInit((nm2s*) H2, i);
		return_code = nmppsHadamardInitSort((nm2s*) H2,(nm2s*) H2_sort, i);
		if (return_code!=0) return return_code;
		hash ^= nmppsHash64u((long long *) H2_sort, i*i/32);
	}

	return_code = hash^0xf32dfdb8;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
} 