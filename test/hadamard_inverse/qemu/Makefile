#SHELL=cmd
#-include C:\Program\ Files\Module\NMC-SDK\nmc4-ide\include\nmc4vars_win.mk
#OS_RM    = del 
#.SUFFIXES:


TARGET   = test.abs
TARGETD  = testd.abs

CC       = nmc-gcc
AS       = nmc-gcc
CXXFLAGS =  -O0 -Wall -mnmc4-fixed -g
LIBS     =  -lnmpp-nm6407i -lc
LIBSD    =  -lnmpp-nm6407i -lc 
LDFLAGS  = -Wl,-Map=test.map  -Wl,-Tqemu-nm6407i.lds
LDFLAGSD = -Wl,-Map=testd.map -Wl,-Tqemu-nm6407i.lds 
INC_DIRS = -I"$(MC12101)/include" -I../../../include -I.. -I$(NMPP)/include
LIB_DIRS = -L"$(MC12101)/lib" -L$(NMPP)/lib
SOURCES  = ../../../nm/hash64.S ../../../nm/mulmm_2col.S ../../../nm/transpose.S ../../../common/hadamard_init.cpp ../../../common/hadamard.cpp ../../../common/mulmm.cpp ../main.cpp

.DEFAULT_GOAL := all

all: $(TARGET) 

$(TARGET): $(SOURCES) Makefile 
	@echo ----------------------
	$(CC)  -o$(TARGET) $(CXXFLAGS) $(LDFLAGS)  $(INC_DIRS) $(LIB_DIRS)  $(SOURCES) $(LIBS)
	nmc-objdump -D $(TARGET) > dasm.txt

run: $(TARGET)
	nmc-qemu   $(TARGET)

rund: $(TARGET) 
	nmc-qemu -g 10000 $(TARGET)

# set path to MinGW/bin    For example:  SET PATH=%PATH%;d:\SDK\msys64\mingw64\bin\
monitor:
	
	
gdb :	
	nmc-gdb  $(TARGET)


clean: 
	-$(OS_RM) *.abs *.elf *.map 
	

