#include "queue.h"

// El tipo de dato que se usará
typedef struct {
  char* name;
  int age; // Se usará la edad como prioridad
} Person;

// Crear una copia de la estructura `Person`
Person* create_person(void* data) {
  Person* originalPerson = (Person*)data;
  Person* person = (Person*)malloc(sizeof(Person));
  assert(person != NULL);
  person->name = (char*)malloc(sizeof(char) * (strlen(originalPerson->name) + 1));
  assert(person->name != NULL);
  strcpy(person->name, originalPerson->name);
  person->age = originalPerson->age;
  return person;
}

// Comparar dos personas por edad (prioridad)
int cmp(void* a, void* b) {
  int ageA = ((Person*)a)->age;
  int ageB = ((Person*)b)->age;
  return ageA - ageB; // Mayor edad = mayor prioridad
}

// Imprimir una persona
void print_person(void* data) {
  Person* p = (Person*)data;
  printf("(%s - %d) ", p->name, p->age);
}

// Liberar memoria de una persona
void destroy_person(void* data) {
  Person* p = (Person*)data;
  free(p->name);
  free(p);
}

// Ejemplo de uso
int main() {
  // Crear cola de prioridad
  PQueue* queue = pq_create();

  // Insertar elementos
  printf("\nInsertando elementos:\n");
  Person p1 = {"Alice", 30};
  Person p2 = {"Bob", 25};
  Person p3 = {"Charlie", 35};
  Person p4 = {"Diana", 28};
  Person p5 = {"Eve", 40};

  pq_insert(queue, &p1, (Copy)create_person, cmp);
  pq_insert(queue, &p2, (Copy)create_person, cmp);
  pq_insert(queue, &p3, (Copy)create_person, cmp);
  pq_insert(queue, &p4, (Copy)create_person, cmp);
  pq_insert(queue, &p5, (Copy)create_person, cmp);

  pq_display(queue, print_person);

  // Extraer el máximo
  printf("\n\nExtrayendo máximos:\n");
  for (int i = 0; i < 3; i++) {
    Person* max = (Person*)pq_extract_max(queue, cmp);
    if (max) {
      printf("Máximo extraído: ");
      print_person(max);
      printf("\n");
      destroy_person(max);
    }
  }
  pq_display(queue, print_person);

  // Eliminar un elemento específico
  printf("\n\nEliminando un elemento específico (Diana):\n");
  pq_delete(queue, &p4, cmp, destroy_person);
  pq_display(queue, print_person);

  // Insertar un nuevo elemento
  printf("\n\nInsertando un nuevo elemento (Frank - 33):\n");
  Person p6 = {"Frank", 33};
  pq_insert(queue, &p6, (Copy)create_person, cmp);
  pq_display(queue, print_person);

  // Liberar la cola de prioridad
  printf("\n\nDestruyendo la cola de prioridad:\n");
  pq_destroy(queue, destroy_person);
  printf("Cola destruida correctamente.\n");
}
