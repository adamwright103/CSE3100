#include <assert.h>

// TODO
unsigned firstDigit(unsigned k)
{
  // fill in code below
  while (k / 10 != 0)
  {
    k /= 10;
  }
  return k;
}

// TODO
void FirstDigitCount(unsigned *a, unsigned n, unsigned freq[10])
{
  // fill in your code below
  int first_digit = 0;
  for (int i = 0; i < n; i++)
  {
    first_digit = firstDigit(a[i]);
    freq[first_digit] += 1;
  }
}
