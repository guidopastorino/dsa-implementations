#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_SIZE 10
#define LOAD_FACTOR_THRESHOLD 0.90

typedef struct {
  char* key;
  int val;
} Entry;

typedef struct _Node {
  Entry* entry;
  struct _Node* next;
} Node;

typedef struct {
  Node** table;
  int count;
  int size;
} HashTable;

HashTable* create_hashtable(){
  HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
  assert(ht != NULL);
  ht->table = (Node**)calloc(INITIAL_SIZE, sizeof(Node*));
  assert(ht->table != NULL);
  ht->size = INITIAL_SIZE;
  ht->count = 0;
  return ht;
}

Node* create_node(char* key, int val){
  Node* node = (Node*)malloc(sizeof(Node));
  assert(node != NULL);
  node->entry = (Entry*)malloc(sizeof(Entry));
  assert(node->entry != NULL);
  node->entry->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  assert(node->entry->key != NULL);
  strcpy(node->entry->key, key);
  node->entry->val = val;
  node->next = NULL;
  return node;
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
  Node** old_table = ht->table;

  ht->size *= 2;
  ht->table = (Node**)calloc(ht->size, sizeof(Entry*));
  assert(ht->table != NULL);

  for(int i = 0; i<old_size; i++){
    Node* current = old_table[i];
    while(current != NULL){
      Node* temp = current->next;
      unsigned int new_index = hash(ht, current->entry->key);
      current->next = ht->table[new_index];
      ht->table[new_index] = current;
      current = temp;
    }
  }

  free(old_table);
}

int needs_resize(HashTable* ht){
  return ((float)ht->count / ht->size) >= LOAD_FACTOR_THRESHOLD;
}

void insert(HashTable* ht, char* key, int val){
  if(needs_resize(ht)){
    resize(ht);
  }

  unsigned int index = hash(ht, key);

  Node* new_entry = create_node(key, val);
  Node* current = ht->table[index];

  if(current == NULL){
    ht->table[index] = new_entry;
  } else {
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;
  }

  ht->count++;
}

void delete(HashTable* ht, char* key){
  unsigned int index = hash(ht, key);

  Node* current = ht->table[index];
  Node* prev = NULL;

  while(current != NULL){
    if(strcmp(current->entry->key, key) == 0){
      if(prev == NULL){
        ht->table[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current->entry->key);
      free(current->entry);
      free(current);
      current = NULL;
      ht->count--;
      return;
    }
    prev = current;
    current = current->next;
  }
}

int search(HashTable* ht, char* key){
  unsigned int index = hash(ht, key);
  Node* current = ht->table[index];

  while(current != NULL){
    if(strcmp(current->entry->key, key) == 0){
      return current->entry->val;
    }
    current = current->next;
  }

  return -1;
}

void display(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    printf("%d: ", i);
    Node* current = ht->table[i];
    while(current != NULL){
      printf("(%s, %d) -> ", current->entry->key, current->entry->val);
      current = current->next;
    }
    printf("NULL\n");
  }
}

void destroy(HashTable* ht){
  for(int i = 0; i<ht->size; i++){
    Node* current = ht->table[i];
    while(current != NULL){
      Node* temp = current;
      current = current->next;
      free(temp->entry->key);
      free(temp->entry);
      free(temp);
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
    {"Walter", 39}, {"Ximena", 30}, {"Yuri", 22}, {"Zara", 25},
    {"Aaron", 26}, {"Becky", 31}, {"Caleb", 28}, {"Daphne", 34},
    {"Elliot", 29}, {"Faith", 23}, {"Gavin", 33}, {"Hazel", 27},
    {"Ian", 36}, {"Joy", 25}, {"Kyle", 37}, {"Lily", 32},
    {"Mason", 30}, {"Nora", 22}, {"Owen", 24}, {"Piper", 26},
    {"Quinton", 35}, {"Ruby", 29}, {"Scott", 31}, {"Tara", 20},
    {"Ulysses", 28}, {"Vivian", 21}, {"Wyatt", 40}, {"Xyla", 33},
    {"Yara", 34}, {"Zane", 39}, {"Amber", 25}, {"Blake", 23},
    {"Cora", 27}, {"Derek", 38}, {"Eva", 30}, {"Finn", 28},
    {"Gina", 24}, {"Hunter", 32}, {"Ivy", 31}, {"Jared", 29},
    {"Kara", 35}, {"Logan", 36}, {"Mila", 22}, {"Noah", 34},
    {"Omar", 33}, {"Paige", 26}, {"Quinn", 31}, {"Riley", 27},
    {"Sophie", 30}, {"Trent", 37}, {"Ulric", 28}, {"Violet", 24}
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