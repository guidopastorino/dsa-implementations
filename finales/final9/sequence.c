#include "sequence.h"

Sequence* crear_sequencia(){
  Sequence* seq = (Sequence*)malloc(sizeof(Sequence));
  assert(seq != NULL);
  seq->head = NULL;
  seq->size = 0;
  return seq;
}

static Nodo* crear_nodo(int data){
  Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
  assert(nodo != NULL);
  nodo->data = data;
  nodo->cantidadMenores = 0;
  nodo->next = NULL;
  return nodo;
}

void buscar_por_cantidadMenores(Sequence* seq, int cantidadMenores){
  Nodo* current = seq->head;

  printf("Números en la secuencia con cantidadMenores igual a %d: ", cantidadMenores);
  while(current != NULL){
    if(current->cantidadMenores == cantidadMenores){
      printf("%d ", current->data);
    }
    current = current->next;
  }

  printf("\n");
}

static void actualizar_cantidad_menores(Sequence* seq){
  Nodo* current = seq->head;
  while(current != NULL){
    int menores = 0;
    Nodo* temp = seq->head;
    while(temp != current){
      if(temp->data < current->data){
        menores++;
      }
      temp = temp->next;
    }
    current->cantidadMenores = menores;
    current = current->next;
  }
}

void insertar_en_posicion(Sequence* seq, int data, int pos){
  if(pos < 0){
    printf("pos tiene que ser mayor que 0\n");
    return;
  }
  Nodo* nodo = crear_nodo(data);
  if(pos == 0){
    nodo->next = seq->head;
    seq->head = nodo;
  } else {
    Nodo* current = seq->head;
    // Nos colocamos en el nodo anterior a 'pos'
    for(int i = 0; i<pos-1 && current != NULL; i++){
      current = current->next;
    }
    if(current == NULL){
      printf("Posición fuera de rango\n");
      return;
    }
    nodo->next = current->next;
    current->next = nodo;
  }
  // Actualizar la cantidadMenores de los nodos de la sequencia
  actualizar_cantidad_menores(seq);
  seq->size++;
}

void borrar_en_posicion(Sequence* seq, int pos){
  if(pos < 0){
    printf("pos tiene que ser mayor que 0\n");
    return;
  }
  if(pos == 0){
    Nodo* temp = seq->head;
    seq->head = seq->head->next;
    free(temp);
  } else {
    Nodo* current = seq->head;
    // Nos colocamos en el nodo anterior a 'pos'
    for(int i = 0; i<pos-1 && current != NULL; i++){
      current = current->next;
    }
    // Si llegamos a NULL, significa que la posición está fuera de rango
    if (current == NULL || current->next == NULL) {
      printf("Posición fuera de rango\n");
      return;
    }
    Nodo* temp = current->next;
    current->next = current->next->next;
    free(temp);
  }
  // Actualizar la cantidadMenores de los nodos de la sequencia
  actualizar_cantidad_menores(seq);
  seq->size--;
}

void ordenar_por_cantidadMenores(Sequence* seq, int cantidadMenores){
  if (seq->head == NULL || seq->head->next == NULL) {
    // La secuencia está vacía o tiene un solo elemento, no se necesita ordenar.
    return;
  }

  Nodo* sorted = NULL; // Lista ordenada.
  Nodo* current = seq->head; // Nodo actual en la lista original.

  while (current != NULL) {
    Nodo* next = current->next; // Guardar el siguiente nodo.
    
    // Inserta el nodo en la lista ordenada de forma adecuada.
    if (sorted == NULL || current->cantidadMenores <= sorted->cantidadMenores) {
      // Si la lista ordenada está vacía o el nodo actual debe ir al inicio.
      current->next = sorted;
      sorted = current;
    } else {
      Nodo* sorted_current = sorted;
      // Buscar la posición correcta en la lista ordenada.
      while (sorted_current->next != NULL && sorted_current->next->cantidadMenores < current->cantidadMenores) {
        sorted_current = sorted_current->next;
      }
      // Insertar el nodo en la posición correcta.
      current->next = sorted_current->next;
      sorted_current->next = current;
    }

    // Mover al siguiente nodo de la lista original.
    current = next;
  }

  // Actualizar la cabeza de la secuencia para que apunte a la lista ordenada.
  seq->head = sorted;
}

void imprimir_secuencia(Sequence* seq){
  Nodo* current = seq->head;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void liberar_secuencia(Sequence* seq){
  Nodo* current = seq->head;
  while(current != NULL){
    Nodo* temp = current;
    current = current->next;
    free(temp);
  }
  free(seq);
}