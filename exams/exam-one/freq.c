#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

unsigned firstDigit(unsigned k);
void FirstDigitCount(unsigned *a, unsigned n, unsigned freq[10]);

int main(int argc, char *argv[])
{
  assert(argc == 2);
  unsigned n = atoi(argv[1]);

  assert(n >= 1 && n <= 100000);
  unsigned a[n], i;

  unsigned sum = 0;
  for (i = 0; i < n; i++)
  {
    a[i] = sum;
    sum += i + 1;
  }
  unsigned freq[10];
  FirstDigitCount(a, n, freq);
  for (i = 0; i < 10; i++)
    printf("%d\t%d\n", i, freq[i]);
  return 0;
}