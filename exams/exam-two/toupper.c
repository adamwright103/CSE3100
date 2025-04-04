#include "redirect.c"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    printf("%s filename file_result\n", argv[0]);
    return 0;
  }

  char *argv_list[] = {"tr", "a-z", "A-Z", NULL};
  redirectStdin(argv[1]);
  redirectStdout(argv[2]);
  // fill in one line of code to execute the command specified by argv_list[]
  execvp(argv_list[0], argv_list);

  perror("Something went wrong!\n");
  return -1;
}