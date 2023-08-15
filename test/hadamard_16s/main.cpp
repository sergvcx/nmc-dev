#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"
#include "../../include/dumpx.h"

const int size_had = 128;
__attribute__((section(".data.imu0"))) long long H2[size_had * (size_had / 32)];
__attribute__((section(".data.imu0"))) long long H2_sort[size_had * (size_had / 32)];
__attribute__((section(".data.imu3"))) long long A_had[size_had * (size_had / 4)];
__attribute__((section(".data.imu1"))) long long temp_had[size_had * (size_had / 4)];
__attribute__((section(".data.imu2"))) long long A_had_result[size_had * (size_had / 4)];

int main()
{
	A_had[0] = 0x0001000200030004;
	for (int i = 1; i < size_had * (size_had / 4); i++)
	{
		A_had[i] = (i % 64) * 0x0001000200030004;
	}

	// dump_16u("%04x ", A_had, size_had, size_had, size_had * 2, 2);
	// printf("\n");

	int hash = 0;
	int return_code;

	for (int i = 32; i <= size_had; i <<= 1)
	{
		nmppsHadamardInit((nm2s *)H2, i);
		return_code = nmppsHadamardInitSort((nm2s *)H2, (nm2s *)H2_sort, i);
		if (return_code != 0)
			return return_code;
		nmppsHadamard_16s((nm16s *)A_had, (nm16s *)A_had_result, (nm2s *)H2_sort, (nm16s *)temp_had, i);
		hash ^= nmppsHash64u((long long *)A_had_result, i * i / 4);
	}

	// single call
	// nmppsHadamardInit((nm2s *)H2, size_had);
	// return_code = nmppsHadamardInitSort((nm2s *)H2, (nm2s *)H2_sort, size_had);
	// if (return_code != 0)
	// 	return return_code;
	// nmppsHadamard_16s((nm16s *)A_had, (nm16s *)A_had_result, (nm2s *)H2_sort, (nm16s *)temp_had, size_had);

	// printing src and dst
	// dump_16u("%04x ", A_had, size_had, size_had, size_had * 2, 2);
	// printf("\n");
	// dump_16u("%04x ", A_had_result, size_had, size_had, size_had * 2, 2);

	// printf("%x\n", nmppsHash64u((long long *)A_had_result, size_had * size_had / 4));

	return_code = hash^0x842fe23d;

	printf("return code = 0x%0x\n", return_code);

	return return_code;

	return 0;
}