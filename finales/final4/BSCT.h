#ifndef _BSCT_H_
#define _BSCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef void (*VisitorFuncInt)(int data, void* extra_data);

// Estructura
typedef struct {
  int* arr;
  int size;
  int capacity;
} BSCT;

BSCT bsct_foreach(BSCT *tree, VisitorFuncInt visit, void *extra_data);

/* Tome un arreglo y devuelva un árbol binario completo ordenado con los elementos del arreglo original */
BSCT* to_bsctree(int tree[]);

void cambio_greedy(int C);

#endif