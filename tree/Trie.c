#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Definición de un nodo en el Trie
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE]; // Arreglo de punteros a los nodos hijos
    bool isEndOfWord;  // Marca si este nodo es el final de una palabra
} TrieNode;

// Función para crear un nuevo nodo
TrieNode* createNode() {
  TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
  if (newNode) {
      newNode->isEndOfWord = false;
      for (int i = 0; i < ALPHABET_SIZE; i++) {
          newNode->children[i] = NULL;
      }
  }
  return newNode;
}

// Función para insertar una palabra en el Trie
void insert(TrieNode* root, const char* word) {
  TrieNode* currentNode = root;
  while (*word) {
      int index = *word - 'a';  // Calcular índice para el carácter
      if (currentNode->children[index] == NULL) {
          currentNode->children[index] = createNode();
      }
      currentNode = currentNode->children[index];
      word++;
  }
  currentNode->isEndOfWord = true;  // Marcar el final de la palabra
}

// Función para buscar una palabra en el Trie
bool search(TrieNode* root, const char* word) {
  TrieNode* currentNode = root;
  while (*word) {
      int index = *word - 'a';
      if (currentNode->children[index] == NULL) {
          return false;  // La palabra no existe
      }
      currentNode = currentNode->children[index];
      word++;
  }
  return currentNode->isEndOfWord;  // Verificar si es el final de una palabra
}

// Función auxiliar para eliminar un nodo del Trie
bool deleteHelper(TrieNode* root, const char* word, int depth) {
  if (root == NULL) {
    return false;
  }

  // Caso base: Si hemos llegado al final de la palabra
  if (word[depth] == '\0') {
    if (root->isEndOfWord) {
      root->isEndOfWord = false;
    }

    // Si no hay hijos, podemos eliminar el nodo
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (root->children[i] != NULL) {
        return false;
      }
    }
    return true; // El nodo es eliminable
  }

  // Recursión hacia el siguiente nodo
  int index = word[depth] - 'a';
  if (deleteHelper(root->children[index], word, depth + 1)) {
    free(root->children[index]);
    root->children[index] = NULL;

    // Si el nodo actual no tiene hijos y no es el final de una palabra, lo podemos eliminar
    if (!root->isEndOfWord) {
      for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
          return false;
        }
      }
      return true; // El nodo es eliminable
    }
  }
  return false;
}

// Función para eliminar una palabra del Trie
void delete(TrieNode* root, const char* word) {
    deleteHelper(root, word, 0);
}

// Función auxiliar para imprimir las palabras
void printWordsHelper(TrieNode* root, char* word, int level) {
  if (root == NULL) {
    return;
  }

  // Si el nodo es el final de una palabra, imprimimos la palabra
  if (root->isEndOfWord) {
    word[level] = '\0';  // Finalizamos la palabra
    printf("%s\n", word);
  }

  // Recorremos todos los hijos
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i] != NULL) {
      word[level] = i + 'a';  // Asignamos el carácter correspondiente
      printWordsHelper(root->children[i], word, level + 1);  // Llamada recursiva
    }
  }
}

// Función para imprimir todas las palabras del Trie
void printWords(TrieNode* root) {
  char word[100];  // Asumimos que las palabras no son más largas de 100 caracteres
  printWordsHelper(root, word, 0);
}

// Función para verificar si existe alguna palabra que empiece con el prefijo dado
bool startsWith(TrieNode* root, const char* prefix) {
  TrieNode* currentNode = root;
  while (*prefix) {
    int index = *prefix - 'a';  // Calcular índice para el carácter del prefijo
    if (currentNode->children[index] == NULL) {
      return false;  // No existe el prefijo
    }
    currentNode = currentNode->children[index];
    prefix++;
  }
  return true;  // El prefijo existe en el Trie
}

// Función para liberar la memoria del Trie
void freeTrie(TrieNode* root) {
  if (root == NULL) {
    return;
  }
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i] != NULL) {
      freeTrie(root->children[i]);
    }
  }
  free(root);
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

  freeTrie(root);  // Liberar la memoria del Trie
  return 0;
}
