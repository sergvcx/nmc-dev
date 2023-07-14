@set GCC_EXEC_PREFIX=/cygdrive/C/Program Files/Module/NMC-SDK/nmc4-ide/lib/gcc/
@set PATH=%NMC_GCC_TOOLPATH%\nmc4-ide\bin;%NMC_GCC_TOOLPATH%\nmc4-ide\lib;%PATH%

mc12101run -p -R -a0 -v test.abs
