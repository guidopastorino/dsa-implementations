#include "functions.h"

int main() {
  const char* input = "[1,3,3,-1,2]";
  Sequence seq = parse_sequence(input);

  printf("Sequence: ");
  for (int i = 0; i < seq.size; i++) {
    printf("%d ", seq.array[i]);
  }
  printf("\n");

  Partition part = partition_sequence(seq);
  if (part.is_valid) {
    printf("Partition found:\nSubset 1: ");
    for (int i = 0; i < part.subset1.size; i++) {
      printf("%d ", part.subset1.array[i]);
    }
    printf("\nSubset 2: ");
    for (int i = 0; i < part.subset2.size; i++) {
      printf("%d ", part.subset2.array[i]);
    }
    printf("\n");
  } else {
    printf("Partition not possible\n");
  }

  free(seq.array);
  free(part.subset1.array);
  free(part.subset2.array);
  return 0;
}