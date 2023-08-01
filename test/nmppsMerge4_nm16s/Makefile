.PHONY: qemu

board:	
	$(MAKE) -C mc12101

qemu:	
	$(MAKE) -C qemu


# on board run

run:
	$(MAKE) -C mc12101 run



# on board run with gdb

monitor:	
	$(MAKE) -C mc12101 monitor
	
rund:
	$(MAKE) -C mc12101 rund

gdb:
	$(MAKE) -C mc12101 gdb



# on qemu run

qrun:
	$(MAKE) -C qemu run

# on qemu run with gdb
	
qrund:
	$(MAKE) -C qemu rund


qgdb:
	$(MAKE) -C qemu gdb

