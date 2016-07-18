CFLAGS= -Wall
OBJS = mlisp.o parse.o debug.o util.o gc.o env.o eval.o

mlisp:  $(OBJS)
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
