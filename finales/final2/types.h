#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int dni;
  int tiempoEnEspera; // en segundos
  int esPremium;
  int tiempoDeMembresia; // en segundos
} Usuario;

typedef int (*Compare)(Usuario usuario1, Usuario usuario2);
typedef void (*Print)(Usuario usuario);

#endif