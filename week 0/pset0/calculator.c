// Perform simples addition
#include <cs50.h>
#include <stdio.h>

int addition(int a, int b);

int main(void)
{
    //Prompt user for x
    long x = get_long("x: ");

    //Prompt user for y
    long y = get_long("y: ");

    //Perform addition
    printf("%d\n", addition(x, y));
}


int addition(int a, int b)
{
    int result = a + b;

    return result;
}