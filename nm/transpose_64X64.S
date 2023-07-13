.global _transpose_2x2
.global _transpose_4x4
.global _transpose_64x64
.global _transpose_64x64_Mask_bL
.global _transpose_64x64_Mask_bC
#include "printx.hs"

.p2align 3	
.data	//IMU_2
	Masks:
		.quad 0x00000000FFFFFFFF
		.quad 0xFFFFFFFF00000000
	Matrix_2X2:
		.quad 0x0000000100000000
		.quad 0x0000000000000001
	Matrix_gen:
		.quad 0x0000000000000001
		.quad 0x0000000000000000
		.quad 0x0000000100000000
		.quad 0x0000000000000000
		.quad 0x0000000000000000
		.quad 0x0000000100000000
		.quad 0x0000000000000000
		.quad 0x0000000000000001

//--------------------------------------------------2X2------------------------57tacts
.section .text.MyCode
_transpose_2x2:
    ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5]; 	//array addr
	ar2 = [--ar5];	//result addr
	
	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
    ar1 = Matrix_2X2;
    rep 2 wfifo = [ar1++],ftw, wtw;

	//ar3 = Masks;
	//rep 2 ram = [ar3++];
	
	//ar0 = ar0 + 4;
	//rep 2 data = [--ar0] with vsum , data, ;
	//rep 2 data = [ar0++] with mask ram, data, afifo;
	//rep 2 [ar2++] = afifo;
	
	ar3 = Masks;
	rep 1 ram = [ar3++];

	ar0 = ar0 + 4;
	rep 1 data = [--ar0] with vsum , data, ;
	rep 1 data = [--ar0] with mask ram, data, afifo;
	rep 1 [ar2++] = afifo;

	rep 1 data = [ar0++] with vsum , data, ;
	rep 1 data = [ar0++] with mask ram, afifo, data;
	rep 1 [ar2] = afifo;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;

//-------------------------------------------------4X4---------------------132tacts---129if_W16
_transpose_4x4:
    ar5 = ar7 - 2;
	push ar6, gr6;	//rg for addr + 6
	push ar5, gr5;	//rg for addr + 2
	push ar4, gr4;	//rg for recover
	push ar3, gr3;	//array addr + 4
	push ar2, gr2;	//addr vsum matrix
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	
	ar0 = [--ar5];
	gr2 = ar0;		//saved array addr
	gr0 = 8;
	
	ar1 = [--ar5];

	gr7 = 4;
	gr3 = ar0;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr4 = ar3;		//saved addr +  4
	gr3 = 8;

	gr7 = 2;
	gr5 = ar0;
	gr5 = gr5 + gr7;
	ar5 = gr5;
	gr1 = ar5;		//saved addr +  2
	gr5 = 8;

	gr7 = 6;
	gr6 = ar0;
	gr6 = gr6 + gr7;
	ar6 = gr6;
	ar4 = ar6;		//saved addr + 6
	gr6 = 8;
	
	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
    ar2 = Matrix_gen;
    rep 8 wfifo = [ar2++],ftw, wtw;

	rep 2 data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	rep 2 data = [ar3++gr3], ftw with vsum , data, afifo;
	rep 2 [ar1++] = afifo, wtw;

	ar0 = gr2;
	ar3 = gr4;
	rep 2 data = [ar3++gr3], ftw with vsum , data, ;
	wtw;
	rep 2 data = [ar0++gr0] with vsum , data, afifo;
	rep 2 [ar1++] = afifo;

	ar2 = Matrix_gen;
    rep 8 wfifo = [ar2++],ftw, wtw;

	rep 2 data = [ar5++gr5], ftw with vsum , data, ;
	wtw;
	rep 2 data = [ar6++gr6], ftw with vsum , data, afifo;
	rep 2 [ar1++] = afifo, wtw;

	ar5 = gr1;
	ar6 = ar4;
	rep 2 data = [ar6++gr6], ftw with vsum , data, ;
	wtw;
	rep 2 data = [ar5++gr5] with vsum , data, afifo;
	rep 2 [ar1++] = afifo;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;

//-------------------------------------------------64X64---------------------1,041-per-elem
_transpose_64x64:
    ar5 = ar7 - 2;
	push ar4, gr4;	//rg for recover
	push ar3, gr3;	//array addr + 64
	push ar2, gr2;	//addr vsum W matrix
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	
	gr1 = 32;		//counter for loop

	ar0 = [--ar5];
	gr2 = ar0;		//saved array addr
	gr0 = 128;
	
	ar1 = [--ar5];

	gr7 = 64;
	gr3 = ar0;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr4 = ar3;		//saved addr + 64
	gr3 = 128;
	
	gr7 = 2;

	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
