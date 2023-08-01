.global _nmppsMerge4_16s

.section .data.imu1
	.align 3
	weights: .quad       0x0000000000000001,0,0,0, \
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
_nmppsMerge4_16s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	
	ar0 = [--ar5];					// * src0
	ar1 = [--ar5];					// * src1
	ar2 = [--ar5];					// * src2
	ar3 = [--ar5];					// * src3
	ar6 = [--ar5];					// dst
	gr5 = [--ar5];					// sizeSrc
	gr5 >>= 2;

	SET vr, gr0
	SET nb1, 0x80008000
	SET sb, 0x00020002
	SET f1cr, 0x80008000
	wtw;

	ar4 = weights;
	gr6 = 8;
	gr0 = 2;
	gr1 = 2;
	gr2 = 2;
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
	ar6++;
	ar6++;
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
	ar6++;
	ar6++;
	ar6++;
	ar6++;
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
	ar6++;
	ar6++;
	ar6++;
	ar6++;
	ar6++;
	ar6++;
	ar4 += gr4;
	call core_ClipMul4D4W4_AddVr;

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;