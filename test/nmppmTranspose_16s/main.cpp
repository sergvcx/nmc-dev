#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/dumpx.h"
#include "../../include/mTranspose.h"
#include "../../include/hadamard.h"
#include "time.h"

const int width = 128;
const int height = 128;
__attribute__((section(".data.imu0"))) long long array[width * height / 4];
__attribute__((section(".data.imu1"))) long long result[width * height / 4];

int main()
{
	array[0] = 0x0004000300020001;
	for (int i = 1; i < width * height / 4; i++)
	{
		array[i] = array[i - 1] + 0x0004000400040004;
	};

	int hash_columns = 0;
	int hash_lines = 0;

	// for (int i = 4; i <= height; i += 4)
	// {
	// 	for (int j = 4; j <= width; j += 4)
	// 	{
	// 		long long t0c = static_cast<long long>(clock());
	// 		nmppmTranspose_16s((nm16s *)array, (nm16s *)result, i, j);
	// 		long long t1c = static_cast<long long>(clock());
	// 		hash_columns ^= nmppsHash64u(result, i * j / 4);

	// 		long long t0l = static_cast<long long>(clock());
	// 		nmppmTranspose_16s_Lines((nm16s *)array, (nm16s *)result, i, j);
	// 		long long t1l = static_cast<long long>(clock());
	// 		hash_lines ^= nmppsHash64u(result, i * j / 4);

	// 		long long time_lines =t1l - t0l;
	// 		long long time_cols =t1c - t0c;

	// 		if (time_cols>time_lines) printf("%d ", 0);
	// 		else if (time_lines>time_cols) printf("%d ", 1);
	// 		else printf("%d ", 2);

	// 		// dump_16u("%04x ", array, i, j, j * 2, 2);
	// 		// printf("\n");
	// 		// dump_16u("%04x ", result, j, i, i * 2, 2);
	// 		// printf("-----------------------------------\n");
	// 	}
	// 		printf("\n");
	// }

	long long t0c = static_cast<long long>(clock());
		nmppmTranspose_16s((nm16s *)array, (nm16s *)result, height, width);
		long long t1c = static_cast<long long>(clock());

		long long t0l = static_cast<long long>(clock());
		nmppmTranspose_16s_Lines((nm16s *)array, (nm16s *)result, height, width);
		long long t1l = static_cast<long long>(clock());

		printf("col speed = %f\n", ((double)t1c-(double)t0c)/(height*width));
		printf("lines speed = %f\n", ((double)t1l-(double)t0l)/(height*width));

	// nmppmTranspose_16s((nm16s *)array, (nm16s *)result, height, width);
	// dump_16u("%04x ", array, height, width, width * 2, 2);
	// printf("\n");
	// dump_16u("%04x ", result, width, height, height * 2, 2);
	// printf("-----------------------------------\n");

	// dump_64s("%0llx ", array, height, width / 4, width / 4, 2);
	// printf("\n");
	// dump_64s("%0llx ", result, width, height / 4, height / 4, 2);

	// int return_code = hash^0x779121de; // lines or columns 128, 128
	int return_code = hash_columns^hash_lines; // lines or columns 128, 128

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}