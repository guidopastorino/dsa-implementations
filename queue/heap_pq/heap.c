#include "heap.h"

MaxHeap* heap_create(){
  MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
  assert(heap != NULL);
  heap->array = (void**)malloc(sizeof(void*) * MAX_SIZE);
  assert(heap->array != NULL);
  heap->size = 0;
  return heap;
}

static void swap(void** a, void** b){
  void* temp = *a;
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

void heapify_down(MaxHeap* heap, int i, Compare cmp){
  int left = left_child(i);
  int right = right_child(i);
  int largest = i;

  if(left < heap->size && cmp(heap->array[left], heap->array[largest]) > 0){
    largest = left;
  }

  if(right < heap->size && cmp(heap->array[right], heap->array[largest]) > 0){
    largest = right;
  }

  if(i != largest){
    swap(&heap->array[largest], &heap->array[i]);
    heapify_down(heap, largest, cmp);
  }
}

void heapify_up(MaxHeap* heap, int i, Compare cmp){
  while(i != 0 && cmp(heap->array[i], heap->array[parent(i)]) > 0){
    swap(&heap->array[i], &heap->array[parent(i)]);
    i = parent(i);
  }
}

void heap_insert(MaxHeap* heap, void* data, Copy cpy, Compare cmp){
  if(heap->size == MAX_SIZE){
    printf("Heap is full. Cannot insert\n");
    return;
  }
  heap->array[heap->size] = cpy(data);
  heapify_up(heap, heap->size, cmp);
  heap->size++;
}

void heap_delete(MaxHeap* heap, void* data, Compare cmp, Destroy destr){
  if(heap->size == 0){
    printf("Heap is empty. Cannot delete\n");
    return;
  }
  int index = -1;
  for(int i = 0; i<heap->size; i++){
    if(cmp(heap->array[i], data) == 0){
      index = i;
      break;
    }
  }
  if(index == -1){
    printf("Element not found\n");
    return;
  }
  // destruir el elemento que se va a eliminar
  destr(heap->array[index]);
  // Reemplazar con el último elemento
  heap->array[index] = heap->array[--heap->size];
  heapify_down(heap, index, cmp);
}

void* heap_extract_max(MaxHeap* heap, Compare cmp){
  if(heap->size == 0){
    printf("Heap is empty. Cannot delete\n");
    return NULL;
  }
  void* max = heap->array[0];
  heap->array[0] = heap->array[--heap->size];
  heapify_down(heap, 0, cmp);
  return max;
}

void heap_display(MaxHeap* heap, Print print){
  if(heap->size == 0){
    printf("Heap is empty\n");
    return;
  }
  printf("Heap: ");
  for(int i = 0; i<heap->size; i++){
    print(heap->array[i]);
  }
  printf("\n");
}

void heap_destroy(MaxHeap* heap, Destroy destr){
  for(int i = 0; i<heap->size; i++){
    destr(heap->array[i]);
  }
  free(heap->array);
  free(heap);
}