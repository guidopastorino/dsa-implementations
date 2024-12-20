#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _SLNode {
  int data;
  struct _SLNode* next;
} SLNode;

SLNode* create_node(int data);
void insert_begin(SLNode** head, int data);
void insert_end(SLNode** head, int data);
void insert_pos(SLNode** head, int data, int pos);
void delete_begin(SLNode** head);
void delete_end(SLNode** head);
void delete_pos(SLNode** head, int pos);
void print_list(SLNode* head);
void free_list(SLNode** head);

// Función main para probar las operaciones de la lista enlazada
int main() {
  SLNode* head = NULL;

  // Insertar elementos al principio
  insert_begin(&head, 10);
  insert_begin(&head, 20);
  insert_begin(&head, 30);

  printf("Lista después de insertar al principio: ");
  print_list(head);  // Esperado: 30 -> 20 -> 10 -> NULL

  // Insertar elementos al final
  insert_end(&head, 40);
  insert_end(&head, 50);

  printf("Lista después de insertar al final: ");
  print_list(head);  // Esperado: 30 -> 20 -> 10 -> 40 -> 50 -> NULL

  // Insertar en una posición específica
  insert_pos(&head, 25, 3);  // Insertar en la posición 3

  printf("Lista después de insertar en la posición 3: ");
  print_list(head);  // Esperado: 30 -> 20 -> 25 -> 10 -> 40 -> 50 -> NULL

  // Eliminar el primer nodo
  delete_begin(&head);

  printf("Lista después de eliminar el primer nodo: ");
  print_list(head);  // Esperado: 20 -> 25 -> 10 -> 40 -> 50 -> NULL

  printf("Insertar nodo en psoicion fuera de rango (se inserta al final):");
  insert_pos(&head, 79, 10000);
  print_list(head);

  // Eliminar el último nodo
  delete_end(&head);

  printf("Lista después de eliminar el último nodo: ");
  print_list(head);  // Esperado: 20 -> 25 -> 10 -> 40 -> NULL

  // Eliminar nodo en una posición específica
  delete_pos(&head, 2);  // Eliminar el nodo en la posición 2 (25)

  printf("Lista después de eliminar el nodo en la posición 2: ");
  print_list(head);  // Esperado: 20 -> 10 -> 40 -> NULL

  // Liberar la lista
  free_list(&head);

  printf("Lista después de liberar: ");
  print_list(head);  // Esperado: NULL (lista vacía)

  return 0;
}

SLNode* create_node(int data){
  SLNode* node = (SLNode*)malloc(sizeof(SLNode));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  return node;
}

void insert_begin(SLNode** head, int data){
  SLNode* node = create_node(data);
  node->next = *head;
  *head = node;
}

void insert_end(SLNode** head, int data){
  SLNode* node = create_node(data);
  if(*head == NULL){
    *head = node;
  } else {
    SLNode* current = *head;
    while(current->next)
      current = current->next;
    current->next = node;
  }
}

void insert_pos(SLNode** head, int data, int pos) {
  assert(pos >= 1);
  if (pos == 1) {
    insert_begin(head, data);
  } else {
    SLNode* node = create_node(data);
    SLNode* current = *head;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
      current = current->next;
    }
    // Si llegamos al final de la lista, insertamos al final (ya que sería que es una posicion fuera de rango)
    if (current == NULL) {
      insert_end(head, data);  // Insertar al final si pos es mayor al tamaño
    } else {
      node->next = current->next;
      current->next = node;
    }
  }
}

void delete_begin(SLNode** head){
  assert(*head != NULL);
  SLNode* temp = *head;
  *head = (*head)->next;
  free(temp);
}

void delete_end(SLNode** head){
  assert(*head != NULL);
  if(!(*head)->next){
    free(*head);
    *head = NULL;
  } else {
    SLNode* current = *head;
    while(current->next->next)
      current = current->next;
    free(current->next);
    current->next = NULL;
  }
}

void delete_pos(SLNode** head, int pos){
  assert(*head != NULL && pos >= 1);
  if(pos == 1){
    delete_begin(head);
  } else {
    SLNode* temp = NULL, *current = *head;
    for(int i = 1; i<pos-1 && current != NULL; i++){
      current = current->next;
    } 
    // Verifica que el nodo actual (current) no sea NULL (posición válida en la lista)
    // y que el siguiente nodo (current->next) también exista, para garantizar
    // que hay un nodo a eliminar en la posición solicitada.
    if(current == NULL || current->next == NULL) {
      printf("Posición fuera de rango.\n");
      return;
    }
    temp = current->next;
    current->next = temp->next;
    free(temp);
  }
}

void print_list(SLNode* head){
  SLNode* current = head;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void free_list(SLNode** head){
  SLNode* current = *head;
  while(current != NULL){
    SLNode* temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}
