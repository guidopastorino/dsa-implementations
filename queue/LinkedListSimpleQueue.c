#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Node {
  int data;
  struct _Node* next;
} Node;

typedef struct {
  Node* front;
  Node* rear;
} Queue;

Node* create_node(int data){
  Node* node = (Node*)malloc(sizeof(Node));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  return node;
}

Queue* create_queue(){
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  assert(queue != NULL);
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void enqueue(Queue* queue, int data){
  Node* node = create_node(data);
  if(queue->front == NULL){
    queue->front = queue->rear = node;
  } else {
    queue->rear->next = node;
    queue->rear = node;
  }
}

int dequeue(Queue* queue){
  if(queue->front == NULL){
    printf("Queue is empty. Cannot dequeue\n");
    return -1;
  }
  Node* temp = queue->front;
  int data = temp->data;
  queue->front = queue->front->next;
  if(queue->front == NULL)
    queue->rear = NULL;
  free(temp);
  return data;
}

int peek(Queue* queue){
  if(queue->front == NULL){
    printf("Queue is empty. Cannot peek\n");
    return -1;
  }
  return queue->front->data;
}

void display(Queue* queue){
  printf("Queue: ");
  Node* current = queue->front;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void free_queue(Queue* queue){
  Node* current = queue->front;
  while(current != NULL){
    Node* temp = current;
    current = current->next;
    free(temp);
  }
  free(queue);
  queue->front = queue->rear = NULL;
}

int main() {
  Queue* queue = create_queue();

  // Agregar elementos a la cola
  printf("Enqueuing elements...\n");
  enqueue(queue, 10);
  enqueue(queue, 20);
  enqueue(queue, 30);
  display(queue);

  // Obtener el elemento al frente
  printf("Front element: %d\n", peek(queue));

  // Eliminar elementos de la cola
  printf("Dequeuing element: %d\n", dequeue(queue));
  display(queue);

  printf("Dequeuing element: %d\n", dequeue(queue));
  display(queue);

  printf("Dequeuing element: %d\n", dequeue(queue));
  display(queue);

  // Intentar hacer dequeue en una cola vacía
  printf("Dequeuing from empty queue: %d\n", dequeue(queue));

  // Liberar memoria
  free_queue(queue);

  return 0;
}