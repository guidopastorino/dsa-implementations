#include "heap.h"

int main() {
  BHeap *heap = create_heap();

  // Insertamos algunos elementos en el Min-Heap
  insert(heap, 10);
  insert(heap, 15);
  insert(heap, 20);
  insert(heap, 30);
  insert(heap, 5);

  printf("Heap antes de borrar el máximo: ");
  print_heap(heap);

  // Llamamos a la función para borrar el máximo
  int max = bheap_erase_max(heap);
  printf("El máximo borrado es: %d\n", max);

  printf("Heap después de borrar el máximo: ");
  print_heap(heap);

  destroy_heap(heap);
  return 0;
}