#include <stdio.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x); // Swap value by reference
    printf("x: %i\n", x);

    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);

}