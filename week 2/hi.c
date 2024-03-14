#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string s = "HI!";
    string t = "BYE!";

    // Print the ASCII code of each element
    printf("%i %i %i %i %i %i %i %i %i\n", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8]);

    printf("%s %s\n", s, t);

}