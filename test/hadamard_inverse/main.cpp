#include "stdio.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size_had = 128;
__attribute__((section(".data.imu0"))) long long H2[size_had*(size_had/32)];
__attribute__((section(".data.imu0"))) long long H2_sort[size_had*(size_had/32)];
__attribute__((section(".data.imu3"))) long long A_had[size_had*(size_had/2)];
__attribute__((section(".data.imu1"))) long long temp_had[size_had*(size_had/2)];
__attribute__((section(".data.imu2"))) long long A_had_result[size_had*(size_had/2)];

int main()
{
	A_had[0]=0x000000ff000000ff;
	for (int i = 1; i < size_had*(size_had/2); i++) A_had[i] = ((A_had[i-1]<<61)>>60) + i%16;

	int hash1 = 0;
	int hash2 = 0;
	int return_code;

	for (int i = 32; i <= size_had; i<<=1) {
		hash1 ^= nmppsHash64u((long long *) A_had, i*i/2);
	}
	for (int i = 32; i <= size_had; i<<=1) {
		nmppsHadamardInit((nm2s*) H2, i);
		nmppsHadamardInitSort((nm2s*) H2, (nm2s*) H2_sort, i);
		nmppsHadamard((nm32s*) A_had, (nm32s*) A_had_result, (nm2s*) H2_sort, (nm32s*) temp_had, i);
		nmppsHadamardInverse((nm32s*) A_had_result, (nm32s*) A_had, (nm2s*) H2_sort, (nm32s*) temp_had, i);
		hash2 ^= nmppsHash64u((long long *) A_had, i*i/2);
	}

	return_code = hash1^hash2;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}