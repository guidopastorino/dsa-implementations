CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

OBJS = main.o bst.o hashtable.o

main: $(OBJS)
	@$(CC) $(CFLAGS) -o main $(OBJS)

valgrind: main
	@valgrind --leak-check=full --show-leak-kinds=all -s ./main

clean:
	@rm -f *.o main
