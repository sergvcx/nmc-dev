.global _nmppsSub_Abs_Even_32f

.p2align 3	
.data
	Matrix_1:
		.quad 0x0000000000000001
        .quad 0x0000000000000000
    Matrix_2:
		.quad 0x0000000100000000
        .quad 0x0000000000000000

.section .text.MyCode
_nmppsSub_Abs_Even_32f:
    ar5 = ar7 - 2;
	push ar0, gr0; 	// srcVec1
	push ar1, gr1;	// srcVec2
	push ar2, gr2;	// dstVec
    push ar3, gr3;  // srcVec1 + 2
    push ar4, gr4;  // srcVec2 + 2
    push ar6, gr6;  // matrix addr

    ar0 = [--ar5];
    gr0 = 4;
    ar3 = ar0 + 2;
    gr3 = gr0;
   
    ar1 = [--ar5];
    gr1 = gr0;
    ar4 = ar1 + 2;
    gr4 = gr0;
   
    ar2 = [--ar5];
   
    ar6 = Matrix_1;
    gr6 = Matrix_2;
    
    fpu 0 rep 1 vreg6 = [ar6++];
    fpu 0 rep 1 vreg7 = [ar6];
    fpu 0 rep 1 vreg4 = [gr6++];
    fpu 0 rep 1 vreg5 = [gr6];

    fpu 1 rep 1 vreg6 = fpu 0 vreg6;
    fpu 1 rep 1 vreg7 = fpu 0 vreg7;
    fpu 1 rep 1 vreg4 = fpu 0 vreg4;
    fpu 1 rep 1 vreg5 = fpu 0 vreg5;
    
    gr7 = [--ar5];  // srcCount
    gr7 = gr7 >> 7;
    gr2 = gr7;

    goto condition;
loopRep32:
    fpu 0 rep 32 vreg0 = [ar0++gr0];
    fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg4, vreg5);
    fpu 0 rep 32 vreg2 = [ar3++gr3];
    fpu 0 .matrix vreg3 = vreg2 * .retrive(vreg6, vreg7);
    fpu 0 .float vreg3 = vreg1 + vreg3;
    
    fpu 1 rep 32 vreg0 = [ar1++gr1];
    fpu 1 .matrix vreg1 = vreg0 * .retrive(vreg4, vreg5);
    fpu 1 rep 32 vreg2 = [ar4++gr4];
    fpu 1 .matrix vreg3 = vreg2 * .retrive(vreg6, vreg7);
    fpu 1 .float vreg3 = vreg1 + vreg3;

    fpu 0 vreg1 = fpu 1 vreg3;
    fpu 0 .float vreg2 = vreg0 - vreg1;
    fpu 0 .float vreg2 = /vreg2/;
    fpu 0 rep 32 [ar2++] = vreg2;
condition:
    gr7--;
    if >= goto loopRep32;

    gr2 = gr2 << 25;
    gr2 = gr2 >> 26;    //кратно 4 
    vlen = gr2;
    fpu 0 vlen vreg0 = [ar0++gr0];
    fpu 0 .matrix vreg1 = vreg0 * .retrive(vreg4, vreg5);
    fpu 0 vlen vreg2 = [ar3++gr3];
    fpu 0 .matrix vreg3 = vreg2 * .retrive(vreg6, vreg7);
    fpu 0 .float vreg3 = vreg1 + vreg3;
    
    fpu 1 vlen vreg0 = [ar1++gr1];
    fpu 1 .matrix vreg1 = vreg0 * .retrive(vreg4, vreg5);
    fpu 1 vlen vreg2 = [ar4++gr4];
    fpu 1 .matrix vreg3 = vreg2 * .retrive(vreg6, vreg7);
    fpu 1 .float vreg3 = vreg1 + vreg3;

    fpu 0 vreg1 = fpu 1 vreg3;
    fpu 0 .float vreg2 = vreg0 - vreg1;
    fpu 0 .float vreg2 = /vreg2/;
    fpu 0 vlen [ar2++] = vreg2;

    pop ar4, gr4;
    pop ar3, gr3;
    pop ar2, gr2;
	pop ar1, gr1;
    pop ar0, gr0;
	return;
