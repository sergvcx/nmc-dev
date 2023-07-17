#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size_had = 256;
__attribute__((section(".data.imu0"))) long long H2[size_had*(size_had/32)];
__attribute__((section(".data.imu1"))) long long H2_sort[size_had*(size_had/32)];

int main() {
	int hash = 0;

	for (int i = 32; i <= size_had; i<<=1) {
		nmppsHadamardInit((nm2s*) H2, i);
		nmppsHadamardInitSort((nm2s*) H2,(nm2s*) H2_sort, i);
		hash ^= nmppsHash64u((long long *) H2_sort, i*i/32);
	}

	int return_code = hash;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
} 