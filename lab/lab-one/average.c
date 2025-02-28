// Only this line of comment is provided

#include <stdio.h>

int main(void)
{
    double input, total = 0;
    int numberInputed = 0;

    while (scanf("%lf", &input) == 1)
    { // pay attention to %lf
        total += input;
        numberInputed++;

        printf("Total=%f Average=%f\n", total, total / numberInputed); // pay attention to %f
    };
    return 0;
}