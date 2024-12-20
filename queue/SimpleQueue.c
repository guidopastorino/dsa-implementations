#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 5

// Estructura para la cola
typedef struct {
  int front;  // Índice del primer elemento
  int rear;   // Índice del último elemento
  int arr[MAX_SIZE];  // Almacena los elementos de la cola
} Queue;

// Inicializa la cola con índices vacíos
void initialize_queue(Queue* queue) {
  queue->front = queue->rear = -1;
}

// Verifica si la cola está llena
int is_full(Queue* queue) {
  return queue->rear == MAX_SIZE - 1;
}

// Verifica si la cola está vacía
int is_empty(Queue* queue) {
  return queue->front == -1 && queue->rear == -1;
}

// Agrega un elemento al final de la cola
void enqueue(Queue* queue, int data) {
  if (is_full(queue)) {
    printf("Queue is full. Cannot enqueue\n");
    return;
  }
  if (is_empty(queue)) {
    queue->front = 0;  // Inicia el índice del frente en el primer elemento
  }
  queue->arr[++queue->rear] = data;
}

// Elimina y devuelve el primer elemento de la cola
int dequeue(Queue* queue) {
  if (is_empty(queue)) {
    printf("Queue is empty. Cannot dequeue\n");
    return -1;
  }
  int data = queue->arr[queue->front];
  if (queue->front == queue->rear) {
    // Si se elimina el único elemento, reinicia la cola
    queue->front = queue->rear = -1;
  } else {
    queue->front++;
  }
  return data;
}

// Devuelve el primer elemento sin eliminarlo
int peek(Queue* queue) {
  if (is_empty(queue)) {
    printf("Queue is empty. Cannot peek\n");
    return -1;
  }
  return queue->arr[queue->front];
}

// Muestra todos los elementos de la cola
void display(Queue* queue) {
  if (is_empty(queue)) {
    printf("Queue is empty\n");
    return;
  }
  printf("Queue: ");
  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%d ", queue->arr[i]);
  }
  printf("\n");
}

int main() {
  Queue queue;
  initialize_queue(&queue);

  printf("Enqueuing elements...\n");
  enqueue(&queue, 10);
  enqueue(&queue, 20);
  enqueue(&queue, 30);
  enqueue(&queue, 40);
  enqueue(&queue, 50);
  display(&queue);

  printf("Trying to enqueue when full...\n");
  enqueue(&queue, 60);

  printf("Front element: %d\n", peek(&queue));

  printf("Dequeuing elements...\n");
  printf("Dequeued: %d\n", dequeue(&queue));
  display(&queue);

  printf("Dequeued: %d\n", dequeue(&queue));
  display(&queue);

  dequeue(&queue);
  dequeue(&queue);
  dequeue(&queue);

  printf("Dequeuing from empty queue...\n");
  dequeue(&queue);

  return 0;
}