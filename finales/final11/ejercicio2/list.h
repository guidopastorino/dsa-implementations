#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _Node {
  void* data;
  struct _Node* next;
} Node;

typedef void* (*Copy)(void*);
typedef int (*Compare)(void*, void*);
typedef void (*Print)(void*);
typedef void (*Destroy)(void*);

void glist_insert(Node** head, void* data, Copy copy);
Node* glist_merge_lists(Node* list1, Node* list2, Node* list3, Copy copy, Compare cmp);
void glist_insertion_sort(Node** head, Compare cmp);
void glist_display(Node* head, Print print);
void glist_destroy(Node** head, Destroy destr);

#endif