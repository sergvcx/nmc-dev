#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/dumpx.h"
#include "../../include/vReodering.h"
#include "../../include/hadamard.h"

const int srcSize = 128;
const int dstSize = srcSize*4;
__attribute__((section(".data.imu0"))) long long array0[srcSize/4];
__attribute__((section(".data.imu0"))) long long array1[srcSize/4];
__attribute__((section(".data.imu0"))) long long array2[srcSize/4];
__attribute__((section(".data.imu0"))) long long array3[srcSize/4];
__attribute__((section(".data.imu1"))) long long result[dstSize/4];

int main() {
	array0[0] = 0x0004000300020001;
	array1[0] = 0x0080007000600050;
	array2[0] = 0x0b0003000a000900;
	array3[0] = 0xf000e000d000c000;
	for(int i = 1; i < srcSize/4; i++) {
		array0[i] = array0[i-1]+0x0001000100010001;
		array1[i] = array1[i-1]+0x0001000100010001;
		array2[i] = array2[i-1]+0x0001000100010001;
		array3[i] = array3[i-1]+0x0001000100010001;
	};

	int hash = 0;

	for (int i = 4; i <= srcSize; i+=4) {
		nmppsMerge4_16s((nm16s*) array0, (nm16s*) array1, (nm16s*) array2, (nm16s*) array3, (nm16s*) result, i);
		hash ^= nmppsHash64u(result, i*16);
	dump_64s("%llx ", array0, srcSize/4, 1, 1, 2);
	dump_64s("%llx ", array1, srcSize/4, 1, 1, 2);
	dump_64s("%llx ", array2, srcSize/4, 1, 1, 2);
	dump_64s("%llx ", array3, srcSize/4, 1, 1, 2);
	dump_64s("%llx ", result, dstSize/16, 4, 4, 2);
	}
	
	int return_code = hash;

	printf("return code = 0x%0x\n", return_code);
	
	return return_code;
} 