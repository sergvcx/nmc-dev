#include "../include/nmtype.h"

int get_2s(long long * p, int index){
	p += index/32;
	index %= 32;
	return (int) ((*p<<(62-2*index))>>62);
};

extern "C" void nmppsMulMM_2s32s_2col(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2) {
	long long * a = (long long*) A;
	int * b = (int*) B;
	int * c = (int*) C;
	int temp0, temp1;
	for (int i = 0; i < H; i++) {
		temp0 = 0;
		temp1 = 0;
		long long * p = a + i*(W1/32);
		for (int j = 0; j < W1; j++) {
			int s = get_2s(p, j);
			temp0 += (s * b[W2*j]);
			temp1 += (s * b[W2*j+1]);
		}
		c[W2*i] = temp0;
		c[W2*i+1] = temp1;
	}
};

extern "C" void nmppsMulMM_2s16s_4col(nm2s* A, int H, int W1, nm16s* B, nm16s* C, int W2) {
	long long * a = (long long*) A;
	short * b = (short*) B;
	short * c = (short*) C;
	short temp0, temp1, temp2, temp3;
	for (int i = 0; i < H; i++) {
		temp0 = 0;
		temp1 = 0;
		temp2 = 0;
		temp3 = 0;
		long long * p = a + i*(W1/32);
		for (int j = 0; j < W1; j++) {
			int s = get_2s(p, j);
			temp0 += (s * b[W2*j]);
			temp1 += (s * b[W2*j+1]);
			temp2 += (s * b[W2*j+2]);
			temp3 += (s * b[W2*j+3]);
		}
		c[W2*i] = temp0;
		c[W2*i+1] = temp1;
		c[W2*i+2] = temp2;
		c[W2*i+3] = temp3;
	}
};