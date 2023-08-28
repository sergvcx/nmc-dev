.global _nmppsAbs_32f
#include "printx.hs"

.section .text.MyCode
_nmppsAbs_32f:
    ar5 = ar7 - 2;
	push ar0, gr0; 	// srcVec1
	push ar1, gr1;	// dstVec

    ar0 = [--ar5];
    ar1 = [--ar5];
    gr7 = [--ar5];  // srcCount

    delayed goto loopRep32Condition;
    gr0 = gr7;
    gr7 = gr7 >> 6;
loopRep32:
    fpu 0 rep 32 vreg0 = [ar0++];
    fpu 0 .float vreg1 = /vreg0/;
    fpu 0 rep 32 [ar1++] = vreg1;
loopRep32Condition:
    gr7--;
    if >= goto loopRep32;
    
    gr0 = gr0 << 26;
    gr0 = gr0 >> 27;
    gr0--;
    if < goto endMark;
    vlen = gr0;
    fpu 0 rep vlen vreg0 = [ar0++];
    fpu 0 .float vreg1 = /vreg0/;
    fpu 0 rep vlen [ar1++] = vreg1;
endMark:
	pop ar1, gr1;
    pop ar0, gr0;
	return;
