#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 10
#define NEG_INF -99999

typedef struct {
  int arr[MAX];
  int size;
} MaxHeap;

// Inicializa un MaxHeap vacío.
void initialize(MaxHeap* heap) {
  heap->size = 0;
}

// Intercambia los valores de dos enteros.
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Devuelve el índice del padre de un nodo.
int parent(int i) {
  return (i - 1) / 2;
}

// Devuelve el índice del hijo izquierdo de un nodo.
int left_child(int i) {
  return 2 * i + 1;
}

// Devuelve el índice del hijo derecho de un nodo.
int right_child(int i) {
  return 2 * i + 2;
}

// Ajusta un nodo hacia abajo para restaurar la propiedad del MaxHeap.
void heapify_down(int i, int arr[], int size) {
  int left = left_child(i);
  int right = right_child(i);
  int largest = i;

  if (left < size && arr[left] > arr[largest]) {
    largest = left;
  }
  if (right < size && arr[right] > arr[largest]) {
    largest = right;
  }

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify_down(largest, arr, size);
  }
}

// Ajusta un nodo hacia arriba para restaurar la propiedad del MaxHeap.
void heapify_up(int i, int arr[], int size) {
  while (i != 0 && arr[parent(i)] < arr[i]) {
    swap(&arr[parent(i)], &arr[i]);
    i = parent(i);
  }
}

// Inserta un elemento en el MaxHeap.
void insert(MaxHeap* heap, int data) {
  if (heap->size == MAX) {
    printf("Heap is full\n");
    return;
  }
  int i = heap->size;
  heap->arr[i] = data;
  heap->size++;
  heapify_up(i, heap->arr, heap->size);
}

// Elimina un elemento específico del MaxHeap.
void delete(MaxHeap* heap, int data) {
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

// Extrae y devuelve el elemento máximo del MaxHeap.
int extract_max(MaxHeap* heap) {
  if (heap->size == 0) {
    printf("Heap is empty\n");
    return -1;
  }
  int element = heap->arr[0];
  heap->arr[0] = heap->arr[--heap->size];
  heapify_down(0, heap->arr, heap->size);
  return element;
}

// Incrementa el valor de un nodo en el MaxHeap.
void increase_key(MaxHeap* heap, int i, int new_val) {
  if (new_val < heap->arr[i]) {
    printf("El nuevo valor es menor que el valor actual\n");
    return;
  }
  heap->arr[i] = new_val;
  heapify_up(i, heap->arr, heap->size);
}

// Elimina un nodo en el índice dado del MaxHeap.
void delete_i(MaxHeap* heap, int i) {
  increase_key(heap, i, NEG_INF);
  extract_max(heap);
}

// Convierte un arreglo en un MaxHeap.
void heapify(int arr[], int size) {
  for (int i = parent(size - 1); i >= 0; i--) {
    heapify_down(i, arr, size);
  }
}

// Heapsort Ascendente y Descendente con MaxHeap
// Ordena un arreglo usando la propiedad del MaxHeap
void heapsort(int arr[], int size, int ascending) {
  // Construir un MaxHeap
  heapify(arr, size);

  for (int i = size - 1; i > 0; i--) {
    // Intercambiar el elemento de la raíz con el último elemento no ordenado
    swap(&arr[0], &arr[i]);

    // Restaurar la propiedad del MaxHeap
    heapify_down(0, arr, i);
  }

  // Si se requiere orden descendente, simplemente invierte el arreglo
  if (!ascending) {
    for (int i = 0; i < size / 2; i++) {
      swap(&arr[i], &arr[size - 1 - i]);
    }
  }
}


// Imprime el contenido de un arreglo.
void print_arr(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  MaxHeap heap;
  initialize(&heap);

  printf("Insertando elementos...\n");
  insert(&heap, 10);
  insert(&heap, 20);
  insert(&heap, 5);
  insert(&heap, 15);
  insert(&heap, 30);

  printf("Heap después de inserciones:\n");
  print_arr(heap.arr, heap.size);

  printf("Extrayendo el máximo: %d\n", extract_max(&heap));
  printf("Heap después de extraer el máximo:\n");
  print_arr(heap.arr, heap.size);

  printf("Eliminando elemento 15...\n");
  delete(&heap, 15);
  printf("Heap después de eliminar 15:\n");
  print_arr(heap.arr, heap.size);

  printf("Aumentando la clave del índice 2 a 25...\n");
  increase_key(&heap, 2, 25);
  printf("Heap después de aumentar la clave:\n");
  print_arr(heap.arr, heap.size);

  printf("Convirtiendo un arreglo en MaxHeap:\n");
  int arr[] = {12, 3, 8, 15, 6};
  int size = sizeof(arr) / sizeof(arr[0]);
  heapify(arr, size);
  print_arr(arr, size);

  printf("Ordenando arreglo con heapsort en forma ascendente...\n");
  heapsort(arr, size, 1);
  print_arr(arr, size);

  printf("Ordenando arreglo con heapsort en forma descendente...\n");
  heapsort(arr, size, 0);
  print_arr(arr, size);

  return 0;
}