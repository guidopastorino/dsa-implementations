#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
  char* key;
  int val;
} Entry;

typedef struct {
  Entry** table;
  int count;
  int size;
} HashTable;

#define INITIAL_SIZE 10
#define LOAD_FACTOR_THRESHOLD 0.75

// ----------------------------------------------
HashTable* create_hashtable();
Entry* create_entry(char* key, int val);
unsigned int hash(HashTable* ht, char* key);
void resize(HashTable* ht);
int needs_resize(HashTable* ht);
void insert(HashTable* ht, char* key, int val);
void delete(HashTable* ht, char* key);
int search(HashTable* ht, char* key);
void display(HashTable* ht);
void destroy(HashTable* ht);
// ----------------------------------------------

HashTable* create_hashtable(){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->table = (Entry**)calloc(INITIAL_SIZE, sizeof(Entry*));
  assert(ht->table != NULL);
  ht->size = INITIAL_SIZE;
  ht->count = 0;
  return ht;
}

Entry* create_entry(char* key, int val){
  Entry* entry = (Entry*)malloc(sizeof(Entry));
  assert(entry != NULL);
  entry->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(entry->key != NULL);
  strcpy(entry->key, key);
  entry->val = val;
  return entry;
}

unsigned int hash(HashTable* ht, char* key){
  unsigned int hash = 0;
  while(*key){
    hash = (hash << 5) + *key++;
  }
  return hash % ht->size;
}

void resize(HashTable* ht){
  int old_size = ht->size;
  Entry** old_table = ht->table;

  ht->size *= 2;
  ht->table = (Entry**)calloc(ht->size, sizeof(Entry*));
  assert(ht->table != NULL);

  for(int i = 0; i<old_size; i++){
    Entry* entry = old_table[i];
    if(entry != NULL){
      unsigned int index = hash(ht, entry->key);
      int j = 0;
      while(ht->table[index] != NULL){
        index = (index + ++j) % ht->size;
      }
      ht->table[index] = entry;
    }
  }

  free(old_table);
}

int needs_resize(HashTable* ht){
  return ((float)ht->count / ht->size >= LOAD_FACTOR_THRESHOLD);
}

void insert(HashTable* ht, char* key, int val){
  if(needs_resize(ht)){
    resize(ht);
  }

  unsigned int index = hash(ht, key);
  int i = 0;

  while(ht->table[index] != NULL){
    if(strcmp(ht->table[index]->key, key) == 0){
      ht->table[index]->val = val;
      return;
    }
    index = (index + ++i) % ht->size;
  }

  ht->table[index] = create_entry(key, val);
  ht->count++;
}

void delete(HashTable* ht, char* key){
  unsigned int index = hash(ht, key);
  int i = 0;

  while(ht->table[index] != NULL){
    if(strcmp(ht->table[index]->key, key) == 0){
      free(ht->table[index]->key);
      free(ht->table[index]);
      ht->table[index] = NULL;
      ht->count--;
      return;
    }
    index = (index + ++i) % ht->size;
  }
}

int search(HashTable* ht, char* key){
  unsigned int index = hash(ht, key);
  int i = 0;

  while(ht->table[index] != NULL){
    if(strcmp(ht->table[index]->key, key) == 0){
      return ht->table[index]->val;
    }
    index = (index + ++i) % ht->size;
  }

  return -1;
}

void display(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    printf("%d: ", i);
    if(ht->table[i] != NULL){
      printf("(%s, %d)\n", ht->table[i]->key, ht->table[i]->val);
    } else {
      printf("NULL\n");
    }
  }
}

void destroy(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    if(ht->table[i] != NULL){
      free(ht->table[i]->key);
      free(ht->table[i]);
      ht->table[i] = NULL;
    }
  }
  free(ht->table);
  free(ht);
}


int main(){
  Entry entries[] = {
    {"Alice", 25}, {"Bob", 30}, {"Charlie", 35}, {"Diana", 28},
    {"Ethan", 40}, {"Fiona", 22}, {"George", 29}, {"Hannah", 31},
    {"Ivan", 27}, {"Jasmine", 33}, {"Kevin", 24}, {"Laura", 26},
    {"Mike", 32}, {"Nina", 21}, {"Oliver", 37}, {"Paula", 23},
    {"Quinn", 34}, {"Rachel", 20}, {"Sam", 38}, {"Tina", 36},
    {"Ursula", 29}, {"Victor", 41}, {"Wendy", 30}, {"Xander", 39},
    {"Yasmine", 28}, {"Zack", 26}, {"Anna", 27}, {"Brian", 24},
    {"Cindy", 32}, {"David", 34}, {"Ella", 25}, {"Frank", 33},
    {"Grace", 30}, {"Henry", 31}, {"Isla", 22}, {"Jack", 35},
    {"Karen", 23}, {"Liam", 38}, {"Mona", 20}, {"Nathan", 29},
    {"Oscar", 40}, {"Penny", 21}, {"Quincy", 37}, {"Rita", 27},
    {"Steve", 36}, {"Tracy", 26}, {"Uma", 28}, {"Vera", 24},
    {"Walter", 39}, {"Ximena", 30}, {"Yuri", 22}, {"Zara", 25}
  };

  int entriesSize = sizeof(entries) / sizeof(entries[0]);

  printf("Cantidad de entradas: %d\n", entriesSize);

  HashTable* ht = create_hashtable();

  for(int i = 0; i<entriesSize; i++){
    insert(ht, entries[i].key, entries[i].val);
  }

  display(ht);

  destroy(ht);

  return 0;
}