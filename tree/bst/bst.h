#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct _BSTNode {
  int data;
  struct _BSTNode* left;
  struct _BSTNode* right;
} BSTNode;

// Crea un nuevo nodo bst
BSTNode* createNode(int data);

// Inserta un nodo en el bst
BSTNode* insert(BSTNode* root, int data);

// Devuelve 1 si el dato está en el bst, 0 en caso contrario
int search(BSTNode* root, int data);

// Elimina un nodo del bst
BSTNode* delete(BSTNode* root, int data);

// Retorna la cantidad de hojas
int count_leaf_nodes(BSTNode* root);

// Devuelve los ancestros de un nodo
int count_node_ancestors(BSTNode* root, int target);

// Verifica si el arbol es un bst full

// Verifica si el arbol es un bst completo

// Verifica si el arbol es un bst perfecto

// Verifica si el arbol es un bst balanceado

// Verifica si el arbol es un bst degenerado

// Recorrido inorder del bst
void inorder(BSTNode* root);

// Elimina la memoria ocupada en el bst
void destroy_tree(BSTNode* root);

// Calcula la intersección de dos BSTs.
BSTNode* bst_intersection(BSTNode* root1, BSTNode* root2);

// Calcula la unión de dos BSTs.
BSTNode* bst_union(BSTNode* root1, BSTNode* root2);

// Calcula la diferencia entre dos BSTs.
BSTNode* bst_difference(BSTNode* root1, BSTNode* root2);

// Encuentra el nodo con el valor máximo en el BST.
BSTNode* find_max(BSTNode* root);

// Encuentra el k-ésimo elemento más pequeño en el BST.
BSTNode* kth_smallest(BSTNode* root, int k);

// Encuentra el k-ésimo elemento más grande en el BST.
BSTNode* kth_largest(BSTNode* root, int k);

// Comprueba si dos BSTs son idénticos.
BSTNode* is_identical(BSTNode* root1, BSTNode* root2);

// Función para comprobar si root2 es un subárbol de root1
int is_subtree(BSTNode* root1, BSTNode* root2);

// Encuentra el ancestro común más cercano de dos nodos (Lowest Common Ancestor).
BSTNode* lowest_common_ancestor(BSTNode* root, BSTNode* node1, BSTNode* node2);

// Calcula la suma de los valores de los nodos dentro de un rango dado.
int range_sum(BSTNode* root, int low, int high);

// Convierte el BST en una lista doblemente enlazada (en inorden).
// convert_to_dll

// Verifica si un árbol binario genérico es un BST válido.
int is_bst(BSTNode* root);

// Genera un árbol espejo del BST.
void mirror(BSTNode* root);

// Cuenta los nodos cuyos valores están dentro de un rango específico.
// count_nodes_in_range

// Implementa un recorrido por niveles en el BST.
// level_order

// Calcula el diámetro del árbol.
// diameter

// Verifica si hay un camino con una suma específica en el BST.
int path_sum(BSTNode* root, int sum);

// Genera todas las rutas desde la raíz a las hojas.
// all_paths

// Encuentra el sucesor inorden de un nodo.
// find_successor

// Encuentra el predecesor inorden de un nodo.
// find_predecessor

// Encuentra el sucesor en inorden de un nodo sin usar recursión.
// inorder_successor_non_recursive

// Encuentra el predecesor en inorden de un nodo sin usar recursión.
// inorder_predecessor_non_recursive

// Serializa el BST en un formato que pueda almacenarse o transmitirse.
// serialize_tree

// Reconstruye un BST a partir de su representación serializada.
// deserialize_tree

// Convierte el BST en un arreglo en inorden.
// tree_to_array

// Construye un BST equilibrado a partir de un arreglo ordenado.
// array_to_bst

// Convierte el BST en un Min Heap.
// convert_to_min_heap

// Convierte el BST en un Max Heap.
// convert_to_max_heap

// Cuenta las inversiones en un arreglo usando el BST.
// count_inversions

// Verifica si el BST es simétrico.
// is_symmetric

// Encuentra la ruta desde la raíz hasta un nodo específico.
// path_to_node

