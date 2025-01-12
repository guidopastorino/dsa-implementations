#include "bst.h"

BSTNode* createNode(int data){
  BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
  assert(node != NULL);
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

BSTNode* insert(BSTNode* root, int data){
  if(root == NULL) return createNode(data);
  if(data < root->data){
    root->left = insert(root->left, data);
  } else if(data > root->data){
    root->right = insert(root->right, data);
  }
  return root;
}

int search(BSTNode* root, int data){
  if(root == NULL) return 0;
  if(data == root->data){
    return 1;
  }
  if(data < root->data){
    return search(root->left, data);
  }
  return search(root->right, data);
}

static BSTNode* find_min(BSTNode* root){
  if(root == NULL) return NULL;
  while(root->left != NULL){
    root = root->left;
  }
  return root;
}

BSTNode* delete(BSTNode* root, int data){
  if(root == NULL) return NULL;
  if(data < root->data){
    root->left = delete(root->left, data);
  } else if(data > root->data){
    root->right = delete(root->right, data);
  } else {
    if(root->left == NULL || root->right == NULL){
      BSTNode* temp = root->left ? root->left : root->right;
      if(!temp){
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      free(temp);
    } else {
      BSTNode* temp = find_min(root->right);
      root->data = temp->data;
      root->right = delete(root->right, temp->data);
    }
  }
  return root;
}

int count_leaf_nodes(BSTNode* root){
  if(root == NULL) return 0;

  if(root->left == NULL && root->right == NULL) return 1;

  return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

int count_node_ancestors(BSTNode* root, int target){
  if(root == NULL) return 0;
  if(root->data == target) return 0;
  if(target < root->data){
    int leftCount = count_node_ancestors(root->left, target);
    if(leftCount != -1) return leftCount + 1;
  }
  if(target > root->data){
    int rightCount = count_node_ancestors(root->right, target);
    if(rightCount != -1) return rightCount + 1;
  }
  return -1; // Nodo no encontrado
}

// types


void inorder(BSTNode* root){
  if(root != NULL){
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }  
}

void destroy_tree(BSTNode* root){
  if(root != NULL){
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
  }
}

static void inorder_intersection(BSTNode* root1, BSTNode* root2, BSTNode** result){
  if(root1 == NULL) return;

  inorder_intersection(root1->left, root2, result);

  if(search(root2, root1->data)){
    *result = insert(*result, root1->data);
  }

  inorder_intersection(root1->right, root2, result);
}

BSTNode* bst_intersection(BSTNode* root1, BSTNode* root2){
  BSTNode* result = NULL;
  inorder_intersection(root1, root2, &result);
  return result;
}

static void inorder_add_to_union(BSTNode* root, BSTNode** result){
  if(root == NULL) return;
  inorder_add_to_union(root->left, result);
  *result = insert(*result, root->data);
  inorder_add_to_union(root->right, result);
}

BSTNode* bst_union(BSTNode* root1, BSTNode* root2){
  BSTNode* result = NULL;
  inorder_add_to_union(root1, &result);
  inorder_add_to_union(root2, &result);
  return result;
}

void inorder_intersection(BSTNode* root1, BSTNode* root2, BSTNode** result){
  if(root1 == NULL) return;
  inorder_intersection(root1->left, root2, result);
  if(!search(root2, root1->data)){
    *result = insert(*result, root1->data);
  }
  inorder_intersection(root1->right, root2, result);
}

BSTNode* bst_difference(BSTNode* root1, BSTNode* root2){
  BSTNode* result = NULL;
  inorder_intersection(root1, root2, &result);
  return result;
}

BSTNode* find_max(BSTNode* root){
  return NULL;
}

static void kth_smallest_aux(BSTNode* root, int* k, BSTNode** result){
  if(!root || *result) return;

  kth_smallest_aux(root->left, k, result);

  (*k)--;
  if(*k == 0){
    *result = root;
    return;
  }

  kth_smallest_aux(root->right, k, result);
}

BSTNode* kth_smallest(BSTNode* root, int k){
  BSTNode* result = NULL;
  kth_smallest_aux(root, &k, &result);
  return result;
}

static void kth_largest_aux(BSTNode* root, int* k, BSTNode** result){
  if(!root || *result) return;

  kth_largest_aux(root->right, k, result);

  (*k)--;
  if(*k == 0){
    *result = root;
    return;
  }

  kth_largest_aux(root->left, k, result);
}

BSTNode* kth_largest(BSTNode* root, int k){
  BSTNode* result = NULL;
  kth_largest_aux(root, &k, &result);
  return result;
}

BSTNode* is_identical(BSTNode* root1, BSTNode* root2){
  if(root1 == NULL && root2 == NULL) return 1;

  if(root1 == NULL || root2 == NULL || root1->data != root2->data) return 0;

  return is_identical(root1->left, root2->left) && is_identical(root1->right, root2->right);
}

int is_subtree(BSTNode* root1, BSTNode* root2){
  if (!root2) return 1; // Un árbol vacío siempre es subárbol
  if (!root1) return 0; // root2 no puede ser subárbol de un árbol vacío

  if(is_identical(root1, root2)) return 1;

  return is_subtree(root1->left, root2) || is_subtree(root1->right, root2);
}

BSTNode* lowest_common_ancestor(BSTNode* root, BSTNode* node1, BSTNode* node2){
  if(!root) return NULL;

  // si ambos nodos estan en el lado izquierdo
  if(node1->data < root->data && node2->data < root->data){
    return lowest_common_ancestor(root->left, node1, node2);
  }

  // si ambos nodos estan en el lado derecho
  if(node1->data > root->data && node2->data > root->data){
    return lowest_common_ancestor(root->right, node1, node2);
  }
  
  // Si los nodos están en lados opuestos o uno de ellos es el actual, este es el LCA
  return root;
}

int range_sum(BSTNode* root, int low, int high){
  if(!root) return 0;
  int sum = 0;
  if(root->data >= low && root->data <= high){
    sum += root->data;
  }
  if(root->data > low){
    sum += range_sum(root->left, low, high);
  }
  if(root->data < high){
    sum += range_sum(root->right, low, high);
  }
  return sum;
}

int is_bst_aux(BSTNode* root, int min, int max){
  if(!root) return 1;

  // Verificar si el valor del nodo actual está fuera de los límites
  if(root->data <= min || root->data >= max){
    return 0;
  }

  return is_bst_aux(root->left, min, root->data) && is_bst_aux(root->right, root->data, max);
}

int is_bst(BSTNode* root){
  return is_bst_aux(root, INT_MIN, INT_MAX);
}

void mirror(BSTNode* root){
  if(!root) return;

  BSTNode* temp = root->left;
  root->left = root->right;
  root->right = temp;

  mirror(root->left);
  mirror(root->right);
}


int path_sum(BSTNode* root, int sum){
  if(!root) return 0;

  int remainingSum = 0;

  if(!root->left || !root->right){
    return remainingSum == 0;
  }

  return path_sum(root->left, remainingSum) || path_sum(root->right, remainingSum);
}