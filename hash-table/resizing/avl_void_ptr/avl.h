#ifndef _AVL_H_
#define _AVL_H_

#include "types.h"

/// @brief Macro para obtener el valor máximo entre dos números.
/// @param a Primer número a comparar.
/// @param b Segundo número a comparar.
/// @return El valor máximo entre `a` y `b`.
#define MAX(a, b)(a > b ? a : b)

/// @brief Estructura que representa un nodo del árbol AVL
typedef struct _AVLNode {
  void* data;               /* Dato general de tipo void* que contendrá el nodo */ 
  struct _AVLNode* left;    /* Referencia al hijo izquierdo del nodo */ 
  struct _AVLNode* right;   /* Referencia al hijo derecho del nodo */
  int height;               /* Altura del nodo */         
} AVLNode;

/// @brief Estructura general que representa un árbol AVL
typedef struct {
  AVLNode* root;            /* Nodo raíz del arbol */
  Copy copy;                /* Función para copiar un dato a otra dirección de memoria */
  Compare cmp;              /* Función para comparar dos datos de tipo void* */
  Print print;              /* Función para imprimir el dato de un nodo */
  Destroy destr;            /* Función para destruir el dato de un nodo */
} AVLTree;

/// @brief Crea un árbol AVL vacío.
/// @param copy Función para copiar los datos almacenados en el árbol.
/// @param cmp Función para comparar los datos almacenados en el árbol.
/// @param print Función para imprimir los datos del árbol.
/// @param destr Función para liberar la memoria de los datos almacenados en el árbol.
/// @return Un puntero a una estructura de árbol AVL recién creada.
AVLTree* avl_create_tree(Copy copy, Compare cmp, Print print, Destroy destr);

/// @brief Inserta un dato en el árbol AVL, manteniendo su equilibrio.
/// @param avl Puntero al árbol AVL.
/// @param data Dato a insertar en el árbol.
void avl_insert(AVLTree* avl, void* data);

/// @brief Elimina un dato del árbol AVL, manteniendo su equilibrio.
/// @param avl Puntero al árbol AVL.
/// @param data Dato a eliminar del árbol.
void avl_delete(AVLTree* avl, void* data);

/// @brief Busca un dato en el árbol AVL.
/// @param avl Puntero al árbol AVL.
/// @param data Dato a buscar en el árbol.
/// @return Devuelve 1 si el dato se encuentra en el árbol, o 0 en caso contrario.
int avl_search(AVLTree* avl, void* data);

/// @brief Recorre el árbol AVL en profundidad y aplica la función de impresión a cada nodo.
/// @param avl Puntero al árbol AVL.
void avl_dfs(AVLTree* avl);

/// @brief Libera toda la memoria asociada al árbol AVL.
/// @param avl Puntero al árbol AVL.
void avl_destroy(AVLTree* avl);

#endif /* _AVL_H_ */