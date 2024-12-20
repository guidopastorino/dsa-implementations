#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
  char* key;
  int val;
} Entry;

void init_hashtable(Entry* hashtable[]){
  for(int i = 0; i<TABLE_SIZE; i++){
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
  int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    // Si ya existe, actualizamos su valor
    if(strcmp(hashtable[index]->key, key) == 0){
      hashtable[index]->val = val;
      return;
    }
    index = (originalIndex + ++i) % TABLE_SIZE;
    // Tabla llena
    if(i == TABLE_SIZE){
      return;
    }
  }
  // Inserción en una celda vacía
  hashtable[index] = (Entry*)malloc(sizeof(Entry));
  assert(hashtable[index] != NULL);
  hashtable[index]->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(hashtable[index]->key != NULL);
  strcpy(hashtable[index]->key, key);
  hashtable[index]->val = val;
}

void delete(Entry* hashtable[], char* key){
  int index = hash(key);
  int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    // Si encontramos al entry, lo eliminamos
    if(strcmp(hashtable[index]->key, key) == 0){
      free(hashtable[index]->key);
      free(hashtable[index]);
      hashtable[index] = NULL;
      return;
    } else {
      index = (originalIndex + ++i) % TABLE_SIZE;
      // Tabla llena
      if(i == TABLE_SIZE){
        return;
      }
    }
  }
}

int search(Entry* hashtable[], char* key){
  int index = hash(key);
  int originalIndex = index;
  int i = 0;
  while(hashtable[index] != NULL){
    if(strcmp(hashtable[index]->key, key) == 0){
      return hashtable[index]->val;
    }
    index = (index + ++i) % TABLE_SIZE;
    if(i == TABLE_SIZE) return -1;
  }
  return -1;
}

void print_table(Entry* hashtable[]){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      printf("%d: (%s, %d)\n", i, hashtable[i]->key, hashtable[i]->val);
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void free_table(Entry* hashtable[]){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      free(hashtable[i]->key);
      free(hashtable[i]);
      hashtable[i] = NULL;
    }
  }
}

int main() {
  Entry *hashtable[TABLE_SIZE];
  init_hashtable(hashtable);

  insert(hashtable, "Henry", 8);
  insert(hashtable, "Charlie", 3);
  insert(hashtable, "Guido", 0);
  insert(hashtable, "Alice", 1);
  insert(hashtable, "Michael", 3);
  insert(hashtable, "David", 4);
  insert(hashtable, "Eve", 5);
  insert(hashtable, "Frank", 6);
  insert(hashtable, "Grace", 7);
  insert(hashtable, "Isabel", 9);

  print_table(hashtable);

  free_table(hashtable);

  return 0;
}