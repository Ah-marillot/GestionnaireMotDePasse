#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s nombre1 nombre2\n", argv[0]);
    return 1;
  }

  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);

  int somme = num1 + num2;
  printf("La somme de %d et %d est %d\n", num1, num2, somme);

  return 0;
}

