PROG := a.out
SRCS := main.c gc.c vm.c object.c
OBJS := main.o gc.o vm.o object.o
CC := gcc

%.o: %.c
	$(CC) -c $<

$(PROG): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(PROG)

all: clean $(PROG)
