#include "sequence.h"

int main() {
  // Crear la secuencia
  Sequence* seq = crear_sequencia();

  // Insertar elementos en la secuencia
  printf("Insertando números en la secuencia...\n");
  insertar_en_posicion(seq, 12, 0); // 12 en posición 0
  insertar_en_posicion(seq, 30, 1); // 30 en posición 1
  insertar_en_posicion(seq, 1, 2);  // 1 en posición 2
  insertar_en_posicion(seq, 2, 3);  // 2 en posición 3

  // Mostrar la secuencia inicial
  printf("Secuencia inicial:\n");
  imprimir_secuencia(seq);

  // Buscar elementos con cantidadMenores = 1
  printf("\nBuscando elementos con cantidadMenores = 1...\n");
  buscar_por_cantidadMenores(seq, 1);

  // Ordenar por cantidadMenores
  printf("\nOrdenando la secuencia por cantidadMenores...\n");
  ordenar_por_cantidadMenores(seq, 1);

  // Mostrar la secuencia ordenada
  printf("Secuencia ordenada:\n");
  imprimir_secuencia(seq);


  // Eliminar elemento en posición 2
  printf("\nEliminando elemento en posición 2...\n");
  borrar_en_posicion(seq, 2);

  // Mostrar la secuencia final
  printf("Secuencia después de eliminar en posición 2:\n");
  imprimir_secuencia(seq);

  // Liberar la memoria de la secuencia
  liberar_secuencia(seq);

  return 0;
}
