#include "stdlib.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

void fill_array( long long * a, int size) {
	srand((unsigned) 23);
	for (int i = 0; i < size*size/2; i++) {
		a[i] = ((long long)rand()<<32) | (rand());
	}
}

const int H = 120;
const int W = 2560;
__attribute__((section(".data.imu0"))) long long A2[H*(W/32)];
__attribute__((section(".data.imu1"))) long long A32[W];
__attribute__((section(".data.imu2"))) long long Res[H];


int main()
{
	srand((unsigned) 63);
	for (int i = 0; i < H*(W/32); i++) A2[i] = ((long long)rand()<<32) | (rand());
	for (int i = 0; i < W; i++) A32[i] = ((long long)rand()<<32) | (rand());

	int hash = 0;
	for (int h = 1; h <= H; h++) {
		for (int w = 32; w <= W; w+=32) {
			nmppsMulMM_2s32s_2col((nm2s*) A2, h, w, (nm32s*) A32, (nm32s*) Res, 2);
			hash ^= nmppsHash64u((long long *) Res, h);
		}
	}

	return hash^0x330C5AA6;
}