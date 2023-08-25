#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/dumpx.h"
#include "../../include/mTranspose.h"
#include "../../include/hadamard.h"
#include "time.h"

const int width = 1280;
const int height = 4;
__attribute__((section(".data.imu0"))) long long array[width * height / 4];
__attribute__((section(".data.imu1"))) long long result[width * height / 4];

int main()
{
	array[0] = 0x0004000300020001;
	for (int i = 1; i < width * height / 4; i++)
	{
		array[i] = array[i - 1] + 0x0004000400040004;
	};

	int hash = 0;

	for (int i = 4; i <= height; i += 4)
	{
		for (int j = 4; j <= width; j += 4)
		{
			// long long t0 = static_cast<long long>(clock());
			nmppmTranspose_16s((nm16s *)array, (nm16s *)result, i, j);
			// long long t1 = static_cast<long long>(clock());
			hash ^= nmppsHash64u(result, i * j / 4);

			// long long time = t1 - t0;
			// double speed = (double) time / (i*j);
			// printf("speed=%f\n", speed);

			// dump_16u("%04x ", array, i, j, j * 2, 2);
			// printf("\n");
			// dump_16u("%04x ", result, j, i, i * 2, 2);
			// printf("-----------------------------------\n");
		}
			//printf("\n");
	}

	// single call test
	// nmppmTranspose_16s((nm16s *)array, (nm16s *)result, height, width);
	// dump_16u("%04x ", array, height, width, width * 2, 2);
	// printf("\n");
	// dump_16u("%04x ", result, width, height, height * 2, 2);
	// printf("-----------------------------------\n");

	// different print format
	// dump_64s("%0llx ", array, height, width / 4, width / 4, 2);
	// printf("\n");
	// dump_64s("%0llx ", result, width, height / 4, height / 4, 2);
int return_code = hash;
	//int return_code = hash^0x779121de; // lines or columns 128, 128

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}