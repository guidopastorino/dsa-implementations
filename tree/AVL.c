#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(a, b)(a > b ? a : b)

typedef struct _AVLNode {
  int data;
  struct _AVLNode* left;
  struct _AVLNode* right;
  int height;
} AVLNode;

AVLNode* create_node(int data){
  AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
  assert(node != NULL);
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

int height(AVLNode* root){
  if(root == NULL) return 0;
  return root->height;
}

void update_height(AVLNode* root){
  if(root != NULL){
    root->height = MAX(height(root->left), height(root->right)) + 1;
  }
}

int balance_factor(AVLNode* root){
  if(root == NULL) return 0;
  return height(root->left) - height(root->right);
}


AVLNode* rotate_left(AVLNode* x){
  AVLNode* y = x->right;
  AVLNode* T2 = y->left;
  y->left = x;
  x->right = T2;
  update_height(x);
  update_height(y);
  return y;
}

AVLNode* rotate_right(AVLNode* y){
  AVLNode* x = y->left;
  AVLNode* T2 = x->right;
  x->right = y;
  y->left = T2;
  update_height(y);
  update_height(x);
  return x;
}

AVLNode* balance_tree(AVLNode* root){
  int balance = balance_factor(root);

  if(balance > 1){
    if(balance_factor(root->left) < 0){
      root->left = rotate_left(root->left);
    }
    return rotate_right(root);
  }

  if(balance < -1){
    if(balance_factor(root->right) > 0){
      root->right = rotate_right(root->right);
    }
    return rotate_left(root);
  }

  return root;
}

AVLNode* insert(AVLNode* root, int data){
  if(root == NULL) return create_node(data);
  if(data < root->data){
    root->left = insert(root->left, data);
  } else if(data > root->data){
    root->right = insert(root->right, data);
  } else {
    return root;
  }
  update_height(root);
  return balance_tree(root);
}

AVLNode* find_min(AVLNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL)
    root = root->left;
  return root;
}

AVLNode* delete(AVLNode* root, int data){
  if(root == NULL) return root;
  if(data < root->data){
    root->left = delete(root->left, data);
  } else if(data > root->data){
    root->right = delete(root->right, data);
  } else {
    if(root->left == NULL || root->right == NULL){
      // Caso: Nodo con un solo hijo o ninguno.

      AVLNode* temp = root->left ? root->left : root->right; 
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
    } else {
      AVLNode* temp = find_min(root->right);
      root->data = temp->data;
      root->right = delete(root->right, temp->data);
    }
  }
  if(root == NULL) return NULL;
  update_height(root);
  return balance_tree(root);
}

int nodes_count(AVLNode* root){
  if(root == NULL) return 0;
  return 1 + nodes_count(root->left) + nodes_count(root->right);
}

void bfs(AVLNode* root){
  if(root == NULL) return;
  int count = nodes_count(root);
  AVLNode** queue = (AVLNode**)malloc(sizeof(AVLNode*) * count);
  assert(queue != NULL);
  int front = 0, rear = 0;
  queue[rear++] = root;
  while(front < rear){
    AVLNode* node = queue[front++];
    printf("%d ", node->data);
    if(node->left)
      queue[rear++] = node->left;
    if(node->right)
      queue[rear++] = node->right;
  }
  free(queue);
  printf("\n");
}

void free_avl(AVLNode* root){
  if(root != NULL){
    free_avl(root->left);
    free_avl(root->right);
    free(root);
  }
}

int main() {
  AVLNode* root = NULL;

  // Insertamos algunos valores en el árbol
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 5);
  root = insert(root, 4);
  root = insert(root, 6);
  root = insert(root, 15);

  printf("Árbol después de las inserciones (BFS):\n");
  bfs(root); // Debe mostrar un árbol balanceado.

  // Probamos eliminar un nodo con dos hijos
  printf("Eliminando nodo 10...\n");
  root = delete(root, 10);

  printf("Árbol después de eliminar 10 (BFS):\n");
  bfs(root); // Verificamos que el árbol siga balanceado.

  // Probamos eliminar un nodo hoja
  printf("Eliminando nodo 4...\n");
  root = delete(root, 4);

  printf("Árbol después de eliminar 4 (BFS):\n");
  bfs(root);

  // Probamos eliminar un nodo con un solo hijo
  printf("Eliminando nodo 15...\n");
  root = delete(root, 15);

  printf("Árbol después de eliminar 15 (BFS):\n");
  bfs(root);

  // Liberamos la memoria del árbol
  free_avl(root);

  return 0;
}