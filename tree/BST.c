#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _BSTNode {
  int data;
  struct _BSTNode* left;
  struct _BSTNode* right;
} BSTNode;

BSTNode* create_node(int data){
  BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
  assert(node != NULL);
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

int count_nodes(BSTNode* root){
  if(root == NULL) return 0;
  return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int height(BSTNode* root){
  if(root == NULL) return 0;
  int left_height = height(root->left);
  int right_height = height(root->right);
  return 1 + (left_height > right_height ? left_height : right_height);
}

BSTNode* insert(BSTNode* root, int data){
  if(root == NULL) return create_node(data);
  if(data < root->data){
    root->left = insert(root->left, data);
  } else if(data > root->data){
    root->right = insert(root->right, data);
  }
  return root;
}

int search(BSTNode* root, int data){
  if(root == NULL) return 0;
  if(data == root->data) return 1;
  if(data < root->data)
    return search(root->left, data);
  else
    return search(root->right, data);
}

BSTNode* find_min(BSTNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL)
    root = root->left;
  return root;
}

BSTNode* delete(BSTNode* root, int data){
  if(root == NULL) return root;
  if(data < root->data){
    root->left = delete(root->left, data);
  } else if(data > root->data){
    root->right = delete(root->right, data);
  } else {
    if(root->left == NULL || root->right == NULL) { 
      // Caso: Nodo con un solo hijo o ninguno.
      BSTNode* temp = root->left ? root->left : root->right; 
      // Si el hijo izquierdo no es NULL, asignamos `temp` a `root->left`.
      // Si no, asignamos `temp` al hijo derecho (`root->right`).

      if(temp == NULL) { 
        // Si no hay hijos (nodo hoja), simplemente eliminamos el nodo.
        temp = root; // Guardamos el nodo actual en `temp` para liberarlo después.
        root = NULL; // Actualizamos `root` para indicar que este nodo se eliminó.
      } else { 
        // Si hay un hijo, copiamos los datos del hijo en el nodo actual (`root`).
        *root = *temp; 
        // Esto evita tener que modificar demasiados punteros. Básicamente,
        // sobrescribimos los datos y punteros del nodo actual con los del hijo.
      }

      free(temp); 
      // Finalmente, liberamos la memoria del nodo original o del nodo hijo
      // que fue reemplazado.
    } else {
      // Nodo con 2 hijos 
      // Sucesor inorder más pequeño del subarbol derecho
      BSTNode* temp = find_min(root->right);
      root->data = temp->data;
      root->right = delete(root->right, temp->data);
    }
  }
  return root;
}

void inorder(BSTNode* root){
  if(root != NULL){
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
}

void bfs(BSTNode* root){
  if(root == NULL) return;
  int count = count_nodes(root);
  BSTNode** queue = (BSTNode**)malloc(sizeof(BSTNode*) * count);
  assert(queue != NULL);
  int front = 0, rear = 0;
  queue[rear++] = root;
  while(front < rear){
    BSTNode* node = queue[front++];
    printf("%d ", node->data);
    if(node->left)
      queue[rear++] = node->left;
    if(node->right)
      queue[rear++] = node->right;
  }
  free(queue);
  printf("\n");
}

void free_tree(BSTNode* root) {
  if (root == NULL) return; // Caso base: si el árbol está vacío, no hacer nada.
  
  // Liberamos recursivamente los subárboles izquierdo y derecho
  free_tree(root->left);
  free_tree(root->right);

  // Liberamos el nodo actual
  free(root);
}

// --------------------------
// Cantidad de hojas
int count_leaf_nodes(BSTNode* root){
  if(root == NULL) return 0;
  if(root->left == NULL && root->right == NULL) return 1;
  return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

// Imprimir ancestros de un nodo
// target es el nodo que queremos imprimir sus ancestros
int print_ancestors(BSTNode* root, int target){
  if(root == NULL) return 0;
  if(root->data == target) return 1;

  if(print_ancestors(root->left, target) || print_ancestors(root->right, target)){
    printf("%d ", root->data);
    return 1;
  }

  return 0;
}

// aux func
void print_ancestors_helper(BSTNode* root, int target) {
  printf("Ancestros del nodo %d: ", target);
  if (!print_ancestors(root, target)) {
    printf("El nodo %d no está en el árbol.\n", target);
  } else {
    printf("\n");
  }
}

// Checks if the tree is Full Binary Tree
int is_full(BSTNode* root){
  if(root == NULL) return 1;
  if((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL)) return 0;
  return is_full(root->left) && is_full(root->right);
}

// Checks if the tree is Complete Binary Tree
int is_complete_helper(BSTNode* root, int index, int count){
  if(root == NULL) return 1;
  if(index >= count) return 0;
  return is_complete_helper(root->left, 2 * index + 1, count) && is_complete_helper(root->right, 2 * index + 2, count);
}

int is_complete(BSTNode* root){
  if(root == NULL) return 1;
  int index = 0;
  int count = count_nodes(root);
  return is_complete_helper(root, index, count);
}

// Checks if the tree is Perfect Binary Tree
int is_perfect_binary_tree(BSTNode* root) {
  int h = height(root);
  int total_nodes = (1 << h) - 1; // Fórmula: 2^h - 1
  return count_nodes(root) == total_nodes;
}

// Checks if the tree is Balanced Binary Tree
int is_balanced_binary_tree(BSTNode* root) {
  if (root == NULL) return 1;

  int left_height = height(root->left);
  int right_height = height(root->right);

  if (abs(left_height - right_height) > 1) return 0;

  return is_balanced_binary_tree(root->left) && is_balanced_binary_tree(root->right);
}

// Checks if the tree Degenerate Binary Tree
int is_degenerate_binary_tree(BSTNode* root) {
  if (root == NULL) return 1;
  if (root->left != NULL && root->right != NULL) return 0; // Tiene ambos hijos
  return is_degenerate_binary_tree(root->left) && is_degenerate_binary_tree(root->right); // Ambas ramas deben ser degeneradas
}
// --------------------------


int main() {
  // Árbol genérico para pruebas
  printf("=== Árbol Binario Genérico ===\n");
  BSTNode* root = NULL;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 70);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 60);
  root = insert(root, 80);

  printf("Árbol en inorden (ordenado):\n");
  inorder(root);
  printf("\n");

  printf("Recorrido BFS (nivel por nivel):\n");
  bfs(root);

  printf("Número de hojas en el árbol: %d\n", count_leaf_nodes(root));

  print_ancestors_helper(root, 60);
  print_ancestors_helper(root, 70);
  print_ancestors_helper(root, 50);
  print_ancestors_helper(root, 80);

  int search_val = 40;
  printf("¿El valor %d está en el árbol? %s\n", search_val, search(root, search_val) ? "Sí" : "No");

  printf("Eliminando el nodo 30.\n");
  root = delete(root, 30);
  printf("Árbol en inorden después de eliminar 30:\n");
  inorder(root);
  printf("\n");

  printf("Altura del árbol: %d\n", height(root));
  printf("Número de nodos en el árbol: %d\n", count_nodes(root));
  printf("¿Es un árbol completo? %s\n", is_complete(root) ? "Sí" : "No");
  printf("¿Es un árbol perfecto? %s\n", is_perfect_binary_tree(root) ? "Sí" : "No");
  printf("¿Es un árbol balanceado? %s\n", is_balanced_binary_tree(root) ? "Sí" : "No");
  printf("¿Es un árbol degenerado? %s\n", is_degenerate_binary_tree(root) ? "Sí" : "No");

  free_tree(root);
  printf("\n");

  // Árbol completo
  printf("=== Árbol Binario Completo ===\n");
  BSTNode* complete_tree = NULL;
  complete_tree = insert(complete_tree, 50);
  complete_tree = insert(complete_tree, 30);
  complete_tree = insert(complete_tree, 70);
  complete_tree = insert(complete_tree, 20);
  complete_tree = insert(complete_tree, 40);
  complete_tree = insert(complete_tree, 60);
  complete_tree = insert(complete_tree, 80);

  printf("¿Es un árbol completo? %s\n", is_complete(complete_tree) ? "Sí" : "No");
  free_tree(complete_tree);
  printf("\n");

  // Árbol degenerado (similar a una lista)
  printf("=== Árbol Binario Degenerado ===\n");
  BSTNode* degenerate_tree = NULL;
  degenerate_tree = insert(degenerate_tree, 10);
  degenerate_tree = insert(degenerate_tree, 20);
  degenerate_tree = insert(degenerate_tree, 30);
  degenerate_tree = insert(degenerate_tree, 40);
  degenerate_tree = insert(degenerate_tree, 50);

  printf("¿Es un árbol degenerado? %s\n", is_degenerate_binary_tree(degenerate_tree) ? "Sí" : "No");
  free_tree(degenerate_tree);
  printf("\n");

  // Árbol perfecto
  printf("=== Árbol Binario Perfecto ===\n");
  BSTNode* perfect_tree = NULL;
  perfect_tree = insert(perfect_tree, 50);
  perfect_tree = insert(perfect_tree, 30);
  perfect_tree = insert(perfect_tree, 70);
  perfect_tree = insert(perfect_tree, 20);
  perfect_tree = insert(perfect_tree, 40);
  perfect_tree = insert(perfect_tree, 60);
  perfect_tree = insert(perfect_tree, 80);

  printf("¿Es un árbol perfecto? %s\n", is_perfect_binary_tree(perfect_tree) ? "Sí" : "No");
  free_tree(perfect_tree);
  printf("\n");

  return 0;
}