// Elimina un subárbol específico dentro del BST.
// delete_subtree

// Crea una copia exacta del BST.
// clone_tree

// Cuenta los nodos internos (nodos no hoja).
// count_internal_nodes

// Cuenta los nodos con un solo hijo.
// count_single_child_nodes

// Calcula la distancia entre dos nodos en términos de número de aristas.
// distance_between_nodes

// Verifica si existe un camino desde la raíz hasta una hoja con una suma específica.
// check_path_with_given_sum

// Cuenta todos los caminos en el BST que tienen una suma específica.
// count_paths_with_sum

// Encuentra el valor más cercano a un número dado en el BST.
// find_closest_value

// Convierte el BST a una lista doblemente enlazada circular.
// bst_to_circular_dll

// Invierte el BST (equivalente a un árbol espejo).
// invert_tree

// Encuentra todos los nodos a una distancia k desde la raíz.
// nodes_at_k_distance

// Encuentra el valor más pequeño en el BST que sea mayor o igual a un valor dado.
// find_ceil

// Encuentra el valor más grande en el BST que sea menor o igual a un valor dado.
// find_floor

// Cuenta los pares de nodos cuyos valores suman un número dado.
// count_bst_pairs_with_sum

// Calcula la suma de todos los nodos hoja.
// sum_of_leaf_nodes

// Calcula la suma de los valores de todos los nodos internos.
// sum_of_internal_nodes

// Calcula la suma de todos los valores del subárbol derecho.
// sum_of_right_subtree

// Calcula la suma de todos los valores del subárbol izquierdo.
// sum_of_left_subtree

// Elimina todos los nodos del árbol excepto las hojas.
// delete_tree_except_leaves

// Calcula el ancho máximo del árbol en cualquier nivel.
// max_width

// Cuenta el número de nodos en un nivel específico k.
// count_nodes_at_level_k

// Calcula la suma de los nodos en cada línea vertical del árbol.
// vertical_sum

// Realiza un recorrido del árbol en orden vertical.
// vertical_order_traversal

// Imprime los nodos que forman la vista superior del árbol.
// top_view

// Imprime los nodos que forman la vista inferior del árbol.
// bottom_view

// Imprime los nodos que forman la vista izquierda del árbol.
// left_view

// Imprime los nodos que forman la vista derecha del árbol.
// right_view

// Encuentra el nodo más profundo del árbol.
// deepest_node

// Calcula la suma de los nodos en un nivel específico k.
// sum_of_nodes_at_depth_k

// Encuentra el subárbol más grande que también sea un BST.
// find_largest_bst

// Comprueba si dos árboles binarios son isomorfos.
// isomorphic_trees

// Realiza un recorrido en zigzag del árbol.
// zigzag_traversal

// Imprime los nodos en la frontera del árbol (hojas y bordes).
// boundary_traversal

// Encuentra todos los nodos cuyos valores están entre dos valores dados.
// find_nodes_between

// Encuentra todos los nodos que están a una distancia k desde un nodo objetivo.
// find_k_distance_nodes_from_target

// Reemplaza cada nodo con la suma de sus descendientes.
// replace_with_sum_of_descendants

// Cuenta todos los caminos desde la raíz a las hojas que contienen un número par de nodos.
// count_paths_with_even_nodes

// Construye un BST dado su recorrido en preorden.
// construct_bst_from_preorder

// Construye un BST dado su recorrido en postorden.
// construct_bst_from_postorder

// Construye un BST a partir de sus recorridos en inorden y preorden.
// construct_bst_from_inorder_and_preorder

// Construye un BST a partir de sus recorridos en inorden y postorden.
// construct_bst_from_inorder_and_postorder

// Combina dos BSTs en uno.
// merge_two_bsts

// Elimina los nodos que no están dentro de un rango específico.
// delete_nodes_outside_range

// Convierte el BST en un arreglo con los nodos ordenados por niveles.
// convert_to_array_sorted_levels

// Verifica si la suma de cualquier camino desde la raíz hasta una hoja es un número primo.
// check_if_root_to_leaf_sum_is_prime

