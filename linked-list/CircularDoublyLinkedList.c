#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { BACKWARDS, FORWARDS } Traversing;

typedef struct _CDNode {
  int data;
  struct _CDNode* prev;
  struct _CDNode* next;
} CDNode;

CDNode* create_node(int data);
void insert_begin(CDNode** tail, int data);
void insert_end(CDNode** tail, int data);
void insert_pos(CDNode** tail, int data, int pos);
void delete_begin(CDNode** tail);
void delete_end(CDNode** tail);
void delete_pos(CDNode** tail, int pos);
void print_list(CDNode* tail, Traversing direction);
void free_list(CDNode** tail);

int main() {
  CDNode* tail = NULL;

  // Insertar al inicio
  insert_begin(&tail, 10);
  insert_begin(&tail, 20);
  insert_begin(&tail, 30);

  // Imprimir lista hacia adelante
  printf("Lista después de insertar al inicio:\n");
  print_list(tail, FORWARDS);

  // Insertar al final
  insert_end(&tail, 40);
  insert_end(&tail, 50);

  printf("Lista después de insertar al final:\n");
  print_list(tail, FORWARDS);

  // Insertar en posición específica
  insert_pos(&tail, 25, 3);
  printf("Lista después de insertar 25 en posición 3:\n");
  print_list(tail, FORWARDS);

  // Eliminar al inicio
  delete_begin(&tail);
  printf("Lista después de eliminar al inicio:\n");
  print_list(tail, FORWARDS);

  // Eliminar al final
  delete_end(&tail);
  printf("Lista después de eliminar al final:\n");
  print_list(tail, FORWARDS);

  // Eliminar en posición específica
  delete_pos(&tail, 3);
  printf("Lista después de eliminar posición 3:\n");
  print_list(tail, FORWARDS);

  // Imprimir lista hacia atrás
  printf("Lista en orden inverso:\n");
  print_list(tail, BACKWARDS);

  // Liberar toda la lista
  free_list(&tail);
  printf("Lista después de liberar:\n");
  print_list(tail, FORWARDS);

  return 0;
}

CDNode* create_node(int data) {
  CDNode* node = (CDNode*)malloc(sizeof(CDNode));
  assert(node != NULL);
  node->data = data;
  node->prev = node;
  node->next = node;
  return node;
}

void insert_begin(CDNode** tail, int data) {
  CDNode* node = create_node(data);
  if(*tail == NULL) {
    *tail = node;
  } else {
    node->next = (*tail)->next;
    node->prev = *tail;
    (*tail)->next->prev = node;
    (*tail)->next = node;
  }
}

void insert_end(CDNode** tail, int data) {
  CDNode* node = create_node(data);
  if(*tail == NULL) {
    *tail = node;
  } else {
    node->next = (*tail)->next;
    node->prev = *tail;
    (*tail)->next->prev = node;
    (*tail)->next = node;
    *tail = node;
  }
}

void insert_pos(CDNode** tail, int data, int pos) {
  assert(pos >= 1);
  if(pos == 1) {
    insert_begin(tail, data);
  } else {
    CDNode* current = (*tail)->next;
    for(int i = 1; i < pos - 1; i++) {
      current = current->next;
      if(current == (*tail)->next) {
        printf("Position out of range\n");
        return;
      }
    }
    CDNode* node = create_node(data);
    node->next = current->next;
    node->prev = current;
    current->next->prev = node;
    current->next = node;
  }
}

void delete_begin(CDNode** tail) {
  assert(*tail != NULL);
  if(*tail == (*tail)->next) {
    free(*tail);
    *tail = NULL;
  } else {
    CDNode* temp = (*tail)->next;
    (*tail)->next = temp->next;
    temp->next->prev = *tail;
    free(temp);
  }
}

void delete_end(CDNode** tail) {
  assert(*tail != NULL);
  if(*tail == (*tail)->next) {
    free(*tail);
    *tail = NULL;
  } else {
    CDNode* temp = *tail;
    (*tail)->prev->next = (*tail)->next;
    (*tail)->next->prev = (*tail)->prev;
    *tail = (*tail)->prev;
    free(temp);
  }
}

void delete_pos(CDNode** tail, int pos) {
  assert(*tail != NULL && pos >= 1);
  if(pos == 1) {
    delete_begin(tail);
  } else {
    CDNode* current = (*tail)->next;
    for(int i = 1; i < pos; i++) {
      current = current->next;
      if(current == (*tail)->next) {
        printf("Position out of range\n");
        return;
      }
    }
    if(current == *tail) {
      *tail = current->prev;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
  }
}

void print_list(CDNode* tail, Traversing direction) {
  if(tail == NULL) {
    printf("NULL\n");
    return;
  }

  CDNode* current = (direction == FORWARDS) ? tail->next : tail;
  do {
    printf("%d -> ", current->data);
    current = (direction == FORWARDS) ? current->next : current->prev;
  } while(current != ((direction == FORWARDS) ? tail->next : tail));
  printf("(circular)\n");
}

void free_list(CDNode** tail) {
  if(*tail == NULL) return;

  CDNode* current = (*tail)->next;
  CDNode* temp;

  while(current != *tail) {
    temp = current;
    current = current->next;
    free(temp);
  }
  free(*tail);
  *tail = NULL;
}