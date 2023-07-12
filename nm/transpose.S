.global _nmppsTranspose
#include "printx.hs"

.p2align 3	
.data	//IMU_2
	Masks:
		.quad 0x00000000FFFFFFFF
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

.macro Transpose_rep N
	ar2 = Matrix_gen;
    rep 8 wfifo = [ar2++],ftw, wtw;

	rep \N data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	rep \N data = [ar3++gr3], ftw with vsum , data, afifo;
	rep \N [ar1++] = afifo, wtw;

	ar0 = gr7;
	gr7 = gr7 + gr1;
	ar3 = gr7;
	rep \N data = [ar3++gr3], ftw with vsum , data, ;
	wtw;
	rep \N data = [ar0++gr0] with vsum , data, afifo;
	rep \N [ar4++] = afifo;
    
    goto RET_MACRO;
.endm

.macro Transpose_rep_mask N
	gr7 = Masks;
	rep \N ram = [gr7];
	rep \N data = [ar3++] with vsum , data, ;
	rep \N data = [ar0++] with mask ram, data, afifo;
	rep \N [ar1++gr1] = afifo;

	ar3 = gr3;
    ar0 = ar6;
    ar1 = ar5;
	rep \N data = [ar0++] with vsum , data, ;
	rep \N data = [ar3++] with mask ram, afifo, data;
	rep \N [ar1++gr1] = afifo;

    goto RET_MACRO_MASK;
.endm

.section .text.MyCode
//-------------------------------------------------GENERAL---------------------?-per-elem
_nmppsTranspose:
    ar5 = ar7 - 2;
	push ar0, gr0; 	//array addr
	push ar1, gr1;	//result addr
	push ar2, gr2;	//counter
	push ar3, gr3;	//array addr + width
	push ar4, gr4;	//
    push ar5, gr5;  //_ n height
	push ar6, gr6;  //_ n width

	ar0 = [--ar5];  //array addr

	ar1 = [--ar5];  //result addr

	gr5 = [--ar5];	//height
	gr6 = [--ar5];	//width

	
	gr7 = gr6 - gr5;
	if < delayed goto Columns;
		gr1 = gr6;		//width
		gr2 = gr1;
Lines:
	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
	ar2 = Matrix_2X2;
    rep 2 wfifo = [ar2++],ftw, wtw;
	ar2 = Masks;
	rep 32 ram = [ar2];

    gr0 = gr5;
    gr0 = gr0 >> 1; //counter for lines

    gr4 = gr6;
    gr4 = gr4 >> 6; //counter for columns-reps
    
    gr3 = ar0;
    gr3 = gr3 + gr6;
    ar3 = gr3;      //array addr + width

    ar6 = ar0;		//saved array addr
    
	gr7 = ar1;
    gr7 = gr7 + gr5;
    ar5 = gr7;		//result addr + height

	ar4 = ar1;		//result addr saved

	delayed goto Con2;
		gr1 = gr5;
    	gr1 = gr1 << 1; //height * 2
Cycle:
	rep 32 data = [ar3++] with vsum , data, ;
	rep 32 data = [ar0++] with mask ram, data, afifo;
	rep 32 [ar1++gr1] = afifo;

	ar3 = gr3;
    ar0 = ar6;
    ar1 = ar5;
	rep 32 data = [ar0++] with vsum , data, ;
	rep 32 data = [ar3++] with mask ram, afifo, data;
	rep 32 [ar1++gr1] = afifo;

    ar5 = ar1;
	gr7 = ar1;		//optimize by switching operations
    gr7 = gr7 - gr5;
	ar1 = gr7;
Con2:
    gr4--;
    if >= delayed goto Cycle;
		ar6 = ar0;
		gr3 = ar3;

	ar2 = Transpose_rep_mask_mark;
	gr2 = gr6;
	gr2 = gr2 << 26;
	gr2 = gr2 >> 27;
	if =0 delayed goto RET_MACRO_MASK;
		gr2--;
		gr2 <<= 4;
	ar2 += gr2;
    goto ar2;		//goto rep (W % 64) / 2

RET_MACRO_MASK:
	gr7 = Masks;
	rep 32 ram = [gr7];
	ar6 = ar3;
	ar0 = ar3;
    gr3 = ar0;
    gr3 = gr3 + gr6;
    ar3 = gr3;
    ar4 = ar4 + 2;
	ar1 = ar4;
	gr7 = ar1;
    gr7 = gr7 + gr5;
    ar5 = gr7;
	gr0--;
	if > delayed goto Con2;
		gr4 = gr6;
		gr4 = gr4 >> 6;

	goto End;

