#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{

  // Fill in code below
  // When deciding which way to go for the next step, generate a random number as follows.
  // r = rand() % 4;
  // Treat r = 0, 1, 2, 3 as up, right, down and left respectively.

  // The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$.
  // The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.

  // map is max size of (2*64 + 1) x (2*64 + 1)
  int map[129][129] = {0};
  int x = n, y = n; // x, y will be current coords of walker, starting in center of square
  int visited_count = 0;

  // while inside the square
  while (x > 0 && x < 2 * n && y > 0 && y < 2 * n)
  {
    if (!map[x][y])
    {
      map[x][y] = 1;
      visited_count++;
    }
    int r = rand() % 4;
    switch (r) // up, right, down, left
    {
    case 0:
      y++;
      break;
    case 1:
      x++;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      break;
    }
  }

  int total_inside_points = (2 * n - 1) * (2 * n - 1);
  return (double)visited_count / total_inside_points;
}

// Do not change the code below
int main(int argc, char *argv[])
{
  int trials = 1000;
  int i, n, seed;
  if (argc == 2)
    seed = atoi(argv[1]);
  else
    seed = 12345;

  srand(seed);
  for (n = 1; n <= 64; n *= 2)
  {
    double sum = 0.;
    for (i = 0; i < trials; i++)
    {
      double p = two_d_random(n);
      sum += p;
    }
    printf("%d %.3lf\n", n, sum / trials);
  }
  return 0;
}