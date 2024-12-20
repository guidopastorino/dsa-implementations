#include "avl.h"

AVLTree* avl_create_tree(Copy copy, Compare cmp, Print print, Destroy destr){
  AVLTree* avl = (AVLTree*)malloc(sizeof(AVLTree));
  assert(avl != NULL);
  avl->copy = copy;
  avl->cmp = cmp;
  avl->print = print;
  avl->destr = destr;
  avl->root = NULL;
  return avl;
}

/// @brief Crea un nodo para el árbol AVL, copiando el dato proporcionado.
/// @param data Puntero al dato que se almacenará en el nodo.
/// @param copy Función que copia el dato para asegurarse de que el árbol tenga su propia versión.
/// @return Un puntero al nodo AVL recién creado.
static AVLNode* avl_create_node(void* data, Copy copy){
  AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
  assert(node != NULL);
  node->data = copy(data);
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

/// @brief Obtiene la altura de un nodo en el árbol AVL.
/// @param root Puntero al nodo cuya altura se desea obtener.
/// @return La altura del nodo o 0 si el nodo es NULL.
static int height(AVLNode* root){
  if(root == NULL) return 0;
  return root->height;
}

/// @brief Calcula el factor de balance de un nodo en el árbol AVL.
/// @param root Puntero al nodo cuyo factor de balance se desea calcular.
/// @return La diferencia entre la altura del subárbol izquierdo y derecho del nodo.
static int balance_factor(AVLNode* root){
  if(root == NULL) return 0;
  return height(root->left) - height(root->right);
}

/// @brief Actualiza la altura de un nodo en el árbol AVL en base a las alturas de sus hijos.
/// @param root Puntero al nodo cuya altura se actualizará.
static void update_height(AVLNode* root){
  if(root != NULL){
    root->height = MAX(height(root->left), height(root->right)) + 1;
  }
}

/// @brief Realiza una rotación hacia la izquierda sobre un nodo en el árbol AVL.
/// @param x Puntero al nodo que será rotado hacia la izquierda.
/// @return Puntero al nuevo nodo raíz después de la rotación.
static AVLNode* avl_left_rotate(AVLNode* x){
  AVLNode* y = x->right;
  AVLNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  update_height(x);
  update_height(y);
  return y;
}

/// @brief Realiza una rotación hacia la derecha sobre un nodo en el árbol AVL.
/// @param y Puntero al nodo que será rotado hacia la derecha.
/// @return Puntero al nuevo nodo raíz después de la rotación.
static AVLNode* avl_right_rotate(AVLNode* y){
  AVLNode* x = y->left;
  AVLNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  update_height(y);
  update_height(x);
  return x;
}

/// @brief Balancea un subárbol AVL desde el nodo raíz proporcionado.
///        Realiza las rotaciones necesarias para mantener la propiedad AVL.
/// @param root Puntero al nodo raíz del subárbol a balancear.
/// @return Puntero a la nueva raíz del subárbol balanceado.
static AVLNode* balance_tree(AVLNode* root){
  if(root == NULL) return NULL;

  int balance = balance_factor(root);

  if(balance > 1){
    if(balance_factor(root->left) < 0){
      root->left = avl_left_rotate(root->left);
    }
    return avl_right_rotate(root);
  }

  if(balance < -1){
    if(balance_factor(root->right) > 0){
      root->right = avl_right_rotate(root->right);
    }
    return avl_left_rotate(root);
  }

  return root;
}

/// @brief Inserta un dato en un subárbol AVL de forma recursiva, balanceando el árbol cuando sea necesario.
/// @param root Puntero al nodo raíz del subárbol donde se insertará el dato.
/// @param data Puntero al dato que se desea insertar.
/// @param copy Función para copiar el dato.
/// @param cmp Función para comparar los datos.
/// @return Puntero a la nueva raíz del subárbol después de la inserción.
static AVLNode* avl_insert_aux(AVLNode* root, void* data, Copy copy, Compare cmp){
  if(root == NULL) return avl_create_node(data, copy);
  if(cmp(data, root->data) < 0){
    root->left = avl_insert_aux(root->left, data, copy, cmp);
  } else if(cmp(data, root->data) > 0){
    root->right = avl_insert_aux(root->right, data, copy, cmp);
  }
  update_height(root);
  return balance_tree(root);
}

void avl_insert(AVLTree* avl, void* data){
  avl->root = avl_insert_aux(avl->root, data, avl->copy, avl->cmp);
}

/// @brief Encuentra el nodo con el valor mínimo en un subárbol AVL.
/// @param root Puntero al nodo raíz del subárbol.
/// @return Puntero al nodo con el valor mínimo.
static AVLNode* find_min(AVLNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL)
    root = root->left;
  return root;
}

