PROG := a.out
SRCS := main.c gc.c vm.c object.c
OBJS := main.o gc.o vm.o object.o
CC := gcc

%.o: %.c
	$(CC) -g -c $<

$(PROG): $(OBJS)
	$(CC) -g -o $@ $^

clean:
	rm -f $(OBJS) $(PROG)

all: clean $(PROG)
