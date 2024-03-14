// Divide x by y
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for x
    float x = get_float("x: ");

    // Prompt user for y
    float y = get_float("y: ");

    // Divide x by y
    float z = x / y;

    // Perform addition
    printf("%.5f\n", z);

}