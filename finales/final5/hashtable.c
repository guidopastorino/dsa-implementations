#include "hashtable.h"

HashTable* ht_create(){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->arr = (int*)calloc(MAX_SIZE, sizeof(int));
  assert(ht->arr != NULL);
  return ht;
}

static unsigned int hash(int x){
  return x % MAX_SIZE;
}

static unsigned int hash2(int x) {
  return 1 + (x % (MAX_SIZE - 1));
}

void ht_insert(HashTable* ht, int x){
  unsigned int index = hash(x);
  int i = 0;

  while(ht->arr[index] != 0){
    index = (index + ++i) % MAX_SIZE;
    if(i == MAX_SIZE) return;
  }

  // insertar el elemento
  ht->arr[index] = x;
}

int ht_search(HashTable* ht, int x){
  unsigned int index = hash(x);
  int i = 0;

  while(ht->arr[index] != 0){
    if(ht->arr[index] == x){
      return x;
    }
    index = (index + ++i) % MAX_SIZE;
    if(i == MAX_SIZE) return -1; // valor de error
  }

  // insertar el elemento
  return -1; // valor de error
}

int ht_display(HashTable* ht){
  for(int i = 0; i<MAX_SIZE; i++){
    if(ht->arr[i] != 0){
      printf("%d: %d\n", i, ht->arr[i]);
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

int ht_destroy(HashTable* ht){
  free(ht->arr);
  free(ht);
}