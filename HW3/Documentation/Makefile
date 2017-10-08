INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= pthreadex.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	pthreadex

clean:
	-rm -f *.o *.d
	-rm -f perfmon pthreadex

distclean:
	-rm -f *.o *.d
	-rm -f pthreadex

Multi: pthreadex.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
