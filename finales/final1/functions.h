#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int* array;
  int size;
} Sequence;

typedef struct {
  Sequence subset1;
  Sequence subset2;
  int is_valid;
} Partition;

Sequence parse_sequence(const char* input);

int can_partition(int* arr, int size, int index, int sum1, int sum2, Partition* part);

Partition partition_sequence(Sequence seq);

#endif