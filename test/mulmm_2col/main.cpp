#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int H = 120;
const int W = 2560;
__attribute__((section(".data.imu0"))) long long A2[H*(W/32)];
__attribute__((section(".data.imu1"))) long long A32[W];
__attribute__((section(".data.imu2"))) long long Res[H];


int main()
{
	A2[0]=5; A32[0]=8;
	for (int i = 1; i < H*(W/32); i++) A2[i] = (A2[i-1]<<2)-30;
	for (int i = 1; i < W; i++) A32[i] = (A2[i-1]<<6)-100;

	int hash = 0;
	for (int h = 1; h <= H; h++) {
		for (int w = 32; w <= W; w+=32) {
			nmppsMulMM_2s32s_2col((nm2s*) A2, h, w, (nm32s*) A32, (nm32s*) Res, 2);
			hash ^= nmppsHash64u((long long *) Res, h);
		}
	}

	int return_code = hash^0x5e134e5e;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}