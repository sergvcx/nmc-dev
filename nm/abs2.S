.global _nmppsAbs2_8s
.global _nmppsAbs2_16s
.global _nmppsAbs2_32s
.global _nmppsAbs2_64s

.section .data.imu1
	.align 3
	Matr8: .quad	0x00000000000000ff, \
					0x000000000000ff00, \
					0x0000000000ff0000, \
					0x00000000ff000000, \
					0x000000ff00000000, \
					0x0000ff0000000000, \
					0x00ff000000000000, \
					0xff00000000000000
	Matr16: .quad	0x000000000000ffff, \
					0x00000000ffff0000, \
					0x0000ffff00000000, \
					0xffff000000000000
	Matr32: .quad	0x00000000ffffffff, \
					0xffffffff00000000
	Matr64: .quad	0xffffffffffffffff

.macro SET reg,val
#if __NM4__== 0
	\reg = \val; 
#else
	sir = \val; 
	\reg = sir;
#endif
.endm

.text
Abs2:
	with gr0 = gr7>>5;			// gr0=size/n/32

	if =0 goto EndLoop with gr0--;
	Loop:
		rep 32 ram=[ar0++] with 0 or activate data;
		rep 32 with vsum afifo, ram, ram;
	if > delayed goto Loop with gr0--;
		rep 32 with activate afifo xor afifo;
		rep 32 [ar1++]=afifo;
	EndLoop:

	with gr7 <<= 27;			// gr7[4:0],0
	with gr7 >>= 27;			// 0,gr7[4:0]

	Loop2:
	if <= goto EndLoop2;
		rep 1 ram=[ar0++] with 0 or activate data;
		rep 1 with vsum afifo, ram, ram;
		rep 1 with activate afifo xor afifo;
	delayed goto Loop2;
		rep 1 [ar1++]=afifo;
		with gr7--;
	EndLoop2:
	return;


_nmppsAbs2_8s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	
	ar0 = [--ar5];				// * a
	ar1 = [--ar5];				// * b
	gr7 = [--ar5] with gr7>>=3;	// size/8

	SET nb1, 0x80808080
	SET sb, 0x2020202
	SET f1cr, 0x80808080
	SET f2cr, 0x80808080

	ar5 = Matr8;
	rep 8 wfifo = [ar5++], ftw, wtw;

	call Abs2;

	pop ar1, gr1;
	pop ar0, gr0;
	return;


_nmppsAbs2_16s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	
	ar0 = [--ar5];				// * a
	ar1 = [--ar5];				// * b
	gr7 = [--ar5] with gr7>>=2;	// size/4

	SET nb1, 0x80008000
	SET sb, 0x20002
	SET f1cr, 0x80008000
	SET f2cr, 0x80008000

	ar5 = Matr16;
	rep 4 wfifo = [ar5++], ftw, wtw;

	call Abs2;

	pop ar1, gr1;
	pop ar0, gr0;
	return;


_nmppsAbs2_32s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	
	ar0 = [--ar5];				// * a
	ar1 = [--ar5];				// * b
	gr7 = [--ar5] with gr7>>=1;	// size/2

	SET nb1, 0x80000000
	SET sb, 0x2
	SET f1cr, 0x80000000
	SET f2cr, 0x80000000

	ar5 = Matr32;
	rep 2 wfifo = [ar5++], ftw, wtw;

	call Abs2;

	pop ar1, gr1;
	pop ar0, gr0;
	return;


_nmppsAbs2_64s:
	ar5 = ar7 - 2;
	push ar0, gr0;
	push ar1, gr1;
	
	ar0 = [--ar5];				// * a	,	gr1=1
	ar1 = [--ar5];				// * b
	gr7 = [--ar5];				// size

	SET nb1, 0x0
	SET sb, 0x0
	// SET f1cr, 0x0
	wtw;
	sir = 0x80000000;
	f1crh= sir;
	f2crh= sir;
	sir =0;
	f1crl = sir;
	f2crl = sir;

	ar5 = Matr64;
	rep 1 wfifo = [ar5++], ftw, wtw;

	call Abs2;

	pop ar1, gr1;
	pop ar0, gr0;
	return;