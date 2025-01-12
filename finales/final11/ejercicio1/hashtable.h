#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INITIAL_SIZE 10
#define GROWTH_FACTOR 2
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct _Entry {
  char* key;
  int is_deleted; // Bandera para alertar si una posición fue eliminada o no
} Entry;

typedef struct _HashTable {
  Entry** table;
  int count;
  int size;
} HashTable;

HashTable* ht_create();
void ht_insert(HashTable* ht, char* key);
int ht_search_prefix(HashTable* ht, char* prefix);
int ht_search_char(HashTable* ht, char c);
void ht_delete(HashTable* ht, char* key);
void ht_display(HashTable* ht);
void ht_destroy(HashTable* ht);

#endif