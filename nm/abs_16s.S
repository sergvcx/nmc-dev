.global _mod
.global _abs_16s
#include "printx.hs"

//--------------------------------------------------------------MOD---------
.p2align 3	
.data	//IMU_2
	Masks: 
		.quad 0x000000000000FFFF
        .quad 0x00000000FFFF0000
		.quad 0x0000FFFF00000000
		.quad 0xFFFF000000000000
        .quad 0x0000000000000000
		.quad 0x0000000000000000
		.quad 0x0000000000000001
		.quad 0x0000000100000000
		.quad 0x0000000000000001
		.quad 0x0000000100000000
		.quad 0x0000000000000000
		.quad 0x0000000000000000
		
.section .text.MyCode	
_mod:
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5]; 	//array addr
	ar2 = [--ar5];	//result addr
	gr2 = ar2;
	ar1 = Masks;
	
	sir = 80008000h;
	nb1 = sir;
	sir = 00020002h;
	sb = sir;
	rep 12 wfifo = [ar1++],ftw, wtw;
	sir = 80008000h;
	f1cr = sir;
	
	rep 1 ram = [ar0] with activate data or 0;
	rep 1 ftw with vsum afifo, ram, ram;
	rep 1 [ar2] = afifo, wtw;
	
	rep 1 data = [ar2++], ftw with vsum , data, 0;
	rep 1 [ar2] = afifo, wtw;
	ar2 = gr2;
	rep 1 data = [ar2] with vsum , data, 0;
	rep 1 [ar2] = afifo;
	
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	return;

//--------------------------------------------------abs_16s--- ~1,05 per elem --------
_abs_16s:
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5]; 	//array addr
	ar2 = [--ar5];	//result addr
	gr0 = [--ar5];	//counter
	gr1 = 1 << 7;
	gr1 = gr1 - 1;
	gr1 = gr1 and gr0;
	gr1 = gr1 >> 2;		//counter for rep 1
	gr0 = gr0 >> 7;		//counter for rep 32
	gr2 = 4;			//step for mem
	gr7 = 2;
	gr3 = ar2;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr3 = 4;
	
	sir = 80008000h;
	nb1 = sir;
	sir = 00020002h;
	sb = sir;
	sir = 80008000h;
	f1cr = sir;
	//PRINTF1("counter rep 32 =%d\n",gr0)
	//PRINTF1("counter rep 1 =%d\n",gr1)
	gr0--;
	goto Condition;
Loop:
	rep 12 wfifo = [ar1++],ftw, wtw;
	rep 32 ram = [ar0++] with activate data or 0;
	rep 32 ftw with vsum afifo, ram, ram;
	rep 32 [ar2],ram = afifo, wtw;
	rep 32 ftw with vsum , ram, 0;
	rep 32 [ar3++gr3] = afifo, wtw;
	rep 32 with vsum , ram, 0;
	rep 32 [ar2++gr2] = afifo;
Condition:
	if >= delayed goto Loop with gr0--;
		ar1 = Masks; //64b
	
	gr1--;
	goto Mark;
Cycle:
	rep 12 wfifo = [ar1++], ftw, wtw;
	rep 1 ram = [ar0++] with activate data or 0;
	rep 1 ftw with vsum afifo, ram, ram;
	rep 1 [ar2],ram = afifo, wtw;
	rep 1 ftw with vsum , ram, 0;
	rep 1 [ar3++gr3] = afifo, wtw;
	rep 1 with vsum , ram, 0;
	rep 1 [ar2++gr2] = afifo;
Mark:
	if >= delayed goto Cycle with gr1--;
		ar1 = Masks;
	
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
