#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b)(a > b ? a : b)

typedef struct _AVLNode {
  char* key;
  int val;
  struct _AVLNode* left;
  struct _AVLNode* right;
  int height;
} AVLNode;

// Funciones AVL
AVLNode* avl_crear_nodo(char* key, int val){
  AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
  assert(node != NULL);
  node->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(node->key != NULL);
  strcpy(node->key, key);
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

int avl_height(AVLNode* root){
  if(root == NULL) return 0;
  return root->height;
}

void avl_update_height(AVLNode* root){
  if(root != NULL){
    root->height = MAX(avl_height(root->left), avl_height(root->right)) + 1;
  }
}

int avl_balance_factor(AVLNode* root){
  if(root == NULL) return 0;
  return avl_height(root->left) - avl_height(root->right);
}

AVLNode* avl_rotate_left(AVLNode* x){
  AVLNode* y = x->right;
  AVLNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  avl_update_height(x);
  avl_update_height(y);
  return y;
}

AVLNode* avl_rotate_right(AVLNode* y){
  AVLNode* x = y->left;
  AVLNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  avl_update_height(y);
  avl_update_height(x);
  return x;
}

AVLNode* avl_balance(AVLNode* root){
  int balance = avl_balance_factor(root);

  // left case
  if(balance > 1){
    if(avl_balance_factor(root->left) < 0){ // left-right case
      root->left = avl_rotate_left(root->left);
    }
    return avl_rotate_right(root);
  }

  // right case
  if(balance < -1){
    if(avl_balance_factor(root->right) > 0){ // right-left case
      root->right = avl_rotate_right(root->right);
    }
    return avl_rotate_left(root);
  }

  return root;
}

AVLNode* avl_insert(AVLNode* root, char* key, int val){
  if(root == NULL) return avl_crear_nodo(key, val);
  if(strcmp(key, root->key) < 0){
    root->left = avl_insert(root->left, key, val);
  } else if(strcmp(key, root->key) > 0){
    root->right = avl_insert(root->right, key, val);
  } else {
    return root; // No se permiten valores duplicados
  }
  // Actualizamos altura
  avl_update_height(root);
  // Balanceamos el arbol
  return avl_balance(root);
}

int avl_search(AVLNode* root, char* key) {
  if (root == NULL) {
    return -1; // No encontrado
  }
  int cmp = strcmp(key, root->key);
  if (cmp == 0) {
    return root->val; // Se encontró, devuelve el valor asociado
  } else if (cmp < 0) {
    return avl_search(root->left, key); // Buscar en el subárbol izquierdo
  } else {
    return avl_search(root->right, key); // Buscar en el subárbol derecho
  }
}

AVLNode* avl_find_min(AVLNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL){
    root = root->left;
  }
  return root;
}

AVLNode* avl_delete(AVLNode* root, char* key){
  if(root == NULL) return NULL;
  if(strcmp(key, root->key) < 0){
    root->left = avl_delete(root->left, key);
  } else if(strcmp(key, root->key) > 0){
    root->right = avl_delete(root->right, key);
  } else {
    if(root->left == NULL || root->right == NULL){
      AVLNode* temp = root->left ? root->left : root->right;
      if(!temp){
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      // liberamos la memoria ocupada por el string del nodo y el nodo
      free(temp->key);
      free(temp);
    } else {
      AVLNode* temp = avl_find_min(root->right);

      // Liberar la clave actual antes de sobrescribirla
      free(root->key);

      // Copiar profundamente la clave del nodo mínimo
      root->key = (char*)malloc(strlen(temp->key) + 1);
      assert(root->key != NULL);
      strcpy(root->key, temp->key);

      // Copiar el valor
      root->val = temp->val;

      // Eliminar el nodo mínimo del subárbol derecho
      root->right = avl_delete(root->right, temp->key);
    }
  }
  if(root == NULL) return NULL;
  avl_update_height(root);
  return avl_balance(root);
}

// INORDER DFS
void avl_print(AVLNode* root){
  if(root != NULL){
    avl_print(root->left);
    printf("(%s, %d) ", root->key, root->val);
    avl_print(root->right);
  }
}

void avl_free(AVLNode* root){
  if(root != NULL){
    avl_free(root->left);
    avl_free(root->right);

    free(root->key);
    free(root);
  }
}

// Funciones tabla hash
#define TABLE_SIZE 10

// notation replacement for AVLNode* hashtable[]. Using this notation: HashTable hashtable (it is the same)
typedef AVLNode* HashTable[TABLE_SIZE];

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
  hashtable[index] = avl_insert(hashtable[index], key, val);
}

int hashtable_search(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  return avl_search(hashtable[index], key);
}

void hashtable_delete(HashTable hashtable, char* key){
  unsigned int index = hash(key);
  hashtable[index] = avl_delete(hashtable[index], key);
}

void hashtable_print(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      printf("%d: ", i);
      avl_print(hashtable[i]);
      printf("\n");
    } else {
      printf("%d: NULL\n", i);
    }
  }
}

void hashtable_free(HashTable hashtable){
  for(int i = 0; i<TABLE_SIZE; i++){
    if(hashtable[i] != NULL){
      avl_free(hashtable[i]);
    }
  }
  hashtable_init(hashtable);
}

int main(){
  HashTable hashtable;
  hashtable_init(hashtable);

  // Realizando 20 inserciones
  for(int i = 1; i <= 10; i++) {
    char key[10];
    snprintf(key, sizeof(key), "clave%d", i);
    hashtable_insert(hashtable, key, i * 10);
  }

  hashtable_print(hashtable);
  
  // Realizando búsquedas
  for(int i = 1; i <= 20; i++) {
    char key[10];
    snprintf(key, sizeof(key), "clave%d", i);
    printf("Buscar %s: %d\n", key, hashtable_search(hashtable, key));
  }

  // Eliminando algunas claves
  hashtable_delete(hashtable, "clave3");
  hashtable_delete(hashtable, "clave10");
  printf("\nTabla hash después de eliminar 'clave3' y 'clave10':\n");
  hashtable_print(hashtable);

  // Búsquedas adicionales
  printf("\nBuscar claves eliminadas:\n");
  printf("Buscar clave3: %d\n", hashtable_search(hashtable, "clave3"));
  printf("Buscar clave10: %d\n", hashtable_search(hashtable, "clave10"));
  
  // Liberar la memoria
  hashtable_free(hashtable);
  puts("");
  printf("Tabla hash despúes de liberar:\n");

  hashtable_print(hashtable);
  
  return 0;
}