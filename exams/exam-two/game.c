#include "run-game.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: %s n p\n", argv[0]);
    return 0;
  }
  int n = atoi(argv[1]);
  double p = atof(argv[2]);
  assert(n >= 1 && n <= 10000);
  assert(p >= 0.1 && p < 1.0);
  run_simulation(n, p);
  return 0;
}