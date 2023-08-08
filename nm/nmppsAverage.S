.global _nmppsAverage

.p2align 3	
.data
	constForAverage:
		.quad 0x3F0000003F000000

.section .text.MyCode
_nmppsAverage:
    ar5 = ar7 - 2;
	push ar0, gr0; 	//
	push ar1, gr1;	//
	push ar2, gr2;	//
	push ar3, gr3;	//
	push ar4, gr4;	//
    push ar5, gr5;  //
	push ar6, gr6;  //

    ar0 = [--ar5];
    ar1 = [--ar5];
    ar2 = [--ar5];
    gr7 = [--ar5];
    gr7 = gr7 >> 6;
    gr0 = gr7;
    ar3 = constForAverage;

    goto condition;
loop_rep32:
    fpu 0 rep 32 vreg0 = [ar0++];
    fpu 0 rep 32 vreg1 = [ar1++];
    fpu 0 rep 32 vreg3 = [ar3];
    fpu 0 .float vreg2 = vreg0 + vreg1;
    fpu 0 .float vreg2 = vreg2 * vreg3;
    fpu 0 rep 32 [ar2++] = vreg2;
condition:
    gr7--;
    if >= goto loop_rep32;

    gr0 = gr0 << 26;
    gr0 = gr0 >> 27;
    gr0--;
    vlen = gr0;
    fpu 0 rep vlen vreg0 = [ar0++];
    fpu 0 rep vlen vreg1 = [ar1++];
    fpu 0 rep vlen vreg3 = [ar3];
    fpu 0 .float vreg2 = vreg0 + vreg1;
    fpu 0 .float vreg2 = vreg2 * vreg3;
    fpu 0 rep vlen [ar2++] = vreg2;

	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
    pop ar2, gr2;
	pop ar1, gr1;
    pop ar0, gr0;
	return;
