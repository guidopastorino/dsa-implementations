#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 5

typedef struct {
  int arr[MAX_SIZE];
  int front;
  int rear;
  int size;
} CircularQueue;

void initialize_queue(CircularQueue* queue){
  queue->front = 0;
  queue->rear = -1;
  queue->size = 0;
}

int is_empty(CircularQueue* queue){
  return queue->size == 0;
}

int is_full(CircularQueue* queue){
  return queue->size == MAX_SIZE;
}

void enqueue(CircularQueue* queue, int data){
  if(is_full(queue)){
    printf("Queue is full. Cannot enqueue\n");
    return;
  }
  queue->rear = (queue->rear + 1) % MAX_SIZE;
  queue->arr[queue->rear] = data;
  queue->size++;
  printf("Enqueued %d\n", data);
}

int dequeue(CircularQueue* queue){
  if(is_empty(queue)){
    printf("Queue is empty. Cannot dequeue\n");
    return -1;
  }
  int element = queue->arr[queue->front];
  queue->front = (queue->front + 1) % MAX_SIZE;
  queue->size--;
  printf("Dequeued %d\n", element);
  return element;
}

int peek(CircularQueue* queue){
  if(is_empty(queue)){
    printf("Queue is empty. Cannot peek\n");
    return -1;
  }
  return queue->arr[queue->front];
}

void display(CircularQueue* queue){
  if(is_empty(queue)){
    printf("Queue is empty\n");
    return;
  }
  printf("Queue: ");
  for(int i = 0; i<queue->size; i++){
    int index = (queue->front + i) % MAX_SIZE;
    printf("%d ", queue->arr[index]);
  }
  printf("\n");
}

int main() {
  CircularQueue queue;
  initialize_queue(&queue);

  // Agregar elementos a la cola
  enqueue(&queue, 10);
  enqueue(&queue, 20);
  enqueue(&queue, 30);
  enqueue(&queue, 40);
  enqueue(&queue, 50);

  // Intentar agregar más elementos cuando la cola está llena
  enqueue(&queue, 60);

  // Mostrar la cola
  display(&queue);

  // Obtener el elemento al frente
  printf("Front element: %d\n", peek(&queue));

  // Eliminar elementos de la cola
  dequeue(&queue);
  dequeue(&queue);

  // Mostrar la cola después de dequeues
  display(&queue);

  // Agregar elementos nuevamente
  enqueue(&queue, 60);
  enqueue(&queue, 70);

  // Mostrar la cola después de nuevos enqueues
  display(&queue);

  return 0;
}