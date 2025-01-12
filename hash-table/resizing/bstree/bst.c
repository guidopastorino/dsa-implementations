#include "bst.h"

BSTNode* create_mode(int data){
  BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
  assert(node != NULL);
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BSTNode* bst_insert(BSTNode* root, int data){
  printf("Insertando %d\n", data);
  if(root == NULL) return create_mode(data);
  if(data < root->data){
    root->left = bst_insert(root->left, data);
  } else if(data > root->data){
    root->right = bst_insert(root->right, data);
  }
  return root;
}

/// @brief Encuentra el nodo con el valor mínimo en un árbol binario de búsqueda.
/// @param root Puntero al nodo raíz del árbol o subárbol.
/// @return Puntero al nodo con el valor mínimo en el árbol o subárbol.
static BSTNode* find_min(BSTNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL)
    root = root->left;
  return root;
}

BSTNode* bst_delete(BSTNode* root, int data){
  if(root == NULL) return NULL;
  if(data < root->data){
    root->left = bst_delete(root->left, data);
  } else if(data > root->data) {
    root->right = bst_delete(root->right, data);
  } else {
    if(root->left == NULL || root->right == NULL){
      BSTNode* temp = root->left ? root->left : root->right;
      if(!temp){
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      free(temp);
    } else {
      BSTNode* temp = find_min(root->right);
      root->data = temp->data;
      root->right = bst_delete(root->right, temp->data);
    }
  }
  return root;
}

int bst_search(BSTNode* root, int data){
  if(root == NULL) return 0;
  if(data == root->data) return 1;
  if(data < root->data)
    return bst_search(root->left, data);
  return bst_search(root->right, data);
}

void bst_inorder(BSTNode* root){
  if(root != NULL){
    bst_inorder(root->left);
    printf("%d ", root->data);
    bst_inorder(root->right);
  }
}

void bst_destroy(BSTNode* root){
  if(root != NULL){
    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
  }
}