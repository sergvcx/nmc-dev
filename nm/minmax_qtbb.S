.global _nmppsMinMax_8s
.global _nmppsMinMax_16s
.global _nmppsMinMax_32s
.global _nmppsMinMax_64s

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

.section .data.imu1
	.align 3

.section .data.imu2
	.align 3

.text
nmppsMinMax:
	gr4 = gr7;
	gr7 = gr7 >> 5; // size/n/32
	gr2 = Loop;
	gr1 = ar1;
	ar4 = ar3;
	ar5 = ar3;
	Loop:
	if <= goto EndLoop;
		rep 32 ram=[ar0++];
		rep 32 data=[ar1++] with data - ram;
		ar1 = gr1;
		rep 32 [ar4++] = afifo with 0 or activate afifo;
		rep 32 data=[ar1++]  with mask afifo, data, ram;
		rep 32 [ar2++]=afifo;
		ar1 = gr1;
		rep 32 data = [ar5++] with 0 or activate data;
		rep 32 data=[ar1++] with mask afifo, ram, data;
	delayed goto gr2 with gr7--;
		gr1 = ar1;
		rep 32 [ar3++]=afifo;
		nul;
	EndLoop:

	gr4 <<= 27;
	gr4 >>= 27;

	Loop2:
	if <= goto EndLoop2;
		rep 1 ram=[ar0++];
		rep 1 data=[ar1] with data - ram;
		rep 1 [ar3]=afifo with 0 or activate afifo;
		rep 1 data=[ar1] with mask afifo, data, ram;
		rep 1 [ar2++] = afifo;
		rep 1 data=[ar3] with 0 or activate data;
		rep 1 data=[ar1++] with mask afifo, ram, data;
		rep 1 [ar3++]=afifo;
	goto Loop2 with gr4--;
	EndLoop2:
	return;

_nmppsMinMax_64s:
	SET nb1, 0x0
	wtw;
	//SET f1cr, 0x0
	//SET f2cr, 0x0
	sir = 0x80000000;
	f1crh= sir;
	f2crh= sir;
	sir =0;
	f1crl = sir;
	f2crl = sir;


	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	
	ar0 = [--ar5]; // * a
	ar1 = [--ar5]; // * b
	ar2 = [--ar5]; // * a_res
	ar3 = [--ar5]; // * b_res

	gr7 = [--ar5]; // size
	
	call nmppsMinMax;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;

_nmppsMinMax_32s:
	SET nb1, 0x80000000
	wtw;
	SET f1cr, 0x80000000
	SET f2cr, 0x80000000

	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	
	ar0 = [--ar5]; // * a
	ar1 = [--ar5]; // * b
	ar2 = [--ar5]; // * a_res
	ar3 = [--ar5]; // * b_res

	gr7 = [--ar5];  // size
	gr7 = gr7 >> 1; // size/2
	
	call nmppsMinMax;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;

_nmppsMinMax_16s:
	SET nb1, 0x80008000
	wtw;
	SET f1cr, 0x80008000
	SET f2cr, 0x80008000

	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	
	ar0 = [--ar5]; // * a
	ar1 = [--ar5]; // * b
	ar2 = [--ar5]; // * a_res
	ar3 = [--ar5]; // * b_res

	gr7 = [--ar5];  // size
	gr7 = gr7 >> 2; // size/2
	
	call nmppsMinMax;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;

_nmppsMinMax_8s:
	SET nb1, 0x80808080
	wtw;
	SET f1cr, 0x80808080
	SET f2cr, 0x80808080

	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	
	ar0 = [--ar5]; // * a
	ar1 = [--ar5]; // * b
	ar2 = [--ar5]; // * a_res
	ar3 = [--ar5]; // * b_res

	gr7 = [--ar5];  // size
	gr7 = gr7 >> 3; // size/2
	
	call nmppsMinMax;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
