#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _DLNode {
  int data;
  struct _DLNode* prev;
  struct _DLNode* next;
} DLNode;

typedef enum { BACKWARDS, FORWARDS } Traversing;

DLNode* create_node(int data);
void insert_begin(DLNode** head, int data);
void insert_end(DLNode** head, int data);
void insert_pos(DLNode** head, int data, int pos);
void delete_begin(DLNode** head);
void delete_end(DLNode** head);
void delete_pos(DLNode** head, int pos);
void print_list(DLNode* head, Traversing direction);
void free_list(DLNode** head);

// Main
int main() {
  DLNode* head = NULL;

  // Insertar elementos al inicio
  printf("Insertar elementos al inicio:\n");
  insert_begin(&head, 10);
  insert_begin(&head, 20);
  insert_begin(&head, 30);
  print_list(head, FORWARDS);

  // Insertar elementos al final
  printf("\nInsertar elementos al final:\n");
  insert_end(&head, 40);
  insert_end(&head, 50);
  print_list(head, FORWARDS);

  // Insertar en una posición específica
  printf("\nInsertar 25 en la posición 2:\n");
  insert_pos(&head, 25, 2);
  print_list(head, FORWARDS);

  printf("\nInsertar 35 en la posición 4:\n");
  insert_pos(&head, 35, 4);
  print_list(head, FORWARDS);

  // Recorrer hacia atrás
  printf("\nRecorrer la lista hacia atrás:\n");
  print_list(head, BACKWARDS);

  // Eliminar elementos
  printf("\nEliminar el primer elemento:\n");
  delete_begin(&head);
  print_list(head, FORWARDS);

  printf("\nEliminar el último elemento:\n");
  delete_end(&head);
  print_list(head, FORWARDS);

  printf("\nEliminar el elemento en la posición 3:\n");
  delete_pos(&head, 3);
  print_list(head, FORWARDS);

  // Recorre la lista hacia adelante y hacia atrás para verificar su integridad
  printf("\nRecorrer la lista final hacia adelante:\n");
  print_list(head, FORWARDS);

  printf("\nRecorrer la lista final hacia atrás:\n");
  print_list(head, BACKWARDS);

  // Liberar la lista
  printf("\nLiberar la lista completa:\n");
  free_list(&head);
  print_list(head, FORWARDS);

  return 0;
}

DLNode* create_node(int data){
  DLNode* node = (DLNode*)malloc(sizeof(DLNode));
  assert(node != NULL);
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

void insert_begin(DLNode** head, int data){
  DLNode* node = create_node(data);
  if(*head == NULL){
    *head = node;
  } else {
    node->next = *head;
    (*head)->prev = node;
    *head = node;
  }
}

void insert_end(DLNode** head, int data){
  DLNode* node = create_node(data);
  if(*head == NULL){
    *head = node;
  } else {
    DLNode* current = *head;
    while(current->next)
      current = current->next;
    current->next = node;
    node->prev = current;
  }
}

void insert_pos(DLNode** head, int data, int pos){
  assert(pos >= 1);
  if(pos == 1){
    insert_begin(head, data);
  } else {
    DLNode* node = create_node(data);
    DLNode* current = *head;
    for(int i = 1; i<pos-1 && current != NULL; i++){
      current = current->next;
    }
    assert(current != NULL);
    node->next = current->next;
    if(current->next)
      current->next->prev = node;
    current->next = node;
    node->prev = current;
  }

}

void delete_begin(DLNode** head){
  assert(*head != NULL);
  DLNode* temp = *head;
  *head = (*head)->next;
  if(*head != NULL)
    (*head)->prev = NULL;
  free(temp);
}

void delete_end(DLNode** head){
  assert(*head != NULL);
  if(!(*head)->next){
    free(*head);
    *head = NULL;
  } else {
    DLNode* current = *head;
    while(current->next)
      current = current->next;
    current->prev->next = NULL;
    free(current);
  }
}

void delete_pos(DLNode** head, int pos){
  assert(pos >= 1 && *head != NULL);
  if(pos == 1){
    delete_begin(head);
  } else {
    DLNode* current = *head;
    // recorrer hasta el nodo que queremos eliminar (current apunta al nodo a eliminar)
    for(int i = 1; i<pos && current != NULL; i++){
      current = current->next;
    }
    if(current->next)
      current->next->prev = current->prev;
    if(current->prev)
      current->prev->next = current->next;
    free(current);
  }
}

void print_list(DLNode* head, Traversing direction){
  DLNode* current = head;
  if(direction == FORWARDS){
    while(current != NULL){
      printf("%d -> ", current->data);
      current = current->next;
    }
  } else {
    while(current->next != NULL){
      current = current->next;
    }
    while(current != NULL){
      printf("%d -> ", current->data);
      current = current->prev;
    }
  }
  printf("NULL\n");
}

void free_list(DLNode** head){
  DLNode* current = *head;
  while(current != NULL){
    DLNode* temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}
