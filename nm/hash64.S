.global _nmppsHash64u

.section .data.imu3
	Tmp: .quad 0x0000000000000000
	MatrHash: .quad	0x0000000000000001
	Tmp32: .space 62<<3

.macro SET reg,val
#if __NM4__== 0
	\reg = \val;
#else
	sir = \val;
	\reg = sir;
#endif
.endm

.text
_nmppsHash64u:
	ar5 = ar7 - 2;								// сохраняется указатель стека
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;

	ar0 = [--ar5];								// адрес входного параметра
	gr1 = [--ar5];								// размер массива

	SET nb1, 0									// разбиение по 64 разряда
	SET sb, 0									// разбиение на 1 строку

	ar5 = MatrHash with gr0 = gr1>>5;
	rep 1 wfifo = [ar5], ftw, wtw;
	ar1 = Tmp32;								// адрес временного массива
	ar2 = ar1;
	ar5 = Tmp;									// адрес промежуточного результата

	rep 32 data = [ar5] with data xor data;		// начальный afifo

	with gr0;
	if =0 goto EndLoop with gr0--;
	Loop:
	if > delayed goto Loop with gr0--;
		rep 32 data=[ar0++] with vsum, shift afifo, data;
		nul;
	EndLoop:

	rep 32 [ar1++]=afifo;						// запись временного массива
	ar1 = ar2;

	gr3 = 4;
	gr4 = gr3;
	ar3 = ar2;
	ar4 = ar3;
	ar4++;
	ar4++;
	rep 16 ram = [ar3++gr3];
	ar1 = ar3;
	rep 16 data = [ar4++gr4] with ram + data;
	rep 16 [ar3++] = afifo;
	ar3 = ar1;
	rep 8 ram = [ar3++gr3];
	ar1 = ar3;
	rep 8 data = [ar4++gr4] with ram + data;
	rep 8 [ar3++] = afifo;
	ar3 = ar1;
	rep 4 ram = [ar3++gr3];
	ar1 = ar3;
	rep 4 data = [ar4++gr4] with ram + data;
	rep 4 [ar3++] = afifo;
	ar3 = ar1;
	rep 2 ram = [ar3++gr3];
	ar1 = ar3;
	rep 2 data = [ar4++gr4] with ram + data;
	rep 2 [ar3++] = afifo;
	ar3 = ar1;
	rep 1 ram = [ar3++];
	rep 1 data = [ar3++] with ram + data;

	gr1 <<= 27;
	gr1 >>= 27;

	Loop1:
	if <= goto EndLoop1;
	delayed goto Loop1;
		rep 1 data=[ar0++] with vsum, shift afifo, data;
		with gr1--;
	EndLoop1:

	rep 1 [ar5] = afifo;
	gr7 = [ar5++];
	gr6 = [ar5++];

	gr7 = gr7 + gr6;

	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;
