#include "ht_clientes.h"
#include "ht_consumos.h"

int main(){
  Cliente* clientes[] = {
    &(Cliente){"Juan", "Pérez", "Avenida 123", 46374815, "3401553434"},
    &(Cliente){"Roberto", "Carlos", "Avenida 889", 28273866, "3401557711"},
    &(Cliente){"Ana", "Martínez", "Calle 234", 19384756, "3401558822"},
    &(Cliente){"Lucía", "Gómez", "Calle 567", 82736415, "3401559944"},
    &(Cliente){"Carlos", "Rodríguez", "Calle 789", 92837461, "3401555533"},
    &(Cliente){"María", "Fernández", "Avenida 890", 71829364, "3401551144"},
    &(Cliente){"Laura", "González", "Calle 101", 17283946, "3401552233"},
    &(Cliente){"Pedro", "Sánchez", "Avenida 456", 83746512, "3401554455"},
    &(Cliente){"Sofía", "Hernández", "Calle 789", 37482916, "3401557766"},
    &(Cliente){"Jorge", "Díaz", "Avenida 112", 91827364, "3401558899"},
    &(Cliente){"Pablo", "Silva", "Calle 567", 83927461, "3401553311"},
    &(Cliente){"Isabel", "Moreno", "Calle 890", 12983745, "3401554422"},
    &(Cliente){"Carmen", "Torres", "Avenida 567", 29384715, "3401555566"},
    &(Cliente){"Luis", "Ruiz", "Calle 333", 74829163, "3401556677"},
    &(Cliente){"Miguel", "Flores", "Avenida 998", 84736291, "3401558899"},
    &(Cliente){"Paula", "Navarro", "Calle 777", 39284715, "3401551133"},
    &(Cliente){"Emilio", "Vega", "Avenida 124", 19374628, "3401552244"},
    &(Cliente){"Gloria", "Ramos", "Calle 987", 91837465, "3401553355"},
    &(Cliente){"Adriana", "Castro", "Avenida 675", 82736492, "3401554466"},
    &(Cliente){"Manuel", "Romero", "Calle 999", 91827364, "3401555577"}
  };

  int cantClientes = sizeof(clientes) / sizeof(clientes[0]);

  HashTableClientes* ht_clientes = ht_clientes_create();

  for(int i = 0; i<cantClientes; i++){
    ht_clientes_insert(ht_clientes, clientes[i]);
  }

  ht_clientes_display(ht_clientes);

  // 

  Consumo* consumos[] = {
    &(Consumo){"01/12/2024", 1500, 46374815},
    &(Consumo){"02/12/2024", 2200, 28273866},
    &(Consumo){"03/12/2024", 3000, 19384756},
    &(Consumo){"04/12/2024", 1750, 82736415},
    &(Consumo){"05/12/2024", 2500, 92837461},
    &(Consumo){"06/12/2024", 3100, 71829364},
    &(Consumo){"07/12/2024", 2000, 17283946},
    &(Consumo){"08/12/2024", 1800, 83746512},
    &(Consumo){"09/12/2024", 2700, 37482916},
    &(Consumo){"10/12/2024", 1950, 91827364},
    &(Consumo){"11/12/2024", 2200, 83927461},
    &(Consumo){"12/12/2024", 2450, 12983745},
    &(Consumo){"13/12/2024", 1700, 29384715},
    &(Consumo){"14/12/2024", 1900, 74829163},
    &(Consumo){"15/12/2024", 2300, 84736291},
    &(Consumo){"16/12/2024", 2500, 39284715},
    &(Consumo){"17/12/2024", 2100, 19374628},
    &(Consumo){"18/12/2024", 2800, 91837465},
    &(Consumo){"19/12/2024", 1500, 82736492},
    &(Consumo){"20/12/2024", 2000, 91827364} // Repetido intencionalmente para mostrar manejo de colisiones.
  };

  int cantConsumos = sizeof(consumos) / sizeof(consumos[0]);

  HashTableConsumos* ht_consumos = ht_consumos_create();

  for(int i = 0; i<cantConsumos; i++){
    ht_consumos_insert(ht_consumos, consumos[i]);
  }

  printf("¿Cuánto consumió %s %s el 03/12/2024?\n", clientes[2]->nombre, clientes[2]->apellido);
  printf("%d\n", ((ht_consumos_search(ht_consumos, clientes[2]->DNI, "03/12/2024") != NULL) 
                  ? ht_consumos_search(ht_consumos, clientes[2]->DNI, "03/12/2024")->monto 
                  : 0));

  ht_consumos_display(ht_consumos);


  return 0;
}