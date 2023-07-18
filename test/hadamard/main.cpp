#include "stdlib.h"
#include "stdio.h"
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
	A_had[0]=7;
	for (int i = 1; i < size_had*(size_had/2); i++) A_had[i] = (A_had[i-1]<<61)>>60;

	int hash=0;
	int return_code;

	for (int i = 32; i <= size_had; i<<=1) {
		nmppsHadamardInit((nm2s*) H2, i);
		return_code = nmppsHadamardInitSort((nm2s*) H2, (nm2s*) H2_sort, i);
		if (return_code!=0) return return_code;
		nmppsHadamard((nm32s*) A_had, (nm32s*) A_had_result, (nm2s*) H2_sort, (nm32s*) temp_had, i);
		hash ^= nmppsHash64u((long long *) A_had_result, i*i/2);
	}

	return_code = hash^0xfc800307;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}