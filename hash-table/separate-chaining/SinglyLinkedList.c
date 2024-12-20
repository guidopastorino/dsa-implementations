#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _Entry {
  char* key;
  int val;
  struct _Entry* next;
} Entry;

#define TABLE_SIZE 10

void init_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hashtable[i] = NULL;
  }
}

unsigned int hash(char* key) {
  unsigned int hash = 0;
  while (*key) {
    hash = (hash << 5) + *key++;
  }
  return hash % TABLE_SIZE;
}

Entry* create_node(char* key, int val) {
  Entry* node = (Entry*)malloc(sizeof(Entry));
  assert(node != NULL);
  node->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(node->key != NULL);
  strcpy(node->key, key);
  node->val = val;
  node->next = NULL;
  return node;
}

void insert(Entry* hashtable[], char* key, int val) {
  unsigned int index = hash(key);

  if (hashtable[index] == NULL) {
    // Crear nodo si el bucket está vacío
    hashtable[index] = create_node(key, val);
    return;
  }

  Entry* current = hashtable[index];

  // Recorrer la lista enlazada en el bucket
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      current->val = val; // Actualizar valor si la clave ya existe
      return;
    }
    if (current->next == NULL) break;
    current = current->next;
  }

  // Agregar nuevo nodo al final
  current->next = create_node(key, val);
}

int search(Entry* hashtable[], char* key) {
  unsigned int index = hash(key);
  Entry* current = hashtable[index]; // Se ubica en el 'head' de la lista

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->val;
    }
    current = current->next;
  }

  return -1; // No encontrado
}

void delete(Entry* hashtable[], char* key) {
  unsigned int index = hash(key);
  Entry* current = hashtable[index];
  Entry* prev = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        // Si es el primer nodo, actualizar el bucket
        hashtable[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current->key);
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

void print_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry* current = hashtable[i];
    printf("%d: ", i);
    while (current != NULL) {
      printf("(%s, %d) -> ", current->key, current->val);
      current = current->next;
    }
    printf("NULL\n");
  }
}

void free_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry* current = hashtable[i];
    while (current != NULL) {
      Entry* temp = current;
      current = current->next;
      free(temp->key);
      free(temp);
    }
    hashtable[i] = NULL; // Resetear el bucket
  }
}

int main() {
  Entry* hashtable[TABLE_SIZE];
  init_table(hashtable);

  // Insertar elementos
  insert(hashtable, "Apple", 10);
  insert(hashtable, "Banana", 20);
  insert(hashtable, "Orange", 30);
  insert(hashtable, "Mango", 40);
  insert(hashtable, "Pineapple", 50);
  insert(hashtable, "Grapes", 60);
  insert(hashtable, "Watermelon", 70);

  // Imprimir tabla
  printf("Tabla después de inserciones:\n");
  print_table(hashtable);

  // Buscar elementos
  printf("\nBuscar 'Apple': %d\n", search(hashtable, "Apple"));
  printf("Buscar 'Grapes': %d\n", search(hashtable, "Grapes"));
  printf("Buscar 'Banana': %d\n", search(hashtable, "Banana"));
  printf("Buscar 'Strawberry': %d\n", search(hashtable, "Strawberry")); // No existente

  // Eliminar un elemento
  delete(hashtable, "Banana");
  printf("\nTabla después de eliminar 'Banana':\n");
  print_table(hashtable);

  // Intentar buscar el elemento eliminado
  printf("\nBuscar 'Banana' después de eliminar: %d\n", search(hashtable, "Banana"));

  // Liberar memoria
  free_table(hashtable);

  return 0;
}