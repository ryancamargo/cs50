#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for his name
    string name = get_string("What's your name? ");

    // Print Hello Name
    printf("hello, %s\n", name);
}
