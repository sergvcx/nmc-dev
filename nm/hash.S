.global _hashRep32
#include "printx.hs"

.section .bss.MyData1
    .align 8
	.global B
	B:  .space  64<<2
	
.p2align 3	
.data									//IMU_2
	Matrix:
		.quad 0x0000000000000001
		.quad 0x0000000000000001
		
.section .text.SomeCode
//-------------------------------------------HASH-rep32-------------
_hashRep32:
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5]; 	//array addr
	gr0 = [--ar5];	//counter
	gr1 = 1 << 6;
	gr1 = gr1 - 1;
	gr1 = gr1 and gr0;
	gr1 = gr1 >> 1;		//counter for rep 1
	gr0 = gr0 >> 6;		//counter for rep 32
	
	ar2, gr2 = B;
	
	sir = 0h;
	nb1 = sir;
	sb = sir;
	ar1 = Matrix;
	rep 1 wfifo = [ar1++],ftw, wtw;
	
	rep 32 with 0;
	gr0--;
	goto Condition;
Loop_32:
	rep 32 data = [ar0++] with vsum , shift afifo, data;
Condition:
	if >= delayed goto Loop_32 with gr0--;
	nul;
	nul;
	
	rep 32 [ar2++] = afifo;
	
	ar2 = gr2;
	rep 16 data = [ar2++] with data;
	rep 16 data = [ar2++] with vsum , shift afifo, data;
	ar2 = gr2;
	rep 16 [ar2++] = afifo;
	
	ar2 = gr2;
	rep 8 data = [ar2++] with data;
	rep 8 data = [ar2++] with vsum , shift afifo, data;
	ar2 = gr2;
	rep 8 [ar2++] = afifo;
	
	ar2 = gr2;
	rep 4 data = [ar2++] with data;
	rep 4 data = [ar2++] with vsum , shift afifo, data;
	ar2 = gr2;
	rep 4 [ar2++] = afifo;
	
	ar2 = gr2;
	rep 2 data = [ar2++] with data;
	rep 2 data = [ar2++] with vsum , shift afifo, data;
	ar2 = gr2;
	rep 2 [ar2++] = afifo;
	
	ar2 = gr2;
	rep 1 data = [ar2++] with data;
	rep 1 data = [ar2] with vsum , shift afifo, data;
	
	gr1--;
	goto Mark;
Cycle:
	rep 1 data = [ar0++] with vsum , shift afifo, data;
Mark:
	if >= delayed goto Cycle with gr1--;
	nul;
	nul;
	
	rep 1 [ar2] = afifo;
	gr7 = [ar2++];
	gr2 = [ar2];
	gr7 = gr7 + gr2;
	
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return gr7;
