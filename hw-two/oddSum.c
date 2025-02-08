#include <stdio.h>
#include <stdlib.h>

int oddSumHelp(int count, int bound, int value)
{
  // fill in your code below

  // base cases:
  if (count == 1 && bound == value)
  {
    printf("%d ", bound);
    return 1; // solution found
  }
  if (count == 0 || bound <= 0 || value <= 0)
  {
    return 0; // no solution
  }

  // now call recursivly finding a bound that will sum to value
  for (int next_bound = bound; next_bound > 0; next_bound -= 2)
  {

    if (oddSumHelp(count - 1, next_bound - 2, value - next_bound))
    {
      printf("%d ", next_bound);
      return value;
    }
  }
  return 0;
}

// Do not change the code below
void oddSum(int count, int bound, int value)
{
  if (value <= 0 || count <= 0 || bound <= 0)
    return;

  if (bound % 2 == 0)
    bound -= 1;

  if (!oddSumHelp(count, bound, value))
    printf("No solutions.\n");
  else
    printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc != 4)
    return -1;

  int count = atoi(argv[1]);
  int bound = atoi(argv[2]);
  int value = atoi(argv[3]);

  // oddSum(4, 10, 20);
  // oddSum(10,20,100);
  // oddSum(20,20,200);
  oddSum(count, bound, value);
  return 0;
}