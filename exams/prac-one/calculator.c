#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"

node *addition(node *num1, node *num2)
{
  node *result = NULL;
  int carry = 0;
  // TODO: Write code to add two numbers represented by num1 and num2
  int sum;
  while (num1 != NULL || num2 != NULL || carry)
  {
    sum = carry;
    if (num1 != NULL)
    {
      sum += num1->v;
      num1 = num1->next;
    }
    if (num2 != NULL)
    {
      sum += num2->v;
      num2 = num2->next;
    }
    result = prepend(result, new_node(sum % 10));
    carry = sum / 10;
  }

  return result;
}

node *subtraction(node *num1, node *num2)
{
  node *result = NULL;
  int borrow = 0;
  while (num1 != NULL || num2 != NULL)
  {                    // 3 points
    int diff = borrow; // 1 point
    if (num1 != NULL)
    {                    // 1 point
      diff += num1->v;   // 1 point
      num1 = num1->next; // 1 point
    }
    if (num2 != NULL)
    {                    // 1 point
      diff -= num2->v;   // 1 point
      num2 = num2->next; // 1 point
    }
    if (diff < 0)
    {              // 1 point
      diff += 10;  // 1 point
      borrow = -1; // 1 point
    }
    else
    {
      borrow = 0; // 1 point
    }
    result = prepend(result, new_node(diff)); // 4 points
  }
  return result;
}

node *remove_leading_zeros(node *num)
{
  node *temp = num;
  while (temp != NULL && temp->v == 0)
  {
    node *temp2 = temp;
    temp = temp->next;
    free(temp2);
  }
  return temp;
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Usage: ./calculator number1 number2\n");
    exit(0);
  }
  node *num1 = NULL, *num2 = NULL;
  node *sum = NULL;
  node *difference = NULL;

  for (int i = 0; i < strlen(argv[1]); i++)
  {
    if (!isdigit(argv[1][i]))
    {
      printf("Invalid inputin number1\n");
      exit(0);
    }
    num1 = prepend(num1, new_node(argv[1][i] - '0'));
  }
  for (int i = 0; i < strlen(argv[2]); i++)
  {
    if (!isdigit(argv[2][i]))
    {
      printf("Invalid input in number2\n");
      exit(0);
    }
    num2 = prepend(num2, new_node(argv[2][i] - '0'));
  }
  sum = addition(num1, num2);
  difference = subtraction(num1, num2);
  // difference = 100;

  sum = remove_leading_zeros(sum);
  difference = remove_leading_zeros(difference);

  print_list(sum);
  print_list(difference);

  delete_list(num1);
  delete_list(num2);
  delete_list(sum);
  delete_list(difference);
  return 0;
}