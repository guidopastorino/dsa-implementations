#include "hashtable.h"

int mod(int x){
  return x % 9;
}

int main(){
  HashTable* ht = ht_create();
  int arr[] = {9, 18, 12, 3, 14, 4, 21}; // Orden ajustado

  for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){
    ht_insert(ht, arr[i]);
  }

  ht_display(ht);

  printf("4 está en la tabla? %s\n", ht_search(ht, 4) != -1 ? "SI" : "NO");
  printf("404 está en la tabla? %s\n", ht_search(ht, 404) != -1 ? "SI" : "NO");

  return 0;
}