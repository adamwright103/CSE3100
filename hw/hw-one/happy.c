#include <stdio.h>
#include <stdlib.h>

int sum_squares(int n) {
    int sum = 0;
    while (n > 0) {
        // get each digit from mod 10 and add to sum
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	int m = n;
	//TODO
	//add code below
	while (n != 1 && n != 4) {
	    n = sum_squares(n);
	    printf("%d\n", n);
	}






	if(n==1) printf("%d is a happy number.\n", m);
	else printf("%d is NOT a happy number.\n", m);
	return 0;
}