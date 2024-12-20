#include "hashtable.h"

typedef struct {
  int id;
  char* name;
} User;

// Función para copiar datos de un usuario y crear un nuevo usuario
void* copy_user(void* data) {
  User* original = (User*)data;
  User* copy = (User*)malloc(sizeof(User));
  copy->id = original->id;
  copy->name = (char*)malloc(sizeof(char) * (strlen(original->name) + 1));
  strcpy(copy->name, original->name);
  return copy;
}

// Función para comparar dos usuarios
int compare_user(void* data1, void* data2) {
  User* user1 = (User*)data1;
  User* user2 = (User*)data2;
  return strcmp(user1->name, user2->name);
}

// Función para imprimir un usuario
void print_user(void* data) {
  User* user = (User*)data;
  printf("(%d, %s) ", user->id, user->name);
}

// Función para destruir un usuario
void destroy_user(void* data) {
  User* user = (User*)data;
  free(user->name);
  free(user);
}

// Función de hash para usuarios
unsigned int hash_user(void* data, int size) {
  User* user = (User*)data;
  unsigned int hash_value = 0;
  
  // Hash del id
  hash_value = (hash_value * 31) + user->id;

  // Hash del name (cadena de caracteres)
  char* str = user->name;
  while (*str) {
    hash_value = (hash_value * 31) + (unsigned int)(*str);
    str++;
  }

  return hash_value % size;
}

int main() {
  // Crear la tabla hash
  HashTable* ht = ht_create(hash_user, copy_user, compare_user, print_user, destroy_user);

  // Array dinámico con 20 usuarios
  char* names[] = {
    "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank",
    "Ivy", "Jack", "Kate", "Leo", "Mona", "Nick", "Olivia", "Paul",
    "Quincy", "Rose", "Steve", "Tina"
  };
  int count = sizeof(names) / sizeof(names[0]);
  User users[count];

  // Asignar dinámicamente los nombres y insertar usuarios en la tabla hash
  for (int i = 0; i < count; i++) {
    users[i].id = i + 1;
    users[i].name = (char*)malloc(sizeof(char) * (strlen(names[i]) + 1));
    strcpy(users[i].name, names[i]);
    User* user = &users[i];
    ht_insert(ht, user);  // Insertamos el usuario en la tabla hash
  }

  // Mostrar el contenido de la tabla hash
  printf("Contenido de la tabla hash:\n");
  ht_display(ht);

  // Buscar un usuario en la tabla hash
  if (ht_search(ht, &users[7])) {
    printf("\nUsuario encontrado: (%d, %s)\n", users[7].id, users[7].name);
  } else {
    printf("\nUsuario no encontrado: (%d, %s)\n", users[7].id, users[7].name);
  }

  // Eliminar un usuario de la tabla hash
  ht_delete(ht, &users[7]);
  printf("\nDespués de eliminar a %s:\n", users[7].name);
  ht_display(ht);

  // Liberar los nombres del array de usuarios
  for (int i = 0; i < count; i++) {
    free(users[i].name);
  }

  // Destruir la tabla hash y liberar memoria
  ht_destroy(ht);

  return 0;
}