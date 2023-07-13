.global _minMax
.global _minMaxMas
.global _logMinMaxMas
	
.text
_minMax:
	ar5 = ar7 - 2;
    push ar1, gr1;
	ar1 = [--ar5];
	gr1 = [ar1];
	ar5 = [--ar5];
	gr7 = [ar5];
	with gr1 - gr7;
	if < goto _END;
	
	
	[ar1] = gr7;
	[ar5] = gr1;
_END:
	pop ar1, gr1;
    return;

_minMaxMas:
	ar5 = ar7 - 2;
    push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5];
	ar1 = [--ar5];
	gr7 = [--ar5];
	//ar2 = ar0;
	//ar3 = ar1;
	gr0 = [ar0++];
	gr1 = [ar1++];
	
Loop:
	with gr0 - gr1;
	if < goto CON with gr7--;
	
	
	[--ar0] = gr1;
	[--ar1] = gr0;
	ar0++;//=gr0;
	ar1++;//=gr1;
CON:
	
	if > delayed goto Loop;
		gr0 = [ar0++];
		gr1 = [ar1++];
	
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
    return;
	
_logMinMaxMas: // 20 ticks per minmax
	ar5 = ar7 - 2;
	push ar5, gr5;
	push ar4, gr4;
    push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar0 = [--ar5];
	ar1 = [--ar5];
	gr7 = [--ar5];
	
	gr0 = [ar0];
	gr1 = [ar1];
	gr2 = gr0 - gr1;
	gr2 = gr2 A>> 31;
Cycle:
	gr5 = gr1 xor gr0;
	gr3 = not gr2 and gr0;
	gr4 = gr2 and gr1;
	gr3 = gr3 or gr4;
	[ar1++] = gr3 with gr3 = gr5 xor gr3;
	[ar0++] = gr3;
		
	gr0 = [ar0];
	gr1 = [ar1] with 	gr7--;
//Condition:
	if > delayed goto Cycle;
		gr2 = gr0 - gr1;
		gr2 = gr2 A>> 31;
//Exit:
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
    return;