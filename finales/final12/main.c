#include "bst.h"

int main(){
    BSTSet bstSetTree = NULL;

    bstSetTree = agregarBST(bstSetTree, 10);
    bstSetTree = agregarBST(bstSetTree, 40);
    bstSetTree = agregarBST(bstSetTree, 20);
    bstSetTree = agregarBST(bstSetTree, 15);
    bstSetTree = agregarBST(bstSetTree, 35);

    puts("Arbol actual luego de insertar los nodos:\n");
    imprimeBST(bstSetTree);
    puts("\n");

    // creamos un segundo arbol
    BSTSet bstSetTreeAux = NULL;
    // insertamos dos elementos en comun con 'bstSetTree'
    bstSetTreeAux = agregarBST(bstSetTreeAux, 10);
    bstSetTreeAux = agregarBST(bstSetTreeAux, 20);
    bstSetTreeAux = agregarBST(bstSetTreeAux, 40);
    bstSetTreeAux = agregarBST(bstSetTreeAux, 22); // este elemento no existe en el 'bstSetTree'

    puts("Arbol auxiliar\n");
    imprimeBST(bstSetTreeAux);
    puts("\n");

    puts("Árbol con la intersección de dos árboles:\n");
    BSTSet arbolInterseccion = interseccionBST(bstSetTree, bstSetTreeAux);
    imprimeBST(arbolInterseccion);
    puts("\n");

    int k = 5;
    BSTSet nodoMasLejanoK = lejanoBST(bstSetTree, k);

    if(nodoMasLejanoK != 0){
        printf("Nodo mayor más lejano a %d: %d\n", k, nodoMasLejanoK->dato);
    } else {
        printf("No es posible encontrar un nodo mayor más lejano a %d\n", k);
    }

    destruirBST(bstSetTree);
    destruirBST(bstSetTreeAux);
    destruirBST(arbolInterseccion);
    destruirBST(nodoMasLejanoK);

    return 0;
}