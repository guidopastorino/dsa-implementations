// Una Descending Priority Queue ordena los elementos en orden descendente de prioridad, de manera que los elementos con mayor prioridad estén al frente. Esto es útil cuando se desea procesar los elementos de la prioridad más alta primero.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int data;
  int priority;
} Entry;

typedef struct {
  Entry* entries;
  int capacity; // elementos máximos
  int size; // tamaño actual
} DPQueue;

DPQueue* create_queue(int capacity){
  DPQueue* queue = (DPQueue*)malloc(sizeof(DPQueue));
  assert(queue != NULL);
  queue->entries = (Entry*)malloc(sizeof(Entry) * capacity);
  assert(queue->entries != NULL);
  queue->capacity = capacity;
  queue->size = 0;
  return queue;
}

void resize(DPQueue* queue){
  queue->capacity *= 2;
  queue->entries = (Entry*)realloc(queue->entries, sizeof(Entry) * queue->capacity);
  assert(queue->entries != NULL);
}

void enqueue(DPQueue* queue, int data, int priority){
  if(queue->size == queue->capacity){
    resize(queue);
  }
  Entry entry = {data, priority};

  int i = queue->size - 1;
  while(i >= 0 && queue->entries[i].priority < priority){
    queue->entries[i + 1] = queue->entries[i];
    i--;
  }
  queue->entries[i + 1] = entry;
  queue->size++;
  printf("Enqueued %d with priority %d\n", entry.data, entry.priority);
}

Entry dequeue(DPQueue* queue){
  if(queue->size == 0){
    printf("Queue is empty. Cannot dequeue\n");
    return (Entry){-1, -1};
  }
  Entry element = queue->entries[0];

  // Mover todos los elementos a la izquierda
  for(int i = 1; i<queue->size; i++){
    queue->entries[i - 1] = queue->entries[i];
  }

  printf("Dequeued %d with priority %d\n", element.data, element.priority);
  return element;
}

Entry peek(DPQueue* queue){
  if(queue->size == 0){
    printf("Queue is empty. Cannot peek\n");
    return (Entry){-1, -1};
  }
  return queue->entries[0];
}

void display(DPQueue* queue) {
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

void free_queue(DPQueue* queue){
  free(queue->entries);
  free(queue);
}

int main() {
  DPQueue* queue = create_queue(5);

  // Insertar elementos en la cola
  enqueue(queue, 100, 3);
  enqueue(queue, 200, 1);
  enqueue(queue, 300, 2);
  enqueue(queue, 400, 5);

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
  enqueue(queue, 600, 2);
  display(queue);

  // Liberar memoria
  free_queue(queue);

  return 0;
}