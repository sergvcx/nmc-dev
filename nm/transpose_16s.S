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
transpose4Lines:
	gr6 = gr4<<1;

	ar1 = ar0;
	gr1 = gr5<<1;
	ar1 += gr1;
	gr1 = 2;
	ar2 = ar1;
	gr2 = gr5<<1;
	ar2 += gr2;
	gr2 = 2;
	ar3 = ar2;
	gr3 = gr5<<1;
	ar3 += gr3;
	gr3 = 2;

	gr4 = 32;
	ar5 = ar6;
	
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	ar6 = ar5;
	gr6 >>= 2;
	ar6 += gr6;
	gr6 <<= 2;
	ar5 = ar6;
	ar4 += gr4;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	ar6 = ar5;
	gr6 >>= 2;
	ar6 += gr6;
	gr6 <<= 2;
	ar5 = ar6;
	ar4 += gr4;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	
	ar6 = ar5;
	gr6 >>= 2;
	ar6 += gr6;
	gr6 <<= 2;
	ar4 += gr4;
	call core_ClipMul4D4W4_AddVr;
	return;

transpose4Columns:
	gr4 = 32;

	gr6 = 2;

	ar1 = ar0;
	gr1 = gr5>>1;
	ar1 += gr1;
	gr1 = gr0;
	ar2 = ar1;
	gr2 = gr5>>1;
	ar2 += gr2;
	gr2 = gr0;
	ar3 = ar2;
	gr3 = gr5>>1;
	ar3 += gr3;
	gr3 = gr0;
	
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	ar4 += gr4;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	ar4 += gr4;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	call core_ClipMul4D4W4_AddVr;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	
	ar4 += gr4;
	call core_ClipMul4D4W4_AddVr;
	return;

// transpose lines
_nmppmTranspose_16s_Lines:
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

	SET vr, 0
	SET nb1, 0x80008000
	SET sb, 0x00020002
	SET f1cr, 0x80008000
	wtw;

	gr5 >>= 2;
	gr0 = 2;
	ar4 = weights;

	gr1 = gr4>>2;	// gr7?
	loop:
	if <= goto endLoop;
		push ar1, gr1;
		push ar4, gr4;
		push ar6, gr6;
		call transpose4Lines;
		pop ar6, gr6;
		pop ar4, gr4;
		pop ar1, gr1;
		ar0 = ar3;
		gr6 = 2;
		ar6 += gr6;
	goto loop with gr1--;
	endLoop:

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;

// transpose columns
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

	SET vr, 0
	SET nb1, 0x80008000
	SET sb, 0x00020002
	SET f1cr, 0x80008000
	wtw;

	gr0 = gr5<<1;
	gr5 = gr4>>2;
	ar4 = weights;

	gr1 = gr5>>2;
	loopCol:
	if <= goto endLoopCol;
		push ar0, gr0;
		push ar1, gr1;
		push ar4, gr4;
		call transpose4Columns;
		pop ar4, gr4;
		pop ar1, gr1;
		pop ar0, gr0;
		gr0 = 2;
		ar0 += gr0;
		gr0 = gr5<<1;
	goto loopCol with gr1--;
	endLoopCol:

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;