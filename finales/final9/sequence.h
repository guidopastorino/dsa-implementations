#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Nodo {
  int data;
  struct _Nodo* next;
  int cantidadMenores;
} Nodo;

typedef struct {
  Nodo* head;
  int size;
} Sequence;

/* Crea una secuencia */
Sequence* crear_sequencia();

/* Devuelve un arreglo con los números que tienen la misma cantidadMenores */
void buscar_por_cantidadMenores(Sequence*, int);

/* Inserta un número en una posición */
void insertar_en_posicion(Sequence*, int, int);

/* Elimina el nodo en la posición especifica */
void borrar_en_posicion(Sequence*, int);

/* Ordena la lista enlazada en base a la cantidad menores */
/* Se utiliza el algoritmo de Insertion Sort */
void ordenar_por_cantidadMenores(Sequence*, int);

/* Imprime la secuencia */
void imprimir_secuencia(Sequence*);

/* Libera la secuencia */
void liberar_secuencia(Sequence*);

#endif