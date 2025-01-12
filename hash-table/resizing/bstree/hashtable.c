#include "hashtable.h"

HashTable* ht_create(){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->table = (BSTNode**)calloc(INITIAL_SIZE, sizeof(BSTNode));
  assert(ht->table != NULL);
  ht->count = 0;
  ht->size = INITIAL_SIZE;
  return ht;
}

/// @brief Calcula un índice hash más disperso para un dato dado.
/// @param data Valor entero a ser hasheado.
/// @param size Tamaño de la tabla hash.
/// @return Índice dentro de la tabla hash.
static unsigned int hash(int data, int size){
  unsigned int hash = (data * 2654435761u) ^ (data >> 16); // Mezcla datos
  return hash % size;
}

/// @brief Inserta todos los elementos de un árbol binario de búsqueda en la tabla hash.
/// @param ht Puntero a la tabla hash donde se reinserta el árbol.
/// @param root Puntero a la raíz del árbol binario que contiene los elementos.
static void reinsert_tree(HashTable* ht, BSTNode* root){
  reinsert_tree(ht, root->left);
  reinsert_tree(ht, root->right);

  ht_insert(ht, root->data);

  free(root);
}

/// @brief Redimensiona la tabla hash, aumentando su tamaño y reubicando los elementos.
/// @param ht Puntero a la tabla hash que se va a redimensionar.
static void resize(HashTable* ht){
  int old_size = ht->size;
  BSTNode** old_table = ht->table;

  ht->size *= GROWTH_FACTOR;
  ht->table = (BSTNode**)calloc(ht->size, sizeof(BSTNode*));
  assert(ht->table != NULL);

  for(int i = 0; i<old_size; i++){
    if(ht->table[i] != NULL){
      reinsert_tree(ht, ht->table[i]);
    }
  }

  free(old_table);
}

/// @brief Verifica si la tabla hash necesita ser redimensionada, basándose en la carga de la tabla.
/// @param ht Puntero a la tabla hash que se va a verificar.
/// @return 1 si la tabla hash necesita ser redimensionada, 0 si no.
static int needs_resize(HashTable* ht){
  return ((float)ht->count / ht->size) >= LOAD_FACTOR_THRESHOLD;
}

void ht_insert(HashTable* ht, int data){
  if(needs_resize(ht)){
    resize(ht);
  }
  unsigned int index = hash(data, ht->size);
  ht->table[index] = bst_insert(ht->table[index], data);
  ht->count++;
}

void ht_delete(HashTable* ht, int data){
  unsigned int index = hash(data, ht->size);
  ht->table[index] = bst_delete(ht->table[index], data);
  ht->count--;
}

int ht_search(HashTable* ht, int data){
  unsigned int index = hash(data, ht->size);
  return bst_search(ht->table[index], data);
}

void ht_print(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    printf("%d: ", i);
    if(ht->table[i] != NULL){
      bst_inorder(ht->table[i]);
      printf("\n");
    } else {
      printf("NULL\n");
    }
  }
}

void ht_destroy(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL){
      bst_destroy(ht->table[i]);
    }
  }
  free(ht->table);
  free(ht);
}