#ifndef _HT_CLIENTES_
#define _HT_CLIENTES_

#include "types.h"

#define INITIAL_SIZE 10
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct {
  char* nombre;
  char* apellido;
  char* direccion;
  int DNI;
  char* telefono;
} Cliente;

typedef struct _HashNode {
  Cliente* cliente;
  struct _HashNode* next;
} HashNode;

typedef struct {
  HashNode** table;
  int size;            // Tamaño actual de la tabla
  int count;           // Número de elementos en la tabla
} HashTableClientes;

HashTableClientes* ht_clientes_create();
void ht_clientes_insert(HashTableClientes* ht, Cliente* cliente);
// void ht_clientes_delete(HashTableClientes* ht, int DNI);
Cliente* ht_clientes_search(HashTableClientes* ht, int DNI);
void ht_clientes_display(HashTableClientes* ht);
void ht_clientes_destroy(HashTableClientes* ht);

#endif