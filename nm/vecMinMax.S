.global _vecMinMaxMas
.global _vecMinMaxRep32
#include "printx.hs"

.section .bss.MyData1
    .align 8
	.global A
	A:  .space  64<<2

//----------------------------------------------------------------------------------time per elem ~23+
.section .text.AAA
_vecMinMaxMas:
	ar5 = ar7 - 2;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar1 = [--ar5];
	ar2 = [--ar5];
	gr7 = [--ar5];	//counter
	gr7 = gr7 >> 1;
	ar5 = A;
	
	sir = 80000000h;
	nb1 = sir;
    	wtw;
	
	sir = 80000000h;
	f1cr = sir;
    
	sir = 80000000h;
	f2cr = sir;
    
Loop:
	rep 1 ram = [ar2];									// ram = b
	
	rep 1 data = [ar1] with data - ram;					// data = a, afifo = a - b
	rep 1 with activate afifo or 0; 					// afifo = (a - b) A>> 31
	
	rep 1 data = [ar1] with mask afifo, data, ram;		// afifo = min
	rep 1 [ar5] = afifo;  								// temp_a = min
	
	rep 1 data = [ar1] with data - ram;
	rep 1 with activate afifo or 0;
	
	rep 1 data = [ar1] with mask afifo, ram, data;		// afifo = max
	rep 1 [ar2++] = afifo;								// b = max
	
	//rep 1 data = [ar5++] with data;
	//rep 1 [ar1++] = afifo;
	ar0,gr0 = [ar5++];									// a = min
	[ar1++] = ar0,gr0;
	gr7--;
	if > delayed goto Loop;
	nul;
	nul;
	
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	
	//PRINTF("Output\: \n")
	//PRINTF1("A addr =%X\n",ar2)
	//PRINTF1("A val =%d\n",[ar2])
	
	return;
	
//-----------------------------------------------------------------------------time per elem ~5.8
_vecMinMaxRep32:
	ar5 = ar7 - 2;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	//push ar0, gr0;
	ar1 = [--ar5]; 		//adr a
	ar2 = [--ar5];		//adr b
	gr7 = [--ar5];
	gr3 = 1 << 6;
	gr3 = gr3 - 1;
	gr3 = gr3 and gr7;
	gr3 = gr3 >> 1;
	gr3 = gr3 + 1;		//counter for rep 1
	gr7 = gr7 >> 6;		
	gr7++;				//counter for rep 32
	ar4, gr4 = A;
	
	sir = 80000000h;
	nb1 = sir;
    	wtw;
	sir = 80000000h;
	f1cr = sir;
	sir = 80000000h;
	f2cr = sir;
    
	goto Condition_32;
Cycle_32:
	rep 32 ram = [ar2++];									// ram = b
	
	rep 32 data = [ar1++] with data - ram;					// data = a, afifo = a - b
	rep 32 with activate afifo or 0; 						// afifo = (a - b) A>> 31
	
	ar1 = gr1;
	rep 32 data = [ar1++] with mask afifo, data, ram;		// afifo = min
	rep 32 [ar4++] = afifo;  								// temp_a = min
	
	ar1 = gr1;
	rep 32 data = [ar1++] with data - ram;
	rep 32 with activate afifo or 0;
	
	ar1 = gr1;
	ar2 = gr2;
	rep 32 data = [ar1++] with mask afifo, ram, data;		// afifo = max
	rep 32 [ar2++] = afifo;									// b = max
	
	ar1 = gr1;
	ar4 = gr4;
	rep 32 data = [ar4++] with data;						//min -> a
	rep 32 [ar1++] = afifo;
	ar4 = gr4;
Condition_32:
	gr7--;
	if > delayed goto Cycle_32;
	gr1 = ar1;
	gr2 = ar2;
	
	ar2++;
	goto Condition_1;
Cycle_1:
	rep 1 ram = [ar2];									// ram = b
	
	rep 1 data = [ar1] with data - ram;					// data = a, afifo = a - b
	rep 1 with activate afifo or 0; 					// afifo = (a - b) A>> 31
	
	rep 1 data = [ar1] with mask afifo, data, ram;		// afifo = min
	rep 1 [ar4] = afifo;  								// temp_a = min
	
	rep 1 data = [ar1] with data - ram;
	rep 1 with activate afifo or 0;
	
	rep 1 data = [ar1] with mask afifo, ram, data;		// afifo = max
	rep 1 [ar2++] = afifo;								// b = max
	
	rep 1 data = [ar4++] with data;
	rep 1 [ar1++] = afifo;
	//ar0,gr0 = [ar4++];									// a = min
	//[ar1++] = ar0,gr0;
Condition_1:
	gr3--;
	if > delayed goto Cycle_1;
	nul;
	nul;
	
	//pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	
	return;
