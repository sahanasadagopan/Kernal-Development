INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=circbuff

HFILES= circbuff.h
CFILES= circbuff.c 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

circbuff:	circbuff.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ circbuff.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
