.global _nmppsMulMM_2s32s_2col
.global _nmppsMulMM_2s16s_4col

.macro SET reg,val
#if __NM4__== 0
	\reg = \val;
#else
	sir = \val;
	\reg = sir;
#endif
.endm

.section .data.imu0
	.align 3

.macro MULMM_REP N
	gr5 =2 with gr3;
	if =0 delayed goto EndLoopW_f_rep\@ with gr3--;
		rep 32 wfifo=[ar1++gr1], ftw, wtw;
		rep \N data=[ar0++gr0] with vsum, data, 0;
	
	LoopW_f_rep\@:
		ar0 = ar5;
		ar5 += gr5;
		if > delayed goto LoopW_f_rep\@ with gr3--;
			rep 32 wfifo=[ar1++gr1], ftw, wtw;
			rep \N data=[ar0++gr0] with vsum, data, afifo;
		
	EndLoopW_f_rep\@:
	delayed goto End;
		rep \N [ar2++gr2] = afifo;
		nul;
.endm

MulMM_Common:
	SET sb, 0xaaaaaaaa
	
	gr0 = gr1 >> 4; // W/16 смещение

	gr3 = gr1 >> 5; // W/32

	gr1 = gr2;

	ar3 = ar0 with gr3--;
	gr4 = gr3;
	gr7 = gr5 >> 5; // H/32
	ar5 = ar1;

	LoopH_f:
		if =0 goto EndLoopH_f;
		ar0 = ar3;
		rep 32 wfifo=[ar1++gr1], ftw, wtw;
		rep 32 data=[ar0++gr0] with vsum, data, 0;
		with gr3;
		ar3 += 2;
		LoopW_f:
			if =0  goto EndLoopW_f;
			ar0 = ar3;
			rep 32 wfifo=[ar1++gr1], ftw, wtw;
			rep 32 data=[ar0++gr0] with vsum, data, afifo;
			delayed goto LoopW_f with gr3--;
				ar3 += 2;
		EndLoopW_f:

		rep 32 [ar2++gr2] = afifo;

		ar1 = ar5;
		gr3 = gr4;

		gr0 = -gr0;
		ar3 = ar0+gr0;
		gr0 = -gr0;

		delayed goto LoopH_f with gr7--;
			ar3 += 2;
	EndLoopH_f:

	ar4 = MulMM_rep1; // адрес перехода

	gr5 <<= 27;
	gr4 = gr5 >> 27; // H%32
	if =0 goto End;
	
	gr4--;
	gr4 <<= 4;
	ar4 += gr4;


	ar0 = ar3;
	ar3 += 2;

	ar5 = ar3;

	goto ar4;
	MulMM_rep1:
	MULMM_REP 1
	MULMM_REP 2
	MULMM_REP 3
	MULMM_REP 4
	MULMM_REP 5
	MULMM_REP 6
	MULMM_REP 7
	MULMM_REP 8
	MULMM_REP 9
	MULMM_REP 10
	MULMM_REP 11
	MULMM_REP 12
	MULMM_REP 13
	MULMM_REP 14
	MULMM_REP 15
	MULMM_REP 16
	MULMM_REP 17
	MULMM_REP 18
	MULMM_REP 19
	MULMM_REP 20
	MULMM_REP 21
	MULMM_REP 22
	MULMM_REP 23
	MULMM_REP 24
	MULMM_REP 25
	MULMM_REP 26
	MULMM_REP 27
	MULMM_REP 28
	MULMM_REP 29
	MULMM_REP 30
	MULMM_REP 31

	End:
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;

//************************************************
_nmppsMulMM_2s32s_2col:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	
	ar0 = [--ar5]; // * A
	gr5 = [--ar5]; // H
	gr1 = [--ar5]; // W1
	ar1 = [--ar5]; // * B
	ar2 = [--ar5]; // * C
	gr2 = [--ar5]; // W2

	SET nb1, 0x80000000
	goto MulMM_Common;

//************************************************
_nmppsMulMM_2s16s_4col:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	
	ar0 = [--ar5]; // * A
	gr5 = [--ar5]; // H
	gr1 = [--ar5]; // W1
	ar1 = [--ar5]; // * B
	ar2 = [--ar5]; // * C
	gr2 = [--ar5]; // W2
	gr2 A>>= 1;

	SET nb1, 0x80008000
	goto MulMM_Common;