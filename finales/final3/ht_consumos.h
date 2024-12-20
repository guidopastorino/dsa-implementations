#ifndef HT_CONSUMOS_H
#define HT_CONSUMOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INITIAL_HTCONSUMOS_SIZE 16
#define LOAD_FACTOR_THRESHOLD 0.75

// Estructura de Consumo
typedef struct {
  char* fecha;
  int monto;
  int DNI;
} Consumo;

// Nodo de la tabla hash
typedef struct HashNodeConsumo {
  Consumo* consumo;
  struct HashNodeConsumo* next; // Para manejo de colisiones
} HashNodeConsumo;

// Tabla hash
typedef struct {
  HashNodeConsumo** table;
  int size;  // Tamaño actual de la tabla
  int count; // Número de elementos en la tabla
} HashTableConsumos;

// Funciones públicas
HashTableConsumos* ht_consumos_create();
void ht_consumos_insert(HashTableConsumos* ht, Consumo* consumo);
Consumo* ht_consumos_search(HashTableConsumos* ht, int DNI, char* fecha);
void ht_consumos_display(HashTableConsumos* ht);
void ht_consumos_destroy(HashTableConsumos* ht);

#endif