/// @brief Elimina un dato de un subárbol AVL de forma recursiva, balanceando el árbol cuando sea necesario.
/// @param root Puntero al nodo raíz del subárbol donde se eliminará el dato.
/// @param data Puntero al dato que se desea eliminar.
/// @param cmp Función para comparar los datos.
/// @param destr Función para liberar los datos almacenados.
/// @return Puntero a la nueva raíz del subárbol después de la eliminación.
static AVLNode* avl_delete_aux(AVLNode* root, void* data, Copy copy, Compare cmp, Destroy destr){
  if(root == NULL) return NULL;
  if(cmp(data, root->data) < 0){
    root->left = avl_delete_aux(root->left, data, copy, cmp, destr);
  } else if(cmp(data, root->data) > 0){
    root->right = avl_delete_aux(root->right, data, copy, cmp, destr);
  } else {
    if(root->left == NULL || root->right == NULL){
      AVLNode* temp = root->left ? root->left : root->right;
      if(!temp){
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      destr(temp->data);
      free(temp);
    } else {
      AVLNode* temp = find_min(root->right);
      destr(root->data);
      root->data = copy(temp->data);
      root->right = avl_delete_aux(root->right, temp->data, copy, cmp, destr);
    }
  }
  if(root == NULL) return NULL;
  update_height(root);
  return balance_tree(root);
}

void avl_delete(AVLTree* avl, void* data){
  avl->root = avl_delete_aux(avl->root, data, avl->copy, avl->cmp, avl->destr);
}

/// @brief Busca un dato en un subárbol AVL de manera recursiva.
/// @param root Puntero al nodo raíz del subárbol donde se realizará la búsqueda.
/// @param data Puntero al dato que se desea buscar.
/// @param cmp Función para comparar los datos almacenados en los nodos.
/// @return 1 si el dato está presente en el subárbol, 0 en caso contrario.
static int avl_search_aux(AVLNode* root, void* data, Compare cmp){
  if(root == NULL) return 0;
  if(cmp(data, root->data) == 0) return 1;
  if(cmp(data, root->data) < 0)
    return avl_search_aux(root->left, data, cmp);
  return avl_search_aux(root->right, data, cmp);
}

int avl_search(AVLTree* avl, void* data){
  return avl_search_aux(avl->root, data, avl->cmp);
}

/// @brief Realiza un recorrido en orden (DFS) sobre el subárbol AVL de manera recursiva.
/// @param root Puntero al nodo raíz del subárbol.
/// @param print Función para imprimir los datos almacenados en los nodos.
static void avl_dfs_aux(AVLNode* root, Print print){
  if(root != NULL){
    avl_dfs_aux(root->left, print);
    print(root->data);
    avl_dfs_aux(root->right, print);
  }
}

void avl_dfs(AVLTree* avl){
  avl_dfs_aux(avl->root, avl->print);
  printf("\n");
}

/// @brief Destruye el subárbol AVL de manera recursiva, liberando la memoria de cada nodo.
/// @param root Puntero al nodo raíz del subárbol.
/// @param destr Función para destruir los datos almacenados en los nodos.
static void avl_destroy_aux(AVLNode* root, Destroy destr){
  if(root != NULL){
    avl_destroy_aux(root->left, destr);
    avl_destroy_aux(root->right, destr);

    destr(root->data);
    free(root);
  }
}

void avl_destroy(AVLTree* avl){
  if(avl != NULL){
    avl_destroy_aux(avl->root, avl->destr);
    free(avl);
  }
}