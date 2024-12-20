// Max Heap
#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Función para copiar un elemento
typedef void* (*Copy)(void*);
// Función para comparar dos elementos
typedef int (*Compare)(void*, void*);
// Función para imprimir un elemento
typedef void (*Print)(void*);
// Función para destruir un elemento
typedef void (*Destroy)(void*);

#define MAX_SIZE 10

typedef struct {
  void** array;
  int size;
} MaxHeap;

MaxHeap* heap_create();

static void swap(void** a, void** b);

static int parent(int i);

static int left_child(int i);

static int right_child(int i);

void heapify_up(MaxHeap* heap, int i, Compare cmp);

void heapify_down(MaxHeap* heap, int i, Compare cmp);

void heap_insert(MaxHeap* heap, void* data, Copy cpy, Compare cmp);

void heap_delete(MaxHeap* heap, void* data, Compare cmp, Destroy destr);

void* heap_extract_max(MaxHeap* heap, Compare cmp);

void heap_display(MaxHeap* heap, Print print);

void heap_destroy(MaxHeap* heap, Destroy destr);

#endif