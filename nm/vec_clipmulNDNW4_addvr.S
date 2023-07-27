//------------------------------------------------------------------------
//
//  $Workfile:: FilterCoreRow02.asm             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//
//! \if file_doc
//!
//! \author S. Mushkaev
//!
//! \endif
//!
//------------------------------------------------------------------------


#include "nmc.hs"


#define TAIL_REP(N) tail_rep N
.macro tail_rep N
	rep \N data=[ar0++gr0] with vsum ,activate data, vr;
	nul;
	Next_Block\@:
		gr2 = [ar1++] with gr1--;	// Read next disp
		ar0 = ar2 + gr2;			// Set next pointer
		wtw;
		nul;
	if > delayed goto Next_Block\@;
		rep \N data=[ar0++gr0] with vsum ,activate data,afifo;
		rep 4 wfifo=[ar4++],ftw;

	//<Last_Block>
	gr2 = [ar1++];					// Read last disp
	ar0 = ar2 + gr2;				// Set last pointer, Dec packet counter
	delayed return;
		wtw;
		rep \N data=[ar0++gr0] with vsum ,activate data,afifo;
		rep \N [ar6++gr6]=afifo;		// Output result
.endm tail_rep;

/////////////////////////////////////////////////////////////////////////////////////////
// Core Weight summation of several vectors
/////////////////////////////////////////////////////////////////////////////////////////
//		ar0			First Input Buffer		
//		gr0			Input Buffer Stride for ar0		
//		ar1			Array of displacements from First Input Buffer
//		gr1			Number input buffers (must 3 or grater)
//		ar4			WeightBuffer				
//		gr4			nb1							
//		gr5			Input buffer size in longs
//		ar6			Ouput Buffer
//		gr6			Output Buffer Stride	
//		nb1	
//		sb
//		vr
//		f1cr
/////////////////////////////////////////////////////////////////////////////////////////

//#define AR_1 ar5
//#define AR_2 gr5
//#define AR_4 ar3
//#define GR_1 gr3
    //------------------------------------------------------------------------
    //! \fn void core_ClipMulNDNW4_AddVr(nmreg nb1, nmreg sb, nmreg f1cr, nmreg vr, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg ar4, nmreg gr4, nmreg gr5, nmreg ar6, nmreg gr6);
    //!			 
    //------------------------------------------------------------------------
.section .text.nmpp.core
core_ClipMulNDNW4_AddVr:
BRANCH

	push ar5,gr5;
	ar3 = ar4 with gr7 = gr5>>5;	// Store pointer to weight array  
									// Count of blocks by rep 32
	rep 4 wfifo=[ar4++],ftw,wtw;	// preload matrix for First_vsum

	ar5 = ar1 with gr3 = gr1 noflags;// Store pointer to array of displacemts
									// Store number of arrays
	gr5 = ar0;						// Anchor pointer
//	ar1 = ar5;						// Restore pointer to array of displacemts
//	gr1 = gr3;						// Restore number of arrays
	gr2 = [ar1++] with gr1--;		// Read first disp   , Dec number of arrays
	ar2 = gr5	  with gr1--;		// Restore anchor pointer Dec number of arrays
	ar0 = ar2 + gr2 with gr7 ;		// Set  first pointer, 

	if =0 delayed goto Rep_N;
		rep 4 wfifo=[ar4++],ftw;		// Preload matrix for Next_vsum
		nul;
	Next_Packet:
		// <First_Block>
		rep 32 data=[ar0++gr0] with vsum ,activate data, vr;
		gr5 = ar0;						// Store new anchor pointer
		gr5-= gr2;
		Next_Block:
			gr2 = [ar1++] with gr1--;	// Read next disp
			ar0 = ar2 + gr2;			// Set next pointer
			wtw;
			nul;
		if > delayed goto Next_Block;
			rep 32 data=[ar0++gr0] with vsum ,activate data,afifo;
			rep 4 wfifo=[ar4++],ftw;

		//<Last_Block>
		ar4 = ar3;						// Restore pointer to weight array  
		gr2 = [ar1++];					// Read last disp
		ar0 = ar2 + gr2 with gr7--;		// Set last pointer, Dec packet counter
		wtw;
		rep 32 data=[ar0++gr0] with vsum ,activate data,afifo;
		rep 4 wfifo=[ar4++],ftw;		// Preload matrix for First_Block
		//<First_Block>
		ar1 = ar5;						// Restore pointer to array of displacemts
		ar2 = gr5 with	gr1 = gr3 noflags;				// Restore anchor pointer
										// Restore number of arrays
		gr2 = [ar1++]   with gr1=gr1 - 1 noflags;		// Read first disp   , Dec number of arrays
		ar0 = ar2 + gr2 with gr1=gr1 - 1 noflags;		// Set  first pointer, Dec number of arrays
		wtw;
	if > delayed goto Next_Packet;
		rep 4 wfifo=[ar4++],ftw;		// Preload matrix for Next_Block
		rep 32 [ar6++gr6]=afifo;		// Output result


	Rep_N:
//local Start:label;
	pop ar5,gr5;	// restore size
	gr3 = gr5 << 27 ;//(32-5);
	ar3 = TailRep0 with gr3>>=23 ;//32-10+1;
	///gr3>>=32-10;
	
	ar3 += gr3;
	if >= delayed goto ar3;
		nul;
		nul;
TailRep0:
	delayed return;
		wtw;
		nul;
		nul;
	.rept 12;
		nul;
	.endr;

	TAIL_REP(1)
	TAIL_REP(2)
	TAIL_REP(3)
	TAIL_REP(4)
	TAIL_REP(5)
	TAIL_REP(6)
	TAIL_REP(7)
	TAIL_REP(8)
	TAIL_REP(9)
	TAIL_REP(10)
	TAIL_REP(11)
	TAIL_REP(12)
	TAIL_REP(13)
	TAIL_REP(14)
	TAIL_REP(15)
	TAIL_REP(16)
	TAIL_REP(17)
	TAIL_REP(18)
	TAIL_REP(19)
	TAIL_REP(20)
	TAIL_REP(21)
	TAIL_REP(22)
	TAIL_REP(23)
	TAIL_REP(24)
	TAIL_REP(25)
	TAIL_REP(26)
	TAIL_REP(27)
	TAIL_REP(28)
	TAIL_REP(29)
	TAIL_REP(30)
	TAIL_REP(31)


WAIT
