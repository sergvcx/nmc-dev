#include "../include/nmtype.h"

char afifo8;
short afifo16;
int afifo32;
long long afifo64;
extern "C" {
void nmppsMinMax_8s( nm8s *srcA, nm8s *srcB, nm8s *dstMin, nm8s *dstMax, int size) {
	char *a = (char*) srcA;
	char *b = (char*) srcB;
	char *a_res = (char*) dstMin;
	char *b_res = (char*) dstMax;
	for (int i = 0; i < size - size%8; i++) {
		afifo8 = a[i] - b[i];
		afifo8 = afifo8>>7;
		a_res[i] = (afifo8&a[i]) | (~afifo8&b[i]);
		b_res[i] = (afifo8&b[i]) | (~afifo8&a[i]);
	}
}

void nmppsMinMax_16s( nm16s *srcA, nm16s *srcB, nm16s *dstMin, nm16s *dstMax, int size) {
	short *a = (short*) srcA;
	short *b = (short*) srcB;
	short *a_res = (short*) dstMin;
	short *b_res = (short*) dstMax;
	for (int i = 0; i < size - size%4; i++) {
		afifo16 = a[i] - b[i];
		afifo16 = afifo16>>15;
		a_res[i] = (afifo16&a[i]) | (~afifo16&b[i]);
		b_res[i] = (afifo16&b[i]) | (~afifo16&a[i]);
	}
}

void nmppsMinMax_32s( nm32s *srcA, nm32s *srcB, nm32s *dstMin, nm32s *dstMax, int size) {
	int *a = (int*) srcA;
	int *b = (int*) srcB;
	int *a_res = (int*) dstMin;
	int *b_res = (int*) dstMax;
	for (int i = 0; i < size - size%2; i++) {
		afifo32 = a[i] - b[i];
		afifo32 = afifo32>>31;
		a_res[i] = (afifo32&a[i]) | (~afifo32&b[i]);
		b_res[i] = (afifo32&b[i]) | (~afifo32&a[i]);
	}
}

void nmppsMinMax_64s( nm64s *srcA, nm64s *srcB, nm64s *dstMin, nm64s *dstMax, int size) {
	long long *a = (long long*) srcA;
	long long *b = (long long*) srcB;
	long long *a_res = (long long*) dstMin;
	long long *b_res = (long long*) dstMax;
	for (int i = 0; i < size; i++) {
		afifo64 = a[i] - b[i];
		afifo64 = afifo64>>31;
		a_res[i] = (afifo64&a[i]) | (~afifo64&b[i]);
		b_res[i] = (afifo64&b[i]) | (~afifo64&a[i]);
	}
}
};