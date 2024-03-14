#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_int("How many scores? ");

    int scores[n];
 //   scores[0] = get_int("Score: ");
 //   scores[1] = get_int("Score: ");
 //   scores[2] = get_int("Score: ");

    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score: ");
    }

    // Floating-point imprecision example
    printf("Average: %.20f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
}