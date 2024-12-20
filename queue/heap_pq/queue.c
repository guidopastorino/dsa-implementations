#include "queue.h"

PQueue* pq_create(){
  PQueue* queue = (PQueue*)malloc(sizeof(PQueue));
  assert(queue != NULL);
  queue->heap = heap_create();
  return queue;
}

void pq_insert(PQueue* queue, void* data, Copy cpy, Compare cmp){
  heap_insert(queue->heap, data, cpy, cmp);
}

void pq_delete(PQueue* queue, void* data, Compare cmp, Destroy destr){
  heap_delete(queue->heap, data, cmp, destr);
}

void* pq_extract_max(PQueue* queue, Compare cmp){
  return heap_extract_max(queue->heap, cmp);
}

void pq_display(PQueue* queue, Print print){
  heap_display(queue->heap, print);
}

void pq_destroy(PQueue* queue, Destroy destr){
  // destruir heap
  heap_destroy(queue->heap, destr);
  // destruir queue
  free(queue);
}