Loop:
    ar2 = Matrix_gen;
    rep 8 wfifo = [ar2++],ftw, wtw;

	rep 32 data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	rep 32 data = [ar3++gr3], ftw with vsum , data, afifo;
	rep 32 [ar1++] = afifo, wtw;

	ar0 = gr2;
	ar3 = gr4;
	rep 32 data = [ar3++gr3], ftw with vsum , data, ;
	wtw;
	rep 32 data = [ar0++gr0] with vsum , data, afifo;
	rep 32 [ar1++] = afifo;

	gr2 = gr2 + gr7;
	ar0 = gr2;
	gr1--;
	if > delayed goto Loop;
	gr4 = gr4 + gr7;
	ar3 = gr4;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	return;

//-------------------------------------------------64X64--Mask-Lines--------------------1,028-per-elem
_transpose_64x64_Mask_bL:
    ar5 = ar7 - 2;
	push ar6, gr6;	//result addr + 64
	push ar4, gr4;	//rg for recover
	push ar3, gr3;	//array addr + 64
	push ar2, gr2;	//addr vsum W matrix
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	
	gr0 = 32;		//counter for loop

	ar0 = [--ar5];
	gr2 = ar0;		//saved array addr
	
	gr7 = 64;
	gr3 = ar0;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr4 = ar3;		//saved addr + 64

	ar1 = [--ar5];
	gr1 = 128;
	gr3 = ar1;		//saved result addr
	ar6 = ar1;
	ar6 = ar6 + 64;	//result addr + 64
	gr6 = 128;
	
	gr7 = 2;
	ar5 = Masks;

	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
	ar2 = Matrix_2X2;
    rep 2 wfifo = [ar2++],ftw, wtw;
	rep 32 ram = [ar5];
Cycle:
	rep 32 data = [ar0++] with vsum , data, ;
	rep 32 data = [ar3++] with mask ram, afifo, data;
	rep 32 [ar6++gr6] = afifo;
	
	ar0 = gr2;
	ar3 = gr4;
	rep 32 data = [ar3++] with vsum , data, ;
	rep 32 data = [ar0++] with mask ram, data, afifo;
	rep 32 [ar1++gr1] = afifo;

	ar0 = ar3;
	gr2 = ar3;
	gr4 = gr4 + gr1; 
	ar3 = gr4;
	gr3 = gr3 + gr7;
	ar1 = gr3;
	ar6 = ar1;
	gr0--;
	if > delayed goto Cycle;
	ar6 = ar6 + 64;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;

//-------------------------------------------------64X64--Mask-Columns--------------------1,029-per-elem
_transpose_64x64_Mask_bC:
    ar5 = ar7 - 2;
	push ar6, gr6;	//2
	push ar5, gr5;	//saved res addr n res addr + 64
	push ar4, gr4;	//saved array addr n addr + 64
	push ar3, gr3;	//array addr + 64
	push ar2, gr2;	//result addr + 64
	push ar1, gr1;	//result addr
	push ar0, gr0; 	//array addr
	
	gr1 = 32;		//counter for loop

	ar0 = [--ar5];
	ar4 = ar0;		
	gr0 = 128;
	
	gr7 = 64;
	gr3 = ar0;
	gr3 = gr3 + gr7;
	ar3 = gr3;
	gr4 = ar3;		
	gr3 = gr0;

	ar1 = [--ar5];
	gr2 = ar1;
	gr2 = gr2 + gr7;
	ar2 = gr2;
	ar5 = ar1;
	gr5 = ar2;
	
	gr6 = 2;

	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
	ar6 = Matrix_2X2;
    rep 2 wfifo = [ar6++],ftw, wtw;
	ar6 = Masks;
	rep 32 ram = [ar6];
Mark:
	rep 32 data = [ar3++gr3] with vsum , data, ;
	rep 32 data = [ar0++gr0] with mask ram, data, afifo;
	rep 32 [ar1++] = afifo;

	ar0 = ar4;
	ar3 = gr4;
	rep 32 data = [ar0++gr0] with vsum , data, ;
	rep 32 data = [ar3++gr3] with mask ram, afifo, data;
	rep 32 [ar2++] = afifo;

	ar4 = ar4 + 2;
	gr4 = gr4 + gr6;
	ar0 = ar4;
	ar3 = gr4;
	ar1 = ar2;
	gr2 = ar2;
	gr1--;
	if > delayed goto Mark;
		gr2 = gr2 + gr7;
		ar2 = gr2;

    pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
