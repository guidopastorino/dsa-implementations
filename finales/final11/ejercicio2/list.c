#include "list.h"

static Node* glist_create_node(void* data, Copy copy){
  Node* node = (Node*)malloc(sizeof(Node));
  assert(node != NULL);
  node->data = copy(data);
  node->next = NULL;
  return node;
}

void glist_insert(Node** head, void* data, Copy copy){
  Node* node = glist_create_node(data, copy);
  node->next = *head;
  *head = node;
}

Node* glist_merge_lists(Node* list1, Node* list2, Node* list3, Copy copy, Compare cmp){
  Node* mergedList = NULL;
  Node** tail = &mergedList;

  while(list1 != NULL || list2 != NULL || list3 != NULL){
    Node* smallest = NULL;

    if(list1 != NULL && (list2 == NULL || cmp(list1->data, list2->data) <= 0) && (list3 == NULL || cmp(list1->data, list3->data) <= 0)){
      smallest = list1;
      list1 = list1->next;
    }
    else if(list2 != NULL && (list1 == NULL || cmp(list2->data, list1->data) <= 0) && (list3 == NULL || cmp(list2->data, list3->data) <= 0)){
      smallest = list2;
      list2 = list2->next;
    }
    else if(list3 != NULL){
      smallest = list3;
      list3 = list3->next;
    }

    // Crear un nuevo nodo en lugar de reutilizar el nodo original
    Node* newNode = glist_create_node(smallest->data, copy);
    
    *tail = newNode;
    tail = &((*tail)->next);
  }

  return mergedList;
}

void glist_insertion_sort(Node** head, Compare cmp){
  Node* sorted = NULL;
  Node* current = *head;

  while(current != NULL){
    Node* next = current->next;
    if(sorted == NULL || cmp(current->data, sorted->data) <= 0){
      current->next = sorted;
      sorted = current;
    } else {
      Node* temp = sorted;
      while(temp->next != NULL && cmp(current->data, temp->next->data) > 0){
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }

  *head = sorted;
}

void glist_display(Node* head, Print print){
  Node* current = head;
  while(current != NULL){
    print(current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void glist_destroy(Node** head, Destroy destr){
  Node* current = *head;
  while(current != NULL){
    Node* temp = current;
    current = current->next;
    destr(temp->data);
    free(temp);
  }
  *head = NULL;
}