#include "conjunto_difuso.h"

static CDNodo* crear_nodo(void* data, double gp, Copy copy){
  CDNodo* nodo = (CDNodo*)malloc(sizeof(CDNodo));
  assert(nodo != NULL);
  nodo->data = copy(data);
  nodo->gp = gp;
  nodo->next = NULL;
  return nodo;
}

CD* cd_crear(){
  CD* cd = (CD*)malloc(sizeof(CD));
  assert(cd != NULL);
  cd->head = NULL;
  cd->size = 0;
  return cd;
}

void cd_agregar(CD* cd, void* data, double gp, Copy copy, Compare cmp){
  if(!(gp >= 0 || gp <= 1)) return; // Grado de pertenencia no válido

  CDNodo* current = cd->head;

  while(current != NULL){
    // Si el elemento ya existe, actualizamos su gp
    if(cmp(current->data, data) == 0){
      current->gp = gp;
      return;
    }
    current = current->next;
  }

  // Creamos el nuevo nodo y lo agregamos a la lista
  CDNodo* nodo = crear_nodo(data, gp, copy);
  nodo->next = cd->head;
  cd->head = nodo;
  cd->size++; // Aumentamos el tamaño de la lista
}

void cd_modificar_gp(CD* cd, void* data, double gp, Compare cmp, Destroy destr){
  if(!(gp >= 0 || gp <= 1)) return; // Grado de pertenencia no válido

  CDNodo* current = cd->head;
  CDNodo* prev = NULL;

  while(current != NULL){
    if(cmp(current->data, data) == 0){
      if(gp == 0){
        if(prev == NULL){
          cd->head = current->next;
        } else {
          prev->next = current->next;
        }
        destr(current);
        cd->size--;
      } else {
        current->gp = gp;
      }
    }
    prev = current;
    current = current->next;
  }
}

int cd_subconjunto(CD* A, CD* B, Compare cmp){
  CDNodo* currentA = A->head;

  // Verificar si para cualquier elemento de A, gpA(x) <= gpB(x)
  while(currentA != NULL){
    CDNodo* currentB = B->head;
    double gpB = 0;
    while(currentB != NULL){
      if(cmp(currentA->data, currentB->data) == 0){
        gpB = currentB->gp;
      }
      currentB = currentB->next;
    }
    if(currentA->gp > gpB) return -1;
    currentA = currentA->next;
  }

  return 1;
}

static double max(int a, int b){
  return a > b ? a : b;
}

CD* cd_union(CD* A, CD* B, Copy copy, Compare cmp){
  CD* cd_union = cd_crear();

  // Agregar todos los elementos del conjunto difuso A al conjunto unión
  CDNodo* currentA = A->head;
  while(currentA != NULL){
    cd_agregar(cd_union, currentA->data, currentA->gp, copy, cmp);
    currentA = currentA->next;
  }

  CDNodo* currentB = B->head;
  while(currentB != NULL){
    CDNodo* currentUnion = cd_union->head;
    while(currentUnion != NULL){
      // Actualizar el nodo con el gp más alto
      if(cmp(currentB->data, currentUnion->data) == 0){
        currentUnion->gp = max(currentB->gp, currentUnion->gp);
        break;
      }
      currentUnion = currentUnion->next;
    }

    // Si el nodo actual que recorrió la lista de unión es NULL, significa que no existe el nodo de la lista B en la unión
    // por lo cual, lo agregamos a la lista de unión
    if(currentUnion == NULL){
      cd_agregar(cd_union, currentB->data, currentB->gp, copy, cmp);
    }

    currentB = currentB->next;
  }

  return cd_union;
}

CD* cd_diferencia(CD* A, CD* B, Copy copy, Compare cmp){
  CD* cd_dif = cd_crear();

  CDNodo* currentA = A->head;
  while(currentA != NULL){
    CDNodo* currentB = B->head;
    int gpB = 0;
    while(currentB != NULL){
      if(cmp(currentA->data, currentB->data) == 0){
        gpB = currentB->gp;
        break;
      }
      currentB = currentB->next;
    }

    double diffGp = (currentA->gp >= gpB) ? (currentA->gp - gpB) : 0;
    // Agregar el nodo si la diferencia es mayor a 0
    if(diffGp > 0){
      cd_agregar(cd_dif, currentA->data, diffGp, copy, cmp);
    }
    
    currentA = currentA->next;
  }
  return cd_dif;
}