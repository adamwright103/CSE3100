// In this assignment, we write code to convert decimal integers into hexadecimal numbers
// We pratice using arrays in this assignment
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// convert the decimal integer d to hexadecimal, the result is stored in hex[]
void dec_hex(int d, char hex[])
{
  char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
                   'C', 'D', 'E', 'F'};

  int k = 0;
  // Fill in your code below
  // It should not be hard to obtain the last digit of a hex number
  // Then what?
  // If we are getting the digits in a reverse order, what should we do in the end?

  // should repetadly take mod 16 of num, add the hex equivalent to hex array, and then continue
  // untill number is 0

  // creates reversed array of hex digits
  while (d > 0)
  {
    hex[k] = digits[d % 16];
    d /= 16;
    k++;
  }

  // reverse the array
  for (int i = 0; i < k / 2; i++)
  {
    char temp = hex[i];
    hex[i] = hex[k - i - 1];
    hex[k - i - 1] = temp;
  }

  // Make sure the last character is a zero so that we can print the string correctly
  hex[k] = '\0';
}

// Do not change the code below
int main()
{
  int d;
  char hex[80];

  printf("Enter a positive integer : ");
  scanf("%d", &d);
  dec_hex(d, hex);
  printf("%s\n", hex);
  return 0;
}