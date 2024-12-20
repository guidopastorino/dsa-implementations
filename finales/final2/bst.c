#include "bst.h"

BSTNode* create_node(Usuario usuario){
  BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
  assert(node != NULL);
  node->usuario = usuario;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BSTNode* bst_insert(BSTNode* root, Usuario usuario, Compare cmp){
  if(root == NULL) return create_node(usuario);
  if(cmp(usuario, root->usuario) < 0){
    root->left = bst_insert(root->left, usuario, cmp);
  } else if(cmp(usuario, root->usuario) > 0){
    root->right = bst_insert(root->right, usuario, cmp);
  }
  return root;
}

Usuario bst_search(BSTNode* root, int dni, Compare cmp){
  if(root == NULL) return (Usuario){0,0,0,0};
  if(dni < root->usuario.dni){
    return bst_search(root->left, dni, cmp);
  }
  return bst_search(root->right, dni, cmp);
}

void bst_bfs(BSTNode* root, Print print){
  if(root == NULL) return;
  BSTNode* queue[100];
  for(int i = 0; i<100; i++)
    queue[i] = NULL;
  int front = 0, rear = 0;
  queue[rear++] = root;
  while(front < rear){
    BSTNode* node = queue[front++];
    print(node->usuario);
    if(node->left) queue[rear++] = node->left;
    if(node->right) queue[rear++] = node->right;
  }
  printf("\n");
}

void bst_destroy(BSTNode* root){
  if(root != NULL){
    bst_destroy(root->left);
    bst_destroy(root->right);

    free(root);
  }
}