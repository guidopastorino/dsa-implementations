#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TABLE_SIZE 10

typedef struct {
  char* key;
  int val;
  int distance;
} Entry;

typedef Entry* HashTable[TABLE_SIZE]; // Entry* hashtable[] (for params)

Entry* create_node(char* key, int val, int distance){
  Entry* node = (Entry*)malloc(sizeof(Entry));
  assert(node != NULL);
  node->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(node->key != NULL);
  strcpy(node->key, key);
  node->val = val;
  node->distance = distance;
  return node;
}

void hashtable_init(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++)
    hashtable[i] = NULL;
}

unsigned int hash(char* key){
  unsigned int hash = 0;
  while(*key){
    hash = (hash << 5) + *key++;
  }
  return hash % TABLE_SIZE;
}

void hashtable_insert(HashTable hashtable, char* key, int val){
  unsigned int index = hash(key);
  int distance = 0;

  Entry* node = create_node(key, val, distance);

  while(hashtable[index] != NULL){
    if(hashtable[index]->distance < distance){
      Entry* temp = hashtable[index];
      hashtable[index] = node;
      node = temp;
    }
    distance++;
    index = (index + 1) % TABLE_SIZE;
  }

  hashtable[index] = node;
  node->distance = distance;
}

int hashtable_search(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  int distance = 0;

  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      return hashtable[index]->val;
    }
    if(hashtable[index]->distance < distance) break;
    distance++;
    index = (index + 1) % TABLE_SIZE;
  }
  return -1;
}

void hashtable_delete(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  int distance = 0;

  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      free(hashtable[index]->key);
      free(hashtable[index]);
      hashtable[index] = NULL;

      unsigned int next_index = (index + 1) % TABLE_SIZE;

      while(hashtable[next_index] != NULL && hashtable[next_index]->distance < distance){
        hashtable[next_index]->distance--;
        hashtable[index] = hashtable[next_index];
        hashtable[next_index] = NULL;
        index = next_index;
        next_index = (index + 1) % TABLE_SIZE;
      }

      return;
    }

    if(hashtable[index]->distance < distance) break;
    distance++;
    index = (index + 1) % TABLE_SIZE;
  }
}

void hashtable_print(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      printf("%d: ", i);
      printf("(%s, %d) - distance: %d\n", hashtable[i]->key, hashtable[i]->val, hashtable[i]->distance);
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void hashtable_free(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      free(hashtable[i]->key);
      free(hashtable[i]);
    }
  }
  hashtable_init(hashtable);
}

int main() {
  HashTable hashtable;
  hashtable_init(hashtable);

  // Insertar elementos
  printf("Insertando elementos en la tabla hash...\n");
  hashtable_insert(hashtable, "apple", 10);
  hashtable_insert(hashtable, "banana", 20);
  hashtable_insert(hashtable, "cherry", 30);
  hashtable_insert(hashtable, "date", 40);
  hashtable_insert(hashtable, "elderberry", 50);
  hashtable_insert(hashtable, "fig", 60);
  hashtable_insert(hashtable, "grape", 70);
  hashtable_insert(hashtable, "honeydew", 80);

  // Imprimir estado de la tabla
  printf("\nEstado de la tabla después de las inserciones:\n");
  hashtable_print(hashtable);

  // Buscar elementos
  printf("\nBuscando elementos:\n");
  printf("Valor de 'apple': %d\n", hashtable_search(hashtable, "apple"));
  printf("Valor de 'cherry': %d\n", hashtable_search(hashtable, "cherry"));
  printf("Valor de 'kiwi' (inexistente): %d\n", hashtable_search(hashtable, "kiwi"));

  // Eliminar elementos
  printf("\nEliminando elementos 'banana' y 'grape':\n");
  hashtable_delete(hashtable, "banana");
  hashtable_delete(hashtable, "grape");

  // Imprimir estado de la tabla después de eliminaciones
  printf("\nEstado de la tabla después de las eliminaciones:\n");
  hashtable_print(hashtable);

  // Liberar memoria
  printf("\nLiberando memoria de la tabla hash...\n");
  hashtable_free(hashtable);

  // Estado final
  printf("Estado final de la tabla tras liberar memoria:\n");
  hashtable_print(hashtable);

  return 0;
}
