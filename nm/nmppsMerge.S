.global _nmppsAbs2_8s

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