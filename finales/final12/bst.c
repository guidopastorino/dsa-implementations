#include "bst.h"

BSTSet crearBST(int dato){
    BSTSet nodo = (BSTSet)malloc(sizeof(bstNodo));
    assert(nodo != NULL);
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

BSTSet agregarBST(BSTSet raiz, int dato){
    if(raiz == NULL) return crearBST(dato); // Creamos el nuevo nodo a ser insertado
    if(dato < raiz->dato){
        raiz->izq = agregarBST(raiz->izq, dato);
    } else if(dato > raiz->dato){
        raiz->der = agregarBST(raiz->der, dato);
    }
    // Evitamos agregar valores duplicados y retornamos
    return raiz;
}

/// @brief Cuenta cuantos nodos existen en el arbol
/// @param raiz Raiz del arbol binario
/// @return Cantidad de nodos que existen en el arbol
static int nodes_count(BSTSet raiz){
    if(raiz == NULL) return 0;
    return 1 + nodes_count(raiz->izq) + nodes_count(raiz->der);
}

void imprimeBST(BSTSet raiz){
    if(raiz == NULL) return;
    int count = nodes_count(raiz);
    // queue de tipo struct bstNodo_** para almacenar datos de tipo struct bstNodo_*;
    BSTSet* queue = (BSTSet*)calloc(count, sizeof(BSTSet));
    assert(queue != NULL);
    int front = 0, rear = 0;
    queue[rear++] = raiz;
    while(front != rear){
        BSTSet nodo = queue[front++]; // desencolamos
        printf("%d ", nodo->dato);
        if(nodo->izq) queue[rear++] = nodo->izq; // encolamos (si existe) el hijo izquierdo
        if(nodo->der) queue[rear++] = nodo->der; // encolamos (si existe) el hijo derecho
    }
    printf("\n");
    free(queue); // liberamos la queue
}

/// @brief Verifica si existe 'nodo' en el arbol 'raiz2'
/// @param nodo Nodo del arbol binario
/// @param raiz2 Arbol binario que va a ser recorrido para verificar si existe o no el nodo
/// @return 1 si existe el nodo, 0 en caso contrario
static int existeNodoBSTAux(BSTSet nodo, BSTSet raiz2){
    if(nodo == NULL || raiz2 == NULL) return 0;
    // Si el nodo existe, retornamos 1
    if(nodo->dato == raiz2->dato) return 1;
    if(nodo->dato < raiz2->dato){
        return existeNodoBSTAux(nodo, raiz2->izq); // Verificamos si existe en el subarbol izquierdo de raiz2
    }
    return existeNodoBSTAux(nodo, raiz2->der); // Verificamos si existe en el subarbol derecho de raiz2
}

/// @brief Verifica si existe el nodo del primer arbol (raiz1) y si existe, lo agrega al arbol de intersección 
/// @param nodo Nodo del arbol raiz1 el cual se verificará si existe o no
/// @param raiz2 Arbol para verificar si 'nodo' se encuentra en él o no
/// @param bstSetInter Puntero a puntero del arbol de interseccion, el cual, se le agregarán los nodos que comparten los dos árboles
static void interseccionBSTAux(BSTSet nodo, BSTSet raiz2, BSTSet* bstSetInter){
    if(nodo == NULL || raiz2 == NULL) return;
    if(existeNodoBSTAux(nodo, raiz2)){
        printf("Agregando dato %d al arbol interseccion\n", nodo->dato);
        *bstSetInter = agregarBST(*bstSetInter, nodo->dato);
    }
    interseccionBSTAux(nodo->izq, raiz2, bstSetInter);
    interseccionBSTAux(nodo->der, raiz2, bstSetInter);
}

BSTSet interseccionBST(BSTSet raiz1, BSTSet raiz2){
    // Si uno de los dos árboles es nulo (no tiene nodos), su intersección es vacía
    if(raiz1 == NULL || raiz2 == NULL) return NULL;

    BSTSet bstSetInter = NULL;
    
    interseccionBSTAux(raiz1, raiz2, &bstSetInter);

    return bstSetInter;
}

/// @brief La diferencia de valor absoluto sea más grande
/// @param raiz 
/// @param k 
/// @param nodoMayorMasLejano 
/// @return 
static int esLejanoMayor(BSTSet raiz, int k, BSTSet nodoMayorMasLejano){
    return abs(raiz->dato) > k && raiz->dato > nodoMayorMasLejano->dato;
}

/// @brief Verifica si en el arbol existe uno mayor (reasigna el valor al nodo nodoMayorMasLejano
/// @param raiz Raíz del árbol
/// @param k Entero el cual se verifica si x nodo cumple la condicion
/// @param nodoMayorMasLejano Puntero a puntero del nodo que sirve para almacenar (mientras se hace recursión sobre el arbol) el nodo que verifica la condicion
static void existeLejanoBST(BSTSet raiz, int k, BSTSet* nodoMayorMasLejano){
    if(raiz == NULL) return;
    if(esLejanoMayor(raiz, k, *nodoMayorMasLejano)){
        (*nodoMayorMasLejano)->dato = raiz->dato;
    }
    existeLejanoBST(raiz->izq, k, nodoMayorMasLejano);
    existeLejanoBST(raiz->der, k, nodoMayorMasLejano);
}

BSTSet lejanoBST(BSTSet raiz, int k){
    // si el árbol es nulo, no existe el elemento
    if(raiz == NULL) return NULL;

    // Variable que nos ayudará a almacenar el nodo mayor más lejano en cada recursión
    // Preservaremos este nodo en cada recorrido, actualizandolo en base de que si otro nodo cumple la condición y si es mayor a este
    BSTSet nodoMayorMasLejano = crearBST(0);

    // Recorremos el arbol, verificando si cada nodo cumple o no la condicion
    existeLejanoBST(raiz, k, &nodoMayorMasLejano);

    return nodoMayorMasLejano;
}

void destruirBST(BSTSet raiz){
    if(raiz != NULL){
        destruirBST(raiz->izq);
        destruirBST(raiz->der);

        free(raiz);
    }
}