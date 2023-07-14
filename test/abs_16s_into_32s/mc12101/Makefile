SHELL=cmd
OS_RM    = del 
.SUFFIXES:

PATH := $(PATH);C:\Module\nmc-sdk\bin

TARGET   = test.abs
TARGETD  = testd.abs

CC       = nmc-gcc
AS       = nmc-gcc
CXXFLAGS =  -O2 -Wall -mnmc4-fixed -g
LIBS     =  -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -Wl,--no-whole-archive
LIBSD    =  -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101_stub_nmc4_fixed -Wl,--no-whole-archive 
LDFLAGS  = -Wl,-Map=test.map  -Wl,-Tmc12101-nmpu1.lds
LDFLAGSD = -Wl,-Map=testd.map -Wl,-Tmc12101-nmpu1.lds
INC_DIRS = -I"$(MC12101)/include" -I../../../include -I..
LIB_DIRS = -L"$(MC12101)/lib" 
SOURCES  = ../main.cpp ../../../nm/*.S ../../../nm/*.cpp ../../../common/dataInit.cpp ../../../pc/*.cpp


.DEFAULT_GOAL := all

all: $(TARGET) $(TARGETD)

$(TARGET): $(SOURCES) Makefile 
	@echo ----------------------
	$(CC)  -o$(TARGET) $(CXXFLAGS) $(LDFLAGS)  $(INC_DIRS) $(LIB_DIRS)  $(SOURCES) $(LIBS)
	nmc-objdump -D $(TARGET) > dasm.txt

$(TARGETD): $(SOURCES) Makefile 
	@echo ----------------------
	$(CC)  -o$(TARGETD) $(CXXFLAGS) $(LDFLAGSD) $(INC_DIRS) $(LIB_DIRS) $(SOURCES) $(LIBSD) 
	
run: $(TARGET)
	mc12101run -p -R -a1 -v $(TARGET)

rund: $(TARGETD) 
	mc12101run -p -R -a1 -v $(TARGETD)

rpc:
	hal-run --server_ip=213.141.142.228 --server_port=5557   -p -R -a1 $(TARGET)


# set path to MinGW/bin    For example:  SET PATH=%PATH%;d:\SDK\msys64\mingw64\bin\

monitor:
	nm_gdb_monitor_mc12101.exe
	
gdb :	
	nmc-gdb  $(TARGETD)


clean: 
	-$(OS_RM) *.abs *.elf *.map 
	

