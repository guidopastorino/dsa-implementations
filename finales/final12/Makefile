CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = main
SRCS = main.c bst.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	@rm -f *.o $(TARGET)

run: all
	@./$(TARGET)

valgrind: all
	@valgrind ./$(TARGET) --leak-check=full

.PHONY: all clean run valgrind

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@