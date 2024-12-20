#include "ht_consumos.h"

// Función auxiliar para crear un nodo de consumo
static HashNodeConsumo* crear_nodo(Consumo consumo) {
    HashNodeConsumo* node = (HashNodeConsumo*)malloc(sizeof(HashNodeConsumo));
    assert(node != NULL);

    node->consumo = (Consumo*)malloc(sizeof(Consumo));
    assert(node->consumo != NULL);

    node->consumo->fecha = (char*)malloc(strlen(consumo.fecha) + 1);
    assert(node->consumo->fecha != NULL);
    strcpy(node->consumo->fecha, consumo.fecha);

    node->consumo->monto = consumo.monto;
    node->consumo->DNI = consumo.DNI;
    node->next = NULL;

    return node;
}

// Función para calcular el hash compuesto basado en DNI y fecha
static unsigned int hash_compuesto(int DNI, char* fecha, int size) {
    unsigned int hash_dni = DNI % size;
    unsigned int hash_fecha = 0;

    for (int i = 0; fecha[i] != '\0'; i++) {
        hash_fecha = (hash_fecha * 31 + fecha[i]) % size;
    }

    return (hash_dni + hash_fecha) % size;
}

// Función para verificar si es necesario redimensionar la tabla
static int needs_resize(HashTableConsumos* ht) {
    return ((float)ht->count / ht->size) >= LOAD_FACTOR_THRESHOLD;
}

// Función para redimensionar la tabla hash
static void ht_consumos_resize(HashTableConsumos* ht) {
    int old_size = ht->size;
    HashNodeConsumo** old_table = ht->table;

    ht->size *= 2; // Doblar el tamaño
    ht->table = (HashNodeConsumo**)calloc(ht->size, sizeof(HashNodeConsumo*));
    assert(ht->table != NULL);
    ht->count = 0; // Reiniciar contador

    for (int i = 0; i < old_size; i++) {
        HashNodeConsumo* current = old_table[i];
        while (current != NULL) {
            HashNodeConsumo* next = current->next;
            ht_consumos_insert(ht, current->consumo);
            free(current);
            current = next;
        }
    }

    free(old_table);
}

// Crear tabla hash
HashTableConsumos* ht_consumos_create() {
    HashTableConsumos* ht = (HashTableConsumos*)malloc(sizeof(HashTableConsumos));
    assert(ht != NULL);
    ht->table = (HashNodeConsumo**)calloc(INITIAL_HTCONSUMOS_SIZE, sizeof(HashNodeConsumo*));
    assert(ht->table != NULL);
    ht->size = INITIAL_HTCONSUMOS_SIZE;
    ht->count = 0;

    return ht;
}

// Insertar un consumo en la tabla hash
void ht_consumos_insert(HashTableConsumos* ht, Consumo* consumo) {
    if (needs_resize(ht)) {
        ht_consumos_resize(ht);
    }

    unsigned int index = hash_compuesto(consumo->DNI, consumo->fecha, ht->size);
    HashNodeConsumo* current = ht->table[index];
    HashNodeConsumo* node = crear_nodo(*consumo);

    // Insertar al principio de la lista para manejo de colisiones
    node->next = current;
    ht->table[index] = node;

    ht->count++;
}

// Buscar un consumo por DNI y fecha
Consumo* ht_consumos_search(HashTableConsumos* ht, int DNI, char* fecha) {
    unsigned int index = hash_compuesto(DNI, fecha, ht->size);
    HashNodeConsumo* current = ht->table[index];

    while (current != NULL) {
        if (current->consumo->DNI == DNI && strcmp(current->consumo->fecha, fecha) == 0) {
            return current->consumo;
        }
        current = current->next;
    }

    return NULL;
}

// Mostrar todos los consumos
void ht_consumos_display(HashTableConsumos* ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNodeConsumo* current = ht->table[i];
        printf("%d: ", i);

        while (current != NULL) {
            printf("(%s, %d, %d) -> ",
                   current->consumo->fecha,
                   current->consumo->monto,
                   current->consumo->DNI);
            current = current->next;
        }

        printf("NULL\n");
    }
}

// Liberar memoria de la tabla hash
void ht_consumos_destroy(HashTableConsumos* ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNodeConsumo* current = ht->table[i];

        while (current != NULL) {
            HashNodeConsumo* next = current->next;

            free(current->consumo->fecha);
            free(current->consumo);
            free(current);

            current = next;
        }
    }

    free(ht->table);
    free(ht);
}