#include "hashtable.h"

HashTable* ht_create(HashFn hash, Copy copy, Compare cmp, Print print, Destroy destr){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->table = (AVLTree**)calloc(INITIAL_SIZE, sizeof(AVLTree*));
  assert(ht->table != NULL);
  ht->size = INITIAL_SIZE;
  ht->count = 0;
  ht->hash = hash;
  // Funciones auxiliares que nos ayudarán a manipular datos void*
  ht->copy = copy;
  ht->cmp = cmp;
  ht->print = print;
  ht->destr = destr;
  // Inicializamos cada árbol AVL de los buckets de la tabla hash
  for(int i = 0; i<ht->size; i++){
    ht->table[i] = NULL;
  }
  return ht;
}

/// @brief Reinserta los nodos de un árbol AVL en la tabla hash durante una operación de redimensionamiento.
/// Libera la memoria de los nodos originales después de mover sus datos.
/// @param ht Puntero a la tabla hash en la que se reinserta.
/// @param root Nodo raíz del árbol AVL que será procesado.
static void reinsert_avl(HashTable* ht, AVLNode* root){
  if(root != NULL){
    reinsert_avl(ht, root->left);
    reinsert_avl(ht, root->right);

    ht_insert(ht, root->data);

    // luego de realizar la inserción del dato del nodo, liberamos la memoria
    ht->destr(root->data);
    free(root);
  }
}

/// @brief Cambia el tamaño de la tabla hash aumentando el número de buckets y reinserta los elementos existentes.
/// @param ht Puntero a la tabla hash que será redimensionada.
static void resize(HashTable* ht){
  int old_size = ht->size;
  AVLTree** old_table = ht->table;

  // Incrementamos el tamaño por un factor de 1.5
  ht->size = (int)(ht->size * 1.5);;  // Crecer gradualmente, no duplicar
  ht->table = (AVLTree**)calloc(ht->size, sizeof(AVLTree*));

  // Inicializamos los árboles de cada bucket de la nueva tabla
  for(int i = 0; i < ht->size; i++){
    ht->table[i] = NULL;
  }

  // Reinsertamos los árboles viejos en la nueva tabla
  for(int i = 0; i < old_size; i++){
    if(old_table[i] != NULL && old_table[i]->root != NULL){
      // Reinsertamos el árbol
      reinsert_avl(ht, old_table[i]->root);
      free(old_table[i]); // liberamos el bucket viejo
    }
  }

  // Liberamos la memoria de la tabla vieja
  free(old_table);
}

/// @brief Verifica si la tabla hash necesita ser redimensionada según el factor de carga.
/// @param ht Puntero a la tabla hash a verificar.
/// @return 1 si necesita redimensionarse, 0 en caso contrario.
static int needs_resize(HashTable* ht){
  return ((float)ht->count / ht->size >= LOAD_FACTOR_THRESHOLD);
}

void ht_insert(HashTable* ht, void* data){
  if(needs_resize(ht)){
    resize(ht);
  }
  unsigned int index = ht->hash(data, ht->size);
  if(ht->table[index] == NULL){
    ht->table[index] = avl_create_tree(ht->copy, ht->cmp, ht->print, ht->destr);
  }
  avl_insert(ht->table[index], data);
  ht->count++;
}

void ht_delete(HashTable* ht, void* data) {
  unsigned int index = ht->hash(data, ht->size);
  avl_delete(ht->table[index], data);
}

int ht_search(HashTable* ht, void* data){
  unsigned int index = ht->hash(data, ht->size);
  return avl_search(ht->table[index], data);
}

void ht_display(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    printf("%d: ", i);
    if(ht->table[i] != NULL && ht->table[i]->root != NULL){
      avl_dfs(ht->table[i]);
    } else {
      printf("NULL\n");
    }
  }
}

void ht_destroy(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL && ht->table[i]->root != NULL){
      avl_destroy(ht->table[i]);
    }
  }
  free(ht->table);
  free(ht);
}