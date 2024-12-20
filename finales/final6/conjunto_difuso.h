#ifndef _CONJUNTO_DIFUSO_H_
#define _CONJUNTO_DIFUSO_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Función para copiar un dato
typedef void* (*Copy)(void* data);
// Función para eliminar un dato
typedef void (*Destroy)(void* data);
// Función para imprimir un dato
typedef void (*Print)(void* data);
// Función para comparar dos datos (se compararán en base a su grado de pertenencia)
typedef int (*Compare)(void* data1, void* data2);

// Representaremos el Conjunto Difuso como una lista enlazada simple
typedef struct _CDNodo {
  void* data;
  double gp; // grado de pertenencia del nodo
  struct _CDNodo* next;
} CDNodo;

typedef struct ConjuntoDifuso {
  CDNodo* head;
  int size;
} CD;

/* Crea una estructura de tipo CD */
CD* cd_crear();

/* Agrega el elemento al conjunto con el grado de pertenencia dado */
void cd_agregar(CD* cd, void* data, double gp, Copy copy, Compare cmp);

/* Modifica el grado de pertenencia del elemento dado. Si el nuevo grado de pertenencia es 0 el elemento debe será eliminado */
void cd_modificar_gp(CD* cd, void* data, double gp, Compare cmp, Destroy destr);

/* Toma dos conjuntos difusos A y B y devuelve un int indicando si A es subconjunto de B */
int cd_subconjunto(CD* A, CD* B, Compare cmp);

/* Toma dos conjuntos difusos y devuelve un nuevo conjunto con la unión de ambos */
CD* cd_union(CD* A, CD* B, Copy copy, Compare cmp);

/* Tome dos conjuntos difusos y devuelve un nuevo conjunto con la diferencia entre ambos */
CD* cd_diferencia(CD* A, CD* B, Copy copy, Compare cmp);

#endif