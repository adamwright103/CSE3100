#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define NUM_THREADS 2

typedef struct
{
  unsigned int id;
  TMatrix *m, *n, *t;
} thread_arg_t;

static void *thread_main(void *p_arg)
{
  // TODO
  thread_arg_t *arg = (thread_arg_t *)p_arg;
  for (int i = arg->id; i < arg->m->nrows; i += NUM_THREADS)
  {
    for (int j = 0; j < arg->n->ncols; j++)
    {
      TElement sum = (TElement)0;
      for (unsigned int k = 0; k < arg->m->ncols; k++)
      {
        sum += arg->m->data[i][k] * arg->n->data[k][j];
      }
      arg->t->data[i][j] = sum;
    }
  }
  pthread_exit(NULL);
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit.
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix *mulMatrix_thread(TMatrix *m, TMatrix *n)
{
  if (m == NULL || n == NULL || m->ncols != n->nrows)
    return NULL;

  TMatrix *t = newMatrix(m->nrows, n->ncols);
  if (t == NULL)
    return t;

  // TODO
  // create two threads
  pthread_t threads[NUM_THREADS];
  thread_arg_t args[NUM_THREADS];

  // multiply threads
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