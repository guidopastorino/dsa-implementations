#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 10

typedef struct {
  int arr[MAX_SIZE];
  int front;
  int rear;
  int size;
} Deque;

void initialize_deque(Deque* deque) {
  deque->front = deque->rear = -1;
  deque->size = 0;
}

int is_empty(Deque* deque) {
  return deque->size == 0;
}

int is_full(Deque* deque) {
  return deque->size == MAX_SIZE;
}

// Inserta un elemento en el frente
void enqueue_front(Deque* deque, int data) {
  if (is_full(deque)) {
    printf("Deque is full. Cannot enqueue front\n");
    return;
  }
  if (is_empty(deque)) {
    deque->front = deque->rear = 0;
  } else {
    deque->front = (deque->front - 1 + MAX_SIZE) % MAX_SIZE;
  }
  deque->arr[deque->front] = data;
  deque->size++;
  printf("Enqueued %d at front\n", data);
}

// Inserta un elemento en el final
void enqueue_rear(Deque* deque, int data) {
  if (is_full(deque)) {
    printf("Deque is full. Cannot enqueue rear\n");
    return;
  }
  if (is_empty(deque)) {
    deque->front = deque->rear = 0;
  } else {
    deque->rear = (deque->rear + 1) % MAX_SIZE;
  }
  deque->arr[deque->rear] = data;
  deque->size++;
  printf("Enqueued %d at rear\n", data);
}

// Elimina un elemento del frente
int dequeue_front(Deque* deque) {
  if (is_empty(deque)) {
    printf("Deque is empty. Cannot dequeue front\n");
    return -1;
  }
  int element = deque->arr[deque->front];
  if (deque->front == deque->rear) {
    deque->front = deque->rear = -1;
  } else {
    deque->front = (deque->front + 1) % MAX_SIZE;
  }
  deque->size--;
  printf("Dequeued %d from front\n", element);
  return element;
}

// Elimina un elemento del final
int dequeue_rear(Deque* deque) {
  if (is_empty(deque)) {
    printf("Deque is empty. Cannot dequeue rear\n");
    return -1;
  }
  int element = deque->arr[deque->rear];
  if (deque->front == deque->rear) {
    deque->front = deque->rear = -1;
  } else {
    deque->rear = (deque->rear - 1 + MAX_SIZE) % MAX_SIZE;
  }
  deque->size--;
  printf("Dequeued %d from rear\n", element);
  return element;
}

// Muestra los elementos del deque
void display(Deque* deque) {
  if (is_empty(deque)) {
    printf("Deque is empty\n");
    return;
  }
  printf("Deque: ");
  for (int i = 0; i < deque->size; i++) {
    int index = (deque->front + i) % MAX_SIZE; // Ajuste circular
    printf("%d ", deque->arr[index]);
  }
  printf("\n");
}

int main() {
  Deque deque;
  initialize_deque(&deque);

  // Inserta elementos en el frente y en el final
  enqueue_rear(&deque, 10);
  enqueue_rear(&deque, 20);
  enqueue_front(&deque, 5);
  enqueue_rear(&deque, 30);
  enqueue_front(&deque, 1);

  // Mostrar elementos
  display(&deque);

  // Elimina elementos del frente y del final
  dequeue_front(&deque);
  dequeue_rear(&deque);

  // Mostrar después de eliminar
  display(&deque);

  // Inserta más elementos
  enqueue_rear(&deque, 40);
  enqueue_front(&deque, 2);

  // Mostrar después de nuevos enqueues
  display(&deque);

  return 0;
}
