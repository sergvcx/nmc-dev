.global _nmppmTranspose_16s

.section .data.nmpp
	.align 3
	weights: .quad		 0x0000000000000001,0,0,0, \
						 0x0000000000010000,0,0,0, \
						 0x0000000100000000,0,0,0, \
						 0x0001000000000000,0,0,0, \
						  \
						 0,0x0000000000000001,0,0, \
						 0,0x0000000000010000,0,0, \
						 0,0x0000000100000000,0,0, \
						 0,0x0001000000000000,0,0, \
						  \
						 0,0,0x0000000000000001,0, \
						 0,0,0x0000000000010000,0, \
						 0,0,0x0000000100000000,0, \
						 0,0,0x0001000000000000,0, \
						  \
						 0,0,0,0x0000000000000001, \
						 0,0,0,0x0000000000010000, \
						 0,0,0,0x0000000100000000, \
						 0,0,0,0x0001000000000000

.macro SET reg,val
#if __NM4__== 0
	\reg = \val; 
#else
	sir = \val; 
	\reg = sir;
#endif
.endm

.text
_nmppmTranspose_16s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;

	ar0 = [--ar5];					// * srcMatrix
	ar6 = [--ar5];					// * dstMAtrix
	gr4 = [--ar5];					// * height
	gr5 = [--ar5];					// * width

	gr0 = 2;

	gr5 >>= 2;
	ar1 = ar0;
	gr1 = gr5;
	ar1 += gr1;
	gr1 = 2;

	ar2 = ar1;
	gr2 = gr5;
	ar2 += gr2;
	gr2 = 2;

	ar3 = ar2;
	gr3 = gr5;
	ar3 += gr3;
	gr3 = 2;

	gr6 = gr5<<1;

	ar4 = weights;

	call core_ClipMul4D4W4_AddVr;

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;