#include "hashtable.h"
#include <time.h>

/// @brief Genera un número aleatorio entre un rango [min, max].
/// @param min Límite inferior del rango.
/// @param max Límite superior del rango.
/// @return Un número aleatorio entre min y max (inclusive).
int rand_num(int min, int max) {
  if (min > max) {
    fprintf(stderr, "Error: min no puede ser mayor que max.\n");
    exit(EXIT_FAILURE);
  }
  return min + (rand() % (max - min + 1));
}

int main() {
  // Crear una nueva tabla hash
  HashTable* ht = ht_create();
  printf("Tabla hash creada.\n");

  printf("Insertando valores en la tabla hash:\n");
  for (int i = 0; i < 100; i++) {
    ht_insert(ht, rand_num(10, 100));
  }

  // Imprimir el contenido de la tabla hash
  printf("\nContenido de la tabla hash:\n");
  ht_print(ht);

  // Destruir la tabla hash
  ht_destroy(ht);

  return 0;
}