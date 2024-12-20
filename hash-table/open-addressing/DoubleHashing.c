#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
  char* key;
  int val;
} Entry;

void init_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hashtable[i] = NULL;
  }
}

unsigned int hash1(char* key) {
  unsigned int hash1 = 0;
  while (*key) {
    hash1 = (hash1 << 5) + *key++;
  }
  return hash1 % TABLE_SIZE;
}

unsigned int hash2(char* key) {
  unsigned int hash2 = 0;
  while (*key) {
    hash2 = (hash2 << 5) + *key++;
  }
  return 1 + (hash2 % (TABLE_SIZE - 1)); // Asegura que nunca sea 0
}

void insert(Entry* hashtable[], char* key, int val) {
  unsigned int index = hash1(key);
  unsigned int offset = hash2(key);
  int i = 0;

  while (hashtable[(index + i * offset) % TABLE_SIZE] != NULL) {
    if (strcmp(hashtable[(index + i * offset) % TABLE_SIZE]->key, key) == 0) {
      // Si la clave ya existe, actualizamos el valor
      hashtable[(index + i * offset) % TABLE_SIZE]->val = val;
      return;
    }
    i++;
    if (i == TABLE_SIZE) return; // Tabla llena
  }

  // Insertar en la primera celda disponible
  hashtable[(index + i * offset) % TABLE_SIZE] = (Entry*)malloc(sizeof(Entry));
  assert(hashtable[(index + i * offset) % TABLE_SIZE] != NULL);
  hashtable[(index + i * offset) % TABLE_SIZE]->key = (char*)malloc(strlen(key) + 1);
  assert(hashtable[(index + i * offset) % TABLE_SIZE]->key != NULL);
  strcpy(hashtable[(index + i * offset) % TABLE_SIZE]->key, key);
  hashtable[(index + i * offset) % TABLE_SIZE]->val = val;
}

int search(Entry* hashtable[], char* key) {
  unsigned int index = hash1(key);
  unsigned int offset = hash2(key);
  int i = 0;

  while (hashtable[(index + i * offset) % TABLE_SIZE] != NULL) {
    if (strcmp(hashtable[(index + i * offset) % TABLE_SIZE]->key, key) == 0) {
      return hashtable[(index + i * offset) % TABLE_SIZE]->val;
    }
    i++;
    if (i == TABLE_SIZE) return -1; // No encontrado
  }

  return -1;
}

void delete(Entry* hashtable[], char* key) {
  unsigned int index = hash1(key);
  unsigned int offset = hash2(key);
  int i = 0;

  while (hashtable[(index + i * offset) % TABLE_SIZE] != NULL) {
    if (strcmp(hashtable[(index + i * offset) % TABLE_SIZE]->key, key) == 0) {
      free(hashtable[(index + i * offset) % TABLE_SIZE]->key);
      free(hashtable[(index + i * offset) % TABLE_SIZE]);
      hashtable[(index + i * offset) % TABLE_SIZE] = NULL;
      return;
    }
    i++;
    if (i == TABLE_SIZE) return; // No encontrado
  }
}

void print_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hashtable[i] != NULL) {
      printf("%d: (%s, %d)\n", i, hashtable[i]->key, hashtable[i]->val);
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void free_table(Entry* hashtable[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hashtable[i] != NULL) {
      free(hashtable[i]->key);
      free(hashtable[i]);
      hashtable[i] = NULL;
    }
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

  // Imprimir la tabla
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