#include "../common/nmtype.h"
#include "nmpp.h"

bool isPowerOfTwo(int n) {
	return (n > 0) && !(n&(n-1));
}

void nmppsHadamardInit(nm2s* H, int size) {
	if (!isPowerOfTwo(size)) return;

	nmppsPut_2s(H, 0, 1);

	int2b Hij;

	for (int n = 1; n < size; n+=n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				nmppsGetVal_2s(H, i*size+j, &Hij);
				nmppsPut_2s(H, (i+n)*size+j, Hij);
				nmppsPut_2s(H, i*size+j+n, Hij);
				nmppsPut_2s(H, (i+n)*size+j+n, -Hij);
			}
		}
	}
};

void nmppsHadamardInitSort(nm2s* Hsrc, nm2s* Hdst, int size) {
	if (!isPowerOfTwo(size)) return;

	int *final_pos;
	final_pos = (int *)malloc32(size/16);

	final_pos[0]=0;
	for (int n = 1; n < size; n+=n) {
		for (int i = 0; i < n; i++) {
			final_pos[i]*=2;
			final_pos[2*n-i-1]=final_pos[i]+1;
		}
	}

	for (int i = 0; i < size; i++) {
		int* src_addr = ((int*)Hsrc+(final_pos[i]*size/16));
		int* dst_addr = ((int*)Hdst+(i*size/16));
		nmppsCopy_2s((nm2s*) src_addr, (nm2s*)dst_addr, size);
	}
	free(final_pos);
};