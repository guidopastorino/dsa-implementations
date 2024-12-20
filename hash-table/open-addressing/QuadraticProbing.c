#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
  char* key;
  int val;
} Entry;

void initialize_table(Entry* hashtable[]){
  for(int i = 0; i < TABLE_SIZE; i++){
    hashtable[i] = NULL;
  }
}

unsigned int hash(char* key){
  unsigned int hash = 0;
  while(*key){
    hash = (hash << 5) + *key++;
  }
  return hash % TABLE_SIZE;
}

void insert(Entry* hashtable[], char* key, int val){
  unsigned int index = hash(key);
  unsigned int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      hashtable[index]->val = val;
      return;
    }
    index = (originalIndex + i * i) % TABLE_SIZE;
    i++;
    if(i == TABLE_SIZE) return;  // Si la tabla está llena, no se puede insertar más
  }
  hashtable[index] = (Entry*)malloc(sizeof(Entry));
  assert(hashtable[index] != NULL);
  hashtable[index]->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(hashtable[index]->key != NULL);
  strcpy(hashtable[index]->key, key);
  hashtable[index]->val = val;
}

int search(Entry* hashtable[], char* key){
  unsigned int index = hash(key);
  unsigned int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      return hashtable[index]->val;
    }
    index = (originalIndex + i * i) % TABLE_SIZE;
    i++;
    if(i == TABLE_SIZE) return -1;  // Si la tabla se recorre completamente, no se encuentra
  }
  return -1;
}

void delete(Entry* hashtable[], char* key){
  int index = hash(key);
  int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      free(hashtable[index]->key);
      free(hashtable[index]);
      hashtable[index] = NULL;
      return;
    }
    index = (originalIndex + i * i) % TABLE_SIZE;
    i++;
    if(i == TABLE_SIZE) return;  // Si la tabla se recorre completamente, no se elimina
  }
}

void print_table(Entry* hashtable[]){
  for(int i = 0; i < TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      printf("%d: (%s, %d)\n", i, hashtable[i]->key, hashtable[i]->val);
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void free_table(Entry* hashtable[]){
  for(int i = 0; i < TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      free(hashtable[i]->key);
      free(hashtable[i]);
      hashtable[i] = NULL;
    }
  }
}

int main(){
  Entry* hashtable[TABLE_SIZE];
  initialize_table(hashtable);

  // Insertar elementos
  insert(hashtable, "Apple", 10);
  insert(hashtable, "Banana", 20);
  insert(hashtable, "Orange", 30);
  insert(hashtable, "Mango", 40);
  insert(hashtable, "Pineapple", 50);
  insert(hashtable, "Grapes", 60);
  insert(hashtable, "Watermelon", 70);

  printf("Tabla después de inserciones:\n");
  print_table(hashtable);

  // Buscar algunos elementos
  printf("\nBuscar 'Apple': %d\n", search(hashtable, "Apple"));
  printf("Buscar 'Grapes': %d\n", search(hashtable, "Grapes"));
  printf("Buscar 'Banana': %d\n", search(hashtable, "Banana"));
  printf("Buscar 'Pineapple': %d\n", search(hashtable, "Pineapple"));
  printf("Buscar 'Strawberry': %d\n", search(hashtable, "Strawberry"));  // Elemento no existente

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