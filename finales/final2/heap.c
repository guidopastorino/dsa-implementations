#include "heap.h"

void heap_init(MaxHeap* heap){
  heap->size = 0;
}

static void swap(Usuario* usuario1, Usuario* usuario2){
  Usuario temp = *usuario1;
  *usuario1 = *usuario2;
  *usuario2 = temp;
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

  if(left < heap->size && cmp(heap->usuarios[left], heap->usuarios[largest]) > 0){
    largest = left;
  }

  if(right < heap->size && cmp(heap->usuarios[right], heap->usuarios[largest]) > 0){
    largest = right;
  }

  if(largest != i){
    swap(&heap->usuarios[i], &heap->usuarios[largest]);
    heapify_down(heap, largest, cmp);
  }
}

void heapify_up(MaxHeap* heap, int i, Compare cmp){
  while(i != 0 && cmp(heap->usuarios[i], heap->usuarios[parent(i)]) > 0){
    swap(&heap->usuarios[i], &heap->usuarios[parent(i)]);
    i = parent(i);
  }
}

void heap_insert(MaxHeap* heap, Usuario usuario, Compare cmp){
  if(heap->size == MAXHEAP_SIZE){
    printf("Heap is full. Cannot insert\n");
    return;
  }
  heap->usuarios[heap->size] = usuario;
  heapify_up(heap, heap->size, cmp);
  heap->size++;
}

void heap_delete(MaxHeap* heap, int dni, Compare cmp){
  if(heap->size == 0){
    printf("Heap is empty. Cannot delete\n");
    return;
  }
  int index = -1;
  for(int i = 0; i<heap->size; i++){
    if(heap->usuarios[i].dni == dni){
      index = i;
    }
  }
  if(index == -1){
    printf("User with DNI %d not found\n", dni);
    return;
  }
  heap->usuarios[index] = heap->usuarios[--heap->size];
  heapify_down(heap, index, cmp);
}

Usuario heap_extract_max(MaxHeap* heap, Compare cmp){
  if(heap->size == 0){
    printf("Heap is empty. Cannot delete\n");
    return (Usuario){0, 0, 0, 0};
  }
  Usuario usuario = heap->usuarios[0];
  heap->usuarios[0] = heap->usuarios[--heap->size];
  heapify_down(heap, 0, cmp);
  return usuario;
}

void heap_display(MaxHeap heap, Print print){
  for(int i = 0; i<heap.size; i++){
    print(heap.usuarios[i]);
  }
}