#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef struct bstNodo_ {
    int dato;
    struct bstNodo_ *der , *izq;
} bstNodo;

typedef bstNodo* BSTSet;

/// @brief Crea un nuevo nodo para el arbol
/// @param dato Dato que tendrá el nodo
/// @return Puntero a la direccion de memoria donde se creó el nodo
BSTSet crearBST(int dato);

/// @brief Agrega un nuevo dato al arbol. Si el dato es duplicado (ya existe) ignora el procedimiento y no lo inserta
/// @param raiz Raiz del arbol a agregar el nodo
/// @param dato Nuevo dato que se agregara al arbol
/// @return Puntero al nuevo dato agregado que contiene el nuevo nodo
BSTSet agregarBST(BSTSet raiz, int dato);

/// @brief Recorre el árbol imprimiendo los nodos por nivel. Usa una queue para almacenar los nodos y mientras los recorre se desencolan y se imprimen.
/// @param raiz Raiz del árbol
void imprimeBST(BSTSet raiz);

/// @brief Retorna un nuevo arbol binario con la interseccion de los dos arboles
/// @param raiz1 Raiz del primer arbol para obtener su interseccion
/// @param raiz2 Raiz del segundo arbol para obtener su interseccion
/// @return Arbol binario con la interseccion de los dos arboles pasados por parametro
BSTSet interseccionBST(BSTSet raiz1, BSTSet raiz2);

/// @brief Dado un conjunto y un entero k, devuelve el número presente en el conjunto más lejano a k (en valor absoluto, puede ser mayor o menor).
/// @param raiz Árbol a verificar si existe el nodo con el número mayor a entero k (el más lejano) que queremos encontrar
/// @param k Entero que verificaremos si existe su mayor más lejano
/// @return El nodo en el arbol con el número mayor más lejano a k 
BSTSet lejanoBST(BSTSet raiz, int k);

/// @brief Destruye (libera la memoria) de todos los nodos de un arbol binario
/// @param raiz Raiz del arbol a ser destruido
void destruirBST(BSTSet raiz);

#endif