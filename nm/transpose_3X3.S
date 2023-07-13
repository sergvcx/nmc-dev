.global _transpose_3x3_32s
.global _transpose_3x3_RISC_32s
#include "printx.hs"

.p2align 3	
.data	//IMU_2
	Matrix_3X3:
		.quad 0x0000000000000001
		.quad 0x0000000000000000
		.quad 0x0000000000000000
		.quad 0x0000000100000000
		.quad 0x0000000000000000
		.quad 0x0000000100000000
		.quad 0x0000000000000001
		.quad 0x0000000000000000
		.quad 0x0000000000000001
		.quad 0x0000000000000000
		.quad 0x0000000000000000
		.quad 0x0000000100000000

.section .text.MyCode
//-------------------------------------------------3X3---------------------98tacts
_transpose_3x3_32s:
    ar5 = ar7 - 2;
	push ar4, gr4;	//rg for recover
	push ar3, gr3;	//array addr + 2
	push ar2, gr2;	//addr vsum matrix
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	ar0 = [--ar5];
	ar1 = [--ar5];
	gr2 = ar0;
	ar4 = ar1;
	gr0 = ar0;
	gr7 = 2;
	gr3 = gr0;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr4 = ar3;
	gr3 = 4;
	gr0 = 4;
	gr1 = 4;
	
	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
    ar2 = Matrix_3X3;
    rep 12 wfifo = [ar2++],ftw, wtw;

	rep 2 data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	rep 2 data = [ar3++gr3], ftw with vsum , data, afifo;
	rep 2 [ar1++gr1] = afifo, wtw;
	ar1 = ar4;
	ar1++;
	ar1++;
	ar0 = gr2;
	gr0 = 6;
	rep 1 data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	ar3 = gr4;
	rep 1 data = [ar0], ftw with vsum , data, afifo;
	rep 1 [ar1++gr1] = afifo, wtw;
	rep 1 data = [ar3++], ftw with vsum , data, ;
	wtw;
	rep 1 data = [ar3++gr3] with vsum , data, afifo;
	rep 1 [ar1++] = afifo;
	gr7 = [ar3];
	[ar1] = gr7;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	return;

//----------------------------------------------3X3--RISC---------------164tacts
_transpose_3x3_RISC_32s:
    ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	ar0 = [--ar5];
	ar1 = [--ar5];
	
	gr2 = 3;
	gr0 = 3;
	gr1 = ar0;
MARK_1:
	gr7 = [ar0];
	ar0 += gr0;
	[ar1++] = gr7;
	gr2--;
	if > goto MARK_1;
	
	gr1++;
	ar0 = gr1;
    gr2 = gr0;
MARK_2:
	gr7 = [ar0];
	ar0 += gr0;
	[ar1++] = gr7;
	gr2--;
	if > goto MARK_2;

	gr1++;
	ar0 = gr1;
    gr2 = gr0;
MARK_3:
	gr7 = [ar0];
	ar0 += gr0;
	[ar1++] = gr7;
	gr2--;
	if > goto MARK_3;

	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;
