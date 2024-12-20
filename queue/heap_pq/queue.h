// Tipos de funciones
#ifndef _TYPES_H_
#define _TYPES_H_

#include "heap.h"

typedef struct {
  MaxHeap* heap;
} PQueue;

PQueue* pq_create();

void pq_insert(PQueue* queue, void* data, Copy cpy, Compare cmp);

void pq_delete(PQueue* queue, void* data, Compare cmp, Destroy destr);

void* pq_extract_max(PQueue* queue, Compare cmp);

void pq_display(PQueue* queue, Print print);

void pq_destroy(PQueue* queue, Destroy destr);

#endif