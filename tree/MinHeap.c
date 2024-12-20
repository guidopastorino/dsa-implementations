#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 10
#define NEG_INF -99999 // Valor arbitrariamente bajo para eliminar un nodo.

// Estructura de datos para el MinHeap.
typedef struct {
  int arr[MAX];
  int size;
} MinHeap;

// Inicializa el heap vacío.
void initialize(MinHeap* heap) {
  heap->size = 0;
}

// Intercambia dos enteros en memoria.
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Retorna el índice del padre de un nodo.
int parent(int i) {
  return (i - 1) / 2;
}

// Retorna el índice del hijo izquierdo.
int left_child(int i) {
  return 2 * i + 1;
}

// Retorna el índice del hijo derecho.
int right_child(int i) {
  return 2 * i + 2;
}

// Restaura la propiedad del MinHeap desde el nodo `i` hacia abajo.
void heapify_down(int i, int arr[], int size) {
  int left = left_child(i);
  int right = right_child(i);
  int smallest = i;

  if (left < size && arr[left] < arr[smallest]) {
    smallest = left;
  }

  if (right < size && arr[right] < arr[smallest]) {
    smallest = right;
  }

  if (i != smallest) {
    swap(&arr[i], &arr[smallest]);
    heapify_down(smallest, arr, size);
  }
}

// Restaura la propiedad del MinHeap desde el nodo `i` hacia arriba.
void heapify_up(int i, int arr[], int size) {
  while (i != 0 && arr[parent(i)] > arr[i]) {
    swap(&arr[parent(i)], &arr[i]);
    i = parent(i);
  }
}

// Inserta un elemento en el heap.
void insert(MinHeap* heap, int data) {
  if (heap->size == MAX) {
    printf("Heap is full\n");
    return;
  }
  int i = heap->size;
  heap->arr[i] = data;
  heap->size++;
  heapify_up(i, heap->arr, heap->size);
}

// Elimina un elemento específico del heap.
void delete(MinHeap* heap, int data) {
  if (heap->size == 0) {
    printf("Heap is empty\n");
    return;
  }
  int index = -1;
  for (int i = 0; i < heap->size; i++) {
    if (heap->arr[i] == data) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    printf("Element to be deleted not found\n");
    return;
  }
  heap->arr[index] = heap->arr[--heap->size];
  heapify_down(index, heap->arr, heap->size);
}

// Extrae el mínimo del heap (la raíz).
int extract_min(MinHeap* heap) {
  if (heap->size == 0) {
    printf("Heap is empty\n");
    return -1; // Valor predeterminado para un heap vacío.
  }
  int element = heap->arr[0];
  heap->arr[0] = heap->arr[--heap->size];
  heapify_down(0, heap->arr, heap->size);
  return element;
}

// Reduce el valor de un nodo en el índice `i`.
void decrease_key(MinHeap* heap, int i, int new_val) {
  if (new_val > heap->arr[i]) {
    printf("El nuevo valor es mayor que el valor actual\n");
    return;
  }
  heap->arr[i] = new_val;
  heapify_up(i, heap->arr, heap->size);
}

// Elimina un nodo en el índice `i`.
void delete_i(MinHeap* heap, int i) {
  decrease_key(heap, i, NEG_INF);
  extract_min(heap);
}

// Convierte un arreglo en un MinHeap.
void heapify(int arr[], int size) {
  for (int i = parent(size - 1); i >= 0; i--) {
    heapify_down(i, arr, size);
  }
}

// Heapsort Ascendente y Descendente con MinHeap
// Ordena un arreglo usando la propiedad del MinHeap
void heapsort(int arr[], int size, int ascending) {
  // Construir un MinHeap
  heapify(arr, size);

  for (int i = size - 1; i > 0; i--) {
    // Intercambiar el elemento de la raíz con el último elemento no ordenado
    swap(&arr[0], &arr[i]);

    // Restaurar la propiedad del MinHeap
    heapify_down(0, arr, i);
  }

  // Si se requiere orden ascendente, simplemente invierte el arreglo
  if (ascending) {
    for (int i = 0; i < size / 2; i++) {
      swap(&arr[i], &arr[size - 1 - i]);
    }
  }
}

// Imprime el contenido del heap.
void print_arr(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  MinHeap heap;
  initialize(&heap);

  printf("Insertando elementos...\n");
  insert(&heap, 10);
  insert(&heap, 20);
  insert(&heap, 5);
  insert(&heap, 15);
  insert(&heap, 30);

  printf("Heap después de inserciones:\n");
  print_arr(heap.arr, heap.size);

  printf("Extrayendo el mínimo: %d\n", extract_min(&heap));
  printf("Heap después de extraer el mínimo:\n");
  print_arr(heap.arr, heap.size);

  printf("Eliminando elemento 15...\n");
  delete(&heap, 15);
  printf("Heap después de eliminar 15:\n");
  print_arr(heap.arr, heap.size);

  printf("Disminuyendo la clave del índice 2 a 1...\n");
  decrease_key(&heap, 2, 1);
  printf("Heap después de disminuir la clave:\n");
  print_arr(heap.arr, heap.size);

  // Prueba de heapsort ascendente
  int arr[] = {12, 3, 8, 15, 6};
  int size = sizeof(arr) / sizeof(arr[0]);

  printf("Arreglo original para heapsort:\n");
  print_arr(arr, size);

  printf("Ordenando en forma ascendente con MinHeap...\n");
  heapsort(arr, size, 1);
  print_arr(arr, size);

  printf("Ordenando en forma descendente con MinHeap...\n");
  heapsort(arr, size, 0);
  print_arr(arr, size);

  return 0;
}
