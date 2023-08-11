#include "../include/nmtype.h"
#include "../include/hadamard.h"

extern "C"
{

	void nmppsMulMM_2s32s(nm2s *A, int H, int W1, nm32s *B, nm32s *C, int W2)
	{
		nm32s *src_col = B;
		nm32s *dst_col = C;

		for (int i = 0; i < W2; i += 2)
		{
			nmppsMulMM_2s32s_2col(A, H, W1, src_col, dst_col, W2);
			src_col += 2;
			dst_col += 2;
		}
	}

	void nmppsMulMM_2s16s(nm2s *A, int H, int W1, nm16s *B, nm16s *C, int W2)
	{
		int *src_col = (int *)B;
		int *dst_col = (int *)C;

		for (int i = 0; i < W2; i += 4)
		{
			{
				nmppsMulMM_2s16s_4col(A, H, W1, (nm16s *)src_col, (nm16s *)dst_col, W2);
				src_col += 2;
				dst_col += 2;
			}
		}
	}
}