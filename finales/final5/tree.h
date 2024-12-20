#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum color { Rojo, Azul, Neutro } Color;

typedef struct Nodo_ {
  char* cdato;
  Color colorNodo;
  struct Nodo_ *der, *izq;
} Nodo;

typedef Nodo* ArbolBinarioColoreado;

// Retorna el color del Arbol.
Color color(ArbolBinarioColoreado inicio);

// Retorna la cantidad de hojas puras.
int CantidadPuras(ArbolBinarioColoreado inicio);

#endif