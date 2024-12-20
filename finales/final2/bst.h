#ifndef _BST_H_
#define _BST_H_

#include "types.h"

typedef struct _BSTNode {
  Usuario usuario;
  struct _BSTNode* left;
  struct _BSTNode* right;
} BSTNode;

BSTNode* create_node(Usuario usuario);

BSTNode* bst_insert(BSTNode* root, Usuario usuario, Compare cmp);

Usuario bst_search(BSTNode* root, int dni, Compare cmp);

void bst_bfs(BSTNode* root, Print print);

void bst_destroy(BSTNode* root);

#endif