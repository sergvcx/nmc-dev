@set GCC_EXEC_PREFIX=/cygdrive/C/Program Files/Module/NMC-SDK/nmc4-ide/lib/gcc/
@set PATH=%NMC_GCC_TOOLPATH%\nmc4-ide\bin;%NMC_GCC_TOOLPATH%\nmc4-ide\lib;%PATH%

nmc-gcc  -otest.abs  -O2 -Wall -mnmc4-float -g -Wl,-Map=test.abs.map -Wl,-Tmc12101-nmpu0.lds  -I"%MC12101%/include"  -L"%MC12101%/lib" main.cpp  -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -Wl,--no-whole-archive
