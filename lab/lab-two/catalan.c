#include <stdio.h>

/* This function calculates n-th Catalan number.
 * n is assumed to be non-negative.
 * Do not worry about overflow.
 * Do not print anything in this function.
 * Do not use floating-point numbers (or operations).
 */
long catalan_number(int n)
{
  if (n < 0)
  {
    return 0;
  }
  else if (n == 0)
  {
    return 1;
  }

  return (4 * n - 2) * catalan_number(n - 1) / (n + 1);
}

/* do not change main function */
int main(void)
{
  int n;

  while (scanf("%d", &n) == 1)
  {
    if (n < 0)
      printf("C(%2d) is not defined.\n", n);
    else
      printf("C(%2d)=%18ld\n", n, catalan_number(n));
  }
  return 0;
}