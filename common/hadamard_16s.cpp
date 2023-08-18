#include "../include/nmtype.h"
#include "../include/hadamard.h"
#include "../include/mTranspose.h"
#include "nmpp.h"

void nmppsHadamard_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size) {
	// dst = H * (H * src^T)^T

	int nShift = 0;
	int nSize = size;
	while (nSize >>= 1) nShift++;

	int nShift1 = nShift / 2;
	int nShift2 = nShift - nShift1;

	nmppmTranspose_16s(src, temp, size, size);
	nmppsMulMM_2s16s(H, size, size, temp, dst, size);
	nmppsRShiftC_16s(dst, nShift1, temp, size * size);
	nmppmTranspose_16s(temp, dst, size, size);
	nmppsMulMM_2s16s(H, size, size, dst, temp, size);
	nmppsRShiftC_16s(temp, nShift2, dst, size * size);
}

void nmppsHadamardInverse_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size) {
	// dst = (1/n * H *((1/n * H * src)^T))^T

	int nShift = 0;
	int nSize = size;
	while (nSize >>= 1) nShift++;

	int nShift1 = nShift / 2;
	int nShift2 = nShift - nShift1;

	nmppsMulMM_2s16s(H, size, size, src, temp, size);
	nmppsRShiftC_16s(temp, nShift1, dst, size * size);
	nmppmTranspose_16s(dst, temp, size, size);
	nmppsMulMM_2s16s(H, size, size, temp, dst, size);
	nmppsRShiftC_16s(dst, nShift2, temp, size * size);
	nmppmTranspose_16s(temp, dst, size, size);
}