Columns:
    gr2 = gr2 >> 1; //counter for columns

    gr4 = gr5;
    gr4 = gr4 >> 6; //counter for lines-reps

	//save addr
    ar5 = ar0;
    //set step
    gr0 = gr1;
    gr0 = gr0 << 1;

	//saved addr + width
    gr7 = ar0;
	gr7 = gr7 + gr1;
    ar3 = gr7;
    //set step
	gr3 = gr0;

    gr7 = ar1;
	gr7 = gr7 + gr5;
    ar4 = gr7;

	gr7 = ar0;

	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
	goto Con1;
Loop:
    rep 8 wfifo = [ar2++],ftw, wtw;

	rep 32 data = [ar0++gr0], ftw with vsum , data, ;
	wtw;
	rep 32 data = [ar3++gr3], ftw with vsum , data, afifo;
	rep 32 [ar1++] = afifo, wtw;

	ar0 = gr7;
	gr7 = gr7 + gr1;
	ar3 = gr7;
	rep 32 data = [ar3++gr3], ftw with vsum , data, ;
	wtw;
	rep 32 data = [ar0++gr0] with vsum , data, afifo;
	rep 32 [ar4++] = afifo;

	gr7 = ar0;
Con1:
	gr4--;
    if >= delayed goto Loop;
		ar2 = Matrix_gen;

	ar6 = Transpose_rep_mark;
	gr6 = gr5;
	gr6 = gr6 << 26;
	gr6 = gr6 >> 27;
	if =0 delayed goto RET_MACRO;
		gr6--;
		gr7 = gr6;
	gr6 <<= 4;
	gr7 <<= 1;
	gr6 = gr6 + gr7;
	ar6 += gr6;
	gr7 = ar0;
    goto ar6;		//goto rep (H % 64) / 2
		
RET_MACRO:
	ar1 = ar4;
    gr7 = ar4;
    gr7 = gr7 + gr5;
    ar4 = gr7;
	ar5 = ar5 + 2;
	ar0 = ar5;
	gr7 = ar0;
	gr7 = gr7 + gr1;
	ar3 = gr7;
	gr7 = ar0;
	gr2--;
	if > delayed goto Con1;
		gr4 = gr5;
		gr4 = gr4 >> 6;

	goto End;

Transpose_rep_mark:
	Transpose_rep 1
	Transpose_rep 2
	Transpose_rep 3
	Transpose_rep 4
	Transpose_rep 5
	Transpose_rep 6
	Transpose_rep 7
	Transpose_rep 8
	Transpose_rep 9
	Transpose_rep 10
	Transpose_rep 11
	Transpose_rep 12
	Transpose_rep 13
	Transpose_rep 14
	Transpose_rep 15
	Transpose_rep 16
	Transpose_rep 17
	Transpose_rep 18
	Transpose_rep 19
	Transpose_rep 20
	Transpose_rep 21
	Transpose_rep 22
	Transpose_rep 23
	Transpose_rep 24
	Transpose_rep 25
	Transpose_rep 26
	Transpose_rep 27
	Transpose_rep 28
	Transpose_rep 29
	Transpose_rep 30
	Transpose_rep 31
Transpose_rep_mask_mark:
    Transpose_rep_mask 1
    Transpose_rep_mask 2
	Transpose_rep_mask 3
	Transpose_rep_mask 4
	Transpose_rep_mask 5
	Transpose_rep_mask 6
	Transpose_rep_mask 7
	Transpose_rep_mask 8
	Transpose_rep_mask 9
	Transpose_rep_mask 10
	Transpose_rep_mask 11
	Transpose_rep_mask 12
	Transpose_rep_mask 13
	Transpose_rep_mask 14
	Transpose_rep_mask 15
	Transpose_rep_mask 16
	Transpose_rep_mask 17
	Transpose_rep_mask 18
	Transpose_rep_mask 19
	Transpose_rep_mask 20
	Transpose_rep_mask 21
	Transpose_rep_mask 22
	Transpose_rep_mask 23
	Transpose_rep_mask 24
	Transpose_rep_mask 25
	Transpose_rep_mask 26
	Transpose_rep_mask 27
	Transpose_rep_mask 28
	Transpose_rep_mask 29
	Transpose_rep_mask 30
	Transpose_rep_mask 31

End:
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
    pop ar2, gr2;
	pop ar1, gr1;
    pop ar0, gr0;
	return;
