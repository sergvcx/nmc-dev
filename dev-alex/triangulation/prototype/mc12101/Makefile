SHELL=cmd
OS_RM    = del 
.SUFFIXES:

PATH := $(PATH);C:\Module\nmc-sdk\bin

TARGET   = test.abs
TARGETD  = testd.abs

CC       = nmc-gcc
AS       = nmc-gcc
CXXFLAGS =  -O2 -Wall -mnmc4-float -g
LIBS     =  -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -Wl,--no-whole-archive -lnmpp-nm6407f
LIBSD    =  -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -lmc12101_stub_nmc4_float -Wl,--no-whole-archive -lnmpp-nm6407f
LDFLAGS  = -Wl,-Map=test.map  -Wl,-Tmc12101-nmpu0.lds
LDFLAGSD = -Wl,-Map=testd.map -Wl,-Tmc12101-nmpu0.lds
INC_DIRS = -I"$(MC12101)/include" -I../../../../include -I.. -I$(NMPP)/include
LIB_DIRS = -L"$(MC12101)/lib" -L$(NMPP)/lib
SOURCES  = ../main.cpp ../../../../common/triangulation.cpp ../../../../nm/nmppsAverage.S

.DEFAULT_GOAL := all

all: $(TARGET) $(TARGETD)

$(TARGET): $(SOURCES) Makefile mc12101-nmpu0.lds  
	@echo ------ build release --------------
	$(CC)  -o$(TARGET) $(CXXFLAGS) $(LDFLAGS)  $(INC_DIRS) $(LIB_DIRS)  $(SOURCES) $(LIBS) $(ERRECHO)
	nmc-objdump -D $(TARGET) > dasm.txt

$(TARGETD): $(SOURCES) Makefile mc12101-nmpu0.lds 
	@echo ------ build debug ----------------
	$(CC)  -o$(TARGETD) $(CXXFLAGS) $(LDFLAGSD) $(INC_DIRS) $(LIB_DIRS) $(SOURCES) $(LIBSD) $(ERRECHO)
	nmc-objdump -D $(TARGETD) > dasmd.txt
	
run: $(TARGET)
	mc12101run -p -a0 -v $(TARGET)

rund: $(TARGETD) 
	mc12101run -p -a0 -v $(TARGETD)

rpc:
	hal-run --server_ip=213.141.142.228 --server_port=5557   -p -a0 $(TARGET)


# set path to MinGW/bin    For example:  SET PATH=%PATH%;d:\SDK\msys64\mingw64\bin\

monitor:
	nm_gdb_monitor_mc12101.exe
	
gdb :	
	nmc-gdb  $(TARGETD)


clean: 
	-$(OS_RM) *.abs *.elf *.map 
	

