#ifndef _HEAP_H_
#define _HEAP_H_

#include "types.h"

#define MAXHEAP_SIZE 100

typedef struct {
  Usuario usuarios[MAXHEAP_SIZE];
  int size;
} MaxHeap;

void heap_init(MaxHeap* heap);

static void swap(Usuario* usuario1, Usuario* usuario2);

static int parent(int i);

static int left_child(int i);

static int right_child(int i);

void heapify_down(MaxHeap* heap, int i, Compare cmp);

void heapify_up(MaxHeap* heap, int i, Compare cmp);

void heap_insert(MaxHeap* heap, Usuario usuario, Compare cmp);

void heap_delete(MaxHeap* heap, int dni, Compare cmp);

Usuario heap_extract_max(MaxHeap* heap, Compare cmp);

void heap_display(MaxHeap heap, Print print);

#endif