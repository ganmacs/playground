CFLAGS= -Wall
OBJS = main.o parse.o debug.o util.o gc.o

mlisp: mlisp.h $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS): mlisp.h

.PHONY: clean cleanobj test

clean: cleanobj
	rm mlisp

cleanobj:
	rm -f *.o

test: mlisp
	@./test.sh

all: mlisp clean mlisp
