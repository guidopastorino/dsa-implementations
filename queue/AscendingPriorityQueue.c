// Una Ascending Priority Queue es una cola de prioridad donde los elementos se organizan en orden ascendente, es decir, el elemento con la prioridad más baja está al frente y es desencolado primero

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int data;
  int priority;
} Entry;

typedef struct {
  Entry* entries;
  int size; // Tamaño actual del Queue
  int capacity; // Capacidad máxima
} APQueue;

APQueue* create_queue(int capacity){
  APQueue* queue = (APQueue*)malloc(sizeof(APQueue));
  assert(queue != NULL);
  queue->entries = (Entry*)malloc(sizeof(Entry) * capacity);
  assert(queue->entries != NULL);
  queue->capacity = capacity;
  queue->size = 0;
  return queue;
}

void resize_queue(APQueue* queue){
  queue->capacity *= 2;
  queue->entries = (Entry*)realloc(queue->entries, sizeof(Entry) * queue->capacity);
  assert(queue->entries != NULL);
}

void enqueue(APQueue* queue, int data, int priority){
  if(queue->size == queue->capacity){
    resize_queue(queue);
  }

  Entry entry = {data, priority};
  int i = queue->size - 1;

  // Desplaza los elementos con mayor prioridad hacia la derecha
  while(i >= 0 && queue->entries[i].priority > priority){
    queue->entries[i + 1] = queue->entries[i];
    i--;
  }

  queue->entries[i + 1] = entry;
  queue->size++;
  printf("Enqueued %d with priority %d\n", data, priority);
}

Entry dequeue(APQueue* queue){
  if(queue->size == 0){
    printf("Queue is empty. Cannot dequeue\n");
    return (Entry){-1, -1};
  }
  Entry front_entry = queue->entries[0];

  // Desplazar los elementos hacia la izquierda
  for(int i = 1; i<queue->size; i++){
    queue->entries[i - 1] = queue->entries[i];
  }

  queue->size--;
  printf("Dequeued %d with priority %d\n", front_entry.data, front_entry.priority);
  return front_entry;
}

Entry peek(APQueue* queue){
  if(queue->size == 0){
    printf("Queue is empty. Cannot peek\n");
    return (Entry){-1, -1};
  }

  Entry front_entry = queue->entries[0];
  return front_entry;
}

void display(APQueue* queue) {
  if (queue->size == 0) {
    printf("Queue is empty\n");
    return;
  }

  printf("Queue: ");
  for (int i = 0; i < queue->size; i++) {
    printf("[data = %d, priority = %d] ", queue->entries[i].data, queue->entries[i].priority);
  }
  printf("\n");
}


// Libera la memoria de la cola de prioridad
void free_queue(APQueue* queue) {
  free(queue->entries);
  free(queue);
}

int main() {
  APQueue* queue = create_queue(5);

  // Insertar elementos en la cola
  enqueue(queue, 100, 3);
  enqueue(queue, 200, 1);
  enqueue(queue, 300, 2);
  enqueue(queue, 400, 0);

  // Mostrar los elementos de la cola
  display(queue);

  // Obtener el elemento al frente
  Entry front = peek(queue);
  printf("Front element: data = %d, priority = %d\n", front.data, front.priority);

  // Eliminar elementos de la cola
  dequeue(queue);
  display(queue);

  dequeue(queue);
  display(queue);

  // Insertar más elementos
  enqueue(queue, 500, 4);
  enqueue(queue, 600, 1);
  display(queue);

  // Liberar memoria
  free_queue(queue);

  return 0;
}