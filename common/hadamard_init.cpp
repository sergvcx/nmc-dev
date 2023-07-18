#include "stdio.h"
#include "../include/nmtype.h"
#include "../include/hadamard.h"
#include "nmpp.h"

bool isPowerOfTwo(int n) {
	return (n > 0) && !(n&(n-1));
}

void nmppsHadamardInit(nm2s* H, int dim) {
	if (!isPowerOfTwo(dim)) return;

	nmppsPut_2s(H, 0, 1);

	int2b Hij;

	for (int n = 1; n < dim; n+=n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				nmppsGetVal_2s(H, i*dim+j, &Hij);
				nmppsPut_2s(H, (i+n)*dim+j, Hij);
				nmppsPut_2s(H, i*dim+j+n, Hij);
				nmppsPut_2s(H, (i+n)*dim+j+n, -Hij);
			}
		}
	}
};

void nmppsHadamardInitSort(const nm2s* srcNaturalOrderdMtr, nm2s* dstSequencyOrderedMtr, int dim) {
	if (!isPowerOfTwo(dim)) return;

	int *final_pos;
	final_pos = (int *)malloc32(dim/16);

	final_pos[0]=0;
	for (int n = 1; n < dim; n+=n) {
		for (int i = 0; i < n; i++) {
			final_pos[i]*=2;
			final_pos[2*n-i-1]=final_pos[i]+1;
		}
	}

	for (int i = 0; i < dim; i++) {
		int* src_addr = ((int*)srcNaturalOrderdMtr+(final_pos[i]*dim/16));
		int* dst_addr = ((int*)dstSequencyOrderedMtr+(i*dim/16));
		nmppsCopy_2s((nm2s*) src_addr, (nm2s*)dst_addr, dim);
	}
	
	free(final_pos);
	printf("Memory succesfully freed");
};