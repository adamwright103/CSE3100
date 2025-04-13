#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define NUM_THREADS 2

typedef struct
{
  unsigned int id;
  TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void *thread_main(void *p_arg)
{
  // TODO
  // create thread, we should add split the matrix into two parts and have a thread add each part
  thread_arg_t *arg = (thread_arg_t *)p_arg;
  int half_row = arg->m->nrows / NUM_THREADS;
  int start_row = arg->id ? half_row : 0;
  int end_row = arg->id ? arg->m->nrows : half_row;

  for (int i = start_row; i < end_row; i++)
  {
    for (int j = 0; j < arg->m->ncols; j++)
    {
      arg->t->data[i][j] = arg->m->data[i][j] + arg->n->data[i][j];
    }
  }
  pthread_exit(NULL);
}

/* Return the sum of two matrices. The result is in a newly creaed matrix.
 *
 * If a pthread function fails, report error and exit.
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix *addMatrix_thread(TMatrix *m, TMatrix *n)
{
  if (m == NULL || n == NULL || m->nrows != n->nrows || m->ncols != n->ncols)
    return NULL;

  TMatrix *t = newMatrix(m->nrows, m->ncols);
  if (t == NULL)
    return t;

  // TODO
  // create two threads
  pthread_t threads[NUM_THREADS];
  thread_arg_t args[NUM_THREADS];
  // sum threads
  for (unsigned int i = 0; i < NUM_THREADS; i++)
  {
    args[i].id = i;
    args[i].m = m;
    args[i].n = n;
    args[i].t = t;
    if (pthread_create(&threads[i], NULL, thread_main, &args[i]) != 0)
    {
      perror("pthread_create");
      freeMatrix(t);
      return NULL;
    }
  }
  // join the 2 threads
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  return t;
}