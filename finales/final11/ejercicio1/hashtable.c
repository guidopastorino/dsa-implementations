#include "hashtable.h"

static Entry* create_entry(char* key){
  Entry* entry = (Entry*)malloc(sizeof(Entry));
  assert(entry != NULL);
  entry->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(entry->key != NULL);
  strcpy(entry->key, key);
  entry->is_deleted = 0;
  return entry;
}

HashTable* ht_create(){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->table = (Entry**)calloc(INITIAL_SIZE, sizeof(Entry*));
  assert(ht->table != NULL);
  ht->count = 0;
  ht->size = INITIAL_SIZE;
  return ht;
}

static unsigned int hash(char* key, int size){
  unsigned int hash = 0;
  while(*key){
    hash = (hash << 5) + *key++;
  }
  return hash % size;
}

static void resize(HashTable* ht){
  int old_size = ht->size;
  Entry** old_table = ht->table;

  ht->size *= GROWTH_FACTOR;
  ht->table = (Entry**)calloc(ht->size, sizeof(Entry*));
  assert(ht->table != NULL);
  ht->count = 0;

  for(int i = 0; i<old_size; i++){
    if(old_table[i] != NULL && !old_table[i]->is_deleted){
      ht_insert(ht, old_table[i]->key);
      free(old_table[i]->key);
      free(old_table[i]);
    }
  }

  free(old_table);
}

static int needs_resize(HashTable* ht){
  return (float)ht->count / ht->size >= LOAD_FACTOR_THRESHOLD;
}

void ht_insert(HashTable* ht, char* key){
  if(needs_resize(ht)) resize(ht);
  unsigned int index = hash(key, ht->size);
  int probe_count = 0;

  while(ht->table[index] != NULL){
    if(!ht->table[index]->is_deleted && strcmp(ht->table[index]->key, key) == 0){
      printf("La clave %s ya existe en la tabla\n", key);
      return;
    }
    index = (index + ++probe_count) % ht->size;
  }

  if(ht->table[index] == NULL || ht->table[index]->is_deleted){
    if(ht->table[index] != NULL){
      free(ht->table[index]->key);
      free(ht->table[index]);
    }
    ht->table[index] = create_entry(key);
    ht->count++;
  }
}

int ht_search_prefix(HashTable* ht, char* prefix){
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL && !ht->table[i]->is_deleted){
      if(strncmp(ht->table[i]->key, prefix, strlen(prefix)) == 0){
        return 1;
      }
    }
  }
  return 0;
}

int ht_search_char(HashTable* ht, char c){
  int count = 0;
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL && !ht->table[i]->is_deleted){
      if(ht->table[i]->key[0] == c){
        count++;
      }
    }
  }
  return count;
}

void ht_delete(HashTable* ht, char* key){
  unsigned int index = hash(key, ht->size);
  int probe_count = 0;

  while(ht->table[index] != NULL){
    if(!ht->table[index]->is_deleted && strcmp(ht->table[index]->key, key) == 0){
      ht->table[index]->is_deleted = 1;
      ht->count--;
      return;
    }
    index = (index + ++probe_count) % ht->size;
    if(probe_count >= ht->size) return;
  }
}

void ht_display(HashTable* ht) {
  for (int i = 0; i < ht->size; i++) {
    printf("%d: ", i);
    if (ht->table[i] != NULL) {
      if (!ht->table[i]->is_deleted) {
        printf("%s\n", ht->table[i]->key); // Clave válida
      } else {
        printf("(eliminado)\n"); // Entrada eliminada
      }
    } else {
      printf("NULL\n"); // Entrada vacía
    }
  }
}

void ht_destroy(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL){
      free(ht->table[i]->key);
      free(ht->table[i]);
    }
  }
  free(ht->table);
  free(ht);
}
