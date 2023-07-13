#include "../include/nmtype.h"

char afifo8;
short afifo16;
int afifo32;
long long afifo64;

void nmppsMinMax_8s_x86( nm8s *srcA, nm8s *srcB, nm8s *dstMin, nm8s *dstMax, int size) {
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

void nmppsMinMax_16s_x86( nm16s *srcA, nm16s *srcB, nm16s *dstMin, nm16s *dstMax, int size) {
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

void nmppsMinMax_32s_x86( nm32s *srcA, nm32s *srcB, nm32s *dstMin, nm32s *dstMax, int size) {
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

void nmppsMinMax_64s_x86( nm64s *srcA, nm64s *srcB, nm64s *dstMin, nm64s *dstMax, int size) {
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

void nmppsMinMax_8s_C( nm8s *srcA, nm8s *srcB, nm8s *dstMin, nm8s *dstMax, int size){
	int *a = (int*) srcA;
	int *b = (int*) srcB;
	int *a_res = (int*) dstMin;
	int *b_res = (int*) dstMax;
	for (int i = 0; i < size/4; i+=2) {
		int a0 = (a[i]<<24)>>24;	// ---* ----
		int a1 = (a[i]<<16)>>24;	// --*- ----
		int a2 = (a[i]<<8)>>24;		// -*-- ----
		int a3 = (a[i])>>24;		// *--- ----
		int a4 = (a[i+1]<<24)>>24;	// ---- ---*
		int a5 = (a[i+1]<<16)>>24;	// ---- --*-
		int a6 = (a[i+1]<<8)>>24;	// ---- -*--
		int a7 = (a[i+1])>>24;		// ---- *---

		int b0 = (b[i]<<24)>>24;	// ---* ----
		int b1 = (b[i]<<16)>>24;	// --*- ----
		int b2 = (b[i]<<8)>>24;		// -*-- ----
		int b3 = (b[i])>>24;		// *--- ----
		int b4 = (b[i+1]<<24)>>24;	// ---- ---*
		int b5 = (b[i+1]<<16)>>24;	// ---- --*-
		int b6 = (b[i+1]<<8)>>24;	// ---- -*--
		int b7 = (b[i+1])>>24;		// ---- *---

		a_res[i] = (a0<b0) ? a0 : b0;
		a_res[i] &= 0x000000ff;
		a_res[i] |= (((a1<b1) ? a1 : b1)<<8);
		a_res[i] &= 0x0000ffff;
		a_res[i] |= (((a2<b2) ? a2 : b2)<<16);
		a_res[i] &= 0x00ffffff;
		a_res[i] |= (((a3<b3) ? a3 : b3)<<24);

		b_res[i] = (a0<b0) ? b0 : a0;
		b_res[i] &= 0x000000ff;
		b_res[i] |= (((a1<b1) ? b1 : a1)<<8);
		b_res[i] &= 0x0000ffff;
		b_res[i] |= (((a2<b2) ? b2 : a2)<<16);
		b_res[i] &= 0x00ffffff;
		b_res[i] |= (((a3<b3) ? b3 : a3)<<24);

		a_res[i+1] = (a4<b4) ? a4 : b4;
		a_res[i+1] &= 0x000000ff;
		a_res[i+1] |= (((a5<b5) ? a5 : b5)<<8);
		a_res[i+1] &= 0x0000ffff;
		a_res[i+1] |= (((a6<b6) ? a6 : b6)<<16);
		a_res[i+1] &= 0x00ffffff;
		a_res[i+1] |= (((a7<b7) ? a7 : b7)<<24);

		b_res[i+1] = (a4<b4) ? b4 : a4;
		b_res[i+1] &= 0x000000ff;
		b_res[i+1] |= (((a5<b5) ? b5 : a5)<<8);
		b_res[i+1] &= 0x0000ffff;
		b_res[i+1] |= (((a6<b6) ? b6 : a6)<<16);
		b_res[i+1] &= 0x00ffffff;
		b_res[i+1] |= (((a7<b7) ? b7 : a7)<<24);
	}
};

void nmppsMinMax_16s_C( nm16s *srcA, nm16s *srcB, nm16s *dstMin, nm16s *dstMax, int size){
	int *a = (int*) srcA;
	int *b = (int*) srcB;
	int *a_res = (int*) dstMin;
	int *b_res = (int*) dstMax;
	for (int i = 0; i < size/2; i+=2) {
		int a0 = (a[i]<<16)>>16;	// -* --
		int a1 = (a[i])>>16;		// *- --
		int a2 = (a[i+1]<<16)>>16;	// -- -*
		int a3 = (a[i+1])>>16;		// -- *-

		int b0 = (b[i]<<16)>>16;
		int b1 = (b[i])>>16;
		int b2 = (b[i+1]<<16)>>16;
		int b3 = (b[i+1])>>16;

		a_res[i] = (a0<b0) ? a0 : b0;
		a_res[i] &= 0x0000ffff;
		a_res[i] |= (((a1<b1) ? a1 : b1)<<16);

		b_res[i] = (a0<b0) ? b0 : a0;
		b_res[i] &= 0x0000ffff;
		b_res[i] |= (((a1<b1) ? b1 : a1)<<16);

		a_res[i+1] = (a2<b2) ? a2 : b2;
		a_res[i+1] &= 0x0000ffff;
		a_res[i+1] |= (((a3<b3) ? a3 : b3)<<16);

		b_res[i+1] = (a2<b2) ? b2 : a2;
		b_res[i+1] &= 0x0000ffff;
		b_res[i+1] |= (((a3<b3) ? b3 : a3)<<16);
	}
};

void nmppsMinMax_32s_C( nm32s *srcA, nm32s *srcB, nm32s *dstMin, nm32s *dstMax, int size){
	int *a = (int*) srcA;
	int *b = (int*) srcB;
	int *a_res = (int*) dstMin;
	int *b_res = (int*) dstMax;
	for (int i = 0; i < size; i+=2) {
		a_res[i] = (a[i]<b[i]) ? a[i] : b[i];
		b_res[i] = (a[i]<b[i]) ? b[i] : a[i];
		a_res[i+1] = (a[i+1]<b[i+1]) ? a[i+1] : b[i+1];
		b_res[i+1] = (a[i+1]<b[i+1]) ? b[i+1] : a[i+1];
	}
};

void nmppsMinMax_64s_C( nm64s *srcA, nm64s *srcB, nm64s *dstMin, nm64s *dstMax, int size){
	long long *a = (long long*) srcA;
	long long *b = (long long*) srcB;
	long long *a_res = (long long*) dstMin;
	long long *b_res = (long long*) dstMax;
	for (int i = 0; i < size; i++) {
		a_res[i] = (a[i]<b[i]) ? a[i] : b[i];
		b_res[i] = (a[i]<b[i]) ? b[i] : a[i];
	}
};