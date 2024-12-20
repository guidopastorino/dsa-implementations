#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define MAX_SIZE 10

typedef struct {
  int* arr;
  int size; // current heap size
} BHeap;

BHeap* create_heap();

void heapify_down(BHeap* heap, int i);

void heapify_up(BHeap* heap, int i);

void insert(BHeap* heap, int data);

int bheap_erase_max(BHeap *);

void print_heap(BHeap* heap);

void destroy_heap(BHeap* heap);

#endif