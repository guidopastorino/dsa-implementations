#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

#define INITIAL_SIZE 10        // Tamaño inicial de la tabla
#define GROWTH_FACTOR 2        // Factor de crecimiento: aumenta el tamaño por 2
#define LOAD_FACTOR_THRESHOLD 0.75 // Umbral de carga: se redimensiona cuando esté al 75% lleno

typedef struct {
  BSTNode** table;
  int count;
  int size;
} HashTable;

/// @brief Crea una nueva tabla hash y la inicializa.
/// @return Puntero a la nueva tabla hash creada.
HashTable* ht_create();

/// @brief Inserta un valor en la tabla hash.
/// @param ht Puntero a la tabla hash donde se va a insertar el valor.
/// @param data Valor que se va a insertar en la tabla hash.
void ht_insert(HashTable* ht, int data);

/// @brief Elimina un valor de la tabla hash.
/// @param ht Puntero a la tabla hash donde se encuentra el valor.
/// @param data Valor que se desea eliminar de la tabla hash.
void ht_delete(HashTable* ht, int data);

/// @brief Busca un valor en la tabla hash.
/// @param ht Puntero a la tabla hash donde se va a buscar el valor.
/// @param data Valor que se busca en la tabla hash.
/// @return 1 si el valor se encuentra en la tabla hash, 0 si no.
int ht_search(HashTable* ht, int data);

/// @brief Imprime el contenido de la tabla hash.
/// @param ht Puntero a la tabla hash que se va a imprimir.
void ht_print(HashTable* ht);

/// @brief Destruye la tabla hash, liberando la memoria utilizada.
/// @param ht Puntero a la tabla hash que se va a destruir.
void ht_destroy(HashTable* ht);

#endif /* _HASHTABLE_H_ */