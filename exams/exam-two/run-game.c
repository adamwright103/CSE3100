#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// write an integer to a pipe
void write_int(int pd, int value) { write(pd, &value, sizeof(int)); }
// read an integer from a pipe
// the function returns the number of bytes read
int read_int(int pd, int *value) { return read(pd, value, sizeof(int)); }

double random_double() { return (double)rand() / RAND_MAX; }

int coin_flip(double p) { return random_double() < p; }

void run_simulation(int n, double p)
{
  int pd1[2];
  // pipe creation
  if (pipe(pd1) < 0)
  {
    perror("Error.");
    exit(-1);
  }

  int pd2[2];
  // pipe creation
  if (pipe(pd2) < 0)
  {
    perror("Error.");
    exit(-1);
  }
  pid_t pid = fork();
  if (pid == 0)
  {
    // TODO
    // fill in code below
    // note this is player A

    srand(3100);
    close(pd1[0]); // close pipe 1 read
    close(pd2[1]); // close pipe 2 write

    int v;
    // TODO
    // complete the following line of code
    while (read_int(pd2[0], &v) != 0)
    {
      // TODO
      // fill in code below
      if (v == 1)
      {
        // got told to flip a coin so flip and send to parent
        int result = coin_flip(p);
        write_int(pd1[1], result);
      }
    }
    // TODO
    // fill in code below
    // close remaining pipes
    close(pd2[0]);
    close(pd1[1]);
    exit(EXIT_SUCCESS);
  }
  // TODO
  // fill in code below

  // close unneccsary pipes for parent/A
  close(pd1[1]);
  close(pd2[0]);

  int pd3[2];
  // pipe creation
  if (pipe(pd3) < 0)
  {
    perror("Error.");
    exit(-1);
  }

  int pd4[2];
  // pipe creation
  if (pipe(pd4) < 0)
  {
    perror("Error.");
    exit(-1);
  }
  pid_t pid1 = fork();

  if (pid1 == 0)
  {
    // TODO
    // fill in code below
    // note this is player B

    srand(3504);
    close(pd1[0]); // close pipe for child A
    close(pd2[1]); // close pipe for child A
    close(pd3[0]); // close pipe 3 read
    close(pd4[1]); // close pipe 4 write

    int v;
    // TODO
    // complete the following line of code
    while (read_int(pd4[0], &v) != 0)
    {
      // TODO
      // fill in code below
      if (v == 1)
      {
        // got told to flip a coin so flip and send to parent
        int result = coin_flip(p);
        write_int(pd3[1], result);
      }
    }

    // TODO
    // fill in code below
    close(pd4[0]);
    close(pd3[1]);
    exit(EXIT_SUCCESS);
  }

  int n1 = 0;
  int n2 = 0;
  int v1, v2;

  while (n1 + n2 < n)
  {
    // TODO
    // finish the follow lines of code
    write_int(pd2[1], 1);
    write_int(pd4[1], 1);
    read_int(pd1[0], &v1);
    read_int(pd3[0], &v2);
    if (v1)
      n1++;
    else
    {
      if (v2)
        n2++;
    }
  }
  printf("prob of A wins = %.3lf\n", (double)(n1) / (n1 + n2));
  // TODO
  // fill in code below

  // close remaining pipes
  close(pd1[0]);
  close(pd2[1]);
  close(pd3[0]);
  close(pd3[1]);
  close(pd4[0]);
  close(pd4[1]);

  // await children to exit
  waitpid(pid, NULL, 0);
  waitpid(pid1, NULL, 0);
}