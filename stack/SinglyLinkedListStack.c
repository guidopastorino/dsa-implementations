#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 'push' (stack operation) -> 'insert_begin' (sl operation)
// 'pop' (stack operation) -> 'delete_begin' (sl operation)

typedef struct _SLNode {
  int data;
  struct _SLNode* next;
} SLNode;

SLNode* create_node(int data){
  SLNode* node = (SLNode*)malloc(sizeof(SLNode));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  return node;
}

void push(SLNode** head, int data){
  SLNode* node = create_node(data);
  node->next = *head;
  *head = node;
}

int pop(SLNode** head){
  if(*head == NULL){
    printf("Stack is empty. Cannot pop\n");
    return -1;
  }
  int data = (*head)->data;
  SLNode* temp = *head;
  *head = (*head)->next;
  free(temp);
  return data;
}

int top(SLNode** head){
  if(*head == NULL){
    printf("Stack is empty. Cannot get top\n");
    return -1;
  }
  return (*head)->data;
}

void display(SLNode* head){
  SLNode* current = head;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void free_stack(SLNode** head){
  SLNode* current = *head;
  while(current != NULL){
    SLNode* temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}

int main(){
  SLNode* stack = NULL;
  push(&stack, 10);
  push(&stack, 20);
  display(stack);
  printf("Top: %d\n", top(&stack));
  pop(&stack);
  display(stack);
  printf("Top: %d\n", top(&stack));
  pop(&stack);
  display(stack);

  free_stack(&stack);

  return 0;
}