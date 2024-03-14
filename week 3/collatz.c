#include <cs50.h>
#include <stdio.h>

int conjecture(int i);
int collatz(int n);

int main(void)
{
    int x = get_int("n: ");
    int c = conjecture(x);
    int n = collatz(x);
    if (c == 1)
    {
        printf("It is functioning.\n");
        printf("conjecture(%i): %i\n", x, n);
    }
    else
    {
        printf("It is not functioning.\n");
    }
}



int conjecture(int i)
{
    // Base case
    if (i == 1)
    {
        return 1;
    }
    // Even numbers
    else if ((i % 2) == 0)
    {
        return conjecture(i / 2);
    }
    // Odd numbers
    else
    {
        return conjecture(3 * i + 1);
    }
}


int collatz(int n)
{
    // Base case
    if (n == 1)
        return 0;
    // Even numbers
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);
    // Odd numbers
    else
        return 1 + collatz(3 * n + 1);
}