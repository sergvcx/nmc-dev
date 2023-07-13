SHELL=cmd
-include C:\Program\ Files\Module\NMC-SDK\nmc4-ide\include\nmc4vars_win.mk
OS_RM    = del 
.SUFFIXES:


TARGET   = test.abs
TARGETD  = testd.abs

CC       = nmc-gcc
AS       = nmc-gcc
CXXFLAGS =  -O2 -Wall -mnmc4-fixed -g
LIBS     =  -lnmpp-nm6407i -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -Wl,--no-whole-archive
LIBSD    =  -lnmpp-nm6407i -lnm6407int -Wl,--whole-archive -lnm6407_io_nmc -lmc12101load_nm -lmc12101_stub_nmc4_fixed -Wl,--no-whole-archive 
LDFLAGS  = -Wl,-Map=test.map  -Wl,-Tmc12101-nmpu1.lds
LDFLAGSD = -Wl,-Map=testd.map -Wl,-Tmc12101-nmpu1.lds 
INC_DIRS = -I"$(MC12101)/include" -I../../../include -I.. -I$(NMPP)/include
LIB_DIRS = -L"$(MC12101)/lib" -L$(NMPP)/lib
SOURCES  = ../../../nm/*.S ../../../common/*.cpp ../main.cpp


.DEFAULT_GOAL := all

all: $(TARGET) $(TARGETD)

$(TARGET): $(SOURCES) Makefile 
	@echo ------ build release --------------
	$(CC)  -o$(TARGET) $(CXXFLAGS) $(LDFLAGS)  $(INC_DIRS) $(LIB_DIRS)  $(SOURCES) $(LIBS)
	nmc-objdump -D $(TARGET) > dasm.txt

$(TARGETD): $(SOURCES) Makefile 
	@echo ------ build debug ----------------
	$(CC)  -o$(TARGETD) $(CXXFLAGS) $(LDFLAGSD) $(INC_DIRS) $(LIB_DIRS) $(SOURCES) $(LIBSD) 

rpc: $(TARGET)
	hal-run --server_ip=213.141.142.228  --server_port=5557 -p -R -a1 -v $(TARGET)


run: $(TARGET)
	mc12101run -p -R -a1 -v $(TARGET)

rund: $(TARGETD) 
	mc12101run -p -R -a1 -v $(TARGETD)

monitor:
	nm_gdb_monitor_mc12101 0 1 5555
	
gdb:
	nmc-gdb  $(TARGETD)


clean: 
	-$(OS_RM) *.abs *.elf *.map 
	