// Encuentra el valor mediano de los nodos en el BST.
// find_median

// Cuenta los subárboles únicos dentro del BST.
// count_unique_subtrees

// Encuentra la hoja más cercana a un nodo dado.
// find_closest_leaf

// Calcula la distancia desde la raíz hasta un nodo específico.
// distance_from_root_to_node

// Imprime los primos (nodos en el mismo nivel, pero con diferentes padres) de un nodo dado.
// print_cousins

// Encuentra el Ancestro Común Más Bajo (LCA, por sus siglas en inglés) de dos nodos sin usar recursión.
// find_lca_non_recursive

// Imprime los niveles del árbol en orden inverso (de hojas a raíz).
// print_level_order_reverse

// Verifica si existe un camino con una suma mayor a un valor k.
// path_sum_greater_than_k

// Encuentra el camino más largo desde la raíz hasta una hoja.
// longest_root_to_leaf_path

// Verifica si el árbol es plegable (foldable).
// check_if_foldable

// Recorta el árbol eliminando nodos cuyo valor total de subárbol sea menor a un umbral.
// prune_tree

// Actualiza el valor de un nodo existente, asegurando que el BST siga siendo válido.
// update_value

// Imprime los k elementos más pequeños del BST.
// print_k_smallest_elements

// Imprime los k elementos más grandes del BST.
// print_k_largest_elements

// Encuentra el k-ésimo elemento más pequeño del BST.
// find_kth_smallest

// Encuentra el k-ésimo elemento más grande del BST.
// find_kth_largest

// Calcula la suma de todos los caminos desde la raíz hasta las hojas.
// sum_of_all_paths

// Cuenta cuántos nodos tienen valores dentro de un rango dado.
// count_nodes_in_range

// Encuentra el subárbol cuya suma de nodos es más cercana a k.
// find_subtree_sum_closest_to_k

// Calcula el diámetro del árbol (la distancia más larga entre dos nodos).
// diameter_of_bst

// Lista todos los caminos desde la raíz hasta las hojas.
// list_all_paths

// Devuelve una lista de todos los ancestros de un nodo específico.
// find_all_ancestors

// Verifica si un árbol binario cumple las propiedades de BST.
// check_bst_property

// Encuentra todos los nodos hoja del BST.
// find_all_leaves

// Calcula el promedio de los valores de los nodos en cada nivel.
// find_average_of_levels

// Verifica si un árbol binario es un subárbol de otro.
// check_if_subtree

// Encuentra el ancestro común más cercano entre múltiples nodos.
// find_closest_common_ancestor

// Genera la imagen especular del BST.
// mirror_image

// Cuenta los subárboles que tienen todos sus nodos con el mismo valor.
// count_unival_subtrees

// Encuentra el centro del árbol (nodo o arista más equilibrado para dividir el árbol).
// tree_center

// Elimina los nodos con un solo hijo.
// remove_half_nodes

// Convierte el BST en un árbol sesgado (nodos en una sola dirección).
// convert_to_skewed_tree

// Encuentra el valor más grande en cada nivel del BST.
// largest_value_at_each_level

// Verifica si un arreglo dado podría ser el recorrido postorden de un BST.
// validate_postorder

// Verifica si un arreglo dado podría ser el recorrido preorden de un BST.
// validate_preorder

// Encuentra el segundo valor más grande en el BST.
// find_second_largest

// Verifica si el árbol está balanceado en términos de peso (suma de valores en los subárboles).
// check_if_weight_balanced

// Encuentra todos los nodos a una distancia k de un nodo objetivo.
// find_all_nodes_at_distance_k

// Encuentra los k valores más cercanos a un número dado.
// find_k_closest_values

// Invierte un subárbol específico del BST.
// invert_subtree

// Encuentra nodos en la misma profundidad que un nodo dado.
// find_nodes_at_same_depth

// Convierte el BST en una lista enlazada en inorden.
// flatten_to_linked_list

// Verifica que la estructura del árbol sea válida (sin ciclos ni errores de punteros).
// validate_tree_structure

// Encuentra todos los caminos cuya multiplicación de valores sea k.
// find_paths_with_product_k

#endif