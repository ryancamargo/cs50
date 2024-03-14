#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long x = get_long("x: ");
    long y = get_long("y: ");

    // Type casting = telling the computer to threat the variable as it was another type of variable 
    double z = (double) x / (double) y;

    printf("%.20f\n", z);
}