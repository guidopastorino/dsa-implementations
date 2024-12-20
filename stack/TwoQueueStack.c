// Stack utilizando dos colas

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_CAPACITY 10

// Definición de estructuras y funciones para la Queue

typedef struct {
  int arr[MAX_CAPACITY];
  int front;
  int rear;
} Queue;

void queue_init(Queue* queue){
  queue->front = queue->rear = -1;
}

int queue_is_empty(Queue* queue){
  return queue->front == -1;
}

int queue_is_full(Queue* queue){
  return queue->rear == MAX_CAPACITY - 1;
}

void queue_enqueue(Queue* queue, int data){
  if(queue_is_full(queue)){
    printf("Queue is full. Cannot enqueue\n");
    return;
  }

  if(queue_is_empty(queue)){
    queue->front = queue->rear = 0;
  } else {
    queue->rear++;
  }

  queue->arr[queue->rear] = data;
}

int queue_dequeue(Queue* queue){
  if(queue_is_empty(queue)){
    printf("Queue is empty. Cannot dequeue\n");
    return -1;
  }

  int element = queue->arr[queue->front];

  if(queue->front == queue->rear){
    queue->front = queue->rear = -1;
  } else {
    queue->front++;
  }

  return element;
}

int queue_front(Queue* queue){
  if(queue_is_empty(queue)){
    printf("Queue is empty. Cannot get front\n");
    return -1;
  }

  return queue->arr[queue->front];
}

// Definición de estructuras y funciones para el Stack

typedef struct {
  Queue queue1;
  Queue queue2;
} Stack;

void stack_init(Stack* stack){
  queue_init(&stack->queue1);
  queue_init(&stack->queue2);
}

void stack_push(Stack* stack, int data){
  // Insertar en queue2
  queue_enqueue(&stack->queue2, data);

  // Mover todos los elementos de queue1 a queue2
  while(!queue_is_empty(&stack->queue1)){
    queue_enqueue(&stack->queue2, queue_dequeue(&stack->queue1));
  }

  // intercambiamos las colas
  Queue temp = stack->queue1;
  stack->queue1 = stack->queue2;
  stack->queue2 = temp;
}

int stack_pop(Stack* stack){
  if(queue_is_empty(&stack->queue1)){
    printf("Stack is empty. Cannot pop\n");
    return -1;
  }
  return queue_dequeue(&stack->queue1);
}

int stack_top(Stack* stack){
  return queue_front(&stack->queue1);
}

void stack_display(Stack* stack){
  printf("Stack: ");
  Queue q = stack->queue1;
  for(int i = q.front; i<=q.rear; i++){
    printf("%d ", q.arr[i]);
  }
  printf("\n");
}

// Programa principal para probar la pila
int main() {
  Stack stack;
  stack_init(&stack);

  stack_push(&stack, 10);
  stack_push(&stack, 20);
  stack_push(&stack, 30);

  stack_display(&stack);

  printf("Cima: %d\n", stack_top(&stack));

  printf("Pop: %d\n", stack_pop(&stack));
  printf("Pop: %d\n", stack_pop(&stack));

  stack_display(&stack);

  stack_push(&stack, 40);
  printf("Cima: %d\n", stack_top(&stack));

  printf("Pop: %d\n", stack_pop(&stack));
  printf("Pop: %d\n", stack_pop(&stack));

  stack_display(&stack);

  return 0;
}