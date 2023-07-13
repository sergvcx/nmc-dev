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
const int W1 = 128;
const int W2 = 120;
__attribute__((section(".data.imu0"))) long long A2[H*(W1/32)];
__attribute__((section(".data.imu1"))) long long A32[W1*(W2/2)];
__attribute__((section(".data.imu2"))) long long Res[H*(W2/2)];


int main()
{
	srand((unsigned) 63);
	for (int i = 0; i < H*(W1/32); i++) A2[i] = ((long long)rand()<<32) | (rand());
	for (int i = 0; i < W1*(W2/2); i++) A32[i] = ((long long)rand()<<32) | (rand());

	int hash = 0;
	for (int h = 1; h <= H; h++) {
		for (int w1 = 32; w1 <= W1; w1+=32) {
			for (int w2 = 2; w2 <= W2; w2+=2) {
				nmppsMulMM_2s32s((nm2s*) A2, h, w1, (nm32s*) A32, (nm32s*) Res, w2);
				hash ^= nmppsHash64u((long long *) Res, h*(w2/2));
			}
		}
	}

	return hash^0x32B23AAF;
}