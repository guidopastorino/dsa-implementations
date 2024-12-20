#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _CSNode {
  int data;
  struct _CSNode* next;
} CSNode;

CSNode* create_node(int data);
void insert_begin(CSNode** tail, int data);
void insert_end(CSNode** tail, int data);
void insert_pos(CSNode** tail, int data, int pos);
void delete_begin(CSNode** tail);
void delete_end(CSNode** tail);
void delete_pos(CSNode** tail, int pos);
void print_list(CSNode* tail);
void free_list(CSNode** tail);

int main() {
  CSNode* tail = NULL;

  // Inserta elementos al final de la lista
  printf("Insertando elementos al final:\n");
  insert_end(&tail, 10);
  insert_end(&tail, 20);
  insert_end(&tail, 30);
  insert_end(&tail, 40);
  print_list(tail);

  // Inserta elementos al inicio de la lista
  printf("\nInsertando elementos al inicio:\n");
  insert_begin(&tail, 5);
  insert_begin(&tail, 0);
  print_list(tail);

  // Inserta elementos en una posición específica
  printf("\nInsertando elementos en una posición específica:\n");
  insert_pos(&tail, 3, 15);  // Inserta 15 en la posición 3
  print_list(tail);

  // Elimina el primer elemento
  printf("\nEliminando el primer elemento:\n");
  delete_begin(&tail);
  print_list(tail);

  // Elimina el último elemento
  printf("\nEliminando el último elemento:\n");
  delete_end(&tail);
  print_list(tail);

  // Elimina un elemento en una posición específica
  printf("\nEliminando un elemento en una posición específica:\n");
  delete_pos(&tail, 4);  // Elimina el nodo en la posición 4
  print_list(tail);

  // Libera la lista
  printf("\nLiberando la lista:\n");
  free_list(&tail);
  if (tail == NULL) {
    printf("Lista liberada exitosamente.\n");
  } else {
    printf("Error al liberar la lista.\n");
  }

  return 0;
}

CSNode* create_node(int data){
  CSNode* node = (CSNode*)malloc(sizeof(CSNode));
  assert(node != NULL);
  node->data = data;
  node->next = node;
  return node;
}

void insert_begin(CSNode** tail, int data){
  CSNode* node = create_node(data);
  if(*tail == NULL){
    *tail = node;
  } else {
    node->next = (*tail)->next;
    (*tail)->next = node;
  }
}

void insert_end(CSNode** tail, int data){
  CSNode* node = create_node(data);
  if(*tail == NULL){
    *tail = node;
  } else {
    node->next = (*tail)->next;
    (*tail)->next = node;
    *tail = node;
  }
}

void insert_pos(CSNode** tail, int data, int pos){
  assert(pos >= 1);
  if(pos == 1){
    insert_begin(tail, data);
  } else {
    CSNode* current = (*tail)->next;
    for(int i = 1; i < pos-1; i++){
      current = current->next;
      if(current == (*tail)->next){
        printf("Position out of range\n");
        return;
      }
    }
    CSNode* node = create_node(data);
    node->next = current->next;
    current->next = node;
    if(current == *tail) *tail = node;  // Asegura que el nuevo nodo es el último.
  }
}

void delete_begin(CSNode** tail){
  assert(*tail != NULL);
  if(*tail == (*tail)->next){
    free(*tail);
    *tail = NULL;
  } else {
    CSNode* temp = (*tail)->next;
    (*tail)->next = (*tail)->next->next;
    free(temp);
  }
}

void delete_end(CSNode** tail){
  assert(*tail != NULL);
  if(*tail == (*tail)->next){
    free(*tail);
    *tail = NULL;
  } else {
    CSNode* current = (*tail)->next;
    while(current->next != *tail){
      current = current->next;
    }
    CSNode* temp = *tail;
    current->next = (*tail)->next;
    *tail = current;
    free(temp);
  }
}

void delete_pos(CSNode** tail, int pos){
  assert(*tail != NULL && pos >= 1);
  if(pos == 1){
    delete_begin(tail);
  } else {
    CSNode* current = (*tail)->next;
    for(int i = 1; i < pos-1; i++){
      current = current->next;
      if(current == (*tail)->next){
        printf("Position out of range\n");
        return;
      }
    }
    CSNode* temp = current->next;
    current->next = temp->next;
    if(temp == *tail) *tail = current;  // Ajustar `tail` si el nodo eliminado es el último.
    free(temp);  // Liberar el nodo eliminado.
  }
}

void print_list(CSNode* tail){
  if(tail == NULL){
    printf("NULL\n");
  } else {
    CSNode* current = tail->next;
    do {
      printf("%d -> ", current->data);
      current = current->next;
    } while(current != tail->next);
  }
  printf("\n");
}

void free_list(CSNode** tail){
  if(*tail == NULL) return;

  CSNode* current = (*tail)->next;
  CSNode* temp;

  do {
    temp = current;
    current = current->next;
    free(temp);
  } while(current != (*tail)->next);

  *tail = NULL;
}
