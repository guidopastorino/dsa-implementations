#include "ht_clientes.h"

HashTableClientes* ht_clientes_create(){
  HashTableClientes* ht = (HashTableClientes*)malloc(sizeof(HashTableClientes));
  assert(ht != NULL);
  ht->table = (HashNode**)calloc(INITIAL_SIZE, sizeof(HashNode*));
  assert(ht->table != NULL);
  ht->size = INITIAL_SIZE;
  ht->count = 0;
  return ht;
}

static HashNode* crear_nodo(Cliente cliente){
  HashNode* hashNode = (HashNode*)malloc(sizeof(HashNode));
  assert(hashNode != NULL);
  hashNode->cliente = (Cliente*)malloc(sizeof(Cliente));
  assert(hashNode->cliente != NULL);
  // 
  hashNode->cliente->nombre = (char*)malloc(sizeof(char) * (strlen(cliente.nombre) + 1));
  assert(hashNode->cliente->nombre != NULL);
  strcpy(hashNode->cliente->nombre, cliente.nombre);
  // 
  hashNode->cliente->apellido = (char*)malloc(sizeof(char) * (strlen(cliente.apellido) + 1));
  assert(hashNode->cliente->apellido != NULL);
  strcpy(hashNode->cliente->apellido, cliente.apellido);
  // 
  hashNode->cliente->direccion = (char*)malloc(sizeof(char) * (strlen(cliente.direccion) + 1));
  assert(hashNode->cliente->direccion != NULL);
  strcpy(hashNode->cliente->direccion, cliente.direccion);
  // 
  hashNode->cliente->DNI = cliente.DNI;
  // 
  hashNode->cliente->telefono = (char*)malloc(sizeof(char) * (strlen(cliente.telefono) + 1));
  assert(hashNode->cliente->telefono != NULL);
  strcpy(hashNode->cliente->telefono, cliente.telefono);
  // 
  hashNode->next = NULL;
  return hashNode;
}

static unsigned int hash(HashTableClientes* ht, int DNI){
  return DNI % ht->size;
}

static void ht_clientes_resize(HashTableClientes* ht) {
  int old_size = ht->size;
  HashNode** old_table = ht->table;

  ht->size *= 2; // Aumentamos el tamaño de la tabla
  ht->table = (HashNode**)calloc(ht->size, sizeof(HashNode*));
  assert(ht->table != NULL);

  // Reinsertar elementos desde la tabla vieja
  for (int i = 0; i < old_size; i++) {
    HashNode* current = old_table[i];
    while (current != NULL) {
      HashNode* next = current->next; // Guardar el siguiente nodo
      unsigned int index = hash(ht, current->cliente->DNI);

      // Insertar directamente el nodo en la nueva tabla
      current->next = ht->table[index];
      ht->table[index] = current;

      current = next; // Avanzar al siguiente nodo
    }
  }

  free(old_table); // Liberar la memoria de la tabla vieja
}

static int needs_resize(HashTableClientes* ht){
  return ((float)ht->count / ht->size) >= LOAD_FACTOR_THRESHOLD;
}

void ht_clientes_insert(HashTableClientes* ht, Cliente* cliente){
  if(needs_resize(ht)){
    ht_clientes_resize(ht);
  }
  unsigned int index = hash(ht, cliente->DNI);
  HashNode* current = ht->table[index];
  HashNode* prev = NULL;
  while(current != NULL){
    if(current->cliente->DNI == cliente->DNI){
      printf("Error: Cliente con DNI %d ya existe.\n", cliente->DNI);
      return;
    }
    prev = current;
    current = current->next;
  }
  // insertar nuevo nodo
  HashNode* nodo = crear_nodo(*cliente);
  if(prev == NULL){
    ht->table[index] = nodo;
  } else {
    prev->next = nodo;
  }
  ht->count++;
}

// void ht_clientes_delete(HashTableClientes* ht, int DNI){
  
// }

Cliente* ht_clientes_search(HashTableClientes* ht, int DNI){
  unsigned int index = hash(ht, DNI);
  HashNode* current = ht->table[index];

  while(current != NULL){
    if(current->cliente->DNI == DNI){
      return current->cliente;
    }
    current = current->next;
  }

  return NULL;
}

void ht_clientes_display(HashTableClientes* ht){
  for(int i = 0; i<ht->size; i++){
    HashNode* current = ht->table[i];
    printf("%d: ", i);
    while(current != NULL){
      printf("(%s, %s, %s, %d, %s) -> ",
              current->cliente->nombre,
              current->cliente->apellido,
              current->cliente->direccion,
              current->cliente->DNI,
              current->cliente->telefono);
      current = current->next;
    }
    printf("NULL \n");
  }
}

void ht_clientes_destroy(HashTableClientes* ht){
  
}
