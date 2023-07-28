//------------------------------------------------------------------------
//
//  Neuro Matrix Performance Primitives
//
//  Copyright (c) RC Module
//
//
//! \if file_doc
//!
//! \file   nmppsDecimate.asm
//! \author Иван Жиленков
//! \brief  
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmc.hs"
//void core_ClipMul4D4W4_AddVr(nmreg nb1, 
//								nmreg sb, 
//								nmreg F1CR, 
//								nmreg vr, 
//								nmreg ar0, nmreg gr0, 
//								nmreg ar1, nmreg gr1, 
//								nmreg ar2, nmreg gr2, 
//								nmreg ar3, nmreg gr3, 
//								nmreg ar4, nmreg gr4, 
//								nmreg gr5, 
//								nmreg ar6, nmreg gr6)

//void nmppsDecimate_16s(nm16s* pSrc, int startPos, int step, nm16s* pDst, int nSize);


.section .data.nmpp
 	.align 3
	weights: .quad       0x0000000000000001,0,0,0, \
						 0x0000000000010000,0,0,0, \
						 0x0000000100000000,0,0,0, \
						 0x0001000000000000,0,0,0, \
						  \
						 0,0x0000000000000001,0,0, \
						 0,0x0000000000010000,0,0, \
						 0,0x0000000100000000,0,0, \
						 0,0x0001000000000000,0,0, \
						  \
						 0,0,0x0000000000000001,0, \
						 0,0,0x0000000000010000,0, \
						 0,0,0x0000000100000000,0, \
						 0,0,0x0001000000000000,0, \
						  \
						 0,0,0,0x0000000000000001, \
						 0,0,0,0x0000000000010000, \
						 0,0,0,0x0000000100000000, \
						 0,0,0,0x0001000000000000

.section .text.nmpp
BRANCH
.global _nmppsDecimate_16s
_nmppsDecimate_16s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	
	ar0 = [--ar5]	with gr6 = false;	// pSrc
	SET vr gr6		//vr = 0
	gr4 = [--ar5]	with gr6++;			// startPos
	gr0 = [--ar5]	with gr6++;			// step
	ar6 = [--ar5]	with gr0 >>=1;		// pDst
	gr5 = [--ar5]	with gr4 <<=5;		// nSize
		
	SET nb1 80008000h	
	SET sb  00020002h
	SET f1cr 80008000h
	wtw;
	with gr5>>=2; 
	ar4 = weights with gr1 = gr0;
	ar1 = ar0 + gr0 	with gr2 = gr1;
	ar2 = ar1 + gr1 	with gr3 = gr2<<2;	
	delayed call core_ClipMul4D4W4_AddVr	with gr0<<=2;
		ar3 = ar2 + gr2 with gr1<<=2;
		ar4 += gr4		with gr2<<=2;
	
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;

	return;
WAIT
