#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100   // Tamaño máximo de elementos en el stack

typedef struct {
  int array[SIZE]; // Array que almacenará los elementos
  int top;         // Índice del elemento en la cima del stack
} Stack;

void stack_init(Stack* stack){
  stack->top = -1;
}

int stack_is_empty(Stack* stack){
  return stack->top == -1;
}

int stack_is_full(Stack* stack){
  return stack->top == SIZE - 1;
}

void stack_push(Stack* stack, int data){
  if(stack_is_full(stack)){
    printf("Stack if full. Cannot push\n");
    return;
  }
  stack->array[++(stack->top)] = data;
}

int stack_pop(Stack* stack){
  if(stack_is_empty(stack)){
    printf("Stack if empty. Cannot pop\n");
    return -1;
  }
  return stack->array[(stack->top)--];
}

int stack_top(Stack* stack){
  if(stack_is_empty(stack)){
    printf("Stack if empty. Cannot get top\n");
    return -1;
  }
  return stack->array[stack->top];
}

void stack_print(Stack* stack){
  printf("Stack: ");
  for(int i = 0; i<(stack->top + 1); i++)
    printf("%d ", stack->array[i]);
  printf("\n");
}

int main() {
  Stack stack;

  // Inicializar el stack
  stack_init(&stack);

  // Push algunos elementos al stack
  printf("Pushing elements onto the stack...\n");
  stack_push(&stack, 10);
  stack_push(&stack, 20);
  stack_push(&stack, 30);
  stack_push(&stack, 40);

  stack_print(&stack);

  // Mostrar el valor en la cima del stack
  printf("Top element: %d\n", stack_top(&stack));

  // Pop algunos elementos
  printf("Popped element: %d\n", stack_pop(&stack));
  printf("Popped element: %d\n", stack_pop(&stack));

  // Mostrar el nuevo top
  printf("New top element: %d\n", stack_top(&stack));

  // Verificar si el stack está vacío
  if (stack_is_empty(&stack)) {
    printf("Stack is empty!\n");
  } else {
    printf("Stack is not empty!\n");
  }

  // Hacer pop hasta que el stack esté vacío
  while (!stack_is_empty(&stack)) {
    printf("Popped element: %d\n", stack_pop(&stack));
  }

  // Verificar si el stack está vacío
  if (stack_is_empty(&stack)) {
    printf("Stack is empty!\n");
  }

  stack_print(&stack);

  return 0;
}