.global _nmppmTranspose_32s

.p2align 3	
.data	//IMU_2
	Masks:
		.quad 0x00000000FFFFFFFF
	Matrix_2X2:
		.quad 0x0000000100000000
		.quad 0x0000000000000001
	Array_addr:
		.space 1<<2
	Res_addr:
		.space 1<<2

.macro Transpose_rep N
	rep \N ram = [ar5];
	rep \N data = [ar0++gr0] with vsum , data, ;			//input addr
	ar0 = ar3;
	rep \N data = [ar0++gr0] with mask ram, afifo, data;	//input addr + Width
	ar1 = ar2;
	rep \N [ar1++gr1] = afifo;								//output res + Height
	ar2 = ar1;

	ar0 = ar3;
	rep \N data = [ar0++gr0] with vsum , data, ;			//input addr + Width
	ar3 = ar0;
	ar6 = Array_addr;
	ar0 = [ar6];
	rep \N data = [ar0++gr0] with mask ram, data, afifo;	//input addr
	ar6 = Res_addr;
	delayed return;
		ar1 = [ar6];
		rep \N [ar1++gr1] = afifo;							//output res
		rep 32 ram = [ar5];
.endm

.section .text.MyCode
//-------------------------------------------------GENERAL---------------------1.264-per-elem
_nmppmTranspose_32s:
    ar5 = ar7 - 2;
	push ar0, gr0; 	//array addr			step
	push ar1, gr1;	//result addr			step
	push ar2, gr2;	//result addr + Height	counter1
	push ar3, gr3;	//array addr + Width	counter2
	push ar4, gr4;	//pointer				width
    push ar5, gr5;  //Masks addr			height
	push ar6, gr6;  //MACRO addr			shift

	ar0 = [--ar5];  //array addr
	ar6 = Array_addr;
	[ar6] = ar0;

	ar1 = [--ar5];  //result addr
	ar6 = Res_addr;
	[ar6] = ar1;

	gr5 = [--ar5];	//height
	gr4 = [--ar5];	//width

	sir = 80000000h;
	nb1 = sir;
	sir = 2h;
	sb = sir;
	ar2 = Matrix_2X2;
    rep 2 wfifo = [ar2++],ftw, wtw;
	ar5 = Masks;
	rep 32 ram = [ar5];

	gr7 = ar0;
    gr7 = gr7 + gr4;
    ar3 = gr7;      //array addr + width

	gr7 = ar1;
    gr7 = gr7 + gr5;
    ar2 = gr7;		//result addr + height

	gr7 = gr5 - gr4;
	if < goto Lines_to_Columns;

Columns_to_Lines:
	gr2 = gr4;
    gr2 = gr2 >> 1; //counter for columns

    gr3 = gr5;
    gr3 = gr3 >> 6; //counter for lines-reps

	gr1 = 2;		//res step = 2

	ar4 = ar0;		//pointer for addr

	delayed goto Condition_rep32;
		gr0 = gr4;
    	gr0 = gr0 << 1; //addr step = width * 2

Lines_to_Columns:
	gr2 = gr5;
    gr2 = gr2 >> 1; //counter for lines

    gr3 = gr4;
    gr3 = gr3 >> 6; //counter for columns-reps

	gr0 = 2;		//add step = 2

	ar4 = ar1;		//pointer for res

	delayed goto Condition_rep32;
		gr1 = gr5;
		gr1 = gr1 << 1; //res step = height * 2

Loop:
	rep 32 data = [ar0++gr0] with vsum , data, ;			//input addr
	ar0 = ar3;
	rep 32 data = [ar0++gr0] with mask ram, afifo, data;	//input addr + Width
	ar1 = ar2;
	rep 32 [ar1++gr1] = afifo;								//output res + Height
	ar2 = ar1;

	ar0 = ar3;
	rep 32 data = [ar0++gr0] with vsum , data, ;			//input addr + Width
	ar3 = ar0;
	ar6 = Array_addr;
	ar0 = [ar6];
	rep 32 data = [ar0++gr0] with mask ram, data, afifo;	//input addr
	[ar6] = ar0;
	ar6 = Res_addr;
    ar1 = [ar6];
	rep 32 [ar1++gr1] = afifo;								//output res
Condition_rep32:
    gr3--;
    if >= delayed goto Loop;
		[ar6] = ar1;
		nul;

	gr7 = gr5 - gr4;
	if < delayed goto Common_Tail;
		gr6 = gr4;
		nul;

Columns_Tail:
	gr6 = gr5;

Common_Tail:
	gr6 = gr6 << 26;
	gr6 = gr6 >> 27;
	if =0 delayed goto Iteration_End;
		gr6--;
		gr7 = gr6;
	gr6 <<= 4;
	gr7 <<= 2;
	gr6 = gr6 + gr7;
	ar6 = Transpose_rep_mark;
	ar6 += gr6;
	call ar6;
	
Iteration_End:
	gr7 = gr5 - gr4;
	if < delayed goto Lines_recovery;
		gr3 = gr4;
	    gr3 = gr3 >> 6;	//counter recover

Columns_recovery:
	gr3 = gr5;
    gr3 = gr3 >> 6;	//counter recover
	ar4 = ar4 + 2;
	delayed goto Common_recovery;
		ar0 = ar4;
		ar1 = ar2;

Lines_recovery:
	ar0 = ar3;
	ar4 = ar4 + 2;
	ar1 = ar4;

Common_recovery:
	gr7 = ar1;
	gr7 = gr7 + gr5;
	ar2 = gr7;
	ar6 = Array_addr;
	[ar6] = ar0;
	ar6 = Res_addr;
	[ar6] = ar1;
	gr7 = ar0;
	gr2--;
	if > delayed goto Condition_rep32;
		gr7 = gr7 + gr4;
		ar3 = gr7;

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
    pop ar2, gr2;
	pop ar1, gr1;
    pop ar0, gr0;
	return;

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
