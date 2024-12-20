#include "BSCT.h"

// función auxiliar
static void inorder(BSCT *tree, VisitorFuncInt visit, void *extra_data, int index){
  if(index >= tree->size) return;
  inorder(tree, visit, extra_data, 2 * index + 1); // visitamos el subárbol izquierdo
  visit(tree->arr[index], extra_data);
  inorder(tree, visit, extra_data, 2 * index + 2); // visitamos el subárbol derecho
}

void bsct_foreach(BSCT *tree, VisitorFuncInt visit, void *extra_data){
  inorder(tree, visit, extra_data, 0);
}

static int compare(int* a, int* b){
  return *(int*)a - *(int*)b;
}

BSCT* to_bsctree(int tree[]){
  int n = sizeof(tree) / sizeof(tree[0]);
  BSCT* bsct_tree = (BSCT*)malloc(sizeof(BSCT));
  assert(bsct_tree != NULL);
  bsct_tree->arr = (int*)calloc(n, sizeof(int));
  assert(bsct_tree->arr != NULL);
  bsct_tree->size = 0;
  bsct_tree->capacity = n;

  // ordenamos el arreglo original
  qsort(tree, n, sizeof(int), compare);

  // Copiar el arreglo ordenado al árbol
  for(int i = 0; i<n; i++)
    bsct_tree->arr[i] = tree[i];

  return bsct_tree;
}

void cambio_greedy(int C){
  int monedas[] = {20, 10, 5, 1};
  int cantidad_monedas[4] = {0};
  
  for(int i = 0; i<4; i++){
    cantidad_monedas[i] = C / monedas[i];
    C %= monedas[i];
  }

  // Imprimir el resultado
  printf("Número mínimo de monedas:\n");
  for (int i = 0; i < 4; i++) {
    if (cantidad_monedas[i] > 0) {
      printf("Monedas de %d ctvos: %d\n", monedas[i], cantidad_monedas[i]);
    }
  }
}