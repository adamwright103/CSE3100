#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double curr = 0, pi = 0;
	double divisor = 1.0/16;
	//TODO
	//add code below
	for (int i = 0; i <= n; i++) {
	    // eval main term
		curr = (4.0/(8*i + 1)) - (2.0/(8*i + 4)) - (1.0/(8*i + 5)) - (1.0/(8*i + 6));
		// update scaling term
		divisor *= 16; // divisor will be equal to 16^i

        curr /= divisor;
        
        pi += curr;
	}








	printf("PI = %.10f\n", pi);
	return 0;
}