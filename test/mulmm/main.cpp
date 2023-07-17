#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int H = 80;
const int W1 = 128;
const int W2 = 20;
__attribute__((section(".data.imu0"))) long long A2[H*(W1/32)];
__attribute__((section(".data.imu1"))) long long A32[W1*(W2/2)];
__attribute__((section(".data.imu2"))) long long Res[H*(W2/2)];


int main()
{
	A2[0]=5; A32[0]=8;
	for (int i = 1; i < H*(W1/32); i++) A2[i] = (A2[i-1]<<62)>>61;
	for (int i = 1; i < W1*(W2/2); i++) A32[i] = (A2[i-1]<<62)>>61;

	int hash = 0;
	for (int h = 1; h <= H; h++) {
		for (int w1 = 32; w1 <= W1; w1+=32) {
			for (int w2 = 2; w2 <= W2; w2+=2) {
				nmppsMulMM_2s32s((nm2s*) A2, h, w1, (nm32s*) A32, (nm32s*) Res, w2);
				hash ^= nmppsHash64u((long long *) Res, h*(w2/2));
			}
		}
	}

	int return_code = hash^0x33a06f6b;

	printf("return code = 0x%0x\n", return_code);

	return return_code;
}