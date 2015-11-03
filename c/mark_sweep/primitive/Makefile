PROG := a.out
SRCS := main.c gc.c vm.c
OBJS := main.o gc.o vm.o
CC := /usr/local/Cellar/gcc/5.2.0/bin/gcc-5

%.o: %.c
	$(CC) -c $<

$(PROG): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(PROG)

all: clean $(PROG)
