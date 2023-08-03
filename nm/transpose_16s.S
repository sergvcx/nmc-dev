.global _nmppmTranspose_16s

.section .data.nmpp
	.align 3
	mulWH:   .quad		0x0000000000000000, \
						0x0000000000000000
	width:   .quad		0x0000000000000000
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

	SET nb1, 0x80000000
	SET sb , 0x2
	ar4 = mulWH;
	gr4 >>= 2;
	[ar4] = gr4;
	rep 2 wfifo = [ar4++], ftw;
	wtw;
	ar4 = width;
	[ar4] = gr5;
	rep 1 data = [ar4] with vsum , data, 0;
	rep 1 [ar4] = afifo;
	gr5 = [ar4];

	[ar6] = gr5;

	//SET vr, 0
	//SET nb1, 0x80008000
	//SET sb, 0x00020002
	//SET f1cr, 0x80008000
	//wtw;
//
	//ar4 = weights;
	//gr6 = 8;
	//gr0 = 2;
	//ar1 = ar0;
	//gr1 = 2;
	//ar2 = ar0;
	//gr2 = 2;
	//ar3 = ar0;
	//gr3 = 2;
//
	//call core_ClipMul4D4W4_AddVr;

	return;