#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int absolute(int a)
{
  // TODO: Write code to return absolute value of a number
  //  function should return absolute value of a number absolute(9)=9, absolute(-9)=9
  return (a < 0) ? -a : a;
}

void sort_squares(int *arr, int n)
{
  int left = 0;
  int right = n - 1;
  int *result = (int *)malloc(n * sizeof(int));

  for (int i = n - 1; i >= 0; i--)
  {
    if (absolute(arr[left]) > absolute(arr[right]))
    {
      result[i] = arr[left] * arr[left];
      left++;
    }
    else
    {
      // fill code here
      result[i] = arr[right] * arr[right];
      right--;
    }
  }

  // copying elements of result to arr
  for (int i = 0; i < n; i++)
  {
    arr[i] = result[i];
  }

  // fill code here
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: ./squares [elements in ascending order]\n");
    exit(0);
  }
  int n = argc - 1;
  int *arr = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    arr[i] = atoi(argv[i + 1]);
  }
  sort_squares(arr, n);
  print_array(arr, n);
  free(arr);
}