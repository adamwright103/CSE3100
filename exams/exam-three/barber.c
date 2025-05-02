#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_CHAIRS 3
#define NUM_CUSTOMERS 20
#define MAX_HAIRCUTS 10

pthread_mutex_t mutex;
pthread_cond_t customer_cond;
pthread_cond_t barber_cond;

int waiting = 0;
int total_haircuts = 0;
int barber_done = 0;
int chairs[NUM_CHAIRS] = {0};
int current_customer = 0;

void print_status()
{
  if (current_customer == 0)
  {
    printf("Sleep ");
  }
  else
  {
    printf(" %02d ", current_customer);
  }
  printf("-------------------------- Chairs: ");
  for (int i = 0; i < NUM_CHAIRS; i++)
  {
    printf("%02d ", chairs[i]);
  }
  printf("\n");
}

void *barber(void *arg)
{
  while (1)
  {
    // TODO
    // Identify critical sections and add mutex locks and unlocks
    // Indentify positions add wait and signalling for threads
    pthread_mutex_lock(&mutex);
    while (waiting == 0 && !barber_done)
    {
      current_customer = 0;
      print_status();
      pthread_cond_wait(&customer_cond, &mutex);
    }
    if (barber_done)
    {
      pthread_mutex_unlock(&mutex);
      break;
    }

    current_customer = chairs[0];
    // moving customers up a chair
    for (int i = 0; i < NUM_CHAIRS - 1; i++)
    {
      chairs[i] = chairs[i + 1];
    }
    chairs[NUM_CHAIRS - 1] = 0;
    waiting--;

    printf("Barber is cutting hair of customer %d, haircut %d\n",
           current_customer, total_haircuts + 1);
    print_status();

    // unlock before sleep
    pthread_mutex_unlock(&mutex);

    sleep(3); // time to simulate a haircut

    pthread_mutex_lock(&mutex);
    printf("Barber done with customer %d\n", current_customer);

    total_haircuts++; // critical
    if (total_haircuts >= MAX_HAIRCUTS)
    {
      barber_done = 1;
      printf("Barber is done for today\n");
    }
    // signal customers
    pthread_cond_signal(&barber_cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *customer(void *arg)
{
  long id = (long)arg;
  // TODO
  // Identify critical sections and add mutex locks and unlocks
  // Indentify positions add wait and signalling for threads

  pthread_mutex_lock(&mutex); // if statement has critical variables
  if (!barber_done && waiting + total_haircuts < MAX_HAIRCUTS - 1)
  {
    for (int i = 0; i < NUM_CHAIRS; i++)
    {
      if (chairs[i] == 0)
      {
        chairs[i] = id;
        waiting++;
        print_status();
        pthread_cond_signal(&customer_cond);
        while (chairs[0] != id && !barber_done)
        {
          // checking if it is customer's turn
          pthread_cond_wait(&barber_cond, &mutex);
        }
        if (chairs[0] == id)
        {
          pthread_mutex_unlock(&mutex);
          return NULL;
        }
      }
    }
    printf("Customer %ld leaves because no chairs left to wait\n", id);
  }
  else
  {
    printf("Customer %ld leaves because no more haircuts today \n", id);
  }

  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("usage: ./barber [seed]\n");
    exit(1);
  }
  srand(atoi(argv[1]));
  pthread_t barber_thread, customer_threads[NUM_CUSTOMERS];

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&customer_cond, NULL);
  pthread_cond_init(&barber_cond, NULL);

  pthread_create(&barber_thread, NULL, barber, NULL);

  for (long i = 1; i <= NUM_CUSTOMERS; i++)
  {
    pthread_create(&customer_threads[i - 1], NULL, customer, (void *)i);
    sleep(rand() % 3 + 1); // time to simulate customer arrival
  }

  pthread_join(barber_thread, NULL);
  for (int i = 0; i < NUM_CUSTOMERS; i++)
  {
    pthread_join(customer_threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&customer_cond);
  pthread_cond_destroy(&barber_cond);

  return 0;
}