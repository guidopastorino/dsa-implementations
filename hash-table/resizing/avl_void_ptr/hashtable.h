#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "types.h"
#include "avl.h"

/* Tamaño inicial de la tabla hash */
#define INITIAL_SIZE 10

/** 
  * Umbral de carga para redimensionar la tabla.
*/
#define LOAD_FACTOR_THRESHOLD 0.95

/**
  * La estructura HashTable es una implementación de una tabla hash que maneja las colisiones utilizando árboles AVL.
  * 
  * Cada "bucket" en la tabla hash puede almacenar múltiples elementos si los índices calculados por la función hash son iguales.
  * 
  * Estos elementos se organizan en árboles AVL
*/
typedef struct _HashTable {
  AVLTree** table;    /* Tabla con punteros a árboles AVL, donde cada índice maneja una colisión */
  int size;           /* Número de "buckets" o espacios disponibles en la tabla hash (capacidad total) */
  int count;          /* Número de elementos insertados en la tabla hash */
  HashFn hash;        /* Función hash que calcula el índice en el array para cada dato */
  Copy copy;          /* Función para copiar un dato a otra dirección de memoria */
  Compare cmp;        /* Función para comparar dos datos de tipo void* */
  Print print;        /* Función para imprimir el dato de un nodo */
  Destroy destr;      /* Función para destruir el dato de un nodo y liberar memoria */
} HashTable;

/// @brief Crea una nueva tabla hash con un tamaño inicial determinado.
/// @param hash Función de hash que calcula el índice para cada dato.
/// @param copy Función para copiar los datos almacenados en la tabla.
/// @param cmp Función para comparar los datos almacenados en la tabla.
/// @param print Función para imprimir los datos almacenados en la tabla.
/// @param destr Función para liberar la memoria de los datos almacenados en la tabla.
/// @return Un puntero a la nueva tabla hash creada.
HashTable* ht_create(HashFn hash, Copy copy, Compare cmp, Print print, Destroy destr);

/// @brief Inserta un dato en la tabla hash.
/// @param ht Puntero a la tabla hash donde se insertará el dato.
/// @param data El dato a insertar en la tabla hash.
void ht_insert(HashTable* ht, void* data);

/// @brief Elimina un dato de la tabla hash.
/// @param ht Puntero a la tabla hash de la cual se eliminará el dato.
/// @param data El dato a eliminar de la tabla hash.
void ht_delete(HashTable* ht, void* data);

/// @brief Busca un dato en la tabla hash.
/// @param ht Puntero a la tabla hash donde se buscará el dato.
/// @param data El dato a buscar en la tabla hash.
/// @return 1 si el dato se encuentra en la tabla hash, 0 en caso contrario.
int ht_search(HashTable* ht, void* data);

/// @brief Muestra el contenido de la tabla hash, recorriendo cada índice.
/// @param ht Puntero a la tabla hash que se desea mostrar.
void ht_display(HashTable* ht);

/// @brief Libera toda la memoria asociada a la tabla hash.
/// @param ht Puntero a la tabla hash que se desea destruir.
void ht_destroy(HashTable* ht);

#endif /* _HASHTABLE_H_ */