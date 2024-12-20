#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _BSTNode {
  char* key;
  int val;
  struct _BSTNode* left;
  struct _BSTNode* right;
} BSTNode;

// BST Functions
BSTNode* bst_create_node(char* key, int val){
  BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
  assert(node != NULL);
  node->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(node->key != NULL);
  strcpy(node->key, key);
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BSTNode* bst_insert(BSTNode* root, char* key, int val){
  if(root == NULL) return bst_create_node(key, val);
  if(strcmp(key, root->key) < 0){
    root->left = bst_insert(root->left, key, val);
  } else if(strcmp(key, root->key) > 0){
    root->right = bst_insert(root->right, key, val);
  }
  return root;
}

int bst_search(BSTNode* root, char* key){
  if(root == NULL) return -1;
  if(strcmp(key, root->key) == 0) return root->val;
  if(strcmp(key, root->key) < 0){
    return bst_search(root->left, key);
  } else {
    return bst_search(root->right, key);
  }
}

BSTNode* find_min(BSTNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL){
    root = root->left;
  }
  return root;
}

BSTNode* bst_delete(BSTNode* root, char* key){
  if(root == NULL) return NULL;
  if(strcmp(key, root->key) < 0){
    root->left = bst_delete(root->left, key);
  } else if(strcmp(key, root->key) > 0){
    root->right = bst_delete(root->right, key);
  } else {
    if(root->left == NULL || root->right == NULL){
      BSTNode* temp = root->left ? root->left : root->right;
      if(!temp){
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      free(temp->key);
      free(temp);
    } else {
      BSTNode* temp = find_min(root->right);

      free(root->key);
      
      root->key = (char*)malloc(sizeof(char) * (strlen(temp->key) + 1));
      assert(root->key != NULL);
      strcpy(root->key, temp->key);

      root->val = temp->val;

      root->right = bst_delete(root->right, temp->key);
    }
  }
  return root;
}

// INORDER DFS
void bst_print(BSTNode* root){
  if(root != NULL){
    bst_print(root->left);
    printf("(%s, %d) ", root->key, root->val);
    bst_print(root->right);
  }
}

void bst_free(BSTNode* root){
  if(root != NULL){
    bst_free(root->left);
    bst_free(root->right);

    free(root->key);
    free(root);
  }
}

// Hashtable functions

#define TABLE_SIZE 10

typedef BSTNode* HashTable[TABLE_SIZE];

void hashtable_init(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++)
    hashtable[i] = NULL;
}

unsigned int hash(char* key){
  unsigned int hash = 0;
  while(*key){
    hash = (hash << 5) + *key++;
  }
  return hash % TABLE_SIZE;
}

void hashtable_insert(HashTable hashtable, char* key, int val){
  unsigned int index = hash(key);
  hashtable[index] = bst_insert(hashtable[index], key, val);
}

int hashtable_search(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  return bst_search(hashtable[index], key);
}

void hashtable_delete(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  hashtable[index] = bst_delete(hashtable[index], key);
}

void hashtable_print(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      printf("%d: ", i);
      bst_print(hashtable[i]);
      printf("\n");
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void hashtable_free(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      bst_free(hashtable[i]);
    }
  }
  hashtable_init(hashtable);
}

int main() {
  HashTable hashtable;
  hashtable_init(hashtable);

  // Insertar elementos
  hashtable_insert(hashtable, "apple", 10);
  hashtable_insert(hashtable, "banana", 20);
  hashtable_insert(hashtable, "cherry", 30);
  hashtable_insert(hashtable, "date", 40);
  hashtable_insert(hashtable, "elderberry", 50);

  printf("Estado del hashtable tras inserciones:\n");
  hashtable_print(hashtable);

  // Buscar elementos
  printf("\nBuscando valores:\n");
  printf("Valor de 'apple': %d\n", hashtable_search(hashtable, "apple"));
  printf("Valor de 'cherry': %d\n", hashtable_search(hashtable, "cherry"));
  printf("Valor de 'fig' (inexistente): %d\n", hashtable_search(hashtable, "fig"));

  // Eliminar elementos
  printf("\nEliminando 'banana' y 'cherry':\n");
  hashtable_delete(hashtable, "banana");
  hashtable_delete(hashtable, "cherry");
  hashtable_print(hashtable);

  // Verificar eliminación y búsqueda de elementos eliminados
  printf("\nBuscando valores después de eliminar:\n");
  printf("Valor de 'banana': %d\n", hashtable_search(hashtable, "banana"));
  printf("Valor de 'cherry': %d\n", hashtable_search(hashtable, "cherry"));

  // Liberar memoria
  printf("\nLiberando memoria del hashtable...\n");
  hashtable_free(hashtable);

  // Imprimir estado final
  printf("Estado final del hashtable tras liberar memoria:\n");
  hashtable_print(hashtable);

  return 0;
}