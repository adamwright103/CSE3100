#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// TODO
// Implement the below function
// Simulate one particle moving n steps in random directions
// Use a random number generator to decide which way to go at every step
// When the particle stops at a final location, use the memory pointed to by grid to
// record the number of particles that stop at this final location
// Feel free to declare, implement and use other functions when needed

// Generate a random number using rand() % 6. If this number is 0 or 1, you should move left or right
// on the x-axis, respectively. If it is 2 or 3, you should move up or down on the y-axis, respectively. If it is 4
// or 5, move up or down on the z-axis, respectively

void print_result(int *grid, int n);

void one_particle(int *grid, int n)
{
  int x[3] = {n, n, n}; // location of particle [x, y, z], starting at center of grid
  int s = (2 * n + 1);

  for (int i = 0; i < n; i++)
  {
    int direction = rand() % 6;
    switch (direction)
    {
    case 0:
      // move left
      x[0]--;
      break;
    case 1:
      // move right
      x[0]++;
      break;
    case 2:
      // move foward
      x[1]++;
      break;
    case 3:
      // move backward
      x[1]--;
      break;
    case 4:
      // move up
      x[2]++;
      break;
    case 5:
      // move down
      x[2]--;
      break;
    default:
      printf("direction error, out of range\n");
      break;
    }
  }
  // record the final location of the particle
  grid[x[0] + s * x[1] + s * s * x[2]]++;
  // printf("particle at %d %d %d (i = %d)\n", x[0], x[1], x[2], x[0] + s * x[1] + s * s * x[2]);
}

// TODO
// Implement the following function
// This function returns the fraction of particles that lie within the distance
// r*n from the origin (including particles exactly r*n away)
// The distance used here is Euclidean distance
// Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
  // can compare r^2 with the sum of the squares of the coordinates
  int total = 0, count = 0, s = (2 * n + 1);
  for (int i = 0; i < s; i++)
  {
    for (int j = 0; j < s; j++)
    {
      for (int k = 0; k < s; k++)
      {
        // get all particals
        total += grid[i + s * j + s * s * k];

        int distance_squared = (i - n) * (i - n) + (j - n) * (j - n) + (k - n) * (k - n);
        if (distance_squared <= r * r * n * n)
        {
          count += grid[i + s * j + s * s * k];
        }
      }
    }
  }
  return (double)count / (total);
}

// use this function to print results
void print_result(int *grid, int n)
{
  printf("radius density\n");
  // int s = (2 * n + 1);
  // for (int z = 0; z < s; z++)
  // {
  //   for (int y = 0; y < s; y++)
  //   {
  //     for (int x = 0; x < s; x++)
  //     {
  //       printf("%d ", grid[x + s * y + s * s * z]);
  //     }
  //     printf("\n");
  //   }
  //   printf("\n");
  // }

  for (int k = 1; k <= 20; k++)
  {
    printf("%.2lf   %lf\n", 0.05 * k, density(grid, n, 0.05 * k));
  }
}

// TODO
// Finish the following function
// See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
  // fill in a few line of code below

  // grid should be 2n + 1 in each dimension as allows for max steps of n in each direction
  int *grid = (int *)calloc((2 * n + 1) * (2 * n + 1) * (2 * n + 1), sizeof(int));
  if (grid == NULL)
  {
    printf("malloc failed\n");
    exit(1);
  }

  for (int i = 1; i <= m; i++)
  {
    one_particle(grid, n);
  }

  print_result(grid, n);
  free(grid);
  // fill in some code below
}

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    printf("Usage: %s n m\n", argv[0]);
    return 0;
  }
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);

  assert(n >= 1 && n <= 50);
  assert(m >= 1 && m <= 1000000);
  srand(12345);
  diffusion(n, m);
  return 0;
}