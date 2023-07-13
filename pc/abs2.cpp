#include "../include/nmtype.h"

extern "C" void nmppsAbs2_8s( nm8s *srcA, nm8s *dstB, int size){
	char *a = (char*) srcA;
	char *b = (char*) dstB;
	for (int i = 0; i < size - size%8; i++) {
		char afifo = a[i] >> 7;
		b[i] = (afifo&(-a[i]))|(~afifo&a[i]);
		afifo = b[i] >> 7;
		b[i] ^= afifo;
	};
};

extern "C" void nmppsAbs2_16s( nm16s *srcA, nm16s *dstB, int size){
	short *a = (short*) srcA;
	short *b = (short*) dstB;
	for (int i = 0; i < size - size%4; i++) {
		short afifo = a[i] >> 15;
		b[i] = (afifo&(-a[i]))|(~afifo&a[i]);
		afifo = b[i] >> 15;
		b[i] ^= afifo;
	};
};

extern "C" void nmppsAbs2_32s( nm32s *srcA, nm32s *dstB, int size){
	int *a = (int*) srcA;
	int *b = (int*) dstB;
	for (int i = 0; i < size - size%2; i++) {
		int afifo = a[i] >> 31;
		b[i] = (afifo&(-a[i]))|(~afifo&a[i]);
		afifo = b[i] >> 31;
		b[i] ^= afifo;
	};
};

extern "C" void nmppsAbs2_64s( nm64s *srcA, nm64s *dstB, int size){
	long long *a = (long long*) srcA;
	long long *b = (long long*) dstB;
	for (int i = 0; i < size; i++) {
		long long afifo = a[i] >> 63;
		b[i] = (afifo&(-a[i]))|(~afifo&a[i]);
		afifo = b[i] >> 63;
		b[i] ^= afifo;
	};
};
