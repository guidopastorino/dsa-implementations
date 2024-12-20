#include "functions.h"

Sequence parse_sequence(const char* input){
  Sequence seq;
  seq.array = NULL;
  seq.size = 0;

  const char* ptr = input;

  while(*ptr){
    if(*ptr == '-' || (*ptr >= '0' && *ptr <= '9')){
      seq.array = (int*)realloc(seq.array, sizeof(int) * (seq.size + 1));
      seq.array[seq.size++] = strtol(ptr, (char**)&ptr, 10);
    } else {
      ptr++;
    }
  }

  return seq;
}

int can_partition(int* array, int size, int index, int sum1, int sum2, Partition* part){
  if(index == size){
    if(sum1 == sum2){
      return 1;
    }
    return 0;
  }

  // Intentamos agregar el elemento actual al subset1
  part->subset1.array = (int*)realloc(part->subset1.array, sizeof(int) * (part->subset1.size + 1));
  part->subset1.array[part->subset1.size++] = array[index];
  if(can_partition(array, size, index + 1, sum1 + array[index], sum2, part)){
    return 1;
  }
  part->subset1.size--; // Retrocedemos

  // Intentamos agregar el elemento actual al subset2
  part->subset2.array = (int*)realloc(part->subset2.array, sizeof(int) * (part->subset2.size + 1));
  part->subset2.array[part->subset2.size++] = array[index];
  if(can_partition(array, size, index + 1, sum1, sum2 + array[index], part)){
    return 1;
  }
  part->subset2.size--; // Retrocedemos

  return 0;
}

Partition partition_sequence(Sequence seq){
  Partition part;
  part.subset1.array = NULL;
  part.subset1.size = 0;
  part.subset2.array = NULL;
  part.subset2.size = 0;
  part.is_valid = 0;

  if(can_partition(seq.array, seq.size, 0, 0, 0, &part)){
    part.is_valid = 1;
  }
  
  return part;
}