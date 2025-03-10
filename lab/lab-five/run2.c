#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t child;
  int exitStatus;

  // at least, there should be 3 arguments
  // 2 for the first command, and the rest for the second command
  if (argc < 4)
  {
    fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
    return 1;
  }

  // first parent should fork and let child run first argument,
  // then await it before char **argforking again to run 2nd
  child = fork();
  int exitStatusFirst;

  switch (child)
  {
  case -1:
  {
    // error occured
    perror("fork()");
    exit(EXIT_FAILURE);
    break;
  }
  case 0:
  {
    // in child process
    // run first command
    execlp(argv[1], argv[1], argv[2], NULL);
    perror("execlp()");
    exit(EXIT_FAILURE);
    break;
  }
  default:
  {
    if (waitpid(child, &exitStatus, 0) > 0)
    {

      if (WIFEXITED(exitStatus) && !WEXITSTATUS(exitStatus))
      {
        // succuess, we should continue to run next command
        exitStatusFirst = exitStatus;
        break;
      }

      else
      {
        perror("execlp()");
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      // waitpid() failed
      perror("waitpid()");
      exit(EXIT_FAILURE);
    }
  }
  }

  // first command worked successfully correctly
  // we will run 2nd command
  child = fork();
  switch (child)
  {
  case -1:
  {
    // error occured
    perror("fork()");
    exit(EXIT_FAILURE);
    break;
  }
  case 0:
  {
    // in child process
    // run first command
    char *second_argv[argc - 2];
    for (int i = 0; i < argc - 3; i++)
    {
      second_argv[i] = argv[i + 3];
    }
    second_argv[argc - 3] = NULL;

    execvp(second_argv[0], second_argv);
    perror("execvp()");
    exit(EXIT_FAILURE);
    break;
  }
  default:
  {
    if (waitpid(child, &exitStatus, 0) > 0)
    {

      if (WIFEXITED(exitStatus) && !WEXITSTATUS(exitStatus))
      {
        // succuess, we can exit
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatusFirst), exitStatusFirst);
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), exitStatus);
        return 0;
      }

      else
      {
        perror("execvp()");
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      // waitpid() failed
      perror("waitpid()");
      exit(EXIT_FAILURE);
    }
  }
  }

  return 0;
}