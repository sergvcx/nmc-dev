#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/dumpx.h"
#include "../../include/mTranspose.h"
#include "../../include/hadamard.h"

const int width = 32;
const int height = 4;
__attribute__((section(".data.imu0"))) long long array[width * height / 4];
__attribute__((section(".data.imu1"))) long long result[width * height / 4];

int main()
{
	array[0] = 0xc000090000500001;
	for (int i = 1; i < width * height / 4; i++)
	{
		array[i] = array[i - 1] + 0x0001000100010001;
	};

	int hash = 0;

	// for (int i = 4; i <= height; i += 4)
	// {
	// 	for (int j = 4; j <= width; j += 4)
	// 	{
	// 		nmppmTranspose_16s((nm16s *)array, (nm16s *)result, i, j);
	// 		hash ^= nmppsHash64u(result, i * j / 4);
	// 	}
	// }
	nmppmTranspose_16s((nm16s *)array, (nm16s *)result, height, width);

	dump_16u("%04x ", array, height, width, width * 2, 2);
	printf("\n");
	dump_16u("%04x ", result, width, height, height * 2, 2);

	int return_code = hash;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}