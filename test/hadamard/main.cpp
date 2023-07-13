#include "stdlib.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

void fill_array( long long * a, int size) {
	srand((unsigned) 23);
	for (int i = 0; i < size*size/2; i++) {
		a[i] = ((long long)rand()<<32) | (rand());
	}
}

const int size_had = 128;
__attribute__((section(".data.imu0"))) long long H2[size_had*(size_had/32)];
__attribute__((section(".data.imu0"))) long long H2_sort[size_had*(size_had/32)];
__attribute__((section(".data.imu3"))) long long A_had[size_had*(size_had/2)];
__attribute__((section(".data.imu1"))) long long temp_had[size_had*(size_had/2)];
__attribute__((section(".data.imu2"))) long long A_had_result[size_had*(size_had/2)];

int main()
{
	fill_array(A_had, size_had);

	int hash=0;

	for (int i = 32; i <= size_had; i<<=1) {
		nmppsHadamardInit((nm2s*) H2, i);
		nmppsHadamardInitSort((nm2s*) H2, (nm2s*) H2_sort, i);
		nmppsHadamard((nm32s*) A_had, (nm32s*) A_had_result, (nm2s*) H2_sort, (nm32s*) temp_had, i);
		hash ^= nmppsHash64u((long long *) A_had_result, i*i/2);
	}

	return hash ^ 0x7ee68ca5;
}