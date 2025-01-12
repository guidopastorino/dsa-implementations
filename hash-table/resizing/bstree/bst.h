#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _BSTNode {
  int data;
  struct _BSTNode* left;
  struct _BSTNode* right;
} BSTNode;

/// @brief Crea un nuevo nodo en el árbol binario de búsqueda con el valor dado.
/// @param data Valor que se almacenará en el nuevo nodo.
/// @return Puntero al nuevo nodo creado.
BSTNode* create_mode(int data);

/// @brief Inserta un valor en el árbol binario de búsqueda de manera recursiva.
/// @param root Puntero al nodo raíz del árbol o subárbol.
/// @param data Valor que se va a insertar.
/// @return Puntero al nodo raíz actualizado del árbol o subárbol.
BSTNode* bst_insert(BSTNode* root, int data);

/// @brief Elimina un nodo con el valor dado en el árbol binario de búsqueda.
/// @param root Puntero al nodo raíz del árbol o subárbol.
/// @param data Valor del nodo que se desea eliminar.
/// @return Puntero al nodo raíz actualizado del árbol o subárbol después de la eliminación.
BSTNode* bst_delete(BSTNode* root, int data);

/// @brief Busca un valor en el árbol binario de búsqueda.
/// @param root Puntero al nodo raíz del árbol o subárbol.
/// @param data Valor que se busca.
/// @return 1 si el valor se encuentra en el árbol, 0 en caso contrario.
int bst_search(BSTNode* root, int data);

/// @brief Realiza un recorrido en orden del árbol binario de búsqueda y ejecuta una acción sobre cada nodo.
/// @param root Puntero al nodo raíz del árbol o subárbol.
void bst_inorder(BSTNode* root);

/// @brief Destruye el árbol binario de búsqueda liberando la memoria de cada nodo.
/// @param root Puntero al nodo raíz del árbol o subárbol que se destruirá.
void bst_destroy(BSTNode* root);

#endif /* _BST_H_ */