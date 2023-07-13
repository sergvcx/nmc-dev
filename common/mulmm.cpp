#include "../include/nmtype.h"
#include "../include/hadamard.h"

void nmppsMulMM_2s32s(nm2s* A, int H, int W1, nm32s* B, nm32s* C, int W2) {
	nm32s * src_col = B;
	nm32s * dst_col = C;
		
	for(int i = 0; i < W2; i += 2) {
		nmppsMulMM_2s32s_2col(A, H, W1, src_col, dst_col, W2);
		src_col+=2;
		dst_col+=2;
	}
}