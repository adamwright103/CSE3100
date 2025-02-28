//In this assignment, we will find the smallest positive integer that
// can be expressed as a sum of two positive cube numbers in two distinct ways.
// More specifically, we want to find the smallest n such that n == i1*i1*i1 + j1*j1*j1,
// n == i2*i2*i2 + j2*j2*j2, and (i1, j1) and (i2, j2) are not the same in the sense that
// not only (i1, j1) not euqal to (i2, j2), but also (i1, j1) not equal to (j2, i2).
// We practice using loops in this assignment.
// Also, we practice how to do an early exit in a loop. We exit the loop once we find the smallest n.
// Once we are done, we will be delighted surprised to find out that this number already played a big role in
// our computer science study.
#include <stdio.h>
int main()
{
	int i, j, n;

	//We assume the smallest such n is no more than 1000000
	for(n=1; n<=1000000; n++)
	{
		//Use count to record the number of different ways of summing two positive cube numbers to n
		int count = 0;

        // increment untill i^3 is greater than n (cannot sum to equal n)
		for (i = 1; i*i*i < n; i++) {
		    // increment untill i^3 + j^3 is greater than n (cannot sum to equal n)
			for (j = i; i*i*i + j*j*j <= n; j++) {
				if (i*i*i + j*j*j == n) {
					count++;
					if (count == 2) {
					    // found 2 pairs that sum to n therefore exit loops
						goto found_sol;
					}
				}
			}
		}

	}


    found_sol: {
	//Do not change code below
	printf("%d is the solution:\n", n);
	for(i=1; i<=100; i++)
		for(j = i; j<= 100; j++)
		{
			if (i*i*i + j*j*j == n)
			{
				printf("%d * %d * %d + %d * %d * %d = %d\n", i, i, i, j, j, j, n);
			}
		}

	return 0;
	//Do not try to hard code the solution, that is not the way to learn.
    }
}