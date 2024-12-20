#include "tree.h"

void contar_colores(ArbolBinarioColoreado nodo, int* cantidadAzules, int* cantidadRojas){
  if(nodo == NULL) return;

  if(nodo->colorNodo == Azul){
    (*cantidadAzules)++;
  } else if(nodo->colorNodo == Rojo){
    (*cantidadRojas)++;
  }

  contar_colores(nodo->izq, cantidadAzules, cantidadRojas);
  contar_colores(nodo->der, cantidadAzules, cantidadRojas);
}

// Retorna el color del Arbol.
Color color(ArbolBinarioColoreado inicio){
  int cantidadAzules = 0;
  int cantidadRojas = 0;

  contar_colores(inicio, &cantidadAzules, &cantidadRojas);

  if(cantidadAzules > cantidadRojas){
    return Azul;
  } else if(cantidadRojas > cantidadAzules){
    return Rojo;
  } else {
    return Neutro;
  }
}

int contar_puras(ArbolBinarioColoreado nodo, Color colorAncestro){
  if(nodo == NULL) return 0;

  // Si es una hoja, verificar si es pura
  if(nodo->izq == NULL && nodo->der == NULL){
    return (nodo->colorNodo == colorAncestro) ? 1 : 0;
  }

  return contar_puras(nodo->izq, colorAncestro) + contar_puras(nodo->der, colorAncestro);
}

// Retorna la cantidad de hojas puras.
int CantidadPuras(ArbolBinarioColoreado inicio){
  if(inicio == NULL) return 0;
  return contar_puras(inicio, inicio->colorNodo);
}