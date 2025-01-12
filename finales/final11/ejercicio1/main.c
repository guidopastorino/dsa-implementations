#include "hashtable.h"

int main()
{
  char *palabras[] = {
    "gato", "perro", "casa", "avion", "montana",
    "rayo", "sol", "estrella", "arbol", "rio",
    "lago", "nieve", "planta", "puerta", "libro",
    "mesa", "silla", "ventana", "flor", "cielo"
  };

  int cantPalabras = sizeof(palabras) / sizeof(palabras[0]);

  // Crear tabla hash
  printf("Creando tabla hash...\n");
  HashTable *ht = ht_create();

  // Insertar palabras
  printf("Insertando palabras en la tabla hash...\n");
  for (int i = 0; i < cantPalabras; i++)
  {
    printf("Insertando: %s\n", palabras[i]);
    ht_insert(ht, palabras[i]);
  }

  // Mostrar tabla
  printf("\nTabla hash después de insertar:\n");
  ht_display(ht);

  printf("Existe prefijo \'gat\'? %s\n", ht_search_prefix(ht, "gat") ? "Sí" : "No");
  printf("Existe prefijo \'hola\'? %s\n", ht_search_prefix(ht, "hola") ? "Sí" : "No");

  printf("Cantidad de palabras que comienzan con \'a\': %d\n", ht_search_char(ht, 'a'));

  // Eliminar algunas palabras
  printf("\nEliminando palabras de la tabla hash...\n");
  char *palabrasEliminar[] = {"gato", "montana", "rio", "libro"};
  int cantEliminar = sizeof(palabrasEliminar) / sizeof(palabrasEliminar[0]);
  for (int i = 0; i < cantEliminar; i++)
  {
    printf("Eliminando: %s\n", palabrasEliminar[i]);
    ht_delete(ht, palabrasEliminar[i]);
  }

  // Mostrar tabla después de eliminar
  printf("\nTabla hash después de eliminar algunas palabras:\n");
  ht_display(ht);

  // Reinsertar palabras eliminadas
  printf("\nReinsertando palabras eliminadas...\n");
  for (int i = 0; i < cantEliminar; i++)
  {
    printf("Reinsertando: %s\n", palabrasEliminar[i]);
    ht_insert(ht, palabrasEliminar[i]);
  }

  // Mostrar tabla después de reinserciones
  printf("\nTabla hash después de reinserciones:\n");
  ht_display(ht);

  // Destruir la tabla hash
  printf("\nDestruyendo la tabla hash...\n");
  ht_destroy(ht);

  printf("Pruebas finalizadas.\n");
  return 0;
}
