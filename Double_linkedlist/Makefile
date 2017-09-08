INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=doublelinkedlist

HFILES= doublelinkedlist.h
CFILES= doublelinkedlist.c 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

linkedlist:	doublelinnkedlist.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ doublelinkedlist.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
