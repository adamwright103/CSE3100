#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
  perror(s);
  exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
  // TODO
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  char *out = malloc((len1 + len2 + 1) * sizeof(char));
  if (out == NULL)
  {
    my_error("malloc failed");
  }
  out[0] = '\0'; // need to initilise for valgrind?
  out = strcat(out, s1);
  out = strcat(out, s2);
  return out;
}

int main(int argc, char *argv[])
{
  char *s;

  s = my_strcat("", argv[0]);

  for (int i = 1; i < argc; i++)
  {
    char *temp = my_strcat(s, argv[i]);
    free(s); // Free the last catted string
    s = temp;
  }

  printf("%s\n", s);
  free(s);
  return 0;
}