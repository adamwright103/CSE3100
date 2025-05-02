#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>

#define NUM 2

#define M 60
#define N 80
#define N_INIT_CONFIG 2

int A[M][N] = {{0}};
struct thread_data
{
  int id;
  int num_generations;
  pthread_barrier_t *p_barrier;
};

// display the game borad
void display()
{
  int i, j;

  for (i = 0; i < M; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (A[i][j] == 1)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}

// copy a small board into a bigger game board
void copy_block(int m, int n, int source[][n], int i_d, int j_d, int m1, int n1,
                int dest[][n1])
{
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    {
      if (i_d + i < m1 && j_d + j < n1)
        dest[i_d + i][j_d + j] = source[i][j];
    }
}

/* This function determines the state of cell A[i][j] in the next generation.
 * Return value is either 0 or 1, indicating A[i][j]'s value in the next
 * generation.
 * */
int next_state(int i, int j)
{
  int sum = 0;

  // Add the values of cells in a 3x3 matrix
  for (int ii = i - 1; ii <= i + 1; ii++)
  {
    int ni = ii;
    // you can also use one statement like
    ni = (ii + M) % M;

    for (int jj = j - 1; jj <= j + 1; jj++)
    {
      // here we use %
      int nj = (jj + N) % N;
      sum += A[ni][nj];
    }
  }
  // You could skip A[i][j] in the loop, but need many comparisons.
  sum -= A[i][j];

  // the number of comparisons can be reduced, but the logic would be less
  // straightforward
  if (A[i][j] == 1 && (sum == 2 || sum == 3))
    return 1;
  if (A[i][j] == 0 && sum == 3)
    return 1;
  return 0;
}

// this is the function that we need to modify to use two threads
void next_generation()
{
  int B[M][N];
  int i, j;

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      B[i][j] = next_state(i, j);

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      A[i][j] = B[i][j];
}

void *game_thread(void *threadarg)
{
  // Fill code here - assign these variables
  struct thread_data *my_data = (struct thread_data *)threadarg;
  int id = my_data->id;
  int num_generations = my_data->num_generations;
  pthread_barrier_t *p_barrier = my_data->p_barrier;
  int B[M][N];
  int i, j, k;

  // split the game board into 2.
  int num_rows = M / NUM;
  int start_row = id * num_rows;
  int end_row = id ? M : num_rows;

  for (k = 0; k < num_generations; k++)
  {
    // TODO
    // fill in code below

    // calculate next generation
    for (i = start_row; i < end_row; i++)
    {
      for (j = 0; j < N; j++)
      {
        B[i][j] = next_state(i, j);
      }
    }

    // wait for all threads to calculate the next generation then proceed
    pthread_barrier_wait(p_barrier);
    for (i = start_row; i < end_row; i++)
    {
      for (j = 0; j < N; j++)
      {
        A[i][j] = B[i][j];
      }
    }

    // waiting for all threads to update board
    pthread_barrier_wait(p_barrier);
  }
  // fill code here

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  // hard coded configuration.
  int a[10][10] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };
  int d[3][3] = {{0, 1, 1}, {1, 1, 0}, {0, 1, 0}};

  if (argc < 3)
  {
    printf("Usage: %s init_conf num_generations [multi_thread(y/n)]\n",
           argv[0]);
    return 1;
  }

  int init_conf = atoi(argv[1]);
  if (init_conf > N_INIT_CONFIG || init_conf < 1)
  {
    printf("init_conf must be an integer that is  >= 1 and <= 2.\n");
    return -1;
  }

  // set up the initial configuration
  switch (init_conf)
  {
  case 1:
    copy_block(10, 10, a, M / 2, N / 2, M, N, A);
    break;
  case 2:
    copy_block(3, 3, d, M / 2, N / 2, M, N, A);
    break;
  default:
    // should never get here
    printf("Error: Invalid init_conf.\n");
    return -1;
  }

  int num_generations = atoi(argv[2]);
  if (num_generations <= 0)
  {
    printf("Error: Number of generations must be an integer > 0.\n");
    return 1;
  }
  if (argc >= 4 && (strcmp(argv[3], "n") == 0 || strcmp(argv[3], "N") == 0))
  {
    for (int i = 0; i < num_generations; i++)
      next_generation();
    display();
    return 0;
  }

  pthread_barrier_t barrier;
  pthread_t threads[NUM];
  struct thread_data thread_data_array[NUM];
  pthread_barrier_init(&barrier, NULL, NUM);

  for (int i = 0; i < NUM; i++)
  {
    thread_data_array[i].id = i;
    thread_data_array[i].p_barrier = &barrier;
    thread_data_array[i].num_generations = num_generations;
    pthread_create(&threads[i], NULL, (void *)game_thread,
                   &thread_data_array[i]);
  }

  for (int i = 0; i < NUM; i++)
    pthread_join(threads[i], NULL);

  pthread_barrier_destroy(&barrier);
  display();

  return 0;
}