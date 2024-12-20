CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g -Wno-unused-function
TARGET = main
SRCS = main.c avl.c hashtable.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o $(TARGET)

run: all
	@./$(TARGET)

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

help:
	@echo "Comandos disponibles:"
	@echo "  make: Compila el programa y genera el ejecutable $(TARGET)"
	@echo "  make run: Ejecuta el programa generado"
	@echo "  make clean: Elimina los archivos objeto (.o) y el ejecutable $(TARGET)"
	@echo "  make valgrind: Ejecuta Valgrind para detectar fugas de memoria"

.PHONY: all clean run valgrind help