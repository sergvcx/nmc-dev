#include "../include/nmtype.h"
#include "../include/hadamard.h"
#include "nmpp.h"

/*size=32, time=2.843628
size=64, time=11.207092
size=128, time=46.435730 c++ transp


size=32, time=1.011292
size=64, time=2.287170
size=128, time=9.574402 fast

size=32, time=447.391479
size=64, time=3559.143860
size=128, time=28408.257996 c++ mulmm

size=32, time=449.230347
size=64, time=3568.077026
size=128, time=28445.145386 slow*/
void nmppsHadamard(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size) {
	// dst = H * (H * src^T)^T

	nmppsTranspose(src, temp, size, size);
	nmppsMulMM_2s32s(H, size, size, temp, dst, size);
	nmppsTranspose(dst, temp, size, size);
	nmppsMulMM_2s32s(H, size, size, temp, dst, size);
}

void nmppsHadamardInverse(nm32s* src, nm32s* dst, nm2s* H, nm32s* temp, int size) {
	// dst = (1/n * H *((1/n * H * src)^T))^T

	int nShift = 0;
	while (size >>= 1) nShift++; 

	nmppsMulMM_2s32s(H, size, size, src, temp, size);
	nmppsRShiftC_32s(temp, nShift, dst, size*size);
	nmppsTranspose(dst, temp, size, size);
	nmppsMulMM_2s32s(H, size, size, temp, dst, size);
	nmppsRShiftC_32s(dst, nShift, temp, size*size);
	nmppsTranspose(temp, dst, size, size);
}