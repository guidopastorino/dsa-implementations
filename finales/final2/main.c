#include "bst.h"
#include "heap.h"

// Función para comparar dos usuarios
int comparar_usuarios(Usuario usuario1, Usuario usuario2){
  if(usuario1.esPremium && !usuario2.esPremium) return 1;
  if(!usuario1.esPremium && usuario2.esPremium) return -1;
  if(usuario1.esPremium && usuario2.esPremium) {
    return usuario1.tiempoDeMembresia - usuario2.tiempoDeMembresia;
  }
  return usuario1.tiempoEnEspera - usuario2.tiempoEnEspera;
}

// Función para imprimir un usuario
void imprimir_usuario(Usuario usuario){
  printf("(DNI: %d, Tiempo en espera: %d, Es premium: %s, Tiempo de membresía: %d)\n",
  usuario.dni, usuario.tiempoEnEspera, usuario.esPremium ? "SI" : "NO", usuario.tiempoDeMembresia);
}

// Usuarios
Usuario usuarios[10] = {
  // dni, tiempo de espera, es premium, tiempo de membresia

  {12345678, 120, 1, 31536000}, // 1 año de membresía
  {23456789, 300, 0, 0},
  {34567890, 60, 1, 15768000},  // 6 meses de membresía
  {45678901, 0, 0, 0},
  {56789012, 450, 1, 63115200}, // 2 años de membresía
  {67890123, 10, 0, 0},
  {78901234, 180, 1, 94608000}, // 3 años de membresía
  {89012345, 0, 0, 0},
  {90123456, 600, 1, 126144000}, // 4 años de membresía
  {12345001, 50, 0, 0}
};

int cantUsuarios = sizeof(usuarios) / sizeof(usuarios[0]);

int main(){
  BSTNode* root = NULL;

  for(int i = 0; i<cantUsuarios; i++){
    root = bst_insert(root, usuarios[i], comparar_usuarios);
  }

  printf("Usuarios en el BST: \n");
  bst_bfs(root, imprimir_usuario); 

  bst_destroy(root);

  puts("");
  puts("");
  puts("");
  // ==========================
  MaxHeap heap;
  heap_init(&heap);

  for(int i = 0; i<cantUsuarios; i++){
    heap_insert(&heap, usuarios[i], comparar_usuarios);
  }

  printf("Usuarios del Heap: \n");
  heap_display(heap, imprimir_usuario);

  puts("");
  puts("");

  printf("Mostrando elementos con máxima prioridad en el Max Heap: \n");
  for(int i = 0; i<cantUsuarios; i++){
    imprimir_usuario(heap_extract_max(&heap, comparar_usuarios));
  }

  puts("");

  return 0;
}