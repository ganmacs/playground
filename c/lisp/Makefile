CFLAGS= -Wall
OBJS = main.o

mlisp: mlisp.h $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS): mlisp.h

clean: cleanobj
	rm mlisp

cleanobj:
	rm -f *.o

.PHONY: clean mlisp
