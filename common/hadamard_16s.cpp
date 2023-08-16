#include "../include/nmtype.h"
#include "../include/hadamard.h"
#include "../include/mTranspose.h"
#include "nmpp.h"

void nmppsHadamard_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size) {
	// dst = H * (H * src^T)^T

	nmppmTranspose_16s(src, temp, size, size);
	nmppsMulMM_2s16s(H, size, size, temp, dst, size);
	nmppmTranspose_16s(dst, temp, size, size);
	nmppsMulMM_2s16s(H, size, size, temp, dst, size);
}

void nmppsHadamardInverse_16s(nm16s* src, nm16s* dst, nm2s* H, nm16s* temp, int size) {
	// dst = (1/n * H *((1/n * H * src)^T))^T

	int nShift = 0;
	int nSize = size;
	while (nSize >>= 1) nShift++;

	nmppsMulMM_2s16s(H, size, size, src, temp, size);
	nmppsRShiftC_16u((const nm16u*)temp, nShift, (nm16u*)dst, size * size);
	nmppmTranspose_16s(dst, temp, size, size);
	nmppsMulMM_2s16s(H, size, size, temp, dst, size);
	nmppsRShiftC_16u((const nm16u*)dst, nShift, (nm16u*)temp, size * size);
	nmppmTranspose_16s(temp, dst, size, size);
}