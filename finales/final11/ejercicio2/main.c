#include "list.h"

// Función para copiar palabras
void* copyString(void* data) {
  char* str = (char*)data;
  char* copy = (char*)malloc(strlen(str) + 1);
  strcpy(copy, str);
  return copy;
}

// Función de comparación para palabras
int compareStrings(void* a, void* b) {
  return strcmp((char*)a, (char*)b);
}

// Función para imprimir palabras
void printString(void* data) {
  printf("%s -> ", (char*)data);
}

// Función para destruir palabras
void destroyString(void* data) {
  free(data);
}

int main() {
  // Crear listas enlazadas
  Node* list1 = NULL;
  Node* list2 = NULL;
  Node* list3 = NULL;

  // Insertar palabras en las listas
  glist_insert(&list1, "banana", copyString);
  glist_insert(&list1, "apple", copyString);
  glist_insert(&list1, "cherry", copyString);

  glist_insert(&list2, "grape", copyString);
  glist_insert(&list2, "fig", copyString);
  glist_insert(&list2, "date", copyString);

  glist_insert(&list3, "kiwi", copyString);
  glist_insert(&list3, "lemon", copyString);
  glist_insert(&list3, "mango", copyString);

  // Mostrar listas originales
  printf("Lista 1 original:\n");
  glist_display(list1, printString);

  printf("Lista 2 original:\n");
  glist_display(list2, printString);

  printf("Lista 3 original:\n");
  glist_display(list3, printString);

  // Fusionar las tres listas
  Node* mergedList = glist_merge_lists(list1, list2, list3, copyString, compareStrings);
  printf("\nLista fusionada:\n");
  glist_display(mergedList, printString);

  // Ordenar la lista fusionada
  glist_insertion_sort(&mergedList, compareStrings);
  printf("\nLista fusionada y ordenada:\n");
  glist_display(mergedList, printString);

  // Destruir todas las listas
  glist_destroy(&list1, destroyString);
  glist_destroy(&list2, destroyString);
  glist_destroy(&list3, destroyString);
  glist_destroy(&mergedList, destroyString);

  return 0;
}