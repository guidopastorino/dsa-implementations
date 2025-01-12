#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
  struct TrieNode* children[ALPHABET_SIZE];
  int isEndOfWord;
} TrieNode;

// Crear un nodo Trie
TrieNode* createNode() {
  TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
  assert(node != NULL);
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    node->children[i] = NULL;
  }
  node->isEndOfWord = 0;
  return node;
}

// Insertar una palabra en el Trie
void insert(TrieNode* root, char* word) {
  TrieNode* current = root;

  for (int i = 0; word[i] != 0; i++) {
    int index = word[i] - 'a';
    if (!current->children[index]) {
      current->children[index] = createNode();
    }
    current = current->children[index];
  }

  current->isEndOfWord = 1;
}

// Buscar una palabra en el Trie
int search(TrieNode* root, char* word) {
  TrieNode* current = root;

  for (int i = 0; word[i] != 0; i++) {
    int index = word[i] - 'a';

    if (!current->children[index]) {
      return 0;
    }

    current = current->children[index];
  }

  return current->isEndOfWord;
}

// Eliminar una palabra del Trie
int deleteHelper(TrieNode* root, char* word, int depth) {
  if (root == NULL) return 0;

  if (word[depth] == 0) {
    if (root->isEndOfWord) {
      root->isEndOfWord = 0;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (root->children[i] != NULL) return 0;
    }

    return 1;  // Nodo puede ser liberado
  }

  int index = word[depth] - 'a';
  if (deleteHelper(root->children[index], word, depth + 1)) {
    free(root->children[index]);
    root->children[index] = NULL;

    if (!root->isEndOfWord) {
      for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) return 0;
      }
      return 1;  // Nodo puede ser liberado
    }
  }

  return 0;
}

// Función para eliminar una palabra
void delete(TrieNode* root, char* word) {
  deleteHelper(root, word, 0);
}

// Imprimir todas las palabras en el Trie
void printWordsHelper(TrieNode* root, char* word, int level) {
  if (root == NULL) return;

  if (root->isEndOfWord) {
    word[level] = 0;
    printf("%s\n", word);
  }

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i] != NULL) {
      word[level] = i + 'a';
      printWordsHelper(root->children[i], word, level + 1);
    }
  }
}

void printWords(TrieNode* root) {
  char word[100];
  printWordsHelper(root, word, 0);
}

// Comprobar si hay palabras con cierto prefijo
int startsWith(TrieNode* root, char* prefix) {
  TrieNode* current = root;

  for (int i = 0; prefix[i] != 0; i++) {
    int index = prefix[i] - 'a';

    if (!current->children[index]) {
      return 0;
    }

    current = current->children[index];
  }

  return 1;
}

// Liberar la memoria del Trie
void freeTrie(TrieNode* root) {
  if (root != NULL) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (root->children[i] != NULL) {
        freeTrie(root->children[i]);
      }
    }
    free(root);
  }
}

int main() {
  TrieNode* root = createNode();  // Crear el nodo raíz del Trie

  insert(root, "hello");
  insert(root, "world");
  insert(root, "her");
  insert(root, "word");

  printf("Palabras en el Trie:\n");
  printWords(root);

  printf("\nBuscar 'hello': %s\n", search(root, "hello") ? "Encontrado" : "No encontrado");
  printf("Buscar 'world': %s\n", search(root, "world") ? "Encontrado" : "No encontrado");
  printf("Buscar 'word': %s\n", search(root, "word") ? "Encontrado" : "No encontrado");

  printf("\nEmpieza con 'wo': %s\n", startsWith(root, "wo") ? "Sí" : "No");
  printf("Empieza con 'he': %s\n", startsWith(root, "he") ? "Sí" : "No");
  printf("Empieza con 'hi': %s\n", startsWith(root, "hi") ? "Sí" : "No");

  delete(root, "hello");
  printf("\nPalabras en el Trie después de eliminar 'hello':\n");
  printWords(root);

  freeTrie(root);  // Liberar memoria
  return 0;
}
