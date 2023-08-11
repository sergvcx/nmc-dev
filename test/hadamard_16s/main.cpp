#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"
#include "../../include/dumpx.h"

const int size_had = 32;
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
		if (i < (size_had / 4))
		{
			A_had[i] = A_had[i-1] + 0x0004000400040004;
			continue;
		}
		A_had[i] = A_had[i - size_had/4];
	}

	// int hash = 0;
	// int return_code;

	// for (int i = 32; i <= size_had; i <<= 1)
	// {
	// 	nmppsHadamardInit((nm2s *)H2, i);
	// 	return_code = nmppsHadamardInitSort((nm2s *)H2, (nm2s *)H2_sort, i);
	// 	if (return_code != 0)
	// 		return return_code;
	// 	nmppsHadamard_16s((nm16s *)A_had, (nm16s *)A_had_result, (nm2s *)H2_sort, (nm16s *)temp_had, i);
	// 	hash ^= nmppsHash64u((long long *)A_had_result, i * i / 2);
	// }

	// return_code = hash;

	// printf("return code = 0x%0x\n", return_code);

	// return return_code;

	for (int i = 0; i < size_had * (size_had / 32); i++)
		H2[i] = 0x5555555555555555;

	nmppsMulMM_2s16s((nm2s *)H2, size_had, size_had, (nm16s *)A_had, (nm16s *)A_had_result, size_had);

	dump_16u("%04x ", A_had, size_had, size_had, size_had * 2, 2);
	printf("\n");
	dump_16u("%04x ", A_had_result, size_had, size_had, size_had * 2, 2);

	printf("%x\n", nmppsHash64u((long long *)A_had_result, size_had * size_had / 4));

	return 0;
}