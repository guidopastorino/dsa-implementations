#include "heap.h"

BHeap* create_heap(){
  BHeap* heap = (BHeap*)malloc(sizeof(BHeap));
  assert(heap != NULL);
  heap->arr = (int*)calloc(MAX_SIZE, sizeof(int));
  assert(heap->arr != NULL);
  heap->size = 0;
  return heap;
}

static void swap(int* a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

static int parent(int i){
  return (i - 1) / 2;
}

static int left_child(int i){
  return 2 * i + 1;
}

static int right_child(int i){
  return 2 * i + 2;
}

void heapify_down(BHeap* heap, int i){
  int left = left_child(i);  
  int right = right_child(i);
  int smallest = i;

  if(left < heap->size && heap->arr[left] < heap->arr[smallest]){
    smallest = left;
  }

  if(right < heap->size && heap->arr[right] < heap->arr[smallest]){
    smallest = right;
  }

  if(i != smallest){
    swap(&heap->arr[i], &heap->arr[smallest]);
    heapify_down(heap, smallest);
  }
}

void heapify_up(BHeap* heap, int i){
  while(i != 0 && heap->arr[i] < heap->arr[parent(i)]){
    swap(&heap->arr[i], &heap->arr[parent(i)]);
    i = parent(i);
  }
}

void insert(BHeap* heap, int data){
  if(heap->size == MAX_SIZE){
    printf("Heap is full. Cannot insert more elements\n");
    return;
  }
  heap->arr[heap->size] = data;
  heapify_up(heap, heap->size);
  heap->size++;
}

// Función para encontrar el máximo en el Min-Heap
int find_max(BHeap* heap){
  int start = heap->size / 2;
  int max = INT_MIN;

  for(int i = start; i<heap->size; i++){
    if(heap->arr[i] > max){
      max = heap->arr[i];
    }
  }

  return max;
}

/* Dado un min-heap binario, remueve el mayor elemento y lo retorna */
int bheap_erase_max(BHeap* heap){
  if(heap->size == 0){
    return -1;
  }

  int max = find_max(heap);
  int start = heap->size / 2;
  int maxIndex = -1;

  for(int i = start; i<heap->size; i++){
    if(heap->arr[i] == max){
      maxIndex = i;
    }
  }

  heap->arr[maxIndex] = heap->arr[--heap->size];
  heapify_down(heap, maxIndex);

  return max;
}

void print_heap(BHeap* heap){
  for(int i = 0; i<heap->size; i++){
    printf("%d ", heap->arr[i]);
  }
  printf("\n");
}

void destroy_heap(BHeap* heap){
  free(heap->arr);
  free(heap);
}