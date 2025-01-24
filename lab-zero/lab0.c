#include <stdio.h>
/*
 * Revise lab0.c. Use a while loop to calculate the sum of positive even integers below 200 and print the
 * result to the standard output. This is very similar to the sum example we have studied. Think about how
 * much you should increase the loop control variable to get to the next even number.
 */

int main(void)
{
    int sum = 0, i = 0;
    while (i < 200) {
        sum += i;
        i += 2;
    }
    printf("Hello, World!\n");
    printf("%d\n", sum);
    return 0;
}