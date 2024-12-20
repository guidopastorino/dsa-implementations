#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 9

typedef struct {
  int* arr;
} HashTable;

HashTable* ht_create();
void ht_insert(HashTable* ht, int x);
int ht_search(HashTable* ht, int x);
int ht_display(HashTable* ht);
int ht_destroy(HashTable* ht);

#endif