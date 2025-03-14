CC = gcc
CFLAGS =
LDFLAGS =

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

all:
	(cd tool;make)
	(cd c;make)
	(cd file-io;make)
	(cd file-dir;make)
	(cd process;make)
	(cd signal;make)
	(cd ipc;make)
	(cd sync;make)
	(cd socket;make)
	(cd misc;make)

clean :
	(cd tool;make clean)
	(cd c;make clean)
	(cd file-io;make clean)
	(cd file-dir;make clean)
	(cd process;make clean)
	(cd signal;make clean)
	(cd ipc;make clean)
	(cd sync;make clean)
	(cd socket;make clean)
	(cd misc;make clean)