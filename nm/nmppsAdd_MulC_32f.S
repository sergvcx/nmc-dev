.global _nmppsAdd_MulC_32f

.section .text.MyCode
_nmppsAdd_MulC_32f:
    ar5 = ar7 - 2;
	push ar0, gr0; 	// srcVec1
	push ar1, gr1;	// srcVec2
	push ar2, gr2;	// dstVec
	push ar3, gr3;	// nVal

    ar0 = [--ar5];
    ar1 = [--ar5];
    ar2 = [--ar5];
    ar3 = [--ar5];
    gr7 = [--ar5];  // srcCount
    gr7 = gr7 >> 6;
    gr0 = gr7;

    goto condition;
loopRep32:
    fpu 0 rep 32 vreg0 = [ar0++];
    fpu 0 rep 32 vreg1 = [ar1++];
    fpu 0 rep 1 vreg3 = [ar3];
    fpu 0 .float vreg2 = vreg0 + vreg1;
    fpu 0 .float vreg2 = vreg2 * .retrive(vreg3);
    fpu 0 rep 32 [ar2++] = vreg2;
condition:
    gr7--;
    if >= goto loopRep32;

    gr0 = gr0 << 26;
    gr0 = gr0 >> 27;
    gr0--;
    vlen = gr0;
    fpu 0 rep vlen vreg0 = [ar0++];
    fpu 0 rep vlen vreg1 = [ar1++];
    fpu 0 rep 1 vreg3 = [ar3];
    fpu 0 .float vreg2 = vreg0 + vreg1;
    fpu 0 .float vreg2 = vreg2 * .retrive(vreg3);
    fpu 0 rep vlen [ar2++] = vreg2;

	pop ar3, gr3;
    pop ar2, gr2;
	pop ar1, gr1;
    pop ar0, gr0;
	return;
