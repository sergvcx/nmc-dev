

// `Format` - строка форматирования одного элемента со стандартным синтаксисом `printf`. 
// `mtr`    - любой регистр или метка, указывающая на начало матрицы 
// `height` - высота матрицы в элементах (8,16,32 или 64-разрядных) в виде константы или любого регистра кроме `ar5 ar7`
// `width`  - ширина матрицы в виде константы или любого регистра кроме `ar5 ar7`
// `stride` - смещение в элементах при переходе от начала одной строки к следующей в виде константы или любого регистра кроме `ar5 ar7`
// для работы макросов `MPRINTF_XX` жолден быть прилинокован `mprintx.cpp`
#define MPRINTF_8S(   Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_8s
#define MPRINTF_16S(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_16s
#define MPRINTF_32S(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_32s
#define MPRINTF_64S(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_64s

#define MPRINTF_8U(   Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_8u
#define MPRINTF_16U(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_16u
#define MPRINTF_32U(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_32u
#define MPRINTF_64U(  Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_64u


#define MPRINTF_32F( Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_32f
#define MPRINTF_64F( Format, mtr, height, width, stride) MPRINTF_MACRO Format,mtr,height,width,stride,_mprintf_64u

// Пример:
// mtr:  .quad 0x0706050403020100, 0x1716151413121110, 0x2726252423222120, 0x3736353433323130 
// mtr32f:  .float 0.1, 0.2, 0.3, 0.4 
// mtr64f:  .double 0.1, 0.2, 0.3, 0.4 
// MPRINTF_8U( "%0x,", mtr,2,16,16)
// MPRINTF_16U("%0d ", mtr,2,8,8)
// MPRINTF_32U("%0x ", mtr,2,4,4)
// MPRINTF_64U("%0lx ",mtr,2,2,2)
// MPRINTF_32F("%.3fx ",mtr,2,2,2)
	

.macro MPRINTF_MACRO format, mtr, height, width, stride, printer
	push ar5,gr5;
	gr5 = \mtr;
	delayed skip skip_text\@;
		[MTR\@]=gr5;
format_msg\@:
    .ascii "\format\0"
MTR\@: 	.long 0

skip_text\@:
	

	ar5 = ar7;
    ar7 += 6;
	
	gr5 =false;
	[ar5 ++ ] = gr5;
	
	gr5 = \stride;
	[ ar5++ ] = gr5;	
	
	gr5 = \width;
	[ ar5++ ] = gr5;	
	
	gr5 = \height;
	[ ar5++ ] = gr5;	
	
	gr5 = [MTR\@];
	[ ar5++ ] = gr5;	
	
	gr5 = format_msg\@;
	[ ar5++ ] = gr5;	
	
	call \printer with gr5 = gr7;
	ar7 -=6 with gr7 = gr5;
	pop ar5,gr5;
.endm



#define PRINTF(Format) PRINTF_MACRO Format
#define PRINTF1(Format, Arg) PRINTF1_MACRO Format,Arg
#define PRINTF2(Format, Arg1,Arg2) PRINTF2_MACRO Format,Arg1,Arg2
#define PRINTFL(Format, Arg1) PRINTFL_MACRO Format,Arg1


// USAGE in *.S sources:
// #include "printx.hs"
// PRINTF("Hello\n")
// PRINTF1("C addr =%X\n",ar5)
// PRINTF2("[C]={%d,%d}\n",[ar5++],[ar5++])
//
// PRINTF1("=%x\n",gr4)
// PRINTF1("=%x\n",[ar4])
// PRINTF1("=%x\n",[tmp])
// PRINTF1("=%x\n",tmp)
// PRINTF2("=%x %x\n",ar4,gr4)
// PRINTF2("=%x %x\n",gr4,ar4)
// PRINTF2("=%x %x\n",gr4,gr4)
// PRINTF2("=%x %x\n",ar4,ar4)
// PRINTFL("=%lX\n",[ar4])
// PRINTF2("=%x %x\n",[ar4++],[ar4++])
	
	
.macro PRINTF_MACRO format
	push ar5,gr5;
	skip skip_text\@;
format_msg\@:
    .ascii "\format\0"

skip_text\@:
	ar5 = ar7;
    ar7 += 2 with gr5 = false;
	[ ar5++ ] = gr5;	// align stack
	gr5 = format_msg\@;
	[ ar5++ ] = gr5;	
	call _printf with gr5=gr7;
	ar7 -=2 with gr7 = gr5;
	pop ar5,gr5;
.endm


.macro PRINTF1_MACRO format,arg
	push ar5,gr5;
	push ar4,gr4;
	gr4 = \arg;
	skip skip_text\@;
format_msg\@:
    .ascii "\format\0"
	
skip_text\@:
	ar5 = ar7;
    ar7 += 2;
	[ ar5++ ] = gr4;	
	gr5 = format_msg\@;
	[ ar5++ ] = gr5;	
	call _printf with gr5 = gr7;
	ar7 -=2 with gr7 = gr5;
	pop ar4,gr4;
	pop ar5,gr5;
.endm

.macro PRINTF2_MACRO format,arg1,arg2
	push ar5,gr5;
	push ar4,gr4; 	// save origin   gr4 => [ar7-1]
	ar7+=2;			//      origin   gr4 at [ar7-3]
	gr4 = \arg1;
	[ar7+-2] = gr4;	// save          arg1 => [ar7-2]
	gr4 = [ar7+-3];	// load origin   gr4  <= [ar7-3]
	ar4 = \arg2;	// load          ar4  <= arg2 
	gr4 = [ar7+-2];	// load          gr4  <= arg1
	delayed skip skip_text\@;
		ar7-=2;
format_msg\@:
    .ascii "\format\0"
skip_text\@:
	ar5 = ar7;
    ar7 += 4;
	gr5 = false;
	[ ar5++ ] = gr5;	
	[ ar5++ ] = ar4;	
	[ ar5++ ] = gr4;	
	gr5 = format_msg\@;
	[ ar5++ ] = gr5;	
	call _printf with gr5 = gr7;
	ar7 -=4 with gr7 = gr5;
	pop ar4,gr4;
	pop ar5,gr5;
.endm


.macro PRINTFL_MACRO format,arg1
	push ar5,gr5;
	push ar4,gr4; 
	ar4,gr4=\arg1;
	skip skip_text\@;
	
format_msg\@:
    .ascii "\format\0"
skip_text\@:
	ar5 = ar7;
    ar7 += 6;
	gr5 = false;
	ar5++; // align stack for 64-bit arg(ar4,gr4)
	[ ar5++ ] = gr5;	
	[ ar5++ ] = ar4;	
	[ ar5++ ] = gr4;	
	gr5 = format_msg\@;
	ar5++;		
	[ ar5++ ] = gr5;	
	call _printf with gr5 = gr7;
	ar7 -=6 with gr7 = gr5;
	pop ar4,gr4;
	pop ar5,gr5;
.endm
