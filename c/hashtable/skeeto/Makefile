CFLAGS= -Wall
OBJ = main.o hashtab.o

hashtab: $(OBJ)
main.o: main.c hashtab.h strht.h
hashtab.o: hashtab.c hashtab.h

.PHONY : clean run

run : hashtab

clean :
	$(RM) $(OBJ) hashtab
