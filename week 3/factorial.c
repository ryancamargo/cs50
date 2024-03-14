#include <stdio.h>
#include <cs50.h>

int fact(int n);

int main(void)
{
    int x = get_int("Give the number to calculate factorial: ");
    int f = fact(x);
    printf("Result: %i\n", f);
}



// Function using recursion
int fact(int n)
{
    // Base case
    if (n == 1)
    {
        return 1;
    }

    // Recursive case
    else
    {
        return n * fact(n - 1);
    }

}




/* Function using iteration
int fact2(int n)
{
    int product = 1;
    while (n > 0)
    {
        product *= n;
        n--;
    }
    return product;
}
*/